/*
 *  HASH.H - Macro definitions for hash.c
 *  Copyright (c) 1991 Chestnut Software, Inc.  All rights reserved.
 *
 *  Created: 9/8/91
 *
 *  Author:  Dmitry Nizhegorodov
 */

/****************************************************************************
 *
 *  Hash tables: accessors;  hashing, search and relocation macros
 *
 * 
 ****************************************************************************/

extern SI_Long SI_igcd();

#define M_BEGIN if (TRUE) {
#define M_END  } else FALSE

#define HASHED_ENTRY_P(t) (t > HASH_EQL)

/****************************************************************************
 *
 *  Configuration
 *
 ****************************************************************************/

/* representation of hash-array entries */
#define CONS_ENTRIES    0
#define VECTOR_ENTRIES  1

/* implementation of hash table iterators */
#define STACK_BASED     0
#define HEAP_BASED      1

#ifndef HASH_TABLE_ITERATORS 
#define HASH_TABLE_ITERATORS  STACK_BASED
#endif

#ifndef HASH_ARRAY_ENTRIES
#define HASH_ARRAY_ENTRIES  VECTOR_ENTRIES
#endif

/****************************************************************************
 *
 *  Data types
 *
 ****************************************************************************/

typedef unsigned long SI_Hash;
typedef long    SI_Htype;
typedef long    SI_Htest;

#define fast register

/****************************************************************************
 *
 *  Hash tables
 *
 ****************************************************************************/

#define ROBUST 0
#define WEAK   1

#define RESIDENTP(o) 0
#define ROBUSTP(type)   (!(type))

#define HASH_TYPE(t)  HASH_METHOD(t)
#define HASH_GC_FLAG(htab)  M_CAR(HASH_ARRAY(htab))

/* GC FLAG field specifies whether or not rehash is needed. */
#define UPDATE_GC_FLAG() \
    (SI_gc_genobj =  CONSP(SI_gc_genobj) \
     ? SI_gc_genobj : cons(FIX(0), FIX(0)))

#define SET_GC_FLAG(htab) \
    (UPDATE_GC_FLAG(), \
     ((HASH_GC_FLAG(htab))= SI_gc_genobj))

#define SAFE_SET_GC_FLAG(htab) \
    ( \
     STACK_PUSH(htab), \
     UPDATE_GC_FLAG(), \
     htab = STACK_POP(), \
     HASH_GC_FLAG(htab) = SI_gc_genobj)

#define COMPUTE_THRESHOLD(s)  (FIX(2*s))  /* fix later */

#define TABLE_COUNTER(t) \
 (IFIX(ARRAY_COUNTER(ROBUST_HASH_ARRAY(t))) + \
 IFIX(ARRAY_COUNTER(WEAK_HASH_ARRAY(t))))

#define NEEDS_REHASH(tab) \
    (HASH_GC_FLAG(tab) != SI_gc_genobj)

#define FORCE_REHASH(tab) rehash(tab)

/* Depending of the nature of the hash method some
 * extra protection might be necessary 
 */
#define REHASH_AND_SET(test, key, hash_table, value, hashcode, ignore)  \
    (HASH_FUNC_CAN_CONS(test) \
     ? safe_sethash_with_rehash(key, hash_table, value, hashcode, ignore) \
     : unsafe_sethash_with_rehash(key, hash_table, value, hashcode, ignore)) 

#define REHASH_AND_GET        gethash_with_rehash
#define REHASH_AND_REMOVE     remhash_with_rehash

/* Hash table initialization default values */
#define Default_hash_size		FIX(67L)
#define Default_rehash_size		FIX(10L) 
#define Default_rehash_threshold	FIX(134L)

/****************************************************************************
 *
 *  Hash table arrays                                                         
 *
 ****************************************************************************/

/* Each array has 2 extra fields in addition to actual table size:
 * Counter and Threshold */
#define ARRAY_EXTRA_FIELDS 2
#define COUNTER_FIELD      0
#define THRESHOLD_FIELD    1

#define HASH_ARRAYS(htab)   (M_CADR(HASH_ARRAY(htab)))
#define REHASH_SIZE_CODE(htab)   (M_CDDR(HASH_ARRAY(htab)))
#define ROBUST_HASH_ARRAY(t) (M_CAR(HASH_ARRAYS(t)))
#define   WEAK_HASH_ARRAY(t) (M_CDR(HASH_ARRAYS(t)))
#define FIND_HASH_ARRAY(tab, type) \
    (type ? WEAK_HASH_ARRAY(tab) : ROBUST_HASH_ARRAY(tab))

#define ARRAY_FULL_P(a)  \
    (ARRAY_COUNTER(a) > ARRAY_THRESHOLD(a))

#define ARRAY_FULL_SIZE(hsize)  (hsize + ARRAY_EXTRA_FIELDS)

#define MAKE_HASH_ARRAY(hsize)  make_vector(FIX(ARRAY_FULL_SIZE(hsize)), NIL)

/* array accessors */

#define ARRAY_COUNTER(arr)    (SI_ISVREF(arr, COUNTER_FIELD))

#define PLUSPLUS_ARRAY_COUNTER(harray) \
   (ARRAY_COUNTER(harray) = FIX(IFIX(ARRAY_COUNTER(harray)) + 1L))

#define MINUMINU_ARRAY_COUNTER(harray) \
   (ARRAY_COUNTER(harray) = FIX(IFIX(ARRAY_COUNTER(harray)) - 1L))

#define ARRAY_THRESHOLD(arr)  (SI_ISVREF(arr, THRESHOLD_FIELD))

#define HASH_ARRAY_SIZE(a) \
    (SI_PRIMITIVE_VECTOR_LENGTH(a) - ARRAY_EXTRA_FIELDS)

#define HASH_INDEX(hash, a)     (hash % HASH_ARRAY_SIZE(a))

/* hash array contents accessor */
#define HAREF(arr, i)  (SI_ISVREF(arr, i + ARRAY_EXTRA_FIELDS))

#define FIND_BUCKET(hash,a) (HAREF(a, HASH_INDEX(hash,a)))

#define NEW_HASH_SIZE(tab, size)  (new_hash_size(tab, size))
#define ADJUST_ARRAY(t, a) \
    (MAKE_HASH_ARRAY(NEW_HASH_SIZE(t, HASH_ARRAY_SIZE(a))))

#define INIT_HASH_ARRAY(tab, type, arr) \
  M_BEGIN \
    if (type) WEAK_HASH_ARRAY(tab) = arr ; \
    else    ROBUST_HASH_ARRAY(tab) = arr;  \
  M_END

/*************************************************************************
 *
 * Hash array lookup primitives
 * 
 ************************************************************************/

/* possible inline EQL replacing it by INLINE_EQL */
#define LOOKUP_ENTRY(test, buck, key, pair) \
   M_BEGIN \
    switch (test) { \
    case HASH_EQ : \
	  LOOKUP_WITH_PREDICATE(EQ,bucket,key,pair); \
    case HASH_EQL : \
	  LOOKUP_WITH_PREDICATE(EQL,bucket,key,pair); \
    case HASH_EQUAL : \
          HASHED_LOOKUP_WITH_PREDICATE( EQUAL_METHOD, \
             hash_table, hashcode, bucket, key, pair); \
    case HASH_EQUALP: \
          HASHED_LOOKUP_WITH_PREDICATE( EQUALP_METHOD, \
             hash_table, hashcode, bucket, key, pair); \
    default: \
	error(1,"hash lookup: wrong hash index: ~S", FIX(test)); \
    } \
  M_END

/* WITH_prev indicates that the lookup macro has to keep track of
   pointers to previous entry. It is necessary for replacement/ removing
   operations on hash arrays
 */
#define WITH_prev TRUE
#if WITH_prev == TRUE
#define MAYBE_STORE_PREV(b)  (prev = (b))
#else
#define MAYBE_STORE_PREV(b)  (b)
#endif

#define LOOKUP_WITH_PREDICATE(pred, bucket, key, pair) \
	while (TRUEP(bucket)) { \
	    if (MATCH_ENTRY(pred,bucket,key,pair)) \
		break; \
	    bucket = NEXT_ENTRY(MAYBE_STORE_PREV(bucket)); \
	} \
	break

/* Specialized hash-search methods
 *
 * The implementation assumes that any method do not conses. If in future
 *  releases it will be necessary to provide methods that might cons
 * [or, say, provide more sophisticated  EQUAL/EQUALP that must cons],
 * lookup with such a methods can be implemented by means of separate
 * routines with GC protection 
 * [see make_rehashing_set_function macro definition below]
 *
 */

/* later implement with call to remoute specialized function */
#define EQUAL_METHOD(tab, hashcode, bucket, key, pair) \
		if MATCH_HASHED_ENTRY(EQUAL,bucket,pair,key) \
		    break

/* later implement with call to remoute specialized function */
#define EQUALP_METHOD(tab, hashcode, bucket, key, pair) \
		if MATCH_HASHED_ENTRY(EQUALP,bucket,pair,key) \
		    break

#define HASHED_LOOKUP_WITH_PREDICATE(meth, tab, hashcode, bucket, key, pair) \
	while (TRUEP(bucket)) { \
	    if (MATCH_HASH(bucket, pair, hashcode)) { \
	        meth(tab, hashcode, bucket, key, pair); \
	    } \
	    bucket = NEXT_ENTRY(MAYBE_STORE_PREV(bucket)); \
	} \
	break


/****************************************************************************
 *
 *  Prime numbers
 *
 ****************************************************************************/

#define BASE_PRIME_NUMBER()  61

/****************************************************************************
 *
 *  Hash codes, functions and hash types
 *
 ****************************************************************************/

/* initial values for hash table "test" */
#define HASH_EQ		0
#define HASH_EQL	1
#define HASH_EQUAL	2
#define HASH_EQUALP	3
#define HASH_TEST	7
#define HASH_PERCENT	8	/* clear=fixed, set=percent */

#define HASH_VALUE_LENGTH (SI_BITS_PER_BYTE * sizeof(SI_Hash))


/****************************************************************************
 * 
 *  Inlined type-specific hash methods
 *
 ****************************************************************************/

/* The following SET_HASH_foo macros have SET_ prefix because they are
 * assignment macros; 'hashval' is assumed to be  SI_Hash <hashval>=0L
 * 
 * Every macro produces a ROBUST hash value; note that they return
 * hash values, not hash codes, mostly because knowing  the hash type
 * it is better not to duplicate HASH_VALUES_2
 * [in current implementation it is no-op for ROBUST things ]
 */
#define SET_HASH_BIGNUM(hashval, arg) \
  M_BEGIN \
    /* assuming SI_Hash hashval; */ \
    SI_Bignum_digit_type *scan, *end; \
 \
    scan = BIGNUM_START_PTR (arg); \
    end = scan + BIGNUM_LENGTH (arg); \
    /* assuming hashval = 0L; */ \
     \
    while (scan < end)  \
	ASSIGN_MERGE_HASH_CODES(hashval, *scan++); \
  M_END

#define SET_HASH_RATIO(hashval, arg) \
    M_BEGIN \
     ASSIGN_MERGE_HASH_CODES(hashval, SI_RATIO_NUMERATOR(arg)); \
     ASSIGN_MERGE_HASH_CODES(hashval, SI_RATIO_DENOMINATOR(arg)); \
    M_END

#define SET_HASH_COMPLEX(hashval, arg) \
   M_BEGIN  \
     ASSIGN_MERGE_HASH_CODES(hashval, COMPLEX_REAL(arg)); \
     ASSIGN_MERGE_HASH_CODES(hashval, COMPLEX_IMAG(arg)); \
   M_END

#define SET_HASH_NUMBER(h, o) \
        if (FIXNUMP(o)) \
	    h = OBJECT_TO_HASH(o);  \
	else if (DOUBLEP(o)) \
	    h = (SI_Hash)IDOUBLE(o); \
        else if (BIGNUMP(o))  \
	    SET_HASH_BIGNUM(h, o); \
	else if (RATIOP(o)) \
	    SET_HASH_RATIO(h, o); \
	else if (COMPLEXP(o)) \
	    SET_HASH_COMPLEX(h, o); \
	else error(2, "SET_HASH: wrong number ~A", o)

#define SET_HASH_STRING(h, o) \
M_BEGIN \
    fast char * sp;  \
    for (sp = ISTRING(o);*sp; sp++) \
    ASSIGN_MERGE_HASH_CODES(h, *sp); \
M_END

/* to be improved later */
#define SET_HASH_BIT_VECTOR(h, o) \
    (ASSIGN_MERGE_HASH_CODES(h, IFIX(SI_GENERAL_VECTOR_FILL_POINTER(o))))

/* to be improved later */
#define SET_HASH_ARRAY(h, o) \
    (ASSIGN_MERGE_HASH_CODES(h, SI_GENERAL_ARRAY_RANK(o)))

/* to be improved later */
#define SET_HASH_HASHTABLE(h, o) \
    (ASSIGN_MERGE_HASH_CODES(h, IFIX(hash_table_count(o))))


/****************************************************************************
 * 
 *  Inlined built-in hash methods
 *
 ****************************************************************************/

#define SET_HASH_EQ(val, type, obj) \
/*     SI_Hash val; \
 *     SI_Htype type; \
 *     Object obj; \
 *     SI_Htest test; \
 */ \
	val = OBJECT_TO_HASH(obj); \
	SET_HASH_TYPE(type, obj)

#define SET_HASH_EQL(val, type, obj) \
/*     SI_Hash val; \
 *     SI_Htype type; \
 *     Object obj; \
 *     SI_Htest test; \
 */ \
	val = 0L;  \
	type = ROBUST; \
	if (!NUMBERP(obj)) { \
	    val = OBJECT_TO_HASH(obj);  \
	    SET_HASH_TYPE(type, obj); \
	} \
	else  \
	    SET_HASH_NUMBER(val, obj)

#define SET_HASH_EQUAL(val, type, obj) \
/*     SI_Hash val; \
 *     SI_Htype type; \
 *     Object obj; \
 *     SI_Htest test; \
 */ \
	val = 0L;  \
	type = ROBUST; \
	if (CONSP(obj)) \
	    val = hash_equal_cons(obj, 0, &type); \
	else if (STRINGP(obj)) { \
	    SET_HASH_STRING(val, obj); \
	} \
	else if (BIT_VECTOR_P(obj)) \
            SET_HASH_BIT_VECTOR(val, obj); \
	else if (!NUMBERP(obj)) { \
	    val = OBJECT_TO_HASH(obj); \
	    SET_HASH_TYPE(type, obj); \
	} \
	else  \
	    SET_HASH_NUMBER(val, obj)

#define SET_HASH_EQUALP(val, type, obj) \
	val = 0L;  \
	type = ROBUST; \
	if (CONSP(obj)) \
	    val = hash_equalp_cons(obj, 0, &type); \
	else if (STRINGP(obj)) { \
	    SET_HASH_STRING(val, obj); \
	} \
        else if (ARRAYP(obj)) \
            SET_HASH_ARRAY(val, obj); \
	else if (HASH_TABLE_P(obj)) \
            SET_HASH_HASHTABLE(val, obj); \
	else if (!NUMBERP(obj)) { \
	    val = OBJECT_TO_HASH(obj); \
	    SET_HASH_TYPE(type, obj); \
	} \
	else  \
	    SET_HASH_NUMBER(val, obj)

/****************************************************************************
 * 
 *  Internal inlined hash-value, hash-type and hash-code computation macros
 *
 ****************************************************************************/

/* getting bigger */
#define FIND_HASH(o, t) (*Hash_functions[t])(o)

/* New "FIND_HASH"
 * This is for an interface where all 3 values are in use
 * ***the current approach is to store "hashcode" rather than "hashvalue"
 * in "hashed entries"; after fixing it, it is possible not to compute
 * "hashcodes" in most of the functions
 */
#define SET_FIND_HASH(hash_code, hashval, hashtype, obj, test) \
/*     Objject hash_code; \
 *     SI_Hash hashval; \
 *     SI_Htype hashtype; \
 *     Object obj; \
 *     SI_Htest test; \
 */ \
    SET_HASH_VALUES(hashval, hashtype, obj, test); \
    hash_code = HASH_VALUES_2(hashval, hashtype)

/* provides interface obj+test -> hashcode */
#define FIND_HASH_CODE(hash_code, obj, test) \
M_BEGIN  \
    SI_Hash s_f_h_val; \
    SI_Htype s_f_h_type; \
    SET_HASH_VALUES(s_f_h_val, s_f_h_type, obj, test); \
    hash_code = HASH_VALUES_2(s_f_h_val, s_f_h_type); \
M_END

/* Given an object and hash test code, computes
 * the hash value and the hash type.
 * Requires 
 *     SI_Hash val;
 *     SI_Htype type;
 *     Object obj;
 *     SI_Htest test;
 *
 * This is an operator, not an expression, because:
 * (1) it is used always in the context where operators can be used;
 * (2) it is desirable to inline everything, and some operations
 * like code for bignums, can't be implemented as 
 * expressions. 
 *
 * NOTE: some pieces of the code looks alike. Unfortunatelly, there is no way
 * to use advantage of "switch" and in the same time share a lot of code
 */
#define SET_HASH_VALUES(val, type, obj, test)  \
/*     SI_Hash val; \
 *     SI_Htype type; \
 *     Object obj; \
 *     SI_Htest test; \
 */ \
M_BEGIN  \
    switch (test) {  \
    case HASH_EQ:  \
        SET_HASH_EQ(val, type, obj); \
	break;  \
    case HASH_EQL:  \
        SET_HASH_EQL(val, type, obj); \
	break; \
    case HASH_EQUAL: \
	SET_HASH_EQUAL(val, type, obj); \
	break; \
    case HASH_EQUALP: \
	SET_HASH_EQUALP(val, type, obj); \
	break; \
    default:  \
	/* invoke anything else using the table of hash metods */ \
	GET_HASH_VALUES(val, type, (*Hash_functions[test])(obj)); \
    }  \
    /* it is strictly necessary here in oder to produce exactly the same \
     * value that GET_HASH_VALUES(val, type, HASH_VALUES_2(val, type)) \
     * can produce \
     */ \
    val = CORRECT_HASH_VALUE(val); \
M_END
    
/****************************************************************************
 * 
 *  HAsh value merging macros
 *
 ****************************************************************************/

/* Merging of hash codes. MERGE_HASH_SHIFT should be coprime with 
 * HASH_VALUE_LENGTH; 7 or 11 are both good
 */
#define MERGE_HASH_SHIFT    7 
#define MERGE_HASH_RSH(x)   ((x) >> (HASH_VALUE_LENGTH - MERGE_HASH_SHIFT))
#define MERGE_HASH_LSH(x)   ((x) << MERGE_HASH_SHIFT)
#define MERGE_HASH(a, b)    ((MERGE_HASH_LSH(a) | MERGE_HASH_RSH(a)) ^ (b))

/* argument "a" can not be a side-effecting expression */
#define MERGE_HASH_CODES(a, b)  (MERGE_HASH((SI_Hash)(a), (SI_Hash) (b)))
 
/* hash value collector; this explicit assignment macro helps to
 * avoid a double-evaluation  of "res"
 */
#define ASSIGN_MERGE_HASH_CODES(res, new) \
    (res = MERGE_HASH_CODES(res, new))

/****************************************************************************
 * 
 *  Hash code composing, decomposing and correction
 *
 ****************************************************************************/

#define OBJECT_TO_HASH(o) (SI_Hash)(o)

/* Two macros [both pure expressions] are to update a hash type.
 * REFINE_HASH_TYPE is a collector used by hash metods like HASH_EQUAL
 * The strategy is that the type can be changed from ROBUST to WEAK,
 * but never backwards.
 * SET_HASH_TYPE is a destructive assignment expression.
 */
#define SET_HASH_TYPE(t, o) \
    (t = (SI_IMMEDIATEP(o) || RESIDENTP(o)) ? ROBUST : WEAK )

#define REFINE_HASH_TYPE(t, o) \
    (t |= (SI_IMMEDIATEP(o) || RESIDENTP(o)) ? ROBUST : WEAK )

/* makes hash value small enough to be represented as positive fixnum */
#define CORRECT_HASH_VALUE(h) ((h) & IMOST_POSITIVE_FIXNUM)

/* returns boxed h if it ROBUST, otherwise boxed -h */
/* otherwise returns boxed  -h */
#define HASH_VALUES_2(h, t) \
    FIX( ROBUSTP(t) ? CORRECT_HASH_VALUE(h) :-(SI_Long)(CORRECT_HASH_VALUE(h)))


/* this is old version, it does not work when val is an unsigned long
#define GET_HASH_VALUES(val, type, box) \
    (val = IFIX(box), (type = (val < 0) \
     ? val = - val, WEAK : ROBUST))
*/
#define GET_HASH_VALUES(hashval, type, box) \
M_BEGIN \
    SI_Long val; \
    val = IFIX(box); \
    if (val < 0) { \
	hashval = (SI_Hash)- val; \
        type =  WEAK; \
    } \
    else { \
        type = ROBUST; \
        hashval = (SI_Hash)val; \
    } \
M_END


#define GET_HASH_FUNCTION(type) \
    (Hash_functions[type])

#define HASH_FUNC_CAN_CONS(t) (t > HASH_EQL)
#define LIST_WIDTH  30
#define LIST_DEPTH  10

#define Declare_rehash_flag  long SI_rehash_flag = TRUE;
#define MAYBE_REHASH()  SI_rehash_flag
#define REHASHED()      SI_rehash_flag = FALSE;


/****************************************************************************
 *
 * Rehashing policy
 *
 * REHASH_CODE() field of a hash table represents either absolute 
 * (specified as fixnum value of :rehash-size) or relative
 * (specified as float) imcrementing of hash array size
 * absolute value is  represented by a positive fixnum, relative is 
 * represented by negative fixnum.
 *
 ****************************************************************************/

#define REHASH_SIZE_LIMIT  (1L << 20)
#define REHASH_NORMALIZE(s) (rehash_normalize(s))
#define GET_ABSOLUTE_GROW(size, increment) REHASH_NORMALIZE(size + increment)
#define REHASH_SIZE_BASE 8
#define REHASH_SIZE_MODULO   (1 << REHASH_SIZE_BASE)
#define GET_PERCENT_GROW(size , index) \
    REHASH_NORMALIZE( size > REHASH_SIZE_MODULO ? ((size >> 4) * index) >> 4 \
     : (size * index) >> REHASH_SIZE_BASE)
    
#define COMPUTE_PERCENT_REHASH_SIZE(float) \
    (- (SI_Long)((CORRECT_FLOAT_REHASH(float) * REHASH_SIZE_MODULO) / 1))

#define CORRECT_FLOAT_REHASH(f) \
  ((f > 1 && f < 8) ? f : 2)

#define ABSOLUTE_GROW_P(size_val) (size_val < 0 ? FALSE : TRUE)


#define REHASH_UPGRADING(size, rehash) \
    (ABSOLUTE_GROW_P(rehash) \
     ? GET_ABSOLUTE_GROW(size, rehash) \
     : GET_PERCENT_GROW(size, -rehash))


/****************************************************************************
 *
 *  Hash table array entries                                                  
 *
 ************************************************************************** */

#if HASH_ARRAY_ENTRIES == CONS_ENTRIES

/* cons-based entries (defined in opposite to vector based ones ) */

#define MAKE_ENTRY(res, key, val, n) \
    (res = cons(key, val), res = cons(res, n))
#define MAKE_HASHED_ENTRY(res, hash, key, val, n) \
    (res = cons(hash, pair), res = cons(hash, res), res = cons(res, n))

#define NEXT_ENTRY(e)    (M_CDR(e))

#define MATCH_ENTRY(fun,bucket,key, pair) \
    (fun(M_CAR(pair = M_CAR(bucket)), key))

#define MATCH_HASH(bucket, pair, hcode) \
    (M_CAR(pair = M_CAR(bucket)) == hcode)

#define MATCH_HASHED_ENTRY(fun, bucket, pair, key) \
    (fun(M_CAR(pair = M_CDR(pair)), key))

#define ENTRY_VALUE(e, p)  (M_CDR(p))

#define SET_ENTRY_VALUE(e,p,v) \
    (M_CDR(p) = v)

#endif /* CONS_ENTRIES */

#if HASH_ARRAY_ENTRIES == VECTOR_ENTRIES

/* vector based entries */

#define MAKE_ENTRY(res, key, val, n) \
    (res = make_vector(FIX(3), NIL),  \
     SI_ISVREF(res,0) = key, \
     SI_ISVREF(res,1) = val, \
     SI_ISVREF(res,2) = n)

#define MAKE_HASHED_ENTRY(res, hash, key, val, n) \
    (res = make_vector(FIX(4), NIL),  \
     SI_ISVREF(res,0) = key, \
     SI_ISVREF(res,1) = val, \
     SI_ISVREF(res,2) = n,   \
     SI_ISVREF(res,3) = hash)

#define NEXT_ENTRY(e)    SI_ISVREF(e, 2)

#define MATCH_ENTRY(fun, e, k, p) \
    (fun(k, VENTRY_KEY(e)))

#define MATCH_HASH(e, p, hcode) \
    (SI_ISVREF(bucket, 3) == hcode)

#define MATCH_HASHED_ENTRY(fun, e, p, k) \
    MATCH_ENTRY(fun,e,k,p)

#define ENTRY_VALUE(e, p) (SI_ISVREF(e, 1))
#define ENTRY_KEY(e, p) (SI_ISVREF(e, 0))

#define VENTRY_VALUE(e) (SI_ISVREF(e, 1))
#define VENTRY_KEY(e) (SI_ISVREF(e, 0))
#define VENTRY_CODE(e) (SI_ISVREF(e, 3))

#define SET_ENTRY_VALUE(e,p,v) \
    (SI_ISVREF(e, 1) = v)

#endif /* VECTOR_ENTRIES */

/*****************************************************************************
 *
 * The macro make_rehashing_set_function provides a way to create specialized
 * rehash-and-sethash functions that differ in some before-lookup and 
 * after-lookup actions
 *
 *****************************************************************************/

#define make_rehashing_set_function(name, befor_rehash, after_rehash, key, hash_table, value, hashcode, ignore) \
static Object name (key, hash_table, value, hashcode, ignore) \
    Object key, hash_table, value, hashcode, ignore; \
{ \
    Declare_local_temp; \
    Object bucket, prev = NIL, array; \
    SI_Hash hashval; SI_Htype test, type; \
    SI_Dimension hindex; \
    SI_Stack_item *bottom; \
    Declare_stack_pointer; \
	SI_old_stack_marker;\
	\
    befor_rehash(key, hash_table, value, hashcode); \
     \
    test     = HASH_METHOD(hash_table); \
    array = WEAK_HASH_ARRAY(hash_table); \
 \
    /* perform rehashing */ \
    bottom = Stack; \
    SPREAD_ENTRIES(array); \
    CLEAR_ARRAY(array); \
    ASSEMBLY_ENTRIES(array, bottom, rehash_and_add_entry, test); \
 \
    after_rehash(key, hash_table, value, hashcode); \
 \
    GET_HASH_VALUES(hashval, type, hashcode); \
    hindex = HASH_INDEX(hashval, array); \
    bucket = HAREF(array, hindex); \
 \
    LOOKUP_ENTRY(test, bucket, key, pair); \
 \
    /* the entry is found */ \
    if (TRUEP(bucket)) { \
	SET_ENTRY_VALUE(bucket, pair, value); \
	return VALUES_1(value); \
    } \
 \
    /* assumes that another rehash *might* be needed */ \
    else if (NEEDS_REHASH(hash_table)) { \
	return REHASH_AND_SET(test, key, hash_table, value, hashcode, ignore); \
    } \
 \
    /* this helper function conses */ \
    else return(create_and_add_entry(hash_table,key,value,hashcode)); \
}

/* 
 * "Before" methods. Take a key, a hash table,a value and 
 * a code as  arguments
 */


/* used by set_with_rehash methods that never cons. Provides GC safe
 * updatre of GC flaf field by means of SAFE_SET_GC_FLAG;
 * permits to the compiler to put variables k, t, v into registers 
 */
#define SAVE_NOTHING(k, t, v, code)  \
    STACK_PUSH(k); \
    STACK_PUSH(v); \
    /* takes care about t */ \
    SAFE_SET_GC_FLAG(t); \
    v = STACK_POP(); \
    k = STACK_POP()


/* used by set_with_rehash methods that can cons. 
 * Protects arguments and resets[if necessary] GC flag field
 */
#define SAVE_TABLE_AND_PAIR(key, hash_table, value, code) \
    SAVE_STACK(); \
    PROTECT_3(hash_table, key, value); \
    SET_GC_FLAG(hash_table)

/* 
 * "After" methods. Take a key, a hash table,a value and 
 * a code as  arguments
 */

#define REHASH_THE_KEY(k, t, v, code) \
    FIND_HASH_CODE(code, k, HASH_METHOD(t)); \
    RESTORE_STACK()

    
#define NOOP(k, t, v, code)

/****************************************************************************
 * 
 *   Stack-based iterative operations with hash arrays
 *
 ***************************************************************************/

#define STACK_VAL(ref)  (ref->object)
#define FOR_EVERY_ENTRY(arr, func) \
   { SI_Dimension _i, _size; \
     Object _e; \
	 for (_i = 0, _size = HASH_ARRAY_SIZE(arr); _i \
	      < _size; _i++) { \
	     for (_e = HAREF(arr,_i); \
		  TRUEP(_e); _e = NEXT_ENTRY(_e)) \
		    {func(_e);}}}


#define SPREAD_ENTRIES(arr) \
    FOR_EVERY_ENTRY(arr, STACK_PUSH)

#define CLEAR_ARRAY(arr) \
    { SI_Dimension _i; \
	 for (_i =0; _i \
	      < HASH_ARRAY_SIZE(arr); _i++)  \
		  HAREF(arr,_i) = NIL; }

/* func is a function that inserts an entry in the array in 
 * the specific, caller provided way [ with rehash, without it, etc]
 */
#define ASSEMBLY_ENTRIES(arr,eptr,func,test) \
   { SI_Stack_item *_i;\
	 for (_i = eptr; \
	      _i < Stack; _i++)  \
                func(STACK_VAL(_i), arr, test);}

#define GROW_ARRAY(table, type) \
M_BEGIN  \
 	    Object array, new_array;  \
	    SI_Htype test; \
	    SI_Stack_item *e_ptr;  \
	    Declare_stack_pointer; \
	     \
	    SAVE_STACK(); \
	    PROTECT_2(table, array); \
 \
	    test     = HASH_METHOD(table); \
	    e_ptr = Stack;     \
	    array = FIND_HASH_ARRAY(table, type);  \
	    SPREAD_ENTRIES(array);  \
	    new_array = ADJUST_ARRAY(table, array);  \
	    ARRAY_COUNTER(new_array) = ARRAY_COUNTER(array);  \
	    array = new_array; \
	    ARRAY_THRESHOLD(array) =  \
		COMPUTE_THRESHOLD(HASH_ARRAY_SIZE(array)); \
	    INIT_HASH_ARRAY(table, type, array);  \
	     \
	    /* perform lazily, not worrying about rehashment */ \
	    ASSEMBLY_ENTRIES(array, e_ptr, add_entry, test);  \
	    Stack = e_ptr;  \
	     \
	    RESTORE_STACK(); \
M_END 

/*****************************************************************************
 *
 *  Hash table iterations                                                      
 *
 ****************************************************************************/


/* Package iterator state data structure */
typedef struct {
  SI_Stack_item *old;
  SI_Stack_item *next;
  SI_Stack_item *top;
  UCHAR          phase;
} State;

#define STACK_TOP(a) ((a)->object)

#define STATE_STR_SIZE  4*sizeof(Object)
#define MAKE_ITERATOR_STATE() \
    make_array(FIX(STATE_STR_SIZE), Qstring_char, \
	       KOPT, KOPT,KOPT,KOPT,KOPT,KOPT);

#define ISTATE(s) ((State *)SI_PRIMITIVE_VECTOR_CONTENTS(s, SI_PVT_Object))

/*
 *
 * Map
 *
 */

/* This macro supports "Maphash" function and is a wrapper around
 * FOR_EVERY_ENTRY iterator. It provides:
 * (1) func is a functional object
 * (2) fun takes 2 arguments: key and value
 * (3) establishes protection */
#define FOR_EVERY_PAIR(array, fun) \
    M_BEGIN \
       Object function, temp; \
       /* prevent multiply evaluation; create lexical scope */ \
       function = fun; \
       SAVE_STACK(); \
       PROTECT_3(array, temp, function); \
       FOR_EVERY_ENTRY(array, CALL_FUN_WITH_PAIR); \
       RESTORE_STACK(); \
    M_END 

/* in lexical scope of 'function' */
#define CALL_FUN_WITH_PAIR(entry) \
    (STACK_PUSH(entry), \
    funcall2(function, VENTRY_KEY(entry), VENTRY_VALUE(entry)), \
    entry = STACK_POP())


/****************************************************************************
 * 
 * Hash Lookup comparators
 * 
 * The standard hash lookup comparators are EQ, EQL. EQUAL and EQUALP.
 * The implementation allows to provide extensions - add more hash 
 * functions with corresponding hash lookup comparators. Some of compara-
 * tors which are complicated enough can not be implemented without
 * consing; the full ANSII implementation of pathnames also can cause
 * consing EQUAL and EQUALP. For such a comparators it is necessary to
 * perform the lookup safely
 *
 ****************************************************************************/

/* Currently assume no comparators can cons */
#define COMPARATOR_CAN_CONS(test) FALSE

#define SAFE_GETHASH(key, table, default)   /* currently empty */
#define SAFE_SETHASH(key, table, value)     /* currently empty */
#define SAFE_REMHASH(key, table)            /* currently empty */

/****************************************************************************
 *
 * User defined hash tests and hash methods: to be implemented
 * 
 ****************************************************************************/



















