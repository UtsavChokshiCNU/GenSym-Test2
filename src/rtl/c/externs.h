/****** All externs included by runtime.h or kernel.h, ******
 ****** except for those related to NIL and T; and     ******
 ****** Stack and Values_count.                        ******/

/*** object.h ***/

extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;

#ifdef USE_PROTOTYPES

extern Object SI_cons_with_gc(Object x, Object y);
extern Object SI_cons(void);

#else

extern Object SI_cons_with_gc();
extern Object SI_cons();

#endif

extern SI_Primitive_vector_constant SI_Stack_vector_header;

/* do_..aref.. should be renamed to SI_..row_aref..   */

#ifdef USE_PROTOTYPES

extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);

#else

extern Object do_aref_1();
extern Object do_setf_aref();

#endif

#ifdef KLUDGE_DOUBLE_FLOATS

extern Double_float_kludge_union SI_Double_float_kludge_temp; 
extern Double_float_kludge_union SI_Double_float_kludge_temp1; 

#endif

#ifdef SI_RUNTIME_INTERNAL

extern Object SI_alloc_bignum();

#endif

extern Object SI_symbol_field();
extern Object SI_set_symbol_field();

#ifdef SI_RUNTIME_INTERNAL

extern char *Initial_symbol_names[];

extern void INIT_STATIC_PACKAGE();

#endif

/* externals  for append2, nconc2 */

#ifdef USE_PROTOTYPES

extern Object append2(Object list1, Object list2);
extern Object nconc2(Object list1, Object list2);

#else

extern Object append2();
extern Object nconc2();

#endif

#ifdef USE_PROTOTYPES

extern SI_Long  integer_to_long(Object n);
extern SI_Ulong integer_to_unsigned_long(Object n);

#else

extern SI_Long  integer_to_long();
extern SI_Ulong integer_to_unsigned_long();

#endif

#ifdef USE_PROTOTYPES

extern char *SI_istring(Object o);

#else

extern char *SI_istring();

#endif

/**************************************************************************
*
* Constant allocation support
*
***************************************************************************/

#ifdef USE_PROTOTYPES

extern Object STATIC_FUNCTION1(Object (*entry) (/* ??? */), 
			       Object env, 
			       long variadicp, long nreq, long npos);
extern Object STATIC_SYMBOL(char *name, Object pkg);
extern Object STATIC_PACKAGE(char *name);
extern Object STATIC_CONS(Object o1, Object o2);
extern Object STATIC_STRING(char *s);
extern Object STATIC_LIST(long n, ...);
extern Object STATIC_LIST_STAR(long n, ...);
extern Object STATIC_FLOAT(DOUBLE d);
extern Object STATIC_RATIO(Object numerator, Object denominator);
extern Object STATIC_POSITIVE_BIGNUM(SI_Dimension length);
extern Object STATIC_NEGATIVE_BIGNUM(SI_Dimension length);
extern Object STATIC_GENERAL_ARRAY(long n, ...);
extern Object STATIC_ARRAY(Object type, long n, ...);
extern void   SET_BIGNUM_DIGIT(Object bignum, SI_Dimension number, 
			       SI_Long high, SI_Long low);

#else

extern Object STATIC_FUNCTION1();
extern Object STATIC_SYMBOL();
extern Object STATIC_PACKAGE(); 
extern Object STATIC_CONS();
extern Object STATIC_STRING();
extern Object STATIC_LIST();
extern Object STATIC_LIST_STAR();
extern Object STATIC_FLOAT();
extern Object STATIC_RATIO();
extern Object STATIC_POSITIVE_BIGNUM();
extern Object STATIC_NEGATIVE_BIGNUM();
extern Object STATIC_GENERAL_ARRAY();
extern Object STATIC_ARRAY();
extern void   SET_BIGNUM_DIGIT();

#endif

/*** values.h ***/

extern TLS Object Values[];

#if SI_SUPPORT_SF

extern TLS Object SI_First_value;

extern Object list_values(Object x); /* Should be SI_ */

#endif

#ifdef RETURN_MULTIPLE_VALUES

extern void SI_save_values();
extern void SI_save_more_values();
extern Object SI_restore_values();

#endif

/*** core.h ***/

extern void SI_set_symbol_value_location(Object symbol, Object *address);
extern void SI_set_symbol_function_location();

extern Object UNIQUE_TAG();

#if SI_SUPPORT_SF

extern Object SI_obtain_rest_list();

extern Object SI_make_rest_arg();

extern Object SI_keyword_arg_p();

extern TLS Object SI_Called_function;

#endif

extern TLS SI_Special_frame *SI_Special_stack;

extern SI_Stack_item *Lisp_stack;

extern TLS SI_Frontier_frame *SI_Frontier_stack;

extern TLS SI_Catch_frame *SI_Catch_stack;

extern long SI_gc_count;
extern void restore_frontier();	/* should be SI_ */

extern TLS SI_Area *Current_area;	/* Ought to have SI_ prefix */

/* These will appear in translated code, as arguments to the
   SET_CURRENT_AREA macro. */

extern SI_Area Static_area, Dynamic_area;
extern SI_Area Local_area;

extern Object SI_throw(/* Object tag, firstval */);

extern long SI_re_throw();

/* PROGV support */

extern void SI_progv_save_bindings();
extern void SI_progv_do_bindings();
extern void SI_progv_restore_bindings();

/***************************************************************************
 *
 * Function call support
 *
 **************************************************************************/

extern Object SI_internal_funcall();
extern Object SI_mv_funcall();

/***************************************************************************
 *
 * GC protection
 *
 **************************************************************************/

#ifdef SI_SUPPORT_SF

extern void SI_add_external_root();

#endif

/***************************************************************************
 *
 * Error Reporting
 *
 **************************************************************************/

#ifdef USE_PROTOTYPES

extern Object (*SI_error_fptr) (int n, char *lstr, ...);
/** errorn is defined in ifuns.h or in c-ifuns.h **/
extern Object (*SI_cerror_fptr)(int n, char *cstr,char *estr, ...);
extern Object (*SI_warn_fptr)  (int n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) (/* int n, char *lstr, va_dcl va_alist*/);
/** errorn is defined in ifuns.h or in c-ifuns.h **/
extern Object (*SI_cerror_fptr)(/* int n, char *cstr,char *estr, va_dcl va_alist*/);
extern Object (*SI_warn_fptr)  (/* int n, char *lstr, va_dcl va_alist*/);

#endif

/***************************************************************************
 *
 * Miscellaneous
 *
 **************************************************************************/

/* Externs for "virtual registers" used as temporaries by various macros.
   (All ought to have SI_ prefix ...) */

extern TLS UCHAR Tempu;
extern TLS Object Temp1;
extern TLS Object T_temp;
extern TLS SI_Ulong UL_temp;	/* FLI */
extern TLS SI_Long L_temp;	/* FLI */
extern TLS SI_Long L_temp1;	/* FLI */

/* True iff we're doing runtime-specific initialization */

extern short	Initialization;	/* should be SI_ */

/* for inlined numeric macro */
extern Object SI_do_math2();

/*** instance.h ***/

/******************************************************************************
 *
 * Structures (defstructs)
 *
 *****************************************************************************/

#if (SI_SUPPORT_SF || defined(SI_RUNTIME_INTERNAL))
extern Object SI_make_structure();
#endif

extern Object make_structure_class(Object,Object,Object,Object,Object,Object);

/******************************************************************************
 *
 * Functions
 *
 *****************************************************************************/

#if SI_OBJECT_INITIALIZERS_WORK
#if SI_SUPPORT_CLOS
extern struct SI_Function_slot_vector_struct SI_Function_slot_vector;
#endif
#endif

/******************************************************************************
 *
 * Hash-tables
 *
 *****************************************************************************/

#ifdef SI_RUNTIME_INTERNAL

extern Object SI_gc_genobj;     /* used to detect relocating gc */

#endif /* SI_RUNTIME_INTERNAL */


/*** inline.h ***/

extern Object MAKE_FUNCTION();

#ifdef USE_PROTOTYPES

extern char *SI_string_base(Object);
extern Object ncons(Object);
extern Object nth_inline(Object,Object);
extern Object m_nthcdr(long n, Object list);

#else

extern char *SI_string_base();
extern Object ncons();
extern Object nth_inline();
extern Object m_nthcdr();

#endif

/*** specific.h ***/

#ifdef USE_PROTOTYPES
extern void *SI_array_contents(Object array);
#else
extern void *SI_array_contents();
#endif

#ifndef SI_RUNTIME_INTERNAL
extern Object unsigned_long_to_bignum();
extern Object istring_to_string();
#endif
extern Object istring_to_string_or_nil();

/*** lisplib.h ***/

#include "lisplib.h"

/*** ffi.h ***/

extern Object Qforeign_type;
extern Object Qprimitive_foreign_type;
extern Object Qpointer_foreign_type;
extern Object Qarray_foreign_type;
extern Object Qstructure_foreign_type;

extern Object make_foreign_pointer_internal();


#if SI_SUPPORT_CLOS
/* include "clos.h" */
#endif

/*** smcompat.h ***/

extern TLS Object SI_First_value;	/* ugh */

extern Object NEW_PACKAGE(char *name);
extern Object SET_PACKAGE(char *name);
extern void   SI_ADD_PACKAGE_NICKNAME(/* Object *package, char *name */);
extern Object SI_NEW_SYMBOL(/* Object *package, char *name, int externalp */);
extern void   SI_ADD_SHADOW(/* Object *package, Object symbol*/);
extern void   SI_ADD_PACKAGE_USE(/* Object *package,Object *package_to_use */);
extern void   SI_ADD_IMPORT(/*Object *package,Object symbol,int externalp*/);

extern Object SI_ENSURE_GLOBAL(/*Object *loc,Object *pkgp,char *name,int e*/);

extern Object SI_ENSURE_GLOBAL_CONSTANT
              (/*Object val,Object *pkgp,char *name,int e*/);


#if !SI_SUPPORT_CLOS
/* #include "sdefs.h" */
#include "ifuns.h"
#else
#include "c-sdefs.h"
#include "c-ifuns.h"
#endif

#include "initvars.h"

#ifdef SI_RUNTIME_INTERNAL

/*** runint.h ***/

/* Externs (in no particular order) */

#ifdef USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, int align, 
		       enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object g2rtl_SI_alloc_primitive_vector(SI_Dimension numelems, 
					enum SI_gcls etype);

extern void SI_shorten_primitive_vector(Object pv, long int len);

extern Object SI_fill_primitive_vector(Object pv, Object init);

extern Object iname_char(char *iname);
extern Object make_duplicate_string(Object oldstring);
extern Object imake_duplicate_string(char *oldstring);
extern char *strupr(char *str);
extern char *strlwr(char *str);
extern Object make_canonical_rational(long int n, long int d);
extern Object do_aref_1(Object arr, long int i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object sequence_type_p(Object rtype);
extern Object ifind_symbol(char *name, Object pkg);
extern char *isymbol_name(Object sym);
extern Object get_next_node(enum SI_type nodetype);
extern Object istring_to_string(char *istring);
extern Object chase_input_stream(Object stream);
extern Object chase_output_stream(Object stream);
extern Object chase_write_stream(Object stream);
extern Object make_complex(Object r, Object i);
extern Object ifind_package(char *name);
extern Object iintern(char *name, Object pkg);

extern Object interaction_stream_p(Object x);

extern void SI_type_error(Object datum, Object expected_type);
extern void SI_undefined_function_error(Object name);
extern void SI_fatal_error(char *lstr, ...);

#else

extern Object SI_alloc();
extern Object SI_alloc_primitive_vector();

extern void SI_shorten_primitive_vector();

extern Object SI_fill_primitive_vector();

extern Object iname_char();
extern Object make_duplicate_string();
extern Object imake_duplicate_string();
extern char *strupr();
extern char *strlwr();
extern Object make_canonical_rational();
extern Object do_aref_1();
extern Object do_setf_aref();
extern Object sequence_type_p();
extern Object ifind_symbol();
extern char *isymbol_name();
extern Object get_next_node();
extern Object istring_to_string();
extern Object chase_input_stream();
extern Object chase_output_stream();
extern Object chase_write_stream();
extern Object make_complex();
extern Object ifind_package();
extern Object iintern();

extern Object interaction_stream_p();

extern void SI_type_error();
extern void SI_undefined_function_error();
extern void SI_fatal_error();

#endif

extern Object fill_symbol_name();
extern Object do_list_star_n();
extern Object dolistn();
extern Object do_intern();
extern Object do_find_symbol();
extern int garbage_collect();
extern long get_system_time();
extern Object do_read_run();
extern Object do_read_char();
extern Object do_formatr();
extern Object apply_format_nil();

extern char Default_path[];

/* Stuff related to defstruct. */
extern void SI_INIT_structure_class();
extern Object SI_find_structure_header();
extern Object SI_find_structure_print_function();
extern Object SI_structure_type_specifier_p();
extern int SI_structure_typep();
extern int SI_structure_subtypep();


extern void SI_clear_whitespace_input();
extern void SI_y_or_n_p_aux();
extern Object SI_y_or_n_p_query();
extern Object SI_yes_or_no_p_query();
extern Object SI_delete_if();
extern SI_Area *SI_area_name_to_area();
extern Object   SI_STORED_NUMBER_P();
extern Object   SI_make_static_array();
extern SI_Long SI_igcd();
extern void    SI_INIT_read();
extern Object SI_array_row_major_index_aux();

extern Object SI_fp_eql_1;
extern Object SI_fp_eq_1;
extern Object SI_fp_eq_2;

#endif

/*** bignum.h ***/

#ifdef SI_RUNTIME_INTERNAL

#include "bigext.h"

#endif
