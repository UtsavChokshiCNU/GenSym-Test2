/*
 * statics.c - allocators and globals for various startup data
 *             STATIC_CONS and STATIC_STRING could go to separate files
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;

#if SI_USE_PROTOTYPES

extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object cons(Object,Object);

#else

extern Object SI_alloc_primitive_vector();
extern Object SI_alloc();
extern Object cons();

#endif


extern Object xmake_canonical_rational();

/* Note use of ldelete, lremove */


/* A bunch of hair to conditionalize MAKE_FUNCTION for CLOS support. */
#if SI_SUPPORT_CLOS
#if SI_OBJECT_INITIALIZERS_WORK

/* The variable SI_Function_slot_vector is needed to support static
 * initializers for functions (see CONSTANT_COMPILED_FUNCTION) anyway, so
 * might as well make use of it here too.
 */
struct SI_Function_slot_vector_struct SI_Function_slot_vector =
    {{SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR(A_T, 0), {FIX(0)}}};
static Object Function_slot_vector = TAG_VECTOR(SI_Function_slot_vector);

/* If object initializers work, then the slot vector is already allocated,
 * and this doesn't have to do anything.
 */
#define ALLOCATE_FUNCTION_SLOT_VECTOR()

#else /* !SI_OBJECT_INITIALIZERS_WORK */

/* Lazily allocate a zero-length simple-vector in static space. */
static Object Function_slot_vector = UNBOUND;
#define ALLOCATE_FUNCTION_SLOT_VECTOR() \
    if (EQ(Function_slot_vector, UNBOUND)) { \
      Declare_area(a); \
      SAVE_CURRENT_AREA(a); \
      SET_CURRENT_AREA(Static_area); \
      Function_slot_vector = SI_alloc_primitive_vector((SI_Dimension)0, A_T); \
      RESTORE_CURRENT_AREA(a); \
    }

#endif

#else /* !SI_SUPPORT_CLOS */

/* If not supporting CLOS, this is a nop. */
#define ALLOCATE_FUNCTION_SLOT_VECTOR()		/* nothing */

#endif

Object MAKE_FUNCTION (entry, env, variadicp, nreq, npos)
    Object (*entry)(), env;
    long variadicp, nreq, npos;
{
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(env);

    ALLOCATE_FUNCTION_SLOT_VECTOR();

    result = SI_ALLOC(SI_Function, SI_FUNCTION_TYPE, SI_INSTANCE_TAG, SI_UGLY);
    SI_INIT_FUNCTION(result,
		     (variadicp ? SI_VARIADIC_FLAG : 0) |
		     (nreq < npos ? SI_OPTIONAL_FLAG : 0) ,
		     nreq, npos);
    SI_SET_WRAPPER(result, SI_WRAPPER_function);
    SI_SET_STANDARD_OBJECT_SLOT_VECTOR(result, Function_slot_vector, 0);
    SI_FUNCTION_ENTRY(result) = entry;
    SI_FUNCTION_ENV(result) = env;
    RESTORE_STACK();

    return result;
}

Object STATIC_FUNCTION1 (entry, env, variadicp, nreq, npos)
    Object (*entry)(), env;
    long variadicp, nreq, npos;
{
    Object result;
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = MAKE_FUNCTION(entry, env, variadicp, nreq, npos);
    RESTORE_CURRENT_AREA(a);
    return result;
}


Object STATIC_CONS (o1, o2)
    Object o1, o2;
{
    Object result;
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = cons(o1, o2);
    RESTORE_CURRENT_AREA(a);
    return result;
}


Object STATIC_STRING (s)
    char *s;
{
    Object result;
    Declare_area(a);
    SI_Dimension len;

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    len = strlen(s);
    result = SI_alloc_primitive_vector(len, A_STRING_CHAR);
    MEMCPY(&SI_ISCHAR(result, 0), s, (int)len);
    RESTORE_CURRENT_AREA(a);
    return result;
}


