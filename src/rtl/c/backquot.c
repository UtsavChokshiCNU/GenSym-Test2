/*
 * backquot.c
 * Input file:  /usr/staff/jar/runtime/backquot.lisp
 * Translated on 3/30/91    8:50:13 pm
 * Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object Ptrun;
extern Object Qappend;
extern Object Qbackquote;
extern Object Qcons;
extern Object Qlist_star;
extern Object Qlist;
extern Object Qnconc;
extern Object Qquote;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;
extern TLS Object T_temp;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object STATIC_STRING(char *s);
extern Object append2(Object list1, Object list2);
extern Object cadr(Object);
extern Object cons(Object,Object);
extern Object eql(Object,Object);
extern Object equal(Object,Object);
extern Object every(long,...);
extern Object funcall1(Object func, Object arg);
extern Object last(Object,Object);
extern Object list_star(long,...);
extern Object list(long,...);
extern Object make_symbol(Object);
extern Object mapcar(long,...);
extern Object ncons(Object a);
extern Object notany(long,...);
extern Object nreconc(Object,Object);
extern Object reverse(Object);
extern Object set_macro_function(Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern Object STATIC_FUNCTION1();
extern Object STATIC_STRING();
extern Object append2();
extern Object cadr();
extern Object cons();
extern Object eql();
extern Object equal();
extern Object every();
extern Object funcall1();
extern Object last();
extern Object list_star();
extern Object list();
extern Object make_symbol();
extern Object mapcar();
extern Object ncons();
extern Object notany();
extern Object nreconc();
extern Object reverse();
extern Object set_macro_function();

#endif



/* -*- Mode: Lisp; Package: USER; -*-
 * Code for backquote macro from Guy Steele 2, Appendix C (pp. 960-967).
 * See Steele's text for comments.
 * To generate backquot.c from backquot.lisp:
 *   1. Prep-file and translate-file backquot.lisp
 *   2. Insert backquot.top
 * 1.  $ is pseudo-backquote and % is pseudo-comma.  These should be changed
 *     to ` and , before installing in the run-time kernel.  
 * 3.  The globals below can be made into any unique node (e.g. cons
 *     cells) to save space and initialization time.
 * 4.  If desired, you can remove *bq-simplify-p* (assume T) and the code
 *     which refers to it.
 * 5.  After certain optimizations are implemented in the Translator,
 *     it would be worthwhile retranslating this; you'll get better code.  
 *     For that reason, and general robustness, it would be good
 *     if you could keep the Lisp in sync w/C.
 *     The optimizations involved are:  T_ macros; tail recursion; 
 *     common-subexpression elimination; open-coding of mapping (e.g. mapcar)
 *     and sequence (e.g. every, notany) functions.
 * 6.  The code seems to have a bug:  It doesn't detect commas that
 *     occur outside of backquotes, e.g. (a ,b).  Maybe you can think of
 *     a way to do this by adding a *backquote-level* or an extra arg
 *     for the recursive reader so that the , handler knows that it's 
 *     "inside" a backquote.
 *
 * 1.  It would help efficiency to replace maptree by a version that
 *     takes an "immediate function" argument rather than an fpointer.
 *     This could be added to the Translator as a type-declaration hack.
 *     Such functions must be called with exactly the correct number of
 *     args; maybe "box", "unbox", "normalize" them.  This might be cute for
 *     the kernel too:  mapcar takes immediate by default; "normalize" if
 *     opt, rest, key, etc.
 * 2.  It would help some of these functions to insert type declarations -
 *     e.g. predicate (for "frob" functions).  Could also be part of
 *     "boxing"/normalizing for every, notany, etc.
 */


Object Qcomma = UNBOUND;
Object Qcomma_atsign = UNBOUND;
Object Qcomma_dot = UNBOUND;

static Object Bq_list = UNBOUND;

static Object Bq_append = UNBOUND;

static Object Bq_listSTAR = UNBOUND;

static Object Bq_nconc = UNBOUND;

static Object Bq_clobberable = UNBOUND;

static Object Bq_quote = UNBOUND;

static Object Bq_quote_nil = UNBOUND;

static Object Bq_simplify_p = T;

extern Object NEW_SYMBOL(); 

/* backquot.top        (Initialization code)
 * Input file:  /usr/staff/jar/runtime/backquot.lisp
 * Translated on 3/30/91    8:50:15 pm
 * Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
 */

void backquot_top_level()
{
    extern Object expand_backquote();
                /*  CONST1 = "COMMA"  */
    SI_Declare_static_string(CONST1, d1, "COMMA");
                /*  CONST2 = "COMMA-ATSIGN"  */
    SI_Declare_static_string(CONST2, d2, "COMMA-ATSIGN");
                /*  CONST3 = "COMMA-DOT"  */
    SI_Declare_static_string(CONST3, d3, "COMMA-DOT");
                /*  CONST4 = "BQ-LIST"  */
    SI_Declare_static_string(CONST4, d4, "BQ-LIST");
                /*  CONST5 = "BQ-APPEND"  */
    SI_Declare_static_string(CONST5, d5, "BQ-APPEND");
                /*  CONST6 = "BQ-LIST*"  */
    SI_Declare_static_string(CONST6, d6, "BQ-LIST*");
                /*  CONST7 = "BQ-NCONC"  */
    SI_Declare_static_string(CONST7, d7, "BQ-NCONC");
                /*  CONST8 = "BQ-CLOBBERABLE"  */
    SI_Declare_static_string(CONST8, d8, "BQ-CLOBBERABLE");
                /*  CONST9 = "BQ-QUOTE"  */
    SI_Declare_static_string(CONST9, d9, "BQ-QUOTE");

    SI_Declare_static_constant(FP_EXPAND_BACKQUOTE, d0,
			STATIC_FUNCTION(expand_backquote,NIL,FALSE,1,1));

    Bq_simplify_p = NIL; /* to avoid buggy simplifier */

    Qcomma = NEW_SYMBOL(Ptrun,"COMMA",TRUE);
    Qcomma_atsign =  NEW_SYMBOL(Ptrun,"COMMA-ATSIGN",TRUE);
    Qcomma_dot =  NEW_SYMBOL(Ptrun,"COMMA-DOT",TRUE);
    Bq_list = make_symbol(CONST4);
    Bq_append = make_symbol(CONST5);
    Bq_listSTAR = make_symbol(CONST6);
    Bq_nconc = make_symbol(CONST7);
    Bq_clobberable = make_symbol(CONST8);
    Bq_quote = make_symbol(CONST9);
    Bq_quote_nil = LIST_2(Bq_quote,NIL);
    set_macro_function(Qbackquote,FP_EXPAND_BACKQUOTE);
}

Object expand_backquote(macroarg)
    Object macroarg;
{
    Object x;
    Object temp1;
    extern Object bq_completely_process();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(macroarg);
    PROTECTI_2(x,temp1);
    macroarg = M_CDR(macroarg);
    x = M_CAR(macroarg);
    temp1 = bq_completely_process(x);
    RESTORE_STACK();
    return(temp1);
}

Object bq_completely_process(x)
    Object x;
{
    Object raw_result;
    Object temp1;
    extern Object bq_process();
    extern Object bq_simplify();
    extern Object bq_remove_tokens();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_2(raw_result,temp1);
    raw_result = bq_process(x);
    temp1 = bq_remove_tokens((Bq_simplify_p ? bq_simplify(raw_result) : 
	    raw_result));
    RESTORE_STACK();
    return(temp1);
}

Object bq_process(x)
    Object x;
{
    Declare_local_temp;
    Object q;
    Object p;
    Object temp1;
    Object temp2;
    Object temp3;
    Object temp4;
    extern Object bq_completely_process();
    extern Object bq_process();
    extern Object bracket();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_6(q,p,temp1,temp2,temp3,temp4);
    if (ATOM(x)) {
	temp1 = T_VALUES_1(LIST_2(Bq_quote,x));
    }
    else if (EQ(CAR(x),Qbackquote)) {
	temp1 = bq_process(bq_completely_process(CADR(x)));
    }
    else if (CALL_2(EQ,CAR(x),Qcomma_atsign)) {
	temp2 = CADR(x);
	temp1 = error(2, ",@~S after `",temp2);
    }
    else if (CALL_2(EQ,CAR(x),Qcomma_dot)) {
	temp3 = CADR(x);
	temp1 = error(2, ",.~S after `",temp3);
    }
    else {
	for ((q = NIL), (p = x); !ATOM(p); (temp4 = CALL_2(cons,
		bracket(CAR(p)),q)), (p = CDR(p)), (q = temp4)) {
	    if (CALL_2(EQ,CAR(p),Qcomma)) {
		if (CDDR(p)) {
		    error(2, "Malformed ,~S",p);
		}
		temp1 = CALL_2(cons,Bq_append,CALL_2(nreconc,q,
			LIST_1(CADR(p))));
		goto LABEL1;
	    }
	    if (CALL_2(EQ,CAR(p),Qcomma_atsign)) {
		error(2, "Dotted ,@~S",p);
	    }
	    if (CALL_2(EQ,CAR(p),Qcomma_dot)) {
		error(2, "Dotted ,.~S",p);
	    }
	}
	temp1 = CALL_2(cons,Bq_append,CALL_2(nreconc,q,
		LIST_1(LIST_2(Bq_quote,p))));
	LABEL1: 
	;
    }
    RESTORE_STACK();
    return(temp1);
}

Object bracket(x)
    Object x;
{
    Declare_local_temp;
    Object temp1;
    extern Object bq_process();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_1(temp1);
    if (ATOM(x)) {
	temp1 = T_VALUES_1(CALL_2(LIST_2,Bq_list,bq_process(x)));
    }
    else if (CALL_2(EQ,CAR(x),Qcomma)) {
	temp1 = T_VALUES_1(CALL_2(LIST_2,Bq_list,CADR(x)));
    }
    else if (CALL_2(EQ,CAR(x),Qcomma_atsign)) {
	temp1 = T_VALUES_1(CADR(x));
    }
    else if (CALL_2(EQ,CAR(x),Qcomma_dot)) {
	temp1 = T_VALUES_1(CALL_2(LIST_2,Bq_clobberable,CADR(x)));
    }
    else 
	temp1 = T_VALUES_1(CALL_2(LIST_2,Bq_list,bq_process(x)));
    RESTORE_STACK();
    return(temp1);
}

Object maptree(fn,x)
    Object fn;
    Object x;
{
    Declare_local_temp;
    Object a;
    Object d;
    Object temp1;
    extern Object maptree();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(fn,x);
    PROTECTI_3(a,d,temp1);
    if (ATOM(x)) {
	temp1 = funcall1(fn,x);
    }
    else {
	a = CALL_2(funcall1,fn,CAR(x));
	d = CALL_2(maptree,fn,CDR(x));
	temp1 = ((CALL_2(eql,a,CAR(x)) && CALL_2(eql,d,CDR(x))) ? 
		VALUES_1(x) : cons(a,d));
    }
    RESTORE_STACK();
    return(temp1);
}

Object bq_splicing_frob(x)
    Object x;
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_1(temp1);
    temp1 = ((CONSP(x) && (CALL_2(EQ,CAR(x),Qcomma_atsign) || CALL_2(EQ,
	    CAR(x),Qcomma_dot))) ? VALUES_1(T) : VALUES_1(NIL));
    RESTORE_STACK();
    return(temp1);
}

Object bq_frob(x)
    Object x;
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_1(temp1);
    temp1 = ((CONSP(x) && (CALL_2(EQ,CAR(x),Qcomma) || CALL_2(EQ,CAR(x),
	    Qcomma_atsign) || CALL_2(EQ,CAR(x),Qcomma_dot))) ? VALUES_1(T) : 
	    VALUES_1(NIL));
    RESTORE_STACK();
    return(temp1);
}

Object bq_simplify(x)
    Object x;
{
    Declare_local_temp;
    Object l1_x;
    Object temp1;
    extern Object bq_simplify();
    extern Object maptree();
    extern Object bq_simplify_args();
    SI_Declare_static_constant(Q_bq_simplify, d0,
			       STATIC_FUNCTION(bq_simplify, NIL, FALSE, 1L, 1L));
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_2(l1_x,temp1);
    if (ATOM(x)) {
	temp1 = VALUES_1(x);
    }
    else {
	l1_x = (CALL_2(EQ,CAR(x),Bq_quote) ? x : maptree(Q_bq_simplify,x));
	temp1 = (CALL_2(NEQ,CAR(l1_x),Bq_append) ? VALUES_1(l1_x) : 
		bq_simplify_args(l1_x));
    }
    RESTORE_STACK();
    return(temp1);
}

Object bq_simplify_args(x)
    Object x;
{
    Declare_local_temp;
    Object result;
    Object args;
    Object temp1;
    Object temp2;
    extern Object bq_attach_append();
    extern Object bq_attach_conses();
    extern Object bq_frob();
    extern Object bq_splicing_frob();
    SI_Declare_static_constant(Q_bq_splicing_frob, d0,
		STATIC_FUNCTION(bq_splicing_frob, NIL, FALSE, 1, 1));       
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_4(result,args,temp1,temp2);
    result = NIL;
    args = reverse(CDR(x));
    while (args) {
	if (T_ATOM(CAR(args))) {
	    temp1 = CALL_3(bq_attach_append,Bq_append,CAR(args),result);
	}
	else if (CALL_2(EQ,CAAR(args),Bq_list) && 
		notany(2,Q_bq_splicing_frob,CDAR(args))) {
	    temp1 = CALL_2(bq_attach_conses,CDAR(args),result);
	}
	else if (CALL_2(EQ,CAAR(args),Bq_listSTAR) && 
		notany(2,Q_bq_splicing_frob,CDAR(args))) {
	    temp1 = CALL_2(bq_attach_conses,
		    reverse(T_CDR(reverse(CDAR(args)))),
		    CALL_3(bq_attach_append,Bq_append,
		    T_CAR(last(CAR(args), KOPT)),result));
	}
	else if (CALL_2(EQ,CAAR(args),Bq_quote) && T_CONSP(CADAR(args)) && 
		!bq_frob(CADAR(args)) && !CDDAR(args)) {
	    temp1 = CALL_2(bq_attach_conses,LIST_1(CALL_2(LIST_2,Bq_quote,
		    CAADAR(args))),result);
	}
	else if (CALL_2(EQ,CAAR(args),Bq_clobberable)) {
	    temp1 = CALL_3(bq_attach_append,Bq_nconc,CADAR(args),result);
	}
	else 
	    temp1 = CALL_3(bq_attach_append,Bq_append,CAR(args),result);
	args = CDR(args);
	result = temp1;
    }
    temp2 = VALUES_1(result);
    RESTORE_STACK();
    return(temp2);
}

Object null_or_quoted(x)
    Object x;
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_1(temp1);
    temp1 = ((!x || (CONSP(x) && CALL_2(EQ,CAR(x),Bq_quote))) ? 
	    VALUES_1(T) : VALUES_1(NIL));
    RESTORE_STACK();
    return(temp1);
}

Object bq_attach_append(op,item,result)
    Object op;
    Object item;
    Object result;
{
    Declare_local_temp;
    Object temp1;
    extern Object bq_splicing_frob();
    extern Object null_or_quoted();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(op,item,result);
    PROTECTI_1(temp1);
    if (null_or_quoted(item) && null_or_quoted(result)) {
	temp1 = T_VALUES_1(CALL_2(LIST_2,Bq_quote,CALL_2(append2,
		CADR(item),CADR(result))));
    }
    else if (!result || equal(result,Bq_quote_nil)) {
	temp1 = (bq_splicing_frob(item) ? T_VALUES_1(LIST_2(op,item)) : 
		VALUES_1(item));
    }
    else if (CONSP(result) && CALL_2(EQ,CAR(result),op)) {
	temp1 = T_VALUES_1(CALL_3(LIST_STAR_3,CAR(result),item,CDR(result)));
    }
    else 
	temp1 = T_VALUES_1(LIST_3(op,item,result));
    RESTORE_STACK();
    return(temp1);
}

Object bq_attach_conses(items,result)
    Object items;
    Object result;
{
    Declare_local_temp;
    Object temp1;
    extern Object null_or_quoted();
    SI_Declare_static_constant(FP_CADR, d0,
		STATIC_FUNCTION(cadr, NIL, FALSE, 1, 1));
    SI_Declare_static_constant(FP_NULL_OR_QUOTED, d1,
		STATIC_FUNCTION(null_or_quoted, NIL, FALSE, 1L, 1L));
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(items,result);
    PROTECTI_1(temp1);
    if (every(2,FP_NULL_OR_QUOTED,items) && null_or_quoted(result)) {
	temp1 = T_VALUES_1(CALL_2(LIST_2,Bq_quote,CALL_2(append2,
		mapcar(2,FP_CADR,items),CADR(result))));
    }
    else if (!result || equal(result,Bq_quote_nil)) {
	temp1 = cons(Bq_list,items);
    }
    else if (CONSP(result) && (CALL_2(EQ,CAR(result),Bq_list) || CALL_2(EQ,
	    CAR(result),Bq_listSTAR))) {
	temp1 = CALL_2(cons,CAR(result),CALL_2(append2,items,CDR(result)));
    }
    else 
	temp1 = CALL_2(cons,Bq_listSTAR,CALL_2(append2,items,LIST_1(result)));
    RESTORE_STACK();
    return(temp1);
}

Object bq_remove_tokens(x)
    Object x;
{
    Declare_local_temp;
    Object temp1;
    extern Object bq_remove_tokens();
    extern Object maptree();
    SI_Declare_static_constant(Q_bq_remove_tokens, d0,
		STATIC_FUNCTION(bq_remove_tokens, NIL, FALSE, 1L, 1L));
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(x);
    PROTECTI_1(temp1);
    if (EQ(x,Bq_list)) {
	temp1 = VALUES_1(Qlist);
    }
    else if (EQ(x,Bq_append)) {
	temp1 = VALUES_1(Qappend);
    }
    else if (EQ(x,Bq_nconc)) {
	temp1 = VALUES_1(Qnconc);
    }
    else if (EQ(x,Bq_listSTAR)) {
	temp1 = VALUES_1(Qlist_star);
    }
    else if (EQ(x,Bq_quote)) {
	temp1 = VALUES_1(Qquote);
    }
    else if (ATOM(x)) {
	temp1 = VALUES_1(x);
    }
    else if (CALL_2(EQ,CAR(x),Bq_clobberable)) {
	temp1 = bq_remove_tokens(CADR(x));
    }
    else if (CALL_2(EQ,CAR(x),Bq_listSTAR) && T_CONSP(CDDR(x)) && !CDDDR(x)) {
	temp1 = cons(Qcons,maptree(Q_bq_remove_tokens,CDR(x)));
    }
    else 
	temp1 = maptree(Q_bq_remove_tokens,x);
    RESTORE_STACK();
    return(temp1);
}


void SI_INIT_backquote()
{
    extern Object SI_NEW_SYMBOL();
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    Qbackquote = SI_NEW_SYMBOL(&Ptrun,"BACKQUOTE",TRUE);
    backquot_top_level();
    RESTORE_CURRENT_AREA(a);
}


Object SI_comma_macro_handler (ch, pair)
    long ch;
    Object pair;
{
    switch(ch) {
    case '@' :
	M_CAR(pair) = Qcomma_atsign; break;
    case '.' :
	M_CAR(pair) = Qcomma_dot;    break;
    default:
	M_CAR(pair) = Qcomma;
    }
    return VALUES_1(pair);
}



