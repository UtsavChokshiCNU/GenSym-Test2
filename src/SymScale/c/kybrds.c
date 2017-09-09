/* kybrds.c
 * Input file:  keyboards.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kybrds.h"


DEFINE_VARIABLE_WITH_SYMBOL(Key_index_to_key_symbol_array, Qkey_index_to_key_symbol_array);

DEFINE_VARIABLE_WITH_SYMBOL(Key_index_to_lisp_character_array, Qkey_index_to_lisp_character_array);

DEFINE_VARIABLE_WITH_SYMBOL(Lisp_int_character_to_key_index_array, Qlisp_int_character_to_key_index_array);

DEFINE_VARIABLE_WITH_SYMBOL(Lisp_character_to_key_index_alist, Qlisp_character_to_key_index_alist);

DEFINE_VARIABLE_WITH_SYMBOL(Bindable_keysyms, Qbindable_keysyms);

DEFINE_VARIABLE_WITH_SYMBOL(Pseudo_keysyms, Qpseudo_keysyms);

Object Key_code_for_key_symbol_prop = UNBOUND;

static Object Qkey_code_for_key_symbol;  /* key-code-for-key-symbol */

/* DEFINE-KEY-SYMBOL-1 */
Object define_key_symbol_1(key_symbol_1,key_index,pretty_key_symbol,
	    character_object,character_index,bindable_p,pseudo_p)
    Object key_symbol_1, key_index, pretty_key_symbol, character_object;
    Object character_index, bindable_p, pseudo_p;
{
    Object temp, push_arg;

    x_note_fn_call(20,0);
    temp = Key_index_to_key_symbol_array;
    SVREF(temp,key_index) = pretty_key_symbol;
    mutate_global_property(key_symbol_1,key_index,Qkey_code_for_key_symbol);
    if (bindable_p)
	Bindable_keysyms = nconc2(Bindable_keysyms,LIST_1(key_symbol_1));
    if (pseudo_p)
	Pseudo_keysyms = nconc2(Pseudo_keysyms,LIST_1(key_symbol_1));
    if (character_object) {
	temp = Key_index_to_lisp_character_array;
	SVREF(temp,key_index) = character_object;
	if (num_len(3,FIX((SI_Long)0L),character_index,
		FIXNUM_SUB1(Maximum_number_of_key_indexes))) {
	    temp = Lisp_int_character_to_key_index_array;
	    return VALUES_1(SVREF(temp,character_index) = key_index);
	}
	else {
	    push_arg = CONS(character_object,key_index);
	    temp = CONS(push_arg,Lisp_character_to_key_index_alist);
	    Lisp_character_to_key_index_alist = temp;
	    return VALUES_1(Lisp_character_to_key_index_alist);
	}
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-KEY-CODE-TO-KEY-SYMBOL */
Object convert_key_code_to_key_symbol(key_code)
    Object key_code;
{
    Object unicode, index_1;

    x_note_fn_call(20,1);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	index_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	index_1 = FIXNUM_LOGAND(Key_index_bits,key_code);
    if ((SI_Long)-1L < IFIX(index_1) && FIXNUM_LT(index_1,
	    Maximum_number_of_key_indexes))
	return VALUES_1(ISVREF(Key_index_to_key_symbol_array,IFIX(index_1)));
    else
	return VALUES_1(Nil);
}

/* KEY-CODE-FROM-CHARACTER */
Object key_code_from_character(character_1)
    Object character_1;
{
    Object temp;
    SI_Long index_1;

    x_note_fn_call(20,2);
    index_1 = IFIX(CHAR_INT(character_1));
    if ((SI_Long)-1L < index_1 && index_1 < 
	    IFIX(Maximum_number_of_key_indexes))
	temp = ISVREF(Lisp_int_character_to_key_index_array,index_1);
    else {
	temp = assq_function(character_1,Lisp_character_to_key_index_alist);
	temp = CDR(temp);
    }
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(Illegal_key_code);
}

void keyboards_INIT()
{
    Object gensymed_symbol, the_array;
    SI_Long i, ab_loop_bind_;
    Object AB_package;

    x_note_fn_call(20,3);
    SET_PACKAGE("AB");
    if (Key_index_to_key_symbol_array == UNBOUND) {
	gensymed_symbol = Maximum_number_of_key_indexes;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	Key_index_to_key_symbol_array = the_array;
    }
    if (Key_index_to_lisp_character_array == UNBOUND) {
	gensymed_symbol = Maximum_number_of_key_indexes;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	Key_index_to_lisp_character_array = the_array;
    }
    if (Lisp_int_character_to_key_index_array == UNBOUND) {
	gensymed_symbol = Maximum_number_of_key_indexes;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	Lisp_int_character_to_key_index_array = the_array;
    }
    if (Lisp_character_to_key_index_alist == UNBOUND)
	Lisp_character_to_key_index_alist = Nil;
    if (Bindable_keysyms == UNBOUND)
	Bindable_keysyms = Nil;
    if (Pseudo_keysyms == UNBOUND)
	Pseudo_keysyms = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qkey_code_for_key_symbol = STATIC_SYMBOL("KEY-CODE-FOR-KEY-SYMBOL",
	    AB_package);
    Key_code_for_key_symbol_prop = Qkey_code_for_key_symbol;
}
