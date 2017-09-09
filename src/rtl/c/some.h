/*
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

/* common function for some, every, notany, notevery */
#define SOME_FUNC     0
#define EVERY_FUNC    1
#define  INVOKE_SEVERAL(f,p,n)     \
    va_list  ap;                   \
    Object result;                 \
    SI_va_start(ap,n);                  \
    result = several(f,n,ap);   \
    if (!p) result = (result == NIL) ? T : NIL; \
    va_end(ap);                    \
    return result 

static Object several (flag, n, ap)
    long flag, n;
    va_list ap;
{
    Declare_local_temp;
    long iterate, length;
    long i, j, arity;
    Object result, temp;
    Object function;
    Stack_item *temp_ptr;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECTI_2(function,result);
 
    result = (flag == SOME_FUNC) ? NIL : T;
    function = va_arg(ap, Object);
    arity = n - 1;
    /* spread the sequences onto the stack, find the 
       length of the shortest  one  and arity of function call */
    for (i = 1, temp_ptr = Stack,
	 iterate = ilength((STACK_PUSH(va_arg(ap,Object)), STACK_REF(-1)));
	 i < arity ; i++) 
	if ((length = ilength((STACK_PUSH(va_arg(ap,Object)), STACK_REF(-1)))) < iterate)
	    iterate = length;
    
    /* iterate the function application with corresponding arrguments */
    for (i = 0; i < iterate; i++) {

	/* push arguments onto the stack */
	for (j = 0; j < arity; j++) {
	    temp = temp_ptr[j].object;
 	    if (ARRAYP(temp)) 
		STACK_PUSH(do_aref_1(temp,i));
	    else {
		temp_ptr[j].object = M_CDR(temp);
		STACK_PUSH(M_CAR(temp));
	    }
	}
	result = internal_funcall(function, arity, NIL);

	if ((flag == SOME_FUNC && result != NIL) ||
            (flag == EVERY_FUNC && result == NIL)) break;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
