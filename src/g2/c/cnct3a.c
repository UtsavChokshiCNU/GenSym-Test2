/* cnct3a.c
 * Input file:  connect3a.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cnct3a.h"


static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qab_gensym;          /* gensym */

static Object Qcross_section_pattern;  /* cross-section-pattern */

static Object Qconnection;         /* connection */

static Object Qjunction_block_class;  /* junction-block-class */

static Object Qsensor;             /* sensor */

static Object string_constant;     /* "Cannot join connections with incompatible cross sections." */

static Object Qconnection_style;   /* connection-style */

static Object Qdiagonal;           /* diagonal */

static Object string_constant_1;   /* "Cannot make junction for diagonal connections." */

static Object string_constant_2;   /* "Cannot join connections because there is no defined class for ~
				    *                the junction."
				    */

static Object string_constant_3;   /* "Cannot join connections because the class for the junction, ~
				    *                ~a, is not defined."
				    */

static Object string_constant_4;   /* "Cannot join connections because the class for the junction, ~
				    *                ~a, is not a subclass of ~a."
				    */

static Object string_constant_5;   /* "Cannot join a connection to itself." */

static Object Qdefault_junction;   /* default-junction */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* MAKE-JUNCTION */
Object make_junction(junction_connection,loose_end)
    Object junction_connection, loose_end;
{
    Object loose_end_connection, junction_connection_frame_or_class;
    Object loose_end_connection_frame_or_class, x2, cross_section_pattern;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp_1;
    Object temp_2, new_cons, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, cross_section_stripe, width;
    Object ab_loop_list_, ab_loopvar_, ab_loop_desetq_, temp_3;
    Object junction_block_class, x, sub_class_bit_vector;
    Object problem_format_string_qm, plist, workspace, junction_block;
    Object connection_item_table_binary_tree, element_qm, temp_4;
    Object slot_group_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_5;
    char temp;

    x_note_fn_call(101,0);
    loose_end_connection = get_connection_for_loose_end(loose_end);
    junction_connection_frame_or_class = ISVREF(junction_connection,
	    (SI_Long)1L);
    loose_end_connection_frame_or_class = ISVREF(loose_end_connection,
	    (SI_Long)1L);
    if (SIMPLE_VECTOR_P(loose_end_connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(loose_end_connection_frame_or_class)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(loose_end_connection_frame_or_class,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(loose_end_connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	cross_section_pattern = ISVREF(loose_end_connection_frame_or_class,
		(SI_Long)20L);
    else {
	if (lookup_global_or_kb_specific_property_value(loose_end_connection_frame_or_class,
		Class_description_gkbprop)) {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = loose_end_connection_frame_or_class;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(loose_end_connection_frame_or_class) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_1:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_1;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_1;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_1;
	      end_loop_1:
		gensymed_symbol = Qnil;
	      end_1:;
		goto end_2;
	    }
	    goto next_loop;
	  end_loop:
	    gensymed_symbol = Qnil;
	  end_2:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = loose_end_connection_frame_or_class;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_1,
			Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_2:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_2;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_3:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_3;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_3;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_3;
	      end_loop_3:
		kb_properties = Qnil;
	      end_3:;
		goto end_4;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    kb_properties = Qnil;
	  end_4:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_4:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_4;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_5:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_5;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_5;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_5;
		  end_loop_5:
		    kb_specific_value = Qnil;
		  end_5:;
		    goto end_6;
		}
		goto next_loop_4;
	      end_loop_4:
		kb_specific_value = Qnil;
	      end_6:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_6:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_6;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_7:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_7;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_7;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_7;
		  end_loop_7:
		    resulting_value = Qnil;
		  end_7:;
		    goto end_8;
		}
		goto next_loop_6;
	      end_loop_6:
		resulting_value = Qnil;
	      end_8:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	else {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = Qconnection;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_8:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_8;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_9:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_9;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_9;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_9;
	      end_loop_9:
		gensymed_symbol = Qnil;
	      end_9:;
		goto end_10;
	    }
	    goto next_loop_8;
	  end_loop_8:
	    gensymed_symbol = Qnil;
	  end_10:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qconnection;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_1,
			Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_10:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_10;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_11:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_11;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_11;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_11;
	      end_loop_11:
		kb_properties = Qnil;
	      end_11:;
		goto end_12;
	    }
	    goto next_loop_10;
	  end_loop_10:
	    kb_properties = Qnil;
	  end_12:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_12:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_12;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_13:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_13;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_13;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_13;
		  end_loop_13:
		    kb_specific_value = Qnil;
		  end_13:;
		    goto end_14;
		}
		goto next_loop_12;
	      end_loop_12:
		kb_specific_value = Qnil;
	      end_14:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_14:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_14;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_15:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_15;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_15;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_15;
		  end_loop_15:
		    resulting_value = Qnil;
		  end_15:;
		    goto end_16;
		}
		goto next_loop_14;
	      end_loop_14:
		resulting_value = Qnil;
	      end_16:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
    }
    temp_2 = CAAR(cross_section_pattern);
    cross_section_stripe = CONSP(temp_2) ? CDR(cross_section_pattern) : 
	    cross_section_pattern;
    width = Nil;
    ab_loop_list_ = cross_section_stripe;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_16:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_16;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
    goto next_loop_16;
  end_loop_16:
    temp_2 = ab_loopvar_;
    goto end_17;
    temp_2 = Qnil;
  end_17:;
    if (SIMPLE_VECTOR_P(junction_connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(junction_connection_frame_or_class)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(junction_connection_frame_or_class,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(junction_connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	cross_section_pattern = ISVREF(junction_connection_frame_or_class,
		(SI_Long)20L);
    else {
	if (lookup_global_or_kb_specific_property_value(junction_connection_frame_or_class,
		Class_description_gkbprop)) {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = junction_connection_frame_or_class;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(junction_connection_frame_or_class) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_17:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_17;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_18:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_18;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_18;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_18;
	      end_loop_18:
		gensymed_symbol = Qnil;
	      end_18:;
		goto end_19;
	    }
	    goto next_loop_17;
	  end_loop_17:
	    gensymed_symbol = Qnil;
	  end_19:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = junction_connection_frame_or_class;
		temp_3 = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_3,
			Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_19:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_19;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_20:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_20;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_20;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_20;
	      end_loop_20:
		kb_properties = Qnil;
	      end_20:;
		goto end_21;
	    }
	    goto next_loop_19;
	  end_loop_19:
	    kb_properties = Qnil;
	  end_21:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_21:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_21;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_22:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_22;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_22;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_22;
		  end_loop_22:
		    kb_specific_value = Qnil;
		  end_22:;
		    goto end_23;
		}
		goto next_loop_21;
	      end_loop_21:
		kb_specific_value = Qnil;
	      end_23:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_23:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_23;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_24:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_24;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_24;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_24;
		  end_loop_24:
		    resulting_value = Qnil;
		  end_24:;
		    goto end_25;
		}
		goto next_loop_23;
	      end_loop_23:
		resulting_value = Qnil;
	      end_25:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	else {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = Qconnection;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_25:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_25;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_26:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_26;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_26;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_26;
	      end_loop_26:
		gensymed_symbol = Qnil;
	      end_26:;
		goto end_27;
	    }
	    goto next_loop_25;
	  end_loop_25:
	    gensymed_symbol = Qnil;
	  end_27:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qconnection;
		temp_3 = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_3,
			Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_27:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_27;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_28:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_28;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_28;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_28;
	      end_loop_28:
		kb_properties = Qnil;
	      end_28:;
		goto end_29;
	    }
	    goto next_loop_27;
	  end_loop_27:
	    kb_properties = Qnil;
	  end_29:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_29:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_29;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_30:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_30;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_30;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_30;
		  end_loop_30:
		    kb_specific_value = Qnil;
		  end_30:;
		    goto end_31;
		}
		goto next_loop_29;
	      end_loop_29:
		kb_specific_value = Qnil;
	      end_31:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_31:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_31;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_32:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_32;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_32;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_32;
		  end_loop_32:
		    resulting_value = Qnil;
		  end_32:;
		    goto end_33;
		}
		goto next_loop_31;
	      end_loop_31:
		resulting_value = Qnil;
	      end_33:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	cross_section_pattern = ISVREF(temp_1,(SI_Long)6L);
    }
    temp_1 = CAAR(cross_section_pattern);
    cross_section_stripe = CONSP(temp_1) ? CDR(cross_section_pattern) : 
	    cross_section_pattern;
    width = Nil;
    ab_loop_list_ = cross_section_stripe;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_33:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_33;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
    goto next_loop_33;
  end_loop_33:
    temp_1 = ab_loopvar_;
    goto end_34;
    temp_1 = Qnil;
  end_34:;
    if (NUM_GT(temp_2,temp_1)) {
	if (SIMPLE_VECTOR_P(loose_end_connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(loose_end_connection_frame_or_class)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(loose_end_connection_frame_or_class,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(loose_end_connection_frame_or_class,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    junction_block_class = 
		    get_lookup_slot_value(loose_end_connection_frame_or_class,
		    Qjunction_block_class);
	else {
	    if (lookup_global_or_kb_specific_property_value(loose_end_connection_frame_or_class,
		    Class_description_gkbprop)) {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = loose_end_connection_frame_or_class;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(loose_end_connection_frame_or_class) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_34:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_34;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_35:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_35;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_35;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_35;
		  end_loop_35:
		    gensymed_symbol = Qnil;
		  end_35:;
		    goto end_36;
		}
		goto next_loop_34;
	      end_loop_34:
		gensymed_symbol = Qnil;
	      end_36:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = loose_end_connection_frame_or_class;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_36:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_36;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_37:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_37;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_37;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_37;
		  end_loop_37:
		    kb_properties = Qnil;
		  end_37:;
		    goto end_38;
		}
		goto next_loop_36;
	      end_loop_36:
		kb_properties = Qnil;
	      end_38:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_38:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_38;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_39:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_39;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_39;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_39;
		      end_loop_39:
			kb_specific_value = Qnil;
		      end_39:;
			goto end_40;
		    }
		    goto next_loop_38;
		  end_loop_38:
		    kb_specific_value = Qnil;
		  end_40:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_40:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_40;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_41:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_41;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_41;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_41;
		      end_loop_41:
			resulting_value = Qnil;
		      end_41:;
			goto end_42;
		    }
		    goto next_loop_40;
		  end_loop_40:
		    resulting_value = Qnil;
		  end_42:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qjunction_block_class,
			gensymed_symbol,Nil);
	    }
	    else {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = Qconnection;
		gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_42:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_42;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_43:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_43;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_43;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_43;
		  end_loop_43:
		    gensymed_symbol = Qnil;
		  end_43:;
		    goto end_44;
		}
		goto next_loop_42;
	      end_loop_42:
		gensymed_symbol = Qnil;
	      end_44:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = Qconnection;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_44:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_44;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_45:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_45;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_45;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_45;
		  end_loop_45:
		    kb_properties = Qnil;
		  end_45:;
		    goto end_46;
		}
		goto next_loop_44;
	      end_loop_44:
		kb_properties = Qnil;
	      end_46:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_46:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_46;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_47:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_47;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_47;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_47;
		      end_loop_47:
			kb_specific_value = Qnil;
		      end_47:;
			goto end_48;
		    }
		    goto next_loop_46;
		  end_loop_46:
		    kb_specific_value = Qnil;
		  end_48:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_48:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_48;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_49:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_49;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_49;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_49;
		      end_loop_49:
			resulting_value = Qnil;
		      end_49:;
			goto end_50;
		    }
		    goto next_loop_48;
		  end_loop_48:
		    resulting_value = Qnil;
		  end_50:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qjunction_block_class,
			gensymed_symbol,Nil);
	    }
	    junction_block_class = ISVREF(temp_2,(SI_Long)6L);
	}
    }
    else {
	if (SIMPLE_VECTOR_P(junction_connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(junction_connection_frame_or_class)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(junction_connection_frame_or_class,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(junction_connection_frame_or_class,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    junction_block_class = 
		    get_lookup_slot_value(junction_connection_frame_or_class,
		    Qjunction_block_class);
	else {
	    if (lookup_global_or_kb_specific_property_value(junction_connection_frame_or_class,
		    Class_description_gkbprop)) {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = junction_connection_frame_or_class;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(junction_connection_frame_or_class) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_50:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_50;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_51:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_51;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_51;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_51;
		  end_loop_51:
		    gensymed_symbol = Qnil;
		  end_51:;
		    goto end_52;
		}
		goto next_loop_50;
	      end_loop_50:
		gensymed_symbol = Qnil;
	      end_52:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = junction_connection_frame_or_class;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_52:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_52;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_53:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_53;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_53;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_53;
		  end_loop_53:
		    kb_properties = Qnil;
		  end_53:;
		    goto end_54;
		}
		goto next_loop_52;
	      end_loop_52:
		kb_properties = Qnil;
	      end_54:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_54:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_54;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_55:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_55;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_55;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_55;
		      end_loop_55:
			kb_specific_value = Qnil;
		      end_55:;
			goto end_56;
		    }
		    goto next_loop_54;
		  end_loop_54:
		    kb_specific_value = Qnil;
		  end_56:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_56:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_56;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_57:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_57;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_57;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_57;
		      end_loop_57:
			resulting_value = Qnil;
		      end_57:;
			goto end_58;
		    }
		    goto next_loop_56;
		  end_loop_56:
		    resulting_value = Qnil;
		  end_58:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qjunction_block_class,
			gensymed_symbol,Nil);
	    }
	    else {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = Qconnection;
		gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_58:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_58;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_59:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_59;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_59;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_59;
		  end_loop_59:
		    gensymed_symbol = Qnil;
		  end_59:;
		    goto end_60;
		}
		goto next_loop_58;
	      end_loop_58:
		gensymed_symbol = Qnil;
	      end_60:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = Qconnection;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_60:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_60;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_61:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_61;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_61;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_61;
		  end_loop_61:
		    kb_properties = Qnil;
		  end_61:;
		    goto end_62;
		}
		goto next_loop_60;
	      end_loop_60:
		kb_properties = Qnil;
	      end_62:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_62:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_62;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_63:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_63;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_63;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_63;
		      end_loop_63:
			kb_specific_value = Qnil;
		      end_63:;
			goto end_64;
		    }
		    goto next_loop_62;
		  end_loop_62:
		    kb_specific_value = Qnil;
		  end_64:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_64:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_64;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_65:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_65;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_65;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_65;
		      end_loop_65:
			resulting_value = Qnil;
		      end_65:;
			goto end_66;
		    }
		    goto next_loop_64;
		  end_loop_64:
		    resulting_value = Qnil;
		  end_66:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qjunction_block_class,
			gensymed_symbol,Nil);
	    }
	    junction_block_class = ISVREF(temp_2,(SI_Long)6L);
	}
    }
    if ( 
	    !TRUEP(connection_cross_section_patterns_compatible_qm(loose_end_connection,
	    junction_connection))) {
	x = get_block_at_other_end_of_connection(loose_end_connection,
		loose_end);
	if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		(SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(x,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qsensor,
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
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_5;
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	problem_format_string_qm = string_constant;
    else {
	plist = ISVREF(loose_end_connection,(SI_Long)9L);
	temp = plist ? EQ(getfq_function_no_default(plist,
		Qconnection_style),Qdiagonal) : TRUEP(Qnil);
	if (temp);
	else {
	    plist = ISVREF(junction_connection,(SI_Long)9L);
	    temp = plist ? EQ(getfq_function_no_default(plist,
		    Qconnection_style),Qdiagonal) : TRUEP(Qnil);
	}
	if (temp)
	    problem_format_string_qm = string_constant_1;
	else if ( !TRUEP(junction_block_class))
	    problem_format_string_qm = string_constant_2;
	else {
	    if (SYMBOLP(junction_block_class)) {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = junction_block_class;
		gensymed_symbol_2 = SXHASH_SYMBOL_1(junction_block_class) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_66:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_66;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_67:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_67;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_67;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_67;
		  end_loop_67:
		    gensymed_symbol = Qnil;
		  end_67:;
		    goto end_68;
		}
		goto next_loop_66;
	      end_loop_66:
		gensymed_symbol = Qnil;
	      end_68:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = junction_block_class;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_68:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_68;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_69:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_69;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_69;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_69;
		  end_loop_69:
		    kb_properties = Qnil;
		  end_69:;
		    goto end_70;
		}
		goto next_loop_68;
	      end_loop_68:
		kb_properties = Qnil;
	      end_70:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_70:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_70;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_71:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_71;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_71;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_71;
		      end_loop_71:
			kb_specific_value = Qnil;
		      end_71:;
			goto end_72;
		    }
		    goto next_loop_70;
		  end_loop_70:
		    kb_specific_value = Qnil;
		  end_72:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_72:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_72;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_73:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_73;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_73;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_73;
		      end_loop_73:
			resulting_value = Qnil;
		      end_73:;
			goto end_74;
		    }
		    goto next_loop_72;
		  end_loop_72:
		    resulting_value = Qnil;
		  end_74:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp = TRUEP(resulting_value);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		problem_format_string_qm = string_constant_3;
	    else {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = junction_block_class;
		gensymed_symbol_2 = SXHASH_SYMBOL_1(junction_block_class) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_74:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_74;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_75:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_75;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_75;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_75;
		  end_loop_75:
		    gensymed_symbol = Qnil;
		  end_75:;
		    goto end_76;
		}
		goto next_loop_74;
	      end_loop_74:
		gensymed_symbol = Qnil;
	      end_76:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = junction_block_class;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_76:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_76;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_77:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_77;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_77;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_77;
		  end_loop_77:
		    kb_properties = Qnil;
		  end_77:;
		    goto end_78;
		}
		goto next_loop_76;
	      end_loop_76:
		kb_properties = Qnil;
	      end_78:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_78:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_78;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_79:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_79;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_79;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_79;
		      end_loop_79:
			kb_specific_value = Qnil;
		      end_79:;
			goto end_80;
		    }
		    goto next_loop_78;
		  end_loop_78:
		    kb_specific_value = Qnil;
		  end_80:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_80:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_80;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_81:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_81;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_81;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_81;
		      end_loop_81:
			resulting_value = Qnil;
		      end_81:;
			goto end_82;
		    }
		    goto next_loop_80;
		  end_loop_80:
		    resulting_value = Qnil;
		  end_82:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Default_junction_class_description,
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
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_5;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if ( !temp)
		    problem_format_string_qm = string_constant_4;
		else if (EQ(loose_end_connection,junction_connection))
		    problem_format_string_qm = string_constant_5;
		else
		    problem_format_string_qm = Qnil;
	    }
	}
    }
    if (problem_format_string_qm) {
	notify_user(3,problem_format_string_qm,junction_block_class,
		Qdefault_junction);
	return VALUES_1(Nil);
    }
    else {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)5L) : Nil;
	workspace = gensymed_symbol;
	junction_block = make_entity(1,junction_block_class);
	update_images_of_block(loose_end,T,Nil);
	if (EQ(ISVREF(loose_end_connection,(SI_Long)2L),loose_end))
	    update_connection_images(T,workspace,loose_end_connection);
	update_connection_images(T,workspace,junction_connection);
	if (determine_position_of_and_insert_junction_block(junction_block,
		junction_connection,loose_end)) {
	    update_images_of_block(junction_block,Nil,Nil);
	    update_connection_images(Nil,workspace,junction_connection);
	    if ( !EQ(ISVREF(loose_end_connection,(SI_Long)3L),junction_block))
		update_connection_images(Nil,workspace,loose_end_connection);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)6L) : Nil;
	    if (gensymed_symbol) {
		gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)6L) : Nil;
		connection_item_table_binary_tree = gensymed_symbol;
		element_qm = M_CDR(connection_item_table_binary_tree);
		if (element_qm)
		    reclaim_connection_item_table_leaves(element_qm);
		inline_note_reclaim_cons(connection_item_table_binary_tree,
			Qab_gensym);
		temp_4 = Available_gensym_conses;
		M_CDR(connection_item_table_binary_tree) = temp_4;
		Available_gensym_conses = connection_item_table_binary_tree;
	    }
	    gensymed_symbol = loose_end;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = Nil;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp_4 = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_4;
		temp_4 = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp_4,FIX((SI_Long)6L)) = gensymed_symbol_1;
	    }
	    delete_frame(loose_end);
	    return VALUES_1(T);
	}
	else {
	    delete_frame(junction_block);
	    update_images_of_block(loose_end,Nil,Nil);
	    if (EQ(ISVREF(loose_end_connection,(SI_Long)2L),loose_end))
		update_connection_images(Nil,workspace,loose_end_connection);
	    update_connection_images(Nil,workspace,junction_connection);
	    return VALUES_1(Nil);
	}
    }
}

static Object Qleft;               /* left */

static Object Qright;              /* right */

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

static Object Qbegin_corner;       /* begin-corner */

static Object Qend_corner;         /* end-corner */

/* DETERMINE-POSITION-OF-AND-INSERT-JUNCTION-BLOCK */
Object determine_position_of_and_insert_junction_block(junction_block,
	    junction_connection,loose_end)
    Object junction_block, junction_connection, loose_end;
{
    Object gensymed_symbol, temp, temp_1, connection, distance;
    Object intercept_or_corner, rest_of_deltas;
    Object x_position_of_intercept_or_corner;
    Object y_position_of_intercept_or_corner, orientation_horizontal_p;
    Object connection_being_dragged, junction_block_input_end_side;
    Object junction_block_output_end_side;
    Object junction_block_connection_being_dragged_end_side;
    Object inhibit_insertion_p, temp_2, link_2_delta;
    Object link_2_orientation_horizontal_p, new_rest_of_deltas;
    Object try_to_insert_again_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,1);
    add_missing_deltas_to_connection(junction_connection);
    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    result = find_vector_length_from_point_to_connection_if_within_limit(junction_connection,
	    temp,temp_1,mouse_leeway_in_workspace(FIX((SI_Long)4096L)));
    MVS_7(result,connection,distance,intercept_or_corner,rest_of_deltas,
	    x_position_of_intercept_or_corner,
	    y_position_of_intercept_or_corner,orientation_horizontal_p);
    PUSH_SPECIAL(Orientation_horizontal_p,orientation_horizontal_p,0);
      if (connection) {
	  connection_being_dragged = get_connection_for_loose_end(loose_end);
	  junction_block_input_end_side = Nil;
	  junction_block_output_end_side = Nil;
	  junction_block_connection_being_dragged_end_side = Nil;
	  inhibit_insertion_p = Nil;
	  result = compute_stretched_links_of_connection_being_dragged(connection_being_dragged,
		  loose_end);
	  MVS_3(result,temp_1,link_2_delta,link_2_orientation_horizontal_p);
	  junction_block_connection_being_dragged_end_side = 
		  link_2_orientation_horizontal_p ? (IFIX(link_2_delta) > 
		  (SI_Long)0L ? Qleft : Qright) : IFIX(link_2_delta) > 
		  (SI_Long)0L ? Qtop : Qbottom;
	  if (NUMBERP(intercept_or_corner)) {
	      temp_1 = FIXNUM_ABS(intercept_or_corner);
	      gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)2L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)0L) : FIX((SI_Long)0L);
	      gensymed_symbol_2 = IFIX(gensymed_symbol);
	      if (FIXNUM_LT(temp_1,FIX(gensymed_symbol_1 - 
			  gensymed_symbol_2))) {
		  if (Orientation_horizontal_p)
		      x_position_of_intercept_or_corner = 
			      FIXNUM_MINUS(x_position_of_intercept_or_corner,
			      intercept_or_corner);
		  else
		      y_position_of_intercept_or_corner = 
			      FIXNUM_MINUS(y_position_of_intercept_or_corner,
			      intercept_or_corner);
		  intercept_or_corner = Qbegin_corner;
		  temp_3 = TRUEP(T);
	      }
	      else
		  temp_3 = TRUEP(Nil);
	  }
	  else
	      temp_3 = EQ(intercept_or_corner,Qbegin_corner);
	  if (temp_3) {
	      if ( !EQ(rest_of_deltas,ISVREF(junction_connection,
			  (SI_Long)6L))) {
		  new_rest_of_deltas = ISVREF(junction_connection,(SI_Long)6L);
		next_loop:
		  if ( !TRUEP(new_rest_of_deltas))
		      goto end_loop;
		  if (EQ(CDR(new_rest_of_deltas),rest_of_deltas))
		      goto end_loop;
		  new_rest_of_deltas = M_CDR(new_rest_of_deltas);
		  goto next_loop;
		end_loop:
		  rest_of_deltas = new_rest_of_deltas;
		  junction_block_input_end_side = Orientation_horizontal_p 
			  ? (IFIX(CAR(rest_of_deltas)) > (SI_Long)0L ? 
			  Qtop : Qbottom) : IFIX(CAR(rest_of_deltas)) > 
			  (SI_Long)0L ? Qleft : Qright;
		  junction_block_output_end_side = 
			  Orientation_horizontal_p ? 
			  (IFIX(CADR(rest_of_deltas)) > (SI_Long)0L ? 
			  Qright : Qleft) : IFIX(CADR(rest_of_deltas)) > 
			  (SI_Long)0L ? Qbottom : Qtop;
	      }
	      else
		  inhibit_insertion_p = T;
	      temp_3 = TRUEP(T);
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if (temp_3);
	  else {
	      if (NUMBERP(intercept_or_corner)) {
		  temp_1 = FIXNUM_MINUS(CAR(rest_of_deltas),
			  intercept_or_corner);
		  temp_1 = FIXNUM_ABS(temp_1);
		  gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)2L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol);
		  gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)0L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_2 = IFIX(gensymed_symbol);
		  if (FIXNUM_LT(temp_1,FIX(gensymed_symbol_1 - 
			  gensymed_symbol_2))) {
		      if (Orientation_horizontal_p)
			  x_position_of_intercept_or_corner = 
				  FIXNUM_ADD(x_position_of_intercept_or_corner,
				  FIXNUM_MINUS(CAR(rest_of_deltas),
				  intercept_or_corner));
		      else
			  y_position_of_intercept_or_corner = 
				  FIXNUM_ADD(y_position_of_intercept_or_corner,
				  FIXNUM_MINUS(CAR(rest_of_deltas),
				  intercept_or_corner));
		      intercept_or_corner = Qend_corner;
		      temp_3 = TRUEP(T);
		  }
		  else
		      temp_3 = TRUEP(Nil);
	      }
	      else
		  temp_3 = EQ(intercept_or_corner,Qend_corner);
	      if (temp_3) {
		  if ( ! !TRUEP(CDR(rest_of_deltas))) {
		      junction_block_input_end_side = 
			      Orientation_horizontal_p ? 
			      (IFIX(CAR(rest_of_deltas)) > (SI_Long)0L ? 
			      Qleft : Qright) : IFIX(CAR(rest_of_deltas)) 
			      > (SI_Long)0L ? Qtop : Qbottom;
		      junction_block_output_end_side = 
			      Orientation_horizontal_p ? 
			      (IFIX(CADR(rest_of_deltas)) > (SI_Long)0L ? 
			      Qbottom : Qtop) : IFIX(CADR(rest_of_deltas)) 
			      > (SI_Long)0L ? Qright : Qleft;
		  }
		  else
		      inhibit_insertion_p = T;
		  temp_3 = TRUEP(T);
	      }
	      else
		  temp_3 = TRUEP(Nil);
	  }
	  if (temp_3) {
	      if ( !TRUEP(inhibit_insertion_p) &&  
		      !(EQ(junction_block_connection_being_dragged_end_side,
		      junction_block_input_end_side) || 
		      EQ(junction_block_connection_being_dragged_end_side,
		      junction_block_output_end_side))) {
		  insert_junction_block(junction_block,junction_connection,
			  loose_end,connection_being_dragged,
			  junction_block_input_end_side,
			  junction_block_output_end_side,
			  junction_block_connection_being_dragged_end_side,
			  intercept_or_corner,rest_of_deltas,
			  x_position_of_intercept_or_corner,
			  y_position_of_intercept_or_corner);
		  result = VALUES_1(T);
	      }
	      else {
		  remove_redundant_deltas_from_connection(junction_connection);
		  result = VALUES_1(Nil);
	      }
	  }
	  else if (Orientation_horizontal_p && 
		  link_2_orientation_horizontal_p ||  
		  !TRUEP(Orientation_horizontal_p) &&  
		  !TRUEP(link_2_orientation_horizontal_p)) {
	      temp_1 = l_abs(link_2_delta);
	      if (FIXNUM_LT(temp_1,
		      mouse_leeway_in_workspace(FIX((SI_Long)4096L)))) {
		  if ( !TRUEP(ISVREF(connection_being_dragged,(SI_Long)6L))) {
		      if (IFIX(link_2_delta) > (SI_Long)0L && 
			      IFIX(CAR(rest_of_deltas)) > (SI_Long)0L ||  
			      !(IFIX(link_2_delta) > (SI_Long)0L) &&  
			      !(IFIX(CAR(rest_of_deltas)) > (SI_Long)0L)) {
			  temp_1 = FIXNUM_MINUS(intercept_or_corner,
				  link_2_delta);
			  temp_1 = FIXNUM_ABS(temp_1);
			  gensymed_symbol = ISVREF(junction_block,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)2L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_1 = IFIX(gensymed_symbol);
			  gensymed_symbol = ISVREF(junction_block,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)0L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_2 = IFIX(gensymed_symbol);
			  temp_3 = FIXNUM_LT(temp_1,FIX(gensymed_symbol_1 
				  - gensymed_symbol_2));
		      }
		      else {
			  temp_1 = 
				  FIXNUM_MINUS(FIXNUM_MINUS(CAR(rest_of_deltas),
				  intercept_or_corner),
				  FIXNUM_NEGATE(link_2_delta));
			  temp_1 = FIXNUM_ABS(temp_1);
			  gensymed_symbol = ISVREF(junction_block,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)2L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_1 = IFIX(gensymed_symbol);
			  gensymed_symbol = ISVREF(junction_block,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)0L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_2 = IFIX(gensymed_symbol);
			  temp_3 = FIXNUM_LT(temp_1,FIX(gensymed_symbol_1 
				  - gensymed_symbol_2));
		      }
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  try_to_insert_again_qm =  !temp_3 ? T : Nil;
	      }
	      else
		  try_to_insert_again_qm = Nil;
	      remove_redundant_deltas_from_connection(junction_connection);
	      if (try_to_insert_again_qm) {
		  delete_last_bend_from_connection(connection_being_dragged,
			  loose_end);
		  result = determine_position_of_and_insert_junction_block(junction_block,
			  junction_connection,loose_end);
	      }
	      else
		  result = VALUES_1(Nil);
	  }
	  else {
	      junction_block_input_end_side = Orientation_horizontal_p ? 
		      (IFIX(CAR(rest_of_deltas)) > (SI_Long)0L ? Qleft : 
		      Qright) : IFIX(CAR(rest_of_deltas)) > (SI_Long)0L ? 
		      Qtop : Qbottom;
	      if (EQ(junction_block_input_end_side,Qleft))
		  junction_block_output_end_side = Qright;
	      else if (EQ(junction_block_input_end_side,Qright))
		  junction_block_output_end_side = Qleft;
	      else if (EQ(junction_block_input_end_side,Qtop))
		  junction_block_output_end_side = Qbottom;
	      else
		  junction_block_output_end_side = Qtop;
	      insert_junction_block(junction_block,junction_connection,
		      loose_end,connection_being_dragged,
		      junction_block_input_end_side,
		      junction_block_output_end_side,
		      junction_block_connection_being_dragged_end_side,
		      intercept_or_corner,rest_of_deltas,
		      x_position_of_intercept_or_corner,
		      y_position_of_intercept_or_corner);
	      result = VALUES_1(T);
	  }
      }
      else {
	  remove_redundant_deltas_from_connection(junction_connection);
	  result = VALUES_1(Nil);
      }
    POP_SPECIAL();
    return result;
}

static Object Qconnection_item_table;  /* connection-item-table */

static Object Qoutput;             /* output */

static Object Qjunction_block_connection_1;  /* junction-block-connection-1 */

static Object Qjunction_block_connection_2;  /* junction-block-connection-2 */

static Object Qinput;              /* input */

static Object Qjunction_block_connection_3;  /* junction-block-connection-3 */

/* INSERT-JUNCTION-BLOCK */
Object insert_junction_block(junction_block,junction_connection,loose_end,
	    connection_being_dragged,input_end_side,output_end_side,
	    connection_being_dragged_end_side,intercept_or_corner,
	    rest_of_deltas,x_position_of_intercept_or_corner,
	    y_position_of_intercept_or_corner)
    Object junction_block, junction_connection, loose_end;
    Object connection_being_dragged, input_end_side, output_end_side;
    Object connection_being_dragged_end_side, intercept_or_corner;
    Object rest_of_deltas, x_position_of_intercept_or_corner;
    Object y_position_of_intercept_or_corner;
{
    Object gensymed_symbol, temp, temp_1, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection;
    Object ab_less_than_branch_qm_, noting_changes_to_kb_p;
    Object junction_block_connection_1, connection_1_connection_frame_or_class;
    Object connection_1_connection_class, connection_1_input_end_object;
    Object connection_1_output_end_object, junction_block_connection_2;
    Object junction_block_connection_1_last_delta;
    Object junction_block_connection_2_first_delta;
    Object junction_block_connection_2_connection_frame_qm;
    Object junction_on_corner_p, temp_3, new_cons, connection_table;
    Object connection_item_1, connection_item_2, connection_item_3;
    Object gensymed_symbol_3, slot_group_qm, rest_of_old_deltas;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, junction_block_half_width;
    SI_Long count_1, svref_new_value, delta;
    char temp_2, connection_1_transient_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,2);
    gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    junction_block_half_width = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    shift_block(junction_block,FIX(IFIX(x_position_of_intercept_or_corner) 
	    - junction_block_half_width),
	    FIX(IFIX(y_position_of_intercept_or_corner) - 
	    junction_block_half_width));
    if (EQ(connection_being_dragged_end_side,Qleft)) {
	gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(connection_being_dragged_end_side,Qright)) {
	gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else {
	gensymed_symbol_1 = IFIX(x_position_of_intercept_or_corner);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    if (EQ(connection_being_dragged_end_side,Qtop)) {
	gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(connection_being_dragged_end_side,Qbottom)) {
	gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else {
	gensymed_symbol_1 = IFIX(y_position_of_intercept_or_corner);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    change_connection_deltas_for_object_being_dragged(connection_being_dragged,
	    loose_end,temp,temp_1);
    temp_2 = TRUEP(Noting_changes_to_kb_p);
    if (temp_2);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(junction_connection,(SI_Long)7L)) 
		& (SI_Long)128L;
	temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_2)
	note_change_to_connection_1(junction_connection);
    temp_2 = TRUEP(Noting_changes_to_kb_p);
    if (temp_2);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(connection_being_dragged,
		(SI_Long)7L)) & (SI_Long)128L;
	temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_2)
	note_change_to_connection_1(connection_being_dragged);
    count_1 = (SI_Long)0L;
  next_loop:
    if (count_1 > (SI_Long)10000L)
	cerror((SI_Long)2L,"Continue",
		"Probable infinite loop while inserting junction");
    gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_2 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
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
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
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
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_2;
    end_loop_2:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_3;
      connection = ab_connection_;
      delete_connection(1,connection);
      goto end_2;
      goto next_loop_1;
    end_loop_3:
    end_2:;
    POP_SPECIAL();
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)5L) : Nil;
    add_subblock(junction_block,gensymed_symbol);
    noting_changes_to_kb_p = Nil;
    PUSH_SPECIAL(Noting_changes_to_kb_p,noting_changes_to_kb_p,0);
      junction_block_connection_1 = junction_connection;
      connection_1_connection_frame_or_class = 
	      ISVREF(junction_block_connection_1,(SI_Long)1L);
      connection_1_transient_p = (SI_Long)0L != 
	      (IFIX(ISVREF(junction_block_connection_1,(SI_Long)7L)) & 
	      (SI_Long)64L);
      connection_1_connection_class = 
	      SYMBOLP(connection_1_connection_frame_or_class) ? 
	      connection_1_connection_frame_or_class : 
	      ISVREF(ISVREF(connection_1_connection_frame_or_class,
	      (SI_Long)1L),(SI_Long)1L);
      connection_1_input_end_object = ISVREF(junction_block_connection_1,
	      (SI_Long)3L);
      connection_1_output_end_object = ISVREF(junction_block_connection_1,
	      (SI_Long)2L);
      junction_block_connection_2 = make_connection_1();
      junction_block_connection_1_last_delta = Nil;
      junction_block_connection_2_first_delta = Nil;
      junction_block_connection_2_connection_frame_qm = Nil;
      junction_on_corner_p = Nil;
      if ( !connection_1_transient_p) {
	  svref_new_value = IFIX(ISVREF(junction_block_connection_2,
		  (SI_Long)7L)) | (SI_Long)2L;
	  ISVREF(junction_block_connection_2,(SI_Long)7L) = 
		  FIX(svref_new_value);
      }
      temp_3 = 
	      copy_frame_serial_number(increment_current_frame_serial_number());
      SVREF(junction_block_connection_2,FIX((SI_Long)10L)) = temp_3;
      decache_roles_for_entities_related_to_this_connection(junction_block_connection_1);
      decache_roles_for_entities_related_to_this_connection(connection_being_dragged);
      new_cons = Available_gensym_conses;
      if (new_cons) {
	  Available_gensym_conses = M_CDR(new_cons);
	  gensymed_symbol = new_cons;
      }
      else
	  gensymed_symbol = Nil;
      if ( !TRUEP(gensymed_symbol))
	  gensymed_symbol = replenish_gensym_cons_pool();
      M_CAR(gensymed_symbol) = Qconnection_item_table;
      M_CDR(gensymed_symbol) = Nil;
      inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
      connection_table = gensymed_symbol;
      connection_item_1 = make_connection_item_1(junction_block_connection_1);
      connection_item_2 = make_connection_item_1(junction_block_connection_2);
      connection_item_3 = make_connection_item_1(connection_being_dragged);
      temp = get_direction_of_connection(2,junction_block_connection_1,
	      connection_1_input_end_object);
      if (EQ(temp,Qoutput)) {
	  temp_3 = gensym_cons_1(Qjunction_block_connection_1,Nil);
	  SVREF(connection_item_1,FIX((SI_Long)2L)) = temp_3;
      }
      else {
	  temp_3 = gensym_cons_1(Qjunction_block_connection_1,Nil);
	  SVREF(connection_item_1,FIX((SI_Long)1L)) = temp_3;
      }
      temp = get_direction_of_connection(2,junction_block_connection_2,
	      connection_1_output_end_object);
      if (EQ(temp,Qoutput)) {
	  temp_3 = gensym_cons_1(Qjunction_block_connection_2,Nil);
	  SVREF(connection_item_2,FIX((SI_Long)2L)) = temp_3;
      }
      else {
	  temp_3 = gensym_cons_1(Qjunction_block_connection_2,Nil);
	  SVREF(connection_item_2,FIX((SI_Long)1L)) = temp_3;
      }
      temp = get_direction_of_connection(2,connection_being_dragged,loose_end);
      if (EQ(temp,Qinput)) {
	  temp_3 = gensym_cons_1(Qjunction_block_connection_3,Nil);
	  SVREF(connection_item_3,FIX((SI_Long)2L)) = temp_3;
      }
      else {
	  temp_3 = gensym_cons_1(Qjunction_block_connection_3,Nil);
	  SVREF(connection_item_3,FIX((SI_Long)1L)) = temp_3;
      }
      gensymed_symbol = junction_block_connection_1;
      set_balanced_binary_tree_entry(connection_table,Qeq,Nil,T,
	      gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	      IFIX(Most_positive_fixnum)),connection_item_1);
      gensymed_symbol = junction_block_connection_2;
      set_balanced_binary_tree_entry(connection_table,Qeq,Nil,T,
	      gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	      IFIX(Most_positive_fixnum)),connection_item_2);
      gensymed_symbol = connection_being_dragged;
      set_balanced_binary_tree_entry(connection_table,Qeq,Nil,T,
	      gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	      IFIX(Most_positive_fixnum)),connection_item_3);
      gensymed_symbol = junction_block;
      gensymed_symbol_3 = Nil;
      slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
      gensymed_symbol_3 = connection_table;
      if (slot_group_qm)
	  SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_3;
      else if ( !EQ(gensymed_symbol_3,Qnil)) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	  temp_3 = make_icon_slot_group_1();
	  SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_3;
	  temp_3 = ISVREF(gensymed_symbol,(SI_Long)14L);
	  SVREF(temp_3,FIX((SI_Long)6L)) = gensymed_symbol_3;
      }
      set_output_end_of_connection_1(junction_block_connection_2,
	      connection_1_output_end_object,
	      ISVREF(junction_block_connection_1,(SI_Long)4L));
      if (EQ(output_end_side,Qtop))
	  gensymed_symbol_1 = (SI_Long)0L;
      else if (EQ(output_end_side,Qleft))
	  gensymed_symbol_1 = (SI_Long)1L;
      else if (EQ(output_end_side,Qbottom))
	  gensymed_symbol_1 = (SI_Long)2L;
      else
	  gensymed_symbol_1 = (SI_Long)3L;
      gensymed_symbol_2 = junction_block_half_width << (SI_Long)2L;
      set_input_end_of_connection_1(junction_block_connection_2,
	      junction_block,FIX(gensymed_symbol_1 + gensymed_symbol_2));
      if (EQ(input_end_side,Qtop))
	  gensymed_symbol_1 = (SI_Long)0L;
      else if (EQ(input_end_side,Qleft))
	  gensymed_symbol_1 = (SI_Long)1L;
      else if (EQ(input_end_side,Qbottom))
	  gensymed_symbol_1 = (SI_Long)2L;
      else
	  gensymed_symbol_1 = (SI_Long)3L;
      gensymed_symbol_2 = junction_block_half_width << (SI_Long)2L;
      set_output_end_of_connection_1(junction_block_connection_1,
	      junction_block,FIX(gensymed_symbol_1 + gensymed_symbol_2));
      if (connection_1_transient_p) {
	  svref_new_value = IFIX(ISVREF(junction_block_connection_2,
		  (SI_Long)7L)) | (SI_Long)64L;
	  ISVREF(junction_block_connection_2,(SI_Long)7L) = 
		  FIX(svref_new_value);
      }
      if (connection_1_transient_p || 
	      always_instantiate_connection_frame_for_this_class_qm(connection_1_connection_class)) 
		  {
	  junction_block_connection_2_connection_frame_qm = 
		  make_new_connection_frame_for_connection(junction_block_connection_2,
		  connection_1_connection_class);
	  temp = junction_block_connection_2_connection_frame_qm;
	  gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)5L) : Nil;
	  activate_connection_frame_if_appropriate(temp,gensymed_symbol);
      }
      else
	  SVREF(junction_block_connection_2,FIX((SI_Long)1L)) = 
		  connection_1_connection_class;
      if ((SI_Long)0L != (IFIX(ISVREF(junction_block_connection_1,
	      (SI_Long)7L)) & (SI_Long)1L)) {
	  temp_2 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_2);
	  else {
	      gensymed_symbol_1 = IFIX(ISVREF(junction_block_connection_2,
		      (SI_Long)7L)) & (SI_Long)128L;
	      temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_2)
	      note_change_to_connection_1(junction_block_connection_2);
	  svref_new_value = IFIX(ISVREF(junction_block_connection_2,
		  (SI_Long)7L)) | (SI_Long)1L;
	  ISVREF(junction_block_connection_2,(SI_Long)7L) = 
		  FIX(svref_new_value);
      }
      else {
	  temp_2 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_2);
	  else {
	      gensymed_symbol_1 = IFIX(ISVREF(junction_block_connection_2,
		      (SI_Long)7L)) & (SI_Long)128L;
	      temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_2)
	      note_change_to_connection_1(junction_block_connection_2);
	  svref_new_value = IFIX(ISVREF(junction_block_connection_2,
		  (SI_Long)7L)) &  ~(SI_Long)1L;
	  ISVREF(junction_block_connection_2,(SI_Long)7L) = 
		  FIX(svref_new_value);
      }
      clone_connection_attributes_plist(junction_block_connection_1,
	      junction_block_connection_2);
      replace_connection_in_block(connection_1_output_end_object,
	      junction_block_connection_1,junction_block_connection_2);
      if (G2_has_v5_mode_windows_p)
	  send_ws_representations_item_insert_as_subblock(junction_block_connection_2,
		  junction_block,Nil);
      if (EQ(ISVREF(connection_being_dragged,(SI_Long)3L),loose_end)) {
	  if (EQ(connection_being_dragged_end_side,Qtop))
	      gensymed_symbol_1 = (SI_Long)0L;
	  else if (EQ(connection_being_dragged_end_side,Qleft))
	      gensymed_symbol_1 = (SI_Long)1L;
	  else if (EQ(connection_being_dragged_end_side,Qbottom))
	      gensymed_symbol_1 = (SI_Long)2L;
	  else
	      gensymed_symbol_1 = (SI_Long)3L;
	  gensymed_symbol_2 = junction_block_half_width << (SI_Long)2L;
	  set_input_end_of_connection_1(connection_being_dragged,
		  junction_block,FIX(gensymed_symbol_1 + gensymed_symbol_2));
	  if (G2_has_v5_mode_windows_p) {
	      temp = 
		      get_or_make_connection_frame_and_activate_if_appropriate(connection_being_dragged);
	      gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)5L) : Nil;
	      temp_1 = gensymed_symbol;
	      send_ws_representations_item_layer_change(temp,temp_1,
		      get_or_make_connection_frame_and_activate_if_appropriate(junction_block_connection_2));
	  }
      }
      else {
	  if (EQ(connection_being_dragged_end_side,Qtop))
	      gensymed_symbol_1 = (SI_Long)0L;
	  else if (EQ(connection_being_dragged_end_side,Qleft))
	      gensymed_symbol_1 = (SI_Long)1L;
	  else if (EQ(connection_being_dragged_end_side,Qbottom))
	      gensymed_symbol_1 = (SI_Long)2L;
	  else
	      gensymed_symbol_1 = (SI_Long)3L;
	  gensymed_symbol_2 = junction_block_half_width << (SI_Long)2L;
	  set_output_end_of_connection_1(connection_being_dragged,
		  junction_block,FIX(gensymed_symbol_1 + gensymed_symbol_2));
      }
      update_runtime_structures_according_to_edit(1,
	      junction_block_connection_1);
      update_runtime_structures_according_to_edit(1,connection_being_dragged);
      if (junction_block_connection_2_connection_frame_qm)
	  update_runtime_structures_according_to_edit(1,
		  junction_block_connection_2_connection_frame_qm);
      if (FIXNUMP(intercept_or_corner)) {
	  delta = IFIX(intercept_or_corner) > (SI_Long)0L ? 
		  junction_block_half_width :  - junction_block_half_width;
	  junction_block_connection_1_last_delta = 
		  FIX(IFIX(intercept_or_corner) - delta);
	  junction_block_connection_2_first_delta = 
		  FIX(IFIX(FIXNUM_MINUS(CAR(rest_of_deltas),
		  intercept_or_corner)) - delta);
      }
      else {
	  junction_block_connection_1_last_delta = CAR(rest_of_deltas);
	  junction_block_connection_2_first_delta = CADR(rest_of_deltas);
	  rest_of_deltas = CDR(rest_of_deltas);
	  junction_on_corner_p = T;
      }
      if (EQ(ISVREF(junction_block_connection_1,(SI_Long)6L),rest_of_deltas)) {
	  temp_2 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_2);
	  else {
	      gensymed_symbol_1 = IFIX(ISVREF(junction_block_connection_1,
		      (SI_Long)7L)) & (SI_Long)128L;
	      temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_2)
	      note_change_to_connection_1(junction_block_connection_1);
	  SVREF(junction_block_connection_1,FIX((SI_Long)6L)) = 
		  junction_block_connection_1_last_delta;
	  M_CAR(rest_of_deltas) = junction_block_connection_2_first_delta;
	  temp_2 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_2);
	  else {
	      gensymed_symbol_1 = IFIX(ISVREF(junction_block_connection_2,
		      (SI_Long)7L)) & (SI_Long)128L;
	      temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_2)
	      note_change_to_connection_1(junction_block_connection_2);
	  SVREF(junction_block_connection_2,FIX((SI_Long)6L)) = rest_of_deltas;
      }
      else {
	  rest_of_old_deltas = ISVREF(junction_block_connection_1,(SI_Long)6L);
	next_loop_4:
	  if ( !TRUEP(rest_of_old_deltas))
	      goto end_loop_4;
	  if (EQ(CDR(rest_of_old_deltas),rest_of_deltas))
	      goto end_loop_4;
	  rest_of_old_deltas = M_CDR(rest_of_old_deltas);
	  goto next_loop_4;
	end_loop_4:
	  M_CAR(rest_of_deltas) = junction_block_connection_2_first_delta;
	  temp_2 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_2);
	  else {
	      gensymed_symbol_1 = IFIX(ISVREF(junction_block_connection_2,
		      (SI_Long)7L)) & (SI_Long)128L;
	      temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_2)
	      note_change_to_connection_1(junction_block_connection_2);
	  SVREF(junction_block_connection_2,FIX((SI_Long)6L)) = rest_of_deltas;
	  if (junction_on_corner_p) {
	      M_CAR(rest_of_old_deltas) = 
		      junction_block_connection_1_last_delta;
	      M_CDR(rest_of_old_deltas) = Nil;
	  }
	  else {
	      temp_3 = 
		      gensym_cons_1(junction_block_connection_1_last_delta,
		      Nil);
	      M_CDR(rest_of_old_deltas) = temp_3;
	  }
      }
      remove_redundant_deltas_from_connection(junction_block_connection_1);
      remove_redundant_deltas_from_connection(junction_block_connection_2);
      result = send_ws_representations_connection_moved(junction_block_connection_2);
    POP_SPECIAL();
    return result;
}

Object Objects_to_not_consider_qm = UNBOUND;

/* FIND-VECTOR-LENGTH-FROM-POINT-TO-BLOCK-CONNECTIONS-IF-WITHIN-LIMIT */
Object find_vector_length_from_point_to_block_connections_if_within_limit(x_in_workspace,
	    y_in_workspace,block,standard_maximum_distance_to_allow,
	    objects_to_not_consider_qm)
    Object x_in_workspace, y_in_workspace, block;
    Object standard_maximum_distance_to_allow, objects_to_not_consider_qm;
{
    Object nearest_connection_qm, nearest_distance_qm;
    Object maximum_distance_to_allow, scope_conses, ab_node_stack_;
    Object ab_current_node_, gensymed_symbol, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object temp, ab_less_than_branch_qm_, connection_frame_or_class, x2;
    Object cross_section_pattern, gensymed_symbol_1, gensymed_symbol_4, temp_2;
    Object new_cons, global_properties, kb_properties, kb_specific_value;
    Object resulting_value, cross_section_stripe, width, ab_loop_list_;
    Object ab_loopvar_, ab_loop_desetq_;
    Object geometric_change_to_connection_is_temporary_p;
    Object this_connection_nearest_connection_qm;
    Object this_connection_nearest_distance_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, half_width_of_connection;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(101,3);
    PUSH_SPECIAL(Objects_to_not_consider_qm,objects_to_not_consider_qm,2);
      if ( !TRUEP(Objects_to_not_consider_qm) ||  
	      !TRUEP(memq_function(block,Objects_to_not_consider_qm))) {
	  nearest_connection_qm = Nil;
	  nearest_distance_qm = Nil;
	  maximum_distance_to_allow = Nil;
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  gensymed_symbol = ISVREF(block,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)6L) : Nil;
	  ab_skip_list_form_ = gensymed_symbol;
	  ab_skip_list_p_ = Nil;
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  ab_connection_ = Nil;
	  ab_connection_item_ = Nil;
	  connection = Nil;
	  PUSH_SPECIAL(Scope_conses,scope_conses,1);
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
			ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L);
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
		    ab_next_node_ = ISVREF(ISVREF(ab_current_node_,
			    (SI_Long)0L),(SI_Long)0L);
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
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
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
	    if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		    ab_connection_ && EQ(ISVREF(ab_connection_,
		    (SI_Long)3L),block))
		goto end_1;
	    goto next_loop_1;
	  end_loop_1:
	  end_1:
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_2;
	    connection = ab_connection_;
	    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		cross_section_pattern = ISVREF(connection_frame_or_class,
			(SI_Long)20L);
	    else {
		if (lookup_global_or_kb_specific_property_value(connection_frame_or_class,
			Class_description_gkbprop)) {
		    gensymed_symbol = CDR(Symbol_properties_table);
		    gensymed_symbol_1 = connection_frame_or_class;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(connection_frame_or_class) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_3:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_3;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_4:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_4;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			    goto end_2;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_4;
		      end_loop_4:
			gensymed_symbol = Qnil;
		      end_2:;
			goto end_3;
		    }
		    goto next_loop_3;
		  end_loop_3:
		    gensymed_symbol = Qnil;
		  end_3:;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = connection_frame_or_class;
			temp_2 = Symbol_properties_table;
			temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			new_cons = Available_gensym_conses;
			if (new_cons) {
			    Available_gensym_conses = M_CDR(new_cons);
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_gensym_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			M_CDR(gensymed_symbol_1) = Nil;
			inline_note_allocate_cons(gensymed_symbol_1,
				Qab_gensym);
			gensymed_symbol = 
				set_balanced_binary_tree_entry(temp_2,Qeq,
				Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = 
			    Current_kb_specific_property_list_property_name;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			    & IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_5:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_5;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_6:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_6;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_properties = M_CDR(M_CAR(gensymed_symbol));
			    goto end_4;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_6;
		      end_loop_6:
			kb_properties = Qnil;
		      end_4:;
			goto end_5;
		    }
		    goto next_loop_5;
		  end_loop_5:
		    kb_properties = Qnil;
		  end_5:;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			gensymed_symbol = CDR(kb_properties);
			gensymed_symbol_1 = Class_description_gkbprop;
			gensymed_symbol_2 = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			gensymed_symbol_3 = (SI_Long)0L;
		      next_loop_7:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_7;
			gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
				(SI_Long)0L));
			if (gensymed_symbol_2 < gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)1L);
			else if (gensymed_symbol_2 > gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)2L);
			else {
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)3L);
			    gensymed_symbol_4 = Nil;
			  next_loop_8:
			    if ( !TRUEP(gensymed_symbol))
				goto end_loop_8;
			    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
				kb_specific_value = 
					M_CDR(M_CAR(gensymed_symbol));
				goto end_6;
			    }
			    gensymed_symbol = M_CDR(gensymed_symbol);
			    goto next_loop_8;
			  end_loop_8:
			    kb_specific_value = Qnil;
			  end_6:;
			    goto end_7;
			}
			goto next_loop_7;
		      end_loop_7:
			kb_specific_value = Qnil;
		      end_7:;
			if (kb_specific_value);
			else
			    kb_specific_value = No_specific_property_value;
		    }
		    else
			kb_specific_value = No_specific_property_value;
		    if ( !EQ(kb_specific_value,No_specific_property_value))
			resulting_value = kb_specific_value;
		    else {
			gensymed_symbol = CDR(global_properties);
			gensymed_symbol_1 = Class_description_gkbprop;
			gensymed_symbol_2 = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			gensymed_symbol_3 = (SI_Long)0L;
		      next_loop_9:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_9;
			gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
				(SI_Long)0L));
			if (gensymed_symbol_2 < gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)1L);
			else if (gensymed_symbol_2 > gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)2L);
			else {
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)3L);
			    gensymed_symbol_4 = Nil;
			  next_loop_10:
			    if ( !TRUEP(gensymed_symbol))
				goto end_loop_10;
			    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
				resulting_value = 
					M_CDR(M_CAR(gensymed_symbol));
				goto end_8;
			    }
			    gensymed_symbol = M_CDR(gensymed_symbol);
			    goto next_loop_10;
			  end_loop_10:
			    resulting_value = Qnil;
			  end_8:;
			    goto end_9;
			}
			goto next_loop_9;
		      end_loop_9:
			resulting_value = Qnil;
		      end_9:;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    temp = 
			    get_slot_description_of_class_description_function(Qcross_section_pattern,
			    gensymed_symbol,Nil);
		}
		else {
		    gensymed_symbol = CDR(Symbol_properties_table);
		    gensymed_symbol_1 = Qconnection;
		    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_11:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_11;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_12:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_12;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			    goto end_10;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_12;
		      end_loop_12:
			gensymed_symbol = Qnil;
		      end_10:;
			goto end_11;
		    }
		    goto next_loop_11;
		  end_loop_11:
		    gensymed_symbol = Qnil;
		  end_11:;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = Qconnection;
			temp_2 = Symbol_properties_table;
			temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			new_cons = Available_gensym_conses;
			if (new_cons) {
			    Available_gensym_conses = M_CDR(new_cons);
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_gensym_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			M_CDR(gensymed_symbol_1) = Nil;
			inline_note_allocate_cons(gensymed_symbol_1,
				Qab_gensym);
			gensymed_symbol = 
				set_balanced_binary_tree_entry(temp_2,Qeq,
				Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = 
			    Current_kb_specific_property_list_property_name;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			    & IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_13:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_13;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_14:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_14;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_properties = M_CDR(M_CAR(gensymed_symbol));
			    goto end_12;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_14;
		      end_loop_14:
			kb_properties = Qnil;
		      end_12:;
			goto end_13;
		    }
		    goto next_loop_13;
		  end_loop_13:
		    kb_properties = Qnil;
		  end_13:;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			gensymed_symbol = CDR(kb_properties);
			gensymed_symbol_1 = Class_description_gkbprop;
			gensymed_symbol_2 = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			gensymed_symbol_3 = (SI_Long)0L;
		      next_loop_15:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_15;
			gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
				(SI_Long)0L));
			if (gensymed_symbol_2 < gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)1L);
			else if (gensymed_symbol_2 > gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)2L);
			else {
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)3L);
			    gensymed_symbol_4 = Nil;
			  next_loop_16:
			    if ( !TRUEP(gensymed_symbol))
				goto end_loop_16;
			    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
				kb_specific_value = 
					M_CDR(M_CAR(gensymed_symbol));
				goto end_14;
			    }
			    gensymed_symbol = M_CDR(gensymed_symbol);
			    goto next_loop_16;
			  end_loop_16:
			    kb_specific_value = Qnil;
			  end_14:;
			    goto end_15;
			}
			goto next_loop_15;
		      end_loop_15:
			kb_specific_value = Qnil;
		      end_15:;
			if (kb_specific_value);
			else
			    kb_specific_value = No_specific_property_value;
		    }
		    else
			kb_specific_value = No_specific_property_value;
		    if ( !EQ(kb_specific_value,No_specific_property_value))
			resulting_value = kb_specific_value;
		    else {
			gensymed_symbol = CDR(global_properties);
			gensymed_symbol_1 = Class_description_gkbprop;
			gensymed_symbol_2 = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			gensymed_symbol_3 = (SI_Long)0L;
		      next_loop_17:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_17;
			gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
				(SI_Long)0L));
			if (gensymed_symbol_2 < gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)1L);
			else if (gensymed_symbol_2 > gensymed_symbol_3)
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)2L);
			else {
			    gensymed_symbol = ISVREF(gensymed_symbol,
				    (SI_Long)3L);
			    gensymed_symbol_4 = Nil;
			  next_loop_18:
			    if ( !TRUEP(gensymed_symbol))
				goto end_loop_18;
			    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
				resulting_value = 
					M_CDR(M_CAR(gensymed_symbol));
				goto end_16;
			    }
			    gensymed_symbol = M_CDR(gensymed_symbol);
			    goto next_loop_18;
			  end_loop_18:
			    resulting_value = Qnil;
			  end_16:;
			    goto end_17;
			}
			goto next_loop_17;
		      end_loop_17:
			resulting_value = Qnil;
		      end_17:;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    temp = 
			    get_slot_description_of_class_description_function(Qcross_section_pattern,
			    gensymed_symbol,Nil);
		}
		cross_section_pattern = ISVREF(temp,(SI_Long)6L);
	    }
	    temp = CAAR(cross_section_pattern);
	    cross_section_stripe = CONSP(temp) ? 
		    CDR(cross_section_pattern) : cross_section_pattern;
	    width = Nil;
	    ab_loop_list_ = cross_section_stripe;
	    ab_loopvar_ = FIX((SI_Long)0L);
	    ab_loop_desetq_ = Nil;
	  next_loop_19:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_19;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    width = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
	    goto next_loop_19;
	  end_loop_19:
	    gensymed_symbol_2 = IFIX(ab_loopvar_);
	    goto end_18;
	    gensymed_symbol_2 = IFIX(Qnil);
	  end_18:;
	    gensymed_symbol_3 = (SI_Long)1L;
	    half_width_of_connection = gensymed_symbol_2 >>  -  - 
		    gensymed_symbol_3;
	    temp = half_width_of_connection > 
		    IFIX(standard_maximum_distance_to_allow) ? 
		    FIX(half_width_of_connection) : Nil;
	    if (temp);
	    else
		temp = standard_maximum_distance_to_allow;
	    maximum_distance_to_allow = temp;
	    if ( !TRUEP(Objects_to_not_consider_qm) ||  
		    !TRUEP(memq_function(connection,
		    Objects_to_not_consider_qm))) {
		geometric_change_to_connection_is_temporary_p = T;
		PUSH_SPECIAL(Geometric_change_to_connection_is_temporary_p,geometric_change_to_connection_is_temporary_p,
			0);
		  add_missing_deltas_to_connection(connection);
		  result = find_vector_length_from_point_to_connection_if_within_limit(connection,
			  x_in_workspace,y_in_workspace,
			  maximum_distance_to_allow);
		  MVS_2(result,this_connection_nearest_connection_qm,
			  this_connection_nearest_distance_qm);
		  if (this_connection_nearest_distance_qm) {
		      if ( !TRUEP(nearest_distance_qm) || 
			      FIXNUM_LT(this_connection_nearest_distance_qm,
			      nearest_distance_qm)) {
			  nearest_distance_qm = 
				  this_connection_nearest_distance_qm;
			  nearest_connection_qm = 
				  this_connection_nearest_connection_qm;
		      }
		  }
		  remove_redundant_deltas_from_connection(connection);
		POP_SPECIAL();
	    }
	    goto next_loop;
	  end_loop_2:
	    result = VALUES_2(nearest_connection_qm,nearest_distance_qm);
	    goto end_19;
	    result = VALUES_1(Qnil);
	  end_19:;
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object array_constant;      /* # */

/* FIND-VECTOR-LENGTH-FROM-POINT-TO-CONNECTION-IF-WITHIN-LIMIT */
Object find_vector_length_from_point_to_connection_if_within_limit(connection,
	    x_in_workspace,y_in_workspace,maximum_distance_to_allow)
    Object connection, x_in_workspace, y_in_workspace;
    Object maximum_distance_to_allow;
{
    Object nearest_connection_qm, nearest_distance_qm;
    Object nearest_intercept_or_corner_qm, nearest_rest_of_deltas_qm;
    Object nearest_x_position_of_intercept_or_corner_qm;
    Object nearest_y_position_of_intercept_or_corner_qm;
    Object nearest_orientation_horizontal_p, connection_frame_or_class;
    Object intercept_or_corner_qm, x_position_of_intercept_or_corner_qm;
    Object y_position_of_intercept_or_corner_qm, distance_from_point_qm;
    Object input_end_object, input_end_position, input_end_side;
    Object gensymed_symbol, plist, connection_diagonal_p;
    Object initial_orientation_horizontal_p, delta_or_deltas, rest_of_deltas;
    Object stable_axis_position, variable_axis_begin_position, vertex_x;
    Object vertex_y, current_delta, next_delta, orientation_horizontal_p;
    Object variable_axis_end_position, variable_axis_point_position;
    Object stable_axis_point_position, next_x_and_y_vertex_available_qm;
    Object ab_loop_iter_flag_;
    SI_Long input_end_position_on_side, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, input_end_x_position, input_end_y_position;
    Declare_special(2);
    Object result;

    x_note_fn_call(101,4);
    nearest_connection_qm = Nil;
    nearest_distance_qm = Nil;
    nearest_intercept_or_corner_qm = Nil;
    nearest_rest_of_deltas_qm = Nil;
    nearest_x_position_of_intercept_or_corner_qm = Nil;
    nearest_y_position_of_intercept_or_corner_qm = Nil;
    nearest_orientation_horizontal_p = Nil;
    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
    intercept_or_corner_qm = Nil;
    x_position_of_intercept_or_corner_qm = Nil;
    y_position_of_intercept_or_corner_qm = Nil;
    distance_from_point_qm = Nil;
    input_end_object = ISVREF(connection,(SI_Long)3L);
    input_end_position = ISVREF(connection,(SI_Long)5L);
    input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
	    (SI_Long)3L);
    input_end_position_on_side = IFIX(input_end_position) >>  -  - (SI_Long)2L;
    gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    if (EQ(input_end_side,Qleft))
	gensymed_symbol_2 = (SI_Long)0L;
    else if (EQ(input_end_side,Qright)) {
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    }
    else
	gensymed_symbol_2 = input_end_position_on_side;
    input_end_x_position = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    if (EQ(input_end_side,Qtop))
	gensymed_symbol_2 = (SI_Long)0L;
    else if (EQ(input_end_side,Qbottom)) {
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    }
    else
	gensymed_symbol_2 = input_end_position_on_side;
    input_end_y_position = gensymed_symbol_1 + gensymed_symbol_2;
    plist = ISVREF(connection,(SI_Long)9L);
    connection_diagonal_p = plist ? (EQ(getfq_function_no_default(plist,
	    Qconnection_style),Qdiagonal) ? T : Nil) : Qnil;
    initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? T : Nil;
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    rest_of_deltas = delta_or_deltas;
    stable_axis_position = initial_orientation_horizontal_p ? 
	    FIX(input_end_y_position) : FIX(input_end_x_position);
    variable_axis_begin_position = initial_orientation_horizontal_p ? 
	    FIX(input_end_x_position) : FIX(input_end_y_position);
    vertex_x = FIX(input_end_x_position);
    vertex_y = FIX(input_end_y_position);
    current_delta = Nil;
    PUSH_SPECIAL(Current_delta,current_delta,1);
      next_delta = Nil;
      orientation_horizontal_p = initial_orientation_horizontal_p;
      PUSH_SPECIAL(Orientation_horizontal_p,orientation_horizontal_p,0);
	variable_axis_end_position = Nil;
	variable_axis_point_position = Nil;
	stable_axis_point_position = Nil;
	next_x_and_y_vertex_available_qm = T;
	ab_loop_iter_flag_ = T;
      next_loop:
	Current_delta = FIRST(rest_of_deltas);
	next_delta = SECOND(rest_of_deltas);
	if ( !TRUEP(ab_loop_iter_flag_))
	    Orientation_horizontal_p =  !TRUEP(Orientation_horizontal_p) ? 
		    T : Nil;
	variable_axis_end_position = 
		FIXNUM_ADD(variable_axis_begin_position,Current_delta);
	variable_axis_point_position = Orientation_horizontal_p ? 
		x_in_workspace : y_in_workspace;
	stable_axis_point_position = Orientation_horizontal_p ? 
		y_in_workspace : x_in_workspace;
	if ( !TRUEP(ab_loop_iter_flag_))
	    next_x_and_y_vertex_available_qm =  
		    !TRUEP(next_x_and_y_vertex_available_qm) ? T : Nil;
	if ( !TRUEP(next_delta))
	    goto end_loop;
	if (connection_diagonal_p)
	    result = find_vector_length_from_point_to_diagonal_connection_link(x_in_workspace,
		    y_in_workspace,vertex_x,vertex_y,
		    maximum_distance_to_allow,Orientation_horizontal_p,
		    Current_delta,next_delta,next_x_and_y_vertex_available_qm);
	else
	    result = find_vector_length_from_point_to_connection_link(variable_axis_point_position,
		    stable_axis_point_position,
		    variable_axis_begin_position,
		    variable_axis_end_position,stable_axis_position,
		    maximum_distance_to_allow,Current_delta,
		    Orientation_horizontal_p);
	MVS_6(result,distance_from_point_qm,intercept_or_corner_qm,
		x_position_of_intercept_or_corner_qm,
		y_position_of_intercept_or_corner_qm,vertex_x,vertex_y);
	if (distance_from_point_qm) {
	    if ( !TRUEP(nearest_distance_qm) || 
		    FIXNUM_LT(distance_from_point_qm,nearest_distance_qm)) {
		nearest_distance_qm = distance_from_point_qm;
		nearest_connection_qm = connection;
		nearest_intercept_or_corner_qm = intercept_or_corner_qm;
		nearest_rest_of_deltas_qm = rest_of_deltas;
		nearest_x_position_of_intercept_or_corner_qm = 
			x_position_of_intercept_or_corner_qm;
		nearest_y_position_of_intercept_or_corner_qm = 
			y_position_of_intercept_or_corner_qm;
		nearest_orientation_horizontal_p = Orientation_horizontal_p;
	    }
	}
	variable_axis_begin_position = stable_axis_position;
	stable_axis_position = variable_axis_end_position;
	rest_of_deltas = CDR(rest_of_deltas);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (connection_diagonal_p)
	    result = find_vector_length_from_point_to_diagonal_connection_link(x_in_workspace,
		    y_in_workspace,vertex_x,vertex_y,
		    maximum_distance_to_allow,Orientation_horizontal_p,
		    Current_delta,FIX((SI_Long)0L),
		    next_x_and_y_vertex_available_qm);
	else
	    result = find_vector_length_from_point_to_connection_link(variable_axis_point_position,
		    stable_axis_point_position,
		    variable_axis_begin_position,
		    variable_axis_end_position,stable_axis_position,
		    maximum_distance_to_allow,Current_delta,
		    Orientation_horizontal_p);
	MVS_6(result,distance_from_point_qm,intercept_or_corner_qm,
		x_position_of_intercept_or_corner_qm,
		y_position_of_intercept_or_corner_qm,vertex_x,vertex_y);
	if (distance_from_point_qm) {
	    if ( !TRUEP(nearest_distance_qm) || 
		    FIXNUM_LT(distance_from_point_qm,nearest_distance_qm)) {
		nearest_distance_qm = distance_from_point_qm;
		nearest_connection_qm = connection;
		nearest_intercept_or_corner_qm = intercept_or_corner_qm;
		nearest_rest_of_deltas_qm = rest_of_deltas;
		nearest_x_position_of_intercept_or_corner_qm = 
			x_position_of_intercept_or_corner_qm;
		nearest_y_position_of_intercept_or_corner_qm = 
			y_position_of_intercept_or_corner_qm;
		nearest_orientation_horizontal_p = Orientation_horizontal_p;
	    }
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_7(nearest_connection_qm,nearest_distance_qm,
	    nearest_intercept_or_corner_qm,nearest_rest_of_deltas_qm,
	    nearest_x_position_of_intercept_or_corner_qm,
	    nearest_y_position_of_intercept_or_corner_qm,
	    nearest_orientation_horizontal_p);
}

/* FIND-VECTOR-LENGTH-FROM-POINT-TO-DIAGONAL-CONNECTION-LINK */
Object find_vector_length_from_point_to_diagonal_connection_link(x_in_workspace,
	    y_in_workspace,vertex_x,vertex_y,maximum_distance_to_allow,
	    orientation_horizontal_p,current_delta,next_delta,
	    next_x_and_y_vertex_available_qm)
    Object x_in_workspace, y_in_workspace, vertex_x, vertex_y;
    Object maximum_distance_to_allow, orientation_horizontal_p, current_delta;
    Object next_delta, next_x_and_y_vertex_available_qm;
{
    Object new_vertex_x, new_vertex_y;
    Declare_special(2);
    Object result;

    x_note_fn_call(101,5);
    PUSH_SPECIAL(Current_delta,current_delta,1);
      PUSH_SPECIAL(Orientation_horizontal_p,orientation_horizontal_p,0);
	if (next_x_and_y_vertex_available_qm) {
	    result = compute_new_vertex(vertex_x,vertex_y,
		    Orientation_horizontal_p,Current_delta,next_delta,Nil);
	    MVS_2(result,new_vertex_x,new_vertex_y);
	    result = find_vector_length_from_point_to_diagonal_connection_link_1(x_in_workspace,
		    y_in_workspace,vertex_x,vertex_y,new_vertex_x,
		    new_vertex_y,maximum_distance_to_allow);
	}
	else
	    result = VALUES_6(Nil,Nil,Nil,Nil,vertex_x,vertex_y);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object float_constant;      /* 0.0 */

/* FIND-VECTOR-LENGTH-FROM-POINT-TO-DIAGONAL-CONNECTION-LINK-1 */
Object find_vector_length_from_point_to_diagonal_connection_link_1(x_in_workspace,
	    y_in_workspace,vertex_x,vertex_y,new_vertex_x,new_vertex_y,
	    maximum_distance_to_allow)
    Object x_in_workspace, y_in_workspace, vertex_x, vertex_y, new_vertex_x;
    Object new_vertex_y, maximum_distance_to_allow;
{
    Object x1, y1_1, x2, y2, delta_x, delta_y, m1, m2, b1, b2, x3, y3, fx1;
    Object fy1, fx2, x_intercept, y_intercept, distance_from_point_qm;
    Object intercept_or_corner_qm, x_position_of_intercept_or_corner_qm;
    Object y_position_of_intercept_or_corner_qm, try_for_corner_qm, temp, d1;
    Object d2;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char switch_point_order_qm;
    double temp_1, temp_2, temp_3, temp_4, arg, arg_1, arg_2, delta_x_1;
    double delta_y_1, fd1, fd2;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(101,6);
    switch_point_order_qm = FIXNUM_LT(new_vertex_x,vertex_x);
    x1 = Nil;
    y1_1 = Nil;
    x2 = Nil;
    y2 = Nil;
    delta_x = Nil;
    delta_y = Nil;
    m1 = Nil;
    m2 = Nil;
    b1 = Nil;
    b2 = Nil;
    x3 = Nil;
    y3 = Nil;
    fx1 = Nil;
    fy1 = Nil;
    fx2 = Nil;
    x_intercept = Nil;
    y_intercept = Nil;
    distance_from_point_qm = Nil;
    intercept_or_corner_qm = Nil;
    x_position_of_intercept_or_corner_qm = Nil;
    y_position_of_intercept_or_corner_qm = Nil;
    try_for_corner_qm = Nil;
    if (switch_point_order_qm) {
	x1 = new_vertex_x;
	y1_1 = new_vertex_y;
	x2 = vertex_x;
	y2 = vertex_y;
    }
    else {
	x1 = vertex_x;
	y1_1 = vertex_y;
	x2 = new_vertex_x;
	y2 = new_vertex_y;
    }
    delta_x = FIXNUM_MINUS(x2,x1);
    delta_y = FIXNUM_MINUS(y2,y1_1);
    if (IFIX(delta_x) == (SI_Long)0L) {
	if (FIXNUM_LE(vertex_y,y_in_workspace) && FIXNUM_LE(y_in_workspace,
		new_vertex_y) || FIXNUM_LE(new_vertex_y,y_in_workspace) && 
		FIXNUM_LE(y_in_workspace,vertex_y)) {
	    temp = FIXNUM_MINUS(x1,x_in_workspace);
	    distance_from_point_qm = FIXNUM_ABS(temp);
	    intercept_or_corner_qm = FIX((SI_Long)0L);
	    x_position_of_intercept_or_corner_qm = x1;
	    y_position_of_intercept_or_corner_qm = y_in_workspace;
	}
	else
	    try_for_corner_qm = T;
    }
    else if (IFIX(delta_y) == (SI_Long)0L) {
	if (FIXNUM_LE(vertex_x,x_in_workspace) && FIXNUM_LE(x_in_workspace,
		new_vertex_x) || FIXNUM_LE(new_vertex_x,x_in_workspace) && 
		FIXNUM_LE(x_in_workspace,vertex_x)) {
	    temp = FIXNUM_MINUS(y1_1,y_in_workspace);
	    distance_from_point_qm = FIXNUM_ABS(temp);
	    intercept_or_corner_qm = FIX((SI_Long)0L);
	    x_position_of_intercept_or_corner_qm = x_in_workspace;
	    y_position_of_intercept_or_corner_qm = y1_1;
	}
	else
	    try_for_corner_qm = T;
    }
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    fx1 = lfloat(x1,float_constant);
	    fy1 = lfloat(y1_1,float_constant);
	    fx2 = lfloat(x2,float_constant);
	    delta_x = lfloat(delta_x,float_constant);
	    delta_y = lfloat(delta_y,float_constant);
	    x3 = lfloat(x_in_workspace,float_constant);
	    y3 = lfloat(y_in_workspace,float_constant);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
	    m1 = DOUBLE_TO_DOUBLE_FLOAT(temp_1 / temp_2);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
	    m2 = DOUBLE_TO_DOUBLE_FLOAT( - (temp_1 / temp_2));
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
	    b1 = DOUBLE_TO_DOUBLE_FLOAT(temp_3 - temp_4 * temp_1 / temp_2);
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y3);
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x3);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
	    b2 = DOUBLE_TO_DOUBLE_FLOAT(temp_3 + temp_4 * temp_1 / temp_2);
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(b2);
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(b1);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(m1);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(m2);
	    x_intercept = DOUBLE_TO_DOUBLE_FLOAT((temp_3 - temp_4) / 
		    (temp_1 - temp_2));
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(m1);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x_intercept);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(b1);
	    y_intercept = DOUBLE_TO_DOUBLE_FLOAT(temp_4 * temp_1 + temp_2);
	    arg = DOUBLE_FLOAT_TO_DOUBLE(fx1);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(x_intercept);
	    arg_2 = DOUBLE_FLOAT_TO_DOUBLE(fx2);
	    if (arg <= arg_1 && arg_1 <= arg_2 &&  
		    !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1) &&  
		    !inline_nanp_for_comparison(arg_2)) {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x3);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(x_intercept);
		delta_x_1 = temp_1 - temp_2;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(y3);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(y_intercept);
		delta_y_1 = temp_1 - temp_2;
		distance_from_point_qm = 
			l_round(float_distance(DOUBLE_TO_DOUBLE_FLOAT(delta_x_1),
			DOUBLE_TO_DOUBLE_FLOAT(delta_y_1)),_);
		intercept_or_corner_qm = FIX((SI_Long)0L);
		x_position_of_intercept_or_corner_qm = l_round(x_intercept,_);
		y_position_of_intercept_or_corner_qm = l_round(y_intercept,_);
	    }
	    else
		try_for_corner_qm = T;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    if (try_for_corner_qm) {
	temp = FIXNUM_MINUS(x1,x_in_workspace);
	d1 = FIXNUM_ABS(temp);
	temp = FIXNUM_MINUS(y1_1,y_in_workspace);
	d2 = FIXNUM_ABS(temp);
	if (FIXNUM_LT(d1,
		Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation) 
		&& FIXNUM_LT(d2,
		Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation))
	    gensymed_symbol = IFIX(isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
		    FIXNUM_TIMES(d2,d2))));
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		fd1 = (double)IFIX(d1);
		fd2 = (double)IFIX(d2);
		gensymed_symbol = 
			IFIX(l_round(DOUBLE_TO_DOUBLE_FLOAT(sqrt(fd1 * fd1 
			+ fd2 * fd2)),_));
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	temp = FIXNUM_MINUS(x2,x_in_workspace);
	d1 = FIXNUM_ABS(temp);
	temp = FIXNUM_MINUS(y2,y_in_workspace);
	d2 = FIXNUM_ABS(temp);
	if (FIXNUM_LT(d1,
		Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation) 
		&& FIXNUM_LT(d2,
		Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation))
	    gensymed_symbol_1 = IFIX(isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
		    FIXNUM_TIMES(d2,d2))));
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		fd1 = (double)IFIX(d1);
		fd2 = (double)IFIX(d2);
		gensymed_symbol_1 = 
			IFIX(l_round(DOUBLE_TO_DOUBLE_FLOAT(sqrt(fd1 * fd1 
			+ fd2 * fd2)),_));
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	distance_from_point_qm = FIX(MIN(gensymed_symbol,gensymed_symbol_1));
    }
    if (distance_from_point_qm && NUM_LE(distance_from_point_qm,
	    maximum_distance_to_allow))
	return VALUES_6(distance_from_point_qm,intercept_or_corner_qm,
		x_position_of_intercept_or_corner_qm,
		y_position_of_intercept_or_corner_qm,new_vertex_x,
		new_vertex_y);
    else
	return VALUES_6(Nil,Nil,Nil,Nil,new_vertex_x,new_vertex_y);
}

/* FIND-VECTOR-LENGTH-FROM-POINT-TO-CONNECTION-LINK */
Object find_vector_length_from_point_to_connection_link(variable_axis_point_position,
	    stable_axis_point_position,variable_axis_begin_position,
	    variable_axis_end_position,stable_axis_position,
	    maximum_distance_to_allow,current_delta,orientation_horizontal_p)
    Object variable_axis_point_position, stable_axis_point_position;
    Object variable_axis_begin_position, variable_axis_end_position;
    Object stable_axis_position, maximum_distance_to_allow, current_delta;
    Object orientation_horizontal_p;
{
    Object distance_from_point_qm, intercept_or_corner_qm;
    Object x_position_of_intercept_or_corner_qm;
    Object y_position_of_intercept_or_corner_qm, temp, d1;
    SI_Long gensymed_symbol, gensymed_symbol_1, d2;
    char temp_1;
    double fd1, fd2;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(101,7);
    PUSH_SPECIAL(Orientation_horizontal_p,orientation_horizontal_p,1);
      PUSH_SPECIAL(Current_delta,current_delta,0);
	distance_from_point_qm = Nil;
	intercept_or_corner_qm = Nil;
	x_position_of_intercept_or_corner_qm = Nil;
	y_position_of_intercept_or_corner_qm = Nil;
	if (IFIX(Current_delta) > (SI_Long)0L) {
	    if (FIXNUM_GE(variable_axis_end_position,
		    variable_axis_point_position) && 
		    FIXNUM_GE(variable_axis_point_position,
		    variable_axis_begin_position)) {
		temp = FIXNUM_MINUS(stable_axis_point_position,
			stable_axis_position);
		distance_from_point_qm = FIXNUM_ABS(temp);
		intercept_or_corner_qm = 
			FIXNUM_MINUS(variable_axis_point_position,
			variable_axis_begin_position);
		x_position_of_intercept_or_corner_qm = 
			Orientation_horizontal_p ? 
			variable_axis_point_position : stable_axis_position;
		y_position_of_intercept_or_corner_qm = 
			Orientation_horizontal_p ? stable_axis_position : 
			variable_axis_point_position;
	    }
	    else {
		temp = FIXNUM_MINUS(stable_axis_point_position,
			stable_axis_position);
		if (FIXNUM_LT(FIXNUM_ABS(temp),maximum_distance_to_allow)) {
		    if (FIXNUM_GT(variable_axis_point_position,
			    variable_axis_end_position)) {
			temp = FIXNUM_MINUS(variable_axis_point_position,
				variable_axis_end_position);
			temp = FIXNUM_ABS(temp);
		    }
		    else {
			temp = FIXNUM_MINUS(variable_axis_begin_position,
				variable_axis_point_position);
			temp = FIXNUM_ABS(temp);
		    }
		    temp_1 = FIXNUM_LT(temp,maximum_distance_to_allow);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    temp = FIXNUM_MINUS(stable_axis_point_position,
			    stable_axis_position);
		    d1 = FIXNUM_ABS(temp);
		    gensymed_symbol = IFIX(variable_axis_point_position);
		    gensymed_symbol_1 = 
			    FIXNUM_GT(variable_axis_point_position,
			    variable_axis_end_position) ? 
			    IFIX(variable_axis_end_position) : 
			    IFIX(variable_axis_begin_position);
		    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		    d2 = ABS(gensymed_symbol);
		    if (FIXNUM_LT(d1,
			    Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation) 
			    && d2 < 
			    IFIX(Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation))
			distance_from_point_qm = 
				isqrt(FIX(IFIX(FIXNUM_TIMES(d1,d1)) + d2 * 
				d2));
		    else {
			if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			    fd1 = (double)IFIX(d1);
			    fd2 = (double)d2;
			    distance_from_point_qm = 
				    l_round(DOUBLE_TO_DOUBLE_FLOAT(sqrt(fd1 
				    * fd1 + fd2 * fd2)),_);
			}
			POP_LOCAL_ALLOCATION(0,0);
		    }
		    if (FIXNUM_GT(variable_axis_point_position,
			    variable_axis_end_position)) {
			intercept_or_corner_qm = Qend_corner;
			x_position_of_intercept_or_corner_qm = 
				Orientation_horizontal_p ? 
				variable_axis_end_position : 
				stable_axis_position;
			y_position_of_intercept_or_corner_qm = 
				Orientation_horizontal_p ? 
				stable_axis_position : 
				variable_axis_end_position;
		    }
		    else {
			intercept_or_corner_qm = Qbegin_corner;
			x_position_of_intercept_or_corner_qm = 
				Orientation_horizontal_p ? 
				variable_axis_begin_position : 
				stable_axis_position;
			y_position_of_intercept_or_corner_qm = 
				Orientation_horizontal_p ? 
				stable_axis_position : 
				variable_axis_begin_position;
		    }
		}
	    }
	}
	else if (FIXNUM_LE(variable_axis_end_position,
		variable_axis_point_position) && 
		FIXNUM_LE(variable_axis_point_position,
		variable_axis_begin_position)) {
	    temp = FIXNUM_MINUS(stable_axis_point_position,
		    stable_axis_position);
	    distance_from_point_qm = FIXNUM_ABS(temp);
	    intercept_or_corner_qm = 
		    FIXNUM_MINUS(variable_axis_point_position,
		    variable_axis_begin_position);
	    x_position_of_intercept_or_corner_qm = 
		    Orientation_horizontal_p ? 
		    variable_axis_point_position : stable_axis_position;
	    y_position_of_intercept_or_corner_qm = 
		    Orientation_horizontal_p ? stable_axis_position : 
		    variable_axis_point_position;
	}
	else {
	    temp = FIXNUM_MINUS(stable_axis_point_position,
		    stable_axis_position);
	    if (FIXNUM_LT(FIXNUM_ABS(temp),maximum_distance_to_allow)) {
		if (FIXNUM_LT(variable_axis_point_position,
			variable_axis_end_position)) {
		    temp = FIXNUM_MINUS(variable_axis_point_position,
			    variable_axis_end_position);
		    temp = FIXNUM_ABS(temp);
		}
		else {
		    temp = FIXNUM_MINUS(variable_axis_begin_position,
			    variable_axis_point_position);
		    temp = FIXNUM_ABS(temp);
		}
		temp_1 = FIXNUM_LT(temp,maximum_distance_to_allow);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = FIXNUM_MINUS(stable_axis_point_position,
			stable_axis_position);
		d1 = FIXNUM_ABS(temp);
		gensymed_symbol = IFIX(variable_axis_point_position);
		gensymed_symbol_1 = FIXNUM_LT(variable_axis_point_position,
			variable_axis_end_position) ? 
			IFIX(variable_axis_end_position) : 
			IFIX(variable_axis_begin_position);
		gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		d2 = ABS(gensymed_symbol);
		if (FIXNUM_LT(d1,
			Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation) 
			&& d2 < 
			IFIX(Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation))
		    distance_from_point_qm = 
			    isqrt(FIX(IFIX(FIXNUM_TIMES(d1,d1)) + d2 * d2));
		else {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			fd1 = (double)IFIX(d1);
			fd2 = (double)d2;
			distance_from_point_qm = 
				l_round(DOUBLE_TO_DOUBLE_FLOAT(sqrt(fd1 * 
				fd1 + fd2 * fd2)),_);
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		}
		if (FIXNUM_LT(variable_axis_point_position,
			variable_axis_end_position)) {
		    intercept_or_corner_qm = Qend_corner;
		    x_position_of_intercept_or_corner_qm = 
			    Orientation_horizontal_p ? 
			    variable_axis_end_position : stable_axis_position;
		    y_position_of_intercept_or_corner_qm = 
			    Orientation_horizontal_p ? 
			    stable_axis_position : variable_axis_end_position;
		}
		else {
		    intercept_or_corner_qm = Qbegin_corner;
		    x_position_of_intercept_or_corner_qm = 
			    Orientation_horizontal_p ? 
			    variable_axis_begin_position : 
			    stable_axis_position;
		    y_position_of_intercept_or_corner_qm = 
			    Orientation_horizontal_p ? 
			    stable_axis_position : 
			    variable_axis_begin_position;
		}
	    }
	}
	if (distance_from_point_qm) {
	    if (FIXNUM_LE(distance_from_point_qm,maximum_distance_to_allow))
		result = VALUES_4(distance_from_point_qm,
			intercept_or_corner_qm,
			x_position_of_intercept_or_corner_qm,
			y_position_of_intercept_or_corner_qm);
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ADD-MISSING-DELTAS-TO-CONNECTION */
Object add_missing_deltas_to_connection(connection)
    Object connection;
{
    Object noting_changes_to_kb_p, gensymed_symbol, output_end_object;
    Object output_end_position, output_end_side, delta_or_deltas;
    Object missing_link_delta_1, missing_link_delta_2, last_delta_anchor_x;
    Object last_delta_anchor_y, last_delta_orientation_horizontal_p;
    Object svref_new_value;
    SI_Long output_end_position_on_side, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, output_end_x_position, output_end_y_position;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,8);
    noting_changes_to_kb_p = Nil;
    PUSH_SPECIAL(Noting_changes_to_kb_p,noting_changes_to_kb_p,0);
      gensymed_symbol = connection;
      output_end_object = ISVREF(gensymed_symbol,(SI_Long)2L);
      output_end_position = ISVREF(gensymed_symbol,(SI_Long)4L);
      output_end_side = ISVREF(array_constant,IFIX(output_end_position) & 
	      (SI_Long)3L);
      output_end_position_on_side = IFIX(output_end_position) >>  -  - 
	      (SI_Long)2L;
      gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      if (EQ(output_end_side,Qleft))
	  gensymed_symbol_2 = (SI_Long)0L;
      else if (EQ(output_end_side,Qright)) {
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_3 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	  gensymed_symbol_3 = Dont_include_offset_for_end_position_qm ? 
		  (SI_Long)0L : (SI_Long)1L;
	  gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
      }
      else
	  gensymed_symbol_2 = output_end_position_on_side;
      output_end_x_position = gensymed_symbol_1 + gensymed_symbol_2;
      gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      if (EQ(output_end_side,Qtop))
	  gensymed_symbol_2 = (SI_Long)0L;
      else if (EQ(output_end_side,Qbottom)) {
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_3 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	  gensymed_symbol_3 = Dont_include_offset_for_end_position_qm ? 
		  (SI_Long)0L : (SI_Long)1L;
	  gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
      }
      else
	  gensymed_symbol_2 = output_end_position_on_side;
      output_end_y_position = gensymed_symbol_1 + gensymed_symbol_2;
      delta_or_deltas = ISVREF(connection,(SI_Long)6L);
      missing_link_delta_1 = Nil;
      missing_link_delta_2 = Nil;
      result = compute_last_delta_anchor_point(1,connection);
      MVS_3(result,last_delta_anchor_x,last_delta_anchor_y,
	      last_delta_orientation_horizontal_p);
      temp = TRUEP(Noting_changes_to_kb_p);
      if (temp);
      else {
	  gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		  (SI_Long)128L;
	  temp =  !((SI_Long)0L != gensymed_symbol_1) ?  
		  !TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		  TRUEP(Nil);
      }
      if (temp)
	  note_change_to_connection_1(connection);
      if ( !TRUEP(delta_or_deltas)) {
	  if (last_delta_orientation_horizontal_p) {
	      missing_link_delta_1 = FIX(output_end_x_position - 
		      IFIX(last_delta_anchor_x));
	      missing_link_delta_2 = FIX(output_end_y_position - 
		      IFIX(last_delta_anchor_y));
	  }
	  else {
	      missing_link_delta_1 = FIX(output_end_y_position - 
		      IFIX(last_delta_anchor_y));
	      missing_link_delta_2 = FIX(output_end_x_position - 
		      IFIX(last_delta_anchor_x));
	  }
	  svref_new_value = IFIX(missing_link_delta_2) == (SI_Long)0L ? 
		  gensym_cons_1(missing_link_delta_1,Nil) : 
		  gensym_list_2(missing_link_delta_1,missing_link_delta_2);
      }
      else if (ATOM(delta_or_deltas)) {
	  if (last_delta_orientation_horizontal_p) {
	      missing_link_delta_1 = FIX(output_end_y_position - 
		      IFIX(last_delta_anchor_y));
	      missing_link_delta_2 = FIX(output_end_x_position - 
		      IFIX(last_delta_anchor_x));
	  }
	  else {
	      missing_link_delta_1 = FIX(output_end_x_position - 
		      IFIX(last_delta_anchor_x));
	      missing_link_delta_2 = FIX(output_end_y_position - 
		      IFIX(last_delta_anchor_y));
	  }
	  svref_new_value = gensym_cons_1(delta_or_deltas,
		  gensym_list_2(missing_link_delta_1,missing_link_delta_2));
      }
      else {
	  if (last_delta_orientation_horizontal_p) {
	      missing_link_delta_1 = FIX(output_end_y_position - 
		      IFIX(last_delta_anchor_y));
	      missing_link_delta_2 = FIX(output_end_x_position - 
		      IFIX(last_delta_anchor_x));
	  }
	  else {
	      missing_link_delta_1 = FIX(output_end_x_position - 
		      IFIX(last_delta_anchor_x));
	      missing_link_delta_2 = FIX(output_end_y_position - 
		      IFIX(last_delta_anchor_y));
	  }
	  svref_new_value = nconc2(delta_or_deltas,
		  gensym_list_2(missing_link_delta_1,missing_link_delta_2));
      }
      result = VALUES_1(SVREF(connection,FIX((SI_Long)6L)) = svref_new_value);
    POP_SPECIAL();
    return result;
}

/* REMOVE-REDUNDANT-DELTAS-FROM-CONNECTION */
Object remove_redundant_deltas_from_connection(connection)
    Object connection;
{
    Object noting_changes_to_kb_p, delta_or_deltas, temp_1, rest_of_deltas;
    SI_Long gensymed_symbol;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,9);
    noting_changes_to_kb_p = Nil;
    PUSH_SPECIAL(Noting_changes_to_kb_p,noting_changes_to_kb_p,0);
      delta_or_deltas = ISVREF(connection,(SI_Long)6L);
      if (ATOM(delta_or_deltas) ||  !TRUEP(CDR(delta_or_deltas)) ||  
	      !TRUEP(CDDR(delta_or_deltas))) {
	  if (CONSP(delta_or_deltas))
	      reclaim_gensym_list_1(delta_or_deltas);
	  temp = TRUEP(Noting_changes_to_kb_p);
	  if (temp);
	  else {
	      gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp =  !((SI_Long)0L != gensymed_symbol) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp)
	      note_change_to_connection_1(connection);
	  result = VALUES_1(SVREF(connection,FIX((SI_Long)6L)) = Nil);
      }
      else if ( !TRUEP(CDDDR(delta_or_deltas))) {
	  temp = TRUEP(Noting_changes_to_kb_p);
	  if (temp);
	  else {
	      gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp =  !((SI_Long)0L != gensymed_symbol) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp)
	      note_change_to_connection_1(connection);
	  temp_1 = CAR(delta_or_deltas);
	  reclaim_gensym_list_1(delta_or_deltas);
	  result = VALUES_1(SVREF(connection,FIX((SI_Long)6L)) = temp_1);
      }
      else {
	  rest_of_deltas = delta_or_deltas;
	next_loop:
	  if ( !TRUEP(rest_of_deltas))
	      goto end_loop;
	  if ( !TRUEP(CDDDR(rest_of_deltas)))
	      goto end_loop;
	  rest_of_deltas = M_CDR(rest_of_deltas);
	  goto next_loop;
	end_loop:
	  reclaim_gensym_list_1(CDR(rest_of_deltas));
	  M_CDR(rest_of_deltas) = Nil;
	  result = VALUES_1(delta_or_deltas);
      }
    POP_SPECIAL();
    return result;
}

/* REMOVE-LAST-DELTA-FROM-CONNECTION */
Object remove_last_delta_from_connection(connection)
    Object connection;
{
    Object noting_changes_to_kb_p, delta_or_deltas, temp_1, rest_of_deltas;
    SI_Long gensymed_symbol;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,10);
    noting_changes_to_kb_p = Nil;
    PUSH_SPECIAL(Noting_changes_to_kb_p,noting_changes_to_kb_p,0);
      delta_or_deltas = ISVREF(connection,(SI_Long)6L);
      if (ATOM(delta_or_deltas) ||  !TRUEP(CDR(delta_or_deltas))) {
	  if (CONSP(delta_or_deltas))
	      reclaim_gensym_list_1(delta_or_deltas);
	  temp = TRUEP(Noting_changes_to_kb_p);
	  if (temp);
	  else {
	      gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp =  !((SI_Long)0L != gensymed_symbol) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp)
	      note_change_to_connection_1(connection);
	  result = VALUES_1(SVREF(connection,FIX((SI_Long)6L)) = Nil);
      }
      else if ( !TRUEP(CDDR(delta_or_deltas))) {
	  temp = TRUEP(Noting_changes_to_kb_p);
	  if (temp);
	  else {
	      gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp =  !((SI_Long)0L != gensymed_symbol) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp)
	      note_change_to_connection_1(connection);
	  temp_1 = CAR(delta_or_deltas);
	  reclaim_gensym_list_1(delta_or_deltas);
	  result = VALUES_1(SVREF(connection,FIX((SI_Long)6L)) = temp_1);
      }
      else {
	  rest_of_deltas = delta_or_deltas;
	next_loop:
	  if ( !TRUEP(rest_of_deltas))
	      goto end_loop;
	  if ( !TRUEP(CDDR(rest_of_deltas)))
	      goto end_loop;
	  rest_of_deltas = M_CDR(rest_of_deltas);
	  goto next_loop;
	end_loop:
	  reclaim_gensym_list_1(CDR(rest_of_deltas));
	  M_CDR(rest_of_deltas) = Nil;
	  result = VALUES_1(delta_or_deltas);
      }
    POP_SPECIAL();
    return result;
}

/* CONNECTION-VERTICES-IN-WORKSPACE */
Object connection_vertices_in_workspace(connection)
    Object connection;
{
    Object input, output, input_end_position, output_end_position, plist;
    Object diagonal_p, start_x, start_y, end_x, end_y, temp, res, x, y, deltas;
    Object horizontal_p, deltas_old_value;
    SI_Long temp_1, gensymed_symbol, gensymed_symbol_1;
    char input_end_horizontal_p, output_end_horizontal_p;
    Object result;

    x_note_fn_call(101,11);
    input = ISVREF(connection,(SI_Long)3L);
    output = ISVREF(connection,(SI_Long)2L);
    input_end_position = ISVREF(connection,(SI_Long)5L);
    output_end_position = ISVREF(connection,(SI_Long)4L);
    plist = ISVREF(connection,(SI_Long)9L);
    diagonal_p = plist ? (EQ(getfq_function_no_default(plist,
	    Qconnection_style),Qdiagonal) ? T : Nil) : Qnil;
    input_end_horizontal_p = (SI_Long)1L == (IFIX(input_end_position) & 
	    (SI_Long)1L);
    output_end_horizontal_p = (SI_Long)1L == (IFIX(output_end_position) & 
	    (SI_Long)1L);
    result = determine_connection_terminal_coordinate(input,
	    input_end_position);
    MVS_2(result,start_x,start_y);
    result = determine_connection_terminal_coordinate(output,
	    output_end_position);
    MVS_2(result,end_x,end_y);
    if (FIXNUM_EQ(start_x,end_x) &&  !input_end_horizontal_p &&  
	    !output_end_horizontal_p || FIXNUM_EQ(start_y,end_y) && 
	    input_end_horizontal_p && output_end_horizontal_p)
	temp = gensym_list_2(gensym_cons_1(start_x,start_y),
		gensym_cons_1(end_x,end_y));
    else {
	res = Qnil;
	x = start_x;
	y = start_y;
	deltas = ISVREF(connection,(SI_Long)6L);
	horizontal_p = (SI_Long)1L == (IFIX(input_end_position) & 
		(SI_Long)1L) ? T : Nil;
      next_loop:
	res = gensym_cons_1(gensym_cons_1(x,y),res);
	if ( !TRUEP(deltas))
	    goto end_loop;
	if (diagonal_p) {
	    if (horizontal_p) {
		if (CONSP(deltas)) {
		    deltas_old_value = deltas;
		    temp_1 = IFIX(FIRST(deltas_old_value));
		    deltas = REST(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		else {
		    deltas_old_value = deltas;
		    deltas = Nil;
		    temp_1 = IFIX(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		gensymed_symbol_1 = IFIX(x);
		x = FIX(gensymed_symbol + gensymed_symbol_1);
	    }
	    else {
		if (CONSP(deltas)) {
		    deltas_old_value = deltas;
		    temp_1 = IFIX(FIRST(deltas_old_value));
		    deltas = REST(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		else {
		    deltas_old_value = deltas;
		    deltas = Nil;
		    temp_1 = IFIX(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		gensymed_symbol_1 = IFIX(y);
		y = FIX(gensymed_symbol + gensymed_symbol_1);
	    }
	    if (deltas) {
		if (horizontal_p) {
		    if (CONSP(deltas)) {
			deltas_old_value = deltas;
			temp_1 = IFIX(FIRST(deltas_old_value));
			deltas = REST(deltas_old_value);
			gensymed_symbol = temp_1;
		    }
		    else {
			deltas_old_value = deltas;
			deltas = Nil;
			temp_1 = IFIX(deltas_old_value);
			gensymed_symbol = temp_1;
		    }
		    gensymed_symbol_1 = IFIX(y);
		    y = FIX(gensymed_symbol + gensymed_symbol_1);
		}
		else {
		    if (CONSP(deltas)) {
			deltas_old_value = deltas;
			temp_1 = IFIX(FIRST(deltas_old_value));
			deltas = REST(deltas_old_value);
			gensymed_symbol = temp_1;
		    }
		    else {
			deltas_old_value = deltas;
			deltas = Nil;
			temp_1 = IFIX(deltas_old_value);
			gensymed_symbol = temp_1;
		    }
		    gensymed_symbol_1 = IFIX(x);
		    x = FIX(gensymed_symbol + gensymed_symbol_1);
		}
	    }
	    else if (horizontal_p)
		y = end_y;
	    else
		x = end_x;
	}
	else {
	    if (horizontal_p) {
		if (CONSP(deltas)) {
		    deltas_old_value = deltas;
		    temp_1 = IFIX(FIRST(deltas_old_value));
		    deltas = REST(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		else {
		    deltas_old_value = deltas;
		    deltas = Nil;
		    temp_1 = IFIX(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		gensymed_symbol_1 = IFIX(x);
		x = FIX(gensymed_symbol + gensymed_symbol_1);
	    }
	    if (!horizontal_p) {
		if (CONSP(deltas)) {
		    deltas_old_value = deltas;
		    temp_1 = IFIX(FIRST(deltas_old_value));
		    deltas = REST(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		else {
		    deltas_old_value = deltas;
		    deltas = Nil;
		    temp_1 = IFIX(deltas_old_value);
		    gensymed_symbol = temp_1;
		}
		gensymed_symbol_1 = IFIX(y);
		y = FIX(gensymed_symbol + gensymed_symbol_1);
	    }
	}
	if ( !TRUEP(diagonal_p))
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	goto next_loop;
      end_loop:
	if ( !TRUEP(diagonal_p)) {
	    if (horizontal_p)
		res = gensym_cons_1(gensym_cons_1(end_x,y),res);
	    else
		res = gensym_cons_1(gensym_cons_1(x,end_y),res);
	}
	res = gensym_cons_1(gensym_cons_1(end_x,end_y),res);
	temp = nreverse(res);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* DETERMINE-CONNECTION-TERMINAL-COORDINATE */
Object determine_connection_terminal_coordinate(item,end_position)
    Object item, end_position;
{
    Object side, gensymed_symbol, block_left, block_top, block_right;
    Object block_bottom, temp;
    SI_Long offset;

    x_note_fn_call(101,12);
    side = ISVREF(array_constant,IFIX(end_position) & (SI_Long)3L);
    offset = IFIX(end_position) >>  -  - (SI_Long)2L;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    block_left = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    block_top = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    block_right = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    block_bottom = gensymed_symbol;
    if (EQ(side,Qleft))
	return VALUES_2(block_left,FIX(IFIX(block_top) + offset));
    else if (EQ(side,Qtop))
	return VALUES_2(FIX(IFIX(block_left) + offset),block_top);
    else if (EQ(side,Qright))
	return VALUES_2(block_right,FIX(IFIX(block_top) + offset));
    else if (EQ(side,Qbottom)) {
	temp = FIXNUM_ADD1(block_bottom);
	return VALUES_2(FIX(IFIX(block_left) + offset),temp);
    }
    else
	return VALUES_1(Qnil);
}

/* COMPUTE-DRAGGED-CONNECTION-ANCHOR-POINT */
Object compute_dragged_connection_anchor_point(connection,block)
    Object connection, block;
{
    Object gensymed_symbol, input_end_object, input_end_position;
    Object input_end_side, gensymed_symbol_1, initial_orientation_horizontal_p;
    Object output_end_object, output_end_position, output_end_side;
    Object delta_or_deltas;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position;

    x_note_fn_call(101,13);
    if (EQ(ISVREF(connection,(SI_Long)2L),block))
	return compute_last_delta_anchor_point(1,connection);
    else {
	gensymed_symbol = connection;
	input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
	input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
	input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
		(SI_Long)3L);
	input_end_position_on_side = IFIX(input_end_position) >>  -  - 
		(SI_Long)2L;
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	if (EQ(input_end_side,Qleft))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(input_end_side,Qright)) {
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = input_end_position_on_side;
	input_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	if (EQ(input_end_side,Qtop))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(input_end_side,Qbottom)) {
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = input_end_position_on_side;
	input_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
	initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
	if (initial_orientation_horizontal_p);
	else
	    initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? 
		    T : Nil;
	output_end_object = ISVREF(gensymed_symbol,(SI_Long)2L);
	output_end_position = ISVREF(gensymed_symbol,(SI_Long)4L);
	output_end_side = ISVREF(array_constant,IFIX(output_end_position) 
		& (SI_Long)3L);
	output_end_position_on_side = IFIX(output_end_position) >>  -  - 
		(SI_Long)2L;
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	if (EQ(output_end_side,Qleft))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(output_end_side,Qright)) {
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = output_end_position_on_side;
	output_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	if (EQ(output_end_side,Qtop))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(output_end_side,Qbottom)) {
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = output_end_position_on_side;
	output_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
	delta_or_deltas = ISVREF(connection,(SI_Long)6L);
	if ( !TRUEP(delta_or_deltas))
	    return VALUES_2(FIX(output_end_x_position),
		    FIX(output_end_y_position));
	else if (ATOM(delta_or_deltas)) {
	    if (initial_orientation_horizontal_p)
		return VALUES_2(FIX(input_end_x_position + 
			IFIX(delta_or_deltas)),FIX(output_end_y_position));
	    else
		return VALUES_2(FIX(output_end_x_position),
			FIX(input_end_y_position + IFIX(delta_or_deltas)));
	}
	else if (initial_orientation_horizontal_p)
	    return VALUES_2(FIX(input_end_x_position + 
		    IFIX(CAR(delta_or_deltas))),FIX(input_end_y_position + 
		    IFIX(CADR(delta_or_deltas))));
	else
	    return VALUES_2(FIX(input_end_x_position + 
		    IFIX(CADR(delta_or_deltas))),FIX(input_end_y_position 
		    + IFIX(CAR(delta_or_deltas))));
    }
}

/* COMPUTE-LAST-DELTA-ANCHOR-POINT */
Object compute_last_delta_anchor_point varargs_1(int, n)
{
    Object connection;
    Object override_delta_or_deltas, gensymed_symbol, input_end_object;
    Object input_end_position, input_end_side;
    Object initial_orientation_horizontal_p, delta_or_deltas;
    Object stable_axis_position, variable_axis_begin_position, rest_of_deltas;
    Object delta, orientation_horizontal_p, variable_axis_end_position;
    Object ab_loop_iter_flag_;
    SI_Long input_end_position_on_side, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, input_end_x_position, input_end_y_position;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,14);
    INIT_ARGS_nonrelocating();
    connection = REQUIRED_ARG_nonrelocating();
    override_delta_or_deltas = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = connection;
    input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
    input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
    input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
	    (SI_Long)3L);
    input_end_position_on_side = IFIX(input_end_position) >>  -  - (SI_Long)2L;
    gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    if (EQ(input_end_side,Qleft))
	gensymed_symbol_2 = (SI_Long)0L;
    else if (EQ(input_end_side,Qright)) {
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    }
    else
	gensymed_symbol_2 = input_end_position_on_side;
    input_end_x_position = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    if (EQ(input_end_side,Qtop))
	gensymed_symbol_2 = (SI_Long)0L;
    else if (EQ(input_end_side,Qbottom)) {
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    }
    else
	gensymed_symbol_2 = input_end_position_on_side;
    input_end_y_position = gensymed_symbol_1 + gensymed_symbol_2;
    initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? T : Nil;
    delta_or_deltas = override_delta_or_deltas;
    if (delta_or_deltas);
    else
	delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    if ( !TRUEP(delta_or_deltas))
	return VALUES_4(FIX(input_end_x_position),
		FIX(input_end_y_position),initial_orientation_horizontal_p,
		delta_or_deltas);
    else if (ATOM(delta_or_deltas)) {
	if (initial_orientation_horizontal_p)
	    return VALUES_4(FIX(input_end_x_position + 
		    IFIX(delta_or_deltas)),FIX(input_end_y_position),
		    initial_orientation_horizontal_p,delta_or_deltas);
	else
	    return VALUES_4(FIX(input_end_x_position),
		    FIX(input_end_y_position + IFIX(delta_or_deltas)),
		    initial_orientation_horizontal_p,delta_or_deltas);
    }
    else {
	stable_axis_position = initial_orientation_horizontal_p ? 
		FIX(input_end_y_position) : FIX(input_end_x_position);
	variable_axis_begin_position = initial_orientation_horizontal_p ? 
		FIX(input_end_x_position) : FIX(input_end_y_position);
	rest_of_deltas = delta_or_deltas;
	delta = Nil;
	orientation_horizontal_p = initial_orientation_horizontal_p;
	PUSH_SPECIAL(Orientation_horizontal_p,orientation_horizontal_p,0);
	  variable_axis_end_position = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop:
	  if ( !TRUEP(rest_of_deltas))
	      goto end_loop;
	  delta = CAR(rest_of_deltas);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      Orientation_horizontal_p =  !TRUEP(Orientation_horizontal_p) 
		      ? T : Nil;
	  variable_axis_end_position = 
		  FIXNUM_ADD(variable_axis_begin_position,delta);
	  if ( !TRUEP(CDR(rest_of_deltas)))
	      goto end_loop;
	  variable_axis_begin_position = stable_axis_position;
	  stable_axis_position = variable_axis_end_position;
	  ab_loop_iter_flag_ = Nil;
	  rest_of_deltas = M_CDR(rest_of_deltas);
	  goto next_loop;
	end_loop:
	  if (Orientation_horizontal_p) {
	      result = VALUES_4(variable_axis_end_position,
		      stable_axis_position,Orientation_horizontal_p,
		      rest_of_deltas);
	      goto end_1;
	  }
	  else {
	      result = VALUES_4(stable_axis_position,
		      variable_axis_end_position,Orientation_horizontal_p,
		      rest_of_deltas);
	      goto end_1;
	  }
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
}

/* LOOSE-END-CONNECTION-P */
Object loose_end_connection_p(connection)
    Object connection;
{
    Object connection_input, connection_output, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(101,15);
    connection_input = ISVREF(connection,(SI_Long)3L);
    connection_output = ISVREF(connection,(SI_Long)2L);
    sub_class_bit_vector = ISVREF(ISVREF(connection_input,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(connection_output,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	temp_1 =  !temp ? T : Nil;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(connection_output,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	    temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

/* UPDATE-EXTREME-EDGES-FROM-CONNECTIONS-OF-BLOCK */
Object update_extreme_edges_from_connections_of_block(subblock,
	    do_only_loose_ends_p)
    Object subblock, do_only_loose_ends_p;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(101,16);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
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
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
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
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),subblock))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      if ( !(do_only_loose_ends_p &&  
	      !TRUEP(loose_end_connection_p(connection))))
	  update_extreme_edges_from_connection(connection);
      goto next_loop;
    end_loop_2:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* RECTANGLE-FOR-CONNECTION-SEGMENT */
Object rectangle_for_connection_segment(x1,y1_1,extend1,x2,y2,extend2,
	    half_width,fudge)
    Object x1, y1_1, extend1, x2, y2, extend2, half_width, fudge;
{
    Object temp, temp_1, incff_1_arg, temp_2, temp_3, left, top, right, bottom;
    Object result;

    x_note_fn_call(101,17);
    temp = FIXNUM_MINUS(x1,x2);
    temp_1 = FIXNUM_MINUS(y1_1,y2);
    if (FIXNUM_GE(FIXNUM_ABS(temp),FIXNUM_ABS(temp_1))) {
	if ( !TRUEP(extend1))
	    incff_1_arg = FIX((SI_Long)0L);
	else if (NUM_LT(x1,x2))
	    incff_1_arg = FIXNUM_NEGATE(half_width);
	else
	    incff_1_arg = half_width;
	x1 = FIXNUM_ADD(x1,incff_1_arg);
	if ( !TRUEP(extend2))
	    incff_1_arg = FIX((SI_Long)0L);
	else if (NUM_LT(x2,x1))
	    incff_1_arg = FIXNUM_NEGATE(half_width);
	else
	    incff_1_arg = half_width;
	x2 = FIXNUM_ADD(x2,incff_1_arg);
	temp_2 = FIXNUM_MIN(x1,x2);
	temp_3 = FIXNUM_MINUS(FIXNUM_MIN(y1_1,y2),half_width);
	temp = FIXNUM_MAX(x1,x2);
	temp_1 = FIXNUM_ADD(FIXNUM_MAX(y1_1,y2),half_width);
	result = VALUES_4(temp_2,temp_3,temp,temp_1);
    }
    else {
	if ( !TRUEP(extend1))
	    incff_1_arg = FIX((SI_Long)0L);
	else if (NUM_LT(y1_1,y2))
	    incff_1_arg = FIXNUM_NEGATE(half_width);
	else
	    incff_1_arg = half_width;
	y1_1 = FIXNUM_ADD(y1_1,incff_1_arg);
	if ( !TRUEP(extend2))
	    incff_1_arg = FIX((SI_Long)0L);
	else if (NUM_LT(y2,y1_1))
	    incff_1_arg = FIXNUM_NEGATE(half_width);
	else
	    incff_1_arg = half_width;
	y2 = FIXNUM_ADD(y2,incff_1_arg);
	temp_2 = FIXNUM_MINUS(FIXNUM_MIN(x1,x2),half_width);
	temp_3 = FIXNUM_MIN(y1_1,y2);
	temp = FIXNUM_ADD(FIXNUM_MAX(x1,x2),half_width);
	temp_1 = FIXNUM_MAX(y1_1,y2);
	result = VALUES_4(temp_2,temp_3,temp,temp_1);
    }
    MVS_4(result,left,top,right,bottom);
    temp_2 = FIXNUM_MINUS(FIXNUM_MIN(left,right),fudge);
    temp_3 = FIXNUM_MINUS(FIXNUM_MIN(top,bottom),fudge);
    temp = FIXNUM_ADD(FIXNUM_MAX(left,right),fudge);
    temp_1 = FIXNUM_ADD(FIXNUM_MAX(top,bottom),fudge);
    return VALUES_4(temp_2,temp_3,temp,temp_1);
}

/* MAP-OVER-CONNECTION-RECTANGLES */
Object map_over_connection_rectangles(connection,function,argument)
    Object connection, function, argument;
{
    Object plist;
    char temp;

    x_note_fn_call(101,18);
    plist = ISVREF(connection,(SI_Long)9L);
    temp = plist ? EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal) : TRUEP(Qnil);
    if (temp);
    else
	temp = TRUEP(connection_line_pattern(connection));
    if (temp);
    else
	temp = TRUEP(connection_has_arrows_p(connection));
    if (temp)
	return map_over_diagonal_connection_rectangles(connection,function,
		argument);
    else
	return map_over_orthogonal_or_thin_diagonal_connection_rectangles(connection,
		function,argument);
}

/* MAP-OVER-ORTHOGONAL-OR-THIN-DIAGONAL-CONNECTION-RECTANGLES */
Object map_over_orthogonal_or_thin_diagonal_connection_rectangles(connection,
	    function,argument)
    Object connection, function, argument;
{
    Object gensymed_symbol, input_end_object, input_end_position;
    Object input_end_side, gensymed_symbol_1, initial_orientation_horizontal_p;
    Object output_end_object, output_end_position, output_end_side;
    Object delta_or_deltas, current_x_position, current_y_position;
    Object horizontal_p, connection_half_width, plist, diagonal_qm;
    Object one_segment_qm, sub_class_bit_vector, extend_final_endpoint_qm;
    Object answer, left, top, right, bottom, last_x, last_y, incff_1_arg;
    Object delta_1, delta_2_qm, ab_loop_list_, temp_1, delta, extend_1;
    Object ab_loop_iter_flag_;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position, superior_class_bit_number;
    SI_Long sub_class_vector_index, fudge, incff_1_arg_1, temp;
    Object result;

    x_note_fn_call(101,19);
    gensymed_symbol = connection;
    input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
    input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
    input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
	    (SI_Long)3L);
    input_end_position_on_side = IFIX(input_end_position) >>  -  - (SI_Long)2L;
    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    if (EQ(input_end_side,Qleft))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(input_end_side,Qright)) {
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = input_end_position_on_side;
    input_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    if (EQ(input_end_side,Qtop))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(input_end_side,Qbottom)) {
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = input_end_position_on_side;
    input_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
    initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? T : Nil;
    output_end_object = ISVREF(gensymed_symbol,(SI_Long)2L);
    output_end_position = ISVREF(gensymed_symbol,(SI_Long)4L);
    output_end_side = ISVREF(array_constant,IFIX(output_end_position) & 
	    (SI_Long)3L);
    output_end_position_on_side = IFIX(output_end_position) >>  -  - 
	    (SI_Long)2L;
    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    if (EQ(output_end_side,Qleft))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(output_end_side,Qright)) {
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = output_end_position_on_side;
    output_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    if (EQ(output_end_side,Qtop))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(output_end_side,Qbottom)) {
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = output_end_position_on_side;
    output_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    current_x_position = FIX(input_end_x_position);
    current_y_position = FIX(input_end_y_position);
    horizontal_p = initial_orientation_horizontal_p;
    connection_half_width = 
	    compute_connection_half_width_adjusted_for_fins(connection);
    plist = ISVREF(connection,(SI_Long)9L);
    diagonal_qm = plist ? (EQ(getfq_function_no_default(plist,
	    Qconnection_style),Qdiagonal) ? T : Nil) : Qnil;
    one_segment_qm =  !TRUEP(delta_or_deltas) || ATOM(delta_or_deltas) ? 
	    (horizontal_p ? (input_end_y_position == output_end_y_position 
	    ? T : Nil) : input_end_x_position == output_end_x_position ? T 
	    : Nil) : Qnil;
    sub_class_bit_vector = ISVREF(ISVREF(output_end_object,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	extend_final_endpoint_qm = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
    }
    else
	extend_final_endpoint_qm = Nil;
    answer = argument;
    fudge = diagonal_qm ? (SI_Long)3L : (SI_Long)0L;
    if (diagonal_qm) {
	if ( !TRUEP(delta_or_deltas)) {
	    result = rectangle_for_connection_segment(current_x_position,
		    current_y_position,Nil,FIX(output_end_x_position),
		    FIX(output_end_y_position),extend_final_endpoint_qm,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	}
	else if (NUMBERP(delta_or_deltas)) {
	    if (horizontal_p) {
		last_x = current_x_position;
		last_y = current_y_position;
		incff_1_arg = delta_or_deltas;
		current_x_position = FIXNUM_ADD(current_x_position,
			incff_1_arg);
		incff_1_arg_1 = output_end_y_position - 
			IFIX(current_y_position);
		temp = IFIX(current_y_position) + incff_1_arg_1;
		current_y_position = FIX(temp);
		result = rectangle_for_connection_segment(last_x,last_y,
			Nil,current_x_position,current_y_position,Nil,
			connection_half_width,FIX(fudge));
		MVS_4(result,left,top,right,bottom);
		answer = inline_funcall_5(function,left,top,right,bottom,
			answer);
		horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	    }
	    else {
		last_x = current_x_position;
		last_y = current_y_position;
		incff_1_arg_1 = output_end_x_position - 
			IFIX(current_x_position);
		temp = IFIX(current_x_position) + incff_1_arg_1;
		current_x_position = FIX(temp);
		incff_1_arg = delta_or_deltas;
		current_y_position = FIXNUM_ADD(current_y_position,
			incff_1_arg);
		result = rectangle_for_connection_segment(last_x,last_y,
			Nil,current_x_position,current_y_position,Nil,
			connection_half_width,FIX(fudge));
		MVS_4(result,left,top,right,bottom);
		answer = inline_funcall_5(function,left,top,right,bottom,
			answer);
		horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	    }
	    result = rectangle_for_connection_segment(current_x_position,
		    current_y_position,Nil,FIX(output_end_x_position),
		    FIX(output_end_y_position),extend_final_endpoint_qm,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	}
	else {
	    delta_1 = Nil;
	    delta_2_qm = Nil;
	    ab_loop_list_ = delta_or_deltas;
	    last_x = Nil;
	    last_y = Nil;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    delta_1 = CAR(ab_loop_list_);
	    temp_1 = CDR(ab_loop_list_);
	    delta_2_qm = CAR(temp_1);
	    last_x = current_x_position;
	    last_y = current_y_position;
	    if (horizontal_p) {
		if ( !TRUEP(delta_2_qm))
		    delta_2_qm = FIX(output_end_y_position - 
			    IFIX(current_y_position));
		incff_1_arg = delta_1;
		current_x_position = FIXNUM_ADD(current_x_position,
			incff_1_arg);
		incff_1_arg = delta_2_qm;
		current_y_position = FIXNUM_ADD(current_y_position,
			incff_1_arg);
	    }
	    else {
		if ( !TRUEP(delta_2_qm))
		    delta_2_qm = FIX(output_end_x_position - 
			    IFIX(current_x_position));
		incff_1_arg = delta_2_qm;
		current_x_position = FIXNUM_ADD(current_x_position,
			incff_1_arg);
		incff_1_arg = delta_1;
		current_y_position = FIXNUM_ADD(current_y_position,
			incff_1_arg);
	    }
	    result = rectangle_for_connection_segment(last_x,last_y,Nil,
		    current_x_position,current_y_position,Nil,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:;
	    result = rectangle_for_connection_segment(current_x_position,
		    current_y_position,Nil,FIX(output_end_x_position),
		    FIX(output_end_y_position),extend_final_endpoint_qm,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	}
    }
    else if (one_segment_qm) {
	result = rectangle_for_connection_segment(current_x_position,
		current_y_position,Nil,FIX(output_end_x_position),
		FIX(output_end_y_position),extend_final_endpoint_qm,
		connection_half_width,FIX(fudge));
	MVS_4(result,left,top,right,bottom);
	answer = inline_funcall_5(function,left,top,right,bottom,answer);
    }
    else if ( !TRUEP(delta_or_deltas)) {
	if (horizontal_p) {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    incff_1_arg_1 = output_end_x_position - IFIX(current_x_position);
	    temp = IFIX(current_x_position) + incff_1_arg_1;
	    current_x_position = FIX(temp);
	    temp = IFIX(current_y_position) + (SI_Long)0L;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,Nil,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	else {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    temp = IFIX(current_x_position) + (SI_Long)0L;
	    current_x_position = FIX(temp);
	    incff_1_arg_1 = output_end_y_position - IFIX(current_y_position);
	    temp = IFIX(current_y_position) + incff_1_arg_1;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,Nil,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	result = rectangle_for_connection_segment(current_x_position,
		current_y_position,T,FIX(output_end_x_position),
		FIX(output_end_y_position),extend_final_endpoint_qm,
		connection_half_width,FIX(fudge));
	MVS_4(result,left,top,right,bottom);
	answer = inline_funcall_5(function,left,top,right,bottom,answer);
    }
    else if (NUMBERP(delta_or_deltas)) {
	if (horizontal_p) {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    incff_1_arg = delta_or_deltas;
	    current_x_position = FIXNUM_ADD(current_x_position,incff_1_arg);
	    temp = IFIX(current_y_position) + (SI_Long)0L;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,Nil,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	else {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    temp = IFIX(current_x_position) + (SI_Long)0L;
	    current_x_position = FIX(temp);
	    incff_1_arg = delta_or_deltas;
	    current_y_position = FIXNUM_ADD(current_y_position,incff_1_arg);
	    result = rectangle_for_connection_segment(last_x,last_y,Nil,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	if (horizontal_p) {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    incff_1_arg_1 = output_end_x_position - IFIX(current_x_position);
	    temp = IFIX(current_x_position) + incff_1_arg_1;
	    current_x_position = FIX(temp);
	    temp = IFIX(current_y_position) + (SI_Long)0L;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,T,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	else {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    temp = IFIX(current_x_position) + (SI_Long)0L;
	    current_x_position = FIX(temp);
	    incff_1_arg_1 = output_end_y_position - IFIX(current_y_position);
	    temp = IFIX(current_y_position) + incff_1_arg_1;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,T,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	result = rectangle_for_connection_segment(current_x_position,
		current_y_position,T,FIX(output_end_x_position),
		FIX(output_end_y_position),extend_final_endpoint_qm,
		connection_half_width,FIX(fudge));
	MVS_4(result,left,top,right,bottom);
	answer = inline_funcall_5(function,left,top,right,bottom,answer);
    }
    else {
	delta = Nil;
	ab_loop_list_ = delta_or_deltas;
	extend_1 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	delta = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    extend_1 = T;
	if (horizontal_p) {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    incff_1_arg = delta;
	    current_x_position = FIXNUM_ADD(current_x_position,incff_1_arg);
	    temp = IFIX(current_y_position) + (SI_Long)0L;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,
		    extend_1,current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	else {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    temp = IFIX(current_x_position) + (SI_Long)0L;
	    current_x_position = FIX(temp);
	    incff_1_arg = delta;
	    current_y_position = FIXNUM_ADD(current_y_position,incff_1_arg);
	    result = rectangle_for_connection_segment(last_x,last_y,
		    extend_1,current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:;
	if (horizontal_p) {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    incff_1_arg_1 = output_end_x_position - IFIX(current_x_position);
	    temp = IFIX(current_x_position) + incff_1_arg_1;
	    current_x_position = FIX(temp);
	    temp = IFIX(current_y_position) + (SI_Long)0L;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,T,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	else {
	    last_x = current_x_position;
	    last_y = current_y_position;
	    temp = IFIX(current_x_position) + (SI_Long)0L;
	    current_x_position = FIX(temp);
	    incff_1_arg_1 = output_end_y_position - IFIX(current_y_position);
	    temp = IFIX(current_y_position) + incff_1_arg_1;
	    current_y_position = FIX(temp);
	    result = rectangle_for_connection_segment(last_x,last_y,T,
		    current_x_position,current_y_position,T,
		    connection_half_width,FIX(fudge));
	    MVS_4(result,left,top,right,bottom);
	    answer = inline_funcall_5(function,left,top,right,bottom,answer);
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	}
	result = rectangle_for_connection_segment(current_x_position,
		current_y_position,T,FIX(output_end_x_position),
		FIX(output_end_y_position),extend_final_endpoint_qm,
		connection_half_width,FIX(fudge));
	MVS_4(result,left,top,right,bottom);
	answer = inline_funcall_5(function,left,top,right,bottom,answer);
    }
    return VALUES_1(answer);
}

/* MAP-OVER-DIAGONAL-CONNECTION-RECTANGLES */
Object map_over_diagonal_connection_rectangles(connection,function,argument)
    Object connection, function, argument;
{
    Object connection_frame_or_class, x2, cross_section_pattern;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp_1;
    Object temp_2, new_cons, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, cross_section_stripe, width;
    Object ab_loop_list_, ab_loopvar_, ab_loop_desetq_, stripes_width;
    Object fins_width, answer, vertices, upper_points, lower_points;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, x1, y1_1;
    Object y2, x3, y3, x4, y4, ab_loop_list__1, left, top, right, bottom;
    Object ab_loop_iter_flag_;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    double fwidth2;
    Declare_special(4);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(101,20);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		> (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    cross_section_pattern = ISVREF(connection_frame_or_class,
		    (SI_Long)20L);
	else {
	    if (lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		    Class_description_gkbprop)) {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = connection_frame_or_class;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(connection_frame_or_class) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_1:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_1;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_1;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_1;
		  end_loop_1:
		    gensymed_symbol = Qnil;
		  end_1:;
		    goto end_2;
		}
		goto next_loop;
	      end_loop:
		gensymed_symbol = Qnil;
	      end_2:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = connection_frame_or_class;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_2:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_2;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_3:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_3;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_3;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_3;
		  end_loop_3:
		    kb_properties = Qnil;
		  end_3:;
		    goto end_4;
		}
		goto next_loop_2;
	      end_loop_2:
		kb_properties = Qnil;
	      end_4:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_4:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_4;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_5:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_5;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_5;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_5;
		      end_loop_5:
			kb_specific_value = Qnil;
		      end_5:;
			goto end_6;
		    }
		    goto next_loop_4;
		  end_loop_4:
		    kb_specific_value = Qnil;
		  end_6:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_6:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_6;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_7:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_7;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_7;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_7;
		      end_loop_7:
			resulting_value = Qnil;
		      end_7:;
			goto end_8;
		    }
		    goto next_loop_6;
		  end_loop_6:
		    resulting_value = Qnil;
		  end_8:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qcross_section_pattern,
			gensymed_symbol,Nil);
	    }
	    else {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = Qconnection;
		gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_8:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_8;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_9:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_9;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_9;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_9;
		  end_loop_9:
		    gensymed_symbol = Qnil;
		  end_9:;
		    goto end_10;
		}
		goto next_loop_8;
	      end_loop_8:
		gensymed_symbol = Qnil;
	      end_10:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = Qconnection;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_10:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_10;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_11:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_11;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_11;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_11;
		  end_loop_11:
		    kb_properties = Qnil;
		  end_11:;
		    goto end_12;
		}
		goto next_loop_10;
	      end_loop_10:
		kb_properties = Qnil;
	      end_12:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_12:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_12;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_13:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_13;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_13;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_13;
		      end_loop_13:
			kb_specific_value = Qnil;
		      end_13:;
			goto end_14;
		    }
		    goto next_loop_12;
		  end_loop_12:
		    kb_specific_value = Qnil;
		  end_14:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_14:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_14;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_15:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_15;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_15;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_15;
		      end_loop_15:
			resulting_value = Qnil;
		      end_15:;
			goto end_16;
		    }
		    goto next_loop_14;
		  end_loop_14:
		    resulting_value = Qnil;
		  end_16:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qcross_section_pattern,
			gensymed_symbol,Nil);
	    }
	    cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
	}
	temp_2 = CAAR(cross_section_pattern);
	cross_section_stripe = CONSP(temp_2) ? CDR(cross_section_pattern) :
		 cross_section_pattern;
	width = Nil;
	ab_loop_list_ = cross_section_stripe;
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_desetq_ = Nil;
      next_loop_16:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_16;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	width = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
	goto next_loop_16;
      end_loop_16:
	stripes_width = ab_loopvar_;
	goto end_17;
	stripes_width = Qnil;
      end_17:;
	fins_width = connection_has_arrows_p(connection) ? 
		FIX((SI_Long)0L) : connection_arrow_width(connection);
	fwidth2 = (double)(IFIX(FIXNUM_ADD(stripes_width,fins_width)) + 
		(SI_Long)2L) / 2.0;
	answer = argument;
	vertices = Nil;
	upper_points = Nil;
	lower_points = Nil;
	current_image_x_scale = FIX((SI_Long)4096L);
	current_image_y_scale = FIX((SI_Long)4096L);
	current_x_origin_of_drawing = FIX((SI_Long)0L);
	current_y_origin_of_drawing = FIX((SI_Long)0L);
	PUSH_SPECIAL(Current_y_origin_of_drawing,current_y_origin_of_drawing,
		3);
	  PUSH_SPECIAL(Current_x_origin_of_drawing,current_x_origin_of_drawing,
		  2);
	    PUSH_SPECIAL(Current_image_y_scale,current_image_y_scale,1);
	      PUSH_SPECIAL(Current_image_x_scale,current_image_x_scale,0);
		vertices = compute_connection_vertices(connection);
		upper_points = 
			compute_miter_points(DOUBLE_TO_DOUBLE_FLOAT(fwidth2),
			vertices);
		lower_points = 
			compute_miter_points(DOUBLE_TO_DOUBLE_FLOAT( - 
			fwidth2),vertices);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	x1 = Nil;
	y1_1 = Nil;
	x2 = Nil;
	y2 = Nil;
	ab_loop_list_ = upper_points;
	x3 = Nil;
	y3 = Nil;
	x4 = Nil;
	y4 = Nil;
	ab_loop_list__1 = lower_points;
	left = Nil;
	top = Nil;
	right = Nil;
	bottom = Nil;
	ab_loop_iter_flag_ = T;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_17;
      next_loop_17:
	x1 = CAR(ab_loop_list_);
	temp_2 = CDR(ab_loop_list_);
	y1_1 = CAR(temp_2);
	temp_2 = CDR(ab_loop_list_);
	temp_2 = CDR(temp_2);
	x2 = CAR(temp_2);
	temp_2 = CDR(ab_loop_list_);
	temp_2 = CDR(temp_2);
	temp_2 = CDR(temp_2);
	y2 = CAR(temp_2);
	if (ab_loop_iter_flag_) {
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_17;
	}
	else {
	    ab_loop_list__1 = CDDR(ab_loop_list__1);
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_17;
	}
	x3 = CAR(ab_loop_list__1);
	temp_2 = CDR(ab_loop_list__1);
	y3 = CAR(temp_2);
	temp_2 = CDR(ab_loop_list__1);
	temp_2 = CDR(temp_2);
	x4 = CAR(temp_2);
	temp_2 = CDR(ab_loop_list__1);
	temp_2 = CDR(temp_2);
	temp_2 = CDR(temp_2);
	y4 = CAR(temp_2);
	if ( !TRUEP(x2))
	    goto end_loop_17;
	temp_2 = FIXNUM_MIN(x1,x2);
	temp_2 = FIXNUM_MIN(temp_2,x3);
	left = FIXNUM_MIN(temp_2,x4);
	temp_2 = FIXNUM_MIN(y1_1,y2);
	temp_2 = FIXNUM_MIN(temp_2,y3);
	top = FIXNUM_MIN(temp_2,y4);
	temp_2 = FIXNUM_MAX(x1,x2);
	temp_2 = FIXNUM_MAX(temp_2,x3);
	right = FIXNUM_ADD1(FIXNUM_MAX(temp_2,x4));
	temp_2 = FIXNUM_MAX(y1_1,y2);
	temp_2 = FIXNUM_MAX(temp_2,y3);
	bottom = FIXNUM_ADD1(FIXNUM_MAX(temp_2,y4));
	answer = inline_funcall_5(function,left,top,right,bottom,answer);
	ab_loop_iter_flag_ = Nil;
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_17;
	goto next_loop_17;
      end_loop_17:;
	if (connection_has_arrows_p(connection))
	    answer = map_over_connection_arrows(connection,vertices,
		    function,answer);
	reclaim_gensym_list_1(vertices);
	reclaim_gensym_list_1(upper_points);
	reclaim_gensym_list_1(lower_points);
	result = VALUES_1(answer);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qadd_rectangle_to_region;  /* add-rectangle-to-region */

/* CONNECTION-BOUNDING-REGION */
Object connection_bounding_region(connection)
    Object connection;
{
    x_note_fn_call(101,21);
    return map_over_connection_rectangles(connection,
	    SYMBOL_FUNCTION(Qadd_rectangle_to_region),make_empty_region());
}

static Object Qupdate_extreme_edges_from_connection_1;  /* update-extreme-edges-from-connection-1 */

/* UPDATE-EXTREME-EDGES-FROM-CONNECTION */
Object update_extreme_edges_from_connection(connection)
    Object connection;
{
    x_note_fn_call(101,22);
    map_over_connection_rectangles(connection,
	    SYMBOL_FUNCTION(Qupdate_extreme_edges_from_connection_1),Nil);
    return VALUES_1(Nil);
}

/* UPDATE-EXTREME-EDGES-FROM-CONNECTION-1 */
Object update_extreme_edges_from_connection_1(left,top,right,bottom,arg)
    Object left, top, right, bottom, arg;
{
    Object temp;

    x_note_fn_call(101,23);
    if (FIXNUM_LT(left,Extreme_left_edge_so_far))
	Extreme_left_edge_so_far = left;
    if (FIXNUM_GT(right,Extreme_right_edge_so_far))
	Extreme_right_edge_so_far = right;
    if (FIXNUM_LT(top,Extreme_top_edge_so_far))
	Extreme_top_edge_so_far = top;
    if (FIXNUM_GT(bottom,Extreme_bottom_edge_so_far)) {
	Extreme_bottom_edge_so_far = bottom;
	temp = Extreme_bottom_edge_so_far;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* COMPUTE-CONNECTION-HALF-WIDTH-ADJUSTED-FOR-FINS */
Object compute_connection_half_width_adjusted_for_fins(connection)
    Object connection;
{
    Object plist, connection_frame_or_class, x2, cross_section_pattern;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp_1;
    Object temp_2, new_cons, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, cross_section_stripe, width;
    Object ab_loop_list_, ab_loopvar_, ab_loop_desetq_;
    SI_Long basis_half_width, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(101,24);
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist && EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal))
	basis_half_width = (SI_Long)1L;
    else {
	connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		> (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    cross_section_pattern = ISVREF(connection_frame_or_class,
		    (SI_Long)20L);
	else {
	    if (lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		    Class_description_gkbprop)) {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = connection_frame_or_class;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(connection_frame_or_class) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_1:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_1;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_1;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_1;
		  end_loop_1:
		    gensymed_symbol = Qnil;
		  end_1:;
		    goto end_2;
		}
		goto next_loop;
	      end_loop:
		gensymed_symbol = Qnil;
	      end_2:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = connection_frame_or_class;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_2:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_2;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_3:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_3;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_3;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_3;
		  end_loop_3:
		    kb_properties = Qnil;
		  end_3:;
		    goto end_4;
		}
		goto next_loop_2;
	      end_loop_2:
		kb_properties = Qnil;
	      end_4:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_4:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_4;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_5:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_5;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_5;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_5;
		      end_loop_5:
			kb_specific_value = Qnil;
		      end_5:;
			goto end_6;
		    }
		    goto next_loop_4;
		  end_loop_4:
		    kb_specific_value = Qnil;
		  end_6:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_6:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_6;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_7:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_7;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_7;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_7;
		      end_loop_7:
			resulting_value = Qnil;
		      end_7:;
			goto end_8;
		    }
		    goto next_loop_6;
		  end_loop_6:
		    resulting_value = Qnil;
		  end_8:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qcross_section_pattern,
			gensymed_symbol,Nil);
	    }
	    else {
		gensymed_symbol = CDR(Symbol_properties_table);
		gensymed_symbol_1 = Qconnection;
		gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_8:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_8;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_9:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_9;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
			goto end_9;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_9;
		  end_loop_9:
		    gensymed_symbol = Qnil;
		  end_9:;
		    goto end_10;
		}
		goto next_loop_8;
	      end_loop_8:
		gensymed_symbol = Qnil;
	      end_10:;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = Qconnection;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    new_cons = Available_gensym_conses;
		    if (new_cons) {
			Available_gensym_conses = M_CDR(new_cons);
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gensym_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		    gensymed_symbol = 
			    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,
			    T,gensymed_symbol,temp_2,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = 
			Current_kb_specific_property_list_property_name;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_10:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_10;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_11:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_11;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_properties = M_CDR(M_CAR(gensymed_symbol));
			goto end_11;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_11;
		  end_loop_11:
		    kb_properties = Qnil;
		  end_11:;
		    goto end_12;
		}
		goto next_loop_10;
	      end_loop_10:
		kb_properties = Qnil;
	      end_12:;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    gensymed_symbol = CDR(kb_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_12:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_12;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_13:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_13;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_13;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_13;
		      end_loop_13:
			kb_specific_value = Qnil;
		      end_13:;
			goto end_14;
		    }
		    goto next_loop_12;
		  end_loop_12:
		    kb_specific_value = Qnil;
		  end_14:;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    gensymed_symbol = CDR(global_properties);
		    gensymed_symbol_1 = Class_description_gkbprop;
		    gensymed_symbol_2 = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_14:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_14;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_15:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_15;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			    resulting_value = M_CDR(M_CAR(gensymed_symbol));
			    goto end_15;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_15;
		      end_loop_15:
			resulting_value = Qnil;
		      end_15:;
			goto end_16;
		    }
		    goto next_loop_14;
		  end_loop_14:
		    resulting_value = Qnil;
		  end_16:;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			get_slot_description_of_class_description_function(Qcross_section_pattern,
			gensymed_symbol,Nil);
	    }
	    cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
	}
	temp_2 = CAAR(cross_section_pattern);
	cross_section_stripe = CONSP(temp_2) ? CDR(cross_section_pattern) :
		 cross_section_pattern;
	width = Nil;
	ab_loop_list_ = cross_section_stripe;
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_desetq_ = Nil;
      next_loop_16:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_16;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	width = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
	goto next_loop_16;
      end_loop_16:
	gensymed_symbol_2 = IFIX(ab_loopvar_);
	goto end_17;
	gensymed_symbol_2 = IFIX(Qnil);
      end_17:;
	gensymed_symbol_3 = (SI_Long)1L;
	basis_half_width = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
    }
    gensymed_symbol_2 = basis_half_width;
    gensymed_symbol_3 =  !((SI_Long)0L != (IFIX(ISVREF(connection,
	    (SI_Long)7L)) & (SI_Long)1L)) ? IFIX(connection_fin_length(2,
	    connection,FIX(basis_half_width * (SI_Long)2L))) + (SI_Long)3L 
	    : (SI_Long)1L;
    return VALUES_1(FIX(gensymed_symbol_2 + gensymed_symbol_3));
}

/* OUTPUT-CONNECTIONS-OF-BLOCK */
Object output_connections_of_block(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,25);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
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
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
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
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      ab_loopvar__2 = gensym_cons_1(connection,Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      goto next_loop;
    end_loop_2:
      result = VALUES_1(ab_loopvar_);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qgraph;              /* graph */

/* DESCENDENTS-OF-BLOCK-OR-CONNECTION */
Object descendents_of_block_or_connection(block_or_connection)
    Object block_or_connection;
{
    Object list_1, stack, sibling, gensym_pop_store, cons_1, next_cons;
    Object cdr_new_value, temp, infs, sub_class_bit_vector, gensymed_symbol_3;
    Object subblocks, queue, next_queue_element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, list_1_1, list_2, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(101,26);
    list_1 = Nil;
    stack = gensym_cons_1(block_or_connection,Nil);
    sibling = Nil;
  next_loop:
    if ( !TRUEP(stack))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = stack;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	Available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    stack = next_cons;
    temp = gensym_pop_store;
    sibling = Nil;
    if (EQ(temp,Tree_traversal_marker)) {
	gensym_pop_store = Nil;
	cons_1 = stack;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    cdr_new_value = Available_gensym_conses;
	    M_CDR(cons_1) = cdr_new_value;
	    Available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	stack = next_cons;
	sibling = gensym_pop_store;
    }
    else if ( !SYMBOLP(temp)) {
	if (SIMPLE_VECTOR_P(temp) && EQ(ISVREF(temp,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct))
	    infs = Nil;
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(temp,(SI_Long)1L),
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
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		subblocks = gensymed_symbol_3;
		if (subblocks) {
		    queue = subblocks;
		    next_queue_element = Nil;
		    gensymed_symbol_3 = Nil;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    next_queue_element = ISVREF(queue,(SI_Long)0L);
		  next_loop_1:
		    if (EQ(next_queue_element,queue))
			goto end_loop_1;
		    gensymed_symbol_3 = ISVREF(next_queue_element,(SI_Long)2L);
		    next_queue_element = ISVREF(next_queue_element,
			    (SI_Long)0L);
		    ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_1;
		  end_loop_1:
		    infs = ab_loopvar_;
		    goto end_1;
		    infs = Qnil;
		  end_1:;
		}
		else
		    infs = Nil;
	    }
	    else if (EQ(ISVREF(ISVREF(temp,(SI_Long)1L),(SI_Long)1L),Qgraph))
		infs = Nil;
	    else {
		gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		subblocks = gensymed_symbol_3;
		if (subblocks) {
		    queue = subblocks;
		    next_queue_element = Nil;
		    gensymed_symbol_3 = Nil;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    next_queue_element = ISVREF(queue,(SI_Long)0L);
		  next_loop_2:
		    if (EQ(next_queue_element,queue))
			goto end_loop_2;
		    gensymed_symbol_3 = ISVREF(next_queue_element,(SI_Long)2L);
		    next_queue_element = ISVREF(next_queue_element,
			    (SI_Long)0L);
		    ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_2;
		  end_loop_2:
		    list_1_1 = ab_loopvar_;
		    goto end_2;
		    list_1_1 = Qnil;
		  end_2:;
		}
		else
		    list_1_1 = Nil;
		list_2 = output_connections_of_block(temp);
		if ( !TRUEP(list_1_1))
		    temp_2 = list_2;
		else if ( !TRUEP(list_2))
		    temp_2 = list_1_1;
		else
		    temp_2 = nconc2(list_1_1,list_2);
		infs = nreverse(temp_2);
	    }
	}
	if ( !TRUEP(infs))
	    sibling = temp;
	else {
	    temp_3 = T ? infs : copy_list_using_gensym_conses_1(infs);
	    temp_2 = gensym_cons_1(Tree_traversal_marker,Nil);
	    stack = nconc2(temp_3,nconc2(temp_2,nconc2(gensym_cons_1(temp,
		    Nil),stack)));
	}
    }
    if (sibling) {
	if ( !EQ(sibling,block_or_connection))
	    list_1 = gensym_cons_1(sibling,list_1);
    }
    goto next_loop;
  end_loop:
    if (stack)
	reclaim_gensym_list_1(stack);
    return VALUES_1(list_1);
}

/* LOCAL-EDGES-OF-BLOCK-OR-CONNECTION */
Object local_edges_of_block_or_connection(block_or_connection)
    Object block_or_connection;
{
    Object extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(101,27);
    extreme_left_edge_so_far = Most_positive_fixnum;
    PUSH_SPECIAL(Extreme_left_edge_so_far,extreme_left_edge_so_far,3);
      extreme_top_edge_so_far = Most_positive_fixnum;
      PUSH_SPECIAL(Extreme_top_edge_so_far,extreme_top_edge_so_far,2);
	extreme_right_edge_so_far = Most_negative_fixnum;
	PUSH_SPECIAL(Extreme_right_edge_so_far,extreme_right_edge_so_far,1);
	  extreme_bottom_edge_so_far = Most_negative_fixnum;
	  PUSH_SPECIAL(Extreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    if (SIMPLE_VECTOR_P(block_or_connection) && 
		    EQ(ISVREF(block_or_connection,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		update_extreme_edges_from_connection(block_or_connection);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(block_or_connection,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_class_description,
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
		if (temp) {
		    if (ISVREF(block_or_connection,(SI_Long)21L))
			update_extreme_edges_from_connection(ISVREF(block_or_connection,
				(SI_Long)21L));
		}
		else
		    update_extreme_edges_from_block_bounds(block_or_connection);
	    }
	    result = VALUES_4(Extreme_left_edge_so_far,
		    Extreme_top_edge_so_far,Extreme_right_edge_so_far,
		    Extreme_bottom_edge_so_far);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* BOUNDING-REGION-OF-BLOCK-OR-CONNECTION */
Object bounding_region_of_block_or_connection(block_or_connection)
    Object block_or_connection;
{
    Object extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Object sub_class_bit_vector, left, top, right, bottom;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(101,28);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return connection_bounding_region(block_or_connection);
    else {
	extreme_left_edge_so_far = Most_positive_fixnum;
	PUSH_SPECIAL(Extreme_left_edge_so_far,extreme_left_edge_so_far,3);
	  extreme_top_edge_so_far = Most_positive_fixnum;
	  PUSH_SPECIAL(Extreme_top_edge_so_far,extreme_top_edge_so_far,2);
	    extreme_right_edge_so_far = Most_negative_fixnum;
	    PUSH_SPECIAL(Extreme_right_edge_so_far,extreme_right_edge_so_far,
		    1);
	      extreme_bottom_edge_so_far = Most_negative_fixnum;
	      PUSH_SPECIAL(Extreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		      0);
		if (SIMPLE_VECTOR_P(block_or_connection) && 
			EQ(ISVREF(block_or_connection,(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct))
		    update_extreme_edges_from_connection(block_or_connection);
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(block_or_connection,(SI_Long)1L),
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
		    if (temp) {
			if (ISVREF(block_or_connection,(SI_Long)21L))
			    update_extreme_edges_from_connection(ISVREF(block_or_connection,
				    (SI_Long)21L));
		    }
		    else
			update_extreme_edges_from_block_bounds(block_or_connection);
		}
		result = VALUES_4(Extreme_left_edge_so_far,
			Extreme_top_edge_so_far,Extreme_right_edge_so_far,
			Extreme_bottom_edge_so_far);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	MVS_4(result,left,top,right,bottom);
	return make_region_from_rectangle(left,top,right,bottom);
    }
}

/* GET-WORKSPACE-OF-BLOCK-OR-CONNECTION */
Object get_workspace_of_block_or_connection(block_or_connection)
    Object block_or_connection;
{
    Object this_block, superblock_qm, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(101,29);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return workspace_of_connection_qm(block_or_connection);
    else {
	this_block = block_or_connection;
	superblock_qm = Nil;
      next_loop:
	gensymed_symbol = ISVREF(this_block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)5L) : Nil;
	superblock_qm = gensymed_symbol;
	if ( !TRUEP(superblock_qm)) {
	    sub_class_bit_vector = ISVREF(ISVREF(this_block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    if (temp)
		return VALUES_1(this_block);
	    else
		return VALUES_1(Nil);
	}
	this_block = superblock_qm;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* BLOCK-OR-CONNECTION-OVERLAP-CACHE-VALID-P */
Object block_or_connection_overlap_cache_valid_p(block_or_connection)
    Object block_or_connection;
{
    x_note_fn_call(101,30);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block_or_connection,
		(SI_Long)7L)) & (SI_Long)32L) ? T : Nil);
    else
	return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block_or_connection,
		(SI_Long)5L)) & (SI_Long)65536L) ? T : Nil);
}

static Object Qoverlapping_blocks;  /* overlapping-blocks */

static Object Qoverlapping_blocks_cache;  /* overlapping-blocks-cache */

/* SET-BLOCK-OR-CONNECTION-OVERLAP-CACHE-VALID-P */
Object set_block_or_connection_overlap_cache_valid_p(block_or_connection,
	    valid_p)
    Object block_or_connection, valid_p;
{
    SI_Long svref_new_value;

    x_note_fn_call(101,31);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct)) {
	if (valid_p) {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)7L)) | (SI_Long)32L;
	    ISVREF(block_or_connection,(SI_Long)7L) = FIX(svref_new_value);
	}
	else {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)7L)) &  ~(SI_Long)32L;
	    ISVREF(block_or_connection,(SI_Long)7L) = FIX(svref_new_value);
	}
	if ( !TRUEP(valid_p)) {
	    if (getfq_function_no_default(ISVREF(block_or_connection,
		    (SI_Long)9L),Qoverlapping_blocks))
		return change_connection_attribute_1(block_or_connection,
			Qoverlapping_blocks,Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	if (valid_p) {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)5L)) | (SI_Long)65536L;
	    ISVREF(block_or_connection,(SI_Long)5L) = FIX(svref_new_value);
	}
	else {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)5L)) &  ~(SI_Long)65536L;
	    ISVREF(block_or_connection,(SI_Long)5L) = FIX(svref_new_value);
	}
	if ( !TRUEP(valid_p)) {
	    if (get_lookup_slot_value_given_default(block_or_connection,
		    Qoverlapping_blocks_cache,Nil)) {
		reclaim_gensym_list_1(get_lookup_slot_value_given_default(block_or_connection,
			Qoverlapping_blocks_cache,Nil));
		return set_non_savable_lookup_slot_value(block_or_connection,
			Qoverlapping_blocks_cache,Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* BLOCK-OR-CONNECTION-OVERLAP-CACHE-P */
Object block_or_connection_overlap_cache_p(block_or_connection)
    Object block_or_connection;
{
    x_note_fn_call(101,32);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block_or_connection,
		(SI_Long)7L)) & (SI_Long)16L) ? T : Nil);
    else
	return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block_or_connection,
		(SI_Long)5L)) & (SI_Long)16384L) ? T : Nil);
}

/* SET-BLOCK-OR-CONNECTION-OVERLAP-CACHE-P */
Object set_block_or_connection_overlap_cache_p(block_or_connection,new_value)
    Object block_or_connection, new_value;
{
    SI_Long svref_new_value;

    x_note_fn_call(101,33);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct)) {
	if (new_value) {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)7L)) | (SI_Long)16L;
	    ISVREF(block_or_connection,(SI_Long)7L) = FIX(svref_new_value);
	}
	else {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)7L)) &  ~(SI_Long)16L;
	    ISVREF(block_or_connection,(SI_Long)7L) = FIX(svref_new_value);
	}
	return VALUES_1(new_value);
    }
    else {
	if (new_value) {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)5L)) | (SI_Long)16384L;
	    ISVREF(block_or_connection,(SI_Long)5L) = FIX(svref_new_value);
	}
	else {
	    svref_new_value = IFIX(ISVREF(block_or_connection,
		    (SI_Long)5L)) &  ~(SI_Long)16384L;
	    ISVREF(block_or_connection,(SI_Long)5L) = FIX(svref_new_value);
	}
	return VALUES_1(new_value);
    }
}

/* BLOCK-OR-CONNECTION-OVERLAP-CACHE */
Object block_or_connection_overlap_cache(block_or_connection)
    Object block_or_connection;
{
    x_note_fn_call(101,34);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return getfq_function_no_default(ISVREF(block_or_connection,
		(SI_Long)9L),Qoverlapping_blocks);
    else
	return get_lookup_slot_value_given_default(block_or_connection,
		Qoverlapping_blocks_cache,Nil);
}

/* SET-BLOCK-OR-CONNECTION-OVERLAP-CACHE */
Object set_block_or_connection_overlap_cache(block_or_connection,new_value)
    Object block_or_connection, new_value;
{
    x_note_fn_call(101,35);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return change_connection_attribute_1(block_or_connection,
		Qoverlapping_blocks,new_value);
    else
	return set_non_savable_lookup_slot_value(block_or_connection,
		Qoverlapping_blocks_cache,new_value);
}

/* BLOCK-OR-CONNECTION-MIGHT-OVERLAP-P */
Object block_or_connection_might_overlap_p(block_or_connection)
    Object block_or_connection;
{
    Object temp;

    x_note_fn_call(101,36);
    temp =  
	    !TRUEP(block_or_connection_overlap_cache_valid_p(block_or_connection)) 
	    ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return block_or_connection_overlap_cache_p(block_or_connection);
}

Object Workspace_geometry_tick_mask = UNBOUND;

/* NOTE-CHANGE-TO-WORKSPACE-GEOMETRY */
Object note_change_to_workspace_geometry(workspace_qm)
    Object workspace_qm;
{
    Object temp, stack, subblock_or_connection, gensym_pop_store, cons_1;
    Object next_cons, temp_1, infs, sub_class_bit_vector, gensymed_symbol_3;
    Object subblocks, queue, next_queue_element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, list_1, list_2, temp_3, temp_4;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;

    x_note_fn_call(101,37);
    if (workspace_qm) {
	temp = FIXNUM_LOGAND(FIXNUM_ADD1(ISVREF(workspace_qm,
		(SI_Long)25L)),Workspace_geometry_tick_mask);
	ISVREF(workspace_qm,(SI_Long)25L) = temp;
	if ((SI_Long)0L != (IFIX(ISVREF(workspace_qm,(SI_Long)5L)) & 
		(SI_Long)65536L)) {
	    svref_new_value = IFIX(ISVREF(workspace_qm,(SI_Long)5L)) &  
		    ~(SI_Long)65536L;
	    ISVREF(workspace_qm,(SI_Long)5L) = FIX(svref_new_value);
	    stack = gensym_cons_1(workspace_qm,Nil);
	    subblock_or_connection = Nil;
	  next_loop:
	    if ( !TRUEP(stack))
		goto end_loop;
	    gensym_pop_store = Nil;
	    cons_1 = stack;
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_gensym);
		temp = Available_gensym_conses;
		M_CDR(cons_1) = temp;
		Available_gensym_conses = cons_1;
	    }
	    else
		next_cons = Nil;
	    stack = next_cons;
	    temp_1 = gensym_pop_store;
	    subblock_or_connection = Nil;
	    if (EQ(temp_1,Tree_traversal_marker)) {
		gensym_pop_store = Nil;
		cons_1 = stack;
		if (cons_1) {
		    gensym_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qab_gensym);
		    temp = Available_gensym_conses;
		    M_CDR(cons_1) = temp;
		    Available_gensym_conses = cons_1;
		}
		else
		    next_cons = Nil;
		stack = next_cons;
		subblock_or_connection = gensym_pop_store;
	    }
	    else if ( !SYMBOLP(temp_1)) {
		if (SIMPLE_VECTOR_P(temp_1) && EQ(ISVREF(temp_1,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct))
		    infs = Nil;
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(temp_1,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Workspace_class_description,
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
			temp_2 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			gensymed_symbol_3 = ISVREF(temp_1,(SI_Long)14L);
			gensymed_symbol_3 = gensymed_symbol_3 ? 
				ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
			subblocks = gensymed_symbol_3;
			if (subblocks) {
			    queue = subblocks;
			    next_queue_element = Nil;
			    gensymed_symbol_3 = Nil;
			    ab_loopvar_ = Nil;
			    ab_loopvar__1 = Nil;
			    ab_loopvar__2 = Nil;
			    next_queue_element = ISVREF(queue,(SI_Long)0L);
			  next_loop_1:
			    if (EQ(next_queue_element,queue))
				goto end_loop_1;
			    gensymed_symbol_3 = ISVREF(next_queue_element,
				    (SI_Long)2L);
			    next_queue_element = ISVREF(next_queue_element,
				    (SI_Long)0L);
			    ab_loopvar__2 = 
				    gensym_cons_1(gensymed_symbol_3,Nil);
			    if (ab_loopvar__1)
				M_CDR(ab_loopvar__1) = ab_loopvar__2;
			    else
				ab_loopvar_ = ab_loopvar__2;
			    ab_loopvar__1 = ab_loopvar__2;
			    goto next_loop_1;
			  end_loop_1:
			    infs = ab_loopvar_;
			    goto end_1;
			    infs = Qnil;
			  end_1:;
			}
			else
			    infs = Nil;
		    }
		    else if (EQ(ISVREF(ISVREF(temp_1,(SI_Long)1L),
			    (SI_Long)1L),Qgraph))
			infs = Nil;
		    else {
			gensymed_symbol_3 = ISVREF(temp_1,(SI_Long)14L);
			gensymed_symbol_3 = gensymed_symbol_3 ? 
				ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
			subblocks = gensymed_symbol_3;
			if (subblocks) {
			    queue = subblocks;
			    next_queue_element = Nil;
			    gensymed_symbol_3 = Nil;
			    ab_loopvar_ = Nil;
			    ab_loopvar__1 = Nil;
			    ab_loopvar__2 = Nil;
			    next_queue_element = ISVREF(queue,(SI_Long)0L);
			  next_loop_2:
			    if (EQ(next_queue_element,queue))
				goto end_loop_2;
			    gensymed_symbol_3 = ISVREF(next_queue_element,
				    (SI_Long)2L);
			    next_queue_element = ISVREF(next_queue_element,
				    (SI_Long)0L);
			    ab_loopvar__2 = 
				    gensym_cons_1(gensymed_symbol_3,Nil);
			    if (ab_loopvar__1)
				M_CDR(ab_loopvar__1) = ab_loopvar__2;
			    else
				ab_loopvar_ = ab_loopvar__2;
			    ab_loopvar__1 = ab_loopvar__2;
			    goto next_loop_2;
			  end_loop_2:
			    list_1 = ab_loopvar_;
			    goto end_2;
			    list_1 = Qnil;
			  end_2:;
			}
			else
			    list_1 = Nil;
			list_2 = output_connections_of_block(temp_1);
			if ( !TRUEP(list_1))
			    temp_3 = list_2;
			else if ( !TRUEP(list_2))
			    temp_3 = list_1;
			else
			    temp_3 = nconc2(list_1,list_2);
			infs = nreverse(temp_3);
		    }
		}
		if ( !TRUEP(infs))
		    subblock_or_connection = temp_1;
		else {
		    temp_4 = T ? infs : copy_list_using_gensym_conses_1(infs);
		    temp_3 = gensym_cons_1(Tree_traversal_marker,Nil);
		    stack = nconc2(temp_4,nconc2(temp_3,
			    nconc2(gensym_cons_1(temp_1,Nil),stack)));
		}
	    }
	    if (subblock_or_connection) {
		if ( !EQ(subblock_or_connection,workspace_qm))
		    set_block_or_connection_overlap_cache_valid_p(subblock_or_connection,
			    Nil);
	    }
	    goto next_loop;
	  end_loop:
	    temp_1 = Qnil;
	    if (stack)
		reclaim_gensym_list_1(stack);
	    return VALUES_1(temp_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-SUBBLOCKS-AND-CONNECTIONS-FROM-DRAWING-QUEUES */
Object remove_subblocks_and_connections_from_drawing_queues(workspace,block)
    Object workspace, block;
{
    Object stack, subblock, gensym_pop_store, cons_1, next_cons, cdr_new_value;
    Object temp, infs, sub_class_bit_vector, gensymed_symbol_3, subblocks;
    Object queue, next_queue_element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, list_1, list_2, temp_2, temp_3, x2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(101,38);
    stack = gensym_cons_1(block,Nil);
    subblock = Nil;
  next_loop:
    if ( !TRUEP(stack))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = stack;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	Available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    stack = next_cons;
    temp = gensym_pop_store;
    subblock = Nil;
    if (EQ(temp,Tree_traversal_marker)) {
	gensym_pop_store = Nil;
	cons_1 = stack;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    cdr_new_value = Available_gensym_conses;
	    M_CDR(cons_1) = cdr_new_value;
	    Available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	stack = next_cons;
	subblock = gensym_pop_store;
    }
    else if ( !SYMBOLP(temp)) {
	if (SIMPLE_VECTOR_P(temp) && EQ(ISVREF(temp,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct))
	    infs = Nil;
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(temp,(SI_Long)1L),
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
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		subblocks = gensymed_symbol_3;
		if (subblocks) {
		    queue = subblocks;
		    next_queue_element = Nil;
		    gensymed_symbol_3 = Nil;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    next_queue_element = ISVREF(queue,(SI_Long)0L);
		  next_loop_1:
		    if (EQ(next_queue_element,queue))
			goto end_loop_1;
		    gensymed_symbol_3 = ISVREF(next_queue_element,(SI_Long)2L);
		    next_queue_element = ISVREF(next_queue_element,
			    (SI_Long)0L);
		    ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_1;
		  end_loop_1:
		    infs = ab_loopvar_;
		    goto end_1;
		    infs = Qnil;
		  end_1:;
		}
		else
		    infs = Nil;
	    }
	    else if (EQ(ISVREF(ISVREF(temp,(SI_Long)1L),(SI_Long)1L),Qgraph))
		infs = Nil;
	    else {
		gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		subblocks = gensymed_symbol_3;
		if (subblocks) {
		    queue = subblocks;
		    next_queue_element = Nil;
		    gensymed_symbol_3 = Nil;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    next_queue_element = ISVREF(queue,(SI_Long)0L);
		  next_loop_2:
		    if (EQ(next_queue_element,queue))
			goto end_loop_2;
		    gensymed_symbol_3 = ISVREF(next_queue_element,(SI_Long)2L);
		    next_queue_element = ISVREF(next_queue_element,
			    (SI_Long)0L);
		    ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_2;
		  end_loop_2:
		    list_1 = ab_loopvar_;
		    goto end_2;
		    list_1 = Qnil;
		  end_2:;
		}
		else
		    list_1 = Nil;
		list_2 = output_connections_of_block(temp);
		if ( !TRUEP(list_1))
		    temp_2 = list_2;
		else if ( !TRUEP(list_2))
		    temp_2 = list_1;
		else
		    temp_2 = nconc2(list_1,list_2);
		infs = nreverse(temp_2);
	    }
	}
	if ( !TRUEP(infs))
	    subblock = temp;
	else {
	    temp_3 = T ? infs : copy_list_using_gensym_conses_1(infs);
	    temp_2 = gensym_cons_1(Tree_traversal_marker,Nil);
	    stack = nconc2(temp_3,nconc2(temp_2,nconc2(gensym_cons_1(temp,
		    Nil),stack)));
	}
    }
    if (subblock) {
	if ( !EQ(subblock,block)) {
	    if ( !EQ(subblock,block)) {
		if (SIMPLE_VECTOR_P(subblock) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subblock)) > 
			(SI_Long)2L &&  !EQ(ISVREF(subblock,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(subblock,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    remove_block_from_drawing_queues(workspace,subblock);
		else
		    note_deletion_of_connection_for_drawing(subblock);
	    }
	}
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
    if (stack)
	reclaim_gensym_list_1(stack);
    return VALUES_1(temp);
}

/* VALIDATE-OVERLAPPING-CACHE-FOR-WORKSPACE */
Object validate_overlapping_cache_for_workspace(workspace)
    Object workspace;
{
    SI_Long svref_new_value;

    x_note_fn_call(101,39);
    svref_new_value = IFIX(ISVREF(workspace,(SI_Long)5L)) | (SI_Long)65536L;
    ISVREF(workspace,(SI_Long)5L) = FIX(svref_new_value);
    return VALUES_1(T);
}

/* DRAW-BLOCK-OR-CONNECTION */
Object draw_block_or_connection(block_or_connection)
    Object block_or_connection;
{
    x_note_fn_call(101,40);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return draw_connection(block_or_connection,Nil);
    else
	return draw_block_possibly_with_frame(block_or_connection,Nil);
}

static Object Qframe_transforms_of_block;  /* frame-transforms-of-block */

static Object Qabove;              /* above */

static Object Qabove_inclusive;    /* above-inclusive */

/* OVERLAPPING-SIBLINGS */
Object overlapping_siblings(workspace,block_or_connection,aboveness)
    Object workspace, block_or_connection, aboveness;
{
    Object x2, sub_class_bit_vector, thing, list_1, block, gensymed_symbol_3;
    Object block_qm, frame_transform_block_qm, transformed_qm, this_region;
    Object extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far, left, top;
    Object right, bottom, candidates, answer, sibling, ab_loop_list_, region;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(101,41);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_connection)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(block_or_connection,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(block_or_connection,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(block_or_connection,
		(SI_Long)1L),(SI_Long)19L);
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
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    thing = temp ? ISVREF(block_or_connection,(SI_Long)21L) : 
	    block_or_connection;
    if ( !((SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)5L)) & 
	    (SI_Long)65536L)))
	validate_overlapping_cache_for_workspace(workspace);
    if (block_or_connection_overlap_cache_valid_p(thing))
	list_1 = block_or_connection_overlap_cache(thing);
    else {
	block = SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct) ? 
		ISVREF(thing,(SI_Long)3L) : thing;
	if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)32768L) &&  
		!TRUEP(frame_description_reference_of_block_qm(block)) ? 
		TRUEP(T) : TRUEP(Nil)) {
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		thing = ISVREF(thing,(SI_Long)3L);
	    gensymed_symbol_3 = ISVREF(thing,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)5L) : Nil;
	    block_qm = gensymed_symbol_3;
	  next_loop:
	    if ( !TRUEP(block_qm))
		goto end_loop;
	    if (get_lookup_slot_value_given_default(block_qm,
		    Qframe_transforms_of_block,Nil))
		goto end_loop;
	    gensymed_symbol_3 = ISVREF(block_qm,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)5L) : Nil;
	    block_qm = gensymed_symbol_3;
	    goto next_loop;
	  end_loop:
	    frame_transform_block_qm = block_qm;
	    goto end_1;
	    frame_transform_block_qm = Qnil;
	  end_1:;
	    if (frame_transform_block_qm) {
		block = SIMPLE_VECTOR_P(frame_transform_block_qm) && 
			EQ(ISVREF(frame_transform_block_qm,(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct) 
			? ISVREF(frame_transform_block_qm,(SI_Long)3L) : 
			frame_transform_block_qm;
		transformed_qm = (SI_Long)0L != (IFIX(ISVREF(block,
			(SI_Long)5L)) & (SI_Long)32768L) &&  
			!TRUEP(frame_description_reference_of_block_qm(block)) 
			? T : Nil;
		if (SIMPLE_VECTOR_P(frame_transform_block_qm) && 
			EQ(ISVREF(frame_transform_block_qm,(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct))
		    this_region = 
			    connection_bounding_region(frame_transform_block_qm);
		else {
		    extreme_left_edge_so_far = Most_positive_fixnum;
		    PUSH_SPECIAL(Extreme_left_edge_so_far,extreme_left_edge_so_far,
			    3);
		      extreme_top_edge_so_far = Most_positive_fixnum;
		      PUSH_SPECIAL(Extreme_top_edge_so_far,extreme_top_edge_so_far,
			      2);
			extreme_right_edge_so_far = Most_negative_fixnum;
			PUSH_SPECIAL(Extreme_right_edge_so_far,extreme_right_edge_so_far,
				1);
			  extreme_bottom_edge_so_far = Most_negative_fixnum;
			  PUSH_SPECIAL(Extreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
				  0);
			    if (SIMPLE_VECTOR_P(frame_transform_block_qm) 
				    && EQ(ISVREF(frame_transform_block_qm,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_connection_g2_struct))
				update_extreme_edges_from_connection(frame_transform_block_qm);
			    else {
				sub_class_bit_vector = 
					ISVREF(ISVREF(frame_transform_block_qm,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Connection_class_description,
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
				if (temp) {
				    if (ISVREF(frame_transform_block_qm,
					    (SI_Long)21L))
					update_extreme_edges_from_connection(ISVREF(frame_transform_block_qm,
						(SI_Long)21L));
				}
				else
				    update_extreme_edges_from_block_bounds(frame_transform_block_qm);
			    }
			    result = VALUES_4(Extreme_left_edge_so_far,
				    Extreme_top_edge_so_far,
				    Extreme_right_edge_so_far,
				    Extreme_bottom_edge_so_far);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    MVS_4(result,left,top,right,bottom);
		    this_region = make_region_from_rectangle(left,top,
			    right,bottom);
		}
		candidates = blocks_potentially_touching_region(workspace,
			this_region);
		answer = Nil;
		sibling = Nil;
		ab_loop_list_ = candidates;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		sibling = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		block = SIMPLE_VECTOR_P(sibling) && EQ(ISVREF(sibling,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct) 
			? ISVREF(sibling,(SI_Long)3L) : sibling;
		if (EQ(transformed_qm,(SI_Long)0L != (IFIX(ISVREF(block,
			(SI_Long)5L)) & (SI_Long)32768L) &&  
			!TRUEP(frame_description_reference_of_block_qm(block)) 
			? T : Nil)) {
		    if (SIMPLE_VECTOR_P(sibling) && EQ(ISVREF(sibling,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_connection_g2_struct))
			region = connection_bounding_region(sibling);
		    else {
			extreme_left_edge_so_far = Most_positive_fixnum;
			PUSH_SPECIAL(Extreme_left_edge_so_far,extreme_left_edge_so_far,
				3);
			  extreme_top_edge_so_far = Most_positive_fixnum;
			  PUSH_SPECIAL(Extreme_top_edge_so_far,extreme_top_edge_so_far,
				  2);
			    extreme_right_edge_so_far = Most_negative_fixnum;
			    PUSH_SPECIAL(Extreme_right_edge_so_far,extreme_right_edge_so_far,
				    1);
			      extreme_bottom_edge_so_far = 
				      Most_negative_fixnum;
			      PUSH_SPECIAL(Extreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
				      0);
				if (SIMPLE_VECTOR_P(sibling) && 
					EQ(ISVREF(sibling,(SI_Long)0L),
					Qg2_defstruct_structure_name_connection_g2_struct))
				    update_extreme_edges_from_connection(sibling);
				else {
				    sub_class_bit_vector = 
					    ISVREF(ISVREF(sibling,
					    (SI_Long)1L),(SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(Connection_class_description,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_1 = (SI_Long)1L;
					gensymed_symbol_2 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_1 = 
						gensymed_symbol_1 << 
						gensymed_symbol_2;
					gensymed_symbol = gensymed_symbol 
						& gensymed_symbol_1;
					temp = (SI_Long)0L < gensymed_symbol;
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp) {
					if (ISVREF(sibling,(SI_Long)21L))
					    update_extreme_edges_from_connection(ISVREF(sibling,
						    (SI_Long)21L));
				    }
				    else
					update_extreme_edges_from_block_bounds(sibling);
				}
				result = VALUES_4(Extreme_left_edge_so_far,
					Extreme_top_edge_so_far,
					Extreme_right_edge_so_far,
					Extreme_bottom_edge_so_far);
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			MVS_4(result,left,top,right,bottom);
			region = make_region_from_rectangle(left,top,right,
				bottom);
		    }
		    if (regions_intersect_p(region,this_region)) {
			answer = gensym_cons_1(sibling,answer);
			if (SIMPLE_VECTOR_P(sibling) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sibling)) > 
				(SI_Long)2L &&  !EQ(ISVREF(sibling,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(sibling,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp = TRUEP(Nil);
			if ((temp ? 
				TRUEP(frame_description_reference_of_block_qm(sibling)) 
				: TRUEP(Nil)) ? TRUEP(T) : TRUEP(Nil)) {
			    temp_1 = 
				    descendents_of_block_or_connection(sibling);
			    answer = nconc2(temp_1,answer);
			}
		    }
		    reclaim_region(region);
		}
		goto next_loop_1;
	      end_loop_1:;
		reclaim_region(this_region);
		reclaim_gensym_list_1(candidates);
		answer = nreverse(answer);
	    }
	    else
		answer = Nil;
	}
	else {
	    block = SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct) ? 
		    ISVREF(thing,(SI_Long)3L) : thing;
	    transformed_qm = (SI_Long)0L != (IFIX(ISVREF(block,
		    (SI_Long)5L)) & (SI_Long)32768L) &&  
		    !TRUEP(frame_description_reference_of_block_qm(block)) 
		    ? T : Nil;
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		this_region = connection_bounding_region(thing);
	    else {
		extreme_left_edge_so_far = Most_positive_fixnum;
		PUSH_SPECIAL(Extreme_left_edge_so_far,extreme_left_edge_so_far,
			3);
		  extreme_top_edge_so_far = Most_positive_fixnum;
		  PUSH_SPECIAL(Extreme_top_edge_so_far,extreme_top_edge_so_far,
			  2);
		    extreme_right_edge_so_far = Most_negative_fixnum;
		    PUSH_SPECIAL(Extreme_right_edge_so_far,extreme_right_edge_so_far,
			    1);
		      extreme_bottom_edge_so_far = Most_negative_fixnum;
		      PUSH_SPECIAL(Extreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
			      0);
			if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_connection_g2_struct))
			    update_extreme_edges_from_connection(thing);
			else {
			    sub_class_bit_vector = ISVREF(ISVREF(thing,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Connection_class_description,
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
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				if (ISVREF(thing,(SI_Long)21L))
				    update_extreme_edges_from_connection(ISVREF(thing,
					    (SI_Long)21L));
			    }
			    else
				update_extreme_edges_from_block_bounds(thing);
			}
			result = VALUES_4(Extreme_left_edge_so_far,
				Extreme_top_edge_so_far,
				Extreme_right_edge_so_far,
				Extreme_bottom_edge_so_far);
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		MVS_4(result,left,top,right,bottom);
		this_region = make_region_from_rectangle(left,top,right,
			bottom);
	    }
	    candidates = blocks_potentially_touching_region(workspace,
		    this_region);
	    answer = Nil;
	    sibling = Nil;
	    ab_loop_list_ = candidates;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    sibling = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    block = SIMPLE_VECTOR_P(sibling) && EQ(ISVREF(sibling,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct) ? 
		    ISVREF(sibling,(SI_Long)3L) : sibling;
	    if (EQ(transformed_qm,(SI_Long)0L != (IFIX(ISVREF(block,
		    (SI_Long)5L)) & (SI_Long)32768L) &&  
		    !TRUEP(frame_description_reference_of_block_qm(block)) 
		    ? T : Nil)) {
		if (SIMPLE_VECTOR_P(sibling) && EQ(ISVREF(sibling,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct))
		    region = connection_bounding_region(sibling);
		else {
		    extreme_left_edge_so_far = Most_positive_fixnum;
		    PUSH_SPECIAL(Extreme_left_edge_so_far,extreme_left_edge_so_far,
			    3);
		      extreme_top_edge_so_far = Most_positive_fixnum;
		      PUSH_SPECIAL(Extreme_top_edge_so_far,extreme_top_edge_so_far,
			      2);
			extreme_right_edge_so_far = Most_negative_fixnum;
			PUSH_SPECIAL(Extreme_right_edge_so_far,extreme_right_edge_so_far,
				1);
			  extreme_bottom_edge_so_far = Most_negative_fixnum;
			  PUSH_SPECIAL(Extreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
				  0);
			    if (SIMPLE_VECTOR_P(sibling) && 
				    EQ(ISVREF(sibling,(SI_Long)0L),
				    Qg2_defstruct_structure_name_connection_g2_struct))
				update_extreme_edges_from_connection(sibling);
			    else {
				sub_class_bit_vector = 
					ISVREF(ISVREF(sibling,(SI_Long)1L),
					(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Connection_class_description,
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
				if (temp) {
				    if (ISVREF(sibling,(SI_Long)21L))
					update_extreme_edges_from_connection(ISVREF(sibling,
						(SI_Long)21L));
				}
				else
				    update_extreme_edges_from_block_bounds(sibling);
			    }
			    result = VALUES_4(Extreme_left_edge_so_far,
				    Extreme_top_edge_so_far,
				    Extreme_right_edge_so_far,
				    Extreme_bottom_edge_so_far);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    MVS_4(result,left,top,right,bottom);
		    region = make_region_from_rectangle(left,top,right,bottom);
		}
		if (regions_intersect_p(region,this_region)) {
		    answer = gensym_cons_1(sibling,answer);
		    if (SIMPLE_VECTOR_P(sibling) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sibling)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(sibling,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(sibling,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if ((temp ? 
			    TRUEP(frame_description_reference_of_block_qm(sibling)) 
			    : TRUEP(Nil)) ? TRUEP(T) : TRUEP(Nil)) {
			temp_1 = descendents_of_block_or_connection(sibling);
			answer = nconc2(temp_1,answer);
		    }
		}
		reclaim_region(region);
	    }
	    goto next_loop_2;
	  end_loop_2:;
	    reclaim_region(this_region);
	    reclaim_gensym_list_1(candidates);
	    answer = nreverse(answer);
	}
	set_block_or_connection_overlap_cache_valid_p(thing,T);
	set_block_or_connection_overlap_cache_p(thing, ! !TRUEP(answer) ? 
		T : Nil);
	set_block_or_connection_overlap_cache(thing,answer);
	list_1 = answer;
    }
    if (EQ(aboveness,Qabove) || EQ(aboveness,Qt)) {
	gensymed_symbol_3 = list_1;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol_3))
	    goto end_loop_3;
	if (EQ(M_CAR(gensymed_symbol_3),thing)) {
	    temp_1 = gensymed_symbol_3;
	    goto end_2;
	}
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	goto next_loop_3;
      end_loop_3:
	temp_1 = Qnil;
      end_2:;
	return VALUES_1(CDR(temp_1));
    }
    else if (EQ(aboveness,Qabove_inclusive)) {
	gensymed_symbol_3 = list_1;
      next_loop_4:
	if ( !TRUEP(gensymed_symbol_3))
	    goto end_loop_4;
	if (EQ(M_CAR(gensymed_symbol_3),thing))
	    return VALUES_1(gensymed_symbol_3);
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	goto next_loop_4;
      end_loop_4:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(list_1);
}

static Object Qgraph_grid;         /* graph-grid */

static Object Qgraph_axis_label;   /* graph-axis-label */

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

/* DRAW-OVERLAPPING-BLOCKS */
Object draw_overlapping_blocks(workspace,block_or_connection,aboveness,
	    include_xor_overlay_qm)
    Object workspace, block_or_connection, aboveness, include_xor_overlay_qm;
{
    Object x2, sub_class_bit_vector, this_thing, siblings, gensymed_symbol_3;
    Object subblock_of_a_graph_qm, erase_instead_qm, above_qm, thing;
    Object ab_loop_list_, connection_qm, in_overlay_qm, condition_1;
    Object condition_2, block, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(101,42);
    if ( !((SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)5L)) & 
	    (SI_Long)65536L)))
	validate_overlapping_cache_for_workspace(workspace);
    if (block_or_connection_might_overlap_p(block_or_connection)) {
	if (SIMPLE_VECTOR_P(block_or_connection) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_connection)) > 
		(SI_Long)2L &&  !EQ(ISVREF(block_or_connection,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block_or_connection,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(block_or_connection,
		    (SI_Long)1L),(SI_Long)19L);
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
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	this_thing = temp ? ISVREF(block_or_connection,(SI_Long)21L) : 
		block_or_connection;
	siblings = 
		copy_list_using_gensym_conses_1(overlapping_siblings(workspace,
		this_thing,Nil));
	if (siblings) {
	    if (SIMPLE_VECTOR_P(block_or_connection) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_connection)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(block_or_connection,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(block_or_connection,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol_3 = ISVREF(ISVREF(block_or_connection,
			(SI_Long)1L),(SI_Long)1L);
		subblock_of_a_graph_qm = EQ(gensymed_symbol_3,Qgraph_grid) 
			? T : Nil;
		if (subblock_of_a_graph_qm);
		else
		    subblock_of_a_graph_qm = EQ(gensymed_symbol_3,
			    Qgraph_axis_label) ? T : Nil;
	    }
	    else
		subblock_of_a_graph_qm = Nil;
	    erase_instead_qm = Nil;
	    PUSH_SPECIAL(Erase_instead_qm,erase_instead_qm,0);
	      above_qm = Nil;
	      thing = Nil;
	      ab_loop_list_ = siblings;
	      connection_qm = Nil;
	      in_overlay_qm = Nil;
	      condition_1 = Nil;
	      condition_2 = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      thing = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      connection_qm = SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct) ? 
		      T : Nil) : Qnil;
	      if (connection_qm) {
		  block = ISVREF(thing,(SI_Long)3L);
		  temp_1 = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) 
			  & (SI_Long)1024L) ? T : Nil;
		  if (temp_1);
		  else {
		      block = ISVREF(thing,(SI_Long)2L);
		      temp_1 = (SI_Long)0L != (IFIX(ISVREF(block,
			      (SI_Long)5L)) & (SI_Long)1024L) ? T : Nil;
		  }
		  in_overlay_qm = temp_1;
	      }
	      else
		  in_overlay_qm = (SI_Long)0L != (IFIX(ISVREF(thing,
			  (SI_Long)5L)) & (SI_Long)1024L) ? T : Nil;
	      if (EQ(aboveness,Qt) || EQ(aboveness,Qabove)) {
		  if (include_xor_overlay_qm) {
		      temp_1 = above_qm;
		      if (temp_1);
		      else
			  temp_1 = in_overlay_qm;
		      condition_1 = temp_1;
		  }
		  else
		      condition_1 = above_qm ? ( !TRUEP(in_overlay_qm) ? T 
			      : Nil) : Qnil;
	      }
	      else if (EQ(aboveness,Qabove_inclusive)) {
		  if (include_xor_overlay_qm) {
		      temp_1 = above_qm;
		      if (temp_1);
		      else
			  temp_1 = EQ(thing,this_thing) ? T : Nil;
		      if (temp_1);
		      else
			  temp_1 = in_overlay_qm;
		      condition_1 = temp_1;
		  }
		  else
		      condition_1 = above_qm || EQ(thing,this_thing) ? ( 
			      !TRUEP(in_overlay_qm) ? T : Nil) : Qnil;
	      }
	      else
		  condition_1 = T;
	      if ( !(subblock_of_a_graph_qm && EQ(ISVREF(ISVREF(thing,
		      (SI_Long)1L),(SI_Long)1L),Qgraph))) {
		  temp_1 = EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) ? T : Nil;
		  if (temp_1);
		  else
		      temp_1 =  !TRUEP(connection_qm) ? ((SI_Long)0L != 
			      (IFIX(ISVREF(thing,(SI_Long)4L)) & 
			      (SI_Long)1024L) ? T : Nil) : Qnil;
		  condition_2 = temp_1;
	      }
	      else
		  condition_2 = Nil;
	      if (condition_1 && condition_2)
		  draw_block_or_connection(thing);
	      if (EQ(thing,this_thing))
		  above_qm = T;
	      goto next_loop;
	    end_loop:;
	      reclaim_gensym_list_1(siblings);
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

/* DRAW-CURRENT-CONNECTION-OVERLAPPING-THINGS */
Object draw_current_connection_overlapping_things(left,top,right,bottom,
	    things_to_draw)
    Object left, top, right, bottom, things_to_draw;
{
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, thing;
    Object ab_loop_list_;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    Declare_special(4);

    x_note_fn_call(101,43);
    left_edge_of_draw_area = Left_edge_of_draw_area;
    top_edge_of_draw_area = Top_edge_of_draw_area;
    right_edge_of_draw_area = Right_edge_of_draw_area;
    bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
    PUSH_SPECIAL(Bottom_edge_of_draw_area,bottom_edge_of_draw_area,3);
      PUSH_SPECIAL(Right_edge_of_draw_area,right_edge_of_draw_area,2);
	PUSH_SPECIAL(Top_edge_of_draw_area,top_edge_of_draw_area,1);
	  PUSH_SPECIAL(Left_edge_of_draw_area,left_edge_of_draw_area,0);
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(left);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,left) 
		    && FIXNUM_LT(left,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			left)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_x_scale,left));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Left_edge_of_draw_area);
	    Left_edge_of_draw_area = FIX(MAX(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(top);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,top) 
		    && FIXNUM_LT(top,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			top)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_y_scale,top));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Top_edge_of_draw_area);
	    Top_edge_of_draw_area = FIX(MAX(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(right);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    right) && FIXNUM_LT(right,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			right)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_x_scale,right));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Right_edge_of_draw_area);
	    Right_edge_of_draw_area = FIX(MIN(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(bottom);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    bottom) && FIXNUM_LT(bottom,
			Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			bottom)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_y_scale,bottom));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_draw_area);
	    Bottom_edge_of_draw_area = FIX(MIN(gensymed_symbol,
		    gensymed_symbol_1));
	    if (FIXNUM_LT(Left_edge_of_draw_area,Right_edge_of_draw_area) 
		    && FIXNUM_LT(Top_edge_of_draw_area,
		    Bottom_edge_of_draw_area)) {
		add_cursors_to_current_window(Left_edge_of_draw_area,
			Top_edge_of_draw_area,Right_edge_of_draw_area,
			Bottom_edge_of_draw_area,T,T,T);
		thing = Nil;
		ab_loop_list_ = things_to_draw;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		thing = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		draw_block_or_connection(thing);
		goto next_loop;
	      end_loop:;
		add_cursors_to_current_window(Left_edge_of_draw_area,
			Top_edge_of_draw_area,Right_edge_of_draw_area,
			Bottom_edge_of_draw_area,T,T,T);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(things_to_draw);
}

static Object Qdraw_current_connection_overlapping_things;  /* draw-current-connection-overlapping-things */

/* DRAW-BLOCKS-OVERLAPPING-CONNECTION */
Object draw_blocks_overlapping_connection(workspace,connection)
    Object workspace, connection;
{
    Object this_thing, erase_instead_qm, siblings, siblings_to_draw, above_p;
    Object thing, ab_loop_list_, connection_p, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, block, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(101,44);
    if (workspace) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)5L)) & 
		(SI_Long)65536L)))
	    validate_overlapping_cache_for_workspace(workspace);
	temp = TRUEP(block_or_connection_might_overlap_p(connection));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	this_thing = ISVREF(connection,(SI_Long)21L);
	erase_instead_qm = Nil;
	PUSH_SPECIAL(Erase_instead_qm,erase_instead_qm,0);
	  siblings = 
		  copy_list_using_gensym_conses_1(overlapping_siblings(workspace,
		  this_thing,Nil));
	  siblings_to_draw = Qnil;
	  if (siblings) {
	      above_p = Nil;
	      thing = Nil;
	      ab_loop_list_ = siblings;
	      connection_p = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      thing = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      connection_p = SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct) ? 
		      T : Nil) : Qnil;
	      if (above_p) {
		  if (connection_p) {
		      block = ISVREF(thing,(SI_Long)3L);
		      temp = (SI_Long)0L != (IFIX(ISVREF(block,
			      (SI_Long)5L)) & (SI_Long)1024L);
		      if (temp);
		      else {
			  block = ISVREF(thing,(SI_Long)2L);
			  temp = (SI_Long)0L != (IFIX(ISVREF(block,
				  (SI_Long)5L)) & (SI_Long)1024L);
		      }
		  }
		  else
		      temp = (SI_Long)0L != (IFIX(ISVREF(thing,
			      (SI_Long)5L)) & (SI_Long)1024L);
		  temp =  !temp;
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ? EQ(Current_drawing_transfer_mode,
		      Kpaint_infered_from_xor) ||  !TRUEP(connection_p) && 
		      (SI_Long)0L != (IFIX(ISVREF(thing,(SI_Long)4L)) & 
		      (SI_Long)1024L) : TRUEP(Nil)) {
		  ab_loopvar__2 = gensym_cons_1(thing,Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
	      }
	      temp_1 = above_p;
	      if (temp_1);
	      else
		  temp_1 = EQ(thing,this_thing) ? T : Nil;
	      above_p = temp_1;
	      goto next_loop;
	    end_loop:
	      siblings_to_draw = ab_loopvar_;
	      goto end_1;
	      siblings_to_draw = Qnil;
	    end_1:;
	      map_over_connection_rectangles(this_thing,
		      SYMBOL_FUNCTION(Qdraw_current_connection_overlapping_things),
		      siblings_to_draw);
	      reclaim_gensym_list_1(siblings_to_draw);
	  }
	  reclaim_gensym_list_1(siblings);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Kxor;                /* :xor */

/* DRAW-OVERLAPPING-XOR-BLOCKS */
Object draw_overlapping_xor_blocks(workspace,block)
    Object workspace, block;
{
    Object siblings_above, erase_instead_qm, thing, ab_loop_list_, x2;
    char temp;
    Declare_special(1);

    x_note_fn_call(101,45);
    if (EQ(Current_drawing_transfer_mode,Kxor)) {
	siblings_above = overlapping_siblings(workspace,block,Qabove);
	if (siblings_above) {
	    erase_instead_qm = Nil;
	    PUSH_SPECIAL(Erase_instead_qm,erase_instead_qm,0);
	      thing = Nil;
	      ab_loop_list_ = siblings_above;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      thing = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (SIMPLE_VECTOR_P(thing) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(thing,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(thing,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  temp = (SI_Long)0L != (IFIX(ISVREF(thing,(SI_Long)4L)) & 
			  (SI_Long)1024L);
		  if (temp);
		  else
		      temp = (SI_Long)0L != (IFIX(ISVREF(thing,
			      (SI_Long)5L)) & (SI_Long)1024L);
	      }
	      else {
		  block = ISVREF(thing,(SI_Long)3L);
		  temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			  (SI_Long)1024L);
		  if (temp);
		  else {
		      block = ISVREF(thing,(SI_Long)2L);
		      temp = (SI_Long)0L != (IFIX(ISVREF(block,
			      (SI_Long)5L)) & (SI_Long)1024L);
		  }
	      }
	      if ( !temp)
		  draw_block_or_connection(thing);
	      goto next_loop;
	    end_loop:;
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

static Object Qlayer_position_of_block;  /* layer-position-of-block */

/* BLOCK-OR-CONNECTION-LESS-P */
Object block_or_connection_less_p(thing_1,thing_2)
    Object thing_1, thing_2;
{
    Object temp;

    x_note_fn_call(101,46);
    temp = SIMPLE_VECTOR_P(thing_1) && EQ(ISVREF(thing_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct) ? 
	    ISVREF(thing_1,(SI_Long)11L) : 
	    get_lookup_slot_value_given_default(thing_1,
	    Qlayer_position_of_block,FIX((SI_Long)0L));
    temp = FIXNUM_LT(temp,SIMPLE_VECTOR_P(thing_2) && EQ(ISVREF(thing_2,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct) ? 
	    ISVREF(thing_2,(SI_Long)11L) : 
	    get_lookup_slot_value_given_default(thing_2,
	    Qlayer_position_of_block,FIX((SI_Long)0L))) ? T : Nil;
    return VALUES_1(temp);
}

/* ADD-THING-TO-SPACIAL-INDEX */
Object add_thing_to_spacial_index(geometry,thing,recurse_p)
    Object geometry, thing, recurse_p;
{
    Object sub_class_bit_vector, x2, gensymed_symbol_3, left, top, right;
    Object bottom, stack, subthing, gensym_pop_store, cons_1, next_cons;
    Object cdr_new_value, temp_1, infs, subblocks, queue, next_queue_element;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, list_1, list_2, temp_2;
    Object temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Object result;

    x_note_fn_call(101,47);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return add_connection_to_spacial_index(geometry,thing);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
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
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (ISVREF(thing,(SI_Long)21L))
		return add_connection_to_spacial_index(geometry,
			ISVREF(thing,(SI_Long)21L));
	    else
		return VALUES_1(Nil);
	}
	else {
	    if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol_3 = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)1L);
		temp = EQ(gensymed_symbol_3,Qgraph_grid);
		if (temp);
		else
		    temp = EQ(gensymed_symbol_3,Qgraph_axis_label);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(Nil);
	    else {
		result = local_edges_of_block_or_connection(thing);
		MVS_4(result,left,top,right,bottom);
		geometry_insert(geometry,thing,left,top,right,bottom);
		if (recurse_p) {
		    stack = gensym_cons_1(thing,Nil);
		    subthing = Nil;
		  next_loop:
		    if ( !TRUEP(stack))
			goto end_loop;
		    gensym_pop_store = Nil;
		    cons_1 = stack;
		    if (cons_1) {
			gensym_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qab_gensym);
			cdr_new_value = Available_gensym_conses;
			M_CDR(cons_1) = cdr_new_value;
			Available_gensym_conses = cons_1;
		    }
		    else
			next_cons = Nil;
		    stack = next_cons;
		    temp_1 = gensym_pop_store;
		    subthing = Nil;
		    if (EQ(temp_1,Tree_traversal_marker)) {
			gensym_pop_store = Nil;
			cons_1 = stack;
			if (cons_1) {
			    gensym_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qab_gensym);
			    cdr_new_value = Available_gensym_conses;
			    M_CDR(cons_1) = cdr_new_value;
			    Available_gensym_conses = cons_1;
			}
			else
			    next_cons = Nil;
			stack = next_cons;
			subthing = gensym_pop_store;
		    }
		    else if ( !SYMBOLP(temp_1)) {
			if (SIMPLE_VECTOR_P(temp_1) && EQ(ISVREF(temp_1,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_connection_g2_struct))
			    infs = Nil;
			else {
			    sub_class_bit_vector = ISVREF(ISVREF(temp_1,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Workspace_class_description,
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
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				gensymed_symbol_3 = ISVREF(temp_1,
					(SI_Long)14L);
				gensymed_symbol_3 = gensymed_symbol_3 ? 
					ISVREF(gensymed_symbol_3,
					(SI_Long)4L) : Nil;
				subblocks = gensymed_symbol_3;
				if (subblocks) {
				    queue = subblocks;
				    next_queue_element = Nil;
				    gensymed_symbol_3 = Nil;
				    ab_loopvar_ = Nil;
				    ab_loopvar__1 = Nil;
				    ab_loopvar__2 = Nil;
				    next_queue_element = ISVREF(queue,
					    (SI_Long)0L);
				  next_loop_1:
				    if (EQ(next_queue_element,queue))
					goto end_loop_1;
				    gensymed_symbol_3 = 
					    ISVREF(next_queue_element,
					    (SI_Long)2L);
				    next_queue_element = 
					    ISVREF(next_queue_element,
					    (SI_Long)0L);
				    ab_loopvar__2 = 
					    gensym_cons_1(gensymed_symbol_3,
					    Nil);
				    if (ab_loopvar__1)
					M_CDR(ab_loopvar__1) = ab_loopvar__2;
				    else
					ab_loopvar_ = ab_loopvar__2;
				    ab_loopvar__1 = ab_loopvar__2;
				    goto next_loop_1;
				  end_loop_1:
				    infs = ab_loopvar_;
				    goto end_1;
				    infs = Qnil;
				  end_1:;
				}
				else
				    infs = Nil;
			    }
			    else if (EQ(ISVREF(ISVREF(temp_1,(SI_Long)1L),
				    (SI_Long)1L),Qgraph))
				infs = Nil;
			    else {
				gensymed_symbol_3 = ISVREF(temp_1,
					(SI_Long)14L);
				gensymed_symbol_3 = gensymed_symbol_3 ? 
					ISVREF(gensymed_symbol_3,
					(SI_Long)4L) : Nil;
				subblocks = gensymed_symbol_3;
				if (subblocks) {
				    queue = subblocks;
				    next_queue_element = Nil;
				    gensymed_symbol_3 = Nil;
				    ab_loopvar_ = Nil;
				    ab_loopvar__1 = Nil;
				    ab_loopvar__2 = Nil;
				    next_queue_element = ISVREF(queue,
					    (SI_Long)0L);
				  next_loop_2:
				    if (EQ(next_queue_element,queue))
					goto end_loop_2;
				    gensymed_symbol_3 = 
					    ISVREF(next_queue_element,
					    (SI_Long)2L);
				    next_queue_element = 
					    ISVREF(next_queue_element,
					    (SI_Long)0L);
				    ab_loopvar__2 = 
					    gensym_cons_1(gensymed_symbol_3,
					    Nil);
				    if (ab_loopvar__1)
					M_CDR(ab_loopvar__1) = ab_loopvar__2;
				    else
					ab_loopvar_ = ab_loopvar__2;
				    ab_loopvar__1 = ab_loopvar__2;
				    goto next_loop_2;
				  end_loop_2:
				    list_1 = ab_loopvar_;
				    goto end_2;
				    list_1 = Qnil;
				  end_2:;
				}
				else
				    list_1 = Nil;
				list_2 = output_connections_of_block(temp_1);
				if ( !TRUEP(list_1))
				    temp_2 = list_2;
				else if ( !TRUEP(list_2))
				    temp_2 = list_1;
				else
				    temp_2 = nconc2(list_1,list_2);
				infs = nreverse(temp_2);
			    }
			}
			if ( !TRUEP(infs))
			    subthing = temp_1;
			else {
			    temp_3 = T ? infs : 
				    copy_list_using_gensym_conses_1(infs);
			    temp_2 = gensym_cons_1(Tree_traversal_marker,Nil);
			    stack = nconc2(temp_3,nconc2(temp_2,
				    nconc2(gensym_cons_1(temp_1,Nil),stack)));
			}
		    }
		    if (subthing) {
			if ( !EQ(subthing,thing))
			    add_thing_to_spacial_index(geometry,subthing,
				    recurse_p);
		    }
		    goto next_loop;
		  end_loop:
		    temp_1 = Qnil;
		    if (stack)
			reclaim_gensym_list_1(stack);
		    return VALUES_1(temp_1);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
    }
}

static Object Qworkspace_connections_which_need_indexing;  /* workspace-connections-which-need-indexing */

/* REMOVE-THING-FROM-SPACIAL-INDEX */
Object remove_thing_from_spacial_index(workspace,geometry,thing)
    Object workspace, geometry, thing;
{
    Object sub_class_bit_vector, connection, x2, gensymed_symbol_3, left, top;
    Object right, bottom, stack, subthing, gensym_pop_store, cons_1, next_cons;
    Object cdr_new_value, temp_1, infs, subblocks, queue, next_queue_element;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, list_1, list_2, temp_2;
    Object temp_3;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Object result;

    x_note_fn_call(101,48);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct)) {
	geometry_flush(geometry,thing);
	svref_new_value = IFIX(ISVREF(thing,(SI_Long)7L)) &  ~(SI_Long)128L;
	ISVREF(thing,(SI_Long)7L) = FIX(svref_new_value);
	return set_non_savable_lookup_slot_value(workspace,
		Qworkspace_connections_which_need_indexing,
		delete_gensym_element_1(thing,
		get_lookup_slot_value_given_default(workspace,
		Qworkspace_connections_which_need_indexing,Nil)));
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
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
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    geometry_flush(geometry,thing);
	    if (ISVREF(thing,(SI_Long)21L)) {
		geometry_flush(geometry,ISVREF(thing,(SI_Long)21L));
		connection = ISVREF(thing,(SI_Long)21L);
		svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) &  
			~(SI_Long)128L;
		ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
		return set_non_savable_lookup_slot_value(workspace,
			Qworkspace_connections_which_need_indexing,
			delete_gensym_element_1(connection,
			get_lookup_slot_value_given_default(workspace,
			Qworkspace_connections_which_need_indexing,Nil)));
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol_3 = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)1L);
		temp = EQ(gensymed_symbol_3,Qgraph_grid);
		if (temp);
		else
		    temp = EQ(gensymed_symbol_3,Qgraph_axis_label);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(Nil);
	    else {
		result = local_edges_of_block_or_connection(thing);
		MVS_4(result,left,top,right,bottom);
		geometry_delete(geometry,thing,left,top,right,bottom);
		stack = gensym_cons_1(thing,Nil);
		subthing = Nil;
	      next_loop:
		if ( !TRUEP(stack))
		    goto end_loop;
		gensym_pop_store = Nil;
		cons_1 = stack;
		if (cons_1) {
		    gensym_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qab_gensym);
		    cdr_new_value = Available_gensym_conses;
		    M_CDR(cons_1) = cdr_new_value;
		    Available_gensym_conses = cons_1;
		}
		else
		    next_cons = Nil;
		stack = next_cons;
		temp_1 = gensym_pop_store;
		subthing = Nil;
		if (EQ(temp_1,Tree_traversal_marker)) {
		    gensym_pop_store = Nil;
		    cons_1 = stack;
		    if (cons_1) {
			gensym_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qab_gensym);
			cdr_new_value = Available_gensym_conses;
			M_CDR(cons_1) = cdr_new_value;
			Available_gensym_conses = cons_1;
		    }
		    else
			next_cons = Nil;
		    stack = next_cons;
		    subthing = gensym_pop_store;
		}
		else if ( !SYMBOLP(temp_1)) {
		    if (SIMPLE_VECTOR_P(temp_1) && EQ(ISVREF(temp_1,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_connection_g2_struct))
			infs = Nil;
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(temp_1,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Workspace_class_description,
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
			    gensymed_symbol_3 = ISVREF(temp_1,(SI_Long)14L);
			    gensymed_symbol_3 = gensymed_symbol_3 ? 
				    ISVREF(gensymed_symbol_3,(SI_Long)4L) :
				     Nil;
			    subblocks = gensymed_symbol_3;
			    if (subblocks) {
				queue = subblocks;
				next_queue_element = Nil;
				gensymed_symbol_3 = Nil;
				ab_loopvar_ = Nil;
				ab_loopvar__1 = Nil;
				ab_loopvar__2 = Nil;
				next_queue_element = ISVREF(queue,(SI_Long)0L);
			      next_loop_1:
				if (EQ(next_queue_element,queue))
				    goto end_loop_1;
				gensymed_symbol_3 = 
					ISVREF(next_queue_element,(SI_Long)2L);
				next_queue_element = 
					ISVREF(next_queue_element,(SI_Long)0L);
				ab_loopvar__2 = 
					gensym_cons_1(gensymed_symbol_3,Nil);
				if (ab_loopvar__1)
				    M_CDR(ab_loopvar__1) = ab_loopvar__2;
				else
				    ab_loopvar_ = ab_loopvar__2;
				ab_loopvar__1 = ab_loopvar__2;
				goto next_loop_1;
			      end_loop_1:
				infs = ab_loopvar_;
				goto end_1;
				infs = Qnil;
			      end_1:;
			    }
			    else
				infs = Nil;
			}
			else if (EQ(ISVREF(ISVREF(temp_1,(SI_Long)1L),
				(SI_Long)1L),Qgraph))
			    infs = Nil;
			else {
			    gensymed_symbol_3 = ISVREF(temp_1,(SI_Long)14L);
			    gensymed_symbol_3 = gensymed_symbol_3 ? 
				    ISVREF(gensymed_symbol_3,(SI_Long)4L) :
				     Nil;
			    subblocks = gensymed_symbol_3;
			    if (subblocks) {
				queue = subblocks;
				next_queue_element = Nil;
				gensymed_symbol_3 = Nil;
				ab_loopvar_ = Nil;
				ab_loopvar__1 = Nil;
				ab_loopvar__2 = Nil;
				next_queue_element = ISVREF(queue,(SI_Long)0L);
			      next_loop_2:
				if (EQ(next_queue_element,queue))
				    goto end_loop_2;
				gensymed_symbol_3 = 
					ISVREF(next_queue_element,(SI_Long)2L);
				next_queue_element = 
					ISVREF(next_queue_element,(SI_Long)0L);
				ab_loopvar__2 = 
					gensym_cons_1(gensymed_symbol_3,Nil);
				if (ab_loopvar__1)
				    M_CDR(ab_loopvar__1) = ab_loopvar__2;
				else
				    ab_loopvar_ = ab_loopvar__2;
				ab_loopvar__1 = ab_loopvar__2;
				goto next_loop_2;
			      end_loop_2:
				list_1 = ab_loopvar_;
				goto end_2;
				list_1 = Qnil;
			      end_2:;
			    }
			    else
				list_1 = Nil;
			    list_2 = output_connections_of_block(temp_1);
			    if ( !TRUEP(list_1))
				temp_2 = list_2;
			    else if ( !TRUEP(list_2))
				temp_2 = list_1;
			    else
				temp_2 = nconc2(list_1,list_2);
			    infs = nreverse(temp_2);
			}
		    }
		    if ( !TRUEP(infs))
			subthing = temp_1;
		    else {
			temp_3 = T ? infs : 
				copy_list_using_gensym_conses_1(infs);
			temp_2 = gensym_cons_1(Tree_traversal_marker,Nil);
			stack = nconc2(temp_3,nconc2(temp_2,
				nconc2(gensym_cons_1(temp_1,Nil),stack)));
		    }
		}
		if (subthing) {
		    if ( !EQ(subthing,thing))
			remove_thing_from_spacial_index(workspace,geometry,
				subthing);
		}
		goto next_loop;
	      end_loop:
		temp_1 = Qnil;
		if (stack)
		    reclaim_gensym_list_1(stack);
		return VALUES_1(temp_1);
	    }
	}
    }
}

/* ADD-CONNECTION-TO-SPACIAL-INDEX */
Object add_connection_to_spacial_index(geometry,connection)
    Object geometry, connection;
{
    Object region, region_strip, top, bottom, region_strip_1;
    Object remaining_region_strips, ab_loop_list_, region_strip_2, a, b, left;
    Object right, ab_loop_list__1, ab_loop_desetq_;

    x_note_fn_call(101,49);
    region = connection_bounding_region(connection);
    region_strip = Nil;
    top = Nil;
    bottom = Nil;
    region_strip_1 = Nil;
    remaining_region_strips = Nil;
    ab_loop_list_ = M_CAR(region);
    region_strip_2 = Nil;
    a = Nil;
    b = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    region_strip_1 = CAR(ab_loop_list_);
    remaining_region_strips = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(remaining_region_strips))
	goto end_loop;
    region_strip_2 = FIRST(remaining_region_strips);
    a = CAR(region_strip_1);
    b = CAR(region_strip_2);
    if ( !FIXNUM_EQ(a,b)) {
	top = a;
	bottom = b;
	region_strip = region_strip_1;
	left = Nil;
	right = Nil;
	ab_loop_list__1 = CDR(region_strip);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !FIXNUM_EQ(left,right))
	    geometry_insert(geometry,connection,left,top,right,bottom);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    reclaim_region(region);
    return VALUES_1(connection);
}

/* RECOMPUTE-LAYER-POSITIONS */
Object recompute_layer_positions(workspace)
    Object workspace;
{
    Object i, stack, thing, gensym_pop_store, cons_1, next_cons, cdr_new_value;
    Object temp, sub_class_bit_vector, gensymed_symbol_3, subblocks, queue;
    Object next_queue_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object list_1, list_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(101,50);
    i = FIX((SI_Long)0L);
    stack = gensym_cons_1(workspace,Nil);
    thing = Nil;
  next_loop:
    if ( !TRUEP(stack))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = stack;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	Available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    stack = next_cons;
    thing = gensym_pop_store;
    if ( !SYMBOLP(thing)) {
	if ( !EQ(thing,workspace)) {
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct)) {
		SVREF(thing,FIX((SI_Long)11L)) = i;
		if (connection_frame_of_connection_qm(thing)) {
		    temp = connection_frame_of_connection_qm(thing);
		    set_non_savable_lookup_slot_value(temp,
			    Qlayer_position_of_block,i);
		}
	    }
	    else
		set_non_savable_lookup_slot_value(thing,
			Qlayer_position_of_block,i);
	    i = FIXNUM_ADD1(i);
	}
	if (T) {
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		temp = Nil;
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    gensymed_symbol_3 = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_1:
			if (EQ(next_queue_element,queue))
			    goto end_loop_1;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_1;
		      end_loop_1:
			temp = ab_loopvar_;
			goto end_1;
			temp = Qnil;
		      end_1:;
		    }
		    else
			temp = Nil;
		    temp = nreverse(temp);
		}
		else if (EQ(ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)1L),
			Qgraph))
		    temp = Nil;
		else {
		    gensymed_symbol_3 = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_2:
			if (EQ(next_queue_element,queue))
			    goto end_loop_2;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_2;
		      end_loop_2:
			list_1 = ab_loopvar_;
			goto end_2;
			list_1 = Qnil;
		      end_2:;
		    }
		    else
			list_1 = Nil;
		    list_2 = output_connections_of_block(thing);
		    if ( !TRUEP(list_1))
			temp = list_2;
		    else if ( !TRUEP(list_2))
			temp = list_1;
		    else
			temp = nconc2(list_1,list_2);
		}
	    }
	}
	else {
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		temp = Nil;
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    gensymed_symbol_3 = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_3:
			if (EQ(next_queue_element,queue))
			    goto end_loop_3;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_3;
		      end_loop_3:
			temp = ab_loopvar_;
			goto end_3;
			temp = Qnil;
		      end_3:;
		    }
		    else
			temp = Nil;
		    temp = nreverse(temp);
		}
		else if (EQ(ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)1L),
			Qgraph))
		    temp = Nil;
		else {
		    gensymed_symbol_3 = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_4:
			if (EQ(next_queue_element,queue))
			    goto end_loop_4;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_4;
		      end_loop_4:
			list_1 = ab_loopvar_;
			goto end_4;
			list_1 = Qnil;
		      end_4:;
		    }
		    else
			list_1 = Nil;
		    list_2 = output_connections_of_block(thing);
		    if ( !TRUEP(list_1))
			temp = list_2;
		    else if ( !TRUEP(list_2))
			temp = list_1;
		    else
			temp = nconc2(list_1,list_2);
		}
	    }
	    temp = copy_list_using_gensym_conses_1(temp);
	}
	stack = nconc2(temp,stack);
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
    if (stack)
	reclaim_gensym_list_1(stack);
    return VALUES_1(temp);
}

/* COMPUTE-USER-VISIBLE-LAYER-POSITION-OF-ITEM */
Object compute_user_visible_layer_position_of_item(item)
    Object item;
{
    Object workspace_qm, i, stack, thing, gensym_pop_store, cons_1, next_cons;
    Object cdr_new_value, temp, infs, sub_class_bit_vector, gensymed_symbol_3;
    Object subblocks, queue, next_queue_element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, list_1, list_2, temp_2, temp_3, this_item_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(101,51);
    workspace_qm = get_workspace_if_any(item);
    i = FIX((SI_Long)0L);
    if ( !TRUEP(workspace_qm))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	stack = gensym_cons_1(workspace_qm,Nil);
	thing = Nil;
      next_loop:
	if ( !TRUEP(stack))
	    goto end_loop;
	gensym_pop_store = Nil;
	cons_1 = stack;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    cdr_new_value = Available_gensym_conses;
	    M_CDR(cons_1) = cdr_new_value;
	    Available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	stack = next_cons;
	temp = gensym_pop_store;
	thing = Nil;
	if (EQ(temp,Tree_traversal_marker)) {
	    gensym_pop_store = Nil;
	    cons_1 = stack;
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_gensym);
		cdr_new_value = Available_gensym_conses;
		M_CDR(cons_1) = cdr_new_value;
		Available_gensym_conses = cons_1;
	    }
	    else
		next_cons = Nil;
	    stack = next_cons;
	    thing = gensym_pop_store;
	}
	else if ( !SYMBOLP(temp)) {
	    if (SIMPLE_VECTOR_P(temp) && EQ(ISVREF(temp,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		infs = Nil;
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(temp,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_1:
			if (EQ(next_queue_element,queue))
			    goto end_loop_1;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_1;
		      end_loop_1:
			infs = ab_loopvar_;
			goto end_1;
			infs = Qnil;
		      end_1:;
		    }
		    else
			infs = Nil;
		}
		else if (EQ(ISVREF(ISVREF(temp,(SI_Long)1L),(SI_Long)1L),
			Qgraph))
		    infs = Nil;
		else {
		    gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_2:
			if (EQ(next_queue_element,queue))
			    goto end_loop_2;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_2;
		      end_loop_2:
			list_1 = ab_loopvar_;
			goto end_2;
			list_1 = Qnil;
		      end_2:;
		    }
		    else
			list_1 = Nil;
		    list_2 = output_connections_of_block(temp);
		    if ( !TRUEP(list_1))
			temp_2 = list_2;
		    else if ( !TRUEP(list_2))
			temp_2 = list_1;
		    else
			temp_2 = nconc2(list_1,list_2);
		    infs = nreverse(temp_2);
		}
	    }
	    if ( !TRUEP(infs))
		thing = temp;
	    else {
		temp_3 = T ? infs : copy_list_using_gensym_conses_1(infs);
		temp_2 = gensym_cons_1(Tree_traversal_marker,Nil);
		stack = nconc2(temp_3,nconc2(temp_2,
			nconc2(gensym_cons_1(temp,Nil),stack)));
	    }
	}
	if (thing) {
	    if ( !EQ(thing,workspace_qm)) {
		this_item_qm = SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct) 
			? connection_frame_of_connection_qm(thing) : thing;
		if (EQ(item,this_item_qm))
		    goto end_3;
		i = FIXNUM_ADD1(i);
	    }
	}
	goto next_loop;
      end_loop:
      end_3:
	if (stack)
	    reclaim_gensym_list_1(stack);
	return VALUES_1(i);
    }
}

static Object Qworkspace_spacial_index_qm;  /* workspace-spacial-index? */

/* BUILD-SPACIAL-INDEX */
Object build_spacial_index(workspace)
    Object workspace;
{
    Object temp, gensymed_symbol, temp_1, temp_2, temp_3, geometry, i, stack;
    Object thing, gensym_pop_store, cons_1, next_cons, cdr_new_value;
    Object sub_class_bit_vector, subblocks, queue, next_queue_element;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, list_1, list_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_4;

    x_note_fn_call(101,52);
    temp = Default_size_of_spacial_index;
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_3 = gensymed_symbol;
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    geometry = create_geometry(temp,temp_1,temp_2,temp_3,gensymed_symbol);
    i = FIX((SI_Long)0L);
    stack = gensym_cons_1(workspace,Nil);
    thing = Nil;
  next_loop:
    if ( !TRUEP(stack))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = stack;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	Available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    stack = next_cons;
    thing = gensym_pop_store;
    if ( !SYMBOLP(thing)) {
	if ( !EQ(thing,workspace)) {
	    add_thing_to_spacial_index(geometry,thing,Nil);
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct)) {
		SVREF(thing,FIX((SI_Long)11L)) = i;
		if (connection_frame_of_connection_qm(thing)) {
		    temp_3 = connection_frame_of_connection_qm(thing);
		    set_non_savable_lookup_slot_value(temp_3,
			    Qlayer_position_of_block,i);
		}
	    }
	    else
		set_non_savable_lookup_slot_value(thing,
			Qlayer_position_of_block,i);
	    i = FIXNUM_ADD1(i);
	}
	if (T) {
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		temp_3 = Nil;
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    temp_4 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_4 = TRUEP(Nil);
		if (temp_4) {
		    gensymed_symbol = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_1:
			if (EQ(next_queue_element,queue))
			    goto end_loop_1;
			gensymed_symbol = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_1;
		      end_loop_1:
			temp_3 = ab_loopvar_;
			goto end_1;
			temp_3 = Qnil;
		      end_1:;
		    }
		    else
			temp_3 = Nil;
		    temp_3 = nreverse(temp_3);
		}
		else if (EQ(ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)1L),
			Qgraph))
		    temp_3 = Nil;
		else {
		    gensymed_symbol = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_2:
			if (EQ(next_queue_element,queue))
			    goto end_loop_2;
			gensymed_symbol = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_2;
		      end_loop_2:
			list_1 = ab_loopvar_;
			goto end_2;
			list_1 = Qnil;
		      end_2:;
		    }
		    else
			list_1 = Nil;
		    list_2 = output_connections_of_block(thing);
		    if ( !TRUEP(list_1))
			temp_3 = list_2;
		    else if ( !TRUEP(list_2))
			temp_3 = list_1;
		    else
			temp_3 = nconc2(list_1,list_2);
		}
	    }
	}
	else {
	    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		temp_3 = Nil;
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    temp_4 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_4 = TRUEP(Nil);
		if (temp_4) {
		    gensymed_symbol = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_3:
			if (EQ(next_queue_element,queue))
			    goto end_loop_3;
			gensymed_symbol = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_3;
		      end_loop_3:
			temp_3 = ab_loopvar_;
			goto end_3;
			temp_3 = Qnil;
		      end_3:;
		    }
		    else
			temp_3 = Nil;
		    temp_3 = nreverse(temp_3);
		}
		else if (EQ(ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)1L),
			Qgraph))
		    temp_3 = Nil;
		else {
		    gensymed_symbol = ISVREF(thing,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_4:
			if (EQ(next_queue_element,queue))
			    goto end_loop_4;
			gensymed_symbol = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_4;
		      end_loop_4:
			list_1 = ab_loopvar_;
			goto end_4;
			list_1 = Qnil;
		      end_4:;
		    }
		    else
			list_1 = Nil;
		    list_2 = output_connections_of_block(thing);
		    if ( !TRUEP(list_1))
			temp_3 = list_2;
		    else if ( !TRUEP(list_2))
			temp_3 = list_1;
		    else
			temp_3 = nconc2(list_1,list_2);
		}
	    }
	    temp_3 = copy_list_using_gensym_conses_1(temp_3);
	}
	stack = nconc2(temp_3,stack);
    }
    goto next_loop;
  end_loop:
    if (stack)
	reclaim_gensym_list_1(stack);
    validate_layer_positions(workspace);
    set_non_savable_lookup_slot_value(workspace,
	    Qworkspace_spacial_index_qm,geometry);
    return VALUES_1(geometry);
}

/* DESTROY-SPACIAL-INDEX */
Object destroy_spacial_index(workspace)
    Object workspace;
{
    Object connections, connection, ab_loop_list_;
    SI_Long svref_new_value;

    x_note_fn_call(101,53);
    if (get_lookup_slot_value_given_default(workspace,
	    Qworkspace_spacial_index_qm,Nil)) {
	connections = get_lookup_slot_value_given_default(workspace,
		Qworkspace_connections_which_need_indexing,Nil);
	if (connections) {
	    connection = Nil;
	    ab_loop_list_ = connections;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    connection = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) &  
		    ~(SI_Long)128L;
	    ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
	    goto next_loop;
	  end_loop:;
	    set_non_savable_lookup_slot_value(workspace,
		    Qworkspace_connections_which_need_indexing,Nil);
	    reclaim_gensym_list_1(connections);
	}
	reclaim_geometry(get_lookup_slot_value_given_default(workspace,
		Qworkspace_spacial_index_qm,Nil));
	return set_non_savable_lookup_slot_value(workspace,
		Qworkspace_spacial_index_qm,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-CHANGE-OF-CONNECTION-FOR-DRAWING */
Object note_change_of_connection_for_drawing(connection)
    Object connection;
{
    Object workspace_qm, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object workspace_connections_which_need_indexing_new_value;
    SI_Long gensymed_symbol, svref_new_value;

    x_note_fn_call(101,54);
    if ( !(Loading_kb_p || (SI_Long)0L != (IFIX(ISVREF(connection,
	    (SI_Long)7L)) & (SI_Long)256L))) {
	gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)128L;
	if ( !((SI_Long)0L != gensymed_symbol)) {
	    workspace_qm = workspace_of_connection_qm(connection);
	    if (workspace_qm) {
		note_change_to_workspace_geometry(workspace_qm);
		if (get_lookup_slot_value_given_default(workspace_qm,
			Qworkspace_spacial_index_qm,Nil)) {
		    svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) 
			    | (SI_Long)128L;
		    ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
		    gensym_push_modify_macro_arg = connection;
		    car_1 = gensym_push_modify_macro_arg;
		    cdr_1 = 
			    get_lookup_slot_value_given_default(workspace_qm,
			    Qworkspace_connections_which_need_indexing,Nil);
		    workspace_connections_which_need_indexing_new_value = 
			    gensym_cons_1(car_1,cdr_1);
		    set_non_savable_lookup_slot_value(workspace_qm,
			    Qworkspace_connections_which_need_indexing,
			    workspace_connections_which_need_indexing_new_value);
		    return VALUES_1(connection);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-DELETION-OF-CONNECTION-FOR-DRAWING */
Object note_deletion_of_connection_for_drawing(connection)
    Object connection;
{
    Object workspace_qm;

    x_note_fn_call(101,55);
    workspace_qm = workspace_of_connection_qm(connection);
    if (workspace_qm) {
	note_change_to_workspace_geometry(workspace_qm);
	update_spacial_index(workspace_qm,connection,Qremove);
	remove_thing_from_image_plane_drawing_queues(workspace_qm,connection);
	return note_deletion_of_connection_for_selection(connection);
    }
    else
	return VALUES_1(Nil);
}

/* ENSURE-SPACIAL-INDEX-IS-UP-TO-DATE */
Object ensure_spacial_index_is_up_to_date(workspace)
    Object workspace;
{
    Object geometry_qm, connections, connection, ab_loop_list_;
    SI_Long svref_new_value;

    x_note_fn_call(101,56);
    geometry_qm = get_lookup_slot_value_given_default(workspace,
	    Qworkspace_spacial_index_qm,Nil);
    connections = get_lookup_slot_value_given_default(workspace,
	    Qworkspace_connections_which_need_indexing,Nil);
    if (geometry_qm) {
	ensure_layer_positions(workspace);
	connection = Nil;
	ab_loop_list_ = connections;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connection = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	geometry_flush(geometry_qm,connection);
	add_connection_to_spacial_index(geometry_qm,connection);
	svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) &  
		~(SI_Long)128L;
	ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(connections);
	return set_non_savable_lookup_slot_value(workspace,
		Qworkspace_connections_which_need_indexing,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qblock_or_connection_less_p;  /* block-or-connection-less-p */

/* BLOCKS-POTENTIALLY-TOUCHING-REGION */
Object blocks_potentially_touching_region(workspace,region)
    Object workspace, region;
{
    Object geometry_qm, list_1, stack, sibling, gensym_pop_store, cons_1;
    Object next_cons, cdr_new_value, temp, infs, sub_class_bit_vector;
    Object gensymed_symbol_3, subblocks, queue, next_queue_element;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, list_1_1, list_2, temp_2;
    Object temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(101,57);
    geometry_qm = get_lookup_slot_value_given_default(workspace,
	    Qworkspace_spacial_index_qm,Nil);
    if ( !TRUEP(geometry_qm)) {
	list_1 = Nil;
	stack = gensym_cons_1(workspace,Nil);
	sibling = Nil;
      next_loop:
	if ( !TRUEP(stack))
	    goto end_loop;
	gensym_pop_store = Nil;
	cons_1 = stack;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    cdr_new_value = Available_gensym_conses;
	    M_CDR(cons_1) = cdr_new_value;
	    Available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	stack = next_cons;
	temp = gensym_pop_store;
	sibling = Nil;
	if (EQ(temp,Tree_traversal_marker)) {
	    gensym_pop_store = Nil;
	    cons_1 = stack;
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_gensym);
		cdr_new_value = Available_gensym_conses;
		M_CDR(cons_1) = cdr_new_value;
		Available_gensym_conses = cons_1;
	    }
	    else
		next_cons = Nil;
	    stack = next_cons;
	    sibling = gensym_pop_store;
	}
	else if ( !SYMBOLP(temp)) {
	    if (SIMPLE_VECTOR_P(temp) && EQ(ISVREF(temp,(SI_Long)0L),
		    Qg2_defstruct_structure_name_connection_g2_struct))
		infs = Nil;
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(temp,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_1:
			if (EQ(next_queue_element,queue))
			    goto end_loop_1;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_1;
		      end_loop_1:
			infs = ab_loopvar_;
			goto end_1;
			infs = Qnil;
		      end_1:;
		    }
		    else
			infs = Nil;
		}
		else if (EQ(ISVREF(ISVREF(temp,(SI_Long)1L),(SI_Long)1L),
			Qgraph))
		    infs = Nil;
		else {
		    gensymed_symbol_3 = ISVREF(temp,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
		    subblocks = gensymed_symbol_3;
		    if (subblocks) {
			queue = subblocks;
			next_queue_element = Nil;
			gensymed_symbol_3 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
			next_queue_element = ISVREF(queue,(SI_Long)0L);
		      next_loop_2:
			if (EQ(next_queue_element,queue))
			    goto end_loop_2;
			gensymed_symbol_3 = ISVREF(next_queue_element,
				(SI_Long)2L);
			next_queue_element = ISVREF(next_queue_element,
				(SI_Long)0L);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_2;
		      end_loop_2:
			list_1_1 = ab_loopvar_;
			goto end_2;
			list_1_1 = Qnil;
		      end_2:;
		    }
		    else
			list_1_1 = Nil;
		    list_2 = output_connections_of_block(temp);
		    if ( !TRUEP(list_1_1))
			temp_2 = list_2;
		    else if ( !TRUEP(list_2))
			temp_2 = list_1_1;
		    else
			temp_2 = nconc2(list_1_1,list_2);
		    infs = nreverse(temp_2);
		}
	    }
	    if ( !TRUEP(infs))
		sibling = temp;
	    else {
		temp_3 = T ? infs : copy_list_using_gensym_conses_1(infs);
		temp_2 = gensym_cons_1(Tree_traversal_marker,Nil);
		stack = nconc2(temp_3,nconc2(temp_2,
			nconc2(gensym_cons_1(temp,Nil),stack)));
	    }
	}
	if (sibling) {
	    if ( !EQ(sibling,workspace))
		list_1 = gensym_cons_1(sibling,list_1);
	}
	goto next_loop;
      end_loop:
	if (stack)
	    reclaim_gensym_list_1(stack);
	return VALUES_1(list_1);
    }
    else {
	ensure_spacial_index_is_up_to_date(workspace);
	list_1 = geometry_find_in_region(geometry_qm,region);
	return sort_list(list_1,
		SYMBOL_FUNCTION(Qblock_or_connection_less_p),Nil);
    }
}

/* BLOCKS-TOUCHING-REGION-FOR-DRAWING */
Object blocks_touching_region_for_drawing(workspace,region,sorted_qm)
    Object workspace, region, sorted_qm;
{
    Object geometry_qm, list_1, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, block, temp;

    x_note_fn_call(101,58);
    geometry_qm = get_lookup_slot_value_given_default(workspace,
	    Qworkspace_spacial_index_qm,Nil);
    if ( !TRUEP(geometry_qm) || region_covers_workspace_qm(workspace,region)) {
	list_1 = Nil;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)4L) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	block = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
      next_loop:
	if (EQ(ab_next_queue_element_,ab_queue_form_))
	    goto end_loop;
	block = ISVREF(ab_next_queue_element_,(SI_Long)2L);
	ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
	list_1 = gensym_cons_1(block,list_1);
	goto next_loop;
      end_loop:
	temp = list_1;
	goto end_1;
	temp = Qnil;
      end_1:;
	return VALUES_2(temp,Nil);
    }
    else {
	ensure_spacial_index_is_up_to_date(workspace);
	list_1 = geometry_find_in_region(geometry_qm,region);
	temp = sorted_qm ? sort_list(list_1,
		SYMBOL_FUNCTION(Qblock_or_connection_less_p),Nil) : list_1;
	return VALUES_2(temp,T);
    }
}

/* BLOCKS-TOUCHING-REGION-OF-IMAGE-PLANE */
Object blocks_touching_region_of_image_plane(workspace,region_of_window,
	    sorted_qm)
    Object workspace, region_of_window, sorted_qm;
{
    Object region_of_workspace, blocks, flag;
    Object result;

    x_note_fn_call(101,59);
    region_of_workspace = 
	    transform_region_to_workspace_coordinates(region_of_window);
    result = blocks_touching_region_for_drawing(workspace,
	    region_of_workspace,sorted_qm);
    MVS_2(result,blocks,flag);
    reclaim_region(region_of_workspace);
    return VALUES_2(blocks,flag);
}

/* IMAGE-PLANE-HAS-DRAWING-IN-WINDOW-P */
Object image_plane_has_drawing_in_window_p(image_plane)
    Object image_plane;
{
    Object workspace_qm, current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, draw_area_region;
    Object candidate_blocks_and_connections, block_or_connection;
    Object ab_loop_list_, ab_loop_it_, temp, images_region;
    Object visible_images_region, outer_region, inner_region, border_region;
    Object visible_border_region;
    Declare_special(5);
    Object result;

    x_note_fn_call(101,60);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	current_frame_transform_qm = Nil;
	current_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
	current_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
	current_x_origin_of_drawing = ISVREF(image_plane,(SI_Long)13L);
	current_y_origin_of_drawing = ISVREF(image_plane,(SI_Long)14L);
	PUSH_SPECIAL(Current_y_origin_of_drawing,current_y_origin_of_drawing,
		4);
	  PUSH_SPECIAL(Current_x_origin_of_drawing,current_x_origin_of_drawing,
		  3);
	    PUSH_SPECIAL(Current_image_y_scale,current_image_y_scale,2);
	      PUSH_SPECIAL(Current_image_x_scale,current_image_x_scale,1);
		PUSH_SPECIAL(Current_frame_transform_qm,current_frame_transform_qm,
			0);
		  draw_area_region = 
			  make_region_from_rectangle(ISVREF(image_plane,
			  (SI_Long)6L),ISVREF(image_plane,(SI_Long)7L),
			  ISVREF(image_plane,(SI_Long)8L),
			  ISVREF(image_plane,(SI_Long)9L));
		  candidate_blocks_and_connections = 
			  blocks_touching_region_of_image_plane(workspace_qm,
			  draw_area_region,Nil);
		  block_or_connection = Nil;
		  ab_loop_list_ = candidate_blocks_and_connections;
		  ab_loop_it_ = Nil;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  block_or_connection = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  ab_loop_it_ = 
			  block_or_connection_overlaps_window_rectangle_p(block_or_connection,
			  ISVREF(image_plane,(SI_Long)6L),
			  ISVREF(image_plane,(SI_Long)7L),
			  ISVREF(image_plane,(SI_Long)8L),
			  ISVREF(image_plane,(SI_Long)9L));
		  if (ab_loop_it_) {
		      temp = ab_loop_it_;
		      goto end_1;
		  }
		  goto next_loop;
		end_loop:
		  temp = Qnil;
		end_1:;
		  reclaim_gensym_list_1(candidate_blocks_and_connections);
		  if (temp);
		  else if (image_plane_background_images(image_plane)) {
		      images_region = 
			      region_containing_background_images(image_plane);
		      visible_images_region = 
			      intersect_region(images_region,draw_area_region);
		      temp =  ! !TRUEP(M_CAR(visible_images_region)) ? T : Nil;
		      reclaim_region(images_region);
		      reclaim_region(visible_images_region);
		  }
		  else
		      temp = Nil;
		  if (temp);
		  else if ( !TRUEP(printing_image_plane_p(image_plane)) || 
			   !TRUEP(suppress_printing_border_p(image_plane))) {
		      outer_region = 
			      make_region_from_rectangle(ISVREF(image_plane,
			      (SI_Long)15L),ISVREF(image_plane,
			      (SI_Long)16L),ISVREF(image_plane,
			      (SI_Long)17L),ISVREF(image_plane,(SI_Long)18L));
		      inner_region = 
			      make_region_from_rectangle(ISVREF(image_plane,
			      (SI_Long)19L),ISVREF(image_plane,
			      (SI_Long)20L),ISVREF(image_plane,
			      (SI_Long)21L),ISVREF(image_plane,(SI_Long)22L));
		      border_region = subtract_region(outer_region,
			      inner_region);
		      visible_border_region = 
			      intersect_region(border_region,draw_area_region);
		      temp =  ! !TRUEP(M_CAR(visible_border_region)) ? T : Nil;
		      reclaim_region(inner_region);
		      reclaim_region(outer_region);
		      reclaim_region(border_region);
		      reclaim_region(visible_border_region);
		  }
		  else
		      temp = Nil;
		  reclaim_region(draw_area_region);
		  result = VALUES_1(temp);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* CONNECTION-OVERLAPS-WINDOW-RECTANGLE-P-1 */
Object connection_overlaps_window_rectangle_p_1(left,top,right,bottom,
	    value_so_far)
    Object left, top, right, bottom, value_so_far;
{
    Object temp, scale, value;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result, l2, t2, r2;
    SI_Long b2;

    x_note_fn_call(101,61);
    temp = value_so_far;
    if (temp)
	return VALUES_1(temp);
    else {
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(left);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,left) && 
		FIXNUM_LT(left,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    left)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    left));
	l2 = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(top);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,top) && 
		FIXNUM_LT(top,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    top)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    top));
	t2 = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	value = FIXNUM_ADD1(right);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	r2 = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	value = FIXNUM_ADD1(bottom);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	b2 = gensymed_symbol + gensymed_symbol_1;
	if (b2 >= IFIX(Bottom_edge_of_draw_area) && 
		IFIX(Bottom_edge_of_draw_area) >= t2 || 
		IFIX(Bottom_edge_of_draw_area) >= b2 && b2 >= 
		IFIX(Top_edge_of_draw_area)) {
	    temp = r2 >= IFIX(Right_edge_of_draw_area) ? 
		    (IFIX(Right_edge_of_draw_area) >= l2 ? T : Nil) : Qnil;
	    if (temp)
		return VALUES_1(temp);
	    else if (IFIX(Right_edge_of_draw_area) >= r2)
		return VALUES_1(r2 >= IFIX(Left_edge_of_draw_area) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qconnection_overlaps_window_rectangle_p_1;  /* connection-overlaps-window-rectangle-p-1 */

/* CONNECTION-OVERLAPS-WINDOW-RECTANGLE-P */
Object connection_overlaps_window_rectangle_p(connection,left,top,right,bottom)
    Object connection, left, top, right, bottom;
{
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Declare_special(4);
    Object result;

    x_note_fn_call(101,62);
    left_edge_of_draw_area = left;
    top_edge_of_draw_area = top;
    right_edge_of_draw_area = right;
    bottom_edge_of_draw_area = bottom;
    PUSH_SPECIAL(Bottom_edge_of_draw_area,bottom_edge_of_draw_area,3);
      PUSH_SPECIAL(Right_edge_of_draw_area,right_edge_of_draw_area,2);
	PUSH_SPECIAL(Top_edge_of_draw_area,top_edge_of_draw_area,1);
	  PUSH_SPECIAL(Left_edge_of_draw_area,left_edge_of_draw_area,0);
	    result = map_over_connection_rectangles(connection,
		    SYMBOL_FUNCTION(Qconnection_overlaps_window_rectangle_p_1),
		    Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* BLOCK-OR-CONNECTION-OVERLAPS-WINDOW-RECTANGLE-P */
Object block_or_connection_overlaps_window_rectangle_p(block_or_connection,
	    left,top,right,bottom)
    Object block_or_connection, left, top, right, bottom;
{
    Object x2;
    char temp;

    x_note_fn_call(101,63);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    EQ(ISVREF(block_or_connection,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return connection_overlaps_window_rectangle_p(block_or_connection,
		left,top,right,bottom);
    else {
	if (SIMPLE_VECTOR_P(block_or_connection) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_connection)) > 
		(SI_Long)2L &&  !EQ(ISVREF(block_or_connection,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block_or_connection,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return block_overlaps_window_rectangle_p(block_or_connection,
		    left,top,right,bottom);
	else
	    return VALUES_1(Nil);
    }
}

/* BLOCK-OVERLAPS-WINDOW-RECTANGLE-P */
Object block_overlaps_window_rectangle_p(block,left,top,right,bottom)
    Object block, left, top, right, bottom;
{
    Object scale, gensymed_symbol_1, value, temp, ab_queue_form_;
    Object ab_next_queue_element_, subblock, ab_loop_it_, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object ab_less_than_branch_qm_;
    SI_Long gensymed_symbol, gensymed_symbol_2, unshifted_result, l2, t2;
    SI_Long value_1, r2, b2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(101,64);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    value = gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    l2 = gensymed_symbol + gensymed_symbol_2;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    scale = Current_image_y_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    value = gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    t2 = gensymed_symbol + gensymed_symbol_2;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    value_1 = gensymed_symbol_2 + (SI_Long)1L;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value_1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value_1 && 
	    value_1 < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value_1)));
    r2 = gensymed_symbol + gensymed_symbol_2;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    scale = Current_image_y_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    value_1 = gensymed_symbol_2 + (SI_Long)1L;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value_1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value_1 && 
	    value_1 < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value_1)));
    b2 = gensymed_symbol + gensymed_symbol_2;
    if (b2 >= IFIX(bottom) && IFIX(bottom) >= t2 || IFIX(bottom) >= b2 && 
	    b2 >= IFIX(top)) {
	temp = r2 >= IFIX(right) ? (IFIX(right) >= l2 ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = IFIX(right) >= r2 ? (r2 >= IFIX(left) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    if (temp);
    else {
	gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)4L) : Nil;
	ab_queue_form_ = gensymed_symbol_1;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	ab_loop_it_ = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
      next_loop:
	if (EQ(ab_next_queue_element_,ab_queue_form_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
	ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
	ab_loop_it_ = block_overlaps_window_rectangle_p(subblock,left,top,
		right,bottom);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)6L) : Nil;
	ab_skip_list_form_ = gensymed_symbol_1;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	PUSH_SPECIAL(Scope_conses,scope_conses,0);
	  ab_loop_it_ = Nil;
	  gensymed_symbol_1 = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol_1)) {
	      temp = M_CAR(gensymed_symbol_1);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol_1);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L);
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
		  ab_next_node_ = ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L);
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
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	      goto end_2;
	  goto next_loop_2;
	end_loop_2:
	end_2:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_3;
	  connection = ab_connection_;
	  ab_loop_it_ = connection_overlaps_window_rectangle_p(connection,
		  left,top,right,bottom);
	  if (ab_loop_it_) {
	      result = VALUES_1(ab_loop_it_);
	      goto end_3;
	  }
	  goto next_loop_1;
	end_loop_3:
	  result = VALUES_1(Qnil);
	end_3:;
	POP_SPECIAL();
	return result;
    }
}

void connect3a_INIT()
{
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol;
    Object AB_package, Qworkspace_geometry_tick_mask;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(101,65);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qjunction_block_class = STATIC_SYMBOL("JUNCTION-BLOCK-CLASS",AB_package);
    Qsensor = STATIC_SYMBOL("SENSOR",AB_package);
    string_constant = 
	    STATIC_STRING("Cannot join connections with incompatible cross sections.");
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    string_constant_1 = 
	    STATIC_STRING("Cannot make junction for diagonal connections.");
    string_constant_2 = 
	    STATIC_STRING("Cannot join connections because there is no defined class for ~\n               the junction.");
    string_constant_3 = 
	    STATIC_STRING("Cannot join connections because the class for the junction, ~\n               ~a, is not defined.");
    string_constant_4 = 
	    STATIC_STRING("Cannot join connections because the class for the junction, ~\n               ~a, is not a subclass of ~a.");
    string_constant_5 = STATIC_STRING("Cannot join a connection to itself.");
    Qdefault_junction = STATIC_SYMBOL("DEFAULT-JUNCTION",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qbegin_corner = STATIC_SYMBOL("BEGIN-CORNER",AB_package);
    Qend_corner = STATIC_SYMBOL("END-CORNER",AB_package);
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qjunction_block_connection_1 = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CONNECTION-1",AB_package);
    Qjunction_block_connection_2 = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CONNECTION-2",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qjunction_block_connection_3 = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CONNECTION-3",AB_package);
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    ISASET_1(array_constant,(SI_Long)0L,Qtop);
    ISASET_1(array_constant,(SI_Long)1L,Qleft);
    ISASET_1(array_constant,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant,(SI_Long)3L,Qright);
    float_constant = STATIC_FLOAT(0.0);
    Qadd_rectangle_to_region = STATIC_SYMBOL("ADD-RECTANGLE-TO-REGION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_rectangle_to_region,
	    STATIC_FUNCTION(add_rectangle_to_region,NIL,FALSE,5,5));
    Qupdate_extreme_edges_from_connection_1 = 
	    STATIC_SYMBOL("UPDATE-EXTREME-EDGES-FROM-CONNECTION-1",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_extreme_edges_from_connection_1,
	    STATIC_FUNCTION(update_extreme_edges_from_connection_1,NIL,
	    FALSE,5,5));
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qoverlapping_blocks = STATIC_SYMBOL("OVERLAPPING-BLOCKS",AB_package);
    Qoverlapping_blocks_cache = STATIC_SYMBOL("OVERLAPPING-BLOCKS-CACHE",
	    AB_package);
    Qworkspace_geometry_tick_mask = 
	    STATIC_SYMBOL("WORKSPACE-GEOMETRY-TICK-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_geometry_tick_mask,
	    Workspace_geometry_tick_mask);
    gensymed_symbol = (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_SUB1(Positive_bits_per_fixnum);
    gensymed_symbol = IFIX(ash(FIX(gensymed_symbol),gensymed_symbol_1));
    SET_SYMBOL_VALUE(Qworkspace_geometry_tick_mask,FIX(gensymed_symbol - 
	    (SI_Long)1L));
    Qframe_transforms_of_block = STATIC_SYMBOL("FRAME-TRANSFORMS-OF-BLOCK",
	    AB_package);
    Qabove = STATIC_SYMBOL("ABOVE",AB_package);
    Qabove_inclusive = STATIC_SYMBOL("ABOVE-INCLUSIVE",AB_package);
    Qgraph_grid = STATIC_SYMBOL("GRAPH-GRID",AB_package);
    Qgraph_axis_label = STATIC_SYMBOL("GRAPH-AXIS-LABEL",AB_package);
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    Qdraw_current_connection_overlapping_things = 
	    STATIC_SYMBOL("DRAW-CURRENT-CONNECTION-OVERLAPPING-THINGS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_current_connection_overlapping_things,
	    STATIC_FUNCTION(draw_current_connection_overlapping_things,NIL,
	    FALSE,5,5));
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qlayer_position_of_block = STATIC_SYMBOL("LAYER-POSITION-OF-BLOCK",
	    AB_package);
    Qworkspace_connections_which_need_indexing = 
	    STATIC_SYMBOL("WORKSPACE-CONNECTIONS-WHICH-NEED-INDEXING",
	    AB_package);
    Qworkspace_spacial_index_qm = 
	    STATIC_SYMBOL("WORKSPACE-SPACIAL-INDEX\?",AB_package);
    Qblock_or_connection_less_p = 
	    STATIC_SYMBOL("BLOCK-OR-CONNECTION-LESS-P",AB_package);
    SET_SYMBOL_FUNCTION(Qblock_or_connection_less_p,
	    STATIC_FUNCTION(block_or_connection_less_p,NIL,FALSE,2,2));
    Qconnection_overlaps_window_rectangle_p_1 = 
	    STATIC_SYMBOL("CONNECTION-OVERLAPS-WINDOW-RECTANGLE-P-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconnection_overlaps_window_rectangle_p_1,
	    STATIC_FUNCTION(connection_overlaps_window_rectangle_p_1,NIL,
	    FALSE,5,5));
}
