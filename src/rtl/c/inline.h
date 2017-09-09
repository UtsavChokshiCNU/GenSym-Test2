/*
 * inline.h - inline functions (C macros) for Common Lisp
 *            runtime support library
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 * For macros supporting Common Lisp special forms, see kernel.h.
 */

/* #define ACONS(k,d,a)		CAREFUL_CALL_2(cons, cons(k,d), a) */
#define ACONS(k,d,a)		acons(k,d,a)
#define ATOM(a)			(!CONSP(a))

#define ICHAR(o,i)		SI_string_base(o)[i]
#define SET_ICHAR(o,i,c)	(ICHAR(o,i) = c)
#define CHAR(a,b)		CHR(ICHAR(a,IFIX(b)))
#define SET_CHAR(s,i,c)         (ICHAR(s,IFIX(i)) = ICHAR_CODE(c), c)

#define CHAR_CODE(a)		FIX(CHR_CODE(a))
#define CHAR_FONT(a)		FIX(CHR_FONT(a))
#define CHAR_BITS(a)		FIX(CHR_BITS(a))
#define CHAR_INT(a)		FIX(ICHAR_INT(a))
#define CODE_CHAR(a)	(CHR(IFIX(a)))

/* 9/4/91: bits and fonts are obsolete; ignore them */
#define MAKE_CHAR(a,b,c)	(MAKE_CHR(ICHAR_CODE(a), 0))
#define STANDARD_CHAR_P(a)	((GRAPHIC_CHAR_P(a) && \
				  (a) != CHR('\177')) || \
				 (a) == CHR('\n'))
#define GRAPHIC_CHAR_P(a)	isprint(ICHAR_CODE(a))
#define STRING_CHAR_P(c)        (ICHAR_BITS(c) == 0 && ICHAR_FONT(c) == 0)
#define ALPHA_CHAR_P(a)		isalpha(ICHAR_CODE(a))
#define UPPER_CASE_P(a)		isupper(ICHAR_CODE(a))
#define LOWER_CASE_P(a)		islower(ICHAR_CODE(a))
#define ALPHANUMERICP(a)	isalnum(ICHAR_CODE(a))
#define CHAR_EQ(a,b)		(ICHAR_INT(a) == ICHAR_INT(b))
#define CHAR_NE(a,b)		(ICHAR_INT(a) != ICHAR_INT(b))
#define CHAR_LT(a,b)		(ICHAR_INT(a) < ICHAR_INT(b))
#define CHAR_GT(a,b)		(ICHAR_INT(a) > ICHAR_INT(b))
#define CHAR_LE(a,b)		(ICHAR_INT(a) <= ICHAR_INT(b))
#define CHAR_GE(a,b)		(ICHAR_INT(a) >= ICHAR_INT(b))
#define CHAR_UPCASE(c)		MAKE_CHR(TOUPPER(ICHAR_CODE(c)), \
					  ICHAR_BITS(c))
#define CHAR_DOWNCASE(c)	MAKE_CHR(TOLOWER(ICHAR_CODE(c)), \
					  ICHAR_BITS(c))
#define CHAR_EQUAL(a,b)		(ICHAR_UPCASE(a) == ICHAR_UPCASE(b))
#define CHAR_NOT_EQUAL(a,b)	(ICHAR_UPCASE(a) != ICHAR_UPCASE(b))
#define CHAR_LESSP(a,b)		(ICHAR_UPCASE(a) < ICHAR_UPCASE(b))
#define CHAR_GREATERP(a,b)	(ICHAR_UPCASE(a) > ICHAR_UPCASE(b))
#define CHAR_NOT_GREATERP(a,b)	(ICHAR_UPCASE(a) <= ICHAR_UPCASE(b))
#define CHAR_NOT_LESSP(a,b)	(ICHAR_UPCASE(a) >= ICHAR_UPCASE(b))
#define COMPLEXP(a)		SI_STORED_OBJECT_TYPEP(a, COMPLEX_TYPE)
#define ENDP(a)			((a) == NIL)  /* unsafe */
#define EQ(a, b)		((a) == (b))
#define EQL(a, b)		(EQ((a),(b)) || (!SI_IMMEDIATEP(a) && \
                                   !SI_IMMEDIATEP(b) && TRUEP(eql((a),(b)))))
#define EQUAL(a, b)		(EQ(a,b) || (!SI_IMMEDIATEP(a) && \
                                   !SI_IMMEDIATEP(b) && TRUEP(equal(a,b))))
#define TYPEP(a, b, c)          (typep(a, b, c))
#define FLOATP(a)		DOUBLEP(a)
#define HASH_TABLE_P(a)	SI_STORED_OBJECT_TYPEP(a, HASH_TABLE_TYPE)
#define IDENTITY(a)		(a)
#define INT_CHAR(a)		CHR(IFIX(a))
#define SI_INTEGERP(a)		(SI_IMMEDIATEP(a) ? FIXNUMP(a) : \
				 (SI_STORED_OBJECT_TYPE(a) == BIGNUM_TYPE \
                                  || SI_STORED_OBJECT_TYPE(a) == LONG64_TYPE))
#define INTEGERP(a)		SI_INTEGERP((a))
#define LISTP(a)		((a) == NIL || CONSP(a))
#define NOT(a)			((a) == NIL ? T : NIL )

#define NUMBERP(a)	        (SI_IMMEDIATEP(a) ? FIXNUMP(a) : \
				 SI_ENUM_LE(SI_STORED_OBJECT_TYPE(a), COMPLEX_TYPE))
#define RANDOM_STATE_P(a)	SI_STORED_OBJECT_TYPEP(a, RANDOM_STATE_TYPE)
#define RATIOP(a)            SI_STORED_OBJECT_TYPEP(a, RATIO_TYPE)
#define RATIONALP(a)	        (SI_IMMEDIATEP(a) ? FIXNUMP(a) : \
				 (SI_ENUM_GE(SI_STORED_OBJECT_TYPE(a), OBIGNUM_TYPE) && \
				  SI_ENUM_LE(SI_STORED_OBJECT_TYPE(a), RATIO_TYPE)))
#define NUMERATOR(a)		(RATIOP(a) ? RATIO_NUMERATOR(a) : (a))
#define DENOMINATOR(a)		(RATIOP(a) ? RATIO_DENOMINATOR(a) : FIX(1L))
#define READTABLEP(a)		SI_STORED_OBJECT_TYPEP(a, READTABLE_TYPE)
#define RPLACA(a,b)		(M_CAR(a) = (b), (a))
#define RPLACD(a,b)		(M_CDR(a) = (b), (a))
#define STREAMP(a)		SI_STORED_OBJECT_TYPEP(a, STREAM_TYPE)
#define WHITESPACE_CHAR_P(a)	isspace(ICHAR_CODE(a))

/* Support for (TYPEP foo 'double-float) */
#define DOUBLE_FLOAT_P(x)	DOUBLEP(x)


#if SI_SUPPORT_SF

/* Change entry-name for TRUN:%APPEND-2 in symbols.lisp? */
#define APPEND_2 		append2
/* Could be open-coded: (if (endp x) y (setf (cdr (last x)) y)) */
#define NCONC_2 		nconc2
#define REALP(o)		(SI_IMMEDIATEP(o) ? FIXNUMP(o) : \
				 SI_ENUM_LE(SI_STORED_OBJECT_TYPE(o), DOUBLE_TYPE))
#define SEQUENCEP(o)		(LISTP(o) || VECTORP(o))
#define BITP(o)			((o) == ZERO || (o) == FIX(1))

#define BOUNDP(x) 		(boundp(x) != NIL)
#define EQUALP(x, y) 		(equalp(x, y) != NIL)
#define INPUT_STREAM_P(x)  	(input_stream_p(x) != NIL)
#define OUTPUT_STREAM_P(x) 	(output_stream_p(x) != NIL)

#define BROADCAST_STREAM_P(x)	(broadcast_stream_p(x) != NIL)
#define CONCATENATED_STREAM_P(x) (concatenated_stream_p(x) != NIL)
#define ECHO_STREAM_P(x)	(echo_stream_p(x) != NIL)
#define FILE_STREAM_P(x)	(file_stream_p(x) != NIL)
#define STRING_INPUT_STREAM_P(x) (string_input_stream_p(x) != NIL)
#define STRING_OUTPUT_STREAM_P(x) (string_output_stream_p(x) != NIL)
#define STRING_STREAM_P(x)	(string_stream_p(x) != NIL)
#define SYNONYM_STREAM_P(x)	(synonym_stream_p(x) != NIL)
#define TWO_WAY_STREAM_P(x)	(two_way_stream_p(x) != NIL)
#define INTERACTION_STREAM_P(x) (interaction_stream_p(x) != NIL)

#endif /* SI_SUPPORT_SF */


#ifdef SI_RUNTIME_INTERNAL
#define SI_Declare_static_string(v,d,s) \
    SI_Declare_static_constant(v,d,STATIC_STRING(s))

/* The (d = 0, d) is there purely to make lint happy. */
#define SI_Declare_static_constant(v,d,exp)	\
    static Object v = UNBOUND;		\
    int d = (v == UNBOUND ? (v = (exp), 0) : (d = 0, d))
#endif


#define bit aref
#define bit0 aref0
#define bit1 aref1
#define bit2 aref2
#define bit3 aref3
#define bit4 aref4
#define bit5 aref5
#define bit6 aref6
#define bit7 aref7
#define sbit aref
#define set_bit0 set_aref0
#define set_bit1 set_aref1
#define set_bit2 set_aref2
#define set_bit3 set_aref3
#define set_bit4 set_aref4
#define set_bit5 set_aref5
#define set_bit6 set_aref6
#define set_bit7 set_aref7


/* More functions */

#define CAAR(a)		((a && M_CAR(a)) ? M_CAAR(a) : NIL)
#define CADR(a)		((a && M_CDR(a)) ? M_CADR(a) : NIL)
#define CDAR(a)		((a && M_CAR(a)) ? M_CDAR(a) : NIL)
#define CDDR(a)		((a && M_CDR(a)) ? M_CDDR(a) : NIL)
#define CAAAR(a)	((a && M_CAR(a) && M_CAAR(a)) ? M_CAAAR(a) : NIL)
#define CAADR(a)	((a && M_CDR(a) && M_CADR(a)) ? M_CAADR(a) : NIL)
#define CADAR(a)	((a && M_CAR(a) && M_CDAR(a)) ? M_CADAR(a) : NIL)
#define CADDR(a)	((a && M_CDR(a) && M_CDDR(a)) ? M_CADDR(a) : NIL)
#define CDAAR(a)	((a && M_CAR(a) && M_CAAR(a)) ? M_CDAAR(a) : NIL)
#define CDADR(a)	((a && M_CDR(a) && M_CADR(a)) ? M_CDADR(a) : NIL)
#define CDDAR(a)	((a && M_CAR(a) && M_CDAR(a)) ? M_CDDAR(a) : NIL)
#define CDDDR(a)	((a && M_CDR(a) && M_CDDR(a)) ? M_CDDDR(a) : NIL)
#define CAAAAR(a)	(CAAAR(a) ? M_CAAAAR(a) : NIL)
#define CAAADR(a)	(CAADR(a) ? M_CAAADR(a) : NIL)
#define CAADAR(a)	(CADAR(a) ? M_CAADAR(a) : NIL)
#define CAADDR(a)	(CADDR(a) ? M_CAADDR(a) : NIL)
#define CADAAR(a)	(CDAAR(a) ? M_CADAAR(a) : NIL)
#define CADADR(a)	(CDADR(a) ? M_CADADR(a) : NIL)
#define CADDAR(a)	(CDDAR(a) ? M_CADDAR(a) : NIL)
#define CADDDR(a)	(CDDDR(a) ? M_CADDDR(a) : NIL)
#define CDAAAR(a)	(CAAAR(a) ? M_CDAAAR(a) : NIL)
#define CDAADR(a)	(CAADR(a) ? M_CDAADR(a) : NIL)
#define CDADAR(a)	(CADAR(a) ? M_CDADAR(a) : NIL)
#define CDADDR(a)	(CADDR(a) ? M_CDADDR(a) : NIL)
#define CDDAAR(a)	(CDAAR(a) ? M_CDDAAR(a) : NIL)
#define CDDADR(a)	(CDADR(a) ? M_CDDADR(a) : NIL)
#define CDDDAR(a)	(CDDAR(a) ? M_CDDDAR(a) : NIL)
#define CDDDDR(a)	(CDDDR(a) ? M_CDDDDR(a) : NIL)

#define FIRST(a)	CAR(a)
#define SECOND(a)	CADR(a)
#define THIRD(a)	CADDR(a)
#define FOURTH(a)	CADDDR(a)
#define FIFTH(a)	NTH(FIX(4L),a)
#define SIXTH(a)	NTH(FIX(5L),a)
#define SEVENTH(a)	NTH(FIX(6L),a)
#define EIGHTH(a)	NTH(FIX(7L),a)
#define NINTH(a)	NTH(FIX(8L),a)
#define TENTH(a)	NTH(FIX(9L),a)
#define REST(a)		CDR(a)
/* SF wants this to be an lvalue */
#define NTH(a,b)	nth_inline(a,b)

#define LIST_STAR_2(a0,a1)	cons(a0,a1)

/* #define LIST_STAR_3(a0,a1,a2)   CAREFUL_CALL_2(cons,a0,cons(a1,a2)) */
#define LIST_STAR_3(a0,a1,a2)   list_star(3,a0,a1,a2)

#define LIST_0()		NIL
#define LIST_1(a0)		ncons(a0)
#define LIST_2(a0,a1)		list(2,a0,a1)
#define LIST_3(a0,a1,a2)	list(3,a0,a1,a2)
#define LIST_4(a0,a1,a2,a3)	list(4,a0,a1,a2,a3)
#define LIST_5(a0,a1,a2,a3,a4)	list(5,a0,a1,a2,a3,a4)
#define LIST_6(a0,a1,a2,a3,a4,a5) list(6,a0,a1,a2,a3,a4,a5)
#define LIST_7(a0,a1,a2,a3,a4,a5,a6) list(7,a0,a1,a2,a3,a4,a5,a6)
#define LIST_8(a0,a1,a2,a3,a4,a5,a6,a7) list(8,a0,a1,a2,a3,a4,a5,a6,a7)
#define LIST_9(a0,a1,a2,a3,a4,a5,a6,a7,a8) \
		(list(9,a0,a1,a2,a3,a4,a5,a6,a7,a8))
#define LIST_10(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9)  \
		(list(10,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9))
#define LIST_11(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) \
		(list(11,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10))
#define LIST_12(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11) \
		(list(12,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11))
#define LIST_13(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12) \
		(list(13,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12))
#define LIST_14(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13) \
		(list(14,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13))
#define LIST_15(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14) \
		(list(15,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14))
#define LIST_16(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15) \
		(list(16,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15))
#define LIST_17(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16) \
		(list(17,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16))
#define LIST_18(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17) \
		(list(18,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17))
#define LIST_19(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18) \
		(list(19,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18))
#define LIST_20(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19) \
		(list(20,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19))
#define LIST_21(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20) \
		(list(21,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20))
#define LIST_22(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21) \
		(list(22,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,a21))
#define LIST_23(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22) \
		(list(23,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,a21,a22))
#define LIST_24(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23) \
		(list(24,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,a21,a22,a23))
#define LIST_25(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24) \
		(list(25,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,a21,a22,a23,a24))
#define LIST_26(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25) \
		(list(26,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25))
#define LIST_27(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26) \
		(list(27,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26))
#define LIST_28(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h) \
		(list(28,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h))
#define LIST_29(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h,i) \
		(list(29,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h,i))
#define LIST_30(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h,i,j) \
		(list(30,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h,i,j))

#define LIST_31(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h,i,j,k) \
		(list(31,a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14, \
			a15,a16,a17,a18,a19,a20,b,c,d,e,f,g,h,i,j,k))

#define NTH_0(a)	CAR(a)
#define NTH_1(a)	CADR(a)
#define NTH_2(a)	CADDR(a)
#define NTH_3(a)	NTH(FIX(3),a)
#define NTH_4(a)	NTH(FIX(4),a)
#define NTH_5(a)	NTH(FIX(5),a)
#define NTH_6(a)	NTH(FIX(6),a)
#define NTH_7(a)	NTH(FIX(7),a)
#define NTH_8(a)	NTH(FIX(8),a)
#define NTH_9(a)	NTH(FIX(9),a)
#define NTH_10(a)	NTH(FIX(10),a)
#define NTH_11(a)	NTH(FIX(11),a)
#define NTH_12(a)	NTH(FIX(12),a)
#define NTH_13(a)	NTH(FIX(13),a)
#define NTH_14(a)	NTH(FIX(14),a)
#define NTH_15(a)	NTH(FIX(15),a)
#define NTH_16(a)	NTH(FIX(16),a)
#define NTH_17(a)	NTH(FIX(17),a)
#define NTH_18(a)	NTH(FIX(18),a)
#define NTH_19(a)	NTH(FIX(19),a)
#define NTH_20(a)	NTH(FIX(20),a)
#define NTH_21(a)	NTH(FIX(21),a)
#define NTH_22(a)	NTH(FIX(22),a)
#define NTH_23(a)	NTH(FIX(23),a)
#define NTH_24(a)	NTH(FIX(24),a)
#define NTH_25(a)	NTH(FIX(25),a)
#define NTH_26(a)	NTH(FIX(26),a)
#define NTH_27(a)	NTH(FIX(27),a)
#define NTH_28(a)	NTH(FIX(28),a)
#define NTH_29(a)	NTH(FIX(29),a)
#define NTH_30(a)	NTH(FIX(30),a)
#define NTH_31(a)	NTH(FIX(31),a)
#define NTH_32(a)	NTH(FIX(32),a)
#define NTH_33(a)	NTH(FIX(33),a)
#define NTH_34(a)	NTH(FIX(34),a)
#define NTH_35(a)	NTH(FIX(35),a)
#define NTH_36(a)	NTH(FIX(36),a)
#define NTH_37(a)	NTH(FIX(37),a)
#define NTH_38(a)	NTH(FIX(38),a)
#define NTH_39(a)	NTH(FIX(39),a)
#define NTH_40(a)	NTH(FIX(40),a)

/* Use global temporary to avoid argument reevaluation */

#define T_VALUES_1(a)    (T_temp = (a), VALUES_1(T_temp))

#define T_CAR(a)	(T_temp=(a),CAR(T_temp))
#define T_CDR(a)	(T_temp=(a),CDR(T_temp))
#define T_CAAR(a)	(T_temp=(a),CAAR(T_temp))
#define T_CADR(a)	(T_temp=(a),CADR(T_temp))
#define T_CDAR(a)	(T_temp=(a),CDAR(T_temp))
#define T_CDDR(a)	(T_temp=(a),CDDR(T_temp))
#define T_CAAAR(a)	(T_temp=(a),CAAAR(T_temp))
#define T_CAADR(a)	(T_temp=(a),CAADR(T_temp))
#define T_CADAR(a)	(T_temp=(a),CADAR(T_temp))
#define T_CADDR(a)	(T_temp=(a),CADDR(T_temp))
#define T_CDAAR(a)	(T_temp=(a),CDAAR(T_temp))
#define T_CDADR(a)	(T_temp=(a),CDADR(T_temp))
#define T_CDDAR(a)	(T_temp=(a),CDDAR(T_temp))
#define T_CDDDR(a)	(T_temp=(a),CDDDR(T_temp))
#define T_CAAAAR(a)	(T_temp=(a),CAAAAR(T_temp))
#define T_CAAADR(a)	(T_temp=(a),CAAADR(T_temp))
#define T_CAADAR(a)	(T_temp=(a),CAADAR(T_temp))
#define T_CAADDR(a)	(T_temp=(a),CAADDR(T_temp))
#define T_CADAAR(a)	(T_temp=(a),CADAAR(T_temp))
#define T_CADADR(a)	(T_temp=(a),CADADR(T_temp))
#define T_CADDAR(a)	(T_temp=(a),CADDAR(T_temp))
#define T_CADDDR(a)	(T_temp=(a),CADDDR(T_temp))
#define T_CDAAAR(a)	(T_temp=(a),CDAAAR(T_temp))
#define T_CDAADR(a)	(T_temp=(a),CDAADR(T_temp))
#define T_CDADAR(a)	(T_temp=(a),CDADAR(T_temp))
#define T_CDADDR(a)	(T_temp=(a),CDADDR(T_temp))
#define T_CDDAAR(a)	(T_temp=(a),CDDAAR(T_temp))
#define T_CDDADR(a)	(T_temp=(a),CDDADR(T_temp))
#define T_CDDDAR(a)	(T_temp=(a),CDDDAR(T_temp))
#define T_CDDDDR(a)	(T_temp=(a),CDDDDR(T_temp))
#define T_FIRST(a)	T_CAR(a)
#define T_SECOND(a)	T_CADR(a)
#define T_THIRD(a)	T_CADDR(a)
#define T_FOURTH(a)	T_CADDDR(a)
#define T_ATOM(a)	(T_temp = (a), ATOM(T_temp))
#define T_CONSP(a)	(T_temp = (a), CONSP(T_temp))
#define T_LISTP(a)	(T_temp = (a), LISTP(T_temp))
#define T_SYMBOLP(a)	(T_temp = (a), SYMBOLP(T_temp))

/* Direct versions of CxxxR that assume there will be no need to
   take CAR or CDR of NIL */

#define M_CAAR(a)		M_CAR(M_CAR(a))
#define M_CADR(a)		M_CAR(M_CDR(a))
#define M_CDAR(a)		M_CDR(M_CAR(a))
#define M_CDDR(a)		M_CDR(M_CDR(a))
#define M_CAAAR(a)		M_CAR(M_CAAR(a))
#define M_CAADR(a)		M_CAR(M_CADR(a))
#define M_CADAR(a)		M_CAR(M_CDAR(a))
#define M_CADDR(a)		M_CAR(M_CDDR(a))
#define M_CDAAR(a)		M_CDR(M_CAAR(a))
#define M_CDADR(a)		M_CDR(M_CADR(a))
#define M_CDDAR(a)		M_CDR(M_CDAR(a))
#define M_CDDDR(a)		M_CDR(M_CDDR(a))
#define M_CAAAAR(a)		M_CAR(M_CAAAR(a))
#define M_CAAADR(a)		M_CAR(M_CAADR(a))
#define M_CAADAR(a)		M_CAR(M_CADAR(a))
#define M_CAADDR(a)		M_CAR(M_CADDR(a))
#define M_CADAAR(a)		M_CAR(M_CDAAR(a))
#define M_CADADR(a)		M_CAR(M_CDADR(a))
#define M_CADDAR(a)		M_CAR(M_CDDAR(a))
#define M_CADDDR(a)		M_CAR(M_CDDDR(a))
#define M_CDAAAR(a)		M_CDR(M_CAAAR(a))
#define M_CDAADR(a)		M_CDR(M_CAADR(a))
#define M_CDADAR(a)		M_CDR(M_CADAR(a))
#define M_CDADDR(a)		M_CDR(M_CADDR(a))
#define M_CDDAAR(a)		M_CDR(M_CDAAR(a))
#define M_CDDADR(a)		M_CDR(M_CDADR(a))
#define M_CDDDAR(a)		M_CDR(M_CDDAR(a))
#define M_CDDDDR(a)		M_CDR(M_CDDDR(a))
#define M_NTH(a,b)		M_CAR(m_nthcdr(FIXNUM_TO_INT(a),b))

#define M_FIRST(a)		M_CAR(a)
#define M_SECOND(a)		M_CADR(a)
#define M_THIRD(a)		M_CADDR(a)
#define M_FOURTH(a)		M_CADDDR(a)
#define M_FIFTH(a)		M_NTH(FIX(4),a)
#define M_SIXTH(a)		M_NTH(FIX(5),a)
#define M_SEVENTH(a)		M_NTH(FIX(6),a)
#define M_EIGHTH(a)		M_NTH(FIX(7),a)
#define M_NINTH(a)		M_NTH(FIX(8),a)
#define M_TENTH(a)		M_NTH(FIX(9),a)
#define M_REST(a)		M_CDR(a)

#define M_NTH_0(a)		M_CAR(a)
#define M_NTH_1(a)		M_CADR(a)
#define M_NTH_2(a)		M_CADDR(a)
#define M_NTH_3(a)		M_CADDDR(a)
#define M_NTH_4(a)		M_NTH(FIX(4),a)
#define M_NTH_5(a)		M_NTH(FIX(5),a)
#define M_NTH_6(a)		M_NTH(FIX(6),a)
#define M_NTH_7(a)		M_NTH(FIX(7),a)
#define M_NTH_8(a)		M_NTH(FIX(8),a)
#define M_NTH_9(a)		M_NTH(FIX(9),a)
#define M_NTH_10(a)		M_NTH(FIX(10),a)
#define M_NTH_11(a)		M_NTH(FIX(11),a)
#define M_NTH_12(a)		M_NTH(FIX(12),a)
#define M_NTH_13(a)		M_NTH(FIX(13),a)
#define M_NTH_14(a)		M_NTH(FIX(14),a)
#define M_NTH_15(a)		M_NTH(FIX(15),a)
#define M_NTH_16(a)		M_NTH(FIX(16),a)
#define M_NTH_17(a)		M_NTH(FIX(17),a)
#define M_NTH_18(a)		M_NTH(FIX(18),a)
#define M_NTH_19(a)		M_NTH(FIX(19),a)
#define M_NTH_20(a)		M_NTH(FIX(20),a)
#define M_NTH_21(a)		M_NTH(FIX(21),a)
#define M_NTH_22(a)		M_NTH(FIX(22),a)
#define M_NTH_23(a)		M_NTH(FIX(23),a)
#define M_NTH_24(a)		M_NTH(FIX(24),a)
#define M_NTH_25(a)		M_NTH(FIX(25),a)
#define M_NTH_26(a)		M_NTH(FIX(26),a)
#define M_NTH_27(a)		M_NTH(FIX(27),a)
#define M_NTH_28(a)		M_NTH(FIX(28),a)
#define M_NTH_29(a)		M_NTH(FIX(29),a)
#define M_NTH_30(a)		M_NTH(FIX(30),a)
#define M_NTH_31(a)		M_NTH(FIX(31),a)
#define M_NTH_32(a)		M_NTH(FIX(32),a)
#define M_NTH_33(a)		M_NTH(FIX(33),a)
#define M_NTH_34(a)		M_NTH(FIX(34),a)
#define M_NTH_35(a)		M_NTH(FIX(35),a)
#define M_NTH_36(a)		M_NTH(FIX(36),a)
#define M_NTH_37(a)		M_NTH(FIX(37),a)
#define M_NTH_38(a)		M_NTH(FIX(38),a)
#define M_NTH_39(a)		M_NTH(FIX(39),a)
#define M_NTH_40(a)		M_NTH(FIX(40),a)

/* Common Lisp constants */

#define CHAR_CODE_LIMIT  FIX(256L) /* upper exclusive (code range 0-255) */
#define CHAR_FONT_LIMIT  FIX(1L)
#define CHAR_BITS_LIMIT  FIX(32L)
#define CHAR_CONTROL_BIT FIX(ICHAR_CONTROL_BIT)
#define CHAR_META_BIT	 FIX(ICHAR_META_BIT)
#define CHAR_SUPER_BIT	 FIX(ICHAR_SUPER_BIT)
#define CHAR_HYPER_BIT	 FIX(ICHAR_HYPER_BIT)

#define BOOLE_CLR	ZERO
#define BOOLE_AND	FIX(1L)
#define BOOLE_ANDC1	FIX(2L)
#define BOOLE_2		FIX(3L)
#define BOOLE_ANDC2	FIX(4L)
#define BOOLE_1		FIX(5L)
#define BOOLE_XOR	FIX(6L)
#define BOOLE_IOR	FIX(7L)
#define BOOLE_NOR	FIX(8L)
#define BOOLE_EQV	FIX(9L)
#define BOOLE_C1	FIX(10L)
#define BOOLE_ORC1	FIX(11L)
#define BOOLE_C2	FIX(12L)
#define BOOLE_ORC2	FIX(13L)
#define BOOLE_NAND	FIX(14L)
#define BOOLE_SET	FIX(15L)

#define MOST_POSITIVE_FIXNUM    FIX(IMOST_POSITIVE_FIXNUM)
#define MOST_NEGATIVE_FIXNUM    FIX(IMOST_NEGATIVE_FIXNUM)
#define CALL_ARGUMENTS_LIMIT    FIX(MAXARGS)	/* upper bound #args passed */
#define MULTIPLE_VALUES_LIMIT   FIX(MAXARGS)
#define ARRAY_RANK_LIMIT        FIX(IARRAY_RANK_LIMIT)
#define ARRAY_DIMENSION_LIMIT   FIX(IARRAY_DIMENSION_LIMIT)
#define ARRAY_TOTAL_SIZE_LIMIT  FIX(IARRAY_TOTAL_SIZE_LIMIT)
#define INTERNAL_TIME_UNITS_PER_SECOND Internal_time_units_per_second


/* Random Chestnut, Gold Hill, Lucid extensions */
/* #define NNUM_EQ(a,b)		(num_eq(a, b) ? NIL : T)
   commented out  as strange */
#define RPLACB(a,b)		(RPLACA((a),M_CAR(b)),RPLACD((a),M_CDR(b)),(a))
#define NCONS_IF(a)		((a) ? ncons(a) : NIL)
#define NEQL(a,b)		(!EQL(a, b) ? T : NIL)
#define NEQ(a,b)		(((a) != (b)) ? T : NIL)
#define FILEP(a)	       (STREAMP(a) && (STREAM_STYPE(a) == FILE_STREAM))
#define WINDOWP(a)		SI_STORED_OBJECT_TYPEP(a, WINDOW_TYPE)
/* GCLISP extension. */
#define NAMED_STRUCTURE_P(a)	(STRUCTURE_OBJECT_P(a) ? \
				 SI_STRUCTURE_NAME(a) : NIL)

/* Perhaps to be open-coded in future (or past?) */
#define STRING                  string
#define SET                     SET_SYMBOL_VALUE

#define FOREIGN_TYPE(o) (FOREIGN_TYPE_P(o) ? o : get_foreign_type(o,T))
#define FOREIGN_TYPE2(o,e) (FOREIGN_TYPE_P(o) ? o : get_foreign_type(o,e))
