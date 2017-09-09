/*
 * load_run.c -  Chestnut Run-Time Library entry for function load_run
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object Default_pathname_defaults;
extern Object Kerror;
extern Object Kinput;
DECLARE_VARIABLE(Load_pathname);
DECLARE_VARIABLE(Load_print);
DECLARE_VARIABLE(Load_truename);
DECLARE_VARIABLE(Load_verbose);
DECLARE_VARIABLE(Package);
extern Object Qstring_char;
extern TLS SI_Catch_frame *SI_Catch_stack;
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern TLS SI_Special_frame *SI_Special_stack;
DECLARE_VARIABLE(Standard_output);

#if SI_USE_PROTOTYPES

extern long SI_re_throw(void);
extern Object eval_run(Object);
extern Object format(long n, Object destination, char *control_string, ...);
extern Object lclose(Object stream, Object abort);
extern Object lopen(Object filename, Object direction, Object element_type, Object if_exists, Object if_does_not_exist);
extern Object lread(Object,Object,Object,Object);
extern Object merge_pathnames(Object,Object,Object);
extern Object print(Object,Object);
extern Object truename(Object);

#else

extern int SI_re_throw();
extern Object eval_run();
extern Object format();
extern Object lclose();
extern Object lopen();
extern Object lread();
extern Object merge_pathnames();
extern Object print();
extern Object truename();

#endif


#include "filesys.h"

Object load_run (filename, verbose, printarg, if_does_not_exist)
  Object filename, verbose, printarg, if_does_not_exist;
{
    Declare_local_temp;
  Declare_stack_pointer;
  Declare_catch(1);
  Declare_special(3);
  Object truefile, stream, sexpr;

  SAVE_STACK();
  PROTECT_4(filename, verbose, printarg, if_does_not_exist);
  PROTECTI_3(truefile,stream,sexpr);
  filename = merge_pathnames(filename, Default_pathname_defaults, KOPT);
  if (UNSUPPLIED_P(verbose)) verbose = Load_verbose;
  if (UNSUPPLIED_P(printarg)) printarg = Load_print;
  if (UNSUPPLIED_P(if_does_not_exist)) if_does_not_exist = Kerror;

  stream = NIL;
  if (PUSH_UNWIND_PROTECT(0)) {
    stream = lopen(filename, Kinput, Qstring_char, KOPT, if_does_not_exist);
    if (TRUEP(stream)) {
      truefile = truename(stream);
      if (TRUEP(verbose))
	(void)format(3, Standard_output, "~%; Loading ~s...", truefile);
      PUSH_SPECIAL(Package, Package, 0);
	PUSH_SPECIAL(Load_pathname, filename, 1);
	  PUSH_SPECIAL(Load_truename, truefile, 2);
	    for ( ;; ) {
	      sexpr = lread(stream, NIL, SI_EOF_TOKEN, NIL);
	      if (sexpr == SI_EOF_TOKEN) break;
	      sexpr = eval_run(sexpr);
	      if (TRUEP(printarg)) (void)print(sexpr, NIL);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    }
  }
  POP_UNWIND_PROTECT(0);
  if (TRUEP(stream)) lclose(stream,_);
  CONTINUE_UNWINDING(0);
  RESTORE_STACK();
  return VALUES_1(TRUEP(stream) ? T : NIL);
}
