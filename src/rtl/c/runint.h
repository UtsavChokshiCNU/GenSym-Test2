/*
 * runint.h - LISP-TO-C runtime system structures and defines
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 * These definitions are for use only internal to the runtime library.
 * This file is not #included by translated user files.
 */

#ifndef SI_RUNTIME_INTERNAL
#define SI_RUNTIME_INTERNAL
#endif

#if defined(sun) && !defined(sparc)
#define sun3
#endif

#ifdef _IBMR2
#define unix
#endif

#if defined(hp9000s300) || defined(hp9000s400)
#define hp
#endif

/* Two separate #if define's here, so that each fits on a separate line, */
/* to make the VAX preprocessor happy */
#if defined(hp9000s700) || defined(hp9000s800)
#define hp
#endif

#if !defined(sun3) && !defined(masscomp)
#include <stdlib.h>
#endif

#if !defined(WIN32)
#ifdef _MSC_VER
#include <bios.h>
#include <dos.h>
#include <graph.h>
#include <fcntl.h>
#endif
#else
#include <dos.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <malloc.h>
#endif /* Win32 */

#ifdef __ZTC__
#include <bios.h>
#include <dos.h>
#include <fcntl.h>
#include <sys/stat.h>
#endif

/* What about <sys/types.h> ?  <sys/stat.h> ? */

#if defined(VMS)
#include <unixlib.h>
#include <unixio.h>
#include <types.h>
#include <stat.h>
#include <time.h>
#include <socket.h>
#endif



#if !defined(_MSC_VER) && !defined(__ZTC__) && !defined(VMS)
#ifndef NeXT
#include <unistd.h>
#endif

/* hp only finds some libraries if this is defined. */
#ifdef hp
#define _INCLUDE_POSIX_SOURCE
#endif

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>

#if !defined(oldsequent) && !defined(NeXT) && !defined(__APPLE__)
#include <malloc.h>
#endif /* not oldsequent or NeXT */

#endif /* not VMS and not MSDOS */

#if !defined(WIN32)
#if defined(_MCS_VER) && defined(_MSC_HUGE)
/* only for huge memory model !! */
#define malloc(size)  halloc(1L, size)
#endif
#endif /* not Win32 */

#if SI_SUPPORT_THREAD

#if defined(Platform_Windows)
/* InterlockedCompareExchange64 (see MSDN) says: 
 * The variables for this function must be aligned on a 64-bit (8 bytes) boundary; otherwise,
 * this function will behave unpredictably on multiprocessor x86 systems and any
 * non-x86 systems. See _aligned_malloc. */
#   define malloc(size)		_aligned_malloc(size, 8)
#   define free(p)		_aligned_free(p)
#elif defined(Platform_Linux)
/* SI_STAMP() requires this for bypassing ABA problems in __sync_val_compare_and_swap;
 * Although the CAS function itself doesn't require alignments explicitly.
 * NOTICE that LSB didn't define aligned_malloc(), and there's no correspond
 * special free() needed. */
/*#   define malloc(size)		aligned_alloc(8, size)*/
/* With `aligned_malloc` it (expectedly) doesn't link;
 * with `aligned_alloc` it links, but both SymScale and mtg2 sigsegv at SETUP_REST, list.c:44
 * without any define both SymScale & mtg2 work (at least start).
 */
#endif

#endif /* SI_SUPPORT_THREAD */

#if defined(sun)
#define SI_BCOPY_HANDLES_OVERLAP  1
#else
#define SI_BCOPY_HANDLES_OVERLAP  0
#endif

//[tam.srogatch][2010-09-27]: What else could it use?
#define HAVE_MEMCPY
#define HAVE_MEMMOVE

/* If a machine doesn't have memcpy, use bcopy instead */
#ifdef HAVE_MEMCPY
#define MEMCPY(to, from, n) (memcpy(to, from, n))
#else
#define MEMCPY(to, from, n) (BCOPY(from, to, n))
#endif

/* If a machine doesn't have bcopy, use memmove if available */
#ifdef HAVE_BCOPY
#define BCOPY(from, to, n) (bcopy(from, to, n))
#else
#ifdef HAVE_MEMMOVE
#define BCOPY(from, to, n) (memmove(to, from, n))
#else /*HAVE_MEMMOVE*/
#include "Need a replacement for bcopy/memmove on this machine"
#endif /*HAVE_MEMMOVE*/
#endif /*HAVE_BCOPY*/

/* sys/time.h: for microsecond interval timer */
#if defined(sun) || defined(sgi) || defined(DGUX) || defined(motorola) || defined(_IBMR2) || defined(__osf__) || defined(_nst) || defined(linux) || defined(hp) || defined(__APPLE__)
#include <sys/time.h>
#else
/* time.h: for localtime() and struct tm */
/* This is included by <sys/time.h> */
#include <time.h>
#endif /* not sun or sgi */

#if defined(_IBMR2) || defined(linux)
#include <time.h>
#endif

/* The following is a workaround that we use to provide in oder to
fix a bug on IBM RISC (RS6000); While it seems like fixed right now,
some customers might happen to use the old C include files
on IBM RISC. That is why  we preserve the workaround, but
with flag _IBMR2_old instead of _IBMR2. Customers who find timeval
unavailable, must replace _IBMR2_old by _IBMR2. (Dmitry, Aug'92)
*/
#ifdef _IBMR2_old
/* This ought to be defined in <time.h> or <sys/time.h>, but isn't */
struct timeval {
    long tv_sec;
    long tv_usec;
};
#endif

/* strings.h is from Berkeley, string.h is from AT&T.  string.h defines
   more things, e.g. strpbrk */
#ifdef oldsequent
#include <strings.h>
#else  /* not oldsequent */
#include <string.h>
#endif /* not oldsequent */

/* It would be nice to #include <limits.h> to get the definition of
   CHAR_BIT (= number of bits per character).  But it's not available on
   all platforms. */

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

/***********************************/


typedef char BOOLE;

/* Fix for VMS setjmp() */
/* [No longer needed]
   #ifdef VMS
   #define _JBLEN 15
   #endif

   #ifdef oldsequent
   #define _JBLEN 11
   #endif
 */

/* Special tokens */

enum SI_more_token_id {
    SI_TOKEN_ID_VALUE = SI_MORE_TOKEN_IDS, /* Property indicator */
    SI_TOKEN_ID_FUNCTION,	/* Property indicator */
    SI_TOKEN_ID_SETF_FUNCTION,	/* Property indicator */
    SI_TOKEN_ID_NAME,		/* Property indicator */
    SI_TOKEN_ID_DOT,		/* Used internally to reader */
    SI_TOKEN_ID_EOF,		/* Used by load */
    SI_TOKEN_ID_MACRO,		/* Used by symbol-macro and macro_function */
    SI_TOKEN_ID_SPECIAL_OPERATOR
};

#define DOT_TOKEN		SI_MAKE_TOKEN(SI_TOKEN_ID_DOT)
#define SI_EOF_TOKEN            SI_MAKE_TOKEN(SI_TOKEN_ID_EOF)
#define SI_MACRO_TOKEN		SI_MAKE_TOKEN(SI_TOKEN_ID_MACRO)
#define SI_SPECIAL_OPERATOR_TOKEN SI_MAKE_TOKEN(SI_TOKEN_ID_SPECIAL_OPERATOR)

enum SI_special_op {
  SI_BEGIN_SPECIAL_OP = 0,
  SI_SPECIAL_OP_BLOCK,
  SI_SPECIAL_OP_CATCH,
  SI_SPECIAL_OP_EVAL_WHEN,
  SI_SPECIAL_OP_FLET,
  SI_SPECIAL_OP_FUNCTION,
  SI_SPECIAL_OP_GO,
  SI_SPECIAL_OP_IF,
  SI_SPECIAL_OP_LABELS,
  SI_SPECIAL_OP_LET,
  SI_SPECIAL_OP_LET_STAR,
  SI_SPECIAL_OP_LOAD_TIME_VALUE,
  SI_SPECIAL_OP_LOCALLY,
  SI_SPECIAL_OP_MACROLET,
  SI_SPECIAL_OP_MULTIPLE_VALUE_CALL,
  SI_SPECIAL_OP_MULTIPLE_VALUE_PROG1,
  SI_SPECIAL_OP_PROGN,
  SI_SPECIAL_OP_PROGV,
  SI_SPECIAL_OP_QUOTE,
  SI_SPECIAL_OP_RETURN_FROM,
  SI_SPECIAL_OP_SETQ,
  SI_SPECIAL_OP_SYMBOL_MACROLET,
  SI_SPECIAL_OP_TAGBODY,
  SI_SPECIAL_OP_THE,
  SI_SPECIAL_OP_THROW,
  SI_SPECIAL_OP_UNWIND_PROTECT,
  SI_END_SPECIAL_OP
};

typedef struct {
    SI_Header h;
    Object real;
    Object imag;
} SI_Complex;

#define COMPLEX_REAL(o)		SI_STORED_OBJECT_FIELD(o, SI_Complex, real)
#define COMPLEX_IMAG(o)		SI_STORED_OBJECT_FIELD(o, SI_Complex, imag)


typedef struct {
    SI_Header h;
    Object *location;
#if SI_SUPPORT_THREAD
    short local_count[VALUE_CELL_SLOTS];
    Object *local_location[VALUE_CELL_SLOTS];
#endif
} SI_Value_cell;

/* A value-cell holds a pointer to a C global variable */
#define VALUE_CELL_LOCATION(a)  SI_STORED_OBJECT_FIELD(a, SI_Value_cell, location)
#define VALUE_CELL_P(a)      SI_STORED_OBJECT_TYPEP(a, VALUE_CELL_TYPE)

#if SI_SUPPORT_THREAD
#define VALUE_CELL_LOCAL_COUNT(a, index) \
    SI_STORED_OBJECT_FIELD(a, SI_Value_cell, local_count)[index]
#define VALUE_CELL_LOCAL_LOCATION(a, index) \
    SI_STORED_OBJECT_FIELD(a, SI_Value_cell, local_location)[index]
#endif

typedef struct {
    SI_Header h;
    UCHAR	x;		/* current x position */
    UCHAR	y;		/* current y position */
    UCHAR	left;		/* left corner of window */
    UCHAR	top;		/* top line of window */
    UCHAR	height;		/* number of lines in window */
    UCHAR	width;		/* number of columns in window */
    short	attribute;	/* screen attribute */
} SI_Window;



#define SI_SET_STORED_OBJECT_TYPE(o, t) \
    (SI_STORED_OBJECT_FIELD(o, SI_Header, type) = (unsigned)(t))

#define INDIRECT_SYMBOL(a)      ISYMBOL_PLIST(a)

#define PATHNAME_PATH(a)	SI_STORED_OBJECT_FIELD(a, SI_Pathname, path)

#define COPY_CONS(a)		(ATOM(a) ? (a) : cons(M_CAR(a), M_CDR(a)))

/* KOPT and UNSUPPLIED_P */
#define KOPT			_
#define UNSUPPLIED_P(a)         ((a) == KOPT)

/*
 * Constants:
 */

#define LONGBITS 64		/* See numbers.c */

#define MAXFMTSTR 20000		/* buffer to hold result of format call */
#define MAXINITSYMS 2048

/* Stream element types */
#define S_STRING_CHAR		0
#define S_CHARACTER		1
#define S_BIT			2
#define S_INTEGER		3
#define S_UNSIGNED_BYTE_8	4
#define S_UNSIGNED_BYTE_16	5
#define S_UNSIGNED_BYTE_32	6
#define S_SIGNED_BYTE_8		7
#define S_SIGNED_BYTE_16	8
#define S_SIGNED_BYTE_32	9
#define S_UNSIGNED_BYTE		10
#define S_SIGNED_BYTE		11

/* Stream types */
#define AUX_STREAM		0x00
#define BROADCAST_STREAM	0x10
#define CONCATENATED_STREAM	0x20
#define ECHO_STREAM		0x30
#define FILE_STREAM		0x40
#define SYNONYM_STREAM		0x50
#define TWO_WAY_STREAM		0x60
#define STRING_INPUT_STREAM	0x70
#define STRING_OUTPUT_STREAM	0x80
#define INTERACTION_STREAM	0x90

/* Stream directions */
#define S_INPUT			0x000
#define S_OUTPUT		0x100
#define S_IO			0x200
#define S_PROBE			0x300

/* Stream closed_p */
#define S_CLOSED_P		0x400

/* Hash methods */
#define HM_EQUAL	0
#define HM_EQL		1
#define HM_EQ		2
#define HM_FIXED	0
#define HM_PERCENTAGE	1

/* Microsoft C defines these already */
#ifndef _MAX_PATH
#define _MAX_PATH 144
#define _MAX_DRIVE 3
#define _MAX_DIR 130
#define _MAX_FNAME 130
#define _MAX_EXT 130
#endif

/* Rest argument protection */
/* do { ... } while(0)  is an idiom invented by the authors of MIT Scheme. */
/* Its purpose is to make a macro have correct single-statement syntax. */

#define SETUP_REST(nargs, rest)  \
    do {long _nargs = (nargs);                 \
        long _rest_index;                      \
        va_list _ap;                          \
        SI_va_start(_ap,nargs);                        \
        rest = (Object *)Stack;               \
        Stack += _nargs;                      \
        for(_rest_index = 0; _rest_index < _nargs; ++_rest_index) \
            rest[_rest_index]                 \
                = va_arg(_ap, Object);        \
        va_end(_ap);                          \
    } while(0)

/* These allow to pass non-Object argumants using the Lisp stack. */
#define SI_STACK_PUSH(a, t) (STACK_PUSH(((t) a)))
#define SI_STACK_POP(t)     ((t)STACK_POP())

/* These are used internally in the runtime library for temporary consing.
   They replace SAVE_STRING_HEAP_POS and RESTORE_STRING_HEAP_POS. */

#define BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos) \
    SAVE_CURRENT_AREA(prev_area); \
    SET_CURRENT_AREA(Dynamic_area); \
    SAVE_FRONTIER(prev_pos)

#define END_LOCAL_ALLOCATION(prev_area, prev_pos) \
    RESTORE_FRONTIER(prev_pos); \
    RESTORE_CURRENT_AREA(prev_area)


/* Hack to silence lint. */
#ifdef lint
#undef va_arg
#define va_arg(list,mode) ((mode *)(unsigned long)(list += sizeof(mode)))[-1]
#endif


/* Obsolescent */
#define BIGNUM_VALUE(a)		0
#define OBIGNUMP(a)		0
typedef Object FIXNUM;
#define SI_UNTAG_WINDOW(o)	SI_UNTAG_STORED(o, SI_Window) /* format.c */
#define ISYMBOL_PLIST(o)	SI_SYMBOL_PLIST(o)
#define USYMBOL_PLIST(s) 	SI_SYMBOL_PLIST(s)

/* VECTOR_CONTENTS used in strings.c, coerce.c, packages.c.
   Used at least once as lvalue */
#define VECTOR_CONTENTS(o)	SI_VECTOR_CONTENTS(o, SI_PVT_Char)/*CONTENTS_POINTER*/

/* hash.c pred.c */
#define VECTOR_SIZE(o) \
    (SI_VECTOR_PRIMITIVE_P(o) ? SI_PRIMITIVE_VECTOR_LENGTH(o) \
			      : SI_GENERAL_VECTOR_TOTAL_SIZE(o))

/* format.c seqsupp.c */
#define SI_VECTOR_LENGTH(o) \
    (SI_VECTOR_PRIMITIVE_P(o) ? SI_PRIMITIVE_VECTOR_LENGTH(o) \
			      : IFIX(SI_GENERAL_VECTOR_FILL_POINTER(o)))

#if SI_SUPPORT_THREAD

#define SI_PUSH_SPECIAL_DFLTD(variable, newValue, nesting) { \
    SI_sf[nesting].link = SI_Special_stack; \
    SI_sf[nesting].location = &SI_Special_data->variable##_LOCAL; \
    SI_sf[nesting].saved_value = variable; \
    SI_sf[nesting].saved_symbol = UNBOUND; \
    SI_sf[nesting].local_count = &SI_Special_count->variable##_COUNT; \
    SI_Special_stack = &SI_sf[nesting]; \
    \
    SI_Special_data->variable##_LOCAL = (SUPPLIEDP(newValue) ? newValue : variable); \
    SI_Special_count->variable##_COUNT += 1; \
}

#else

#define SI_PUSH_SPECIAL_DFLTD(glob, arg, frame) \
     PUSH_SPECIAL(glob, (SUPPLIEDP(arg) ? arg : glob), frame)

#endif

/* Simple renamings: */

#define FIXNUMBITS 		SI_BITS_PER_FIXNUM /* numbers.c */
#define PNODE_TYPE(o) 		SI_STORED_OBJECT_TYPE(o)
#define IMMEDIATE_P(o)		SI_IMMEDIATEP(o)
#define T_FIX(n) 		FIX(n)
#define T_IFIX(o)		IFIX(o)
#define ALIGNEDTYPE SI_ALIGNED_TYPE


/* Don't put a comment on the last line, since the Masscomp preprocessor*/
/* is broken and will complain */
#define ISSIZE(o)		VECTOR_SIZE(o)
