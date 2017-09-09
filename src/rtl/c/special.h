/*
 * special.h -  Chestnut Run-Time Library entry for special variable definitions
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  26 Jun 2009
 *
 * Copyright (c) 2009 Versata Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *

   Note: Add new items into this file will result in correspond modifications on
   Chestnut Translator's Lisp side (TUTIL::*SPECIAL-VARIABLE-NAMES* in map-name.lisp)
   -- binghe, 2009/5/11
 */

#ifndef SI_SPECIAL_DOT_H
#define SI_SPECIAL_DOT_H

#ifndef SI_HAVE_OBJECT_DEFINED
# if SI_SUPPORT_THREAD
    typedef Gensym_Ulong Object;
# else
    typedef void *Object;
# endif
#endif

#if SI_SUPPORT_THREAD

#define INCLUDE_SI_SPECIAL(type, postfix) \
	type Current_print_level ## _ ## postfix; \
	type Debug_io ## _ ## postfix; \
	type Error_output ## _ ## postfix; \
	type Load_pathname ## _ ## postfix; \
	type Load_print ## _ ## postfix; \
	type Load_truename ## _ ## postfix; \
	type Load_verbose ## _ ## postfix; \
	type Package ## _ ## postfix; \
	type Print_array ## _ ## postfix; \
	type Print_base ## _ ## postfix; \
	type Print_case ## _ ## postfix; \
	type Print_circle ## _ ## postfix; \
	type Print_escape ## _ ## postfix; \
	type Print_gensym ## _ ## postfix; \
	type Print_length ## _ ## postfix; \
	type Print_level ## _ ## postfix; \
	type Print_lines ## _ ## postfix; \
	type Print_miser_width ## _ ## postfix; \
	type Print_pprint_dispatch ## _ ## postfix; \
	type Print_pretty ## _ ## postfix; \
	type Print_radix ## _ ## postfix; \
	type Print_readably ## _ ## postfix; \
	type Print_right_margin ## _ ## postfix; \
	type Read_base ## _ ## postfix; \
	type Read_default_float_format ## _ ## postfix; \
	type SI_Format_stream ## _ ## postfix; \
	type Standard_input ## _ ## postfix; \
	type Standard_output ## _ ## postfix; \
	type Terminal_io ## _ ## postfix; \
	type Gensym_error_message_buffer ## _ ## postfix

#ifdef RTL_BOOTSTRAP

struct SI_Tls_data {
    INCLUDE_SI_SPECIAL(Object, LOCAL);
};

struct SI_Tls_count {
    INCLUDE_SI_SPECIAL(short, COUNT);
};

#endif /* RTL_BOOTSTRAP */

extern TLS struct SI_Tls_data* SI_Special_data;
extern TLS struct SI_Tls_count* SI_Special_count;

#if SI_USE_PROTOTYPES

extern struct SI_Tls_data* SI_init_tls_data(SI_Size_type size);
extern struct SI_Tls_count* SI_init_tls_count(SI_Size_type size);

#else

extern struct SI_Tls_data* SI_init_tls_data();
extern struct SI_Tls_count* SI_init_tls_count();

#endif

#define SI_INIT_TLS_DATA() SI_Special_data = \
	SI_init_tls_data(sizeof(struct SI_Tls_data))

#define SI_INIT_TLS_COUNT() SI_Special_count = \
	SI_init_tls_count(sizeof(struct SI_Tls_count))

#define SI_INIT_TLS_BLOCK() \
	SI_INIT_TLS_DATA(); \
	SI_INIT_TLS_COUNT()

#define DEFINE_VARIABLE(var) \
	Object var ## _GLOBAL = UNBOUND

#define DEFINE_VARIABLE_WITH_SYMBOL(var, quotedVar) \
	volatile Object var ## _GLOBAL = UNBOUND; \
	Object quotedVar = UNBOUND

#define DECLARE_VARIABLE(var) \
	extern Object var ## _GLOBAL

#define DECLARE_VARIABLE_WITH_SYMBOL(var, quotedVar) \
	extern volatile Object var ## _GLOBAL; \
	extern Object quotedVar

#define DEFINE_STATIC_VARIABLE(type, var, value) \
	static type var ## _GLOBAL = value

#define SPECIAL_VALUE(var) \
	*(SI_Special_count->var ## _COUNT ? &SI_Special_data->var ## _LOCAL : &var ## _GLOBAL)

#define STATIC_VALUE(var) var ## _GLOBAL
#define GLOBAL_VALUE(var) var ## _GLOBAL
#define LOCAL_VALUE(var) SI_Special_data->var ## _LOCAL

#define Current_print_level SPECIAL_VALUE(Current_print_level)
#define Debug_io SPECIAL_VALUE(Debug_io)
#define Error_output SPECIAL_VALUE(Error_output)
#define Load_pathname SPECIAL_VALUE(Load_pathname)
#define Load_print SPECIAL_VALUE(Load_print)
#define Load_truename SPECIAL_VALUE(Load_truename)
#define Load_verbose SPECIAL_VALUE(Load_verbose)
#define Package SPECIAL_VALUE(Package)
#define Print_array SPECIAL_VALUE(Print_array)
#define Print_base SPECIAL_VALUE(Print_base)
#define Print_case SPECIAL_VALUE(Print_case)
#define Print_circle SPECIAL_VALUE(Print_circle)
#define Print_escape SPECIAL_VALUE(Print_escape)
#define Print_gensym SPECIAL_VALUE(Print_gensym)
#define Print_length SPECIAL_VALUE(Print_length)
#define Print_level SPECIAL_VALUE(Print_level)
#define Print_lines SPECIAL_VALUE(Print_lines)
#define Print_miser_width SPECIAL_VALUE(Print_miser_width)
#define Print_pprint_dispatch SPECIAL_VALUE(Print_pprint_dispatch)
#define Print_pretty SPECIAL_VALUE(Print_pretty)
#define Print_radix SPECIAL_VALUE(Print_radix)
#define Print_readably SPECIAL_VALUE(Print_readably)
#define Print_right_margin SPECIAL_VALUE(Print_right_margin)
#define Read_base SPECIAL_VALUE(Read_base)
#define Read_default_float_format SPECIAL_VALUE(Read_default_float_format)
#define SI_Format_stream SPECIAL_VALUE(SI_Format_stream)
#define Standard_input SPECIAL_VALUE(Standard_input)
#define Standard_output SPECIAL_VALUE(Standard_output)
#define Terminal_io SPECIAL_VALUE(Terminal_io)

/* Special variables defined on G2 lisp side */
#define Gensym_error_message_buffer SPECIAL_VALUE(Gensym_error_message_buffer)

#else

#define DEFINE_VARIABLE(var) Object var = UNBOUND

#define DEFINE_VARIABLE_WITH_SYMBOL(var, quotedVar) \
        Object var = UNBOUND; \
        Object quotedVar = UNBOUND

#define DECLARE_VARIABLE(var) extern Object var

#define DECLARE_VARIABLE_WITH_SYMBOL(var, quotedVar) \
        extern Object var; \
        extern Object quotedVar

#define DEFINE_STATIC_VARIABLE(type, var, value) static type var = value
#define SPECIAL_VALUE(var) var
#define STATIC_VALUE(var) var
#define GLOBAL_VALUE(var) var
#define LOCAL_VALUE(var) var
#define SI_INIT_TLS_BLOCK() do {} while(0)

#endif /* SI_SUPPORT_THREAD */
#endif /* SI_SPECIAL_DOT_H */
