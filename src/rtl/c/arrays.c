/*
 * arrays.c -  Array creation and initialization
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"
#include <stdio.h>

extern TLS SI_Area *Current_area;
extern Object Pcl;
extern Object Ptx;
extern Object Qbase_char;
extern Object Qbit;
extern Object Qdouble_float;
extern Object Qfloat;
extern Object Qlong_float;
extern Object Qshort_float;
extern Object Qsigned_byte;
extern Object Qsingle_float;
extern Object Qstandard_char;
extern Object Qstring_char;
extern Object Qunsigned_byte;
#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area;
extern SI_Area Static_area;
extern SI_Area Local_area;

#if SI_USE_PROTOTYPES

extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_malloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object g2rtl_make_malloced_array();
extern void g2rtl_free_malloced_array_internal(Object array);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object STATIC_FLOAT(DOUBLE d);
extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object elt(Object,Object);
extern Object equal(Object,Object);
extern SI_Long integer_to_long(Object n);
extern SI_Ulong integer_to_unsigned_long(Object n);
extern Object list(long,...);
extern Object upgraded_array_element_type(Object type, Object env);

#else

extern Object SI_alloc_primitive_vector();
extern Object SI_malloc_primitive_vector();
extern void g2rtl_free_malloced_array_internal();
extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();
extern Object STATIC_FLOAT();
extern Object STATIC_FUNCTION1();
extern Object elt();
extern Object equal();
extern SI_Long integer_to_long();
extern SI_Ulong integer_to_unsigned_long();
extern Object list();
extern Object upgraded_array_element_type();

#endif



#ifndef LAZILY_INITIALIZED_PACKAGES

extern Object SI_NEW_SYMBOL(/* Object *package, char *name, int externalp */);
#undef NEW_SYMBOL
#define NEW_SYMBOL(pkg, name, externalp) SI_NEW_SYMBOL(&pkg, name, externalp)

#endif

static void initialize_contents(), initialize_element();
static SI_Dimension init_arr();
static Object temp_array_row_major_index();
static enum SI_etype type_to_etype();

Object Array_rank_limit = ARRAY_RANK_LIMIT;
Object Array_dimension_limit = ARRAY_DIMENSION_LIMIT;
Object Array_total_size_limit = ARRAY_TOTAL_SIZE_LIMIT;


Object make_array (dimensions, element_type, initial_element, initial_contents,
		   adjustable, fill_pointer, displaced_to,
		   displaced_index_offset)
    Object dimensions, element_type, initial_element, initial_contents,
	   adjustable, fill_pointer, displaced_to, displaced_index_offset;
{
    Declare_local_temp;
    register long i;
    enum SI_etype etype;
    SI_Dimension dims[IARRAY_RANK_LIMIT];
    Object dimension_vector;
    long rank;
    SI_Dimension size;
    long dim;
    Object temp, arr;
    Declare_stack_pointer;
    SI_Declare_static_constant(FLOAT_ZERO, d, STATIC_FLOAT(0.0));

    SAVE_STACK();
    PROTECT_8(dimensions,element_type,initial_element,initial_contents,
	adjustable, fill_pointer,displaced_to, displaced_index_offset);
    PROTECTI_3(temp, arr, dimension_vector);
    if (UNSUPPLIED_P(element_type))
	element_type = T;
    if (!SUPPLIEDP(adjustable))
	adjustable = NIL;
    if (!SUPPLIEDP(fill_pointer))
	fill_pointer = NIL;
    if (!SUPPLIEDP(displaced_to))
	displaced_to = NIL;
    if (!SUPPLIEDP(displaced_index_offset))
	displaced_index_offset = ZERO;

    rank = 0;
    if (CONSP(dimensions)) {
	for (temp = dimensions; temp != NIL; temp = M_CDR(temp)) {
	    if (rank >= IARRAY_RANK_LIMIT) {
		warn(2, "make_array: rank exceeds ARRAY-RANK-LIMIT - ~s",
		     dimensions);
		break;
	    }
	    dim = T_IFIX(M_CAR(temp));
	    if (dim < 0 || dim >= IARRAY_DIMENSION_LIMIT)
		error(2, "make_array: invalid dimension - ~s", M_CAR(temp));
	    dims[rank++] = dim;
	}
    } else if (dimensions != NIL) {
	rank = 1L;
	dim = IFIX(dimensions);
	if (dim < 0 || dim >= IARRAY_DIMENSION_LIMIT)
	    error(2, "make_array: invalid dimension - ~s", dimensions);
	dims[0] = dim;
    }

    etype = type_to_etype(element_type);

    if (UNSUPPLIED_P(initial_element))
	switch (etype) {
	case A_STRING_CHAR:
	    initial_element = CHR('\0');
	    break;
	case A_SINGLE_FLOAT:
	case A_DOUBLE_FLOAT:
	    initial_element = FLOAT_ZERO;
	    break;
	case A_T:
	    initial_element = NIL;
	    break;
	default:
	    initial_element = ZERO;
	}

    for (size = 1L, i = 0; i < rank; i++) {
	size *= dims[i];
	if (size >= IARRAY_TOTAL_SIZE_LIMIT) {
	    warn(2, "make_array: size exceeds ARRAY-TOTAL-SIZE-LIMIT - ~s",
		 dimensions);
	    size = IARRAY_TOTAL_SIZE_LIMIT - 1L;
	    break;
	}
    }
    if (rank != 1L ||
	fill_pointer != NIL ||
	adjustable != NIL ||
	displaced_to != NIL) {
	arr = SI_ALLOC(SI_General_array,
		       SI_GENERAL_ARRAY_TYPE,
		       SI_ARRAY_TAG,
		       SI_NORMAL);

	/* Structure must be initialized before more allocation happens */
	SI_INIT_GENERAL_ARRAY(arr, rank, etype);
	SI_GENERAL_ARRAY_DISPLACED_TO(arr) = UNBOUND;
	SI_DISPLACED_INDEX_OFFSET(arr) = displaced_index_offset;
	if (rank == 1L)
	    SI_GENERAL_VECTOR_FILL_POINTER(arr) =
		(FIXNUMP(fill_pointer) ? fill_pointer : FIX(dims[0]));
	else {
	    SI_GENERAL_NVARRAY_DIMENSIONS(arr) = UNBOUND; /* for gc */
	    dimension_vector =
		SI_alloc_primitive_vector((SI_Dimension)rank,
					  SI_DIMENSION_ETYPE);
	    SI_GENERAL_NVARRAY_DIMENSIONS(arr) = dimension_vector;
	    /* Copy dimensions into header */
	    for (i = 0; i < rank; i++)
		SI_PRIMITIVE_VECTOR_CONTENTS(dimension_vector,
					     SI_PVT_Dimension)[i] =
						 dims[i];
	}

	/* Body must be allocated *last* - must initialize it before next GC */
	temp = SI_alloc_primitive_vector(size, etype);
	SI_GENERAL_ARRAY_DISPLACED_TO(arr) = temp;
    } else
	arr = SI_alloc_primitive_vector(size, etype);

    /* Initialize array. */
    if (UNSUPPLIED_P(initial_contents))
        initialize_element(arr, size, initial_element);
    else if (rank == 0)
	initialize_element(arr, size, initial_contents);
    else
	initialize_contents(arr, rank, initial_contents);

    RESTORE_STACK();
    return VALUES_1(arr);
}

/* This only makes a 1-dimensional simple array, with element-type of 
 * (unsigned-byte 16), and no other arguments specified.
 * but it malloc's the space for it, pads by one or two bytes to return
 * an even address, and marks the amount of padding so it can be freed by
 * a call to free_malloced_array_internal.
 */

/* This code assumes SI_TAG_WIDTH == 1, and that no GC is in use,
 * and that the following macros copied from heap.c haven't been changed.
 */

/* This isn't really the correct definition of SI_INIT_DYNAMICNESS_LABEL,
 * but it's good enough given that we're not using GC. Including the
 * real definition, as we did with SI_INIT_HEADER by moving it from heap.c
 * to object.h, introduces a real mess, because it references all kinds
 * of other stuff private to heap.c.
 */
#pragma warning(push) 
#pragma warning(disable : 4005)
#if defined SI_INIT_DYNAMICNESS_LABEL
#undef SI_INIT_DYNAMICNESS_LABEL
#endif

#define SI_INIT_DYNAMICNESS_LABEL(o)    (0)
#pragma warning(pop)

Object make_malloced_array (length)
    long length;
{
    Object arr = NULL;
    enum SI_etype etype = A_UNSIGNED_BYTE_16;
    
    /*
    fprintf(stderr, "make_malloced_array called on length %ld\n", length);
    fflush(stdout);
    */
    arr = SI_malloc_primitive_vector(length, etype);

    initialize_element(arr, length, (Object)ZERO);
    return arr;
}


static void initialize_element (arr, total_size, initial_element)
    Object arr, initial_element;
    SI_Dimension total_size;
{
    Object pv = arr;
    register SI_Dimension i;
    enum SI_etype etype;

    UCHAR char_elem;
    SI_BITS_TYPE bit_elem;
    float float_elem;
    double double_elem;
    short byte16_elem;
    SI_Long byte32_elem;
    SI_int64 byte64_elem;
    unsigned char ubyte8_elem;
    unsigned short ubyte16_elem;
    SI_Ulong ubyte32_elem;
    SI_uint64 ubyte64_elem;

    while (!SI_VECTOR_PRIMITIVE_P(pv))
	/* ought to track displaced offset as well */
        pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);

    etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

    switch (etype) {
    case A_T:
	if (initial_element==0 && total_size > 5)
	    memset(SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Object), 0, sizeof(Object) * total_size);
	else
	for (i = 0; i < total_size; i++) {
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Object)[i] = initial_element;
	}
	break;
    case A_STRING_CHAR:
	char_elem = CHR_CODE(initial_element);
	for (i = 0; i < total_size; i++) {
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i] = char_elem;
	}
	break;
    case A_SINGLE_FLOAT:
	float_elem = (float)IDOUBLE(initial_element);
	for (i = 0; i < total_size; i++) {
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Float)[i] = float_elem;
	}
	break;
    case A_DOUBLE_FLOAT:
	double_elem = IDOUBLE(initial_element);
	for (i = 0; i < total_size; i++) {
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Double)[i] = double_elem;
	}
	break;
    case A_BIT:
	bit_elem = (FIXNUM_ODDP(initial_element) ? -1 : 0);
	total_size += SI_BITS_TYPE_MASK;	/* convert to block count */
	total_size >>= SI_BITS_TYPE_SHIFT;
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Bits)[i] = bit_elem;
	break;
    case A_BYTE_8:
	char_elem = (UCHAR)IFIX(initial_element);
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i] = char_elem;
	break;
    case A_BYTE_16:
	byte16_elem = (short)IFIX(initial_element);
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Short)[i] = byte16_elem;
	break;
    case A_BYTE_32:
	byte32_elem = INTEGER_TO_INT(initial_element);
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long)[i] = byte32_elem;
	break;
    case A_BYTE_64:
	byte64_elem = INTEGER_TO_INT64(initial_element);
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long64)[i] = byte64_elem;
	break;
    case A_UNSIGNED_BYTE_8:
	ubyte8_elem = (unsigned char)IFIX(initial_element);
	if (ubyte8_elem == 0 && total_size > 5)
	    memset(SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Uchar), 0, total_size * sizeof(unsigned char));
	else
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Uchar)[i] = ubyte8_elem;
	break;
    case A_UNSIGNED_BYTE_16:
	ubyte16_elem = (unsigned short)IFIX(initial_element);
	if (ubyte16_elem == 0 && total_size > 5)
	    memset(SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ushort), 0, total_size * sizeof(unsigned short));
	else
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ushort)[i] = ubyte16_elem;
	break;
    case A_UNSIGNED_BYTE_32:
	ubyte32_elem = INTEGER_TO_UNSIGNED_LONG(initial_element);
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong)[i] = ubyte32_elem;
	break;
    case A_UNSIGNED_BYTE_64:
	ubyte64_elem = INTEGER_TO_UINT64(initial_element);
	for (i = 0; i < total_size; i++)
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong64)[i] = ubyte64_elem;
	break;
    default:
	error(1, "initialize_element: unknown element type");
	break;
    }
}

/* This could be optimized more. */
Object SI_fill_primitive_vector(pv, init)
    Object pv, init;
{   initialize_element(pv, SI_PRIMITIVE_VECTOR_LENGTH(pv), init);
    return pv;
}

static void initialize_contents (arr, rank, initial_contents)
    Object arr, initial_contents;
    long rank;
{
    Object pv = arr;
    enum SI_etype etype;
    SI_Dimension *pdim;
    SI_Dimension kludge;

    if (UNSUPPLIED_P(initial_contents))
	return;

    while (!SI_VECTOR_PRIMITIVE_P(pv))
	/* ought to track displaced offset as well */
        pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);

    if (SI_VECTOR_PRIMITIVE_P(arr)) {
	rank = 1L;
	kludge = SI_PRIMITIVE_VECTOR_LENGTH(arr);
	pdim = &kludge;
    }
    else {
	rank = SI_GENERAL_ARRAY_RANK(arr);
	if (rank == 1L) {
	    kludge = /* array_dimension(arr, FIX(0)) */
		     SI_PRIMITIVE_VECTOR_LENGTH(pv);
	    pdim = &kludge;
	} else
	    pdim = &SI_GENERAL_NVARRAY_DIMENSION(arr, 0);
    }

    etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

    (void)init_arr(pv, (SI_Dimension)0, etype, rank, pdim, initial_contents);
}

/* Returns an updated (row-major) index into the array. */

static SI_Dimension init_arr (pv, i, etype, rank, pdim, initial_contents)
    Object pv;
    SI_Dimension i;
    enum SI_etype etype;
    long rank;
    SI_Dimension *pdim;
    Object initial_contents;
{
    SI_Dimension idim, j;
    Object elem;

    /* Speed could definitely be imporved here */
    if (rank > 0) {
	idim = *pdim++;
	--rank;
	for (j = 0; j < idim; j++)
	    i = init_arr(pv, i, etype, rank, pdim,
			 elt(initial_contents, FIX(j)));
	return i;
    }
    else {
	elem = initial_contents;
#	define DO_IT(type, etype, value) \
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, type)[i] = (etype)(value); \
		break;
	switch (etype) {
	case A_T:
	    DO_IT(SI_PVT_Object, Object, elem);
	case A_STRING_CHAR:
	    DO_IT(SI_PVT_Char, char, CHR_CODE(elem));
	case A_SINGLE_FLOAT:
	    DO_IT(SI_PVT_Float, float, SINGLE_FLOAT_TO_FLOAT(elem));
	case A_DOUBLE_FLOAT:
	    DO_IT(SI_PVT_Double, double, IDOUBLE(elem));
	case A_BIT:
	    if (FIXNUM_ODDP(elem))
		SI_SBIT_ACCESS(pv,i) |= SI_SBIT_MASK(i);
	    else
		SI_SBIT_ACCESS(pv,i) &= ~SI_SBIT_MASK(i);
	    break;
	case A_BYTE_8:
	    DO_IT(SI_PVT_Char, char, IFIX(elem));
	case A_BYTE_16:
	    DO_IT(SI_PVT_Short, short, IFIX(elem));
	case A_BYTE_32:
	    DO_IT(SI_PVT_Long, SI_Long, INTEGER_TO_LONG(elem));
	case A_BYTE_64:
	    DO_IT(SI_PVT_Long64, SI_int64, INTEGER_TO_INT64(elem));
	case A_UNSIGNED_BYTE_8:
	    DO_IT(SI_PVT_Uchar, unsigned char, IFIX(elem));
	case A_UNSIGNED_BYTE_16:
	    DO_IT(SI_PVT_Ushort, unsigned short, IFIX(elem));
	case A_UNSIGNED_BYTE_32:
	    DO_IT(SI_PVT_Ulong, SI_Ulong, INTEGER_TO_UNSIGNED_LONG(elem));
	case A_UNSIGNED_BYTE_64:
	    DO_IT(SI_PVT_Ulong64, SI_uint64, INTEGER_TO_UINT64(elem));
	default:
	    error(1, "initialize_contents: unknown element type");
	    break;
	}
#       undef DO_IT
	return i+1;
    }
}

/* Miscellaneous */

#if 0 /* SI_SUPPORT_MF */
/* This is temporary -- only for MF's arefr and setf_arefr */
static Object temp_array_row_major_index (a, subscripts)
    Object a;
    Object subscripts;
{
    Declare_local_temp;
    SI_Dimension i, j;
    int rank;
    SI_Dimension *pdim;
    Object s, first;

    if (SI_PRIMITIVE_VECTOR_P(a))
	return VALUES_1(M_CAR(subscripts));

    rank = SI_GENERAL_ARRAY_RANK(a);
    if (rank == 0)
	return VALUES_1(ZERO);
    first = M_CAR(subscripts);
    if (rank == 1)
	return VALUES_1(first);
    j = IFIX(first);
    pdim = &SI_GENERAL_NVARRAY_DIMENSION(a, 0);
    for (i = 1, s = M_CDR(subscripts);
	 i < rank && s != NIL;
	 ++i, s = M_CDR(s)) {
	j *= *++pdim;
	j += IFIX(M_CAR(s));
    }
    if (i < rank || s != NIL)
	warn(3, "array_row_major_index: inconsistent arguments - ~S ~S",
	     a, subscripts);
    return VALUES_1(FIX(j));
}
#endif

/* Vector of element types, for type_to_etype and array_element_type.
 *
 * Element_types used to be defined as a variable with a static initializer.
 * When modifying things to not use static initializers, it was easier to just
 * redefine it with this macro definition than to modify all the places that
 * referenced it.
 */

#define Element_types \
    (SI_Etypes_var == UNBOUND ? SI_initialize_array_element_types() : SI_Etypes_var)

#define ETYPES_SIZE 18L
Object SI_Etypes_var = UNBOUND;

Object SI_initialize_array_element_types()
{ Declare_area(a);
  Object v;

  SAVE_CURRENT_AREA(a);
  SET_CURRENT_AREA(Static_area);
  Qstring_char = NEW_SYMBOL(Ptx,"STRING-CHAR",TRUE);
  Qsingle_float = NEW_SYMBOL(Pcl,"SINGLE-FLOAT",TRUE);
  Qdouble_float = NEW_SYMBOL(Pcl,"DOUBLE-FLOAT",TRUE);
  Qbit = NEW_SYMBOL(Pcl,"BIT",TRUE);
  Qsigned_byte = NEW_SYMBOL(Pcl,"SIGNED-BYTE",TRUE);
  Qunsigned_byte = NEW_SYMBOL(Pcl,"UNSIGNED-BYTE",TRUE);
  SI_Etypes_var = v = SI_alloc_primitive_vector((SI_Dimension)ETYPES_SIZE, A_T);
  SI_ISVREF(v, 0) = NIL;
  SI_ISVREF(v, 1) = NIL;
  SI_ISVREF(v, 2) = NIL;
  SI_ISVREF(v, 3) = NIL;
  SI_ISVREF(v, 4) = NIL;
  SI_ISVREF(v, A_T) = T;
  SI_ISVREF(v, A_STRING_CHAR) = Qstring_char;
  SI_ISVREF(v, A_SINGLE_FLOAT) = Qsingle_float;
  SI_ISVREF(v, A_DOUBLE_FLOAT) = Qdouble_float;
  SI_ISVREF(v, A_BIT) = Qbit;
  SI_ISVREF(v, A_BYTE_8) = LIST_2(Qsigned_byte, FIX(8));
  SI_ISVREF(v, A_BYTE_16) = LIST_2(Qsigned_byte, FIX(16));
  SI_ISVREF(v, A_BYTE_32) = LIST_2(Qsigned_byte, FIX(32));
  SI_ISVREF(v, A_BYTE_64) = LIST_2(Qsigned_byte, FIX(64));
  SI_ISVREF(v, A_UNSIGNED_BYTE_8) = LIST_2(Qunsigned_byte, FIX(8));
  SI_ISVREF(v, A_UNSIGNED_BYTE_16) = LIST_2(Qunsigned_byte, FIX(16));
  SI_ISVREF(v, A_UNSIGNED_BYTE_32) = LIST_2(Qunsigned_byte, FIX(32));
  SI_ISVREF(v, A_UNSIGNED_BYTE_64) = LIST_2(Qunsigned_byte, FIX(64));
  RESTORE_CURRENT_AREA(a);
  return v;
}

static enum SI_etype type_to_etype (type)
    Object type;
{   SI_Declare_static_constant(FP_EQUAL, d,
			       STATIC_FUNCTION(equal, NIL, FALSE, 2, 2));
    Object upgraded;
    Object etypes_var = Element_types;
    SI_Dimension i;
    upgraded = upgraded_array_element_type(type, NIL);

    /* Optimize purpose only, the later "for" loop can do all the things. */
    if (EQ(upgraded, SI_ISVREF(etypes_var, A_T)))
	return (enum SI_etype)A_T;
    else if (EQ(upgraded, SI_ISVREF(etypes_var, A_UNSIGNED_BYTE_16)))
        return (enum SI_etype)A_UNSIGNED_BYTE_16;
    else if (EQ(upgraded, SI_ISVREF(etypes_var, A_DOUBLE_FLOAT)))
	return (enum SI_etype)A_DOUBLE_FLOAT;
    else if (EQ(upgraded, SI_ISVREF(etypes_var, A_UNSIGNED_BYTE_8)))
	return (enum SI_etype)A_UNSIGNED_BYTE_8;
    else {
        for (i = ETYPES_SIZE-1; i >= 0; --i)
	    if (EQ(upgraded, SI_ISVREF(etypes_var, i)))
	    return (enum SI_etype)i;
        error(3, "type_to_etype: internal error - ~S/~S", type, upgraded);
    }
    /*NOTREACHED*/
}


Object upgraded_array_element_type (type, env)
    Object type, env;
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;
    Object etypes_var = Element_types;

    if (UNSUPPLIED_P(env)) {
	env = NIL;
    }
    if (env != NIL)
	error(1, "upgraded_array_element_type: environments NYI");

    SAVE_STACK();
    PROTECT_1(type);
    PROTECTI_1(temp1);
    if (SYMBOLP(type)) {
	if (EQ(type,Qstandard_char) || EQ(type,Qbase_char))
	    type = Qstring_char; 
	if (EQ(type,Qstring_char) ||
	    EQ(type,Qbit)) {
	    temp1 = VALUES_1(type);
	}
	else if (EQ(type,Qdouble_float) || EQ(type,Qfloat) || EQ(type,
		Qlong_float)) {
	    temp1 = VALUES_1(Qdouble_float);
	}
	else if (EQ(type,Qsingle_float) || EQ(type,Qshort_float)) {
	    temp1 = VALUES_1(Qsingle_float);
	}
	else 
	    temp1 = VALUES_1(T);
    }
    else if (!CONSP(type)) {
	temp1 = VALUES_1(T);
    }
    else if (EQ(CAR(type),Qsigned_byte)) {
	if (FIXNUM_LE(CADR(type),FIX(8L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_BYTE_8)));
	}
	else if (FIXNUM_LE(CADR(type),FIX(16L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_BYTE_16)));
	}
	else if (FIXNUM_LE(CADR(type),FIX(32L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_BYTE_32)));
	}
	else if (FIXNUM_LE(CADR(type),FIX(64L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_BYTE_64)));
	}
	else 
	    temp1 = VALUES_1(T);
    }
    else if (EQ(CAR(type),Qunsigned_byte)) {
	if (FIXNUM_LE(CADR(type),FIX(1L))) {
	    temp1 = VALUES_1(Qbit);
	}
	else if (FIXNUM_LE(CADR(type),FIX(8L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_UNSIGNED_BYTE_8)));
	}
	else if (FIXNUM_LE(CADR(type),FIX(16L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_UNSIGNED_BYTE_16)));
	}
	else if (FIXNUM_LE(CADR(type),FIX(32L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_UNSIGNED_BYTE_32)));
	}
	else if (FIXNUM_LE(CADR(type),FIX(64L))) {
	    temp1 = VALUES_1(SVREF(etypes_var, FIX(A_UNSIGNED_BYTE_64)));
	}
	else 
	    temp1 = VALUES_1(T);
    }
    else 
	temp1 = VALUES_1(T);
    RESTORE_STACK();
    return(temp1);
}

Object array_element_type (arr)
    Object arr;
{
    Declare_local_temp;
    return VALUES_1(SI_ISVREF(Element_types, (long)SI_ARRAY_ETYPE(arr)));
}
