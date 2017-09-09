/*
 * Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
 */

#include "runtime.h"

extern Object Qblock;
extern Object Qcatch;
extern Object Qeval_when;
extern Object Qflet;
extern Object Qfunction;
extern Object Qgo;
extern Object Qif;
extern Object Qlabels;
extern Object Qlet;
extern Object Qlet_star;
extern Object Qload_time_value;
extern Object Qlocally;
extern Object Qmacrolet;
extern Object Qmultiple_value_call;
extern Object Qmultiple_value_prog1;
extern Object Qprogn;
extern Object Qprogv;
extern Object Qquote;
extern Object Qreturn_from;
extern Object Qsetq;
extern Object Qsymbol_macrolet;
extern Object Qtagbody;
extern Object Qthe;
extern Object Qthrow;
extern Object Qunwind_protect;

extern TLS SI_Area *Current_area;
extern Object Pcl;
extern Object Qand;
extern Object Qcond;
extern Object Qdeclare;
extern Object Qdefun;
extern Object Qdefvar;
extern Object Qdo;
extern Object Qincf;
extern Object Qlambda;
extern Object Qor;
extern Object Qunless;
extern Object Qwhen;
extern TLS Object SI_Called_function;
extern TLS SI_Catch_frame *SI_Catch_stack;
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern TLS SI_Special_frame *SI_Special_stack;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;
extern TLS Object T_temp;

#if SI_USE_PROTOTYPES

extern Object MAKE_FUNCTION(Object (*entry)(), Object env, long variadicp, long nreq, long npos);
extern Object (*SI_cerror_fptr)(long n, char *cstr,char *estr, ...);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);
extern void SI_progv_do_bindings(Object vals);
extern void SI_progv_restore_bindings(Stack_item *sp);
extern void SI_progv_save_bindings(Object syms);
extern long SI_re_throw(void);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object SI_throw(Object tag, Object firstval);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object add1(Object);
extern Object add(Object a, Object b);
extern Object apply1(Object func, Object arglist);
extern Object cons(Object,Object);
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall(Object original_function, int args_on_stack, Object arglist);
#else
extern Object funcall0(Object func);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
#endif
extern Object funcall(long,...);
extern Object length(Object);
extern Object macro_function(Object,Object);
extern Object mapcar(long,...);
extern Object set_symbol_function(Object,Object);
extern Object set(Object,Object);
extern Object symbol_value(Object);
extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);

#else

extern Object MAKE_FUNCTION();
extern Object (*SI_cerror_fptr)();
extern Object (*SI_error_fptr) ();
extern Object SI_internal_funcall();
extern void SI_progv_do_bindings();
extern void SI_progv_restore_bindings();
extern void SI_progv_save_bindings();
extern int SI_re_throw();
extern Object SI_symbol_field();
extern Object SI_throw();
extern Object (*SI_warn_fptr) ();
extern Object STATIC_FUNCTION1();
extern Object add1();
extern Object add();
extern Object apply1();
extern Object cons();
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall();
#else
extern Object funcall0();
extern Object funcall1();
extern Object funcall2();
#endif
extern Object funcall();
extern Object length();
extern Object macro_function();
extern Object mapcar();
extern Object set_symbol_function();
extern Object set();
extern Object symbol_value();
extern Object SI_set_symbol_field();

#endif


#include "evalrun.h"

/*
 * do not retranslate it.  File was hand-modified. (D.N. apr. 92)
 */


extern Object NEW_SYMBOL(); 
extern Object SI_set_symbol_value_helper();
static long initialized_p;

#define SUPPORT_CATCH

static Object eval_progn();

static void define_special_operator(symbol_ptr,name,code)
  Object *symbol_ptr;
  char *name;
  long code;
{
  *symbol_ptr = NEW_SYMBOL(Pcl, name, TRUE);
  SET_SYMBOL_FUNCTION(*symbol_ptr,
                      cons(SI_SPECIAL_OPERATOR_TOKEN, FIX(code)));
}

#define DEFINE_SPECIAL_OPERATOR(symbol,name,code) \
  define_special_operator(&symbol,name,(long)code)

void SI_initialize_special_operators()
{
  Declare_area(a);

  SAVE_CURRENT_AREA(a);
  SET_CURRENT_AREA(Static_area);
    
  DEFINE_SPECIAL_OPERATOR(Qblock, "BLOCK",
			  SI_SPECIAL_OP_BLOCK);
  DEFINE_SPECIAL_OPERATOR(Qcatch, "CATCH",
			  SI_SPECIAL_OP_CATCH);
  DEFINE_SPECIAL_OPERATOR(Qeval_when, "EVAL-WHEN",
			  SI_SPECIAL_OP_EVAL_WHEN);
  DEFINE_SPECIAL_OPERATOR(Qflet, "FLET",
			  SI_SPECIAL_OP_FLET);
  DEFINE_SPECIAL_OPERATOR(Qfunction, "FUNCTION",
			  SI_SPECIAL_OP_FUNCTION);
  DEFINE_SPECIAL_OPERATOR(Qgo, "GO",
			  SI_SPECIAL_OP_GO);
  DEFINE_SPECIAL_OPERATOR(Qif, "IF",
			  SI_SPECIAL_OP_IF);
  DEFINE_SPECIAL_OPERATOR(Qlabels, "LABELS",
			  SI_SPECIAL_OP_LABELS);
  DEFINE_SPECIAL_OPERATOR(Qlet, "LET",
			  SI_SPECIAL_OP_LET);
  DEFINE_SPECIAL_OPERATOR(Qlet_star, "LET*",
			  SI_SPECIAL_OP_LET_STAR);
  DEFINE_SPECIAL_OPERATOR(Qload_time_value, "LOAD-TIME-VALUE",
			  SI_SPECIAL_OP_LOAD_TIME_VALUE);
  DEFINE_SPECIAL_OPERATOR(Qlocally, "LOCALLY",
			  SI_SPECIAL_OP_LOCALLY);
  DEFINE_SPECIAL_OPERATOR(Qmacrolet, "MACROLET",
			  SI_SPECIAL_OP_MACROLET);
  DEFINE_SPECIAL_OPERATOR(Qmultiple_value_call, "MULTIPLE-VALUE-CALL",
			  SI_SPECIAL_OP_MULTIPLE_VALUE_CALL);
  DEFINE_SPECIAL_OPERATOR(Qmultiple_value_prog1, "MULTIPLE-VALUE-PROG1",
			  SI_SPECIAL_OP_MULTIPLE_VALUE_PROG1);
  DEFINE_SPECIAL_OPERATOR(Qprogn, "PROGN",
			  SI_SPECIAL_OP_PROGN);
  DEFINE_SPECIAL_OPERATOR(Qprogv, "PROGV",
			  SI_SPECIAL_OP_PROGV);
  DEFINE_SPECIAL_OPERATOR(Qquote, "QUOTE",
			  SI_SPECIAL_OP_QUOTE);
  DEFINE_SPECIAL_OPERATOR(Qreturn_from, "RETURN-FROM",
			  SI_SPECIAL_OP_RETURN_FROM);
  DEFINE_SPECIAL_OPERATOR(Qsetq, "SETQ",
			  SI_SPECIAL_OP_SETQ);
  DEFINE_SPECIAL_OPERATOR(Qsymbol_macrolet, "SYMBOL-MACROLET",
			  SI_SPECIAL_OP_SYMBOL_MACROLET);
  DEFINE_SPECIAL_OPERATOR(Qtagbody, "TAGBODY",
			  SI_SPECIAL_OP_TAGBODY);
  DEFINE_SPECIAL_OPERATOR(Qthe, "THE",
			  SI_SPECIAL_OP_THE);
  DEFINE_SPECIAL_OPERATOR(Qthrow, "THROW",
			  SI_SPECIAL_OP_THROW);
  DEFINE_SPECIAL_OPERATOR(Qunwind_protect, "UNWIND-PROTECT",
			  SI_SPECIAL_OP_UNWIND_PROTECT);

  RESTORE_CURRENT_AREA(a);
    
}

/* lazily invoking GC-safe initializer */
static void SI_INIT_evalrun() 
{
  Declare_area(a);

  SAVE_CURRENT_AREA(a);
  SET_CURRENT_AREA(Static_area);
    
  SI_initialize_special_operators();

  Qand = NEW_SYMBOL(Pcl, "AND", TRUE);
  Qcond = NEW_SYMBOL(Pcl, "COND", TRUE);
  Qdeclare = NEW_SYMBOL(Pcl, "DECLARE", TRUE);
  Qdefun = NEW_SYMBOL(Pcl, "DEFUN", TRUE);
  Qdefvar = NEW_SYMBOL(Pcl, "DEFVAR", TRUE);
  Qdo = NEW_SYMBOL(Pcl, "DO", TRUE);
  Qif = NEW_SYMBOL(Pcl, "IF", TRUE);
  Qincf = NEW_SYMBOL(Pcl, "INCF", TRUE);
  Qlambda = NEW_SYMBOL(Pcl, "LAMBDA", TRUE);
  Qor = NEW_SYMBOL(Pcl, "OR", TRUE);
  Qunless = NEW_SYMBOL(Pcl, "UNLESS", TRUE);
  Qwhen = NEW_SYMBOL(Pcl, "WHEN", TRUE);

  RESTORE_CURRENT_AREA(a);
    
}

/* apply_lambda is invoked by SI_internal_funcall
 *
 * Utilizes the state of the Lisp stack just before actual call:
 * all arguments are placed above actual Stack pointer.
 * it is safe because no GC or Stack changes could happen
 *
 * The whole evaluator could be implemented in terms of stack operations
 * without consing argument lists
 * This is a development time vs. runtime benefits tradeoff
 *
 */

Object apply_lambda varargs_1(int, n)
{   
    Declare_local_temp;
    Object temp1;
    Object syms;
    Stack_item *bottom;
    Catch_buf old_env_1;
    int ap, sp;

    ENSURE_STACK(2*n); 
    ap = 2*n; sp = n;
     
    /* spread values; reserve positions for symbols */
    for (;sp ; STACK_REF(--ap) = NIL)
	STACK_REF(--ap) = STACK_REF(--sp);
    /* expect right number of arguments (see "defun" branch in eval_run ) */
    syms = FORMARGS();
    for (bottom = Stack, Stack+=(2*n); ap < n && TRUEP(syms); ++ap,++sp) {
	temp1 = M_CAR(syms);

#       undef SELF_EVALUATING_SYMBOL_P
#       define SELF_EVALUATING_SYMBOL_P(sym) \
        (EQ(sym,NIL) || EQ(sym,T) || KEYWORDP(sym))
	if (SELF_EVALUATING_SYMBOL_P(temp1)) {
	    error(2, "evaluator: Invalid variable ~S.", temp1);
	    /*NOTREACHED*/
	}
#       undef SELF_EVALUATING_SYMBOL_P
#       define BOT_REF(n) (bottom[n].object)
	syms = M_CDR(syms);
	BOT_REF(sp) = temp1;
        temp1 = SI_symbol_field(temp1, SI_SymVal);
	(void)SI_set_symbol_value_helper(BOT_REF(sp), BOT_REF(sp+1));
	BOT_REF(++sp)	 = temp1; /* save old value */
    }
    if (TRUEP(syms)) cerror(2, "eval as is", "eval: not enough arguments");
    else if (ap < n) {
	warn(1, "eval: too many arguments");
	/* correct Stack value */
	Stack = bottom + sp;
    }
    STACK_PUSH(FIX(ap)); /* number of pairs */
    UNWIND_PROTECT(invisible_arg, old_env_1, LABEL1); 
      temp1 = eval_progn(FORMS());
    LABEL1: 
    END_PROGV(unwind_p, old_env_1);
    return(temp1);
}

/* Runtime evaluator */

Object eval_run(exp)
    Object exp;
{
    Declare_local_temp;
#ifdef SUPPORT_CATCH
    Declare_catch(1);
#endif
    Object fun;
    Object subform;
    Object l1_subform;
    Object unwind_p;
    Object var_init_step_list;
    Object test_result;
    Object test;
    Object result_forms;
    Object body;
    Object l1_unwind_p;
    Object var_init_step;
    Object fname;
    Object lambda_form;
    Object var;
    Object delta_p;
    Object delta;
    Object l1_fun;
    Object args;
    Object temp1;
    Object temp2;
    Object temp3;
    Object temp4;
    Object temp5;
    Object temp6;
    Object temp7;
    Object temp8;
    Object temp9;
    Object temp10;
    Object temp11;
    Object temp12;
    Object temp13;
    Object temp14;
    Object temp15;
    Object temp16;
    Object temp17;
    Object temp18;
    Object temp19;
    Object temp20;
    Object temp21;
    Object temp22;
    Object temp23;
    Object temp24;
    Object temp25;
    Object temp26;
    extern Object binding_variable();
    extern Object binding_initform();
    SI_Declare_static_constant(FP_BINDING_VARIABLE, d0,
		STATIC_FUNCTION(binding_variable, NIL, FALSE, 1, 1));
    SI_Declare_static_constant(FP_BINDING_INITFORM, d1,
		STATIC_FUNCTION(binding_initform, NIL, FALSE, 1, 1));
    SI_Declare_static_constant(FP_EVAL_RUN, d2,
		STATIC_FUNCTION(eval_run, NIL, FALSE, 1, 1));
    Catch_buf old_env_1;
    Catch_buf old_env_2;
    Declare_stack_pointer;

    INIT_EVALRUN(); /* GC safe */
    SAVE_STACK();
    PROTECT_1(exp);
    PROTECTI_10(fun,subform,l1_subform,unwind_p,var_init_step_list,
	    test_result,test,result_forms,body,l1_unwind_p);
    PROTECTI_10(var_init_step,fname,lambda_form,var,delta_p,delta,l1_fun,
	    args,temp1,temp2);
    PROTECTI_10(temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10,temp11,
	    temp12);
    PROTECTI_10(temp13,temp14,temp15,temp16,temp17,temp18,temp19,temp20,
	    temp21,temp22);
    PROTECTI_4(temp23,temp24,temp25,temp26);
    if (CONSP(exp)) {
	temp2 = CAR(exp);
	if (EQ(temp2,Qquote)) {
	    temp1 = T_VALUES_1(SECOND(exp));
	}
	else if (EQ(temp2,Qfunction)) {
	    fun = SECOND(exp);
	    temp1 = (SYMBOLP(fun) ? T_VALUES_1(SYMBOL_FUNCTION(fun)) : 
		    VALUES_1(fun));
	}
	else if (EQ(temp2,Qif)) {
	    temp1 = (TRUEP(eval_run(SECOND(exp))) ? eval_run(THIRD(exp)) : 
		    eval_run(FOURTH(exp)));
	}
	else if (EQ(temp2,Qwhen)) {
	    temp1 = (TRUEP(eval_run(SECOND(exp))) ? eval_progn(CDDR(exp)) : 
		    VALUES_1(NIL));
	}
	else if (EQ(temp2,Qunless)) {
	    temp1 = (!TRUEP(eval_run(SECOND(exp))) ? eval_progn(CDDR(exp)) : 
		    VALUES_1(NIL));
	}
	else if (EQ(temp2,Qcond)) {
	    for(temp3=CDR(exp);;temp3=CDR(temp3)) {
	      if(!TRUEP(temp3)) {
		temp1 = VALUES_1(NIL);
		break;
	      }
	      temp5=CAR(temp3);
	      if(TRUEP(temp4=eval_run(CAR(temp5))))
		if(TRUEP(CDR(temp5)))
		  temp1 = eval_progn(CDR(temp5));
		else 
		  temp1 = VALUES_1(temp4);
	      break;
	    }
	}
	else if (EQ(temp2,Qand)) {
	    exp = CDR(exp);
	    if (!exp) {
		temp1 = VALUES_1(T);
	    }
	    else {
		BEGIN_LOOP: 
		subform = CAR(exp);
		exp = CDR(exp);
		if (ENDP(exp)) {
		    temp1 = eval_run(subform);
		    goto LABEL1;
		}
		else if (!TRUEP(eval_run(subform))) {
		    temp1 = VALUES_1(NIL);
		    goto LABEL1;
		}
		goto BEGIN_LOOP;
		/*END_LOOP: */
		temp1 = VALUES_1(NIL);
		LABEL1: 
		;
	    }
	}
	else if (EQ(temp2,Qor)) {
	    exp = CDR(exp);
	    L1_BEGIN_LOOP: 
	    l1_subform = CAR(exp);
	    exp = CDR(exp);
	    if (!TRUEP(exp)) {
		temp1 = eval_run(l1_subform);
		goto LABEL2;
	    }
	    else if (TRUEP(l1_subform = eval_run(l1_subform))) {
		temp1 = VALUES_1(l1_subform);
		goto LABEL2;
	    }
	    goto L1_BEGIN_LOOP;
	    /*L1_END_LOOP: */
	    temp1 = VALUES_1(NIL);
	    LABEL2: 
	    ;
	}
	else if (EQ(temp2,Qsetq) || EQ(temp2,Qdefvar)) {
	    temp1 = CALL_2(set,SECOND(exp),eval_run(THIRD(exp)));
	}
	else if (EQ(temp2,Qprogn)) {
	    temp1 = eval_progn(CDR(exp));
	}
	else if (EQ(temp2,Qlet)) {
	    temp3 = mapcar(2,FP_BINDING_VARIABLE,SECOND(exp));
	    temp4 = mapcar(2,FP_BINDING_INITFORM,SECOND(exp));
	    PROGV(temp3, temp4, unwind_p, old_env_1, LABEL3);
	      temp1 = eval_progn(CDDR(exp));
	    LABEL3: 
	    END_PROGV(unwind_p, old_env_1);
	}
	else if (EQ(temp2,Qdo)) {
	    var_init_step_list = SECOND(exp);
	    test_result = THIRD(exp);
	    test = FIRST(test_result);
	    result_forms = CDR(test_result);
	    body = CDDDR(exp);
	    temp5 = mapcar(2,FP_BINDING_VARIABLE,var_init_step_list);
	    temp6 = mapcar(2,FP_BINDING_INITFORM,var_init_step_list);
	    PROGV(temp5, temp6, l1_unwind_p, old_env_2, LABEL4);
	      while (!TRUEP(eval_run(test))) {
		  eval_progn(body);
		  for (temp7 = var_init_step_list; temp7; temp7 = M_CDR(temp7)) {
		      var_init_step = M_CAR(temp7);
		      if (CONSP(var_init_step) && TRUEP(CDDR(var_init_step))) {
			  CALL_2(set,FIRST(var_init_step),
				  eval_run(THIRD(var_init_step)));
		      }
		  }
	      }
	      temp1 = eval_progn(result_forms);
	    LABEL4: 
	    END_PROGV(l1_unwind_p, old_env_2);
	}
	else if (EQ(temp2,Qdefun)) {
	    fname = SECOND(exp);
	    lambda_form = cons(Qlambda, CDDR(exp));
	    temp1 = length(THIRD(exp));
	    temp2 = cons(lambda_form, NIL);
	    /* all interpreted functions are positional for now */
	    temp2 = MAKE_FUNCTION(apply_lambda, temp2, TRUE, 
				  IFIX(temp1), IFIX(temp1));
	    set_symbol_function(fname,temp2);
	    temp1 = VALUES_1(fname);
	}
	else if (EQ(temp2,Qincf)) {
	    var = SECOND(exp);
	    delta_p = CDDR(exp);
	    if (!TRUEP(delta_p)) {
		temp1 = CALL_2(set,var,add1(symbol_value(var)));
	    }
	    else {
		delta = CAR(delta_p);
		temp1 = CALL_2(set,var,CALL_2(add,symbol_value(var),
			eval_run(delta)));
	    }
	}
	else if (EQ(temp2,Qdeclare)) {
	    temp1 = VALUES_1(NIL);
	}
#ifdef SUPPORT_CATCH
	else if (EQ(temp2,Qcatch)) {
	  if (PUSH_CATCH(eval_run(CADR(exp)),0)) {
	    temp1 = eval_progn(CDDR(exp));
	  }
	  else
	    temp1 = CATCH_VALUES();
	  POP_CATCH(0);
	}
	else if (EQ(temp2,Qthrow)) {
	  temp3 = eval_run(CADR(exp));
	  temp1 = eval_progn(CDDR(exp));
	  THROW(temp3,temp1);
	}
#endif
	else {
	    l1_fun = CAR(exp);
	    args = CDR(exp);
	    if (SYMBOLP(l1_fun) && TRUEP(macro_function(l1_fun, KOPT))) {
		temp1 = eval_run(CALL_3(funcall2,macro_function(l1_fun, KOPT),
			exp,NIL));
	    }
	    else {
		/* lambda call */
		if (CONSP(l1_fun)) {
		    if (!(EQ(Qlambda, CAR(l1_fun))))
			error
			    (2, "evaluator: bad lambda expression ~S", l1_fun);
		    /* all interpreted functions are positional for now */
		    temp1 = length(SECOND(l1_fun));
		    temp2 = cons(l1_fun, NIL);
		    l1_fun = 
			MAKE_FUNCTION(apply_lambda,temp2,TRUE,
				      IFIX(temp1),IFIX(temp1));
		}
		temp8 = length(args);
		if (FIXNUM_EQ(temp8,ZERO)) {
		    temp1 = FUNCALL_0(l1_fun);
		}
		else if (FIXNUM_EQ(temp8,FIX(1))) {
		    temp1 = eval_run(CAR(args));
		    temp1 = FUNCALL_1(l1_fun,temp1);
		}
		else if (FIXNUM_EQ(temp8,FIX(2))) {
		    temp10 = l1_fun;
		    temp9 = CAR(args);
		    args = CDR(args);
		    temp11 = eval_run(temp9);
		    temp12 = eval_run(CAR(args));
		    temp1 = FUNCALL_2(temp10,temp11,temp12);
		}
		else if (FIXNUM_EQ(temp8,FIX(3))) {
		    temp15 = l1_fun;
		    temp13 = CAR(args);
		    args = CDR(args);
		    temp16 = eval_run(temp13);
		    temp14 = CAR(args);
		    args = CDR(args);
		    temp17 = eval_run(temp14);
		    temp18 = eval_run(CAR(args));
		    temp1 = FUNCALL_3(temp15,temp16,temp17,temp18);
		}
		else if (FIXNUM_EQ(temp8,FIX(4))) {
		    temp22 = l1_fun;
		    temp19 = CAR(args);
		    args = CDR(args);
		    temp23 = eval_run(temp19);
		    temp20 = CAR(args);
		    args = CDR(args);
		    temp24 = eval_run(temp20);
		    temp21 = CAR(args);
		    args = CDR(args);
		    temp25 = eval_run(temp21);
		    temp26 = eval_run(CAR(args));
		    temp1 = funcall(5,temp22,temp23,temp24,temp25,temp26);
		}
		else 
		    temp1 = CALL_2(apply1,l1_fun,mapcar(2,FP_EVAL_RUN,args));
	    }
	}
    }
    else if (SYMBOLP(exp)) {
	temp1 = symbol_value(exp);
    }
    else 
	temp1 = VALUES_1(exp);
    RESTORE_STACK();
    return(temp1);
}


static Object eval_progn(forms)
    Object forms;
{
    Declare_local_temp;
    Object subform;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(forms);
    PROTECTI_2(subform,temp1);
    BEGIN_LOOP: 
    subform = CAR(forms);
    forms = CDR(forms);
    if (ENDP(forms)) {
	temp1 = eval_run(subform);
	goto LABEL1;
    }
    else 
	eval_run(subform);
    goto BEGIN_LOOP;
    /*END_LOOP: */
    temp1 = VALUES_1(NIL);
    LABEL1: 
    RESTORE_STACK();
    return(temp1);
}

Object binding_variable(var_initform)
    Object var_initform;
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(var_initform);
    PROTECTI_1(temp1);
    temp1 = (ATOM(var_initform) ? VALUES_1(var_initform) : 
	    T_VALUES_1(CAR(var_initform)));
    RESTORE_STACK();
    return(temp1);
}

Object binding_initform(var_initform)
    Object var_initform;
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(var_initform);
    PROTECTI_1(temp1);
    temp1 = (ATOM(var_initform) ? VALUES_1(NIL) : 
	    T_VALUES_1(SECOND(var_initform)));
    temp1 = eval_run(temp1);
    RESTORE_STACK();
    return(temp1);
}


