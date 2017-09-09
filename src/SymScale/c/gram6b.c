/* gram6b.c
 * Input file:  grammar6b.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram6b.h"


/* COMPILE-CONNECTIONS?-FOR-SLOT */
Object compile_connections_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(201,0);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return fix_up_connections_qm(parse_result);
}

static Object Qinherited;          /* inherited */

static Object Qnone;               /* none */

static Object Qsc;                 /* \; */

static Object Qstubs;              /* stubs */

static Object string_constant;     /* "Coordinates must be positive and of reasonable size" */

/* FIX-UP-CONNECTIONS? */
Object fix_up_connections_qm(connections_qm)
    Object connections_qm;
{
    Object stub, ab_loop_list_, trailing_pointer, leading_pointer;
    Object cdr_new_value, result_1, temp_1, temp_2;
    SI_Long i, arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(201,1);
    if (EQ(connections_qm,Qinherited))
	return VALUES_1(Nil);
    else if (EQ(connections_qm,Qnone))
	return VALUES_1(Qnone);
    else {
	if (EQ(CAR(connections_qm),Qsc)) {
	    stub = Nil;
	    ab_loop_list_ = CDR(connections_qm);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    stub = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (LISTP(stub)) {
		trailing_pointer = Nil;
		leading_pointer = stub;
		i = (SI_Long)0L;
	      next_loop_1:
		if ( !TRUEP(leading_pointer))
		    goto end_loop_1;
		if (i == (SI_Long)6L) {
		    if (CDR(leading_pointer) && EQ(Qnone,
			    CADR(leading_pointer))) {
			cdr_new_value = CDDR(leading_pointer);
			M_CDR(leading_pointer) = cdr_new_value;
			if ( !TRUEP(CAR(leading_pointer))) {
			    cdr_new_value = CDR(leading_pointer);
			    M_CDR(trailing_pointer) = cdr_new_value;
			}
		    }
		    goto end_loop_1;
		}
		trailing_pointer = leading_pointer;
		leading_pointer = CDR(leading_pointer);
		i = i + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    goto next_loop;
	  end_loop:;
	    result_1 = phrase_cons(Qstubs,CDR(connections_qm));
	}
	else
	    result_1 = phrase_cons(Qstubs,phrase_cons(connections_qm,Nil));
	stub = Nil;
	ab_loop_list_ = CDR(result_1);
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	stub = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	arg = (SI_Long)0L;
	arg_1 = IFIX(FIFTH(stub));
	arg_2 = (SI_Long)1000L;
	if ( !(arg <= arg_1 && arg_1 <= arg_2)) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
	if (temp)
	    return VALUES_1(result_1);
	else {
	    temp_1 = Bad_phrase;
	    temp_2 = copy_text_string(string_constant);
	    return VALUES_2(temp_1,temp_2);
	}
    }
}

static Object string_constant_1;   /* ";~%" */

static Object array_constant;      /* # */

/* WRITE-ATTRIBUTE-DESCRIPTIONS-FROM-SLOT */
Object write_attribute_descriptions_from_slot(list_of_attribute_descriptions,
	    definition)
    Object list_of_attribute_descriptions, definition;
{
    Object listed_description;

    x_note_fn_call(201,2);
    if (list_of_attribute_descriptions) {
	listed_description = list_of_attribute_descriptions;
      next_loop:
	if ( !TRUEP(listed_description))
	    goto end_loop;
	write_attribute_description(3,CAR(listed_description),definition,
		definition);
	if (CDR(listed_description))
	    tformat(1,string_constant_1);
	listed_description = M_CDR(listed_description);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object Qdatum;              /* datum */

static Object Qvalue;              /* value */

static Object Qquantity;           /* quantity */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qitem_or_value;      /* item-or-value */

static Object Qindexed_attributes_for_definition;  /* indexed-attributes-for-definition */

static Object string_constant_2;   /* "~(~a::~a~)" */

static Object Qab_class;           /* class */

static Object Qinstantiate_variable;  /* instantiate-variable */

static Object string_constant_3;   /* " is given by " */

static Object string_constant_4;   /* " is an instance of " */

static Object string_constant_5;   /* "," */

static Object string_constant_6;   /* " is a structure," */

static Object string_constant_7;   /* " is a sequence," */

static Object string_constant_8;   /* " is " */

static Object string_constant_9;   /* " " */

static Object string_constant_10;  /* "~( has values ~a or ~a~)" */

static Object string_constant_11;  /* " has values " */

static Object string_constant_12;  /* "or" */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Kfuncall;            /* :funcall */

static Object string_constant_13;  /* " initially is given by " */

static Object string_constant_14;  /* " initially is an instance of " */

static Object string_constant_15;  /* " initially is " */

static Object Qtext;               /* text */

static Object string_constant_16;  /* ", with an index" */

/* WRITE-ATTRIBUTE-DESCRIPTION */
Object write_attribute_description varargs_1(int, n)
{
    Object description, definition_of_description, definition;
    Object defining_class_qm, attribute_name, attribute_type_specification_1;
    Object attribute_type_modifications_1;
    Object attribute_type_specification_for_printing, temp, initial_value_qm;
    Object initial_type_qm, attribute_range_qm, indexed_attributes;
    Object name_of_defined_class, write_symbols_parsably_qm, class_1;
    Object slot_description, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, override_qm;
    Object default_initialization_value_qm, initial_value_to_print;
    Object initial_type_for_printing, write_strings_parsably_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(201,3);
    INIT_ARGS_nonrelocating();
    description = REQUIRED_ARG_nonrelocating();
    definition_of_description = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    defining_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    attribute_name = CAR(description);
    attribute_type_specification_1 = attribute_type_specification(description);
    attribute_type_modifications_1 = attribute_type_modifications(description);
    if (EQ(attribute_type_specification_1,Qdatum))
	attribute_type_specification_for_printing = Qvalue;
    else if (EQ(attribute_type_specification_1,Qnumber))
	attribute_type_specification_for_printing = Qquantity;
    else if (EQ(attribute_type_specification_1,Qitem_or_datum))
	attribute_type_specification_for_printing = Qitem_or_value;
    else
	attribute_type_specification_for_printing = 
		attribute_type_specification_1;
    temp = CDDR(description);
    initial_value_qm = CAR(temp);
    temp = CDDDR(description);
    initial_type_qm = CAR(temp);
    attribute_range_qm = CDDDDR(description);
    indexed_attributes = 
	    get_lookup_slot_value_given_default(definition_of_description,
	    Qindexed_attributes_for_definition,Nil);
    name_of_defined_class = ISVREF(definition,(SI_Long)20L);
    if (defining_class_qm)
	tformat(3,string_constant_2,defining_class_qm,attribute_name);
    else {
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		0);
	  twrite_symbol(1,attribute_name);
	POP_SPECIAL();
    }
    if (CONSP(attribute_type_specification_for_printing)) {
	if (EQ(CAR(attribute_type_specification_1),Qab_class)) {
	    class_1 = CADR(attribute_type_specification_1);
	    if (initial_value_qm && EQ(SECOND(initial_value_qm),
		    Qinstantiate_variable))
		twrite(string_constant_3);
	    else
		twrite(string_constant_4);
	    twrite(supply_a_or_an(class_1));
	    twrite_symbol(1,class_1);
	    if (initial_value_qm || attribute_range_qm)
		twrite(string_constant_5);
	}
	else if (structure_type_specification_p(attribute_type_specification_1))
	    twrite(string_constant_6);
	else if (sequence_type_specification_p(attribute_type_specification_1))
	    twrite(string_constant_7);
    }
    else {
	twrite(string_constant_8);
	twrite(supply_a_or_an(attribute_type_specification_for_printing));
	twrite_symbol(1,attribute_type_specification_for_printing);
	twrite(string_constant_5);
    }
    if (attribute_type_modifications_1) {
	twrite(string_constant_9);
	write_attribute_type_modifications(attribute_type_modifications_1);
	twrite(string_constant_5);
    }
    if (attribute_range_qm) {
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		0);
	  if (IFIX(length(attribute_range_qm)) == (SI_Long)2L)
	      tformat(3,string_constant_10,FIFTH(description),
		      SIXTH(description));
	  else {
	      twrite(string_constant_11);
	      write_list_in_chicago_style(2,CDDDDR(description),
		      string_constant_12);
	  }
	  if (initial_value_qm)
	      tformat(1,string_constant_5);
	POP_SPECIAL();
    }
    if ( !EQ(definition_of_description,definition)) {
	slot_description = 
		get_slot_description_of_class_description_function(attribute_name,
		lookup_global_or_kb_specific_property_value(ISVREF(definition_of_description,
		(SI_Long)20L),Class_description_gkbprop),Nil);
	if (slot_description) {
	    if (SYMBOLP(name_of_defined_class)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = name_of_defined_class;
		key_hash_value = SXHASH_SYMBOL_1(name_of_defined_class) & 
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = name_of_defined_class;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			svref_arg_1 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
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
	      next_loop_3:
		if (level < ab_loop_bind_)
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_2;
		goto next_loop_4;
	      end_loop_5:
	      end_2:
		level = level - (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_6:
		    if (level < ab_loop_bind_)
			goto end_loop_6;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_8;
		  end_loop_7:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_3;
		    goto next_loop_7;
		  end_loop_8:
		  end_3:
		    level = level - (SI_Long)1L;
		    goto next_loop_6;
		  end_loop_6:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
			goto end_4;
		    goto next_loop_10;
		  end_loop_11:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_9;
		  end_loop_9:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_2 = TRUEP(resulting_value);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	override_qm = temp_2 ? 
		get_next_most_specific_override_on_slot_description(ISVREF(definition,
		(SI_Long)20L),slot_description) : Nil;
	default_initialization_value_qm = override_qm ? 
		SECOND(override_qm) : Nil;
    }
    else
	default_initialization_value_qm = Nil;
    if (initial_value_qm || default_initialization_value_qm) {
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		1);
	  initial_value_to_print = default_initialization_value_qm ? 
		  (aggregate_evaluation_value_p(default_initialization_value_qm) 
		  || CONSP(default_initialization_value_qm) && 
		  EQ(CAR(default_initialization_value_qm),Kfuncall) ? 
		  default_initialization_value_qm : 
		  CAR(default_initialization_value_qm)) : initial_value_qm;
	  initial_type_for_printing = default_initialization_value_qm &&  
		  !TRUEP(aggregate_evaluation_value_p(initial_value_to_print)) 
		  ? CADR(default_initialization_value_qm) : initial_type_qm;
	  if (CONSP(initial_value_to_print) && 
		  EQ(CAR(initial_value_to_print),Kfuncall)) {
	      twrite(EQ(SECOND(initial_value_to_print),
		      Qinstantiate_variable) ? string_constant_13 : 
		      string_constant_14);
	      write_symbol_with_a_or_an(1,THIRD(initial_value_to_print));
	  }
	  else if (aggregate_evaluation_value_p(initial_value_to_print)) {
	      twrite(string_constant_15);
	      write_evaluation_value(1,initial_value_to_print);
	  }
	  else {
	      twrite(string_constant_15);
	      if (EQ(initial_type_for_printing,Qsymbol))
		  print_constant(2,initial_value_to_print,Qsymbol);
	      else if (EQ(initial_type_for_printing,Qtext)) {
		  write_strings_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
			  0);
		    twrite_general_string(initial_value_to_print);
		  POP_SPECIAL();
	      }
	      else
		  print_constant(2,initial_value_to_print,
			  initial_type_for_printing);
	  }
	POP_SPECIAL();
    }
    if (memq_function(attribute_name,indexed_attributes))
	return twrite(string_constant_16);
    else
	return VALUES_1(Nil);
}

static Object string_constant_17;  /* "inherited" */

static Object Qinput;              /* input */

static Object string_constant_18;  /* "input " */

static Object Qoutput;             /* output */

static Object string_constant_19;  /* "output " */

static Object string_constant_20;  /* "" */

static Object string_constant_21;  /* "~(~a~a~a~a~a located at ~a ~d~)" */

static Object string_constant_22;  /* "~( with style ~a~)" */

static Object string_constant_23;  /* " and" */

static Object string_constant_24;  /* " with line-pattern " */

static Object Qconnection_line_pattern;  /* connection-line-pattern */

static Object Qslot_value_writer;  /* slot-value-writer */

static Object string_constant_25;  /* "[deleted attribute]" */

static Object string_constant_26;  /* " with connection-arrows " */

static Object Qconnection_arrows;  /* connection-arrows */

/* WRITE-CONNECTIONS?-FROM-SLOT */
Object write_connections_qm_from_slot(value,definition)
    Object value, definition;
{
    Object name_qm, class_1, direction_qm, edge, coordinate, style_qm;
    Object pattern_qm, connection_arrows_qm, more_qm, ab_loop_list_, temp;
    Object temp_1, slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm;
    Declare_special(2);

    x_note_fn_call(201,4);
    if ( !TRUEP(value))
	return twrite(string_constant_17);
    else if (EQ(value,Qnone))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else {
	name_qm = Nil;
	class_1 = Nil;
	direction_qm = Nil;
	edge = Nil;
	coordinate = Nil;
	style_qm = Nil;
	pattern_qm = Nil;
	connection_arrows_qm = Nil;
	more_qm = Nil;
	ab_loop_list_ = CDR(value);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	temp = CAR(ab_loop_list_);
	name_qm = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	class_1 = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	temp = CDR(temp);
	direction_qm = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	edge = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	coordinate = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	style_qm = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	pattern_qm = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	connection_arrows_qm = CAR(temp);
	more_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = direction_qm;
	if (temp);
	else
	    temp = class_1;
	temp = supply_a_or_an(temp);
	if (EQ(direction_qm,Qinput))
	    temp_1 = string_constant_18;
	else if (EQ(direction_qm,Qoutput))
	    temp_1 = string_constant_19;
	else
	    temp_1 = string_constant_20;
	tformat(8,string_constant_21,temp,temp_1,class_1,name_qm ? 
		string_constant_9 : string_constant_20,name_qm ? name_qm : 
		string_constant_20,edge,coordinate);
	if (style_qm)
	    tformat(2,string_constant_22,style_qm);
	if (pattern_qm) {
	    if (style_qm)
		tformat(1,string_constant_23);
	    tformat(1,string_constant_24);
	    slot_value_writer_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnection_line_pattern),
		    Qslot_value_writer);
	    if (slot_value_writer_qm) {
		write_symbols_in_lower_case_qm = T;
		write_symbols_parsably_qm = T;
		PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			  0);
		    inline_funcall_2(slot_value_writer_qm,pattern_qm,
			    definition);
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		twrite(string_constant_25);
	}
	if (connection_arrows_qm) {
	    if (style_qm || pattern_qm)
		tformat(1,string_constant_23);
	    tformat(1,string_constant_26);
	    slot_value_writer_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnection_arrows),
		    Qslot_value_writer);
	    if (slot_value_writer_qm) {
		write_symbols_in_lower_case_qm = T;
		write_symbols_parsably_qm = T;
		PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			  0);
		    inline_funcall_2(slot_value_writer_qm,
			    connection_arrows_qm,definition);
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		twrite(string_constant_25);
	}
	if (more_qm)
	    tformat(1,string_constant_1);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COMPILE-NAME-OR-NAMES-FOR-SLOT */
Object compile_name_or_names_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(201,5);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(translation,Qnone))
	return VALUES_1(Nil);
    else if (SYMBOLP(translation))
	return VALUES_1(translation);
    else if ( !TRUEP(CDDR(translation)))
	return VALUES_1(SECOND(translation));
    else
	return VALUES_1(CDR(translation));
}

static Object array_constant_1;    /* # */

/* WRITE-NAME-OR-NAMES-FROM-SLOT */
Object write_name_or_names_from_slot(name_or_names,gensymed_symbol)
    Object name_or_names, gensymed_symbol;
{
    Object ab_loop_destructure_, name, rest_of_names;

    x_note_fn_call(201,6);
    if ( !TRUEP(name_or_names))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (ATOM(name_or_names))
	return twrite_symbol(2,name_or_names,T);
    else {
	ab_loop_destructure_ = name_or_names;
	name = Nil;
	rest_of_names = Nil;
	name = CAR(ab_loop_destructure_);
	rest_of_names = CDR(ab_loop_destructure_);
      next_loop:
	twrite_symbol(2,name,T);
	if ( !TRUEP(rest_of_names))
	    goto end_loop;
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	name = CAR(rest_of_names);
	rest_of_names = CDR(rest_of_names);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_27;  /* ", " */

/* WRITE-FOCAL-CLASSES-FROM-SLOT */
Object write_focal_classes_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object name, rest_qm, ab_loop_list_;

    x_note_fn_call(201,7);
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else {
	name = Nil;
	rest_qm = Nil;
	ab_loop_list_ = value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name = CAR(ab_loop_list_);
	rest_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	twrite_symbol(1,name);
	if (rest_qm)
	    twrite(string_constant_27);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_28;  /* "~(~NF~)" */

static Object string_constant_29;  /* "~(~A~)" */

/* WRITE-LIST-IN-CHICAGO-STYLE */
Object write_list_in_chicago_style varargs_1(int, n)
{
    Object list_1, and_or_or;
    Object list_of_blocks_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(201,8);
    INIT_ARGS_nonrelocating();
    list_1 = REQUIRED_ARG_nonrelocating();
    and_or_or = REQUIRED_ARG_nonrelocating();
    list_of_blocks_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    write_list_in_chicago_style_given_format(list_1,and_or_or,
	    list_of_blocks_qm ? string_constant_28 : string_constant_29);
    return VALUES_1(Nil);
}

static Object string_constant_30;  /* ", ~a " */

/* WRITE-LIST-IN-CHICAGO-STYLE-GIVEN-FORMAT */
Object write_list_in_chicago_style_given_format(list_1,and_or_or,
	    tformat_string)
    Object list_1, and_or_or, tformat_string;
{
    Object listed_element;

    x_note_fn_call(201,9);
    if ( !TRUEP(list_1))
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)4L));
    else if ( !TRUEP(M_CDR(list_1)))
	tformat(2,tformat_string,M_CAR(list_1));
    else if ( !TRUEP(M_CDR(M_CDR(list_1)))) {
	tformat(2,tformat_string,M_CAR(list_1));
	twrite_character(FIX((SI_Long)32L));
	twrite_general_string(and_or_or);
	twrite_character(FIX((SI_Long)32L));
	tformat(2,tformat_string,M_CAR(M_CDR(list_1)));
    }
    else {
	listed_element = list_1;
      next_loop:
	if ( !TRUEP(listed_element))
	    goto end_loop;
	tformat(2,tformat_string,M_CAR(listed_element));
	if (CDDR(listed_element))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	else if (CDR(listed_element))
	    tformat(2,string_constant_30,and_or_or);
	listed_element = M_CDR(listed_element);
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* SENTENCE-END-PUNCTUATION? */
Object sentence_end_punctuation_qm(symbol_or_string)
    Object symbol_or_string;
{
    Object string_1, temp;

    x_note_fn_call(201,10);
    string_1 = stringw(symbol_or_string);
    temp = FIX(UBYTE_16_ISAREF_1(string_1,
	    IFIX(FIXNUM_SUB1(lengthw(string_1)))));
    temp = wide_character_member(temp,Sentence_end_punctuation_characters);
    return VALUES_1(FIRST(temp));
}

/* COMPILE-FOCAL-OBJECTS-FOR-SLOT */
Object compile_focal_objects_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(201,11);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(translation,Qnone))
	return VALUES_1(Nil);
    else if (SYMBOLP(translation))
	return phrase_cons(translation,Nil);
    else
	return VALUES_1(CDR(translation));
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qfocal_classes;      /* focal-classes */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* FOCAL-OBJECTS-EVALUATION-SETTER */
Object focal_objects_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,12);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_focal_objects_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfocal_classes),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_focal_objects_evaluation_setter:
    return result;
}

/* FOCAL-OBJECTS-EVALUATION-GETTER */
Object focal_objects_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(201,13);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfocal_classes),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-FOCAL-OBJECTS-FROM-SLOT */
Object write_focal_objects_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object name, rest_qm, ab_loop_list_;

    x_note_fn_call(201,14);
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else {
	name = Nil;
	rest_qm = Nil;
	ab_loop_list_ = value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name = CAR(ab_loop_list_);
	rest_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	twrite_symbol(1,name);
	if (rest_qm)
	    twrite(string_constant_27);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COMPILE-CATEGORIES-FOR-SLOT */
Object compile_categories_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(201,15);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_symbol_list(translation);
}

/* COMPILE-SYMBOL-LIST */
Object compile_symbol_list(translation)
    Object translation;
{
    x_note_fn_call(201,16);
    if (EQ(translation,Qnone))
	return VALUES_1(Nil);
    else if (SYMBOLP(translation))
	return phrase_cons(translation,Nil);
    else
	return VALUES_1(CDR(translation));
}

static Object list_constant_2;     /* # */

/* CATEGORIES-EVALUATION-SETTER */
Object categories_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,17);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_2))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_categories_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfocal_classes),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_categories_evaluation_setter:
    return result;
}

/* CATEGORIES-EVALUATION-GETTER */
Object categories_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(201,18);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfocal_classes),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-CATEGORIES-FROM-SLOT */
Object write_categories_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(201,19);
    return write_symbol_list(1,value);
}

static Object Quser_defined;       /* user-defined */

/* FIX-DEFAULT-OVERRIDE-ON-USER-DEFINED-SLOT */
Object fix_default_override_on_user_defined_slot(phrase)
    Object phrase;
{
    Object initialization_phrase, temp;

    x_note_fn_call(201,20);
    initialization_phrase = SECOND(phrase);
    temp = fix_override_initial_value(initialization_phrase);
    M_SECOND(phrase) = temp;
    temp = phrase_cons(Quser_defined,Nil);
    M_CDDR(phrase) = temp;
    return VALUES_1(phrase);
}

static Object Qtruth_value;        /* truth-value */

/* FIX-OVERRIDE-INITIAL-VALUE */
Object fix_override_initial_value(initialization_phrase)
    Object initialization_phrase;
{
    Object temp;
    char temp_1;

    x_note_fn_call(201,21);
    if (CONSP(initialization_phrase)) {
	if (EQ(M_CAR(initialization_phrase),Kfuncall))
	    return phrase_cons(initialization_phrase,Nil);
	else if (truth_value_phrase_p(initialization_phrase))
	    return phrase_list_2(CAR(initialization_phrase),Qtruth_value);
	else {
	    if (phrase_number_p(CAR(initialization_phrase))) {
		temp = CDR(initialization_phrase);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return phrase_list_2(CAR(initialization_phrase),
			CDR(initialization_phrase));
	    else if (CONSP(initialization_phrase) && 
		    EQ(M_CDR(initialization_phrase),
		    Phrase_structure_marker) || 
		    CONSP(initialization_phrase) && 
		    EQ(M_CDR(initialization_phrase),Phrase_sequence_marker))
		return VALUES_1(initialization_phrase);
	    else
		return VALUES_1(Qnil);
	}
    }
    else if ( !TRUEP(initialization_phrase))
	return phrase_list_2(Nil,Nil);
    else if (phrase_number_p(initialization_phrase))
	return phrase_list_2(initialization_phrase,Qnumber);
    else if (SYMBOLP(initialization_phrase))
	return phrase_list_2(initialization_phrase,Qsymbol);
    else if (text_string_p(initialization_phrase))
	return phrase_list_2(initialization_phrase,Qtext);
    else
	return VALUES_1(Qnil);
}

/* DEFINITION-SUBCLASSP */
Object definition_subclassp(definition,class_1)
    Object definition, class_1;
{
    Object superclass, ab_loop_list_, ab_loop_it_, gensymed_symbol, temp;

    x_note_fn_call(201,22);
    superclass = Nil;
    ab_loop_list_ = ISVREF(definition,(SI_Long)21L);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superclass = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(superclass,
	    Class_description_gkbprop);
    ab_loop_it_ = gensymed_symbol ? memq_function(class_1,
	    ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Quse_slot_value_compiler_for_default_overrides_p;  /* use-slot-value-compiler-for-default-overrides-p */

static Object Qslot_value_compiler;  /* slot-value-compiler */

static Object string_constant_31;  /* "~a" */

/* COMPILE-DEFAULT-OVERRIDE */
Object compile_default_override(override,slot_name_qm,defining_class,
	    definition,report_error_qm)
    Object override, slot_name_qm, defining_class, definition, report_error_qm;
{
    Object grammar_category_qm, slot_value_compiler_qm, compilation;
    Object error_text_qm;
    Object result;

    x_note_fn_call(201,23);
    grammar_category_qm = 
	    get_grammar_category_for_default_override(slot_name_qm,
	    defining_class,T);
    slot_value_compiler_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
	    Quse_slot_value_compiler_for_default_overrides_p) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
	    Qslot_value_compiler) : Nil;
    if (slot_value_compiler_qm) {
	result = funcall(7,slot_value_compiler_qm,SECOND(override),
		definition,slot_name_qm,defining_class,Nil,Nil);
	MVS_2(result,compilation,error_text_qm);
	if (error_text_qm || EQ(compilation,Bad_phrase)) {
	    if (error_text_qm) {
		if (report_error_qm)
		    tformat(2,string_constant_31,error_text_qm);
		reclaim_text_string(error_text_qm);
	    }
	    return VALUES_1(T);
	}
	else {
	    M_SECOND(override) = compilation;
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_32;  /* "The initial value for ~a could not be compiled." */

static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

static Object Qcar_equal;          /* car-equal */

static Object string_constant_33;  /* "This attribute initialization list has duplicate attribute names." */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qframe_flags;        /* frame-flags */

static Object Qforward_chain_flag;  /* forward-chain-flag */

static Object Qalways_forward_chain_if_possible_flag;  /* always-forward-chain-if-possible-flag */

static Object Qpassive_flag;       /* passive-flag */

static Object Qdont_backward_chain_flag;  /* dont-backward-chain-flag */

static Object Qdepth_first_flag;   /* depth-first-flag */

static Object Qcache_data_for_explanation_flag;  /* cache-data-for-explanation-flag */

static Object Qinitial_value_of_variable_or_parameter;  /* initial-value-of-variable-or-parameter */

static Object string_constant_34;  /* "The initial value, " */

static Object string_constant_35;  /* ", is not compatible ~
				    *                                          with the type of the variable, ~NT."
				    */

static Object Qinterface_timeout_period;  /* interface-timeout-period */

static Object Qg2_array_length;    /* g2-array-length */

static Object string_constant_36;  /* "Bad g2-array length." */

static Object Qg2_array_element_type;  /* g2-array-element-type */

static Object string_constant_37;  /* "You cannot use ~a, since it names a value type, and ~
				    *                             so cannot be a class name."
				    */

static Object Qlist_type;          /* list-type */

static Object string_constant_38;  /* "The following are not inheritable system attributes ~
				    *                      for this class: "
				    */

static Object string_constant_39;  /* "~(~a~)" */

static Object string_constant_40;  /* "interface-timeout-period should be a value between 1 and 16 seconds" */

static Object array_constant_2;    /* # */

/* COMPILE-DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS-FOR-SLOT */
Object compile_default_overrides_for_class_definitions_for_slot varargs_1(int, n)
{
    Object translation, definition, gensymed_symbol;
    Object override, ab_loop_list_, problem_override_qm, temp, temp_1;
    Object direct_superior_classes_qm, direct_superiors_are_defined_qm;
    Object bad_attribute_name_qm, badly_formed_attribute_name_qm, problems_qm;
    Object g2_array_length_problems_qm, interface_timeout_period_problems_qm;
    Object fixed_translation, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object foundation_class_qm, class_inheritance_path_qm;
    Object system_slot_override_but_no_foundation_class_qm, annotation;
    Object initial_value_incompatible_qm, listed_default_override;
    Object default_override, error_or_default_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_name_or_alias, slot_name_is_qualified_qm;
    Object class_check_or_user_defined_qm, override_on_user_defined_slot_qm;
    Object alias_or_slot_name_qm, slot_name_qm, possibly_acceptable_classes_qm;
    Object possibly_acceptable_class_qm, unacceptable_classes_qm;
    Object unacceptable_class_qm, class_check_bad_qm;
    Object inheritable_slot_description_qm, slot_defining_class_qm, superior;
    Object ab_loop_list__1, ab_loop_it_, class_1, ab_loop_list__2;
    Object name_denotation, unqualified_name, flags, defining_class;
    Object grammar_category_qm, compiled_value, slot_value_writer_qm;
    Object write_symbols_in_lower_case_qm, write_symbols_parsably_qm, temp_3;
    Object compilation, error_text_qm, element_type;
    SI_Long bv16_length, temp_2, aref_new_value, length_1, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5;
    Declare_varargs_nonrelocating;
    Declare_special(7);
    Object result;

    x_note_fn_call(201,24);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !( !TRUEP(translation) || EQ(translation,Qnone))) {
	if (EQ(CAR(translation),Qsc)) {
	    override = Nil;
	    ab_loop_list_ = CDR(translation);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    override = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(SECOND(override),Bad_phrase)) {
		problem_override_qm = override;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    problem_override_qm = Qnil;
	  end_1:;
	}
	else
	    problem_override_qm = EQ(SECOND(translation),Bad_phrase) ? 
		    translation : Qnil;
	if (problem_override_qm) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant_32,
		    map_system_slot_name_to_alias(FIRST(problem_override_qm),
		    definition));
	    return VALUES_2(temp,temp_1);
	}
    }
    direct_superior_classes_qm = ISVREF(definition,(SI_Long)21L);
    direct_superiors_are_defined_qm = 
	    direct_superiors_are_defined_p(direct_superior_classes_qm);
    bad_attribute_name_qm = Nil;
    badly_formed_attribute_name_qm = Nil;
    problems_qm = Nil;
    g2_array_length_problems_qm = Nil;
    interface_timeout_period_problems_qm = Nil;
    if ( !TRUEP(translation) || EQ(translation,Qnone))
	fixed_translation = Nil;
    else if (EQ(CAR(translation),Qsc)) {
	override = Nil;
	temp_1 = copy_for_phrase(translation);
	ab_loop_list_ = CDR(temp_1);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = phrase_cons(override,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	fixed_translation = ab_loopvar_;
	goto end_2;
	fixed_translation = Qnil;
      end_2:;
    }
    else
	fixed_translation = phrase_cons(copy_for_phrase(translation),Nil);
    foundation_class_qm = direct_superiors_are_defined_qm ? 
	    most_refined_foundation_class_of_direct_superiors(1,
	    direct_superior_classes_qm) : Nil;
    class_inheritance_path_qm = direct_superiors_are_defined_qm ? 
	    get_lookup_slot_value_given_default(definition,
	    Qclass_inheritance_path_of_definition,Nil) : Qnil;
    system_slot_override_but_no_foundation_class_qm = Nil;
    annotation = Nil;
    initial_value_incompatible_qm = Nil;
    listed_default_override = fixed_translation;
    default_override = Nil;
    error_or_default_value = Nil;
  next_loop_2:
    if ( !TRUEP(listed_default_override))
	goto end_loop_2;
    default_override = CAR(listed_default_override);
    error_or_default_value = SECOND(default_override);
    if (member(4,CAR(default_override),CDR(listed_default_override),Ktest,
	    Qcar_equal)) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_33);
	return VALUES_2(temp,temp_1);
    }
    else if (CONSP(error_or_default_value) && 
	    EQ(M_CAR(error_or_default_value),Bad_phrase)) {
	temp = Bad_phrase;
	temp_1 = CDR(error_or_default_value) ? 
		copy_text_string(CDR(error_or_default_value)) : 
		tformat_text_string(2,string_constant_32,
		map_system_slot_name_to_alias(M_CAR(default_override),
		definition));
	return VALUES_2(temp,temp_1);
    }
    else;
    listed_default_override = M_CDR(listed_default_override);
    goto next_loop_2;
  end_loop_2:;
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      temp_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
      temp_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      override = Nil;
	      ab_loop_list_ = fixed_translation;
	      slot_name_or_alias = Nil;
	      slot_name_is_qualified_qm = Nil;
	      class_check_or_user_defined_qm = Nil;
	      override_on_user_defined_slot_qm = Nil;
	      alias_or_slot_name_qm = Nil;
	      slot_name_qm = Nil;
	      possibly_acceptable_classes_qm = Nil;
	      possibly_acceptable_class_qm = Nil;
	      unacceptable_classes_qm = Nil;
	      unacceptable_class_qm = Nil;
	      class_check_bad_qm = Nil;
	      inheritable_slot_description_qm = Nil;
	      slot_defining_class_qm = Nil;
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_3;
	      override = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      slot_name_or_alias = CAR(override);
	      slot_name_is_qualified_qm = CONSP(slot_name_or_alias) ? T : Nil;
	      class_check_or_user_defined_qm = THIRD(override);
	      override_on_user_defined_slot_qm = 
		      EQ(class_check_or_user_defined_qm,Quser_defined) ? T 
		      : Nil;
	      alias_or_slot_name_qm =  
		      !TRUEP(override_on_user_defined_slot_qm) ? 
		      map_system_slot_name_to_alias(slot_name_or_alias,
		      definition) : Nil;
	      slot_name_qm = override_on_user_defined_slot_qm ? 
		      slot_name_or_alias : 
		      map_alias_to_system_slot_name(alias_or_slot_name_qm,
		      definition);
	      possibly_acceptable_classes_qm =  
		      !TRUEP(override_on_user_defined_slot_qm) ? 
		      FIRST(class_check_or_user_defined_qm) : Qnil;
	      if (class_inheritance_path_qm) {
		  superior = Nil;
		  ab_loop_list__1 = CDR(class_inheritance_path_qm);
		  ab_loop_it_ = Nil;
		next_loop_4:
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop_4;
		  superior = M_CAR(ab_loop_list__1);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  class_1 = Nil;
		  ab_loop_list__2 = possibly_acceptable_classes_qm;
		next_loop_5:
		  if ( !TRUEP(ab_loop_list__2))
		      goto end_loop_5;
		  class_1 = M_CAR(ab_loop_list__2);
		  ab_loop_list__2 = M_CDR(ab_loop_list__2);
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(superior,
			  Class_description_gkbprop);
		  if (gensymed_symbol ? TRUEP(memq_function(class_1,
			  ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) {
		      ab_loop_it_ = T;
		      goto end_3;
		  }
		  goto next_loop_5;
		end_loop_5:
		  ab_loop_it_ = Nil;
		  goto end_3;
		  ab_loop_it_ = Qnil;
		end_3:;
		  if (ab_loop_it_) {
		      possibly_acceptable_class_qm = ab_loop_it_;
		      goto end_4;
		  }
		  goto next_loop_4;
		end_loop_4:
		  possibly_acceptable_class_qm = Qnil;
		end_4:;
	      }
	      else if (Loading_kb_p && direct_superiors_are_defined_qm) {
		  superior = Nil;
		  ab_loop_list__1 = direct_superior_classes_qm;
		  ab_loop_it_ = Nil;
		next_loop_6:
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop_6;
		  superior = M_CAR(ab_loop_list__1);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  class_1 = Nil;
		  ab_loop_list__2 = possibly_acceptable_classes_qm;
		  ab_loop_it_ = Nil;
		next_loop_7:
		  if ( !TRUEP(ab_loop_list__2))
		      goto end_loop_7;
		  class_1 = M_CAR(ab_loop_list__2);
		  ab_loop_list__2 = M_CDR(ab_loop_list__2);
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(superior,
			  Class_description_gkbprop);
		  ab_loop_it_ = gensymed_symbol ? memq_function(class_1,
			  ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
		  if (ab_loop_it_)
		      goto end_5;
		  goto next_loop_7;
		end_loop_7:
		  ab_loop_it_ = Qnil;
		end_5:;
		  if (ab_loop_it_) {
		      possibly_acceptable_class_qm = ab_loop_it_;
		      goto end_6;
		  }
		  goto next_loop_6;
		end_loop_6:
		  possibly_acceptable_class_qm = Qnil;
		end_6:;
	      }
	      else
		  possibly_acceptable_class_qm = Nil;
	      unacceptable_classes_qm =  
		      !TRUEP(override_on_user_defined_slot_qm) ? 
		      SECOND(class_check_or_user_defined_qm) : Qnil;
	      if (unacceptable_classes_qm) {
		  if (class_inheritance_path_qm) {
		      superior = Nil;
		      ab_loop_list__1 = CDR(class_inheritance_path_qm);
		    next_loop_8:
		      if ( !TRUEP(ab_loop_list__1))
			  goto end_loop_8;
		      superior = M_CAR(ab_loop_list__1);
		      ab_loop_list__1 = M_CDR(ab_loop_list__1);
		      if (memq_function(superior,unacceptable_classes_qm)) {
			  unacceptable_class_qm = T;
			  goto end_7;
		      }
		      goto next_loop_8;
		    end_loop_8:
		      unacceptable_class_qm = Qnil;
		    end_7:;
		  }
		  else if (Loading_kb_p && direct_superiors_are_defined_qm) {
		      superior = Nil;
		      ab_loop_list__1 = direct_superior_classes_qm;
		    next_loop_9:
		      if ( !TRUEP(ab_loop_list__1))
			  goto end_loop_9;
		      superior = M_CAR(ab_loop_list__1);
		      ab_loop_list__1 = M_CDR(ab_loop_list__1);
		      if (memq_function(superior,unacceptable_classes_qm)) {
			  unacceptable_class_qm = T;
			  goto end_8;
		      }
		      goto next_loop_9;
		    end_loop_9:
		      unacceptable_class_qm = Qnil;
		    end_8:;
		  }
		  else
		      unacceptable_class_qm = Nil;
	      }
	      else
		  unacceptable_class_qm = Nil;
	      if ( !TRUEP(override_on_user_defined_slot_qm)) {
		  temp_1 =  !TRUEP(possibly_acceptable_class_qm) ? T : Nil;
		  if (temp_1);
		  else
		      temp_1 = unacceptable_class_qm;
		  class_check_bad_qm = temp_1;
	      }
	      else
		  class_check_bad_qm = Nil;
	      inheritable_slot_description_qm = 
		      slot_description_from_superior_class(slot_name_qm,
		      definition);
	      slot_defining_class_qm = inheritable_slot_description_qm ? 
		      ISVREF(inheritable_slot_description_qm,(SI_Long)3L) :
		       Nil;
	      if (override_on_user_defined_slot_qm) {
		  name_denotation = FIRST(override);
		  unqualified_name = CONSP(name_denotation) ? 
			  M_CAR(M_CDR(M_CDR(name_denotation))) : 
			  name_denotation;
		  if (SYMBOLP(unqualified_name)) {
		      if (reserved_system_slot_name_p(definition,
			      unqualified_name)) {
			  bad_attribute_name_qm = unqualified_name;
			  goto end_loop_3;
		      }
		  }
		  else {
		      badly_formed_attribute_name_qm = unqualified_name;
		      goto end_loop_3;
		  }
	      }
	      else if ( !TRUEP(foundation_class_qm)) {
		  system_slot_override_but_no_foundation_class_qm = 
			  slot_name_or_alias;
		  problems_qm = T;
	      }
	      else if (EQ(slot_name_qm,Qframe_flags)) {
		  flags = SECOND(override);
		  if (memq_function(Qvariable,
			      possibly_acceptable_classes_qm)) {
		      temp_1 = FIRST(flags);
		      gensymed_symbol_1 = EQ(temp_1,Qforward_chain_flag) ? 
			      (SI_Long)2L : (SI_Long)0L;
		      gensymed_symbol_2 = EQ(SECOND(flags),
			      Qalways_forward_chain_if_possible_flag) ? 
			      (SI_Long)32L : (SI_Long)0L;
		      temp_1 = THIRD(flags);
		      if (EQ(temp_1,Qpassive_flag))
			  gensymed_symbol_3 = (SI_Long)16L + (SI_Long)32768L;
		      else if (EQ(temp_1,Qdont_backward_chain_flag))
			  gensymed_symbol_3 = (SI_Long)32768L;
		      else if (EQ(temp_1,Qdepth_first_flag))
			  gensymed_symbol_3 = (SI_Long)8L;
		      else
			  gensymed_symbol_3 = (SI_Long)0L;
		      temp_1 = FOURTH(flags);
		      gensymed_symbol_4 = EQ(temp_1,
			      Qcache_data_for_explanation_flag) ? 
			      (SI_Long)1048576L : (SI_Long)0L;
		      temp_2 = gensymed_symbol_1 + gensymed_symbol_2 + 
			      gensymed_symbol_3 + gensymed_symbol_4;
		  }
		  else {
		      gensymed_symbol_1 = (SI_Long)16L;
		      gensymed_symbol_2 = (SI_Long)32768L;
		      temp_1 = FIRST(flags);
		      gensymed_symbol_3 = EQ(temp_1,Qforward_chain_flag) ? 
			      (SI_Long)2L : (SI_Long)0L;
		      gensymed_symbol_4 = EQ(SECOND(flags),
			      Qalways_forward_chain_if_possible_flag) ? 
			      (SI_Long)32L : (SI_Long)0L;
		      temp_1 = THIRD(flags);
		      gensymed_symbol_5 = EQ(temp_1,
			      Qcache_data_for_explanation_flag) ? 
			      (SI_Long)1048576L : (SI_Long)0L;
		      temp_2 = gensymed_symbol_1 + gensymed_symbol_2 + 
			      gensymed_symbol_3 + gensymed_symbol_4 + 
			      gensymed_symbol_5;
		  }
		  M_SECOND(override) = FIX(temp_2);
	      }
	      else if (EQ(slot_name_qm,
		      Qinitial_value_of_variable_or_parameter)) {
		  if (inheritable_slot_description_qm)
		      defining_class = 
			      ISVREF(inheritable_slot_description_qm,
			      (SI_Long)3L);
		  else {
		      temp_1 = THIRD(override);
		      temp_1 = FIRST(temp_1);
		      defining_class = FIRST(temp_1);
		  }
		  grammar_category_qm = 
			  get_grammar_category_for_default_override(slot_name_qm,
			  defining_class,T);
		  temp_1 = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
			  Qslot_value_compiler);
		  compiled_value = funcall(7,temp_1,SECOND(override),Nil,
			  slot_name_qm,defining_class,Nil,Nil);
		  if ( 
			  !TRUEP(check_initial_value_of_variable_or_parameter(compiled_value,
			  fixed_translation,definition))) {
		      tformat(1,string_constant_34);
		      slot_value_writer_qm = 
			      getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
			      Qslot_value_writer);
		      if (slot_value_writer_qm) {
			  write_symbols_in_lower_case_qm = T;
			  write_symbols_parsably_qm = T;
			  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
				  1);
			    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
				    0);
			      inline_funcall_2(slot_value_writer_qm,
				      compiled_value,definition);
			    POP_SPECIAL();
			  POP_SPECIAL();
		      }
		      else
			  twrite(string_constant_25);
		      tformat(2,string_constant_35,
			      get_data_type_of_variable_or_parameter_from_frame(2,
			      definition,fixed_translation));
		      problems_qm = T;
		  }
		  M_SECOND(override) = compiled_value;
	      }
	      else if (EQ(slot_name_qm,Qinterface_timeout_period)) {
		  temp_1 = override;
		  temp = slot_name_qm;
		  temp_3 = slot_defining_class_qm;
		  if (temp_3);
		  else {
		      temp_3 = THIRD(override);
		      temp_3 = FIRST(temp_3);
		      temp_3 = FIRST(temp_3);
		  }
		  if (compile_default_override(temp_1,temp,temp_3,
			  definition,T))
		      interface_timeout_period_problems_qm = T;
	      }
	      else if (EQ(slot_name_qm,Qg2_array_length)) {
		  result = compile_g2_array_length_for_slot(3,
			  SECOND(override),Nil,Nil);
		  MVS_2(result,compilation,error_text_qm);
		  if (EQ(compilation,Bad_phrase)) {
		      g2_array_length_problems_qm = T;
		      temp_1 = error_text_qm;
		      if (temp_1);
		      else
			  temp_1 = string_constant_36;
		      twrite_general_string(temp_1);
		  }
		  else
		      M_SECOND(override) = compilation;
	      }
	      else if (EQ(slot_name_qm,Qg2_array_element_type)) {
		  element_type = SECOND(override);
		  if (type_specification_for_user_or_datum_type(element_type)) 
			      {
		      tformat(2,string_constant_37,element_type);
		      problems_qm = T;
		  }
	      }
	      else if (EQ(slot_name_qm,Qlist_type)) {
		  element_type = SECOND(override);
		  if (type_specification_for_user_or_datum_type(element_type)) 
			      {
		      tformat(2,string_constant_37,element_type);
		      problems_qm = T;
		  }
	      }
	      else {
		  temp_1 = override;
		  temp = slot_name_qm;
		  temp_3 = slot_defining_class_qm;
		  if (temp_3);
		  else {
		      temp_3 = THIRD(override);
		      temp_3 = FIRST(temp_3);
		      temp_3 = FIRST(temp_3);
		  }
		  if (compile_default_override(temp_1,temp,temp_3,
			  definition,T))
		      problems_qm = T;
	      }
	      if ( !TRUEP(override_on_user_defined_slot_qm) && ( 
		      !TRUEP(inheritable_slot_description_qm) || 
		      class_check_bad_qm)) {
		  if ( !TRUEP(problems_qm))
		      tformat(1,string_constant_38);
		  if (problems_qm)
		      twrite(string_constant_27);
		  tformat(2,string_constant_39,alias_or_slot_name_qm);
		  problems_qm = T;
	      }
	      goto next_loop_3;
	    end_loop_3:;
	      annotation = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (bad_attribute_name_qm)
	return bad_attribute_name(bad_attribute_name_qm);
    else if (badly_formed_attribute_name_qm)
	return badly_formed_attribute_name();
    else if (problems_qm && system_slot_override_but_no_foundation_class_qm)
	return system_slot_override_but_no_foundation_class(system_slot_override_but_no_foundation_class_qm);
    else if (problems_qm || g2_array_length_problems_qm)
	return VALUES_2(Bad_phrase,annotation);
    else if (interface_timeout_period_problems_qm) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_40);
	return VALUES_2(temp,temp_1);
    }
    else if (initial_value_incompatible_qm) {
	reclaim_text_string(annotation);
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)55L));
	return VALUES_2(temp,temp_1);
    }
    else {
	reclaim_text_string(annotation);
	override = Nil;
	ab_loop_list_ = fixed_translation;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_10:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_10;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(THIRD(override),Quser_defined))
	    temp_1 = override;
	else {
	    temp_1 = THIRD(override);
	    temp_1 = FIRST(temp_1);
	    temp_1 = phrase_list_3(FIRST(override),SECOND(override),
		    FIRST(temp_1));
	}
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_10;
      end_loop_10:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

static Object Qinitial_value;      /* initial-value */

static Object string_constant_41;  /* "The following are not attributes of ~(~A~): " */

static Object string_constant_42;  /* " for ~(~a~)" */

/* COMPILE-DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS-FOR-SLOT */
Object compile_default_overrides_for_object_definitions_for_slot varargs_1(int, n)
{
    Object translation, definition, gensymed_symbol;
    Object direct_superior_classes_qm, direct_superiors_are_defined_qm;
    Object bad_attribute_name_qm, badly_formed_attribute_name_qm, problems_qm;
    Object g2_array_length_problems_qm, fixed_translation, override, temp;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object foundation_class_qm;
    Object system_slot_override_but_no_foundation_class_qm, annotation;
    Object initial_value_incompatible_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_name_or_alias, slot_name_is_qualified_qm;
    Object class_check_or_user_defined_qm, override_on_user_defined_slot_qm;
    Object alias_or_slot_name_qm, slot_name_qm, class_check_bad_qm;
    Object foundation_class_slot_description, slot_defining_class_qm;
    Object name_denotation, unqualified_name, flags, defining_class;
    Object grammar_category_qm, compiled_value, slot_value_writer_qm;
    Object write_symbols_in_lower_case_qm, write_symbols_parsably_qm;
    Object compilation, error_text_qm, element_type, temp_2, temp_3;
    SI_Long bv16_length, temp_1, aref_new_value, length_1, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5;
    Declare_varargs_nonrelocating;
    Declare_special(7);
    Object result;

    x_note_fn_call(201,25);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    direct_superior_classes_qm = ISVREF(definition,(SI_Long)21L);
    direct_superiors_are_defined_qm = 
	    direct_superiors_are_defined_p(direct_superior_classes_qm);
    bad_attribute_name_qm = Nil;
    badly_formed_attribute_name_qm = Nil;
    problems_qm = Nil;
    g2_array_length_problems_qm = Nil;
    if ( !TRUEP(translation) || EQ(translation,Qnone))
	fixed_translation = Nil;
    else if (EQ(CAR(translation),Qsc)) {
	override = Nil;
	temp = copy_for_phrase(translation);
	ab_loop_list_ = CDR(temp);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = phrase_cons(override,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	fixed_translation = ab_loopvar_;
	goto end_1;
	fixed_translation = Qnil;
      end_1:;
    }
    else
	fixed_translation = phrase_cons(copy_for_phrase(translation),Nil);
    foundation_class_qm = direct_superiors_are_defined_qm ? 
	    most_refined_foundation_class_of_direct_superiors(1,
	    direct_superior_classes_qm) : Nil;
    system_slot_override_but_no_foundation_class_qm = Nil;
    annotation = Nil;
    initial_value_incompatible_qm = Nil;
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      temp_1 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
      temp_1 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      override = Nil;
	      ab_loop_list_ = fixed_translation;
	      slot_name_or_alias = Nil;
	      slot_name_is_qualified_qm = Nil;
	      class_check_or_user_defined_qm = Nil;
	      override_on_user_defined_slot_qm = Nil;
	      alias_or_slot_name_qm = Nil;
	      slot_name_qm = Nil;
	      class_check_bad_qm = Nil;
	      foundation_class_slot_description = Nil;
	      slot_defining_class_qm = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      override = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      slot_name_or_alias = CAR(override);
	      slot_name_is_qualified_qm = CONSP(slot_name_or_alias) ? T : Nil;
	      class_check_or_user_defined_qm = THIRD(override);
	      override_on_user_defined_slot_qm = 
		      EQ(class_check_or_user_defined_qm,Quser_defined) ? T 
		      : Nil;
	      alias_or_slot_name_qm =  
		      !TRUEP(override_on_user_defined_slot_qm) ? 
		      map_system_slot_name_to_alias(slot_name_or_alias,
		      definition) : Nil;
	      slot_name_qm = override_on_user_defined_slot_qm ? 
		      slot_name_or_alias : 
		      map_alias_to_system_slot_name(alias_or_slot_name_qm,
		      definition);
	      if (class_check_or_user_defined_qm && foundation_class_qm && 
		       !EQ(class_check_or_user_defined_qm,Quser_defined)) {
		  if (EQ(slot_name_or_alias,Qinitial_value))
		      class_check_bad_qm =  !EQ(foundation_class_qm,
			      class_check_or_user_defined_qm) ? T : Nil;
		  else {
		      gensymed_symbol = 
			      lookup_global_or_kb_specific_property_value(foundation_class_qm,
			      Class_description_gkbprop);
		      class_check_bad_qm =  !(gensymed_symbol ? 
			      TRUEP(memq_function(class_check_or_user_defined_qm,
			      ISVREF(gensymed_symbol,(SI_Long)2L))) : 
			      TRUEP(Nil)) ? T : Nil;
		  }
	      }
	      else
		  class_check_bad_qm = Nil;
	      foundation_class_slot_description = 
		      slot_description_from_superior_class(slot_name_qm,
		      definition);
	      slot_defining_class_qm = foundation_class_slot_description ? 
		      ISVREF(foundation_class_slot_description,
		      (SI_Long)3L) : Nil;
	      if (EQ(class_check_or_user_defined_qm,Quser_defined)) {
		  name_denotation = FIRST(override);
		  unqualified_name = CONSP(name_denotation) ? 
			  M_CAR(M_CDR(M_CDR(name_denotation))) : 
			  name_denotation;
		  if (SYMBOLP(unqualified_name)) {
		      if (reserved_system_slot_name_p(definition,
			      unqualified_name)) {
			  bad_attribute_name_qm = unqualified_name;
			  goto end_loop_1;
		      }
		  }
		  else {
		      badly_formed_attribute_name_qm = unqualified_name;
		      goto end_loop_1;
		  }
	      }
	      else if ( !TRUEP(foundation_class_qm)) {
		  system_slot_override_but_no_foundation_class_qm = 
			  slot_name_or_alias;
		  problems_qm = T;
	      }
	      else if (EQ(slot_name_qm,Qframe_flags)) {
		  flags = SECOND(override);
		  if (EQ(class_check_or_user_defined_qm,Qvariable)) {
		      temp = FIRST(flags);
		      gensymed_symbol_1 = EQ(temp,Qforward_chain_flag) ? 
			      (SI_Long)2L : (SI_Long)0L;
		      gensymed_symbol_2 = EQ(SECOND(flags),
			      Qalways_forward_chain_if_possible_flag) ? 
			      (SI_Long)32L : (SI_Long)0L;
		      temp = THIRD(flags);
		      if (EQ(temp,Qpassive_flag))
			  gensymed_symbol_3 = (SI_Long)16L + (SI_Long)32768L;
		      else if (EQ(temp,Qdont_backward_chain_flag))
			  gensymed_symbol_3 = (SI_Long)32768L;
		      else if (EQ(temp,Qdepth_first_flag))
			  gensymed_symbol_3 = (SI_Long)8L;
		      else
			  gensymed_symbol_3 = (SI_Long)0L;
		      temp = FOURTH(flags);
		      gensymed_symbol_4 = EQ(temp,
			      Qcache_data_for_explanation_flag) ? 
			      (SI_Long)1048576L : (SI_Long)0L;
		      temp_1 = gensymed_symbol_1 + gensymed_symbol_2 + 
			      gensymed_symbol_3 + gensymed_symbol_4;
		  }
		  else {
		      gensymed_symbol_1 = (SI_Long)16L;
		      gensymed_symbol_2 = (SI_Long)32768L;
		      temp = FIRST(flags);
		      gensymed_symbol_3 = EQ(temp,Qforward_chain_flag) ? 
			      (SI_Long)2L : (SI_Long)0L;
		      gensymed_symbol_4 = EQ(SECOND(flags),
			      Qalways_forward_chain_if_possible_flag) ? 
			      (SI_Long)32L : (SI_Long)0L;
		      temp = THIRD(flags);
		      gensymed_symbol_5 = EQ(temp,
			      Qcache_data_for_explanation_flag) ? 
			      (SI_Long)1048576L : (SI_Long)0L;
		      temp_1 = gensymed_symbol_1 + gensymed_symbol_2 + 
			      gensymed_symbol_3 + gensymed_symbol_4 + 
			      gensymed_symbol_5;
		  }
		  M_SECOND(override) = FIX(temp_1);
	      }
	      else if (EQ(slot_name_qm,
		      Qinitial_value_of_variable_or_parameter)) {
		  defining_class = foundation_class_slot_description ? 
			  ISVREF(foundation_class_slot_description,
			  (SI_Long)3L) : THIRD(override);
		  grammar_category_qm = 
			  get_grammar_category_for_default_override(slot_name_qm,
			  defining_class,T);
		  temp = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
			  Qslot_value_compiler);
		  compiled_value = funcall(7,temp,SECOND(override),Nil,
			  slot_name_qm,defining_class,Nil,Nil);
		  if ( 
			  !TRUEP(check_initial_value_of_variable_or_parameter(compiled_value,
			  fixed_translation,definition))) {
		      tformat(1,string_constant_34);
		      slot_value_writer_qm = 
			      getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
			      Qslot_value_writer);
		      if (slot_value_writer_qm) {
			  write_symbols_in_lower_case_qm = T;
			  write_symbols_parsably_qm = T;
			  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
				  1);
			    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
				    0);
			      inline_funcall_2(slot_value_writer_qm,
				      compiled_value,definition);
			    POP_SPECIAL();
			  POP_SPECIAL();
		      }
		      else
			  twrite(string_constant_25);
		      tformat(2,string_constant_35,
			      get_data_type_of_variable_or_parameter_from_frame(2,
			      definition,fixed_translation));
		      problems_qm = T;
		  }
		  M_SECOND(override) = compiled_value;
	      }
	      else if (EQ(slot_name_qm,Qg2_array_length)) {
		  result = compile_g2_array_length_for_slot(3,
			  SECOND(override),Nil,Nil);
		  MVS_2(result,compilation,error_text_qm);
		  if (EQ(compilation,Bad_phrase)) {
		      g2_array_length_problems_qm = T;
		      temp = error_text_qm;
		      if (temp);
		      else
			  temp = string_constant_36;
		      twrite_general_string(temp);
		  }
		  else
		      M_SECOND(override) = compilation;
	      }
	      else if (EQ(slot_name_qm,Qg2_array_element_type)) {
		  element_type = SECOND(override);
		  if (type_specification_for_user_or_datum_type(element_type)) 
			      {
		      tformat(2,string_constant_37,element_type);
		      problems_qm = T;
		  }
	      }
	      else if (EQ(slot_name_qm,Qlist_type)) {
		  element_type = SECOND(override);
		  if (type_specification_for_user_or_datum_type(element_type)) 
			      {
		      tformat(2,string_constant_37,element_type);
		      problems_qm = T;
		  }
	      }
	      else {
		  temp = override;
		  temp_2 = slot_name_qm;
		  temp_3 = slot_defining_class_qm;
		  if (temp_3);
		  else
		      temp_3 = THIRD(override);
		  if (compile_default_override(temp,temp_2,temp_3,
			  definition,T))
		      problems_qm = T;
	      }
	      if ( !EQ(class_check_or_user_defined_qm,Quser_defined) && ( 
		      !TRUEP(foundation_class_slot_description) || 
		      class_check_bad_qm)) {
		  if ( !TRUEP(problems_qm))
		      tformat(2,string_constant_41,foundation_class_qm);
		  if (problems_qm)
		      twrite(string_constant_27);
		  tformat(2,string_constant_39,alias_or_slot_name_qm);
		  if (class_check_bad_qm)
		      tformat(2,string_constant_42,
			      class_check_or_user_defined_qm);
		  problems_qm = T;
	      }
	      goto next_loop_1;
	    end_loop_1:;
	      annotation = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (bad_attribute_name_qm)
	return bad_attribute_name(bad_attribute_name_qm);
    else if (badly_formed_attribute_name_qm)
	return badly_formed_attribute_name();
    else if (problems_qm && system_slot_override_but_no_foundation_class_qm)
	return system_slot_override_but_no_foundation_class(system_slot_override_but_no_foundation_class_qm);
    else if (problems_qm || g2_array_length_problems_qm)
	return VALUES_2(Bad_phrase,annotation);
    else if (initial_value_incompatible_qm) {
	reclaim_text_string(annotation);
	temp_2 = Bad_phrase;
	temp = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)55L));
	return VALUES_2(temp_2,temp);
    }
    else {
	reclaim_text_string(annotation);
	return VALUES_1(fixed_translation);
    }
}

/* COMPILE-DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS-FOR-SLOT */
Object compile_default_overrides_for_connection_definitions_for_slot varargs_1(int, n)
{
    Object translation, definition, gensymed_symbol;
    Object fixed_translation, override, temp, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, bad_attribute_name_qm;
    Object badly_formed_attribute_name_qm, slot_name_or_alias;
    Object slot_name_is_qualified_qm, unqualified_name, slot_description_qm;
    Object defining_class_qm, unaliased_slot_name_qm, name_denotation;
    Declare_varargs_nonrelocating;

    x_note_fn_call(201,26);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(translation) || EQ(translation,Qnone))
	fixed_translation = Nil;
    else if (EQ(CAR(translation),Qsc)) {
	override = Nil;
	temp = copy_for_phrase(translation);
	ab_loop_list_ = CDR(temp);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = phrase_cons(override,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	fixed_translation = ab_loopvar_;
	goto end_1;
	fixed_translation = Qnil;
      end_1:;
    }
    else
	fixed_translation = phrase_cons(copy_for_phrase(translation),Nil);
    bad_attribute_name_qm = Nil;
    badly_formed_attribute_name_qm = Nil;
    override = Nil;
    ab_loop_list_ = fixed_translation;
    slot_name_or_alias = Nil;
    slot_name_is_qualified_qm = Nil;
    unqualified_name = Nil;
    slot_description_qm = Nil;
    defining_class_qm = Nil;
    unaliased_slot_name_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name_or_alias = CAR(override);
    slot_name_is_qualified_qm = CONSP(slot_name_or_alias) ? T : Nil;
    name_denotation = FIRST(override);
    unqualified_name = CONSP(name_denotation) ? 
	    M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation;
    slot_description_qm =  !TRUEP(slot_name_is_qualified_qm) ? 
	    possibly_aliased_slot_description_from_superior_class(slot_name_or_alias,
	    definition) : Nil;
    defining_class_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)3L) : Nil;
    unaliased_slot_name_qm = slot_description_qm ? 
	    ISVREF(slot_description_qm,(SI_Long)2L) : Nil;
    if (SYMBOLP(unqualified_name)) {
	if (reserved_system_slot_name_p(definition,unqualified_name)) {
	    bad_attribute_name_qm = unqualified_name;
	    goto end_loop_1;
	}
	if (defining_class_qm)
	    compile_default_override(override,unaliased_slot_name_qm,
		    defining_class_qm,definition,Nil);
    }
    else {
	badly_formed_attribute_name_qm = unqualified_name;
	goto end_loop_1;
    }
    goto next_loop_1;
  end_loop_1:;
    if (bad_attribute_name_qm)
	return bad_attribute_name(bad_attribute_name_qm);
    else if (badly_formed_attribute_name_qm)
	return badly_formed_attribute_name();
    else
	return VALUES_1(fixed_translation);
}

/* COMPILE-DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS-FOR-SLOT */
Object compile_default_overrides_for_message_definitions_for_slot varargs_1(int, n)
{
    Object translation, definition, gensymed_symbol;
    Object fixed_translation, override, temp, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, bad_attribute_name_qm;
    Object badly_formed_attribute_name_qm, slot_name_or_alias;
    Object slot_name_is_qualified_qm, unqualified_name, slot_description_qm;
    Object defining_class_qm, unaliased_slot_name_qm, name_denotation;
    Declare_varargs_nonrelocating;

    x_note_fn_call(201,27);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(translation) || EQ(translation,Qnone))
	fixed_translation = Nil;
    else if (EQ(CAR(translation),Qsc)) {
	override = Nil;
	temp = copy_for_phrase(translation);
	ab_loop_list_ = CDR(temp);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = phrase_cons(override,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	fixed_translation = ab_loopvar_;
	goto end_1;
	fixed_translation = Qnil;
      end_1:;
    }
    else
	fixed_translation = phrase_cons(copy_for_phrase(translation),Nil);
    bad_attribute_name_qm = Nil;
    badly_formed_attribute_name_qm = Nil;
    override = Nil;
    ab_loop_list_ = fixed_translation;
    slot_name_or_alias = Nil;
    slot_name_is_qualified_qm = Nil;
    unqualified_name = Nil;
    slot_description_qm = Nil;
    defining_class_qm = Nil;
    unaliased_slot_name_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name_or_alias = CAR(override);
    slot_name_is_qualified_qm = CONSP(slot_name_or_alias) ? T : Nil;
    name_denotation = FIRST(override);
    unqualified_name = CONSP(name_denotation) ? 
	    M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation;
    slot_description_qm =  !TRUEP(slot_name_is_qualified_qm) ? 
	    possibly_aliased_slot_description_from_superior_class(slot_name_or_alias,
	    definition) : Nil;
    defining_class_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)3L) : Nil;
    unaliased_slot_name_qm = slot_description_qm ? 
	    ISVREF(slot_description_qm,(SI_Long)2L) : Nil;
    if (SYMBOLP(unqualified_name)) {
	if (reserved_system_slot_name_p(definition,unqualified_name)) {
	    bad_attribute_name_qm = unqualified_name;
	    goto end_loop_1;
	}
	if (defining_class_qm)
	    compile_default_override(override,unaliased_slot_name_qm,
		    defining_class_qm,definition,Nil);
    }
    else {
	badly_formed_attribute_name_qm = unqualified_name;
	goto end_loop_1;
    }
    goto next_loop_1;
  end_loop_1:;
    if (bad_attribute_name_qm)
	return bad_attribute_name(bad_attribute_name_qm);
    else if (badly_formed_attribute_name_qm)
	return badly_formed_attribute_name();
    else
	return VALUES_1(fixed_translation);
}

static Object Qdata_type_of_variable_or_parameter;  /* data-type-of-variable-or-parameter */

/* DATA-TYPE-FROM-CLASS */
Object data_type_from_class(class_1)
    Object class_1;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(201,28);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_1;
    key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
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
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_1:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_1;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	    svref_arg_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_2) = head;
	M_CDR(gensymed_symbol_2) = tail;
	inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    skip_list = CDR(global_properties);
    key_value = Current_kb_specific_property_list_property_name;
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
  next_loop_3:
    if (level < ab_loop_bind_)
	goto end_loop_3;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_4:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_5:
    if ( !TRUEP(marked))
	goto end_loop_4;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_5;
  end_loop_4:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_2;
    goto next_loop_4;
  end_loop_5:
  end_2:
    level = level - (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	skip_list = CDR(kb_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_6:
	if (level < ab_loop_bind_)
	    goto end_loop_6;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_7:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_8:
	if ( !TRUEP(marked))
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_8;
      end_loop_7:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_3;
	goto next_loop_7;
      end_loop_8:
      end_3:
	level = level - (SI_Long)1L;
	goto next_loop_6;
      end_loop_6:;
	kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_10:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_11:
	if ( !TRUEP(marked))
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_11;
      end_loop_10:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_4;
	goto next_loop_10;
      end_loop_11:
      end_4:
	level = level - (SI_Long)1L;
	goto next_loop_9;
      end_loop_9:;
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_4 = (SI_Long)1L;
	    gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	    temp_2 = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return VALUES_1(ISVREF(get_slot_description_of_class_description_function(Qdata_type_of_variable_or_parameter,
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop),Nil),(SI_Long)6L));
    else
	return VALUES_1(Nil);
}

/* WRITE-DEFAULT-OVERRIDES */
Object write_default_overrides(value,frame)
    Object value, frame;
{
    Object override, rest_qm, ab_loop_list_;

    x_note_fn_call(201,29);
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else {
	override = Nil;
	rest_qm = Nil;
	ab_loop_list_ = value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	override = CAR(ab_loop_list_);
	rest_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_default_override(override,frame);
	if (rest_qm)
	    tformat(1,string_constant_1);
	goto next_loop;
      end_loop:;
	if (CDR(value)) {
	    Leave_text_representation_as_a_single_line_qm = Nil;
	    return VALUES_1(Leave_text_representation_as_a_single_line_qm);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* WRITE-DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS-FROM-SLOT */
Object write_default_overrides_for_class_definitions_from_slot(value,frame)
    Object value, frame;
{
    x_note_fn_call(201,30);
    return write_default_overrides(value,frame);
}

/* WRITE-DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS-FROM-SLOT */
Object write_default_overrides_for_object_definitions_from_slot(value,frame)
    Object value, frame;
{
    x_note_fn_call(201,31);
    return write_default_overrides(value,frame);
}

/* WRITE-DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS-FROM-SLOT */
Object write_default_overrides_for_connection_definitions_from_slot(value,
	    frame)
    Object value, frame;
{
    x_note_fn_call(201,32);
    return write_default_overrides(value,frame);
}

/* WRITE-DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS-FROM-SLOT */
Object write_default_overrides_for_message_definitions_from_slot(value,frame)
    Object value, frame;
{
    x_note_fn_call(201,33);
    return write_default_overrides(value,frame);
}

static Object Qclass_definition;   /* class-definition */

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object array_constant_3;    /* # */

static Object Qiteration_state;    /* iteration-state */

static Object array_constant_4;    /* # */

static Object string_constant_43;  /* "~( initially is ~a~)" */

static Object Qquantitative_variable;  /* quantitative-variable */

static Object Qquantitative_parameter;  /* quantitative-parameter */

static Object Qsensor;             /* sensor */

static Object string_constant_44;  /* "data-type for ~(~a~): " */

static Object Qvalidity_interval;  /* validity-interval */

static Object string_constant_45;  /* "validity-interval: " */

static Object Qseconds;            /* seconds */

static Object Qsimulation_details;  /* simulation-details */

static Object Qmake_simulation_subtable_with_specific_class_and_install;  /* make-simulation-subtable-with-specific-class-and-install */

static Object string_constant_46;  /* "supply-simulation-subtable: ~(~a~)" */

static Object string_constant_47;  /* "supply-simulation-subtable: simulation-subtable" */

static Object Qattribute_displays_for_class;  /* attribute-displays-for-class */

static Object string_constant_48;  /* "attribute-displays: " */

static Object Qcross_section_pattern_for_class;  /* cross-section-pattern-for-class */

static Object string_constant_49;  /* "cross-section-pattern: " */

static Object Qinsert_duplicate_elements_qm;  /* insert-duplicate-elements? */

static Object string_constant_50;  /* "allow-duplicate-elements-for-g2-list: ~a" */

static Object string_constant_51;  /* "yes" */

static Object string_constant_52;  /* "no" */

static Object Qparameter;          /* parameter */

static Object string_constant_53;  /* "options-for-~(~a~): " */

static Object Qvariable_or_parameter_history_specification_qm;  /* variable-or-parameter-history-specification? */

static Object Qhistory_specification_for_simulation_subtables_qm;  /* history-specification-for-simulation-subtables? */

static Object string_constant_54;  /* "history-keeping-spec for " */

static Object string_constant_55;  /* "simulation-subtable: " */

static Object string_constant_56;  /* "variable-or-parameter: " */

static Object Quser_menu_choice_priority;  /* user-menu-choice-priority */

static Object Qaction_button_priority;  /* action-button-priority */

static Object string_constant_57;  /* "action-priority for " */

static Object string_constant_58;  /* "action-button: " */

static Object string_constant_59;  /* "user-menu-choice: " */

static Object list_constant_3;     /* # */

static Object Qon_value_for_check_box;  /* on-value-for-check-box */

static Object string_constant_60;  /* "on-value for check-box: " */

static Object Qvalue_for_radio_button;  /* value-for-radio-button */

static Object string_constant_61;  /* "on-value for radio-button: " */

static Object Qoff_value_for_check_box;  /* off-value-for-check-box */

static Object string_constant_62;  /* "off-value for check-box: " */

static Object string_constant_63;  /* "~(~A~): " */

static Object string_constant_64;  /* "initial-value for ~(~a~): " */

static Object list_constant_4;     /* # */

static Object Qg2_array_initial_values;  /* g2-array-initial-values */

static Object string_constant_65;  /* "initial-values for ~(~a~): " */

static Object Qquantity_array;     /* quantity-array */

static Object Qfloat_array;        /* float-array */

static Object Qinteger_array;      /* integer-array */

static Object Qsymbol_array;       /* symbol-array */

static Object Qtext_array;         /* text-array */

static Object Qtruth_value_array;  /* truth-value-array */

static Object Qitem_array;         /* item-array */

static Object Qvalue_array;        /* value-array */

static Object Qg2_array;           /* g2-array */

static Object string_constant_66;  /* "element-type for item-list: ~(~a~)" */

static Object string_constant_67;  /* "element-type for item-array: ~(~a~)" */

static Object string_constant_68;  /* "array-length for g2-array: ~(~a~)" */

static Object Qstubs_for_class;    /* stubs-for-class */

static Object string_constant_69;  /* "stubs: " */

/* WRITE-DEFAULT-OVERRIDE */
Object write_default_override(override,frame)
    Object override, frame;
{
    Object unaliased_slot_name, user_defined_p, class_of_override;
    Object grammar_category_qm, override_value, aliased_slot_name;
    Object class_inheritance_path, initial_value, slot_name;
    Object write_symbols_parsably_qm, temp, funcall_form, gensymed_symbol;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object entry_hash, initial_type, write_strings_parsably_qm;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm, class_1;
    Object car_1, cdr_1, data_type_qm, array_class;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char class_definition_p, temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(201,34);
    result = decode_default_override(3,override,frame,T);
    MVS_4(result,unaliased_slot_name,user_defined_p,class_of_override,
	    grammar_category_qm);
    override_value = SECOND(override);
    class_definition_p = EQ(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L),
	    Qclass_definition);
    if ( !TRUEP(user_defined_p)) {
	aliased_slot_name = 
		get_alias_for_slot_name_if_any(unaliased_slot_name,
		class_of_override);
	if (aliased_slot_name);
	else
	    aliased_slot_name = unaliased_slot_name;
    }
    else
	aliased_slot_name = Nil;
    class_inheritance_path = get_lookup_slot_value_given_default(frame,
	    Qclass_inheritance_path_of_definition,Nil);
    if (user_defined_p) {
	initial_value = CAR(override_value);
	slot_name = unaliased_slot_name;
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		0);
	  if (CONSP(slot_name) && EQ(M_CAR(slot_name),Qclass_qualified_name)) {
	      twrite_symbol(1,CONSP(slot_name) ? M_CAR(M_CDR(slot_name)) : 
		      Nil);
	      twrite_beginning_of_wide_string(array_constant_3,
		      FIX((SI_Long)2L));
	      twrite_symbol(1,CONSP(slot_name) ? 
		      M_CAR(M_CDR(M_CDR(slot_name))) : slot_name);
	  }
	  else
	      twrite_symbol(1,slot_name);
	POP_SPECIAL();
	if ( ! !TRUEP(initial_value)) {
	    if (CONSP(override_value)) {
		temp = M_CAR(override_value);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(M_CAR(M_CAR(override_value)),Kfuncall) : 
		    TRUEP(Nil)) {
		funcall_form = M_CAR(override_value);
		twrite(EQ(SECOND(funcall_form),Qinstantiate_variable) ? 
			string_constant_13 : string_constant_14);
		return write_symbol_with_a_or_an(1,THIRD(funcall_form));
	    }
	    else {
		gensymed_symbol = override_value;
		temp_1 = FIXNUMP(gensymed_symbol);
		if (temp_1);
		else
		    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
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
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
				& IFIX(Most_positive_fixnum);
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_1:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
		      next_loop_2:
			if ( !TRUEP(marked))
			    goto end_loop_1;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
			goto next_loop_2;
		      end_loop_1:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    twrite_beginning_of_wide_string(array_constant_4,
			    FIX((SI_Long)14L));
		    return write_evaluation_value(1,override_value);
		}
		else {
		    initial_type = CADR(override_value);
		    if (EQ(initial_type,Qsymbol))
			return tformat(2,string_constant_43,initial_value);
		    else if (EQ(initial_type,Qtext)) {
			twrite(string_constant_15);
			write_strings_parsably_qm = T;
			PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
				0);
			  result = twrite_general_string(initial_value);
			POP_SPECIAL();
			return result;
		    }
		    else {
			twrite(string_constant_15);
			return print_constant(2,initial_value,initial_type);
		    }
		}
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(unaliased_slot_name,Qdata_type_of_variable_or_parameter)) {
	if (class_definition_p) {
	    if (memq_function(Qquantitative_variable,class_inheritance_path))
		temp = Qquantitative_variable;
	    else if (memq_function(Qquantitative_parameter,
		    class_inheritance_path))
		temp = Qquantitative_parameter;
	    else
		temp = Qsensor;
	    tformat(2,string_constant_44,temp);
	}
	else
	    tformat(2,string_constant_44,THIRD(override));
	slot_value_writer_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
		Qslot_value_writer);
	if (slot_value_writer_qm) {
	    write_symbols_in_lower_case_qm = T;
	    write_symbols_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		      0);
		result = VALUES_1(inline_funcall_2(slot_value_writer_qm,
			override_value,Nil));
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return twrite(string_constant_25);
    }
    else if (EQ(unaliased_slot_name,Qvalidity_interval)) {
	twrite(string_constant_45);
	if (NUMBERP(override_value))
	    return print_constant(2,override_value,Qseconds);
	else
	    return twrite_symbol(1,override_value);
    }
    else if (EQ(unaliased_slot_name,Qsimulation_details)) {
	if (EQ(SECOND(override_value),
		Qmake_simulation_subtable_with_specific_class_and_install))
	    return tformat(2,string_constant_46,THIRD(override_value));
	else
	    return twrite(string_constant_47);
    }
    else if (EQ(unaliased_slot_name,Qattribute_displays_for_class)) {
	twrite(string_constant_48);
	return write_attribute_displays_for_class(override_value);
    }
    else if (EQ(unaliased_slot_name,Qcross_section_pattern_for_class)) {
	twrite(string_constant_49);
	return write_cross_section_pattern_from_slot(override_value,frame);
    }
    else if (EQ(unaliased_slot_name,Qinsert_duplicate_elements_qm))
	return tformat(2,string_constant_50,override_value ? 
		string_constant_51 : string_constant_52);
    else if (EQ(unaliased_slot_name,Qframe_flags)) {
	class_1 = memq_function(Qvariable,class_inheritance_path) ? 
		Qvariable : Qparameter;
	tformat(2,string_constant_53,class_1);
	if (EQ(class_1,Qvariable))
	    return write_variable_frame_flags_from_slot(override_value,Nil);
	else if (EQ(class_1,Qparameter))
	    return write_parameter_frame_flags_from_slot(override_value,Nil);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(unaliased_slot_name,
	    Qvariable_or_parameter_history_specification_qm) || 
	    EQ(unaliased_slot_name,
	    Qhistory_specification_for_simulation_subtables_qm)) {
	twrite(string_constant_54);
	if (EQ(unaliased_slot_name,
		Qhistory_specification_for_simulation_subtables_qm))
	    twrite(string_constant_55);
	else
	    twrite(string_constant_56);
	return write_history_specification_from_slot(override_value,Nil);
    }
    else if (EQ(unaliased_slot_name,Quser_menu_choice_priority) || 
	    EQ(unaliased_slot_name,Qaction_button_priority)) {
	twrite(string_constant_57);
	if (EQ(unaliased_slot_name,Qaction_button_priority))
	    twrite(string_constant_58);
	else
	    twrite(string_constant_59);
	slot_value_writer_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
		Qslot_value_writer);
	if (slot_value_writer_qm) {
	    write_symbols_in_lower_case_qm = T;
	    write_symbols_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		      0);
		result = VALUES_1(inline_funcall_2(slot_value_writer_qm,
			override_value,Nil));
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return twrite(string_constant_25);
    }
    else if (member_eql(unaliased_slot_name,list_constant_3)) {
	if (EQ(unaliased_slot_name,Qon_value_for_check_box))
	    twrite(string_constant_60);
	else if (EQ(unaliased_slot_name,Qvalue_for_radio_button))
	    twrite(string_constant_61);
	else if (EQ(unaliased_slot_name,Qoff_value_for_check_box))
	    twrite(string_constant_62);
	else
	    tformat(2,string_constant_63,aliased_slot_name);
	return write_attribute_from_slot(override_value,Nil);
    }
    else if (EQ(unaliased_slot_name,Qinitial_value_of_variable_or_parameter)) {
	tformat(2,string_constant_64,THIRD(override));
	if (CONSP(override_value)) {
	    car_1 = M_CAR(override_value);
	    cdr_1 = M_CDR(override_value);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else
	    temp_1 =  !TRUEP(slot_value_number_p(override_value));
	if (temp_1)
	    return write_attribute(override_value);
	else {
	    if (frame) {
		temp = assq_function(Qdata_type_of_variable_or_parameter,
			ISVREF(frame,(SI_Long)27L));
		data_type_qm = SECOND(temp);
	    }
	    else
		data_type_qm = Nil;
	    if (data_type_qm &&  !TRUEP(memq_function(data_type_qm,
		    list_constant_4)))
		return print_constant(2,override_value,data_type_qm);
	    else
		return write_attribute_from_slot(override_value,Nil);
	}
    }
    else if (EQ(unaliased_slot_name,Qg2_array_initial_values)) {
	array_class = THIRD(override);
	tformat(2,string_constant_65,array_class);
	if ( !TRUEP(override_value))
	    return twrite_beginning_of_wide_string(array_constant,
		    FIX((SI_Long)4L));
	else if (EQ(array_class,Qquantity_array))
	    return print_constant_list(override_value,Qnumber);
	else if (EQ(array_class,Qfloat_array))
	    return print_constant_list(override_value,Qfloat);
	else if (EQ(array_class,Qinteger_array))
	    return print_constant_list(override_value,Qinteger);
	else if (EQ(array_class,Qsymbol_array))
	    return write_symbol_list_from_slot(override_value,frame);
	else if (EQ(array_class,Qtext_array))
	    return print_constant_list(override_value,Qtext);
	else if (EQ(array_class,Qtruth_value_array))
	    return print_constant_list(override_value,Qtruth_value);
	else if (EQ(array_class,Qitem_array))
	    return print_designation_list(override_value);
	else if (EQ(array_class,Qvalue_array))
	    return print_datum_constant_list(override_value);
	else if (EQ(array_class,Qg2_array))
	    return print_item_and_datum_constant_list(2,override_value,frame);
	else
	    return twrite_beginning_of_wide_string(array_constant,
		    FIX((SI_Long)4L));
    }
    else if (EQ(unaliased_slot_name,Qlist_type))
	return tformat(2,string_constant_66,override_value);
    else if (EQ(unaliased_slot_name,Qg2_array_element_type))
	return tformat(2,string_constant_67,override_value);
    else if (EQ(unaliased_slot_name,Qg2_array_length))
	return tformat(2,string_constant_68,override_value);
    else if (EQ(unaliased_slot_name,Qstubs_for_class)) {
	twrite(string_constant_69);
	return write_connections_qm_from_slot(override_value,frame);
    }
    else {
	tformat(2,string_constant_63,aliased_slot_name);
	slot_value_writer_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
		Qslot_value_writer);
	if (slot_value_writer_qm) {
	    write_symbols_in_lower_case_qm = T;
	    write_symbols_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		      0);
		result = VALUES_1(inline_funcall_2(slot_value_writer_qm,
			override_value,Nil));
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return twrite(string_constant_25);
    }
}

/* WRITE-SIMULATOR-CLASS-FROM-SLOT */
Object write_simulator_class_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(201,35);
    return twrite_symbol(1,value);
}

/* TRANSFORM-DATE-PHRASE-AND-TIME-OF-DAY-INTO-FRAME-EDIT-TIMESTAMP */
Object transform_date_phrase_and_time_of_day_into_frame_edit_timestamp(date_and_time_of_day_as_seconds_since_midnight)
    Object date_and_time_of_day_as_seconds_since_midnight;
{
    Object universal_date, time_of_day_as_seconds_since_midnight, day, month;
    Object year, seconds, minutes, hours, temp;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(201,36);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    universal_date = 
		    FIRST(date_and_time_of_day_as_seconds_since_midnight);
	    time_of_day_as_seconds_since_midnight = 
		    SECOND(date_and_time_of_day_as_seconds_since_midnight);
	    result = decode_universal_date(universal_date);
	    MVS_3(result,day,month,year);
	    result = decode_normalized_time_of_day(time_of_day_as_seconds_since_midnight);
	    MVS_3(result,seconds,minutes,hours);
	    unix_time = g2ext_get_encoded_unix_time(IFIX(seconds),
		    IFIX(minutes),IFIX(hours),IFIX(day),IFIX(month),
		    IFIX(year));
	    arg = unix_time;
	    arg_1 = -1.0;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		temp = encode_unix_time_after_failure(seconds,minutes,
			hours,day,month,year);
		gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    }
	    else
		gensymed_symbol = unix_time;
	    gensymed_symbol_1 = (double)((SI_Long)60L * 
		    IFIX(Global_daylight_saving_time_adjustment));
	    result = finish_edit_timestamp_transform(DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol 
		    - gensymed_symbol_1));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    POP_LOCAL_ALLOCATION(1,1);
    return result;
}

/* CONVERT-LOCAL-DATE-TO-EDIT-TIMESTAMP */
Object convert_local_date_to_edit_timestamp(universal_date)
    Object universal_date;
{
    Object date, month, year, temp;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(201,37);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result = decode_universal_date(universal_date);
	    MVS_3(result,date,month,year);
	    unix_time = g2ext_get_encoded_unix_time((SI_Long)0L,
		    (SI_Long)0L,(SI_Long)0L,IFIX(date),IFIX(month),IFIX(year));
	    arg = unix_time;
	    arg_1 = -1.0;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		temp = encode_unix_time_after_failure(FIX((SI_Long)0L),
			FIX((SI_Long)0L),FIX((SI_Long)0L),date,month,year);
		gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    }
	    else
		gensymed_symbol = unix_time;
	    gensymed_symbol_1 = (double)((SI_Long)60L * 
		    IFIX(Global_daylight_saving_time_adjustment));
	    unix_time = gensymed_symbol - gensymed_symbol_1;
	    result = finish_edit_timestamp_transform(DOUBLE_TO_DOUBLE_FLOAT(unix_time));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    POP_LOCAL_ALLOCATION(1,1);
    return result;
}

static Object string_constant_70;  /* "Bad date: can't go back that far in time" */

static Object string_constant_71;  /* "Bad date: can't go forward that far in time" */

/* FINISH-EDIT-TIMESTAMP-TRANSFORM */
Object finish_edit_timestamp_transform(unix_time)
    Object unix_time;
{
    Object minutes, seconds;
    double arg, arg_1, temp, temp_1;
    Object result;

    x_note_fn_call(201,38);
    arg = DOUBLE_FLOAT_TO_DOUBLE(unix_time);
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Time_of_frame_edit_base_time);
    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	return VALUES_2(Bad_phrase,string_constant_70);
    else {
	arg = DOUBLE_FLOAT_TO_DOUBLE(unix_time);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Time_of_last_allowable_frame_edit_time);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    return VALUES_2(Bad_phrase,string_constant_71);
	else {
	    temp = DOUBLE_FLOAT_TO_DOUBLE(unix_time);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Time_of_frame_edit_base_time);
	    result = lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp - temp_1),
		    FIX((SI_Long)60L));
	    MVS_2(result,minutes,seconds);
	    Text_time_stamp_seconds = seconds;
	    return VALUES_2(minutes,seconds);
	}
    }
}

/* TRANSFORM-DATE-AND-TIME-OF-DAY-INTO-FRAME-EDIT-TIMESTAMP */
Object transform_date_and_time_of_day_into_frame_edit_timestamp(phrase)
    Object phrase;
{
    Object date_as_edit_timestamp, time_of_day_as_seconds_since_midnight;

    x_note_fn_call(201,39);
    date_as_edit_timestamp = FIRST(phrase);
    time_of_day_as_seconds_since_midnight = SECOND(phrase);
    return add(date_as_edit_timestamp,
	    lfloor(time_of_day_as_seconds_since_midnight,FIX((SI_Long)60L)));
}

static Object string_constant_72;  /* "Bad date: " */

static Object string_constant_73;  /* ".  It cannot be earlier than " */

static Object Qcm;                 /* \, */

/* COMPILE-AUTHORS-WITH-TIME-OF-LAST-EDIT?-FOR-SLOT */
Object compile_authors_with_time_of_last_edit_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, date_qm, temp_2, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(201,40);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (ATOM(parse_result))
	return VALUES_1(parse_result);
    else {
	if (CONSP(parse_result)) {
	    temp = CDR(parse_result);
	    temp_1 = ATOM(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    date_qm = CDR(parse_result);
	else {
	    temp = FIRST(parse_result);
	    if (CONSP(temp)) {
		temp = FIRST(parse_result);
		date_qm = CDR(temp);
	    }
	    else
		date_qm = Nil;
	}
	if (date_qm && FIXNUM_LT(date_qm,Frame_edit_base_timestamp)) {
	    temp_2 = Bad_phrase;
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
		      tformat(1,string_constant_72);
		      twrite_frame_edit_timestamp(date_qm);
		      tformat(1,string_constant_73);
		      twrite_frame_edit_timestamp(Frame_edit_base_timestamp);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return VALUES_2(temp_2,temp);
	}
	else {
	    if (CDR(parse_result)) {
		temp = CDR(parse_result);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = SECOND(parse_result);
		temp_1 = EQ(FIRST(temp),Qcm);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = SECOND(parse_result);
		return phrase_cons(FIRST(parse_result),CDR(temp));
	    }
	    else
		return VALUES_1(parse_result);
	}
    }
}

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* WRITE-AUTHORS-WITH-TIME-OF-LAST-EDIT?-FROM-SLOT */
Object write_authors_with_time_of_last_edit_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp, first_author_qm, last_edit_timestamp_qm, author;
    Object ab_loop_list_;
    char temp_1;

    x_note_fn_call(201,41);
    if (CONSP(value)) {
	temp = FIRST(value);
	if (CONSP(temp)) {
	    temp = FIRST(value);
	    first_author_qm = CAR(temp);
	}
	else
	    first_author_qm = FIRST(value);
    }
    else
	first_author_qm = value;
    if (CONSP(value)) {
	temp = FIRST(value);
	if (CONSP(temp)) {
	    temp = FIRST(value);
	    last_edit_timestamp_qm = CDR(temp);
	}
	else {
	    temp = CDR(value);
	    last_edit_timestamp_qm =  !LISTP(temp) ? CDR(value) : Nil;
	}
    }
    else
	last_edit_timestamp_qm = Nil;
    if (first_author_qm || last_edit_timestamp_qm) {
	if (first_author_qm)
	    twrite_symbol(1,first_author_qm);
	if (last_edit_timestamp_qm) {
	    if (first_author_qm)
		twrite_beginning_of_wide_string(array_constant_5,
			FIX((SI_Long)1L));
	    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)1L));
	    twrite_frame_edit_timestamp(last_edit_timestamp_qm);
	    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)1L));
	}
	if (CONSP(value)) {
	    temp = CDR(value);
	    temp_1 = LISTP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    author = Nil;
	    ab_loop_list_ = CDR(value);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    author = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	    twrite_symbol(1,author);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qauthors;            /* authors */

static Object Qtimestamp;          /* timestamp */

static Object Qminutes;            /* minutes */

static Object Qhours;              /* hours */

static Object Qdate;               /* date */

static Object Qmonth;              /* month */

static Object Qyear;               /* year */

static Object string_constant_74;  /* "timestamp out of range" */

static Object string_constant_75;  /* "there cannot be a timestamp without an author" */

static Object string_constant_76;  /* "~NT " */

static Object string_constant_77;  /* "~NV must be one of the following types: ~a" */

/* AUTHORS-WITH-TIME-OF-LAST-EDIT?-EVALUATION-SETTER */
Object authors_with_time_of_last_edit_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, author_sequence;
    Object timestamp_structure, encoded_timestamp_qm, date_phrase;
    Object transform_result, error_qm, convert_result, convert_error_qm;
    Object held_vector, x, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, authors_list, head, tail, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long temp_2, next_index, length_1, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,42);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_6,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_authors_with_time_of_last_edit_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_8)) {
	author_sequence = estructure_slot(evaluation_value,Qauthors,Nil);
	timestamp_structure = estructure_slot(evaluation_value,Qtimestamp,Nil);
	encoded_timestamp_qm = Nil;
	if (timestamp_structure) {
	    gensymed_symbol = timestamp_structure;
	    if ( !((SI_Long)0L <= IFIX(estructure_slot(gensymed_symbol,
		    Qminutes,Nil)) && IFIX(estructure_slot(gensymed_symbol,
		    Qminutes,Nil)) <= (SI_Long)59L && (SI_Long)0L <= 
		    IFIX(estructure_slot(gensymed_symbol,Qhours,Nil)) && 
		    IFIX(estructure_slot(gensymed_symbol,Qhours,Nil)) <= 
		    (SI_Long)23L && (SI_Long)1L <= 
		    IFIX(estructure_slot(gensymed_symbol,Qdate,Nil)) && 
		    IFIX(estructure_slot(gensymed_symbol,Qdate,Nil)) <= 
		    (SI_Long)31L && (SI_Long)1L <= 
		    IFIX(estructure_slot(gensymed_symbol,Qmonth,Nil)) && 
		    IFIX(estructure_slot(gensymed_symbol,Qmonth,Nil)) <= 
		    (SI_Long)12L && (SI_Long)1993L <= 
		    IFIX(estructure_slot(gensymed_symbol,Qyear,Nil)))) {
		temp = Bad_phrase;
		temp_1 = copy_text_string(string_constant_74);
		result = VALUES_2(temp,temp_1);
		goto end_setter;
	    }
	    temp = estructure_slot(gensymed_symbol,Qdate,Nil);
	    temp_1 = FIXNUM_SUB1(estructure_slot(gensymed_symbol,Qmonth,Nil));
	    temp_1 = nth(temp_1,Months_of_the_year);
	    date_phrase = phrase_list_3(temp,temp_1,
		    estructure_slot(gensymed_symbol,Qyear,Nil));
	    result = transform_input_phrase_into_universal_date(date_phrase);
	    MVS_2(result,transform_result,error_qm);
	    if (EQ(transform_result,Bad_phrase)) {
		temp = Bad_phrase;
		temp_1 = copy_text_string(error_qm);
		result = VALUES_2(temp,temp_1);
		goto end_setter;
	    }
	    else {
		result = convert_local_date_to_edit_timestamp(transform_result);
		MVS_2(result,convert_result,convert_error_qm);
		if (EQ(convert_result,Bad_phrase)) {
		    temp = Bad_phrase;
		    temp_1 = copy_text_string(convert_error_qm);
		    result = VALUES_2(temp,temp_1);
		    goto end_setter;
		}
		else {
		    temp_2 = IFIX(estructure_slot(gensymed_symbol,Qhours,
			    Nil)) * (SI_Long)3600L;
		    encoded_timestamp_qm = 
			    transform_date_and_time_of_day_into_frame_edit_timestamp(phrase_list_2(convert_result,
			    FIX(temp_2 + 
			    IFIX(estructure_slot(gensymed_symbol,Qminutes,
			    Nil)) * (SI_Long)60L)));
		}
	    }
	}
	gensymed_symbol = author_sequence;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	x = Nil;
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
	x = validated_elt;
	ab_loopvar__2 = phrase_cons(x,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	authors_list = ab_loopvar_;
	goto end_1;
	authors_list = Qnil;
      end_1:;
	if ( !TRUEP(encoded_timestamp_qm) &&  !TRUEP(CDR(authors_list)))
	    result = VALUES_1(CAR(authors_list));
	else if (encoded_timestamp_qm &&  !TRUEP(authors_list)) {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_75);
	    result = VALUES_2(temp,temp_1);
	}
	else if ( !TRUEP(CDR(authors_list))) {
	    if (encoded_timestamp_qm)
		result = phrase_cons(CAR(authors_list),encoded_timestamp_qm);
	    else
		result = VALUES_1(CAR(authors_list));
	}
	else {
	    head = encoded_timestamp_qm ? phrase_cons(CAR(authors_list),
		    encoded_timestamp_qm) : CAR(authors_list);
	    tail = CDR(authors_list) ? phrase_cons(phrase_cons(Qcm,
		    CDR(authors_list)),Nil) : Nil;
	    if ( !TRUEP(tail))
		result = VALUES_1(head);
	    else
		result = phrase_cons(head,tail);
	}
      end_setter:;
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
		  tformat(2,string_constant_76,list_constant_7);
		  tformat(2,string_constant_76,list_constant_8);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_77,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_authors_with_time_of_last_edit_qm_evaluation_setter:
    return result;
}

static Object Qunknown;            /* unknown */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_structure;       /* structure */

/* AUTHORS-WITH-TIME-OF-LAST-EDIT?-EVALUATION-GETTER */
Object authors_with_time_of_last_edit_qm_evaluation_getter(value,frame,
	    slot_description)
    Object value, frame, slot_description;
{
    Object temp, first_author_qm, last_edit_timestamp_qm, other_authors_qm;
    Object authors_sequence, result_1, temp_2, minutes, hours, date, month;
    Object year, gensymed_symbol, temp_3, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(201,43);
    if (value) {
	if (CONSP(value)) {
	    temp = FIRST(value);
	    if (CONSP(temp)) {
		temp = FIRST(value);
		first_author_qm = CAR(temp);
	    }
	    else
		first_author_qm = FIRST(value);
	}
	else
	    first_author_qm = value;
	if (first_author_qm);
	else
	    first_author_qm = Qunknown;
	if (CONSP(value)) {
	    temp = FIRST(value);
	    if (CONSP(temp)) {
		temp = FIRST(value);
		last_edit_timestamp_qm = CDR(temp);
	    }
	    else {
		temp = CDR(value);
		last_edit_timestamp_qm =  !LISTP(temp) ? CDR(value) : Nil;
	    }
	}
	else
	    last_edit_timestamp_qm = Nil;
	if (CONSP(value)) {
	    temp = CDR(value);
	    temp_1 = LISTP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	other_authors_qm = temp_1 ? CDR(value) : Nil;
	authors_sequence = allocate_evaluation_sequence(other_authors_qm ? 
		eval_cons_1(first_author_qm,
		copy_list_using_eval_conses_1(other_authors_qm)) : 
		eval_cons_1(first_author_qm,Nil));
	result_1 = allocate_evaluation_structure(eval_list_2(Qauthors,
		authors_sequence));
	if (last_edit_timestamp_qm) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		result = gensym_decode_unix_time(add(Time_of_frame_edit_base_time,
			ltimes(last_edit_timestamp_qm,FIX((SI_Long)60L))));
		MVS_6(result,temp,minutes,hours,date,month,year);
		gensymed_symbol = allocate_managed_array(1,
			FIX((SI_Long)10L + (SI_Long)1L));
		gensymed_symbol_1 = (SI_Long)0L;
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset);
		    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
		}
		else {
		    temp_3 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		    ISVREF(temp_3,svref_arg_2) = FIX((SI_Long)1L);
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qyear;
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_3,FIX((SI_Long)1L)) = Qyear;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = year;
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
		    temp_3 = temp_1 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_3;
		}
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = year;
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
		    SVREF(temp_3,FIX((SI_Long)2L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qmonth;
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_3,FIX((SI_Long)3L)) = Qmonth;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = month;
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
		    temp_3 = temp_1 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_3;
		}
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = month;
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
		    SVREF(temp_3,FIX((SI_Long)4L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qdate;
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_3,FIX((SI_Long)5L)) = Qdate;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = date;
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
		    temp_3 = temp_1 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_3;
		}
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = date;
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
		    SVREF(temp_3,FIX((SI_Long)6L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qhours;
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_3,FIX((SI_Long)7L)) = Qhours;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = hours;
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
		    temp_3 = temp_1 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_3;
		}
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = hours;
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
		    SVREF(temp_3,FIX((SI_Long)8L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qminutes;
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_3,FIX((SI_Long)9L)) = Qminutes;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = minutes;
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
		    temp_3 = temp_1 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp_3;
		}
		else {
		    temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = minutes;
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
		    SVREF(temp_3,FIX((SI_Long)10L)) = svref_new_value;
		}
		set_evaluation_structure_slot(result_1,Qtimestamp,
			eval_cons_1(gensymed_symbol,Qab_structure));
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	temp = result_1;
    }
    else
	temp = allocate_evaluation_structure(eval_list_2(Qauthors,
		allocate_evaluation_sequence(Nil)));
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_78;  /* "Hours must be between 1 and 12" */

static Object string_constant_79;  /* "Hours must be between 0 and 23" */

static Object string_constant_80;  /* "Minutes must be between 0 and 59" */

static Object string_constant_81;  /* "Seconds must be between 0 and 59" */

static Object Qp_dot_m_dot;        /* p.m. */

/* FILTER-AND-NORMALIZE-TIME-OF-DAY */
Object filter_and_normalize_time_of_day(time_of_day_phrase)
    Object time_of_day_phrase;
{
    Object hour, minutes, side_of_meridian, seconds, twenty_four_hour_clock;
    Object temp, minutes_in_seconds;
    char temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(201,44);
    hour = FIRST(time_of_day_phrase);
    minutes = SECOND(time_of_day_phrase);
    side_of_meridian = THIRD(time_of_day_phrase);
    seconds = FOURTH(time_of_day_phrase);
    if (seconds);
    else
	seconds = copy_for_phrase(FIX((SI_Long)0L));
    twenty_four_hour_clock = FIFTH(time_of_day_phrase);
    if ( !TRUEP(twenty_four_hour_clock) &&  !((SI_Long)1L <= IFIX(hour) && 
	    IFIX(hour) <= (SI_Long)12L))
	return VALUES_2(Bad_phrase,string_constant_78);
    else if (twenty_four_hour_clock &&  !((SI_Long)0L <= IFIX(hour) && 
	    IFIX(hour) <= (SI_Long)23L))
	return VALUES_2(Bad_phrase,string_constant_79);
    else if ( !((SI_Long)0L <= IFIX(minutes) && IFIX(minutes) <= (SI_Long)59L))
	return VALUES_2(Bad_phrase,string_constant_80);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(seconds) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L)
		temp = aref1(seconds,FIX((SI_Long)0L));
	    else
		temp = seconds;
	    temp_1 =  !TRUEP(num_len(3,FIX((SI_Long)0L),temp,
		    FIX((SI_Long)59L)));
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (temp_1)
	    return VALUES_2(Bad_phrase,string_constant_81);
	else {
	    minutes_in_seconds = ltimes(FIX((SI_Long)60L),add(minutes,
		    ltimes(FIX((SI_Long)60L),twenty_four_hour_clock ? hour 
		    : EQ(side_of_meridian,Qp_dot_m_dot) ? 
		    FIX(IFIX(mod(hour,FIX((SI_Long)12L))) + (SI_Long)12L) :
		     mod(hour,FIX((SI_Long)12L)))));
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		    result = copy_for_phrase(add(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,
			    (SI_Long)0L)),minutes_in_seconds));
		POP_LOCAL_ALLOCATION(0,0);
		return result;
	    }
	    else
		return add(seconds,minutes_in_seconds);
	}
    }
}

/* DECODE-NORMALIZED-TIME-OF-DAY */
Object decode_normalized_time_of_day(time_of_day_as_seconds_since_midnight)
    Object time_of_day_as_seconds_since_midnight;
{
    Object total_minutes, seconds, hours, minutes;
    Object result;

    x_note_fn_call(201,45);
    result = chestnut_floorf_function(time_of_day_as_seconds_since_midnight,
	    FIX((SI_Long)60L));
    MVS_2(result,total_minutes,seconds);
    result = chestnut_floorf_function(total_minutes,FIX((SI_Long)60L));
    MVS_2(result,hours,minutes);
    return VALUES_3(seconds,minutes,hours);
}

/* DECODE-NORMALIZED-TIME-OF-DAY-WITH-SUBSECONDS */
Object decode_normalized_time_of_day_with_subseconds(time_of_day_as_seconds_since_midnight)
    Object time_of_day_as_seconds_since_midnight;
{
    Object total_minutes, seconds, hours, minutes;
    Object result;

    x_note_fn_call(201,46);
    result = lfloor(time_of_day_as_seconds_since_midnight,FIX((SI_Long)60L));
    MVS_2(result,total_minutes,seconds);
    result = lfloor(total_minutes,FIX((SI_Long)60L));
    MVS_2(result,hours,minutes);
    return VALUES_3(seconds,minutes,hours);
}

static Object Qab_no;              /* no */

static Object string_constant_82;  /* "Maximum number of data points must be positive." */

static Object string_constant_83;  /* "Maximum number of data points must be less than or equal to ~d." */

static Object string_constant_84;  /* "The minimum interval between data points must be greater than or equal to zero." */

/* COMPILE-HISTORY-SPECIFICATION-FOR-SLOT */
Object compile_history_specification_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object new_value, temp, temp_2, temp_3, maximum_number_of_data_points;
    Object minimum_data_point_interval_qm;
    Object millisecond_interval_or_bad_phrase_qm, bad_phrase_text_string_qm;
    char temp_1;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(201,47);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qab_no))
	new_value = Nil;
    else {
	if (parse_result) {
	    temp = SECOND(parse_result);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = parse_result;
	    temp_2 = SECOND(parse_result);
	    M_CDR(parse_result) = temp_2;
	    if (THIRD(parse_result)) {
		temp_3 = THIRD(parse_result);
		temp_2 = CAR(temp_3);
		M_THIRD(parse_result) = temp_2;
	    }
	    if (FOURTH(parse_result)) {
		temp_3 = FOURTH(parse_result);
		temp_2 = CAR(temp_3);
		M_FOURTH(parse_result) = temp_2;
	    }
	    new_value = temp;
	}
	else
	    new_value = parse_result;
    }
    maximum_number_of_data_points = SECOND(new_value);
    minimum_data_point_interval_qm = FOURTH(new_value);
    if (maximum_number_of_data_points && 
	    IFIX(maximum_number_of_data_points) <= (SI_Long)0L) {
	temp_3 = Bad_phrase;
	temp = copy_text_string(string_constant_82);
	return VALUES_2(temp_3,temp);
    }
    else if (maximum_number_of_data_points && 
	    FIXNUM_GT(maximum_number_of_data_points,
	    Largest_ring_buffer_vector_size)) {
	temp_3 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_83,
		Largest_ring_buffer_vector_size);
	return VALUES_2(temp_3,temp);
    }
    else if (minimum_data_point_interval_qm) {
	if (FIXNUMP(minimum_data_point_interval_qm) && 
		IFIX(minimum_data_point_interval_qm) < (SI_Long)0L) {
	    temp_3 = Bad_phrase;
	    temp = copy_text_string(string_constant_84);
	    return VALUES_2(temp_3,temp);
	}
	else {
	    millisecond_interval_or_bad_phrase_qm = Nil;
	    bad_phrase_text_string_qm = Nil;
	    if (FIXNUMP(minimum_data_point_interval_qm) && 
		    IFIX(minimum_data_point_interval_qm) == (SI_Long)0L)
		millisecond_interval_or_bad_phrase_qm = FIX((SI_Long)0L);
	    else {
		result = adjust_scheduling_interval(minimum_data_point_interval_qm);
		MVS_2(result,millisecond_interval_or_bad_phrase_qm,
			bad_phrase_text_string_qm);
	    }
	    if ( !TRUEP(millisecond_interval_or_bad_phrase_qm))
		return VALUES_1(Bad_phrase);
	    else if (EQ(millisecond_interval_or_bad_phrase_qm,Bad_phrase))
		return VALUES_2(millisecond_interval_or_bad_phrase_qm,
			bad_phrase_text_string_qm);
	    else {
		M_FOURTH(new_value) = millisecond_interval_or_bad_phrase_qm;
		return VALUES_1(new_value);
	    }
	}
    }
    else
	return VALUES_1(new_value);
}

static Object string_constant_85;  /* "do not keep history" */

static Object string_constant_86;  /* "keep history" */

static Object string_constant_87;  /* " with " */

static Object string_constant_88;  /* "maximum number of data points = ~d" */

static Object string_constant_89;  /* " and " */

static Object string_constant_90;  /* "maximum age of data points = " */

static Object string_constant_91;  /* ", with minimum interval between data points = " */

/* WRITE-HISTORY-SPECIFICATION-FROM-SLOT */
Object write_history_specification_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object minimum_interval_qm;
    SI_Long temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(201,48);
    if ( !TRUEP(value))
	return twrite(string_constant_85);
    else {
	twrite(string_constant_86);
	if (CDR(value))
	    twrite(string_constant_87);
	if (SECOND(value)) {
	    tformat(2,string_constant_88,SECOND(value));
	    if (THIRD(value))
		twrite(string_constant_89);
	}
	if (THIRD(value)) {
	    twrite(string_constant_90);
	    print_constant(2,THIRD(value),Qseconds);
	}
	minimum_interval_qm = FOURTH(value);
	if (minimum_interval_qm) {
	    twrite(string_constant_91);
	    temp = IFIX(minimum_interval_qm) % (SI_Long)1000L;
	    if (temp == (SI_Long)0L) {
		temp = IFIX(minimum_interval_qm) / (SI_Long)1000L;
		return print_constant(2,FIX(temp),Qseconds);
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		    result = print_constant(2,
			    DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(minimum_interval_qm) 
			    / 1000.0),Qseconds);
		POP_LOCAL_ALLOCATION(0,0);
		return result;
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Kconvert_to_phrase_failure;  /* :convert-to-phrase-failure */

static Object Qinstantiate_object_in_attribute;  /* instantiate-object-in-attribute */

/* FIX-ATTRIBUTE-INITIAL-VALUE */
Object fix_attribute_initial_value varargs_1(int, n)
{
    Object attribute_initial_value, attribute_initial_item_class;
    Object attribute_initial_type_qm;
    Object attribute_initial_item_class_restricted_to_variable_or_parameter;
    Object phrase, error_string;
    Declare_varargs_nonrelocating;
    Declare_catch(1);
    Object result;

    x_note_fn_call(201,49);
    INIT_ARGS_nonrelocating();
    attribute_initial_value = REQUIRED_ARG_nonrelocating();
    attribute_initial_item_class = REQUIRED_ARG_nonrelocating();
    attribute_initial_type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    attribute_initial_item_class_restricted_to_variable_or_parameter = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (PUSH_CATCH(Kconvert_to_phrase_failure,0)) {
	if (attribute_initial_value) {
	    phrase = convert_initial_value_to_phrase(attribute_initial_value);
	    if (SYMBOLP(attribute_initial_type_qm) && 
		    lookup_global_or_kb_specific_property_value(attribute_initial_type_qm,
		    Numeric_data_type_gkbprop))
		result = phrase_cons(phrase,attribute_initial_type_qm);
	    else
		result = VALUES_1(phrase);
	}
	else if (attribute_initial_item_class)
	    result = phrase_list_3(Kfuncall,
		    attribute_initial_item_class_restricted_to_variable_or_parameter 
		    ? Qinstantiate_variable : 
		    Qinstantiate_object_in_attribute,
		    attribute_initial_item_class);
	else
	    result = VALUES_1(Nil);
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	error_string = CATCH_VALUES();
    POP_CATCH(0);
    result = VALUES_2(Bad_phrase,error_string);
  end_gensymed_symbol:
    return result;
}

static Object array_constant_8;    /* # */

/* CONVERT-INITIAL-VALUE-TO-PHRASE */
Object convert_initial_value_to_phrase(element)
    Object element;
{
    Object value, new_long, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, gensymed_symbol, held_vector, name;
    Object attribute_value, plist, ab_loopvar_, ab_loopvar__1, sub_element;
    Object list_of_elements, elt_1, validated_elt, x2;
    SI_Long next_index, length_1, gensymed_symbol_1;
    SI_int64 aref_new_value;
    char temp_2;
    double aref_new_value_1;
    Object result;

    x_note_fn_call(201,50);
    if (element && SYMBOLP(element))
	return VALUES_1(element);
    else if (FIXNUMP(element))
	return VALUES_1(element);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(element) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == (SI_Long)1L) {
	value = evaluation_value_value(element);
	if (FIXNUMP(value))
	    return VALUES_1(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    return note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
		}
		else {
		    temp = Available_float_array_conses_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    return note_use_of_managed_float_in_phrase(new_float);
	}
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(element) != (SI_Long)0L)
	return copy_for_phrase(element);
    else if (CONSP(element) && EQ(M_CDR(element),Qtruth_value))
	return phrase_cons(M_CAR(element),Qtruth_value);
    else if (CONSP(element) && EQ(M_CDR(element),Qab_structure)) {
	gensymed_symbol = element;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	name = Nil;
	attribute_value = Nil;
	value = Nil;
	plist = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
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
	ab_loopvar__1 = phrase_cons(name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    plist = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	ab_loopvar__1 = phrase_cons(convert_initial_value_to_phrase(value),
		Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    plist = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	return phrase_cons(plist,Phrase_structure_marker);
	return VALUES_1(Qnil);
    }
    else if (CONSP(element) && EQ(M_CDR(element),Qsequence)) {
	gensymed_symbol = element;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	sub_element = Nil;
	list_of_elements = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	sub_element = validated_elt;
	ab_loopvar__1 = 
		phrase_cons(convert_initial_value_to_phrase(sub_element),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    list_of_elements = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_1;
      end_loop_1:
	return phrase_cons(list_of_elements,Phrase_sequence_marker);
	return VALUES_1(Qnil);
    }
    else {
	if (SIMPLE_VECTOR_P(element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L &&  
		!EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    result = copy_constant_wide_string_given_length(array_constant_8,
		    FIX((SI_Long)35L));
	    THROW(Kconvert_to_phrase_failure,result);
	}
	else
	    return VALUES_1(Qnil);
    }
}

/* MAKE-INITIAL-VALUE-FOR-USER */
Object make_initial_value_for_user(initial_value)
    Object initial_value;
{
    Object car_1, cdr_1, temp, managed_value;
    char temp_1;

    x_note_fn_call(201,51);
    if (LISTP(initial_value) && EQ(CAR(initial_value),Kfuncall) && 
	    (SI_Long)3L == IFIX(length(initial_value)) && 
	    (EQ(CADR(initial_value),Qinstantiate_object_in_attribute) || 
	    EQ(CADR(initial_value),Qinstantiate_variable)))
	return VALUES_1(Nil);
    else {
	if (CONSP(initial_value)) {
	    car_1 = M_CAR(initial_value);
	    cdr_1 = M_CDR(initial_value);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    managed_value = M_CAR(initial_value);
	    if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(initial_value))),
		    Qtruth_value)) {
		if (FIXNUM_EQ(managed_value,Truth))
		    return VALUES_1(Evaluation_true_value);
		else if (FIXNUM_EQ(managed_value,Falsity))
		    return VALUES_1(Evaluation_false_value);
		else
		    return eval_cons_1(managed_value,Qtruth_value);
	    }
	    else if (FIXNUMP(managed_value) || SYMBOLP(managed_value))
		return VALUES_1(managed_value);
	    else
		return copy_evaluation_value_1(managed_value);
	}
	else if (Nil) {
	    if (FIXNUM_EQ(initial_value,Truth))
		return VALUES_1(Evaluation_true_value);
	    else if (FIXNUM_EQ(initial_value,Falsity))
		return VALUES_1(Evaluation_false_value);
	    else
		return eval_cons_1(initial_value,Qtruth_value);
	}
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(initial_value) != 
		(SI_Long)0L)
	    return copy_wide_string(initial_value);
	else if (FIXNUMP(initial_value) || SYMBOLP(initial_value))
	    return VALUES_1(initial_value);
	else
	    return copy_evaluation_value_1(initial_value);
    }
}

/* MAKE-INITIAL-VALUE-FOR-USER-GIVEN-TYPE */
Object make_initial_value_for_user_given_type(initial_value,initial_type)
    Object initial_value, initial_type;
{
    Object substitute_value, answer, temp;

    x_note_fn_call(201,52);
    if (EQ(initial_type,Qtruth_value)) {
	substitute_value = slot_value_list_2(initial_value,Qtruth_value);
	answer = make_initial_value_for_user(substitute_value);
	reclaim_slot_value_list_1(substitute_value);
	temp = answer;
    }
    else
	temp = make_initial_value_for_user(initial_value);
    return VALUES_1(temp);
}

/* MAKE-INITIAL-ITEM-CLASS-FOR-USER */
Object make_initial_item_class_for_user(initial_value)
    Object initial_value;
{
    x_note_fn_call(201,53);
    if (LISTP(initial_value) && EQ(CAR(initial_value),Kfuncall) && 
	    (SI_Long)3L == IFIX(length(initial_value)) && 
	    (EQ(CADR(initial_value),Qinstantiate_object_in_attribute) || 
	    EQ(CADR(initial_value),Qinstantiate_variable)))
	return VALUES_1(CADDR(initial_value));
    else
	return VALUES_1(Nil);
}

/* INITIAL-ITEM-CLASS-RESTRICTED-TO-VARIABLE-OR-PARAMETER-FOR-USER-P */
Object initial_item_class_restricted_to_variable_or_parameter_for_user_p(initial_value)
    Object initial_value;
{
    x_note_fn_call(201,54);
    if (LISTP(initial_value) && EQ(CAR(initial_value),Kfuncall) && 
	    (SI_Long)3L == IFIX(length(initial_value)))
	return VALUES_1(EQ(CADR(initial_value),Qinstantiate_variable) ? T :
		 Nil);
    else
	return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

static Object Qattribute_initial_value;  /* attribute-initial-value */

static Object Qattribute_initial_item_class;  /* attribute-initial-item-class */

static Object Qattribute_initial_type;  /* attribute-initial-type */

static Object Qattribute_initial_item_class_restricted_to_variable_or_parameter;  /* attribute-initial-item-class-restricted-to-variable-or-parameter */

static Object Qattribute_name;     /* attribute-name */

static Object Qattribute_type_specification;  /* attribute-type-specification */

static Object Qattribute_format;   /* attribute-format */

static Object Qformat_override;    /* format-override */

static Object Qwhole_number_precision;  /* whole-number-precision */

static Object Qddd_dot_dddd_format;  /* ddd.dddd-format */

static Object Qfraction_precision;  /* fraction-precision */

static Object Qattribute_is_indexed;  /* attribute-is-indexed */

static Object Qattribute_range;    /* attribute-range */

static Object list_constant_12;    /* # */

static Object Qdate_format_description;  /* date-format-description */

static Object string_constant_92;  /* "Bad attribute format ~s for attribute ~s" */

static Object Qfloat_format;       /* float-format */

static Object string_constant_93;  /* "Incompatible initial-value for attribute ~s" */

static Object list_constant_13;    /* # */

static Object Qnormalized_parse;   /* normalized-parse */

/* ATTRIBUTE-DESCRIPTIONS-EVALUATION-SETTER */
Object attribute_descriptions_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object attribute_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, temp_2, temp_3, result_1, error_string_qm;
    Object fixed_attribute_initial_value, type_spec, gensymed_symbol_1;
    Object fixed_attribute_description, fixed_attribute_type, held_vector_1;
    Object range_elt, ab_loopvar__3, ab_loopvar__4, attribute_range_list;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object bad_phrase_qm, error_message, type_string;
    SI_Long next_index, length_1, next_index_1, length_2, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_3, i, ab_loop_bind_;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,55);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_9))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_10,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_attribute_descriptions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_11)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	attribute_info = Nil;
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
	attribute_info = validated_elt;
	gensymed_symbol = attribute_info;
	temp_2 = estructure_slot(gensymed_symbol,Qattribute_initial_value,Nil);
	temp_3 = estructure_slot(gensymed_symbol,
		Qattribute_initial_item_class,Nil);
	temp = estructure_slot(gensymed_symbol,Qattribute_initial_type,Nil);
	if (estructure_slot(gensymed_symbol,
		Qattribute_initial_item_class_restricted_to_variable_or_parameter,
		Nil)) {
	    temp_1 = estructure_slot(gensymed_symbol,
		    Qattribute_initial_item_class_restricted_to_variable_or_parameter,
		    Nil);
	    temp_1 = CONSP(temp_1) && 
		    EQ(M_CDR(estructure_slot(gensymed_symbol,
		    Qattribute_initial_item_class_restricted_to_variable_or_parameter,
		    Nil)),Qtruth_value) ? 
		    (EQ(M_CAR(estructure_slot(gensymed_symbol,
		    Qattribute_initial_item_class_restricted_to_variable_or_parameter,
		    Nil)),Truth) ? T : Nil) : Nil;
	}
	else
	    temp_1 = Nil;
	result = fix_attribute_initial_value(4,temp_2,temp_3,temp,temp_1);
	MVS_2(result,result_1,error_string_qm);
	if (EQ(result_1,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_setter;
	}
	else
	    fixed_attribute_initial_value = result_1;
	temp_1 = estructure_slot(gensymed_symbol,Qattribute_name,Nil);
	temp = phrase_list_3(temp_1,fixed_attribute_initial_value,
		estructure_slot(gensymed_symbol,
		Qattribute_initial_item_class,Nil));
	if (estructure_slot(gensymed_symbol,Qattribute_type_specification,
		    Nil)) {
	    type_spec = 
		    type_specification_for_user_type(estructure_slot(gensymed_symbol,
		    Qattribute_type_specification,Nil));
	    if (type_spec);
	    else
		type_spec = phrase_list_2(Qab_class,
			estructure_slot(gensymed_symbol,
			Qattribute_type_specification,Nil));
	    if (estructure_slot(gensymed_symbol,Qattribute_format,Nil)) {
		temp_1 = estructure_slot(gensymed_symbol,Qattribute_format,
			Nil);
		if (SYMBOLP(temp_1))
		    temp_1 = phrase_list_2(Qformat_override,
			    estructure_slot(gensymed_symbol,
			    Qattribute_format,Nil));
		else {
		    gensymed_symbol_1 = estructure_slot(gensymed_symbol,
			    Qattribute_format,Nil);
		    temp_1 = estructure_slot(gensymed_symbol_1,
			    Qwhole_number_precision,Nil);
		    temp_1 = phrase_list_3(Qformat_override,
			    Qddd_dot_dddd_format,phrase_cons(temp_1,
			    estructure_slot(gensymed_symbol_1,
			    Qfraction_precision,Nil)));
		}
		temp_1 = phrase_list_3(Type_and_modifications_tag,
			type_spec,phrase_cons(temp_1,Nil));
	    }
	    else
		temp_1 = type_spec;
	}
	else
	    temp_1 = Nil;
	temp = phrase_list_2(temp,temp_1);
	if (estructure_slot(gensymed_symbol,Qattribute_is_indexed,Nil)) {
	    temp_1 = estructure_slot(gensymed_symbol,Qattribute_is_indexed,
		    Nil);
	    temp_1 = CONSP(temp_1) && 
		    EQ(M_CDR(estructure_slot(gensymed_symbol,
		    Qattribute_is_indexed,Nil)),Qtruth_value) ? 
		    (EQ(M_CAR(estructure_slot(gensymed_symbol,
		    Qattribute_is_indexed,Nil)),Truth) ? T : Nil) : Nil;
	}
	else
	    temp_1 = Nil;
	fixed_attribute_description = fix_attribute_description(temp,temp_1);
	fixed_attribute_type = 
		attribute_definition_type_specification(SECOND(fixed_attribute_description));
	if (estructure_slot(gensymed_symbol,Qattribute_range,Nil) && 
		type_specification_subtype_p(Qsymbol,fixed_attribute_type)) {
	    gensymed_symbol_1 = estructure_slot(gensymed_symbol,
		    Qattribute_range,Nil);
	    held_vector_1 = Nil;
	    next_index_1 = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    range_elt = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    held_vector_1 = M_CAR(gensymed_symbol_1);
	    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	  next_loop_1:
	    if (next_index_1 >= length_2)
		goto end_loop_1;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    next_index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_1 & 
		    (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index_1 = next_index_1 + (SI_Long)1L;
	    range_elt = validated_elt;
	    ab_loopvar__4 = phrase_cons(range_elt,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_1;
	  end_loop_1:
	    attribute_range_list = ab_loopvar__2;
	    goto end_1;
	    attribute_range_list = Qnil;
	  end_1:;
	}
	else
	    attribute_range_list = Nil;
	if (estructure_slot(gensymed_symbol,Qattribute_format,Nil)) {
	    temp_1 = estructure_slot(gensymed_symbol,Qattribute_format,Nil);
	    if (SYMBOLP(temp_1)) {
		if ( !(memq_function(estructure_slot(gensymed_symbol,
			Qattribute_format,Nil),list_constant_12) || 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(estructure_slot(gensymed_symbol,
			Qattribute_format,Nil)),Qdate_format_description))) {
		    temp = Bad_phrase;
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
			  length_3 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_3 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_3 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
			      temp_1 = estructure_slot(gensymed_symbol,
				      Qattribute_format,Nil);
			      tformat(3,string_constant_92,temp_1,
				      estructure_slot(gensymed_symbol,
				      Qattribute_name,Nil));
			      temp_1 = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    result = VALUES_2(temp,temp_1);
		    goto end_setter;
		}
	    }
	    else {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfloat_format),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)3L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_1 = function;
		    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
			    Qattribute_format,Nil);
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = Nil;
		    result = inline_funcall_4(gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3,
			    gensymed_symbol_4,gensymed_symbol_5);
		}
		else
		    result = VALUES_1(Nil);
		MVS_2(result,bad_phrase_qm,error_message);
		if (EQ(bad_phrase_qm,Bad_phrase)) {
		    result = VALUES_2(Bad_phrase,error_message);
		    goto end_setter;
		}
	    }
	}
	if ( 
		!TRUEP(compatible_initial_attribute_value_p(estructure_slot(gensymed_symbol,
		Qattribute_initial_value,Nil),fixed_attribute_type))) {
	    temp = Bad_phrase;
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
		  length_3 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_3 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_3 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(2,string_constant_93,
			      estructure_slot(gensymed_symbol,
			      Qattribute_name,Nil));
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    result = VALUES_2(temp,temp_1);
	    goto end_setter;
	}
	if ( !TRUEP(attribute_range_list))
	    temp_1 = fixed_attribute_description;
	else {
	    i = IFIX(length(fixed_attribute_description));
	    temp_1 = last(fixed_attribute_description,_);
	    temp_1 = CAR(temp_1);
	    ab_loop_bind_ = EQUAL(temp_1,list_constant_13) ? (SI_Long)5L : 
		    (SI_Long)4L;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	  next_loop_2:
	    if (i >= ab_loop_bind_)
		goto end_loop_2;
	    ab_loopvar__4 = phrase_cons(Nil,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    i = i + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:
	    temp_1 = ab_loopvar__2;
	    goto end_2;
	    temp_1 = Qnil;
	  end_2:;
	    temp_1 = nconc2(fixed_attribute_description,nconc2(temp_1,
		    attribute_range_list));
	}
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_3;
	temp_1 = Qnil;
      end_3:;
	result = phrase_cons(Qnormalized_parse,temp_1);
      end_setter:;
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
	      length_3 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_3 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_3 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_76,list_constant_7);
		  tformat(2,string_constant_76,list_constant_11);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_77,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_attribute_descriptions_evaluation_setter:
    return result;
}

static Object list_constant_14;    /* # */

/* ATTRIBUTE-DESCRIPTIONS-EVALUATION-GETTER */
Object attribute_descriptions_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object attribute_info, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, gensymed_symbol_2;
    Object source_attribute_name, source_attribute_type_specification;
    Object source_attribute_initial_value, source_attribute_initial_type;
    Object source_attribute_range, attribute_type_modifications_1, temp;
    Object format_1, category_evaluator_interface, function, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, value, range_elt;
    Object ab_loop_list__1, ab_loopvar__2;

    x_note_fn_call(201,56);
    if (slot_value) {
	attribute_info = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	gensymed_symbol_2 = attribute_info;
	source_attribute_name = CAR(gensymed_symbol_2);
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	source_attribute_type_specification = CAR(gensymed_symbol_2);
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	source_attribute_initial_value = CAR(gensymed_symbol_2);
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	source_attribute_initial_type = CAR(gensymed_symbol_2);
	source_attribute_range = CDR(gensymed_symbol_2);
	set_evaluation_structure_slot(gensymed_symbol_1,Qattribute_name,
		source_attribute_name);
	if ( !EQUAL(source_attribute_type_specification,list_constant_14))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_type_specification,
		    user_type_for_type_specification(attribute_definition_type_specification(source_attribute_type_specification)));
	attribute_type_modifications_1 = 
		attribute_definition_type_modifications(source_attribute_type_specification);
	temp = assq_function(Qformat_override,attribute_type_modifications_1);
	format_1 = CDR(temp);
	if (format_1) {
	    if (EQ(CAR(format_1),Qddd_dot_dddd_format)) {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfloat_format),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_2 = function;
		    gensymed_symbol_3 = SECOND(format_1);
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = Nil;
		    temp = inline_funcall_3(gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		else
		    temp = Nil;
	    }
	    else
		temp = CAR(format_1);
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_format,temp);
	}
	value = 
		make_initial_value_for_user_given_type(source_attribute_initial_value,
		source_attribute_initial_type);
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_initial_value,value);
	value = 
		make_initial_item_class_for_user(source_attribute_initial_value);
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_initial_item_class,value);
	if (initial_item_class_restricted_to_variable_or_parameter_for_user_p(source_attribute_initial_value))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_initial_item_class_restricted_to_variable_or_parameter,
		    T ? Evaluation_true_value : Evaluation_false_value);
	if (SYMBOLP(source_attribute_initial_type) && 
		lookup_global_or_kb_specific_property_value(source_attribute_initial_type,
		Numeric_data_type_gkbprop)) {
	    value = source_attribute_initial_type;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qattribute_initial_type,value);
	}
	if (frame && memq_function(source_attribute_name,
		get_lookup_slot_value_given_default(frame,
		Qindexed_attributes_for_definition,Nil)))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_is_indexed,Evaluation_true_value);
	if (source_attribute_range) {
	    range_elt = Nil;
	    ab_loop_list__1 = source_attribute_range;
	    gensymed_symbol_2 = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    range_elt = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loopvar__2 = eval_cons_1(range_elt,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		gensymed_symbol_2 = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    temp = allocate_evaluation_sequence(gensymed_symbol_2);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_range,temp);
	}
	ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPATIBLE-INITIAL-ATTRIBUTE-VALUE-P */
Object compatible_initial_attribute_value_p(initial_value,type_specification)
    Object initial_value, type_specification;
{
    Object temp;

    x_note_fn_call(201,57);
    if (type_specification_subtype_p(type_specification,Qdatum))
	temp = type_specification_type_p(initial_value,type_specification);
    else if (class_type_specification_p(type_specification))
	temp =  !TRUEP(initial_value) ? T : Nil;
    else
	temp = T;
    return VALUES_1(temp);
}

static Object Qitem;               /* item */

/* INHERITED-ATTRIBUTES-EVALUATION-GETTER */
Object inherited_attributes_evaluation_getter(slot_value,frame_qm,
	    slot_description)
    Object slot_value, frame_qm, slot_description;
{
    Object class_inheritance_path_qm, attribute, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, pretty_slot_names_encountered_qm;
    Object working_list_of_attribute_descriptions_qm, superior;
    Object class_description_qm, copied_attribute_descriptions;
    Object copied_attribute, ab_loop_list__1, attribute_name, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, copied_superior_attribute_descriptions_qm;
    Object attribute_info, source_attribute_name;
    Object source_attribute_type_specification, source_attribute_initial_value;
    Object source_attribute_initial_type, source_attribute_range, value;
    Object range_elt;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(201,58);
    class_inheritance_path_qm = frame_qm ? 
	    get_lookup_slot_value_given_default(frame_qm,
	    Qclass_inheritance_path_of_definition,Nil) : Nil;
    if (class_inheritance_path_qm) {
	attribute = Nil;
	ab_loop_list_ = ISVREF(frame_qm,(SI_Long)22L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = gensym_cons_1(CAR(attribute),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	pretty_slot_names_encountered_qm = ab_loopvar_;
	goto end_1;
	pretty_slot_names_encountered_qm = Qnil;
      end_1:;
	working_list_of_attribute_descriptions_qm = Nil;
	superior = Nil;
	ab_loop_list_ = CDR(class_inheritance_path_qm);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(superior,Qitem))
	    goto end_loop_1;
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L))) {
	    copied_attribute_descriptions = 
		    copy_for_slot_value(ISVREF(lookup_global_or_kb_specific_property_value(superior,
		    Class_definition_gkbprop),(SI_Long)22L));
	    copied_attribute = Nil;
	    ab_loop_list__1 = copied_attribute_descriptions;
	    attribute_name = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    copied_attribute = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    attribute_name = CAR(copied_attribute);
	    if (memq_function(attribute_name,
			pretty_slot_names_encountered_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = superior;
		key_hash_value = SXHASH_SYMBOL_1(superior) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_3:
		if (level < ab_loop_bind_)
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_2;
		goto next_loop_4;
	      end_loop_5:
	      end_2:
		level = level - (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = superior;
		    temp = Symbol_properties_table;
		    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
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
	      next_loop_6:
		if (level < ab_loop_bind_)
		    goto end_loop_6;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_7:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_7;
	      end_loop_8:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_6;
	      end_loop_6:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
			goto end_4;
		    goto next_loop_10;
		  end_loop_11:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_9;
		  end_loop_9:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_12:
		    if (level < ab_loop_bind_)
			goto end_loop_12;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_13:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_14:
		    if ( !TRUEP(marked))
			goto end_loop_13;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_14;
		  end_loop_13:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_5;
		    goto next_loop_13;
		  end_loop_14:
		  end_5:
		    level = level - (SI_Long)1L;
		    goto next_loop_12;
		  end_loop_12:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_2 = 
			ISVREF(get_slot_description_of_class_description_function(attribute_name,
			gensymed_symbol,Nil),(SI_Long)1L);
		M_CAR(copied_attribute) = temp_2;
	    }
	    else
		pretty_slot_names_encountered_qm = 
			gensym_cons_1(attribute_name,
			pretty_slot_names_encountered_qm);
	    goto next_loop_2;
	  end_loop_2:
	    working_list_of_attribute_descriptions_qm = 
		    nconc2(working_list_of_attribute_descriptions_qm,
		    copied_attribute_descriptions);
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_gensym_list_1(pretty_slot_names_encountered_qm);
	copied_superior_attribute_descriptions_qm = 
		working_list_of_attribute_descriptions_qm;
	goto end_6;
	copied_superior_attribute_descriptions_qm = Qnil;
      end_6:;
    }
    else
	copied_superior_attribute_descriptions_qm = Nil;
    slot_value = copied_superior_attribute_descriptions_qm;
    if (slot_value) {
	attribute_info = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_15:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_15;
	attribute_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	source_attribute_name = CAR(attribute_info);
	source_attribute_type_specification = 
		attribute_type_specification(attribute_info);
	temp_1 = CDDR(attribute_info);
	source_attribute_initial_value = CAR(temp_1);
	temp_1 = CDDDR(attribute_info);
	source_attribute_initial_type = CAR(temp_1);
	source_attribute_range = CDDDDR(attribute_info);
	set_evaluation_structure_slot(gensymed_symbol_1,Qattribute_name,
		source_attribute_name);
	if ( !EQUAL(source_attribute_type_specification,list_constant_14))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_type_specification,
		    user_type_for_type_specification(source_attribute_type_specification));
	value = make_initial_value_for_user(source_attribute_initial_value);
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_initial_value,value);
	value = 
		make_initial_item_class_for_user(source_attribute_initial_value);
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_initial_item_class,value);
	if (SYMBOLP(source_attribute_initial_type) && 
		lookup_global_or_kb_specific_property_value(source_attribute_initial_type,
		Numeric_data_type_gkbprop)) {
	    value = source_attribute_initial_type;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qattribute_initial_type,value);
	}
	if (frame_qm && memq_function(source_attribute_name,
		get_lookup_slot_value_given_default(frame_qm,
		Qindexed_attributes_for_definition,Nil)))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_is_indexed,Evaluation_true_value);
	if (source_attribute_range) {
	    range_elt = Nil;
	    ab_loop_list__1 = source_attribute_range;
	    gensymed_symbol_2 = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_16:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_16;
	    range_elt = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loopvar__2 = eval_cons_1(range_elt,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		gensymed_symbol_2 = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_16;
	  end_loop_16:
	    temp_1 = allocate_evaluation_sequence(gensymed_symbol_2);
	    goto end_7;
	    temp_1 = Qnil;
	  end_7:;
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_range,temp_1);
	}
	ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_15;
      end_loop_15:
	temp_1 = allocate_evaluation_sequence(gensymed_symbol);
	goto end_8;
	temp_1 = Qnil;
      end_8:;
	reclaim_slot_value(slot_value);
    }
    else
	temp_1 = Nil;
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

static Object Qhistory;            /* history */

static Object Qmaximum_number_of_data_points;  /* maximum-number-of-data-points */

static Object Qmaximum_age_of_data_points;  /* maximum-age-of-data-points */

static Object Qminimum_interval_between_data_points;  /* minimum-interval-between-data-points */

/* HISTORY-SPECIFICATION-EVALUATION-SETTER */
Object history_specification_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,59);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_15))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_16,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_history_specification_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	gensymed_symbol = evaluation_value;
	temp_2 = phrase_cons(Qhistory,Nil);
	temp = estructure_slot(gensymed_symbol,
		Qmaximum_number_of_data_points,Nil) || 
		estructure_slot(gensymed_symbol,
		Qmaximum_age_of_data_points,Nil) || 
		estructure_slot(gensymed_symbol,
		Qminimum_interval_between_data_points,Nil) ? 
		phrase_cons(estructure_slot(gensymed_symbol,
		Qmaximum_number_of_data_points,Nil),Nil) : Nil;
	temp_1 = estructure_slot(gensymed_symbol,
		Qmaximum_age_of_data_points,Nil) || 
		estructure_slot(gensymed_symbol,
		Qminimum_interval_between_data_points,Nil) ? 
		phrase_cons(estructure_slot(gensymed_symbol,
		Qmaximum_age_of_data_points,Nil),Nil) : Nil;
	result = VALUES_1(nconc2(temp_2,nconc2(temp,nconc2(temp_1,
		estructure_slot(gensymed_symbol,
		Qminimum_interval_between_data_points,Nil) ? 
		phrase_cons(invert_adjusted_scheduling_interval(estructure_slot(gensymed_symbol,
		Qminimum_interval_between_data_points,Nil)),Nil) : Nil))));
    }
    else
	result = VALUES_1(Qab_no);
  end_history_specification_evaluation_setter:
    return result;
}

/* HISTORY-SPECIFICATION-EVALUATION-GETTER */
Object history_specification_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, maximum_number, maximum_age, minimum_interval;
    Object temp;

    x_note_fn_call(201,60);
    if (slot_value) {
	gensymed_symbol = slot_value;
	gensymed_symbol = CDR(gensymed_symbol);
	maximum_number = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	maximum_age = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	minimum_interval = CAR(gensymed_symbol);
	if (maximum_number || maximum_age || minimum_interval) {
	    temp = maximum_number ? 
		    eval_list_2(Qmaximum_number_of_data_points,
		    maximum_number) : Nil;
	    temp = allocate_evaluation_structure(nconc2(temp,
		    nconc2(maximum_age ? 
		    eval_list_2(Qmaximum_age_of_data_points,maximum_age) : 
		    Nil,minimum_interval ? 
		    eval_list_2(Qminimum_interval_between_data_points,
		    minimum_interval) : Nil)));
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_17;    /* # */

/* LIST-OF-CLASSES-EVALUATION-SETTER */
Object list_of_classes_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object class_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,61);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_17))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_list_of_classes_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_11)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	class_name = Nil;
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
	class_name = validated_elt;
	ab_loopvar__2 = phrase_cons(class_name,Nil);
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
	result = phrase_cons(Nil,temp_1);
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
		  tformat(2,string_constant_76,list_constant_7);
		  tformat(2,string_constant_76,list_constant_11);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_77,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_list_of_classes_evaluation_setter:
    return result;
}

/* LIST-OF-CLASSES-EVALUATION-GETTER */
Object list_of_classes_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object class_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(201,62);
    if (slot_value) {
	class_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(class_name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_18;    /* # */

/* LIST-OF-OBJECT-CLASSES-EVALUATION-SETTER */
Object list_of_object_classes_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object class_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,63);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_18))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_list_of_object_classes_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_11)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	class_name = Nil;
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
	class_name = validated_elt;
	ab_loopvar__2 = phrase_cons(class_name,Nil);
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
	result = phrase_cons(Nil,temp_1);
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
		  tformat(2,string_constant_76,list_constant_7);
		  tformat(2,string_constant_76,list_constant_11);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_77,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_list_of_object_classes_evaluation_setter:
    return result;
}

/* LIST-OF-OBJECT-CLASSES-EVALUATION-GETTER */
Object list_of_object_classes_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object class_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(201,64);
    if (slot_value) {
	class_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(class_name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_19;    /* # */

/* LIST-OF-CONNECTION-CLASSES-EVALUATION-SETTER */
Object list_of_connection_classes_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object class_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,65);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_19))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_list_of_connection_classes_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_11)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	class_name = Nil;
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
	class_name = validated_elt;
	ab_loopvar__2 = phrase_cons(class_name,Nil);
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
	result = phrase_cons(Nil,temp_1);
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
		  tformat(2,string_constant_76,list_constant_7);
		  tformat(2,string_constant_76,list_constant_11);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_77,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_list_of_connection_classes_evaluation_setter:
    return result;
}

/* LIST-OF-CONNECTION-CLASSES-EVALUATION-GETTER */
Object list_of_connection_classes_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object class_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(201,66);
    if (slot_value) {
	class_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(class_name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_20;    /* # */

/* LIST-OF-MESSAGE-CLASSES-EVALUATION-SETTER */
Object list_of_message_classes_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object class_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,67);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_20))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_list_of_message_classes_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_11)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	class_name = Nil;
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
	class_name = validated_elt;
	ab_loopvar__2 = phrase_cons(class_name,Nil);
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
	result = phrase_cons(Nil,temp_1);
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
		  tformat(2,string_constant_76,list_constant_7);
		  tformat(2,string_constant_76,list_constant_11);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_77,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_list_of_message_classes_evaluation_setter:
    return result;
}

/* LIST-OF-MESSAGE-CLASSES-EVALUATION-GETTER */
Object list_of_message_classes_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object class_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(201,68);
    if (slot_value) {
	class_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(class_name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CLASS-INHERITANCE-PATH-OF-DEFINITION-EVALUATION-GETTER */
Object class_inheritance_path_of_definition_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object class_name, ab_loop_list_, my_list, ab_loopvar_, ab_loopvar__1;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(201,69);
    if (slot_value) {
	class_name = Nil;
	ab_loop_list_ = slot_value;
	my_list = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	skip_list = CDR(Symbol_properties_table);
	key_value = class_name;
	key_hash_value = SXHASH_SYMBOL_1(class_name) & 
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
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_2:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_3;
      end_loop_2:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_name;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		svref_arg_1 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
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
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_5:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_6;
      end_loop_5:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_11:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_12;
	  end_loop_11:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L)) {
	    ab_loopvar__1 = eval_cons_1(class_name,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		my_list = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	goto next_loop;
      end_loop:
	temp_1 = allocate_evaluation_sequence(my_list);
	goto end_5;
	temp_1 = Qnil;
      end_5:;
    }
    else
	temp_1 = Nil;
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

static Object list_constant_21;    /* # */

static Object list_constant_22;    /* # */

static Object Qattribute_list;     /* attribute-list */

static Object Qqualified_class;    /* qualified-class */

static Object Qattribute;          /* attribute */

static Object Qdisplay_with_name;  /* display-with-name */

static Object Qx_offset;           /* x-offset */

static Object Qy_offset;           /* y-offset */

/* ATTRIBUTE-DISPLAYS-SPEC?-EVALUATION-SETTER */
Object attribute_displays_spec_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object attr_display_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, gensymed_symbol_1, held_vector_1, attr_info;
    Object ab_loopvar__3, ab_loopvar__4, result_1, attr_list;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, next_index_1, length_2, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_3;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,70);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_21))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_22,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_attribute_displays_spec_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,Qsymbol))
	result = VALUES_1(evaluation_value);
    else if (type_specification_type_p(gensymed_symbol,list_constant_11)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	attr_display_info = Nil;
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
	attr_display_info = validated_elt;
	gensymed_symbol = attr_display_info;
	gensymed_symbol_1 = estructure_slot(gensymed_symbol,
		Qattribute_list,Nil);
	held_vector_1 = Nil;
	next_index_1 = (SI_Long)1L;
	length_2 = (SI_Long)0L;
	attr_info = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
	held_vector_1 = M_CAR(gensymed_symbol_1);
	length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
      next_loop_1:
	if (next_index_1 >= length_2)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		next_index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index_1 & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index_1 = next_index_1 + (SI_Long)1L;
	attr_info = validated_elt;
	gensymed_symbol_1 = attr_info;
	if ( !TRUEP(estructure_slot(gensymed_symbol_1,Qqualified_class,Nil)))
	    result_1 = estructure_slot(gensymed_symbol_1,Qattribute,Nil);
	else {
	    temp_1 = estructure_slot(gensymed_symbol_1,Qqualified_class,Nil);
	    result_1 = phrase_list_3(Qclass_qualified_name,temp_1,
		    estructure_slot(gensymed_symbol_1,Qattribute,Nil));
	}
	ab_loopvar__4 = 
		phrase_cons(evaluation_truth_value_is_true_p(estructure_slot(gensymed_symbol_1,
		Qdisplay_with_name,Nil)) ? phrase_cons(result_1,Nil) : 
		result_1,Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	goto next_loop_1;
      end_loop_1:
	attr_list = ab_loopvar__2;
	goto end_1;
	attr_list = Qnil;
      end_1:;
	temp = phrase_cons(Qcm,attr_list);
	temp_1 = estructure_slot(gensymed_symbol,Qposition,Nil);
	if (CONSP(temp_1) && EQ(M_CDR(estructure_slot(gensymed_symbol,
		Qposition,Nil)),Qab_structure)) {
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qposition,Nil);
	    temp_1 = estructure_slot(gensymed_symbol,Qx_offset,Nil);
	    temp_1 = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,
		    Qy_offset,Nil));
	}
	else
	    temp_1 = estructure_slot(gensymed_symbol,Qposition,Nil);
	ab_loopvar__2 = phrase_cons(phrase_list_2(temp,temp_1),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	result = phrase_cons(Qsc,temp_1);
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
	      length_3 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_3 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_3 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_76,list_constant_7);
		  tformat(2,string_constant_76,Qsymbol);
		  tformat(2,string_constant_76,list_constant_11);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_77,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_attribute_displays_spec_qm_evaluation_setter:
    return result;
}

/* ATTRIBUTE-DISPLAYS-SPEC?-EVALUATION-GETTER */
Object attribute_displays_spec_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object attr_display_info, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, gensymed_symbol_2;
    Object source_attr_list, source_position, source_attr, ab_loop_list__1;
    Object ab_loopvar__2, gensymed_symbol_3, thing, temp, source_x_position;
    Object source_y_position;

    x_note_fn_call(201,71);
    if (slot_value) {
	if (CONSP(slot_value)) {
	    attr_display_info = Nil;
	    ab_loop_list_ = slot_value;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    attr_display_info = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	    gensymed_symbol_2 = attr_display_info;
	    source_attr_list = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_position = CAR(gensymed_symbol_2);
	    source_attr = Nil;
	    ab_loop_list__1 = source_attr_list;
	    gensymed_symbol_2 = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    source_attr = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    gensymed_symbol_3 = allocate_evaluation_structure(Nil);
	    if (CONSP(source_attr)) {
		if (CONSP(source_attr) && EQ(M_CAR(source_attr),
			Qclass_qualified_name)) {
		    set_evaluation_structure_slot(gensymed_symbol_3,
			    Qattribute,THIRD(source_attr));
		    set_evaluation_structure_slot(gensymed_symbol_3,
			    Qqualified_class,SECOND(source_attr));
		    set_evaluation_structure_slot(gensymed_symbol_3,
			    Qdisplay_with_name,Evaluation_false_value);
		}
		else {
		    thing = CAR(source_attr);
		    if (CONSP(thing) && EQ(M_CAR(thing),
				Qclass_qualified_name)) {
			temp = CAR(source_attr);
			set_evaluation_structure_slot(gensymed_symbol_3,
				Qattribute,THIRD(temp));
			temp = CAR(source_attr);
			set_evaluation_structure_slot(gensymed_symbol_3,
				Qqualified_class,SECOND(temp));
			set_evaluation_structure_slot(gensymed_symbol_3,
				Qdisplay_with_name,Evaluation_true_value);
		    }
		    else {
			set_evaluation_structure_slot(gensymed_symbol_3,
				Qattribute,CAR(source_attr));
			set_evaluation_structure_slot(gensymed_symbol_3,
				Qdisplay_with_name,Evaluation_true_value);
		    }
		}
	    }
	    else {
		set_evaluation_structure_slot(gensymed_symbol_3,Qattribute,
			source_attr);
		set_evaluation_structure_slot(gensymed_symbol_3,
			Qdisplay_with_name,Evaluation_false_value);
	    }
	    ab_loopvar__2 = eval_cons_1(gensymed_symbol_3,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		gensymed_symbol_2 = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    temp = allocate_evaluation_sequence(gensymed_symbol_2);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qattribute_list,temp);
	    if (CONSP(source_position)) {
		gensymed_symbol_2 = allocate_evaluation_structure(Nil);
		gensymed_symbol_3 = source_position;
		source_x_position = CAR(gensymed_symbol_3);
		gensymed_symbol_3 = CDR(gensymed_symbol_3);
		source_y_position = CAR(gensymed_symbol_3);
		set_evaluation_structure_slot(gensymed_symbol_2,Qx_offset,
			source_x_position);
		set_evaluation_structure_slot(gensymed_symbol_2,Qy_offset,
			source_y_position);
		temp = gensymed_symbol_2;
	    }
	    else
		temp = set_evaluation_structure_slot(gensymed_symbol_1,
			Qposition,source_position);
	    set_evaluation_structure_slot(gensymed_symbol_1,Qposition,temp);
	    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    temp = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	}
	else
	    temp = Nil;
    }
    else
	temp = Qinherited;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_23;    /* # */

static Object list_constant_24;    /* # */

/* NEW-CLASS-EVALUATION-SETTER */
Object new_class_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,72);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_23))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_24,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_new_class_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qnone))
	result = VALUES_1(Nil);
    else
	result = VALUES_1(evaluation_value);
  end_new_class_evaluation_setter:
    return result;
}

/* NEW-CLASS-EVALUATION-GETTER */
Object new_class_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(201,73);
    temp = slot_value;
    if (temp);
    else
	temp = Qnone;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* LIST-OF-SLOTS-EVALUATION-GETTER */
Object list_of_slots_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object class_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(201,74);
    if (slot_value) {
	class_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(class_name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_25;    /* # */

static Object list_constant_26;    /* # */

static Object Qportname;           /* portname */

static Object Qconnection_class;   /* connection-class */

static Object Qstub_direction;     /* stub-direction */

static Object Qedge_location;      /* edge-location */

static Object Qcoordinate_location;  /* coordinate-location */

static Object Qstyle;              /* style */

static Object Qline_pattern;       /* line-pattern */

/* CONNECTIONS?-EVALUATION-SETTER */
Object connections_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object stub_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, gensymed_symbol_1, gensymed_symbol_2, car_new_value;
    Object category_evaluator_interface, function, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    Object gensymed_symbol_7, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,75);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_25))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_26,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_connections_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qinherited))
	result = VALUES_1(Qinherited);
    else if ( !TRUEP(evaluation_value))
	result = VALUES_1(Qnone);
    else {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	stub_info = Nil;
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
	stub_info = validated_elt;
	gensymed_symbol = stub_info;
	gensymed_symbol_1 = make_phrase_list(FIX((SI_Long)8L));
	gensymed_symbol_2 = gensymed_symbol_1;
	car_new_value = estructure_slot(gensymed_symbol,Qportname,Nil);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	car_new_value = estructure_slot(gensymed_symbol,Qconnection_class,Nil);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	car_new_value = estructure_slot(gensymed_symbol,Qstub_direction,Nil);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	car_new_value = estructure_slot(gensymed_symbol,Qedge_location,Nil);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	car_new_value = estructure_slot(gensymed_symbol,
		Qcoordinate_location,Nil);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	car_new_value = estructure_slot(gensymed_symbol,Qstyle,Nil);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnection_line_pattern),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_3 = function;
	    gensymed_symbol_4 = estructure_slot(gensymed_symbol,
		    Qline_pattern,Nil);
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    gensymed_symbol_7 = Nil;
	    result = inline_funcall_4(gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6,gensymed_symbol_7);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else;
	M_CAR(gensymed_symbol_2) = parse_result_or_bad_phrase;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnection_arrows),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_3 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qconnection_arrows,Nil);
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    result = inline_funcall_4(gensymed_symbol_3,gensymed_symbol,
		    gensymed_symbol_4,gensymed_symbol_5,gensymed_symbol_6);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else;
	M_CAR(gensymed_symbol_2) = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(gensymed_symbol_1,Nil);
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
	result = phrase_cons(Qsc,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_connections_qm_evaluation_setter:
    return result;
}

static Object Qsolid;              /* solid */

/* CONNECTIONS?-EVALUATION-GETTER */
Object connections_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, stub_info, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, gensymed_symbol_2;
    Object source_portname, source_connection_class, source_stub_direction;
    Object source_edge_location, source_coordinate_location, source_style;
    Object source_line_pattern, source_connection_arrows, value;
    Object category_evaluator_interface, function, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, line_pattern_value;

    x_note_fn_call(201,76);
    if (slot_value) {
	if (EQ(slot_value,Qnone) || CONSP(slot_value) &&  
		!TRUEP(CDR(slot_value)))
	    temp = Nil;
	else if (SYMBOLP(slot_value))
	    temp = slot_value;
	else {
	    slot_value = CDR(slot_value);
	    stub_info = Nil;
	    ab_loop_list_ = slot_value;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    stub_info = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	    gensymed_symbol_2 = stub_info;
	    source_portname = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_connection_class = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_stub_direction = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_edge_location = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_coordinate_location = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_style = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_line_pattern = CAR(gensymed_symbol_2);
	    gensymed_symbol_2 = CDR(gensymed_symbol_2);
	    source_connection_arrows = CAR(gensymed_symbol_2);
	    value = source_portname;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,Qportname,
			value);
	    value = source_connection_class;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qconnection_class,value);
	    value = source_stub_direction;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qstub_direction,value);
	    value = source_edge_location;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qedge_location,value);
	    value = source_coordinate_location;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qcoordinate_location,value);
	    value = source_style;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,Qstyle,value);
	    value = source_connection_arrows;
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qconnection_arrows,value);
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnection_line_pattern),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol_2 = function;
		gensymed_symbol_3 = source_line_pattern;
		gensymed_symbol_4 = Nil;
		gensymed_symbol_5 = Nil;
		line_pattern_value = inline_funcall_3(gensymed_symbol_2,
			gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	    }
	    else
		line_pattern_value = Nil;
	    if ( !EQ(line_pattern_value,Qsolid)) {
		value = line_pattern_value;
		if (value)
		    set_evaluation_structure_slot(gensymed_symbol_1,
			    Qline_pattern,value);
	    }
	    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    temp = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_27;    /* # */

static Object list_constant_28;    /* # */

/* STUB-LENGTH-EVALUATION-SETTER */
Object stub_length_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,77);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_27))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_28,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_stub_length_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qinherited))
	result = VALUES_1(Nil);
    else if (FIXNUMP(evaluation_value) || evaluation_value && 
	    SYMBOLP(evaluation_value))
	result = VALUES_1(evaluation_value);
    else
	result = copy_evaluation_value_1(evaluation_value);
  end_stub_length_evaluation_setter:
    return result;
}

/* STUB-LENGTH-EVALUATION-GETTER */
Object stub_length_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(201,78);
    GENSYM_RETURN_ONE(slot_value ? (FIXNUMP(slot_value) || slot_value && 
	    SYMBOLP(slot_value) ? slot_value : 
	    copy_evaluation_value_1(slot_value)) : Qinherited);
    return VALUES_1(Nil);
}

static Object list_constant_29;    /* # */

/* JUNCTION-CLASS-EVALUATION-SETTER */
Object junction_class_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,79);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_29))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_24,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_junction_class_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qnone))
	result = VALUES_1(Nil);
    else
	result = VALUES_1(evaluation_value);
  end_junction_class_evaluation_setter:
    return result;
}

/* JUNCTION-CLASS-EVALUATION-GETTER */
Object junction_class_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(201,80);
    temp = slot_value;
    if (temp);
    else
	temp = Qnone;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_30;    /* # */

/* CLASS-EVALUATION-SETTER */
Object class_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,81);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_30))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_24,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_class_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qnone))
	result = VALUES_1(Nil);
    else
	result = VALUES_1(evaluation_value);
  end_class_evaluation_setter:
    return result;
}

/* CLASS-EVALUATION-GETTER */
Object class_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(201,82);
    temp = slot_value;
    if (temp);
    else
	temp = Qnone;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_31;    /* # */

/* RELATION-NAME?-EVALUATION-SETTER */
Object relation_name_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(201,83);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_31))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_24,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_relation_name_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value)
	result = VALUES_1(evaluation_value);
    else
	result = VALUES_1(Qnone);
  end_relation_name_qm_evaluation_setter:
    return result;
}

/* RELATION-NAME?-EVALUATION-GETTER */
Object relation_name_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(201,84);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

void grammar6b_INIT()
{
    Object focal_objects_evaluation_setter_1;
    Object focal_objects_evaluation_getter_1, categories_evaluation_setter_1;
    Object categories_evaluation_getter_1;
    Object authors_with_time_of_last_edit_qm_evaluation_setter_1;
    Object authors_with_time_of_last_edit_qm_evaluation_getter_1;
    Object attribute_descriptions_evaluation_setter_1;
    Object attribute_descriptions_evaluation_getter_1;
    Object inherited_attributes_evaluation_getter_1;
    Object history_specification_evaluation_setter_1;
    Object history_specification_evaluation_getter_1;
    Object list_of_classes_evaluation_setter_1;
    Object list_of_classes_evaluation_getter_1;
    Object list_of_object_classes_evaluation_setter_1;
    Object list_of_object_classes_evaluation_getter_1;
    Object list_of_connection_classes_evaluation_setter_1;
    Object list_of_connection_classes_evaluation_getter_1;
    Object list_of_message_classes_evaluation_setter_1;
    Object list_of_message_classes_evaluation_getter_1;
    Object class_inheritance_path_of_definition_evaluation_getter_1;
    Object attribute_displays_spec_qm_evaluation_setter_1;
    Object attribute_displays_spec_qm_evaluation_getter_1;
    Object new_class_evaluation_setter_1, new_class_evaluation_getter_1;
    Object list_of_slots_evaluation_getter_1;
    Object connections_qm_evaluation_setter_1;
    Object connections_qm_evaluation_getter_1, stub_length_evaluation_setter_1;
    Object stub_length_evaluation_getter_1, junction_class_evaluation_setter_1;
    Object junction_class_evaluation_getter_1, class_evaluation_setter_1;
    Object class_evaluation_getter_1, relation_name_qm_evaluation_setter_1;
    Object relation_name_qm_evaluation_getter_1;
    Object Qrelation_name_qm, Qnamed, Qtype_specification_simple_expansion;
    Object AB_package, Qjunction_class, Qstub_length, list_constant_80, Qab_or;
    Object Qconnections_qm, list_constant_125, list_constant_108;
    Object list_constant_72, list_constant_124, list_constant_123;
    Object list_constant_122, list_constant_121, list_constant_120;
    Object list_constant_119, list_constant_118, list_constant_117;
    Object list_constant_116, list_constant_115, list_constant_114;
    Object list_constant_113, list_constant_112, Qorthogonal, Qdiagonal;
    Object list_constant_36, list_constant_111, Qleft, Qright, Qbottom, Qtop;
    Object list_constant_110, list_constant_51, list_constant_88;
    Object Qlist_of_slots, list_constant_33, Qnew_class;
    Object Qattribute_displays_spec_qm, list_constant_109, list_constant_107;
    Object list_constant_106, list_constant_105, list_constant_104;
    Object list_constant_103, list_constant_102, list_constant_101;
    Object list_constant_100, list_constant_99, list_constant_98;
    Object list_constant_97, list_constant_96, Qat_standard_position;
    Object list_constant_95, list_constant_94, list_constant_93;
    Object list_constant_92, list_constant_91, list_constant_90;
    Object list_constant_89, list_constant_58, list_constant_87;
    Object Qlist_of_message_classes, Qlist_of_connection_classes;
    Object Qlist_of_object_classes, Qlist_of_classes, Qhistory_specification;
    Object list_constant_86, list_constant_85, list_constant_84;
    Object list_constant_83, list_constant_82, list_constant_81;
    Object list_constant_35, Qinherited_attributes, list_constant_79;
    Object list_constant_78, list_constant_77, list_constant_76;
    Object list_constant_75, list_constant_70, list_constant_74;
    Object list_constant_64, list_constant_63, list_constant_61;
    Object list_constant_60, list_constant_68, list_constant_67;
    Object list_constant_66, Qattribute_descriptions, Qindexed, Qfree_text;
    Object Qtime_stamp, Qinterval, list_constant_73, list_constant_71;
    Object list_constant_69, list_constant_65, list_constant_62;
    Object list_constant_59, list_constant_34, list_constant_57;
    Object list_constant_56, list_constant_55, list_constant_54;
    Object list_constant_53, list_constant_52, list_constant_32;
    Object Qwrite_history_specification_from_slot;
    Object Qcompile_history_specification_for_slot, string_constant_111;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object Qscan_interval, Qrule_scan_interval, Qstatement_text;
    Object Qbox_translation_and_text, Qsimulation_subtable;
    Object Qsimulation_formula, Qsimulation_formulas_qm;
    Object Qtime_increment_for_update, Qtime_increment_for_update_qm;
    Object Qhistory_keeping_spec, Qsimulation_stored_history_specification_qm;
    Object Qvariable_or_parameter, Qinitial_value_for_simulation;
    Object Qnon_default_initial_simulated_value_qm, Qformula, Qformula_qm;
    Object Qdefault_update_interval, Qbackground_collection_interval_qm;
    Object Qlast_recorded_value, Qcurrent_value_of_variable_or_parameter;
    Object Qdata_type, Qcategories, Qrule_categories;
    Object Qattribute_initializations, Qdefault_overrides, Qchange_log;
    Object Qframe_change_log, Qframe_author_or_authors, Qtime_of_latest_change;
    Object Qframe_timestamp_qm, Qnotes, Qframe_status_and_notes, Qnames;
    Object Qname_or_names_for_frame, Qfilter_and_normalize_time_of_day;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_100;
    Object Qauthors_with_time_of_last_edit_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object list_constant_37;
    Object Qwrite_authors_with_time_of_last_edit_qm_from_slot;
    Object Qcompile_authors_with_time_of_last_edit_qm_for_slot;
    Object Qconvert_local_date_to_edit_timestamp;
    Object Qtransform_date_phrase_and_time_of_day_into_frame_edit_timestamp;
    Object Qauthor, Qauthors_list, string_constant_99, string_constant_98;
    Object Qwrite_simulator_class_from_slot, Qsimulator_class;
    Object string_constant_97, Qvalue_on_activation_qm;
    Object Qpercentage_extra_space_to_leave;
    Object Qwrite_default_overrides_for_message_definitions_from_slot;
    Object Qdefault_overrides_for_message_definitions;
    Object Qwrite_default_overrides_for_connection_definitions_from_slot;
    Object Qdefault_overrides_for_connection_definitions;
    Object Qwrite_default_overrides_for_object_definitions_from_slot;
    Object Qdefault_overrides_for_object_definitions;
    Object Qwrite_default_overrides_for_class_definitions_from_slot;
    Object Qdefault_overrides_for_class_definitions;
    Object Qcompile_default_overrides_for_message_definitions_for_slot;
    Object Qcompile_default_overrides_for_connection_definitions_for_slot;
    Object Qcompile_default_overrides_for_object_definitions_for_slot;
    Object Qcompile_default_overrides_for_class_definitions_for_slot;
    Object Qfix_default_override_on_user_defined_slot;
    Object Qwrite_categories_from_slot, Qcompile_categories_for_slot;
    Object string_constant_96, Qsimplify_associative_operation;
    Object Qwrite_focal_objects_from_slot, Qfocal_objects, Qno_item;
    Object Qcompile_focal_objects_for_slot, string_constant_95;
    Object Qwrite_focal_classes_from_slot, string_constant_94;
    Object Qwrite_name_or_names_from_slot, Qname_or_names;
    Object Qcompile_name_or_names_for_slot, Qitem_name;
    Object Qwrite_connections_qm_from_slot;
    Object Qwrite_attribute_descriptions_from_slot;
    Object Qcompile_connections_qm_for_slot;

    x_note_fn_call(201,85);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qconnections_qm = STATIC_SYMBOL("CONNECTIONS\?",AB_package);
    Qcompile_connections_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONNECTIONS\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_connections_qm_for_slot,
	    STATIC_FUNCTION(compile_connections_qm_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qconnections_qm,
	    SYMBOL_FUNCTION(Qcompile_connections_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qconnections_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qinherited = STATIC_SYMBOL("INHERITED",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qstubs = STATIC_SYMBOL("STUBS",AB_package);
    string_constant = 
	    STATIC_STRING("Coordinates must be positive and of reasonable size");
    string_constant_1 = STATIC_STRING(";~%");
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qattribute_descriptions = STATIC_SYMBOL("ATTRIBUTE-DESCRIPTIONS",
	    AB_package);
    Qwrite_attribute_descriptions_from_slot = 
	    STATIC_SYMBOL("WRITE-ATTRIBUTE-DESCRIPTIONS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_attribute_descriptions_from_slot,
	    STATIC_FUNCTION(write_attribute_descriptions_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qattribute_descriptions,
	    SYMBOL_FUNCTION(Qwrite_attribute_descriptions_from_slot),
	    Qslot_value_writer);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qindexed_attributes_for_definition = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTES-FOR-DEFINITION",AB_package);
    string_constant_2 = STATIC_STRING("~(~a::~a~)");
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qinstantiate_variable = STATIC_SYMBOL("INSTANTIATE-VARIABLE",AB_package);
    string_constant_3 = STATIC_STRING(" is given by ");
    string_constant_4 = STATIC_STRING(" is an instance of ");
    string_constant_5 = STATIC_STRING(",");
    string_constant_6 = STATIC_STRING(" is a structure,");
    string_constant_7 = STATIC_STRING(" is a sequence,");
    string_constant_8 = STATIC_STRING(" is ");
    string_constant_9 = STATIC_STRING(" ");
    string_constant_10 = STATIC_STRING("~( has values ~a or ~a~)");
    string_constant_11 = STATIC_STRING(" has values ");
    string_constant_12 = STATIC_STRING("or");
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    string_constant_13 = STATIC_STRING(" initially is given by ");
    string_constant_14 = STATIC_STRING(" initially is an instance of ");
    string_constant_15 = STATIC_STRING(" initially is ");
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_16 = STATIC_STRING(", with an index");
    string_constant_17 = STATIC_STRING("inherited");
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    string_constant_18 = STATIC_STRING("input ");
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    string_constant_19 = STATIC_STRING("output ");
    string_constant_20 = STATIC_STRING("");
    string_constant_21 = STATIC_STRING("~(~a~a~a~a~a located at ~a ~d~)");
    string_constant_22 = STATIC_STRING("~( with style ~a~)");
    string_constant_23 = STATIC_STRING(" and");
    string_constant_24 = STATIC_STRING(" with line-pattern ");
    Qconnection_line_pattern = STATIC_SYMBOL("CONNECTION-LINE-PATTERN",
	    AB_package);
    string_constant_25 = STATIC_STRING("[deleted attribute]");
    string_constant_26 = STATIC_STRING(" with connection-arrows ");
    Qconnection_arrows = STATIC_SYMBOL("CONNECTION-ARROWS",AB_package);
    Qwrite_connections_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-CONNECTIONS\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_connections_qm_from_slot,
	    STATIC_FUNCTION(write_connections_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qconnections_qm,
	    SYMBOL_FUNCTION(Qwrite_connections_qm_from_slot),
	    Qslot_value_writer);
    Qname_or_names = STATIC_SYMBOL("NAME-OR-NAMES",AB_package);
    Qitem_name = STATIC_SYMBOL("ITEM-NAME",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    add_grammar_rules_for_list(5,Qname_or_names,Qitem_name,Qcm,Nil,Qnone);
    Qcompile_name_or_names_for_slot = 
	    STATIC_SYMBOL("COMPILE-NAME-OR-NAMES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_name_or_names_for_slot,
	    STATIC_FUNCTION(compile_name_or_names_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qname_or_names,
	    SYMBOL_FUNCTION(Qcompile_name_or_names_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qname_or_names,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_1 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_name_or_names_from_slot = 
	    STATIC_SYMBOL("WRITE-NAME-OR-NAMES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_name_or_names_from_slot,
	    STATIC_FUNCTION(write_name_or_names_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qname_or_names,
	    SYMBOL_FUNCTION(Qwrite_name_or_names_from_slot),
	    Qslot_value_writer);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_94 = 
	    STATIC_STRING("1o1m838My1m9k83Zy1m838My83-UIy1m83-UIy83-Gy1o83-UIy1n83-Gy1m9k83vy83-UIy1n83-tyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_94));
    string_constant_27 = STATIC_STRING(", ");
    Qfocal_classes = STATIC_SYMBOL("FOCAL-CLASSES",AB_package);
    Qwrite_focal_classes_from_slot = 
	    STATIC_SYMBOL("WRITE-FOCAL-CLASSES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_focal_classes_from_slot,
	    STATIC_FUNCTION(write_focal_classes_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qfocal_classes,
	    SYMBOL_FUNCTION(Qwrite_focal_classes_from_slot),
	    Qslot_value_writer);
    string_constant_28 = STATIC_STRING("~(~NF~)");
    string_constant_29 = STATIC_STRING("~(~A~)");
    string_constant_30 = STATIC_STRING(", ~a ");
    string_constant_95 = 
	    STATIC_STRING("1o1m838Ny1m9k83Zy1m838Ny83-UKy1m83-UKy839Wy1o83-UKy1n839Wy1m9k83vy83-UKy1n83-tyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_95));
    Qfocal_objects = STATIC_SYMBOL("FOCAL-OBJECTS",AB_package);
    Qcompile_focal_objects_for_slot = 
	    STATIC_SYMBOL("COMPILE-FOCAL-OBJECTS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_focal_objects_for_slot,
	    STATIC_FUNCTION(compile_focal_objects_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qfocal_objects,
	    SYMBOL_FUNCTION(Qcompile_focal_objects_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfocal_objects,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_7 = STATIC_CONS(Qno_item,Qnil);
    list_constant_11 = STATIC_CONS(Qsequence,Qnil);
    list_constant_33 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_11);
    set_property_value_function(get_symbol_properties_function(Qfocal_objects),
	    Qtype_specification_simple_expansion,list_constant_33);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qsequence,Qsymbol,
	    FIX((SI_Long)1L));
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_34);
    define_type_specification_explicit_complex_type(Qfocal_objects,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qfocal_objects);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    focal_objects_evaluation_setter_1 = 
	    STATIC_FUNCTION(focal_objects_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfocal_objects,
	    focal_objects_evaluation_setter_1);
    focal_objects_evaluation_getter_1 = 
	    STATIC_FUNCTION(focal_objects_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfocal_objects,
	    focal_objects_evaluation_getter_1);
    Qwrite_focal_objects_from_slot = 
	    STATIC_SYMBOL("WRITE-FOCAL-OBJECTS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_focal_objects_from_slot,
	    STATIC_FUNCTION(write_focal_objects_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qfocal_objects,
	    SYMBOL_FUNCTION(Qwrite_focal_objects_from_slot),
	    Qslot_value_writer);
    string_constant_96 = 
	    STATIC_STRING("1o1m837sy1m9k83Zy1m837sy83-Lby1m83-Lby83mXy1o83-Lby1n83mXy1m9k83vy83-Lby1n83-tyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_96));
    Qcategories = STATIC_SYMBOL("CATEGORIES",AB_package);
    Qcompile_categories_for_slot = 
	    STATIC_SYMBOL("COMPILE-CATEGORIES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_categories_for_slot,
	    STATIC_FUNCTION(compile_categories_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qcategories,
	    SYMBOL_FUNCTION(Qcompile_categories_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qcategories,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qcategories),
	    Qtype_specification_simple_expansion,list_constant_33);
    define_type_specification_explicit_complex_type(Qcategories,
	    list_constant_1);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,Qcategories);
    categories_evaluation_setter_1 = 
	    STATIC_FUNCTION(categories_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qcategories,
	    categories_evaluation_setter_1);
    categories_evaluation_getter_1 = 
	    STATIC_FUNCTION(categories_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcategories,
	    categories_evaluation_getter_1);
    Qwrite_categories_from_slot = 
	    STATIC_SYMBOL("WRITE-CATEGORIES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_categories_from_slot,
	    STATIC_FUNCTION(write_categories_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qcategories,
	    SYMBOL_FUNCTION(Qwrite_categories_from_slot),Qslot_value_writer);
    Quser_defined = STATIC_SYMBOL("USER-DEFINED",AB_package);
    Qfix_default_override_on_user_defined_slot = 
	    STATIC_SYMBOL("FIX-DEFAULT-OVERRIDE-ON-USER-DEFINED-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfix_default_override_on_user_defined_slot,
	    STATIC_FUNCTION(fix_default_override_on_user_defined_slot,NIL,
	    FALSE,1,1));
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    string_constant_31 = STATIC_STRING("~a");
    string_constant_32 = 
	    STATIC_STRING("The initial value for ~a could not be compiled.");
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qcar_equal = STATIC_SYMBOL("CAR-EQUAL",AB_package);
    SET_SYMBOL_FUNCTION(Qcar_equal,STATIC_FUNCTION(car_equal,NIL,FALSE,2,2));
    string_constant_33 = 
	    STATIC_STRING("This attribute initialization list has duplicate attribute names.");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qforward_chain_flag = STATIC_SYMBOL("FORWARD-CHAIN-FLAG",AB_package);
    Qalways_forward_chain_if_possible_flag = 
	    STATIC_SYMBOL("ALWAYS-FORWARD-CHAIN-IF-POSSIBLE-FLAG",AB_package);
    Qpassive_flag = STATIC_SYMBOL("PASSIVE-FLAG",AB_package);
    Qdont_backward_chain_flag = STATIC_SYMBOL("DONT-BACKWARD-CHAIN-FLAG",
	    AB_package);
    Qdepth_first_flag = STATIC_SYMBOL("DEPTH-FIRST-FLAG",AB_package);
    Qcache_data_for_explanation_flag = 
	    STATIC_SYMBOL("CACHE-DATA-FOR-EXPLANATION-FLAG",AB_package);
    Qinitial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    string_constant_34 = STATIC_STRING("The initial value, ");
    string_constant_35 = 
	    STATIC_STRING(", is not compatible ~\n                                         with the type of the variable, ~NT.");
    Qinterface_timeout_period = STATIC_SYMBOL("INTERFACE-TIMEOUT-PERIOD",
	    AB_package);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    string_constant_36 = STATIC_STRING("Bad g2-array length.");
    Qg2_array_element_type = STATIC_SYMBOL("G2-ARRAY-ELEMENT-TYPE",AB_package);
    string_constant_37 = 
	    STATIC_STRING("You cannot use ~a, since it names a value type, and ~\n                            so cannot be a class name.");
    Qlist_type = STATIC_SYMBOL("LIST-TYPE",AB_package);
    string_constant_38 = 
	    STATIC_STRING("The following are not inheritable system attributes ~\n                     for this class: ");
    string_constant_39 = STATIC_STRING("~(~a~)");
    string_constant_40 = 
	    STATIC_STRING("interface-timeout-period should be a value between 1 and 16 seconds");
    array_constant_2 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)42L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)45L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)48L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)50L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)51L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)52L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)54L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)62L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)63L,(SI_Long)57344L);
    Qdefault_overrides_for_class_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS",
	    AB_package);
    Qcompile_default_overrides_for_class_definitions_for_slot = 
	    STATIC_SYMBOL("COMPILE-DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_default_overrides_for_class_definitions_for_slot,
	    STATIC_FUNCTION(compile_default_overrides_for_class_definitions_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qdefault_overrides_for_class_definitions,
	    SYMBOL_FUNCTION(Qcompile_default_overrides_for_class_definitions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdefault_overrides_for_class_definitions,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    string_constant_41 = 
	    STATIC_STRING("The following are not attributes of ~(~A~): ");
    string_constant_42 = STATIC_STRING(" for ~(~a~)");
    Qdefault_overrides_for_object_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS",
	    AB_package);
    Qcompile_default_overrides_for_object_definitions_for_slot = 
	    STATIC_SYMBOL("COMPILE-DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_default_overrides_for_object_definitions_for_slot,
	    STATIC_FUNCTION(compile_default_overrides_for_object_definitions_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qdefault_overrides_for_object_definitions,
	    SYMBOL_FUNCTION(Qcompile_default_overrides_for_object_definitions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdefault_overrides_for_object_definitions,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qdefault_overrides_for_connection_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS",
	    AB_package);
    Qcompile_default_overrides_for_connection_definitions_for_slot = 
	    STATIC_SYMBOL("COMPILE-DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_default_overrides_for_connection_definitions_for_slot,
	    STATIC_FUNCTION(compile_default_overrides_for_connection_definitions_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qdefault_overrides_for_connection_definitions,
	    SYMBOL_FUNCTION(Qcompile_default_overrides_for_connection_definitions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdefault_overrides_for_connection_definitions,
	    Nil,Quse_slot_value_compiler_for_default_overrides_p);
    Qdefault_overrides_for_message_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS",
	    AB_package);
    Qcompile_default_overrides_for_message_definitions_for_slot = 
	    STATIC_SYMBOL("COMPILE-DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_default_overrides_for_message_definitions_for_slot,
	    STATIC_FUNCTION(compile_default_overrides_for_message_definitions_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qdefault_overrides_for_message_definitions,
	    SYMBOL_FUNCTION(Qcompile_default_overrides_for_message_definitions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdefault_overrides_for_message_definitions,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qdata_type_of_variable_or_parameter = 
	    STATIC_SYMBOL("DATA-TYPE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qwrite_default_overrides_for_class_definitions_from_slot = 
	    STATIC_SYMBOL("WRITE-DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_default_overrides_for_class_definitions_from_slot,
	    STATIC_FUNCTION(write_default_overrides_for_class_definitions_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdefault_overrides_for_class_definitions,
	    SYMBOL_FUNCTION(Qwrite_default_overrides_for_class_definitions_from_slot),
	    Qslot_value_writer);
    Qwrite_default_overrides_for_object_definitions_from_slot = 
	    STATIC_SYMBOL("WRITE-DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_default_overrides_for_object_definitions_from_slot,
	    STATIC_FUNCTION(write_default_overrides_for_object_definitions_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdefault_overrides_for_object_definitions,
	    SYMBOL_FUNCTION(Qwrite_default_overrides_for_object_definitions_from_slot),
	    Qslot_value_writer);
    Qwrite_default_overrides_for_connection_definitions_from_slot = 
	    STATIC_SYMBOL("WRITE-DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_default_overrides_for_connection_definitions_from_slot,
	    STATIC_FUNCTION(write_default_overrides_for_connection_definitions_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdefault_overrides_for_connection_definitions,
	    SYMBOL_FUNCTION(Qwrite_default_overrides_for_connection_definitions_from_slot),
	    Qslot_value_writer);
    Qwrite_default_overrides_for_message_definitions_from_slot = 
	    STATIC_SYMBOL("WRITE-DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_default_overrides_for_message_definitions_from_slot,
	    STATIC_FUNCTION(write_default_overrides_for_message_definitions_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdefault_overrides_for_message_definitions,
	    SYMBOL_FUNCTION(Qwrite_default_overrides_for_message_definitions_from_slot),
	    Qslot_value_writer);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    string_constant_43 = STATIC_STRING("~( initially is ~a~)");
    Qquantitative_variable = STATIC_SYMBOL("QUANTITATIVE-VARIABLE",AB_package);
    Qquantitative_parameter = STATIC_SYMBOL("QUANTITATIVE-PARAMETER",
	    AB_package);
    Qsensor = STATIC_SYMBOL("SENSOR",AB_package);
    string_constant_44 = STATIC_STRING("data-type for ~(~a~): ");
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    string_constant_45 = STATIC_STRING("validity-interval: ");
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qmake_simulation_subtable_with_specific_class_and_install = 
	    STATIC_SYMBOL("MAKE-SIMULATION-SUBTABLE-WITH-SPECIFIC-CLASS-AND-INSTALL",
	    AB_package);
    string_constant_46 = STATIC_STRING("supply-simulation-subtable: ~(~a~)");
    string_constant_47 = 
	    STATIC_STRING("supply-simulation-subtable: simulation-subtable");
    Qattribute_displays_for_class = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAYS-FOR-CLASS",AB_package);
    string_constant_48 = STATIC_STRING("attribute-displays: ");
    Qcross_section_pattern_for_class = 
	    STATIC_SYMBOL("CROSS-SECTION-PATTERN-FOR-CLASS",AB_package);
    string_constant_49 = STATIC_STRING("cross-section-pattern: ");
    Qinsert_duplicate_elements_qm = 
	    STATIC_SYMBOL("INSERT-DUPLICATE-ELEMENTS\?",AB_package);
    string_constant_50 = 
	    STATIC_STRING("allow-duplicate-elements-for-g2-list: ~a");
    string_constant_51 = STATIC_STRING("yes");
    string_constant_52 = STATIC_STRING("no");
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    string_constant_53 = STATIC_STRING("options-for-~(~a~): ");
    Qvariable_or_parameter_history_specification_qm = 
	    STATIC_SYMBOL("VARIABLE-OR-PARAMETER-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qhistory_specification_for_simulation_subtables_qm = 
	    STATIC_SYMBOL("HISTORY-SPECIFICATION-FOR-SIMULATION-SUBTABLES\?",
	    AB_package);
    string_constant_54 = STATIC_STRING("history-keeping-spec for ");
    string_constant_55 = STATIC_STRING("simulation-subtable: ");
    string_constant_56 = STATIC_STRING("variable-or-parameter: ");
    Quser_menu_choice_priority = STATIC_SYMBOL("USER-MENU-CHOICE-PRIORITY",
	    AB_package);
    Qaction_button_priority = STATIC_SYMBOL("ACTION-BUTTON-PRIORITY",
	    AB_package);
    string_constant_57 = STATIC_STRING("action-priority for ");
    string_constant_58 = STATIC_STRING("action-button: ");
    string_constant_59 = STATIC_STRING("user-menu-choice: ");
    Qpercentage_extra_space_to_leave = 
	    STATIC_SYMBOL("PERCENTAGE-EXTRA-SPACE-TO-LEAVE",AB_package);
    Qvalue_on_activation_qm = STATIC_SYMBOL("VALUE-ON-ACTIVATION\?",
	    AB_package);
    Qoff_value_for_check_box = STATIC_SYMBOL("OFF-VALUE-FOR-CHECK-BOX",
	    AB_package);
    Qon_value_for_check_box = STATIC_SYMBOL("ON-VALUE-FOR-CHECK-BOX",
	    AB_package);
    Qvalue_for_radio_button = STATIC_SYMBOL("VALUE-FOR-RADIO-BUTTON",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)5L,
	    Qpercentage_extra_space_to_leave,Qvalue_on_activation_qm,
	    Qoff_value_for_check_box,Qon_value_for_check_box,
	    Qvalue_for_radio_button);
    string_constant_60 = STATIC_STRING("on-value for check-box: ");
    string_constant_61 = STATIC_STRING("on-value for radio-button: ");
    string_constant_62 = STATIC_STRING("off-value for check-box: ");
    string_constant_63 = STATIC_STRING("~(~A~): ");
    string_constant_64 = STATIC_STRING("initial-value for ~(~a~): ");
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qtruth_value,Qnumber);
    Qg2_array_initial_values = STATIC_SYMBOL("G2-ARRAY-INITIAL-VALUES",
	    AB_package);
    string_constant_65 = STATIC_STRING("initial-values for ~(~a~): ");
    Qquantity_array = STATIC_SYMBOL("QUANTITY-ARRAY",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    Qsymbol_array = STATIC_SYMBOL("SYMBOL-ARRAY",AB_package);
    Qtext_array = STATIC_SYMBOL("TEXT-ARRAY",AB_package);
    Qtruth_value_array = STATIC_SYMBOL("TRUTH-VALUE-ARRAY",AB_package);
    Qitem_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    Qvalue_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    string_constant_66 = STATIC_STRING("element-type for item-list: ~(~a~)");
    string_constant_67 = STATIC_STRING("element-type for item-array: ~(~a~)");
    string_constant_68 = STATIC_STRING("array-length for g2-array: ~(~a~)");
    Qstubs_for_class = STATIC_SYMBOL("STUBS-FOR-CLASS",AB_package);
    string_constant_69 = STATIC_STRING("stubs: ");
    string_constant_97 = 
	    STATIC_STRING("1o1n83-q+y1m1m9k83-RSy1m9k83nOy83gly1n83-q+y1m1m9k83gIy1m9k83nOy83gJy1m83-q+y1m9k83uxy1m83-q+y1m9k83dy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_97));
    Qsimulator_class = STATIC_SYMBOL("SIMULATOR-CLASS",AB_package);
    Qwrite_simulator_class_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMULATOR-CLASS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simulator_class_from_slot,
	    STATIC_FUNCTION(write_simulator_class_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qsimulator_class,
	    SYMBOL_FUNCTION(Qwrite_simulator_class_from_slot),
	    Qslot_value_writer);
    Qtransform_date_phrase_and_time_of_day_into_frame_edit_timestamp = 
	    STATIC_SYMBOL("TRANSFORM-DATE-PHRASE-AND-TIME-OF-DAY-INTO-FRAME-EDIT-TIMESTAMP",
	    AB_package);
    Qconvert_local_date_to_edit_timestamp = 
	    STATIC_SYMBOL("CONVERT-LOCAL-DATE-TO-EDIT-TIMESTAMP",AB_package);
    string_constant_98 = 
	    STATIC_STRING("1s1m83-*y1m9k83Zy1m83-*y83-U6y1n83-*y1n83-U6y1m9k83vy83-KEy1mln1m83-U6y83q=y1n83-U6y1o83q=y1m9k83-9y83wvy1m9k83-Ay2lln1o83wvy1m8");
    string_constant_99 = 
	    STATIC_STRING("355y83nty1mlm9l1o83uYy8355yl9m1m83q=y83-2y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_frame_edit_timestamp);
    push_optimized_constant(Qconvert_local_date_to_edit_timestamp);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_98,
	    string_constant_99)));
    Qauthors_list = STATIC_SYMBOL("AUTHORS-LIST",AB_package);
    Qauthor = STATIC_SYMBOL("AUTHOR",AB_package);
    add_grammar_rules_for_list(5,Qauthors_list,Qauthor,Qcm,Nil,Nil);
    SET_SYMBOL_FUNCTION(Qtransform_date_phrase_and_time_of_day_into_frame_edit_timestamp,
	    STATIC_FUNCTION(transform_date_phrase_and_time_of_day_into_frame_edit_timestamp,
	    NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qtransform_date_phrase_and_time_of_day_into_frame_edit_timestamp);
    SET_SYMBOL_FUNCTION(Qconvert_local_date_to_edit_timestamp,
	    STATIC_FUNCTION(convert_local_date_to_edit_timestamp,NIL,FALSE,
	    1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qconvert_local_date_to_edit_timestamp);
    string_constant_70 = 
	    STATIC_STRING("Bad date: can\'t go back that far in time");
    string_constant_71 = 
	    STATIC_STRING("Bad date: can\'t go forward that far in time");
    string_constant_72 = STATIC_STRING("Bad date: ");
    string_constant_73 = STATIC_STRING(".  It cannot be earlier than ");
    Qauthors_with_time_of_last_edit_qm = 
	    STATIC_SYMBOL("AUTHORS-WITH-TIME-OF-LAST-EDIT\?",AB_package);
    Qcompile_authors_with_time_of_last_edit_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-AUTHORS-WITH-TIME-OF-LAST-EDIT\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_authors_with_time_of_last_edit_qm_for_slot,
	    STATIC_FUNCTION(compile_authors_with_time_of_last_edit_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qauthors_with_time_of_last_edit_qm,
	    SYMBOL_FUNCTION(Qcompile_authors_with_time_of_last_edit_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qauthors_with_time_of_last_edit_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_5 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_authors_with_time_of_last_edit_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-AUTHORS-WITH-TIME-OF-LAST-EDIT\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_authors_with_time_of_last_edit_qm_from_slot,
	    STATIC_FUNCTION(write_authors_with_time_of_last_edit_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qauthors_with_time_of_last_edit_qm,
	    SYMBOL_FUNCTION(Qwrite_authors_with_time_of_last_edit_qm_from_slot),
	    Qslot_value_writer);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_8 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_35 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_8);
    set_property_value_function(get_symbol_properties_function(Qauthors_with_time_of_last_edit_qm),
	    Qtype_specification_simple_expansion,list_constant_35);
    Qtimestamp = STATIC_SYMBOL("TIMESTAMP",AB_package);
    Qyear = STATIC_SYMBOL("YEAR",AB_package);
    list_constant_36 = STATIC_CONS(Qinteger,Qnil);
    list_constant_37 = STATIC_CONS(Qyear,list_constant_36);
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    list_constant_38 = STATIC_CONS(Qmonth,list_constant_36);
    Qdate = STATIC_SYMBOL("DATE",AB_package);
    list_constant_39 = STATIC_CONS(Qdate,list_constant_36);
    Qhours = STATIC_SYMBOL("HOURS",AB_package);
    list_constant_40 = STATIC_CONS(Qhours,list_constant_36);
    Qminutes = STATIC_SYMBOL("MINUTES",AB_package);
    list_constant_41 = STATIC_CONS(Qminutes,list_constant_36);
    list_constant_42 = STATIC_LIST((SI_Long)5L,list_constant_37,
	    list_constant_38,list_constant_39,list_constant_40,
	    list_constant_41);
    list_constant_43 = STATIC_LIST((SI_Long)6L,Qand,Qyear,Qmonth,Qdate,
	    Qhours,Qminutes);
    list_constant_44 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_42,list_constant_43);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qtimestamp,list_constant_44);
    Qauthors = STATIC_SYMBOL("AUTHORS",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)3L,Qsequence,Qsymbol,
	    FIX((SI_Long)0L));
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qauthors,list_constant_45);
    list_constant_48 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_47);
    list_constant_49 = STATIC_LIST((SI_Long)2L,Qand,Qauthors);
    list_constant_50 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_48,list_constant_49);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_50);
    define_type_specification_explicit_complex_type(Qauthors_with_time_of_last_edit_qm,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qauthors_with_time_of_last_edit_qm);
    string_constant_74 = STATIC_STRING("timestamp out of range");
    string_constant_75 = 
	    STATIC_STRING("there cannot be a timestamp without an author");
    string_constant_76 = STATIC_STRING("~NT ");
    string_constant_77 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    authors_with_time_of_last_edit_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(authors_with_time_of_last_edit_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qauthors_with_time_of_last_edit_qm,
	    authors_with_time_of_last_edit_qm_evaluation_setter_1);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    authors_with_time_of_last_edit_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(authors_with_time_of_last_edit_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qauthors_with_time_of_last_edit_qm,
	    authors_with_time_of_last_edit_qm_evaluation_getter_1);
    Qfilter_and_normalize_time_of_day = 
	    STATIC_SYMBOL("FILTER-AND-NORMALIZE-TIME-OF-DAY",AB_package);
    string_constant_100 = 
	    STATIC_STRING("1r1o83ACy1o833Oy1m9k83-Py833Ty83n3y1nlno9l1m833Oy83-ey1m833Ty83-ey1m9m83-ey1m83-CTy9n1m83n3y1m9k83-Iry1m83n3y1m9k83-i9y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfilter_and_normalize_time_of_day);
    push_optimized_constant(Qsecond);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_100));
    string_constant_101 = 
	    STATIC_STRING("1l1o83ADy1q833Oy1m9k83-Py833Ty1m9k83-Py9l83n3y1olnqp9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsecond);
    push_optimized_constant(Qfilter_and_normalize_time_of_day);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_101));
    string_constant_102 = STATIC_STRING("1m1m83nty83ACy1m83nty83ADy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_102));
    string_constant_103 = 
	    STATIC_STRING("1l1o83-F=y1q833Oy1m9k83-Py833Ty1m9k83-Py83-CTy83n3y1olnqp9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfilter_and_normalize_time_of_day);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_103));
    string_constant_104 = 
	    STATIC_STRING("1n1m83nuy83ACy1m83nuy83ADy1m83nuy83-F=y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_104));
    string_constant_78 = STATIC_STRING("Hours must be between 1 and 12");
    string_constant_79 = STATIC_STRING("Hours must be between 0 and 23");
    string_constant_80 = STATIC_STRING("Minutes must be between 0 and 59");
    string_constant_81 = STATIC_STRING("Seconds must be between 0 and 59");
    Qp_dot_m_dot = STATIC_SYMBOL("P.M.",AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_and_normalize_time_of_day,
	    STATIC_FUNCTION(filter_and_normalize_time_of_day,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qfilter_and_normalize_time_of_day);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qnames = STATIC_SYMBOL("NAMES",AB_package);
    alias_slot_name(3,Qname_or_names_for_frame,Qnames,Qnil);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qnotes = STATIC_SYMBOL("NOTES",AB_package);
    alias_slot_name(3,Qframe_status_and_notes,Qnotes,Qnil);
    Qframe_timestamp_qm = STATIC_SYMBOL("FRAME-TIMESTAMP\?",AB_package);
    Qtime_of_latest_change = STATIC_SYMBOL("TIME-OF-LATEST-CHANGE",AB_package);
    alias_slot_name(3,Qframe_timestamp_qm,Qtime_of_latest_change,Qnil);
    Qframe_author_or_authors = STATIC_SYMBOL("FRAME-AUTHOR-OR-AUTHORS",
	    AB_package);
    alias_slot_name(3,Qframe_author_or_authors,Qauthors,Qnil);
    Qframe_change_log = STATIC_SYMBOL("FRAME-CHANGE-LOG",AB_package);
    Qchange_log = STATIC_SYMBOL("CHANGE-LOG",AB_package);
    alias_slot_name(3,Qframe_change_log,Qchange_log,Qnil);
    Qdefault_overrides = STATIC_SYMBOL("DEFAULT-OVERRIDES",AB_package);
    Qattribute_initializations = STATIC_SYMBOL("ATTRIBUTE-INITIALIZATIONS",
	    AB_package);
    alias_slot_name(3,Qdefault_overrides,Qattribute_initializations,Qnil);
    Qrule_categories = STATIC_SYMBOL("RULE-CATEGORIES",AB_package);
    alias_slot_name(3,Qrule_categories,Qcategories,Qnil);
    Qdata_type = STATIC_SYMBOL("DATA-TYPE",AB_package);
    alias_slot_name(3,Qdata_type_of_variable_or_parameter,Qdata_type,Qnil);
    Qcurrent_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("CURRENT-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qlast_recorded_value = STATIC_SYMBOL("LAST-RECORDED-VALUE",AB_package);
    alias_slot_name(3,Qcurrent_value_of_variable_or_parameter,
	    Qlast_recorded_value,Qnil);
    Qbackground_collection_interval_qm = 
	    STATIC_SYMBOL("BACKGROUND-COLLECTION-INTERVAL\?",AB_package);
    Qdefault_update_interval = STATIC_SYMBOL("DEFAULT-UPDATE-INTERVAL",
	    AB_package);
    alias_slot_name(3,Qbackground_collection_interval_qm,
	    Qdefault_update_interval,Qnil);
    Qformula_qm = STATIC_SYMBOL("FORMULA\?",AB_package);
    Qformula = STATIC_SYMBOL("FORMULA",AB_package);
    alias_slot_name(3,Qformula_qm,Qformula,Qnil);
    Qnon_default_initial_simulated_value_qm = 
	    STATIC_SYMBOL("NON-DEFAULT-INITIAL-SIMULATED-VALUE\?",AB_package);
    Qinitial_value_for_simulation = 
	    STATIC_SYMBOL("INITIAL-VALUE-FOR-SIMULATION",AB_package);
    alias_slot_name(3,Qnon_default_initial_simulated_value_qm,
	    Qinitial_value_for_simulation,Qnil);
    Qhistory_keeping_spec = STATIC_SYMBOL("HISTORY-KEEPING-SPEC",AB_package);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    alias_slot_name(3,Qvariable_or_parameter_history_specification_qm,
	    Qhistory_keeping_spec,Qvariable_or_parameter);
    Qsimulation_stored_history_specification_qm = 
	    STATIC_SYMBOL("SIMULATION-STORED-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    alias_slot_name(3,Qsimulation_stored_history_specification_qm,
	    Qhistory_keeping_spec,Qsimulation_subtable);
    Qtime_increment_for_update_qm = 
	    STATIC_SYMBOL("TIME-INCREMENT-FOR-UPDATE\?",AB_package);
    Qtime_increment_for_update = STATIC_SYMBOL("TIME-INCREMENT-FOR-UPDATE",
	    AB_package);
    alias_slot_name(3,Qtime_increment_for_update_qm,
	    Qtime_increment_for_update,Qnil);
    Qsimulation_formulas_qm = STATIC_SYMBOL("SIMULATION-FORMULAS\?",
	    AB_package);
    Qsimulation_formula = STATIC_SYMBOL("SIMULATION-FORMULA",AB_package);
    alias_slot_name(3,Qsimulation_formulas_qm,Qsimulation_formula,
	    Qsimulation_subtable);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qstatement_text = STATIC_SYMBOL("STATEMENT-TEXT",AB_package);
    alias_slot_name(3,Qbox_translation_and_text,Qstatement_text,Qnil);
    Qrule_scan_interval = STATIC_SYMBOL("RULE-SCAN-INTERVAL",AB_package);
    Qscan_interval = STATIC_SYMBOL("SCAN-INTERVAL",AB_package);
    alias_slot_name(3,Qrule_scan_interval,Qscan_interval,Qnil);
    string_constant_105 = 
	    STATIC_STRING("1t1n830hy1o1m9k830Iy1m9k9l1m9k83-bwy1m9k836xy83=Ty1n830hy1o1m9k83-bwy1m9k836xy1m9k83=Fy83-Y9y1m836xyo1n83-Y9y1r1m9k83kby1m9k83-H");
    string_constant_106 = 
	    STATIC_STRING("y1m9k83-Ty1m9k831Dy1m9k839iy1m9k9m83Sy1lr1n83-Y9y1t1m9k83kby1m9k83-Hy1m9k83-Ty1m9k831Dy1m9k839iy1m9k9m83Sy1m9k83vy83-YAy1nr0t1n8");
    string_constant_107 = 
	    STATIC_STRING("3-Y9y1r1m9k83kby1m9k83-JNy1m9k83-Ty1m9k831Dy1m9k839iy1m9k9m83-oy1m0r1n83-Y9y1t1m9k83kby1m9k83-JNy1m9k83-Ty1m9k831Dy1m9k839iy1m9k");
    string_constant_108 = 
	    STATIC_STRING("9m83-oy1m9k83vy83-YAy1n0rt1n83-Y9y1z1m9k83kby1m9k83-Hy1m9k83-Ty1m9k831Dy1m9k839iy1m9k9m83Sy1m9k83-ty1m9k83kby1m9k83-JNy1m9k83-Ty");
    string_constant_109 = 
	    STATIC_STRING("1m9k831Dy1m9k839iy1m9k9m83-oy1mrz1n83-Y9y13Dy1m9k83kby1m9k83-Hy1m9k83-Ty1m9k831Dy1m9k839iy1m9k9m83Sy1m9k83-ty1m9k83kby1m9k83-JNy");
    string_constant_110 = 
	    STATIC_STRING("1m9k83-Ty1m9k831Dy1m9k839iy1m9k9m83-oy1m9k83vy83-YAy1nrz3Dy1n83-YAy1s1m9k83=Fy1m9k83Dmy1m9k83-oy1m9k837my1m9k831Dy1m9k839iy1m9k9");
    string_constant_111 = STATIC_STRING("m831Nys");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(list(7,
	    string_constant_105,string_constant_106,string_constant_107,
	    string_constant_108,string_constant_109,string_constant_110,
	    string_constant_111)));
    Qab_no = STATIC_SYMBOL("NO",AB_package);
    string_constant_82 = 
	    STATIC_STRING("Maximum number of data points must be positive.");
    string_constant_83 = 
	    STATIC_STRING("Maximum number of data points must be less than or equal to ~d.");
    string_constant_84 = 
	    STATIC_STRING("The minimum interval between data points must be greater than or equal to zero.");
    Qhistory_specification = STATIC_SYMBOL("HISTORY-SPECIFICATION",AB_package);
    Qcompile_history_specification_for_slot = 
	    STATIC_SYMBOL("COMPILE-HISTORY-SPECIFICATION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_history_specification_for_slot,
	    STATIC_FUNCTION(compile_history_specification_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qhistory_specification,
	    SYMBOL_FUNCTION(Qcompile_history_specification_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qhistory_specification,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_85 = STATIC_STRING("do not keep history");
    string_constant_86 = STATIC_STRING("keep history");
    string_constant_87 = STATIC_STRING(" with ");
    string_constant_88 = STATIC_STRING("maximum number of data points = ~d");
    string_constant_89 = STATIC_STRING(" and ");
    string_constant_90 = STATIC_STRING("maximum age of data points = ");
    string_constant_91 = 
	    STATIC_STRING(", with minimum interval between data points = ");
    Qwrite_history_specification_from_slot = 
	    STATIC_SYMBOL("WRITE-HISTORY-SPECIFICATION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_history_specification_from_slot,
	    STATIC_FUNCTION(write_history_specification_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qhistory_specification,
	    SYMBOL_FUNCTION(Qwrite_history_specification_from_slot),
	    Qslot_value_writer);
    Kconvert_to_phrase_failure = STATIC_SYMBOL("CONVERT-TO-PHRASE-FAILURE",
	    Pkeyword);
    Qinstantiate_object_in_attribute = 
	    STATIC_SYMBOL("INSTANTIATE-OBJECT-IN-ATTRIBUTE",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_32,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)39L,(SI_Long)57344L);
    set_property_value_function(get_symbol_properties_function(Qattribute_descriptions),
	    Qtype_specification_simple_expansion,list_constant_33);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    list_constant_51 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_60 = STATIC_CONS(Qattribute_name,list_constant_51);
    Qattribute_type_specification = 
	    STATIC_SYMBOL("ATTRIBUTE-TYPE-SPECIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qattribute_type_specification,
	    STATIC_FUNCTION(attribute_type_specification,NIL,FALSE,1,1));
    list_constant_61 = STATIC_CONS(Qattribute_type_specification,
	    list_constant_51);
    Qattribute_format = STATIC_SYMBOL("ATTRIBUTE-FORMAT",AB_package);
    Qwhole_number_precision = STATIC_SYMBOL("WHOLE-NUMBER-PRECISION",
	    AB_package);
    list_constant_52 = STATIC_CONS(Qwhole_number_precision,list_constant_36);
    Qfraction_precision = STATIC_SYMBOL("FRACTION-PRECISION",AB_package);
    list_constant_53 = STATIC_CONS(Qfraction_precision,list_constant_36);
    list_constant_54 = STATIC_LIST((SI_Long)2L,list_constant_52,
	    list_constant_53);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qand,
	    Qwhole_number_precision,Qfraction_precision);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_54,list_constant_55);
    list_constant_57 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_56);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qattribute_format,
	    list_constant_57);
    Qattribute_initial_value = STATIC_SYMBOL("ATTRIBUTE-INITIAL-VALUE",
	    AB_package);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qattribute_initial_value,
	    Qdatum);
    Qattribute_initial_item_class = 
	    STATIC_SYMBOL("ATTRIBUTE-INITIAL-ITEM-CLASS",AB_package);
    list_constant_64 = STATIC_CONS(Qattribute_initial_item_class,
	    list_constant_51);
    Qattribute_initial_item_class_restricted_to_variable_or_parameter = 
	    STATIC_SYMBOL("ATTRIBUTE-INITIAL-ITEM-CLASS-RESTRICTED-TO-VARIABLE-OR-PARAMETER",
	    AB_package);
    list_constant_58 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_65 = 
	    STATIC_CONS(Qattribute_initial_item_class_restricted_to_variable_or_parameter,
	    list_constant_58);
    Qattribute_initial_type = STATIC_SYMBOL("ATTRIBUTE-INITIAL-TYPE",
	    AB_package);
    list_constant_66 = STATIC_CONS(Qattribute_initial_type,list_constant_51);
    Qattribute_range = STATIC_SYMBOL("ATTRIBUTE-RANGE",AB_package);
    list_constant_59 = STATIC_CONS(list_constant_34,Qnil);
    list_constant_67 = STATIC_CONS(Qattribute_range,list_constant_59);
    Qattribute_is_indexed = STATIC_SYMBOL("ATTRIBUTE-IS-INDEXED",AB_package);
    list_constant_68 = STATIC_CONS(Qattribute_is_indexed,list_constant_58);
    list_constant_69 = STATIC_LIST((SI_Long)9L,list_constant_60,
	    list_constant_61,list_constant_62,list_constant_63,
	    list_constant_64,list_constant_65,list_constant_66,
	    list_constant_67,list_constant_68);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qand,Qattribute_name);
    list_constant_71 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_69,list_constant_70);
    list_constant_72 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_71,list_constant_72);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_73);
    define_type_specification_explicit_complex_type(Qattribute_descriptions,
	    list_constant_10);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qnamed,Qattribute_descriptions);
    Qformat_override = STATIC_SYMBOL("FORMAT-OVERRIDE",AB_package);
    Qddd_dot_dddd_format = STATIC_SYMBOL("DDD.DDDD-FORMAT",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qinterval,Qtime_stamp,
	    Qfree_text);
    Qdate_format_description = STATIC_SYMBOL("DATE-FORMAT-DESCRIPTION",
	    AB_package);
    string_constant_92 = 
	    STATIC_STRING("Bad attribute format ~s for attribute ~s");
    Qfloat_format = STATIC_SYMBOL("FLOAT-FORMAT",AB_package);
    string_constant_93 = 
	    STATIC_STRING("Incompatible initial-value for attribute ~s");
    Qindexed = STATIC_SYMBOL("INDEXED",AB_package);
    list_constant_13 = STATIC_CONS(Qindexed,Qnil);
    Qnormalized_parse = STATIC_SYMBOL("NORMALIZED-PARSE",AB_package);
    attribute_descriptions_evaluation_setter_1 = 
	    STATIC_FUNCTION(attribute_descriptions_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qattribute_descriptions,
	    attribute_descriptions_evaluation_setter_1);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_7);
    attribute_descriptions_evaluation_getter_1 = 
	    STATIC_FUNCTION(attribute_descriptions_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qattribute_descriptions,
	    attribute_descriptions_evaluation_getter_1);
    Qinherited_attributes = STATIC_SYMBOL("INHERITED-ATTRIBUTES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinherited_attributes),
	    Qtype_specification_simple_expansion,list_constant_33);
    list_constant_74 = STATIC_LIST((SI_Long)3L,list_constant_66,
	    list_constant_67,list_constant_68);
    list_constant_75 = STATIC_LIST_STAR((SI_Long)5L,list_constant_60,
	    list_constant_61,list_constant_63,list_constant_64,
	    list_constant_74);
    list_constant_76 = STATIC_CONS(list_constant_70,Qnil);
    list_constant_77 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_75,list_constant_76);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_77,list_constant_72);
    list_constant_79 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_78);
    define_type_specification_explicit_complex_type(Qinherited_attributes,
	    list_constant_79);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    inherited_attributes_evaluation_getter_1 = 
	    STATIC_FUNCTION(inherited_attributes_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinherited_attributes,
	    inherited_attributes_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qhistory_specification),
	    Qtype_specification_simple_expansion,list_constant_35);
    Qmaximum_number_of_data_points = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-DATA-POINTS",AB_package);
    list_constant_81 = STATIC_CONS(Qmaximum_number_of_data_points,
	    list_constant_36);
    Qmaximum_age_of_data_points = 
	    STATIC_SYMBOL("MAXIMUM-AGE-OF-DATA-POINTS",AB_package);
    list_constant_82 = STATIC_CONS(Qmaximum_age_of_data_points,
	    list_constant_36);
    Qminimum_interval_between_data_points = 
	    STATIC_SYMBOL("MINIMUM-INTERVAL-BETWEEN-DATA-POINTS",AB_package);
    list_constant_80 = STATIC_CONS(Qnumber,Qnil);
    list_constant_83 = STATIC_CONS(Qminimum_interval_between_data_points,
	    list_constant_80);
    list_constant_84 = STATIC_LIST((SI_Long)3L,list_constant_81,
	    list_constant_82,list_constant_83);
    list_constant_85 = STATIC_LIST((SI_Long)3L,Qab_or,
	    Qmaximum_number_of_data_points,Qmaximum_age_of_data_points);
    list_constant_86 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_84,list_constant_85);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_86);
    define_type_specification_explicit_complex_type(Qhistory_specification,
	    list_constant_16);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qnamed,Qhistory_specification);
    Qhistory = STATIC_SYMBOL("HISTORY",AB_package);
    history_specification_evaluation_setter_1 = 
	    STATIC_FUNCTION(history_specification_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qhistory_specification,
	    history_specification_evaluation_setter_1);
    history_specification_evaluation_getter_1 = 
	    STATIC_FUNCTION(history_specification_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qhistory_specification,
	    history_specification_evaluation_getter_1);
    Qlist_of_classes = STATIC_SYMBOL("LIST-OF-CLASSES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlist_of_classes),
	    Qtype_specification_simple_expansion,list_constant_33);
    define_type_specification_explicit_complex_type(Qlist_of_classes,
	    list_constant_1);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qnamed,Qlist_of_classes);
    list_of_classes_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_classes_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlist_of_classes,
	    list_of_classes_evaluation_setter_1);
    list_of_classes_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_classes_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_classes,
	    list_of_classes_evaluation_getter_1);
    Qlist_of_object_classes = STATIC_SYMBOL("LIST-OF-OBJECT-CLASSES",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qlist_of_object_classes),
	    Qtype_specification_simple_expansion,list_constant_33);
    define_type_specification_explicit_complex_type(Qlist_of_object_classes,
	    list_constant_1);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qnamed,Qlist_of_object_classes);
    list_of_object_classes_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_object_classes_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlist_of_object_classes,
	    list_of_object_classes_evaluation_setter_1);
    list_of_object_classes_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_object_classes_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_object_classes,
	    list_of_object_classes_evaluation_getter_1);
    Qlist_of_connection_classes = 
	    STATIC_SYMBOL("LIST-OF-CONNECTION-CLASSES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlist_of_connection_classes),
	    Qtype_specification_simple_expansion,list_constant_33);
    define_type_specification_explicit_complex_type(Qlist_of_connection_classes,
	    list_constant_1);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qlist_of_connection_classes);
    list_of_connection_classes_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_connection_classes_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlist_of_connection_classes,
	    list_of_connection_classes_evaluation_setter_1);
    list_of_connection_classes_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_connection_classes_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_connection_classes,
	    list_of_connection_classes_evaluation_getter_1);
    Qlist_of_message_classes = STATIC_SYMBOL("LIST-OF-MESSAGE-CLASSES",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qlist_of_message_classes),
	    Qtype_specification_simple_expansion,list_constant_33);
    define_type_specification_explicit_complex_type(Qlist_of_message_classes,
	    list_constant_1);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qlist_of_message_classes);
    list_of_message_classes_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_message_classes_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlist_of_message_classes,
	    list_of_message_classes_evaluation_setter_1);
    list_of_message_classes_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_message_classes_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_message_classes,
	    list_of_message_classes_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qclass_inheritance_path_of_definition),
	    Qtype_specification_simple_expansion,list_constant_33);
    define_type_specification_explicit_complex_type(Qclass_inheritance_path_of_definition,
	    list_constant_1);
    class_inheritance_path_of_definition_evaluation_getter_1 = 
	    STATIC_FUNCTION(class_inheritance_path_of_definition_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qclass_inheritance_path_of_definition,
	    class_inheritance_path_of_definition_evaluation_getter_1);
    Qattribute_displays_spec_qm = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAYS-SPEC\?",AB_package);
    list_constant_87 = STATIC_CONS(list_constant_11,Qnil);
    list_constant_88 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,list_constant_7,
	    Qnil,list_constant_87);
    set_property_value_function(get_symbol_properties_function(Qattribute_displays_spec_qm),
	    Qtype_specification_simple_expansion,list_constant_88);
    list_constant_108 = STATIC_LIST((SI_Long)2L,Qmember,Qinherited);
    Qattribute_list = STATIC_SYMBOL("ATTRIBUTE-LIST",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    list_constant_89 = STATIC_CONS(Qattribute,list_constant_51);
    Qqualified_class = STATIC_SYMBOL("QUALIFIED-CLASS",AB_package);
    list_constant_90 = STATIC_CONS(Qqualified_class,list_constant_51);
    Qdisplay_with_name = STATIC_SYMBOL("DISPLAY-WITH-NAME",AB_package);
    list_constant_91 = STATIC_CONS(Qdisplay_with_name,list_constant_58);
    list_constant_92 = STATIC_LIST((SI_Long)3L,list_constant_89,
	    list_constant_90,list_constant_91);
    list_constant_93 = STATIC_LIST((SI_Long)3L,Qand,Qattribute,
	    Qdisplay_with_name);
    list_constant_94 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_92,list_constant_93);
    list_constant_95 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_94,list_constant_72);
    list_constant_103 = STATIC_LIST((SI_Long)2L,Qattribute_list,
	    list_constant_95);
    Qat_standard_position = STATIC_SYMBOL("AT-STANDARD-POSITION",AB_package);
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qmember,Qat_standard_position);
    Qx_offset = STATIC_SYMBOL("X-OFFSET",AB_package);
    list_constant_96 = STATIC_CONS(Qx_offset,list_constant_36);
    Qy_offset = STATIC_SYMBOL("Y-OFFSET",AB_package);
    list_constant_97 = STATIC_CONS(Qy_offset,list_constant_36);
    list_constant_98 = STATIC_LIST((SI_Long)2L,list_constant_96,
	    list_constant_97);
    list_constant_99 = STATIC_LIST((SI_Long)3L,Qand,Qx_offset,Qy_offset);
    list_constant_101 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_98,list_constant_99);
    list_constant_102 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_100,
	    list_constant_101);
    list_constant_104 = STATIC_LIST((SI_Long)2L,Qposition,list_constant_102);
    list_constant_105 = STATIC_LIST((SI_Long)2L,list_constant_103,
	    list_constant_104);
    list_constant_106 = STATIC_LIST((SI_Long)3L,Qand,Qattribute_list,
	    Qposition);
    list_constant_107 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_105,list_constant_106);
    list_constant_109 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_107,list_constant_72);
    list_constant_22 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_7,
	    list_constant_108,list_constant_109);
    define_type_specification_explicit_complex_type(Qattribute_displays_spec_qm,
	    list_constant_22);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qattribute_displays_spec_qm);
    attribute_displays_spec_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(attribute_displays_spec_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qattribute_displays_spec_qm,
	    attribute_displays_spec_qm_evaluation_setter_1);
    attribute_displays_spec_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(attribute_displays_spec_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qattribute_displays_spec_qm,
	    attribute_displays_spec_qm_evaluation_getter_1);
    Qnew_class = STATIC_SYMBOL("NEW-CLASS",AB_package);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_51);
    set_property_value_function(get_symbol_properties_function(Qnew_class),
	    Qtype_specification_simple_expansion,list_constant_24);
    define_type_specification_explicit_complex_type(Qnew_class,
	    list_constant_24);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qnamed,Qnew_class);
    new_class_evaluation_setter_1 = 
	    STATIC_FUNCTION(new_class_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qnew_class,
	    new_class_evaluation_setter_1);
    new_class_evaluation_getter_1 = 
	    STATIC_FUNCTION(new_class_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qnew_class,
	    new_class_evaluation_getter_1);
    Qlist_of_slots = STATIC_SYMBOL("LIST-OF-SLOTS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlist_of_slots),
	    Qtype_specification_simple_expansion,list_constant_33);
    define_type_specification_explicit_complex_type(Qlist_of_slots,
	    list_constant_1);
    list_of_slots_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_slots_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_slots,
	    list_of_slots_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qconnections_qm),
	    Qtype_specification_simple_expansion,list_constant_88);
    Qportname = STATIC_SYMBOL("PORTNAME",AB_package);
    list_constant_115 = STATIC_CONS(Qportname,list_constant_51);
    Qconnection_class = STATIC_SYMBOL("CONNECTION-CLASS",AB_package);
    list_constant_116 = STATIC_CONS(Qconnection_class,list_constant_51);
    Qstub_direction = STATIC_SYMBOL("STUB-DIRECTION",AB_package);
    list_constant_110 = STATIC_LIST((SI_Long)3L,Qmember,Qinput,Qoutput);
    list_constant_117 = STATIC_LIST((SI_Long)2L,Qstub_direction,
	    list_constant_110);
    Qedge_location = STATIC_SYMBOL("EDGE-LOCATION",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    list_constant_111 = STATIC_LIST((SI_Long)5L,Qmember,Qtop,Qbottom,
	    Qright,Qleft);
    list_constant_118 = STATIC_LIST((SI_Long)2L,Qedge_location,
	    list_constant_111);
    Qcoordinate_location = STATIC_SYMBOL("COORDINATE-LOCATION",AB_package);
    list_constant_119 = STATIC_CONS(Qcoordinate_location,list_constant_36);
    Qstyle = STATIC_SYMBOL("STYLE",AB_package);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    list_constant_112 = STATIC_LIST((SI_Long)3L,Qmember,Qdiagonal,Qorthogonal);
    list_constant_120 = STATIC_LIST((SI_Long)2L,Qstyle,list_constant_112);
    list_constant_113 = STATIC_LIST((SI_Long)2L,Qnamed,Qconnection_arrows);
    list_constant_121 = STATIC_LIST((SI_Long)2L,Qconnection_arrows,
	    list_constant_113);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    list_constant_114 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qconnection_line_pattern);
    list_constant_122 = STATIC_LIST((SI_Long)2L,Qline_pattern,
	    list_constant_114);
    list_constant_123 = STATIC_LIST((SI_Long)8L,list_constant_115,
	    list_constant_116,list_constant_117,list_constant_118,
	    list_constant_119,list_constant_120,list_constant_121,
	    list_constant_122);
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_123);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_124,list_constant_72);
    list_constant_26 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_7,
	    list_constant_108,list_constant_125);
    define_type_specification_explicit_complex_type(Qconnections_qm,
	    list_constant_26);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qnamed,Qconnections_qm);
    connections_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(connections_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qconnections_qm,
	    connections_qm_evaluation_setter_1);
    Qsolid = STATIC_SYMBOL("SOLID",AB_package);
    connections_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(connections_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconnections_qm,
	    connections_qm_evaluation_getter_1);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_80);
    set_property_value_function(get_symbol_properties_function(Qstub_length),
	    Qtype_specification_simple_expansion,list_constant_28);
    define_type_specification_explicit_complex_type(Qstub_length,
	    list_constant_28);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qnamed,Qstub_length);
    stub_length_evaluation_setter_1 = 
	    STATIC_FUNCTION(stub_length_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qstub_length,
	    stub_length_evaluation_setter_1);
    stub_length_evaluation_getter_1 = 
	    STATIC_FUNCTION(stub_length_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qstub_length,
	    stub_length_evaluation_getter_1);
    Qjunction_class = STATIC_SYMBOL("JUNCTION-CLASS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qjunction_class),
	    Qtype_specification_simple_expansion,list_constant_24);
    define_type_specification_explicit_complex_type(Qjunction_class,
	    list_constant_24);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qnamed,Qjunction_class);
    junction_class_evaluation_setter_1 = 
	    STATIC_FUNCTION(junction_class_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qjunction_class,
	    junction_class_evaluation_setter_1);
    junction_class_evaluation_getter_1 = 
	    STATIC_FUNCTION(junction_class_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qjunction_class,
	    junction_class_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qab_class),
	    Qtype_specification_simple_expansion,list_constant_24);
    define_type_specification_explicit_complex_type(Qab_class,
	    list_constant_24);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qnamed,Qab_class);
    class_evaluation_setter_1 = STATIC_FUNCTION(class_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qab_class,
	    class_evaluation_setter_1);
    class_evaluation_getter_1 = STATIC_FUNCTION(class_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qab_class,
	    class_evaluation_getter_1);
    Qrelation_name_qm = STATIC_SYMBOL("RELATION-NAME\?",AB_package);
    set_property_value_function(get_symbol_properties_function(Qrelation_name_qm),
	    Qtype_specification_simple_expansion,list_constant_24);
    define_type_specification_explicit_complex_type(Qrelation_name_qm,
	    list_constant_24);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qnamed,Qrelation_name_qm);
    relation_name_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(relation_name_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qrelation_name_qm,
	    relation_name_qm_evaluation_setter_1);
    relation_name_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(relation_name_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrelation_name_qm,
	    relation_name_qm_evaluation_getter_1);
}
