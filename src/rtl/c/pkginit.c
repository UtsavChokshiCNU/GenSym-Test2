/*
 * pkginit.c - global variables and initializer for the Package  system
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);

#else

extern void SI_add_external_root();

#endif




DEFINE_VARIABLE(Package);
Object Modules = UNBOUND;
Object List_of_packages = UNBOUND;	/* initialized in initsyms.c */
Object SI_Initial_packages = UNBOUND;

void SI_INIT_packages_1()
{
  PROTECT_GLOBAL(Package);
  if (Package == UNBOUND) Package = NIL;

  PROTECT_GLOBAL(Modules);
  Modules = NIL;

  PROTECT_GLOBAL(List_of_packages);
  if (List_of_packages == UNBOUND) List_of_packages = NIL;

  /* SI_Initial_packages is treated specially by GC, so doesn't need explicit
   * protection here.  A total crock, but until package structure and setup is
   * reimplimented we're sort of stuck with it.  The problem is that the
   * initial packages are allocated with static initializers, so are neither in
   * static nor dynamic space. */
}


