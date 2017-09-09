/*
 * atomic.c -  Chestnut Run-Time Library entry for atomic functions
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  13 Apr 2012
 * Update :  22 April 2014, 4 October 2014
 *
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#ifdef _WIN32
# include "windows.h"
#endif

#if SI_SUPPORT_THREAD

extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area;
extern SI_Area Static_area;
extern SI_Area Local_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, int align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (int n, char *lstr, ...);
extern Object (*SI_warn_fptr) (int n, char *lstr, ...);
extern Object SI_obtain_rest_list(int rest_position, int arg_position, int nargs, va_list *ap);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern void SI_fatal_error(char *lstr, ...);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object string(Object);

#else

extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();
extern Object SI_obtain_rest_list();
extern Object SI_symbol_field();
extern void SI_fatal_error();
extern Object SI_symbol_field();
extern Object string();

#endif

/* IMPORTANT NOTE: Some systems do not have CAS (but have LL/SC), they're
 *     DEC Alpha AXP (ldl_l/stl_c),
 *     IBM PowerPC (lwarx/stwcx),
 *     MIPS (ll/sc),
 * and ARM (v6 and later) (ldrex/strex).
 *
 * Therefore currently SymScale can possibily run on only two systems:
 *     Intel/AMD (CMPXCHG)
 * and SPARC (CAS).
 */

/* TX:COMPARE-AND-SWAP-CAR */
Object compare_and_swap_car(cons, compare, source)
  Object cons, compare, source;
{
    SI_Long old, cmp, src;
    cmp = (SI_Long)compare;
    src = (SI_Long)source;

#ifdef _WIN32
# ifdef _M_X64
    old = InterlockedCompareExchange64((SI_Long*)&M_CAR(cons), src, cmp);
# else
    old = InterlockedCompareExchange((SI_Long*)&M_CAR(cons), src, cmp);
# endif
#else /* linux and other platforms, GCC only */
    old = __sync_val_compare_and_swap((SI_Long*)&M_CAR(cons), cmp, src);
#endif
    if (old == cmp)
	return VALUES_1(T);
    else
	return VALUES_1(NIL);
}

/* TX:ATOMIC-INCFF-CAR */
Object atomic_incff_car(cons, value)
  Object cons, value;
{
    Object old, new_value;
    SI_Long d;

    /* here we assume value is FIXNUM */
    d = (SI_Long)value - SI_FIXNUM_TAG;
#ifdef _WIN32
# ifdef _M_X64
    old = (Object) InterlockedExchangeAdd64((SI_Long*)&M_CAR(cons), d);
# else
    old = (Object) InterlockedExchangeAdd((SI_Long*)&M_CAR(cons), d);
# endif
#else /* linux and other platforms, GCC only */
    old = (Object) __sync_fetch_and_add((SI_Long*)&M_CAR(cons), d);
#endif
    new_value = M_CAR(cons);

    return VALUES_2(new_value, old);
}

/* TX:COMPARE-AND-SWAP-CDR */
Object compare_and_swap_cdr(cons, compare, source)
  Object cons, compare, source;
{
    SI_Long old, cmp, src;
    cmp = (SI_Long)compare;
    src = (SI_Long)source;

#ifdef _WIN32
# ifdef _M_X64
    old = InterlockedCompareExchange64((SI_Long*)&M_CDR(cons), src, cmp);
# else
    old = InterlockedCompareExchange((SI_Long*)&M_CDR(cons), src, cmp);
# endif
#else /* linux and other platforms, GCC only */
    old = __sync_val_compare_and_swap((SI_Long*)&M_CDR(cons), cmp, src);
#endif
    if (old == cmp)
	return VALUES_1(T);
    else
	return VALUES_1(NIL);
}

/* TX:ATOMIC-INCFF-CDR */
Object atomic_incff_cdr(cons, value)
  Object cons, value;
{
    Object old, new_value;
    SI_Long d;

    /* here we assume value is FIXNUM */
    d = (SI_Long)value - SI_FIXNUM_TAG;
#ifdef _WIN32
# ifdef _M_X64
    old = (Object) InterlockedExchangeAdd64((SI_Long*)&M_CDR(cons), d);
# else
    old = (Object) InterlockedExchangeAdd((SI_Long*)&M_CDR(cons), d);
# endif
#else /* linux and other platforms, GCC only */
    old = (Object) __sync_fetch_and_add((SI_Long*)&M_CDR(cons), d);
#endif
    new_value = M_CDR(cons);

    return VALUES_2(new_value, old);
}

/* TX:COMPARE-AND-SWAP-SYMBOL-VALUE */
Object compare_and_swap_symval(symbol, compare, source)
  Object symbol, compare, source;
{
    Declare_local_temp;
    Object res, key, tail, *dest;
    SI_Long old, cmp, src;

    if (symbol == NIL)
	return VALUES_1(NIL);

    key = SI_MAKE_TOKEN(SI_TOKEN_ID_VALUE);
    res = UNBOUND;
    for (tail = SI_SYMBOL_PLIST(symbol); CONSP(tail); tail = M_CDDR(tail))
	if (EQ(M_CAR(tail), key)) { res = M_CADR(tail); break; }

    if (VALUE_CELL_P(res)) {
	short index;
	index = SI_THREAD_INDEX(SI_current_thread());
	if (VALUE_CELL_LOCAL_COUNT(res, index))
	    dest = VALUE_CELL_LOCAL_LOCATION(res, index);
	else
	    dest = VALUE_CELL_LOCATION(res);

	cmp = (SI_Long)compare;
	src = (SI_Long)source;

#ifdef _WIN32
# ifdef _M_X64
	old = InterlockedCompareExchange64((SI_Long*)dest, src, cmp);
# else
	old = InterlockedCompareExchange((SI_Long*)dest, src, cmp);
# endif
#else /* linux and other platforms, GCC only */
	old = (Object) __sync_val_compare_and_swap((SI_Long*)dest, cmp, src);
#endif
	if (old == cmp)
	    return VALUES_1(T);
	else
	    return VALUES_1(NIL);
    } else
	return VALUES_1(NIL);
}

/* TX:ATOMIC-INCFF-SYMBOL-VALUE */
Object atomic_incff_symval(symbol, value)
  Object symbol, value;
{
    Declare_local_temp;
    Object res, key, tail, old, new_value, *dest;
    SI_Long d;

    if (symbol == NIL)
	return VALUES_1(NIL);

    key = SI_MAKE_TOKEN(SI_TOKEN_ID_VALUE);
    res = UNBOUND;
    for (tail = SI_SYMBOL_PLIST(symbol); CONSP(tail); tail = M_CDDR(tail))
	if (EQ(M_CAR(tail), key)) { res = M_CADR(tail); break; }

    if (VALUE_CELL_P(res)) {
	short index;
	index = SI_THREAD_INDEX(SI_current_thread());
	if (VALUE_CELL_LOCAL_COUNT(res, index))
	    dest = VALUE_CELL_LOCAL_LOCATION(res, index);
	else
	    dest = VALUE_CELL_LOCATION(res);

	/* here we assume value is FIXNUM */
	d = (SI_Long)value - SI_FIXNUM_TAG;
#ifdef _WIN32
# ifdef _M_X64
	old = (Object) InterlockedExchangeAdd64((SI_Long*)dest, d);
# else
	old = (Object) InterlockedExchangeAdd((SI_Long*)dest, d);
# endif
#else /* linux and other platforms, GCC only */
	old = (Object) __sync_fetch_and_add((SI_Long*)dest, d);
#endif
	new_value = *dest;

	return VALUES_2(new_value, old);
    } else
	return VALUES_1(NIL);
}

/* TX:ATOMIC-EXCHANGE-SYMBOL-VALUE, the first part is the same with TX:COMPARE-AND-SWAP-SYMBOL-VALUE */
Object atomic_exchange_symval(symbol, source)
  Object symbol, source;
{
    Declare_local_temp;
    Object res, key, tail, old, *dest;

    if (symbol == NIL)
	return VALUES_1(NIL);

    key = SI_MAKE_TOKEN(SI_TOKEN_ID_VALUE);
    res = UNBOUND;
    for (tail = SI_SYMBOL_PLIST(symbol); CONSP(tail); tail = M_CDDR(tail))
	if (EQ(M_CAR(tail), key)) { res = M_CADR(tail); break; }

    if (VALUE_CELL_P(res)) {
	short index;
	index = SI_THREAD_INDEX(SI_current_thread());
	if (VALUE_CELL_LOCAL_COUNT(res, index))
	    dest = VALUE_CELL_LOCAL_LOCATION(res, index);
	else
	    dest = VALUE_CELL_LOCATION(res);

#ifdef _WIN32
# ifdef _M_X64
	old = (Object) InterlockedExchange64((SI_Long*)dest, (SI_Long)source);
# else
	old = (Object) InterlockedExchange((SI_Long*)dest, (SI_Long)source);
# endif
#else /* linux and other platforms, GCC only */
	old = (Object) __sync_lock_test_and_set((SI_Long*)dest, (SI_Long)source);
#endif
	return VALUES_1(old);
    } else
	return VALUES_1(NIL);
}

/* compare-and-swap-simple-vector-slot */
Object compare_and_swap_svslot(Object vector, SI_Long index, Object compare, Object source)
{
    SI_Long *place, old, cmp, src;

    place = (SI_Long*)&ISVREF(vector, index);
    cmp = (SI_Long)compare;
    src = (SI_Long)source;

#ifdef _WIN32
# ifdef _M_X64
    old = InterlockedCompareExchange64(place, src, cmp);
# else
    old = InterlockedCompareExchange(place, src, cmp);
# endif
#else /* linux and other platforms, GCC only */
    old = __sync_val_compare_and_swap(place, cmp, src);
#endif
    if (old == cmp)
	return VALUES_1(T);
    else
	return VALUES_1(NIL);
}

/* atomic-incff-simple-vector-slot */
Object atomic_incff_svslot(vector, index, value)
  Object vector, index, value;
{
    Object old, new_value;
    SI_Long i, *place, d;

    i = IFIX(index);
    place = (SI_Long*)&ISVREF(vector, i);
    d = (SI_Long)value - SI_FIXNUM_TAG;

#ifdef _WIN32
# ifdef _M_X64
    old = (Object) InterlockedExchangeAdd64(place, d);
# else
    old = (Object) InterlockedExchangeAdd(place, d);
# endif
#else /* linux and other platforms, GCC only */
    old = (Object) __sync_fetch_and_add(place, d);
#endif
    new_value = (Object)*place;

    return VALUES_2(new_value, old);
}

#endif /* SI_SUPPORT_THREAD */
