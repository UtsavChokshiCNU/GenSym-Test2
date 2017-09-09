/*
 * sntmisc.c -  Chestnut Run-Time Library entry for function SI_INIT_misc
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kchestnut;
extern Object Kchestnut_3;
extern Object Kx86;
extern Object Kx86_64;
extern Object Long_site_name_string;
extern Object Short_site_name_string;

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object STATIC_CONS(Object o1, Object o2);
extern Object STATIC_STRING(char *s);

#else

extern void SI_add_external_root();
extern Object STATIC_CONS();
extern Object STATIC_STRING();

#endif



#define IINTERNAL_TIME_UNITS_PER_SECOND 1000L

Object Internal_time_units_per_second = FIX(IINTERNAL_TIME_UNITS_PER_SECOND);


Object Features = UNBOUND;	/* initialized by SI_INIT_misc() */

void SI_INIT_misc()
{
  PROTECT_GLOBAL(Features);
  Features = STATIC_CONS(Kchestnut, STATIC_CONS(Kchestnut_3, NIL));

#if defined(Platform_64bit)
  /* Push :x86-64 for runtime architecture detecting */
  Features = STATIC_CONS(Kx86_64, Features);
#else
  Features = STATIC_CONS(Kx86, Features);
#endif

  PROTECT_GLOBAL(Short_site_name_string);
  if (Short_site_name_string == UNBOUND)
    Short_site_name_string = STATIC_STRING("unknown");

  PROTECT_GLOBAL(Short_site_name_string);
  if (Long_site_name_string == UNBOUND)
    Long_site_name_string = STATIC_STRING("unknown");
}
