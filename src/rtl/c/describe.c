/*
 * describe.c -  Chestnut Run-Time Library entry for function describe
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

DECLARE_VARIABLE(Standard_output);

#if SI_USE_PROTOTYPES

extern Object array_total_size(Object);
extern Object elt(Object,Object);
extern Object format(long n, Object destination, char *control_string, ...);
extern Object print(Object,Object);
extern Object symbol_plist(Object);
extern Object symbol_value(Object);
extern Object type_of(Object);

#else

extern Object array_total_size();
extern Object elt();
extern Object format();
extern Object print();
extern Object symbol_plist();
extern Object symbol_value();
extern Object type_of();

#endif




Object describe (object)
    Object object;
{
    Declare_local_temp;
    long i, nelems;
    Object bucket;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(object);
    PROTECTI_1(bucket);
    print(object, Standard_output);
    if (SYMBOLP(object)) {
	format(3, Standard_output, "~%Value=~s~%", symbol_value(object));
	format(3, Standard_output, "~%Property list=~s~%", symbol_plist(object));
    }
    else if (VECTORP(object)) {
	nelems = FIXNUM_TO_INT(array_total_size(object));
	for (i = 0; i < nelems; i++) {
	    format(4, Standard_output, "~%[~d]=~s", i, elt(object, FIX(i)));
	}
        format(2, Standard_output, "~%");
    }
    else if (HASH_TABLE_P(object)) {
	for (i = 0; i < HASH_SIZE(object); i++) {
	    bucket = SVREF(HASH_ARRAY(object), FIX(i));
	    if (bucket != NIL) {
		format(4, Standard_output, "  Bucket #~s = ~s~%",
		       FIX(i), bucket);
	    }
	}
    }
    else
	format(3, Standard_output, "  Type = ~s~%", type_of(object));
    RESTORE_STACK();
    return VALUES_0();
}
