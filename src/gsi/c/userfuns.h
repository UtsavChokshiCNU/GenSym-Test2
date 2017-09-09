/* userfuns.h -- Header for function linking code for Lisp-to-C Translator
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

extern Object Qcar;
extern Object Qcdr;
extern Object Qcharacter;
extern Object Qcons;
extern Object Qconsp;
extern Object Qeq;
extern Object Qequal;
extern Object Qerror;
extern Object Qgentemp;
extern Object Qintern;
extern Object Qfloat;
extern Object Qlist;
extern Object Qmake_array;
extern Object Qmember;
extern Object Qnot;
extern Object Qnull;
extern Object Qnum_lt;
extern Object Qsecond;
extern Object Qstring;
extern Object Qstring_eq;
extern Object Qstringp;
extern Object Qsymbolp;
extern Object Qvector;

#ifdef USE_PROTOTYPES

extern Object car(Object);
extern Object cdr(Object);
extern Object character(Object);
extern Object cons(Object,Object);
extern Object consp(Object);
extern Object eq(Object,Object);
extern Object equal(Object,Object);
extern Object errorn(int,...);
extern Object gentemp(Object,Object);
extern Object intern(Object,Object);
extern Object lfloat(Object,Object);
extern Object list(int,...);
extern Object make_array(int,...);
extern Object member(int,...);
extern Object not(Object);
extern Object null(Object);
extern Object num_ltn(int,...);
extern Object second(Object);
extern Object string(Object);
extern Object string_eq(int,...);
extern Object stringp(Object);
extern Object symbolp(Object);
extern Object vector(int,...);

#else

extern Object car();
extern Object cdr();
extern Object character();
extern Object cons();
extern Object consp();
extern Object eq();
extern Object equal();
extern Object errorn();
extern Object gentemp();
extern Object intern();
extern Object lfloat();
extern Object list();
extern Object make_array();
extern Object member();
extern Object not();
extern Object null();
extern Object num_ltn();
extern Object second();
extern Object string();
extern Object string_eq();
extern Object stringp();
extern Object symbolp();
extern Object vector();

#endif
