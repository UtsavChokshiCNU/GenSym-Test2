/*
 * uconfig.h - library configuration user include file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#ifndef UCONFIG_DOT_H
#define UCONFIG_DOT_H

/***************************************************************************
 *
 * DEFAULTS 
 *
 **************************************************************************/


/* 
 * jh, 4/6/95.  Gensym fix to excise Lisp reader and other unneeded facilities
 * from GSI.
 *
 * binghe, 4/18/2003.  GENSYMCID-1002 reports that GSI actualy need BIGNUMs, so
 * UC_ENSURE__BIGNUMS was removed from following list.
 */
#ifdef GSI_TRANS
#  define UC_ENSURE__READER                  0
#  define UC_ENSURE__PACKAGES                0
#  define UC_ENSURE__STRUCTURES              0
#  define UC_ENSURE__STANDARD_ERROR_HANDLING 0
#else
#  define UC_ENSURE__READER                  1 
#  define UC_ENSURE__PACKAGES                1
#  define UC_ENSURE__STRUCTURES              1
#  define UC_ENSURE__STANDARD_ERROR_HANDLING 1
#endif

#ifndef UC_ENSURE__READER
#define UC_ENSURE__READER   1 
#endif 

#ifndef UC_ENSURE__BIGNUMS
#define UC_ENSURE__BIGNUMS   1
#endif

#ifndef UC_ENSURE__PACKAGES
#define UC_ENSURE__PACKAGES   1
#endif 

#ifndef UC_ENSURE__STRUCTURES
#define UC_ENSURE__STRUCTURES   1
#endif 

/* if UC_ENSURE__STANDARD_SYMBOLS then RTL_driven initialization for
 * all standard symbols on startup phase;
 * otherwise application-driven initialization for required symbols only
 */
#ifndef UC_ENSURE__STANDARD_SYMBOLS
#define UC_ENSURE__STANDARD_SYMBOLS   0
#endif 

#ifndef UC_ENSURE__STANDARD_ERROR_HANDLING 
#define UC_ENSURE__STANDARD_ERROR_HANDLING   1
#endif 

#ifndef UC_ENSURE__GC
#  if SI_COPYING_COLLECTOR && SI_SEGMENTED_DYNAMIC_AREA && !(SI_VISIT_EXACTLY_ONCE &&                        SI_CONSES_HAVE_HEADERS)
     /* the only option that is available under this configuration
     is to disallow GC and perform explicit memory management
     An error message will be signaled at run-time when attempting
     to call (*SI_garbage_collect_ptr)() */
#    define UC_ENSURE__GC   0
#  else
#    define UC_ENSURE__GC   1
#  endif
#endif

/***************************************************************************
 *
 * RULES
 *
 **************************************************************************/

/* CLOS always requires full RTL environment */
#if SI_SUPPORT_CLOS
#undef UC_ENSURE__GC
#define  UC_ENSURE__GC 1
#undef UC_ENSURE__READER
#define  UC_ENSURE__READER 1
#undef UC_ENSURE__BIGNUMS
#define  UC_ENSURE__BIGNUMS 1
#undef UC_ENSURE__PACKAGES
#define  UC_ENSURE__PACKAGES 1
#undef UC_ENSURE__STRUCTURES
#define  UC_ENSURE__STRUCTURES 1
#undef UC_ENSURE__STANDARD_SYMBOLS
#define  UC_ENSURE__STANDARD_SYMBOLS 1
#undef UC_ENSURE__STANDARD_ERROR_HANDLING
#define  UC_ENSURE__STANDARD_ERROR_HANDLING 1
#endif

#if UC_ENSURE__READER != 0
#undef UC_ENSURE__PACKAGES
#define  UC_ENSURE__PACKAGES 1
#endif

/*
 * Gensym change (jh, 10/26/93) per Rick Harris.  Hardwired SI_UCONFIG_GC() to
 * set Gc_inhibit to T so that we get the memory model we need.  See
 * corresponding change in config.h
 */
#if UC_ENSURE__GC != 0
#if SI_COPYING_COLLECTOR && SI_SEGMENTED_DYNAMIC_AREA && !(SI_VISIT_EXACTLY_ONCE && SI_CONSES_HAVE_HEADERS)
/* this configuration can not support automatic copying GC */
#include "This configuration is for non-automatic GC only."
#endif
#define  SI_UCONFIG_GC()     SI_INIT_automatic_gc()
#else 
#define  SI_UCONFIG_GC()     {Gc_inhibit = T; Gc_silence = (SI_gc_silence_init ? T : NIL);}
/* #define  SI_UCONFIG_GC()     {Gc_inhibit = NIL; Gc_silence = NIL;} From RTL 32b3. */
#endif

#if UC_ENSURE__READER != 0
#define  SI_UCONFIG_READER()     SI_INIT_full_reader()
#define  SI_UCONFIG_LAMBDA_KEYWORDS()     SI_INIT_lambda_lists()
#else 
#define  SI_UCONFIG_READER()
#define  SI_UCONFIG_LAMBDA_KEYWORDS()    
#endif

#define  SI_UCONFIG_EVAL()   

#if UC_ENSURE__BIGNUMS != 0
#define  SI_UCONFIG_BIGNUMS()     SI_INIT_new_bignums()
#else 
#define  SI_UCONFIG_BIGNUMS()    
#endif

/* lazy and safe */
#if UC_ENSURE__PACKAGES != 0
#define  SI_UCONFIG_PACKAGES() SI_INIT_packages()
#else 
#define  SI_UCONFIG_PACKAGES()
#endif

/* in fact, it is lazy and safe */
#if UC_ENSURE__STRUCTURES != 0
#define  SI_UCONFIG_STRUCTURES() SI_INIT_structure_class()
#else 
#define  SI_UCONFIG_STRUCTURES()
#endif

/* it is not lazy */
#if UC_ENSURE__STANDARD_SYMBOLS != 0
#define  SI_UCONFIG_STANDARD_SYMBOLS() SI_initsyms(); SI_initfuns()
#else 
#define  SI_UCONFIG_STANDARD_SYMBOLS() 
#endif

/* it is not lazy */
#if UC_ENSURE__STANDARD_ERROR_HANDLING != 0
#define  SI_UCONFIG_STANDARD_ERROR_HANDLING() SI_INIT_error()
#else 
#define  SI_UCONFIG_STANDARD_ERROR_HANDLING()
#endif

/*
 * Dependencies. (informal specification)
 *
 * UC_ENSURE__READER: full-reader  arrays printer bignums structures
 * UC_ENSURE__STANDARD_SYMBOLS : UC_ENSURE__PACKAGES
 * usersyms() : package system setup
 * SI_initsyms() : package system setup
 * bignums: linked in by bignum-initialization code, reader.
            initialized by reader, initialization code, but
            not by fixnum overflow
 * CLOS SYSTEM: all flags ON
 * ... (update gradually)
 */

/****************************************************************************
 *
 * Initializers 
 *
 ****************************************************************************/

/* include the full lisp package functionality */
#define INCLUDE_LISP_PACKAGE \
 SI_DO_UCONFIG { \
     SI_INIT_RTL_CORE();\
     SI_initsyms();\
     SI_initfuns();\
     SI_UCONFIGS();\
     SI_INIT_error();\
     SI_INIT_lambda_lists();\
  } SI_END_UCONFIG

#define SI_INCLUDE_LISP_PACKAGE_SELECTIVELY \
 SI_DO_UCONFIG { \
     SI_INIT_RTL_CORE();\
     SI_UCONFIG_STANDARD_SYMBOLS();\
     SI_UCONFIGS();\
     SI_UCONFIG_STANDARD_ERROR_HANDLING();\
     SI_UCONFIG_LAMBDA_KEYWORDS();\
  } SI_END_UCONFIG

#define SI_UCONFIGS() \
     SI_UCONFIG_PACKAGES(); \
     SI_UCONFIG_READER();\
     SI_UCONFIG_BIGNUMS();\
     SI_UCONFIG_STRUCTURES()

/* 
 * jh, 4/4/95.  Gensym fix - previously, reader would always be present,
 * regardless of UC_ENSURE__READER.
 */
#if UC_ENSURE__READER == 0
#  define GENSYM_INIT_READER_MAYBE
#else
#  define GENSYM_INIT_READER_MAYBE SI_INIT_reader(), /* note the comma */
#endif

/* 
 * jh, 4/10/95.  Gensym fix - previously, standard error handling (including
 * calls to format!)  would always be present, regardless of
 * UC_ENSURE__STANDARD_ERROR_HANDLING.
 */
#if UC_ENSURE__STANDARD_ERROR_HANDLING == 0
#  define GENSYM_INIT_ERROR_MAYBE
#else
#  define GENSYM_INIT_ERROR_MAYBE SI_INIT_error(), /* note the comma */
#endif

/* 
 * jh, 4/11/95.  Gensym fix - previously, bignums would always be present, regardless of
 * UC_ENSURE__BIGNUMS.
 */
#if UC_ENSURE__BIGNUMS == 0
#  define GENSYM_INIT_BIGNUMS_MAYBE
#else
#  define GENSYM_INIT_BIGNUMS_MAYBE SI_INIT_new_bignums(), /* note the comma */
#endif

#define SI_DO_UCONFIG \
  void init_top_level(){\
  extern void init_heaps(),\
  SI_INIT_backquote(), \
  initsyms_top_level(),\
  SI_INIT_NIL(), SI_INIT_T(), SI_INIT_packages(),\
  SI_insert_T(), SI_initsyms(), SI_initfuns(), initfuns(),\
  SI_INIT_dynamic_heaps(), SI_INIT_automatic_gc(),\
  SI_INIT_evals(), SI_INIT_lambda_lists(), \
  GENSYM_INIT_READER_MAYBE \
  GENSYM_INIT_ERROR_MAYBE \
  GENSYM_INIT_BIGNUMS_MAYBE \
  SI_ctrlvars_ENSURE(),  SI_fptrs_ENSURE(), \
  SI_initgc_ENSURE(), SI_readinit_ENSURE(), \
  SI_structi_ENSURE(), SI_errors_ENSURE();

#define SI_END_UCONFIG \
    SI_INIT_numbers();\
    SI_INIT_streams();\
    SI_INIT_io();\
    SI_INIT_print();\
    SI_INIT_filesys();\
    SI_INIT_misc();\
    SI_INIT_evals(); \
    SI_INIT_dynamic_heaps();\
    SI_BOOT_CLOS();\
    SI_INIT_usersyms(); \
    initfuns();\
    SI_ENSURE_GLOBAL_INITIALIZERS(); \
    Random_state = make_random_state(NIL);\
    Initialization = 0;		/* finished initializing */\
 }

#ifdef vms
#define SI_ENSURE_GLOBAL_INITIALIZERS() \
  SI_ctrlvars_ENSURE(); \
  SI_fptrs_ENSURE(); \
  SI_initgc_ENSURE(); \
  SI_readinit_ENSURE(); \
  SI_structi_ENSURE(); \
  SI_errors_ENSURE()
#else
#define SI_ENSURE_GLOBAL_INITIALIZERS()  /* do not bother */
#endif

/* lazy    SI_INIT_structure_class();  Must follow SI_bootstrap_clos() */
/*    backquot_top_level();  defines TRUN::BACKQUOTE macro */
/*       SI_INIT_evals();  makes eval-specific globals. */

#define SI_INIT_RTL_CORE() \
    SI_INIT_TLS_BLOCK();\
    SI_UCONFIG_GC();\
    init_heaps();\
    SI_INIT_NIL();\
    SI_INIT_T(); \
    SI_INIT_WRAPPERS();\
    SI_INIT_packages_1();\
    SI_INIT_THREAD();\
    SI_INIT_LOCK()

/* place user symbols into the Static area */
#define SI_INIT_usersyms() \
if (TRUE)\
{   Declare_area(a); \
    SAVE_CURRENT_AREA(a); \
    SET_CURRENT_AREA(Static_area); \
    usersyms(); \
    RESTORE_CURRENT_AREA(a); \
} else FALSE

#define SI_INIT_full_reader() \
if (TRUE)\
{ \
    SI_INIT_reader();\
    SI_INIT_backquote();\
} else FALSE 

#if SI_SUPPORT_CLOS 
#define SI_INIT_WRAPPERS()    SI_alloc_early_class_wrappers()
#else
#define SI_INIT_WRAPPERS() 
#endif

#if SI_SUPPORT_CLOS
#define SI_BOOT_CLOS() \
    SI_bootstrap_clos()
#else
#define SI_BOOT_CLOS() 
#endif

#endif 

/*  Delivery package */

/* don\'t UC_DELIVER\'it until it\'s deliverable ! */
#ifndef UC_DELIVERY
#define UC_DELIVERY 0
#endif 


#if UC_DELIVERY == 0

#define INCLUDE_LISP_PACKAGE_SELECTIVELY \
     SI_INCLUDE_LISP_PACKAGE_SELECTIVELY

#else  /* UC_DELIVERY == 1 */


/* drop packages ! */

#define STATIC_SYMBOL(x, y) (Object)*x
#define STATIC_PACKAGE(x)   FIX(1)
#define find_package(x) FIX(1)

#undef make_package
#define make_package(n,p,kn,v1,ku,v2) FIX(1)

#define rename_package(p,kn,v1) FIX(1)
#define defpackage_use_package(p,v1) FIX(1)

#undef SET_SYMBOL_VALUE_LOCATION
#define SET_SYMBOL_VALUE_LOCATION(x, y)

#undef SET_SYMBOL_FUNCTION
#define SET_SYMBOL_FUNCTION(x, y)

#undef NEW_SYMBOL
#define NEW_SYMBOL(x, y, z) UNBOUND

#define NEW_PACKAGE(x)
#define SET_PACKAGE(x)

#undef ADD_PACKAGE_NICKNAME
#define ADD_PACKAGE_NICKNAME(x, y)

#undef ADD_PACKAGE_USE
#define ADD_PACKAGE_USE(x, y)

#undef ADD_IMPORT
#define ADD_IMPORT(x, y, z)

#undef make_array
#define make_array SI_make_array_lite
extern Object SI_make_array_lite();

#define DEF_ID(x) Object x = (Object) & x
#define INCLUDE_LISP_PACKAGE_SELECTIVELY \
DEF_ID(Kdynamic); \
DEF_ID(Qlist) ; \
DEF_ID(Qsingle_float) ; \
DEF_ID(Qdouble_float) ; \
DEF_ID(Kstatic) ; \
DEF_ID(Kelement_type); \
DEF_ID(Kinitial_element); \
  void init_top_level(){\
  extern void init_heaps();\
  extern void SI_INIT_dynamic_heaps();\
  \
  SI_INIT_TLS_BLOCK();\
  init_heaps();\
  SI_INIT_dynamic_heaps();\
  Kelement_type =   STATIC_SYMBOL("E",NIL); \
  Kinitial_element =   STATIC_SYMBOL("I",NIL); \
} 

#endif /* UC_DELIVERY == 1 */

