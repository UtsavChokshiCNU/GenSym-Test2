/*
 * numbers.c - LISPTOC math functions
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"

enum unary_op {			/* Unary operations */
    MABS,
    NEGATE,
    ZEROP,
    PLUSP,
    MINUSP,
    ODDP,
    EVENP,
    LOGNOT,
    LOGCOUNT
};

enum binary_op {		/* Binary operations */
    NONE,
    MADD,
    MMINUS,
    MTIMES,
    MDIVIDE,
    LESS,
    MEQUAL,
    MMAX,
    MMIN,
    LOGAND,
    LOGIOR,
    LOGXOR,
    LOGEQV,
    ASH
};

extern TLS SI_Area *Current_area;
extern TLS SI_Long L_temp;
extern Object Qinteger;
extern Object Random_state;
#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;
extern TLS Object Values[];
#include <assert.h>
#include <math.h>

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern SI_Long SI_igcd(SI_Long n1, SI_Long n2);
extern void SI_type_error(Object datum, Object expected_type);
extern Object STATIC_LIST(long n, ...);
extern Object STATIC_STRING(char *s);
extern Object cdouble_to_double(double a);
extern Object clong_to_bignum(SI_Long a);
extern Object int64_to_bignum(SI_int64 a);
extern Object clong_to_int64(SI_Long a);
extern Object cint64_to_int64(SI_int64 a);
extern SI_Long integer_to_long(Object n);
extern SI_int64 integer_to_int64(Object n);
extern Object make_complex(Object r, Object i);
extern double object_to_cdouble(Object n);
extern Object lcomplex(Object real, Object imag);
extern Object lognot(Object);
extern Object logandc1(Object,Object);
extern Object logandc2(Object,Object);
extern Object logbitp(Object,Object);
extern Object lognand(Object,Object);
extern Object lognor(Object,Object);
extern Object logorc1(Object,Object);
extern Object logorc2(Object,Object);
extern Object logtest(Object,Object);
extern Object logior(Object a, Object b);
extern Object logxor(Object a, Object b);
extern Object logand(Object a, Object b);
extern Object logeqv(Object a, Object b);
extern Object SI_do_math2(Object arg1, Object arg2, enum binary_op fn_code);
extern Object integer_decode_float(Object f);
extern Object expt(Object x, Object y);
extern Object latan(Object x, Object y);
extern Object scale_float(Object f, Object k);
extern Object realpart(Object a);
extern Object imagpart(Object a);
extern Object ash(Object a, Object b);
extern Object integer_length(Object a);

#else

extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern SI_Long SI_igcd();
extern void SI_type_error();
extern Object STATIC_LIST();
extern Object STATIC_STRING();
extern Object cdouble_to_double();
extern Object clong_to_bignum();
extern Object int64_to_bignum();
extern Object clong_to_int64();
extern Object cint64_to_int64();
extern SI_Long integer_to_long();
extern SI_int64 integer_to_int64();
extern Object make_complex();
extern double object_to_cdouble();
extern Object lcomplex();
extern Object lognot();
extern Object logandc1();
extern Object logandc2();
extern Object logbitp();
extern Object lognand();
extern Object lognor();
extern Object logorc1();
extern Object logorc2();
extern Object logtest();
extern Object logior();
extern Object logxor();
extern Object logand();
extern Object logeqv();
extern Object SI_do_math2();
extern Object integer_decode_float();
extern Object expt();
extern Object latan();
extern Object scale_float();
extern Object realpart();
extern Object imagpart();
extern Object ash();
extern Object integer_length();

#endif

#include "bigext.h"


#ifndef HAVE_AINT
/* There must be a better way to do this!  Will modf do the trick? */
#define aint(x)   ((x) < 0 ? -floor(-x) : floor(x))
/* This isn't correct.  Fix it later. */
#define rint(x)	  ceil((x) - 0.5)
#endif

extern Object xbignum_normalize();
extern Object make_ratio();
extern Object double_to_integer();

extern long SI_gc_unsafe;
extern jmp_buf SI_restart_unsafe;

extern Object SI_Float_zero;
extern Object SI_Float_one;
extern Object SI_Float_negative_one;

Object Boole_clr   = BOOLE_CLR;
Object Boole_and   = BOOLE_AND;
Object Boole_andc1 = BOOLE_ANDC1;
Object Boole_2	   = BOOLE_2;
Object Boole_andc2 = BOOLE_ANDC2;
Object Boole_1	   = BOOLE_1;
Object Boole_xor   = BOOLE_XOR;
Object Boole_ior   = BOOLE_IOR;
Object Boole_nor   = BOOLE_NOR;
Object Boole_eqv   = BOOLE_EQV;
Object Boole_c1	   = BOOLE_C1;
Object Boole_orc1  = BOOLE_ORC1;
Object Boole_c2	   = BOOLE_C2;
Object Boole_orc2  = BOOLE_ORC2;
Object Boole_nand  = BOOLE_NAND;
Object Boole_set   = BOOLE_SET;

static Object Positive_i = UNBOUND;	/* #c(0 1) */
static Object Negative_i = UNBOUND;	/* #c(0 -1) */

static void init_plus_minus_i()
{ Declare_area(a);

  SAVE_CURRENT_AREA(a);
  SET_CURRENT_AREA(Static_area);
  Positive_i = lcomplex(ZERO, FIX(1L));
  Negative_i = lcomplex(ZERO, FIX(-1L));
  RESTORE_CURRENT_AREA(a);
}

#define INIT_PLUS_MINUS_I() \
    if (Positive_i == UNBOUND) init_plus_minus_i();

static Object do_division();
#if SI_SUPPORT_MF
static Object num_iterate();
static Object num_relop();
#endif
static Object num_iteraten();
static Object cfuncall_d1();
static Object cfuncall_d2();
static Object num_relopn();
static Object do_math1();
static Object multiply_carefully();
static Object integer_quotient();

/* Make sure this works under a case-insensitive linker: use __
   instead of _ to avoid conflict with variables Boole_clr, etc. */
static Object boole__clr();
static Object boole__2();
static Object boole__1();
static Object boole__c1();
static Object boole__c2();
static Object boole__set();

static Object (*Boole_functions[16])() = {
    boole__clr, logand, logandc1, boole__2, logandc2, boole__1, logxor,
    logior, lognor, logeqv, boole__c1, logorc1, boole__c2, logorc2,
    lognand, boole__set
};



/*
 * These two routines are used to perform locally gc unsafe bignum
 * operations in cooperation with the garbage collector, which longjmp's
 * back to restart the operation.
 */

/* Having a GC_Period of less than 3 would prevent SI_alloc_bignum from
 * ever succeeding.  If most bignum operations call SI_alloc_bignum
 * multiple times, even larger GC_Period values will be sure to fail.
 */
#define SI_UNSAFE_OP_FAILED()      /* BUG: GC_Period might be too low */


static Object
perform_safely (f, arg1, arg2)
    Object (*f)();
    Object arg1, arg2;
{
    Object result;
        result = (*f)(arg1, arg2);
        return(result);
        }

static Object
perform_safely_1 (f, arg)
    Object (*f)();
    Object arg;
{
    Object result;
        result = (*f)(arg);         /* if gc occurs, will longjmp to above */
        return(result);
        }

    
Object zerop(a)
    Object a;
{
	Object b;
	double d;
	Object result;
	SI_int64 i;

    if (FIXNUMP(a)) {
		result = ((SI_Long)a == 1 ? T : NIL);
	} else {
	
	switch (PNODE_TYPE(a)) {
	case DOUBLE_TYPE:
		d = object_to_cdouble(a);
		result = d == 0.0 ? T : NIL;
	    break;
	case OBIGNUM_TYPE:
	    b = BIGNUM_VALUE(a);
	    result = b == 0 ? T : NIL;
		break;
	case XBIGNUM_TYPE:
		result = NIL;
		break;
        case LONG64_TYPE:
		i = ILONG64(a);
		result = (i == (SI_int64)0L) ? T : NIL;
		break;
	}}
    return result;
}

Object plusp(a)
    Object a;
{
	Object b;
	double d;
	Object result;
	SI_int64 i;

    if (FIXNUMP(a)) {
		result = (IFIX(a) > 0 ? T : NIL);
	} else {
	switch (PNODE_TYPE(a)) {
	case DOUBLE_TYPE:
		d = object_to_cdouble(a);
		result = d > 0.0 ? T : NIL;
	    break;
	case OBIGNUM_TYPE:
	    b = BIGNUM_VALUE(a);
	    result = b > 0 ? T : NIL;
		break;
	case XBIGNUM_TYPE:
		result = (bignum_test(a) == bignum_comparison_greater
			   ? T : NIL);
		break;
	case LONG64_TYPE:
		i = ILONG64(a);
		result = (i > (SI_int64)0L) ? T : NIL;
		break;
	}}
    return result;
}

Object minusp(a)
    Object a;
{
    return do_math1(a, MINUSP);
}

Object oddp(a)
    Object a;
{
    return do_math1(a, ODDP);
}

Object evenp(a)
    Object a;
{
    return do_math1(a, EVENP);
}

/* = */
Object num_eq (a, b)
    Object a, b;
{
    return SI_do_math2(a, b, MEQUAL);
}

#if SI_SUPPORT_MF
Object num_eqr (a, b)
    Object a, b;
{
    return num_relop(num_eq, a, b);
}
#endif

Object num_eqn varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_relopn(num_eq, n, rest);
    RESTORE_STACK();
    return result;
}

Object num_ne (a, b)
    Object a, b;
{
    Declare_local_temp;
    return VALUES_1(TRUEP(num_eq(a, b)) ? NIL : T);
}

#if SI_SUPPORT_MF
Object num_ner (a, b)
    Object a, b;
{
    return num_relop(num_ne, a, b);
}
#endif

num_membern (arg, n, rest)
    Object arg, *rest;
    int n;
{
    Object next;

    while (n--) {
	next = *rest++;
	if (TRUEP(num_eq(arg, next)))
	    return TRUE;
    }
    return FALSE;
}

Object num_nen varargs_1(int, n)
{
    Declare_local_temp;
    Object result = T, arg, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    while (--n) {
        arg = *rest++;
	if (num_membern(arg, n, rest)) {
	    result = NIL;
	    break;
	}
    }
    RESTORE_STACK();
    return VALUES_1(result);
}

Object num_lt (a, b)
    Object a, b;
{
    Declare_local_temp;
    return (NUM_LT(a, b) ? VALUES_1(T) : VALUES_1(NIL));
}

Object num_ltn varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_relopn(num_lt, n, rest);
    RESTORE_STACK();
    return result;
}

#if SI_SUPPORT_MF
Object num_ltr (a, b)
    Object a, b;
{
    return num_relop(num_lt, a, b);
}
#endif

Object num_gt (a, b)
    Object a, b;
{
    Declare_local_temp;
    return (NUM_LT(b, a) ? VALUES_1(T) : VALUES_1(NIL));
}

Object num_gtn varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_relopn(num_gt, n, rest);
    RESTORE_STACK();
    return result;
}

#if SI_SUPPORT_MF
Object num_gtr(a,b)
    Object a, b;
{
    return num_relop(num_gt, a, b);
}
#endif

Object num_le (a, b)
    Object a, b;
{
    Declare_local_temp;
    return (NUM_GT(a, b) ? VALUES_1(NIL) : VALUES_1(T));
}

Object num_len varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_relopn(num_le, n, rest);
    RESTORE_STACK();
    return result;
}

#if SI_SUPPORT_MF
Object num_ler (a, b)
    Object a, b;
{
    return num_relop(num_le, a, b);
}
#endif

Object num_ge (a, b)
    Object a, b;
{
    Declare_local_temp;
    return (NUM_LT(a, b) ? VALUES_1(NIL) : VALUES_1(T));
}

Object num_gen varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_relopn(num_ge, n, rest);
    RESTORE_STACK();
    return result;
}

#if SI_SUPPORT_MF
Object num_ger(a,b)
    Object a, b;
{
    return num_relop(num_ge, a, b);
}

static Object num_relop(f, a, b)
    Object (*f)();
    Object a, b;
{
    Declare_local_temp;
    Object temp, n1, n2;

    for (n1 = a, temp = b; TRUEP(temp); temp = M_CDR(temp)) {
	n2 = M_CAR(temp);
	if ((*f)(n1, n2) == NIL)
	    return VALUES_1(NIL);
	n1 = n2;
    }
    return VALUES_1(T);
}

#endif

static Object num_relopn (f, n, rest)
    Object (*f)(), *rest;
    long n;
{
    Declare_local_temp;
    Object n1, n2, result = T;

    if (n > 0) {
	n1 = *rest++;
	while (--n) {
	    n2 = *rest++;
	    if ((*f)(n1, n2) == NIL) {
		result = NIL;
		break;
	    }
	    n1 = n2;
	}
    }
    return VALUES_1(result);
}

Object lmax (a, b)
    Object a, b;
{
    return SI_do_math2(a, b, MMAX);
}

#if SI_SUPPORT_MF
Object lmaxr (a, b)
    Object a, b;
{
    return num_iterate(SI_do_math2, a, b, MMAX);
}
#endif

Object maxn varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, MMAX, n, rest);
    RESTORE_STACK();
    return result;
}

Object lmin (a, b)
    Object a, b;
{
    return SI_do_math2(a, b, MMIN);
}

#if SI_SUPPORT_MF
Object lminr (a, b)
    Object a, b;
{
    return num_iterate(SI_do_math2, a, b, MMIN);
}
#endif

Object minn varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, MMIN, n, rest);
    RESTORE_STACK();
    return result;
}

Object l_abs (a)
    Object a;
{
    return do_math1(a, MABS);
}

Object add (a, b)
    Object a, b;
{
    Declare_local_temp;
    SI_Long n;

    if (FIXNUMP(a) && FIXNUMP(b)) {
	n = IFIX(a) +  IFIX(b);
	return VALUES_1(MAKE_INTEGER(n));
    }
    else return SI_do_math2(a, b, MADD);
}

#if SI_SUPPORT_MF
Object addr (a)
    Object a;
{
    Declare_local_temp;
    if (a == NIL)
	return VALUES_1(ZERO);
    else
	return num_iterate(SI_do_math2, CAR(a), CDR(a), MADD);
}
#endif

Object addn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (n == 0) return VALUES_1(ZERO);	/* (+) -> 0 */
    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, MADD, n, rest);
    RESTORE_STACK();
    return result;
}

Object negate (a)
    Object a;
{
    return do_math1(a, NEGATE);
}

Object minus (a, b)
    Object a, b;
{
    return SI_do_math2(a, b, MMINUS);
}

#if SI_SUPPORT_MF
Object minusr (a, b)
    Object a, b;
{
    if (b == NIL)
        return num_iterate(SI_do_math2, a, b, MMINUS);
    else
	return SI_do_math2(ZERO, a, MMINUS);
}
#endif

Object minusn varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    if (n == 1L)
	result = do_math1(*rest, NEGATE);
    else
	result = num_iteraten(SI_do_math2, MMINUS, n, rest);
    RESTORE_STACK();
    return result;
}

Object ltimes (arg1, arg2)
    Object arg1, arg2;
{
    Object result;
    SI_Long n1, n2;
    double d1, d2;
    SI_int64 i1, i2, i;
    int arg1_type = IMMEDIATE_P(arg1) ? (int) FIXNUM_TYPE : (int) PNODE_TYPE(arg1);
    int arg2_type = IMMEDIATE_P(arg2) ? (int) FIXNUM_TYPE : (int) PNODE_TYPE(arg2);

    switch(MAX(arg1_type, arg2_type)) {
		case FIXNUM_TYPE:
		case OBIGNUM_TYPE:
			n1 = INTEGER_TO_LONG(arg1);
			n2 = INTEGER_TO_LONG(arg2);
#ifdef NEW_BIGNUMS
			result = multiply_carefully(n1, n2);
			if (result == NIL) {
				if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
				if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
					result = xbignum_normalize(bignum_multiply(arg1, arg2));
			}
			break;
#else
			n = n1 * n2;
			/* Not tight, but better than nothing */
			if (((n1 >= 0) == (n2 >= 0)) ? (n < 0) : (n > 0))
			warn(3, "*: integer overflow - (* ~d ~d)", arg1, arg2);
			result = MAKE_INTEGER(n);
			break;
#endif
		case XBIGNUM_TYPE:
			if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
			if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
			result = xbignum_normalize(bignum_multiply(arg1, arg2));
			break;
		case DOUBLE_TYPE:
			d1 = object_to_cdouble(arg1);
			d2 = object_to_cdouble(arg2);
			result = cdouble_to_double(d1 * d2);
			break;
		case LONG64_TYPE:
			if (!LONG64P(arg1)) arg1 = FIXNUM_TO_INT64(arg1);
			if (!LONG64P(arg2)) arg2 = FIXNUM_TO_INT64(arg2);
			i1 = ILONG64(arg1);
			i2 = ILONG64(arg2);
			i = i1 * i2;
			/* no need to check overflow here */
			result = INT64_TO_INTEGER(i);
			break;
	}
    return result;
}

Object timesn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (n == 0) return VALUES_1(FIX(1L));	/* (*) -> 1 */
    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, MTIMES, n, rest);
    RESTORE_STACK();
    return result;
}

#if SI_SUPPORT_MF
Object timesr (a)
    Object a;
{
    Declare_local_temp;
    if (a == NIL)
	return VALUES_1(FIX(1L));
    else
	return num_iterate(SI_do_math2, CAR(a), CDR(a), MTIMES);
}
#endif

Object reciprocal(x)
   Object x;
{
    return SI_do_math2(FIX(1L), x, MDIVIDE);
}

Object divide (a, b)
    Object a, b;
{
    return SI_do_math2(a, b, MDIVIDE);
}

Object dividen varargs_1(int, n)
{
    Object result, *rest;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    if (n == 1)
	result = SI_do_math2(FIX(1L), *rest, MDIVIDE);
    else
	result = num_iteraten(SI_do_math2, MDIVIDE, n, rest);
    RESTORE_STACK();
    return result;
}

#if SI_SUPPORT_MF
Object divider (a, b)
    Object a, b;
{
    if (b == NIL)
	return SI_do_math2(FIX(1L), a, MDIVIDE);
    else
	return num_iterate(SI_do_math2, a, b, MDIVIDE);
}
#endif

Object add1 (a)
    Object a;
{
    return SI_do_math2(a, FIX(1L), MADD);
}

Object sub1 (a)
    Object a;
{
    return SI_do_math2(a, FIX(1L), MMINUS);
}

/* Zero is an identity */

Object gcd (a, b)
    Object a, b;
{
    Declare_local_temp;
    SI_Long n1, n2, itemp;
    Object temp;
    Declare_stack_pointer;

    if (a == ZERO)
	temp = l_abs(b);
    else if (b == ZERO)
	temp = l_abs(a);
    else if (a == MOST_NEGATIVE_FIXNUM && b == MOST_NEGATIVE_FIXNUM)
	temp = MAKE_INTEGER(-IMOST_NEGATIVE_FIXNUM);
    else if (FIXNUMP(a) && FIXNUMP(b)) {
	n1 = IFIX(a);
	n2 = IFIX(b);
	if (n1 < 0) n1 = -n1;
	if (n2 < 0) n2 = -n2;
	if (n1 < n2) {
	    itemp = n1;
	    n1 = n2;
	    n2 = itemp;
	}
	if (n2 == 0)
	    temp = FIX(n1);
	else {
	    while (itemp = n1 % n2) {
		n1 = n2;
		n2 = itemp;
	    }
	    temp = FIX(n2);
	}
    }
    else {
	SAVE_STACK();
	PROTECT_2(a, b);
	if (minusp(a)) a = negate(a);
	if (minusp(b)) b = negate(b);
	if (!XBIGNUMP(a)) a = clong_to_bignum(IINTEGER(a));
	if (!XBIGNUMP(b)) b = clong_to_bignum(IINTEGER(b));
	if (bignum_compare(a, b) == bignum_comparison_less) {
	    temp = a;
	    a = b;
	    b = temp;
	}
	if (bignum_test(b) == bignum_comparison_equal) /* zerop */
	    temp = xbignum_normalize(a);
	else {
	    while (bignum_test(
			       temp = 
			       perform_safely(bignum_remainder, a, b)) !=
		   bignum_comparison_equal) {
		a = b;
		b = temp;
	    }
	    temp = xbignum_normalize(b);
	}
	RESTORE_STACK();
    }
    return VALUES_1(temp);
}

#if SI_SUPPORT_MF
Object gcdr (a)
    Object a;
{
    Declare_local_temp;
    if (a == NIL)
	return VALUES_1(ZERO);
    else if (M_CDR(a) == NIL)
	return l_abs(M_CAR(a));
    else
	return num_iterate(gcd, M_CAR(a), M_CDR(a), NONE);
}
#endif

Object gcdn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (n == 0)
	return VALUES_1(ZERO);
    SAVE_STACK();
    SETUP_REST(n, rest);
    if (n == 1)
	result = l_abs(rest[0]);
    else
	result = num_iteraten(gcd, NONE, n, rest);
    RESTORE_STACK();
    return result;
}

Object lcm(a, b)
    Object a, b;
{
    Declare_local_temp;
    Object temp = NIL;
    Declare_stack_pointer;

    if (a == ZERO || b == ZERO)
	return VALUES_1(ZERO);
    SAVE_STACK();
    PROTECT_3(a, b, temp);
    temp = gcd(a, b);
    temp = integer_quotient(b, temp);
    temp = ltimes(a, temp);
    temp = l_abs(temp);
    RESTORE_STACK();
    return temp;
}

#if SI_SUPPORT_MF
Object lcmr(a)
    Object a;
{
    Declare_local_temp;
    if (a == NIL)
	return VALUES_1(FIX(1L)); /* CLtL II */
    else if (M_CDR(a) == NIL)
	return l_abs(M_CAR(a));
    else
	return num_iterate(lcm, M_CAR(a), M_CDR(a), NONE);
}
#endif

Object lcmn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (n == 0)
	return VALUES_1(FIX(1L));
    SAVE_STACK();
    SETUP_REST(n, rest);
    if (n == 1)
	result = l_abs(rest[0]);
    else
	result = num_iteraten(lcm, NONE, n, rest);
    RESTORE_STACK();
    return result;
}

Object xmake_canonical_rational(num, den)
    Object num, den;
{
    Object result, thegcd;
    Declare_stack_pointer;

    if (den == ZERO)
	return error(3, "/: division by zero - (/ ~S ~S)", num, den);

    SAVE_STACK();
    PROTECT_2(num, den);
    PROTECTI_2(result, thegcd);
    if (den == FIX(1))
	result = num;		/* speed hack */
    else if (den == FIX(-1))
	result = negate(num);	/* speed hack */
    else {
	thegcd = gcd(num, den);
	if (minusp(den))
	    thegcd = negate(thegcd);
	num = integer_quotient(num, thegcd);
	den = integer_quotient(den, thegcd);
	if (den == FIX(1))
	    result = num;
	else
	    result = make_ratio(num, den);
    }
    RESTORE_STACK();
    return result;
}

/* Integer_quotient returns the integer result (truncate) of dividing two
   integers. */
/* Note that (/ most-negative-fixnum -1) is a bignum. */

static Object integer_quotient(x, y)
    Object x, y;
{
    Object result = NIL;
    Declare_stack_pointer;
    if (y == FIX(1))
	return x;
    if (y == FIX(-1L))
	return negate(x);
    if (FIXNUMP(x) && FIXNUMP(y))
	return FIXNUM_DIVIDE(x, y);

    SAVE_STACK();
    PROTECT_3(x, y, result);
    if (!XBIGNUMP(x)) x = clong_to_bignum(IINTEGER(x));
    if (!XBIGNUMP(y)) y = clong_to_bignum(IINTEGER(y));
    result = perform_safely(bignum_quotient, x, y);
    result = xbignum_normalize(result);
    RESTORE_STACK();
    return result;
}

Object numerator (x)
    Object x;
{
    Declare_local_temp;
    return VALUES_1(NUMERATOR(x));
}

Object denominator (x)
    Object x;
{
    Declare_local_temp;
    return VALUES_1(DENOMINATOR(x));
}

/* Still used by lreader.c and misc.c - flush after these are fixed */
Object make_canonical_rational(n, d)
    SI_Long n,d;
{
    Declare_local_temp;
    SI_Long thegcd;
    Object result, num, den;
    Declare_stack_pointer;

    if (d == 0L)
      error(2, "division by zero - (/ ~S 0)", MAKE_INTEGER(n));

    SAVE_STACK();
    PROTECTI_3(result, num, den);
    if (d < 0) {
        n = -n;
        d = -d;
    }    
    thegcd = SI_igcd(n,d);
    n /= thegcd;
    d /= thegcd;
    if (d == 1)
        return VALUES_1(MAKE_INTEGER(n));
    num = MAKE_INTEGER(n);
    den = MAKE_INTEGER(d);
    result = make_ratio(num, den);
    RESTORE_STACK();
    return VALUES_1(result);
}


/* Integer division: truncate and friends */

/* 3rd arg to do_division: 1 = quotient, 2 = remainder, 3 = both */

enum division_op {
    TRUNCATE,
    FLOOR,
    CEILING,
    MROUND
};

Object ltruncate (x, y)
    Object x, y;
{
    return do_division(x, y, TRUNCATE, 3, FALSE);
}

Object lfloor(x, y)
    Object x, y;
{
    return do_division(x, y, FLOOR, 3, FALSE);
}

/* Use this if don't care about the remainder */
Object lfloor_1(x, y)
    Object x, y;
{
    return do_division(x, y, FLOOR, 1, FALSE);
}

Object ceiling(x, y)
    Object x, y;
{
    return do_division(x, y, CEILING, 3, FALSE);
}

Object l_round(x, y)
    Object x, y;
{
    return do_division(x, y, MROUND, 3, FALSE);
}

Object mod(x, y)
    Object x, y;
{
    return do_division(x, y, FLOOR, 2, FALSE);
}

Object rem(x, y)
    Object x, y;
{
    return do_division(x, y, TRUNCATE, 2, FALSE);
}

Object lffloor(x, y)
    Object x, y;
{
    return do_division(x, y, FLOOR, 3, TRUE);
}

Object fceiling(x, y)
    Object x, y;
{
    return do_division(x, y, CEILING, 3, TRUE);
}

Object lftruncate(x, y)
    Object x, y;
{
    return do_division(x, y, TRUNCATE, 3, TRUE);
}

Object fround(x, y)
    Object x, y;
{
    return do_division(x, y, MROUND, 3, TRUE);
}

#ifdef NEW_BIGNUMS

static Object do_division(x, y, op, which, floatp)
    Object x, y;
    enum division_op op;
    int which;
    int floatp;
{
    Declare_local_temp;
    Object quo, rem;
    double dy, dz, dq; int res_flag;
    SI_Stack_item *top_of_stack;

    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x, y);
    PROTECTI_2(quo, rem);

    if (UNSUPPLIED_P(y)) y = FIX(1L);
/* TODO:
    if (INTEGER(x) && FIXNUMP(y) {

    }
    else
 */
    if (!RATIONALP(x) || !RATIONALP(y)) {
	dy = object_to_cdouble(y);
	dz = object_to_cdouble(x) / dy;
	switch(op) {
	case TRUNCATE:
	    dq = aint(dz);
	    break;
	case FLOOR:
	    dq = floor(dz);
	    break;
	case CEILING:
	    dq = ceil(dz);
	    break;
	case MROUND:
	    /* Presumes rounding mode is NORMAL */
	    dq = rint(dz);
	    break;
	}
	if (which & 1L)
	    quo = floatp ? cdouble_to_double(dq) : double_to_integer(dq);
	if (which & 2L)
	    rem = cdouble_to_double((dz - dq) * dy);
    } else {
	Object xnum, xden, ynum, yden, numgcd, dengcd, temp1, temp2;
	Object num, den, rnum, rden, halfway;

	PROTECTI_8(xnum, xden, ynum, yden, numgcd, dengcd, temp1, temp2);
	PROTECTI_5(num, den, rnum, rden, halfway);

	/* We compute gcd's and divide in order to keep all numbers as
	   small as possible; this increases our chances of making all
	   arithmetic stay within fixnum range.  On the other hand, if
	   we're dealing in bignums, this could result in significantly
	   more consing than otherwise. */

	/* For example: (truncate 51/35 39/55). */
	xnum = NUMERATOR(x);	                /* 3 * 17 */
	xden = DENOMINATOR(x);			/* 5 * 7 */
	ynum = NUMERATOR(y);			/* 3 * 13 */
	yden = DENOMINATOR(y);			/* 5 * 11 */
	numgcd = gcd(xnum, ynum);		/* 3 */
	dengcd = gcd(xden, yden);		/* 5 */
	temp1 = integer_quotient(xnum, numgcd);	/* 17 */
	temp2 = integer_quotient(yden, dengcd);	/* 11 */
	num = ltimes(temp1, temp2);		/* 17 * 11 */
	temp1 = integer_quotient(xden, dengcd);	/* 7 */
	temp2 = integer_quotient(ynum, numgcd);	/* 13 */
	den = ltimes(temp1, temp2);		/* 7 * 13 */

	/* Compute quotient and remainder of integer division */
	if (FIXNUMP(num) && FIXNUMP(den) && den != MOST_NEGATIVE_FIXNUM) {
	    quo = FIXNUM_DIVIDE(num, den);
	    rem = FIXNUM_REM(num, den);
	} else {
	    if (!XBIGNUMP(num)) num = clong_to_bignum(IINTEGER(num));
	    if (!XBIGNUMP(den)) den = clong_to_bignum(IINTEGER(den));

	    SI_gc_unsafe = 1;
	    top_of_stack = Stack;
	    while (setjmp(SI_restart_unsafe)) {
		Stack = top_of_stack;
		SI_UNSAFE_OP_FAILED();
	    }
	    res_flag = bignum_divide(num, den, &quo, &rem);
	    SI_gc_unsafe = 0;
    	    if (res_flag)
		error(2, "division by zero - (/ ~S 0)", x);
	    quo = xbignum_normalize(quo);
	    rem = xbignum_normalize(rem);
	}
	rnum = ltimes(rem, ynum);
	rden = ltimes(den, yden);
	switch(op) {
	case TRUNCATE:
	    break;
	case FLOOR:
	    /* Choose low value for quo; it will too big by 1 iff rem and y
	       have opposite signs. */
	    if (rnum != ZERO &&
		((plusp(rnum) == plusp(rden)) != (plusp(ynum) != NIL))) {
		/*
		 * INVARIANT: quo*y + rem = x
		 *     ...  = (quo+1)*y + (rem-y)
		 *     ...  = (quo-1)*y + (rem+y)
		 * rem = rnum/rden = (rem*ynum)/(den*yden)
		 * rem + y = (rem*ynum)/(den*yden) + ynum/yden
		 *         = (rem*ynum)/(den*yden) + (den*ynum)/(den*yden)
		 *	   = (rem*ynum + den*ynum)/(den*yden)
		 */
		quo = sub1(quo);
		rnum = add(rnum, ltimes(ynum, den));
	    }
	    break;
	case CEILING:
	    /* Choose high value for quo; it will be too small by 1 iff rem and
	       y have the same sign. */
	    if (rnum != 0 &&
		(plusp(rnum) == plusp(rden)) == (plusp(ynum) != NIL)) {
		quo = add1(quo);
		rnum = minus(rnum, ltimes(ynum, den));
	    }		
	    break;
	case MROUND:
	    /* (ROUND 32767/65536 -2/3) should be -1, -32771/196608 */

	    /* Round to nearest, breaking ties toward the even value for quo.
	     * Conditions under which adjustment are needed are:
	     * 1. |rem| > |y|/2
	     * 2. rem != 0 and |rem| = |y|/2 and oddp(quo).
	     */

	    if (zerop(rnum)) break;		/* no adjustment needed */

	    temp1 = ltimes(ynum, den);
	    halfway = integer_quotient(temp1, FIX(2L));  /* always positive */

	    if (TRUEP(plusp(rnum))) {
	      if (TRUEP(num_gt(rnum, halfway)) ||
		  (TRUEP(num_eq(rnum, halfway)) && TRUEP(oddp(quo)))) {
		if (minusp(y) == minusp(rden)) goto adjust_for_round_add1;
		else goto adjust_for_round_sub1;
	      }
	      else break;
	    }
	    else {
	      halfway = negate(halfway);
	      if (TRUEP(num_lt(rnum, halfway)) ||
		  TRUEP(num_eq(rnum, halfway)) && TRUEP(oddp(quo))) {
		if (minusp(y) != minusp(rden)) goto adjust_for_round_add1;
		else goto adjust_for_round_sub1;
	      }
	      else break;
	    }
	    /*NOTREACHED*/

adjust_for_round_add1:
	    quo = add1(quo);
	    rnum = minus(rnum, temp1);
	    break;
adjust_for_round_sub1:
	    quo = sub1(quo);
	    rnum = add(rnum, temp1);
	    break;
	}
	if ((which & 1) && floatp)
	    quo = cdouble_to_double(object_to_cdouble(quo));
	if (which & 2)
	    rem = xmake_canonical_rational(rnum, rden);
    }
    RESTORE_STACK();
    switch (which) {
    case 1:
	return VALUES_1(quo);
    case 2:
	return VALUES_1(rem);
    case 3:
	break;
    }
    return VALUES_2(quo, rem);	/* lint can't cope if this is in the switch */
}

#else /* Not NEW_BIGNUMS */

static Object do_division (x, y, op, which, floatp)
    Object x, y;
    enum division_op op;
    int which;
{
    Declare_local_temp;
    Object quo, rem, temp;
    SI_Long xnum, xden, ynum, yden, numgcd, dengcd, num, den, iq;
    SI_Long rnum, rden, halfway;
    double dy, dz, dq;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x, y);
    PROTECTI_3(quo, rem, temp);

    if (UNSUPPLIED_P(y))
	y = FIX(1L);
    if (!RATIONALP(x) || !RATIONALP(y)) {
	dy = object_to_cdouble(y);
	dz = object_to_cdouble(x) / dy;
	switch(op) {
	case TRUNCATE:
	    dq = aint(dz);
	    break;
	case FLOOR:
	    dq = floor(dz);
	    break;
	case CEILING:
	    dq = ceil(dz);
	    break;
	case MROUND:
	    /* Presumes rounding mode is NORMAL */
	    dq = rint(dz);
	    break;
	}
	if (which & 1)
	    quo = floatp ? cdouble_to_double(dq) : T_MAKE_INTEGER((SI_Long) dq);
	if (which & 2)
	    rem = cdouble_to_double((dz - dq) * dy);
    } else {
	temp = NUMERATOR(x);
	xnum = INTEGER_TO_LONG(temp);	/* 3 * 17 */
	temp = DENOMINATOR(x);
	xden = INTEGER_TO_LONG(temp);	/* 5 * 7 */
	temp = NUMERATOR(y);
	ynum = INTEGER_TO_LONG(temp);	/* 3 * 13 */
	temp = DENOMINATOR(y);
	yden = INTEGER_TO_LONG(temp);	/* 5 * 11 */
	numgcd=SI_igcd(xnum,ynum);			/* 3 */
	dengcd=SI_igcd(xden,yden);			/* 5 */
	num = (xnum/numgcd)*(yden/dengcd);	/* 17 * 11 */
	den = (xden/dengcd)*(ynum/numgcd);	/* 7 * 13 */
	iq = num / den;
	rnum = (num % den) * ynum;
	rden = den * yden;
	switch(op) {
	case TRUNCATE:
	    break;
	case FLOOR:
	    /* Choose low value for quo; it will too big by 1 iff rem and y
	       have opposite signs. */
	    if (rnum != 0 &&
		(((rnum > 0) == (rden > 0)) != (ynum > 0))) {
		--iq;
		rnum += ynum * den;
	    }
	    break;
	case CEILING:
	    /* Choose high value for quo; it will be too small by 1 iff rem and
	       y have the same sign. */
	    if (rnum != 0 &&
		(((rnum > 0) == (rden > 0)) == (ynum > 0))) {
		++iq;
		rnum -= ynum * den;
	    }		
	    break;
	case MROUND:
	    /* (ROUND 32767/65536 -2/3) should be -1, -32771/196608 */

	    /* Choose a quo such that rem has minimum absolute value. */
	    /* We'll need to adjust only when |rem| > |y|/2. */

	    halfway = (ynum * den) / 2;	    /* always positive */
	    if (rnum > halfway || rnum < -halfway ||
		((rnum == halfway || rnum == -halfway) &&
		 (rden & 1) == 0 && /* ? */
		 (iq & 1))) {
		if ((rnum > 0) == (rden > 0)) {
		    ++iq;
		    rnum -= ynum * den;
		} else {
		    --iq;
		    rnum += ynum * den;
		}
	    }
	    break;
	}
	if (which & 1)
	    quo = floatp ? cdouble_to_double((double) iq) : MAKE_INTEGER(iq);
	if (which & 2)
	    rem = make_canonical_rational(rnum, rden);
    }
    RESTORE_STACK();
    switch (which) {
    case 1:
	return VALUES_1(quo);
    case 2:
	return VALUES_1(rem);
    case 3:
	return VALUES_2(quo, rem);
    }
}
#endif



/* Rational / rationalize */

Object rational(x)
    Object x;
{
    Declare_local_temp;
    Object significand, exponent, sign, num, den, result;
    Declare_stack_pointer;

    if (RATIONALP(x))
	result = x;
    else {
	SAVE_STACK();
	PROTECTI_4(significand, num, den, result);
	MVS_3(integer_decode_float(x), significand, exponent, sign);
	num = ltimes(significand, sign);
	if (FIXNUM_MINUSP(exponent)) {
	    /* den = ash(FIX(1), FIXNUM_NEGATE(exponent)); */
	    den = expt(FIX(SI_FLOAT_RADIX), FIXNUM_NEGATE(exponent));
	    result = xmake_canonical_rational(num, den);
	} else {
	    /* result = ash(num, exponent); */
	    den = expt(FIX(SI_FLOAT_RADIX), exponent);
	    result = ltimes(num, den);
	}
	RESTORE_STACK();
    }
    return VALUES_1(result);
}

static Object srationalize();
static Object simplest_rational();
static Object simplest_rational_internal();

Object rationalize(x)
    Object x;
{
    Declare_local_temp;
    if (RATIONALP(x))
	return VALUES_1(x);
    else if (zerop(x))
	return VALUES_1(ZERO);
    else
	/* This definition is a temporary kludge until we figure out how
	   to do this properly.  It can underflow. */
	return srationalize(x, scale_float(x, FIX(-(SI_FLOAT_MANT_DIG - 1))));
}

/*
 * Simplest rational within an interval.  Translated from IEEE P1178/D4
 * (Scheme draft standard) file nimpl.tex.
 */

static Object srationalize(x,e)
    Object x;
    Object e;
{
    Object l1_e;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,e);
    PROTECTI_2(l1_e,temp1);
    l1_e = l_abs(e);
    temp1 = CALL_2(simplest_rational,minus(x,l1_e),add(x,l1_e));
    RESTORE_STACK();
    return(temp1);
}

static Object simplest_rational(x,y)
    Object x;
    Object y;
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);
    PROTECTI_1(temp1);
    if (num_ge(x,y)) {
	temp1 = (RATIONALP(x) ? VALUES_1(x) : 
		 error(2, "rationalize: internal error - ~S", x));
    }
    else if (num_gt(x,ZERO)) {
	temp1 = simplest_rational_internal(x,y);
    }
    else if (num_lt(y,ZERO)) {
	temp1 = minus(ZERO,CALL_2(simplest_rational_internal,minus(ZERO,y),
		minus(ZERO,x)));
    }
    else 
	temp1 = VALUES_1(ZERO);
    RESTORE_STACK();
    return(temp1);
}

static Object simplest_rational_internal (x, y)
    Object x;
    Object y;
{
    Declare_local_temp;
    Object fx;
    Object fy;
    Object temp1;
    extern Object simplest_rational_internal();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);
    PROTECTI_3(fx,fy,temp1);
    fx = lfloor(x,KOPT);
    fy = lfloor(y,KOPT);
    if (num_ge(fx,x)) {
	temp1 = VALUES_1(fx);
    }
    else if (num_eq(fx,fy)) {
	temp1 = CALL_2(simplest_rational_internal,divide(FIX(1),minus(y,
		fy)),divide(FIX(1),minus(x,fx)));
	temp1 = CALL_2(add,fx,divide(FIX(1), temp1));
    }
    else 
	temp1 = add(FIX(1),fx);
    RESTORE_STACK();
    return(temp1);
}

/* Binary integer exponentiation algorithm */

Object expt (x, y)
    Object x, y;
{
    Declare_local_temp;
    Object result, multiplier;
    int i, invertp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);

    if (RATIONALP(x) && INTEGERP(y)) {
	i = INTEGER_TO_LONG(y);
	if (i < 0) {
	    i = -i;
	    invertp = 1;
	}
	else
	    invertp = 0;
	result = FIX(1L);
	multiplier = x;
	PROTECT_2(result, multiplier);
	while (i>0) {
	    if (i & 1) {
		result = ltimes(result, multiplier);
		--i;
	    } else {
		multiplier = ltimes(multiplier, multiplier);
		i >>= 1;
	    }
	}
	if (invertp)
	    result = reciprocal(result);
    } else
	result = cfuncall_d2(pow,x,y);

    RESTORE_STACK();
    return VALUES_1(result);
}

SI_Long expt_long (x, y)
     SI_Long x, y;
{
  SI_Long multiplier, result = 1L;
  
  if ( y < 0 )
    error(2, "expt_long: negative second argument");
  multiplier = x;
  while ( y > 0 )
    {
      if (y & 1)
	{result = result * multiplier;
	 --y;}
      else
	{multiplier = multiplier * multiplier;
	 y >>= 1;}
    }
  return result;
}

Object lexp (x)
    Object x;
{
    return cfuncall_d1(exp, x);
}

/* &optional 1 1  */
Object llog (x, base)
    Object x, base;
{
    Declare_local_temp;
    Object tmp, result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x, base);

    if (UNSUPPLIED_P(base))
        result = cfuncall_d1(log, x);
    else if (num_eq(base, FIX(10L)))
	result = cfuncall_d1(log10, x);
    else {
	/* Taking the direct call to cfuncall_d1(log, x) out of the CALL_2
	 * macro cures an NCR compiler bug.
	 */
	tmp = cfuncall_d1(log, x);
	result = CALL_2(divide, tmp, cfuncall_d1(log, base));
    }
    RESTORE_STACK();
    return VALUES_1(result);
}

Object lsqrt(x)
    Object x;
{
    if (minusp(x))
	return make_complex(SI_Float_zero, cfuncall_d1(sqrt,l_abs(x)));
    return cfuncall_d1(sqrt,x);
}

/* ISQRT()
 *
 * Hand translation of code from CMU Common Lisp.
 *
 * ISQRT:  Integer square root - isqrt(n)**2 <= n
 * Upper and lower bounds on the result are estimated using integer-length.
 * On each iteration, one of the bounds is replaced by their mean.
 * The lower bound is returned when the bounds meet or differ by only 1.
 * Initial bounds guarantee that lg(sqrt(n)) = lg(n)/2 iterations suffice.
 *
 * (defun isqrt (n)
 *   (if (and (integerp n) (not (minusp n)))
 *       (do* ((lg (integer-length n))
 *	       (lo (ash 1 (ash (1- lg) -1)))
 *	       ;; tighten by 3/4 if possible.
 *	       (hi (+ lo (ash lo (if (oddp lg) -1 0)))))
 *	      ((<= (1- hi) lo) lo)
 *	   (let ((mid (ash (+ lo hi) -1)))
 *	     (if (<= (* mid mid) n) (setq lo mid) (setq hi mid))))
 *       (error "Isqrt: ~S argument must be a nonnegative integer" n)))
 */

static Object bignum_isqrt(n)
  Object n;
{
    Declare_local_temp;
  Declare_protect(4);
  Object lo, hi, mid, temp;
  short lg;

  PROTECT_LOCALS();
  PROTECT_1(n);
  PROTECTI_3(lo, hi, mid);

  lg = (short)IFIX(integer_length(n));
  lo = ash(FIX(1), FIX((lg-1) >> 1));
  if (lg & 1) temp = ash(lo, FIX(-1));
  else temp = lo;
  hi = add(lo, temp);

  for ( ;; ) {
    temp = sub1(hi);
    if (TRUEP(num_le(temp, lo))) break;
    temp = add(lo, hi);
    mid = ash(temp, FIX(-1));
    temp = ltimes(mid, mid);
    if (TRUEP(num_le(temp, n))) lo = mid;
    else hi = mid;
  }
  UNPROTECT_LOCALS();
  return VALUES_1(lo);
}

Object isqrt (x)
  Object x;
{
    Declare_local_temp;
  if (FIXNUMP(x)) {
    SI_Long n, lo, hi, mid;
    short lg;

    n = IFIX(x);
    if (n == 0) return VALUES_1(ZERO);
    else if (n < 0) goto negative_arg;
    else {
      lg = (short)IFIX(integer_length(x));
      lo = (SI_Long)(1 << ((lg-1) >> 1));
      hi = lo + (lo >> ((lg & 1) ? 1 : 0));
      while ((hi-1) > lo) {
	mid = (lo + hi) >> 1;
	if ((mid * mid) <= n) lo = mid;
	else hi = mid;
      }
      return VALUES_1(FIX(lo));
    }
  }
  else if (LONG64P(x)) {
    SI_int64 n, lo, hi, mid;
    short lg;

    n = ILONG64(x);
    if (n == 0) return VALUES_1(ZERO);
    else if (n < 0) goto negative_arg;
    else {
      lg = (short)IFIX(integer_length(x));
      lo = (SI_int64) (1L << ((lg-1) >> 1L));
      hi = lo + (lo >> ((lg & 1L) ? 1L : 0L));
      while ((hi-1) > lo) {
	mid = (lo + hi) >> 1L;
	if ((mid * mid) <= n) lo = mid;
	else hi = mid;
      }
      return VALUES_1(MAKE_INTEGER(lo));
    }
  }
  else if (BIGNUMP(x)) {
    if (minusp(x)) goto negative_arg;
    else return bignum_isqrt(x);
  }
  else {
    SI_type_error(x, Qinteger);
    /*NOTREACHED*/
  }

negative_arg:
  { SI_Declare_static_constant(etype, d, STATIC_LIST(2, Qinteger, FIX(0)));
    SI_type_error(x, etype);
    /*NOTREACHED*/
  }

  // Return 0 in other cases. Code never executed
  return VALUES_1(0);
}

Object phase(x)
    Object x;
{
    return latan(imagpart(x),realpart(x));
}

static Object complex_conjugate(a)
  Object a;
{
    Declare_local_temp;
  Declare_protect(1);
  Object temp;

  PROTECT_LOCALS();
  PROTECT_1(a);
  temp = negate(COMPLEX_IMAG(a));
  temp = make_complex(COMPLEX_REAL(a), temp);
  UNPROTECT_LOCALS();
  return VALUES_1(temp);
}

Object conjugate(a)
  Object a;
{
    Declare_local_temp;
  if (!COMPLEXP(a)) return VALUES_1(a);
  else return complex_conjugate(a);
}

Object signum(x)
    Object x;
{
    Declare_local_temp;
    Object result;
    if (FIXNUMP(x)) {
      if (FIXNUM_PLUSP(x))
	result = FIX(1L);
      else
	result = EQ(x, ZERO) ? ZERO : FIX(-1L);
    }
    else switch(PNODE_TYPE(x)) {
    case RATIO_TYPE:
	x = RATIO_NUMERATOR(x);
    case OBIGNUM_TYPE:
    case XBIGNUM_TYPE:
	result = plusp(x) ? FIX(1L) : FIX(-1L);
	break;
    case LONG64_TYPE:
	result = (ILONG64(x) > (SI_int64) 0L) ? FIX(1L) : FIX(-1L);
	break;
    default:
	result = zerop(x) ? x : divide(x, l_abs(x));
	break;
    }
    return VALUES_1(result);
}

Object lsin(x)
    Object x;
{
    return cfuncall_d1(sin, x);
}

Object lcos(x)
    Object x;
{
    return cfuncall_d1(cos, x);
}

Object ltan(x)
    Object x;
{
    return cfuncall_d1(tan,x);
}

Object cis(x)
    Object x;
{
    Declare_local_temp;
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    result = CALL_2(make_complex, lcos(x), lsin(x));

    RESTORE_STACK();
    return VALUES_1(result);
}

/* Object hard_asin(Object x)
 * Object hard_acos(Object x)
 *
 * These are used when the argument can't be coerced into the domain of the C
 * library routines asin and acos, which require a double in the range [-1,1].
 * In this case, could conceivably use the formulas from CLtL, even though they
 * may not be great, since it seems better than nothing.
 *
 *   lasin(z) = -i*log(i*z + sqrt(1 - z*z))
 *   lacos(z) = -i*log(z + i*sqrt(1 - z*z))
 *
 * However, since complex arithmetic isn't supported yet this still fails.
 * Instead, just signal an error here.
 */

#if 0
static Object hard_asin(z)
  Object z;
{
    Declare_local_temp;
  Declare_protect(3);
  Object t1, t2;

  PROTECT_LOCALS();
  PROTECT_1(z);
  PROTECTI_2(t1, t2);

  INIT_PLUS_MINUS_I();

  t1 = ltimes(Positive_i, z);		/* i * z */
  t2 = ltimes(z, z);			/* z * z */
  t2 = minus(FIX(1), t2);		/* 1 - z*z */
  t2 = lsqrt(t2);			/* sqrt(1 - z*z) */
  t1 = add(t1,t2);			/* i*z + sqrt(1 - z*z) */
  t1 = llog(t1);			/* log(i*z + sqrt(1 - z*z)) */
  t1 = ltimes(Negative_i, t1);		/* -i*log(i*z + sqrt(1 - z*z)) */
  UNPROTECT_LOCALS();
  return VALUES_1(t1);
}

static Object hard_acos(z)
  Object z;
{
    Declare_local_temp;
  Declare_protect(3);
  Object t1, t2;

  PROTECT_LOCALS();
  PROTECT_1(z);
  PROTECTI_2(t1, t2);

  INIT_PLUS_MINUS_I();

  t1 = ltimes(z, z);			/* z * z */
  t1 = minus(FIX(1), t2);		/* 1 - z*z */
  t1 = lsqrt(t2);			/* sqrt(1 - z*z) */
  t1 = ltimes(Positive_i, t1);		/* i*sqrt(1 - z*z) */
  t1 = add(z, t1);			/* z + i*sqrt(1 - z*z) */
  t1 = llog(t1);			/* log(z + i*sqrt(1 - z*z)) */
  t1 = ltimes(Negative_i, t1);		/* -i*log(z + i*sqrt(1 - z*z)) */
  UNPROTECT_LOCALS();
  return VALUES_1(t1);
}
#endif

Object lasin(x)
  Object x;
{
    Declare_local_temp;
  double dx;

  if (!COMPLEXP(x)) {
    dx = object_to_cdouble(x);
    if (-1.0 <= dx && dx <= 1.0)
      return VALUES_1(cdouble_to_double(asin(dx)));
  }
  (void)error(2, "ASIN not yet implemented for arguments outside [-1,1]: ~S.", x);
  /*NOTREACHED*/

  // Return 0 in other cases. Code never executed
  return VALUES_1(0);
}

Object lacos(x)
  Object x;
{
    Declare_local_temp;
  double dx;

  if (!COMPLEXP(x)) {
    dx = object_to_cdouble(x);
    if (-1.0 <= dx && dx <= 1.0)
      return VALUES_1(cdouble_to_double(acos(dx)));
  }
  (void)error(2, "ACOS not yet implemented for arguments outside [-1,1]: ~S.", x);
  /*NOTREACHED*/

  // Return 0 in other cases. Code never executed
  return VALUES_1(0);
}

#define UNIMPLEMENTED_FOR_COMPLEX(name, arg) \
    if (COMPLEXP(arg)) { \
      SI_Declare_static_string(nstr, d, STATIC_STRING(name)); \
      (void)error(3, "~A not yet implemented for complex arguments: ~S.", \
		  nstr, arg); \
    }
      

Object latan(x, y)
    Object x,y;
{ UNIMPLEMENTED_FOR_COMPLEX("ATAN", x);
  if (UNSUPPLIED_P(y)) return cfuncall_d1(atan, x);
  UNIMPLEMENTED_FOR_COMPLEX("ATAN", y);
  return cfuncall_d2(atan2, x, y);
}

Object lsinh(x)
    Object x;
{   UNIMPLEMENTED_FOR_COMPLEX("SINH", x);
    return cfuncall_d1(sinh, x);
}

Object lcosh(x)
    Object x;
{   UNIMPLEMENTED_FOR_COMPLEX("COSH", x);
    return cfuncall_d1(cosh, x);
}

Object ltanh(x)
    Object x;
{   UNIMPLEMENTED_FOR_COMPLEX("TANH", x);
    return cfuncall_d1(tanh,x);
}

Object lasinh(x)
    Object x;
{
    /* Some systems already have arc hyperbolic functions; see config.h */
#ifdef HAVE_ARC_HYPERBOLIC
    UNIMPLEMENTED_FOR_COMPLEX("ASINH", x);
    /* There may need to be some analysis of x here to prevent errors due to
     * the result being complex rather than real. */
    return cfuncall_d1(asinh, x);
#else
    return error(1, "ASINH not yet implemented.");
#endif
}

Object lacosh(x)
    Object x;
{
#ifdef HAVE_ARC_HYPERBOLIC
    UNIMPLEMENTED_FOR_COMPLEX("ACOSH", x);
    /* There may need to be some analysis of x here to prevent errors due to
     * the result being complex rather than real. */
    return cfuncall_d1(acosh, x);
#else
    return error(1, "ACOSH not yet implemented.");
#endif
}

Object latanh(x)
    Object x;
{
#ifdef HAVE_ARC_HYPERBOLIC
    UNIMPLEMENTED_FOR_COMPLEX("ATANH", x);
    /* There may need to be some analysis of x here to prevent errors due to
     * the result being complex rather than real. */
    return cfuncall_d1(atanh, x);
#else
    return error(1, "ATANH not yet implemented.");
#endif
}

/* Decode-float returns 3 values: significand (a float), exponent
   (an integer), and sign (a float). */

Object decode_float(f)
  Object f;
{ double d;
  int exponent;
  Object df, ex, s;

  d = IDOUBLE(f);
  df = cdouble_to_double(frexp(fabs(d), &exponent));
  ex = FIX(exponent);
  s = (d < 0.0) ? SI_Float_negative_one : SI_Float_one;

  return VALUES_3(df, ex, s);
}

Object integer_decode_float(f)
  Object f;
{ double d, significand;
  int exponent;

  d = IDOUBLE(f);
  significand = frexp(fabs(d), &exponent);
  if (d != 0.0) exponent -= SI_FLOAT_MANT_DIG;
  significand = ldexp(significand, SI_FLOAT_MANT_DIG);
  return VALUES_3(double_to_integer(significand),
		  FIX(exponent),
		  (d < 0.0) ? FIX(-1) : FIX(1));
}

Object scale_float(f, k)
    Object f, k;
{
    Declare_local_temp;
    double r;
    /* result = ltimes(f, expt(lfloat(float_radix(f), f), k)); */
    r = ldexp(IDOUBLE(f), (int)IFIX(k));
    return VALUES_1(cdouble_to_double(r));
}

/*ARGSUSED*/
Object float_radix(f)
    Object f;
{
    Declare_local_temp;
    return VALUES_1(FIX(SI_FLOAT_RADIX));
}

/* &optional 1 1 */
Object float_sign(f1, f2)
  Object f1, f2;
{
    Declare_local_temp;
  Object res;

  if (minusp(f1))
    if (UNSUPPLIED_P(f2)) res = SI_Float_negative_one;
    else if (minusp(f2)) res = f2;
    else res = negate(f2);
  else if (UNSUPPLIED_P(f2)) res = SI_Float_one;
  else if (minusp(f2)) res = negate(f2);
  else res = f2;

  return VALUES_1(res);
}

/*ARGSUSED*/
Object float_digits(f)
    Object f;
{
    Declare_local_temp;
    return VALUES_1(FIX(SI_FLOAT_MANT_DIG));
}

/* *** This needs to be conditionalized for SI_SUPPORT_DENORMS. */
Object float_precision(f)
    Object f;
{
    Declare_local_temp;
    /* "Precision will be less than digits for a denormalized or zero
       number."  - CLtL I */
    if (zerop(f))
	return VALUES_1(ZERO);
    else
	return VALUES_1(FIX(SI_FLOAT_MANT_DIG));
}

/* &optional 1 1  */
Object lcomplex(real, imag)
    Object real, imag;
{
    Declare_local_temp;
    /* Pretty bogus */
    if (UNSUPPLIED_P(imag) || zerop(imag))
	return VALUES_1(real);
    return make_complex(real, imag);
}

Object realpart(a)
    Object a;
{
    Declare_local_temp;
    return VALUES_1(COMPLEXP(a) ? COMPLEX_REAL(a) : a);
}

Object imagpart(a)
    Object a;
{
    Declare_local_temp;
    return COMPLEXP(a) ? VALUES_1(COMPLEX_IMAG(a)) : ltimes(ZERO, l_abs(a));
}

/* Bitwise logical operations */

Object logior(a, b)
    Object a, b;
{
    return SI_do_math2(a, b, LOGIOR);
}

#if SI_SUPPORT_MF
Object logiorr(a)
    Object a;
{
    Declare_local_temp;
    return (a == NIL)
	? VALUES_1(ZERO) 
	: num_iterate(SI_do_math2, CAR(a), CDR(a), LOGIOR);
}
#endif

Object logiorn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (n == 0)
	return VALUES_1(ZERO);
    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, LOGIOR, n, rest);
    RESTORE_STACK();
    return result;
}

Object logxor(a, b)
    Object a, b;
{
    return SI_do_math2(a, b, LOGXOR);
}

#if SI_SUPPORT_MF
Object logxorr(a)
    Object a;
{
    Declare_local_temp;
    return (a == NIL)
	? VALUES_1(ZERO) 
	: num_iterate(SI_do_math2, CAR(a), CDR(a), LOGXOR);
	     
}
#endif

Object logxorn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (n == 0)
	return VALUES_1(ZERO);
    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, LOGXOR, n, rest);
    RESTORE_STACK();
    return result;
}

Object logand (a, b)
    Object a, b;
{
	Object result;
	SI_int64 i;

	if (FIXNUMP(a) && FIXNUMP(b)) {
		result = FIX(IFIX(a) & IFIX(b));
	} else if (FIXNUMP(a) && LONG64P(b)) {
	    i = (SI_int64) IFIX(a) & ILONG64(b);
	    result = MAKE_INTEGER(i);
	} else if (LONG64P(a) && FIXNUMP(b)) {
	    i = ILONG64(a) & (SI_int64) IFIX(b);
	    result = MAKE_INTEGER(i);
	} else if (LONG64P(a) && LONG64P(b)) {
	    i = ILONG64(a) & ILONG64(b);
	    result = MAKE_INTEGER(i);
	} else {
	    if (!XBIGNUMP(a)) a = clong_to_bignum(IINTEGER(a));
	    if (!XBIGNUMP(b)) b = clong_to_bignum(IINTEGER(b));
	    result = xbignum_normalize(perform_safely(bignum_logand, a,b));
	}
	return result;
}

#if SI_SUPPORT_MF
Object logandr (a)
    Object a;
{
    Declare_local_temp;
    return (a == NIL)
	    ? VALUES_1(FIX(-1L))
	    :num_iterate(SI_do_math2, CAR(a), CDR(a), LOGAND);
	   
}
#endif

Object logandn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (!n)
	return VALUES_1(FIX(-1L));
    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, LOGAND, n, rest);
    RESTORE_STACK();
    return result;
}

Object logeqv(a, b)
    Object a, b;
{
    return SI_do_math2(a, b, LOGEQV);
}

#if SI_SUPPORT_MF
Object logeqvr(a)
    Object a;
{
    Declare_local_temp;
    return (a == NIL)
	     ? VALUES_1(FIX(-1L))
	     : num_iterate(SI_do_math2, CAR(a), CDR(a), LOGEQV);
}
#endif

Object logeqvn varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *rest;
    Declare_stack_pointer;

    if (!n)
	return VALUES_1(FIX(-1L));
    SAVE_STACK();
    SETUP_REST(n, rest);
    result = num_iteraten(SI_do_math2, LOGEQV, n, rest);
    RESTORE_STACK();
    return result;
}

Object lognand(n1, n2)
    Object n1, n2;
{
    return lognot(logand(n1, n2));
}

Object lognor(n1, n2)
    Object n1, n2;
{
    return lognot(logior(n1, n2));
}

Object logandc1(n1, n2)
    Object n1, n2;
{
    return logand(lognot(n1), n2);
}

Object logandc2(n1, n2)
    Object n1, n2;
{
    return logand(n1, lognot(n2));
}

Object logorc1(n1, n2)
    Object n1, n2;
{
    return logior(lognot(n1), n2);
}

Object logorc2(n1, n2)
    Object n1, n2;
{
    return logior(n1, lognot(n2));
}

/*ARGSUSED*/
static Object boole__clr(n1, n2)
    Object n1, n2;
{
    Declare_local_temp;
    return VALUES_1(ZERO);
}

/*ARGSUSED*/
static Object boole__set(n1, n2)
    Object n1, n2;
{
    return logeqv(n1, n1);
}

/*ARGSUSED*/
static Object boole__1(n1, n2)
    Object n1, n2;
{
    Declare_local_temp;
    return VALUES_1(n1);
}

/*ARGSUSED*/
static Object boole__2(n1, n2)
    Object n1, n2;
{
    Declare_local_temp;
    return VALUES_1(n2);
}

/*ARGSUSED*/
static Object boole__c1(n1, n2)
    Object n1, n2;
{
    return lognot(n1);
}

/*ARGSUSED*/
static Object boole__c2(n1, n2)
    Object n1, n2;
{
    return lognot(n2);
}

Object boole(op, n1, n2)
    Object op;
    Object n1, n2;
{
    return (*Boole_functions[IFIX(op)])(n1, n2);
}

Object lognot(a)
    Object a;
{
    return do_math1(a, LOGNOT);
}

Object logtest(n1, n2)
    Object n1, n2;
{
    Declare_local_temp;
    return VALUES_1(NOT(zerop(logand(n1, n2))));
}

Object logbitp(k, n)
    Object k, n;
{
    Declare_local_temp;
    /* (ldb_test(byte(1L,k),n) */
    return VALUES_1(logand(n, ash(FIX(1L), k)) == ZERO ? NIL : T);
}

Object ash(a, b)
    Object a, b;
{
    return SI_do_math2(a, b, ASH);
}

Object logcount(a)
    Object a;
{
    return do_math1(a, LOGCOUNT);
}

int logcount_long(a)
     SI_Long a;
{
  SI_Long a1 = a;
  int i, count;
  
  if (a1 < 0) a1 = ~a1;
  for (i = 0, count = 0; i < SI_BITS_PER_FIXNUM; i++)
    if (a1 & ((SI_Long)1L << i))
      count++;
  return count;
}

/* Try 31, 47, 767, etc. */
/* Probably buggy on negative arguments */

Object integer_length(a)
    Object a;
{
    Declare_local_temp;
    SI_Long result = 0;
    SI_Long n;
    SI_Ulong i, j;

    if (XBIGNUMP(a))
	result = bignum_integer_length (a);
    else if (LONG64P(a)) {
	SI_int64 n64;
	SI_uint64 i64, j64;

	n64 = INTEGER_TO_INT64(a);
	i64 = (n < 0L) ? (SI_uint64)~n : (SI_uint64)n;
	if (j64 = i64 & 0xffffffff00000000) { result += 32; i64 = j64 >> 32L; }
	if (j64 = i64 & 0xffff0000) { result += 16; i64 = j64; }
	if (j64 = i64 & 0xff00ff00) { result += 8;  i64 = j64; }
	if (j64 = i64 & 0xf0f0f0f0) { result += 4;  i64 = j64; }
	if (j64 = i64 & 0xcccccccc) { result += 2;  i64 = j64; }
	if (j64 = i64 & 0xaaaaaaaa) { result += 1;  i64 = j64; }
	if (i) result += 1;
    } else {
	n = INTEGER_TO_LONG(a);
	i = (n < 0) ? (SI_Ulong)~n : (SI_Ulong)n;
#ifdef Platform_64bit
	if (j = i & 0xffffffff00000000) { result += 32; i = j >> 32; }
#endif
	if (j = i & 0xffff0000) { result += 16; i = j; }
	if (j = i & 0xff00ff00) { result += 8;  i = j; }
	if (j = i & 0xf0f0f0f0) { result += 4;  i = j; }
	if (j = i & 0xcccccccc) { result += 2;  i = j; }
	if (j = i & 0xaaaaaaaa) { result += 1;  i = j; }
	if (i) result += 1;
    }
    return VALUES_1(FIX(result));
}

/* Arguments should be fixnums */
Object byte(size, position)
    Object size, position;
{
    Declare_local_temp;
    Object result;

    result = BYTE(size, position);
    return VALUES_1(result);
}

Object byte_size(bytespec)
    Object bytespec;
{
    Declare_local_temp;
    return VALUES_1(BYTE_SIZE(bytespec));
}

Object byte_position(bytespec)
    Object bytespec;
{
    Declare_local_temp;
    return VALUES_1(BYTE_POSITION(bytespec));
}

Object ldb(bytespec, n)
    Object bytespec, n;
{
    return logand(ash(n, FIXNUM_NEGATE(BYTE_POSITION(bytespec))),
		  minus(ash(FIX(1L), BYTE_SIZE(bytespec)), FIX(1L)));
}

Object ldb_test(bytespec, n)
    Object bytespec, n;
{
    Declare_local_temp;
    return VALUES_1(ldb(bytespec, n) != ZERO ? T : NIL);
}

Object mask_field(bytespec, n)
    Object bytespec, n;
{
    return ash(ldb(bytespec, n), BYTE_POSITION(bytespec));
}

Object dpb(newbyte, bytespec, n)
    Object newbyte, bytespec, n;
{
    Object s = BYTE_SIZE(bytespec);
    Object p = BYTE_POSITION(bytespec);
    Object mask;

    mask = minus(ash(FIX(1L), s), FIX(1L));
    newbyte = logand(newbyte, mask);
    return logior(logand(n, lognot(ash(mask,p))), ash(newbyte, p));
}

Object deposit_field(newbyte, bytespec, n)
    Object newbyte, bytespec, n;
{
    Object s = BYTE_SIZE(bytespec);
    Object p = BYTE_POSITION(bytespec);
    Object mask;

    mask = minus(ash(FIX(1L), s), FIX(1L));
    return logior(logand(n, lognot(ash(mask,p))),
		  mask_field(bytespec, newbyte));
}

/* Random */

/* The low bits from Sun's generator aren't very random! */
#define RAND_DISCARD 2

/* Lokks like rand() only give 15 bits on System V */
#ifdef SI_SYSTEM_V
#define RAND_BITS ((sizeof(int) * CHAR_BIT) - 1 - RAND_DISCARD)
#else
#define RAND_BITS ((sizeof(short) * CHAR_BIT) - 1 - RAND_DISCARD)
#endif

Object l_random(n, state)
    Object n, state;
{
    Declare_local_temp;
    SI_Long num, i;
    Object result;
    SI_Long l;
    double d;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(n, state);
    PROTECTI_1(result);
    if (UNSUPPLIED_P(state)) state = Random_state;

    /* Signatures of Unix rand() and srand() call for ints, not longs or
       unsigneds */
    (void)srand((int) RANDOM_SEED(state));

    if (FIXNUMP(n)) {
	l = num = rand() >> RAND_DISCARD;
	i = SI_BITS_PER_FIXNUM - 1 - RAND_BITS;
	while (i > 0) {
	    l = (l << RAND_BITS) + (num = rand() >> RAND_DISCARD);
	    i -= RAND_BITS;
	}
	i = IFIX(n);
	if (i != 0)
	    l %= i;
	if ((l < 0) != (i < 0))
	    l = -l;
	result = FIX(l);  /* Not an even distribution - fix later */
    } else if (FLOATP(n)) {
	d = 0.0;
	i = IFIX(float_precision(n));
	while (i > 0) {
	    d += (double) (num = rand() >> RAND_DISCARD);
	    d = ldexp(d, -(int)RAND_BITS);
	    i -= RAND_BITS;
	}
	if (d >= 1.0)
	    error(2, "RAND_BITS has the wrong value - ~S", FIX(RAND_BITS));
	d *= IDOUBLE(n);
	result = cdouble_to_double(d);
    } else if (INTEGERP(n)) {
	result = FIX(num = rand() >> RAND_DISCARD);
	i = IFIX(integer_length(n)) - RAND_BITS;
	/* i is number of bits remaining to be computed */
	while (i > 0) {
	    result = ash(result, FIX(MIN(i, RAND_BITS)));
	    result = add(result, FIX(num = rand() >> RAND_DISCARD));
	    i -= RAND_BITS;
	}
	/* Result of mod has same sign as second argument. */
	result = mod(result, n);  /* Not an even distribution - fix later */
    } else
	error(2, "random: invalid argument - ~S", n);
    RANDOM_SEED(state) = num;

    RESTORE_STACK();
    return VALUES_1(result);
}

Object random_state_p(object)
    Object object;
{
    Declare_local_temp;
    return VALUES_1(RANDOM_STATE_P(object) ? T : NIL);
}

/* Auxiliaries */

static Object cfuncall_d1(func, x)
    double (*func)();
    Object x;
{
    return cdouble_to_double((*func)(object_to_cdouble(x)));
}

static Object cfuncall_d2(func, x, y)
    double (*func)();
    Object x, y;
{
    return cdouble_to_double((*func)(object_to_cdouble(x),
				     object_to_cdouble(y)));
}

#if SI_SUPPORT_MF
static Object num_iterate (f, a, b, fn)
    Object (*f)();
    Object a, b;
    enum binary_op fn;
{
    Declare_local_temp;
    Object temp, n1, n2;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(a,b);
    PROTECTI_3(temp,n1,n2);
    for (n1 = VALUES_1(a), temp = b; TRUEP(temp); temp = M_CDR(temp)) {
	n2 = M_CAR(temp);
	if (fn != NONE)
	    n1 = (*f)(n1, n2, fn);
	else
	    n1 = (*f)(n1, n2);
    }
    RESTORE_STACK();
    return n1;
}
#endif

static Object num_iteraten (f, fn, n, rest)
    Object (*f)(), *rest;
    enum binary_op fn;
    int n;
{
    Declare_local_temp;
    Object n1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECTI_2(n1, n2);

    assert(n > 0);	/* This should perhaps be a call to error. */

    n1 = *rest++;
    if (fn != NONE)
	while (--n) n1 = (*f)(n1, *rest++, fn);
    else
	while (--n) n1 = (*f)(n1, *rest++);	
    RESTORE_STACK();
    return VALUES_1(n1);
}

static Object xbignum_zero = NIL;
static Object xbignum_one = NIL;
static Object xbignum_most_positive_fixnum = NIL;
static Object xbignum_most_negative_fixnum = NIL;

init_bignums()
{
    DECLARE_AREA(a);
    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
 /* xbignum_zero = bignum_make_zero();
    xbignum_one = bignum_make_one(0); */
    xbignum_most_positive_fixnum = clong_to_bignum(IMOST_POSITIVE_FIXNUM);
    xbignum_most_negative_fixnum = clong_to_bignum(IMOST_NEGATIVE_FIXNUM);
    RESTORE_CURRENT_AREA(a);
}

Object xbignum_normalize(num)
    Object num;
{
    if (xbignum_most_positive_fixnum == NIL)
	init_bignums();
    if (bignum_compare(num, xbignum_most_positive_fixnum)
	    != bignum_comparison_greater &&
	bignum_compare(num, xbignum_most_negative_fixnum)
	    != bignum_comparison_less)
	return FIX(bignum_to_long(num));
    else
	return num;
}

static Object do_math1 (arg1, fn_code)
    Object arg1;
    enum unary_op fn_code;
{
    Declare_local_temp;
    register int i;
    SI_Long count;
    SI_Long b1;
    SI_Long f1;
    double d1;
    SI_int64 i1;
    Object num, den;
    Object result = NIL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(arg1,result);
    PROTECTI_2(num,den);

    /* until all ZERO/0 bugs found */ /*
    if (arg1 == NIL) {
	warn(1, "do_math1: assuming NIL = 0");
	arg1 = ZERO;
    } */
    if (FIXNUMP(arg1)) {
	f1 = IFIX(arg1);
	switch(fn_code) {
	case MABS:
	    if (f1 == IMOST_NEGATIVE_FIXNUM)
		result = MAKE_INTEGER(-IMOST_NEGATIVE_FIXNUM);
	    else
		result = FIX(f1 < 0 ? -f1 : f1);
	    break;
	case NEGATE:
	    if (f1 == IMOST_NEGATIVE_FIXNUM)
		result = MAKE_INTEGER(-IMOST_NEGATIVE_FIXNUM);
	    else
		result = FIX(-f1);
	    break;
	case MINUSP:
	    result = f1 < 0 ? T : NIL;
	    break;
	case PLUSP:
	    result = f1 > 0 ? T : NIL;
	    break;
	case ZEROP:
	    result = f1 == 0 ? T : NIL;
	    break;
	case ODDP:
	    result = f1 & 1 ? T : NIL;
	    break;
	case EVENP:
	    result = f1 & 1 ? NIL : T;
	    break;
	case LOGNOT:
	    f1 = ~f1;
	    result = MAKE_INTEGER(f1);
	    break;
	case LOGCOUNT:
	    if (f1 < 0) f1 = ~f1;
	    for (i = 0, count = 0; i < SI_BITS_PER_FIXNUM; i++)
		if (f1 & ((SI_Long)1L << i))
		    count++;
	    result = FIX(count);
	    break;
	default:
	    error(3, "do_math1: invalid operation on ~s - ~d", arg1, 
		  FIX(fn_code));
	    break;		/* ERROR! */
	}
    } else
	switch (PNODE_TYPE(arg1)) {
	case DOUBLE_TYPE:
	    d1 = object_to_cdouble(arg1);
	    switch(fn_code) {
	    case MABS:
		result = cdouble_to_double((d1 < 0) ? -d1 : d1);
		break;
	    case NEGATE:
		result = cdouble_to_double(-d1);
		break;
	    case MINUSP:
		result = d1 < 0 ? T : NIL;
		break;
	    case PLUSP:
		result = d1 > 0 ? T : NIL;
		break;
	    case ZEROP:
		result = d1 == 0 ? T : NIL;
		break;
	    default:
		error(3, "do_math1: invalid operation on ~s - ~d", arg1, 
		      FIX(fn_code));
		break;		/* ERROR! */
	    }
	    break;
	case OBIGNUM_TYPE:
	    b1 = BIGNUM_VALUE(arg1);
	    switch(fn_code) {
	    case MABS:
		if (b1 >= 0) {
		    result = arg1;
		    break;
		}
		/* Fall through */
	    case NEGATE:
		b1 = -b1;
		if (b1 < 0)
		    error(2, "abs: integer overflow - ~d", arg1);
		result = MAKE_INTEGER(b1);
		break;
	    case MINUSP:
		result = b1 < 0 ? T : NIL;
		break;
	    case PLUSP:
		result = b1 > 0 ? T : NIL;
		break;
	    case ZEROP:
		result = b1 == 0 ? T : NIL;
		break;
	    case ODDP:
		result = b1 & 1 ? T : NIL;
		break;
	    case EVENP:
		result = b1 & 1 ? NIL : T;
		break;
	    case LOGNOT:
		result = T_MAKE_INTEGER(~b1);
		break;
	    case LOGCOUNT:
		if (b1 < 0) b1 = ~b1;
		for (i = 0, count = 0; i < LONGBITS; i++)
		    if (b1 & ((SI_Long)1L << i))
			count++;
		result = MAKE_INTEGER((SI_Long) count);
		break;
	    default:
		error(3, "do_math1: invalid operation on ~s - ~d", arg1, 
		      FIX(fn_code));
		break;		/* ERROR! */
	    }
	    break;
	case XBIGNUM_TYPE:
	    switch(fn_code) {
	    case MABS:
		if (bignum_test(arg1) != bignum_comparison_less) {
		    result = arg1;
		    break;
		}
		/* Fall through */
	    case NEGATE:
		result = xbignum_normalize(perform_safely_1(bignum_negate, arg1));
		break;
	    case MINUSP:
		result = (bignum_test(arg1) == bignum_comparison_less
			   ? T : NIL);
		break;
	    case PLUSP:
		result = (bignum_test(arg1) == bignum_comparison_greater
			   ? T : NIL);
		break;
	    case ZEROP:
		result = NIL;	/* assume normalized */
		break;
	    case ODDP:
		result = bignum_oddp(arg1) ? T : NIL;
		break;
	    case EVENP:
		result = bignum_oddp(arg1) ? NIL : T;
		break;
	    case LOGNOT:
		result = minus(FIX(-1), arg1);
		break;
	    case LOGCOUNT:
		result = perform_safely_1(bignum_logcount,arg1);
		break;
	    default:
		error(3, "do_math1: invalid operation on ~s - ~d", arg1, 
		      FIX(fn_code));
		break;		/* ERROR! */
	    }
	    break;
	case RATIO_TYPE:
	    num = RATIO_NUMERATOR(arg1);
	    den = RATIO_DENOMINATOR(arg1);
	    switch(fn_code) {
	    case MABS:
		if (plusp(num)) {
		    result = arg1;
		    break;
		}
	    case NEGATE:
		result = make_ratio(negate(num), den);
		break;
	    case MINUSP:
		result = minusp(num);
		break;
	    case PLUSP:
		result = plusp(num);
		break;
	    case ZEROP:
		result = zerop(num);
		break;
	    default:
		error(3, "do_math1: invalid operation on ~s - ~d", arg1, 
		      FIX(fn_code));
		break;		/* ERROR! */
	    }
	    break;
	case LONG64_TYPE:
	    i1 = ILONG64(arg1);
	    switch(fn_code) {
	    case MABS:
		result = INT64_TO_INTEGER ((i1 < (SI_int64) 0L) ? -i1 : i1);
		break;
	    case NEGATE:
		result = INT64_TO_INTEGER (-i1);
		break;
	    case MINUSP:
		result = i1 < (SI_int64) 0L ? T : NIL;
		break;
	    case PLUSP:
		result = i1 > (SI_int64) 0L ? T : NIL;
		break;
	    case ZEROP:
		result = i1 == (SI_int64) 0L ? T : NIL;
		break;
	    default:
		error(3, "do_math1: invalid operation on ~s - ~d", arg1, 
		      FIX(fn_code));
		break;		/* ERROR! */
	    }
	    break;
	default:
	    error(3, "do_math1: invalid operation on ~s - ~d", arg1, 
		  FIX(fn_code));
	    break;
	}
    RESTORE_STACK();
    return VALUES_1(result);
}

Object SI_do_math2 (arg1, arg2, fn_code)
    Object arg1, arg2;
    enum binary_op fn_code;
{
    Declare_local_temp;
    SI_Long n1, n2, n;
    double d1, d2;
    SI_int64 i1, i2, i64;
    Object result = NIL;
    Object num1, num2, den1, den2, num, den;
    int arg1_type;
    int arg2_type;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(arg1, arg2, result);

    arg1_type = IMMEDIATE_P(arg1) ? (int) FIXNUM_TYPE : (int) PNODE_TYPE(arg1);
    arg2_type = IMMEDIATE_P(arg2) ? (int) FIXNUM_TYPE : (int) PNODE_TYPE(arg2);
    switch(MAX(arg1_type, arg2_type)) {
    case FIXNUM_TYPE:
	/* FIXNUM + FIXNUM */
    case OBIGNUM_TYPE:
	if (fn_code == MDIVIDE) {
	    result = xmake_canonical_rational(arg1, arg2);
	    break;
	}
	n1 = INTEGER_TO_LONG(arg1);
	n2 = INTEGER_TO_LONG(arg2);
	switch(fn_code) {
	case ASH:
	    if (n2 < 0L)
		n = n1 >> -n2;
	    else if (IFIX(integer_length(arg1)) + n2 < SI_BITS_PER_FIXNUM)
		n = n1 << n2;
	    else
#ifdef NEW_BIGNUMS
		goto INTEGER_OVERFLOW;
#else
	        warn(3, "ash: integer overflow - (ash ~S ~S)", arg1, arg2);
#endif
	    break;
	case MMINUS:
	    n2 = -n2;
	    /* Fall through */
	case MADD:
	    n = n1 + n2;
	    if (n1 > 0 && n2 > 0 && n < 0 ||
		n1 < 0 && n2 < 0 && n > 0)
#ifdef NEW_BIGNUMS
		goto INTEGER_OVERFLOW;
#else
	        warn(3, "+: integer overflow - (+ ~S ~S)", arg1, arg2);
#endif
	    break;
	case MTIMES:
#ifdef NEW_BIGNUMS
	    result = multiply_carefully(n1, n2);
	    if (result == NIL)
		goto INTEGER_OVERFLOW;
	    else
		goto DONEINT;
#else
	    n = n1 * n2;
	    /* Not tight, but better than nothing */
	    if (((n1 >= 0) == (n2 >= 0)) ? (n < 0) : (n > 0))
		warn(3, "*: integer overflow - (* ~d ~d)", arg1, arg2);
	    break;
#endif
	case LESS:
	    result = n1 < n2 ? T : NIL;
	    goto DONEINT;
	case MEQUAL:
	    result = n1 == n2 ? T : NIL;
	    goto DONEINT;
	case MMAX:
	    result = n1 >= n2 ? arg1 : arg2;
	    goto DONEINT;
	case MMIN:
	    result = n1 <= n2 ? arg1 : arg2;
	    goto DONEINT;
	case LOGAND:
	    n = n1 & n2;
	    break;
	case LOGIOR:
	    n = n1 | n2;
	    break;
	case LOGXOR:
	    n = n1 ^ n2;
	    break;
	case LOGEQV:
	    n = ~(n1 ^ n2);
	    break;
	default:
	    error(1, "SI_do_math2: invalid integer function");
	    break;		/* ERROR! */
	}
	result = MAKE_INTEGER(n);
    DONEINT:
	break;
    case XBIGNUM_TYPE:
    INTEGER_OVERFLOW:
	switch(fn_code) {
	case MADD:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
	    result = xbignum_normalize(perform_safely(bignum_add, arg1, arg2));
	    break;
	case MMINUS:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
	    result = xbignum_normalize(perform_safely(bignum_subtract, arg1, arg2));
	    break;
	case MTIMES:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
	    result = xbignum_normalize(perform_safely(bignum_multiply, arg1, arg2));
	    break;
	case MDIVIDE:
	    result = xmake_canonical_rational(arg1, arg2);
	    break;
	case MEQUAL:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
	    if (bignum_compare(arg1, arg2) == bignum_comparison_equal)
		result = T;
	    else
		result = NIL;
	    break;
	case LESS:
	    if (!XBIGNUMP(arg1))
		result = (bignum_test(arg2) == bignum_comparison_greater
			  ? T : NIL);
	    else if (!XBIGNUMP(arg2))
		result = (bignum_test(arg1) == bignum_comparison_less
			  ? T : NIL);
	    else
		result = (bignum_compare(arg1, arg2) == bignum_comparison_less
			  ? T : NIL);
	    break;
	case MMAX:
	    if (!XBIGNUMP(arg1))
		result = (bignum_test(arg2) == bignum_comparison_less
			  ? arg1 : arg2);
	    else if (!XBIGNUMP(arg2))
		result = (bignum_test(arg1) == bignum_comparison_greater
			  ? arg1 : arg2);
	    else
		result = (bignum_compare(arg1, arg2) == bignum_comparison_greater
		      ? arg1 : arg2);
	    break;
	case MMIN:
	    if (!XBIGNUMP(arg1))
		result = (bignum_test(arg2) == bignum_comparison_less
			  ? arg2 : arg1);
	    else if (!XBIGNUMP(arg2))
		result = (bignum_test(arg1) == bignum_comparison_greater
			  ? arg2 : arg1);
	    else
	    result = (bignum_compare(arg1, arg2) != bignum_comparison_greater
		      ? arg1 : arg2);
	    break;
	case ASH:
	    if (LONG64P(arg1))
		arg1 = int64_to_bignum(integer_to_int64(arg1));
	    else if (!XBIGNUMP(arg1))
		arg1 = clong_to_bignum(IINTEGER(arg1));
	    if (!XBIGNUMP(arg2))
		result = xbignum_normalize(perform_safely(bignum_ash, arg1, arg2));
	    else 
		error(1, "too long shift for ash ");
	    break;
	case LOGAND:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
            result = xbignum_normalize(perform_safely(bignum_logand, arg1,arg2));
	    break;
	case LOGIOR:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
	    result = xbignum_normalize(perform_safely(bignum_logior, arg1,arg2));
	    break;
	case LOGXOR:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
	    result = logand(logior(arg1,arg2),lognot(logand(arg1,arg2)));
	    break;
	case LOGEQV:
	    if (LONG64P(arg1) || LONG64P(arg2)) {
		if (!XBIGNUMP(arg1)) arg1 = int64_to_bignum(integer_to_int64(arg1));
		if (!XBIGNUMP(arg2)) arg2 = int64_to_bignum(integer_to_int64(arg2));
	    } else {
		if (!XBIGNUMP(arg1)) arg1 = clong_to_bignum(IINTEGER(arg1));
		if (!XBIGNUMP(arg2)) arg2 = clong_to_bignum(IINTEGER(arg2));
	    }
	    result = lognot(logxor(arg1,arg2));
	    break;
	default:
	    (void)error(1, "SI_do_math2: invalid or unimplemented integer function");
	    /*NOTREACHED*/
	    break;
	}
	break;
    case DOUBLE_TYPE:
	d1 = object_to_cdouble(arg1);
	d2 = object_to_cdouble(arg2);
	switch(fn_code) {
	case MADD:
	    result = cdouble_to_double(d1 + d2);
	    break;
	case MMINUS:
	    result = cdouble_to_double(d1 - d2);
	    break;
	case MTIMES:
	    result = cdouble_to_double(d1 * d2);
	    break;
	case MDIVIDE:
	    result = cdouble_to_double(d1 / d2);
	    break;
	case LESS:
	    result = d1 < d2 ? T : NIL;
	    break;
	case MEQUAL:
	    result = d1 == d2 ? T : NIL;
	    break;
	case MMAX:
	    result = d1 > d2 ? arg1 : arg2;
	    break;
	case MMIN:
	    result = d1 <= d2 ? arg1 : arg2;
	    break;
	default:
	    error(1, "SI_do_math2: invalid double function");
	    break;		/* ERROR! */
	}
	break;
    case RATIO_TYPE:
	PROTECTI_6(num1, num2, den1, den2, num, den);
	if (RATIOP(arg1)) {
	    num1 = RATIO_NUMERATOR(arg1);
	    den1 = RATIO_DENOMINATOR(arg1);
	}
	else {
	    num1 = arg1;
	    den1 = FIX(1);
	}
	if (RATIOP(arg2)) {
	    num2 = RATIO_NUMERATOR(arg2);
	    den2 = RATIO_DENOMINATOR(arg2);
	}
	else {
	    num2 = arg2;
	    den2 = FIX(1);
	}
	switch(fn_code) {
	case MADD:
	    num1 = ltimes(num1, den2);
	    num2 = ltimes(num2, den1);
	    num = add(num1, num2);
	    den = ltimes(den1, den2);
	    result = xmake_canonical_rational(num, den);
	    break;
	case MMINUS:
	    num1 = ltimes(num1, den2);
	    num2 = ltimes(num2, den1);
	    num = minus(num1, num2);
	    den = ltimes(den1, den2);
	    result = xmake_canonical_rational(num, den);
	    break;
	case MTIMES:
	    num = ltimes(num1, num2);
	    den = ltimes(den1, den2);
	    result = xmake_canonical_rational(num, den);
	    break;
	case MDIVIDE:
	    num = ltimes(num1, den2);
	    den = ltimes(den1, num2);
	    result = xmake_canonical_rational(num, den);
	    break;
	case LESS:
	    num1 = ltimes(num1, den2);
	    num2 = ltimes(num2, den1);
	    result = num_lt(num1, num2);
	    break;
	case MEQUAL:
	    // Rely on the fact that rationals are normalized 
	    result = (TRUEP(num_eq(num1, num2)) &&
		      TRUEP(num_eq(den1, den2))) ? T : NIL;
	    break;
	case MMAX:
	    num1 = ltimes(num1, den2);
	    num2 = ltimes(num2, den1);
	    result = num_gt(num1, num2) ? arg1 : arg2;
	    break;
	case MMIN:
	    num1 = ltimes(num1, den2);
	    num2 = ltimes(num2, den1);
	    result = num_le(num1, num2) ? arg1 : arg2;
	    break;
	default:
	    error(1, "SI_do_math2: invalid rational function");
	    break;		//Error
	}
	break;
    case LONG64_TYPE:
	if (!LONG64P(arg1)) arg1 = FIXNUM_TO_INT64(arg1);
	if (!LONG64P(arg2)) arg2 = FIXNUM_TO_INT64(arg2);
	i1 = ILONG64(arg1);
	i2 = ILONG64(arg2);
	switch(fn_code) {
	case MADD:
	    i64 = i1 + i2;
	    result = cint64_to_int64(i64);
	    break;
	case MMINUS:
	    i64 = i1 - i2;
	    result = cint64_to_int64(i64);
	    break;
	case MTIMES:
	    i64 = i1 * i2;
	    result = cint64_to_int64(i64);
	    break;
	case MDIVIDE:
	    if (i2 == 0L) {
		error(3, "/: division by zero - (/ ~S ~S)", arg1, arg2);
		i64 = 0L;
	    } else
	        i64 = i1 / i2;
	    result = cint64_to_int64(i64);
	    break;
	case LESS:
	    result = (i1 < i2) ? T : NIL;
	    break;
	case MEQUAL:
	    result = (i1 == i2) ? T : NIL;
	    break;
	case MMAX:
	    result = (i1 > i2) ? arg1 : arg2;
	    break;
	case MMIN:
	    result = (i1 <= i2) ? arg1 : arg2;
	    break;
	case ASH:
	    if (i2 < 0L)
		i64 = i1 >> (-i2);
	    else
	        i64 = i1 << i2;
	    result = cint64_to_int64(i64);
	    break;
	case LOGAND:
	    i64 = i1 & i2;
	    result = cint64_to_int64(i64);
	    break;
	case LOGIOR:
	    i64 = i1 | i2;
	    result = cint64_to_int64(i64);
	    break;
	case LOGXOR:
	    i64 = i1 ^ i2;
	    result = cint64_to_int64(i64);
	    break;
	case LOGEQV:
	    i64 = ~(i1 ^ i2);
	    result = cint64_to_int64(i64);
	    break;
	default:
	    error(1, "SI_do_math2: invalid int64 function");
	    break;		/* ERROR! */
	}
	break;
    default:
	error(3, "SI_do_math2: invalid argument type - ~S ~S", arg1, arg2);
	break;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}

/*
 * Integer multiplication, with overflow check.
 * Copied from file mul.c of MIT Scheme microcode.
 * This can be made more efficient by descending into assembly language.
 */

#define DATUM_LENGTH    SI_BITS_PER_FIXNUM
#define SHARP_F		NIL
#define SCHEME_OBJECT   Object
#define LONG_TO_FIXNUM_P(x) ((x) <= IMOST_POSITIVE_FIXNUM)
#define LONG_TO_UNSIGNED_FIXNUM(x) FIX(x)
#define FIXNUM_SIGN_BIT ((SI_Long)1 << (SI_BITS_PER_FIXNUM - 1))
#define fast register
#define Boolean int

#define HALF_WORD_SIZE	((SI_BITS_PER_FIXNUM + SI_FIXNUM_SHIFT) / 2)
#define HALF_WORD_MASK	((SI_Long)1L << HALF_WORD_SIZE) - 1L
#define MAX_MIDDLE	((SI_Long)1L << ((DATUM_LENGTH - 1) - HALF_WORD_SIZE))

#ifdef   ABS
#undef   ABS
#define	 ABS(x)		(((x) < 0) ? -(x) : (x))
#endif

#ifdef A
#undef A
#endif
#ifdef B
#undef B
#endif
#ifdef C
#undef C
#endif

static SCHEME_OBJECT multiply_carefully(Arg1, Arg2)
    SI_Long Arg1, Arg2;
{
#if defined(Platform_Windows) && defined(Platform_32bit)
	__int64 full_result;
	unsigned __int64 unsigned_full_result;

	full_result = ((__int64)Arg1) * ((__int64)Arg2);
	unsigned_full_result = ABS(full_result);
	if (unsigned_full_result < IMOST_POSITIVE_FIXNUM) {
		return FIX((SI_Long)full_result);
	} else {
		return Nil;
	}
#else
  SI_Long A, B, C;
  fast SI_Ulong Hi_A, Hi_B, Lo_A, Lo_B, Lo_C, Middle_C;
  Boolean Sign;

  A = ( (Arg1));
  B = ( (Arg2));
  Sign = ((A < 0) == (B < 0));
  A = ABS(A);
  B = ABS(B);
  Hi_A = ((A >> HALF_WORD_SIZE) & HALF_WORD_MASK);
  Hi_B = ((B >> HALF_WORD_SIZE) & HALF_WORD_MASK);
  if ((Hi_A > 0) && (Hi_B > 0))
    return (SHARP_F);
  Lo_A = (A & HALF_WORD_MASK);
  Lo_B = (B & HALF_WORD_MASK);
  Lo_C = (Lo_A * Lo_B);
  if (Lo_C >= FIXNUM_SIGN_BIT)
    return (SHARP_F);
  Middle_C = (Lo_A * Hi_B) + (Hi_A * Lo_B);
  if (Middle_C >= MAX_MIDDLE)
    return (SHARP_F);
  C = Lo_C + (Middle_C << HALF_WORD_SIZE);
  if (LONG_TO_FIXNUM_P(C))
  {
    if (Sign || (C == 0))
      return (LONG_TO_UNSIGNED_FIXNUM(C));
    else
      return (LONG_TO_UNSIGNED_FIXNUM(-C));
  }
  return (SHARP_F);
#endif
}


/* Danger - this can return noncanonical ratios.  Use with care. */

Object make_ratio(n, d)
    Object n, d;
{
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(n, d);
    result = SI_ALLOC(SI_Ratio, RATIO_TYPE, SI_NUMBER_TAG, SI_NORMAL);
    RATIO_NUMERATOR(result) = n;
    RATIO_DENOMINATOR(result) = d;
    RESTORE_STACK();
    return result;
}
