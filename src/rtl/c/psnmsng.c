/*
 * psnmsng.c -  Chestnut Run-Time Library entry for function parse_namestring
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Default_pathname_defaults;

#if SI_USE_PROTOTYPES

extern Object pathname(Object);
extern Object string(Object);
extern Object subseq(Object,Object,Object);

#else

extern Object pathname();
extern Object string();
extern Object subseq();

#endif


#include "filesys.h"
Object parse_namestring (thing, host, defaults, start, end, junk_allowed)
    Object thing, host, defaults, start, end, junk_allowed;
{
    Declare_local_temp;
    Object prev_defaults = Default_pathname_defaults, result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_7(thing,host,defaults,start,end,junk_allowed,prev_defaults);
    PROTECTI_1(result);
    if (SUPPLIED_P(defaults))
	Default_pathname_defaults = defaults;
    if (SYMBOLP(thing))
	thing = STRING(thing);	/* This feature discontinued by X3J13 */
    if (STRINGP(thing) && (start != NIL || end != NIL))
	thing = subseq(thing, start, end);
    result = pathname(thing);
    Default_pathname_defaults = prev_defaults;
    RESTORE_STACK();
    return VALUES_1(result);
}
