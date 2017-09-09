/*
 *
 *  HASH.C - Hash table functions
 *  Copyright (c) 1991 Chestnut Software, Inc.  All rights reserved.
 *
 *  Created: 9/8/91
 *  Last revision: 5/23/92
 *
 *  Author:  Dmitry Nizhegorodov
 */

#include "runtime.h"

extern Object Qequalp;
extern Object Qequal;
extern Object Qeq;
extern Object Qstring_char;
#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif
extern Object SI_gc_genobj;
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern SI_Long SI_igcd(SI_Long n1, SI_Long n2);
extern char *SI_istring(Object o);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object cons(Object,Object);
extern Object eql(Object,Object);
extern Object equalp(Object,Object);
extern Object equal(Object,Object);
extern Object eq(Object,Object);
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall(Object original_function, int args_on_stack, Object arglist);
#else
extern Object funcall2(Object func, Object arg1, Object arg2);
#endif
extern char *isymbol_name(Object sym);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object make_vector(Object size, Object initial_element);
extern Object hash_table_count(Object hash_table);

#else

extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern SI_Long SI_igcd();
extern char *SI_istring();
extern Object (*SI_warn_fptr) ();
extern Object cons();
extern Object eql();
extern Object equalp();
extern Object equal();
extern Object eq();
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall();
#else
extern Object funcall2();
#endif
extern char *isymbol_name();
extern Object make_array();
extern Object make_vector();
extern Object hash_table_count();

#endif

#include "hash.h"

static Object imake_hash_table();
static Object hash_eq();
static Object hash_eql();
static Object hash_equal();
static Object hash_equalp();
static Object create_and_add_entry();
static Object safe_sethash_with_rehash();
static Object unsafe_sethash_with_rehash();
static Object gethash_with_rehash();
static Object remhash_with_rehash();

static SI_Hash hash_equal_cons();
static SI_Hash hash_equalp_cons();

static SI_Long new_hash_size();
static SI_Long rehash_normalize();

static SI_Ulong isxhash();

static void ncopy_hash_table();
static void add_entry();
static void rehash_and_add_entry ();
static void rehash();

static SI_Ulong expmod();
SI_Ulong SI_next_prime();

/* Reserved for the future enhancement */
static Object Hash_tests = UNBOUND;
static Object Hash_methods = UNBOUND;

/* currently supports invocation of hash_functions;
   after inlining of hash_eq/eql will be not wery useful */
static Object (*Hash_functions[])() = {
    hash_eq,
    hash_eql,
    hash_equal,
    hash_equalp
};
	
void SI_init_hash_tables()
{

/*

Initialize variables:
Qhash_tests           - vector of hash-table comparators,
                        can be adjusted by user;
Qhash_methods         - vector of hash functions, can be adjusted by user;
Qhash_test_conses_p   - predicate on hash test;
Qhash_method_conses_p - predicate on hash method;

*/

}

Object make_hash_table (test, size, rehash_size, rehash_threshold)
    Object test, size, rehash_size, rehash_threshold;
{
    UCHAR method;
    double float_rehash;

    if ( UNSUPPLIED_P(size))
	size = Default_hash_size;
    size = FIX(SI_next_prime(IFIX(size)));

    if (UNSUPPLIED_P(rehash_size))
	rehash_size = Default_rehash_size;
    else {
	if (FIXNUMP(rehash_size)) {
	    /* NOOP*/
	}
	else if (FLOATP(rehash_size)) {
	    float_rehash = IDOUBLE(rehash_size);
	    float_rehash = CORRECT_FLOAT_REHASH(float_rehash);
	    rehash_size = FIX(COMPUTE_PERCENT_REHASH_SIZE(float_rehash));
	}
	else 
	    error(2,"make_hash_table: non-numeric rehash-size ~S", 
		  rehash_size);
    }
    /* ignore user-supplied threshold */
    rehash_threshold = Default_rehash_threshold;

    method = HASH_EQL;  /* default */
    if (!UNSUPPLIED_P(test)) {
	if (COMPILED_FUNCTION_P(test)) {
	    if (IFUNC(test) == eq)
		method = HASH_EQ;
	    else if (IFUNC(test) == equal)
		method = HASH_EQUAL;
	    else if (IFUNC(test) == equalp)
		method = HASH_EQUALP;
	}
	else if (test == Qeq)
	    method = HASH_EQ;
	else if (test == Qequal)
	    method = HASH_EQUAL;
	else if (test == Qequalp)
	    method = HASH_EQUALP;
    }
    return imake_hash_table(method,size, rehash_size);
}

static Object imake_hash_table (method, hash_size, rehash_size)
    UCHAR method;
    Object hash_size, rehash_size;
{
    Declare_local_temp;
    Object table, hash_arrays, robust_array, weak_array, threshold;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(hash_size, rehash_size);
    PROTECTI_4(table,hash_arrays, robust_array, weak_array);

    /* ignore user-supplied size */
    threshold = COMPUTE_THRESHOLD(BASE_PRIME_NUMBER());

    robust_array = MAKE_HASH_ARRAY(BASE_PRIME_NUMBER());
    ARRAY_COUNTER(robust_array) = FIX(0);
    ARRAY_THRESHOLD(robust_array) = threshold;

    weak_array   = MAKE_HASH_ARRAY(BASE_PRIME_NUMBER());
    ARRAY_COUNTER(weak_array) = FIX(0);
    ARRAY_THRESHOLD(weak_array) = threshold;

    /* intermediate design decision;
       will be corrected after SI_Hashtable  be  updated */
    hash_arrays = cons(robust_array, weak_array);
    /* create GC indicator  and rehash_size fields */
    hash_arrays = cons(hash_arrays, rehash_size);
    hash_arrays = cons(NIL, hash_arrays);
    

    table = SI_ALLOC(SI_Hashtable, HASH_TABLE_TYPE, SI_INSTANCE_TAG, SI_UGLY);

    SI_SET_WRAPPER(table, SI_WRAPPER_hash_table);
    HASH_METHOD(table) = method;
    HASH_ARRAY(table) = hash_arrays;
    SET_GC_FLAG(table);

    RESTORE_STACK();
    return VALUES_1(table);
}

Object hash_table_p (object)
    Object object;
{
    Declare_local_temp;
    return VALUES_1(HASH_TABLE_P(object) ? T : NIL);
}

Object gethash (key, hash_table, ldefault)
    Object key, hash_table, ldefault;
{
    Object array, hashcode, value;
    Object bucket, prev = NIL;
    SI_Hash hashval; SI_Htype test, type;
    SI_Dimension hindex;
    Declare_rehash_flag;

    if (!HASH_TABLE_P(hash_table)) {
	warn(1,"gethash: invalid hash_table - ~s", hash_table);
	return VALUES_2(NIL,NIL);
    }
    test = HASH_TEST_METHOD(hash_table);
    if (COMPARATOR_CAN_CONS(test))
	SAFE_GETHASH(key, hash_table, ldefault);

    /* hashcode is a combination of hashvalue and type representing
       as fixnum */
/*
    hashcode = FIND_HASH(key, test);
    GET_HASH_VALUES(hashval, type, hashcode);
*/
    SET_FIND_HASH(hashcode, hashval, type, key, test);

    MAYBE_REHASH() =  type; /* never do rehashing if the hashcode is robust */
    array = FIND_HASH_ARRAY(hash_table, type);
    hindex = HASH_INDEX(hashval, array);
    bucket = HAREF(array, hindex);

    LOOKUP_ENTRY(test, bucket, key, pair);

    /* the entry is found */
    if (TRUEP(bucket)) {
	value = ENTRY_VALUE(bucket,pair);
	return(VALUES_2(value, T));
    }
    
    /* MAYBE_REHASH() is FALSE if the array is ROBUST */
    else if (MAYBE_REHASH() && NEEDS_REHASH(hash_table)) 
	return REHASH_AND_GET(key, hash_table, hashcode, ldefault);
    
    else {
	if(!SUPPLIED_P(ldefault)) ldefault = NIL;
	return(VALUES_2(ldefault, NIL));
    }
}

/* assumes that rehash is needed;
   always operates on WEAK array */
static Object gethash_with_rehash (key, hash_table, hashcode, ldefault)
    Object key, hash_table, hashcode, ldefault;
{
    Object bucket, prev = NIL, array;
    SI_Hash hashval; SI_Htype test, type;
    SI_Dimension hindex;
    Object value;
    Object (*function)();
    SI_Stack_item *bottom;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(hash_table, key, ldefault);
    
    SET_GC_FLAG(hash_table);
    test     = HASH_TEST_METHOD(hash_table);
    function = GET_HASH_FUNCTION(HASH_TYPE(hash_table));
    array = WEAK_HASH_ARRAY(hash_table);

    bottom = Stack;
    SPREAD_ENTRIES(array);
    CLEAR_ARRAY(array);
    ASSEMBLY_ENTRIES(array, bottom, rehash_and_add_entry, test);

    GET_HASH_VALUES(hashval, type, hashcode);
    hindex = HASH_INDEX(hashval, array);
    bucket = HAREF(array, hindex);

    LOOKUP_ENTRY(test, bucket, key, pair);
    RESTORE_STACK();

    if (TRUEP(bucket)) {
	value = ENTRY_VALUE(bucket,pair);
	return(VALUES_2(value, T));
    }
    
    else if (NEEDS_REHASH(hash_table)) 
	return REHASH_AND_GET(key, hash_table, hashcode, ldefault);
    
    else {
	if(!SUPPLIED_P(ldefault)) ldefault = NIL;
	return(VALUES_2(ldefault, NIL));
    }
}


static SI_Ulong isxhash (object)
    Object object;
{
    Declare_local_temp;
    SI_Ulong hashval = 0, i = 0;
    char *p;

 LOOP:
    if (IMMEDIATE_P(object))
	hashval += (SI_Ulong) object;
    else if (CONSP(object)) {
	    hashval += isxhash(M_CAR(object)) ^ i++;
	    object = M_CDR(object);
	    goto LOOP;
	}
    else if (SYMBOLP(object)) {
	    p = isymbol_name(object);
	    while(*p) hashval += ((unsigned int) *p++ ^ i++);
	}
    else if (STRINGP(object)) {
	p = ISTRING(object);
	while(*p) hashval += ((unsigned int) *p++ ^ i++);	
    }
    else 
	    hashval += 0;

    return hashval;
}

static Object hash_eq (object)
    Object object;
{
    SI_Hash hash_val; SI_Htype type;

    SET_HASH_EQ(hash_val, type, object);
    return HASH_VALUES_2(hash_val, type);
}
 
static SI_Hash hash_bignum(arg)
    Object arg;
{
    SI_Hash hashval;
    SI_Bignum_digit_type *scan, *end;

    scan = BIGNUM_START_PTR (arg);
    end = scan + BIGNUM_LENGTH (arg);
    hashval = 0L;
    
    while (scan < end) 
	ASSIGN_MERGE_HASH_CODES(hashval, *scan++);
    
    return (hashval);
}

static Object hash_eql (object)
    Object object;
{
    SI_Hash hash_val;
    SI_Htype type;
    
    SET_HASH_EQL(hash_val, type, object);
    return HASH_VALUES_2(hash_val, type);
}

static Object hash_equal (object)
    Object object;
{
    SI_Htype type;
    SI_Hash  hashval;

    SET_HASH_EQUAL(hashval, type, object);
    return HASH_VALUES_2(hashval, type);
}

static Object hash_equalp (object)
    Object object;
{
    SI_Htype type;
    SI_Hash  hashval;

    SET_HASH_EQUALP(hashval, type, object);
    return HASH_VALUES_2(hashval, type);
}

static SI_Hash hash_equal_cons (object, depth, type)
    Object object;
    long depth;
    long *type;
{
    Declare_local_temp;
    Object x; long width = 0;
    SI_Hash hashval = 0L, h = 0L;
    
    if (depth > LIST_DEPTH) return(0L);
    x = M_CAR(object);

    while (width++ < LIST_WIDTH ) {
	
	if (SYMBOLP(x)) {
	    ASSIGN_MERGE_HASH_CODES(hashval, x);
	    REFINE_HASH_TYPE(*type, x);
	}
	else if (CONSP(x)) {
	    /* refines 'type' by side-effect */
	    h = hash_equal_cons(x, depth+1, type);
	    ASSIGN_MERGE_HASH_CODES(hashval, h);
	}
	else if (IMMEDIATE_P(x)) {
	    ASSIGN_MERGE_HASH_CODES(hashval, x);
	    /* no-op */
	    *type |= ROBUST;
	}
	else if (STRINGP(x)) {
	    SET_HASH_STRING(hashval, x); 
	    /* no-op */
	    *type |= ROBUST;
	}
	else if (BIT_VECTOR_P(x)) {
            SET_HASH_BIT_VECTOR(hashval, x); 
	    /* no-op */
	    *type |= ROBUST;
	}
	else if (!NUMBERP(x)) { 
	    hashval = OBJECT_TO_HASH(x); 
	    REFINE_HASH_TYPE(*type, x); 
	} 
	else  {
	    SET_HASH_NUMBER(hashval, x);
	    /* no-op */
	    *type |= ROBUST;
	}
	if (CONSP(object))
	    object = M_CDR(object);
	else break;
    }
    return hashval;
}

static SI_Hash hash_equalp_cons (object, depth, type)
    Object object;
    long depth;
    long *type;
{
    Declare_local_temp;
    Object x; long width = 0;
    SI_Hash hashval = 0L, h = 0;
    
    if (depth > LIST_DEPTH) return(0L);
    x = M_CAR(object);

    while (width++ < LIST_WIDTH ) {
	
	if (SYMBOLP(x)) {
	    ASSIGN_MERGE_HASH_CODES(hashval, x);
	    REFINE_HASH_TYPE(*type, x);
	}
	else if (CONSP(x)) {
	    /* refines 'type' by side-effect */
	    h = hash_equalp_cons(x, depth+1, type);
	    ASSIGN_MERGE_HASH_CODES(hashval, h);
	}
	else if (IMMEDIATE_P(x)) {
	    ASSIGN_MERGE_HASH_CODES(hashval, x);
	    /* no-op */
	    *type |= ROBUST;
	}
	else if (STRINGP(x)) {
	    SET_HASH_STRING(hashval, x); 
	    /* no-op */
	    *type |= ROBUST;
	}
        else if (ARRAYP(x)) {
            SET_HASH_ARRAY(hashval, x); 
	    /* no-op */
	    *type |= ROBUST;
	}
	else if (HASH_TABLE_P(x)) {
            SET_HASH_HASHTABLE(hashval, x); 
	    /* no-op */
	    *type |= ROBUST;
	}
	else if (!NUMBERP(x)) { 
	    hashval = OBJECT_TO_HASH(x); 
	    REFINE_HASH_TYPE(*type, x); 
	} 
	else  {
	    SET_HASH_NUMBER(hashval, x);
	    /* no-op */
	    *type |= ROBUST;
	}
	if (CONSP(object))
	    object = M_CDR(object);
	else break;
    }
    return hashval;
}

Object sxhash (object)
    Object object;
{
    Declare_local_temp;
    SI_Long hashval;
    hashval = isxhash(object) & (SI_Ulong)IMOST_POSITIVE_FIXNUM;
    return VALUES_1(FIX(hashval));
}

Object remhash (key, hash_table)
    Object key, hash_table;
{
    Declare_local_temp;
    Object array, hashcode;
    Object bucket, prev = NIL;
    SI_Hash hashval; SI_Htype test, type;
    SI_Dimension hindex;
    Declare_rehash_flag;

    if (!HASH_TABLE_P(hash_table)) {
	warn(1,"remhash: invalid hash_table - ~s", hash_table);
	return VALUES_1(NIL);
    }
    test = HASH_TEST_METHOD(hash_table);
    if (COMPARATOR_CAN_CONS(test))
	SAFE_REMHASH(key, hash_table);

    /* hashcode is a combination of hashvalue and type representing
       as fixnum */

/*    hashcode = FIND_HASH(key, test);
    GET_HASH_VALUES(hashval, type, hashcode);
*/
    SET_FIND_HASH(hashcode, hashval, type, key, test);

    MAYBE_REHASH() = type; /* never do rehashing if the hashcode is robust */
    array = FIND_HASH_ARRAY(hash_table, type);
    array = FIND_HASH_ARRAY(hash_table, type);
    hindex = HASH_INDEX(hashval, array);
    bucket = HAREF(array, hindex);

    LOOKUP_ENTRY(test, bucket, key, pair);

    /* the entry is found */
    if (TRUEP(bucket)) {
        if (TRUEP(prev)) NEXT_ENTRY(prev) = NEXT_ENTRY(bucket);
	else HAREF(array, hindex) = NEXT_ENTRY(bucket);
	MINUMINU_ARRAY_COUNTER(array);
	return(VALUES_1(T));
    }
    
    /* MAYBE_REHASH() is FALSE if the array is ROBUST */
    else if (MAYBE_REHASH() && NEEDS_REHASH(hash_table)) 
	return REHASH_AND_REMOVE(key, hash_table, hashcode);
    
    else 
	return(VALUES_1(NIL));
}

static Object remhash_with_rehash (key, hash_table, hashcode)
    Object key, hash_table, hashcode;
{
    Declare_local_temp;
    Object bucket, prev = NIL, array;
    SI_Hash hashval; SI_Htype test, type;
    SI_Dimension hindex;
    Object (*function)();
    SI_Stack_item *bottom;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(hash_table, key);
    
    SET_GC_FLAG(hash_table);
    test     = HASH_TEST_METHOD(hash_table);
    function = GET_HASH_FUNCTION(HASH_TYPE(hash_table));
    array = WEAK_HASH_ARRAY(hash_table);

    bottom = Stack;
    SPREAD_ENTRIES(array);
    CLEAR_ARRAY(array);
    ASSEMBLY_ENTRIES(array, bottom, rehash_and_add_entry, test);

    GET_HASH_VALUES(hashval, type, hashcode);
    hindex = HASH_INDEX(hashval, array);
    bucket = HAREF(array, hindex);

    LOOKUP_ENTRY(test, bucket, key, pair);
    RESTORE_STACK();

    /* the entry is found */
    if (TRUEP(bucket)) {
        if (TRUEP(prev)) NEXT_ENTRY(prev) = NEXT_ENTRY(bucket);
	else HAREF(array, hindex) = NEXT_ENTRY(bucket);
	MINUMINU_ARRAY_COUNTER(array);
	return(VALUES_1(T));
    }

    else if (NEEDS_REHASH(hash_table)) 
	return REHASH_AND_REMOVE(key, hash_table, hashcode);
    
    else 
	return(VALUES_1(NIL));
}


/****************************************************************************
 * 
 * Hash table iteration facilities are provided by  functions 
 * begin_hash_table_iterator(), hash_table_iterator(), 
 * end_hash_table_iterator(), cleanup_hash_table_iterator()
 * 
 * begin_hash_table_iterator creates and returns an object State
 * which represents the state of the iteration process in GC-safe way.
 * The implementation uses the Lisp stack to provide reliable iteration
 * that mighht be interrupted by GC and/or hash array rehhashment.
 *
 * In oder to support nonlocal exits from inside iteration procedures
 * the iteration code emmited by the translator is surrounded by
 * UNWIND_PROTECT forms
 *
 * The example 
 *
 *     (with-hash-table-iterator (next ht) {body})
 *
 * would get translated into :
 *
 ****************************************************************************/


Object begin_hash_table_iterator (table)
    Object table;
{
    Declare_local_temp;
    Object state, array;
    Declare_stack_pointer;
    State *st;

    SAVE_STACK();

    PROTECT_1(table);
    state = MAKE_ITERATOR_STATE();
    st = ISTATE(state);
    RESTORE_STACK();

    st->phase = FALSE;
    st->old  = Stack;
    STACK_PUSH(WEAK_HASH_ARRAY(table));
    st->next = Stack;
    
    array = ROBUST_HASH_ARRAY(table);

    /* move entries of the array onto the stack */
    SPREAD_ENTRIES(array); 
    st->top  = Stack;

    return VALUES_1(state);
}

Object hash_table_iterator (state)
    Object state;
{
    Declare_local_temp;
    Object key, value, entry, array;
    State *st;

    st = ISTATE(state);

NOT_MORE_THAN_TWICE:
    /* perform the following for both hash arrays */
    if (st->next == st->top) {
	if (st->phase) {
	    return VALUES_1(NIL);
	}
	else {
	    /* iterate through the WEAK table */
	    st->phase = TRUE;
	    /* the weak table is stored at the bottom */
	    array = STACK_TOP(st->old);
	    Stack = st->old;
	    st->next = Stack;
	    SPREAD_ENTRIES(array);
	    st->top = Stack;
	    goto NOT_MORE_THAN_TWICE;
	}
    }
    else {
	entry = STACK_TOP(st->next++);
	key   = VENTRY_KEY(entry);
	value = VENTRY_VALUE(entry);
	return VALUES_3(T, key, value);
    }
}


/* This function provides appropriate stack operations in the case of
 * non local exits from the body of an iterator. 
 */

Object end_hash_table_iterator (state) 
    Object state;
{
    Declare_local_temp;
    State *st;
    
    /* if state was not successfully created by begin_hash_table_iterator,
       do nothing and return T */
    if (TRUEP(state)) {
	st = ISTATE(state);
	/* shift the contents of the stack that possible might be stored
	   above the st->top position to the dt->old position */
	while (st->top < Stack) 
	    *st->old++ = *st->top++;
	Stack = st->old;
    }
    return VALUES_1(T);
}

/* normal (not by 'throw') ending of hash table iteration */
Object cleanup_hash_table_iterator (state) 
    Object state;
{
    Declare_local_temp;
    State *st;
    
    /* if state was not successfully created by begin_hash_table_iterator,
       do nothing and return T */
    if (TRUEP(state)) {
	st = ISTATE(state);
	Stack = st->old;
    }
    return VALUES_1(T);
}

Object maphash (func, hash_table)
    Object func, hash_table;
{
    Declare_local_temp;
    Object hash_array;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(func, hash_table);

    hash_array = WEAK_HASH_ARRAY(hash_table);
    FOR_EVERY_PAIR(hash_array, func);

    hash_array = ROBUST_HASH_ARRAY(hash_table);
    FOR_EVERY_PAIR(hash_array, func);

    RESTORE_STACK();
    return VALUES_1(NIL);
}

/* non-consing copying procedure */
static void ncopy_hash_table (table,array)
    Object table, array;
{
    SI_Dimension i, size;
    Object bucket, entry;
    SI_Htype test;

    test = HASH_METHOD(table);
    bucket = HASH_ARRAY(table);
    HASH_ARRAY(table) = array;
    array = bucket;
    size = HASH_SIZE(table);
    for (i = 0; i < size; i++) {
	for (entry = SVREF(array,i); 
	     entry != NIL; entry = bucket) {
	    bucket = M_CDR(entry);
	    add_entry(entry,table,test);
	}
    }
}

Object clrhash (hash_table)
    Object hash_table;
{
    Declare_local_temp;
    Object hash_array;

    hash_array = WEAK_HASH_ARRAY(hash_table);
    CLEAR_ARRAY(hash_array);
    ARRAY_COUNTER(hash_array) = FIX(0);

    hash_array = ROBUST_HASH_ARRAY(hash_table);
    CLEAR_ARRAY(hash_array);
    ARRAY_COUNTER(hash_array) = FIX(0);

    return VALUES_1(hash_table);
}


Object hash_table_count (hash_table)
    Object hash_table;
{
    Declare_local_temp;
    SI_Long count = 0;

    count += IFIX(ARRAY_COUNTER(ROBUST_HASH_ARRAY(hash_table)));
    count += IFIX(ARRAY_COUNTER(  WEAK_HASH_ARRAY(hash_table)));
    return VALUES_1(FIX(count));
}

/* The implementation supports hash tables with  2 hash arrays:
 * one of them for entries with stable [GC-unsensitive] hashes and
 * another for enrties with unstable hashes. Only the last array
 * could be rehashed after GC. The macro MAYBE_REHASH() indicates
 * the situations when rehashment can be invoked  */

/*ARGSUSED*/
Object sethash (key, hash_table, value, ignore)
    Object key, hash_table, value, ignore;
{
    Declare_local_temp;
    Object bucket, prev = NIL, array, hashcode;
    SI_Hash hashval; SI_Htype test, type;
    SI_Dimension hindex;
    
    Declare_rehash_flag;

    test = HASH_TEST_METHOD(hash_table);
    if (COMPARATOR_CAN_CONS(test))
	SAFE_SETHASH(key, hash_table, value);

    /* hashcode is a combination of hashvalue and type represented
       as fixnum */
/*
    hashcode = FIND_HASH(key, test);
    GET_HASH_VALUES(hashval, type, hashcode);
*/

    SET_FIND_HASH(hashcode, hashval, type, key, test);

    MAYBE_REHASH() = type;
    array = FIND_HASH_ARRAY(hash_table, type);
    hindex = HASH_INDEX(hashval, array);
    bucket = HAREF(array, hindex);

    LOOKUP_ENTRY(test, bucket, key, pair);

    /* the entry is found */
    if (TRUEP(bucket)) {
	SET_ENTRY_VALUE(bucket, pair, value);
	return VALUES_1(value);
    }

    /* MAYBE_REHASH() is FALSE if the array is ROBUST */
    else if (MAYBE_REHASH() && NEEDS_REHASH(hash_table)) 
	return REHASH_AND_SET(test,key, hash_table, value, hashcode, ignore);

    /* this helper function conses */
    else return(create_and_add_entry(hash_table,key,value,hashcode));
}
Object set_gethash(o1, o2, o3)
    Object o1, o2, o3;
{
    return sethash(o1, o2, o3, NIL);
}

/****************************************************************************
 * Two functions: safe_sethash_with_rehash and
 *                  unsafe_sethash_with_rehash
 *  store a value in a hash_table assuming that rehashing  is needed;
 *  each function operates on a "weak" array of the hash_table
 *   
 *  safe_sethash_with_rehash supports hash tables which use
 *  hash methods that might cons
 ***************************************************************************/
make_rehashing_set_function (safe_sethash_with_rehash,
                             SAVE_TABLE_AND_PAIR,
			     REHASH_THE_KEY,
			     key, hash_table, value,
                             hashcode, ignore)   

make_rehashing_set_function (unsafe_sethash_with_rehash,
                             SAVE_NOTHING, NOOP,
			     key, hash_table, value,
                             hashcode, ignore)


/* helper function which takes protection away from sethash function */
static Object create_and_add_entry (table,key,value,hashcode)
    Object table, key, value, hashcode;
{
    Declare_local_temp;
    Object bucket, entry;
    Object harray;
    SI_Htype type,test;
    SI_Hash hashval;
    Declare_stack_pointer;
    SI_Dimension hindex;

    SAVE_STACK();
    PROTECT_3(table, key, value);
    PROTECTI_3(harray, bucket, entry);

    test     = HASH_METHOD(table);
    GET_HASH_VALUES(hashval, type, hashcode);
    harray = FIND_HASH_ARRAY(table, type);
    bucket = FIND_HASH_ARRAY(table, type);
    hindex = HASH_INDEX(hashval, harray);
    bucket = HAREF(harray, hindex);

    /* add new (key . value) to hash table */
    if (HASHED_ENTRY_P(test))
	MAKE_HASHED_ENTRY(entry, hashcode, key, value, bucket);
    else 
	MAKE_ENTRY(entry, key, value, bucket);
    
    HAREF(harray, hindex) =  entry;
    PLUSPLUS_ARRAY_COUNTER(harray);
    
    if (ARRAY_FULL_P(harray)) 
	GROW_ARRAY(table, type); 
    RESTORE_STACK();
     return VALUES_1(value);
}

/* assumes that rehash is needed */
static void rehash (hash_table)
    Object hash_table;
 {
    Object array;
    SI_Htype test;
    SI_Stack_item *bottom;

    array = WEAK_HASH_ARRAY(hash_table);
    test     = HASH_METHOD(hash_table);

    bottom = Stack;
    SPREAD_ENTRIES(array);
    CLEAR_ARRAY(array);
    ASSEMBLY_ENTRIES(array, bottom, rehash_and_add_entry, test);
    SET_GC_FLAG(hash_table);

}

/* non-consing function */
static void add_entry (entry, array, test)
    Object entry, array;
    SI_Htype test;
{
    Object key, bucket = NIL, hashcode;
    SI_Hash hashval; SI_Htype  type;
    Object (*func)();

    func = GET_HASH_FUNCTION(test); 
    
    if (HASHED_ENTRY_P(test) && HASH_FUNC_CAN_CONS(test)) {
	hashcode = VENTRY_CODE(entry);
	GET_HASH_VALUES(hashval, type, hashcode);
    }
    else if (!(HASHED_ENTRY_P(test)) && HASH_FUNC_CAN_CONS(test))
	error (1, "add_entry: needs protection, hash function can cons");
    else {/* never cons here */
	/*hashcode = (*func)(ENTRY_KEY(entry, entry));*/
	key = ENTRY_KEY(entry, entry);
	SET_FIND_HASH(hashcode, hashval, type, key, test);
    }
    bucket = FIND_BUCKET(hashval, array);
    
    /* link up the chain */
    SI_ISVREF(entry,2) = bucket;

    /* It is not necessary to update the hashcode field here;
     * if the entry is hashed, keep the old value;
     * otherwise do nothing  */

    HAREF(array, HASH_INDEX(hashval, array)) =  entry;

}

/* this function can cons. It always rehashes the hashcode of 
 * an entry befor liking it 
 */
static void rehash_and_add_entry (entry, array, test)
    Object entry, array;
    SI_Htype test;
{
    Object key, bucket = NIL, hashcode;
    SI_Hash hashval; SI_Htype  type;
    /*
    Object (*func)();
    */
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(entry, array);
/*
    func = GET_HASH_FUNCTION(test); 
    hashcode = (*func)(ENTRY_KEY(entry, entry));
    GET_HASH_VALUES(hashval, type, hashcode);
*/
    key = ENTRY_KEY(entry, entry);
    SET_FIND_HASH(hashcode, hashval, type, key, test);

    bucket = FIND_BUCKET(hashval, array);
    
    SI_ISVREF(entry,2) = bucket;
    
    if (HASHED_ENTRY_P(test))
	SI_ISVREF(entry,3) = hashcode;
    HAREF(array, HASH_INDEX(hashval, array)) =  entry;
    RESTORE_STACK();

}

static SI_Long new_hash_size (table, size)
    Object table;
    SI_Long size;
{
    SI_Long rehash_val, new_size;
    
    rehash_val = IFIX(REHASH_SIZE_CODE(table));
    new_size = REHASH_UPGRADING(size, rehash_val);
    new_size = SI_next_prime(new_size);

    return new_size;
}


static SI_Long rehash_normalize (size)
       SI_Long size;
{

    if (size < 1L)  size = 1L;
    else if (size > REHASH_SIZE_LIMIT) size = REHASH_SIZE_LIMIT;

    return size;
}

/****************************************************************************
 * 
 * Prime number generator
 *
 ****************************************************************************/

#define ODDP(x)    ((x)&1L)
#define EVENP(x)   (!ODDP(x))
#define HALF(x)    ((x) >> 1)


SI_Long jacobi (a, n)
    SI_Ulong a, n;
{
    SI_Ulong t1, t2;
    int sign = 1;

    while(a != 1) {
	if (EVENP(a)) {
	    t1 = HALF(n-1);
	    t2 = HALF(n+1);
	    if (EVENP(t1)) t1 = HALF(t1);
	    else t2 = HALF(t2);
	    sign  ^= sign;
	    a = HALF(a);
	}
	else {
	    t1 = HALF(n-1);
	    t2 = HALF(a-1);
	    sign  ^= sign;
	    t1 = a;
	    a = n % a;
	    n = t1;
	}
    }
    return (sign ? (SI_Long)a : -(SI_Long)a);
}

#define SMOD(n, m) ((n >= m) ? n % m : n)
#define BIG_NUMBER (1L << 15)

static SI_Ulong expmod(b, e, m)
    SI_Ulong b, e, m;
{
    SI_Ulong res, i, temp;

    if (e == 0) res = 1;
    else if (EVENP(e)) {
	temp = expmod(b, HALF(e), m);
	if (temp < BIG_NUMBER) {
	    res = temp * temp;
	    res = res % m;
	}
	else 
	    for (res = 0, i = temp = SMOD(temp,m); i; i--) {
		res  += temp;
		res = SMOD(res,m);
	    }
    }
    else {
	temp = expmod(b, (e-1), m);
	if (temp < BIG_NUMBER) {
	    res = b * temp;
	    res = res % m;
	}
	else 
	    for (res = 0, i = SMOD(b,m), temp = SMOD(temp,m); i; i--) {
		res += temp;
		res = SMOD(res,m);
	    }
    }
    return res;
}

/* Primeness tester. REPEAT_PRIMEP_TEST indicates how many times try the test
 * for given p.
 */
#define REPEAT_PRIMEP_TEST 3
int primep(p)
   SI_Ulong p;
{
    SI_Ulong d;
    SI_Long i, k, j, e;

    if (EVENP(p)) return FALSE;

    for (i = 3, k= 0; k < REPEAT_PRIMEP_TEST; i+=2) {
	d = SI_igcd(p, i);
	if (d == 1) {
	    j = jacobi(i, p);
	    e = expmod(i, HALF(p-1), p);
	    if (e == (p-1)) e = -1;
	    if ((e == j || e == -j))
		k++;
	    else break;
	}
	else return FALSE;
    }
    return ((k < 2) ? FALSE : TRUE);
}

void primes()
{
    SI_Long p = 7 , delta = 10;
    int r;


    while(TRUE) {
	if (r = primep(p)) {
	    printf(" r %d",r);
	    printf("\n prime %d", p);
	    p = p + delta;
	}
	else {
	    printf("\n non   %d", p);
	    p++;
	}
    }
}

/* given a number p returns smallest prime number that
 *  greater or equal p
 */
SI_Ulong SI_next_prime(p)
    SI_Ulong p;
{
    if (EVENP(p)) ++p;
    while(!primep(p)) p+=2;
    return p;
}
