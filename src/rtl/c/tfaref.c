/*
 * tfaref.c -  Chestnut Run-Time Library entry for function typed_foreign_aref
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qarray_foreign_type;
extern Object Qforeign_type;
extern Object Qpointer_foreign_type;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (int n, char *lstr, ...);
extern Object SI_make_rest_arg(Object *args, int n);
extern Object get_foreign_type(Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_make_rest_arg();
extern Object get_foreign_type();

#endif



Object typed_foreign_aref varargs_1(int, n)
{
    Object foreign_type, foreign_pointer;
    Object indices = UNBOUND, type, atype, dims_tail;
    long ndims=0, dims[8], inds[8], position, d, ds, dinc, dlast, ind, dim;
    long bounds_error_p = FALSE;
    Declare_varargs_without_temp;
    Declare_stack_pointer;

    SAVE_STACK();
    INIT_ARGS();
    foreign_type = REQUIRED_ARG();
    foreign_pointer = REQUIRED_ARG();
    SAVE_ARGS();
    indices = REST_ARG();
    PROTECT_3(foreign_type,foreign_pointer,indices);
    foreign_type = FOREIGN_TYPE(foreign_type);
    if(!(FOREIGN_POINTER_TYPE_P(foreign_pointer) &&
	 POINTER_FOREIGN_TYPE_P(type =
				FOREIGN_POINTER_TYPE(foreign_pointer)) &&
	 ARRAY_FOREIGN_TYPE_P(atype =
			      POINTER_FOREIGN_TYPE_TO_TYPE(type))))
      error(1,"Illegal call to foreign_aref");
    dims_tail = ARRAY_FOREIGN_TYPE_DIMENSIONS(atype);
    while (CONSP(dims_tail)) {
      if(!CONSP(indices))
	error(1,"foreign_aref: incorrect number of indices supplied");
      inds[ndims] = ind = IFIX(M_CAR(indices));
      dims[ndims] = dim = IFIX(M_CAR(dims_tail));
      if ( (ind < 0) || (ind >= dim))
	error(4,"typed_foreign_aref: Bounds error: dim# ~D, index ~D, dim ~D",
	      FIX(ndims),FIX(ind),FIX(dim));
      ndims++;
      indices = M_CDR(indices);
      dims_tail = M_CDR(dims_tail);
    }
    if (ndims == 1)
      position = inds[0];
    else if (ndims==0)
      position = 0;
    else {
      if(ARRAY_FOREIGN_TYPE_ROW_MAJOR_P(atype))
	{ dinc= -1L; d=ndims-1; dlast=0; }
      else
	{ dinc=  1; d=0; dlast=ndims-1; }
      position = inds[d];
      ds = dims[d];
      d += dinc;
      position += inds[d]*ds;
      for(; d==dlast;) {
	ds *= dims[d];
	d += dinc;
	position += inds[d]*ds;
      }
    }
    type = ARRAY_FOREIGN_TYPE_ETYPE(atype);
    if(foreign_type != type)
      error(1,"typed_foreign_aref: not of required type");
    RESTORE_STACK();
    return 
      (*FOREIGN_TYPE_READER(type))
	(type,
	 ((char *)FOREIGN_POINTER_ADDRESS(foreign_pointer)+
	  position*FOREIGN_TYPE_SIZE(type)));
}
