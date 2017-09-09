
#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object cdouble_to_double(double a);
extern double object_to_cdouble(Object n);

#else

extern Object cdouble_to_double();
extern double object_to_cdouble();

#endif

/* &optional 1 1 */
/*ARGSUSED*/
Object lfloat(x, y)
    Object x, y; 
{
    Declare_local_temp;
    Object result;

    /* ASSUME ONLY ONE KIND OF FLOAT */
    if (DOUBLEP(x))
	result = x;
    else
	result = cdouble_to_double(object_to_cdouble(x));

    return VALUES_1(result);
}

