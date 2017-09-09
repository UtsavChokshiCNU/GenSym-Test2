#ifndef SI_SVARARGS_H
#define SI_SVARARGS_H

#if  !defined(SI_HAVE_STDARGS)

#include <varargs.h>
#define SI_va_start(ap, pn) va_start(ap)

#define varargs_arglist_1(type1,var1) \
        (var1, va_alist)
#define varargs_arglist_2(type1,var1,type2,var2) \
        (var1, var2, va_alist)
#define varargs_arglist_3(type1,var1,type2,var2,type3,var3) \
        (var1, var2, var3, va_alist)

#define varargs_declarations_1(type1,var1) \
    type1 var1; \
    va_dcl
#define varargs_declarations_2(type1,var1,type2,var2) \
    type1 var1; \
    type2 var2; \
    va_dcl
#define varargs_declarations_3(type1,var1,type2,var2,type3,var3) \
    type1 var1; \
    type2 var2; \
    type3 var3; \
    va_dcl

#else

#include <stdarg.h>

#define va_alist	...
/*#define va_dcl*/

#define SI_va_start(ap, pn) va_start(ap, pn)

#define varargs_arglist_1(type1,var1) \
        (type1 var1, va_alist)
#define varargs_arglist_2(type1,var1,type2,var2) \
        (type1 var1, type2 var2, va_alist)
#define varargs_arglist_3(type1,var1,type2,var2,type3,var3) \
        (type1 var1, type2 var2, type3 var3, va_alist)

#define varargs_declarations_1(type1,var1)
#define varargs_declarations_2(type1,var1,type2,var2)
#define varargs_declarations_3(type1,var1,type2,var2,type3,var3)

#endif

/* These macros are split in two, because the translator might need to
   generate the two parts separately, for froeign functions having
   complicated return types. */

#define varargs_1(type1,var1) \
   varargs_arglist_1(type1,var1) \
   varargs_declarations_1(type1,var1)
#define varargs_2(type1,var1,type2,var2) \
   varargs_arglist_2(type1,var1,type2,var2) \
   varargs_declarations_2(type1,var1,type2,var2)
#define varargs_3(type1,var1,type2,var2,type3,var3) \
   varargs_arglist_3(type1,var1,type2,var2,type3,var3) \
   varargs_declarations_3(type1,var1,type2,var2,type3,var3)

#endif /* SI_SVARARGS_H */
