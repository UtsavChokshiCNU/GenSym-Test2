/* int3a.c
 * Input file:  int3a.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int3a.h"


static Object Qg2int_read_icp_boolean;  /* read-icp-boolean */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

static Object Qg2int_resumable_icp_list_end;  /* resumable-icp-list-end */

/* READ-ICP-BOOLEAN */
Object g2int_read_icp_boolean()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, arg1, value, arg2;

    x_note_fn_call(42,0);
    if (G2int_disable_resumability)
	temp =  !(IFIX(g2int_read_icp_byte()) == (SI_Long)0L) ? T : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_boolean,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_boolean,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_read_icp_boolean);
		    return VALUES_1(G2int_icp_suspend);
		}
		arg1 = value;
	    }
	    arg2 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX((SI_Long)0L);
	    arg1 = FIXNUM_EQ(arg1,arg2) ? T : Nil;
	}
	temp =  !TRUEP(arg1) ? T : Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_boolean;  /* write-icp-boolean */

/* WRITE-ICP-BOOLEAN */
Object g2int_write_icp_boolean(boolean_1)
    Object boolean_1;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(42,1);
    if (G2int_disable_resumability)
	temp = g2int_write_icp_byte(boolean_1 ? FIX((SI_Long)1L) : 
		FIX((SI_Long)0L));
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_boolean,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_boolean,top,Nil);
	}
	boolean_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : boolean_1;
	value = g2int_write_icp_byte(boolean_1 ? FIX((SI_Long)1L) : 
		FIX((SI_Long)0L));
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(boolean_1);
	    g2int_resumable_icp_push(Qg2int_write_icp_boolean);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_corresponding_object_index;  /* read-icp-corresponding-object-index */

static Object Qg2int_true;         /* true */

static Object Qg2int_false;        /* false */

/* READ-ICP-CORRESPONDING-OBJECT-INDEX */
Object g2int_read_icp_corresponding_object_index()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value, test, arg1;
    SI_Long icp_byte;
    char temp_1;

    x_note_fn_call(42,2);
    if (G2int_disable_resumability) {
	icp_byte = IFIX(g2int_peek_icp_byte());
	if (icp_byte > (SI_Long)64000L)
	    temp = Nil;
	else if (icp_byte > (SI_Long)63000L)
	    temp = g2int_read_icp_large_integer(g2int_read_icp_byte());
	else
	    temp = g2int_read_icp_byte();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_corresponding_object_index,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_corresponding_object_index,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    icp_byte = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_peek_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_corresponding_object_index);
		return VALUES_1(G2int_icp_suspend);
	    }
	    icp_byte = IFIX(value);
	}
	if ( !(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) && 
		icp_byte > (SI_Long)64000L)
	    temp = Nil;
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : icp_byte > (SI_Long)63000L) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_byte();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(FIX(icp_byte));
			g2int_resumable_icp_push(Qg2int_read_icp_corresponding_object_index);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		value = g2int_read_icp_large_integer(arg1);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX(icp_byte));
		    g2int_resumable_icp_push(Qg2int_read_icp_corresponding_object_index);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(FIX(icp_byte));
		    g2int_resumable_icp_push(Qg2int_read_icp_corresponding_object_index);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_unsigned_integer;  /* read-icp-unsigned-integer */

/* READ-ICP-UNSIGNED-INTEGER */
Object g2int_read_icp_unsigned_integer()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value, test, arg1;
    SI_Long icp_byte;
    char temp_1;

    x_note_fn_call(42,3);
    if (G2int_disable_resumability) {
	icp_byte = IFIX(g2int_peek_icp_byte());
	if (icp_byte > (SI_Long)64000L)
	    temp = Nil;
	else if (icp_byte > (SI_Long)63000L)
	    temp = g2int_read_icp_large_integer(g2int_read_icp_byte());
	else
	    temp = g2int_read_icp_byte();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_unsigned_integer,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_unsigned_integer,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    icp_byte = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_peek_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_unsigned_integer);
		return VALUES_1(G2int_icp_suspend);
	    }
	    icp_byte = IFIX(value);
	}
	if ( !(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) && 
		icp_byte > (SI_Long)64000L)
	    temp = Nil;
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : icp_byte > (SI_Long)63000L) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_byte();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(FIX(icp_byte));
			g2int_resumable_icp_push(Qg2int_read_icp_unsigned_integer);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		value = g2int_read_icp_large_integer(arg1);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX(icp_byte));
		    g2int_resumable_icp_push(Qg2int_read_icp_unsigned_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(FIX(icp_byte));
		    g2int_resumable_icp_push(Qg2int_read_icp_unsigned_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_1;   /* "An integer outside the allowed range was given to ~
				    *                    ICP-write-unsigned-integer: ~a"
				    */

static Object Qg2int_write_icp_corresponding_object_index;  /* write-icp-corresponding-object-index */

/* WRITE-ICP-CORRESPONDING-OBJECT-INDEX */
Object g2int_write_icp_corresponding_object_index(corresponding_object_index)
    Object corresponding_object_index;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, test, value;
    char temp_1;

    x_note_fn_call(42,4);
    if (G2int_disable_resumability)
	temp = FIXNUMP(corresponding_object_index) ? 
		(IFIX(corresponding_object_index) > (SI_Long)63000L ? 
		g2int_write_icp_large_integer(corresponding_object_index) :
		 g2int_write_icp_byte(corresponding_object_index)) : 
		g2int_icp_error_internal(Qerror,string_constant_1,
		corresponding_object_index,Nil,Nil);
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_corresponding_object_index,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_corresponding_object_index,top,Nil);
	}
	corresponding_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_object_index;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : 
		FIXNUMP(corresponding_object_index)) {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : 
		    IFIX(corresponding_object_index) > (SI_Long)63000L) {
		value = 
			g2int_write_icp_large_integer(corresponding_object_index);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(corresponding_object_index);
		    g2int_resumable_icp_push(Qg2int_write_icp_corresponding_object_index);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else {
		value = g2int_write_icp_byte(corresponding_object_index);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(corresponding_object_index);
		    g2int_resumable_icp_push(Qg2int_write_icp_corresponding_object_index);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	}
	else {
	    value = g2int_icp_error_internal(Qerror,string_constant_1,
		    corresponding_object_index,Nil,Nil);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(corresponding_object_index);
		g2int_resumable_icp_push(Qg2int_write_icp_corresponding_object_index);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_unsigned_integer;  /* write-icp-unsigned-integer */

/* WRITE-ICP-UNSIGNED-INTEGER */
Object g2int_write_icp_unsigned_integer(unsigned_integer)
    Object unsigned_integer;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, test, value;
    char temp_1;

    x_note_fn_call(42,5);
    if (G2int_disable_resumability)
	temp = FIXNUMP(unsigned_integer) ? (IFIX(unsigned_integer) > 
		(SI_Long)63000L ? 
		g2int_write_icp_large_integer(unsigned_integer) : 
		g2int_write_icp_byte(unsigned_integer)) : 
		g2int_icp_error_internal(Qerror,string_constant_1,
		unsigned_integer,Nil,Nil);
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_unsigned_integer,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_unsigned_integer,top,Nil);
	}
	unsigned_integer = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : unsigned_integer;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : FIXNUMP(unsigned_integer)) {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : IFIX(unsigned_integer) > 
		    (SI_Long)63000L) {
		value = g2int_write_icp_large_integer(unsigned_integer);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(unsigned_integer);
		    g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else {
		value = g2int_write_icp_byte(unsigned_integer);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(unsigned_integer);
		    g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	}
	else {
	    value = g2int_icp_error_internal(Qerror,string_constant_1,
		    unsigned_integer,Nil,Nil);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(unsigned_integer);
		g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integer);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_unsigned_integerqm;  /* read-icp-unsigned-integer? */

/* READ-ICP-UNSIGNED-INTEGER? */
Object g2int_read_icp_unsigned_integerqm()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    SI_Long icp_byte;

    x_note_fn_call(42,6);
    if (G2int_disable_resumability) {
	icp_byte = IFIX(g2int_read_icp_byte());
	if (icp_byte == (SI_Long)63000L)
	    temp = Nil;
	else if (icp_byte > (SI_Long)63000L)
	    temp = g2int_read_icp_large_integer(FIX(icp_byte));
	else
	    temp = FIX(icp_byte);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_unsigned_integerqm,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_unsigned_integerqm,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    icp_byte = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_unsigned_integerqm);
		return VALUES_1(G2int_icp_suspend);
	    }
	    icp_byte = IFIX(value);
	}
	if ( !(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) && 
		icp_byte == (SI_Long)63000L)
	    temp = Nil;
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		icp_byte > (SI_Long)63000L) {
	    value = g2int_read_icp_large_integer(FIX(icp_byte));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(FIX(icp_byte));
		g2int_resumable_icp_push(Qg2int_read_icp_unsigned_integerqm);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = T ? FIX(icp_byte) : Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_unsigned_integerqm;  /* write-icp-unsigned-integer? */

/* WRITE-ICP-UNSIGNED-INTEGER? */
Object g2int_write_icp_unsigned_integerqm(unsigned_integer_qm)
    Object unsigned_integer_qm;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, test, value;
    char temp_1;

    x_note_fn_call(42,7);
    if (G2int_disable_resumability) {
	if ( !TRUEP(unsigned_integer_qm))
	    temp = g2int_write_icp_byte(FIX((SI_Long)63000L));
	else if (IFIX(unsigned_integer_qm) > (SI_Long)62999L)
	    temp = g2int_write_icp_large_integer(unsigned_integer_qm);
	else
	    temp = g2int_write_icp_byte(unsigned_integer_qm);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_unsigned_integerqm,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_unsigned_integerqm,top,Nil);
	}
	unsigned_integer_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : unsigned_integer_qm;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) :  !TRUEP(unsigned_integer_qm)) {
	    value = g2int_write_icp_byte(FIX((SI_Long)63000L));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(unsigned_integer_qm);
		g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integerqm);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : IFIX(unsigned_integer_qm) 
		    > (SI_Long)62999L) {
		value = g2int_write_icp_large_integer(unsigned_integer_qm);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(unsigned_integer_qm);
		    g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integerqm);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		value = g2int_write_icp_byte(unsigned_integer_qm);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(unsigned_integer_qm);
		    g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integerqm);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_2;   /* "Integer outside of the range for ICP integers: ~a" */

/* INTEGER-LENGTH-IN-ICP-BYTES */
Object g2int_integer_length_in_icp_bytes(integer)
    Object integer;
{
    Object temp;
    SI_Long fixnum;

    x_note_fn_call(42,8);
    if (FIXNUMP(integer)) {
	fixnum = IFIX(integer);
	temp = fixnum >= (SI_Long)-31500L && fixnum <= (SI_Long)31500L ? 
		FIX((SI_Long)1L) : 
		g2int_large_integer_length_in_icp_bytes(integer);
    }
    else
	temp = g2int_icp_error_internal(Qerror,string_constant_2,integer,
		Nil,Nil);
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_integer;  /* read-icp-integer */

/* READ-ICP-INTEGER */
Object g2int_read_icp_integer()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    SI_Long icp_byte;

    x_note_fn_call(42,9);
    if (G2int_disable_resumability) {
	icp_byte = IFIX(g2int_read_icp_byte());
	temp = icp_byte > (SI_Long)63000L ? 
		g2int_read_icp_large_integer(FIX(icp_byte)) : FIX(icp_byte 
		- (SI_Long)31500L);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_integer,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_integer,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    icp_byte = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_integer);
		return VALUES_1(G2int_icp_suspend);
	    }
	    icp_byte = IFIX(value);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		icp_byte > (SI_Long)63000L) {
	    value = g2int_read_icp_large_integer(FIX(icp_byte));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(FIX(icp_byte));
		g2int_resumable_icp_push(Qg2int_read_icp_integer);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = FIX(icp_byte - (SI_Long)31500L);
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_integer;  /* write-icp-integer */

/* WRITE-ICP-INTEGER */
Object g2int_write_icp_integer(integer)
    Object integer;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, test, value;
    SI_Long fixnum;
    char temp_1;

    x_note_fn_call(42,10);
    if (G2int_disable_resumability) {
	if (FIXNUMP(integer)) {
	    fixnum = IFIX(integer);
	    temp = fixnum >= (SI_Long)-31500L && fixnum <= (SI_Long)31500L 
		    ? g2int_write_icp_byte(FIX(fixnum + (SI_Long)31500L)) :
		     g2int_write_icp_large_integer(FIX(fixnum));
	}
	else
	    temp = g2int_icp_error_internal(Qerror,string_constant_2,
		    integer,Nil,Nil);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_integer,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_integer,top,Nil);
	}
	integer = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : integer;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : FIXNUMP(integer)) {
	    fixnum = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : IFIX(integer);
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : fixnum >= (SI_Long)-31500L 
		    && fixnum <= (SI_Long)31500L) {
		value = g2int_write_icp_byte(FIX(fixnum + (SI_Long)31500L));
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX(fixnum));
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(integer);
		    g2int_resumable_icp_push(Qg2int_write_icp_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else {
		value = g2int_write_icp_large_integer(FIX(fixnum));
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(FIX(fixnum));
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(integer);
		    g2int_resumable_icp_push(Qg2int_write_icp_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	}
	else {
	    value = g2int_icp_error_internal(Qerror,string_constant_2,
		    integer,Nil,Nil);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(integer);
		g2int_resumable_icp_push(Qg2int_write_icp_integer);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_managed_long;  /* write-icp-managed-long */

/* WRITE-ICP-MANAGED-LONG */
Object g2int_write_icp_managed_long(managed_long)
    Object managed_long;
{
    Object tag_temp, temp, resumable_icp_state_1, icp_suspend_1, top, b0_1;
    Object b1_1, b2_1, b3_1, value, v1, v2, v3;
    SI_Long b0, b1, b2, b3;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(42,11);
    tag_temp = UNIQUE_TAG(Qg2int_write_icp_managed_long);
    if (PUSH_CATCH(tag_temp,0)) {
	if (G2int_disable_resumability) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		temp = aref1(managed_long,FIX((SI_Long)0L));
		g2ext_foreign_partition_long(INTEGER_TO_INT64(temp),
			UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_long_union));
		b0 = UBYTE_16_ISAREF_1(G2int_partition_long_union,(SI_Long)0L);
		b1 = UBYTE_16_ISAREF_1(G2int_partition_long_union,(SI_Long)1L);
		b2 = UBYTE_16_ISAREF_1(G2int_partition_long_union,(SI_Long)2L);
		b3 = UBYTE_16_ISAREF_1(G2int_partition_long_union,(SI_Long)3L);
		g2int_write_icp_byte(FIX(b0));
		g2int_write_icp_byte(FIX(b1));
		g2int_write_icp_byte(FIX(b2));
		temp = g2int_write_icp_byte(FIX(b3));
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	    icp_suspend_1 = G2int_icp_suspend;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		top = g2int_resumable_icp_pop();
		if ( !EQ(Qg2int_write_icp_managed_long,top)) {
		    result = g2int_icp_error_internal(Qerror,
			    string_constant,Qg2int_write_icp_managed_long,
			    top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    managed_long = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : managed_long;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if ( !(resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil))) {
		    temp = aref1(managed_long,FIX((SI_Long)0L));
		    g2ext_foreign_partition_long(INTEGER_TO_INT64(temp),
			    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_long_union));
		}
		b0_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_long_union,
			(SI_Long)0L));
		b1_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_long_union,
			(SI_Long)1L));
		b2_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_long_union,
			(SI_Long)2L));
		b3_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_long_union,
			(SI_Long)3L));
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
			    break;
			  case 3:
			    goto l3;
			    break;
			  case 4:
			    goto l4;
			    break;
			  default:
			    break;
			}
		}
	      l1:
		if (EQ(icp_suspend_1,g2int_write_icp_byte(b0_1))) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l2:
		if (EQ(icp_suspend_1,g2int_write_icp_byte(b1_1))) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l3:
		if (EQ(icp_suspend_1,g2int_write_icp_byte(b2_1))) {
		    g2int_resumable_icp_push(FIX((SI_Long)3L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l4:
		value = g2int_write_icp_byte(b3_1);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)4L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		result = VALUES_1(value);
		goto end_block;
	      end_block:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(b3_1);
		    g2int_resumable_icp_push(b2_1);
		    g2int_resumable_icp_push(b1_1);
		    g2int_resumable_icp_push(b0_1);
		    g2int_resumable_icp_push(managed_long);
		    g2int_resumable_icp_push(Qg2int_write_icp_managed_long);
		    result = VALUES_1(G2int_icp_suspend);
		    THROW(tag_temp,result);
		}
		temp = v1;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	result = VALUES_1(temp);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qg2int_read_icp_managed_long;  /* read-icp-managed-long */

/* READ-ICP-MANAGED-LONG */
Object g2int_read_icp_managed_long()
{
    Object tag_temp, new_long, b0, b1, b2, b3, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, arg1, value, arg2, arg3, arg4;
    SI_int64 aref_new_value, temp_1;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(42,12);
    tag_temp = UNIQUE_TAG(Qg2int_read_icp_managed_long);
    if (PUSH_CATCH(tag_temp,0)) {
	if (G2int_disable_resumability) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		new_long = g2int_allocate_managed_long_box();
		b0 = g2int_read_icp_byte();
		b1 = g2int_read_icp_byte();
		b2 = g2int_read_icp_byte();
		b3 = g2int_read_icp_byte();
		aref_new_value = g2ext_foreign_reconstruct_long(IFIX(b0),
			IFIX(b1),IFIX(b2),IFIX(b3));
		set_aref1(new_long,FIX((SI_Long)0L),
			INT64_TO_INTEGER(aref_new_value));
		temp = new_long;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	    icp_suspend_1 = G2int_icp_suspend;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		top = g2int_resumable_icp_pop();
		if ( !EQ(Qg2int_read_icp_managed_long,top)) {
		    result = g2int_icp_error_internal(Qerror,
			    string_constant,Qg2int_read_icp_managed_long,
			    top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_long);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg1 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg2 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_long);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg2 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg3 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg2);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_long);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg3 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg4 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg3);
			    g2int_resumable_icp_push(arg2);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_long);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg4 = value;
		    }
		    b0 = arg1;
		    b1 = arg2;
		    b2 = arg3;
		    b3 = arg4;
		    temp_1 = g2ext_foreign_reconstruct_long(IFIX(b0),
			    IFIX(b1),IFIX(b2),IFIX(b3));
		    arg1 = INT64_TO_INTEGER(temp_1);
		}
		new_long = g2int_allocate_managed_long_box();
		aref_new_value = INTEGER_TO_INT64(arg1);
		set_aref1(new_long,FIX((SI_Long)0L),
			INT64_TO_INTEGER(aref_new_value));
		temp = new_long;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	result = VALUES_1(temp);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qg2int_read_icp_list_of_unsigned_integers;  /* read-icp-list-of-unsigned-integers */

/* READ-ICP-LIST-OF-UNSIGNED-INTEGERS */
Object g2int_read_icp_list_of_unsigned_integers()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(42,13);
    if (G2int_disable_resumability) {
	ab_loop_repeat_ = IFIX(g2int_read_icp_unsigned_integer());
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = 
		g2int_gensym_cons_1(g2int_read_icp_unsigned_integer(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end;
	temp = Qnil;
      end:;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_list_of_unsigned_integers,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_list_of_unsigned_integers,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    ab_loop_repeat_ = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_unsigned_integers);
		return VALUES_1(G2int_icp_suspend);
	    }
	    ab_loop_repeat_ = IFIX(value);
	}
	ab_loopvar_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(FIX(ab_loop_repeat_));
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_unsigned_integers);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg1 = value;
	}
	arg2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = g2int_gensym_cons_1(arg1,arg2);
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
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_unsigned_integers;  /* write-icp-list-of-unsigned-integers */

/* WRITE-ICP-LIST-OF-UNSIGNED-INTEGERS */
Object g2int_write_icp_list_of_unsigned_integers(list_of_unsigned_integers)
    Object list_of_unsigned_integers;
{
    Object unsigned_integer, ab_loop_list_, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, v1, v2, v3;
    Object result;

    x_note_fn_call(42,14);
    if (G2int_disable_resumability) {
	g2int_write_icp_unsigned_integer(length(list_of_unsigned_integers));
	unsigned_integer = Nil;
	ab_loop_list_ = list_of_unsigned_integers;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	unsigned_integer = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_write_icp_unsigned_integer(unsigned_integer);
	goto next_loop;
      end_loop:
	temp = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list_of_unsigned_integers,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_list_of_unsigned_integers,top,Nil);
	}
	list_of_unsigned_integers = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_unsigned_integers;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,
		g2int_write_icp_unsigned_integer(length(list_of_unsigned_integers)))) 
		    {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	unsigned_integer = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loop_list_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_unsigned_integers;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	unsigned_integer = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      resume:
	if (EQ(icp_suspend_1,
		g2int_write_icp_unsigned_integer(unsigned_integer))) {
	    g2int_resumable_icp_push(ab_loop_list_);
	    g2int_resumable_icp_push(unsigned_integer);
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(list_of_unsigned_integers);
	    g2int_resumable_icp_push(Qg2int_write_icp_list_of_unsigned_integers);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_integers;  /* read-icp-list-of-integers */

/* READ-ICP-LIST-OF-INTEGERS */
Object g2int_read_icp_list_of_integers()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(42,15);
    if (G2int_disable_resumability) {
	ab_loop_repeat_ = IFIX(g2int_read_icp_integer());
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = g2int_gensym_cons_1(g2int_read_icp_integer(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end;
	temp = Qnil;
      end:;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_list_of_integers,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_list_of_integers,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    ab_loop_repeat_ = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_integers);
		return VALUES_1(G2int_icp_suspend);
	    }
	    ab_loop_repeat_ = IFIX(value);
	}
	ab_loopvar_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(FIX(ab_loop_repeat_));
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_integers);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg1 = value;
	}
	arg2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = g2int_gensym_cons_1(arg1,arg2);
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
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_integers;  /* write-icp-list-of-integers */

/* WRITE-ICP-LIST-OF-INTEGERS */
Object g2int_write_icp_list_of_integers(list_of_integers)
    Object list_of_integers;
{
    Object integer, ab_loop_list_, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, v1, v2, v3;
    Object result;

    x_note_fn_call(42,16);
    if (G2int_disable_resumability) {
	g2int_write_icp_integer(length(list_of_integers));
	integer = Nil;
	ab_loop_list_ = list_of_integers;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	integer = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_write_icp_integer(integer);
	goto next_loop;
      end_loop:
	temp = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list_of_integers,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_list_of_integers,top,Nil);
	}
	list_of_integers = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_integers;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,
		g2int_write_icp_integer(length(list_of_integers)))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	integer = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loop_list_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_integers;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	integer = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      resume:
	if (EQ(icp_suspend_1,g2int_write_icp_integer(integer))) {
	    g2int_resumable_icp_push(ab_loop_list_);
	    g2int_resumable_icp_push(integer);
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(list_of_integers);
	    g2int_resumable_icp_push(Qg2int_write_icp_list_of_integers);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_large_integer;  /* read-icp-large-integer */

/* READ-ICP-LARGE-INTEGER */
Object g2int_read_icp_large_integer(initial_icp_byte_init)
    Object initial_icp_byte_init;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, initial_icp_byte_1;
    Object test, count_2, arg1, value, arg2;
    SI_Long initial_icp_byte, count_1, negative_value_so_far, ab_loop_repeat_;
    SI_Long temp_1, value_so_far;
    char temp_2;

    x_note_fn_call(42,17);
    initial_icp_byte = IFIX(initial_icp_byte_init);
    if (G2int_disable_resumability) {
	if (initial_icp_byte > (SI_Long)63500L) {
	    count_1 = initial_icp_byte - (SI_Long)63501L;
	    if (count_1 == (SI_Long)2L)
		temp = Most_negative_fixnum;
	    else {
		negative_value_so_far = 
			IFIX(FIXNUM_NEGATE(g2int_read_icp_byte()));
		ab_loop_repeat_ = count_1;
	      next_loop:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		temp_1 = negative_value_so_far << (SI_Long)15L;
		negative_value_so_far = temp_1 - IFIX(g2int_read_icp_byte());
		goto next_loop;
	      end_loop:
		temp = FIX(negative_value_so_far);
		goto end;
		temp = Qnil;
	      end:;
	    }
	}
	else {
	    value_so_far = IFIX(g2int_read_icp_byte());
	    ab_loop_repeat_ = initial_icp_byte - (SI_Long)63001L;
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    temp_1 = value_so_far << (SI_Long)15L;
	    value_so_far = temp_1 + IFIX(g2int_read_icp_byte());
	    goto next_loop_1;
	  end_loop_1:
	    temp = FIX(value_so_far);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_large_integer,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_large_integer,top,Nil);
	}
	initial_icp_byte_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : FIX(initial_icp_byte);
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_2 = TRUEP(test);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? EQ(test,Qg2int_true) : IFIX(initial_icp_byte_1) > 
		(SI_Long)63500L) {
	    count_2 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : 
		    FIX(IFIX(initial_icp_byte_1) - (SI_Long)63501L);
	    if ( !(resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    && IFIX(count_2) == (SI_Long)2L)
		temp = Most_negative_fixnum;
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    negative_value_so_far = IFIX(g2int_resumable_icp_pop());
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(count_2);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(initial_icp_byte_1);
			    g2int_resumable_icp_push(Qg2int_read_icp_large_integer);
			    return VALUES_1(G2int_icp_suspend);
			}
			arg1 = value;
		    }
		    negative_value_so_far = IFIX(FIXNUM_NEGATE(arg1));
		}
		ab_loop_repeat_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? IFIX(g2int_resumable_icp_pop()) : IFIX(count_2);
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		    goto resume;
	      next_loop_2:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop_2;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      resume:
		arg1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(negative_value_so_far << (SI_Long)15L);
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg2 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_byte();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(arg1);
			g2int_resumable_icp_push(FIX(ab_loop_repeat_));
			g2int_resumable_icp_push(FIX(negative_value_so_far));
			g2int_resumable_icp_push(count_2);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(initial_icp_byte_1);
			g2int_resumable_icp_push(Qg2int_read_icp_large_integer);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg2 = value;
		}
		negative_value_so_far = IFIX(FIXNUM_MINUS(arg1,arg2));
		goto next_loop_2;
	      end_loop_2:
		temp = FIX(negative_value_so_far);
		goto end_2;
		temp = Qnil;
	      end_2:;
	    }
	}
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		value_so_far = IFIX(g2int_resumable_icp_pop());
	    else {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(initial_icp_byte_1);
		    g2int_resumable_icp_push(Qg2int_read_icp_large_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		value_so_far = IFIX(value);
	    }
	    ab_loop_repeat_ = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : 
		    IFIX(initial_icp_byte_1) - (SI_Long)63001L;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		goto resume_1;
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	  resume_1:
	    arg1 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX(value_so_far << 
		    (SI_Long)15L);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg2 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(FIX(ab_loop_repeat_));
		    g2int_resumable_icp_push(FIX(value_so_far));
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(initial_icp_byte_1);
		    g2int_resumable_icp_push(Qg2int_read_icp_large_integer);
		    return VALUES_1(G2int_icp_suspend);
		}
		arg2 = value;
	    }
	    value_so_far = IFIX(FIXNUM_ADD(arg1,arg2));
	    goto next_loop_3;
	  end_loop_3:
	    temp = FIX(value_so_far);
	    goto end_3;
	    temp = Qnil;
	  end_3:;
	}
    }
    return VALUES_1(temp);
}

Object G2int_constant_in_large_integer_length_in_icp_bytes = UNBOUND;

/* LARGE-INTEGER-LENGTH-IN-ICP-BYTES */
Object g2int_large_integer_length_in_icp_bytes(fixnum_init)
    Object fixnum_init;
{
    SI_Long fixnum, upper_bits;

    x_note_fn_call(42,18);
    fixnum = IFIX(fixnum_init);
    if (fixnum < (SI_Long)0L) {
	if (fixnum == IFIX(Most_negative_fixnum))
	    return VALUES_1(FIX((SI_Long)4L));
	else
	    fixnum =  - fixnum;
    }
    upper_bits = fixnum & 
	    IFIX(G2int_constant_in_large_integer_length_in_icp_bytes);
    return VALUES_1(upper_bits == (SI_Long)0L ? FIX((SI_Long)2L) : 
	    FIX((SI_Long)3L));
}

Object G2int_write_icp_large_integer_constant = UNBOUND;

static Object Qg2int_write_icp_large_integer;  /* write-icp-large-integer */

/* WRITE-ICP-LARGE-INTEGER */
Object g2int_write_icp_large_integer(fixnum_init)
    Object fixnum_init;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, fixnum_1;
    Object lower_bits_1, test;
    SI_Long fixnum, byte_count, upper_bits, lower_bits;
    char temp_1;

    x_note_fn_call(42,19);
    fixnum = IFIX(fixnum_init);
    if (G2int_disable_resumability) {
	byte_count = (SI_Long)0L;
	if (fixnum < (SI_Long)0L) {
	    if (fixnum == IFIX(Most_negative_fixnum)) {
		g2int_write_icp_byte(FIX((SI_Long)63500L + (SI_Long)2L));
		g2int_write_icp_byte(G2int_write_icp_large_integer_constant);
		g2int_write_icp_byte(FIX((SI_Long)0L));
		return VALUES_1(Nil);
	    }
	    else {
		fixnum =  - fixnum;
		byte_count = byte_count + (SI_Long)500L;
	    }
	}
	upper_bits = fixnum >>  -  - (SI_Long)15L & (SI_Long)32767L;
	lower_bits = fixnum & (SI_Long)32767L;
	byte_count = byte_count + (SI_Long)63000L;
	if (upper_bits == (SI_Long)0L) {
	    g2int_write_icp_byte(FIX(byte_count + (SI_Long)1L));
	    g2int_write_icp_byte(FIX(lower_bits));
	}
	else {
	    g2int_write_icp_byte(FIX(byte_count + (SI_Long)2L));
	    g2int_write_icp_byte(FIX(upper_bits));
	    g2int_write_icp_byte(FIX(lower_bits));
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_large_integer,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_large_integer,top,Nil);
	}
	fixnum_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : FIX(fixnum);
	byte_count = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(fixnum_1) < (SI_Long)0L) {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || FIXNUM_EQ(fixnum_1,Most_negative_fixnum)) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (EQ(icp_suspend_1,
			g2int_write_icp_byte(FIX((SI_Long)63500L + 
			(SI_Long)2L)))) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    temp = G2int_icp_suspend;
		    goto end_block;
		}
	      l2_1:
		if (EQ(icp_suspend_1,
			g2int_write_icp_byte(G2int_write_icp_large_integer_constant))) 
			    {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    temp = G2int_icp_suspend;
		    goto end_block;
		}
	      l3:
		if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)0L)))) {
		    g2int_resumable_icp_push(FIX((SI_Long)3L));
		    temp = G2int_icp_suspend;
		    goto end_block;
		}
		return VALUES_1(Nil);
		goto end_block;
	      end_block:
		if (EQ(icp_suspend_1,temp)) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    temp = G2int_icp_suspend;
		    goto end_block_1;
		}
	    }
	    else if (T) {
		fixnum_1 = FIXNUM_NEGATE(fixnum_1);
		byte_count = byte_count + (SI_Long)500L;
	    }
	}
      l2:
	upper_bits = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : IFIX(fixnum_1) >>  -  - 
		(SI_Long)15L & (SI_Long)32767L;
	lower_bits_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : FIX(IFIX(fixnum_1) & 
		(SI_Long)32767L);
	if ( !(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)))
	    byte_count = byte_count + (SI_Long)63000L;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : upper_bits == (SI_Long)0L) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1_2;
			break;
		      case 2:
			goto l2_2;
			break;
		      default:
			break;
		    }
	    }
	  l1_2:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX(byte_count + 
		    (SI_Long)1L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		temp = G2int_icp_suspend;
		goto end_block_2;
	    }
	  l2_2:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(lower_bits_1))) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		temp = G2int_icp_suspend;
		goto end_block_2;
	    }
	    else
		temp = Nil;
	    goto end_block_2;
	  end_block_2:
	    if (EQ(icp_suspend_1,temp)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(lower_bits_1);
		g2int_resumable_icp_push(FIX(upper_bits));
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		temp = G2int_icp_suspend;
		goto end_block_1;
	    }
	    else
		temp = Nil;
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1_3;
			break;
		      case 2:
			goto l2_3;
			break;
		      case 3:
			goto l3_1;
			break;
		      default:
			break;
		    }
	    }
	  l1_3:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX(byte_count + 
		    (SI_Long)2L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		temp = G2int_icp_suspend;
		goto end_block_3;
	    }
	  l2_3:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX(upper_bits)))) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		temp = G2int_icp_suspend;
		goto end_block_3;
	    }
	  l3_1:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(lower_bits_1))) {
		g2int_resumable_icp_push(FIX((SI_Long)3L));
		temp = G2int_icp_suspend;
		goto end_block_3;
	    }
	    else
		temp = Nil;
	    goto end_block_3;
	  end_block_3:
	    if (EQ(icp_suspend_1,temp)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(lower_bits_1);
		g2int_resumable_icp_push(FIX(upper_bits));
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		temp = G2int_icp_suspend;
		goto end_block_1;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Qnil;
	goto end_block_1;
      end_block_1:
	if (EQ(icp_suspend_1,temp)) {
	    g2int_resumable_icp_push(FIX(byte_count));
	    g2int_resumable_icp_push(fixnum_1);
	    g2int_resumable_icp_push(Qg2int_write_icp_large_integer);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* FIXNUM-LENGTH-IN-ICP-BYTES */
Object g2int_fixnum_length_in_icp_bytes(fixnum)
    Object fixnum;
{
    Object temp;

    x_note_fn_call(42,20);
    temp = g2int_integer_length_in_icp_bytes(fixnum);
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_fixnum;  /* read-icp-fixnum */

/* READ-ICP-FIXNUM */
Object g2int_read_icp_fixnum()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    SI_Long icp_byte;

    x_note_fn_call(42,21);
    if (G2int_disable_resumability) {
	icp_byte = IFIX(g2int_read_icp_byte());
	temp = icp_byte > (SI_Long)63000L ? 
		g2int_read_icp_large_integer(FIX(icp_byte)) : FIX(icp_byte 
		- (SI_Long)31500L);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_fixnum,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_fixnum,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    icp_byte = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_fixnum);
		return VALUES_1(G2int_icp_suspend);
	    }
	    icp_byte = IFIX(value);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		icp_byte > (SI_Long)63000L) {
	    value = g2int_read_icp_large_integer(FIX(icp_byte));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(FIX(icp_byte));
		g2int_resumable_icp_push(Qg2int_read_icp_fixnum);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = FIX(icp_byte - (SI_Long)31500L);
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_fixnum;  /* write-icp-fixnum */

/* WRITE-ICP-FIXNUM */
Object g2int_write_icp_fixnum(fixnum)
    Object fixnum;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(42,22);
    if (G2int_disable_resumability)
	temp = g2int_write_icp_integer(fixnum);
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_fixnum,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_fixnum,top,Nil);
	}
	fixnum = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : fixnum;
	value = g2int_write_icp_integer(fixnum);
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(fixnum);
	    g2int_resumable_icp_push(Qg2int_write_icp_fixnum);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_character;  /* read-icp-character */

/* READ-ICP-CHARACTER */
Object g2int_read_icp_character()
{
    Object encoded_character, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;

    x_note_fn_call(42,23);
    if (G2int_disable_resumability) {
	encoded_character = g2int_read_icp_byte();
	temp = encoded_character ? CODE_CHAR(FIX(IFIX(encoded_character) 
		>>  -  - (SI_Long)8L)) : Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_character,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_character,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    encoded_character = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_character);
		return VALUES_1(G2int_icp_suspend);
	    }
	    encoded_character = value;
	}
	temp = encoded_character ? CODE_CHAR(FIX(IFIX(encoded_character) 
		>>  -  - (SI_Long)8L)) : Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_character;  /* write-icp-character */

/* WRITE-ICP-CHARACTER */
Object g2int_write_icp_character(character_1)
    Object character_1;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(42,24);
    if (G2int_disable_resumability)
	temp = g2int_write_icp_byte(CHAR_INT(character_1));
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_character,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_character,top,Nil);
	}
	character_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : character_1;
	value = g2int_write_icp_byte(CHAR_INT(character_1));
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(character_1);
	    g2int_resumable_icp_push(Qg2int_write_icp_character);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object string_constant_3;   /* "ICP attempted to read a text string longer than ~
				    *            the maximum allowed length of ~a characters.  ~
				    *            The string beginning ~s ~
				    *            will be truncated to the maximum allowed length."
				    */

static Object Qg2int_read_icp_wide_string;  /* read-icp-wide-string */

/* READ-ICP-WIDE-STRING */
Object g2int_read_icp_wide_string()
{
    Object string_length, text_string, character_index, characters_remaining;
    Object temp_1, array, start, array_1, beginning_of_truncated_string;
    Object resumable_icp_state_1, icp_suspend_1, top, test, value;
    Object maximum_length_1, text_string_length_1, v1, v2, v3;
    SI_Long maximum_length, text_string_length, length_1, block_size;
    SI_Long icp_buffer_position, ab_loop_bind_, icp_position, position_1;
    SI_Long temp_2, incff_1_arg, decff_1_arg;
    char temp;
    Object result;

    x_note_fn_call(42,25);
    if (G2int_disable_resumability) {
	string_length = IFIX(ISVREF(G2int_current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)23L ? 
		g2int_read_icp_unsigned_integer() : g2int_read_icp_byte();
	maximum_length = IFIX(ISVREF(G2int_current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)23L ? 
		IFIX(G2int_maximum_length_for_user_text_strings) : 
		(SI_Long)65536L;
	text_string_length = MIN(IFIX(string_length),maximum_length);
	text_string = g2int_obtain_text_string(FIX(text_string_length));
	character_index = FIX((SI_Long)0L);
	characters_remaining = Nil;
      next_loop:
	characters_remaining = FIX(text_string_length - IFIX(character_index));
	if ( !((SI_Long)0L < IFIX(characters_remaining)))
	    goto end_loop;
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = (SI_Long)0L < length_1;
	if (temp);
	else {
	    temp_1 = g2int_ensure_next_icp_message_series();
	    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	    temp = TRUEP(temp_1);
	}
	if ( !temp)
	    temp = TRUEP(Nil);
	else {
	    array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	    start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	    block_size = MIN(length_1,IFIX(characters_remaining));
	    icp_buffer_position = IFIX(start);
	    ab_loop_bind_ = IFIX(start) + block_size;
	  next_loop_1:
	    if (icp_buffer_position >= ab_loop_bind_)
		goto end_loop_1;
	    array_1 = array;
	    icp_position = icp_buffer_position;
	    position_1 = icp_position + icp_position;
	    temp_2 = (UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		    + UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L);
	    UBYTE_16_ISASET_1(text_string,IFIX(character_index),temp_2);
	    character_index = FIXNUM_ADD1(character_index);
	    icp_buffer_position = icp_buffer_position + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    incff_1_arg = block_size;
	    temp_2 = IFIX(G2int_current_read_icp_byte_position) + incff_1_arg;
	    G2int_current_read_icp_byte_position = FIX(temp_2);
	    decff_1_arg = block_size;
	    temp_2 = IFIX(G2int_number_of_icp_bytes_ready_to_read) - 
		    decff_1_arg;
	    G2int_number_of_icp_bytes_ready_to_read = FIX(temp_2);
	    temp = TRUEP(T);
	}
	if ( !temp)
	    g2int_read_icp_suspend();
	goto next_loop;
      end_loop:;
	character_index = FIX(text_string_length);
	characters_remaining = Nil;
      next_loop_2:
	characters_remaining = FIXNUM_MINUS(string_length,character_index);
	if ( !((SI_Long)0L < IFIX(characters_remaining)))
	    goto end_loop_2;
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = (SI_Long)0L < length_1;
	if (temp);
	else {
	    temp_1 = g2int_ensure_next_icp_message_series();
	    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	    temp = TRUEP(temp_1);
	}
	if ( !temp)
	    temp = TRUEP(Nil);
	else {
	    array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	    start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	    block_size = MIN(length_1,IFIX(characters_remaining));
	    incff_1_arg = block_size;
	    temp_2 = IFIX(character_index) + incff_1_arg;
	    character_index = FIX(temp_2);
	    incff_1_arg = block_size;
	    temp_2 = IFIX(G2int_current_read_icp_byte_position) + incff_1_arg;
	    G2int_current_read_icp_byte_position = FIX(temp_2);
	    decff_1_arg = block_size;
	    temp_2 = IFIX(G2int_number_of_icp_bytes_ready_to_read) - 
		    decff_1_arg;
	    G2int_number_of_icp_bytes_ready_to_read = FIX(temp_2);
	    temp = TRUEP(T);
	}
	if ( !temp)
	    g2int_read_icp_suspend();
	goto next_loop_2;
      end_loop_2:;
	if ( !(IFIX(string_length) == text_string_length)) {
	    beginning_of_truncated_string = 
		    g2int_text_string_substring(text_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_3,
		    G2int_maximum_length_for_user_text_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_text_string(beginning_of_truncated_string);
	}
	temp_1 = text_string;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_wide_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_wide_string,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    string_length = g2int_resumable_icp_pop();
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp = TRUEP(test);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? EQ(test,Qg2int_true) : 
		    IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)23L) {
		value = g2int_read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_read_icp_wide_string);
		    return VALUES_1(G2int_icp_suspend);
		}
		string_length = value;
	    }
	    else {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_read_icp_wide_string);
		    return VALUES_1(G2int_icp_suspend);
		}
		string_length = value;
	    }
	}
	maximum_length_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)23L ? G2int_maximum_length_for_user_text_strings :
		 FIX((SI_Long)65536L);
	text_string_length_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : FIXNUM_MIN(string_length,
		maximum_length_1);
	text_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		g2int_obtain_text_string(text_string_length_1);
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp_1 = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		    temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp_1)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	character_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : FIX((SI_Long)0L);
	characters_remaining = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_3:
	characters_remaining = FIXNUM_MINUS(text_string_length_1,
		character_index);
	if ( !((SI_Long)0L < IFIX(characters_remaining)))
	    goto end_loop_3;
      resume:
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = (SI_Long)0L < length_1;
	if (temp);
	else {
	    temp_1 = g2int_ensure_next_icp_message_series();
	    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	    temp = TRUEP(temp_1);
	}
	if ( !temp)
	    temp = TRUEP(Nil);
	else {
	    array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	    start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	    block_size = MIN(length_1,IFIX(characters_remaining));
	    icp_buffer_position = IFIX(start);
	    ab_loop_bind_ = IFIX(start) + block_size;
	  next_loop_4:
	    if (icp_buffer_position >= ab_loop_bind_)
		goto end_loop_4;
	    array_1 = array;
	    icp_position = icp_buffer_position;
	    position_1 = icp_position + icp_position;
	    temp_2 = (UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		    + UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L);
	    UBYTE_16_ISASET_1(text_string,IFIX(character_index),temp_2);
	    character_index = FIXNUM_ADD1(character_index);
	    icp_buffer_position = icp_buffer_position + (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:;
	    incff_1_arg = block_size;
	    temp_2 = IFIX(G2int_current_read_icp_byte_position) + incff_1_arg;
	    G2int_current_read_icp_byte_position = FIX(temp_2);
	    decff_1_arg = block_size;
	    temp_2 = IFIX(G2int_number_of_icp_bytes_ready_to_read) - 
		    decff_1_arg;
	    G2int_number_of_icp_bytes_ready_to_read = FIX(temp_2);
	    temp = TRUEP(T);
	}
	if (EQ(icp_suspend_1, !temp ? g2int_read_icp_suspend() : Nil)) {
	    g2int_resumable_icp_push(characters_remaining);
	    g2int_resumable_icp_push(character_index);
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	goto next_loop_3;
      end_loop_3:;
      l2:
	character_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : text_string_length_1;
	characters_remaining = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume_1;
      next_loop_5:
	characters_remaining = FIXNUM_MINUS(string_length,character_index);
	if ( !((SI_Long)0L < IFIX(characters_remaining)))
	    goto end_loop_5;
      resume_1:
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = (SI_Long)0L < length_1;
	if (temp);
	else {
	    temp_1 = g2int_ensure_next_icp_message_series();
	    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	    temp = TRUEP(temp_1);
	}
	if ( !temp)
	    temp = TRUEP(Nil);
	else {
	    array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	    start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	    block_size = MIN(length_1,IFIX(characters_remaining));
	    incff_1_arg = block_size;
	    temp_2 = IFIX(character_index) + incff_1_arg;
	    character_index = FIX(temp_2);
	    incff_1_arg = block_size;
	    temp_2 = IFIX(G2int_current_read_icp_byte_position) + incff_1_arg;
	    G2int_current_read_icp_byte_position = FIX(temp_2);
	    decff_1_arg = block_size;
	    temp_2 = IFIX(G2int_number_of_icp_bytes_ready_to_read) - 
		    decff_1_arg;
	    G2int_number_of_icp_bytes_ready_to_read = FIX(temp_2);
	    temp = TRUEP(T);
	}
	if (EQ(icp_suspend_1, !temp ? g2int_read_icp_suspend() : Nil)) {
	    g2int_resumable_icp_push(characters_remaining);
	    g2int_resumable_icp_push(character_index);
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	goto next_loop_5;
      end_loop_5:;
	if ( !FIXNUM_EQ(string_length,text_string_length_1)) {
	    beginning_of_truncated_string = 
		    g2int_text_string_substring(text_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_3,
		    G2int_maximum_length_for_user_text_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_text_string(beginning_of_truncated_string);
	}
	result = VALUES_1(text_string);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(text_string);
	    g2int_resumable_icp_push(text_string_length_1);
	    g2int_resumable_icp_push(maximum_length_1);
	    g2int_resumable_icp_push(string_length);
	    g2int_resumable_icp_push(Qg2int_read_icp_wide_string);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp_1 = v1;
    }
    return VALUES_1(temp_1);
}

static Object Qg2int_read_icp_text_string;  /* read-icp-text-string */

/* READ-ICP-TEXT-STRING */
Object g2int_read_icp_text_string()
{
    Object string_1, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object have_wide_string_p_1, test, value;
    char have_wide_string_p, temp_1;

    x_note_fn_call(42,26);
    if (G2int_disable_resumability) {
	have_wide_string_p = FIXNUM_LE(G2int_wide_strings_icp_version,
		ISVREF(G2int_current_icp_socket,(SI_Long)21L));
	string_1 = have_wide_string_p ? g2int_read_icp_wide_string() : 
		g2int_read_icp_gensym_string();
	if (have_wide_string_p)
	    temp = string_1;
	else {
	    temp = g2int_gensym_string_to_wide_string(string_1);
	    g2int_reclaim_gensym_string(string_1);
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_text_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_text_string,top,Nil);
	}
	have_wide_string_p_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		FIXNUM_LE(G2int_wide_strings_icp_version,
		ISVREF(G2int_current_icp_socket,(SI_Long)21L)) ? T : Nil;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    string_1 = g2int_resumable_icp_pop();
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : TRUEP(have_wide_string_p_1)) {
		value = g2int_read_icp_wide_string();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(have_wide_string_p_1);
		    g2int_resumable_icp_push(Qg2int_read_icp_text_string);
		    return VALUES_1(G2int_icp_suspend);
		}
		string_1 = value;
	    }
	    else {
		value = g2int_read_icp_gensym_string();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(have_wide_string_p_1);
		    g2int_resumable_icp_push(Qg2int_read_icp_text_string);
		    return VALUES_1(G2int_icp_suspend);
		}
		string_1 = value;
	    }
	}
	if (have_wide_string_p_1)
	    temp = string_1;
	else {
	    temp = g2int_gensym_string_to_wide_string(string_1);
	    g2int_reclaim_gensym_string(string_1);
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_4;   /* "ICP attempted to read a text string longer than ~
				    *            the maximum allowed length of ~a bytes.  ~
				    *            The string beginning ~s ~
				    *            will be truncated to the maximum allowed length."
				    */

static Object Qg2int_read_icp_gensym_string;  /* read-icp-gensym-string */

/* READ-ICP-GENSYM-STRING */
Object g2int_read_icp_gensym_string()
{
    Object gensym_string, string_length_exceeded_p, last_character_p, icp_byte;
    Object even_p, length_limit_exceeded_p, beginning_of_truncated_string;
    Object temp_2, resumable_icp_state_1, icp_suspend_1, top, value;
    SI_Long string_length, temp, character_code, temp_1, last_char_index;
    SI_Long character_index, gensymed_symbol;
    char character_1;
    Object result;

    x_note_fn_call(42,27);
    if (G2int_disable_resumability) {
	string_length = IFIX(g2int_read_icp_byte());
	temp = IFIX(G2int_maximum_length_for_user_gensym_strings);
	gensym_string = 
		g2int_obtain_simple_gensym_string(FIX(MIN(string_length,
		temp)));
	string_length_exceeded_p = Nil;
	character_code = (SI_Long)0L;
	character_1 = 'a';
	temp_1 = string_length - (SI_Long)1L;
	temp = IFIX(FIXNUM_SUB1(G2int_maximum_length_for_user_gensym_strings));
	last_char_index = MIN(temp_1,temp);
	character_index = (SI_Long)0L;
	last_character_p = Nil;
	icp_byte = Nil;
	even_p = T;
      next_loop:
	if ( !(character_index < string_length))
	    goto end_loop;
	last_character_p = character_index == last_char_index ? T : Nil;
	if (even_p) {
	    icp_byte = g2int_read_icp_byte();
	    even_p = Nil;
	    character_code = last_character_p ? IFIX(icp_byte) : 
		    IFIX(icp_byte) >>  -  - (SI_Long)8L;
	}
	else {
	    even_p = T;
	    gensymed_symbol = IFIX(icp_byte) & (SI_Long)255L;
	    character_code = gensymed_symbol;
	}
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(character_code)));
	if (character_index == 
		IFIX(G2int_maximum_length_for_user_gensym_strings))
	    string_length_exceeded_p = T;
	if ( !TRUEP(string_length_exceeded_p))
	    SET_ISCHAR(gensym_string,character_index,character_1);
	character_index = character_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	result = VALUES_2(gensym_string,string_length_exceeded_p);
	MVS_2(result,gensym_string,length_limit_exceeded_p);
	if (length_limit_exceeded_p) {
	    beginning_of_truncated_string = 
		    g2int_gensym_string_substring(gensym_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_4,
		    G2int_maximum_length_for_user_gensym_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_gensym_string(beginning_of_truncated_string);
	}
	temp_2 = gensym_string;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_gensym_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_gensym_string,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    string_length = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_gensym_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    string_length = IFIX(value);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gensym_string = g2int_resumable_icp_pop();
	else {
	    temp = IFIX(G2int_maximum_length_for_user_gensym_strings);
	    gensym_string = 
		    g2int_obtain_simple_gensym_string(FIX(MIN(string_length,
		    temp)));
	}
	string_length_exceeded_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	character_code = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	character_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		CHARACTER_TO_CHAR(g2int_resumable_icp_pop()) : 'a';
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    last_char_index = IFIX(g2int_resumable_icp_pop());
	else {
	    temp_1 = string_length - (SI_Long)1L;
	    temp = 
		    IFIX(FIXNUM_SUB1(G2int_maximum_length_for_user_gensym_strings));
	    last_char_index = MIN(temp_1,temp);
	}
	character_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	last_character_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	icp_byte = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	even_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : T;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !(character_index < string_length))
	    goto end_loop_1;
	last_character_p = character_index == last_char_index ? T : Nil;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		even_p) {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(even_p);
		g2int_resumable_icp_push(icp_byte);
		g2int_resumable_icp_push(last_character_p);
		g2int_resumable_icp_push(FIX(character_index));
		g2int_resumable_icp_push(FIX(last_char_index));
		g2int_resumable_icp_push(CHAR_TO_CHARACTER(character_1));
		g2int_resumable_icp_push(FIX(character_code));
		g2int_resumable_icp_push(string_length_exceeded_p);
		g2int_resumable_icp_push(gensym_string);
		g2int_resumable_icp_push(FIX(string_length));
		g2int_resumable_icp_push(Qg2int_read_icp_gensym_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    icp_byte = value;
	    even_p = Nil;
	    character_code = last_character_p ? IFIX(icp_byte) : 
		    IFIX(icp_byte) >>  -  - (SI_Long)8L;
	}
	else if (T) {
	    even_p = T;
	    gensymed_symbol = IFIX(icp_byte) & (SI_Long)255L;
	    character_code = gensymed_symbol;
	}
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(character_code)));
	if (character_index == 
		IFIX(G2int_maximum_length_for_user_gensym_strings))
	    string_length_exceeded_p = T;
	if ( !TRUEP(string_length_exceeded_p))
	    SET_ISCHAR(gensym_string,character_index,character_1);
	character_index = character_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	result = VALUES_2(gensym_string,string_length_exceeded_p);
	MVS_2(result,gensym_string,length_limit_exceeded_p);
	if (EQ(icp_suspend_1,gensym_string)) {
	    g2int_resumable_icp_push(Qg2int_read_icp_gensym_string);
	    return VALUES_1(G2int_icp_suspend);
	}
	if (length_limit_exceeded_p) {
	    beginning_of_truncated_string = 
		    g2int_gensym_string_substring(gensym_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_4,
		    G2int_maximum_length_for_user_gensym_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_gensym_string(beginning_of_truncated_string);
	}
	temp_2 = gensym_string;
    }
    return VALUES_1(temp_2);
}

static Object Qg2int_read_icp_raw_gensym_string;  /* read-icp-raw-gensym-string */

/* READ-ICP-RAW-GENSYM-STRING */
Object g2int_read_icp_raw_gensym_string()
{
    Object gensym_string, string_length_exceeded_p, last_character_p, icp_byte;
    Object even_p, raw_gensym_string, length_limit_exceeded_p;
    Object beginning_of_truncated_string, temp_2, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    SI_Long string_length, temp, character_code, temp_1, last_char_index;
    SI_Long character_index, gensymed_symbol;
    char character_1;
    Object result;

    x_note_fn_call(42,28);
    if (G2int_disable_resumability) {
	string_length = IFIX(g2int_read_icp_byte());
	temp = IFIX(G2int_maximum_length_for_user_gensym_strings);
	gensym_string = 
		g2int_obtain_simple_gensym_string(FIX(MIN(string_length,
		temp)));
	string_length_exceeded_p = Nil;
	character_code = (SI_Long)0L;
	character_1 = 'a';
	temp_1 = string_length - (SI_Long)1L;
	temp = IFIX(FIXNUM_SUB1(G2int_maximum_length_for_user_gensym_strings));
	last_char_index = MIN(temp_1,temp);
	character_index = (SI_Long)0L;
	last_character_p = Nil;
	icp_byte = Nil;
	even_p = T;
      next_loop:
	if ( !(character_index < string_length))
	    goto end_loop;
	last_character_p = character_index == last_char_index ? T : Nil;
	if (even_p) {
	    icp_byte = g2int_read_icp_byte();
	    even_p = Nil;
	    character_code = last_character_p ? IFIX(icp_byte) : 
		    IFIX(icp_byte) >>  -  - (SI_Long)8L;
	}
	else {
	    even_p = T;
	    gensymed_symbol = IFIX(icp_byte) & (SI_Long)255L;
	    character_code = gensymed_symbol;
	}
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(character_code)));
	if (character_index == 
		IFIX(G2int_maximum_length_for_user_gensym_strings))
	    string_length_exceeded_p = T;
	if ( !TRUEP(string_length_exceeded_p))
	    SET_ISCHAR(gensym_string,character_index,character_1);
	character_index = character_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	result = VALUES_2(gensym_string,string_length_exceeded_p);
	MVS_2(result,raw_gensym_string,length_limit_exceeded_p);
	if (length_limit_exceeded_p) {
	    beginning_of_truncated_string = 
		    g2int_gensym_string_substring(raw_gensym_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_4,
		    G2int_maximum_length_for_user_gensym_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_gensym_string(beginning_of_truncated_string);
	}
	temp_2 = raw_gensym_string;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_raw_gensym_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_raw_gensym_string,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    string_length = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_raw_gensym_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    string_length = IFIX(value);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gensym_string = g2int_resumable_icp_pop();
	else {
	    temp = IFIX(G2int_maximum_length_for_user_gensym_strings);
	    gensym_string = 
		    g2int_obtain_simple_gensym_string(FIX(MIN(string_length,
		    temp)));
	}
	string_length_exceeded_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	character_code = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	character_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		CHARACTER_TO_CHAR(g2int_resumable_icp_pop()) : 'a';
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    last_char_index = IFIX(g2int_resumable_icp_pop());
	else {
	    temp_1 = string_length - (SI_Long)1L;
	    temp = 
		    IFIX(FIXNUM_SUB1(G2int_maximum_length_for_user_gensym_strings));
	    last_char_index = MIN(temp_1,temp);
	}
	character_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	last_character_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	icp_byte = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	even_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : T;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !(character_index < string_length))
	    goto end_loop_1;
	last_character_p = character_index == last_char_index ? T : Nil;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		even_p) {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(even_p);
		g2int_resumable_icp_push(icp_byte);
		g2int_resumable_icp_push(last_character_p);
		g2int_resumable_icp_push(FIX(character_index));
		g2int_resumable_icp_push(FIX(last_char_index));
		g2int_resumable_icp_push(CHAR_TO_CHARACTER(character_1));
		g2int_resumable_icp_push(FIX(character_code));
		g2int_resumable_icp_push(string_length_exceeded_p);
		g2int_resumable_icp_push(gensym_string);
		g2int_resumable_icp_push(FIX(string_length));
		g2int_resumable_icp_push(Qg2int_read_icp_raw_gensym_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    icp_byte = value;
	    even_p = Nil;
	    character_code = last_character_p ? IFIX(icp_byte) : 
		    IFIX(icp_byte) >>  -  - (SI_Long)8L;
	}
	else if (T) {
	    even_p = T;
	    gensymed_symbol = IFIX(icp_byte) & (SI_Long)255L;
	    character_code = gensymed_symbol;
	}
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(character_code)));
	if (character_index == 
		IFIX(G2int_maximum_length_for_user_gensym_strings))
	    string_length_exceeded_p = T;
	if ( !TRUEP(string_length_exceeded_p))
	    SET_ISCHAR(gensym_string,character_index,character_1);
	character_index = character_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	result = VALUES_2(gensym_string,string_length_exceeded_p);
	MVS_2(result,raw_gensym_string,length_limit_exceeded_p);
	if (EQ(icp_suspend_1,raw_gensym_string)) {
	    g2int_resumable_icp_push(Qg2int_read_icp_raw_gensym_string);
	    return VALUES_1(G2int_icp_suspend);
	}
	if (length_limit_exceeded_p) {
	    beginning_of_truncated_string = 
		    g2int_gensym_string_substring(raw_gensym_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_4,
		    G2int_maximum_length_for_user_gensym_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_gensym_string(beginning_of_truncated_string);
	}
	temp_2 = raw_gensym_string;
    }
    return VALUES_1(temp_2);
}

/* RECLAIM-TEXT-OR-GENSYM-STRING */
Object g2int_reclaim_text_or_gensym_string(text_or_gensym_string)
    Object text_or_gensym_string;
{
    x_note_fn_call(42,29);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_or_gensym_string) != (SI_Long)0L)
	g2int_reclaim_text_string(text_or_gensym_string);
    else
	g2int_reclaim_gensym_string(text_or_gensym_string);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-TEXT-OR-GENSYM-STRING-FUNCTION */
Object g2int_reclaim_if_text_or_gensym_string_function(string_1)
    Object string_1;
{
    x_note_fn_call(42,30);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L)
	g2int_reclaim_text_string(string_1);
    else if (STRINGP(string_1))
	g2int_reclaim_gensym_string(string_1);
    return VALUES_1(Nil);
}

/* WIDE-STRING-LENGTH-IN-ICP-BYTES */
Object g2int_wide_string_length_in_icp_bytes(wide_string)
    Object wide_string;
{
    Object temp;

    x_note_fn_call(42,31);
    temp = g2int_lengthw(wide_string);
    temp = FIXNUM_ADD1(FIXNUM_MIN(temp,
	    G2int_maximum_length_for_user_text_strings));
    return VALUES_1(temp);
}

/* COPY-WIDESTR-TO-ICPBUF */
Object g2int_copy_widestr_to_icpbuf(wide_string,string_start,
	    icp_write_buffer,buffer_start,count_1)
    Object wide_string, string_start, icp_write_buffer, buffer_start, count_1;
{
    Object ab_loop_iter_flag_, array;
    SI_Long i, ab_loop_bind_, j, icp_position, position_1, value, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(42,32);
    i = IFIX(buffer_start);
    ab_loop_bind_ = IFIX(FIXNUM_ADD(buffer_start,count_1));
    j = IFIX(string_start);
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	j = j + (SI_Long)1L;
    array = icp_write_buffer;
    icp_position = i;
    position_1 = icp_position + icp_position;
    value = UBYTE_16_ISAREF_1(wide_string,j);
    temp = value >>  -  - (SI_Long)8L;
    UBYTE_8_ISASET_1(array,position_1,temp);
    temp = position_1 + (SI_Long)1L;
    gensymed_symbol = (SI_Long)255L & value;
    UBYTE_8_ISASET_1(array,temp,gensymed_symbol);
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_5;   /* "ICP attempted to write a text string longer than ~
				    *            the maximum allowed length of ~a characters.  ~
				    *            The string beginning ~s ~
				    *            will be truncated to the maximum allowed length."
				    */

static Object Qg2int_write_icp_wide_string;  /* write-icp-wide-string */

/* WRITE-ICP-WIDE-STRING */
Object g2int_write_icp_wide_string(wide_string)
    Object wide_string;
{
    Object beginning_of_truncated_string, array, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top, test, v1, v2, v3;
    SI_Long length_1, string_length, maximum_length, character_index;
    SI_Long characters_remaining, start, block_size, incff_1_arg, temp;
    SI_Long decff_1_arg;
    char temp_2;
    Object result;

    x_note_fn_call(42,33);
    if (G2int_disable_resumability) {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
	string_length = UBYTE_16_ISAREF_1(wide_string,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	maximum_length = IFIX(ISVREF(G2int_current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)23L ? 
		IFIX(G2int_maximum_length_for_user_text_strings) : 
		(SI_Long)65536L;
	if (string_length >= maximum_length) {
	    beginning_of_truncated_string = 
		    g2int_text_string_substring(wide_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_5,
		    FIX(maximum_length),beginning_of_truncated_string);
	    g2int_reclaim_text_string(beginning_of_truncated_string);
	    string_length = maximum_length;
	}
	if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)23L)
	    g2int_write_icp_unsigned_integer(FIX(string_length));
	else
	    g2int_write_icp_byte(FIX(string_length));
	character_index = (SI_Long)0L;
	characters_remaining = (SI_Long)0L;
      next_loop:
	characters_remaining = string_length - character_index;
	if ( !((SI_Long)0L < characters_remaining))
	    goto end_loop;
	if (G2int_writing_resumable_icp_messages_p && 
		FIXNUM_GT(FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
		G2int_number_of_icp_bytes_to_fill_buffer),
		G2int_minimum_message_series_size_before_suspending))
	    G2int_starresumable_icp_statestar = Nil;
	else {
	    length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	    if ((SI_Long)0L == length_1) {
		g2int_write_get_new_buffer();
		length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	    }
	    array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	    start = IFIX(FIXNUM_ADD1(G2int_current_write_icp_byte_position));
	    block_size = MIN(length_1,characters_remaining);
	    inline_copy_widestr_to_icpbuf(UBYTE_16_SARRAY_TO_USHORT_PTR(wide_string),
		    character_index,UBYTE_8_SARRAY_TO_UCHAR_PTR(array),
		    start,block_size);
	    incff_1_arg = block_size;
	    character_index = character_index + incff_1_arg;
	    incff_1_arg = block_size;
	    temp = IFIX(G2int_current_write_icp_byte_position) + incff_1_arg;
	    G2int_current_write_icp_byte_position = FIX(temp);
	    decff_1_arg = block_size;
	    temp = IFIX(G2int_number_of_icp_bytes_to_fill_buffer) - 
		    decff_1_arg;
	    G2int_number_of_icp_bytes_to_fill_buffer = FIX(temp);
	}
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_wide_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_wide_string,top,Nil);
	}
	wide_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : wide_string;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    string_length = IFIX(g2int_resumable_icp_pop());
	else {
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
	    string_length = UBYTE_16_ISAREF_1(wide_string,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	}
	maximum_length = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)23L ? 
		IFIX(G2int_maximum_length_for_user_text_strings) : 
		(SI_Long)65536L;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp_1 = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		    temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp_1)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
	if (string_length >= maximum_length) {
	    beginning_of_truncated_string = 
		    g2int_text_string_substring(wide_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_5,
		    FIX(maximum_length),beginning_of_truncated_string);
	    g2int_reclaim_text_string(beginning_of_truncated_string);
	    string_length = maximum_length;
	}
      l1:
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_2 = TRUEP(test);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? EQ(test,Qg2int_true) : 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)23L) {
	    if (EQ(icp_suspend_1,
		    g2int_write_icp_unsigned_integer(FIX(string_length)))) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	}
	else if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX(string_length)))) {
	    g2int_resumable_icp_push(Qg2int_false);
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	character_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	characters_remaining = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	characters_remaining = string_length - character_index;
	if ( !((SI_Long)0L < characters_remaining))
	    goto end_loop_1;
      resume:
	if (G2int_writing_resumable_icp_messages_p && 
		FIXNUM_GT(FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
		G2int_number_of_icp_bytes_to_fill_buffer),
		G2int_minimum_message_series_size_before_suspending)) {
	    G2int_starresumable_icp_statestar = Nil;
	    temp_1 = G2int_icp_suspend;
	}
	else {
	    length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	    if ((SI_Long)0L == length_1) {
		g2int_write_get_new_buffer();
		length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	    }
	    array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	    start = IFIX(FIXNUM_ADD1(G2int_current_write_icp_byte_position));
	    block_size = MIN(length_1,characters_remaining);
	    inline_copy_widestr_to_icpbuf(UBYTE_16_SARRAY_TO_USHORT_PTR(wide_string),
		    character_index,UBYTE_8_SARRAY_TO_UCHAR_PTR(array),
		    start,block_size);
	    incff_1_arg = block_size;
	    character_index = character_index + incff_1_arg;
	    incff_1_arg = block_size;
	    temp = IFIX(G2int_current_write_icp_byte_position) + incff_1_arg;
	    G2int_current_write_icp_byte_position = FIX(temp);
	    decff_1_arg = block_size;
	    temp = IFIX(G2int_number_of_icp_bytes_to_fill_buffer) - 
		    decff_1_arg;
	    G2int_number_of_icp_bytes_to_fill_buffer = FIX(temp);
	    temp_1 = G2int_number_of_icp_bytes_to_fill_buffer;
	}
	if (EQ(icp_suspend_1,temp_1)) {
	    g2int_resumable_icp_push(FIX(characters_remaining));
	    g2int_resumable_icp_push(FIX(character_index));
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(FIX(maximum_length));
	    g2int_resumable_icp_push(FIX(string_length));
	    g2int_resumable_icp_push(wide_string);
	    g2int_resumable_icp_push(Qg2int_write_icp_wide_string);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp_1 = v1;
    }
    return VALUES_1(temp_1);
}

static Object Qg2int_write_icp_text_string;  /* write-icp-text-string */

/* WRITE-ICP-TEXT-STRING */
Object g2int_write_icp_text_string(text_string)
    Object text_string;
{
    Object converted_string, output_string, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, want_wide_string_p_1, gensymed_symbol, test;
    Object value;
    char want_wide_string_p, temp_1;

    x_note_fn_call(42,34);
    if (G2int_disable_resumability) {
	want_wide_string_p = FIXNUM_LE(G2int_wide_strings_icp_version,
		ISVREF(G2int_current_icp_socket,(SI_Long)22L));
	converted_string =  !want_wide_string_p ? 
		g2int_wide_string_to_gensym_string(text_string) : Nil;
	output_string = converted_string;
	if (output_string);
	else
	    output_string = text_string;
	temp = want_wide_string_p ? 
		g2int_write_icp_wide_string(output_string) : 
		g2int_write_icp_gensym_string(output_string);
	if (converted_string)
	    g2int_reclaim_gensym_string(converted_string);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_text_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_text_string,top,Nil);
	}
	text_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : text_string;
	want_wide_string_p_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		FIXNUM_LE(G2int_wide_strings_icp_version,
		ISVREF(G2int_current_icp_socket,(SI_Long)22L)) ? T : Nil;
	converted_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() :  !TRUEP(want_wide_string_p_1) ?
		 g2int_wide_string_to_gensym_string(text_string) : Nil;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    output_string = g2int_resumable_icp_pop();
	else {
	    output_string = converted_string;
	    if (output_string);
	    else
		output_string = text_string;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gensymed_symbol = g2int_resumable_icp_pop();
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : TRUEP(want_wide_string_p_1)) {
		value = g2int_write_icp_wide_string(output_string);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(output_string);
		    g2int_resumable_icp_push(converted_string);
		    g2int_resumable_icp_push(want_wide_string_p_1);
		    g2int_resumable_icp_push(text_string);
		    g2int_resumable_icp_push(Qg2int_write_icp_text_string);
		    return VALUES_1(G2int_icp_suspend);
		}
		gensymed_symbol = value;
	    }
	    else {
		value = g2int_write_icp_gensym_string(output_string);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(output_string);
		    g2int_resumable_icp_push(converted_string);
		    g2int_resumable_icp_push(want_wide_string_p_1);
		    g2int_resumable_icp_push(text_string);
		    g2int_resumable_icp_push(Qg2int_write_icp_text_string);
		    return VALUES_1(G2int_icp_suspend);
		}
		gensymed_symbol = value;
	    }
	}
	if (converted_string)
	    g2int_reclaim_gensym_string(converted_string);
	temp = gensymed_symbol;
    }
    return VALUES_1(temp);
}

/* GENSYM-STRING-LENGTH-IN-ICP-BYTES */
Object g2int_gensym_string_length_in_icp_bytes(gensym_string)
    Object gensym_string;
{
    Object temp_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, temp;
    char string_is_simple_qm;

    x_note_fn_call(42,35);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    gensymed_symbol = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string)) : 
	    IFIX(length(gensym_string));
    gensymed_symbol_1 = IFIX(G2int_maximum_length_for_user_gensym_strings);
    gensymed_symbol = MIN(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol_1 = (SI_Long)2L - (SI_Long)1L;
    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol_1 = (SI_Long)2L;
    temp = gensymed_symbol / gensymed_symbol_1;
    temp_1 = FIXNUM_ADD1(FIX(temp));
    return VALUES_1(temp_1);
}

static Object string_constant_6;   /* "ICP attempted to write a string longer than ~
				    *            the maximum allowed length of ~a bytes.  ~
				    *            The string beginning ~s ~
				    *            will be truncated to the maximum allowed length."
				    */

static Object Qg2int_write_icp_raw_gensym_string;  /* write-icp-raw-gensym-string */

/* WRITE-ICP-RAW-GENSYM-STRING */
Object g2int_write_icp_raw_gensym_string(raw_gensym_string)
    Object raw_gensym_string;
{
    Object string_length, beginning_of_truncated_string, first_char, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, string_is_simple_qm_1;
    Object test, v1, v2, v3;
    SI_Long i, ab_loop_bind_;
    char string_is_simple_qm, temp_1;
    Object result;

    x_note_fn_call(42,36);
    if (G2int_disable_resumability) {
	string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(raw_gensym_string);
	string_length = string_is_simple_qm ? 
		SIMPLE_ARRAY_ANY_1_LENGTH(raw_gensym_string) : 
		length(raw_gensym_string);
	if (FIXNUM_GT(string_length,
		G2int_maximum_length_for_user_gensym_strings)) {
	    beginning_of_truncated_string = 
		    g2int_gensym_string_substring(raw_gensym_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_6,
		    G2int_maximum_length_for_user_gensym_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_gensym_string(beginning_of_truncated_string);
	    string_length = G2int_maximum_length_for_user_gensym_strings;
	}
	g2int_write_icp_byte(string_length);
	if (string_is_simple_qm) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(string_length));
	    first_char = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    first_char = CHR(ISCHAR(raw_gensym_string,i));
	    g2int_write_icp_byte(FIX((IFIX(CHAR_INT(first_char)) << 
		    (SI_Long)8L) + 
		    IFIX(CHAR_INT(CHR(ISCHAR(raw_gensym_string,i + 
		    (SI_Long)1L))))));
	    i = i + (SI_Long)2L;
	    goto next_loop;
	  end_loop:
	    if (i < IFIX(string_length))
		g2int_write_icp_byte(CHAR_INT(SCHAR(raw_gensym_string,
			FIXNUM_SUB1(string_length))));
	    temp = Qnil;
	}
	else {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(string_length));
	    first_char = Nil;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    first_char = CHR(ICHAR(raw_gensym_string,i));
	    g2int_write_icp_byte(FIX((IFIX(CHAR_INT(first_char)) << 
		    (SI_Long)8L) + 
		    IFIX(CHAR_INT(CHR(ICHAR(raw_gensym_string,i + 
		    (SI_Long)1L))))));
	    i = i + (SI_Long)2L;
	    goto next_loop_1;
	  end_loop_1:
	    if (i < IFIX(string_length))
		g2int_write_icp_byte(CHAR_INT(CHAR(raw_gensym_string,
			FIXNUM_SUB1(string_length))));
	    temp = Qnil;
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_raw_gensym_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_raw_gensym_string,top,Nil);
	}
	raw_gensym_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : raw_gensym_string;
	string_is_simple_qm_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() :  
		!ARRAY_HAS_FILL_POINTER_P(raw_gensym_string) ? T : Nil;
	string_length = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : string_is_simple_qm_1 ? 
		SIMPLE_ARRAY_ANY_1_LENGTH(raw_gensym_string) : 
		length(raw_gensym_string);
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
	if (FIXNUM_GT(string_length,
		G2int_maximum_length_for_user_gensym_strings)) {
	    beginning_of_truncated_string = 
		    g2int_gensym_string_substring(raw_gensym_string,
		    FIX((SI_Long)0L),FIX((SI_Long)20L));
	    g2int_notify_user_at_console(3,string_constant_6,
		    G2int_maximum_length_for_user_gensym_strings,
		    beginning_of_truncated_string);
	    g2int_reclaim_gensym_string(beginning_of_truncated_string);
	    string_length = G2int_maximum_length_for_user_gensym_strings;
	}
      l1:
	if (EQ(icp_suspend_1,g2int_write_icp_byte(string_length))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : TRUEP(string_is_simple_qm_1)) {
	    i = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : 
		    IFIX(FIXNUM_SUB1(string_length));
	    first_char = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1_1;
			break;
		      case 2:
			goto l2_1;
			break;
		      default:
			break;
		    }
	    }
	  next_loop_2:
	    if (i >= ab_loop_bind_)
		goto end_loop_2;
	    first_char = CHR(ISCHAR(raw_gensym_string,i));
	  l1_1:
	    if (EQ(icp_suspend_1,
		    g2int_write_icp_byte(FIX((IFIX(CHAR_INT(first_char)) 
		    << (SI_Long)8L) + 
		    IFIX(CHAR_INT(CHR(ISCHAR(raw_gensym_string,i + 
		    (SI_Long)1L)))))))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		g2int_resumable_icp_push(first_char);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(i));
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    i = i + (SI_Long)2L;
	    goto next_loop_2;
	  end_loop_2:
	  l2_1:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || i < IFIX(string_length)) {
		if (EQ(icp_suspend_1,
			g2int_write_icp_byte(CHAR_INT(SCHAR(raw_gensym_string,
			FIXNUM_SUB1(string_length)))))) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    g2int_resumable_icp_push(first_char);
		    g2int_resumable_icp_push(FIX(ab_loop_bind_));
		    g2int_resumable_icp_push(FIX(i));
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	    }
	    result = VALUES_1(Qnil);
	}
	else {
	    i = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : 
		    IFIX(FIXNUM_SUB1(string_length));
	    first_char = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1_2;
			break;
		      case 2:
			goto l2_2;
			break;
		      default:
			break;
		    }
	    }
	  next_loop_3:
	    if (i >= ab_loop_bind_)
		goto end_loop_3;
	    first_char = CHR(ICHAR(raw_gensym_string,i));
	  l1_2:
	    if (EQ(icp_suspend_1,
		    g2int_write_icp_byte(FIX((IFIX(CHAR_INT(first_char)) 
		    << (SI_Long)8L) + 
		    IFIX(CHAR_INT(CHR(ICHAR(raw_gensym_string,i + 
		    (SI_Long)1L)))))))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		g2int_resumable_icp_push(first_char);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(i));
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    i = i + (SI_Long)2L;
	    goto next_loop_3;
	  end_loop_3:
	  l2_2:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || i < IFIX(string_length)) {
		if (EQ(icp_suspend_1,
			g2int_write_icp_byte(CHAR_INT(CHAR(raw_gensym_string,
			FIXNUM_SUB1(string_length)))))) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    g2int_resumable_icp_push(first_char);
		    g2int_resumable_icp_push(FIX(ab_loop_bind_));
		    g2int_resumable_icp_push(FIX(i));
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	    }
	    result = VALUES_1(Qnil);
	}
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(string_length);
	    g2int_resumable_icp_push(string_is_simple_qm_1);
	    g2int_resumable_icp_push(raw_gensym_string);
	    g2int_resumable_icp_push(Qg2int_write_icp_raw_gensym_string);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_gensym_string;  /* write-icp-gensym-string */

/* WRITE-ICP-GENSYM-STRING */
Object g2int_write_icp_gensym_string(gensym_string)
    Object gensym_string;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(42,37);
    if (G2int_disable_resumability)
	temp = g2int_write_icp_raw_gensym_string(gensym_string);
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_gensym_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_gensym_string,top,Nil);
	}
	gensym_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gensym_string;
	value = g2int_write_icp_raw_gensym_string(gensym_string);
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(gensym_string);
	    g2int_resumable_icp_push(Qg2int_write_icp_gensym_string);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object Qg2int_icp_filtered_text_string_reader;  /* icp-filtered-text-string-reader */

static Object Qg2int_read_icp_filtered_text_string;  /* read-icp-filtered-text-string */

/* READ-ICP-FILTERED-TEXT-STRING */
Object g2int_read_icp_filtered_text_string()
{
    Object raw_text_string, result_1, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;

    x_note_fn_call(42,38);
    if (G2int_disable_resumability) {
	raw_text_string = g2int_read_icp_text_string();
	result_1 = g2int_export_text_string(2,raw_text_string,
		Qg2int_icp_filtered_text_string_reader);
	g2int_reclaim_text_or_gensym_string(raw_text_string);
	temp = result_1;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_filtered_text_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_filtered_text_string,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    raw_text_string = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_filtered_text_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    raw_text_string = value;
	}
	result_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : g2int_export_text_string(2,
		raw_text_string,Qg2int_icp_filtered_text_string_reader);
	g2int_reclaim_text_or_gensym_string(raw_text_string);
	temp = result_1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_icp_filtered_text_string_writer;  /* icp-filtered-text-string-writer */

static Object Qg2int_write_icp_filtered_text_string;  /* write-icp-filtered-text-string */

/* WRITE-ICP-FILTERED-TEXT-STRING */
Object g2int_write_icp_filtered_text_string(filtered_text_string)
    Object filtered_text_string;
{
    Object text_string, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object gensymed_symbol, value;

    x_note_fn_call(42,39);
    if (G2int_disable_resumability) {
	text_string = g2int_import_text_string(2,filtered_text_string,
		Qg2int_icp_filtered_text_string_writer);
	temp = g2int_write_icp_text_string(text_string);
	g2int_reclaim_text_string(text_string);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_filtered_text_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_filtered_text_string,top,Nil);
	}
	filtered_text_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : filtered_text_string;
	text_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : g2int_import_text_string(2,
		filtered_text_string,Qg2int_icp_filtered_text_string_writer);
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gensymed_symbol = g2int_resumable_icp_pop();
	else {
	    value = g2int_write_icp_text_string(text_string);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(text_string);
		g2int_resumable_icp_push(filtered_text_string);
		g2int_resumable_icp_push(Qg2int_write_icp_filtered_text_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gensymed_symbol = value;
	}
	g2int_reclaim_text_string(text_string);
	temp = gensymed_symbol;
    }
    return VALUES_1(temp);
}

static Object string_constant_7;   /* "Bad ICP-list-element: ~a" */

static Object Qg2int_write_icp_list_element;  /* write-icp-list-element */

/* WRITE-ICP-LIST-ELEMENT */
Object g2int_write_icp_list_element(list_element)
    Object list_element;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, test, value, v1;
    Object v2, v3;
    char temp_1;
    Object result;

    x_note_fn_call(42,40);
    if (G2int_disable_resumability) {
	if ( !TRUEP(list_element))
	    temp = g2int_write_icp_byte(G2int_list_element_null_type_tag);
	else if (FIXNUMP(list_element)) {
	    g2int_write_icp_byte(G2int_list_element_integer_type_tag);
	    temp = g2int_write_icp_integer(list_element);
	}
	else if (SYMBOLP(list_element)) {
	    g2int_write_icp_byte(G2int_list_element_symbol_type_tag);
	    temp = 
		    g2int_write_icp_text_string(g2int_symbol_name_text_string(list_element));
	}
	else if (g2int_text_string_p(list_element)) {
	    g2int_write_icp_byte(G2int_list_element_text_type_tag);
	    temp = g2int_write_icp_text_string(list_element);
	}
	else if (CONSP(list_element)) {
	    g2int_write_icp_byte(G2int_list_element_list_type_tag);
	    temp = g2int_write_icp_list(list_element);
	}
	else
	    temp = g2int_icp_error_internal(Qerror,string_constant_7,
		    list_element,Nil,Nil);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list_element,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_list_element,top,Nil);
	}
	list_element = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_element;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) :  !TRUEP(list_element)) {
	    value = g2int_write_icp_byte(G2int_list_element_null_type_tag);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(list_element);
		g2int_resumable_icp_push(Qg2int_write_icp_list_element);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : FIXNUMP(list_element)) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
			    break;
			  default:
			    break;
			}
		}
	      l1:
		if (EQ(icp_suspend_1,
			g2int_write_icp_byte(G2int_list_element_integer_type_tag))) 
			    {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l2:
		value = g2int_write_icp_integer(list_element);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		result = VALUES_1(value);
		goto end_block;
	      end_block:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(list_element);
		    g2int_resumable_icp_push(Qg2int_write_icp_list_element);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : SYMBOLP(list_element)) {
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			temp = g2int_resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (EQ(icp_suspend_1,
			    g2int_write_icp_byte(G2int_list_element_symbol_type_tag))) 
				{
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_1;
		    }
		  l2_1:
		    value = 
			    g2int_write_icp_text_string(g2int_symbol_name_text_string(list_element));
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_1;
		    }
		    result = VALUES_1(value);
		    goto end_block_1;
		  end_block_1:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(list_element);
			g2int_resumable_icp_push(Qg2int_write_icp_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = v1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(g2int_text_string_p(list_element))) {
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    temp = g2int_resumable_icp_pop();
			    if (! !(FIXNUMP(temp) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp)) {
				  case 1:
				    goto l1_2;
				    break;
				  case 2:
				    goto l2_2;
				    break;
				  default:
				    break;
				}
			}
		      l1_2:
			if (EQ(icp_suspend_1,
				g2int_write_icp_byte(G2int_list_element_text_type_tag))) 
				    {
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_2;
			}
		      l2_2:
			value = g2int_write_icp_text_string(list_element);
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_2;
			}
			result = VALUES_1(value);
			goto end_block_2;
		      end_block_2:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(list_element);
			    g2int_resumable_icp_push(Qg2int_write_icp_list_element);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = v1;
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    test = g2int_resumable_icp_pop();
			    temp_1 = TRUEP(test);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? EQ(test,Qg2int_true) : 
				CONSP(list_element)) {
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				temp = g2int_resumable_icp_pop();
				if (! !(FIXNUMP(temp) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp) && FIXNUM_LE(temp,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp)) {
				      case 1:
					goto l1_3;
					break;
				      case 2:
					goto l2_3;
					break;
				      default:
					break;
				    }
			    }
			  l1_3:
			    if (EQ(icp_suspend_1,
				    g2int_write_icp_byte(G2int_list_element_list_type_tag))) 
					{
				g2int_resumable_icp_push(FIX((SI_Long)1L));
				result = VALUES_1(G2int_icp_suspend);
				goto end_block_3;
			    }
			  l2_3:
			    value = g2int_write_icp_list(list_element);
			    if (EQ(icp_suspend_1,value)) {
				g2int_resumable_icp_push(FIX((SI_Long)2L));
				result = VALUES_1(G2int_icp_suspend);
				goto end_block_3;
			    }
			    result = VALUES_1(value);
			    goto end_block_3;
			  end_block_3:
			    MVS_3(result,v1,v2,v3);
			    if (EQ(icp_suspend_1,v1)) {
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(list_element);
				g2int_resumable_icp_push(Qg2int_write_icp_list_element);
				return VALUES_1(G2int_icp_suspend);
			    }
			    temp = v1;
			}
			else if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) || T) {
			    value = g2int_icp_error_internal(Qerror,
				    string_constant_7,list_element,Nil,Nil);
			    if (EQ(icp_suspend_1,value)) {
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(list_element);
				g2int_resumable_icp_push(Qg2int_write_icp_list_element);
				return VALUES_1(G2int_icp_suspend);
			    }
			    temp = value;
			}
			else
			    temp = Qnil;
		    }
		}
	    }
	}
    }
    return VALUES_1(temp);
}

/* RECLAIM-ICP-LIST-ELEMENT */
Object g2int_reclaim_icp_list_element(icp_list_element)
    Object icp_list_element;
{
    x_note_fn_call(42,41);
    if (CONSP(icp_list_element)) {
	g2int_reclaim_icp_list_element(CAR(icp_list_element));
	g2int_reclaim_icp_list_element(CDR(icp_list_element));
	g2int_reclaim_gensym_cons_1(icp_list_element);
    }
    else if (g2int_text_string_p(icp_list_element))
	g2int_reclaim_text_or_gensym_string(icp_list_element);
    return VALUES_1(Nil);
}

static Object Qg2int_read_icp_list_element;  /* read-icp-list-element */

/* READ-ICP-LIST-ELEMENT */
Object g2int_read_icp_list_element()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, key, value, arg1;

    x_note_fn_call(42,42);
    if (G2int_disable_resumability) {
	temp = g2int_read_icp_byte();
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		temp = Nil;
		break;
	      case 1:
		temp = g2int_read_icp_integer();
		break;
	      case 2:
		temp = g2int_intern_text_string(1,
			g2int_read_icp_text_string());
		break;
	      case 3:
		temp = g2int_read_icp_text_string();
		break;
	      case 4:
		temp = g2int_read_icp_list();
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_list_element,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_list_element,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    key = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_list_element);
		return VALUES_1(G2int_icp_suspend);
	    }
	    key = value;
	}
	temp = key;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		temp = Nil;
		break;
	      case 1:
		value = g2int_read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_list_element);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
		break;
	      case 2:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_read_icp_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		temp = g2int_intern_text_string(1,arg1);
		break;
	      case 3:
		value = g2int_read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_list_element);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
		break;
	      case 4:
		value = g2int_read_icp_list();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_list_element);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list;  /* write-icp-list */

/* WRITE-ICP-LIST */
Object g2int_write_icp_list(list_1)
    Object list_1;
{
    Object list_element, ab_loop_list_, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, v1, v2, v3;
    Object result;

    x_note_fn_call(42,43);
    if (G2int_disable_resumability) {
	g2int_write_icp_unsigned_integer(length(list_1));
	list_element = Nil;
	ab_loop_list_ = list_1;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	list_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_write_icp_list_element(list_element);
	goto next_loop;
      end_loop:
	temp = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_list,top,Nil);
	}
	list_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_1;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,
		    g2int_write_icp_unsigned_integer(length(list_1)))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	list_element = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loop_list_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_1;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	list_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      resume:
	if (EQ(icp_suspend_1,g2int_write_icp_list_element(list_element))) {
	    g2int_resumable_icp_push(ab_loop_list_);
	    g2int_resumable_icp_push(list_element);
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(list_1);
	    g2int_resumable_icp_push(Qg2int_write_icp_list);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list;  /* read-icp-list */

/* READ-ICP-LIST */
Object g2int_read_icp_list()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long item_count, ab_loop_bind_;

    x_note_fn_call(42,44);
    if (G2int_disable_resumability) {
	item_count = (SI_Long)1L;
	ab_loop_bind_ = IFIX(g2int_read_icp_unsigned_integer());
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (item_count > ab_loop_bind_)
	    goto end_loop;
	ab_loopvar__2 = g2int_gensym_cons_1(g2int_read_icp_list_element(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	item_count = item_count + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end;
	temp = Qnil;
      end:;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_list,top,Nil);
	}
	item_count = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)1L;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    ab_loop_bind_ = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(FIX(item_count));
		g2int_resumable_icp_push(Qg2int_read_icp_list);
		return VALUES_1(G2int_icp_suspend);
	    }
	    ab_loop_bind_ = IFIX(value);
	}
	ab_loopvar_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if (item_count > ab_loop_bind_)
	    goto end_loop_1;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_list_element();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(item_count));
		g2int_resumable_icp_push(Qg2int_read_icp_list);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg1 = value;
	}
	arg2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = g2int_gensym_cons_1(arg1,arg2);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	item_count = item_count + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

static Object string_constant_8;   /* "Bad ICP-improper-list-element: ~a" */

static Object Qg2int_write_icp_improper_list_element;  /* write-icp-improper-list-element */

/* WRITE-ICP-IMPROPER-LIST-ELEMENT */
Object g2int_write_icp_improper_list_element(improper_list_element)
    Object improper_list_element;
{
    Object temp, last_element, this_element, ab_loop_list_, this_element_cons;
    Object next_element, resumable_icp_state_1, icp_suspend_1, top, test;
    Object value, v1, v2, v3;
    char temp_1;
    Object result;

    x_note_fn_call(42,45);
    if (G2int_disable_resumability) {
	if ( !TRUEP(improper_list_element))
	    temp = g2int_write_icp_byte(G2int_list_element_null_type_tag);
	else if (FIXNUMP(improper_list_element)) {
	    g2int_write_icp_byte(G2int_list_element_integer_type_tag);
	    temp = g2int_write_icp_integer(improper_list_element);
	}
	else if (SYMBOLP(improper_list_element)) {
	    g2int_write_icp_byte(G2int_list_element_symbol_type_tag);
	    temp = 
		    g2int_write_icp_text_string(g2int_symbol_name_text_string(improper_list_element));
	}
	else if (g2int_text_string_p(improper_list_element)) {
	    g2int_write_icp_byte(G2int_list_element_text_type_tag);
	    temp = g2int_write_icp_text_string(improper_list_element);
	}
	else if (CONSP(improper_list_element)) {
	    last_element = last(improper_list_element,_);
	    if (CONSP(last_element) &&  !TRUEP(CDR(last_element))) {
		g2int_write_icp_byte(G2int_list_element_list_type_tag);
		g2int_write_icp_unsigned_integer(length(improper_list_element));
		this_element = Nil;
		ab_loop_list_ = improper_list_element;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		this_element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		g2int_write_icp_improper_list_element(this_element);
		goto next_loop;
	      end_loop:
		temp = Qnil;
	    }
	    else {
		this_element_cons = improper_list_element;
		this_element = Nil;
		next_element = Nil;
	      next_loop_1:
		this_element = CAR(this_element_cons);
		next_element = CDR(this_element_cons);
		if (ATOM(next_element)) {
		    g2int_write_icp_byte(G2int_list_element_cons_type_tag);
		    g2int_write_icp_improper_list_element(this_element);
		    g2int_write_icp_improper_list_element(next_element);
		    goto end_loop_1;
		}
		else {
		    g2int_write_icp_byte(G2int_list_element_cons_type_tag);
		    g2int_write_icp_improper_list_element(this_element);
		}
		this_element_cons = next_element;
		goto next_loop_1;
	      end_loop_1:
		temp = Qnil;
	    }
	}
	else
	    temp = g2int_icp_error_internal(Qerror,string_constant_8,
		    improper_list_element,Nil,Nil);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_improper_list_element,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_improper_list_element,top,Nil);
	}
	improper_list_element = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : improper_list_element;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) :  !TRUEP(improper_list_element)) {
	    value = g2int_write_icp_byte(G2int_list_element_null_type_tag);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(improper_list_element);
		g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : 
			FIXNUMP(improper_list_element)) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
			    break;
			  default:
			    break;
			}
		}
	      l1:
		if (EQ(icp_suspend_1,
			g2int_write_icp_byte(G2int_list_element_integer_type_tag))) 
			    {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l2:
		value = g2int_write_icp_integer(improper_list_element);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		result = VALUES_1(value);
		goto end_block;
	      end_block:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(improper_list_element);
		    g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : 
			SYMBOLP(improper_list_element)) {
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			temp = g2int_resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (EQ(icp_suspend_1,
			    g2int_write_icp_byte(G2int_list_element_symbol_type_tag))) 
				{
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_1;
		    }
		  l2_1:
		    value = 
			    g2int_write_icp_text_string(g2int_symbol_name_text_string(improper_list_element));
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_1;
		    }
		    result = VALUES_1(value);
		    goto end_block_1;
		  end_block_1:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(improper_list_element);
			g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = v1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(g2int_text_string_p(improper_list_element))) 
				{
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    temp = g2int_resumable_icp_pop();
			    if (! !(FIXNUMP(temp) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp)) {
				  case 1:
				    goto l1_2;
				    break;
				  case 2:
				    goto l2_2;
				    break;
				  default:
				    break;
				}
			}
		      l1_2:
			if (EQ(icp_suspend_1,
				g2int_write_icp_byte(G2int_list_element_text_type_tag))) 
				    {
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_2;
			}
		      l2_2:
			value = 
				g2int_write_icp_text_string(improper_list_element);
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_2;
			}
			result = VALUES_1(value);
			goto end_block_2;
		      end_block_2:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(improper_list_element);
			    g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = v1;
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    test = g2int_resumable_icp_pop();
			    temp_1 = TRUEP(test);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? EQ(test,Qg2int_true) : 
				CONSP(improper_list_element)) {
			    last_element = (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				    ? g2int_resumable_icp_pop() : 
				    last(improper_list_element,_);
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				test = g2int_resumable_icp_pop();
				temp_1 = TRUEP(test);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1 ? EQ(test,Qg2int_true) : 
				    CONSP(last_element) &&  
				    !TRUEP(CDR(last_element))) {
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) {
				    temp = g2int_resumable_icp_pop();
				    if (! !(FIXNUMP(temp) && 
					    FIXNUM_LE(FIX((SI_Long)-128L),
					    temp) && FIXNUM_LE(temp,
					    FIX((SI_Long)127L))))
					switch (INTEGER_TO_CHAR(temp)) {
					  case 1:
					    goto l1_3;
					    break;
					  case 2:
					    goto l2_3;
					    break;
					  case 3:
					    goto l3;
					    break;
					  default:
					    break;
					}
				}
			      l1_3:
				if (EQ(icp_suspend_1,
					g2int_write_icp_byte(G2int_list_element_list_type_tag))) 
					    {
				    g2int_resumable_icp_push(FIX((SI_Long)1L));
				    result = VALUES_1(G2int_icp_suspend);
				    goto end_block_3;
				}
			      l2_3:
				if (EQ(icp_suspend_1,
					g2int_write_icp_unsigned_integer(length(improper_list_element)))) 
					    {
				    g2int_resumable_icp_push(FIX((SI_Long)2L));
				    result = VALUES_1(G2int_icp_suspend);
				    goto end_block_3;
				}
			      l3:
				this_element = (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
					? g2int_resumable_icp_pop() : Nil;
				ab_loop_list_ = (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
					? g2int_resumable_icp_pop() : 
					improper_list_element;
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil))
				    goto resume;
			      next_loop_2:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop_2;
				this_element = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
			      resume:
				if (EQ(icp_suspend_1,
					g2int_write_icp_improper_list_element(this_element))) 
					    {
				    g2int_resumable_icp_push(ab_loop_list_);
				    g2int_resumable_icp_push(this_element);
				    g2int_resumable_icp_push(FIX((SI_Long)3L));
				    result = VALUES_1(G2int_icp_suspend);
				    goto end_block_3;
				}
				goto next_loop_2;
			      end_loop_2:
				result = VALUES_1(Qnil);
				goto end_block_3;
			      end_block_3:
				MVS_3(result,v1,v2,v3);
				if (EQ(icp_suspend_1,v1)) {
				    g2int_resumable_icp_push(Qg2int_true);
				    g2int_resumable_icp_push(last_element);
				    g2int_resumable_icp_push(Qg2int_true);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(improper_list_element);
				    g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
				    return VALUES_1(G2int_icp_suspend);
				}
				temp = v1;
			    }
			    else if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) || T) {
				this_element_cons = (resumable_icp_state_1 
					? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
					? g2int_resumable_icp_pop() : 
					improper_list_element;
				this_element = (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
					? g2int_resumable_icp_pop() : Nil;
				next_element = (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
					? g2int_resumable_icp_pop() : Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil))
				    goto resume_1;
			      next_loop_3:
				this_element = CAR(this_element_cons);
				next_element = CDR(this_element_cons);
			      resume_1:
				test = Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) {
				    test = g2int_resumable_icp_pop();
				    temp_1 = TRUEP(test);
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1 ? EQ(test,Qg2int_true) : 
					ATOM(next_element)) {
				    if (resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) {
					temp = g2int_resumable_icp_pop();
					if (! !(FIXNUMP(temp) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp) && FIXNUM_LE(temp,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp)) {
					      case 1:
						goto l1_4;
						break;
					      case 2:
						goto l2_4;
						break;
					      case 3:
						goto l3_1;
						break;
					      default:
						break;
					    }
				    }
				  l1_4:
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_byte(G2int_list_element_cons_type_tag))) 
						{
					g2int_resumable_icp_push(FIX((SI_Long)1L));
					temp = G2int_icp_suspend;
					goto end_block_4;
				    }
				  l2_4:
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_improper_list_element(this_element))) 
						{
					g2int_resumable_icp_push(FIX((SI_Long)2L));
					temp = G2int_icp_suspend;
					goto end_block_4;
				    }
				  l3_1:
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_improper_list_element(next_element))) 
						{
					g2int_resumable_icp_push(FIX((SI_Long)3L));
					temp = G2int_icp_suspend;
					goto end_block_4;
				    }
				    goto end_loop_3;
				    goto end_block_4;
				  end_block_4:
				    if (EQ(icp_suspend_1,temp)) {
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(next_element);
					g2int_resumable_icp_push(this_element);
					g2int_resumable_icp_push(this_element_cons);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(last_element);
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(improper_list_element);
					g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
					return VALUES_1(G2int_icp_suspend);
				    }
				}
				else if ((resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) || T) {
				    if (resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) {
					temp = g2int_resumable_icp_pop();
					if (! !(FIXNUMP(temp) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp) && FIXNUM_LE(temp,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp)) {
					      case 1:
						goto l1_5;
						break;
					      case 2:
						goto l2_5;
						break;
					      default:
						break;
					    }
				    }
				  l1_5:
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_byte(G2int_list_element_cons_type_tag))) 
						{
					g2int_resumable_icp_push(FIX((SI_Long)1L));
					temp = G2int_icp_suspend;
					goto end_block_5;
				    }
				  l2_5:
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_improper_list_element(this_element))) 
						{
					g2int_resumable_icp_push(FIX((SI_Long)2L));
					temp = G2int_icp_suspend;
					goto end_block_5;
				    }
				    else
					temp = Nil;
				    goto end_block_5;
				  end_block_5:
				    if (EQ(icp_suspend_1,temp)) {
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(next_element);
					g2int_resumable_icp_push(this_element);
					g2int_resumable_icp_push(this_element_cons);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(last_element);
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(improper_list_element);
					g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
					return VALUES_1(G2int_icp_suspend);
				    }
				}
				this_element_cons = next_element;
				goto next_loop_3;
			      end_loop_3:
				temp = Qnil;
			    }
			    else
				temp = Qnil;
			}
			else if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) || T) {
			    value = g2int_icp_error_internal(Qerror,
				    string_constant_8,
				    improper_list_element,Nil,Nil);
			    if (EQ(icp_suspend_1,value)) {
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(improper_list_element);
				g2int_resumable_icp_push(Qg2int_write_icp_improper_list_element);
				return VALUES_1(G2int_icp_suspend);
			    }
			    temp = value;
			}
			else
			    temp = Qnil;
		    }
		}
	    }
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_improper_list_element;  /* read-icp-improper-list-element */

/* READ-ICP-IMPROPER-LIST-ELEMENT */
Object g2int_read_icp_improper_list_element()
{
    Object temp, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object resumable_icp_state_1, icp_suspend_1, top, key, value, arg1, arg2;
    SI_Long item_count, ab_loop_bind_;

    x_note_fn_call(42,46);
    if (G2int_disable_resumability) {
	temp = g2int_read_icp_byte();
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		temp = Nil;
		break;
	      case 1:
		temp = g2int_read_icp_integer();
		break;
	      case 2:
		temp = g2int_intern_text_string(1,
			g2int_read_icp_text_string());
		break;
	      case 3:
		temp = g2int_read_icp_text_string();
		break;
	      case 4:
		item_count = (SI_Long)1L;
		ab_loop_bind_ = IFIX(g2int_read_icp_unsigned_integer());
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if (item_count > ab_loop_bind_)
		    goto end_loop;
		ab_loopvar__2 = 
			g2int_gensym_cons_1(g2int_read_icp_improper_list_element(),
			Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		item_count = item_count + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		temp = ab_loopvar_;
		goto end;
		temp = Qnil;
	      end:;
		break;
	      case 5:
		temp = g2int_read_icp_improper_list_element();
		temp = g2int_gensym_cons_1(temp,
			g2int_read_icp_improper_list_element());
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_improper_list_element,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_improper_list_element,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    key = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
		return VALUES_1(G2int_icp_suspend);
	    }
	    key = value;
	}
	temp = key;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		temp = Nil;
		break;
	      case 1:
		value = g2int_read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
		break;
	      case 2:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		temp = g2int_intern_text_string(1,arg1);
		break;
	      case 3:
		value = g2int_read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
		break;
	      case 4:
		item_count = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? IFIX(g2int_resumable_icp_pop()) : (SI_Long)1L;
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    ab_loop_bind_ = IFIX(g2int_resumable_icp_pop());
		else {
		    value = g2int_read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(FIX(item_count));
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    ab_loop_bind_ = IFIX(value);
		}
		ab_loopvar_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loopvar__1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loopvar__2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		    goto resume;
	      next_loop_1:
		if (item_count > ab_loop_bind_)
		    goto end_loop_1;
	      resume:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_improper_list_element();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(ab_loopvar__2);
			g2int_resumable_icp_push(ab_loopvar__1);
			g2int_resumable_icp_push(ab_loopvar_);
			g2int_resumable_icp_push(FIX(ab_loop_bind_));
			g2int_resumable_icp_push(FIX(item_count));
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		arg2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loopvar__2 = g2int_gensym_cons_1(arg1,arg2);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		item_count = item_count + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		temp = ab_loopvar_;
		goto end_1;
		temp = Qnil;
	      end_1:;
		break;
	      case 5:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_improper_list_element();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg2 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_improper_list_element();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(arg1);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_read_icp_improper_list_element);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg2 = value;
		}
		temp = g2int_gensym_cons_1(arg1,arg2);
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_improper_list;  /* write-icp-improper-list */

/* WRITE-ICP-IMPROPER-LIST */
Object g2int_write_icp_improper_list(improper_list)
    Object improper_list;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(42,47);
    if (G2int_disable_resumability)
	temp = g2int_write_icp_improper_list_element(improper_list);
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_improper_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_improper_list,top,Nil);
	}
	improper_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : improper_list;
	value = g2int_write_icp_improper_list_element(improper_list);
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(improper_list);
	    g2int_resumable_icp_push(Qg2int_write_icp_improper_list);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_improper_list;  /* read-icp-improper-list */

/* READ-ICP-IMPROPER-LIST */
Object g2int_read_icp_improper_list()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(42,48);
    if (G2int_disable_resumability)
	temp = g2int_read_icp_improper_list_element();
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_improper_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_improper_list,top,Nil);
	}
	value = g2int_read_icp_improper_list_element();
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(Qg2int_read_icp_improper_list);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

/* MUTATE-GENSYM-PLIST */
Object g2int_mutate_gensym_plist(gensym_plist,indicator,value)
    Object gensym_plist, indicator, value;
{
    Object l;

    x_note_fn_call(42,49);
    if ( !TRUEP(gensym_plist))
	return g2int_gensym_list_2(indicator,value);
    else {
	l = gensym_plist;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(CAR(l),indicator)) {
	    M_CADR(l) = value;
	    return VALUES_1(gensym_plist);
	}
	l = CDDR(l);
	goto next_loop;
      end_loop:
	return g2int_gensym_cons_1(indicator,g2int_gensym_cons_1(value,
		gensym_plist));
	return VALUES_1(Qnil);
    }
}

static Object Qg2int_item_with_handle_index_space;  /* item-with-handle-index-space */

static Object Qg2int_remove_icp_port_entries_from_icp_object_list;  /* remove-icp-port-entries-from-icp-object-list */

static Object Qg2int_remove_icp_port_entries_from_icp_object;  /* remove-icp-port-entries-from-icp-object */

/* MAKE-ICP-OBJECT-INDEX-SPACE */
Object g2int_make_icp_object_index_space(name_of_icp_object_index_space)
    Object name_of_icp_object_index_space;
{
    Object index_space;

    x_note_fn_call(42,50);
    index_space = g2int_make_index_space_1(name_of_icp_object_index_space,
	    EQ(name_of_icp_object_index_space,
	    Qg2int_item_with_handle_index_space) ? 
	    Qg2int_remove_icp_port_entries_from_icp_object_list : 
	    Qg2int_remove_icp_port_entries_from_icp_object);
    g2int_enlarge_index_space(index_space,FIX((SI_Long)20L));
    return VALUES_1(index_space);
}

Object G2int_use_new_message_group_for_send_icp_enlarge_index_space_p = UNBOUND;

static Object Qg2int_standard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qg2int_item_index_space;  /* item-index-space */

static Object Qg2int_output;       /* output */

static Object Qg2int_frame_serial_number;  /* frame-serial-number */

/* ASSIGN-CORRESPONDING-ICP-OBJECT-INDEX */
Object g2int_assign_corresponding_icp_object_index(icp_object,
	    name_of_corresponding_icp_object_index_space,
	    send_enlarge_message_p)
    Object icp_object, name_of_corresponding_icp_object_index_space;
    Object send_enlarge_message_p;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object new_index_limit_plus_one_qm, index_1;
    Object inner_new_index_limit_plus_one_qm, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);
    Object result;

    x_note_fn_call(42,51);
    port = G2int_current_icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_item_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (G2int_inhibit_corresponding_icp_object_making)
	    index_space_name = Qg2int_standard_icp_object_index_space;
	else if (Nil) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		index_space_name = Qg2int_item_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qg2int_item_index_space : 
			Qg2int_frame_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qg2int_item_index_space : 
		    Qg2int_standard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(G2int_current_icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(G2int_current_icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = 
		g2int_frame_serial_number_to_item_table(G2int_current_icp_port);
    else
	index_space = Qnil;
    new_index_limit_plus_one_qm = Nil;
    if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_1 = FIX((SI_Long)0L);
    else {
	result = g2int_assign_index_in_index_space(index_space);
	MVS_2(result,index_1,inner_new_index_limit_plus_one_qm);
	temp = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
	temp_1 = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
	new_index_limit_plus_one_qm = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		(SI_Long)8L ? Nil : inner_new_index_limit_plus_one_qm;
    }
    g2int_set_in_icp_port(G2int_current_icp_port,index_1,
	    name_of_corresponding_icp_object_index_space,icp_object);
    if (new_index_limit_plus_one_qm && send_enlarge_message_p && 
	    (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
	    (SI_Long)8L ? TRUEP(Nil) : TRUEP(T))) {
	if (G2int_use_new_message_group_for_send_icp_enlarge_index_space_p) {
	    current_icp_port = G2int_current_icp_port;
	    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
	      current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
		temp_1 = IFIX(ISVREF(G2int_current_icp_socket,
			(SI_Long)22L)) >= (SI_Long)17L ? 
			ISVREF(G2int_current_icp_socket,(SI_Long)53L) : Nil;
		if (temp_1);
		else
		    temp_1 = Nil;
		disable_resumability = temp_1;
		PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
			9);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  8);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			    7);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
			      6);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
				5);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  4);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				    3);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
				      2);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					1);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(G2int_writing_icp_message_group);
				  PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
					  0);
				    gensymed_symbol = Nil;
				    gensymed_symbol_1 = 0.0;
				    gensymed_symbol_1 = 0.0;
				    if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					    &&  
					    !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
						{
					g2int_send_icp_enlarge_corresponding_icp_object_index_space(index_space_name,
						new_index_limit_plus_one_qm);
					g2int_end_icp_message_group();
				    }
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
	}
	else
	    g2int_send_icp_enlarge_corresponding_icp_object_index_space(index_space_name,
		    new_index_limit_plus_one_qm);
    }
    if (send_enlarge_message_p)
	return VALUES_1(index_1);
    else
	return VALUES_2(index_1,new_index_limit_plus_one_qm);
}

/* GET-CORRESPONDING-ICP-OBJECT */
Object g2int_get_corresponding_icp_object(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    x_note_fn_call(42,52);
    return g2int_get_from_icp_port_if_any(G2int_current_icp_port,
	    corresponding_icp_object_index,
	    Qg2int_standard_icp_object_index_space);
}

/* STORE-CORRESPONDING-ICP-OBJECT */
Object g2int_store_corresponding_icp_object(corresponding_icp_object_index,
	    corresponding_icp_object)
    Object corresponding_icp_object_index, corresponding_icp_object;
{
    Object index_space, index_1, object, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(42,53);
    index_space = ISVREF(G2int_current_icp_port,(SI_Long)8L);
    index_1 = corresponding_icp_object_index;
    object = corresponding_icp_object;
    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	g2int_enlarge_index_space(index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
	    -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = object);
}

/* STORE-CORRESPONDING-ITEM */
Object g2int_store_corresponding_item(corresponding_icp_object_index,
	    corresponding_icp_object)
    Object corresponding_icp_object_index, corresponding_icp_object;
{
    x_note_fn_call(42,54);
    return g2int_set_in_icp_port(G2int_current_icp_port,
	    corresponding_icp_object_index,Qg2int_item_index_space,
	    corresponding_icp_object);
}

Object G2int_corresponding_icp_object_map_for_symbol_prop = UNBOUND;

static Object Qg2int_corresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

static Object Qg2int_establish_new_object_index_for_symbol;  /* establish-new-object-index-for-symbol */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-SYMBOL */
Object g2int_establish_new_object_index_for_symbol varargs_1(int, n)
{
    Object symbol, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, resumable_icp_state_1, icp_suspend_1;
    Object top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(42,55);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (G2int_disable_resumability) {
	result = g2int_assign_corresponding_icp_object_index(symbol,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	g2int_mutate_global_property(symbol,g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		Qg2int_corresponding_icp_object_map_for_symbol))),
		Qg2int_corresponding_icp_object_map_for_symbol);
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_establish_new_object_index_for_symbol,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_establish_new_object_index_for_symbol,top,Nil);
	}
	symbol = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : symbol;
	icp_port = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : send_enlarge_message_p;
	result = g2int_assign_corresponding_icp_object_index(symbol,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	g2int_mutate_global_property(symbol,g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		Qg2int_corresponding_icp_object_map_for_symbol))),
		Qg2int_corresponding_icp_object_map_for_symbol);
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qg2int_make_corresponding_icp_symbol;  /* make-corresponding-icp-symbol */

/* MAKE-CORRESPONDING-ICP-SYMBOL */
Object g2int_make_corresponding_icp_symbol(symbol)
    Object symbol;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, test, v1, v2, v3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,56);
    if (G2int_disable_resumability) {
	g2int_write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = g2int_assign_corresponding_icp_object_index(symbol,
		  Qg2int_standard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  temp = G2int_current_icp_port;
	  g2int_mutate_global_property(symbol,g2int_gensym_cons_1(temp,
		  g2int_gensym_cons_1(corresponding_icp_object_index,
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		  Qg2int_corresponding_icp_object_map_for_symbol))),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		      (SI_Long)22L) {
		  if (EQ(SYMBOL_PACKAGE(symbol),G2int_keyword_package_1))
		      g2int_send_icp_intern_keyword(corresponding_icp_object_index,
			      g2int_symbol_name_text_string(symbol));
		  else
		      g2int_send_icp_intern(corresponding_icp_object_index,
			      g2int_symbol_name_text_string(symbol));
	      }
	      else
		  g2int_send_icp_intern(corresponding_icp_object_index,
			  g2int_symbol_name_text_string(symbol));
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_make_corresponding_icp_symbol,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_make_corresponding_icp_symbol,top,Nil);
	}
	symbol = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : symbol;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = g2int_resumable_icp_pop();
	  else {
	      result = g2int_assign_corresponding_icp_object_index(symbol,
		      Qg2int_standard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      temp = G2int_current_icp_port;
	      g2int_mutate_global_property(symbol,g2int_gensym_cons_1(temp,
		      g2int_gensym_cons_1(corresponding_icp_object_index,
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		      Qg2int_corresponding_icp_object_map_for_symbol))),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  ||  !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      test = Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  test = g2int_resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qg2int_true) : 
		      IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		      >= (SI_Long)22L) {
		  test = Nil;
		  if (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) {
		      test = g2int_resumable_icp_pop();
		      temp_1 = TRUEP(test);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ? EQ(test,Qg2int_true) : 
			  EQ(SYMBOL_PACKAGE(symbol),G2int_keyword_package_1)) {
		      if (EQ(icp_suspend_1,
			      g2int_send_icp_intern_keyword(corresponding_icp_object_index,
			      g2int_symbol_name_text_string(symbol)))) {
			  g2int_resumable_icp_push(Qg2int_true);
			  g2int_resumable_icp_push(Qg2int_true);
			  g2int_resumable_icp_push(corresponding_icp_object_index);
			  g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
			  g2int_resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(G2int_icp_suspend);
			  POP_SPECIAL();
			  goto end_block;
		      }
		  }
		  else if (EQ(icp_suspend_1,
			  g2int_send_icp_intern(corresponding_icp_object_index,
			  g2int_symbol_name_text_string(symbol)))) {
		      g2int_resumable_icp_push(Qg2int_false);
		      g2int_resumable_icp_push(Qg2int_true);
		      g2int_resumable_icp_push(corresponding_icp_object_index);
		      g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		      g2int_resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(G2int_icp_suspend);
		      POP_SPECIAL();
		      goto end_block;
		  }
	      }
	      else if (EQ(icp_suspend_1,
		      g2int_send_icp_intern(corresponding_icp_object_index,
		      g2int_symbol_name_text_string(symbol)))) {
		  g2int_resumable_icp_push(Qg2int_false);
		  g2int_resumable_icp_push(corresponding_icp_object_index);
		  g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(symbol);
	    g2int_resumable_icp_push(Qg2int_make_corresponding_icp_symbol);
	    return VALUES_1(G2int_icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-SYMBOL */
Object g2int_get_icp_object_index_for_symbol(symbol,icp_port)
    Object symbol, icp_port;
{
    x_note_fn_call(42,57);
    return g2int_getfq_function_no_default(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qg2int_corresponding_icp_object_map_for_symbol),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-SYMBOL */
Object g2int_set_icp_object_index_for_symbol(symbol,
	    corresponding_icp_object_index,icp_port)
    Object symbol, corresponding_icp_object_index, icp_port;
{
    x_note_fn_call(42,58);
    return g2int_mutate_global_property(symbol,
	    g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qg2int_corresponding_icp_object_map_for_symbol))),
	    Qg2int_corresponding_icp_object_map_for_symbol);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-SYMBOL */
Object g2int_reclaim_icp_object_map_for_symbol(symbol)
    Object symbol;
{
    Object icp_object_map;

    x_note_fn_call(42,59);
    icp_object_map = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qg2int_corresponding_icp_object_map_for_symbol);
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(symbol,icp_object_map,
		Qg2int_standard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_symbol;  /* set-access-form-for-symbol */

/* RECLAIM-ICP-PORT-ENTRY-FOR-SYMBOL */
Object g2int_reclaim_icp_port_entry_for_symbol(symbol,icp_port)
    Object symbol, icp_port;
{
    x_note_fn_call(42,60);
    return g2int_reclaim_icp_port_entry(icp_port,symbol,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qg2int_corresponding_icp_object_map_for_symbol),
	    Qg2int_set_access_form_for_symbol);
}

/* SET-ACCESS-FORM-FOR-SYMBOL */
Object g2int_set_access_form_for_symbol(symbol,new_value)
    Object symbol, new_value;
{
    x_note_fn_call(42,61);
    return g2int_mutate_global_property(symbol,new_value,
	    Qg2int_corresponding_icp_object_map_for_symbol);
}

/* INFO-FOR-WRITE-ICP-SYMBOL-AS-VALUE-TYPE */
Object g2int_info_for_write_icp_symbol_as_value_type(symbol_as_value_type)
    Object symbol_as_value_type;
{
    Object temp, existing_index, index_1, index_limit_plus_one_qm;
    Object result;

    x_note_fn_call(42,62);
    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= (SI_Long)8L) {
	if ( !TRUEP(symbol_as_value_type))
	    return VALUES_1(FIX((SI_Long)0L));
	else {
	    temp = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol_as_value_type),
		    Qg2int_corresponding_icp_object_map_for_symbol);
	    existing_index = g2int_getfq_function_no_default(temp,
		    G2int_current_icp_port);
	    if (existing_index)
		result = VALUES_1(existing_index);
	    else
		result = g2int_establish_new_object_index_for_symbol(3,
			symbol_as_value_type,G2int_current_icp_port,Nil);
	    MVS_2(result,index_1,index_limit_plus_one_qm);
	    if (existing_index)
		temp = G2int_inhibit_corresponding_icp_object_making ? 
			FIX((SI_Long)73L) : FIX((SI_Long)70L);
	    else if (G2int_inhibit_corresponding_icp_object_making)
		temp = FIX((SI_Long)73L);
	    else if (EQ(SYMBOL_PACKAGE(symbol_as_value_type),
		    G2int_keyword_package_1) && 
		    (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		    >= (SI_Long)22L ? TRUEP(T) : TRUEP(Nil)))
		temp = FIX((SI_Long)75L);
	    else if ( !TRUEP(index_limit_plus_one_qm))
		temp = FIX((SI_Long)71L);
	    else
		temp = FIX((SI_Long)72L);
	    return VALUES_3(temp,index_1,index_limit_plus_one_qm);
	}
    }
    else
	return VALUES_1(FIX((SI_Long)3L));
}

static Object Qg2int_write_icp_symbol_as_value_type;  /* write-icp-symbol-as-value-type */

/* WRITE-ICP-SYMBOL-AS-VALUE-TYPE */
Object g2int_write_icp_symbol_as_value_type(symbol_as_value_type)
    Object symbol_as_value_type;
{
    Object writing_resumable_icp_messages_p, code, index_1;
    Object index_limit_plus_one_qm, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, temp_1, temp_2, value, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,63);
    if (G2int_disable_resumability) {
	g2int_write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = g2int_info_for_write_icp_symbol_as_value_type(symbol_as_value_type);
	  MVS_3(result,code,index_1,index_limit_plus_one_qm);
	  g2int_write_icp_byte(code);
	  if ( !(IFIX(code) == (SI_Long)0L)) {
	      if ( !(IFIX(code) == (SI_Long)3L)) {
		  if (IFIX(code) == (SI_Long)72L)
		      g2int_write_icp_fixnum(index_limit_plus_one_qm);
		  g2int_write_icp_corresponding_object_index(index_1);
	      }
	      temp = IFIX(code) == (SI_Long)3L || IFIX(code) == 
		      (SI_Long)71L || IFIX(code) == (SI_Long)75L || 
		      IFIX(code) == (SI_Long)72L ? 
		      g2int_write_icp_text_string(g2int_symbol_name_text_string(symbol_as_value_type)) 
		      : Nil;
	  }
	  else
	      temp = Nil;
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_symbol_as_value_type,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_symbol_as_value_type,top,Nil);
	}
	symbol_as_value_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : symbol_as_value_type;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      temp_2 = g2int_resumable_icp_pop();
	      temp = g2int_resumable_icp_pop();
	      result = VALUES_3(temp_1,temp_2,temp);
	  }
	  else
	      result = g2int_info_for_write_icp_symbol_as_value_type(symbol_as_value_type);
	  MVS_3(result,code,index_1,index_limit_plus_one_qm);
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_byte(code))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      result = VALUES_1(G2int_icp_suspend);
	      goto end_block_1;
	  }
	l2_1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  ||  !(IFIX(code) == (SI_Long)0L)) {
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  temp = g2int_resumable_icp_pop();
		  if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) ||  !(IFIX(code) == (SI_Long)3L)) {
		  if (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) {
		      temp = g2int_resumable_icp_pop();
		      if (! !(FIXNUMP(temp) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			      FIXNUM_LE(temp,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp)) {
			    case 1:
			      goto l1_3;
			      break;
			    case 2:
			      goto l2_3;
			      break;
			    default:
			      break;
			  }
		  }
		l1_3:
		  if ((resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) || IFIX(code) == (SI_Long)72L) {
		      if (EQ(icp_suspend_1,
			      g2int_write_icp_fixnum(index_limit_plus_one_qm))) 
				  {
			  g2int_resumable_icp_push(FIX((SI_Long)1L));
			  temp = G2int_icp_suspend;
			  goto end_block_2;
		      }
		  }
		l2_3:
		  if (EQ(icp_suspend_1,
			  g2int_write_icp_corresponding_object_index(index_1))) 
			      {
		      g2int_resumable_icp_push(FIX((SI_Long)2L));
		      temp = G2int_icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp)) {
		      g2int_resumable_icp_push(FIX((SI_Long)1L));
		      result = VALUES_1(G2int_icp_suspend);
		      goto end_block_3;
		  }
	      }
	    l2_2:
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) || IFIX(code) == (SI_Long)3L || 
		      IFIX(code) == (SI_Long)71L || IFIX(code) == 
		      (SI_Long)75L || IFIX(code) == (SI_Long)72L) {
		  value = 
			  g2int_write_icp_text_string(g2int_symbol_name_text_string(symbol_as_value_type));
		  if (EQ(icp_suspend_1,value)) {
		      g2int_resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(G2int_icp_suspend);
		      goto end_block_3;
		  }
		  result = VALUES_1(value);
	      }
	      else
		  result = VALUES_1(Nil);
	      goto end_block_3;
	    end_block_3:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	      result = VALUES_3(v1,v2,v3);
	  }
	  else
	      result = VALUES_1(Nil);
	  goto end_block_1;
	end_block_1:
	  MVS_3(result,v1,v2,v3);
	  if (EQ(icp_suspend_1,v1)) {
	      g2int_resumable_icp_push(index_limit_plus_one_qm);
	      g2int_resumable_icp_push(index_1);
	      g2int_resumable_icp_push(code);
	      g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_block;
	  }
	  result = VALUES_3(v1,v2,v3);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(symbol_as_value_type);
	    g2int_resumable_icp_push(Qg2int_write_icp_symbol_as_value_type);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_symbol_as_value_type;  /* read-icp-symbol-as-value-type */

/* READ-ICP-SYMBOL-AS-VALUE-TYPE */
Object g2int_read_icp_symbol_as_value_type()
{
    Object temp, index_space, index_1, new_index, string_1, symbol;
    Object resumable_icp_state_1, icp_suspend_1, top, key, value, arg1, arg2;
    Object v1, v2, v3, test;
    char temp_1;
    Object result;

    x_note_fn_call(42,64);
    if (G2int_disable_resumability) {
	temp = g2int_peek_icp_byte();
	if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		FIXNUM_LE(temp,FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 3:
		g2int_read_icp_byte();
		temp = g2int_read_icp_text_string();
		temp = g2int_intern_text_string(2,temp,G2int_ab_package_1);
		break;
	      case 0:
		g2int_read_icp_byte();
		temp = Nil;
		break;
	      case 73:
		g2int_read_icp_byte();
		index_space = G2int_current_temporary_icp_object_index_space;
		index_1 = g2int_read_icp_corresponding_object_index();
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		temp = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
		break;
	      case 70:
		g2int_read_icp_byte();
		index_space = G2int_current_standard_icp_object_index_space;
		index_1 = g2int_read_icp_corresponding_object_index();
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		temp = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
		break;
	      case 71:
	      case 72:
		if ((SI_Long)72L == IFIX(g2int_read_icp_byte()))
		    g2int_handler_for_enlarge_corresponding_icp_object_index_space(Qg2int_standard_icp_object_index_space,
			    g2int_read_icp_fixnum());
		new_index = g2int_read_icp_corresponding_object_index();
		string_1 = g2int_read_icp_text_string();
		symbol = g2int_intern_text_string_for_icp(string_1,
			G2int_ab_package_1);
		g2int_store_corresponding_icp_object(new_index,symbol);
		g2int_reclaim_text_string(string_1);
		temp = symbol;
		break;
	      case 75:
		g2int_read_icp_byte();
		new_index = g2int_read_icp_corresponding_object_index();
		string_1 = g2int_read_icp_text_string();
		symbol = g2int_intern_text_string_for_icp(string_1,
			G2int_keyword_package_1);
		g2int_store_corresponding_icp_object(new_index,symbol);
		g2int_reclaim_text_string(string_1);
		temp = symbol;
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_symbol_as_value_type,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_symbol_as_value_type,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    key = g2int_resumable_icp_pop();
	else {
	    value = g2int_peek_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_symbol_as_value_type);
		return VALUES_1(G2int_icp_suspend);
	    }
	    key = value;
	}
	if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		FIXNUM_LE(key,FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(key)) {
	      case 3:
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
			    break;
			  default:
			    break;
			}
		}
	      l1:
		if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l2:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		    arg1 = value;
		}
		arg2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : G2int_ab_package_1;
		result = g2int_intern_text_string(2,arg1,arg2);
		goto end_block;
	      end_block:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_symbol_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
		break;
	      case 0:
		if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_symbol_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = Nil;
		break;
	      case 73:
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_1;
		}
	      l2_1:
		index_space = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			G2int_current_temporary_icp_object_index_space;
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    index_1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(index_space);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_1;
		    }
		    index_1 = value;
		}
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		result = VALUES_1(ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L));
		goto end_block_1;
	      end_block_1:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_symbol_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
		break;
	      case 70:
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_2;
			    break;
			  case 2:
			    goto l2_2;
			    break;
			  default:
			    break;
			}
		}
	      l1_2:
		if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_2;
		}
	      l2_2:
		index_space = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			G2int_current_standard_icp_object_index_space;
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    index_1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(index_space);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_2;
		    }
		    index_1 = value;
		}
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		result = VALUES_1(ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L));
		goto end_block_2;
	      end_block_2:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_symbol_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
		break;
	      case 71:
	      case 72:
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_3;
			    break;
			  case 2:
			    goto l2_3;
			    break;
			  default:
			    break;
			}
		}
	      l1_3:
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    temp_1 = EQ(test,Qg2int_true);
		else {
		    arg1 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : FIX((SI_Long)72L);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg2 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Nil);
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_3;
			}
			arg2 = value;
		    }
		    temp_1 = FIXNUM_EQ(arg1,arg2);
		}
		if (temp_1) {
		    arg1 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : 
			    Qg2int_standard_icp_object_index_space;
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg2 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_fixnum();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_3;
			}
			arg2 = value;
		    }
		    g2int_handler_for_enlarge_corresponding_icp_object_index_space(arg1,
			    arg2);
		}
	      l2_3:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    new_index = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_3;
		    }
		    new_index = value;
		}
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    string_1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(new_index);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_3;
		    }
		    string_1 = value;
		}
		symbol = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			g2int_intern_text_string_for_icp(string_1,
			G2int_ab_package_1);
		g2int_store_corresponding_icp_object(new_index,symbol);
		g2int_reclaim_text_string(string_1);
		result = VALUES_1(symbol);
		goto end_block_3;
	      end_block_3:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_symbol_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
		break;
	      case 75:
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_4;
			    break;
			  case 2:
			    goto l2_4;
			    break;
			  default:
			    break;
			}
		}
	      l1_4:
		if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_4;
		}
	      l2_4:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    new_index = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_4;
		    }
		    new_index = value;
		}
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    string_1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(new_index);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_4;
		    }
		    string_1 = value;
		}
		symbol = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			g2int_intern_text_string_for_icp(string_1,
			G2int_keyword_package_1);
		g2int_store_corresponding_icp_object(new_index,symbol);
		g2int_reclaim_text_string(string_1);
		result = VALUES_1(symbol);
		goto end_block_4;
	      end_block_4:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_symbol_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    return VALUES_1(temp);
}

/* SET-UP-ICP-OBJECT-INDEX-SPACE */
Object g2int_set_up_icp_object_index_space(name_of_icp_index_space)
    Object name_of_icp_index_space;
{
    Object new_icp_object_index_space, index_for_name_of_index_space;
    Object svref_arg_1, temp;
    SI_Long svref_arg_2;

    x_note_fn_call(42,65);
    new_icp_object_index_space = 
	    g2int_make_icp_object_index_space(name_of_icp_index_space);
    index_for_name_of_index_space = 
	    g2int_assign_index_in_index_space(new_icp_object_index_space);
    if (FIXNUM_GE(index_for_name_of_index_space,
	    ISVREF(new_icp_object_index_space,(SI_Long)4L)))
	g2int_enlarge_index_space(new_icp_object_index_space,
		index_for_name_of_index_space);
    svref_arg_1 = ISVREF(ISVREF(new_icp_object_index_space,(SI_Long)2L),
	    IFIX(index_for_name_of_index_space) >>  -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_for_name_of_index_space) & (SI_Long)1023L;
    ISVREF(svref_arg_1,svref_arg_2) = name_of_icp_index_space;
    if (EQ(Qg2int_standard_icp_object_index_space,name_of_icp_index_space)) {
	temp = G2int_current_icp_port;
	g2int_mutate_global_property(name_of_icp_index_space,
		g2int_gensym_cons_1(temp,
		g2int_gensym_cons_1(index_for_name_of_index_space,
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_icp_index_space),
		Qg2int_corresponding_icp_object_map_for_symbol))),
		Qg2int_corresponding_icp_object_map_for_symbol);
    }
    return VALUES_1(new_icp_object_index_space);
}

static Object Qg2int_send_icp_intern;  /* send-icp-intern */

/* SEND-ICP-INTERN */
Object g2int_send_icp_intern(corresponding_icp_object_index,text_string)
    Object corresponding_icp_object_index, text_string;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,66);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_intern;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)81L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_text_string(text_string);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_intern,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_intern,top,Nil);
		goto end_send_icp_intern;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	text_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : text_string;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_intern;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)81L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_text_string(text_string))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(text_string);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_intern);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_intern;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_intern:
    return result;
}

/* HANDLE-ICP-INTERN--BODY */
Object g2int_handle_icp_intern__body(corresponding_icp_object_index,
	    text_string)
    Object corresponding_icp_object_index, text_string;
{
    x_note_fn_call(42,67);
    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
	    g2int_intern_text_string_for_icp(text_string,G2int_ab_package_1));
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_intern;  /* handle-icp-intern */

/* HANDLE-ICP-INTERN */
Object g2int_handle_icp_intern()
{
    Object corresponding_icp_object_index, text_string;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(42,68);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	text_string = g2int_read_icp_text_string();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_intern__body(corresponding_icp_object_index,
		  text_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(text_string);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_intern,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_intern,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_intern);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    text_string = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_intern);
		return VALUES_1(G2int_icp_suspend);
	    }
	    text_string = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_intern__body(corresponding_icp_object_index,
		  text_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(text_string);
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_intern_keyword;  /* send-icp-intern-keyword */

/* SEND-ICP-INTERN-KEYWORD */
Object g2int_send_icp_intern_keyword(corresponding_icp_object_index,
	    text_string)
    Object corresponding_icp_object_index, text_string;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,69);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_intern_keyword;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)86L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_text_string(text_string);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_intern_keyword,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_intern_keyword,top,Nil);
		goto end_send_icp_intern_keyword;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	text_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : text_string;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_intern_keyword;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)86L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_text_string(text_string))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(text_string);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_intern_keyword);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_intern_keyword;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_intern_keyword:
    return result;
}

/* HANDLE-ICP-INTERN-KEYWORD--BODY */
Object g2int_handle_icp_intern_keyword__body(corresponding_icp_object_index,
	    text_string)
    Object corresponding_icp_object_index, text_string;
{
    x_note_fn_call(42,70);
    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
	    g2int_intern_text_string_for_icp(text_string,
	    G2int_keyword_package_1));
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_intern_keyword;  /* handle-icp-intern-keyword */

/* HANDLE-ICP-INTERN-KEYWORD */
Object g2int_handle_icp_intern_keyword()
{
    Object corresponding_icp_object_index, text_string;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(42,71);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	text_string = g2int_read_icp_text_string();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_intern_keyword__body(corresponding_icp_object_index,
		  text_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(text_string);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_intern_keyword,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_intern_keyword,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_intern_keyword);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    text_string = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_intern_keyword);
		return VALUES_1(G2int_icp_suspend);
	    }
	    text_string = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_intern_keyword__body(corresponding_icp_object_index,
		  text_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(text_string);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* INTERN-TEXT-STRING-FOR-ICP */
Object g2int_intern_text_string_for_icp(name,package)
    Object name, package;
{
    Object temp;

    x_note_fn_call(42,72);
    temp = g2int_gsi_intern(g2int_copy_text_string(name));
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_add_to_list_of_symbols;  /* send-icp-add-to-list-of-symbols */

/* SEND-ICP-ADD-TO-LIST-OF-SYMBOLS */
Object g2int_send_icp_add_to_list_of_symbols(corresponding_icp_object_index,
	    symbol,first_element_qm)
    Object corresponding_icp_object_index, symbol, first_element_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,73);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_add_to_list_of_symbols;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(symbol);
	  symbol = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)82L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_corresponding_object_index(symbol);
	  g2int_write_icp_boolean(first_element_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_add_to_list_of_symbols,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_add_to_list_of_symbols,top,Nil);
		goto end_send_icp_add_to_list_of_symbols;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	symbol = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : symbol;
	first_element_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : first_element_qm;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_add_to_list_of_symbols;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      symbol = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(symbol);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      symbol = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)82L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    case 3:
		      goto l3_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(symbol))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_boolean(first_element_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(first_element_qm);
	      g2int_resumable_icp_push(symbol);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_add_to_list_of_symbols);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_add_to_list_of_symbols;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_add_to_list_of_symbols:
    return result;
}

/* HANDLE-ICP-ADD-TO-LIST-OF-SYMBOLS--BODY */
Object g2int_handle_icp_add_to_list_of_symbols__body(corresponding_icp_object_index,
	    symbol,first_element_qm)
    Object corresponding_icp_object_index, symbol, first_element_qm;
{
    Object temp;

    x_note_fn_call(42,74);
    if (first_element_qm)
	temp = g2int_gensym_cons_1(symbol,Nil);
    else {
	temp = 
		g2int_get_corresponding_icp_object(corresponding_icp_object_index);
	temp = nconc2(temp,g2int_gensym_cons_1(symbol,Nil));
    }
    g2int_store_corresponding_icp_object(corresponding_icp_object_index,temp);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_add_to_list_of_symbols;  /* handle-icp-add-to-list-of-symbols */

/* HANDLE-ICP-ADD-TO-LIST-OF-SYMBOLS */
Object g2int_handle_icp_add_to_list_of_symbols()
{
    Object corresponding_icp_object_index, index_1, index_space, symbol;
    Object first_element_qm, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(42,75);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    symbol = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    symbol = Nil;
	first_element_qm = g2int_read_icp_boolean();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_add_to_list_of_symbols__body(corresponding_icp_object_index,
		  symbol,first_element_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_add_to_list_of_symbols,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_add_to_list_of_symbols,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_add_to_list_of_symbols);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    symbol = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_add_to_list_of_symbols);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		symbol = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		symbol = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    first_element_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_boolean();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(symbol);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_add_to_list_of_symbols);
		return VALUES_1(G2int_icp_suspend);
	    }
	    first_element_qm = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_add_to_list_of_symbols__body(corresponding_icp_object_index,
		  symbol,first_element_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_object_map_plist_for_icp_tree = UNBOUND;

/* MUTATE-ICP-PLIST */
Object g2int_mutate_icp_plist(icp_plist,indicator,value)
    Object icp_plist, indicator, value;
{
    Object new_plist, l, old_conses, cdr_new_value;

    x_note_fn_call(42,76);
    if ( !TRUEP(value)) {
	if (EQ(CAR(icp_plist),indicator)) {
	    new_plist = CDDR(icp_plist);
	    M_CDDR(icp_plist) = Nil;
	    g2int_reclaim_gensym_list_1(icp_plist);
	    return VALUES_1(new_plist);
	}
	else {
	    l = CDR(icp_plist);
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(CADR(l),indicator)) {
		old_conses = CDR(l);
		cdr_new_value = CDDDR(l);
		M_CDR(l) = cdr_new_value;
		M_CDDR(old_conses) = Nil;
		g2int_reclaim_gensym_list_1(old_conses);
		return VALUES_1(icp_plist);
	    }
	    l = CDDR(l);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(icp_plist);
	    return VALUES_1(Qnil);
	}
    }
    else if ( !TRUEP(icp_plist))
	return g2int_gensym_list_2(indicator,value);
    else {
	l = icp_plist;
      next_loop_1:
	if ( !TRUEP(l))
	    goto end_loop_1;
	if (EQ(CAR(l),indicator)) {
	    M_CADR(l) = value;
	    return VALUES_1(icp_plist);
	}
	l = CDDR(l);
	goto next_loop_1;
      end_loop_1:
	return g2int_gensym_cons_1(indicator,g2int_gensym_cons_1(value,
		icp_plist));
	return VALUES_1(Qnil);
    }
}

Object G2int_the_type_description_of_symbol_tree = UNBOUND;

Object G2int_chain_of_available_symbol_trees = UNBOUND;

Object G2int_symbol_tree_count = UNBOUND;

/* RECLAIM-SYMBOL-TREE-1 */
Object g2int_reclaim_symbol_tree_1(symbol_tree)
    Object symbol_tree;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(42,77);
    inline_note_reclaim_cons(symbol_tree,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = symbol_tree;
    g2int_reclaim_gensym_list_1(ISVREF(symbol_tree,(SI_Long)1L));
    SVREF(symbol_tree,FIX((SI_Long)1L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_symbol_trees;
    SVREF(symbol_tree,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_symbol_trees = symbol_tree;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SYMBOL-TREE */
Object g2int_reclaim_structure_for_symbol_tree(symbol_tree)
    Object symbol_tree;
{
    x_note_fn_call(42,78);
    return g2int_reclaim_symbol_tree_1(symbol_tree);
}

static Object Qg2_defstruct_structure_name_symbol_tree_g2_struct;  /* g2-defstruct-structure-name::symbol-tree-g2-struct */

/* MAKE-PERMANENT-SYMBOL-TREE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_symbol_tree_structure_internal()
{
    Object def_structure_symbol_tree_variable, symbol_tree_count_new_value;
    Object defstruct_g2_symbol_tree_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(42,79);
    def_structure_symbol_tree_variable = Nil;
    symbol_tree_count_new_value = FIXNUM_ADD1(G2int_symbol_tree_count);
    G2int_symbol_tree_count = symbol_tree_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_symbol_tree_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_symbol_tree_variable = the_array;
	SVREF(defstruct_g2_symbol_tree_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_symbol_tree_g2_struct;
	def_structure_symbol_tree_variable = defstruct_g2_symbol_tree_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_symbol_tree_variable);
}

/* MAKE-SYMBOL-TREE-1 */
Object g2int_make_symbol_tree_1()
{
    Object def_structure_symbol_tree_variable;

    x_note_fn_call(42,80);
    def_structure_symbol_tree_variable = G2int_chain_of_available_symbol_trees;
    if (def_structure_symbol_tree_variable) {
	G2int_chain_of_available_symbol_trees = 
		ISVREF(def_structure_symbol_tree_variable,(SI_Long)0L);
	SVREF(def_structure_symbol_tree_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_symbol_tree_g2_struct;
    }
    else
	def_structure_symbol_tree_variable = 
		g2int_make_permanent_symbol_tree_structure_internal();
    inline_note_allocate_cons(def_structure_symbol_tree_variable,Nil);
    SVREF(def_structure_symbol_tree_variable,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_symbol_tree_variable);
}

static Object Qg2int_write_icp_icp_tree;  /* write-icp-icp-tree */

/* WRITE-ICP-ICP-TREE */
Object g2int_write_icp_icp_tree(icp_tree)
    Object icp_tree;
{
    Object temp, tail, resumable_icp_state_1, icp_suspend_1, top, test, value;
    Object v1, v2, v3;
    char temp_1;
    Object result;

    x_note_fn_call(42,81);
    if (G2int_disable_resumability) {
	if (FIXNUMP(icp_tree)) {
	    g2int_write_icp_byte(FIX((SI_Long)1L));
	    temp = g2int_write_icp_integer(icp_tree);
	}
	else if ( !TRUEP(icp_tree))
	    temp = g2int_write_icp_byte(FIX((SI_Long)0L));
	else if (SYMBOLP(icp_tree))
	    temp = g2int_write_icp_symbol_as_value_type(icp_tree);
	else if (g2int_text_string_p(icp_tree)) {
	    g2int_write_icp_byte(FIX((SI_Long)4L));
	    temp = g2int_write_icp_text_string(icp_tree);
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(icp_tree) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_tree)) == (SI_Long)1L) {
	    g2int_write_icp_byte(FIX((SI_Long)6L));
	    temp = g2int_write_icp_managed_double_float(icp_tree);
	}
	else if (g2int_interned_list_p_function(icp_tree)) {
	    g2int_write_icp_byte(FIX((SI_Long)90L));
	    temp = g2int_write_icp_interned_list_as_value_type(icp_tree);
	}
	else if (ATOM(icp_tree))
	    temp = g2int_write_icp_byte(FIX((SI_Long)0L));
	else {
	    temp = M_CDR(icp_tree);
	    if (CONSP(temp)) {
		g2int_write_icp_byte(FIX((SI_Long)81L));
		tail = icp_tree;
	      next_loop:
		if ( !TRUEP(tail))
		    goto end_loop;
		if (ATOM(tail))
		    goto end_loop;
		g2int_write_icp_icp_tree(M_CAR(tail));
		tail = M_CDR(tail);
		goto next_loop;
	      end_loop:
		if (tail) {
		    g2int_write_icp_byte(FIX((SI_Long)83L));
		    g2int_write_icp_icp_tree(tail);
		}
		else
		    g2int_write_icp_byte(FIX((SI_Long)82L));
		temp = Qnil;
	    }
	    else {
		g2int_write_icp_byte(FIX((SI_Long)80L));
		g2int_write_icp_icp_tree(M_CAR(icp_tree));
		temp = g2int_write_icp_icp_tree(M_CDR(icp_tree));
	    }
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_icp_tree,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_icp_tree,top,Nil);
	}
	icp_tree = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : icp_tree;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : FIXNUMP(icp_tree)) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1;
			break;
		      case 2:
			goto l2;
			break;
		      default:
			break;
		    }
	    }
	  l1:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)1L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l2:
	    value = g2int_write_icp_integer(icp_tree);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    result = VALUES_1(value);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(icp_tree);
		g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) :  !TRUEP(icp_tree)) {
		value = g2int_write_icp_byte(FIX((SI_Long)0L));
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(icp_tree);
		    g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : SYMBOLP(icp_tree)) {
		    value = g2int_write_icp_symbol_as_value_type(icp_tree);
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(icp_tree);
			g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(g2int_text_string_p(icp_tree))) {
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    temp = g2int_resumable_icp_pop();
			    if (! !(FIXNUMP(temp) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp)) {
				  case 1:
				    goto l1_1;
				    break;
				  case 2:
				    goto l2_1;
				    break;
				  default:
				    break;
				}
			}
		      l1_1:
			if (EQ(icp_suspend_1,
				g2int_write_icp_byte(FIX((SI_Long)4L)))) {
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_1;
			}
		      l2_1:
			value = g2int_write_icp_text_string(icp_tree);
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block_1;
			}
			result = VALUES_1(value);
			goto end_block_1;
		      end_block_1:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(icp_tree);
			    g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = v1;
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    test = g2int_resumable_icp_pop();
			    temp_1 = TRUEP(test);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? EQ(test,Qg2int_true) : 
				INLINE_DOUBLE_FLOAT_VECTOR_P(icp_tree) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_tree)) 
				== (SI_Long)1L) {
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				temp = g2int_resumable_icp_pop();
				if (! !(FIXNUMP(temp) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp) && FIXNUM_LE(temp,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp)) {
				      case 1:
					goto l1_2;
					break;
				      case 2:
					goto l2_2;
					break;
				      default:
					break;
				    }
			    }
			  l1_2:
			    if (EQ(icp_suspend_1,
				    g2int_write_icp_byte(FIX((SI_Long)6L)))) {
				g2int_resumable_icp_push(FIX((SI_Long)1L));
				result = VALUES_1(G2int_icp_suspend);
				goto end_block_2;
			    }
			  l2_2:
			    value = 
				    g2int_write_icp_managed_double_float(icp_tree);
			    if (EQ(icp_suspend_1,value)) {
				g2int_resumable_icp_push(FIX((SI_Long)2L));
				result = VALUES_1(G2int_icp_suspend);
				goto end_block_2;
			    }
			    result = VALUES_1(value);
			    goto end_block_2;
			  end_block_2:
			    MVS_3(result,v1,v2,v3);
			    if (EQ(icp_suspend_1,v1)) {
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(icp_tree);
				g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
				return VALUES_1(G2int_icp_suspend);
			    }
			    temp = v1;
			}
			else {
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				test = g2int_resumable_icp_pop();
				temp_1 = TRUEP(test);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1 ? EQ(test,Qg2int_true) : 
				    TRUEP(g2int_interned_list_p_function(icp_tree))) 
					{
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) {
				    temp = g2int_resumable_icp_pop();
				    if (! !(FIXNUMP(temp) && 
					    FIXNUM_LE(FIX((SI_Long)-128L),
					    temp) && FIXNUM_LE(temp,
					    FIX((SI_Long)127L))))
					switch (INTEGER_TO_CHAR(temp)) {
					  case 1:
					    goto l1_3;
					    break;
					  case 2:
					    goto l2_3;
					    break;
					  default:
					    break;
					}
				}
			      l1_3:
				if (EQ(icp_suspend_1,
					g2int_write_icp_byte(FIX((SI_Long)90L)))) 
					    {
				    g2int_resumable_icp_push(FIX((SI_Long)1L));
				    result = VALUES_1(G2int_icp_suspend);
				    goto end_block_3;
				}
			      l2_3:
				value = 
					g2int_write_icp_interned_list_as_value_type(icp_tree);
				if (EQ(icp_suspend_1,value)) {
				    g2int_resumable_icp_push(FIX((SI_Long)2L));
				    result = VALUES_1(G2int_icp_suspend);
				    goto end_block_3;
				}
				result = VALUES_1(value);
				goto end_block_3;
			      end_block_3:
				MVS_3(result,v1,v2,v3);
				if (EQ(icp_suspend_1,v1)) {
				    g2int_resumable_icp_push(Qg2int_true);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(icp_tree);
				    g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
				    return VALUES_1(G2int_icp_suspend);
				}
				temp = v1;
			    }
			    else {
				test = Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) {
				    test = g2int_resumable_icp_pop();
				    temp_1 = TRUEP(test);
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1 ? EQ(test,Qg2int_true) : 
					ATOM(icp_tree)) {
				    value = 
					    g2int_write_icp_byte(FIX((SI_Long)0L));
				    if (EQ(icp_suspend_1,value)) {
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(icp_tree);
					g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
					return VALUES_1(G2int_icp_suspend);
				    }
				    temp = value;
				}
				else {
				    test = Nil;
				    if (resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) {
					test = g2int_resumable_icp_pop();
					temp_1 = TRUEP(test);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1)
					temp_1 = EQ(test,Qg2int_true);
				    else {
					temp = M_CDR(icp_tree);
					temp_1 = CONSP(temp);
				    }
				    if (temp_1) {
					if (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) {
					    temp = g2int_resumable_icp_pop();
					    if (! !(FIXNUMP(temp) && 
						    FIXNUM_LE(FIX((SI_Long)-128L),
						    temp) && 
						    FIXNUM_LE(temp,
						    FIX((SI_Long)127L))))
						switch (INTEGER_TO_CHAR(temp)) 
							    {
						  case 1:
						    goto l1_4;
						    break;
						  case 2:
						    goto l2_4;
						    break;
						  default:
						    break;
						}
					}
				      l1_4:
					if (EQ(icp_suspend_1,
						g2int_write_icp_byte(FIX((SI_Long)81L)))) 
						    {
					    g2int_resumable_icp_push(FIX((SI_Long)1L));
					    result = VALUES_1(G2int_icp_suspend);
					    goto end_block_4;
					}
				      l2_4:
					tail = (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) &&  
						!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
						? 
						g2int_resumable_icp_pop() :
						 icp_tree;
					if (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) {
					    temp = g2int_resumable_icp_pop();
					    if (! !(FIXNUMP(temp) && 
						    FIXNUM_LE(FIX((SI_Long)-128L),
						    temp) && 
						    FIXNUM_LE(temp,
						    FIX((SI_Long)127L))))
						switch (INTEGER_TO_CHAR(temp)) 
							    {
						  case 1:
						    goto l1_5;
						    break;
						  case 2:
						    goto l2_5;
						    break;
						  default:
						    break;
						}
					}
				      next_loop_1:
					if ( !TRUEP(tail))
					    goto end_loop_1;
					if (ATOM(tail))
					    goto end_loop_1;
				      l1_5:
					if (EQ(icp_suspend_1,
						g2int_write_icp_icp_tree(M_CAR(tail)))) 
						    {
					    g2int_resumable_icp_push(FIX((SI_Long)1L));
					    g2int_resumable_icp_push(tail);
					    g2int_resumable_icp_push(FIX((SI_Long)2L));
					    result = VALUES_1(G2int_icp_suspend);
					    goto end_block_4;
					}
					tail = M_CDR(tail);
					goto next_loop_1;
				      end_loop_1:
				      l2_5:
					test = Nil;
					if (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) {
					    test = g2int_resumable_icp_pop();
					    temp_1 = TRUEP(test);
					}
					else
					    temp_1 = TRUEP(Nil);
					if (temp_1 ? EQ(test,Qg2int_true) :
						 TRUEP(tail)) {
					    if (resumable_icp_state_1 ? 
						    TRUEP(G2int_starresumable_icp_statestar) 
						    : TRUEP(Nil)) {
						temp = 
							g2int_resumable_icp_pop();
						if (! !(FIXNUMP(temp) && 
							FIXNUM_LE(FIX((SI_Long)-128L),
							temp) && 
							FIXNUM_LE(temp,
							FIX((SI_Long)127L))))
						    switch (INTEGER_TO_CHAR(temp)) 
								{
						      case 1:
							goto l1_6;
							break;
						      case 2:
							goto l2_6;
							break;
						      default:
							break;
						    }
					    }
					  l1_6:
					    if (EQ(icp_suspend_1,
						    g2int_write_icp_byte(FIX((SI_Long)83L)))) 
							{
						g2int_resumable_icp_push(FIX((SI_Long)1L));
						temp = G2int_icp_suspend;
						goto end_block_5;
					    }
					  l2_6:
					    if (EQ(icp_suspend_1,
						    g2int_write_icp_icp_tree(tail))) 
							{
						g2int_resumable_icp_push(FIX((SI_Long)2L));
						temp = G2int_icp_suspend;
						goto end_block_5;
					    }
					    else
						temp = Nil;
					    goto end_block_5;
					  end_block_5:
					    if (EQ(icp_suspend_1,temp)) {
						g2int_resumable_icp_push(Qg2int_true);
						g2int_resumable_icp_push(FIX((SI_Long)2L));
						g2int_resumable_icp_push(tail);
						g2int_resumable_icp_push(FIX((SI_Long)2L));
						result = VALUES_1(G2int_icp_suspend);
						goto end_block_4;
					    }
					}
					else if ((resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) || T) {
					    if (EQ(icp_suspend_1,
						    g2int_write_icp_byte(FIX((SI_Long)82L)))) 
							{
						g2int_resumable_icp_push(Qg2int_false);
						g2int_resumable_icp_push(FIX((SI_Long)2L));
						g2int_resumable_icp_push(tail);
						g2int_resumable_icp_push(FIX((SI_Long)2L));
						result = VALUES_1(G2int_icp_suspend);
						goto end_block_4;
					    }
					}
					result = VALUES_1(Qnil);
					goto end_block_4;
				      end_block_4:
					MVS_3(result,v1,v2,v3);
					if (EQ(icp_suspend_1,v1)) {
					    g2int_resumable_icp_push(Qg2int_true);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(icp_tree);
					    g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
					    return VALUES_1(G2int_icp_suspend);
					}
					temp = v1;
				    }
				    else if ((resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) || T) {
					if (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) {
					    temp = g2int_resumable_icp_pop();
					    if (! !(FIXNUMP(temp) && 
						    FIXNUM_LE(FIX((SI_Long)-128L),
						    temp) && 
						    FIXNUM_LE(temp,
						    FIX((SI_Long)127L))))
						switch (INTEGER_TO_CHAR(temp)) 
							    {
						  case 1:
						    goto l1_7;
						    break;
						  case 2:
						    goto l2_7;
						    break;
						  case 3:
						    goto l3;
						    break;
						  default:
						    break;
						}
					}
				      l1_7:
					if (EQ(icp_suspend_1,
						g2int_write_icp_byte(FIX((SI_Long)80L)))) 
						    {
					    g2int_resumable_icp_push(FIX((SI_Long)1L));
					    result = VALUES_1(G2int_icp_suspend);
					    goto end_block_6;
					}
				      l2_7:
					if (EQ(icp_suspend_1,
						g2int_write_icp_icp_tree(M_CAR(icp_tree)))) 
						    {
					    g2int_resumable_icp_push(FIX((SI_Long)2L));
					    result = VALUES_1(G2int_icp_suspend);
					    goto end_block_6;
					}
				      l3:
					value = 
						g2int_write_icp_icp_tree(M_CDR(icp_tree));
					if (EQ(icp_suspend_1,value)) {
					    g2int_resumable_icp_push(FIX((SI_Long)3L));
					    result = VALUES_1(G2int_icp_suspend);
					    goto end_block_6;
					}
					result = VALUES_1(value);
					goto end_block_6;
				      end_block_6:
					MVS_3(result,v1,v2,v3);
					if (EQ(icp_suspend_1,v1)) {
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(icp_tree);
					    g2int_resumable_icp_push(Qg2int_write_icp_icp_tree);
					    return VALUES_1(G2int_icp_suspend);
					}
					temp = v1;
				    }
				    else
					temp = Qnil;
				}
			    }
			}
		    }
		}
	    }
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_9;   /* "Unknown type tag ~a in READ-ICP-ICP-TREE" */

static Object Qg2int_read_icp_icp_tree;  /* read-icp-icp-tree */

/* READ-ICP-ICP-TREE */
Object g2int_read_icp_icp_tree()
{
    Object code, temp, list_1, next, last_1, cdr_new_value;
    Object resumable_icp_state_1, icp_suspend_1, top, value, test, key, arg1;
    Object arg2;
    char temp_1;

    x_note_fn_call(42,82);
    if (G2int_disable_resumability) {
	code = g2int_peek_icp_byte();
	if (IFIX(code) == (SI_Long)70L || IFIX(code) == (SI_Long)73L || 
		IFIX(code) == (SI_Long)71L || IFIX(code) == (SI_Long)75L 
		|| IFIX(code) == (SI_Long)72L)
	    temp = g2int_read_icp_symbol_as_value_type();
	else {
	    temp = g2int_read_icp_byte();
	    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		    FIXNUM_LE(temp,FIX((SI_Long)127L))))
		temp = g2int_icp_error_internal(Qerror,string_constant_9,
			code,Nil,Nil);
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    temp = g2int_read_icp_integer();
		    break;
		  case 51:
		    temp = g2int_read_icp_managed_long();
		    break;
		  case 0:
		    temp = Nil;
		    break;
		  case 4:
		    temp = g2int_read_icp_text_string();
		    break;
		  case 6:
		    temp = g2int_read_icp_managed_double_float();
		    break;
		  case 90:
		    temp = g2int_read_icp_interned_list_as_value_type();
		    break;
		  case 81:
		    list_1 = g2int_gensym_cons_1(g2int_read_icp_icp_tree(),
			    Nil);
		    next = Nil;
		    last_1 = list_1;
		    code = Nil;
		  next_loop:
		    code = g2int_peek_icp_byte();
		    if (IFIX(code) == (SI_Long)83L || IFIX(code) == 
			    (SI_Long)82L)
			goto end_loop;
		    next = g2int_gensym_cons_1(g2int_read_icp_icp_tree(),Nil);
		    M_CDR(last_1) = next;
		    last_1 = next;
		    goto next_loop;
		  end_loop:
		    if (IFIX(g2int_read_icp_byte()) == (SI_Long)83L) {
			cdr_new_value = g2int_read_icp_icp_tree();
			M_CDR(last_1) = cdr_new_value;
		    }
		    temp = list_1;
		    break;
		  case 80:
		    temp = g2int_read_icp_icp_tree();
		    temp = g2int_gensym_cons_1(temp,g2int_read_icp_icp_tree());
		    break;
		  default:
		    temp = g2int_icp_error_internal(Qerror,
			    string_constant_9,code,Nil,Nil);
		    break;
		}
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_icp_tree,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_icp_tree,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    code = g2int_resumable_icp_pop();
	else {
	    value = g2int_peek_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
		return VALUES_1(G2int_icp_suspend);
	    }
	    code = value;
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : IFIX(code) == (SI_Long)70L || 
		IFIX(code) == (SI_Long)73L || IFIX(code) == (SI_Long)71L 
		|| IFIX(code) == (SI_Long)75L || IFIX(code) == (SI_Long)72L) {
	    value = g2int_read_icp_symbol_as_value_type();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(code);
		g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		key = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(code);
		    g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
		    return VALUES_1(G2int_icp_suspend);
		}
		key = value;
	    }
	    if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		    FIXNUM_LE(key,FIX((SI_Long)127L)))) {
		value = g2int_icp_error_internal(Qerror,string_constant_9,
			code,Nil,Nil);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(code);
		    g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else
		switch (INTEGER_TO_CHAR(key)) {
		  case 1:
		    value = g2int_read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		    break;
		  case 51:
		    value = g2int_read_icp_managed_long();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		    break;
		  case 0:
		    temp = Nil;
		    break;
		  case 4:
		    value = g2int_read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		    break;
		  case 6:
		    value = g2int_read_icp_managed_double_float();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		    break;
		  case 90:
		    value = g2int_read_icp_interned_list_as_value_type();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		    break;
		  case 81:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			list_1 = g2int_resumable_icp_pop();
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg1 = g2int_resumable_icp_pop();
			else {
			    value = g2int_read_icp_icp_tree();
			    if (EQ(icp_suspend_1,value)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(code);
				g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg1 = value;
			}
			list_1 = g2int_gensym_cons_1(arg1,Nil);
		    }
		    next = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : Nil;
		    last_1 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : list_1;
		    code = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			temp = g2int_resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1;
				break;
			      case 2:
				goto l2;
				break;
			      case 3:
				goto l3;
				break;
			      default:
				break;
			    }
		    }
		  next_loop_1:
		  l1:
		    value = g2int_peek_icp_byte();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(last_1);
			g2int_resumable_icp_push(next);
			g2int_resumable_icp_push(list_1);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    code = value;
		    if (IFIX(code) == (SI_Long)83L || IFIX(code) == 
			    (SI_Long)82L)
			goto end_loop_1;
		  l2:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_icp_tree();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(FIX((SI_Long)2L));
			    g2int_resumable_icp_push(code);
			    g2int_resumable_icp_push(last_1);
			    g2int_resumable_icp_push(next);
			    g2int_resumable_icp_push(list_1);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(code);
			    g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			    return VALUES_1(G2int_icp_suspend);
			}
			arg1 = value;
		    }
		    next = g2int_gensym_cons_1(arg1,Nil);
		    M_CDR(last_1) = next;
		    last_1 = next;
		    goto next_loop_1;
		  end_loop_1:
		  l3:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			temp_1 = EQ(test,Qg2int_true);
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg1 = g2int_resumable_icp_pop();
			else {
			    value = g2int_read_icp_byte();
			    if (EQ(icp_suspend_1,value)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(Nil);
				g2int_resumable_icp_push(FIX((SI_Long)3L));
				g2int_resumable_icp_push(code);
				g2int_resumable_icp_push(last_1);
				g2int_resumable_icp_push(next);
				g2int_resumable_icp_push(list_1);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(code);
				g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg1 = value;
			}
			arg2 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				FIX((SI_Long)83L);
			temp_1 = FIXNUM_EQ(arg1,arg2);
		    }
		    if (temp_1) {
			value = g2int_read_icp_icp_tree();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(FIX((SI_Long)3L));
			    g2int_resumable_icp_push(code);
			    g2int_resumable_icp_push(last_1);
			    g2int_resumable_icp_push(next);
			    g2int_resumable_icp_push(list_1);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(code);
			    g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			    return VALUES_1(G2int_icp_suspend);
			}
			M_CDR(last_1) = value;
		    }
		    temp = list_1;
		    break;
		  case 80:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_icp_tree();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(code);
			    g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			    return VALUES_1(G2int_icp_suspend);
			}
			arg1 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg2 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_icp_tree();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(code);
			    g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			    return VALUES_1(G2int_icp_suspend);
			}
			arg2 = value;
		    }
		    temp = g2int_gensym_cons_1(arg1,arg2);
		    break;
		  default:
		    value = g2int_icp_error_internal(Qerror,
			    string_constant_9,code,Nil,Nil);
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(code);
			g2int_resumable_icp_push(Qg2int_read_icp_icp_tree);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		    break;
		}
	}
    }
    return VALUES_1(temp);
}

/* RECLAIM-ICP-TREE-VALUE */
Object g2int_reclaim_icp_tree_value(value)
    Object value;
{
    Object temp, cdr_arg, e, ab_loop_list_;

    x_note_fn_call(42,83);
    if ( !TRUEP(value) || SYMBOLP(value) || FIXNUMP(value));
    else if (CONSP(value)) {
	temp = last(value,_);
	g2int_reclaim_icp_tree_value(CDR(temp));
	cdr_arg = last(value,_);
	M_CDR(cdr_arg) = Nil;
	e = Nil;
	ab_loop_list_ = value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	e = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_reclaim_icp_tree_value(e);
	goto next_loop;
      end_loop:;
	g2int_reclaim_gensym_list_1(value);
    }
    else if (g2int_text_string_p(value))
	g2int_reclaim_text_string(value);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	g2int_reclaim_managed_simple_float_array_of_length_1(value);
    return VALUES_1(Nil);
}

Object G2int_the_type_description_of_interned_list = UNBOUND;

Object G2int_chain_of_available_interned_lists = UNBOUND;

Object G2int_interned_list_count = UNBOUND;

/* RECLAIM-INTERNED-LIST-1 */
Object g2int_reclaim_interned_list_1(interned_list)
    Object interned_list;
{
    Object svref_new_value;

    x_note_fn_call(42,84);
    inline_note_reclaim_cons(interned_list,Nil);
    svref_new_value = G2int_chain_of_available_interned_lists;
    SVREF(interned_list,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_interned_lists = interned_list;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INTERNED-LIST */
Object g2int_reclaim_structure_for_interned_list(interned_list)
    Object interned_list;
{
    x_note_fn_call(42,85);
    return g2int_reclaim_interned_list_1(interned_list);
}

static Object Qg2_defstruct_structure_name_interned_list_g2_struct;  /* g2-defstruct-structure-name::interned-list-g2-struct */

/* MAKE-PERMANENT-INTERNED-LIST-STRUCTURE-INTERNAL */
Object g2int_make_permanent_interned_list_structure_internal()
{
    Object def_structure_interned_list_variable, interned_list_count_new_value;
    Object defstruct_g2_interned_list_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(42,86);
    def_structure_interned_list_variable = Nil;
    interned_list_count_new_value = FIXNUM_ADD1(G2int_interned_list_count);
    G2int_interned_list_count = interned_list_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_interned_list_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_interned_list_variable = the_array;
	SVREF(defstruct_g2_interned_list_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_interned_list_g2_struct;
	def_structure_interned_list_variable = 
		defstruct_g2_interned_list_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_interned_list_variable);
}

/* MAKE-INTERNED-LIST-1 */
Object g2int_make_interned_list_1(interned_list__list)
    Object interned_list__list;
{
    Object def_structure_interned_list_variable;

    x_note_fn_call(42,87);
    def_structure_interned_list_variable = 
	    G2int_chain_of_available_interned_lists;
    if (def_structure_interned_list_variable) {
	G2int_chain_of_available_interned_lists = 
		ISVREF(def_structure_interned_list_variable,(SI_Long)0L);
	SVREF(def_structure_interned_list_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_interned_list_g2_struct;
    }
    else
	def_structure_interned_list_variable = 
		g2int_make_permanent_interned_list_structure_internal();
    inline_note_allocate_cons(def_structure_interned_list_variable,Nil);
    SVREF(def_structure_interned_list_variable,FIX((SI_Long)1L)) = 
	    interned_list__list;
    SVREF(def_structure_interned_list_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_interned_list_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_interned_list_variable);
}

/* INTERNED-LIST-P-FUNCTION */
Object g2int_interned_list_p_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(42,88);
    temp = SIMPLE_VECTOR_P(x) ? (EQ(ISVREF(x,(SI_Long)0L),
	    Qg2_defstruct_structure_name_interned_list_g2_struct) ? T : 
	    Nil) : Qnil;
    return VALUES_1(temp);
}

Object G2int_interned_list_conses = UNBOUND;

Object G2int_interned_list_conses_in_use = UNBOUND;

/* INTERNED-LIST-CONS */
Object g2int_interned_list_cons(x,y)
    Object x, y;
{
    Object gensymed_symbol, cons_1, interned_list_conses_in_use_new_value;
    XDeclare_area(1);

    x_note_fn_call(42,89);
    if ( !TRUEP(G2int_interned_list_conses)) {
	gensymed_symbol = Nil;
	if (PUSH_AREA(Dynamic_area,0))
	    gensymed_symbol = make_list(1,FIX((SI_Long)50L));
	POP_AREA(0);
	G2int_interned_list_conses = gensymed_symbol;
    }
    cons_1 = G2int_interned_list_conses;
    G2int_interned_list_conses = CDR(cons_1);
    M_CAR(cons_1) = x;
    M_CDR(cons_1) = y;
    interned_list_conses_in_use_new_value = 
	    FIXNUM_ADD1(G2int_interned_list_conses_in_use);
    G2int_interned_list_conses_in_use = interned_list_conses_in_use_new_value;
    return VALUES_1(cons_1);
}

/* COPY-TREE-FOR-INTERNED-LIST */
Object g2int_copy_tree_for_interned_list(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(42,90);
    if (SYMBOLP(tree))
	temp = tree;
    else if (FIXNUMP(tree))
	temp = tree;
    else if (CONSP(tree)) {
	temp = g2int_copy_tree_for_interned_list(CAR(tree));
	temp = g2int_interned_list_cons(temp,
		g2int_copy_tree_for_interned_list(CDR(tree)));
    }
    else
	temp = tree;
    return VALUES_1(temp);
}

Object G2int_interned_list_table_prop = UNBOUND;

Object G2int_interned_list_non_symbol_root = UNBOUND;

Object G2int_interned_list_symbols = UNBOUND;

Object G2int_interned_list_nil = UNBOUND;

static Object Qg2int_interned_list_table;  /* interned-list-table */

/* INTERN-LIST */
Object g2int_intern_list(list_1)
    Object list_1;
{
    Object accumulating_list_p, list_2, element, root, table, entry_or_table;
    Object entry, element_1, ab_loop_list_, temp, element_copy, e;
    Object cdr_new_value, element_count_1, root_1, ab_loop_list__1;
    Object entry_or_table_1, entry_1, result_1;
    SI_Long element_count, limit;

    x_note_fn_call(42,91);
    element_count = (SI_Long)0L;
    accumulating_list_p = Nil;
    list_2 = Nil;
    element = Nil;
    root = Nil;
    table = Nil;
    entry_or_table = Nil;
    entry = Nil;
    element_1 = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    element = element_1;
    element_count = element_count + (SI_Long)1L;
    if (element_count == (SI_Long)1L) {
	root = SYMBOLP(element) ? element : Nil;
	if (root) {
	    temp = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
		    Qg2int_interned_list_table);
	    if (temp);
	    else {
		accumulating_list_p = T;
		G2int_interned_list_symbols = 
			g2int_interned_list_cons(root,
			G2int_interned_list_symbols);
		temp = root;
		temp = g2int_mutate_global_property(temp,
			g2int_interned_list_cons(Nil,Nil),
			Qg2int_interned_list_table);
	    }
	    table = temp;
	}
	else {
	    temp = G2int_interned_list_non_symbol_root;
	    if (temp);
	    else {
		G2int_interned_list_non_symbol_root = 
			g2int_interned_list_cons(Nil,Nil);
		temp = G2int_interned_list_non_symbol_root;
	    }
	    table = temp;
	}
	if (accumulating_list_p && root)
	    list_2 = g2int_interned_list_cons(root,list_2);
	entry_or_table = table;
	entry = Nil;
    }
    if ( !(element_count == (SI_Long)1L && root)) {
	if (CONSP(entry_or_table))
	    table = entry_or_table;
	else {
	    table = g2int_interned_list_cons(entry_or_table,Nil);
	    M_CDR(entry) = table;
	}
	temp = SYMBOLP(element) ? g2int_assq_function(element,CDR(table)) :
		 g2int_assoc_equal(element,CDR(table));
	if (temp);
	else {
	    element_copy = CONSP(element) ? 
		    g2int_copy_tree_for_interned_list(element) : element;
	    e = g2int_interned_list_cons(element_copy,Nil);
	    cdr_new_value = g2int_interned_list_cons(e,CDR(table));
	    M_CDR(table) = cdr_new_value;
	    if ( !TRUEP(accumulating_list_p)) {
		accumulating_list_p = T;
		element_count_1 = FIX((SI_Long)0L);
		element = Nil;
		root_1 = Nil;
		table = Nil;
		entry_or_table = Nil;
		entry = Nil;
		limit = element_count - (SI_Long)1L;
		element_1 = Nil;
		ab_loop_list__1 = list_1;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		element_1 = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if (limit == IFIX(element_count_1))
		    goto end_list_so_far_block;
		element = element_1;
		element_count_1 = FIXNUM_ADD1(element_count_1);
		if (IFIX(element_count_1) == (SI_Long)1L) {
		    root_1 = SYMBOLP(element) ? element : Nil;
		    if (root_1) {
			temp = 
				g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
				Qg2int_interned_list_table);
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    else {
			temp = G2int_interned_list_non_symbol_root;
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    if (accumulating_list_p && root_1)
			list_2 = g2int_interned_list_cons(root_1,list_2);
		    entry_or_table = table;
		    entry = Nil;
		}
		if ( !(IFIX(element_count_1) == (SI_Long)1L && root_1)) {
		    table = CONSP(entry_or_table) ? entry_or_table : Nil;
		    temp = SYMBOLP(element) ? g2int_assq_function(element,
			    CDR(table)) : g2int_assoc_equal(element,
			    CDR(table));
		    if (temp);
		    else
			temp = Nil;
		    entry = temp;
		    if (accumulating_list_p)
			list_2 = g2int_interned_list_cons(CAR(entry),list_2);
		    entry_or_table = CDR(entry);
		}
		goto next_loop_1;
	      end_loop_1:;
	      end_list_so_far_block:;
	    }
	    temp = e;
	}
	entry = temp;
	if (accumulating_list_p)
	    list_2 = g2int_interned_list_cons(CAR(entry),list_2);
	entry_or_table = CDR(entry);
    }
    goto next_loop;
  end_loop:;
    if ((SI_Long)0L == element_count) {
	temp = G2int_interned_list_nil;
	if (temp);
	else {
	    G2int_interned_list_nil = g2int_make_interned_list_1(Nil);
	    temp = G2int_interned_list_nil;
	}
    }
    else {
	temp = CONSP(entry_or_table) ? CAR(entry_or_table) : entry_or_table;
	if (temp);
	else {
	    if ( !TRUEP(accumulating_list_p)) {
		accumulating_list_p = T;
		element_count_1 = FIX((SI_Long)0L);
		element = Nil;
		root = Nil;
		table = Nil;
		entry_or_table_1 = Nil;
		entry_1 = Nil;
		limit = element_count;
		element_1 = Nil;
		ab_loop_list_ = list_1;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		element_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (limit == IFIX(element_count_1))
		    goto end_list_so_far_block_1;
		element = element_1;
		element_count_1 = FIXNUM_ADD1(element_count_1);
		if (IFIX(element_count_1) == (SI_Long)1L) {
		    root = SYMBOLP(element) ? element : Nil;
		    if (root) {
			temp = 
				g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
				Qg2int_interned_list_table);
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    else {
			temp = G2int_interned_list_non_symbol_root;
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    if (accumulating_list_p && root)
			list_2 = g2int_interned_list_cons(root,list_2);
		    entry_or_table_1 = table;
		    entry_1 = Nil;
		}
		if ( !(IFIX(element_count_1) == (SI_Long)1L && root)) {
		    table = CONSP(entry_or_table_1) ? entry_or_table_1 : Nil;
		    temp = SYMBOLP(element) ? g2int_assq_function(element,
			    CDR(table)) : g2int_assoc_equal(element,
			    CDR(table));
		    if (temp);
		    else
			temp = Nil;
		    entry_1 = temp;
		    if (accumulating_list_p)
			list_2 = g2int_interned_list_cons(CAR(entry_1),list_2);
		    entry_or_table_1 = CDR(entry_1);
		}
		goto next_loop_2;
	      end_loop_2:;
	      end_list_so_far_block_1:;
	    }
	    result_1 = g2int_make_interned_list_1(nreverse(list_2));
	    if (CONSP(entry_or_table))
		temp = M_CAR(entry_or_table) = result_1;
	    else
		temp = M_CDR(entry) = result_1;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_intern_list;  /* send-icp-intern-list */

/* SEND-ICP-INTERN-LIST */
Object g2int_send_icp_intern_list(corresponding_icp_object_index,list_1)
    Object corresponding_icp_object_index, list_1;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,92);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_intern_list;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)351L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_icp_tree(list_1);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_intern_list,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_intern_list,top,Nil);
		goto end_send_icp_intern_list;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	list_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_1;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_intern_list;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)351L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_icp_tree(list_1))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(list_1);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_intern_list);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_intern_list;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_intern_list:
    return result;
}

/* HANDLE-ICP-INTERN-LIST--BODY */
Object g2int_handle_icp_intern_list__body(corresponding_icp_object_index,
	    list_1)
    Object corresponding_icp_object_index, list_1;
{
    x_note_fn_call(42,93);
    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
	    g2int_intern_list(list_1));
    g2int_reclaim_gensym_tree_1(list_1);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_intern_list;  /* handle-icp-intern-list */

/* HANDLE-ICP-INTERN-LIST */
Object g2int_handle_icp_intern_list()
{
    Object corresponding_icp_object_index, list_1, abort_for_icp_catcher_qm;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(42,94);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	list_1 = g2int_read_icp_icp_tree();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_intern_list__body(corresponding_icp_object_index,
		  list_1);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_intern_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_intern_list,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_intern_list);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    list_1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_icp_tree();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_intern_list);
		return VALUES_1(G2int_icp_suspend);
	    }
	    list_1 = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_intern_list__body(corresponding_icp_object_index,
		  list_1);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_establish_new_object_index_for_interned_list;  /* establish-new-object-index-for-interned-list */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-INTERNED-LIST */
Object g2int_establish_new_object_index_for_interned_list varargs_1(int, n)
{
    Object interned_list, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(42,95);
    INIT_ARGS_nonrelocating();
    interned_list = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (G2int_disable_resumability) {
	result = g2int_assign_corresponding_icp_object_index(interned_list,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(interned_list,(SI_Long)2L)));
	SVREF(interned_list,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_establish_new_object_index_for_interned_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_establish_new_object_index_for_interned_list,
			top,Nil);
	}
	interned_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : interned_list;
	icp_port = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : send_enlarge_message_p;
	result = g2int_assign_corresponding_icp_object_index(interned_list,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(interned_list,(SI_Long)2L)));
	SVREF(interned_list,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qg2int_make_corresponding_icp_interned_list;  /* make-corresponding-icp-interned-list */

/* MAKE-CORRESPONDING-ICP-INTERNED-LIST */
Object g2int_make_corresponding_icp_interned_list(interned_list)
    Object interned_list;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,96);
    if (G2int_disable_resumability) {
	g2int_write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = g2int_assign_corresponding_icp_object_index(interned_list,
		  Qg2int_standard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
		  g2int_gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(interned_list,(SI_Long)2L)));
	  SVREF(interned_list,FIX((SI_Long)2L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(G2int_inhibit_corresponding_icp_object_making))
	      g2int_send_icp_intern_list(corresponding_icp_object_index,
		      ISVREF(interned_list,(SI_Long)1L));
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_make_corresponding_icp_interned_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_make_corresponding_icp_interned_list,top,Nil);
	}
	interned_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : interned_list;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = g2int_resumable_icp_pop();
	  else {
	      result = g2int_assign_corresponding_icp_object_index(interned_list,
		      Qg2int_standard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
		      g2int_gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(interned_list,(SI_Long)2L)));
	      SVREF(interned_list,FIX((SI_Long)2L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  ||  !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      if (EQ(icp_suspend_1,
		      g2int_send_icp_intern_list(corresponding_icp_object_index,
		      ISVREF(interned_list,(SI_Long)1L)))) {
		  g2int_resumable_icp_push(corresponding_icp_object_index);
		  g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(interned_list);
	    g2int_resumable_icp_push(Qg2int_make_corresponding_icp_interned_list);
	    return VALUES_1(G2int_icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-INTERNED-LIST */
Object g2int_get_icp_object_index_for_interned_list(interned_list,icp_port)
    Object interned_list, icp_port;
{
    x_note_fn_call(42,97);
    return g2int_getfq_function_no_default(ISVREF(interned_list,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-INTERNED-LIST */
Object g2int_set_icp_object_index_for_interned_list(interned_list,
	    corresponding_icp_object_index,icp_port)
    Object interned_list, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(42,98);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(interned_list,(SI_Long)2L)));
    return VALUES_1(SVREF(interned_list,FIX((SI_Long)2L)) = svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-INTERNED-LIST */
Object g2int_reclaim_icp_object_map_for_interned_list(interned_list)
    Object interned_list;
{
    Object icp_object_map;

    x_note_fn_call(42,99);
    icp_object_map = ISVREF(interned_list,(SI_Long)2L);
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(interned_list,icp_object_map,
		Qg2int_standard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_interned_list;  /* set-access-form-for-interned-list */

/* RECLAIM-ICP-PORT-ENTRY-FOR-INTERNED-LIST */
Object g2int_reclaim_icp_port_entry_for_interned_list(interned_list,icp_port)
    Object interned_list, icp_port;
{
    x_note_fn_call(42,100);
    return g2int_reclaim_icp_port_entry(icp_port,interned_list,
	    ISVREF(interned_list,(SI_Long)2L),
	    Qg2int_set_access_form_for_interned_list);
}

/* SET-ACCESS-FORM-FOR-INTERNED-LIST */
Object g2int_set_access_form_for_interned_list(interned_list,new_value)
    Object interned_list, new_value;
{
    x_note_fn_call(42,101);
    return VALUES_1(SVREF(interned_list,FIX((SI_Long)2L)) = new_value);
}

static Object Qg2int_write_icp_interned_list_as_value_type;  /* write-icp-interned-list-as-value-type */

/* WRITE-ICP-INTERNED-LIST-AS-VALUE-TYPE */
Object g2int_write_icp_interned_list_as_value_type(interned_list_as_value_type)
    Object interned_list_as_value_type;
{
    Object interned_list, index_1, writing_resumable_icp_messages_p, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, test, arg1, value;
    Object value_1, v1, v2, v3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,102);
    if (G2int_disable_resumability) {
	interned_list = interned_list_as_value_type;
	index_1 = g2int_getfq_function_no_default(ISVREF(interned_list,
		(SI_Long)2L),G2int_current_icp_port);
	if (G2int_inhibit_corresponding_icp_object_making) {
	    g2int_write_icp_byte(FIX((SI_Long)65534L));
	    g2int_write_icp_maybe_suspend();
	    writing_resumable_icp_messages_p = Nil;
	    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		    0);
	      temp = index_1;
	      if (temp);
	      else
		  temp = 
			  g2int_establish_new_object_index_for_interned_list(3,
			  interned_list,G2int_current_icp_port,Nil);
	      temp = g2int_write_icp_corresponding_object_index(temp);
	    POP_SPECIAL();
	}
	else if (index_1)
	    temp = g2int_write_icp_corresponding_object_index(index_1);
	else {
	    g2int_write_icp_byte(FIX((SI_Long)65535L));
	    g2int_write_icp_maybe_suspend();
	    writing_resumable_icp_messages_p = Nil;
	    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		    0);
	      g2int_write_icp_corresponding_object_index(g2int_establish_new_object_index_for_interned_list(3,
		      interned_list,G2int_current_icp_port,Nil));
	      temp = g2int_write_icp_icp_tree(ISVREF(interned_list,
		      (SI_Long)1L));
	    POP_SPECIAL();
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_interned_list_as_value_type,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_interned_list_as_value_type,top,Nil);
	}
	interned_list_as_value_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : interned_list_as_value_type;
	interned_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : interned_list_as_value_type;
	index_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		g2int_getfq_function_no_default(ISVREF(interned_list,
		(SI_Long)2L),G2int_current_icp_port);
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : 
		TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1;
			break;
		      case 2:
			goto l2;
			break;
		      default:
			break;
		    }
	    }
	  l1:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)65534L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l2:
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1_1;
			break;
		      case 2:
			goto l2_1;
			break;
		      default:
			break;
		    }
	    }
	  l1_1:
	    if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block_1;
	    }
	  l2_1:
	    writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		    0);
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  arg1 = g2int_resumable_icp_pop();
	      else {
		  value = (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? g2int_resumable_icp_pop() : index_1;
		  if ( !(resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) && value)
		      arg1 = value;
		  else {
		      value_1 = 
			      g2int_establish_new_object_index_for_interned_list(3,
			      interned_list,G2int_current_icp_port,Nil);
		      if (EQ(icp_suspend_1,value_1)) {
			  g2int_resumable_icp_push(value);
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
			  g2int_resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(G2int_icp_suspend);
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      arg1 = value_1;
		  }
	      }
	      value = g2int_write_icp_corresponding_object_index(arg1);
	      if (EQ(icp_suspend_1,value)) {
		  g2int_resumable_icp_push(arg1);
		  g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block_1;
	      }
	      result = VALUES_1(value);
	    POP_SPECIAL();
	    goto end_block_1;
	  end_block_1:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    result = VALUES_3(v1,v2,v3);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(index_1);
		g2int_resumable_icp_push(interned_list);
		g2int_resumable_icp_push(interned_list_as_value_type);
		g2int_resumable_icp_push(Qg2int_write_icp_interned_list_as_value_type);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : TRUEP(index_1)) {
		value = g2int_write_icp_corresponding_object_index(index_1);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(index_1);
		    g2int_resumable_icp_push(interned_list);
		    g2int_resumable_icp_push(interned_list_as_value_type);
		    g2int_resumable_icp_push(Qg2int_write_icp_interned_list_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_2;
			    break;
			  case 2:
			    goto l2_2;
			    break;
			  default:
			    break;
			}
		}
	      l1_2:
		if (EQ(icp_suspend_1,
			g2int_write_icp_byte(FIX((SI_Long)65535L)))) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_2;
		}
	      l2_2:
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_3;
			    break;
			  case 2:
			    goto l2_3;
			    break;
			  default:
			    break;
			}
		}
	      l1_3:
		if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_3;
		}
	      l2_3:
		writing_resumable_icp_messages_p = (resumable_icp_state_1 ?
			 TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
			0);
		  if (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) {
		      temp = g2int_resumable_icp_pop();
		      if (! !(FIXNUMP(temp) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			      FIXNUM_LE(temp,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp)) {
			    case 1:
			      goto l1_4;
			      break;
			    case 2:
			      goto l2_4;
			      break;
			    default:
			      break;
			  }
		  }
		l1_4:
		  if ((resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		      arg1 = g2int_resumable_icp_pop();
		  else {
		      value = 
			      g2int_establish_new_object_index_for_interned_list(3,
			      interned_list,G2int_current_icp_port,Nil);
		      if (EQ(icp_suspend_1,value)) {
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(FIX((SI_Long)1L));
			  result = VALUES_1(G2int_icp_suspend);
			  goto end_block_4;
		      }
		      arg1 = value;
		  }
		  if (EQ(icp_suspend_1,
			  g2int_write_icp_corresponding_object_index(arg1))) {
		      g2int_resumable_icp_push(arg1);
		      g2int_resumable_icp_push(FIX((SI_Long)1L));
		      result = VALUES_1(G2int_icp_suspend);
		      goto end_block_4;
		  }
		l2_4:
		  value = g2int_write_icp_icp_tree(ISVREF(interned_list,
			  (SI_Long)1L));
		  if (EQ(icp_suspend_1,value)) {
		      g2int_resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(G2int_icp_suspend);
		      goto end_block_4;
		  }
		  result = VALUES_1(value);
		  goto end_block_4;
		end_block_4:
		  MVS_3(result,v1,v2,v3);
		  if (EQ(icp_suspend_1,v1)) {
		      g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		      g2int_resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(G2int_icp_suspend);
		      POP_SPECIAL();
		      goto end_block_3;
		  }
		  result = VALUES_3(v1,v2,v3);
		POP_SPECIAL();
		goto end_block_3;
	      end_block_3:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_2;
		}
		result = VALUES_3(v1,v2,v3);
		goto end_block_2;
	      end_block_2:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(index_1);
		    g2int_resumable_icp_push(interned_list);
		    g2int_resumable_icp_push(interned_list_as_value_type);
		    g2int_resumable_icp_push(Qg2int_write_icp_interned_list_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_interned_list_as_value_type;  /* read-icp-interned-list-as-value-type */

/* READ-ICP-INTERNED-LIST-AS-VALUE-TYPE */
Object g2int_read_icp_interned_list_as_value_type()
{
    Object corresponding_icp_object_index, tree, interned_list, temp;
    Object index_space, index_1, resumable_icp_state_1, icp_suspend_1, top;
    Object test, arg1, value, arg2, v1, v2, v3;
    char temp_1;
    Object result;

    x_note_fn_call(42,103);
    if (G2int_disable_resumability) {
	if (IFIX(g2int_peek_icp_byte()) == (SI_Long)65535L) {
	    g2int_read_icp_byte();
	    corresponding_icp_object_index = 
		    g2int_read_icp_corresponding_object_index();
	    tree = g2int_read_icp_icp_tree();
	    interned_list = g2int_intern_list(tree);
	    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
		    interned_list);
	    g2int_reclaim_gensym_tree_1(tree);
	    temp = interned_list;
	}
	else if (IFIX(g2int_peek_icp_byte()) == (SI_Long)65534L) {
	    g2int_read_icp_byte();
	    index_space = G2int_current_temporary_icp_object_index_space;
	    index_1 = g2int_read_icp_corresponding_object_index();
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    temp = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else {
	    index_space = G2int_current_standard_icp_object_index_space;
	    index_1 = g2int_read_icp_corresponding_object_index();
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    temp = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_interned_list_as_value_type,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_interned_list_as_value_type,top,Nil);
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp_1 = EQ(test,Qg2int_true);
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_peek_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Nil);
		    g2int_resumable_icp_push(Qg2int_read_icp_interned_list_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		arg1 = value;
	    }
	    arg2 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX((SI_Long)65535L);
	    temp_1 = FIXNUM_EQ(arg1,arg2);
	}
	if (temp_1) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1;
			break;
		      case 2:
			goto l2;
			break;
		      default:
			break;
		    }
	    }
	  l1:
	    if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l2:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		tree = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_icp_tree();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		tree = value;
	    }
	    interned_list = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : g2int_intern_list(tree);
	    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
		    interned_list);
	    g2int_reclaim_gensym_tree_1(tree);
	    result = VALUES_1(interned_list);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(Qg2int_read_icp_interned_list_as_value_type);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp_1 = EQ(test,Qg2int_true);
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_peek_icp_byte();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Nil);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_read_icp_interned_list_as_value_type);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		arg2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : FIX((SI_Long)65534L);
		temp_1 = FIXNUM_EQ(arg1,arg2);
	    }
	    if (temp_1) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_1;
		}
	      l2_1:
		index_space = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			G2int_current_temporary_icp_object_index_space;
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    index_1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(index_space);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_1;
		    }
		    index_1 = value;
		}
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		result = VALUES_1(ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L));
		goto end_block_1;
	      end_block_1:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_read_icp_interned_list_as_value_type);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		index_space = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			G2int_current_standard_icp_object_index_space;
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    index_1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(index_space);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_read_icp_interned_list_as_value_type);
			return VALUES_1(G2int_icp_suspend);
		    }
		    index_1 = value;
		}
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		temp = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_icp_read_task = UNBOUND;

Object G2int_chain_of_available_icp_read_tasks = UNBOUND;

Object G2int_icp_read_task_count = UNBOUND;

/* RECLAIM-ICP-READ-TASK-1 */
Object g2int_reclaim_icp_read_task_1(icp_read_task)
    Object icp_read_task;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(42,104);
    inline_note_reclaim_cons(icp_read_task,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = icp_read_task;
    g2int_reclaim_gensym_list_1(ISVREF(icp_read_task,(SI_Long)3L));
    SVREF(icp_read_task,FIX((SI_Long)3L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_icp_read_tasks;
    SVREF(icp_read_task,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_icp_read_tasks = icp_read_task;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-READ-TASK */
Object g2int_reclaim_structure_for_icp_read_task(icp_read_task)
    Object icp_read_task;
{
    x_note_fn_call(42,105);
    return g2int_reclaim_icp_read_task_1(icp_read_task);
}

static Object Qg2_defstruct_structure_name_icp_read_task_g2_struct;  /* g2-defstruct-structure-name::icp-read-task-g2-struct */

/* MAKE-PERMANENT-ICP-READ-TASK-STRUCTURE-INTERNAL */
Object g2int_make_permanent_icp_read_task_structure_internal()
{
    Object def_structure_icp_read_task_variable, icp_read_task_count_new_value;
    Object defstruct_g2_icp_read_task_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(42,106);
    def_structure_icp_read_task_variable = Nil;
    icp_read_task_count_new_value = FIXNUM_ADD1(G2int_icp_read_task_count);
    G2int_icp_read_task_count = icp_read_task_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_read_task_variable = Nil;
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
	defstruct_g2_icp_read_task_variable = the_array;
	SVREF(defstruct_g2_icp_read_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_read_task_g2_struct;
	def_structure_icp_read_task_variable = 
		defstruct_g2_icp_read_task_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_read_task_variable);
}

/* MAKE-ICP-READ-TASK-1 */
Object g2int_make_icp_read_task_1(icp_read_task_corresponding_icp_object_index)
    Object icp_read_task_corresponding_icp_object_index;
{
    Object def_structure_icp_read_task_variable;

    x_note_fn_call(42,107);
    def_structure_icp_read_task_variable = 
	    G2int_chain_of_available_icp_read_tasks;
    if (def_structure_icp_read_task_variable) {
	G2int_chain_of_available_icp_read_tasks = 
		ISVREF(def_structure_icp_read_task_variable,(SI_Long)0L);
	SVREF(def_structure_icp_read_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_read_task_g2_struct;
    }
    else
	def_structure_icp_read_task_variable = 
		g2int_make_permanent_icp_read_task_structure_internal();
    inline_note_allocate_cons(def_structure_icp_read_task_variable,Nil);
    SVREF(def_structure_icp_read_task_variable,FIX((SI_Long)1L)) = 
	    icp_read_task_corresponding_icp_object_index;
    SVREF(def_structure_icp_read_task_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_icp_read_task_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_icp_read_task_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_icp_read_task_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_icp_read_task_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_icp_read_task_variable);
}

/* ICP-READ-TASK-PRIORITY-FUNCTION */
Object g2int_icp_read_task_priority_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(42,108);
    temp = ISVREF(x,(SI_Long)4L);
    return VALUES_1(temp);
}

/* CURRENT-ICP-READ-TASK-RESUMABLE-P */
Object g2int_current_icp_read_task_resumable_p()
{
    Object task, temp;

    x_note_fn_call(42,109);
    task = G2int_current_resumable_icp_read_task;
    temp = task ? ISVREF(task,(SI_Long)5L) : Nil;
    return VALUES_1(temp);
}

static Object Qg2int_gsi;          /* gsi */

/* KILL-CURRENT-ICP-READ-TASK */
Object g2int_kill_current_icp_read_task()
{
    Object task;

    x_note_fn_call(42,110);
    g2int_reclaim_gensym_list_1(G2int_starresumable_icp_statestar);
    G2int_starresumable_icp_statestar = Nil;
    task = G2int_current_resumable_icp_read_task;
    if (task) {
	SVREF(task,FIX((SI_Long)3L)) = Nil;
	g2int_store_corresponding_icp_object(ISVREF(task,(SI_Long)1L),Nil);
	g2int_gsi_reclaim_contents(ISVREF(task,(SI_Long)6L),Qg2int_gsi);
	g2int_reclaim_icp_read_task_1(task);
	G2int_current_resumable_icp_read_task = Nil;
	return VALUES_1(G2int_current_resumable_icp_read_task);
    }
    else
	return VALUES_1(Nil);
}

/* MAYBE-FINISH-CURRENT-ICP-READ-TASK */
Object g2int_maybe_finish_current_icp_read_task()
{
    Object task;

    x_note_fn_call(42,111);
    task = G2int_current_resumable_icp_read_task;
    if (task &&  !TRUEP(ISVREF(task,(SI_Long)5L))) {
	g2int_store_corresponding_icp_object(ISVREF(task,(SI_Long)1L),Nil);
	g2int_gsi_reclaim_contents(ISVREF(task,(SI_Long)6L),Qg2int_gsi);
	g2int_reclaim_icp_read_task_1(task);
	G2int_current_resumable_icp_read_task = Nil;
	return VALUES_1(G2int_current_resumable_icp_read_task);
    }
    else
	return VALUES_1(Nil);
}

Object G2int_gsi_reclaim_listqm = UNBOUND;

/* RESUME-ICP-TASK-1 */
Object g2int_resume_icp_task_1(function_qm)
    Object function_qm;
{
    Object task, resumable_icp_state, function, gsi_reclaim_list_qm, temp;
    Object suspendp, svref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(42,112);
    task = G2int_current_resumable_icp_read_task;
    resumable_icp_state =  !TRUEP(function_qm) ? ISVREF(task,(SI_Long)3L) :
	     Nil;
    PUSH_SPECIAL(G2int_starresumable_icp_statestar,resumable_icp_state,1);
      function = function_qm;
      if (function);
      else
	  function = ISVREF(task,(SI_Long)2L);
      gsi_reclaim_list_qm = ISVREF(task,(SI_Long)6L);
      PUSH_SPECIAL(G2int_gsi_reclaim_listqm,gsi_reclaim_list_qm,0);
	if (function) {
	    temp = G2int_icp_suspend;
	    suspendp = EQ(temp,inline_funcall_0(function)) ? T : Nil;
	}
	else
	    suspendp = Nil;
	svref_new_value = suspendp ? function : Nil;
	SVREF(task,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = G2int_gsi_reclaim_listqm;
	SVREF(task,FIX((SI_Long)6L)) = svref_new_value;
	svref_new_value = G2int_starresumable_icp_statestar;
	result = VALUES_1(SVREF(task,FIX((SI_Long)3L)) = svref_new_value);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qg2int_read_icp_icp_task_resumable_p;  /* read-icp-icp-task-resumable-p */

/* READ-ICP-ICP-TASK-RESUMABLE-P */
Object g2int_read_icp_icp_task_resumable_p()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(42,113);
    if (G2int_disable_resumability)
	temp = g2int_read_icp_boolean();
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_icp_task_resumable_p,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_icp_task_resumable_p,top,Nil);
	}
	value = g2int_read_icp_boolean();
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(Qg2int_read_icp_icp_task_resumable_p);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

Object G2int_buffer_of_resumable_p = UNBOUND;

Object G2int_index_of_resumable_p_in_icp_buffer = UNBOUND;

static Object Qg2int_write_icp_icp_task_resumable_p;  /* write-icp-icp-task-resumable-p */

/* WRITE-ICP-ICP-TASK-RESUMABLE-P */
Object g2int_write_icp_icp_task_resumable_p(icp_task_resumable_p)
    Object icp_task_resumable_p;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, gensymed_symbol;
    Object value;

    x_note_fn_call(42,114);
    if (G2int_disable_resumability) {
	temp = g2int_write_icp_boolean(icp_task_resumable_p);
	G2int_buffer_of_resumable_p = G2int_current_icp_buffer;
	G2int_index_of_resumable_p_in_icp_buffer = 
		G2int_current_write_icp_byte_position;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_icp_task_resumable_p,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_icp_task_resumable_p,top,Nil);
	}
	icp_task_resumable_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : icp_task_resumable_p;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gensymed_symbol = g2int_resumable_icp_pop();
	else {
	    value = g2int_write_icp_boolean(icp_task_resumable_p);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(icp_task_resumable_p);
		g2int_resumable_icp_push(Qg2int_write_icp_icp_task_resumable_p);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gensymed_symbol = value;
	}
	G2int_buffer_of_resumable_p = G2int_current_icp_buffer;
	G2int_index_of_resumable_p_in_icp_buffer = 
		G2int_current_write_icp_byte_position;
	temp = gensymed_symbol;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_start_icp_task;  /* send-icp-start-icp-task */

/* SEND-ICP-START-ICP-TASK */
Object g2int_send_icp_start_icp_task(resumable_p,icp_task_index,
	    icp_task_priority)
    Object resumable_p, icp_task_index, icp_task_priority;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(42,115);
    index_of_top_of_backtrace_stack = G2int_index_of_top_of_backtrace_stack;
    PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
	      G2int_size_of_basic_backtrace_information),
	      G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qg2int_send_icp_start_icp_task;
      }
      g2int_start_writing_icp_message(FIX((SI_Long)245L));
      g2int_write_icp_icp_task_resumable_p(resumable_p);
      g2int_write_icp_unsigned_integer(icp_task_index);
      g2int_write_icp_unsigned_integer(icp_task_priority);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-START-ICP-TASK--BODY */
Object g2int_handle_icp_start_icp_task__body(resumable_p,icp_task_index,
	    icp_task_priority)
    Object resumable_p, icp_task_index, icp_task_priority;
{
    Object task;

    x_note_fn_call(42,116);
    task = g2int_make_icp_read_task_1(icp_task_index);
    SVREF(task,FIX((SI_Long)4L)) = icp_task_priority;
    SVREF(task,FIX((SI_Long)5L)) = resumable_p;
    g2int_store_corresponding_icp_object(icp_task_index,task);
    G2int_current_resumable_icp_read_task = task;
    return VALUES_1(Nil);
}

/* HANDLE-ICP-START-ICP-TASK */
Object g2int_handle_icp_start_icp_task()
{
    Object resumable_p, icp_task_index, icp_task_priority;

    x_note_fn_call(42,117);
    resumable_p = g2int_read_icp_icp_task_resumable_p();
    icp_task_index = g2int_read_icp_unsigned_integer();
    icp_task_priority = g2int_read_icp_unsigned_integer();
    g2int_handle_icp_start_icp_task__body(resumable_p,icp_task_index,
	    icp_task_priority);
    return VALUES_1(Nil);
}

static Object Qg2int_send_icp_resume_icp_task;  /* send-icp-resume-icp-task */

/* SEND-ICP-RESUME-ICP-TASK */
Object g2int_send_icp_resume_icp_task(resumable_p,icp_task_index)
    Object resumable_p, icp_task_index;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(42,118);
    index_of_top_of_backtrace_stack = G2int_index_of_top_of_backtrace_stack;
    PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
	      G2int_size_of_basic_backtrace_information),
	      G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qg2int_send_icp_resume_icp_task;
      }
      g2int_start_writing_icp_message(FIX((SI_Long)246L));
      g2int_write_icp_icp_task_resumable_p(resumable_p);
      g2int_write_icp_unsigned_integer(icp_task_index);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-RESUME-ICP-TASK--BODY */
Object g2int_handle_icp_resume_icp_task__body(resumable_p,icp_task_index)
    Object resumable_p, icp_task_index;
{
    Object task;

    x_note_fn_call(42,119);
    task = g2int_get_from_icp_port_if_any(G2int_current_icp_port,
	    icp_task_index,Qg2int_standard_icp_object_index_space);
    if ( !TRUEP(task))
	g2int_icp_out_of_synch(1,FIX((SI_Long)6L));
    SVREF(task,FIX((SI_Long)5L)) = resumable_p;
    G2int_current_resumable_icp_read_task = task;
    g2int_resume_icp_task_1(Nil);
    return VALUES_1(Nil);
}

/* HANDLE-ICP-RESUME-ICP-TASK */
Object g2int_handle_icp_resume_icp_task()
{
    Object resumable_p, icp_task_index;

    x_note_fn_call(42,120);
    resumable_p = g2int_read_icp_icp_task_resumable_p();
    icp_task_index = g2int_read_icp_unsigned_integer();
    g2int_handle_icp_resume_icp_task__body(resumable_p,icp_task_index);
    return VALUES_1(Nil);
}

static Object Qg2int_send_icp_abort_icp_task;  /* send-icp-abort-icp-task */

/* SEND-ICP-ABORT-ICP-TASK */
Object g2int_send_icp_abort_icp_task(icp_task_index)
    Object icp_task_index;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(42,121);
    index_of_top_of_backtrace_stack = G2int_index_of_top_of_backtrace_stack;
    PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
	      G2int_size_of_basic_backtrace_information),
	      G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qg2int_send_icp_abort_icp_task;
      }
      g2int_start_writing_icp_message(FIX((SI_Long)250L));
      g2int_write_icp_unsigned_integer(icp_task_index);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-ABORT-ICP-TASK--BODY */
Object g2int_handle_icp_abort_icp_task__body(icp_task_index)
    Object icp_task_index;
{
    Object task;

    x_note_fn_call(42,122);
    task = g2int_get_from_icp_port_if_any(G2int_current_icp_port,
	    icp_task_index,Qg2int_standard_icp_object_index_space);
    if ( !TRUEP(task))
	g2int_icp_out_of_synch(1,FIX((SI_Long)6L));
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    G2int_current_resumable_icp_read_task = task;
    g2int_maybe_finish_current_icp_read_task();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-ABORT-ICP-TASK */
Object g2int_handle_icp_abort_icp_task()
{
    Object icp_task_index;

    x_note_fn_call(42,123);
    icp_task_index = g2int_read_icp_unsigned_integer();
    g2int_handle_icp_abort_icp_task__body(icp_task_index);
    return VALUES_1(Nil);
}

Object G2int_the_type_description_of_icp_write_task = UNBOUND;

Object G2int_chain_of_available_icp_write_tasks = UNBOUND;

Object G2int_icp_write_task_count = UNBOUND;

/* RECLAIM-ICP-WRITE-TASK-1 */
Object g2int_reclaim_icp_write_task_1(icp_write_task)
    Object icp_write_task;
{
    Object svref_new_value;

    x_note_fn_call(42,124);
    inline_note_reclaim_cons(icp_write_task,Nil);
    svref_new_value = G2int_chain_of_available_icp_write_tasks;
    SVREF(icp_write_task,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_icp_write_tasks = icp_write_task;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-WRITE-TASK */
Object g2int_reclaim_structure_for_icp_write_task(icp_write_task)
    Object icp_write_task;
{
    x_note_fn_call(42,125);
    return g2int_reclaim_icp_write_task_1(icp_write_task);
}

static Object Qg2_defstruct_structure_name_icp_write_task_g2_struct;  /* g2-defstruct-structure-name::icp-write-task-g2-struct */

/* MAKE-PERMANENT-ICP-WRITE-TASK-STRUCTURE-INTERNAL */
Object g2int_make_permanent_icp_write_task_structure_internal()
{
    Object def_structure_icp_write_task_variable;
    Object icp_write_task_count_new_value;
    Object defstruct_g2_icp_write_task_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(42,126);
    def_structure_icp_write_task_variable = Nil;
    icp_write_task_count_new_value = FIXNUM_ADD1(G2int_icp_write_task_count);
    G2int_icp_write_task_count = icp_write_task_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_write_task_variable = Nil;
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
	defstruct_g2_icp_write_task_variable = the_array;
	SVREF(defstruct_g2_icp_write_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_write_task_g2_struct;
	def_structure_icp_write_task_variable = 
		defstruct_g2_icp_write_task_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_write_task_variable);
}

/* MAKE-ICP-WRITE-TASK-1 */
Object g2int_make_icp_write_task_1(icp_write_task_corresponding_icp_object_index,
	    icp_write_task_function,icp_write_task_argument_list,
	    icp_write_task_startp,icp_write_task_resumable_icp_state,
	    icp_write_task_completion_function,
	    icp_write_task_completion_argument_list)
    Object icp_write_task_corresponding_icp_object_index;
    Object icp_write_task_function, icp_write_task_argument_list;
    Object icp_write_task_startp, icp_write_task_resumable_icp_state;
    Object icp_write_task_completion_function;
    Object icp_write_task_completion_argument_list;
{
    Object def_structure_icp_write_task_variable;

    x_note_fn_call(42,127);
    def_structure_icp_write_task_variable = 
	    G2int_chain_of_available_icp_write_tasks;
    if (def_structure_icp_write_task_variable) {
	G2int_chain_of_available_icp_write_tasks = 
		ISVREF(def_structure_icp_write_task_variable,(SI_Long)0L);
	SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_write_task_g2_struct;
    }
    else
	def_structure_icp_write_task_variable = 
		g2int_make_permanent_icp_write_task_structure_internal();
    inline_note_allocate_cons(def_structure_icp_write_task_variable,Nil);
    SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)1L)) = 
	    icp_write_task_corresponding_icp_object_index;
    SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)2L)) = 
	    icp_write_task_function;
    SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)3L)) = 
	    icp_write_task_argument_list;
    SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)4L)) = 
	    icp_write_task_startp;
    SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)5L)) = 
	    icp_write_task_resumable_icp_state;
    SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)6L)) = 
	    icp_write_task_completion_function;
    SVREF(def_structure_icp_write_task_variable,FIX((SI_Long)7L)) = 
	    icp_write_task_completion_argument_list;
    return VALUES_1(def_structure_icp_write_task_variable);
}

/* MAKE-RESUMABLE-ICP-OUTPUT-TASK-QUEUE-VECTOR */
Object g2int_make_resumable_icp_output_task_queue_vector()
{
    Object length_1, vector_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(42,128);
    length_1 = FIXNUM_ADD1(FIXNUM_MINUS(G2int_lowest_system_priority,
	    G2int_highest_system_priority));
    vector_1 = g2int_allocate_managed_simple_vector(length_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ISVREF(vector_1,i) = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(vector_1);
}

/* RECLAIM-RESUMABLE-ICP-OUTPUT-TASK-QUEUE-VECTOR */
Object g2int_reclaim_resumable_icp_output_task_queue_vector(vector_qm)
    Object vector_qm;
{
    Object queue_qm, queue, next_queue_element, task;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(42,129);
    if (vector_qm) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_qm));
	queue_qm = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	queue_qm = ISVREF(vector_qm,i);
	if (queue_qm) {
	    SVREF(queue_qm,FIX((SI_Long)2L)) = Nil;
	    queue = queue_qm;
	    next_queue_element = Nil;
	    task = Nil;
	    next_queue_element = ISVREF(queue,(SI_Long)0L);
	  next_loop_1:
	    if (EQ(next_queue_element,queue))
		goto end_loop_1;
	    task = ISVREF(next_queue_element,(SI_Long)2L);
	    next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
	    g2int_reclaim_icp_write_task_1(task);
	    goto next_loop_1;
	  end_loop_1:
	    g2int_reclaim_constant_queue(queue_qm);
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	g2int_reclaim_managed_simple_vector(vector_qm);
    }
    return VALUES_1(Nil);
}

/* RUN-RESUMABLE-ICP-WRITE-TASK */
Object g2int_run_resumable_icp_write_task(task,priority)
    Object task, priority;
{
    Object function, argument_list, resumable_icp_state, current_icp_socket;
    Object writing_resumable_icp_messages_p, icp_write_task_index;
    Object icp_error_suspend_p, suspendp, current_icp_port, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, buffer_of_resumable_p;
    Object index_of_resumable_p_in_icp_buffer, temp_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6, gensymed_symbol_7, gensymed_symbol_8;
    Object gensymed_symbol_9, gensymed_symbol_10, gensymed_symbol_11;
    Object svref_new_value, array, completion_function;
    Object completion_argument_list;
    SI_Long icp_position, position_1, value, temp_2, gensymed_symbol_12;
    double gensymed_symbol_1;
    Declare_special(18);
    Object result;

    x_note_fn_call(42,130);
    function = ISVREF(task,(SI_Long)2L);
    argument_list = ISVREF(task,(SI_Long)3L);
    resumable_icp_state = Nil;
    PUSH_SPECIAL(G2int_starresumable_icp_statestar,resumable_icp_state,17);
      current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,16);
	writing_resumable_icp_messages_p =  
		!(IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? TRUEP(ISVREF(G2int_current_icp_socket,
		(SI_Long)53L)) : TRUEP(Nil)) ? T : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		15);
	  icp_write_task_index = Nil;
	  icp_error_suspend_p = Nil;
	  PUSH_SPECIAL(G2int_icp_error_suspend_p,icp_error_suspend_p,14);
	    suspendp = Nil;
	    current_icp_port = G2int_current_icp_port;
	    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,13);
	      current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,12);
		temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
			>= (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
			(SI_Long)53L) : Nil;
		if (temp);
		else
		    temp = Nil;
		disable_resumability = temp;
		PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
			11);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  10);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			    9);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
			      8);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
				7);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  6);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				    5);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
				      4);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					3);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(G2int_writing_icp_message_group);
				  PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
					  2);
				    gensymed_symbol = Nil;
				    gensymed_symbol_1 = 0.0;
				    gensymed_symbol_1 = 0.0;
				    if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					    &&  
					    !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
						{
					buffer_of_resumable_p = Nil;
					index_of_resumable_p_in_icp_buffer 
						= Nil;
					PUSH_SPECIAL(G2int_index_of_resumable_p_in_icp_buffer,index_of_resumable_p_in_icp_buffer,
						1);
					  PUSH_SPECIAL(G2int_buffer_of_resumable_p,buffer_of_resumable_p,
						  0);
					    if ( 
						    !TRUEP(G2int_disable_resumability)) 
							{
						temp = ISVREF(task,
							(SI_Long)1L);
						if (temp);
						else
						    temp = 
							    g2int_assign_corresponding_icp_object_index(Nil,
							    Qg2int_standard_icp_object_index_space,
							    Nil);
						icp_write_task_index = temp;
						if (ISVREF(task,(SI_Long)4L))
						    g2int_send_icp_start_icp_task(Nil,
							    icp_write_task_index,
							    priority);
						else
						    g2int_send_icp_resume_icp_task(Nil,
							    icp_write_task_index);
					    }
					    SVREF(task,FIX((SI_Long)4L)) = Nil;
					    G2int_starresumable_icp_statestar 
						    = ISVREF(task,(SI_Long)5L);
					    temp = G2int_icp_suspend;
					    temp_1 = length(argument_list);
					    if ( 
						    !(FIXNUM_LE(FIX((SI_Long)-128L),
						    temp_1) && 
						    FIXNUM_LE(temp_1,
						    FIX((SI_Long)127L))))
						temp_1 = Nil;
					    else
						switch (INTEGER_TO_CHAR(temp_1)) 
							    {
						  case 0:
						    temp_1 = 
							    inline_funcall_0(function);
						    break;
						  case 1:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    temp_1 = 
							    inline_funcall_1(gensymed_symbol,
							    gensymed_symbol_2);
						    break;
						  case 2:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    temp_1 = 
							    inline_funcall_2(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3);
						    break;
						  case 3:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    temp_1 = 
							    inline_funcall_3(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4);
						    break;
						  case 4:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    gensymed_symbol_5 = 
							    FOURTH(argument_list);
						    temp_1 = 
							    inline_funcall_4(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4,
							    gensymed_symbol_5);
						    break;
						  case 5:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    gensymed_symbol_5 = 
							    FOURTH(argument_list);
						    gensymed_symbol_6 = 
							    FIFTH(argument_list);
						    temp_1 = 
							    inline_funcall_5(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4,
							    gensymed_symbol_5,
							    gensymed_symbol_6);
						    break;
						  case 6:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    gensymed_symbol_5 = 
							    FOURTH(argument_list);
						    gensymed_symbol_6 = 
							    FIFTH(argument_list);
						    gensymed_symbol_7 = 
							    SIXTH(argument_list);
						    temp_1 = 
							    inline_funcall_6(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4,
							    gensymed_symbol_5,
							    gensymed_symbol_6,
							    gensymed_symbol_7);
						    break;
						  case 7:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    gensymed_symbol_5 = 
							    FOURTH(argument_list);
						    gensymed_symbol_6 = 
							    FIFTH(argument_list);
						    gensymed_symbol_7 = 
							    SIXTH(argument_list);
						    gensymed_symbol_8 = 
							    SEVENTH(argument_list);
						    temp_1 = 
							    inline_funcall_7(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4,
							    gensymed_symbol_5,
							    gensymed_symbol_6,
							    gensymed_symbol_7,
							    gensymed_symbol_8);
						    break;
						  case 8:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    gensymed_symbol_5 = 
							    FOURTH(argument_list);
						    gensymed_symbol_6 = 
							    FIFTH(argument_list);
						    gensymed_symbol_7 = 
							    SIXTH(argument_list);
						    gensymed_symbol_8 = 
							    SEVENTH(argument_list);
						    gensymed_symbol_9 = 
							    EIGHTH(argument_list);
						    temp_1 = 
							    inline_funcall_8(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4,
							    gensymed_symbol_5,
							    gensymed_symbol_6,
							    gensymed_symbol_7,
							    gensymed_symbol_8,
							    gensymed_symbol_9);
						    break;
						  case 9:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    gensymed_symbol_5 = 
							    FOURTH(argument_list);
						    gensymed_symbol_6 = 
							    FIFTH(argument_list);
						    gensymed_symbol_7 = 
							    SIXTH(argument_list);
						    gensymed_symbol_8 = 
							    SEVENTH(argument_list);
						    gensymed_symbol_9 = 
							    EIGHTH(argument_list);
						    gensymed_symbol_10 = 
							    NINTH(argument_list);
						    temp_1 = 
							    inline_funcall_9(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4,
							    gensymed_symbol_5,
							    gensymed_symbol_6,
							    gensymed_symbol_7,
							    gensymed_symbol_8,
							    gensymed_symbol_9,
							    gensymed_symbol_10);
						    break;
						  case 10:
						    gensymed_symbol = function;
						    gensymed_symbol_2 = 
							    FIRST(argument_list);
						    gensymed_symbol_3 = 
							    SECOND(argument_list);
						    gensymed_symbol_4 = 
							    THIRD(argument_list);
						    gensymed_symbol_5 = 
							    FOURTH(argument_list);
						    gensymed_symbol_6 = 
							    FIFTH(argument_list);
						    gensymed_symbol_7 = 
							    SIXTH(argument_list);
						    gensymed_symbol_8 = 
							    SEVENTH(argument_list);
						    gensymed_symbol_9 = 
							    EIGHTH(argument_list);
						    gensymed_symbol_10 = 
							    NINTH(argument_list);
						    gensymed_symbol_11 = 
							    TENTH(argument_list);
						    temp_1 = 
							    inline_funcall_10(gensymed_symbol,
							    gensymed_symbol_2,
							    gensymed_symbol_3,
							    gensymed_symbol_4,
							    gensymed_symbol_5,
							    gensymed_symbol_6,
							    gensymed_symbol_7,
							    gensymed_symbol_8,
							    gensymed_symbol_9,
							    gensymed_symbol_10,
							    gensymed_symbol_11);
						    break;
						  default:
						    temp_1 = Nil;
						    break;
						}
					    suspendp = EQ(temp,temp_1) ? T 
						    : Nil;
					    if (suspendp) {
						svref_new_value = 
							G2int_starresumable_icp_statestar;
						SVREF(task,
							FIX((SI_Long)5L)) 
							= svref_new_value;
						SVREF(task,
							FIX((SI_Long)1L)) 
							= icp_write_task_index;
					    }
					    G2int_starresumable_icp_statestar 
						    = Nil;
					    if (suspendp) {
						array = 
							ISVREF(G2int_buffer_of_resumable_p,
							(SI_Long)4L);
						icp_position = 
							IFIX(G2int_index_of_resumable_p_in_icp_buffer);
						position_1 = icp_position 
							+ icp_position;
						value = (SI_Long)1L;
						temp_2 = value >>  -  - 
							(SI_Long)8L;
						UBYTE_8_ISASET_1(array,
							position_1,temp_2);
						temp_2 = position_1 + 
							(SI_Long)1L;
						gensymed_symbol_12 = 
							(SI_Long)255L & value;
						UBYTE_8_ISASET_1(array,
							temp_2,
							gensymed_symbol_12);
					    }
					  POP_SPECIAL();
					POP_SPECIAL();
					g2int_end_icp_message_group();
				    }
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
	    if (suspendp &&  !TRUEP(G2int_icp_error_suspend_p))
		result = VALUES_1(T);
	    else {
		if (icp_write_task_index) {
		    if (G2int_icp_error_suspend_p) {
			current_icp_socket = ISVREF(G2int_current_icp_port,
				(SI_Long)2L);
			PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,
				12);
			  if (IFIX(ISVREF(G2int_current_icp_socket,
				  (SI_Long)15L)) == (SI_Long)2L) {
			      if (IFIX(ISVREF(G2int_current_icp_socket,
				      (SI_Long)22L)) >= (SI_Long)13L) {
				  current_icp_port = G2int_current_icp_port;
				  PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,
					  11);
				    current_icp_socket = 
					    ISVREF(G2int_current_icp_port,
					    (SI_Long)2L);
				    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,
					    10);
				      temp = 
					      IFIX(ISVREF(G2int_current_icp_socket,
					      (SI_Long)22L)) >= 
					      (SI_Long)17L ? 
					      ISVREF(G2int_current_icp_socket,
					      (SI_Long)53L) : Nil;
				      if (temp);
				      else
					  temp = Nil;
				      disable_resumability = temp;
				      PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
					      9);
					number_of_icp_bytes_for_message_series 
						= FIX((SI_Long)0L);
					PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
						8);
					  icp_buffers_for_message_group = Nil;
					  PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
						  7);
					    icp_buffer_of_start_of_message_series_qm 
						    = Nil;
					    PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
						    6);
					      icp_byte_position_of_start_of_message_series_qm 
						      = Nil;
					      PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
						      5);
						number_of_icp_bytes_to_fill_buffer 
							= FIX((SI_Long)0L);
						PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
							4);
						  current_icp_buffer = Nil;
						  PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
							  3);
						    current_write_icp_byte_position 
							    = Nil;
						    PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
							    2);
						      number_of_icp_bytes_in_message_group 
							      = 
							      FIX((SI_Long)0L);
						      PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
							      1);
							writing_icp_message_group 
								= 
								FIXNUM_ADD1(G2int_writing_icp_message_group);
							PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
								0);
							  gensymed_symbol 
								  = Nil;
							  gensymed_symbol_1 
								  = 0.0;
							  gensymed_symbol_1 
								  = 0.0;
							  if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
								  &&  
								  !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
								      {
							      g2int_send_icp_abort_icp_task(icp_write_task_index);
							      g2int_end_icp_message_group();
							  }
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
			      }
			  }
			POP_SPECIAL();
		    }
		    g2int_deassign_index_in_index_space(icp_write_task_index,
			    ISVREF(G2int_current_icp_port,(SI_Long)8L));
		}
		completion_function = ISVREF(task,(SI_Long)6L);
		completion_argument_list = ISVREF(task,(SI_Long)7L);
		if (completion_function) {
		    temp = length(completion_argument_list);
		    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			    FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 0:
			    inline_funcall_0(completion_function);
			    break;
			  case 1:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    inline_funcall_1(gensymed_symbol,
				    gensymed_symbol_2);
			    break;
			  case 2:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    inline_funcall_2(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3);
			    break;
			  case 3:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    inline_funcall_3(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4);
			    break;
			  case 4:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    gensymed_symbol_5 = 
				    FOURTH(completion_argument_list);
			    inline_funcall_4(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4,gensymed_symbol_5);
			    break;
			  case 5:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    gensymed_symbol_5 = 
				    FOURTH(completion_argument_list);
			    gensymed_symbol_6 = 
				    FIFTH(completion_argument_list);
			    inline_funcall_5(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4,gensymed_symbol_5,
				    gensymed_symbol_6);
			    break;
			  case 6:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    gensymed_symbol_5 = 
				    FOURTH(completion_argument_list);
			    gensymed_symbol_6 = 
				    FIFTH(completion_argument_list);
			    gensymed_symbol_7 = 
				    SIXTH(completion_argument_list);
			    inline_funcall_6(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4,gensymed_symbol_5,
				    gensymed_symbol_6,gensymed_symbol_7);
			    break;
			  case 7:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    gensymed_symbol_5 = 
				    FOURTH(completion_argument_list);
			    gensymed_symbol_6 = 
				    FIFTH(completion_argument_list);
			    gensymed_symbol_7 = 
				    SIXTH(completion_argument_list);
			    gensymed_symbol_8 = 
				    SEVENTH(completion_argument_list);
			    inline_funcall_7(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4,gensymed_symbol_5,
				    gensymed_symbol_6,gensymed_symbol_7,
				    gensymed_symbol_8);
			    break;
			  case 8:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    gensymed_symbol_5 = 
				    FOURTH(completion_argument_list);
			    gensymed_symbol_6 = 
				    FIFTH(completion_argument_list);
			    gensymed_symbol_7 = 
				    SIXTH(completion_argument_list);
			    gensymed_symbol_8 = 
				    SEVENTH(completion_argument_list);
			    gensymed_symbol_9 = 
				    EIGHTH(completion_argument_list);
			    inline_funcall_8(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4,gensymed_symbol_5,
				    gensymed_symbol_6,gensymed_symbol_7,
				    gensymed_symbol_8,gensymed_symbol_9);
			    break;
			  case 9:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    gensymed_symbol_5 = 
				    FOURTH(completion_argument_list);
			    gensymed_symbol_6 = 
				    FIFTH(completion_argument_list);
			    gensymed_symbol_7 = 
				    SIXTH(completion_argument_list);
			    gensymed_symbol_8 = 
				    SEVENTH(completion_argument_list);
			    gensymed_symbol_9 = 
				    EIGHTH(completion_argument_list);
			    gensymed_symbol_10 = 
				    NINTH(completion_argument_list);
			    inline_funcall_9(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4,gensymed_symbol_5,
				    gensymed_symbol_6,gensymed_symbol_7,
				    gensymed_symbol_8,gensymed_symbol_9,
				    gensymed_symbol_10);
			    break;
			  case 10:
			    gensymed_symbol = completion_function;
			    gensymed_symbol_2 = 
				    FIRST(completion_argument_list);
			    gensymed_symbol_3 = 
				    SECOND(completion_argument_list);
			    gensymed_symbol_4 = 
				    THIRD(completion_argument_list);
			    gensymed_symbol_5 = 
				    FOURTH(completion_argument_list);
			    gensymed_symbol_6 = 
				    FIFTH(completion_argument_list);
			    gensymed_symbol_7 = 
				    SIXTH(completion_argument_list);
			    gensymed_symbol_8 = 
				    SEVENTH(completion_argument_list);
			    gensymed_symbol_9 = 
				    EIGHTH(completion_argument_list);
			    gensymed_symbol_10 = 
				    NINTH(completion_argument_list);
			    gensymed_symbol_11 = 
				    TENTH(completion_argument_list);
			    inline_funcall_10(gensymed_symbol,
				    gensymed_symbol_2,gensymed_symbol_3,
				    gensymed_symbol_4,gensymed_symbol_5,
				    gensymed_symbol_6,gensymed_symbol_7,
				    gensymed_symbol_8,gensymed_symbol_9,
				    gensymed_symbol_10,gensymed_symbol_11);
			    break;
			  default:
			    break;
			}
		}
		g2int_reclaim_gensym_list_1(argument_list);
		g2int_reclaim_gensym_list_1(completion_argument_list);
		result = VALUES_1(Nil);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qg2int_not_open;     /* not-open */

static Object Qg2int_blocked;      /* blocked */

static Object Qg2int_time_slice_expired;  /* time-slice-expired */

/* ICP-WRITE-TASK-NOT-ALLOWED-TO-WRITE-P */
Object g2int_icp_write_task_not_allowed_to_write_p(there_is_a_scheduler_qm,
	    check_time_slice_p)
    Object there_is_a_scheduler_qm, check_time_slice_p;
{
    Object current_icp_socket, temp;
    Declare_special(1);

    x_note_fn_call(42,131);
    current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,0);
      if ( !TRUEP(g2int_icp_connection_open_p(G2int_current_icp_socket)))
	  temp = Qg2int_not_open;
      else if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
	      (SI_Long)17L ? TRUEP(ISVREF(G2int_current_icp_socket,
	      (SI_Long)53L)) : TRUEP(Nil))
	  temp = Nil;
      else if (ISVREF(G2int_current_icp_port,(SI_Long)4L))
	  temp = Qg2int_blocked;
      else if (there_is_a_scheduler_qm && check_time_slice_p && 
	      g2int_time_slice_expired_p())
	  temp = Qg2int_time_slice_expired;
      else
	  temp = Qnil;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qg2int_ab;           /* ab */

/* SEND-OR-ENQUEUE-ICP-WRITE-TASK */
Object g2int_send_or_enqueue_icp_write_task(icp_output_port,priority,
	    function,argument_list,completion_function,
	    completion_argument_list)
    Object icp_output_port, priority, function, argument_list;
    Object completion_function, completion_argument_list;
{
    Object resumable_icp_state_1, corresponding_object_index_1;
    Object current_icp_port, icp_socket, startp, check_time_slice_p;
    Object resumable_icp_state, current_icp_socket;
    Object writing_resumable_icp_messages_p, icp_write_task_index;
    Object icp_error_suspend_p, suspendp, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, buffer_of_resumable_p;
    Object index_of_resumable_p_in_icp_buffer, temp_2, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6, gensymed_symbol_7, gensymed_symbol_8;
    Object gensymed_symbol_9, gensymed_symbol_10, gensymed_symbol_11, array;
    SI_Long icp_position, position_1, value, temp_3, gensymed_symbol_12;
    char there_is_a_scheduler_qm, temp;
    double gensymed_symbol_1;
    Declare_special(19);
    Object result;

    x_note_fn_call(42,132);
    resumable_icp_state_1 = Nil;
    corresponding_object_index_1 = Nil;
    current_icp_port = icp_output_port;
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    startp = T;
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,18);
      g2int_ensure_icp_write_callback(icp_socket);
      there_is_a_scheduler_qm = EQ(G2int_current_system_name,Qg2int_ab);
      check_time_slice_p = Nil;
    next_loop:
      if (g2int_icp_write_task_not_allowed_to_write_p(there_is_a_scheduler_qm 
	      ? T : Nil,check_time_slice_p)) {
	  temp = TRUEP(T);
	  goto end;
      }
      resumable_icp_state = Nil;
      PUSH_SPECIAL(G2int_starresumable_icp_statestar,resumable_icp_state,17);
	current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,16);
	  writing_resumable_icp_messages_p =  
		  !(IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		  (SI_Long)17L ? TRUEP(ISVREF(G2int_current_icp_socket,
		  (SI_Long)53L)) : TRUEP(Nil)) ? T : Nil;
	  PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		  15);
	    icp_write_task_index = Nil;
	    icp_error_suspend_p = Nil;
	    PUSH_SPECIAL(G2int_icp_error_suspend_p,icp_error_suspend_p,14);
	      suspendp = Nil;
	      current_icp_port = G2int_current_icp_port;
	      PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,13);
		current_icp_socket = ISVREF(G2int_current_icp_port,
			(SI_Long)2L);
		PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,12);
		  temp_1 = IFIX(ISVREF(G2int_current_icp_socket,
			  (SI_Long)22L)) >= (SI_Long)17L ? 
			  ISVREF(G2int_current_icp_socket,(SI_Long)53L) : Nil;
		  if (temp_1);
		  else
		      temp_1 = Nil;
		  disable_resumability = temp_1;
		  PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
			  11);
		    number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		    PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			    10);
		      icp_buffers_for_message_group = Nil;
		      PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			      9);
			icp_buffer_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
				8);
			  icp_byte_position_of_start_of_message_series_qm 
				  = Nil;
			  PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
				  7);
			    number_of_icp_bytes_to_fill_buffer = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				    6);
			      current_icp_buffer = Nil;
			      PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				      5);
				current_write_icp_byte_position = Nil;
				PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
					4);
				  number_of_icp_bytes_in_message_group = 
					  FIX((SI_Long)0L);
				  PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					  3);
				    writing_icp_message_group = 
					    FIXNUM_ADD1(G2int_writing_icp_message_group);
				    PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
					    2);
				      gensymed_symbol = Nil;
				      gensymed_symbol_1 = 0.0;
				      gensymed_symbol_1 = 0.0;
				      if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					      &&  
					      !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
						  {
					  buffer_of_resumable_p = Nil;
					  index_of_resumable_p_in_icp_buffer 
						  = Nil;
					  PUSH_SPECIAL(G2int_index_of_resumable_p_in_icp_buffer,index_of_resumable_p_in_icp_buffer,
						  1);
					    PUSH_SPECIAL(G2int_buffer_of_resumable_p,buffer_of_resumable_p,
						    0);
					      if ( 
						      !TRUEP(G2int_disable_resumability)) 
							  {
						  temp_1 = 
							  corresponding_object_index_1;
						  if (temp_1);
						  else
						      temp_1 = 
							      g2int_assign_corresponding_icp_object_index(Nil,
							      Qg2int_standard_icp_object_index_space,
							      Nil);
						  icp_write_task_index = 
							  temp_1;
						  if (startp)
						      g2int_send_icp_start_icp_task(Nil,
							      icp_write_task_index,
							      priority);
						  else
						      g2int_send_icp_resume_icp_task(Nil,
							      icp_write_task_index);
					      }
					      startp = Nil;
					      G2int_starresumable_icp_statestar 
						      = resumable_icp_state_1;
					      temp_1 = G2int_icp_suspend;
					      temp_2 = length(argument_list);
					      if ( 
						      !(FIXNUM_LE(FIX((SI_Long)-128L),
						      temp_2) && 
						      FIXNUM_LE(temp_2,
						      FIX((SI_Long)127L))))
						  temp_2 = Nil;
					      else
						  switch (INTEGER_TO_CHAR(temp_2)) 
							      {
						    case 0:
						      temp_2 = 
							      inline_funcall_0(function);
						      break;
						    case 1:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      temp_2 = 
							      inline_funcall_1(gensymed_symbol,
							      gensymed_symbol_2);
						      break;
						    case 2:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      temp_2 = 
							      inline_funcall_2(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3);
						      break;
						    case 3:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      temp_2 = 
							      inline_funcall_3(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4);
						      break;
						    case 4:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      gensymed_symbol_5 = 
							      FOURTH(argument_list);
						      temp_2 = 
							      inline_funcall_4(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4,
							      gensymed_symbol_5);
						      break;
						    case 5:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      gensymed_symbol_5 = 
							      FOURTH(argument_list);
						      gensymed_symbol_6 = 
							      FIFTH(argument_list);
						      temp_2 = 
							      inline_funcall_5(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4,
							      gensymed_symbol_5,
							      gensymed_symbol_6);
						      break;
						    case 6:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      gensymed_symbol_5 = 
							      FOURTH(argument_list);
						      gensymed_symbol_6 = 
							      FIFTH(argument_list);
						      gensymed_symbol_7 = 
							      SIXTH(argument_list);
						      temp_2 = 
							      inline_funcall_6(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4,
							      gensymed_symbol_5,
							      gensymed_symbol_6,
							      gensymed_symbol_7);
						      break;
						    case 7:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      gensymed_symbol_5 = 
							      FOURTH(argument_list);
						      gensymed_symbol_6 = 
							      FIFTH(argument_list);
						      gensymed_symbol_7 = 
							      SIXTH(argument_list);
						      gensymed_symbol_8 = 
							      SEVENTH(argument_list);
						      temp_2 = 
							      inline_funcall_7(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4,
							      gensymed_symbol_5,
							      gensymed_symbol_6,
							      gensymed_symbol_7,
							      gensymed_symbol_8);
						      break;
						    case 8:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      gensymed_symbol_5 = 
							      FOURTH(argument_list);
						      gensymed_symbol_6 = 
							      FIFTH(argument_list);
						      gensymed_symbol_7 = 
							      SIXTH(argument_list);
						      gensymed_symbol_8 = 
							      SEVENTH(argument_list);
						      gensymed_symbol_9 = 
							      EIGHTH(argument_list);
						      temp_2 = 
							      inline_funcall_8(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4,
							      gensymed_symbol_5,
							      gensymed_symbol_6,
							      gensymed_symbol_7,
							      gensymed_symbol_8,
							      gensymed_symbol_9);
						      break;
						    case 9:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      gensymed_symbol_5 = 
							      FOURTH(argument_list);
						      gensymed_symbol_6 = 
							      FIFTH(argument_list);
						      gensymed_symbol_7 = 
							      SIXTH(argument_list);
						      gensymed_symbol_8 = 
							      SEVENTH(argument_list);
						      gensymed_symbol_9 = 
							      EIGHTH(argument_list);
						      gensymed_symbol_10 = 
							      NINTH(argument_list);
						      temp_2 = 
							      inline_funcall_9(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4,
							      gensymed_symbol_5,
							      gensymed_symbol_6,
							      gensymed_symbol_7,
							      gensymed_symbol_8,
							      gensymed_symbol_9,
							      gensymed_symbol_10);
						      break;
						    case 10:
						      gensymed_symbol = 
							      function;
						      gensymed_symbol_2 = 
							      FIRST(argument_list);
						      gensymed_symbol_3 = 
							      SECOND(argument_list);
						      gensymed_symbol_4 = 
							      THIRD(argument_list);
						      gensymed_symbol_5 = 
							      FOURTH(argument_list);
						      gensymed_symbol_6 = 
							      FIFTH(argument_list);
						      gensymed_symbol_7 = 
							      SIXTH(argument_list);
						      gensymed_symbol_8 = 
							      SEVENTH(argument_list);
						      gensymed_symbol_9 = 
							      EIGHTH(argument_list);
						      gensymed_symbol_10 = 
							      NINTH(argument_list);
						      gensymed_symbol_11 = 
							      TENTH(argument_list);
						      temp_2 = 
							      inline_funcall_10(gensymed_symbol,
							      gensymed_symbol_2,
							      gensymed_symbol_3,
							      gensymed_symbol_4,
							      gensymed_symbol_5,
							      gensymed_symbol_6,
							      gensymed_symbol_7,
							      gensymed_symbol_8,
							      gensymed_symbol_9,
							      gensymed_symbol_10,
							      gensymed_symbol_11);
						      break;
						    default:
						      temp_2 = Nil;
						      break;
						  }
					      suspendp = EQ(temp_1,temp_2) 
						      ? T : Nil;
					      if (suspendp) {
						  resumable_icp_state_1 = 
							  G2int_starresumable_icp_statestar;
						  corresponding_object_index_1 
							  = 
							  icp_write_task_index;
					      }
					      G2int_starresumable_icp_statestar 
						      = Nil;
					      if (suspendp) {
						  array = 
							  ISVREF(G2int_buffer_of_resumable_p,
							  (SI_Long)4L);
						  icp_position = 
							  IFIX(G2int_index_of_resumable_p_in_icp_buffer);
						  position_1 = 
							  icp_position + 
							  icp_position;
						  value = (SI_Long)1L;
						  temp_3 = value >>  -  - 
							  (SI_Long)8L;
						  UBYTE_8_ISASET_1(array,
							  position_1,temp_3);
						  temp_3 = position_1 + 
							  (SI_Long)1L;
						  gensymed_symbol_12 = 
							  (SI_Long)255L & 
							  value;
						  UBYTE_8_ISASET_1(array,
							  temp_3,
							  gensymed_symbol_12);
					      }
					    POP_SPECIAL();
					  POP_SPECIAL();
					  g2int_end_icp_message_group();
				      }
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
	      if (suspendp &&  !TRUEP(G2int_icp_error_suspend_p))
		  temp = TRUEP(T);
	      else {
		  if (icp_write_task_index) {
		      if (G2int_icp_error_suspend_p) {
			  current_icp_socket = 
				  ISVREF(G2int_current_icp_port,(SI_Long)2L);
			  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,
				  12);
			    if (IFIX(ISVREF(G2int_current_icp_socket,
				    (SI_Long)15L)) == (SI_Long)2L) {
				if (IFIX(ISVREF(G2int_current_icp_socket,
					(SI_Long)22L)) >= (SI_Long)13L) {
				    current_icp_port = G2int_current_icp_port;
				    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,
					    11);
				      current_icp_socket = 
					      ISVREF(G2int_current_icp_port,
					      (SI_Long)2L);
				      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,
					      10);
					temp_1 = 
						IFIX(ISVREF(G2int_current_icp_socket,
						(SI_Long)22L)) >= 
						(SI_Long)17L ? 
						ISVREF(G2int_current_icp_socket,
						(SI_Long)53L) : Nil;
					if (temp_1);
					else
					    temp_1 = Nil;
					disable_resumability = temp_1;
					PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
						9);
					  number_of_icp_bytes_for_message_series 
						  = FIX((SI_Long)0L);
					  PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
						  8);
					    icp_buffers_for_message_group 
						    = Nil;
					    PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
						    7);
					      icp_buffer_of_start_of_message_series_qm 
						      = Nil;
					      PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
						      6);
						icp_byte_position_of_start_of_message_series_qm 
							= Nil;
						PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
							5);
						  number_of_icp_bytes_to_fill_buffer 
							  = FIX((SI_Long)0L);
						  PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
							  4);
						    current_icp_buffer = Nil;
						    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
							    3);
						      current_write_icp_byte_position 
							      = Nil;
						      PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
							      2);
							number_of_icp_bytes_in_message_group 
								= 
								FIX((SI_Long)0L);
							PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
								1);
							  writing_icp_message_group 
								  = 
								  FIXNUM_ADD1(G2int_writing_icp_message_group);
							  PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
								  0);
							    gensymed_symbol 
								    = Nil;
							    gensymed_symbol_1 
								    = 0.0;
							    gensymed_symbol_1 
								    = 0.0;
							    if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
								    &&  
								    !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
									{
								g2int_send_icp_abort_icp_task(icp_write_task_index);
								g2int_end_icp_message_group();
							    }
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
				}
			    }
			  POP_SPECIAL();
		      }
		      g2int_deassign_index_in_index_space(icp_write_task_index,
			      ISVREF(G2int_current_icp_port,(SI_Long)8L));
		  }
		  if (completion_function) {
		      temp_1 = length(completion_argument_list);
		      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 0:
			      inline_funcall_0(completion_function);
			      break;
			    case 1:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      inline_funcall_1(gensymed_symbol,
				      gensymed_symbol_2);
			      break;
			    case 2:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      inline_funcall_2(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3);
			      break;
			    case 3:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      inline_funcall_3(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4);
			      break;
			    case 4:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      gensymed_symbol_5 = 
				      FOURTH(completion_argument_list);
			      inline_funcall_4(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4,gensymed_symbol_5);
			      break;
			    case 5:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      gensymed_symbol_5 = 
				      FOURTH(completion_argument_list);
			      gensymed_symbol_6 = 
				      FIFTH(completion_argument_list);
			      inline_funcall_5(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4,gensymed_symbol_5,
				      gensymed_symbol_6);
			      break;
			    case 6:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      gensymed_symbol_5 = 
				      FOURTH(completion_argument_list);
			      gensymed_symbol_6 = 
				      FIFTH(completion_argument_list);
			      gensymed_symbol_7 = 
				      SIXTH(completion_argument_list);
			      inline_funcall_6(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4,gensymed_symbol_5,
				      gensymed_symbol_6,gensymed_symbol_7);
			      break;
			    case 7:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      gensymed_symbol_5 = 
				      FOURTH(completion_argument_list);
			      gensymed_symbol_6 = 
				      FIFTH(completion_argument_list);
			      gensymed_symbol_7 = 
				      SIXTH(completion_argument_list);
			      gensymed_symbol_8 = 
				      SEVENTH(completion_argument_list);
			      inline_funcall_7(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4,gensymed_symbol_5,
				      gensymed_symbol_6,gensymed_symbol_7,
				      gensymed_symbol_8);
			      break;
			    case 8:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      gensymed_symbol_5 = 
				      FOURTH(completion_argument_list);
			      gensymed_symbol_6 = 
				      FIFTH(completion_argument_list);
			      gensymed_symbol_7 = 
				      SIXTH(completion_argument_list);
			      gensymed_symbol_8 = 
				      SEVENTH(completion_argument_list);
			      gensymed_symbol_9 = 
				      EIGHTH(completion_argument_list);
			      inline_funcall_8(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4,gensymed_symbol_5,
				      gensymed_symbol_6,gensymed_symbol_7,
				      gensymed_symbol_8,gensymed_symbol_9);
			      break;
			    case 9:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      gensymed_symbol_5 = 
				      FOURTH(completion_argument_list);
			      gensymed_symbol_6 = 
				      FIFTH(completion_argument_list);
			      gensymed_symbol_7 = 
				      SIXTH(completion_argument_list);
			      gensymed_symbol_8 = 
				      SEVENTH(completion_argument_list);
			      gensymed_symbol_9 = 
				      EIGHTH(completion_argument_list);
			      gensymed_symbol_10 = 
				      NINTH(completion_argument_list);
			      inline_funcall_9(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4,gensymed_symbol_5,
				      gensymed_symbol_6,gensymed_symbol_7,
				      gensymed_symbol_8,gensymed_symbol_9,
				      gensymed_symbol_10);
			      break;
			    case 10:
			      gensymed_symbol = completion_function;
			      gensymed_symbol_2 = 
				      FIRST(completion_argument_list);
			      gensymed_symbol_3 = 
				      SECOND(completion_argument_list);
			      gensymed_symbol_4 = 
				      THIRD(completion_argument_list);
			      gensymed_symbol_5 = 
				      FOURTH(completion_argument_list);
			      gensymed_symbol_6 = 
				      FIFTH(completion_argument_list);
			      gensymed_symbol_7 = 
				      SIXTH(completion_argument_list);
			      gensymed_symbol_8 = 
				      SEVENTH(completion_argument_list);
			      gensymed_symbol_9 = 
				      EIGHTH(completion_argument_list);
			      gensymed_symbol_10 = 
				      NINTH(completion_argument_list);
			      gensymed_symbol_11 = 
				      TENTH(completion_argument_list);
			      inline_funcall_10(gensymed_symbol,
				      gensymed_symbol_2,gensymed_symbol_3,
				      gensymed_symbol_4,gensymed_symbol_5,
				      gensymed_symbol_6,gensymed_symbol_7,
				      gensymed_symbol_8,gensymed_symbol_9,
				      gensymed_symbol_10,gensymed_symbol_11);
			      break;
			    default:
			      break;
			  }
		  }
		  g2int_reclaim_gensym_list_1(argument_list);
		  g2int_reclaim_gensym_list_1(completion_argument_list);
		  temp = TRUEP(Nil);
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      if ( !temp) {
	  temp = TRUEP(Nil);
	  goto end;
      }
      check_time_slice_p = T;
      goto next_loop;
    end_loop:
      temp = TRUEP(Qnil);
    end:;
      if (temp)
	  result = g2int_enqueue_icp_write_task(icp_output_port,priority,
		  corresponding_object_index_1,function,argument_list,
		  startp,resumable_icp_state_1,completion_function,
		  completion_argument_list);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2int_resumable_icp_write_callback;  /* resumable-icp-write-callback */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* ENQUEUE-ICP-WRITE-TASK */
Object g2int_enqueue_icp_write_task(icp_output_port,priority,
	    corresponding_object_index_1,function,argument_list,startp,
	    resumable_icp_state_1,completion_function,completion_argument_list)
    Object icp_output_port, priority, corresponding_object_index_1, function;
    Object argument_list, startp, resumable_icp_state_1, completion_function;
    Object completion_argument_list;
{
    Object icp_socket, queue_vector, queue, task, gensymed_symbol;
    Object def_structure_queue_element_variable, gensymed_symbol_1;
    Object current_task_schedule_modify_arg_2;
    Object current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11, schedule_task_qm;
    Object old_structure_being_reclaimed, temp;
    Object def_structure_schedule_task_variable, task_1, ctask, p, v, q;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(42,133);
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    queue_vector = ISVREF(icp_socket,(SI_Long)37L);
    if (queue_vector);
    else {
	queue_vector = g2int_make_resumable_icp_output_task_queue_vector();
	SVREF(icp_socket,FIX((SI_Long)37L)) = queue_vector;
    }
    queue = ISVREF(queue_vector,IFIX(priority));
    if (queue);
    else {
	queue = g2int_make_empty_constant_queue();
	SVREF(queue_vector,priority) = queue;
    }
    task = g2int_make_icp_write_task_1(corresponding_object_index_1,
	    function,argument_list,startp,resumable_icp_state_1,
	    completion_function,completion_argument_list);
    gensymed_symbol = ISVREF(queue,(SI_Long)1L);
    def_structure_queue_element_variable = 
	    G2int_chain_of_available_queue_elements;
    if (def_structure_queue_element_variable)
	G2int_chain_of_available_queue_elements = 
		ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
    else
	def_structure_queue_element_variable = 
		g2int_make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = queue;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
	    gensymed_symbol;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
    gensymed_symbol_1 = def_structure_queue_element_variable;
    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
    SVREF(queue,FIX((SI_Long)1L)) = gensymed_symbol_1;
    if ( !TRUEP(ISVREF(G2int_current_icp_port,(SI_Long)4L))) {
	current_task_schedule_modify_arg_2 = priority;
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_resumable_icp_write_callback);
	current_task_schedule_modify_arg_11 = icp_socket;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)38L);
	if (schedule_task_qm) {
	    if (EQ(schedule_task_qm,G2int_current_schedule_task))
		G2int_current_schedule_task = Nil;
	    if (ISVREF(schedule_task_qm,(SI_Long)6L))
		g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	    inline_note_reclaim_cons(schedule_task_qm,Nil);
	    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	    G2int_structure_being_reclaimed = schedule_task_qm;
	    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
		    (SI_Long)9L));
	    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	    temp = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	def_structure_schedule_task_variable = 
		G2int_chain_of_available_schedule_tasks;
	if (def_structure_schedule_task_variable) {
	    G2int_chain_of_available_schedule_tasks = 
		    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    g2int_make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task_1 = def_structure_schedule_task_variable;
	temp = ISVREF(task_1,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	SVREF(task_1,FIX((SI_Long)4L)) = current_task_schedule_modify_arg_2;
	SVREF(task_1,FIX((SI_Long)5L)) = Nil;
	SVREF(task_1,FIX((SI_Long)9L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task_1,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task_1,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? G2int_current_g2_time : 
		G2int_current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task_1,FIX((SI_Long)7L)) = Qg2int_resumable_icp_write_callback;
	SVREF(task_1,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
	ISVREF(task_1,(SI_Long)10L) = FIX((SI_Long)2L);
	SVREF(task_1,FIX((SI_Long)11L)) = current_task_schedule_modify_arg_11;
	SVREF(task_1,FIX((SI_Long)12L)) = T;
	ctask =  !TRUEP(ISVREF(task_1,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = G2int_system_is_running;
	p = ISVREF(task_1,(SI_Long)4L);
	v = ctask ? G2int_current_task_queue_vector : 
		G2int_deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	gensymed_symbol = ISVREF(q,(SI_Long)1L);
	def_structure_queue_element_variable = 
		G2int_chain_of_available_queue_elements;
	if (def_structure_queue_element_variable)
	    G2int_chain_of_available_queue_elements = 
		    ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
	else
	    def_structure_queue_element_variable = 
		    g2int_make_permanent_queue_element_structure_internal();
	inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = q;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
		gensymed_symbol;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task_1;
	gensymed_symbol_1 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
	SVREF(task_1,FIX((SI_Long)6L)) = gensymed_symbol_1;
	if (ctask && FIXNUM_LT(p,G2int_priority_of_next_task))
	    G2int_priority_of_next_task = p;
	SVREF(icp_socket,FIX((SI_Long)38L)) = task_1;
    }
    return VALUES_1(task);
}

/* RESUMABLE-ICP-WRITE-CALLBACK */
Object g2int_resumable_icp_write_callback(icp_socket,writable_qm)
    Object icp_socket, writable_qm;
{
    Object current_icp_port, queue_vector, queue_qm, current_task_qm;
    Object gensymed_symbol, temp, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    Object def_structure_queue_element_variable;
    Object current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11, schedule_task_qm;
    Object old_structure_being_reclaimed, def_structure_schedule_task_variable;
    Object task, ctask, p, v, q;
    SI_Long priority, current_task_schedule_modify_arg_2;
    char there_is_a_scheduler_qm, temp_2, g2_p;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(42,134);
    if (writable_qm) {
	there_is_a_scheduler_qm = EQ(G2int_current_system_name,Qg2int_ab);
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,0);
	  queue_vector = ISVREF(icp_socket,(SI_Long)37L);
	  if (queue_vector);
	  else {
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_resumable_icp_write_callback;
	  }
	  priority = IFIX(G2int_highest_system_priority);
	next_loop:
	  if (priority > IFIX(G2int_lowest_system_priority))
	      goto end_loop;
	  queue_qm = ISVREF(queue_vector,priority);
	  current_task_qm = Nil;
	next_loop_1:
	  if (queue_qm) {
	      gensymed_symbol = ISVREF(queue_qm,(SI_Long)0L);
	      if (EQ(gensymed_symbol,queue_qm)) {
		  temp = Nil;
		  current_task_qm = temp;
	      }
	      else {
		  gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		  gensymed_symbol_2 = ISVREF(gensymed_symbol,(SI_Long)0L);
		  SVREF(queue_qm,FIX((SI_Long)0L)) = gensymed_symbol_2;
		  SVREF(gensymed_symbol_2,FIX((SI_Long)1L)) = queue_qm;
		  inline_note_reclaim_cons(gensymed_symbol,Nil);
		  temp_1 = G2int_chain_of_available_queue_elements;
		  SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
		  G2int_chain_of_available_queue_elements = gensymed_symbol;
		  temp = gensymed_symbol_1;
		  current_task_qm = temp;
	      }
	  }
	  else
	      current_task_qm = Nil;
	  if ( !TRUEP(current_task_qm)) {
	      temp_2 = TRUEP(Nil);
	      goto end;
	  }
	  if (g2int_run_resumable_icp_write_task(current_task_qm,
		  FIX(priority))) {
	      gensymed_symbol = ISVREF(queue_qm,(SI_Long)1L);
	      def_structure_queue_element_variable = 
		      G2int_chain_of_available_queue_elements;
	      if (def_structure_queue_element_variable)
		  G2int_chain_of_available_queue_elements = 
			  ISVREF(def_structure_queue_element_variable,
			  (SI_Long)0L);
	      else
		  def_structure_queue_element_variable = 
			  g2int_make_permanent_queue_element_structure_internal();
	      inline_note_allocate_cons(def_structure_queue_element_variable,
		      Nil);
	      SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) 
		      = queue_qm;
	      SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) 
		      = gensymed_symbol;
	      SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) 
		      = current_task_qm;
	      gensymed_symbol_1 = def_structure_queue_element_variable;
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	      SVREF(queue_qm,FIX((SI_Long)1L)) = gensymed_symbol_1;
	  }
	  else
	      g2int_reclaim_icp_write_task_1(current_task_qm);
	  if (g2int_icp_write_task_not_allowed_to_write_p(there_is_a_scheduler_qm 
		  ? T : Nil,T)) {
	      temp_2 = TRUEP(T);
	      goto end;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_2 = TRUEP(Qnil);
	end:;
	  if (temp_2) {
	      if ( !TRUEP(ISVREF(G2int_current_icp_port,(SI_Long)4L))) {
		  current_task_schedule_modify_arg_2 = priority;
		  current_task_schedule_modify_arg_8 = 
			  SYMBOL_FUNCTION(Qg2int_resumable_icp_write_callback);
		  current_task_schedule_modify_arg_11 = icp_socket;
		  schedule_task_qm = ISVREF(icp_socket,(SI_Long)38L);
		  if (schedule_task_qm) {
		      if (EQ(schedule_task_qm,G2int_current_schedule_task))
			  G2int_current_schedule_task = Nil;
		      if (ISVREF(schedule_task_qm,(SI_Long)6L))
			  g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		      inline_note_reclaim_cons(schedule_task_qm,Nil);
		      old_structure_being_reclaimed = 
			      G2int_structure_being_reclaimed;
		      G2int_structure_being_reclaimed = schedule_task_qm;
		      g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
			      (SI_Long)9L));
		      SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
		      G2int_structure_being_reclaimed = 
			      old_structure_being_reclaimed;
		      temp_1 = G2int_chain_of_available_schedule_tasks;
		      SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp_1;
		      G2int_chain_of_available_schedule_tasks = 
			      schedule_task_qm;
		  }
		  def_structure_schedule_task_variable = 
			  G2int_chain_of_available_schedule_tasks;
		  if (def_structure_schedule_task_variable) {
		      G2int_chain_of_available_schedule_tasks = 
			      ISVREF(def_structure_schedule_task_variable,
			      (SI_Long)0L);
		      SVREF(def_structure_schedule_task_variable,
			      FIX((SI_Long)0L)) = 
			      Qg2_defstruct_structure_name_schedule_task_g2_struct;
		  }
		  else
		      def_structure_schedule_task_variable = 
			      g2int_make_permanent_schedule_task_structure_internal();
		  inline_note_allocate_cons(def_structure_schedule_task_variable,
			  Nil);
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)2L)) = Nil;
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)9L)) = Nil;
		  task = def_structure_schedule_task_variable;
		  temp_1 = ISVREF(task,(SI_Long)1L);
		  aref_new_value = -1.0;
		  DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
		  ISVREF(task,(SI_Long)4L) = 
			  FIX(current_task_schedule_modify_arg_2);
		  SVREF(task,FIX((SI_Long)5L)) = Nil;
		  SVREF(task,FIX((SI_Long)9L)) = Nil;
		  g2_p =  !TRUEP(T);
		  SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		  temp_1 = ISVREF(task,(SI_Long)1L);
		  aref_new_value = DFLOAT_ISAREF_1(g2_p ? 
			  G2int_current_g2_time : G2int_current_real_time,
			  (SI_Long)0L);
		  DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		  SVREF(task,FIX((SI_Long)7L)) = 
			  Qg2int_resumable_icp_write_callback;
		  SVREF(task,FIX((SI_Long)8L)) = 
			  current_task_schedule_modify_arg_8;
		  ISVREF(task,(SI_Long)10L) = FIX((SI_Long)2L);
		  SVREF(task,FIX((SI_Long)11L)) = 
			  current_task_schedule_modify_arg_11;
		  SVREF(task,FIX((SI_Long)12L)) = T;
		  ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		  if (ctask);
		  else
		      ctask = G2int_system_is_running;
		  p = ISVREF(task,(SI_Long)4L);
		  v = ctask ? G2int_current_task_queue_vector : 
			  G2int_deferred_task_queue_vector;
		  q = ISVREF(v,IFIX(p));
		  gensymed_symbol = ISVREF(q,(SI_Long)1L);
		  def_structure_queue_element_variable = 
			  G2int_chain_of_available_queue_elements;
		  if (def_structure_queue_element_variable)
		      G2int_chain_of_available_queue_elements = 
			      ISVREF(def_structure_queue_element_variable,
			      (SI_Long)0L);
		  else
		      def_structure_queue_element_variable = 
			      g2int_make_permanent_queue_element_structure_internal();
		  inline_note_allocate_cons(def_structure_queue_element_variable,
			  Nil);
		  SVREF(def_structure_queue_element_variable,
			  FIX((SI_Long)0L)) = q;
		  SVREF(def_structure_queue_element_variable,
			  FIX((SI_Long)1L)) = gensymed_symbol;
		  SVREF(def_structure_queue_element_variable,
			  FIX((SI_Long)2L)) = task;
		  gensymed_symbol_1 = def_structure_queue_element_variable;
		  SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
		  SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
		  SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_1;
		  if (ctask && FIXNUM_LT(p,G2int_priority_of_next_task))
		      G2int_priority_of_next_task = p;
		  SVREF(icp_socket,FIX((SI_Long)38L)) = task;
	      }
	      goto end_loop;
	  }
	  priority = priority + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  temp = Qnil;
	POP_SPECIAL();
    }
    else
	temp = Nil;
    result = VALUES_1(temp);
  end_resumable_icp_write_callback:
    return result;
}

/* ENSURE-ICP-WRITE-CALLBACK */
Object g2int_ensure_icp_write_callback(icp_socket)
    Object icp_socket;
{
    Object temp;
    char temp_1;

    x_note_fn_call(42,135);
    temp = ISVREF(icp_socket,(SI_Long)13L);
    if (CDR(temp)) {
	temp = ISVREF(icp_socket,(SI_Long)13L);
	temp_1 = 
		TRUEP(g2int_memq_function(Qg2int_resumable_icp_write_callback,
		CDR(temp)));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	error((SI_Long)1L,"bad write callback");
    if (ISVREF(icp_socket,(SI_Long)13L)) {
	temp = ISVREF(icp_socket,(SI_Long)13L);
	temp_1 = EQ(Qg2int_resumable_icp_write_callback,CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	g2int_register_icp_write_callback(Qg2int_resumable_icp_write_callback,
		icp_socket);
    return VALUES_1(T);
}

void int3a_INIT()
{
    Object temp, reclaim_structure_for_symbol_tree;
    Object reclaim_structure_for_interned_list;
    Object reclaim_structure_for_icp_read_task;
    Object reclaim_structure_for_icp_write_task;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, AB_package;
    Object Qg2int_icp_write_task, Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_icp_write_task_count;
    Object Qg2int_chain_of_available_icp_write_tasks;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_13, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object Qg2int_handle_icp_abort_icp_task, Qg2int_handle_icp_resume_icp_task;
    Object Qg2int_handle_icp_start_icp_task, Qg2int_icp_read_task;
    Object Qg2int_icp_read_task_count;
    Object Qg2int_chain_of_available_icp_read_tasks, string_constant_12;
    Object Qg2int_reclaim_icp_port_entry_for_interned_list;
    Object Qg2int_interned_list, list_constant_1;
    Object Qg2int_interned_list__corresponding_icp_object_map;
    Object Qg2int_intern_list, Qg2int_interned_list_count;
    Object Qg2int_chain_of_available_interned_lists, string_constant_11;
    Object Qg2int_symbol_tree, Qg2int_symbol_tree_count;
    Object Qg2int_chain_of_available_symbol_trees, string_constant_10;
    Object Qg2int_int3a, Qg2int_object_map_plist_for_icp_tree;
    Object Qg2int_reclaim_icp_port_entry_for_symbol, list_constant;
    Object Qg2int_equivalent_icp_value_type, Qg2int_unsigned_integer;
    Object Qg2int_corresponding_icp_object_index, Qg2int_icp_value_reclaimer;
    Object Qg2int_reclaim_gensym_string, Qg2int_raw_gensym_string;
    Object Qg2int_gensym_string, Qg2int_reclaim_text_string;
    Object Qg2int_text_string, Qg2int_reclaim_gensym_list;
    Object Qg2int_list_of_integers, Qg2int_list_of_unsigned_integers;
    Object Qg2int_index_space_remote_procedure_name;
    Object Qg2int_icp_tree_interned_list_type_tag;
    Object Qg2int_list_element_cons_type_tag;
    Object Qg2int_list_element_list_type_tag;
    Object Qg2int_list_element_text_type_tag;
    Object Qg2int_list_element_symbol_type_tag;
    Object Qg2int_list_element_integer_type_tag;
    Object Qg2int_list_element_null_type_tag, Qg2int_gsi_wide_string_type_tag;
    Object Qg2int_gsi_gensym_string_type_tag;
    Object Qg2int_gsi_typed_sequence_type_tag;
    Object Qg2int_rpc_new_item_copy_with_handle, Qg2int_rpc_new_item_copy;
    Object Qg2int_rpc_existing_item_copy;
    Object Qg2int_rpc_new_item_copy_with_reference;
    Object Qg2int_rpc_handle_for_new_sending_side_object_type_tag;
    Object Qg2int_rpc_handle_for_receiving_side_object_handle_type_tag;
    Object Qg2int_rpc_handle_for_sending_side_object_type_tag;
    Object Qg2int_rpc_object_handle_type_tag, Qg2int_rpc_object_type_tag;
    Object Qg2int_rpc_unknown_type_tag, Qg2int_icp_new_keyword_symbol_type_tag;
    Object Qg2int_rpc_handle_for_temporary_object_handle_type_tag;
    Object Qg2int_icp_temporary_index_space_type_tag;
    Object Qg2int_icp_new_symbol_expanding_index_space_type_tag;
    Object Qg2int_icp_new_symbol_type_tag;
    Object Qg2int_icp_standard_index_space_type_tag;
    Object Qg2int_icp_list_non_nil_terminator_type_tag;
    Object Qg2int_icp_list_nil_terminator_type_tag, Qg2int_icp_list_type_tag;
    Object Qg2int_icp_cons_type_tag, Qg2int_gsi_largest_unary_type_number;
    Object Qg2int_gsi_end_type_tag, Qg2int_gsi_long_type_tag;
    Object Qg2int_gsi_structure_type_tag, Qg2int_gsi_sequence_type_tag;
    Object Qg2int_gsi_quantity_list_type_tag;
    Object Qg2int_gsi_item_or_value_list_type_tag;
    Object Qg2int_gsi_value_list_type_tag, Qg2int_gsi_item_list_type_tag;
    Object Qg2int_gsi_64bit_float_list_type_tag;
    Object Qg2int_gsi_logical_list_type_tag, Qg2int_gsi_string_list_type_tag;
    Object Qg2int_gsi_symbol_list_type_tag, Qg2int_gsi_integer_list_type_tag;
    Object Qg2int_gsi_quantity_array_type_tag;
    Object Qg2int_gsi_item_or_value_array_type_tag;
    Object Qg2int_gsi_value_array_type_tag, Qg2int_gsi_item_array_type_tag;
    Object Qg2int_gsi_64bit_float_array_type_tag;
    Object Qg2int_gsi_logical_array_type_tag, Qg2int_gsi_string_array_type_tag;
    Object Qg2int_gsi_symbol_array_type_tag, Qg2int_gsi_integer_array_type_tag;
    Object Qg2int_gsi_unsigned_short_vector_type_tag;
    Object Qg2int_gsi_quantity_type_tag, Qg2int_gsi_item_handle_type_tag;
    Object Qg2int_gsi_value_type_tag, Qg2int_gsi_item_type_tag;
    Object Qg2int_gsi_64bit_float_type_tag, Qg2int_gsi_logical_type_tag;
    Object Qg2int_gsi_string_type_tag, Qg2int_gsi_symbol_type_tag;
    Object Qg2int_gsi_float_type_tag, Qg2int_gsi_integer_type_tag;
    Object Qg2int_gsi_null_type_tag;

    x_note_fn_call(42,136);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_gsi_null_type_tag = STATIC_SYMBOL("GSI-NULL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_null_type_tag,FIX((SI_Long)0L));
    Qg2int_gsi_integer_type_tag = STATIC_SYMBOL("GSI-INTEGER-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_integer_type_tag,FIX((SI_Long)1L));
    Qg2int_gsi_float_type_tag = STATIC_SYMBOL("GSI-FLOAT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_float_type_tag,FIX((SI_Long)2L));
    Qg2int_gsi_symbol_type_tag = STATIC_SYMBOL("GSI-SYMBOL-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_symbol_type_tag,FIX((SI_Long)3L));
    Qg2int_gsi_string_type_tag = STATIC_SYMBOL("GSI-STRING-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_string_type_tag,FIX((SI_Long)4L));
    Qg2int_gsi_logical_type_tag = STATIC_SYMBOL("GSI-LOGICAL-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_logical_type_tag,FIX((SI_Long)5L));
    Qg2int_gsi_64bit_float_type_tag = 
	    STATIC_SYMBOL("GSI-64BIT-FLOAT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_64bit_float_type_tag,FIX((SI_Long)6L));
    Qg2int_gsi_item_type_tag = STATIC_SYMBOL("GSI-ITEM-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_item_type_tag,FIX((SI_Long)7L));
    Qg2int_gsi_value_type_tag = STATIC_SYMBOL("GSI-VALUE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_value_type_tag,FIX((SI_Long)8L));
    Qg2int_gsi_item_handle_type_tag = 
	    STATIC_SYMBOL("GSI-ITEM-HANDLE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_item_handle_type_tag,FIX((SI_Long)9L));
    Qg2int_gsi_quantity_type_tag = STATIC_SYMBOL("GSI-QUANTITY-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_quantity_type_tag,FIX((SI_Long)10L));
    Qg2int_gsi_unsigned_short_vector_type_tag = 
	    STATIC_SYMBOL("GSI-UNSIGNED-SHORT-VECTOR-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_unsigned_short_vector_type_tag,
	    FIX((SI_Long)11L));
    Qg2int_gsi_integer_array_type_tag = 
	    STATIC_SYMBOL("GSI-INTEGER-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_integer_array_type_tag,FIX((SI_Long)17L));
    Qg2int_gsi_symbol_array_type_tag = 
	    STATIC_SYMBOL("GSI-SYMBOL-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_symbol_array_type_tag,FIX((SI_Long)19L));
    Qg2int_gsi_string_array_type_tag = 
	    STATIC_SYMBOL("GSI-STRING-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_string_array_type_tag,FIX((SI_Long)20L));
    Qg2int_gsi_logical_array_type_tag = 
	    STATIC_SYMBOL("GSI-LOGICAL-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_logical_array_type_tag,FIX((SI_Long)21L));
    Qg2int_gsi_64bit_float_array_type_tag = 
	    STATIC_SYMBOL("GSI-64BIT-FLOAT-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_64bit_float_array_type_tag,FIX((SI_Long)22L));
    Qg2int_gsi_item_array_type_tag = 
	    STATIC_SYMBOL("GSI-ITEM-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_item_array_type_tag,FIX((SI_Long)23L));
    Qg2int_gsi_value_array_type_tag = 
	    STATIC_SYMBOL("GSI-VALUE-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_value_array_type_tag,FIX((SI_Long)24L));
    Qg2int_gsi_item_or_value_array_type_tag = 
	    STATIC_SYMBOL("GSI-ITEM-OR-VALUE-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_item_or_value_array_type_tag,
	    FIX((SI_Long)25L));
    Qg2int_gsi_quantity_array_type_tag = 
	    STATIC_SYMBOL("GSI-QUANTITY-ARRAY-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_quantity_array_type_tag,FIX((SI_Long)26L));
    Qg2int_gsi_integer_list_type_tag = 
	    STATIC_SYMBOL("GSI-INTEGER-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_integer_list_type_tag,FIX((SI_Long)33L));
    Qg2int_gsi_symbol_list_type_tag = 
	    STATIC_SYMBOL("GSI-SYMBOL-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_symbol_list_type_tag,FIX((SI_Long)35L));
    Qg2int_gsi_string_list_type_tag = 
	    STATIC_SYMBOL("GSI-STRING-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_string_list_type_tag,FIX((SI_Long)36L));
    Qg2int_gsi_logical_list_type_tag = 
	    STATIC_SYMBOL("GSI-LOGICAL-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_logical_list_type_tag,FIX((SI_Long)37L));
    Qg2int_gsi_64bit_float_list_type_tag = 
	    STATIC_SYMBOL("GSI-64BIT-FLOAT-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_64bit_float_list_type_tag,FIX((SI_Long)38L));
    Qg2int_gsi_item_list_type_tag = STATIC_SYMBOL("GSI-ITEM-LIST-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_item_list_type_tag,FIX((SI_Long)39L));
    Qg2int_gsi_value_list_type_tag = 
	    STATIC_SYMBOL("GSI-VALUE-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_value_list_type_tag,FIX((SI_Long)40L));
    Qg2int_gsi_item_or_value_list_type_tag = 
	    STATIC_SYMBOL("GSI-ITEM-OR-VALUE-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_item_or_value_list_type_tag,FIX((SI_Long)41L));
    Qg2int_gsi_quantity_list_type_tag = 
	    STATIC_SYMBOL("GSI-QUANTITY-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_quantity_list_type_tag,FIX((SI_Long)42L));
    Qg2int_gsi_sequence_type_tag = STATIC_SYMBOL("GSI-SEQUENCE-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_sequence_type_tag,FIX((SI_Long)49L));
    Qg2int_gsi_structure_type_tag = STATIC_SYMBOL("GSI-STRUCTURE-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_structure_type_tag,FIX((SI_Long)50L));
    Qg2int_gsi_long_type_tag = STATIC_SYMBOL("GSI-LONG-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_long_type_tag,FIX((SI_Long)51L));
    Qg2int_gsi_end_type_tag = STATIC_SYMBOL("GSI-END-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_end_type_tag,FIX((SI_Long)59L));
    Qg2int_gsi_largest_unary_type_number = 
	    STATIC_SYMBOL("GSI-LARGEST-UNARY-TYPE-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_largest_unary_type_number,FIX((SI_Long)11L));
    Qg2int_icp_cons_type_tag = STATIC_SYMBOL("ICP-CONS-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_cons_type_tag,FIX((SI_Long)80L));
    Qg2int_icp_list_type_tag = STATIC_SYMBOL("ICP-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_list_type_tag,FIX((SI_Long)81L));
    Qg2int_icp_list_nil_terminator_type_tag = 
	    STATIC_SYMBOL("ICP-LIST-NIL-TERMINATOR-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_list_nil_terminator_type_tag,
	    FIX((SI_Long)82L));
    Qg2int_icp_list_non_nil_terminator_type_tag = 
	    STATIC_SYMBOL("ICP-LIST-NON-NIL-TERMINATOR-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_list_non_nil_terminator_type_tag,
	    FIX((SI_Long)83L));
    Qg2int_icp_standard_index_space_type_tag = 
	    STATIC_SYMBOL("ICP-STANDARD-INDEX-SPACE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_standard_index_space_type_tag,
	    FIX((SI_Long)70L));
    Qg2int_icp_new_symbol_type_tag = 
	    STATIC_SYMBOL("ICP-NEW-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_new_symbol_type_tag,FIX((SI_Long)71L));
    Qg2int_icp_new_symbol_expanding_index_space_type_tag = 
	    STATIC_SYMBOL("ICP-NEW-SYMBOL-EXPANDING-INDEX-SPACE-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_new_symbol_expanding_index_space_type_tag,
	    FIX((SI_Long)72L));
    Qg2int_icp_temporary_index_space_type_tag = 
	    STATIC_SYMBOL("ICP-TEMPORARY-INDEX-SPACE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_temporary_index_space_type_tag,
	    FIX((SI_Long)73L));
    Qg2int_rpc_handle_for_temporary_object_handle_type_tag = 
	    STATIC_SYMBOL("RPC-HANDLE-FOR-TEMPORARY-OBJECT-HANDLE-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_handle_for_temporary_object_handle_type_tag,
	    FIX((SI_Long)74L));
    Qg2int_icp_new_keyword_symbol_type_tag = 
	    STATIC_SYMBOL("ICP-NEW-KEYWORD-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_new_keyword_symbol_type_tag,FIX((SI_Long)75L));
    Qg2int_rpc_unknown_type_tag = STATIC_SYMBOL("RPC-UNKNOWN-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_unknown_type_tag,FIX((SI_Long)0L));
    Qg2int_rpc_object_type_tag = STATIC_SYMBOL("RPC-OBJECT-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_object_type_tag,FIX((SI_Long)7L));
    Qg2int_rpc_object_handle_type_tag = 
	    STATIC_SYMBOL("RPC-OBJECT-HANDLE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_object_handle_type_tag,FIX((SI_Long)8L));
    Qg2int_rpc_handle_for_sending_side_object_type_tag = 
	    STATIC_SYMBOL("RPC-HANDLE-FOR-SENDING-SIDE-OBJECT-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_handle_for_sending_side_object_type_tag,
	    FIX((SI_Long)60L));
    Qg2int_rpc_handle_for_receiving_side_object_handle_type_tag = 
	    STATIC_SYMBOL("RPC-HANDLE-FOR-RECEIVING-SIDE-OBJECT-HANDLE-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_handle_for_receiving_side_object_handle_type_tag,
	    FIX((SI_Long)61L));
    Qg2int_rpc_handle_for_new_sending_side_object_type_tag = 
	    STATIC_SYMBOL("RPC-HANDLE-FOR-NEW-SENDING-SIDE-OBJECT-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_handle_for_new_sending_side_object_type_tag,
	    FIX((SI_Long)62L));
    Qg2int_rpc_new_item_copy_with_reference = 
	    STATIC_SYMBOL("RPC-NEW-ITEM-COPY-WITH-REFERENCE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_new_item_copy_with_reference,
	    FIX((SI_Long)63L));
    Qg2int_rpc_existing_item_copy = STATIC_SYMBOL("RPC-EXISTING-ITEM-COPY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_existing_item_copy,FIX((SI_Long)64L));
    Qg2int_rpc_new_item_copy = STATIC_SYMBOL("RPC-NEW-ITEM-COPY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_new_item_copy,FIX((SI_Long)65L));
    Qg2int_rpc_new_item_copy_with_handle = 
	    STATIC_SYMBOL("RPC-NEW-ITEM-COPY-WITH-HANDLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_new_item_copy_with_handle,FIX((SI_Long)66L));
    Qg2int_gsi_typed_sequence_type_tag = 
	    STATIC_SYMBOL("GSI-TYPED-SEQUENCE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_typed_sequence_type_tag,FIX((SI_Long)67L));
    Qg2int_gsi_gensym_string_type_tag = 
	    STATIC_SYMBOL("GSI-GENSYM-STRING-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_gensym_string_type_tag,FIX((SI_Long)68L));
    Qg2int_gsi_wide_string_type_tag = 
	    STATIC_SYMBOL("GSI-WIDE-STRING-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_wide_string_type_tag,FIX((SI_Long)69L));
    Qg2int_list_element_null_type_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-NULL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_list_element_null_type_tag,FIX((SI_Long)0L));
    Qg2int_list_element_integer_type_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-INTEGER-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_list_element_integer_type_tag,FIX((SI_Long)1L));
    Qg2int_list_element_symbol_type_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_list_element_symbol_type_tag,FIX((SI_Long)2L));
    Qg2int_list_element_text_type_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-TEXT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_list_element_text_type_tag,FIX((SI_Long)3L));
    Qg2int_list_element_list_type_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_list_element_list_type_tag,FIX((SI_Long)4L));
    Qg2int_list_element_cons_type_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-CONS-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_list_element_cons_type_tag,FIX((SI_Long)5L));
    Qg2int_icp_tree_interned_list_type_tag = 
	    STATIC_SYMBOL("ICP-TREE-INTERNED-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_tree_interned_list_type_tag,FIX((SI_Long)90L));
    Qg2int_index_space_remote_procedure_name = 
	    STATIC_SYMBOL("INDEX-SPACE-REMOTE-PROCEDURE-NAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_index_space_remote_procedure_name,
	    FIX((SI_Long)91L));
    Qg2int_read_icp_boolean = STATIC_SYMBOL("READ-ICP-BOOLEAN",AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    Qg2int_resumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_boolean,
	    STATIC_FUNCTION(g2int_read_icp_boolean,NIL,FALSE,0,0));
    Qg2int_write_icp_boolean = STATIC_SYMBOL("WRITE-ICP-BOOLEAN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_boolean,
	    STATIC_FUNCTION(g2int_write_icp_boolean,NIL,FALSE,1,1));
    Qg2int_read_icp_corresponding_object_index = 
	    STATIC_SYMBOL("READ-ICP-CORRESPONDING-OBJECT-INDEX",AB_package);
    Qg2int_true = STATIC_SYMBOL("TRUE",AB_package);
    Qg2int_false = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_corresponding_object_index,
	    STATIC_FUNCTION(g2int_read_icp_corresponding_object_index,NIL,
	    FALSE,0,0));
    Qg2int_read_icp_unsigned_integer = 
	    STATIC_SYMBOL("READ-ICP-UNSIGNED-INTEGER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_unsigned_integer,
	    STATIC_FUNCTION(g2int_read_icp_unsigned_integer,NIL,FALSE,0,0));
    string_constant_1 = 
	    STATIC_STRING("An integer outside the allowed range was given to ~\n                   ICP-write-unsigned-integer: ~a");
    Qg2int_write_icp_corresponding_object_index = 
	    STATIC_SYMBOL("WRITE-ICP-CORRESPONDING-OBJECT-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_corresponding_object_index,
	    STATIC_FUNCTION(g2int_write_icp_corresponding_object_index,NIL,
	    FALSE,1,1));
    Qg2int_write_icp_unsigned_integer = 
	    STATIC_SYMBOL("WRITE-ICP-UNSIGNED-INTEGER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_unsigned_integer,
	    STATIC_FUNCTION(g2int_write_icp_unsigned_integer,NIL,FALSE,1,1));
    Qg2int_read_icp_unsigned_integerqm = 
	    STATIC_SYMBOL("READ-ICP-UNSIGNED-INTEGER\?",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_unsigned_integerqm,
	    STATIC_FUNCTION(g2int_read_icp_unsigned_integerqm,NIL,FALSE,0,0));
    Qg2int_write_icp_unsigned_integerqm = 
	    STATIC_SYMBOL("WRITE-ICP-UNSIGNED-INTEGER\?",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_unsigned_integerqm,
	    STATIC_FUNCTION(g2int_write_icp_unsigned_integerqm,NIL,FALSE,1,1));
    string_constant_2 = 
	    STATIC_STRING("Integer outside of the range for ICP integers: ~a");
    Qg2int_read_icp_integer = STATIC_SYMBOL("READ-ICP-INTEGER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_integer,
	    STATIC_FUNCTION(g2int_read_icp_integer,NIL,FALSE,0,0));
    Qg2int_write_icp_integer = STATIC_SYMBOL("WRITE-ICP-INTEGER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_integer,
	    STATIC_FUNCTION(g2int_write_icp_integer,NIL,FALSE,1,1));
    Qg2int_write_icp_managed_long = STATIC_SYMBOL("WRITE-ICP-MANAGED-LONG",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_managed_long,
	    STATIC_FUNCTION(g2int_write_icp_managed_long,NIL,FALSE,1,1));
    Qg2int_read_icp_managed_long = STATIC_SYMBOL("READ-ICP-MANAGED-LONG",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_managed_long,
	    STATIC_FUNCTION(g2int_read_icp_managed_long,NIL,FALSE,0,0));
    Qg2int_read_icp_list_of_unsigned_integers = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-UNSIGNED-INTEGERS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_unsigned_integers,
	    STATIC_FUNCTION(g2int_read_icp_list_of_unsigned_integers,NIL,
	    FALSE,0,0));
    Qg2int_list_of_unsigned_integers = 
	    STATIC_SYMBOL("LIST-OF-UNSIGNED-INTEGERS",AB_package);
    Qg2int_reclaim_gensym_list = STATIC_SYMBOL("RECLAIM-GENSYM-LIST",
	    AB_package);
    Qg2int_icp_value_reclaimer = STATIC_SYMBOL("ICP-VALUE-RECLAIMER",
	    AB_package);
    g2int_mutate_global_property(Qg2int_list_of_unsigned_integers,
	    Qg2int_reclaim_gensym_list,Qg2int_icp_value_reclaimer);
    Qg2int_write_icp_list_of_unsigned_integers = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-UNSIGNED-INTEGERS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_unsigned_integers,
	    STATIC_FUNCTION(g2int_write_icp_list_of_unsigned_integers,NIL,
	    FALSE,1,1));
    Qg2int_read_icp_list_of_integers = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INTEGERS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_integers,
	    STATIC_FUNCTION(g2int_read_icp_list_of_integers,NIL,FALSE,0,0));
    Qg2int_list_of_integers = STATIC_SYMBOL("LIST-OF-INTEGERS",AB_package);
    g2int_mutate_global_property(Qg2int_list_of_integers,
	    Qg2int_reclaim_gensym_list,Qg2int_icp_value_reclaimer);
    Qg2int_write_icp_list_of_integers = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INTEGERS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_integers,
	    STATIC_FUNCTION(g2int_write_icp_list_of_integers,NIL,FALSE,1,1));
    Qg2int_read_icp_large_integer = STATIC_SYMBOL("READ-ICP-LARGE-INTEGER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_large_integer,
	    STATIC_FUNCTION(g2int_read_icp_large_integer,NIL,FALSE,1,1));
    G2int_constant_in_large_integer_length_in_icp_bytes = 
	    logand(Most_positive_fixnum,
	    ash(FIXNUM_SUB1(FIX((SI_Long)32768L)),FIX((SI_Long)15L)));
    G2int_write_icp_large_integer_constant = 
	    logand(ash(FIXNUM_NEGATE(Most_negative_fixnum),
	    FIX((SI_Long)-15L)),FIXNUM_SUB1(FIX((SI_Long)32768L)));
    Qg2int_write_icp_large_integer = 
	    STATIC_SYMBOL("WRITE-ICP-LARGE-INTEGER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_large_integer,
	    STATIC_FUNCTION(g2int_write_icp_large_integer,NIL,FALSE,1,1));
    Qg2int_read_icp_fixnum = STATIC_SYMBOL("READ-ICP-FIXNUM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_fixnum,
	    STATIC_FUNCTION(g2int_read_icp_fixnum,NIL,FALSE,0,0));
    Qg2int_write_icp_fixnum = STATIC_SYMBOL("WRITE-ICP-FIXNUM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_fixnum,
	    STATIC_FUNCTION(g2int_write_icp_fixnum,NIL,FALSE,1,1));
    Qg2int_read_icp_character = STATIC_SYMBOL("READ-ICP-CHARACTER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_character,
	    STATIC_FUNCTION(g2int_read_icp_character,NIL,FALSE,0,0));
    Qg2int_write_icp_character = STATIC_SYMBOL("WRITE-ICP-CHARACTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_character,
	    STATIC_FUNCTION(g2int_write_icp_character,NIL,FALSE,1,1));
    string_constant_3 = 
	    string_append2(STATIC_STRING("ICP attempted to read a text string longer than ~\n           the maximum allowed length of ~a characters.  ~\n           The string beginning ~s ~\n           will be truncated "),
	    STATIC_STRING("to the maximum allowed length."));
    Qg2int_read_icp_wide_string = STATIC_SYMBOL("READ-ICP-WIDE-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_wide_string,
	    STATIC_FUNCTION(g2int_read_icp_wide_string,NIL,FALSE,0,0));
    Qg2int_read_icp_text_string = STATIC_SYMBOL("READ-ICP-TEXT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_text_string,
	    STATIC_FUNCTION(g2int_read_icp_text_string,NIL,FALSE,0,0));
    string_constant_4 = 
	    string_append2(STATIC_STRING("ICP attempted to read a text string longer than ~\n           the maximum allowed length of ~a bytes.  ~\n           The string beginning ~s ~\n           will be truncated to th"),
	    STATIC_STRING("e maximum allowed length."));
    Qg2int_read_icp_gensym_string = STATIC_SYMBOL("READ-ICP-GENSYM-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_gensym_string,
	    STATIC_FUNCTION(g2int_read_icp_gensym_string,NIL,FALSE,0,0));
    Qg2int_read_icp_raw_gensym_string = 
	    STATIC_SYMBOL("READ-ICP-RAW-GENSYM-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_raw_gensym_string,
	    STATIC_FUNCTION(g2int_read_icp_raw_gensym_string,NIL,FALSE,0,0));
    Qg2int_text_string = STATIC_SYMBOL("TEXT-STRING",AB_package);
    Qg2int_reclaim_text_string = STATIC_SYMBOL("RECLAIM-TEXT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_text_string,
	    STATIC_FUNCTION(g2int_reclaim_text_string,NIL,FALSE,1,1));
    g2int_mutate_global_property(Qg2int_text_string,
	    Qg2int_reclaim_text_string,Qg2int_icp_value_reclaimer);
    Qg2int_gensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    Qg2int_reclaim_gensym_string = STATIC_SYMBOL("RECLAIM-GENSYM-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_gensym_string,
	    STATIC_FUNCTION(g2int_reclaim_gensym_string,NIL,FALSE,1,1));
    g2int_mutate_global_property(Qg2int_gensym_string,
	    Qg2int_reclaim_gensym_string,Qg2int_icp_value_reclaimer);
    Qg2int_raw_gensym_string = STATIC_SYMBOL("RAW-GENSYM-STRING",AB_package);
    g2int_mutate_global_property(Qg2int_raw_gensym_string,
	    Qg2int_reclaim_gensym_string,Qg2int_icp_value_reclaimer);
    string_constant_5 = 
	    string_append2(STATIC_STRING("ICP attempted to write a text string longer than ~\n           the maximum allowed length of ~a characters.  ~\n           The string beginning ~s ~\n           will be truncated"),
	    STATIC_STRING(" to the maximum allowed length."));
    Qg2int_write_icp_wide_string = STATIC_SYMBOL("WRITE-ICP-WIDE-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_wide_string,
	    STATIC_FUNCTION(g2int_write_icp_wide_string,NIL,FALSE,1,1));
    Qg2int_write_icp_text_string = STATIC_SYMBOL("WRITE-ICP-TEXT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_text_string,
	    STATIC_FUNCTION(g2int_write_icp_text_string,NIL,FALSE,1,1));
    string_constant_6 = 
	    string_append2(STATIC_STRING("ICP attempted to write a string longer than ~\n           the maximum allowed length of ~a bytes.  ~\n           The string beginning ~s ~\n           will be truncated to the ma"),
	    STATIC_STRING("ximum allowed length."));
    Qg2int_write_icp_raw_gensym_string = 
	    STATIC_SYMBOL("WRITE-ICP-RAW-GENSYM-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_raw_gensym_string,
	    STATIC_FUNCTION(g2int_write_icp_raw_gensym_string,NIL,FALSE,1,1));
    Qg2int_write_icp_gensym_string = 
	    STATIC_SYMBOL("WRITE-ICP-GENSYM-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_gensym_string,
	    STATIC_FUNCTION(g2int_write_icp_gensym_string,NIL,FALSE,1,1));
    Qg2int_icp_filtered_text_string_reader = 
	    STATIC_SYMBOL("ICP-FILTERED-TEXT-STRING-READER",AB_package);
    Qg2int_read_icp_filtered_text_string = 
	    STATIC_SYMBOL("READ-ICP-FILTERED-TEXT-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_filtered_text_string,
	    STATIC_FUNCTION(g2int_read_icp_filtered_text_string,NIL,FALSE,
	    0,0));
    Qg2int_icp_filtered_text_string_writer = 
	    STATIC_SYMBOL("ICP-FILTERED-TEXT-STRING-WRITER",AB_package);
    Qg2int_write_icp_filtered_text_string = 
	    STATIC_SYMBOL("WRITE-ICP-FILTERED-TEXT-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_filtered_text_string,
	    STATIC_FUNCTION(g2int_write_icp_filtered_text_string,NIL,FALSE,
	    1,1));
    string_constant_7 = STATIC_STRING("Bad ICP-list-element: ~a");
    Qg2int_write_icp_list_element = STATIC_SYMBOL("WRITE-ICP-LIST-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_element,
	    STATIC_FUNCTION(g2int_write_icp_list_element,NIL,FALSE,1,1));
    Qg2int_read_icp_list_element = STATIC_SYMBOL("READ-ICP-LIST-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_element,
	    STATIC_FUNCTION(g2int_read_icp_list_element,NIL,FALSE,0,0));
    Qg2int_write_icp_list = STATIC_SYMBOL("WRITE-ICP-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list,
	    STATIC_FUNCTION(g2int_write_icp_list,NIL,FALSE,1,1));
    Qg2int_read_icp_list = STATIC_SYMBOL("READ-ICP-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list,
	    STATIC_FUNCTION(g2int_read_icp_list,NIL,FALSE,0,0));
    string_constant_8 = STATIC_STRING("Bad ICP-improper-list-element: ~a");
    Qg2int_write_icp_improper_list_element = 
	    STATIC_SYMBOL("WRITE-ICP-IMPROPER-LIST-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_improper_list_element,
	    STATIC_FUNCTION(g2int_write_icp_improper_list_element,NIL,
	    FALSE,1,1));
    Qg2int_read_icp_improper_list_element = 
	    STATIC_SYMBOL("READ-ICP-IMPROPER-LIST-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_improper_list_element,
	    STATIC_FUNCTION(g2int_read_icp_improper_list_element,NIL,FALSE,
	    0,0));
    Qg2int_write_icp_improper_list = 
	    STATIC_SYMBOL("WRITE-ICP-IMPROPER-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_improper_list,
	    STATIC_FUNCTION(g2int_write_icp_improper_list,NIL,FALSE,1,1));
    Qg2int_read_icp_improper_list = STATIC_SYMBOL("READ-ICP-IMPROPER-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_improper_list,
	    STATIC_FUNCTION(g2int_read_icp_improper_list,NIL,FALSE,0,0));
    Qg2int_corresponding_icp_object_index = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX",AB_package);
    Qg2int_unsigned_integer = STATIC_SYMBOL("UNSIGNED-INTEGER",AB_package);
    Qg2int_equivalent_icp_value_type = 
	    STATIC_SYMBOL("EQUIVALENT-ICP-VALUE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_corresponding_icp_object_index,
	    Qg2int_unsigned_integer,Qg2int_equivalent_icp_value_type);
    Qg2int_item_with_handle_index_space = 
	    STATIC_SYMBOL("ITEM-WITH-HANDLE-INDEX-SPACE",AB_package);
    Qg2int_remove_icp_port_entries_from_icp_object_list = 
	    STATIC_SYMBOL("REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT-LIST",
	    AB_package);
    Qg2int_remove_icp_port_entries_from_icp_object = 
	    STATIC_SYMBOL("REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT",
	    AB_package);
    if (G2int_use_new_message_group_for_send_icp_enlarge_index_space_p == 
	    UNBOUND)
	G2int_use_new_message_group_for_send_icp_enlarge_index_space_p = Nil;
    Qg2int_standard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qg2int_item_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2int_output = STATIC_SYMBOL("OUTPUT",AB_package);
    Qg2int_frame_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",
	    AB_package);
    Qg2int_corresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    G2int_corresponding_icp_object_map_for_symbol_prop = 
	    Qg2int_corresponding_icp_object_map_for_symbol;
    Qg2int_establish_new_object_index_for_symbol = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-SYMBOL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_establish_new_object_index_for_symbol,
	    STATIC_FUNCTION(g2int_establish_new_object_index_for_symbol,
	    NIL,TRUE,2,3));
    Qg2int_make_corresponding_icp_symbol = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-SYMBOL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_corresponding_icp_symbol,
	    STATIC_FUNCTION(g2int_make_corresponding_icp_symbol,NIL,FALSE,
	    1,1));
    Qg2int_set_access_form_for_symbol = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-SYMBOL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_symbol,
	    STATIC_FUNCTION(g2int_set_access_form_for_symbol,NIL,FALSE,2,2));
    list_constant = STATIC_LIST((SI_Long)2L,
	    Qg2int_corresponding_icp_object_map_for_symbol,Qsymbol);
    g2int_initialize_icp_object_type_compile(Qsymbol,
	    Qg2int_standard_icp_object_index_space,list_constant);
    Qg2int_reclaim_icp_port_entry_for_symbol = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-SYMBOL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_symbol,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_symbol,NIL,
	    FALSE,2,2));
    g2int_initialize_icp_object_type(Qsymbol,Qnil,Qnil,
	    Qg2int_reclaim_icp_port_entry_for_symbol);
    Qg2int_write_icp_symbol_as_value_type = 
	    STATIC_SYMBOL("WRITE-ICP-SYMBOL-AS-VALUE-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_symbol_as_value_type,
	    STATIC_FUNCTION(g2int_write_icp_symbol_as_value_type,NIL,FALSE,
	    1,1));
    Qg2int_read_icp_symbol_as_value_type = 
	    STATIC_SYMBOL("READ-ICP-SYMBOL-AS-VALUE-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_symbol_as_value_type,
	    STATIC_FUNCTION(g2int_read_icp_symbol_as_value_type,NIL,FALSE,
	    0,0));
    Qg2int_send_icp_intern = STATIC_SYMBOL("SEND-ICP-INTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_intern,
	    STATIC_FUNCTION(g2int_send_icp_intern,NIL,FALSE,2,2));
    Qg2int_handle_icp_intern = STATIC_SYMBOL("HANDLE-ICP-INTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_intern,
	    STATIC_FUNCTION(g2int_handle_icp_intern,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_intern,FIX((SI_Long)81L));
    Qg2int_send_icp_intern_keyword = 
	    STATIC_SYMBOL("SEND-ICP-INTERN-KEYWORD",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_intern_keyword,
	    STATIC_FUNCTION(g2int_send_icp_intern_keyword,NIL,FALSE,2,2));
    Qg2int_handle_icp_intern_keyword = 
	    STATIC_SYMBOL("HANDLE-ICP-INTERN-KEYWORD",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_intern_keyword,
	    STATIC_FUNCTION(g2int_handle_icp_intern_keyword,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_intern_keyword,
	    FIX((SI_Long)86L));
    Qg2int_send_icp_add_to_list_of_symbols = 
	    STATIC_SYMBOL("SEND-ICP-ADD-TO-LIST-OF-SYMBOLS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_add_to_list_of_symbols,
	    STATIC_FUNCTION(g2int_send_icp_add_to_list_of_symbols,NIL,
	    FALSE,3,3));
    Qg2int_handle_icp_add_to_list_of_symbols = 
	    STATIC_SYMBOL("HANDLE-ICP-ADD-TO-LIST-OF-SYMBOLS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_add_to_list_of_symbols,
	    STATIC_FUNCTION(g2int_handle_icp_add_to_list_of_symbols,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_add_to_list_of_symbols,
	    FIX((SI_Long)82L));
    Qg2int_object_map_plist_for_icp_tree = 
	    STATIC_SYMBOL("OBJECT-MAP-PLIST-FOR-ICP-TREE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_object_map_plist_for_icp_tree,
	    G2int_object_map_plist_for_icp_tree);
    Qg2int_int3a = STATIC_SYMBOL("INT3A",AB_package);
    g2int_record_system_variable(Qg2int_object_map_plist_for_icp_tree,
	    Qg2int_int3a,Nil,Qnil,Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_symbol_tree_g2_struct = 
	    STATIC_SYMBOL("SYMBOL-TREE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_symbol_tree = STATIC_SYMBOL("SYMBOL-TREE",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_symbol_tree_g2_struct,
	    Qg2int_symbol_tree,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_symbol_tree,
	    Qg2_defstruct_structure_name_symbol_tree_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_symbol_tree == UNBOUND)
	G2int_the_type_description_of_symbol_tree = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8l831+y1n831+y8m8k1l8m0000001l1n8n83=Py0kmk0k0");
    temp = G2int_the_type_description_of_symbol_tree;
    G2int_the_type_description_of_symbol_tree = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_10));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_symbol_tree_g2_struct,
	    G2int_the_type_description_of_symbol_tree,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_symbol_tree,
	    G2int_the_type_description_of_symbol_tree,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_symbol_trees = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SYMBOL-TREES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_symbol_trees,
	    G2int_chain_of_available_symbol_trees);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_symbol_trees,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_symbol_tree_count = STATIC_SYMBOL("SYMBOL-TREE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_symbol_tree_count,
	    G2int_symbol_tree_count);
    g2int_record_system_variable(Qg2int_symbol_tree_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_symbol_tree = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_symbol_tree,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_symbol_tree,reclaim_structure_for_symbol_tree);
    Qg2int_write_icp_icp_tree = STATIC_SYMBOL("WRITE-ICP-ICP-TREE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_icp_tree,
	    STATIC_FUNCTION(g2int_write_icp_icp_tree,NIL,FALSE,1,1));
    string_constant_9 = 
	    STATIC_STRING("Unknown type tag ~a in READ-ICP-ICP-TREE");
    Qg2int_read_icp_icp_tree = STATIC_SYMBOL("READ-ICP-ICP-TREE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_icp_tree,
	    STATIC_FUNCTION(g2int_read_icp_icp_tree,NIL,FALSE,0,0));
    Qg2_defstruct_structure_name_interned_list_g2_struct = 
	    STATIC_SYMBOL("INTERNED-LIST-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_interned_list = STATIC_SYMBOL("INTERNED-LIST",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_interned_list_g2_struct,
	    Qg2int_interned_list,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_interned_list,
	    Qg2_defstruct_structure_name_interned_list_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_interned_list == UNBOUND)
	G2int_the_type_description_of_interned_list = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8l83*1y1n83*1y8m8k1l8m0000001l1n8n83=3y1l83*2ykok0k0");
    temp = G2int_the_type_description_of_interned_list;
    G2int_the_type_description_of_interned_list = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_11));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_interned_list_g2_struct,
	    G2int_the_type_description_of_interned_list,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_interned_list,
	    G2int_the_type_description_of_interned_list,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_interned_lists = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INTERNED-LISTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_interned_lists,
	    G2int_chain_of_available_interned_lists);
    g2int_record_system_variable(Qg2int_chain_of_available_interned_lists,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_interned_list_count = STATIC_SYMBOL("INTERNED-LIST-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_interned_list_count,
	    G2int_interned_list_count);
    g2int_record_system_variable(Qg2int_interned_list_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_interned_list = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_interned_list,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_interned_list,reclaim_structure_for_interned_list);
    if (G2int_interned_list_conses == UNBOUND)
	G2int_interned_list_conses = Nil;
    if (G2int_interned_list_conses_in_use == UNBOUND)
	G2int_interned_list_conses_in_use = FIX((SI_Long)0L);
    Qg2int_interned_list_table = STATIC_SYMBOL("INTERNED-LIST-TABLE",
	    AB_package);
    G2int_interned_list_table_prop = Qg2int_interned_list_table;
    if (G2int_interned_list_non_symbol_root == UNBOUND)
	G2int_interned_list_non_symbol_root = Nil;
    if (G2int_interned_list_symbols == UNBOUND)
	G2int_interned_list_symbols = Nil;
    if (G2int_interned_list_nil == UNBOUND)
	G2int_interned_list_nil = Nil;
    Qg2int_intern_list = STATIC_SYMBOL("INTERN-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_intern_list,
	    STATIC_FUNCTION(g2int_intern_list,NIL,FALSE,1,1));
    Qg2int_send_icp_intern_list = STATIC_SYMBOL("SEND-ICP-INTERN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_intern_list,
	    STATIC_FUNCTION(g2int_send_icp_intern_list,NIL,FALSE,2,2));
    Qg2int_handle_icp_intern_list = STATIC_SYMBOL("HANDLE-ICP-INTERN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_intern_list,
	    STATIC_FUNCTION(g2int_handle_icp_intern_list,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_intern_list,
	    FIX((SI_Long)351L));
    Qg2int_establish_new_object_index_for_interned_list = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-INTERNED-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_establish_new_object_index_for_interned_list,
	    STATIC_FUNCTION(g2int_establish_new_object_index_for_interned_list,
	    NIL,TRUE,2,3));
    Qg2int_make_corresponding_icp_interned_list = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-INTERNED-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_corresponding_icp_interned_list,
	    STATIC_FUNCTION(g2int_make_corresponding_icp_interned_list,NIL,
	    FALSE,1,1));
    Qg2int_set_access_form_for_interned_list = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-INTERNED-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_interned_list,
	    STATIC_FUNCTION(g2int_set_access_form_for_interned_list,NIL,
	    FALSE,2,2));
    Qg2int_interned_list__corresponding_icp_object_map = 
	    STATIC_SYMBOL("INTERNED-LIST--CORRESPONDING-ICP-OBJECT-MAP",
	    AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,
	    Qg2int_interned_list__corresponding_icp_object_map,
	    Qg2int_interned_list);
    g2int_initialize_icp_object_type_compile(Qg2int_interned_list,
	    Qg2int_standard_icp_object_index_space,list_constant_1);
    Qg2int_reclaim_icp_port_entry_for_interned_list = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-INTERNED-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_interned_list,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_interned_list,
	    NIL,FALSE,2,2));
    g2int_initialize_icp_object_type(Qg2int_interned_list,Qnil,Qnil,
	    Qg2int_reclaim_icp_port_entry_for_interned_list);
    Qg2int_write_icp_interned_list_as_value_type = 
	    STATIC_SYMBOL("WRITE-ICP-INTERNED-LIST-AS-VALUE-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_interned_list_as_value_type,
	    STATIC_FUNCTION(g2int_write_icp_interned_list_as_value_type,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_interned_list_as_value_type = 
	    STATIC_SYMBOL("READ-ICP-INTERNED-LIST-AS-VALUE-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_interned_list_as_value_type,
	    STATIC_FUNCTION(g2int_read_icp_interned_list_as_value_type,NIL,
	    FALSE,0,0));
    Qg2_defstruct_structure_name_icp_read_task_g2_struct = 
	    STATIC_SYMBOL("ICP-READ-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_icp_read_task = STATIC_SYMBOL("ICP-READ-TASK",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_read_task_g2_struct,
	    Qg2int_icp_read_task,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_icp_read_task,
	    Qg2_defstruct_structure_name_icp_read_task_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_icp_read_task == UNBOUND)
	G2int_the_type_description_of_icp_read_task = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8l83-ny1n83-ny8m8k1l8m0000001l1n8n83==y1l83-oykrk0k0");
    temp = G2int_the_type_description_of_icp_read_task;
    G2int_the_type_description_of_icp_read_task = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_12));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_read_task_g2_struct,
	    G2int_the_type_description_of_icp_read_task,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_icp_read_task,
	    G2int_the_type_description_of_icp_read_task,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_icp_read_tasks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-READ-TASKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_icp_read_tasks,
	    G2int_chain_of_available_icp_read_tasks);
    g2int_record_system_variable(Qg2int_chain_of_available_icp_read_tasks,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_icp_read_task_count = STATIC_SYMBOL("ICP-READ-TASK-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_read_task_count,
	    G2int_icp_read_task_count);
    g2int_record_system_variable(Qg2int_icp_read_task_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_icp_read_task = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_icp_read_task,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_icp_read_task,reclaim_structure_for_icp_read_task);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_read_icp_icp_task_resumable_p = 
	    STATIC_SYMBOL("READ-ICP-ICP-TASK-RESUMABLE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_icp_task_resumable_p,
	    STATIC_FUNCTION(g2int_read_icp_icp_task_resumable_p,NIL,FALSE,
	    0,0));
    Qg2int_write_icp_icp_task_resumable_p = 
	    STATIC_SYMBOL("WRITE-ICP-ICP-TASK-RESUMABLE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_icp_task_resumable_p,
	    STATIC_FUNCTION(g2int_write_icp_icp_task_resumable_p,NIL,FALSE,
	    1,1));
    Qg2int_send_icp_start_icp_task = 
	    STATIC_SYMBOL("SEND-ICP-START-ICP-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_start_icp_task,
	    STATIC_FUNCTION(g2int_send_icp_start_icp_task,NIL,FALSE,3,3));
    Qg2int_handle_icp_start_icp_task = 
	    STATIC_SYMBOL("HANDLE-ICP-START-ICP-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_start_icp_task,
	    STATIC_FUNCTION(g2int_handle_icp_start_icp_task,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_start_icp_task,
	    FIX((SI_Long)245L));
    Qg2int_send_icp_resume_icp_task = 
	    STATIC_SYMBOL("SEND-ICP-RESUME-ICP-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_resume_icp_task,
	    STATIC_FUNCTION(g2int_send_icp_resume_icp_task,NIL,FALSE,2,2));
    Qg2int_handle_icp_resume_icp_task = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUME-ICP-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_resume_icp_task,
	    STATIC_FUNCTION(g2int_handle_icp_resume_icp_task,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_resume_icp_task,
	    FIX((SI_Long)246L));
    Qg2int_send_icp_abort_icp_task = 
	    STATIC_SYMBOL("SEND-ICP-ABORT-ICP-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_abort_icp_task,
	    STATIC_FUNCTION(g2int_send_icp_abort_icp_task,NIL,FALSE,1,1));
    Qg2int_handle_icp_abort_icp_task = 
	    STATIC_SYMBOL("HANDLE-ICP-ABORT-ICP-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_abort_icp_task,
	    STATIC_FUNCTION(g2int_handle_icp_abort_icp_task,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_abort_icp_task,
	    FIX((SI_Long)250L));
    Qg2_defstruct_structure_name_icp_write_task_g2_struct = 
	    STATIC_SYMBOL("ICP-WRITE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_icp_write_task = STATIC_SYMBOL("ICP-WRITE-TASK",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_write_task_g2_struct,
	    Qg2int_icp_write_task,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_icp_write_task,
	    Qg2_defstruct_structure_name_icp_write_task_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_icp_write_task == UNBOUND)
	G2int_the_type_description_of_icp_write_task = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8l83-ry1n83-ry8m8k1l8m0000001l1n8n83=1y1r83-vy83-wy83-sy83*+y83-xy83-uy83-tyksk0k0");
    temp = G2int_the_type_description_of_icp_write_task;
    G2int_the_type_description_of_icp_write_task = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_13));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_write_task_g2_struct,
	    G2int_the_type_description_of_icp_write_task,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_icp_write_task,
	    G2int_the_type_description_of_icp_write_task,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_icp_write_tasks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-WRITE-TASKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_icp_write_tasks,
	    G2int_chain_of_available_icp_write_tasks);
    g2int_record_system_variable(Qg2int_chain_of_available_icp_write_tasks,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_icp_write_task_count = STATIC_SYMBOL("ICP-WRITE-TASK-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_write_task_count,
	    G2int_icp_write_task_count);
    g2int_record_system_variable(Qg2int_icp_write_task_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_icp_write_task = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_icp_write_task,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_icp_write_task,reclaim_structure_for_icp_write_task);
    Qg2int_not_open = STATIC_SYMBOL("NOT-OPEN",AB_package);
    Qg2int_blocked = STATIC_SYMBOL("BLOCKED",AB_package);
    Qg2int_time_slice_expired = STATIC_SYMBOL("TIME-SLICE-EXPIRED",AB_package);
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Qg2int_resumable_icp_write_callback = 
	    STATIC_SYMBOL("RESUMABLE-ICP-WRITE-CALLBACK",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qg2int_resumable_icp_write_callback,
	    STATIC_FUNCTION(g2int_resumable_icp_write_callback,NIL,FALSE,2,2));
}
