#include "common_config.h"
#include <math.h>
#ifdef DEBUG_BYTE_CODE
#include <stdio.h>
#endif

typedef void *Object;
typedef Object (*fn_type)();
#define NULL 0
#define Nil 0
#define NIL 0
#define ABS(a)          ((a) <  0 ? -(a) : (a))
#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#define MAX(a,b)        ((a) > (b) ? (a) : (b))
#define SI_FIXNUM_SHIFT 2L
#define SI_OTHER_IMMED_SHIFT 2L
#define SI_HEADER_TAG (SI_OTHER_IMMED_TAG ^ (1L << SI_OTHER_IMMED_SHIFT))
#define SI_SET_TAG(u, tag) ((Object)((SI_Long)(u) + (SI_Long)(tag)))
#define SI_TAG_WIDTH 1L
#define SI_FIXNUM_TAG_VALUE 1L
#define SI_STORED_TAG_VALUE (SI_FIXNUM_TAG_VALUE^1L)
enum SI_tag {
    SI_FIXNUM_TAG      = SI_FIXNUM_TAG_VALUE,
    SI_EVEN_FIXNUM_TAG = SI_FIXNUM_TAG_VALUE,
    SI_ODD_FIXNUM_TAG  = SI_FIXNUM_TAG_VALUE ^ 4L,
    SI_OTHER_IMMED_TAG = SI_FIXNUM_TAG_VALUE ^ 2L,
    SI_CONS_TAG        = SI_STORED_TAG_VALUE,
    SI_SYMBOL_TAG      = SI_STORED_TAG_VALUE,
    SI_ARRAY_TAG       = SI_STORED_TAG_VALUE,
    SI_NUMBER_TAG      = SI_STORED_TAG_VALUE,
    SI_INSTANCE_TAG    = SI_STORED_TAG_VALUE
};
#define SI_TYPE_WIDTH		6L
#define SI_LENGTH_STATUS_WIDTH	4L
#define SI_STUFF_WIDTH 		8L
#define SI_GCALIGN_WIDTH        1L
#define SI_GCRELOCATE_WIDTH     1L
#define SI_HEADER_SHIFT 	(SI_OTHER_IMMED_SHIFT + 1)
#ifdef Platform_64bit
#define SI_BITS_PER_OBJECT 64L
#else
#define SI_BITS_PER_OBJECT 32L
#endif
#define SI_HEADER_REMAINING_BITS  \
       (SI_HEADER_SHIFT + SI_TYPE_WIDTH + \
	SI_LENGTH_STATUS_WIDTH + SI_GCALIGN_WIDTH + \
	SI_GCRELOCATE_WIDTH + SI_STUFF_WIDTH)
#if (SI_BITS_PER_OBJECT - SI_HEADER_REMAINING_BITS) < 16
#define SI_GCLENGTH_WIDTH  (SI_BITS_PER_OBJECT - SI_HEADER_REMAINING_BITS)
#else 
#define SI_GCLENGTH_WIDTH  16L
#endif
#if defined(vms) && defined(vax)
#define SI_ALIGNED_TYPE _align (LONGWORD)
#else
#define SI_ALIGNED_TYPE
#endif
#if defined(vms) || defined(ultrix) ||  defined(i386) || defined(WIN32) || defined(__osf__) || defined(__x86__) || defined(__x86_64__)
#define RTL_BIG_ENDIAN 0
#else
#define RTL_BIG_ENDIAN 1
#endif
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
#endif
enum SI_type {
    SI_UNUSED_TYPE_1,
    FIXNUM_TYPE,	
    OBIGNUM_TYPE,	
    BIGNUM_TYPE,
    RATIO_TYPE,
    DOUBLE_TYPE,
    COMPLEX_TYPE,
    INDIRECT_TYPE,	
    SYMBOL_TYPE,
    MSYMBOL_TYPE,
    USYMBOL_TYPE,
    ESYMBOL_TYPE,
    EMSYMBOL_TYPE,
    KEYWORD_TYPE,
    MKEYWORD_TYPE,
    NIL_TYPE,
    EINDIRECT_TYPE,
    CONS_TYPE,
    SI_GENERAL_ARRAY_TYPE,
    SI_PRIMITIVE_VECTOR_TYPE,
    VALUE_CELL_TYPE,
    WINDOW_TYPE,
    SI_STRUCTURE_TYPE,
    COBJECT_TYPE,
    HASH_TABLE_TYPE,
    PACKAGE_TYPE,
    PATHNAME_TYPE,
    RANDOM_STATE_TYPE,
    READTABLE_TYPE,
    STREAM_TYPE,
    SI_FUNCTION_TYPE,
    SI_GREATEST_TYPE = (1L << SI_TYPE_WIDTH) - 1L
};
#define SI_LEAST_SYMBOL_TYPE   	SYMBOL_TYPE
#define SI_LEAST_INSTANCE_TYPE SI_STRUCTURE_TYPE
#define SI_GREATEST_SYMBOL_TYPE	NIL_TYPE
#define SI_GREATEST_STANDARD_OBJECT_TYPE SI_FUNCTION_TYPE
#define SI_GREATEST_INSTANCE_TYPE SI_GREATEST_STANDARD_OBJECT_TYPE
#define SI_PRECEDES_ISYMBOLS FIXNUM_TYPE /* Arbitrary non-symbol type */

#define SI_IMMEDIATEP(o) ((o) == NIL || (SI_Ulong)(o) & 1L)
#define SI_STORED_OBJECT_P(o) (!SI_IMMEDIATEP(o))
#define SI_STORED_OBJECT_FIELD(o, t, f) ((t *)(o))->f
#define SI_STORED_OBJECT_HAS_HEADER_P(o) (SI_STORED_OBJECT_FIELD(o,SI_Header,tag)== SI_HEADER_TAG)
#define SI_STORED_OBJECT_TYPE(o ) \
    (SI_STORED_OBJECT_HAS_HEADER_P(o) \
     ? ((enum SI_type)(SI_STORED_OBJECT_FIELD(o, SI_Header, type))) \
     : CONS_TYPE)
#define SI_STORED_OBJECT_TYPEP(o, type) \
    (!SI_IMMEDIATEP(o) && SI_STORED_OBJECT_TYPE(o) == (type))
#define FIX(x) SI_SET_TAG((SI_Long)(x) << SI_FIXNUM_SHIFT, SI_FIXNUM_TAG)
#define IFIX(o) ((SI_Long)(o) >> SI_FIXNUM_SHIFT)
#define SI_FIXNUM_TAG_MASK 3
#define FIXNUMP(o) ((enum SI_tag)((long)(o) & SI_FIXNUM_TAG_MASK) == SI_FIXNUM_TAG)
typedef struct {
    Object cdr;
    Object car;
} SI_ALIGNED_TYPE SI_Cons;
#define CONSP(o) (SI_STORED_OBJECT_P(o) && !SI_STORED_OBJECT_HAS_HEADER_P(o))
#define M_CAR(o) SI_STORED_OBJECT_FIELD(o, SI_Cons, car)
#define M_CDR(o) SI_STORED_OBJECT_FIELD(o, SI_Cons, cdr)
typedef double DOUBLE;
typedef struct {
    SI_Header h;
    DOUBLE value;
} SI_ALIGNED_TYPE SI_Double_float;
#define IDOUBLE(o) SI_STORED_OBJECT_FIELD(o, SI_Double_float, value)
typedef struct {
    SI_Header h;
    Object plist;
} SI_ALIGNED_TYPE SI_Symbol;
#define SI_ENUM_LE(e1, e2) 	((unsigned) (e1) <= (unsigned) (e2))
#define SI_ENUM_GE(e1, e2) 	((unsigned) (e1) >= (unsigned) (e2))
#define SI_ENUM_EQ(e1, e2) 	((unsigned) (e1) == (unsigned) (e2))
#define SYMBOLP(o) \
    (SI_IMMEDIATEP(o) ? ((o) == NIL) : \
     (SI_ENUM_GE(SI_STORED_OBJECT_TYPE(o), SI_LEAST_SYMBOL_TYPE) && \
      SI_ENUM_LE(SI_STORED_OBJECT_TYPE(o), SI_GREATEST_SYMBOL_TYPE)))
#define SI_SYMBOL_PLIST(o) SI_STORED_OBJECT_FIELD(o, SI_Symbol, plist)
#define SI_VECTOR_PRIMITIVE_P(o) \
    SI_ENUM_EQ(SI_STORED_OBJECT_TYPE(o), SI_PRIMITIVE_VECTOR_TYPE)
#define SI_PRIMITIVE_VECTOR_P(o) \
    (!SI_IMMEDIATEP(o) && SI_VECTOR_PRIMITIVE_P(o))
#define SIMPLE_ARRAY_ANY_1_P(o) SI_PRIMITIVE_VECTOR_P(o) 
enum SI_gcls {
    SI_BORING,
    SI_BORINGER,
    SI_UGLY,
    SI_UGLIER,
    SI_NORMAL,
    A_T,
    A_STRING_CHAR,
    A_SINGLE_FLOAT,
    A_DOUBLE_FLOAT,
    A_BIT,
    A_BYTE_8,
    A_BYTE_16,
    A_BYTE_32,
    A_BYTE_64,
    A_UNSIGNED_BYTE_8,
    A_UNSIGNED_BYTE_16,
    A_UNSIGNED_BYTE_32,
    A_UNSIGNED_BYTE_64
};
#define SI_etype SI_gcls
#define SI_GENERAL_ARRAY_ETYPE(o) \
    ((enum SI_etype) (SI_STORED_OBJECT_FIELD(o, SI_Header, stuff) & 15))
#define SI_ARRAY_ETYPE(o) SI_GENERAL_ARRAY_ETYPE(o)
#define INLINE_UNSIGNED_BYTE_16_VECTOR_P(symbol) \
    (SIMPLE_ARRAY_ANY_1_P(symbol) && \
     ((long)SI_ARRAY_ETYPE(symbol) == A_UNSIGNED_BYTE_16))
typedef struct {
    SI_Header h;
    Object length;
} SI_ALIGNED_TYPE SI_Primitive_vector;
#define SIMPLE_ARRAY_ANY_1_LENGTH(o) \
    SI_STORED_OBJECT_FIELD(o, SI_Primitive_vector, length)
#define SI_PRIMITIVE_VECTOR_ETYPE(o) \
    ((enum SI_etype) SI_STORED_OBJECT_FIELD(o, SI_Header, stuff))
#define SI_PRIMITIVE_VECTOR_ETYPEP(o, etype) \
    (SI_STORED_OBJECT_TYPEP(o, SI_PRIMITIVE_VECTOR_TYPE) && \
     SI_PRIMITIVE_VECTOR_ETYPE(o) == etype)
#define SIMPLE_VECTOR_P(o) SI_PRIMITIVE_VECTOR_ETYPEP(o, A_T)
#define SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(type, etype) \
  typedef struct { \
      SI_Primitive_vector h; \
      etype contents[1]; \
  } SI_ALIGNED_TYPE type
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Object,Object);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Double,double);
SI_DEFINE_TYPED_PRIMITIVE_VECTOR_STRUCT(SI_PVT_Uchar,unsigned char);
#define SI_PRIMITIVE_VECTOR_CONTENTS(o, t) SI_STORED_OBJECT_FIELD(o, t, contents)
#define SI_ISVREF(o, i) SI_PRIMITIVE_VECTOR_CONTENTS(o, SI_PVT_Object)[i]
#define UBYTE_8_ISAREF_1(a, i1) SI_PRIMITIVE_VECTOR_CONTENTS(a, SI_PVT_Uchar)[i1]
#define BYTE_VECTOR_AREF(vctr,offst) (FIX(UBYTE_8_ISAREF_1(vctr,IFIX(offst))))
#define FLOAT_VECTOR_AREF(thing,index) (((SI_PVT_Double *)(thing))->contents[IFIX(index)])
#define SI_FUNCTIONP(o) SI_STORED_OBJECT_TYPEP(o, SI_FUNCTION_TYPE)
typedef struct {
    SI_Header h;
    Object (*entry)();
    Object env;
} SI_Function;
#define SI_FUNCTION_ENTRY(o) SI_STORED_OBJECT_FIELD(o,SI_Function,entry)

#define ATOM(a) (!CONSP(a))
#define COMPILED_FUNCTION_P(o) SI_FUNCTIONP(o)
#define DOUBLE_ABS(a) (fabs(a))
#define DOUBLE_ADD(a,b) ((a)+(b))
#define DOUBLE_DIVIDE(a,b) ((a)/(b))
#define DOUBLE_EQ(a,b) ((a)==(b))
#define DOUBLE_FLOAT_TO_DOUBLE(x) ((double)IDOUBLE(x))
#define DOUBLE_GE(a,b) ((a)>=(b))
#define DOUBLE_GT(a,b) ((a)>(b))
#define DOUBLE_LE(a,b) ((a)<=(b))
#define DOUBLE_LT(a,b) ((a)<(b))
#define DOUBLE_MAX(a,b) (MAX(a,b))
#define DOUBLE_MIN(a,b) (MIN(a,b))
#define DOUBLE_MINUS(a,b) ((a)-(b))
#define DOUBLE_NE(a,b) ((a)!=(b))
#define DOUBLE_NEGATE(a) (0.0-(a))
#define DOUBLE_PLUSP(a) ((a)>0.0)
#define DOUBLE_SUB1(a) ((a)-1.0)
#define DOUBLE_TIMES(a,b) ((a)*(b))
#define EQ(a, b) ((a)==(b))
#define FIXNUM_ABS(a) (FIXNUM_MINUSP(a)?FIXNUM_NEGATE(a):(a))
#define FIXNUM_ADD(a,b) ((Object)((SI_Long)(a) - 1L + (SI_Long)(b)))
#define FIXNUM_DIVIDE(a,b) FIXNUM_TRUNCATE(a,b)
#define FIXNUM_EQ(a,b) ((SI_Long)(a) == (SI_Long)(b))
#define FIXNUM_GE(a,b) ((SI_Long)(a) >= (SI_Long)(b))
#define FIXNUM_GT(a,b) ((SI_Long)(a) > (SI_Long)(b))
#define FIXNUM_LE(a,b) ((SI_Long)(a) <= (SI_Long)(b))
#define FIXNUM_LOGAND(a,b) ((Object)((SI_Long)(a) & (SI_Long)(b)))
#define FIXNUM_LOGANDC2(a,b) ((Object)((SI_Long)(a) & (~(SI_Long)(b) ^ 3L)))
#define FIXNUM_LOGIOR(a,b) ((Object)((SI_Long)(a) | (SI_Long)(b)))
#define FIXNUM_LSH(a,b) (Object)(((((SI_Long)(a) - 1L) << IFIX(b)) + 1L))
#define FIXNUM_LT(a,b) ((SI_Long)(a) < (SI_Long)(b))
#define FIXNUM_MAX(a,b) ((Object)(MAX((SI_Long)(a), (SI_Long)(b))))
#define FIXNUM_MIN(a,b) ((Object)(MIN((SI_Long)(a), (SI_Long)(b))))
#define FIXNUM_MINUS(a,b) ((Object)((SI_Long)(a) - ((SI_Long)(b) - 1L)))
#define FIXNUM_MINUSP(a) ((SI_Long)(a) < 1L)
#define FIXNUM_NE(a,b) ((SI_Long)(a) != (SI_Long)(b))
#define FIXNUM_NEGATE(a) ((Object)(2L - (SI_Long)(a)))
#define FIXNUM_PLUSP(a) ((SI_Long)(a) > 1L)
#define FIXNUM_RSH(a,b) (Object)((((SI_Long)(a) >> IFIX(b)) & ~3L) + 1L)
#define FIXNUM_SUB1(a) ((Object)((SI_Long)(a) - 4L))
#define FIXNUM_TIMES(a,b) ((Object)(IFIX(a) * ((SI_Long)(b) - 1L) + 1L))
#define INLINE_SYMBOL_PLIST(symbol) ((symbol) == NIL ? SI_Plist_of_nil : SI_SYMBOL_PLIST(symbol))
#define DOUBLE_FLOAT_VECTOR_P(thing) SI_PRIMITIVE_VECTOR_ETYPEP(thing, A_DOUBLE_FLOAT)
#define SVREF(o, i) SI_ISVREF(o, IFIX(i))

#define ISNULL(x) (x == NULL)
#define FLOAT(fixnum,sample_float) ((double)(IFIX(fixnum)))
#define CEILING(float) (FIX((SI_Long)ceil(float)))
#define FLOOR(float) (FIX((SI_Long)floor(float)))
#define DECFF(loc,incr) (((SI_Long)(loc))-=((SI_Long)(incr)-SI_FIXNUM_TAG))
#define INCFF(loc,incr) (((SI_Long)(loc))+=((SI_Long)(incr)-SI_FIXNUM_TAG))

#define inline_funcall_1(fptr,arg1) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1)
#define inline_funcall_2(fptr,arg1,arg2) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2)
#define inline_funcall_3(fptr,arg1,arg2,arg3) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3)
#define inline_funcall_4(fptr,arg1,arg2,arg3,arg4) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4)
#define inline_funcall_5(fptr,arg1,arg2,arg3,arg4,arg5) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5)

extern Object *byte_code_constants;
extern Object **byte_code_variables;
extern fn_type *byte_code_functions;
extern fn_type *byte_code_run_time_functions;

#define DOUBLE_TO_DOUBLE_FLOAT(x)    ((byte_code_run_time_functions[0])(x))

#define MVS_2(r,a,b) ((a)=(r),((byte_code_run_time_functions[5])(&b)))
#define MVS_3(r,a,b,c) ((a)=(r),((byte_code_run_time_functions[3])(&b,&c)))

#define get_variable(x)  (*(byte_code_variables[x]))
#define get_constant(x)  (byte_code_constants[x])

#define call_simple_function_0(x) ((byte_code_functions[x])())
#define call_simple_function_1(x,a1) ((byte_code_functions[x])(a1))
#define call_simple_function_2(x,a1,a2) ((byte_code_functions[x])(a1,a2))
#define call_simple_function_3(x,a1,a2,a3) ((byte_code_functions[x])(a1,a2,a3))
#define call_simple_function_4(x,a1,a2,a3,a4) ((byte_code_functions[x])(a1,a2,a3,a4))
#define call_simple_function_5(x,a1,a2,a3,a4,a5) ((byte_code_functions[x])(a1,a2,a3,a4,a5))
#define call_simple_function_6(x,a1,a2,a3,a4,a5,a6) ((byte_code_functions[x])(a1,a2,a3,a4,a5,a6))
#define call_simple_function_7(x,a1,a2,a3,a4,a5,a6,a7) ((byte_code_functions[x])(a1,a2,a3,a4,a5,a6,a7))
#define call_simple_function_8(x,a1,a2,a3,a4,a5,a6,a7,a8) ((byte_code_functions[x])(a1,a2,a3,a4,a5,a6,a7,a8))

#define call_function_4(x,a1,a2,a3,a4) ((byte_code_functions[x])(a1,a2,a3,a4))
#define call_function_5(x,a1,a2,a3,a4,a5) ((byte_code_functions[x])(a1,a2,a3,a4,a5))
#define call_function_6(x,a1,a2,a3,a4,a5,a6) ((byte_code_functions[x])(a1,a2,a3,a4,a5,a6))
#define call_function_7(x,a1,a2,a3,a4,a5,a6,a7) ((byte_code_functions[x])(a1,a2,a3,a4,a5,a6,a7))

#define funcall_compiled_function_2(x,a1,a2) ((byte_code_run_time_functions[4])(x,a1,a2))

#ifdef DEBUG_BYTE_CODE
#  define debug_print_byte_code_pc_and_tos(pc,tos) \
 fprintf(stderr, "%s pc=%d, tos=%d\n",fn_name,IFIX(pc),IFIX(tos)); fflush(stderr)
#  define debug_print_byte_code_pc_stack_base_and_offset(pc,base, offset) \
 fprintf(stderr, "%s pc=%d, base=%d, offset=%d\n",fn_name,IFIX(pc),IFIX(base), IFIX(offset)); fflush(stderr)
#else
#  define debug_print_byte_code_pc_and_tos(pc,tos) 
#  define debug_print_byte_code_pc_stack_base_and_offset(pc,base, offset)
#endif

#define T (byte_code_constants[33])

#define rtl_length(x) ((byte_code_run_time_functions[1])(x))
#define SI_Plist_of_nil (byte_code_run_time_functions[2])

#ifdef WIN32
#  define DLLEXPORT __declspec( dllexport )
#else
#  define DLLEXPORT
#endif

#define check_version(v) ((( SI_Long (*)(SI_Long)  )(args[4]))((SI_Long)FIX(v)))

#define add_compiled_function(fn) ((( void (*)(SI_Long)  )(args[5]))((SI_Long)(fn)))
