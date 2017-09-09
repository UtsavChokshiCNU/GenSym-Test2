/*
 * core.h - Lisp-to-C support for core language language constructs
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 * Special forms, closures, GC protection, etc.
 */

/* Some useful C macros */
#define ABS(a)          ((a) <  0L ? -(a) : (a))
#ifndef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#endif
#define FOREVER for(;;)

#ifndef TRUE
#define TRUE 1L
#endif

#ifndef FALSE
#define FALSE 0L
#endif

/* True if calls to error & friends should use conditions.
 * False if they should pass format strings and format arguments.
 */
#define SI_SIGNAL_CONDITIONS	FALSE

/* The following supports DEFVAR, DEFPARAMETER, and DEFCONSTANT */

#if 1
#define SET_SYMBOL_VALUE_LOCATION(sym, var) \
    SI_set_symbol_value_location(sym, &(var))
#define SET_SYMBOL_FUNCTION_LOCATION(sym, var) \
    SI_set_symbol_function_location(sym, &(var))
#else
#define SET_SYMBOL_VALUE_LOCATION(sym, var) 
#define SET_SYMBOL_FUNCTION_LOCATION(sym, var) 
#endif


/***************************************************************************
 *
 * Argument processing
 *
 **************************************************************************/

#define SUPPLIEDP(v)	 	((v) != _)

#if SI_SUPPORT_SF

#define SI_COUNTER_VAR n /* as in:  Object foo (n, va_list) ... */

#define XDeclare_varargs \
    va_list SI_ap; \
    long SI_nargs, SI_arg_position, SI_rest_position = -1L; \
    Object SI_keyword, SI_value; \
    Object *SI_rest_var = NULL /* Initializer unnecessary, but silences lint */

#define BEGIN_ARGS(nargs) \
    SI_va_start(SI_ap,SI_COUNTER_VAR); \
    SI_nargs = nargs; /* va_arg(SI_ap, int) */ \
    SI_arg_position = 0L

/* Incompatible with current runtime's REQUIRED_ARG() macro */
#define XREQUIRED_ARG(v) /* This is unnecessary */ \
    (++SI_arg_position, (v) = va_arg(SI_ap, Object))

#define REQUIRED_ARGS_0()

#define REQUIRED_ARGS_1(v1) XREQUIRED_ARG(v1)

#define REQUIRED_ARGS_2(v1, v2) \
    (SI_arg_position += 2L, \
     (v1) = va_arg(SI_ap, Object), \
     (v2) = va_arg(SI_ap, Object))

#define REQUIRED_ARGS_3(v1, v2, v3) \
    (SI_arg_position += 3L, \
     (v1) = va_arg(SI_ap, Object), \
     (v2) = va_arg(SI_ap, Object), \
     (v3) = va_arg(SI_ap, Object))

#define REQUIRED_ARGS_4(v1, v2, v3, v4) \
    (SI_arg_position += 4L, \
     (v1) = va_arg(SI_ap, Object), \
     (v2) = va_arg(SI_ap, Object), \
     (v3) = va_arg(SI_ap, Object), \
     (v4) = va_arg(SI_ap, Object))

#define REQUIRED_ARGS_5(v1, v2, v3, v4, v5) \
    (SI_arg_position += 5L, \
     (v1) = va_arg(SI_ap, Object), \
     (v2) = va_arg(SI_ap, Object), \
     (v3) = va_arg(SI_ap, Object), \
     (v4) = va_arg(SI_ap, Object), \
     (v5) = va_arg(SI_ap, Object))



/* Incompatible with current runtime's OPTIONAL_ARG() macro */
#define XOPTIONAL_ARG(v) \
    ((v) = (SI_arg_position < SI_nargs ? \
	    (++SI_arg_position, va_arg(SI_ap, Object)) : \
	    _))

#define OPTIONAL_ARGS_0()

#define OPTIONAL_ARGS_1(v1) XOPTIONAL_ARG(v1)

#define OPTIONAL_ARGS_2(v1, v2) \
    (XOPTIONAL_ARG(v1), XOPTIONAL_ARG(v2))    /* Suboptimal */

#define OPTIONAL_ARGS_3(v1, v2, v3) \
    (OPTIONAL_ARG(v1), OPTIONAL_ARGS_2(v2, v3))
/* etc. */

#define XREST_ARG(r) \
    (SI_rest_var = &r, SI_rest_position = SI_arg_position)

/* Note: if there is no REST_ARG, then Sun's C compiler with the -O
   compiler option can optimize away the conditional, completely eliding
   the two STACK_PUSHes. */

#define BEGIN_KEYWORD_ARGS() \
    for (; SI_arg_position < SI_nargs; SI_arg_position += 2) { \
	SI_keyword = va_arg(SI_ap, Object); \
	SI_value = va_arg(SI_ap, Object); \
	if (SI_rest_position >= 0) { \
            STACK_PUSH(SI_keyword); \
	    STACK_PUSH(SI_value); \
	}

#define XKEYWORD_ARG(k, v) \
    if (SI_keyword == k) { \
	if (v == _) v = SI_value; \
	continue; \
    }

#define ALLOW_OTHER_KEYS()	/* Add error checking later */

#define KEYWORD_ARG_ALLOW_OTHER_KEYS(var) \
    KEYWORD_ARG(Qallow_other_keys, var)

#define KEYWORD_ARGS_0()

#define KEYWORD_ARGS_1(k1, v1) \
    v1 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_2(k1, v1, k2, v2) \
    v1 = v2 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_3(k1, v1, k2, v2, k3, v3) \
    v1 = v2 = v3 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_4(k1, v1, k2, v2, k3, v3, k4, v4) \
    v1 = v2 = v3 = v4 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_5(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5) \
    v1 = v2 = v3 = v4 = v5 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
        XKEYWORD_ARG(k5, v5); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_6(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5, k6, v6) \
    v1 = v2 = v3 = v4 = v5 = v6 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
        XKEYWORD_ARG(k5, v5); \
        XKEYWORD_ARG(k6, v6); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_7(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5, k6, v6, k7, v7) \
    v1 = v2 = v3 = v4 = v5 = v6 = v7 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
        XKEYWORD_ARG(k5, v5); \
        XKEYWORD_ARG(k6, v6); \
        XKEYWORD_ARG(k7, v7); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_8(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5, k6, v6, k7, v7, k8, v8) \
    v1 = v2 = v3 = v4 = v5 = v6 = v7 = v8 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
        XKEYWORD_ARG(k5, v5); \
        XKEYWORD_ARG(k6, v6); \
        XKEYWORD_ARG(k7, v7); \
        XKEYWORD_ARG(k8, v8); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_9(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5, k6, v6, k7, v7, k8, v8, k9, v9) \
    v1 = v2 = v3 = v4 = v5 = v6 = v7 = v8 = v9 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
        XKEYWORD_ARG(k5, v5); \
        XKEYWORD_ARG(k6, v6); \
        XKEYWORD_ARG(k7, v7); \
        XKEYWORD_ARG(k8, v8); \
        XKEYWORD_ARG(k9, v9); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_10(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5, k6, v6, k7, v7, k8, v8, k9, v9, k10, v10) \
    v1 = v2 = v3 = v4 = v5 = v6 = v7 = v8 = v9 = v10 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
        XKEYWORD_ARG(k5, v5); \
        XKEYWORD_ARG(k6, v6); \
        XKEYWORD_ARG(k7, v7); \
        XKEYWORD_ARG(k8, v8); \
        XKEYWORD_ARG(k9, v9); \
        XKEYWORD_ARG(k10, v10); \
    END_KEYWORD_ARGS()

#define KEYWORD_ARGS_11(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5, k6, v6, k7, v7, k8, v8, k9, v9, k10, v10, k11, v11) \
    v1 = v2 = v3 = v4 = v5 = v6 = v7 = v8 = v9 = v10 = v11 = _; \
    BEGIN_KEYWORD_ARGS(); \
        XKEYWORD_ARG(k1, v1); \
        XKEYWORD_ARG(k2, v2); \
        XKEYWORD_ARG(k3, v3); \
        XKEYWORD_ARG(k4, v4); \
        XKEYWORD_ARG(k5, v5); \
        XKEYWORD_ARG(k6, v6); \
        XKEYWORD_ARG(k7, v7); \
        XKEYWORD_ARG(k8, v8); \
        XKEYWORD_ARG(k9, v9); \
        XKEYWORD_ARG(k10, v10); \
        XKEYWORD_ARG(k11, v11); \
    END_KEYWORD_ARGS()

#define END_KEYWORD_ARGS()  }

/* Note: if there is no REST_ARG, then Sun's C compiler can optimize
   away the conditional, completely eliding the assignment of SI_rest_var
   and the call to SI_obtain_rest_list.  This happens even without the -O
   compiler option. */

#define END_ARGS() \
    if (SI_rest_position >= 0L) \
	*SI_rest_var = \
	    SI_obtain_rest_list(SI_rest_position, SI_arg_position, \
				SI_nargs, &SI_ap); \
    va_end(SI_ap)

/* Sandra's macros */

#define Declare_varargs \
    Declare_varargs_without_temp \
	, SI_va_temp SI_LINTUSE(SI_va_temp)

#define Declare_varargs_without_temp \
    register long SI_va_n, SI_va_i; \
    va_list SI_va_ap; \
    register Object *SI_va_args

#define INIT_ARGS() \
    SI_va_start(SI_va_ap,SI_COUNTER_VAR); \
    SI_va_n = n   /* Temporary perversion */ /* Sandra: va_arg(SI_va_ap,int) */

#define REQUIRED_ARG() \
    (--SI_va_n, va_arg(SI_va_ap,Object))

#define SAVE_ARGS() \
    SI_va_args = (Object *)Stack;          \
    Stack += SI_va_n;                      \
    for(SI_va_i = 0; SI_va_i < SI_va_n;)   \
        SI_va_args[SI_va_i++] = va_arg(SI_va_ap, Object);  \
    va_end(SI_va_ap)

#define OPTIONAL_ARG_P() \
    (SI_va_n > 0)

#define OPTIONAL_ARG() \
    (--SI_va_n, *SI_va_args++)

#define REST_ARG() \
    SI_make_rest_arg(SI_va_args, SI_va_n)

#define KEYWORD_ARG_P(k) \
    SI_keyword_arg_p(k, SI_va_args, SI_va_n) /* Fixnum or NIL */

#define KEYWORD_ARG(s) \
    (SI_va_temp = SI_va_args[IFIX(s)], s = T, SI_va_temp)


#define Declare_varargs_nonrelocating \
    register long SI_va_n; \
    va_list SI_va_ap

#define INIT_ARGS_nonrelocating() \
    SI_va_start(SI_va_ap,SI_COUNTER_VAR); \
    SI_va_n = n 

#define REQUIRED_ARG_nonrelocating() \
    (--SI_va_n, va_arg(SI_va_ap,Object))

#define OPTIONAL_ARG_P_nonrelocating() \
    (SI_va_n > 0)

#define OPTIONAL_ARG_nonrelocating() \
    (--SI_va_n, va_arg(SI_va_ap,Object))

#define END_ARGS_nonrelocating() \
    va_end(SI_va_ap)

#endif /* SI_SUPPORT_SF */


/* Hack to silence lint. */
#ifdef lint
#undef va_arg
#define va_arg(list,mode) ((mode *)(unsigned long)(list += sizeof(mode)))[-1]
#endif

#ifdef lint
#define SI_LINTUSE(var)   = ((var = 0), var)
#else
#define SI_LINTUSE(var) = 0
#endif

#if SI_SUPPORT_MF

#define EXTRACT_KEY(kword,klist,ldefault) \
    (TRUEP(Temp1 = member_odd((kword),(klist))) ? SECOND(Temp1) : (ldefault))
#define EXTRACT_KEY_VALUE(klist) M_FIRST(klist)

#endif



/***************************************************************************
 *
 * Closure reference
 *
 **************************************************************************/

#if SI_SUPPORT_SF

#define FIND_BINDING(n) \
    nthcdr(FIX(n), SI_FUNCTION_ENV(SI_Called_function))
#define NEW_BINDING(x)   	cons(NIL,x)
#define ADD_BINDING    /*old*/NEW_BINDING
#define BINDING_OF(x)    	M_CAR(x)

#endif /* SI_SUPPORT_SF */


#if SI_SUPPORT_MF

#define MAKE_LEXC(f,b)		make_closure(f, b)

typedef Object Binding;
#define MAKE_BINDING(a)         ncons(a)
#define MAKE_NEW_BINDING()      MAKE_BINDING(NIL)
#define BINDING_VALUE(a)	M_CAR(a)

#endif /* SI_SUPPORT_MF */



/***************************************************************************
 *
 * Dynamic state
 *
 * The dynamic state of Lisp consists of three stacks:
 *   - one containing lisp objects and GC protection frames
 *   - one containing saved bindings of dynamic variables
 *   - one consisting of linked frames for CATCHes and UNWIND-PROTECTs
 *
 **************************************************************************/

/**** gcobjmap.h, control.h, core.h ****/
typedef union {			/* Something on the Lisp stack */
    Object object;
    Object *location;
} SI_Stack_item;

typedef struct SI_special_frame {
    struct SI_special_frame *link;
    Object symbol;		/* or Object *location ? */
    Object *location; /* Temp hack -- if this is NULL, use symbol above */
    Object saved_value;
#if SI_SUPPORT_THREAD
    Object saved_symbol;
    short *local_count;
#endif
} SI_Special_frame;

extern TLS SI_Stack_item *Stack;	/* should be SI_ */


/***************************************************************************
 *
 * Lisp stack
 *
 **************************************************************************/

#define STACK_REF(n)  ((Stack+(n))->object)
#define STACK_LOC(n)  ((Stack+(n))->location)
#define STACK_PUSH(a) ((Stack->object=(a)),(void)Stack++)
#define STACK_POP()   ((--Stack)->object)

#define Declare_stack_pointer   SI_Stack_item *SI_old_stack_marker
#define SAVE_STACK()		(SI_old_stack_marker = Stack)
#define RESTORE_STACK()		(Stack = SI_old_stack_marker)

#define Declare_dynamic_state   SI_Stack_item *SI_old_stack_marker_1

/***************************************************************************
 *
 * Special (= dynamic) variables
 *
 **************************************************************************/

/* Each time we bind a special variable, we must push a Special_frame onto
 * the dynamic binding stack.  The Special_frame records the symbol as well
 * as its saved binding so that THROW can know where to restore the bindings.
 */

#define Declare_special(n) \
    SI_Special_frame SI_sf[n]

#if SI_SUPPORT_THREAD

/* Note: remember update SI_PUSH_SPECIAL_DFLTD (runint.h) when you change PUSH_SPECIAL */
#define PUSH_SPECIAL(variable, newValue, nesting) { \
    SI_sf[nesting].link = SI_Special_stack; \
    SI_sf[nesting].location = &SI_Special_data->variable##_LOCAL; \
    SI_sf[nesting].saved_value = variable; \
    SI_sf[nesting].saved_symbol = UNBOUND; \
    SI_sf[nesting].local_count = &SI_Special_count->variable##_COUNT; \
    SI_Special_stack = &SI_sf[nesting]; \
    \
    SI_Special_data->variable##_LOCAL = newValue; \
    SI_Special_count->variable##_COUNT += 1; \
}

/* TODO: write detailed document for this macro! -- Chun Tian (binghe), 2009/9/6 */
#define PUSH_SPECIAL_WITH_SYMBOL(variable, symbol, newValue, nesting) { \
    SI_sf[nesting].link = SI_Special_stack; \
    SI_sf[nesting].location = &SI_Special_data->variable##_LOCAL; \
    SI_sf[nesting].saved_value = variable; \
    SI_sf[nesting].saved_symbol = symbol; \
    SI_sf[nesting].local_count = &SI_Special_count->variable##_COUNT; \
    SI_Special_stack = &SI_sf[nesting]; \
    \
    SI_Special_data->variable##_LOCAL = newValue; \
    if (symbol != UNBOUND) { \
        short index; \
        index = SI_THREAD_INDEX(SI_current_thread()); \
        VALUE_CELL_LOCAL_COUNT(SI_symbol_field(symbol, SI_SymValLoc), index) += 1; \
        VALUE_CELL_LOCAL_LOCATION(SI_symbol_field(symbol, SI_SymValLoc), index) = \
            &SI_Special_data->variable##_LOCAL; \
    } \
    SI_Special_count->variable##_COUNT += 1; \
}

#else

#define PUSH_SPECIAL(var,v,i) \
    (SI_sf[i].link = SI_Special_stack, \
     SI_sf[i].location = &var, \
     SI_sf[i].saved_value = var, \
     var = v, \
     SI_Special_stack = &SI_sf[i])

#define PUSH_SPECIAL_WITH_SYMBOL(variable, symbol, newValue, nesting) \
    (SI_sf[nesting].link = SI_Special_stack, \
     SI_sf[nesting].location = &variable, \
     SI_sf[nesting].saved_value = variable, \
     variable = newValue, \
     SI_Special_stack = &SI_sf[nesting])
#endif

#if SI_SUPPORT_THREAD

#define POP_SPECIAL() { \
    *(SI_Special_stack->location) = SI_Special_stack->saved_value; \
    if (SI_Special_stack->saved_symbol != UNBOUND) { \
        short index; \
        index = SI_THREAD_INDEX(SI_current_thread()); \
        VALUE_CELL_LOCAL_COUNT(SI_symbol_field(SI_Special_stack->saved_symbol, SI_SymValLoc), index) -= 1; \
    } \
    *(SI_Special_stack->local_count) -= 1; \
    SI_Special_stack = SI_Special_stack->link; \
}

#else

#define POP_SPECIAL() \
    (*(SI_Special_stack->location) = SI_Special_stack->saved_value, \
     SI_Special_stack = SI_Special_stack->link)

#endif

#define OLD_PUSH_SPECIAL(s,v,i) \
    (SI_sf[i].link = SI_Special_stack, \
     SI_sf[i].symbol = s, \
     SI_sf[i].location = NULL, \
     SI_sf[i].saved_value = SYMBOL_VALUE(s), \
     SET_SYMBOL_VALUE(s, v), \
     SI_Special_stack = &SI_sf[i])

#define OLD_POP_SPECIAL() \
    (SET_SYMBOL_VALUE(SI_Special_stack->symbol, SI_Special_stack->saved_value), \
     SI_Special_stack = SI_Special_stack->link)

/***************************************************************************
 *
 * Memory management primitives
 *
 **************************************************************************/

/* A segment is a single contiguous chunk of memory under the purview of
 * the Lisp storage manager. */

typedef struct SI_segment_struct {
    struct SI_segment_struct *next;
    void *start;       /* beginning of valid objects */
    void *limit;       /* allocation limit */
    void *end;         /* true size including reserve space */
    void *frontier;    /* next available location in sequence */
    void *gc_temp;     /* used by garbage collectors */
    void *gc_maptemp;  /* used by garbage collectors */
} SI_Segment;

/* An area is a set of segments. */

typedef struct SI_area_struct {
    SI_Segment *first_segment;	 /* chain of segments */
    SI_Segment *current_segment; /* chain of segments */
    SI_Size_type in_use_last_gc;
    SI_Size_type target_size;
    SI_Size_type increment;
    SI_Size_type notify_threshold;
} SI_Area;

typedef struct SI_frontier_frame { 
    long gc_count;
    SI_Segment *segment;   /* current area */
    void *frontptr;        /* current area */
    struct SI_frontier_frame *link;
} SI_Frontier_frame;

typedef struct SI_catch_frame {
    struct SI_catch_frame *link;
    SI_Stack_item *saved_stack_top;
    SI_Special_frame *saved_special_stack;
    Object tag;
    jmp_buf g2jmpbuf;
    SI_Area *saved_area;   /* old area */
    SI_Frontier_frame *frontier;
} SI_Catch_frame;

/*
 * These are used by the translations of the WITH-xxx-AREA and
 * WITH-xxx-ALLOCATION macros.
 */

#define Declare_area(x)         SI_Area *x
#define XDeclare_area(count)    Declare_area((SI__sa[count]))
#define SAVE_CURRENT_AREA(x)    ((x) = Current_area)
#define RESTORE_CURRENT_AREA(x) \
   (SI_FLUSH_ALLOC_CACHE(), (Current_area = (x)), SI_RELOAD_ALLOC_CACHE())
#define SET_CURRENT_AREA(area)  \
   (SI_FLUSH_ALLOC_CACHE(), (Current_area = &(area)), SI_RELOAD_ALLOC_CACHE())


#define Declare_frontier(x)       SI_Frontier_frame x
#define XDeclare_frontier(count)  Declare_frontier((SI__fr[count]))
#define SAVE_FRONTIER(x) \
    ((x).gc_count = SI_gc_count, \
     (x).link = SI_Frontier_stack, \
     SI_Frontier_stack = &(x),\
     (x).segment = Current_area->current_segment, \
     (void)((x).frontptr = (x).segment->frontier)) 

/* The ", 0" is needed because conditional expressions can't be void */
#define RESTORE_FRONTIER(x) \
   (SI_Frontier_stack = (x).link,\
    ((((x).gc_count == SI_gc_count) || (Current_area == &Local_area)) \
     ? ((Current_area->current_segment == (x).segment) \
	? ((x).segment->frontier =  \
	   (x).frontptr, SI_RELOAD_ALLOC_CACHE(), 0) \
	: (restore_frontier((x).segment,(x).frontptr), 0)) \
     : 0))

#define SI_SAVE_AREA_AND_FRONTIER(f) \
    (SAVE_CURRENT_AREA((f).saved_area), \
     (f).frontier = SI_Frontier_stack)

/*
 * The PUSH_AREA and POP_AREA macros are used to coordinate an
 * unwind-protected save and restore of the current allocation area.
 *
 * Usage:
 *
 * if (PUSH_AREA(<area>,<area-index>)) {
 *     <body>;
 * }
 * POP_AREA(<area-index>);
 */
#define PUSH_AREA(area, area_index)  \
   (SAVE_CURRENT_AREA(SI__sa[area_index]), \
    SET_CURRENT_AREA(area),1)

#define POP_AREA(area_index) \
   RESTORE_CURRENT_AREA(SI__sa[area_index])


/*
 * The PUSH_LOCAL_ALLOCATION and POP_LOCAL_ALLOCATION macros
 * are used to coordinate the use of an area in which the data allocated
 * in that area should be discarded by restoring the frontier of that area.
 *
 * Usage:
 *
 * if (PUSH_LOCAL_ALLOCATION(<area>,<area-index>,<frontier-index>)) {
 *     <body>;
 * }
 * POP_LOCAL_ALLOCATION(<area-index>,<frontier-index>);
 *
 */

#define PUSH_LOCAL_ALLOCATION(area,area_index,frontier_index) \
   ((SAVE_CURRENT_AREA(SI__sa[area_index]), \
    SET_CURRENT_AREA(area), \
    SAVE_FRONTIER(SI__fr[frontier_index])),1L)


#define POP_LOCAL_ALLOCATION(area_index,frontier_index) \
   RESTORE_FRONTIER(SI__fr[frontier_index]); \
   RESTORE_CURRENT_AREA(SI__sa[area_index])


/***************************************************************************
 *
 * Catch, throw, and unwind_protect support
 *
 **************************************************************************/

/* Example (SF):

      (CATCH (QUOTE A) (F1 N))

   becomes

      Declare_catch(17);
      ...
      if (PUSH_CATCH(Qa,0)) {
	  result = f1(n);
      }
      POP_CATCH(0);

   Example (MF):

      (CATCH (QUOTE A) (F1 N))

   becomes

      Catch_buf old_env_1;
      ...
      CATCH(temp1, Q_A, old_env_1, LABEL1);
	temp1 = f1(N);
      LABEL1: 
      END_CATCH(old_env_1);
 */

/* This is conceptually similar to special binding.
 * The jmp_buf contains the information needed to restore the generic
 * machine state, and the other two saved pointers are for the benefit
 * of THROW.
 *
 * UNWIND-PROTECT just uses a catch frame with a special token as its
 * tag.  It acts as a kind of wildcard, matching a THROW to any tag.
 * THROW modifys the tag in the catch frame, and stores the tag on the stack;
 * then, after executing the cleanup form, a rethrow is done.
 */

/* Setup the catch buffer.  This has to be seperated from the setjmp() because
 * of the restrictions on where setjmp() may appear, as specified by ANSI-C.
 */
#define SI_PUSH_CATCH(t,f) \
    ((f).link = SI_Catch_stack, \
     (f).saved_special_stack = SI_Special_stack, \
     (f).saved_stack_top = Stack, \
     (f).tag = (t), \
     SI_Catch_stack = &(f), \
     SI_SAVE_AREA_AND_FRONTIER(f))

#define SI_CATCH_THROWN(f)	(setjmp((f).g2jmpbuf))

/* restore Catch stack, Stack and allocation state */
#define SI_POP_CATCH(f) \
     (SI_Catch_stack = (f).link, \
      Stack = (f).saved_stack_top)


/* restore only Catch stack; Stack will be restored by explicit
   RESTORE_VALUES later */
#define SI_POP_UNWIND_PROTECT(f) \
    (SI_Catch_stack = (f).link)

/* assertion: SI_Catch_stack = f.link */
#define SI_CONTINUE_UNWINDING(f) \
    (((f).tag == SI_UNWIND_PROTECT_MARKER) ? \
     0 : \
     SI_re_throw())	/* all values, counter and old tag are on stack */


#if SI_SUPPORT_SF

#define DO_THROW(tag)		SI_throw(tag, result) /* local "result" */

#define Declare_catch(n) \
    SI_Catch_frame SI__cf[n]

/* **** This is pretty disgusting, with unbalanced parens and all.
 * The problem is that the SF translator generates
 *    if (PUSH_CATCH(tag,i)) { body }
 * but the catch buffer setup in PUSH_CATCH must be seperated from the setjmp()
 * done by it because of restrictions on where a setjmp() may appear.  With
 * this definition, the above code expands into the following
 *    if (SI_PUSH_CATCH(tag, cf[i]), TRUE) if (!SI_CATCH_THROWN(cf[i])) {body}
 * Someday though we might want to redesign the interface for the SF
 * translator somewhat.  What I'd like to do is rename this CATCH and do the
 * obvious thing, but until we can compile without MF support there is a name
 * conflict involved in doing so.
 */

#define PUSH_CATCH(t, i) \
    SI_PUSH_CATCH(t, SI__cf[i]), TRUE) if (!SI_CATCH_THROWN(SI__cf[i])

/* First value is at the top of stack, remove it */
#define POP_CATCH(i)		SI_POP_CATCH(SI__cf[i])

#define CATCH_VALUES()    STACK_REF(-1L)

#define PUSH_UNWIND_PROTECT(i) \
    PUSH_CATCH(SI_UNWIND_PROTECT_MARKER,i)

#define POP_UNWIND_PROTECT(i) \
    SI_POP_UNWIND_PROTECT(SI__cf[i])

#define CONTINUE_UNWINDING(i) \
    SI_CONTINUE_UNWINDING(SI__cf[i])

#endif /* SI_SUPPORT_SF */

#if SI_SUPPORT_MF

#define CATCH(result_var, tag, f, label) \
    SI_PUSH_CATCH(tag, f); \
    if (SI_CATCH_THROWN(f)) { \
      result_var = STACK_POP(); /* restore stack and get 1st value */ \
      goto label; \
    }

/* restore only Catch stack here. CATCH takes care of Lisp stack and 1st
   value. This is done in this way in oder to be compartible with
   how MF treats END_CATCH to support "return-from" */
#define END_CATCH(f)		(SI_Catch_stack = (f).link)

#define THROW(tag, firstval)    SI_throw(tag, firstval)

/* unwindingp is no longer needed because it's encoded as
   !EQ((f).tag, SI_UNWIND_PROTECT_MARKER) */

#define UNWIND_PROTECT(unwindingp, f, label) \
    SI_PUSH_CATCH(SI_UNWIND_PROTECT_MARKER, f); \
    if (SI_CATCH_THROWN(f)) goto label;

#define BEGIN_UNWIND_PROTECT(f, label) \
    label: \
    SI_POP_UNWIND_PROTECT(f)

#define END_UNWIND_PROTECT(unwindingp,f) \
    SI_CONTINUE_UNWINDING(f)

#endif /* SI_SUPPORT_MF */


/* PROGV support */

#define SI_PROGV_CLEANUP_STACK(f) \
    (Stack = (f).saved_stack_top)

#if SI_SUPPORT_SF

/* PROGV ends up being even worse than CATCH.
 * Watch out for all the unbalanced parens and curly braces here. 
 * The expansion is
 *
 *   if (
 *       -- Start of code from PUSH_PROGV()
 *        TRUE) {
 *     <do setup>
 *     if (!SI_CATCH_THROWN(...)) {
 *       progv_init_values(vals);
 *       if (TRUE
 *         -- End of code from PUSH_PROGV()
 *               ) <progv body statment>
 *     -- Start of code from POP_PROGV()
 *     }
 *   }
 *   <do cleanup>
 *   -- End of code from POP_PROGV()
 */

#define PUSH_PROGV(syms, vals, i) \
    TRUE) { \
      SI_progv_save_bindings(syms); \
      SI_PUSH_CATCH(SI_UNWIND_PROTECT_MARKER, SI__cf[i]); \
      if (!SI_CATCH_THROWN(SI__cf[i])) { \
	SI_progv_do_bindings(vals); \
	if (TRUE

#define POP_PROGV(i) \
      } \
    } \
    SI_POP_UNWIND_PROTECT(SI__cf[i]); \
    SI_progv_restore_bindings(SI__cf[i].saved_stack_top); \
    CONTINUE_UNWINDING(i); \
    SI_PROGV_CLEANUP_STACK(SI__cf[i])

#endif /* SI_SUPPORT_SF */

#if SI_SUPPORT_MF

#define PROGV(syms, vals, unwind_p, f, label) \
    SI_progv_save_bindings(syms); \
    UNWIND_PROTECT(unwind_p, f, label); \
      SI_progv_do_bindings(vals)

#define END_PROGV(unwind_p, f) \
      SI_POP_UNWIND_PROTECT(f); \
      SI_progv_restore_bindings(f.saved_stack_top); \
    END_UNWIND_PROTECT(unwind_p, f); \
    SI_PROGV_CLEANUP_STACK(f)

#endif /* SI_SUPPORT_MF */

/***************************************************************************
 *
 * Function call support
 *
 **************************************************************************/

#define SI_CALL_ARGUMENTS_LIMIT	50L

#define MV_FUNCALL(fn)		SI_mv_funcall(fn)

#if SI_SUPPORT_CLOS

#define funcall0(fn) FUNCALL_0(fn)
#define funcall1(fn,a1) FUNCALL_1(fn,a1)
#define funcall2(fn,a1,a2) FUNCALL_2(fn,a1,a2)

#define FUNCALL_0(fn) SI_internal_funcall(fn, 0, NIL)
#define FUNCALL_1(fn, a1) (STACK_PUSH(a1), SI_internal_funcall(fn, 1, NIL))
#define FUNCALL_2(fn, a1, a2) \
    (STACK_PUSH(a1), STACK_PUSH(a2), SI_internal_funcall(fn, 2, NIL))

#else

#define FUNCALL_0(fn) funcall0(fn)
#define FUNCALL_1(fn, a1) funcall1(fn,a1)
#define FUNCALL_2(fn, a1, a2) funcall2(fn,a1,a2)

#endif

#define FUNCALL_3(fn, a1, a2, a3) \
    (STACK_PUSH(a1), STACK_PUSH(a2), STACK_PUSH(a3), \
     SI_internal_funcall(fn, 3, NIL))
#define FUNCALL_4(fn, a1, a2, a3, a4) \
    (STACK_PUSH(a1), STACK_PUSH(a2), STACK_PUSH(a3), STACK_PUSH(a4), \
     SI_internal_funcall(fn, 4, NIL))
#define FUNCALL_5(fn, a1, a2, a3, a4, a5) \
    (STACK_PUSH(a1), STACK_PUSH(a2), STACK_PUSH(a3), STACK_PUSH(a4), \
     STACK_PUSH(a5), \
     SI_internal_funcall(fn, 5, NIL))
#define FUNCALL_6(fn, a1, a2, a3, a4, a5, a6) \
    (STACK_PUSH(a1), STACK_PUSH(a2), STACK_PUSH(a3), STACK_PUSH(a4), \
     STACK_PUSH(a5), STACK_PUSH(a6), \
     SI_internal_funcall(fn, 6, NIL))


/* funcalls for symbol objects */
#define FUNCALL_SYMBOL_0(fun) \
    (SI_Called_function =  SYMBOL_FUNCTION(fun), \
     ((SI_FUNCTION_SIMPLE_P(SI_Called_function)&& \
       (!FIXNUMP(SI_FUNCTION_ENV(SI_Called_function)))) \
      ? (*SI_FUNCTION_ENTRY(SI_Called_function))() \
      : SI_internal_funcall(SI_Called_function,0,NIL)))
    
#define FUNCALL_SYMBOL_1(fun, a1) \
    (STACK_PUSH(a1), \
     SI_Called_function =  SYMBOL_FUNCTION(fun), \
     ((SI_FUNCTION_SIMPLE_P(SI_Called_function)&& \
       (!FIXNUMP(SI_FUNCTION_ENV(SI_Called_function)))) \
      ? Stack -=1L, (*SI_FUNCTION_ENTRY(SI_Called_function))(STACK_REF(0))\
      : SI_internal_funcall(SI_Called_function,1L,NIL)))
    
#define FUNCALL_SYMBOL_2(fun, a1, a2) \
    (STACK_PUSH(a1), \
     STACK_PUSH(a2), \
     SI_Called_function =  SYMBOL_FUNCTION(fun), \
     ((SI_FUNCTION_SIMPLE_P(SI_Called_function)&& \
       (!FIXNUMP(SI_FUNCTION_ENV(SI_Called_function)))) \
      ? Stack -=2L, (*SI_FUNCTION_ENTRY(SI_Called_function)) \
      (STACK_REF(0), STACK_REF(1L)) \
      : SI_internal_funcall(SI_Called_function,2L,NIL)))

#define FUNCALL_SYMBOL_3(fun, a1, a2, a3) \
    (STACK_PUSH(a1), \
     STACK_PUSH(a2), \
     STACK_PUSH(a3), \
     SI_Called_function =  SYMBOL_FUNCTION(fun), \
     ((SI_FUNCTION_SIMPLE_P(SI_Called_function)&& \
       (!FIXNUMP(SI_FUNCTION_ENV(SI_Called_function)))) \
      ? Stack -=3L, (*SI_FUNCTION_ENTRY(SI_Called_function)) \
      (STACK_REF(0), STACK_REF(1), STACK_REF(2L)) \
      : SI_internal_funcall(SI_Called_function,3L,NIL)))

#define FUNCALL_SYMBOL_4(fun, a1, a2, a3, a4) \
    (STACK_PUSH(a1), \
     STACK_PUSH(a2), \
     STACK_PUSH(a3), \
     STACK_PUSH(a4), \
     SI_Called_function =  SYMBOL_FUNCTION(fun), \
     ((SI_FUNCTION_SIMPLE_P(SI_Called_function)&& \
       (!FIXNUMP(SI_FUNCTION_ENV(SI_Called_function)))) \
      ? Stack -=4L, (*SI_FUNCTION_ENTRY(SI_Called_function)) \
      (STACK_REF(0), STACK_REF(1L), STACK_REF(2L), STACK_REF(3L)) \
      : SI_internal_funcall(SI_Called_function,4L,NIL)))

#define FUNCALL_SYMBOL_5(fun, a1, a2, a3, a4, a5) \
    (STACK_PUSH(a1), \
     STACK_PUSH(a2), \
     STACK_PUSH(a3), \
     STACK_PUSH(a4), \
     STACK_PUSH(a5), \
     SI_Called_function =  SYMBOL_FUNCTION(fun), \
     ((SI_FUNCTION_SIMPLE_P(SI_Called_function)&& \
       (!FIXNUMP(SI_FUNCTION_ENV(SI_Called_function)))) \
      ? Stack -=5L, (*SI_FUNCTION_ENTRY(SI_Called_function)) \
      (STACK_REF(0), STACK_REF(1L), STACK_REF(2L), STACK_REF(3L), STACK_REF(4L)) \
      : SI_internal_funcall(SI_Called_function,5L,NIL)))

/* FUNCALL_SYMBOL_6, FUNCALL_SYMBOL_7, etc. */


/* etc. etc.   APPLY_1 through _5 needed as well */

#define APPLY_1(fn, t)		SI_internal_funcall(fn, 0, t)
#define APPLY_2(fn, a1, t) \
    (STACK_PUSH(a1), SI_internal_funcall(fn, 1, t))
#define APPLY_3(fn, a1, a2, t) \
    (STACK_PUSH(a1), STACK_PUSH(a2), SI_internal_funcall(fn, 2, t))
#define APPLY_4(fn, a1, a2, a3, t) \
    (STACK_PUSH(a1), STACK_PUSH(a2), STACK_PUSH(a3), \
     SI_internal_funcall(fn, 3, t))
#define APPLY_5(fn, a1, a2, a3, a4, t) \
    (STACK_PUSH(a1), STACK_PUSH(a2), STACK_PUSH(a3), STACK_PUSH(a4), \
     SI_internal_funcall(fn, 4, t))


#define CALL_0(fn)               fn()
#define CALL_1(fn,a)             fn(a)
#define CALL_2(fn,a,b) \
    (STACK_PUSH(a), STACK_REF(0)=(b), Stack -= 1L, \
     fn(STACK_REF(0), STACK_REF(1L)))
#define CALL_3(fn,a,b,c) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_REF(0)=(c), \
     Stack -= 2L, \
     fn(STACK_REF(0), STACK_REF(1),STACK_REF(2)))
#define CALL_4(fn,a,b,c,d) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_REF(0)=(d), Stack -= 3L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3)))
#define CALL_5(fn,a,b,c,d,e) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_REF(0)=(e), Stack -= 4L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4)))
#define CALL_6(fn,a,b,c,d,e,f) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_REF(0)=(f), \
     Stack -= 5L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5)))
#define CALL_7(fn,a,b,c,d,e,f,g) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_REF(0)=(g), Stack -= 6L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6)))
#define CALL_8(fn,a,b,c,d,e,f,g,h) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_REF(0)=(h), Stack -= 7, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7)))
#define CALL_9(fn,a,b,c,d,e,f,g,h,i) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_REF(0)=(i), \
     Stack -= 8L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8)))
#define CALL_10(fn,a,b,c,d,e,f,g,h,i,j) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_REF(0)=(j), Stack -= 9L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9)))
#define CALL_11(fn,a,b,c,d,e,f,g,h,i,j,k) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_REF(0)=(k), Stack -= 10L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10)))
#define CALL_12(fn,a,b,c,d,e,f,g,h,i,j,k,l) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_REF(0)=(l), \
     Stack -= 11L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11)))
#define CALL_13(fn,a,b,c,d,e,f,g,h,i,j,k,l,m) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_REF(0)=(m), Stack -= 12L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12)))
#define CALL_14(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_REF(0)=(n), Stack -= 13L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13)))
#define CALL_15(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_REF(0)=(o), \
     Stack -= 14L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14)))
#define CALL_16(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_REF(0)=(p), Stack -= 15L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15)))
#define CALL_17(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_REF(0)=(q), Stack -= 16L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16)))
#define CALL_18(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_PUSH(q), STACK_REF(0)=(r), \
     Stack -= 17L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16), STACK_REF(17)))
#define CALL_19(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_PUSH(q), STACK_PUSH(r), \
     STACK_REF(0)=(s), Stack -= 18L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16), STACK_REF(17), STACK_REF(18)))
#define CALL_20(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,tt) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_PUSH(q), STACK_PUSH(r), \
     STACK_PUSH(s), STACK_REF(0)=(tt), Stack -= 19L, \
     fn(STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16), STACK_REF(17), STACK_REF(18), STACK_REF(19)))

#define CALLN_0(fn)               (fn(0))
#define CALLN_1(fn,a)             (fn(1,a))
#define CALLN_2(fn,a,b) \
    (STACK_PUSH(a), STACK_REF(0)=(b), Stack -= 1L, \
     fn(2,STACK_REF(0), STACK_REF(1)))
#define CALLN_3(fn,a,b,c) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_REF(0)=(c), \
     Stack -= 2L, \
     fn(3,STACK_REF(0), STACK_REF(1),STACK_REF(2)))
#define CALLN_4(fn,a,b,c,d) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_REF(0)=(d), Stack -= 3L, \
     fn(4,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3)))
#define CALLN_5(fn,a,b,c,d,e) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_REF(0)=(e), Stack -= 4, \
     fn(5,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4)))
#define CALLN_6(fn,a,b,c,d,e,f) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_REF(0)=(f), \
     Stack -= 5L, \
     fn(6,STACK_REF(0), STACK_REF(1), STACK_REF(2), \
	STACK_REF(3), STACK_REF(4), STACK_REF(5)))
#define CALLN_7(fn,a,b,c,d,e,f,g) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_REF(0)=(g), Stack -= 6L, \
     fn(7,STACK_REF(0), STACK_REF(1), STACK_REF(2), \
	STACK_REF(3), STACK_REF(4), STACK_REF(5), \
	STACK_REF(6)))
#define CALLN_8(fn,a,b,c,d,e,f,g,h) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_REF(0)=(h), Stack -= 7L, \
     fn(8,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7)))
#define CALLN_9(fn,a,b,c,d,e,f,g,h,i) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_REF(0)=(i), \
     Stack -= 8L, \
     fn(9,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7), STACK_REF(8)))
#define CALLN_10(fn,a,b,c,d,e,f,g,h,i,j) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_REF(0)=(j), Stack -= 9L, \
     fn(10,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9)))
#define CALLN_11(fn,a,b,c,d,e,f,g,h,i,j,k) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_REF(0)=(k), Stack -= 10L, \
     fn(11,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), \
	STACK_REF(10)))
#define CALLN_12(fn,a,b,c,d,e,f,g,h,i,j,k,l) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_REF(0)=(l), \
     Stack -= 11L, \
     fn(12,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), \
	STACK_REF(10), STACK_REF(11)))
#define CALLN_13(fn,a,b,c,d,e,f,g,h,i,j,k,l,m) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_REF(0)=(m), Stack -= 12L, \
     fn(13,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), \
	STACK_REF(10), STACK_REF(11), STACK_REF(12)))
#define CALLN_14(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_REF(0)=(n), Stack -= 13L, \
     fn(14,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), \
	STACK_REF(10), STACK_REF(11), STACK_REF(12), STACK_REF(13)))
#define CALLN_15(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_REF(0)=(o), \
     Stack -= 14L, \
     fn(15,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), \
	STACK_REF(10), STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14)))
#define CALLN_16(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_REF(0)=(p), Stack -= 15L, \
     fn(16,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), \
	STACK_REF(10), \ STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), \
	STACK_REF(15)))
#define CALLN_17(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_REF(0)=(q), Stack -= 16L, \
     fn(17,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16)))
#define CALLN_18(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_PUSH(q), STACK_REF(0)=(r), \
     Stack -= 17L, \
     fn(18,STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16), STACK_REF(17)))
#define CALLN_19(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_PUSH(q), STACK_PUSH(r), \
     STACK_REF(0)=(s), Stack -= 18L, \
     fn(19, STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16), STACK_REF(17), STACK_REF(18)))
#define CALLN_20(fn,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,tt) \
    (STACK_PUSH(a), STACK_PUSH(b), STACK_PUSH(c), \
     STACK_PUSH(d), STACK_PUSH(e), STACK_PUSH(f), \
     STACK_PUSH(g), STACK_PUSH(h), STACK_PUSH(i), \
     STACK_PUSH(j), STACK_PUSH(k), STACK_PUSH(l), \
     STACK_PUSH(m), STACK_PUSH(n), STACK_PUSH(o), \
     STACK_PUSH(p), STACK_PUSH(q), STACK_PUSH(r), \
     STACK_PUSH(s), STACK_REF(0)=(tt), Stack -= 19L, \
     fn(20, STACK_REF(0), STACK_REF(1), STACK_REF(2), STACK_REF(3), STACK_REF(4), \
	STACK_REF(5), \
	STACK_REF(6), STACK_REF(7), STACK_REF(8), STACK_REF(9), STACK_REF(10), \
	STACK_REF(11), STACK_REF(12), STACK_REF(13), STACK_REF(14), STACK_REF(15), \
	STACK_REF(16), STACK_REF(17), STACK_REF(18), STACK_REF(19)))

/* Use this when fn is itself a macro that clobbers the stack */

#define CAREFUL_CALL_2(fn,a,b) \
    (STACK_PUSH(a), STACK_PUSH(b), \
     STACK_REF(-2L) = fn(STACK_REF(-2L), STACK_REF(-1L)), \
     Stack -= 2L, \
     STACK_REF(0))



/***************************************************************************
 *
 * GC protection
 *
 **************************************************************************/

#ifdef SI_SUPPORT_SF

#define PROTECT_GLOBAL(lvalue)  SI_add_external_root(&lvalue)

#define PROTECT_GLOBAL_1(a)     PROTECT_GLOBAL(a)
#define PROTECT_GLOBAL_2(a,b)   (PROTECT_GLOBAL_1(a), PROTECT_GLOBAL_1(b))
#define PROTECT_GLOBAL_3(a,b,c) (PROTECT_GLOBAL_2(a,b), PROTECT_GLOBAL_1(c))
#define PROTECT_GLOBAL_4(a,b,c,d) \
     (PROTECT_GLOBAL_3(a,b,c), PROTECT_GLOBAL_1(d))
#define PROTECT_GLOBAL_5(a,b,c,d,e) \
     (PROTECT_GLOBAL_4(a,b,c,d), PROTECT_GLOBAL_1(e))
#define PROTECT_GLOBAL_6(a,b,c,d,e,f) \
     (PROTECT_GLOBAL_5(a,b,c,d,e), PROTECT_GLOBAL_1(f))
#define PROTECT_GLOBAL_7(a,b,c,d,e,f,g) \
     (PROTECT_GLOBAL_6(a,b,c,d,e,f), PROTECT_GLOBAL_1(g))
#define PROTECT_GLOBAL_8(a,b,c,d,e,f,g,h) \
     (PROTECT_GLOBAL_7(a,b,c,d,e,f,g), PROTECT_GLOBAL_1(h))
#define PROTECT_GLOBAL_9(a,b,c,d,e,f,g,h,i) \
     (PROTECT_GLOBAL_8(a,b,c,d,e,f,g,h), PROTECT_GLOBAL_1(i))
#define PROTECT_GLOBAL_10(a,b,c,d,e,f,g,h,i,j) \
     (PROTECT_GLOBAL_9(a,b,c,d,e,f,g,h,i), PROTECT_GLOBAL_1(j))

#define Declare_protect(n)      SI_Stack_item *SI_old_stack_marker_2
#define PROTECT_LOCALS()   	(SI_old_stack_marker_2 = Stack)
#define UNPROTECT_LOCALS()	(Stack = SI_old_stack_marker_2)

#endif /* SI_SUPPORT_SF */

#define PROTECT_1(a)		/*(Stack += 3L, \
				 STACK_REF(-3L) = PROTECT_MARKER, \
				 STACK_LOC(-2L) = &a, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_2(a,b)		/*(Stack += 4L, \
				 STACK_REF(-4L) = PROTECT_MARKER, \
				 STACK_LOC(-3L) = &a, \
				 STACK_LOC(-2L) = &b, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_3(a,b,c)	/*(Stack += 5L, \
				 STACK_REF(-5L) = PROTECT_MARKER, \
				 STACK_LOC(-4L) = &a, \
				 STACK_LOC(-3L) = &b, \
				 STACK_LOC(-2L) = &c, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_4(a,b,c,d)	/*(Stack += 6L, \
				 STACK_REF(-6L) = PROTECT_MARKER, \
				 STACK_LOC(-5L) = &a, \
				 STACK_LOC(-4L) = &b, \
				 STACK_LOC(-3L) = &c, \
				 STACK_LOC(-2L) = &d, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_5(a,b,c,d,e)	/*(Stack += 7L, \
				 STACK_REF(-7L) = PROTECT_MARKER, \
				 STACK_LOC(-6L) = &a, \
				 STACK_LOC(-5L) = &b, \
				 STACK_LOC(-4L) = &c, \
				 STACK_LOC(-3L) = &d, \
				 STACK_LOC(-2L) = &e, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_6(a,b,c,d,e,f)	/*(Stack += 8L, \
				 STACK_REF(-8L) = PROTECT_MARKER, \
				 STACK_LOC(-7L) = &a, \
				 STACK_LOC(-6L) = &b, \
				 STACK_LOC(-5L) = &c, \
				 STACK_LOC(-4L) = &d, \
				 STACK_LOC(-3L) = &e, \
				 STACK_LOC(-2L) = &f, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_7(a,b,c,d,e,f,g) /*(Stack += 9L, \
				 STACK_REF(-9L) = PROTECT_MARKER, \
				 STACK_LOC(-8L) = &a, \
				 STACK_LOC(-7L) = &b, \
				 STACK_LOC(-6L) = &c, \
				 STACK_LOC(-5L) = &d, \
				 STACK_LOC(-4L) = &e, \
				 STACK_LOC(-3L) = &f, \
				 STACK_LOC(-2L) = &g, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_8(a,b,c,d,e,f,g,h) /*(Stack += 10L, \
				 STACK_REF(-10L) = PROTECT_MARKER, \
				 STACK_LOC(-9L) = &a, \
				 STACK_LOC(-8L) = &b, \
				 STACK_LOC(-7L) = &c, \
				 STACK_LOC(-6L) = &d, \
				 STACK_LOC(-5L) = &e, \
				 STACK_LOC(-4L) = &f, \
				 STACK_LOC(-3L) = &g, \
				 STACK_LOC(-2L) = &h, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_9(a,b,c,d,e,f,g,h,i) /*(Stack += 11L, \
				 STACK_REF(-11L) = PROTECT_MARKER, \
				 STACK_LOC(-10L) = &a, \
				 STACK_LOC(-9L) = &b, \
				 STACK_LOC(-8L) = &c, \
				 STACK_LOC(-7L) = &d, \
				 STACK_LOC(-6L) = &e, \
				 STACK_LOC(-5L) = &f, \
				 STACK_LOC(-4L) = &g, \
				 STACK_LOC(-3L) = &h, \
				 STACK_LOC(-2L) = &i, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECT_10(a,b,c,d,e,f,g,h,i,j) /*(Stack += 12L, \
				 STACK_REF(-12L) = PROTECT_MARKER, \
				 STACK_LOC(-11L) = &a, \
				 STACK_LOC(-10L) = &b, \
				 STACK_LOC(-9L) = &c, \
				 STACK_LOC(-8L) = &d, \
				 STACK_LOC(-7L) = &e, \
				 STACK_LOC(-6L) = &f, \
				 STACK_LOC(-5L) = &g, \
				 STACK_LOC(-4L) = &h, \
				 STACK_LOC(-3L) = &i, \
				 STACK_LOC(-2L) = &j, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/

#define PROTECTI_1(a)		/*(Stack += 3L, \
				 (a) = UNBOUND, \
				 STACK_REF(-3L) = PROTECT_MARKER, \
				 STACK_LOC(-2L) = &a, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_2(a,b)		/*(Stack += 4L, \
				 a = b = UNBOUND, \
				 STACK_REF(-4L) = PROTECT_MARKER, \
				 STACK_LOC(-3L) = &a, \
				 STACK_LOC(-2L) = &b, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_3(a,b,c)	/*(Stack += 5L, \
				 a = b = c = UNBOUND, \
				 STACK_REF(-5L) = PROTECT_MARKER, \
				 STACK_LOC(-4L) = &a, \
				 STACK_LOC(-3L) = &b, \
				 STACK_LOC(-2L) = &c, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_4(a,b,c,d)	/*(Stack += 6L, \
				 a = b = c = d = UNBOUND, \
				 STACK_REF(-6L) = PROTECT_MARKER, \
				 STACK_LOC(-5L) = &a, \
				 STACK_LOC(-4L) = &b, \
				 STACK_LOC(-3L) = &c, \
				 STACK_LOC(-2L) = &d, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_5(a,b,c,d,e)	/*(Stack += 7L, \
				 a = b = c = d = e = UNBOUND, \
				 STACK_REF(-7L) = PROTECT_MARKER, \
				 STACK_LOC(-6L) = &a, \
				 STACK_LOC(-5L) = &b, \
				 STACK_LOC(-4L) = &c, \
				 STACK_LOC(-3L) = &d, \
				 STACK_LOC(-2L) = &e, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_6(a,b,c,d,e,f)	/*(Stack += 8L, \
				 a = b = c = d = e = f =UNBOUND, \
				 STACK_REF(-8L) = PROTECT_MARKER, \
				 STACK_LOC(-7L) = &a, \
				 STACK_LOC(-6L) = &b, \
				 STACK_LOC(-5L) = &c, \
				 STACK_LOC(-4L) = &d, \
				 STACK_LOC(-3L) = &e, \
				 STACK_LOC(-2L) = &f, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_7(a,b,c,d,e,f,g) /*(Stack += 9L, \
				 a = b = c = d = e = f = g = UNBOUND, \
				 STACK_REF(-9L) = PROTECT_MARKER, \
				 STACK_LOC(-8L) = &a, \
				 STACK_LOC(-7L) = &b, \
				 STACK_LOC(-6L) = &c, \
				 STACK_LOC(-5L) = &d, \
				 STACK_LOC(-4L) = &e, \
				 STACK_LOC(-3L) = &f, \
				 STACK_LOC(-2L) = &g, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_8(a,b,c,d,e,f,g,h) /*(Stack += 10L, \
				 a = b = c = d = e = f = g = h = UNBOUND, \
				 STACK_REF(-10L) = PROTECT_MARKER, \
				 STACK_LOC(-9L) = &a, \
				 STACK_LOC(-8L) = &b, \
				 STACK_LOC(-7L) = &c, \
				 STACK_LOC(-6L) = &d, \
				 STACK_LOC(-5L) = &e, \
				 STACK_LOC(-4L) = &f, \
				 STACK_LOC(-3L) = &g, \
				 STACK_LOC(-2L) = &h, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_9(a,b,c,d,e,f,g,h,i) /*(Stack += 11L, \
				 a =b=c=d=e=f=g=h=i = UNBOUND, \
				 STACK_REF(-11L) = PROTECT_MARKER, \
				 STACK_LOC(-10L) = &a, \
				 STACK_LOC(-9L) = &b, \
				 STACK_LOC(-8L) = &c, \
				 STACK_LOC(-7L) = &d, \
				 STACK_LOC(-6L) = &e, \
				 STACK_LOC(-5L) = &f, \
				 STACK_LOC(-4L) = &g, \
				 STACK_LOC(-3L) = &h, \
				 STACK_LOC(-2L) = &i, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/
#define PROTECTI_10(a,b,c,d,e,f,g,h,i,j) /*(Stack += 12L, \
				 a =b=c=d=e=f=g=h=i=j = UNBOUND, \
				 STACK_REF(-12L) = PROTECT_MARKER, \
				 STACK_LOC(-11L) = &a, \
				 STACK_LOC(-10L) = &b, \
				 STACK_LOC(-9L) = &c, \
				 STACK_LOC(-8L) = &d, \
				 STACK_LOC(-7L) = &e, \
				 STACK_LOC(-6L) = &f, \
				 STACK_LOC(-5L) = &g, \
				 STACK_LOC(-4L) = &h, \
				 STACK_LOC(-3L) = &i, \
				 STACK_LOC(-2L) = &j, \
				 STACK_REF(-1L) = PROTECT_MARKER)*/


/***************************************************************************
 *
 * Error Reporting
 *
 **************************************************************************/
#undef error
#undef errorn
#undef warn
#undef cerror

#define error   (*SI_error_fptr)
#define errorn  (*SI_errorn_fptr)
#define warn    (*SI_warn_fptr)
#define cerror  (*SI_cerror_fptr)

/***************************************************************************
 *
 * Miscellaneous
 *
 **************************************************************************/

/* this should be tricky enough to fool lint but 
   simple enough to be removed by optimizing compiller */   
#define Declare_local_temp  \
     Object SI_Local_temp = (SI_Local_temp = UNBOUND, SI_Local_temp)


/* Temporary kludge; should bind Package, etc. */

#define CALL_INIT_FUNCTION(f) \
    do { extern void f(); f(); } while(0)


/* Macros used by MF's LOOP handler */

#if SI_SUPPORT_MF

#define T_COLLECT(item,result,last_cell) \
		{T_temp = ncons(item); \
		 last_cell = (!ENDP(result) ? (M_CDR(last_cell) = T_temp) \
			      : (result = T_temp)); }

#define T_COLLECT_APPEND(item,result,last_cell) \
		{if (TRUEP(T_temp = copy_list(item))) { \
		    last_cell = last(result ? (M_CDR(last_cell) = T_temp) \
					    : (result = T_temp), KOPT); \
		    } \
		}

#endif /* SI_SUPPORT_MF */


/* Old names */
#define SUPPLIED_P SUPPLIEDP
#define MAXARGS			SI_CALL_ARGUMENTS_LIMIT
#define DECLARE_AREA		Declare_area
#define DECLARE_FRONTIER        Declare_frontier
#define Stack_item		SI_Stack_item
#define internal_funcall	SI_internal_funcall

/* evalrun.c evals.c lreader.c main.c use Catch_bufs -- flush this
   typedef when all these references have been changed to SI_Catch_frame
   or whatever */ 

typedef SI_Catch_frame Catch_buf;

#define Area SI_Area
#define Segment SI_Segment




