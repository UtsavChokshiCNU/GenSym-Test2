/*
 * pathname.c -  Chestnut Run-Time Library entry for function pathname
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object T_temp;

#if SI_USE_PROTOTYPES

extern void SI_INIT_streams(void);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object string(Object);

#else

extern void SI_INIT_streams();
extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object string();

#endif


#include "filesys.h"
#include "strminit.h"

FORWARD_STATIC Object chase_file_stream();

/* pathname is composed six parts:
 *    host, device, directory, name, type, version
 *    PATHNAME_PATH(pathname) -> string containing all but the host
 *    PATHNAME_HOST(pathname) -> host information
 *
 * A 'pathnm' or 'defaults' argument may actually be a pathname,
 * a string or symbol, or a stream.
 */


Object pathname (pathnm)
    Object pathnm;
{
    Declare_local_temp;
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(pathnm);
    PROTECTI_1(result);
    if (PATHNAMEP(pathnm))
	result = pathnm;
    else {
	if (STREAMP(pathnm)) {
	    pathnm = chase_file_stream(pathnm);
	    pathnm = FILE_STREAM_NAME(pathnm);
	}
	result =
	    SI_ALLOC(SI_Pathname, PATHNAME_TYPE, SI_INSTANCE_TAG, SI_NORMAL);
	SI_SET_WRAPPER(result, SI_WRAPPER_pathname);
	PATHNAME_PATH(result) = STRING(pathnm);
	PATHNAME_HOST(result) = NIL;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}

Object truename (pathnm)
    Object pathnm;
{
    Declare_local_temp;
    if (STREAMP(pathnm))
	return T_VALUES_1(FILE_STREAM_NAME(chase_file_stream(pathnm)));
    if (PATHNAMEP(pathnm))
	return VALUES_1(PATHNAME_PATH(pathnm));
    return VALUES_1(STRING(pathnm));
}

static Object chase_file_stream(stream)
    Object stream;
{
    Declare_local_temp;

    INIT_STREAMS();
    while(1) {
	switch(STREAM_STYPE(stream)) {
	case SYNONYM_STREAM:
	    stream = STREAM_OBJ(stream);
	    break;
	case FILE_STREAM:
	    return VALUES_1(stream);
	default:
	    error(2, "chase_file_stream: expected file stream - ~s", stream);
	    break;
	}
    }
}
