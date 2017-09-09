/* methcomb.h -- Stuff related to method combination.
 *
 * Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
 *
 *
 */

/******************************************************************************
 *
 * Functions used in the implementation of call-next-method and next-method-p.
 *
 *****************************************************************************/

#ifdef USE_PROTOTYPES

extern Object	call_next_method(int, ...);

#else

extern Object	call_next_method();

#endif

extern Object	make_call_next_method_safe();
extern Object	make_call_next_method();
extern Object	make_next_method_p();

extern Object	SI_effective_method_no_next_method();

/******************************************************************************
 *
 * Functions used in the expansion of define-method-combination-function.
 *
 *****************************************************************************/

extern Object	make_effective_method();
extern Object	sort_parsed_methods();
extern Object	update_effective_method();
extern Object	finalize_effective_method();

/******************************************************************************
 *
 * Accessors on effective method metaobjects.
 *
 * The primitive accessors are defined with the struct definition.
 *
 *****************************************************************************/

#define SI_EFFECTIVE_METHOD_METHOD(em, index) \
    SVREF(SI_EFFECTIVE_METHOD_METHOD_TABLE(em), index)

#define EFFECTIVE_METHOD_KEYS(em)	SI_EFFECTIVE_METHOD_KEYS(em)

/******************************************************************************
 *
 * Encoded lambda lists
 *
 * Macros for examining an encoded lambda-list structure.
 *
 *****************************************************************************/

#if (256 <= SI_CALL_ARGUMENTS_LIMIT)
#  include "CALL_ARGUMENTS_LIMIT is too big."
#endif

/* An encoded lambda-list is a CONS cell, with the CAR being a fixnum that
 * encodes information about the lambda-list-keywords appearing in the
 * lambda-list and the CDR being a list of the mentioned keyword specifiers.
 *
 * SI_MAKE_ENCODED_LL(e, keys)
 * SI_ENCODED_LL_ENCODING(e)
 * SI_ENCODED_LL_KEYS(e)
 *   Provide an additional level of abstraction from the basic CONS cell.
 */

#define SI_MAKE_ENCODED_LL(e, keys)	cons(e, keys)
#define SI_ENCODED_LL_ENCODING(x)	M_CAR(x)
#define SI_ENCODED_LL_KEYS(x)		M_CDR(x)

/* Encoding masks
 *
 * These masks indicate bit fields within the encoded information which
 * correspond the various pieces of information.  They are used by the macros
 * which extract the information from the encoding.
 */

#define SI_ENCODED_LL_REQUIRED_MASK		0xFF
#define SI_ENCODED_LL_REQUIRED_SHIFT		0
#define SI_ENCODED_LL_POSITIONAL_MASK		0xFF
#define SI_ENCODED_LL_POSITIONAL_SHIFT		8
#define SI_ENCODED_LL_NON_POSITIONAL_MASK	FIX(0x10000)
#define SI_ENCODED_LL_KEY_MASK			FIX(0x20000)
#define SI_ENCODED_LL_ALWKY_MASK		FIX(0x40000)

#define SI_ENCODED_LL_EXTRACT_ARG_COUNT(e, shift, mask) \
    ((IFIX(e) >> shift) & mask)

/* Number of required arguments. */
#define SI_ENCODED_LL_REQUIRED(e) \
    SI_ENCODED_LL_EXTRACT_ARG_COUNT(e, \
				    SI_ENCODED_LL_REQUIRED_SHIFT, \
				    SI_ENCODED_LL_REQUIRED_MASK)

/* Number of positional arguments. */
#define SI_ENCODED_LL_POSITIONAL(e) \
    SI_ENCODED_LL_EXTRACT_ARG_COUNT(e, \
				    SI_ENCODED_LL_POSITIONAL_SHIFT, \
				    SI_ENCODED_LL_POSITIONAL_MASK)

/* True if non-positional arguments are permitted, ie. either &REST or &KEY
 * appeared in the lambda-list.
 */
#define SI_ENCODED_LL_NON_POSITIONAL_P(e) \
    !FIXNUM_ZEROP(FIXNUM_LOGAND(e,SI_ENCODED_LL_NON_POSITIONAL_MASK))

/* True if the non-positional arguments are keyword arguments, ie. &KEY
 * appeared in the lambda-list.  This is never true if
 * encoded-lambda-list-non-positional-p is false. 
 */
#define SI_ENCODED_LL_KEYP(e) \
    !FIXNUM_ZEROP(FIXNUM_LOGAND(e,SI_ENCODED_LL_KEY_MASK))

/* True if unmentioned keywords are permitted, ie. &ALLOW-OTHER-KEYS appeared
 * in the lambda-list.  This is never true if encoded-lambda-list-keyp is
 * false. 
 */
#define SI_ENCODED_LL_ALWKYP(e) \
    !FIXNUM_ZEROP(FIXNUM_LOGAND(e,SI_ENCODED_LL_ALWKY_MASK))

/******************************************************************************
 *
 * Lambda-list info for Effective_methods.
 *
 * These functions all access the encoded lambda-list information in the
 * argument-info slot of the effective-method.
 *
 *****************************************************************************/

#define EFFECTIVE_METHOD_REQUIRED(em) \
    FIX(SI_ENCODED_LL_REQUIRED(SI_EFFECTIVE_METHOD_ARGUMENT_INFO(em)))

#define EFFECTIVE_METHOD_POSITIONAL(em)	\
    FIX(SI_ENCODED_LL_POSITIONAL(SI_EFFECTIVE_METHOD_ARGUMENT_INFO(em)))

#define EFFECTIVE_METHOD_RESTP(em) \
    SI_ENCODED_LL_NON_POSITIONAL_P(SI_EFFECTIVE_METHOD_ARGUMENT_INFO(em))

#define EFFECTIVE_METHOD_KEYP(em) \
    SI_ENCODED_LL_KEYP(SI_EFFECTIVE_METHOD_ARGUMENT_INFO(em))

#define EFFECTIVE_METHOD_ALWKYP(em) \
    SI_ENCODED_LL_ALWKYP(SI_EFFECTIVE_METHOD_ARGUMENT_INFO(em))

/******************************************************************************
 *
 * Getting the keyword permutation vector for a method.
 *
 * The method is specified by its index into the effective method.
 * This macro assumes that the key table slot has already been verified to
 * contain a key table rather than Nil.
 *
 *****************************************************************************/

#define EFFECTIVE_METHOD_KEYWORD_PERMUTATION(em, index)	\
    SVREF(SI_EFFECTIVE_METHOD_KEY_TABLE(em), index)

/******************************************************************************
 *
 * Invoking a method from a Effective_method.
 *
 *****************************************************************************/

/* This macro evaluates the em and index arguments more than once. */
#define EFFECTIVE_METHOD_CALL(em, index, frame, argq) \
    SI_CALL_METHOD(SI_EFFECTIVE_METHOD_METHOD(em, index),em,index,frame,argq)

/******************************************************************************
 *
 * Invoking a method.
 *
 *****************************************************************************/

#define SI_CALL_METHOD(method, em, index, frame, argq) \
    (SI_METHOD_ENTRY(SI_Called_function = method))(em, index, frame, argq)

/******************************************************************************
 *
 * Next method handling.
 *
 *****************************************************************************/

/* Predicate which returns true if a next-method is available. */
#define SI_EFFECTIVE_METHOD_NEXT_METHOD_P(em, index) \
    SBITP_1(SI_EFFECTIVE_METHOD_NEXT_METHOD_TABLE(em), index)

/* The name that appears in translated code. */
#define NEXT_METHOD_P(em, index) \
    SI_EFFECTIVE_METHOD_NEXT_METHOD_P(em, index)

/* Calling the next method, when it is available.
 * This macro evaluates the em and index arguments more than once.
 *
 * *** Using effective_method_call here may not be best, since it evaluates its
 * *** index argument more than once, meaning that the Fixadd1 gets executed 
 * *** multiple times.
 */
#define CALL_NEXT_METHOD(em, index, frame, argq)		\
    (SI_EFFECTIVE_METHOD_NEXT_METHOD_P(em, index) ?		\
     EFFECTIVE_METHOD_CALL(em, FIXNUM_ADD1(index), frame, argq) : \
     SI_effective_method_no_next_method(em, index, frame, argq))

