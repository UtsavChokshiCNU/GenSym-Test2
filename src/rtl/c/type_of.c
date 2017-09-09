/*
 * type_of.c -  Chestnut Run-Time Library entry for function type_of
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qarray;
extern Object Qbignum;
extern Object Qbit_vector;
extern Object Qcharacter;
extern Object Qcobject;
extern Object Qcomplex;
extern Object Qcons;
extern Object Qdouble_float;
extern Object Qfixnum;
extern Object Qforeign_pointer;
extern Object Qfunction;
extern Object Qhash_table;
extern Object Qnull;
extern Object Qpackage_type;
extern Object Qpathname;
extern Object Qrandom_state_type;
extern Object Qratio;
extern Object Qreadtable_type;
extern Object Qsimple_bit_vector;
extern Object Qsimple_string;
extern Object Qsimple_vector;
extern Object Qstream;
extern Object Qstring;
extern Object Qsymbol;
extern Object Qvector;
extern Object Qsigned_byte;

#if SI_SUPPORT_CLOS

#define class_name(a0) \
    GENERIC_FUNCTION_CALL_1(Fclass_name,a0)
extern TLS Object SI_Called_function;
#define Fclass_name SYMBOL_FUNCTION(Qclass_name)
extern Object SI_symbol_field();
extern Object Qclass_name;
extern SI_Primitive_vector_constant SI_Stack_vector_header;

#if SI_USE_PROTOTYPES
extern Object class_of(Object);
#else
extern Object class_of();
#endif

#endif

/* Return symbol for an object's type. */
Object type_of (a)
    Object a;
{
    Declare_local_temp;
    Declare_protect(1);
    Object return_type;
#if SI_SUPPORT_CLOS
	Object class;
#endif
    long simplep;

    PROTECT_LOCALS();
    PROTECTI_1(class);

/*START_TYPEOF:*/
    if (SI_IMMEDIATEP(a)) {
	if (a == NIL)
	    return_type = Qnull;
	else if (FIXNUMP(a))
	    return_type = Qfixnum;
	else if (CHARACTERP(a))
	    return_type = Qcharacter;
	else
	    return_type = Qt;
    }
    else if (ARRAYP(a)) {
	simplep = SIMPLE_ARRAY_P(a);
	if (!VECTORP(a))
	    return_type = Qarray;
	else switch (SI_ARRAY_ETYPE(a)) {
	case A_STRING_CHAR:
	    if (simplep)
		return_type = Qsimple_string;
	    else
		return_type = Qstring;
	    break;
	case A_BIT:
	    if (simplep)
		return_type = Qsimple_bit_vector;
	    else
		return_type = Qbit_vector;
	    break;
	case A_T:
	    if (simplep)
		return_type = Qsimple_vector;
	    else
		return_type = Qvector;
	    break;
	default:
	    /* Lucid: (VECTOR etype (dimensions)) */
	    return_type = Qvector;
	}
    } else
	switch (SI_STORED_OBJECT_TYPE(a)) {
	case SYMBOL_TYPE:
	case USYMBOL_TYPE:
	case MSYMBOL_TYPE:
	case ESYMBOL_TYPE:
	case EMSYMBOL_TYPE:
	case KEYWORD_TYPE:
	case MKEYWORD_TYPE:
	    return_type = Qsymbol;
	    break;
	case INDIRECT_TYPE:
	case EINDIRECT_TYPE:
	    /*** These things don't print as symbols, anyway. ***/
	    /* a = SYMBOL_PLIST(a); */
	    /* goto START_TYPEOF;   */
	    return_type = Qt; /* type unknown */
	    break;
	case OBIGNUM_TYPE:
	case XBIGNUM_TYPE:
	    return_type = Qbignum;
	    break;
        case LONG64_TYPE:
            return_type = LIST_2(Qsigned_byte, FIX(64));
            break;
	case DOUBLE_TYPE:
	    return_type = Qdouble_float; /* Don't mimic Lucid */
	    break;
	case CONS_TYPE:
	    return_type = Qcons;
	    break;
	case RATIO_TYPE:
	    return_type = Qratio;
	    break;
	case COMPLEX_TYPE:
	    return_type = Qcomplex;
	    break;

#if SI_SUPPORT_CLOS
        default:
	    if (SI_INSTANCEP(a)) {
	      class = class_of(a);
	      return_type = class_name(class);
	      if (return_type == NIL) return_type = class;
	    }
	    else
	      return_type = Qt; /* type unknown */
	    break;
#else
	case SI_FUNCTION_TYPE:
	    return_type = Qfunction; /* Lucid: SYSTEM:PROCEDURE */
	    break;
	case COBJECT_TYPE:
	    return_type = ARRAYP(a) ? Qcobject : Qforeign_pointer;
	    break;
	case SI_STRUCTURE_TYPE:
	    return_type = SI_STRUCTURE_NAME(a);
	    break;
	case PACKAGE_TYPE:
	    return_type = Qpackage_type;
	    break;
	case HASH_TABLE_TYPE:
	    return_type = Qhash_table;
	    break;
	case STREAM_TYPE:
	    /* You may want to sub-divide into types of streams */
	    return_type = Qstream;
	    break;
	case RANDOM_STATE_TYPE:
	    return_type = Qrandom_state_type;
	    break;
	case READTABLE_TYPE:
	    return_type = Qreadtable_type;
	    break;
	case PATHNAME_TYPE:
	    return_type = Qpathname;
	    break;
	    /*
	      case WINDOW_TYPE:
	      return_type = Qwindow;
	      break;
	      */
	default:
	    return_type = Qt; /* type unknown */
	    break;
#endif /* SI_SUPPORT_CLOS */
	}
    UNPROTECT_LOCALS();
    return VALUES_1(return_type);
}
