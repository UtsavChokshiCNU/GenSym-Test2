/* object.h - Lisp-to-C object representation
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

/*
 * configuration incompatibility detection
 */
#if SI_PREVENT_MISLINKING && !(defined(lint))

#define CONFIG_REQUIRES(SI_config_symbol, dummyvar) \
    extern int SI_config_symbol;                    \
    static int *dummyvar = &SI_config_symbol;


#define CONFIG_PROVIDES(SI_config_symbol)           \
    int SI_config_symbol;

#else
#define CONFIG_REQUIRES(x,y)    /* requires x */
#define CONFIG_PROVIDES(x)      /* provides x */
#endif

/*
 * checking gc and heap configurations here, for now
 */
#if SI_COPYING_COLLECTOR
CONFIG_REQUIRES(SI_config_copying_collector, local_copying_collectorp)
#else
CONFIG_REQUIRES(SI_config_not_copying_collector, local_copying_collectorp)
#endif
#if SI_SEGMENTED_DYNAMIC_AREA
CONFIG_REQUIRES(SI_config_segmented_dynamic_area, local_segmentedp)
#else
CONFIG_REQUIRES(SI_config_not_segmented_dynamic_area, local_segmentedp)
#endif
#if SI_VISIT_EXACTLY_ONCE
CONFIG_REQUIRES(SI_config_exactly_once, local_exactly_oncep)
#else
CONFIG_REQUIRES(SI_config_not_exactly_once, local_exactly_oncep)
#endif
#if SI_TAG_WIDTH == 1
CONFIG_REQUIRES(SI_config_1_tag_width, local_tag_width_value)
#else
#if SI_TAG_WIDTH == 2
CONFIG_REQUIRES(SI_config_2_tag_width, local_tag_width_value)
#else
#if SI_TAG_WIDTH == 3
CONFIG_REQUIRES(SI_config_3_tag_width, local_tag_width_value)
#else

#endif
#endif
#endif

typedef unsigned char UCHAR;

/* Define our own toupper and tolower since some UNIX systems
 * don't check islower and isupper. */
/* -- Should have SI_ prefixes */

#ifndef TOUPPER
#define TOUPPER(c)	((islower(c)) ? toupper(c) : (c) )
#endif

#ifndef TOLOWER
#define TOLOWER(c)	((isupper(c)) ? tolower(c) : (c) )
#endif

/* The VAX C compiler has to be explicitly told to align things 
   note that ALPHA does not */
#if defined(vms) && defined(vax)
#define SI_ALIGNED_TYPE _align (LONGWORD)
#else
#define SI_ALIGNED_TYPE
#endif

/* lint doesn't want you to compare expressions whose types are enumerated */
#define SI_ENUM_LT(e1, e2) 	((unsigned) (e1) < (unsigned) (e2))
#define SI_ENUM_LE(e1, e2) 	((unsigned) (e1) <= (unsigned) (e2))
#define SI_ENUM_GT(e1, e2) 	((unsigned) (e1) > (unsigned) (e2))
#define SI_ENUM_GE(e1, e2) 	((unsigned) (e1) >= (unsigned) (e2))
#define SI_ENUM_EQ(e1, e2) 	((unsigned) (e1) == (unsigned) (e2))
#define SI_ENUM_NE(e1, e2) 	((unsigned) (e1) != (unsigned) (e2))

/* C type implementing Lisp DOUBLE-FLOAT type */
/* -- Should have SI_ prefix (unless produced by MF) */
typedef double DOUBLE;


/*
 * Object representation
 */

/* The exact definition of Object is pretty much arbitrary, as long as
   (1) it's either an integer or pointer type, and
   (2) sizeof(Object) == sizeof(SI_Long) == sizeof(SI_Ulong).
   The main considerations are type checking and debuggability.

   NOTE: now we have changed to use a C struct pointer for debuggability.
   see EE Addin for Chestnut RTL by Chun Tian (binghe), June 2014.
 */

typedef struct _OBJECT {
    SI_Ulong object[0];
} *Object;

#define SI_HAVE_OBJECT_DEFINED 1

/* Immediate values: NIL, fixnums, and other immediates */

#define Nil	NIL		/* NIL is initialized magically */

#if SI_NIL_IS_ZERO

#define SI_IMMEDIATEP(o)	((o) == NIL || (SI_Ulong) (o) & (SI_Ulong) 1L)

#else

#define SI_IMMEDIATEP(o)	((SI_Ulong) (o) & (SI_Ulong) 1L)

#endif

#define TRUEP(o)		((o) != NIL)

/* Tagging scheme */

#define SI_FIXNUM_TAG_VALUE	1 /* 0, 1, 2, or 3 */
#define SI_STORED_TAG_VALUE	0 /* (SI_FIXNUM_TAG_VALUE ^ 1) */

enum SI_tag {
    SI_FIXNUM_TAG      = SI_FIXNUM_TAG_VALUE,
    SI_EVEN_FIXNUM_TAG = SI_FIXNUM_TAG_VALUE,
    SI_ODD_FIXNUM_TAG  = SI_FIXNUM_TAG_VALUE ^ 4,
    SI_OTHER_IMMED_TAG = SI_FIXNUM_TAG_VALUE ^ 2,
    SI_CONS_TAG        = SI_STORED_TAG_VALUE,

#if SI_TAG_WIDTH == 1

    SI_SYMBOL_TAG      = SI_STORED_TAG_VALUE,
    SI_ARRAY_TAG       = SI_STORED_TAG_VALUE,
    SI_NUMBER_TAG      = SI_STORED_TAG_VALUE,
    SI_INSTANCE_TAG    = SI_STORED_TAG_VALUE

#else
#if SI_TAG_WIDTH == 2

    SI_SYMBOL_TAG      = SI_STORED_TAG_VALUE ^ 2,
    SI_ARRAY_TAG       = SI_STORED_TAG_VALUE ^ 2,
    SI_NUMBER_TAG      = SI_STORED_TAG_VALUE ^ 2,
    SI_INSTANCE_TAG    = SI_STORED_TAG_VALUE ^ 2

#else
#if SI_TAG_WIDTH == 3

    SI_SYMBOL_TAG      = SI_STORED_TAG_VALUE ^ 2,
    SI_ARRAY_TAG       = SI_STORED_TAG_VALUE ^ 4,
    SI_NUMBER_TAG      = SI_STORED_TAG_VALUE ^ 6,
    SI_INSTANCE_TAG    = SI_STORED_TAG_VALUE ^ 6

#else

#error "Unimplemented value for SI_TAG_WIDTH"

#endif /* SI_TAG_WIDTH == 3 */
#endif /* SI_TAG_WIDTH == 2 */
#endif /* SI_TAG_WIDTH == 1 */

};

#define SI_TAG_OF(o)            ((SI_Long)(o) & ~(-1L << SI_TAG_WIDTH))
#define SI_SET_TAG(u, tag)      ((Object)((SI_Long)(u) | (SI_Long)(tag)))

/* Fixnums */

#define SI_FIXNUM_SHIFT 	2
#define SI_FIXNUM_TAG_MASK 	3 /* (1L << SI_FIXNUM_SHIFT) - 1 */
#define SI_FIXNUM_ONE   	4 /* (1L << SI_FIXNUM_SHIFT) */

#if SI_PRECONFIGURED_IMMEDIATES
#define SI_BITS_PER_FIXNUM	SI_PRECONFIGURED_FIXNUM_SIZE
#else
#define SI_BITS_PER_FIXNUM	(SI_BITS_PER_OBJECT-SI_FIXNUM_SHIFT)
#endif

/* -- Should have SI_ prefix */
#ifndef IMOST_POSITIVE_FIXNUM
#define IMOST_POSITIVE_FIXNUM	(((SI_Long)1L << (SI_BITS_PER_FIXNUM-1)) - 1)
#endif
#define IMOST_NEGATIVE_FIXNUM	((SI_Long)-1L << (SI_BITS_PER_FIXNUM-1))

/* These macros are used to tag/untag a 64-bit Lisp pointer (usually a cons) with
 * a 16-bit timestamp. It's for CAS (compare_and_swap) to resolve the ABA problem:
 *
 *     http://en.wikipedia.org/wiki/ABA_problem
 *
 * 32-bit systems are not supported. --binghe, 12/12/2013 */

/* All pointers are aligned to 64 bits (low 4 bits are not used (see runint.h),
 * however we use the high 16 bits on x86_64). For 64-bit platforms other than x86_64, the
 * low 4 bits should be used instead. */
#if SI_SUPPORT_THREAD && defined(Platform_64bit) && defined(_M_X64) || defined(__x86_64__)
/* NOTE: 1. IMMEDIATEs are ignored, 2. old stamps must be clean up before setting a new one. */
# define SI_STAMP(x, s)  ((Object)(SI_IMMEDIATEP(x) ? (SI_Long)(x) : \
    (((SI_Long)(x) & (SI_Long)0xffffffffffff) | ((SI_Long)(s) << 48))))
# define SI_GET_STAMP(x) ((SI_Long)(x) >> 48)
# define SI_UNSTAMP(x)   ((Object)((SI_Long)(x) & (SI_Long)0xffffffffffff))
#else /* Legacy G2 */
# define SI_STAMP(x, s)  (x)
# define SI_GET_STAMP(x) (0)
# define SI_UNSTAMP(x)   (x)
#endif

/* >>0 and &* are no-ops, but they make the C compiler catch type errors */
#define FIX(x) \
    SI_SET_TAG((SI_Long)((fixnum_arithmetic_type)(x) << SI_FIXNUM_SHIFT), SI_FIXNUM_TAG)
#define IFIX(o) 		((SI_Long)((fixnum_arithmetic_type)(o) >> SI_FIXNUM_SHIFT))
#define FIXNUMP(o) \
  ((enum SI_tag)((SI_Long)(o) & SI_FIXNUM_TAG_MASK) == SI_FIXNUM_TAG)
#define ZERO			FIX(0)

/* Other (non-NIL, non-fixnum) immediates:
   . Characters                                    code  00  immedtag
   . Tokens                                          id  10  immedtag
   . SV headers            length [gcbit]  length-status  1  immedtag
   . Other headers  length  type  [gcbit]  length-status  1  immedtag
   */

#if SI_TAG_WIDTH <= 2
#define SI_OTHER_IMMED_SHIFT 	2
#define SI_OTHER_IMMED_TAG_MASK 3 /* (1L << SI_OTHER_IMMED_SHIFT) - 1 */
#else
#define SI_OTHER_IMMED_SHIFT 	SI_TAG_WIDTH
#define SI_OTHER_IMMED_TAG_MASK ((1L << SI_OTHER_IMMED_SHIFT) - 1)
#endif

/* The next bit distinguishes headers from nonheaders */
#define SI_HEADER_SHIFT 	(SI_OTHER_IMMED_SHIFT + 1)
#define SI_NONHEADER_TAG	((int)SI_OTHER_IMMED_TAG)
#define SI_HEADER_TAG \
    (SI_OTHER_IMMED_TAG ^ (1L << SI_OTHER_IMMED_SHIFT))

/* If nonheader, the next bit distinguishes characters from tokens */
#define SI_CHAR_SHIFT		(SI_HEADER_SHIFT + 1)
#define SI_CHAR_TAG		SI_NONHEADER_TAG
#define SI_TOKEN_TAG		(SI_NONHEADER_TAG ^ (1L << SI_HEADER_SHIFT))

/* Characters */

#define CHR(x) \
    ((Object)((((int)(x)) << SI_CHAR_SHIFT) | SI_CHAR_TAG))
#define CHARACTERP(o) \
    (((SI_Long)(o) & ((1L << SI_CHAR_SHIFT) - 1)) == SI_CHAR_TAG)

/* -- Should have SI_ prefix */
#define ICHAR_INT(o)            ((SI_Long)(o) >> SI_CHAR_SHIFT)

#define CHR_CODE(o)  		(ICHAR_INT(o) & 0x00ff)
#define CHR_BITS(o)		((ICHAR_INT(o) >> 8) & 0x00ff)
#define CHR_FONT(o)		(o, 0)


/* Tokens (= markers) */

#define SI_MAKE_TOKEN(id) \
    ((Object)(((id) << SI_CHAR_SHIFT) | SI_TOKEN_TAG))

enum SI_token_id {
    SI_TOKEN_ID_UNSUPPLIED,
    SI_TOKEN_ID_UNBOUND,
    SI_TOKEN_ID_PROTECT_MARKER,
    SI_TOKEN_ID_UNWIND_PROTECT_MARKER,
    SI_TOKEN_ID_NO_APPLICABLE_METHOD_MARKER,

    /* Tokens related to storage management. */
    SI_TOKEN_ID_UNINITIALIZED,	    /* Used by runtime generally */
    SI_TOKEN_ID_GC_LIVE,	    /* Used by mark+sweep garbage collector */
    SI_TOKEN_ID_GC_FORWARDING,      /* Used by stop&copy garbage collector */
    SI_TOKEN_ID_GC_ALIGNING,        /* Used by garbage collector */
    SI_TOKEN_ID_GC_NONRELOCATABLE,  /* Used by garbage collector */

    SI_MORE_TOKEN_IDS
};

#define _                    	SI_MAKE_TOKEN(SI_TOKEN_ID_UNSUPPLIED)
#define UNBOUND		     	SI_MAKE_TOKEN(SI_TOKEN_ID_UNBOUND)
/* -- Should have SI_ prefix */
#define PROTECT_MARKER	     	SI_MAKE_TOKEN(SI_TOKEN_ID_PROTECT_MARKER)
#define SI_UNWIND_PROTECT_MARKER \
    SI_MAKE_TOKEN(SI_TOKEN_ID_UNWIND_PROTECT_MARKER)
#define SI_NO_APPLICABLE_METHOD_MARKER \
    SI_MAKE_TOKEN(SI_TOKEN_ID_NO_APPLICABLE_METHOD_MARKER)

/* These need to be here for use by the stack allocation macros. */
#define SI_UNINITIALIZED_MARKER	  SI_MAKE_TOKEN(SI_TOKEN_ID_UNINITIALIZED)
#define SI_ALIGNMENT_MARKER	  SI_MAKE_TOKEN(SI_TOKEN_ID_GC_ALIGNING)

/* This must be here for use by quick consing */
#define SI_FORWARDING_MARKER  SI_MAKE_TOKEN(SI_TOKEN_ID_GC_FORWARDING)
/* This must be here for use by stack allocation and static object macros */
#define SI_NONRELOCATABLE_MARKER  SI_MAKE_TOKEN(SI_TOKEN_ID_GC_NONRELOCATABLE)

#ifdef SI_RUNTIME_INTERNAL
#define LIVE_MARKER		SI_MAKE_TOKEN(SI_TOKEN_ID_GC_LIVE)
#endif

/* Headers */

#define SI_TYPE_WIDTH		6
#define SI_LENGTH_STATUS_WIDTH	4
#define SI_STUFF_WIDTH 		8 /* used for function nargs+bits, and more */
#define SI_GCALIGN_WIDTH        1 /* used to mark specially aligned objects */
#define SI_GCRELOCATE_WIDTH     1 /* used to mark all dynamic area objects */


/* note that when  sizeof(unsigned) < sizeof(long),
   SI_HEADER_REMAINING_BITS might not fit into "unsigned" bitfield. */
#define SI_HEADER_REMAINING_BITS  \
       (SI_HEADER_SHIFT + SI_TYPE_WIDTH + \
        SI_LENGTH_STATUS_WIDTH + SI_GCALIGN_WIDTH + \
        SI_GCRELOCATE_WIDTH + SI_STUFF_WIDTH)

#if (SI_BITS_PER_OBJECT - SI_HEADER_REMAINING_BITS) < 16
#define SI_GCLENGTH_WIDTH  (SI_BITS_PER_OBJECT - SI_HEADER_REMAINING_BITS)
#else 
#define SI_GCLENGTH_WIDTH  16L /* seems like enough, tested on DEC ALPHA */
#endif

#define SI_TYPE_MASK            ((1L << SI_TYPE_WIDTH) - 1L)

#if RTL_BIG_ENDIAN

typedef struct {
    unsigned stuff         : SI_STUFF_WIDTH;
    unsigned gclength	   : SI_GCLENGTH_WIDTH;
    unsigned gcaligned	   : SI_GCALIGN_WIDTH;
    unsigned gcrelocatable : SI_GCRELOCATE_WIDTH;
    unsigned type	   : SI_TYPE_WIDTH;
    unsigned length_status : SI_LENGTH_STATUS_WIDTH;
    unsigned tag	   : SI_HEADER_SHIFT;
} SI_ALIGNED_TYPE SI_Header;

#if SI_OBJECT_INITIALIZERS_WORK
#define SI_HEADER(type, stuff) \
    {stuff, 0, (unsigned)SI_GC_UNALIGNED, (unsigned)SI_GC_NONRELOCATABLE, \
       (unsigned)(type), (unsigned)SI_UGLY,\
       (unsigned)SI_HEADER_TAG}
#define SI_PRIMITIVE_VECTOR_HEADER(type, etype) \
    {etype, 0, (unsigned)SI_GC_UNALIGNED, (unsigned)SI_GC_NONRELOCATABLE, \
       (unsigned)(type), (unsigned)etype,\
       (unsigned)SI_HEADER_TAG}
#endif /* SI_OBJECT_INITIALIZERS_WORK */

CONFIG_REQUIRES(SI_config_big_endian, local_big_endianp)

#else

typedef struct {
    unsigned tag	   : SI_HEADER_SHIFT;
    unsigned length_status : SI_LENGTH_STATUS_WIDTH;
    unsigned type	   : SI_TYPE_WIDTH;
    unsigned gcrelocatable : SI_GCRELOCATE_WIDTH;
    unsigned gcaligned	   : SI_GCALIGN_WIDTH;
    unsigned gclength	   : SI_GCLENGTH_WIDTH;
    unsigned stuff         : SI_STUFF_WIDTH;
} SI_ALIGNED_TYPE SI_Header;

#if SI_OBJECT_INITIALIZERS_WORK
#define SI_HEADER(type, stuff) \
    {(unsigned)SI_HEADER_TAG, \
	 (unsigned)SI_UGLY, (unsigned)(type), \
	 SI_GC_NONRELOCATABLE, SI_GC_UNALIGNED, 0, stuff}
#define SI_PRIMITIVE_VECTOR_HEADER(type, etype) \
    {(unsigned)SI_HEADER_TAG, \
	 (unsigned)etype, (unsigned)(type), \
	 SI_GC_NONRELOCATABLE, SI_GC_UNALIGNED, 0, etype}
#endif /* SI_OBJECT_INITIALIZERS_WORK */

CONFIG_REQUIRES(SI_config_not_big_endian, local_big_endianp)

#endif /* RTL_BIG_ENDIAN */

/*
 * Object type codes, for headers.
 * NUMBERP is type <= COMPLEX_TYPE
 * SYMBOLP is a range check on the type
 * external-p check for symbols is also a range check (>= ESYMBOL_TYPE)
 * ARRAYP is type >= 64
 * (Non-displaced) array element type is type & 15
 */

enum SI_type {
    SI_UNUSED_TYPE_1,		/* for redundancy, avoid using zero */

    /* Ordering of number type is used to determine coercions and contagion. */
    FIXNUM_TYPE,		/* used only internally in numbers.c */
    LONG64_TYPE,
    OBIGNUM_TYPE,		/* obsolescent */
    BIGNUM_TYPE,
    RATIO_TYPE,
    DOUBLE_TYPE,
    COMPLEX_TYPE,

    INDIRECT_TYPE,		/* must precede symbol types */
#define SI_LEAST_SYMBOL_TYPE   	SYMBOL_TYPE
    SYMBOL_TYPE,		/* non-external initial symbol */
    MSYMBOL_TYPE,		/* non-external non-initial symbol */
    USYMBOL_TYPE,		/* uninterned symbol */

    ESYMBOL_TYPE,		/* external initial symbol */
    EMSYMBOL_TYPE,		/* external non-initial symbol */
    KEYWORD_TYPE,		/* initial keyword */
    MKEYWORD_TYPE,		/* non-initial keyword */
    NIL_TYPE,			/* ? */
#define SI_GREATEST_SYMBOL_TYPE	NIL_TYPE
    EINDIRECT_TYPE,		/* must follow symbol types */

    CONS_TYPE,
    SI_GENERAL_ARRAY_TYPE,
    SI_PRIMITIVE_VECTOR_TYPE,

    VALUE_CELL_TYPE,		/* holds pointer to Object-type C var */
    WINDOW_TYPE,

#define SI_LEAST_INSTANCE_TYPE SI_STRUCTURE_TYPE
    SI_STRUCTURE_TYPE,

    COBJECT_TYPE,
    HASH_TABLE_TYPE,
    PACKAGE_TYPE,
    PATHNAME_TYPE,
    RANDOM_STATE_TYPE,
    READTABLE_TYPE,
    STREAM_TYPE,

#if SI_SUPPORT_THREAD
    SI_THREAD_TYPE,             /* thread type */
    SI_LOCK_TYPE,               /* lock type */
    SI_COND_TYPE,               /* condition variable */
#endif /* SI_SUPPORT_THREAD */

#if SI_SUPPORT_CLOS

    SI_CLASS_WRAPPER_TYPE,
    SI_EFFECTIVE_METHOD_TYPE,
    SI_METHOD_COMBINATION_TYPE,

#define SI_LEAST_STANDARD_OBJECT_TYPE SI_STANDARD_INSTANCE_TYPE
    SI_STANDARD_INSTANCE_TYPE,
    SI_METHOD_TYPE,

#endif /* SI_SUPPORT_CLOS */

    SI_FUNCTION_TYPE,
#define SI_GREATEST_STANDARD_OBJECT_TYPE SI_FUNCTION_TYPE
#define SI_GREATEST_INSTANCE_TYPE SI_GREATEST_STANDARD_OBJECT_TYPE

    SI_GREATEST_TYPE = (1L << SI_TYPE_WIDTH) - 1
};

#define SI_PRECEDES_ISYMBOLS FIXNUM_TYPE /* Arbitrary non-symbol type */

/* GC relocatability status */
enum SI_gcrelocatability {
    SI_GC_NONRELOCATABLE,
    SI_GC_RELOCATABLE
};

/* GC alignment status */
enum SI_gcalignment {
    SI_GC_UNALIGNED,
    SI_GC_ALIGNED
};

/* GC length status / array element types */
enum SI_gcls {
    SI_BORING,
    SI_BORINGER,
    SI_UGLY,
    SI_UGLIER,
    SI_NORMAL,
    A_T,                /* 0 */
    A_STRING_CHAR,      /* 1 */
    A_SINGLE_FLOAT,     /* 2 */
    A_DOUBLE_FLOAT,     /* 3 */
    A_BIT,              /* 4 */
    A_BYTE_8,           /* 5 */
    A_BYTE_16,          /* 6 */
    A_BYTE_32,          /* 7 */
    A_BYTE_64,          /* 8 */
    A_UNSIGNED_BYTE_8,  /* 9 */
    A_UNSIGNED_BYTE_16, /* 10 */
    A_UNSIGNED_BYTE_32, /* 11 */
    A_UNSIGNED_BYTE_64  /* 12 */
};

#define SI_etype SI_gcls

/* Stored objects */

/* To support SI_TAG_WIDTH > 1, the following macro now takes
   a tag as an extra argument:
      SI_TAG_STORED
   In order to remove the tag using a subtraction instead of a mask
   operation (optimization only; saves one instruction), the following
   will also have to take a tag argument:
      SI_STORED_OBJECT_FIELD 
      SI_STORED_OBJECT_TYPE
      SI_STORED_OBJECT_TYPEP
      SI_UNTAG_STORED */


#define SI_STORED_OBJECT_P(o)       (!SI_IMMEDIATEP(o))

#if SI_STORED_TAG_VALUE == 0 && SI_TAG_WIDTH <= 1

#define SI_TAG_STORED(x,tag)        ((Object)(x))
#define SI_STORED_OBJECT_FIELD(o, t, f) \
    ((t *)(o))->f

#ifdef SI_RUNTIME_INTERNAL
#define SI_UNTAG_STORED(o, t) 	((t *)(o))
#endif

#else

#define SI_TAG_STORED(x,tag)        SI_SET_TAG(x, tag)
#define SI_STORED_OBJECT_FIELD(o, t, f) \
    ((t *)((SI_Long)(o) & (-1L << SI_TAG_WIDTH)))->f

#ifdef SI_RUNTIME_INTERNAL
#define SI_UNTAG_STORED(o, t) 	((t *)((SI_Long)(o) & (-1L << SI_TAG_WIDTH)))
#endif

#endif /* SI_STORED_TAG_VALUE == 0 etc. */

#define SI_STORED_OBJECT_HAS_HEADER_P(o) \
             (SI_STORED_OBJECT_FIELD(o, SI_Header, tag) \
              == SI_HEADER_TAG)

#define SI_STORED_OBJECT_HEADER_TYPE_FIELD(o) \
    ((enum SI_type)(SI_STORED_OBJECT_FIELD(o, SI_Header, type)))

#if SI_CONSES_HAVE_HEADERS
#define SI_STORED_OBJECT_TYPE(o) \
    ((enum SI_type)(SI_STORED_OBJECT_FIELD(o, SI_Header, type)))
#else /* !SI_CONSES_HAVE_HEADERS */
#define SI_STORED_OBJECT_TYPE(o ) \
    (SI_STORED_OBJECT_HAS_HEADER_P(o) \
     ? ((enum SI_type)(SI_STORED_OBJECT_FIELD(o, SI_Header, type))) \
     : CONS_TYPE)
#endif /* !SI_CONSES_HAVE_HEADERS */
#define SI_STORED_OBJECT_TYPEP(o, type) \
    (!SI_IMMEDIATEP(o) && SI_STORED_OBJECT_TYPE(o) == (type))


/* General allocator for most kinds of stored objects (anything that
   has a header) */

#define SI_ALLOC(c_type, type_number, tag, gcls) \
    SI_alloc((SI_Size_type)sizeof(c_type), SI_ALIGNMENT_FOR(c_type), \
             type_number, tag, gcls)

#if defined(WIN32)
/* warning C4116: '...' : unnamed type definition in parentheses
 *   This warning comes up because of the following macro (and perhaps others?)
 *   RTL whips up a structure definition on the fly to get the size of it.
 *   Seems weird, and a warning seems pretty appropriate, in general; but the
 *   macro is here and there ain't much we're gonna do about it, so we don't
 *   want to see the warning message when compiling RTL any more.  -jv, 10/30/04
 */
#  pragma warning( disable : 4116 )
#endif  /* WIN32 */

/* We assume that the following always delivers a power of 2 */
#define SI_ALIGNMENT_FOR(type) \
    (sizeof(struct {char c; type x;}) - sizeof(type))


/***************************************************************************
 *
 * Static constant support macros
 *
 **************************************************************************/
#define SI_STATIC_RELOCATION_WORDS   (SI_DYNAMICNESS_LABELED && !SI_COPYING_COLLECTOR)
#if SI_STATIC_RELOCATION_WORDS

#define SI_STATIC_RELOCATION_SIZE            (sizeof(Object)/sizeof(Object))
#define SI_STATIC_RELOCATION_INFO            SI_NONRELOCATABLE_MARKER, 
#define SI_Declare_static_relocation_field   Object  relocation_word;
#define SI_STATIC_HEADER(type,stuff) \
   SI_STATIC_RELOCATION_INFO SI_HEADER(type,stuff)
#define SI_STATIC_PRIMITIVE_VECTOR_HEADER(type,etype) \
   SI_STATIC_RELOCATION_INFO SI_PRIMITIVE_VECTOR_HEADER(type,etype)
#define SI_TAG_STORED_CONSTANT(x,tag)  \
   SI_TAG_STORED(((Object *)x) + 1, tag)

#else
#define SI_STATIC_RELOCATION_SIZE            0 /* none */
#define SI_STATIC_RELOCATION_INFO            /* none */
#define SI_Declare_static_relocation_field   /* none */
#define SI_STATIC_HEADER(type,stuff)         SI_HEADER(type, stuff)
#define SI_STATIC_PRIMITIVE_VECTOR_HEADER(type,etype)   SI_HEADER(type, etype)
#define SI_TAG_STORED_CONSTANT(x, tag)       SI_TAG_STORED(x, tag)
#endif /* must have relocation words on static constants */

/***************************************************************************
 *
 * Conses
 *
 **************************************************************************/
#if  SI_INLINED_CONS_ALLOCATOR && SI_TAG_WIDTH < 3
/* Gensym: we need make_list to be fast, not cons, since we use cons pools */
/*   Also, we want to be sure we don't allocate conses in the local area */
#define SI_QUICK_CONS 0
#else
#define SI_QUICK_CONS 0
#endif

typedef struct {
#if !SI_COPYING_COLLECTOR
    Object relocation_word;
#endif
#if SI_CONSES_HAVE_HEADERS
    SI_Ulong /* SI_Header */ h;
#endif
    Object cdr;
    Object car;
} SI_ALIGNED_TYPE SI_Cons_exposed;

#if !SI_COPYING_COLLECTOR
#define SI_TAG_FAST_CONS(x)    SI_TAG_STORED(((Object *)x) + 1, SI_CONS_TAG)
#else
#define SI_TAG_FAST_CONS(x)    SI_TAG_STORED(x, SI_CONS_TAG)
#endif

#if SI_CONSES_HAVE_HEADERS
CONFIG_REQUIRES(SI_config_conses_have_headers, local_conses_have_headersp)

typedef struct {
    SI_Header h;
    Object cdr;
    Object car;
} SI_ALIGNED_TYPE SI_Cons;

typedef struct {
    SI_Declare_static_relocation_field  /* no semicolon */
    SI_Header h;
    Object cdr;
    Object car;
} SI_ALIGNED_TYPE SI_Cons_constant;

#define CONSP(o)		SI_STORED_OBJECT_TYPEP(o, CONS_TYPE)
#if 0
#define SI_CONS()    \
    SI_ALLOC(SI_Cons, CONS_TYPE, SI_CONS_TAG, SI_NORMAL)
#endif

#else  /* headerless conses */
CONFIG_REQUIRES(SI_config_not_conses_have_headers, local_conses_have_headersp)

typedef struct {
    Object cdr;
    Object car;
} SI_ALIGNED_TYPE SI_Cons;

typedef struct {
    SI_Declare_static_relocation_field  /* no semicolon */
    Object cdr;
    Object car;
} SI_ALIGNED_TYPE SI_Cons_constant;

#define CONSP(o)		(SI_STORED_OBJECT_P(o) && \
                                 !SI_STORED_OBJECT_HAS_HEADER_P(o))

#endif /* SI_CONSES_HAVE_HEADERS */

/* GENSYM-46913, SymScale notes: (by Chun Tian (binghe))
   Disable allocation cache explicitly, as it's not used already. */

#if SI_SUPPORT_THREAD

#define SI_FLUSH_ALLOC_CACHE() 0
#define SI_RELOAD_ALLOC_CACHE() 0

#else /* SI_SUPPORT_THREAD */

#define SI_FRONTIER         SI_cached_frontier
#define SI_ALLOC_LIMIT      SI_cached_limit

#define SI_FLUSH_ALLOC_CACHE()    \
  (Current_area->current_segment->frontier = (void *)SI_cached_frontier)
#define SI_RELOAD_ALLOC_CACHE()   \
  ((SI_cached_frontier = (Object *)Current_area->current_segment->frontier), \
   (SI_cached_limit = (Object *)Current_area->current_segment->limit))

#endif /* SI_SUPPORT_THREAD */

#if SI_QUICK_CONS && SI_SUPPPORT_THREAD
#include "SI_QUICK_CONS is incompatible with SI_SUPPORT_THREAD"
#endif

#if SI_QUICK_CONS

#if !SI_COPYING_COLLECTOR
#define SI_INIT_CONS_RELOC_WORD(cfrunteer)  \
  ((cfrunteer)->relocation_word = ((Current_area == &Dynamic_area)  \
			   ? SI_FORWARDING_MARKER : SI_NONRELOCATABLE_MARKER))
#else
#define SI_INIT_CONS_RELOC_WORD(x)  /* none */ 0
#endif
#if SI_CONSES_HAVE_HEADERS
/* inefficiency: the gcrelocate field must be set correctly */
#define SI_INIT_CONS_HEADER(cfrunteer)  \
 (((cfrunteer)->h = \
    (((unsigned)CONS_TYPE) << (SI_HEADER_SHIFT+SI_LENGTH_STATUS_WIDTH)) \
    | ((unsigned)SI_HEADER_TAG) \
    | (((unsigned)(sizeof(SI_Cons)/sizeof(Object))) << \
       (SI_HEADER_SHIFT+SI_LENGTH_STATUS_WIDTH+SI_TYPE_WIDTH \
	+SI_GCRELOCATE_WIDTH+SI_GCALIGN_WIDTH)) \
    | (((unsigned)SI_NORMAL) << SI_HEADER_SHIFT) \
    | (((unsigned)SI_GC_UNALIGNED) << \
       (SI_HEADER_SHIFT+SI_LENGTH_STATUS_WIDTH+SI_TYPE_WIDTH \
	+SI_GCRELOCATE_WIDTH))), \
  ((cfrunteer)->h |= (((Current_area == &Dynamic_area) \
		       ? (unsigned)SI_GC_RELOCATABLE \
		       : (unsigned)SI_GC_NONRELOCATABLE) \
		      << \
		      (SI_HEADER_SHIFT+SI_LENGTH_STATUS_WIDTH+SI_TYPE_WIDTH))))
           
#else
#define SI_INIT_CONS_HEADER(x)  /* none */ 0
#endif
#define SI_INIT_CONS_INFO(cfrunteer)     \
  (SI_INIT_CONS_RELOC_WORD(cfrunteer), SI_INIT_CONS_HEADER(cfrunteer))

#define SI_CHECK_CONS_SPACE()   \
  (SI_FRONTIER + sizeof(SI_Cons_exposed)/sizeof(Object) < SI_ALLOC_LIMIT)
#define SI_ADVANCE_FRONTIER()   \
  (SI_FRONTIER += sizeof(SI_Cons_exposed)/sizeof(Object))
#define SI_FRONTIER_AS_CONS  ((SI_Cons_exposed *)SI_FRONTIER)
#define SI_UNADVANCED_FRONTIER() \
  (SI_FRONTIER - sizeof(SI_Cons_exposed)/sizeof(Object))
#define SI_FRONTIER_CONS_RESULT()   \
  (SI_ADVANCE_FRONTIER(), SI_TAG_FAST_CONS(SI_UNADVANCED_FRONTIER()))

#define SI_CONS() \
    (SI_CHECK_CONS_SPACE() \
     ? (SI_INIT_CONS_INFO(SI_FRONTIER_AS_CONS), SI_FRONTIER_CONS_RESULT()) \
     : SI_cons())
#define UNSAFE_CONS(a,b)   \
  (SI_INIT_CONS_INFO(SI_FRONTIER_AS_CONS),  \
   SI_FRONTIER_AS_CONS->car = a, \
   SI_FRONTIER_AS_CONS->cdr = b, \
   SI_FRONTIER_CONS_RESULT())

#define SI_UNADVANCED_FRONTIER_AS_CONS  ((SI_Cons_exposed *)SI_UNADVANCED_FRONTIER())
#define SI_UNADVANCED_FRONTIER_CONS_RESULT()   \
    SI_TAG_FAST_CONS(SI_UNADVANCED_FRONTIER())

/* choices for CONS */
/*  might duplicate code, 
    so shouldn't have large expressions for args  */
#define CONS(a,b) \
    (SI_CHECK_CONS_SPACE() \
     ? UNSAFE_CONS(a,b) \
     : SI_cons_with_gc(a,b))

/*  arguments might need to be gc protected, 
    so shouldn't have expressions requiring gc protection for args  */
/*
#define CONS(a,b) \
    (SI_CHECK_CONS_SPACE() \
     ? (SI_INIT_CONS_INFO(SI_FRONTIER_AS_CONS), SI_ADVANCE_FRONTIER(), NIL) \
     : SI_cons(), \
     SI_UNADVANCED_FRONTIER_AS_CONS->car = a, \
     SI_UNADVANCED_FRONTIER_AS_CONS->cdr = b, \
     SI_UNADVANCED_FRONTIER_CONS_RESULT())
 */

/*  has a somewhat large expansion;
    uses the stack even when it isn't necessary  */
/*
#define CONS(a,b) \
    (STACK_REF(0)=a,
     STACK_REF(1)=b,
     Stack += 2,
     SI_CHECK_CONS_SPACE() \
     ? (SI_INIT_CONS_INFO(SI_FRONTIER_AS_CONS), SI_ADVANCE_FRONTIER(), NIL) \
     : SI_cons(), \
     Stack -= 2,
     SI_UNADVANCED_FRONTIER_AS_CONS->car = STACK_REF(0), \
     SI_UNADVANCED_FRONTIER_AS_CONS->cdr = STACK_REF(1), \
     SI_UNADVANCED_FRONTIER_CONS_RESULT())
 */

#else 
#define SI_CONS()               SI_cons()
#define CONS(x,y)               cons(x,y)
#define UNSAFE_CONS(x,y)        cons(x,y)
#endif /* SI_QUICK_CONS */


#define M_CAR(o)		SI_STORED_OBJECT_FIELD(o, SI_Cons, car)
#define M_CDR(o)		SI_STORED_OBJECT_FIELD(o, SI_Cons, cdr)

#if SI_NIL_IS_ZERO || (SI_TAG_WIDTH & 2)
   /* actually the true condition would be
      (SI_CONS_TAG ^ SI_SYMBOL_TAG) & 2, 
      but cpp doesn't see enums */
#define CAR(o)			((o) == NIL ? NIL : M_CAR(o))
#define CDR(o)			((o) == NIL ? NIL : M_CDR(o))
#else
#define CAR(o)			M_CAR(o)
#define CDR(o)			M_CDR(o)
#endif

#define SET_CAR(cell,val)       (M_CAR(cell) = (val))
#define SET_CDR(cell,val)       (M_CDR(cell) = (val))


#if SI_OBJECT_INITIALIZERS_WORK

#define TAG_CONS(id)     	SI_TAG_STORED_CONSTANT(&(id), SI_CONS_TAG)

#if SI_CONSES_HAVE_HEADERS
#define SI_INITIALIZER_FOR_CONS(x, y) \
    {SI_STATIC_HEADER(CONS_TYPE, 0), y, x}
#else
#define SI_INITIALIZER_FOR_CONS(x, y) \
    {SI_STATIC_RELOCATION_INFO y, x}
#endif

#define CONSTANT_CONS(id, x, y) \
    static SI_Cons_constant id = SI_INITIALIZER_FOR_CONS(x, y)

#define CONSTANT_LIST_STAR_3(id, x0, x, y) \
    static SI_Cons_constant id[2] = \
        {SI_INITIALIZER_FOR_CONS(x0, TAG_CONS(id[1])), \
         SI_INITIALIZER_FOR_CONS(x, y)}
#define CONSTANT_LIST_STAR_4(id, x0, x1, x, y) \
    static SI_Cons_constant id[3] = \
        {SI_INITIALIZER_FOR_CONS(x0, TAG_CONS(id[1])), \
         SI_INITIALIZER_FOR_CONS(x1, TAG_CONS(id[2])), \
         SI_INITIALIZER_FOR_CONS(x, y)}
#define CONSTANT_LIST_STAR_5(id, x0, x1, x2, x, y) \
    static SI_Cons_constant id[4] = \
        {SI_INITIALIZER_FOR_CONS(x0, TAG_CONS(id[1])), \
         SI_INITIALIZER_FOR_CONS(x1, TAG_CONS(id[2])), \
         SI_INITIALIZER_FOR_CONS(x2, TAG_CONS(id[3])), \
         SI_INITIALIZER_FOR_CONS(x, y)}
#define CONSTANT_LIST_STAR_6(id, x0, x1, x2, x3, x, y) \
    static SI_Cons_constant id[5] = \
        {SI_INITIALIZER_FOR_CONS(x0, TAG_CONS(id[1])), \
         SI_INITIALIZER_FOR_CONS(x1, TAG_CONS(id[2])), \
         SI_INITIALIZER_FOR_CONS(x2, TAG_CONS(id[3])), \
         SI_INITIALIZER_FOR_CONS(x3, TAG_CONS(id[4])), \
         SI_INITIALIZER_FOR_CONS(x, y)}
/* etc. */
#define CONSTANT_LIST_1(id, x)	CONSTANT_CONS(id, x, NIL)
#define CONSTANT_LIST_2(id, x0, x) \
    CONSTANT_LIST_STAR_3(id, x0, x, NIL)
#define CONSTANT_LIST_3(id, x0, x1, x) \
    CONSTANT_LIST_STAR_4(id, x0, x1, x, NIL)
#define CONSTANT_LIST_4(id, x0, x1, x2, x) \
    CONSTANT_LIST_STAR_5(id, x0, x1, x2, x, NIL)
#define CONSTANT_LIST_5(id, x0, x1, x2, x3, x) \
    CONSTANT_LIST_STAR_6(id, x0, x1, x2, x3, x, NIL)
/* etc. */

#endif

 
/***************************************************************************
 *
 * Arrays
 *
 **************************************************************************/

/* Arrays come in two varieties: primitive vectors, and general arrays.
   A primitive vector is a one-dimensional simple array, i.e. Common Lisp
   type (simple-array * (*)).  These are different from simple-vectors,
   which in Common Lisp are type (simple-array t (*)).

   Primitive vectors were formerly called "simple vectors," but that
   was considered too confusing with respect to the Common Lisp
   simple-vector type.

   A "general vector" is a general array of rank 1. */

#define IARRAY_RANK_LIMIT       8

/* Type of array dimensions */

typedef int SI_Dimension;

#define SI_DIMENSION_ETYPE	A_BYTE_32

#define IARRAY_TOTAL_SIZE_LIMIT (1L << 29) /* IMOST_POSITIVE_FIXNUM (32-bit version) */
#define IARRAY_DIMENSION_LIMIT  (1L << 29) /* IMOST_POSITIVE_FIXNUM (32-bit version) */

#define ARRAYP(o) \
    (!SI_IMMEDIATEP(o) && \
     (SI_STORED_OBJECT_TYPE(o) == SI_GENERAL_ARRAY_TYPE || \
      SI_STORED_OBJECT_TYPE(o) == SI_PRIMITIVE_VECTOR_TYPE))

/* Moved here from heap.c, 10/26/04.  Needs to remain in synch with function
 * init_stack_vector_header().  Moved to header file so it can be used by
 * multiple source files.  - jv, mhd
 */

#define SI_INIT_HEADER(o, type, gcsize, gcls, gcalign) \
   (SI_SET_STORED_OBJECT_TYPE(o, type), \
    SI_STORED_OBJECT_FIELD(o, SI_Header, tag) = (unsigned)SI_HEADER_TAG, \
    SI_STORED_OBJECT_FIELD(o, SI_Header, gclength) = (unsigned)(gcsize), \
    SI_STORED_OBJECT_FIELD(o, SI_Header, length_status) = (unsigned)(gcls), \
    SI_STORED_OBJECT_FIELD(o, SI_Header, gcaligned) = (unsigned)(gcalign), \
    SI_INIT_DYNAMICNESS_LABEL(o), \
    SI_STORED_OBJECT_FIELD(o, SI_Header, stuff) = 0)

#if SI_DYNAMICNESS_LABELED

#define SI_INIT_DYNAMICNESS_LABEL(o) \
    (SI_STORED_OBJECT_FIELD(o, SI_Header, gcrelocatable) = \
           (unsigned)((Current_area == &Dynamic_area) ? \
		      SI_GC_RELOCATABLE : SI_GC_NONRELOCATABLE))

#else

#define SI_INIT_DYNAMICNESS_LABEL(o)    (0) /* unnecessary */

#endif


/* Primitive vectors.
 *
 * Consider moving the length field into the header.  Note that doing so will
 * require modifying IARRAY_DIMENSION_LIMIT.
 */

typedef struct {
    SI_Header h;
    Object length; /* always a fixnum */
} SI_ALIGNED_TYPE SI_Primitive_vector;

typedef struct {
    SI_Declare_static_relocation_field  /* no semicolon */
    SI_Header h;
    Object length; /* always a fixnum */
} SI_ALIGNED_TYPE SI_Primitive_vector_constant;

#define SI_VECTOR_PRIMITIVE_P(o) \
    SI_ENUM_EQ(SI_STORED_OBJECT_TYPE(o), SI_PRIMITIVE_VECTOR_TYPE)

#define SI_PRIMITIVE_VECTOR_ETYPE(o) \
    ((enum SI_etype) SI_STORED_OBJECT_FIELD(o, SI_Header, stuff))

#ifdef SI_RUNTIME_INTERNAL
    #define SI_INIT_PRIMITIVE_VECTOR(o, etype) \
            (SI_STORED_OBJECT_FIELD(o, SI_Header, stuff) = (int)(etype))
#endif

#define SI_PRIMITIVE_VECTOR_P(o) \
    (!SI_IMMEDIATEP(o) && SI_VECTOR_PRIMITIVE_P(o))

#define SI_PRIMITIVE_VECTOR_LENGTH(o) \
    IFIX(SI_STORED_OBJECT_FIELD(o, SI_Primitive_vector, length))

#define SI_SET_PRIMITIVE_VECTOR_LENGTH(o, len) \
    (SI_STORED_OBJECT_FIELD(o, SI_Primitive_vector, length) = FIX(len))

#define SI_PRIMITIVE_VECTOR_CONTENTS(o, t) \
    SI_STORED_OBJECT_FIELD(o, t, contents)

#define SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(type, etype) \
  typedef struct { \
      SI_Primitive_vector h; \
      etype contents[1]; \
  } SI_ALIGNED_TYPE type

SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Object,Object);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Char,char);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Float,float);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Double,double);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Short,short);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Long,SI_Long);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Long64,SI_int64);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Uchar,unsigned char);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Ushort,unsigned short);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Ulong,SI_Ulong);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Ulong64,SI_uint64);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Dimension,SI_Dimension);

/* The conditional on n in the array declaration is because C doesn't permit
 * declarations for zero length arrays!
 */
#define SI_Type_for_primitive_vector(t, n) \
    struct {SI_Primitive_vector v; t contents[n ? n : 1];}

#define SI_Type_for_primitive_vector_constant(t, n) \
    struct {SI_Primitive_vector_constant v; t contents[n ? n : 1];}

#define SI_HEADER_FOR_PRIMITIVE_VECTOR(etype, len) \
        {SI_PRIMITIVE_VECTOR_HEADER(SI_PRIMITIVE_VECTOR_TYPE, (int)(etype)), \
         FIX(len)}

#define SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(etype, len) \
        {SI_STATIC_RELOCATION_INFO \
         SI_PRIMITIVE_VECTOR_HEADER(SI_PRIMITIVE_VECTOR_TYPE, (int)(etype)), \
         FIX(len)}

#define SI_PRIMITIVE_VECTOR_ETYPEP(o, etype) \
    (SI_STORED_OBJECT_TYPEP(o, SI_PRIMITIVE_VECTOR_TYPE) && \
     SI_PRIMITIVE_VECTOR_ETYPE(o) == etype)

/* Specialized primitive-vector types: */

/* Simple general vector = simple-vector = (simple-array t (*))
   (This use of the word "general" is different from that in "general array".)
   */
#define SIMPLE_VECTOR_P(o) 	SI_PRIMITIVE_VECTOR_ETYPEP(o, A_T)

#define SI_ISVREF(o, i) \
    SI_PRIMITIVE_VECTOR_CONTENTS(o, SI_PVT_Object)[i]

/* A trick that uses information that Object is 4 bytes long */
#if 0 /* SI_FIXNUM_SHIFT == 2 */
#define SVREF(o, i)   (*(Object *)(SI_PRIMITIVE_VECTOR_CONTENTS(o, SI_PVT_Char) \
     + (i - SI_FIXNUM_TAG_VALUE)))
#else 
#define SVREF(o, i)             SI_ISVREF(o, IFIX(i))
#endif

#if SI_OBJECT_INITIALIZERS_WORK
#define CONSTANT_VECTOR(id, len) \
    static SI_Type_for_primitive_vector_constant(Object, len) id = \
        {SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(A_T, len), {
#define END_CONSTANT_VECTOR()	}}
#define TAG_VECTOR(id)		SI_TAG_STORED_CONSTANT(&id, SI_ARRAY_TAG)
#endif


#if SI_SUPPORT_CLOS

/* Stack allocation of Simple general vectors (CLOS only) */

/**
 ** These macros support CLOS's requirement to stack-allocate
 ** primitive vectors containing Objects.
 **
 ** WARNING: These macros violate the abstractions of stack_items,
 ** headers, objects, primitive vectors, alignment, the heap,
 ** etc.  In other words, a mess.  They are written this way
 ** because of supposed CLOS performance requirements.
 **/

#define SI_PV_HWORDS                                         \
   (sizeof(SI_Primitive_vector_constant)/sizeof(Object))

#if SI_STATIC_RELOCATION_WORDS

/* *** This assumes SI_PV_HWORDS is not more than 3. */
#define SI_INIT_PV_HWORDS()                                 \
   ((STACK_REF(-SI_PV_HWORDS) = SI_UNINITIALIZED_MARKER),   \
    ((SI_PV_HWORDS > 1)                                     \
     ? ((STACK_REF(-SI_PV_HWORDS+1) = SI_UNINITIALIZED_MARKER), \
	((SI_PV_HWORDS > 2)                                 \
	 ? ((STACK_REF(-SI_PV_HWORDS+2) = SI_UNINITIALIZED_MARKER), 0) \
	 : 0)) \
     : 0))

#else            

/* *** This assumes SI_PV_HWORDS is not more than 2. */
#define SI_INIT_PV_HWORDS()                                 \
   ((STACK_REF(-SI_PV_HWORDS) = SI_UNINITIALIZED_MARKER),   \
    ((SI_PV_HWORDS > 1)                                     \
     ? ((STACK_REF(-SI_PV_HWORDS+1) = SI_UNINITIALIZED_MARKER), 0) \
     : 0))

#endif /* SI_STATIC_RELOCATION_WORDS */

#define SI_INIT_OBJECT_VECTOR_HEADER(ptr, len) \
    (*(ptr) = SI_Stack_vector_header, (ptr)->length = FIX(len))


#if SI_TAG_WIDTH <= 3

/*
 * Assuming:
 *   (1) no alignment restrictions
 */

#define SI_NOT_ALIGNED(x) ((unsigned)(x) & ((1<<SI_TAG_WIDTH)-1))

#define SI_START_PUSHING_OBJECT_VECTOR()                    \
   ((Stack += SI_PV_HWORDS),                                \
    SI_INIT_PV_HWORDS())

#define SI_FINISH_PUSHING_OBJECT_VECTOR(numelems)           \
((SI_INIT_OBJECT_VECTOR_HEADER((SI_Primitive_vector_constant *)   \
     (&STACK_REF(-(SI_PV_HWORDS+numelems))), numelems)), \
 (SI_SET_TAG((&STACK_REF(-(SI_PV_HWORDS+numelems+SI_STATIC_RELOCATION_SIZE))),\
             SI_ARRAY_TAG)))

#ifdef SI_RUNTIME_INTERNAL

#define SI_POP_OBJECT_VECTOR(pv)                            \
   (Stack = ((SI_Stack_item *)(SI_UNTAG_STORED(pv, SI_Primitive_vector))) \
            - SI_STATIC_RELOCATION_SIZE)

#endif

#else

/*
 * Assuming:
 *   (1) alignment restriction for 3-bit tagging
 */

#define SI_START_PUSHING_OBJECT_VECTOR()                    \
    ((SI_NOT_ALIGNED(&STACK_REF(SI_STATIC_RELOCATION_SIZE)) \
	? (STACK_REF(0) = SI_ALIGNMENT_MARKER,              \
	   Stack += SI_PV_HWORDS+1)                         \
	: Stack += SI_PV_HWORDS)                            \
     SI_INIT_PV_HWORDS())

#define SI_FINISH_PUSHING_OBJECT_VECTOR(numelems)           \
((SI_INIT_OBJECT_VECTOR_HEADER((SI_Primitive_vector_constant *)   \
     (&STACK_REF(-(SI_PV_HWORDS+numelems))), numelems)), \
 (SI_SET_TAG((&STACK_REF(-(SI_PV_HWORDS+numelems+SI_STATIC_RELOCATION_SIZE))),\
             SI_ARRAY_TAG)))

#ifdef SI_RUNTIME_INTERNAL

#define SI_POP_OBJECT_VECTOR(pv)                            \
   ((Stack = ((SI_Stack_item *)(SI_UNTAG_STORED(pv, SI_Primitive_vector))) \
             - SI_STATIC_RELOCATION_SIZE),                  \
    ((STACK_REF(-1) == SI_ALIGNMENT_MARKER)                 \
       ? (Stack -= 1)                                       \
       : Stack))

#endif

#endif

#endif /* SI_SUPPORT_CLOS */



/* simple-string = (simple-array string-char (*)) */

#define SIMPLE_STRING_P(o)	SI_PRIMITIVE_VECTOR_ETYPEP(o, A_STRING_CHAR)
#define SI_ISCHAR(o, i) \
    SI_PRIMITIVE_VECTOR_CONTENTS(o, SI_PVT_Char)[i]
#define SCHAR(o, i) 		CHR(SI_ISCHAR(o, IFIX(i)))
#define SET_SCHAR(o,i,c) \
    (SI_ISCHAR(o, IFIX(i)) = ICHAR_CODE(c), c)

#if SI_OBJECT_INITIALIZERS_WORK

#define CONSTANT_STRING(id, len, str) \
    static SI_Type_for_primitive_vector_constant(char, (len) + 1) id = \
        {SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(A_STRING_CHAR, len), str}
#define TAG_STRING(id) 		SI_TAG_STORED_CONSTANT(&id, SI_ARRAY_TAG)

#endif


/* simple-bit-vector = (simple-array bit (*)) */

#define SIMPLE_BIT_VECTOR_P(o)  SI_PRIMITIVE_VECTOR_ETYPEP(o, A_BIT)
#define SI_BITS_TYPE 		unsigned short
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Bits,SI_BITS_TYPE);

/* *** BUG: This assumes that shorts are 16 bits. */
#define SI_BITS_TYPE_MASK	15
#define SI_BITS_TYPE_SHIFT	4

/* SBIT_1, SET_SBIT_1
 *
 * These helpers are used in the implementation of SBIT() and SET_SBIT().
 * They all operate on unboxed indexes.
 *
 *   SI_SBIT_ACCESS(o,i)
 *	Get a block of bits from a bit vector.
 *   SI_SBIT_MASK(i)
 *	Generate a mask to get the specified bit out of a block of bits.
 */

#define SI_SBIT_ACCESS(o,i) \
    (SI_PRIMITIVE_VECTOR_CONTENTS(o,SI_PVT_Bits)[(i) >> SI_BITS_TYPE_SHIFT])

#define SI_SBIT_MASK(i)	(1L << ((i) & SI_BITS_TYPE_MASK))

#define SBITP_1(o,i)	(SI_SBIT_ACCESS(o,IFIX(i)) & SI_SBIT_MASK(IFIX(i)))

#define SBIT_1(o,i)	(SBITP_1(o,i) ? FIX(1) : ZERO)

/* This definition returns zero if v is zero and one otherwise, rather than
 * returning v otherwise.  The justification is that it is an error to try to
 * store anything other than zero or one. */
#define SET_SBIT_1(o,i,v) \
    (((SI_SBIT_ACCESS(o,IFIX(i)) = \
	((v) == ZERO \
	  ? SI_SBIT_ACCESS(o,IFIX(i)) & ~SI_SBIT_MASK(IFIX(i)) \
	  : SI_SBIT_ACCESS(o,IFIX(i)) | SI_SBIT_MASK(IFIX(i)))) \
      & SI_SBIT_MASK(IFIX(i))) ? FIX(1) : ZERO)

#if SI_OBJECT_INITIALIZERS_WORK

#define CONSTANT_BIT_VECTOR(id, len) \
    static SI_Type_for_primitive_vector_constant(SI_BITS_TYPE, \
	((len)+SI_BITS_TYPE_MASK) >> SI_BITS_TYPE_SHIFT) id = \
        {SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(A_BIT, len), {
#define END_CONSTANT_BIT_VECTOR()  }}
#define TAG_BIT_VECTOR(id) 	SI_TAG_STORED_CONSTANT(&id, SI_ARRAY_TAG)

#endif

/* 
    Lisp element type    C type
    t                  / Object
    single-float       / float
    double-float       / double
    string-char	       / char
    bit		       / ---  [SI_BITS_TYPE]
    (unsigned-byte 8)  / unsigned char
    (signed-byte 8)    / char
    (unsigned-byte 16) / unsigned short
    (signed-byte 16)   / short
    (signed-byte 32)   / long
    (unsigned-byte 32) / unsigned long
 */



/* General arrays:
     (deftype general-array ()
       `(and array
	     (not (simple-array * (*)))))
 */

typedef struct {
    SI_Header h;		/* stuff = rank */
    Object displaced_to;
    Object fill_pointer_or_dimensions; /* fill ptr iff rank == 1 */
    Object displaced_index_offset;
    /* Object total_size;   -- needed for displaced vectors */
} SI_ALIGNED_TYPE SI_General_array;

typedef struct {
    SI_Declare_static_relocation_field /* no semicolon */
    SI_Header h;		/* stuff = rank */
    Object displaced_to;
    Object fill_pointer_or_dimensions; /* fill ptr iff rank == 1 */
    Object displaced_index_offset;
    /* Object total_size;   -- needed for displaced vectors */
} SI_ALIGNED_TYPE SI_General_array_constant;

#define SI_GENERAL_ARRAY_P(o) \
    (ARRAYP(o) && \
     !SI_VECTOR_PRIMITIVE_P(o))

#define SI_GENERAL_ARRAY_ETYPE(o) \
    ((enum SI_etype) (SI_STORED_OBJECT_FIELD(o, SI_Header, stuff) & 31))

/* These two tests can be combined */
#define SI_GENERAL_ARRAY_ETYPEP(o, etype) \
    (SI_STORED_OBJECT_TYPEP(o, SI_GENERAL_ARRAY_TYPE) && \
     SI_GENERAL_ARRAY_ETYPE(o) == etype)

#define SI_GENERAL_ARRAY_RANK(o) \
    (SI_STORED_OBJECT_FIELD(o, SI_Header, stuff) >> 5)

#ifdef SI_RUNTIME_INTERNAL
    #define SI_INIT_GENERAL_ARRAY(o, rank, etype) \
            (SI_STORED_OBJECT_FIELD(o, SI_Header, stuff) = \
                 (int)(etype) | ((rank) << 5))
#endif

#define SI_GENERAL_ARRAY_DISPLACED_TO(o) \
    SI_STORED_OBJECT_FIELD(o, SI_General_array, displaced_to)

#define SI_DISPLACED_INDEX_OFFSET(o) \
    SI_STORED_OBJECT_FIELD(o, SI_General_array, displaced_index_offset)

/* For general vectors (i.e. rank == 1): */

/* -- The following won't work in the presence of displaced arrays! */
#define SI_GENERAL_VECTOR_TOTAL_SIZE(o) \
    SI_PRIMITIVE_VECTOR_LENGTH(SI_GENERAL_ARRAY_DISPLACED_TO(o))

#define SI_GENERAL_VECTOR_FILL_POINTER(o) \
    SI_STORED_OBJECT_FIELD(o, SI_General_array, fill_pointer_or_dimensions)

#define FILL_POINTER(o)		SI_GENERAL_VECTOR_FILL_POINTER(o)
#define SET_FILL_POINTER(o, i)  (SI_GENERAL_VECTOR_FILL_POINTER(o) = (i))


/* For general non-vector arrays: */

#define SI_GENERAL_NVARRAY_DIMENSIONS(o) \
    SI_STORED_OBJECT_FIELD(o, SI_General_array, fill_pointer_or_dimensions)

#define SI_GENERAL_NVARRAY_DIMENSION(o, i) \
    SI_PRIMITIVE_VECTOR_CONTENTS(SI_GENERAL_NVARRAY_DIMENSIONS(o), \
				 SI_PVT_Dimension)[i]

#if SI_OBJECT_INITIALIZERS_WORK

#define SI_HEADER_FOR_GENERAL_ARRAY(etype, rank) \
        SI_HEADER(SI_GENERAL_ARRAY_TYPE, (int)(etype) | ((rank) << 5))

#define SI_STATIC_HEADER_FOR_GENERAL_ARRAY(etype, rank) \
        SI_STATIC_HEADER(SI_GENERAL_ARRAY_TYPE, (int)(etype) | ((rank) << 5))

#define CONSTANT_ARRAY(id, rank, len) \
    static struct {SI_General_array_constant a; \
		   SI_Type_for_primitive_vector_constant(SI_Dimension, rank) dims; \
		   SI_Type_for_primitive_vector_constant(Object, len) v;} id = \
        {{SI_STATIC_HEADER_FOR_GENERAL_ARRAY(A_T, rank), \
	  SI_TAG_STORED_CONSTANT(&id.v, SI_ARRAY_TAG), \
	  SI_TAG_STORED_CONSTANT(&id.dims, SI_ARRAY_TAG) /*, offset, totalsize */}, \
	 {SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(SI_DIMENSION_ETYPE, rank), {

#define CONSTANT_ARRAY_CONTENTS(total_size) \
	  }}, {SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(A_T, total_size), {
#define END_CONSTANT_ARRAY()	}}}
#define TAG_ARRAY(id) 		SI_TAG_STORED_CONSTANT(&id, SI_ARRAY_TAG)

#endif


/* Generic definitions for general arrays and simple vectors */

/* Array element type is encoded in the header type */
#define SI_ARRAY_ETYPE(o) \
    SI_GENERAL_ARRAY_ETYPE(o)

#define ARRAY_RANK(o) \
    (SI_VECTOR_PRIMITIVE_P(o) ? \
     FIX(1) : \
     FIX(SI_GENERAL_ARRAY_RANK(o)))

#define ADJUSTABLE_ARRAY_P(o)  /* All general arrays are */  \
    SI_GENERAL_ARRAY_P(o)

#define ARRAY_HAS_FILL_POINTER_P(o) \
    SI_GENERAL_ARRAY_P(o)

#define SIMPLE_ARRAY_P(o) \
    (SI_PRIMITIVE_VECTOR_P(o) || \
     (SI_GENERAL_ARRAY_P(o) && \
      (SI_GENERAL_ARRAY_RANK(o) != 1 && \
       SI_VECTOR_PRIMITIVE_P(SI_GENERAL_ARRAY_DISPLACED_TO(o)))))

#define VECTORP(o) \
    (SI_PRIMITIVE_VECTOR_P(o) || \
     (SI_GENERAL_ARRAY_P(o) && \
      SI_GENERAL_ARRAY_RANK(o) == 1))

#define BIT_VECTOR_P(o) \
    (SIMPLE_BIT_VECTOR_P(o) || \
     (SI_GENERAL_ARRAY_ETYPEP(o, A_BIT)))

#define STRINGP(o) \
    (SIMPLE_STRING_P(o) || \
     (SI_GENERAL_ARRAY_ETYPEP(o, A_STRING_CHAR)))

/* do_..aref.. should be renamed to SI_..row_aref..   */

#define ROW_MAJOR_AREF(arr, ind) (do_aref_1(arr, (SI_Dimension)IFIX(ind)))
#define SET_ROW_MAJOR_AREF(arr, ind, new) \
    (do_setf_aref(arr, (SI_Dimension)IFIX(ind), new))

/* These should all have SI_ prefixes... */

#define ROW_MAJOR_INDEX_0(o) 0

#define ROW_MAJOR_INDEX_1(o, i1) (IFIX(i1))

#define ROW_MAJOR_INDEX_2(o, i1, i2) \
    (ROW_MAJOR_INDEX_1(o, i1)*SI_GENERAL_NVARRAY_DIMENSION(o, 1)+IFIX(i2))

#define ROW_MAJOR_INDEX_3(o, i1, i2, i3) \
    (ROW_MAJOR_INDEX_2(o, i1, i2)*SI_GENERAL_NVARRAY_DIMENSION(o, 2) + \
        IFIX(i3))

#define ROW_MAJOR_INDEX_4(o, i1, i2, i3, i4) \
    (ROW_MAJOR_INDEX_3(o, i1, i2, i3)*SI_GENERAL_NVARRAY_DIMENSION(o, 3) + \
        IFIX(i4))

#define ROW_MAJOR_INDEX_5(o, i1, i2, i3, i4, i5) \
    (ROW_MAJOR_INDEX_4(o, i1, i2, i3, i4)*SI_GENERAL_NVARRAY_DIMENSION(o, 4) + \
        IFIX(i5))

#define ROW_MAJOR_INDEX_6(o, i1, i2, i3, i4, i5, i6) \
    (ROW_MAJOR_INDEX_5(o, i1, i2, i3, i4, i5) * \
        SI_GENERAL_NVARRAY_DIMENSION(o, 5) + IFIX(i6))

#define ROW_MAJOR_INDEX_7(o, i1, i2, i3, i4, i5, i6, i7) \
    (ROW_MAJOR_INDEX_6(o, i1, i2, i3, i4, i5, i6) * \
        SI_GENERAL_NVARRAY_DIMENSION(o, 6) + IFIX(i7))


/* Inline versions for 2-dimensional simple arrays of type t */

#define SAREF2(a, i1, i2) \
  SI_PRIMITIVE_VECTOR_CONTENTS(SI_GENERAL_ARRAY_DISPLACED_TO(a), \
  SI_PVT_Object)[(long)ROW_MAJOR_INDEX_2(a, i1, i2)]

#define SASET2(arr, s1, s2, new) \
  (SI_PRIMITIVE_VECTOR_CONTENTS(SI_GENERAL_ARRAY_DISPLACED_TO(arr), \
   SI_PVT_Object)[(SI_Dimension)ROW_MAJOR_INDEX_2(arr, s1, s2)] = (new))

/***************************************************************************
 *
 * Numbers
 *
 **************************************************************************/

/* inlining of generic operations */

enum SI_binary_op {		/* Binary operations */
    SI_NONE,
    SI_MADD,
    SI_MMINUS,
    SI_MTIMES,
    SI_MDIVIDE,
    SI_LESS,
    SI_MEQUAL,
    SI_MMAX,
    SI_MMIN,
    SI_LOGAND,
    SI_LOGIOR,
    SI_LOGXOR,
    SI_LOGEQV,
    SI_ASH
};

#define NUM_LT(a, b) \
    ((FIXNUMP(a) && FIXNUMP(b)) \
        ? FIXNUM_LT(a,b) \
        :  TRUEP(SI_do_math2(a, b, SI_LESS)))

#define NUM_GT(a, b) \
    ((FIXNUMP(a) && FIXNUMP(b)) \
        ? FIXNUM_GT(a,b) \
        :  TRUEP(SI_do_math2(b, a, SI_LESS)))

#define NUM_EQ(a, b) \
    ((FIXNUMP(a) && FIXNUMP(b)) \
        ? FIXNUM_EQ(a,b) \
        :  TRUEP(SI_do_math2(a, b, SI_MEQUAL)))

#define NUM_LE(a, b) (! NUM_GT(a, b))
#define NUM_GE(a, b) (! NUM_LT(a, b))
#define NUM_NE(a, b) (! NUM_EQ(a, b))



/*   Ratios */
typedef struct {
    SI_Header h;
    Object numerator;
    Object denominator;
} SI_ALIGNED_TYPE SI_Ratio;

typedef struct {
    SI_Declare_static_relocation_field /* no semicolon */
    SI_Header h;
    Object numerator;
    Object denominator;
} SI_ALIGNED_TYPE SI_Ratio_constant;

#if SI_OBJECT_INITIALIZERS_WORK

#define CONSTANT_RATIO(id, x, y) \
    static SI_Ratio_constant id = {SI_STATIC_HEADER(RATIO_TYPE, 0), x, y}
#define TAG_RATIO(id) 		SI_TAG_STORED_CONSTANT(&id, SI_NUMBER_TAG)

#endif

#define SI_RATIO_NUMERATOR(o)	SI_STORED_OBJECT_FIELD(o, SI_Ratio, numerator)
#define SI_RATIO_DENOMINATOR(o)	SI_STORED_OBJECT_FIELD(o, SI_Ratio,denominator)

/* INT64 integers used for 32-bit systems */

typedef struct {
    SI_Header h;
    SI_int64 value;
} SI_ALIGNED_TYPE SI_Long64_integer;

#define LONG64P(o)		SI_STORED_OBJECT_TYPEP(o, LONG64_TYPE)
#define ILONG64(o)		SI_STORED_OBJECT_FIELD(o, SI_Long64_integer, value)
#define MAKE_LONG64(n)		clong_to_int64((SI_Long)n)
#define T_MAKE_LONG64(n)	(L_temp=(n), MAKE_LONG64(L_temp))
#define SI_UNTAG_LONG64(o)	ILONG64(o)

/*   Double floats */

#define DOUBLEP(o)		SI_STORED_OBJECT_TYPEP(o, DOUBLE_TYPE)

#ifndef KLUDGE_DOUBLE_FLOATS

typedef struct {
	char pad[2*sizeof(Object) - sizeof(SI_Header)];
    SI_Header h;
    DOUBLE value;
} SI_ALIGNED_TYPE SI_Double_float;

#if SI_STATIC_RELOCATION_WORDS

typedef struct {
    char pad[2*sizeof(Object) - sizeof(Object)];
    Object relocation_word;
    SI_Header h; /* any gap must follow this field, or the code breaks */
    DOUBLE value;
} SI_ALIGNED_TYPE SI_Double_float_constant;

#else
typedef SI_Double_float  SI_Double_float_constant;
#endif /* SI_STATIC_RELOCATION_WORDS */

#define IDOUBLE(o) \
    SI_STORED_OBJECT_FIELD(o, SI_Double_float, value)

#define IDOUBLE1(o) IDOUBLE(o)

#ifdef SI_RUNTIME_INTERNAL
#define SI_INIT_DOUBLE_FLOAT(o, n) \
    (SI_STORED_OBJECT_FIELD(o, SI_Double_float, value) = (n))

/* -- Phase out */
#define SI_UNTAG_DOUBLE_FLOAT(o) IDOUBLE(o) /* coerce.c */
#endif

#if SI_OBJECT_INITIALIZERS_WORK

#if SI_STATIC_RELOCATION_WORDS
#define CONSTANT_DOUBLE_FLOAT(id, n) \
    static SI_Double_float_constant id = {"", SI_STATIC_HEADER(DOUBLE_TYPE, 0), n}
#else
#define CONSTANT_DOUBLE_FLOAT(id, n) \
    static SI_Double_float_constant id = {SI_STATIC_HEADER(DOUBLE_TYPE, 0), n}
#endif /* SI_STATIC_RELOCATION_WORDS */

#define TAG_DOUBLE_FLOAT(id) 	SI_TAG_STORED(&id.h, SI_NUMBER_TAG)

#endif /* SI_OBJECT_INITIALIZERS_WORK */

#else /* KLUDGE_DOUBLE_FLOATS */

typedef struct {
    char pad[2*sizeof(Object) - sizeof(SI_Header)];
    SI_Header h;
    DOUBLE value;
} SI_ALIGNED_TYPE SI_Aligned_double_float;

#if SI_STATIC_RELOCATION_WORDS

typedef struct { /* no gap may appear in this structure, or the code breaks */
    Object relocation_word;
    SI_Header h;
    DOUBLE value;
} SI_ALIGNED_TYPE SI_Aligned_double_float_constant;

#else
typedef SI_Aligned_double_float SI_Aligned_double_float_constant;
#endif /* SI_STATIC_RELOCATION_WORDS */

struct SI_same_size_as_double {
    char mumble[sizeof(DOUBLE)];
};

typedef struct {
    SI_Header h;
    struct SI_same_size_as_double kludge;
} SI_ALIGNED_TYPE SI_Kludged_double_float;

typedef union {
    DOUBLE number;
    struct SI_same_size_as_double kludge;
} SI_ALIGNED_TYPE Double_float_kludge_union; /* should be SI_ */

#define IDOUBLE(o) \
    (SI_Double_float_kludge_temp.kludge = \
         SI_STORED_OBJECT_FIELD(o, SI_Kludged_double_float, kludge), \
     SI_Double_float_kludge_temp.number)

#define IDOUBLE1(o) \
    (SI_Double_float_kludge_temp1.kludge = \
         SI_STORED_OBJECT_FIELD(o, SI_Kludged_double_float, kludge), \
     SI_Double_float_kludge_temp1.number)

#ifdef SI_RUNTIME_INTERNAL
#define SI_INIT_DOUBLE_FLOAT(o, n) \
    (Double_float_kludge_temp.number = n, \
     SI_STORED_OBJECT_FIELD(o, SI_Kludged_double_float, kludge) = \
         Double_float_kludge_temp.kludge)

/* -- Phase out */
#define SI_UNTAG_DOUBLE_FLOAT(o) \
    SI_STORED_OBJECT_FIELD(o, SI_Kludged_double_float, kludge) /* coerce.c */
#endif

#if SI_OBJECT_INITIALIZERS_WORK

#if SI_STATIC_RELOCATION_WORDS
#define CONSTANT_DOUBLE_FLOAT(id, n) \
    static SI_Aligned_double_float_constant id = \
        {SI_STATIC_HEADER(DOUBLE_TYPE, 0), n}
#else
#define CONSTANT_DOUBLE_FLOAT(id, n) \
    static SI_Aligned_double_float_constant id = \
        {"", SI_STATIC_HEADER(DOUBLE_TYPE, 0), n}
#endif /* SI_STATIC_RELOCATION_WORDS */

#define TAG_DOUBLE_FLOAT(id) 	SI_TAG_STORED(&id.h, SI_NUMBER_TAG)

#endif /* SI_OBJECT_INITIALIZERS_WORK */

#endif /* KLUDGE_DOUBLE_FLOATS */

/*   Bignums */

/* This must be signed 32-bit, because in SI_allocate_bignum() (biginit2.c), an array of A_BYTE_32 is
   allocated for hold bignum digits. In theory, we could also use pure signed 64-bit integers for
   both STD and ENT and modify SI_allocate_bignum() to create A_BYTE_64 arrays, but this will make
   debugging of bignums more difficult (in the sense that the incorrectness is hard to see when there's
   only one internal bignum digit usually).  -- Chun Tian (binghe), 19 Sep 2016. */
typedef int SI_Bignum_digit_type;

typedef struct {
    SI_Header h;
    Object digits;		/* simple byte-32 vector */
    Object length;
} SI_ALIGNED_TYPE SI_Bignum;

typedef struct {
    SI_Declare_static_relocation_field /* no semicolon */
    SI_Header h;
    Object digits;		/* simple byte-32 vector */
    Object length;
} SI_ALIGNED_TYPE SI_Bignum_constant;

#define BIGNUMP(o)		SI_STORED_OBJECT_TYPEP(o, BIGNUM_TYPE)

#ifdef SI_RUNTIME_INTERNAL

#define XBIGNUMP(o)		SI_STORED_OBJECT_TYPEP(o, XBIGNUM_TYPE)
#define XBIGNUM_NEGATIVE_P(o)  	SI_STORED_OBJECT_FIELD(o, SI_Header, stuff)
#define XBIGNUM_LENGTH(o) \
    SI_STORED_OBJECT_FIELD(o, SI_Bignum, length)

SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Bignum_digit_type,SI_Bignum_digit_type);

#define XBIGNUM_ARRAY(o) \
    SI_PRIMITIVE_VECTOR_CONTENTS(SI_STORED_OBJECT_FIELD(o, SI_Bignum, digits),\
				 SI_PVT_Bignum_digit_type)

#define BIGNUM_ALLOCATE(length) SI_alloc_bignum((SI_Dimension)(length))

#define BIGNUM_START_PTR(bignum)					\
  ((SI_Bignum_digit_type *) XBIGNUM_ARRAY(bignum))

#define BIGNUM_SET_HEADER(bignum, length, negative_p)			\
  (XBIGNUM_NEGATIVE_P (bignum) = (negative_p),				\
   XBIGNUM_LENGTH (bignum) = FIX(length))

#define BIGNUM_LENGTH(bignum)						\
  IFIX(XBIGNUM_LENGTH(bignum))

#define BIGNUM_NEGATIVE_P(bignum)					\
  XBIGNUM_NEGATIVE_P(bignum)


#define BIGNUM_REDUCE_LENGTH(target, source, length)			\
    (source, length, target)	/* Lose */
#define BIGNUM_DEALLOCATE(bignum)
/* #define BIGNUM_FORCE_NEW_RESULTS */
#define BIGNUM_EXCEPTION() (error(1,"bignum exception"))
#define fast register

#endif

#if SI_OBJECT_INITIALIZERS_WORK

#define CONSTANT_BIGNUM(id, negative_p, len) \
    static struct {SI_Bignum_constant descr; \
		   SI_Type_for_primitive_vector_constant(long, len) digits;} id = \
        {{SI_STATIC_HEADER(BIGNUM_TYPE, negative_p), \
	  SI_TAG_STORED_CONSTANT(&id.digits, SI_ARRAY_TAG), FIX(len)}, \
         {SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(A_BYTE_32, len), {
#define END_CONSTANT_BIGNUM()	}}}
#define TAG_BIGNUM(id) 		SI_TAG_STORED_CONSTANT(&id.descr, SI_NUMBER_TAG)

#endif /* SI_OBJECT_INITIALIZERS_WORK */


/***************************************************************************
 *
 * Symbols
 *
 **************************************************************************/

/* Put initial_p, external_p, and keyword_p bits in stuff field of header? */
/* Encode package in stuff field of header? */

typedef struct {
    SI_Header h;
    Object plist;
} SI_ALIGNED_TYPE SI_Symbol;

typedef union {
	SI_Symbol symbol;
} ObjectType;

#define SYMBOLP(o) \
    (SI_IMMEDIATEP(o) ? ((o) == NIL) : \
     (SI_ENUM_GE(SI_STORED_OBJECT_TYPE(o), SI_LEAST_SYMBOL_TYPE) && \
      SI_ENUM_LE(SI_STORED_OBJECT_TYPE(o), SI_GREATEST_SYMBOL_TYPE)))

#define SI_SYMBOL_PLIST(o) \
    SI_STORED_OBJECT_FIELD(o, SI_Symbol, plist)

enum SI_Symbol_field {
    SI_SymFbnd,		/* fboundp() & fmakunbound() */
    SI_SymSetfFbnd,	/* fboundp() & fmakunbound() */
    SI_SymBnd,		/* boundp() & makunbound() */
#define SI_SymFldBnd	SI_SymBnd
    SI_SymVal,		/* symbol_value() & writer */
    SI_SymFn,		/* symbol_function() & writer */
    SI_SymPlist,	/* symbol_plist() & writer */
    SI_SymName,		/* symbol_name() */
    SI_SymValLoc,	/* SET_SYMBOL_VALUE_LOCATION() */
    SI_SymSetfFn,	/* setf_function() & writer */
    SI_SymFnLoc	/* SET_SYMBOL_FUNCTION_LOCATION() */
};

#define SYMBOL_PACKAGE(o)	symbol_package(o)
#define SYMBOL_NAME(o)        	symbol_name(o)

#define SYMBOL_FUNCTION(o)	SI_symbol_field(o, SI_SymFn)
#define SET_SYMBOL_FUNCTION(o,v) SI_set_symbol_field(o, v, SI_SymFn)

#define SYMBOL_VALUE(o)		SI_symbol_field(o, SI_SymVal)
#define SET_SYMBOL_VALUE(o,v)	SI_set_symbol_field(o, v, SI_SymVal)


#define SYMBOL_PLIST(o)		SI_symbol_field(o, SI_SymPlist)
#define SET_SYMBOL_PLIST(o,v)	SI_set_symbol_field(o, v, SI_SymPlist)

#define SETF_FUNCTION(o)	SI_symbol_field(o, SI_SymSetfFn)
#define SET_SETF_FUNCTION(o,v)	SI_set_symbol_field(o, v, SI_SymSetfFn)

#define KEYWORDP(o) \
    (!SI_IMMEDIATEP(o) && \
     (SI_STORED_OBJECT_TYPE(o) == KEYWORD_TYPE || \
      SI_STORED_OBJECT_TYPE(o) == MKEYWORD_TYPE))

#ifdef SI_RUNTIME_INTERNAL
#define SI_EXTERNALP(o) \
    SI_ENUM_GE(SI_STORED_OBJECT_TYPE(o), ESYMBOL_TYPE)

#define SI_INDIRECTP(o) \
    (SI_STORED_OBJECT_TYPE(o) == EINDIRECT_TYPE || \
     SI_STORED_OBJECT_TYPE(o) == INDIRECT_TYPE)
#endif

/* Initial symbols (for initsyms.c): */

typedef struct {
    SI_Declare_static_relocation_field /* no semicolon */
    SI_Symbol header;
    unsigned short name_index;
    unsigned short name_offset;
    unsigned short next;
} SI_ALIGNED_TYPE SI_Initial_symbol;

/* This is reversed from the usual style because Initial symbols are always
   static constants. */
typedef struct {
    SI_Symbol header;
    unsigned short name_index;
    unsigned short name_offset;
    unsigned short next;
} SI_ALIGNED_TYPE SI_Initial_symbol_stored;

#ifdef SI_RUNTIME_INTERNAL


/* for symbol-value, setf of symbol-value, boundp, makunbound */
#define SELF_EVALUATING_SYMBOL_P(sym) \
    (EQ(sym,NIL) || EQ(sym,T) || KEYWORDP(sym))

#define ISYMBOL_TYPE(o)		SI_STORED_OBJECT_HEADER_TYPE_FIELD(o)
#define SET_ISYMBOL_TYPE(o, stype) (SI_STORED_OBJECT_FIELD(o, SI_Header, type)\
                        = (unsigned int) stype)

#define ISYMBOL_NEXT(o) \
    SI_STORED_OBJECT_FIELD(o, SI_Initial_symbol_stored, next)
#define ISYMBOL_NAME(o) \
   (&Initial_symbol_names[SI_STORED_OBJECT_FIELD(o, SI_Initial_symbol_stored, \
						 name_index)] \
                         [SI_STORED_OBJECT_FIELD(o, SI_Initial_symbol_stored, \
						 name_offset)])

#define PREVIOUS_ISYMBOL(o) \
    ((Object) ((SI_Long) (o) - sizeof(SI_Initial_symbol)))

#endif

/* translator-specific */
#define SI_SYMNAME_OFFSET_WIDTH  14
#define SI_SYMNAME_OFFSET_SHIFT  SI_TYPE_WIDTH
#define SI_SYMNAME_OFFSET_MASK   ((1L << SI_SYMNAME_OFFSET_WIDTH) - 1L)
#define SI_SYMNAME_INDEX_SHIFT \
   (SI_SYMNAME_OFFSET_WIDTH + SI_SYMNAME_OFFSET_SHIFT)


#if SI_OBJECT_INITIALIZERS_WORK

#if SI_STATIC_RELOCATION_WORDS
#define SI_INIT_SYMBOL_RELOCATION_WORD(sym) \
    (sym)->relocation_word = SI_NONRELOCATABLE_MARKER
#else 
#define SI_INIT_SYMBOL_RELOCATION_WORD(sym)
#endif

#define SI_INIT_SYMBOL_HEADER(symbol, type, p_list)  \
	{ SI_Ulong *hp; \
	      hp = (SI_Ulong *) &(symbol)->h; \
  (*hp = \
    (((unsigned)type) << (SI_HEADER_SHIFT+SI_LENGTH_STATUS_WIDTH)) \
    | ((unsigned)SI_HEADER_TAG) \
    | (((unsigned)SI_UGLY) << SI_HEADER_SHIFT) \
    | (((unsigned)SI_GC_UNALIGNED) << \
       (SI_HEADER_SHIFT+SI_LENGTH_STATUS_WIDTH+SI_TYPE_WIDTH \
	+SI_GCRELOCATE_WIDTH))); \
  (*hp |= ((unsigned)SI_GC_NONRELOCATABLE) \
		      << \
		      (SI_HEADER_SHIFT+SI_LENGTH_STATUS_WIDTH+SI_TYPE_WIDTH));\
  ((symbol)-> plist = p_list);\
  }

#define INITIAL_SYMBOL(index, offset, next, type) \
    {SI_STATIC_RELOCATION_INFO {SI_HEADER(type, 0), NIL}, index, offset, next},
#define IMPORTED_SYMBOL(sym, index, offset, next, type) \
    {SI_STATIC_RELOCATION_INFO {SI_HEADER(type, 0), sym}, index, offset, next},
#define TAG_ISYMBOL(package_id, index) \
    SI_TAG_STORED_CONSTANT(&package_id[index], SI_SYMBOL_TAG)

/* *** */
#define NEW_INITIAL_SYMBOL(index, offset, externalp) \
    ,(((SI_Long)(offset & SI_SYMNAME_OFFSET_WIDTH) \
	  << SI_SYMNAME_OFFSET_SHIFT) | \
      ((SI_Long)index << SI_SYMNAME_INDEX_SHIFT) | \
      ((SI_Long) externalp ? ESYMBOL_TYPE : SYMBOL_TYPE))

#define NEW_INITIAL_KEYWORD(index, offset) \
    ,(((SI_Long)(offset & SI_SYMNAME_OFFSET_WIDTH) \
       << SI_SYMNAME_OFFSET_SHIFT) | \
      ((SI_Long)index << SI_SYMNAME_INDEX_SHIFT) | \
      ((SI_Long) KEYWORD_TYPE ))

#endif /* SI_OBJECT_INITIALIZERS_WORK */


/* Noninitial symbols (formerly "msymbols") */

typedef struct {	/* symbol interned at run time */
    SI_Symbol h;
    Object next;
} SI_Noninitial_symbol;

#if  SI_OBJECT_INITIALIZERS_WORK

typedef struct {	/* symbol interned at run time */
    SI_Declare_static_relocation_field  /* no semicolon */
    SI_Symbol h;
    Object next;
} SI_Noninitial_symbol_constant;

#endif /* SI_OBJECT_INITIALIZERS_WORK */

#ifdef SI_RUNTIME_INTERNAL

#define MSYMBOL_NEXT(o) \
    SI_STORED_OBJECT_FIELD(o, SI_Noninitial_symbol, next)
#define MSYMBOL_NAME(o) \
    SI_STORED_OBJECT_FIELD(o, \
			   struct {SI_Noninitial_symbol h; char name[1];}, \
			   name)

#define MSYMBOLP(a)		(!SI_IMMEDIATEP(a) && \
				 (ISYMBOL_TYPE(a) == MSYMBOL_TYPE || \
				  ISYMBOL_TYPE(a) == MKEYWORD_TYPE))


typedef struct {	/* uninterned symbol */
    SI_Symbol h;
    Object name;
} SI_Uninterned_symbol;

#define USYMBOL_NAME(o) \
   SI_STORED_OBJECT_FIELD(o, SI_Uninterned_symbol, name)

#define USYMBOLP(o)		SI_STORED_OBJECT_TYPEP(o, USYMBOL_TYPE)

#endif /* SI_RUNTIME_INTERNAL */

/* 
 * T symbol and its value 
 */

/* always treat Qt to be T */
#define Qt T

#if SI_OBJECT_INITIALIZERS_WORK
typedef struct {SI_Noninitial_symbol_constant h; char name[2];} SI_Static_T;
extern SI_Static_T SI_T_untagged;
#define T SI_TAG_STORED_CONSTANT((&SI_T_untagged), SI_SYMBOL_TAG)
#else
extern Object T;
#endif /*SI_OBJECT_INITIALIZERS_WORK*/


/* 
 * NIL itself 
 */

#if SI_NIL_IS_ZERO
CONFIG_REQUIRES(SI_config_nil_is_zero, local_nil_is_zerop)

#define NIL 			((Object) 0)

#else
CONFIG_REQUIRES(SI_config_not_nil_is_zero, local_nil_is_zerop)

#if SI_OBJECT_INITIALIZERS_WORK

#define NIL	      SI_TAG_STORED_CONSTANT(&SI_Nil_untagged, SI_SYMBOL_TAG)

extern SI_Cons_constant SI_Nil_untagged;	/* temporary kludge */

#else

extern Object NIL;		/* or #define NIL Qnil? */

#endif /* SI_OBJECT_INITIALIZERS_WORK */
#endif /* SI_NIL_IS_ZERO */

#define Qnil NIL

/***************************************************************************
 *
 * Everything else
 *
 **************************************************************************/

/* structure-related */

#define NAMED_LISTP(o, index, sym) \
    ( CONSP(o) \
     ? EQ(IFIX(index) ? nth(index, o) : M_CAR(o) , sym) \
     : NIL)

/* obsolete */
#if 0
#if SI_SUPPORT_MF
#define setplist(sym,plist)  VALUES_1(SET_SYMBOL_PLIST(sym, plist))
#endif
#endif

#ifdef IMMEDIATE_BYTE_SPECIFIERS

#define BYTE(s, p) \
        ((Object)((((SI_Long)(s) - (int)SI_FIXNUM_TAG) << 15) | ((SI_Long)(p))))
#define BYTE_SIZE(o) \
    SI_SET_TAG(((SI_Long)(o) >> 15) & ((1L << 17) - 4L), SI_FIXNUM_TAG)
#define BYTE_POSITION(o) \
    ((Object) ((SI_Long)(o) & ((1L << 17) - 1L)))

#else

#define BYTE(s, p)              cons(s, p)
#define BYTE_SIZE(o)		M_CAR(o)
#define BYTE_POSITION(o)	M_CDR(o)

#endif

/* Misc. character stuff */

#define MAKE_CHR(c,b)		CHR(((SI_Long) (b) << 8) | (SI_Long) (c))
#define ICHAR_CODE(o)		((UCHAR) CHR_CODE(o))
#define ICHAR_FONT(o)		((UCHAR) CHR_FONT(o))
#define ICHAR_BITS(o)		((UCHAR) CHR_BITS(o))
#define ICHAR_UPCASE(c)		TOUPPER((int)ICHAR_CODE(c))

/* Integer boxing and unboxing */

#define IINTEGER(o) \
    (FIXNUMP(o) ? IFIX(o) : integer_to_long(o))
#define MAKE_INTEGER(n) \
    ((((n) > IMOST_POSITIVE_FIXNUM) || \
      ((n) < IMOST_NEGATIVE_FIXNUM)) ? \
     clong_to_bignum((SI_Long)n) : \
     FIX(n))
#define T_MAKE_INTEGER(n)	(L_temp=(n), MAKE_INTEGER(L_temp))

#define UINTEGER(o) \
    (FIXNUMP(o) ? (SI_Ulong)IFIX(o) : integer_to_unsigned_long(o))
#define UNSIGNED_FIXNUM_OVERFLOW_P(n)  ((n) > IMOST_POSITIVE_FIXNUM)


/* Mics. MF-specific */

#define ISTRING(o) SI_istring(o)
   /* or:    (SIMPLE_STRING_P(o) ? &SI_ISCHAR(o, 0) : SI_istring(o)) */




/* Various constants */

/* These become obsolete with CLtL II */
#define ICHAR_CONTROL_BIT 1L
#define ICHAR_META_BIT    2L
#define ICHAR_SUPER_BIT   4L
#define ICHAR_HYPER_BIT   8L


#if SI_SUPPORT_MF

#define XBIGNUM_TYPE BIGNUM_TYPE
#define OPT _
#define SET_SVREF(o, i, val)    (SVREF(o, i) = (val))

typedef SI_Initial_symbol SYMBOL_NODE; /* symbols.h */
typedef SI_Cons CONS_NODE;      /* MF-generated code */

#endif


/***************************************************************************
 *
 * Obsolescent
 *
 **************************************************************************/

#if SI_SUPPORT_MF

/* Type of pointer to array contents.  This properly ought to be void *,
   but for some unknown reason some C compilers can't cope with that. */
typedef char *CONTENTS_POINTER;

#endif

#define RATIO_NUMERATOR SI_RATIO_NUMERATOR /* inline.h */
#define RATIO_DENOMINATOR SI_RATIO_DENOMINATOR /* inline.h */
