/*
 * specific.h - type-specific functions (C macros) for Common Lisp
 *              runtime support library
 * Also, macros for the foreign language interface.
 *
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

/*
 * Fixnums
 */

#define FIXNUM_ADD(a,b)		((Object)((fixnum_arithmetic_type)(a) - (fixnum_arithmetic_type)1 + (fixnum_arithmetic_type)(b)))
#define FIXNUM_ADD1(a)		((Object)((fixnum_arithmetic_type)(a) + (fixnum_arithmetic_type)4))
#define FIXNUM_MINUS(a,b)	((Object)((fixnum_arithmetic_type)(a) - ((fixnum_arithmetic_type)(b) - (fixnum_arithmetic_type)1)))
#define FIXNUM_NEGATE(a)	((Object)((fixnum_arithmetic_type)2 - (fixnum_arithmetic_type)(a)))
#define FIXNUM_SUB1(a)		((Object)(((fixnum_arithmetic_type)(a) - (fixnum_arithmetic_type)4)))

#define FIXNUM_TIMES(a,b)	((Object)(IFIX(a) * ((fixnum_arithmetic_type)(b) - (fixnum_arithmetic_type)1) + (fixnum_arithmetic_type)1))

/* The division operators are all applcable when
   both arguments are positive fixnums due to the 
   randomness in C's / and % operators when applied to negative numbers.
   (See ANSI C or Harbison & Steele)`
 */

#define FIXNUM_TRUNCATE(a,b)	FIX(((fixnum_arithmetic_type)(a) - 1L) / ((fixnum_arithmetic_type)(b) - 1L))
#define FIXNUM_DIVIDE(a,b)	FIXNUM_TRUNCATE(a,b)
#define FIXNUM_REM(a,b)     	((Object) \
				 ((((fixnum_arithmetic_type)(a) - 1L) % ((fixnum_arithmetic_type)(b) - 1L)) | 1L))
#define FIXNUM_MOD(a,b)         ((Object) \
                                 ((((fixnum_arithmetic_type)(a) - 1L) % ((fixnum_arithmetic_type)(b) - 1L)) | 1L))

#define FIXNUM_ABS(a)		(FIXNUM_MINUSP(a) ? \
				 FIXNUM_NEGATE(a) : \
				 (a))
#define FIXNUM_ASH(a,b)		(FIXNUM_MINUSP(b) ? \
				 (Object)((((fixnum_arithmetic_type)(a) >> -IFIX(b)) & ~3L) \
					  + 1L) : \
				 (Object)((((fixnum_arithmetic_type)(a) - (fixnum_arithmetic_type)1) << IFIX(b) \
					   + (fixnum_arithmetic_type)1)))
#define FIXNUM_RSH(a,b)		(Object)((((fixnum_arithmetic_type)(a) >> IFIX(b)) & ~3L) \
					  + 1L)
#define FIXNUM_LSH(a,b)		(Object)(((((fixnum_arithmetic_type)(a) - (fixnum_arithmetic_type)1) << IFIX(b)) \
					   + (fixnum_arithmetic_type)1))
#define FIXNUM_LOGAND(a,b)	((Object)((fixnum_arithmetic_type)(a) & (fixnum_arithmetic_type)(b)))
#define FIXNUM_LOGANDC2(a,b)	((Object)((fixnum_arithmetic_type)(a) & (~(fixnum_arithmetic_type)(b) ^ 3L)))
#define FIXNUM_LOGIOR(a,b)	((Object)((fixnum_arithmetic_type)(a) | (fixnum_arithmetic_type)(b)))
#define FIXNUM_LOGXOR(a,b)	((Object)(((fixnum_arithmetic_type)(a) ^ (fixnum_arithmetic_type)(b)) + 1L))
#define FIXNUM_LOGEQV(a,b)	((Object)(~((fixnum_arithmetic_type)(a) ^ (fixnum_arithmetic_type)(b)) - 2L))
#define FIXNUM_LOGNOT(a)	((Object)(~(fixnum_arithmetic_type)(a) ^ 3L))
#define FIXNUM_LOGTEST(a,b)	(((fixnum_arithmetic_type)(a) & (fixnum_arithmetic_type)(b)) != 1L)
#define FIXNUM_LOGBITP(a,b)     ((fixnum_arithmetic_type)(a) & (4L << IFIX(b)))
#define FIXNUM_BYTE_MASK(b)     ((4L << IFIX(BYTE_SIZE(b))) - 4L)
#define FIXNUM_LDB(bs,n)	((Object) \
				 ((((fixnum_arithmetic_type)(n) >> IFIX(BYTE_POSITION(bs)))  \
				   & FIXNUM_BYTE_MASK(bs))   \
				  | 1L))
#define FIXNUM_DPB(new,bs,n) \
    ((Object) \
     (((fixnum_arithmetic_type)(n) & ~(FIXNUM_BYTE_MASK(bs) << IFIX(BYTE_POSITION(bs)))) \
      | (((fixnum_arithmetic_type)(new) & FIXNUM_BYTE_MASK(bs)) << IFIX(BYTE_POSITION(bs))) \
      | 1L))
				
#define FIXNUM_LT(a,b)		((fixnum_arithmetic_type)(a) < (fixnum_arithmetic_type)(b))
#define FIXNUM_GT(a,b)		((fixnum_arithmetic_type)(a) > (fixnum_arithmetic_type)(b))
#define FIXNUM_EQ(a,b)		((fixnum_arithmetic_type)(a) == (fixnum_arithmetic_type)(b))
#define FIXNUM_NE(a,b)		((fixnum_arithmetic_type)(a) != (fixnum_arithmetic_type)(b))
#define FIXNUM_GE(a,b)		((fixnum_arithmetic_type)(a) >= (fixnum_arithmetic_type)(b))
#define FIXNUM_LE(a,b)		((fixnum_arithmetic_type)(a) <= (fixnum_arithmetic_type)(b))
#define FIXNUM_MAX(a,b)		((Object)(MAX((fixnum_arithmetic_type)(a), (fixnum_arithmetic_type)(b))))
#define FIXNUM_MIN(a,b)		((Object)(MIN((fixnum_arithmetic_type)(a), (fixnum_arithmetic_type)(b))))
#define FIXNUM_ZEROP(a)		((a) == ZERO)
#define FIXNUM_PLUSP(a)		((fixnum_arithmetic_type)(a) > 1L)
#define FIXNUM_MINUSP(a)	((fixnum_arithmetic_type)(a) < 1L)
#define FIXNUM_ODDP(a)		((fixnum_arithmetic_type)(a) & 4L)
#define FIXNUM_EVENP(a)		((fixnum_arithmetic_type)(a) & 4L ? NIL : T)

/* Fix later */
#define FIXNUM_FLOOR(a,b)	(lfloor(a, b))
#define FIXNUM_CEILING(a,b)	(ceiling(a, b))
#define FIXNUM_ROUND(a,b)	(l_round(a, b))

/*
 * Unboxed double float operations
 * These need  #include <math.h>
 */

#define DOUBLE_ADD(a,b)		((a)+(b))
#define DOUBLE_ADD1(a)		((a)+1.0)
#define DOUBLE_MINUS(a,b)	((a)-(b))
#define DOUBLE_NEGATE(a)	(0.0-(a))
#define DOUBLE_SUB1(a)		((a)-1.0)

#define DOUBLE_TIMES(a,b)	((a)*(b))
#define DOUBLE_DIVIDE(a,b)	((a)/(b))

/* Flush the after the translator gets fixed */
#define DOUBLE_LT(a,b)		((a)<(b))
#define DOUBLE_GT(a,b)		((a)>(b))
#define DOUBLE_EQ(a,b)		((a)==(b))
#define DOUBLE_NE(a,b)		((a)!=(b))
#define DOUBLE_GE(a,b)		((a)>=(b))
#define DOUBLE_LE(a,b)		((a)<=(b))
#define DOUBLE_ZEROP(a)		((a)==0.0)
#define DOUBLE_PLUSP(a)		((a)>0.0)
#define DOUBLE_MINUSP(a)	((a)<0.0)
#define DOUBLE_MAX(a,b)		(MAX(a,b))
#define DOUBLE_MIN(a,b)		(MIN(a,b))

#define DOUBLE_ABS(a)		(fabs(a))
#define DOUBLE_ATAN1(a)		(atan(a))
#define DOUBLE_ATAN(a,b)	(atan2(a,b))
#define DOUBLE_COS(a)		(cos(a))
#define DOUBLE_EXP(a)		(exp(a))
#define DOUBLE_EXPT(a,b)	(pow(a,b))
#define DOUBLE_LOG1(a)		(log(a))
#define DOUBLE_LOG(a,b)		(log(a)/log(b))
#define DOUBLE_SIN(a)		(sin(a))
#define DOUBLE_SQRT(a)		(sqrt(a))
#define DOUBLE_TAN(a)		(tan(a))

#define DOUBLE_CEILING1(a)	(FIX((fixnum_arithmetic_type)ceil(a)))
#define DOUBLE_CEILING(a,b)	(DOUBLE_CEILING1(a/b))
#define DOUBLE_FLOOR1(a)	(FIX((fixnum_arithmetic_type)floor(a)))
#define DOUBLE_FLOOR(a,b)	(DOUBLE_FLOOR1(a/b))
#define DOUBLE_FROUND1(a)	(rint(a))
#define DOUBLE_FROUND(a,b)	(DOUBLE_FROUND1(a/b))
/* Can't replace FIX(rint(a)) with nint(a) here because nint returns an int,
   not a long */
#define DOUBLE_ROUND1(a)	(FIX((fixnum_arithmetic_type)rint(a)))
#define DOUBLE_ROUND(a,b)	(DOUBLE_ROUND1(a/b))
#define DOUBLE_TRUNCATE1(a)	(FIX((fixnum_arithmetic_type)aint(a)))
#define DOUBLE_TRUNCATE(a,b)	(DOUBLE_TRUNCATE1(a/b))

/*
 * Boxed double float operations
 */

#define BINARY_DOUBLE_FLOAT_OP(op,a,b) \
    (DOUBLE_TO_DOUBLE_FLOAT(op(DOUBLE_FLOAT_TO_DOUBLE(a), \
			       DOUBLE_FLOAT_TO_DOUBLE1(b))))
#define UNARY_DOUBLE_FLOAT_OP(op,a) \
    (DOUBLE_TO_DOUBLE_FLOAT(op(DOUBLE_FLOAT_TO_DOUBLE(a))))
#define BINARY_DOUBLE_FLOAT_PRED(op,a,b) \
    (op(DOUBLE_FLOAT_TO_DOUBLE(a), DOUBLE_FLOAT_TO_DOUBLE(b)))
#define UNARY_DOUBLE_FLOAT_PRED(op,a) \
    (op(DOUBLE_FLOAT_TO_DOUBLE(a)))
#define UNARY_DOUBLE_FLOAT_INT(op,a) \
    (op(DOUBLE_FLOAT_TO_DOUBLE(a)))

#define DOUBLE_FLOAT_ADD(a,b)    (BINARY_DOUBLE_FLOAT_OP(DOUBLE_ADD,a,b))
#define DOUBLE_FLOAT_ADD1(a)     (UNARY_DOUBLE_FLOAT_OP(DOUBLE_ADD1,a))
#define DOUBLE_FLOAT_MINUS(a,b)	 (BINARY_DOUBLE_FLOAT_OP(DOUBLE_MINUS,a,b))
#define DOUBLE_FLOAT_NEGATE(a)	 (UNARY_DOUBLE_FLOAT_OP(DOUBLE_NEGATE,a))
#define DOUBLE_FLOAT_SUB1(a)     (UNARY_DOUBLE_FLOAT_OP(DOUBLE_SUB1,a))

#define DOUBLE_FLOAT_TIMES(a,b)  (BINARY_DOUBLE_FLOAT_OP(DOUBLE_TIMES,a,b))
#define DOUBLE_FLOAT_DIVIDE(a,b) (BINARY_DOUBLE_FLOAT_OP(DOUBLE_DIVIDE,a,b))

#define DOUBLE_FLOAT_LT(a,b)	 (BINARY_DOUBLE_FLOAT_PRED(DOUBLE_LT,a,b))
#define DOUBLE_FLOAT_GT(a,b)	 (BINARY_DOUBLE_FLOAT_PRED(DOUBLE_GT,a,b))
#define DOUBLE_FLOAT_EQ(a,b)	 (BINARY_DOUBLE_FLOAT_PRED(DOUBLE_EQ,a,b))
#define DOUBLE_FLOAT_NE(a,b)	 (BINARY_DOUBLE_FLOAT_PRED(DOUBLE_NE,a,b))
#define DOUBLE_FLOAT_GE(a,b)	 (BINARY_DOUBLE_FLOAT_PRED(DOUBLE_GE,a,b))
#define DOUBLE_FLOAT_LE(a,b)	 (BINARY_DOUBLE_FLOAT_PRED(DOUBLE_LE,a,b))
#define DOUBLE_FLOAT_ZEROP(a)    (UNARY_DOUBLE_FLOAT_PRED(DOUBLE_ZEROP,a))
#define DOUBLE_FLOAT_PLUSP(a)    (UNARY_DOUBLE_FLOAT_PRED(DOUBLE_PLUSP,a))
#define DOUBLE_FLOAT_MINUSP(a)   (UNARY_DOUBLE_FLOAT_PRED(DOUBLE_MINUSP,a))
#define DOUBLE_FLOAT_MAX(a,b)	 (IDOUBLE(a) < IDOUBLE1(b) ? (b) : (a))
#define DOUBLE_FLOAT_MIN(a,b)	 (IDOUBLE(a) < IDOUBLE1(b) ? (a) : (b))

#define DOUBLE_FLOAT_ABS(a)      (UNARY_DOUBLE_FLOAT_OP(DOUBLE_ABS,a))
#define DOUBLE_FLOAT_ATAN1(a)    (UNARY_DOUBLE_FLOAT_OP(DOUBLE_ATAN1,a))
#define DOUBLE_FLOAT_ATAN(a,b)	 (BINARY_DOUBLE_FLOAT_OP(DOUBLE_ATAN,a,b))
#define DOUBLE_FLOAT_COS(a)	 (UNARY_DOUBLE_FLOAT_OP(DOUBLE_COS,a))
#define DOUBLE_FLOAT_EXP(a)	 (UNARY_DOUBLE_FLOAT_OP(DOUBLE_EXP,a))
#define DOUBLE_FLOAT_EXPT(a,b)   (BINARY_DOUBLE_FLOAT_OP(DOUBLE_EXPT,a,b))
#define DOUBLE_FLOAT_LOG1(a)	 (UNARY_DOUBLE_FLOAT_OP(DOUBLE_LOG1,a))
#define DOUBLE_FLOAT_LOG(a,b)	 (BINARY_DOUBLE_FLOAT_OP(DOUBLE_LOG,a,b))
#define DOUBLE_FLOAT_SIN(a)	 (UNARY_DOUBLE_FLOAT_OP(DOUBLE_SIN,a))
#define DOUBLE_FLOAT_SQRT(a)	 (UNARY_DOUBLE_FLOAT_OP(DOUBLE_SQRT,a))
#define DOUBLE_FLOAT_TAN(a)	 (UNARY_DOUBLE_FLOAT_OP(DOUBLE_TAN,a))

#define DOUBLE_FLOAT_CEILING1(a)   (UNARY_DOUBLE_FLOAT_INT(DOUBLE_CEILING1,a))
#define DOUBLE_FLOAT_CEILING(a,b) (BINARY_DOUBLE_FLOAT_INT(DOUBLE_CEILING,a,b))
#define DOUBLE_FLOAT_FLOOR1(a)	   (UNARY_DOUBLE_FLOAT_INT(DOUBLE_FLOOR1,a))
#define DOUBLE_FLOAT_FLOOR(a,b)	  (BINARY_DOUBLE_FLOAT_INT(DOUBLE_FLOOR,a,b))
#define DOUBLE_FLOAT_FROUND1(a)	   (UNARY_DOUBLE_FLOAT_OP(DOUBLE_FROUND1,a))
#define DOUBLE_FLOAT_FROUND(a,b)  (BINARY_DOUBLE_FLOAT_OP(DOUBLE_FROUND,a,b))
#define DOUBLE_FLOAT_ROUND1(a)	   (UNARY_DOUBLE_FLOAT_INT(DOUBLE_ROUND1,a))
#define DOUBLE_FLOAT_ROUND(a,b)	  (BINARY_DOUBLE_FLOAT_INT(DOUBLE_ROUND,a,b))
#define DOUBLE_FLOAT_TRUNCATE1(a)  (UNARY_DOUBLE_FLOAT_INT(DOUBLE_TRUNCATE1,a))
#define DOUBLE_FLOAT_TRUNCATE(a,b) \
    (BINARY_DOUBLE_FLOAT_INT(DOUBLE_TRUNCATE,a,b))

/*
 * Array references
 *
 * Macros for open-coding aref's of the form
 *   (aref (the (simple-array <type> (* ...)) <array>) <index> ...)
 */

#ifndef SI_DEBUG_INLINE
#define SI_DEBUG_INLINE 0
#endif

/*  
 *  Type encoding grammar for type-specific inline 
 *  array accessors
 *
 *  NAME ::=    <etype><dtype><aggreg><rankmark><accessor><arity>
 *  
 *  ( array element type )
 * 
 *  <etype> ::=  <T-etype> | _<etype-prefix>
 *  <T-etype>  ::= 
 * 
 *  <etype-prefix>
 *          ::=  DFLOAT 
 *          |    FLOAT
 *          |    BYTE_8
 *          |    BYTE_16
 *          |    BYTE_32
 *          |    BYTE_64
 *          |    UBYTE_8
 *          |    UBYTE_16
 *          |    UBYTE_32
 *          |    UBYTE_64
 *          |    BIT
 *          |    CHAR
 *  
 *  ( type for dimensions )
 *  <dtype> ::=  I                ( integer )
 *          |    L                ( long )
 *          | <boxed-dtype>       ( fixnum )
 *  <boxed-dtype> ::=             ( empty )
 *  
 *  <aggreg>    ::= S             ( simple array/vector )
 *              | 
 *  
 *  <rankmark>  ::= V
 *              |   A 
 *  
 *  <accessor>  ::= REF   ( getter )
 *              |   SET   ( setter )
 *  
 *  <arity>     ::= _<arity-ind> | 
 *  <arity-ind> ::= 0|1|2|3|4|5|6|7|8|9|...
 *  
 */


#if SI_DEBUG_INLINE
#define SI_CHECK_INTEGER(x) x /* opt wrapper */
#define SI_CHECK_VALUE(x) x /* opt wrapper */
#define SI_IARG(x) SI_CHECK_INTEGER(x)
#define SI_IRET(x) SI_CHECK_VALUE(x)
#define SI_DEBUG_INLINE_ERROR(s) error(1,s)
#else
#define SI_IARG(x) (x)
#define SI_IRET(x) (x)
#endif

#define SI_NVARRAY_CONTENTS(o,t) \
    SI_PRIMITIVE_VECTOR_CONTENTS(SI_GENERAL_ARRAY_DISPLACED_TO(o),t)


#if SI_DEBUG_INLINE
#define SI_NONVECTOR_ARRAY_CONTENTS(a,t) \
   ((!SI_PRIMITIVE_VECTOR_P(a) && (SIMPLE_ARRAY_P(a))) \
     ? SI_NVARRAY_CONTENTS(a,t) \
     : SI_DEBUG_INLINE_ERROR("not a simple-array"))
#else
#define SI_NONVECTOR_ARRAY_CONTENTS(a,t) \
       SI_NVARRAY_CONTENTS(a,t)
#endif

#define SI_IROW_MAJOR_INDEX_0(o) 0

#define SI_IROW_MAJOR_INDEX_1(o, i1) (SI_IARG(i1))

#define SI_IROW_MAJOR_INDEX_2(o, i1, i2) \
    (SI_IROW_MAJOR_INDEX_1(o, i1)*SI_GENERAL_NVARRAY_DIMENSION(o, 1)+SI_IARG(i2))

#define SI_IROW_MAJOR_INDEX_3(o, i1, i2, i3) \
    (SI_IROW_MAJOR_INDEX_2(o, i1, i2)*SI_GENERAL_NVARRAY_DIMENSION(o, 2) + \
        SI_IARG(i3))

#define SI_IROW_MAJOR_INDEX_4(o, i1, i2, i3, i4) \
    (SI_IROW_MAJOR_INDEX_3(o, i1, i2, i3)*SI_GENERAL_NVARRAY_DIMENSION(o, 3) + \
        SI_IARG(i4))

#define SI_IROW_MAJOR_INDEX_5(o, i1, i2, i3, i4, i5) \
    (SI_IROW_MAJOR_INDEX_4(o, i1, i2, i3, i4)*SI_GENERAL_NVARRAY_DIMENSION(o, 4) + \
        SI_IARG(i5))

#define SI_IROW_MAJOR_INDEX_6(o, i1, i2, i3, i4, i5, i6) \
    (SI_IROW_MAJOR_INDEX_5(o, i1, i2, i3, i4, i5) * \
        SI_GENERAL_NVARRAY_DIMENSION(o, 5) + SI_IARG(i6))

#define SI_IROW_MAJOR_INDEX_7(o, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IROW_MAJOR_INDEX_6(o, i1, i2, i3, i4, i5, i6) * \
        SI_GENERAL_NVARRAY_DIMENSION(o, 6) + SI_IARG(i7))


/* (simple-array t (*)) */

#define T_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Object)[i]

#define SAREF_0(a) \
    (T_R_M_S_AREF(a, 0))

#define SAREF_1(a, i1) \
    SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Object)[IFIX(i1)])

#define SAREF_2(a, i1, i2) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define SAREF_3(a, i1, i2, i3) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define SAREF_4(a, i1, i2, i3, i4) \
    ((T_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define SAREF_5(a, i1, i2, i3, i4, i5) \
    ((T_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    ((T_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    ((T_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7))))


#define SASET_0(a, x) \
    (T_R_M_S_AREF(a, 0) = (x))

#define SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Object)[IFIX(i1)] = (x))

#define SASET_2(a, i1, i2, x) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = (x))

#define SASET_3(a, i1, i2, i3, x) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = (x))

#define SASET_4(a, i1, i2, i3, i4, x) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = (x))

#define SASET_5(a, i1, i2, i3, i4, i5, x) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = (x))

#define SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = (x))

#define SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (T_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = (x))


/* The name UNSIGNED_BYTE_8_ROW_MAJOR_SIMPLE_AREF will be too long for
   some C preprocessors */

/* unsigned byte, boxed */

#define UBYTE_8_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Uchar)[i]

#define UBYTE_8_SAREF_0(a) \
    FIX(UBYTE_8_R_M_S_AREF(a, 0))

#define UBYTE_8_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Uchar)[IFIX(i1)])

#define UBYTE_8_SAREF_2(a, i1, i2) \
    FIX(UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_8_SAREF_3(a, i1, i2, i3) \
    FIX(UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define UBYTE_8_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_8_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_8_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_8_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7))))


#define UBYTE_8_SASET_0(a, x) \
    (UBYTE_8_R_M_S_AREF(a, 0) = IFIX(x), (x))

#define UBYTE_8_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Uchar)[IFIX(i1)] = IFIX(x), (x))

#define UBYTE_8_SASET_2(a, i1, i2, x) \
    (UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = IFIX(x), (x))

#define UBYTE_8_SASET_3(a, i1, i2, i3, x) \
    (UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = IFIX(x), (x))

#define UBYTE_8_SASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = IFIX(x), (x))

#define UBYTE_8_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = IFIX(x), (x))

#define UBYTE_8_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = IFIX(x), (x))

#define UBYTE_8_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = IFIX(x), (x))

#define UBYTE_16_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Ushort)[i]

#define UBYTE_16_SAREF_0(a) \
    FIX(UBYTE_16_R_M_S_AREF(a, 0))

#define UBYTE_16_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ushort)[IFIX(i1)])

#define UBYTE_16_SAREF_2(a, i1, i2) \
    FIX(UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_16_SAREF_3(a, i1, i2, i3) \
    (FIX(UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define UBYTE_16_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_16_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_16_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_16_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define UBYTE_16_SASET_0(a, x) \
    (UBYTE_16_R_M_S_AREF(a, 0) = IFIX(x), (x))

#define UBYTE_16_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ushort)[IFIX(i1)] = IFIX(x), (x))

#define UBYTE_16_SASET_2(a, i1, i2, x) \
    (UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = IFIX(x), (x))

#define UBYTE_16_SASET_3(a, i1, i2, i3, x) \
    (UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = IFIX(x), (x))

#define UBYTE_16_SASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = IFIX(x), (x))

#define UBYTE_16_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = IFIX(x), (x))

#define UBYTE_16_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = IFIX(x), (x))

#define UBYTE_16_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = IFIX(x), (x))


#define UBYTE_32_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Ulong)[i]

#define UBYTE_32_SAREF_0(a) \
    FIX(UBYTE_32_R_M_S_AREF(a, 0))

#define UBYTE_32_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong)[IFIX(i1)])

#define UBYTE_32_SAREF_2(a, i1, i2) \
    FIX(UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_32_SAREF_3(a, i1, i2, i3) \
    (FIX(UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define UBYTE_32_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_32_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_32_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_32_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define UBYTE_32_SASET_0(a, x) \
    (UBYTE_32_R_M_S_AREF(a, 0) = IFIX(x), (x))

#define UBYTE_32_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong)[IFIX(i1)] = IFIX(x), (x))

#define UBYTE_32_SASET_2(a, i1, i2, x) \
    (UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = IFIX(x), (x))

#define UBYTE_32_SASET_3(a, i1, i2, i3, x) \
    (UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = IFIX(x), (x))

#define UBYTE_32_SASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = IFIX(x), (x))

#define UBYTE_32_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = IFIX(x), (x))

#define UBYTE_32_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = IFIX(x), (x))

#define UBYTE_32_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = IFIX(x), (x))

/* (unsigned-byte 64), boxed */

#define UBYTE_64_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Ulong64)[i]

#define UBYTE_64_SAREF_0(a) \
    FIX(UBYTE_64_R_M_S_AREF(a, 0))

#define UBYTE_64_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong64)[IFIX(i1)])

#define UBYTE_64_SAREF_2(a, i1, i2) \
    FIX(UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_64_SAREF_3(a, i1, i2, i3) \
    (FIX(UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define UBYTE_64_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_64_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_64_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_64_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define UBYTE_64_SASET_0(a, x) \
    (UBYTE_64_R_M_S_AREF(a, 0) = IFIX(x), (x))

#define UBYTE_64_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong64)[IFIX(i1)] = IFIX(x), (x))

#define UBYTE_64_SASET_2(a, i1, i2, x) \
    (UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = IFIX(x), (x))

#define UBYTE_64_SASET_3(a, i1, i2, i3, x) \
    (UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = IFIX(x), (x))

#define UBYTE_64_SASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = IFIX(x), (x))

#define UBYTE_64_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = IFIX(x), (x))

#define UBYTE_64_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = IFIX(x), (x))

#define UBYTE_64_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = IFIX(x), (x))

/* signed byteX, boxed */

#define BYTE_8_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Char)[i]

#define BYTE_8_SAREF_0(a) \
    FIX(BYTE_8_R_M_S_AREF(a, 0))

#define BYTE_8_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[IFIX(i1)])

#define BYTE_8_SAREF_2(a, i1, i2) \
    FIX(BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_8_SAREF_3(a, i1, i2, i3) \
    FIX(BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define BYTE_8_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_8_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_8_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_8_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7))))


#define BYTE_8_SASET_0(a, x) \
    (BYTE_8_R_M_S_AREF(a, 0) = IFIX(x), (x))

#define BYTE_8_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[IFIX(i1)] = IFIX(x), (x))

#define BYTE_8_SASET_2(a, i1, i2, x) \
    (BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = IFIX(x), (x))

#define BYTE_8_SASET_3(a, i1, i2, i3, x) \
    (BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = IFIX(x), (x))

#define BYTE_8_SASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = IFIX(x), (x))

#define BYTE_8_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = IFIX(x), (x))

#define BYTE_8_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = IFIX(x), (x))

#define BYTE_8_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_8_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = IFIX(x), (x))


#define BYTE_16_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Short)[i]

#define BYTE_16_SAREF_0(a) \
    FIX(BYTE_16_R_M_S_AREF(a, 0))

#define BYTE_16_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Short)[IFIX(i1)])

#define BYTE_16_SAREF_2(a, i1, i2) \
    FIX(BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_16_SAREF_3(a, i1, i2, i3) \
    (FIX(BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define BYTE_16_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_16_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_16_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_16_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define BYTE_16_SASET_0(a, x) \
    (BYTE_16_R_M_S_AREF(a, 0) = (short)IFIX(x), (x))

#define BYTE_16_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Short)[IFIX(i1)] = (short)IFIX(x), (x))

#define BYTE_16_SASET_2(a, i1, i2, x) \
    (BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = (short)IFIX(x), (x))

#define BYTE_16_SASET_3(a, i1, i2, i3, x) \
    (BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = (short)IFIX(x), (x))

#define BYTE_16_SASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = (short)IFIX(x), (x))

#define BYTE_16_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = (short)IFIX(x), (x))

#define BYTE_16_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = (short)IFIX(x), (x))

#define BYTE_16_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_16_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = (short)IFIX(x), (x))



#define BYTE_32_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Long)[i]

#define BYTE_32_SAREF_0(a) \
    FIX(BYTE_32_R_M_S_AREF(a, 0))

#define BYTE_32_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long)[IFIX(i1)])

#define BYTE_32_SAREF_2(a, i1, i2) \
    FIX(BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_32_SAREF_3(a, i1, i2, i3) \
    (FIX(BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define BYTE_32_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_32_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_32_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_32_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define BYTE_32_SASET_0(a, x) \
    (BYTE_32_R_M_S_AREF(a, 0) = IFIX(x), (x))

#define BYTE_32_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long)[IFIX(i1)] = IFIX(x), (x))

#define BYTE_32_SASET_2(a, i1, i2, x) \
    (BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = IFIX(x), (x))

#define BYTE_32_SASET_3(a, i1, i2, i3, x) \
    (BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = IFIX(x), (x))

#define BYTE_32_SASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = IFIX(x), (x))

#define BYTE_32_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = IFIX(x), (x))

#define BYTE_32_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = IFIX(x), (x))

#define BYTE_32_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_32_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = IFIX(x), (x))

/* (unsigned-byte 64), boxed */

#define BYTE_64_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Long64)[i]

#define BYTE_64_SAREF_0(a) \
    FIX(BYTE_64_R_M_S_AREF(a, 0))

#define BYTE_64_SAREF_1(a, i1) \
    FIX(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long64)[IFIX(i1)])

#define BYTE_64_SAREF_2(a, i1, i2) \
    FIX(BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_64_SAREF_3(a, i1, i2, i3) \
    (FIX(BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define BYTE_64_SAREF_4(a, i1, i2, i3, i4) \
    (FIX(BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_64_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FIX(BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_64_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FIX(BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_64_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FIX(BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define BYTE_64_SASET_0(a, x) \
    (BYTE_64_R_M_S_AREF(a, 0) = IFIX(x), (x))

#define BYTE_64_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long64)[IFIX(i1)] = IFIX(x), (x))

#define BYTE_64_SASET_2(a, i1, i2, x) \
    (BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) = IFIX(x), (x))

#define BYTE_64_SASET_3(a, i1, i2, i3, x) \
    (BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) = IFIX(x), (x))

#define BYTE_64_SASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = IFIX(x), (x))

#define BYTE_64_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = IFIX(x), (x))

#define BYTE_64_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = IFIX(x), (x))

#define BYTE_64_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_64_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = IFIX(x), (x))

/* T  simple arrays, unboxed*/

#define ISAREF_0(a) \
    SI_IRET(T_R_M_S_AREF(a, 0))

#define ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Object)[SI_IARG(i1)])

#define ISAREF_2(a, i1, i2) \
    SI_IRET(T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define ISAREF_3(a, i1, i2, i3) \
    SI_IRET(T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7))))


#define ISASET_0(a, x) \
    (T_R_M_S_AREF(a, 0) = SI_IARG(x))

#define ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Object)[SI_IARG(i1)] = SI_IARG(x))

#define ISASET_2(a, i1, i2, x) \
    (T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define ISASET_3(a, i1, i2, i3, x) \
    (T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define ISASET_4(a, i1, i2, i3, i4, x) \
    (T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (T_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))


/* unsigned byte, unboxed */
#define UBYTE_8_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Uchar)[i]

#define UBYTE_8_ISAREF_0(a) \
    SI_IRET(UBYTE_8_R_M_S_AREF(a, 0))

#define UBYTE_8_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Uchar)[SI_IARG(i1)])

#define UBYTE_8_ISAREF_2(a, i1, i2) \
    SI_IRET(UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_8_ISAREF_3(a, i1, i2, i3) \
    SI_IRET(UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define UBYTE_8_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_8_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_8_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_8_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7))))


#define UBYTE_8_ISASET_0(a, x) \
    (UBYTE_8_R_M_S_AREF(a, 0) = SI_IARG(x))

#define UBYTE_8_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Uchar)[SI_IARG(i1)] = SI_IARG(x))

#define UBYTE_8_ISASET_2(a, i1, i2, x) \
    (UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define UBYTE_8_ISASET_3(a, i1, i2, i3, x) \
    (UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define UBYTE_8_ISASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define UBYTE_8_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define UBYTE_8_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define UBYTE_8_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))


#define UBYTE_16_ISAREF_0(a) \
    SI_IRET(UBYTE_16_R_M_S_AREF(a, 0))

#define UBYTE_16_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ushort)[SI_IARG(i1)])

#define UBYTE_16_ISAREF_2(a, i1, i2) \
    SI_IRET(UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_16_ISAREF_3(a, i1, i2, i3) \
    (SI_IRET(UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define UBYTE_16_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_16_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_16_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_16_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define UBYTE_16_ISASET_0(a, x) \
    (UBYTE_16_R_M_S_AREF(a, 0) = (unsigned short)SI_IARG(x))

#define UBYTE_16_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ushort)[SI_IARG(i1)] = (unsigned short)SI_IARG(x))

#define UBYTE_16_ISASET_2(a, i1, i2, x) \
    (UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = (unsigned short)SI_IARG(x))

#define UBYTE_16_ISASET_3(a, i1, i2, i3, x) \
    (UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = (unsigned short)SI_IARG(x))

#define UBYTE_16_ISASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = (unsigned short)SI_IARG(x))

#define UBYTE_16_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = (unsigned short)SI_IARG(x))

#define UBYTE_16_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = (unsigned short)SI_IARG(x))

#define UBYTE_16_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = (unsigned short)SI_IARG(x))


#define UBYTE_32_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Ulong)[i]

#define UBYTE_32_ISAREF_0(a) \
    SI_IRET(UBYTE_32_R_M_S_AREF(a, 0))

#define UBYTE_32_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong)[SI_IARG(i1)])

#define UBYTE_32_ISAREF_2(a, i1, i2) \
    SI_IRET(UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_32_ISAREF_3(a, i1, i2, i3) \
    (SI_IRET(UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define UBYTE_32_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_32_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_32_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_32_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define UBYTE_32_ISASET_0(a, x) \
    (UBYTE_32_R_M_S_AREF(a, 0) = SI_IARG(x))

#define UBYTE_32_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong)[SI_IARG(i1)] = SI_IARG(x))

#define UBYTE_32_ISASET_2(a, i1, i2, x) \
    (UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define UBYTE_32_ISASET_3(a, i1, i2, i3, x) \
    (UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define UBYTE_32_ISASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define UBYTE_32_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define UBYTE_32_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define UBYTE_32_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))

/* (unsigned-byte 64), unboxed */

#define UBYTE_64_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Ulong64)[i]

#define UBYTE_64_ISAREF_0(a) \
    SI_IRET(UBYTE_64_R_M_S_AREF(a, 0))

#define UBYTE_64_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong64)[SI_IARG(i1)])

#define UBYTE_64_ISAREF_2(a, i1, i2) \
    SI_IRET(UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define UBYTE_64_ISAREF_3(a, i1, i2, i3) \
    (SI_IRET(UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define UBYTE_64_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define UBYTE_64_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define UBYTE_64_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define UBYTE_64_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define UBYTE_64_ISASET_0(a, x) \
    (UBYTE_64_R_M_S_AREF(a, 0) = SI_IARG(x))

#define UBYTE_64_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Ulong64)[SI_IARG(i1)] = SI_IARG(x))

#define UBYTE_64_ISASET_2(a, i1, i2, x) \
    (UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define UBYTE_64_ISASET_3(a, i1, i2, i3, x) \
    (UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define UBYTE_64_ISASET_4(a, i1, i2, i3, i4, x) \
    (UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define UBYTE_64_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define UBYTE_64_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define UBYTE_64_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (UBYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))

/* signed byteX, unboxed */

#define BYTE_8_ISAREF_0(a) \
    SI_IRET(BYTE_8_R_M_S_AREF(a, 0))

#define BYTE_8_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[SI_IARG(i1)])

#define BYTE_8_ISAREF_2(a, i1, i2) \
    SI_IRET(BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_8_ISAREF_3(a, i1, i2, i3) \
    SI_IRET(BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define BYTE_8_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_8_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_8_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_8_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7))))


#define BYTE_8_ISASET_0(a, x) \
    (BYTE_8_R_M_S_AREF(a, 0) = SI_IARG(x))

#define BYTE_8_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[SI_IARG(i1)] = SI_IARG(x))

#define BYTE_8_ISASET_2(a, i1, i2, x) \
    (BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define BYTE_8_ISASET_3(a, i1, i2, i3, x) \
    (BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define BYTE_8_ISASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define BYTE_8_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define BYTE_8_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define BYTE_8_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_8_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))

#define BYTE_16_ISAREF_0(a) \
    SI_IRET(BYTE_16_R_M_S_AREF(a, 0))

#define BYTE_16_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Short)[SI_IARG(i1)])

#define BYTE_16_ISAREF_2(a, i1, i2) \
    SI_IRET(BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_16_ISAREF_3(a, i1, i2, i3) \
    (SI_IRET(BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define BYTE_16_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_16_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_16_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_16_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define BYTE_16_ISASET_0(a, x) \
    (BYTE_16_R_M_S_AREF(a, 0) = SI_IARG(x))

#define BYTE_16_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Short)[SI_IARG(i1)] = SI_IARG(x))

#define BYTE_16_ISASET_2(a, i1, i2, x) \
    (BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define BYTE_16_ISASET_3(a, i1, i2, i3, x) \
    (BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define BYTE_16_ISASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define BYTE_16_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define BYTE_16_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define BYTE_16_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_16_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))


#define BYTE_32_ISAREF_0(a) \
    SI_IRET(BYTE_32_R_M_S_AREF(a, 0))

#define BYTE_32_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long)[SI_IARG(i1)])

#define BYTE_32_ISAREF_2(a, i1, i2) \
    SI_IRET(BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_32_ISAREF_3(a, i1, i2, i3) \
    (SI_IRET(BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define BYTE_32_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_32_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_32_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_32_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define BYTE_32_ISASET_0(a, x) \
    (BYTE_32_R_M_S_AREF(a, 0) = SI_IARG(x))

#define BYTE_32_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long)[SI_IARG(i1)] = SI_IARG(x))

#define BYTE_32_ISASET_2(a, i1, i2, x) \
    (BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define BYTE_32_ISASET_3(a, i1, i2, i3, x) \
    (BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define BYTE_32_ISASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define BYTE_32_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define BYTE_32_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define BYTE_32_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_32_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))

/* (signed-byte 64), unboxed */

#define BYTE_64_ISAREF_0(a) \
    SI_IRET(BYTE_64_R_M_S_AREF(a, 0))

#define BYTE_64_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long64)[SI_IARG(i1)])

#define BYTE_64_ISAREF_2(a, i1, i2) \
    SI_IRET(BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define BYTE_64_ISAREF_3(a, i1, i2, i3) \
    (SI_IRET(BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3))))

#define BYTE_64_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET(BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define BYTE_64_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET(BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define BYTE_64_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET(BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define BYTE_64_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET(BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3,i4,i5,i6,i7))))


#define BYTE_64_ISASET_0(a, x) \
    (BYTE_64_R_M_S_AREF(a, 0) = SI_IARG(x))

#define BYTE_64_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Long64)[SI_IARG(i1)] = SI_IARG(x))

#define BYTE_64_ISASET_2(a, i1, i2, x) \
    (BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) = SI_IARG(x))

#define BYTE_64_ISASET_3(a, i1, i2, i3, x) \
    (BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) = SI_IARG(x))

#define BYTE_64_ISASET_4(a, i1, i2, i3, i4, x) \
    (BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SI_IARG(x))

#define BYTE_64_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SI_IARG(x))

#define BYTE_64_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SI_IARG(x))

#define BYTE_64_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (BYTE_64_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SI_IARG(x))


/*  float boxed */


#define FLOAT_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Float)[i]

#define FLOAT_SAREF_0(a) \
    FLOAT_TO_SINGLE_FLOAT(FLOAT_R_M_S_AREF(a, 0))

#define FLOAT_SAREF_1(a, i1) \
    FLOAT_TO_SINGLE_FLOAT(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Float)[IFIX(i1)])

#define FLOAT_SAREF_2(a, i1, i2) \
    FLOAT_TO_SINGLE_FLOAT \
     (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define FLOAT_SAREF_3(a, i1, i2, i3) \
    FLOAT_TO_SINGLE_FLOAT \
     (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define FLOAT_SAREF_4(a, i1, i2, i3, i4) \
    (FLOAT_TO_SINGLE_FLOAT \
     (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define FLOAT_SAREF_5(a, i1, i2, i3, i4, i5) \
    (FLOAT_TO_SINGLE_FLOAT \
     (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define FLOAT_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (FLOAT_TO_SINGLE_FLOAT \
     (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define FLOAT_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (FLOAT_TO_SINGLE_FLOAT \
     (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4, i5, i6, i7))))


#define FLOAT_SASET_0(a, x) \
    (FLOAT_R_M_S_AREF(a, 0) = SINGLE_FLOAT_TO_FLOAT(x), (x))

#define FLOAT_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Float)[IFIX(i1)] \
     = SINGLE_FLOAT_TO_FLOAT(x), (x))

#define FLOAT_SASET_2(a, i1, i2, x) \
    (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) \
     = SINGLE_FLOAT_TO_FLOAT(x), (x))

#define FLOAT_SASET_3(a, i1, i2, i3, x) \
    (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) \
     = SINGLE_FLOAT_TO_FLOAT(x), (x))

#define FLOAT_SASET_4(a, i1, i2, i3, i4, x) \
    (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = SINGLE_FLOAT_TO_FLOAT(x), (x))

#define FLOAT_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = SINGLE_FLOAT_TO_FLOAT(x), (x))

#define FLOAT_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = SINGLE_FLOAT_TO_FLOAT(x), (x))

#define FLOAT_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (FLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = SINGLE_FLOAT_TO_FLOAT(x), (x))

/*  double float boxed */
#define DFLOAT_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Double)[i]

#define DFLOAT_SAREF_0(a) \
    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_R_M_S_AREF(a, 0))

#define DFLOAT_SAREF_1(a, i1) \
    DOUBLE_TO_DOUBLE_FLOAT(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Double)[IFIX(i1)])

#define DFLOAT_SAREF_2(a, i1, i2) \
    DOUBLE_TO_DOUBLE_FLOAT \
     (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define DFLOAT_SAREF_3(a, i1, i2, i3) \
    DOUBLE_TO_DOUBLE_FLOAT \
     (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define DFLOAT_SAREF_4(a, i1, i2, i3, i4) \
    (DOUBLE_TO_DOUBLE_FLOAT \
     (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define DFLOAT_SAREF_5(a, i1, i2, i3, i4, i5) \
    (DOUBLE_TO_DOUBLE_FLOAT \
     (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define DFLOAT_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (DOUBLE_TO_DOUBLE_FLOAT \
     (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define DFLOAT_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (DOUBLE_TO_DOUBLE_FLOAT \
     (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4, i5, i6, i7))))


#define DFLOAT_SASET_0(a, x) \
    (DFLOAT_R_M_S_AREF(a, 0) = DOUBLE_FLOAT_TO_DOUBLE(x), (x))

#define DFLOAT_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Double)[IFIX(i1)] \
     = DOUBLE_FLOAT_TO_DOUBLE(x), (x))

#define DFLOAT_SASET_2(a, i1, i2, x) \
    (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) \
     = DOUBLE_FLOAT_TO_DOUBLE(x), (x))

#define DFLOAT_SASET_3(a, i1, i2, i3, x) \
    (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) \
     = DOUBLE_FLOAT_TO_DOUBLE(x), (x))

#define DFLOAT_SASET_4(a, i1, i2, i3, i4, x) \
    (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = DOUBLE_FLOAT_TO_DOUBLE(x), (x))

#define DFLOAT_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = DOUBLE_FLOAT_TO_DOUBLE(x), (x))

#define DFLOAT_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = DOUBLE_FLOAT_TO_DOUBLE(x), (x))

#define DFLOAT_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (DFLOAT_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = DOUBLE_FLOAT_TO_DOUBLE(x), (x))


/*  float unboxed */
#define FLOAT_ISAREF_0(a) \
    SI_IRET(FLOAT_R_M_S_AREF(a, 0))

#define FLOAT_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Float)[SI_IARG(i1)])

#define FLOAT_ISAREF_2(a, i1, i2) \
    SI_IRET(FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define FLOAT_ISAREF_3(a, i1, i2, i3) \
     SI_IRET(FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define FLOAT_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET \
     (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define FLOAT_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET \
     (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define FLOAT_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET \
     (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define FLOAT_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET \
     (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4, i5, i6, i7))))


#define FLOAT_ISASET_0(a, x) \
    (FLOAT_R_M_S_AREF(a, 0) =  (x))

#define FLOAT_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Float)[SI_IARG(i1)] \
     =  (x))

#define FLOAT_ISASET_2(a, i1, i2, x) \
    (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) \
     =  (x))

#define FLOAT_ISASET_3(a, i1, i2, i3, x) \
    (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) \
     = (x))

#define FLOAT_ISASET_4(a, i1, i2, i3, i4, x) \
    (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = (x))

#define FLOAT_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = (x))

#define FLOAT_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = (x))

#define FLOAT_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (FLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = (x))

/*  double float unboxed */
#define DFLOAT_ISAREF_0(a) \
    SI_IRET(DFLOAT_R_M_S_AREF(a, 0))

#define DFLOAT_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Double)[SI_IARG(i1)])

#define DFLOAT_ISAREF_2(a, i1, i2) \
    SI_IRET \
     (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define DFLOAT_ISAREF_3(a, i1, i2, i3) \
    SI_IRET \
     (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define DFLOAT_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET \
     (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define DFLOAT_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET \
     (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define DFLOAT_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET \
     (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define DFLOAT_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET \
     (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4, i5, i6, i7))))


#define DFLOAT_ISASET_0(a, x) \
    (DFLOAT_R_M_S_AREF(a, 0) =  (x))

#define DFLOAT_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Double)[SI_IARG(i1)] \
     =  (x))

#define DFLOAT_ISASET_2(a, i1, i2, x) \
    (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) \
     =  (x))

#define DFLOAT_ISASET_3(a, i1, i2, i3, x) \
    (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) \
     = (x))

#define DFLOAT_ISASET_4(a, i1, i2, i3, i4, x) \
    (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = (x))

#define DFLOAT_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = (x))

#define DFLOAT_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = (x))

#define DFLOAT_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (DFLOAT_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = (x))

/*  simple general vector accessors */
#define SVSET(a, i1, x)          (SVREF(a, i1) = (x))
#define ISVREF(o, i)             SI_ISVREF(o, SI_IARG(i))
#define ISVSET(a, i1, x)          (SI_ISVREF(a, SI_IARG(i1)) = (x))

/*  simple string  accessors */
#define ISCHAR(a, i) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[SI_IARG(i)])

#define SET_ISCHAR(a, i, val) (ISCHAR(a,i) = (val))

/*  char  boxed */
#define CHAR_R_M_S_AREF(a, i) \
    SI_NONVECTOR_ARRAY_CONTENTS(a, SI_PVT_Char)[i]

#define CHAR_SAREF_0(a) \
    CHR(CHAR_R_M_S_AREF(a, 0))

#define CHAR_SAREF_1(a, i1) \
    CHR(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[IFIX(i1)])

#define CHAR_SAREF_2(a, i1, i2) \
    CHR \
     (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)))

#define CHAR_SAREF_3(a, i1, i2, i3) \
    CHR \
     (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define CHAR_SAREF_4(a, i1, i2, i3, i4) \
    (CHR \
     (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define CHAR_SAREF_5(a, i1, i2, i3, i4, i5) \
    (CHR \
     (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define CHAR_SAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (CHR \
     (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define CHAR_SAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (CHR \
     (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4, i5, i6, i7))))


#define CHAR_SASET_0(a, x) \
    (CHAR_R_M_S_AREF(a, 0) = ICHAR_CODE(x), (x))

#define CHAR_SASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[IFIX(i1)] \
     = ICHAR_CODE(x), (x))

#define CHAR_SASET_2(a, i1, i2, x) \
    (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_2(a, i1, i2)) \
     = ICHAR_CODE(x), (x))

#define CHAR_SASET_3(a, i1, i2, i3, x) \
    (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_3(a, i1, i2, i3)) \
     = ICHAR_CODE(x), (x))

#define CHAR_SASET_4(a, i1, i2, i3, i4, x) \
    (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = ICHAR_CODE(x), (x))

#define CHAR_SASET_5(a, i1, i2, i3, i4, i5, x) \
    (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = ICHAR_CODE(x), (x))

#define CHAR_SASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = ICHAR_CODE(x), (x))

#define CHAR_SASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (CHAR_R_M_S_AREF(a, ROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = ICHAR_CODE(x), (x))

/*  char  unboxed */
#define CHAR_ISAREF_0(a) \
    SI_IRET(CHAR_R_M_S_AREF(a, 0))

#define CHAR_ISAREF_1(a, i1) \
    SI_IRET(SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[SI_IARG(i1)])

#define CHAR_ISAREF_2(a, i1, i2) \
    SI_IRET \
     (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)))

#define CHAR_ISAREF_3(a, i1, i2, i3) \
    SI_IRET \
     (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)))

#define CHAR_ISAREF_4(a, i1, i2, i3, i4) \
    (SI_IRET \
     (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4))))

#define CHAR_ISAREF_5(a, i1, i2, i3, i4, i5) \
    (SI_IRET \
     (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5))))

#define CHAR_ISAREF_6(a, i1, i2, i3, i4, i5, i6) \
    (SI_IRET \
     (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6))))

#define CHAR_ISAREF_7(a, i1, i2, i3, i4, i5, i6, i7) \
    (SI_IRET \
     (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4, i5, i6, i7))))


#define CHAR_ISASET_0(a, x) \
    (CHAR_R_M_S_AREF(a, 0) = (x))

#define CHAR_ISASET_1(a, i1, x) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Char)[SI_IARG(i1)] \
     = (x))

#define CHAR_ISASET_2(a, i1, i2, x) \
    (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_2(a, i1, i2)) \
     = (x))

#define CHAR_ISASET_3(a, i1, i2, i3, x) \
    (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_3(a, i1, i2, i3)) \
     = (x))

#define CHAR_ISASET_4(a, i1, i2, i3, i4, x) \
    (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_4(a, i1, i2, i3, i4)) \
     = (x))

#define CHAR_ISASET_5(a, i1, i2, i3, i4, i5, x) \
    (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_5(a, i1, i2, i3, i4, i5)) \
     = (x))

#define CHAR_ISASET_6(a, i1, i2, i3, i4, i5, i6, x) \
    (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_6(a, i1, i2, i3, i4, i5, i6)) \
     = (x))

#define CHAR_ISASET_7(a, i1, i2, i3, i4, i5, i6, i7, x) \
    (CHAR_R_M_S_AREF(a, SI_IROW_MAJOR_INDEX_7(a, i1, i2, i3, i4,i5,i6,i7)) \
     = (x))


/* Fix these later */
#define SBIT0 bit0
#define SBIT2 bit2
#define SBIT3 bit3
#define SBIT4 bit4
#define SBIT5 bit5
#define SBIT6 bit6
#define SBIT7 bit7

#define SET_SBIT0 set_bit0
#define SET_SBIT2 set_bit2
#define SET_SBIT3 set_bit3
#define SET_SBIT4 set_bit4
#define SET_SBIT5 set_bit5
#define SET_SBIT6 set_bit6
#define SET_SBIT7 set_bit7

#define SBIT1(o,i)		SBIT_1(o,i)
#define SET_SBIT1(o,i,v)	SET_SBIT_1(o,i,v)


/*
 * Foreign language interface
 *
 * These must not do repeated argument evaluation.
 */

/* Convert foreign routine's return value to Lisp object */

#define  UNSIGNED_LONG_TO_INTEGER(x) (x <= IMOST_POSITIVE_FIXNUM ? \
                                      FIX(x) : unsigned_long_to_bignum(x))
#define           LONG_TO_INTEGER(x) (MAKE_INTEGER(x))
#define UNSIGNED_SHORT_TO_INTEGER(x) (LONG_TO_FIXNUM((fixnum_arithmetic_type) (x)))
#define          SHORT_TO_INTEGER(x) (LONG_TO_FIXNUM((fixnum_arithmetic_type) (x)))
#define  UNSIGNED_CHAR_TO_INTEGER(x) (LONG_TO_FIXNUM((fixnum_arithmetic_type) (x)))
#define           CHAR_TO_INTEGER(x) (LONG_TO_FIXNUM((fixnum_arithmetic_type) (x)))
#define            INT_TO_INTEGER(x) (LONG_TO_INTEGER((fixnum_arithmetic_type) (x)))  /* ? */
#define          INT64_TO_INTEGER(x) (cint64_to_int64(x))
#define   LONG_TO_FIXNUM(x)          (FIX(x))
#define    INT_TO_FIXNUM(x)          (FIX(x))
#define  SHORT_TO_FIXNUM(x)          (FIX(x))
#define   CHAR_TO_FIXNUM(x)          (FIX(x))
#define  INT64_TO_FIXNUM(x)          (FIX((SI_Long)ILONG64(x)))
#define DOUBLE_TO_DOUBLE_FLOAT(x)    (cdouble_to_double(x))
#define  FLOAT_TO_SINGLE_FLOAT(x)    (cdouble_to_double((double) x))
#define  FLOAT_TO_SHORT_FLOAT(x)     (FLOAT_TO_SINGLE_FLOAT(x))
#define   CHAR_TO_CHARACTER(x)	     (CHR((char) x))
#define  BOOLE_TO_BOOLEAN(x)         ((x) ? T : NIL)
#define   VOID_TO_NULL(x)	     ((x), NIL)

/* Convert Lisp object to foreign routine's argument */

#define INTEGER_TO_LONG(x)	     (IINTEGER(x))
#define INTEGER_TO_UNSIGNED_LONG(x)  (UINTEGER(x))
#define INTEGER_TO_INT(x)	     ((int) INTEGER_TO_LONG(x))
#define INTEGER_TO_UNSIGNED_INT(x)   ((unsigned int) INTEGER_TO_UNSIGNED_LONG(x))
#define INTEGER_TO_INT64(x)	     (LONG64P(x) ? ILONG64(x) : integer_to_int64(x))
#define INTEGER_TO_UINT64(x)	     ((SI_uint64) integer_to_int64(x))
#define INTEGER_TO_SHORT(x)	     ((short)	       IFIX(x))
#define INTEGER_TO_UNSIGNED_SHORT(x) ((unsigned short) IFIX(x))
#define INTEGER_TO_CHAR(x)	     ((char)	       IFIX(x))
#define INTEGER_TO_UNSIGNED_CHAR(x)  ((unsigned char)  IFIX(x))
#define FIXNUM_TO_LONG(x)         (IFIX(x))
#define FIXNUM_TO_INT(x)          ((int)   IFIX(x))
#define FIXNUM_TO_SHORT(x)        ((short) IFIX(x))
#define FIXNUM_TO_CHAR(x)         ((char)  IFIX(x))
#define FIXNUM_TO_INT64(x)        (clong_to_int64(IFIX(x)))
#define DOUBLE_FLOAT_TO_DOUBLE(x) ((double) IDOUBLE(x))
#define DOUBLE_FLOAT_TO_DOUBLE1(x) ((double) IDOUBLE1(x))
#define SINGLE_FLOAT_TO_FLOAT(x)  ((float)  IDOUBLE(x))
#define  SHORT_FLOAT_TO_FLOAT(x)  ((float)  IDOUBLE(x))
#define CHARACTER_TO_CHAR(x)	  ((char) CHR_CODE(x))
#define BOOLEAN_TO_BOOLE(x)	  ((x) ? 1 : 0)
#define        STRING_TO_CHAR_POINTER(x) SI_istring(x)
#define SIMPLE_STRING_TO_CHAR_POINTER(x) &SI_ISCHAR(x, 0)

#define BYTE_8_SARRAY_TO_CHAR_POINTER(x)  ((char *)SI_array_contents(x))
#define BYTE_16_SARRAY_TO_SHORT_POINTER(x) ((short *)SI_array_contents(x))
#define BYTE_32_SARRAY_TO_INT_POINTER(x) ((SI_Long *)SI_array_contents(x))
#define BYTE_64_SARRAY_TO_INT64_POINTER(x) ((SI_int64 *)SI_array_contents(x))
#define UBYTE_8_SARRAY_TO_UCHAR_PTR(x)	 \
    ((unsigned char *)SI_array_contents(x))
#define UBYTE_16_SARRAY_TO_USHORT_PTR(x)  \
    ((unsigned short *)SI_array_contents(x))
#define UBYTE_32_SARRAY_TO_UINT_PTR(x) ((SI_Ulong *)SI_array_contents(x))
#define UBYTE_64_SARRAY_TO_UINT64_PTR(x) ((SI_uint64 *)SI_array_contents(x))
/* #define SFLOAT_SARRAY_TO_FLOAT_POINTER(x) ((float *)SI_array_contents(x)) */
#define DFLOAT_SARRAY_TO_DOUBLE_POINTER(x) ((double *)SI_array_contents(x))

#define SIMPLE_ARRAY_ANY_1_P(o) SI_PRIMITIVE_VECTOR_P(o)
#define SIMPLE_ARRAY_ANY_1_LENGTH(o) \
  SI_STORED_OBJECT_FIELD(o, SI_Primitive_vector, length)
