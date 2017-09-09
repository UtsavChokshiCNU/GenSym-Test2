/*
 * mapcar.c - LISPTOC map functions
 * Copyright (c) 1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);
extern Object cons(Object,Object);

#else

extern Object SI_internal_funcall();
extern Object cons();

#endif




/* internal common mapping function */

enum op {
    MAPCAR,
    MAPLIST,
    MAPC,
    MAPL,
    MAPCAN,
    MAPCON
};

#define  INVOKE_MAP(f,n)     \
    va_list  ap;             \
    Object result;           \
    SI_va_start(ap,n);            \
    result = SI_do_map(f,n,ap); \
    va_end(ap);              \
    return result 

static Object SI_do_map(flag, n, ap)
    enum op flag;
    long n;
    va_list ap;
{
    Declare_local_temp;
    Declare_stack_pointer;
    Stack_item *temp_ptr;
    Object result, func, last, temp;
    long i, j;

    SAVE_STACK();
    /* note: last only for relocating GC,
             temp only because C computes l-val befor r-val */
    PROTECTI_4(func,result,last,temp);
 
    for (temp_ptr = Stack,
	 func = va_arg(ap, Object),
	 i = 0, --n;
	 i < n ; i++) 
	STACK_PUSH(va_arg(ap, Object));

    result = ( flag == MAPC || flag == MAPL) ? *(Object*)temp_ptr : NIL;
    /* iterate the function application with corresponding arrguments */
    while (TRUE) {

	/* push arguments onto the stack */
	for (j = 0; j < n; j++) {
	    
	    if ((temp = temp_ptr[j].object) == NIL) {
		RESTORE_STACK();
		return VALUES_1(result);
	    }
	    else {
		temp_ptr[j].object = M_CDR(temp);
		switch (flag) {
		case MAPCAR:
		case MAPCAN:
		case MAPC:
		    STACK_PUSH(M_CAR(temp));
		    break;
		default:
		    STACK_PUSH(temp);
		}
	    }
	}
	switch (flag) {
	case MAPCAR:
	case MAPLIST:
	    if (result == NIL)
		result = last = cons(NIL,NIL);
	    else {
		temp = cons(NIL,NIL);
		RPLACD(last,temp);
		last = M_CDR(last);
	    }
	    temp = internal_funcall (func,n,NIL);
	    RPLACA(last,temp);
	    break;
	case MAPCAN:
	case MAPCON:
	    if (result == NIL)
		result = last = internal_funcall (func,n,NIL);
	    else { /* must be a list */
		temp = internal_funcall (func,n,NIL);
		RPLACD(last, temp);
	    }
	    if (CONSP(last))
		while (M_CDR(last) != NIL) last = M_CDR(last);
	    break;
	default:
	    internal_funcall (func,n,NIL);
	}
    }
}

Object mapcar varargs_1(int, n)
{
    INVOKE_MAP(MAPCAR,n);
}

Object maplist varargs_1(int, n)
{
    INVOKE_MAP(MAPLIST,n);
}


Object mapc varargs_1(int, n)
{
    INVOKE_MAP(MAPC,n);
}


Object mapl varargs_1(int, n)
{
    INVOKE_MAP(MAPL,n);
}


Object mapcan varargs_1(int, n)
{
    INVOKE_MAP(MAPCAN,n);
}


Object mapcon varargs_1(int, n)
{
    INVOKE_MAP(MAPCON,n);
}
