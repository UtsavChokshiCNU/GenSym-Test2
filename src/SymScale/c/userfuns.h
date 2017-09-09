/* userfuns.h -- Header for function linking code for Lisp-to-C Translator
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

extern Object Qaref;
extern Object Qbit;
extern Object Qsbit;
extern Object Qadd1;
extern Object Qplus;
extern Object Qadjoin;
extern Object Qalpha_char_p;
extern Object Qalphanumericp;
extern Object Qappend;
extern Object Qapply;
extern Object Qaref;
extern Object Qarray_dimension;
extern Object Qarray_element_type;
extern Object Qarray_has_fill_pointer_p;
extern Object Qarray_rank;
extern Object Qarray_total_size;
extern Object Qarrayp;
extern Object Qash;
extern Object Qassoc;
extern Object Qatom;
extern Object Qbit;
extern Object Qboth_case_p;
extern Object Qboundp;
extern Object Qbreak;
extern Object Qbutlast;
extern Object Qbyte;
extern Object Qbyte_position;
extern Object Qcaaaar;
extern Object Qcaaadr;
extern Object Qcaaar;
extern Object Qcaadar;
extern Object Qcaaddr;
extern Object Qcaadr;
extern Object Qcaar;
extern Object Qcadaar;
extern Object Qcadadr;
extern Object Qcadar;
extern Object Qcaddar;
extern Object Qcadddr;
extern Object Qcaddr;
extern Object Qcadr;
extern Object Qcar;
extern Object Qcdaaar;
extern Object Qcdaadr;
extern Object Qcdaar;
extern Object Qcdadar;
extern Object Qcdaddr;
extern Object Qcdadr;
extern Object Qcdar;
extern Object Qcddaar;
extern Object Qcddadr;
extern Object Qcddar;
extern Object Qcdddar;
extern Object Qcddddr;
extern Object Qcdddr;
extern Object Qcddr;
extern Object Qcdr;
extern Object Qceiling;
extern Object Qcerror;
extern Object Qchar_code;
extern Object Qchar_downcase;
extern Object Qchar_eq;
extern Object Qchar_equal;
extern Object Qchar_ge;
extern Object Qchar_greaterp;
extern Object Qchar_gt;
extern Object Qchar_int;
extern Object Qchar_le;
extern Object Qchar_lessp;
extern Object Qchar_lt;
extern Object Qchar_ne;
extern Object Qchar_not_equal;
extern Object Qchar_upcase;
extern Object Qcharacter;
extern Object Qcharacterp;
extern Object Qclear_input;
extern Object Qclrhash;
extern Object Qcode_char;
extern Object Qcoerce;
extern Object Qcompiled_function_p;
extern Object Qconcatenate;
extern Object Qcons;
extern Object Qconsp;
extern Object Qconstantp;
extern Object Qcopy_list;
extern Object Qcopy_seq;
extern Object Qcopy_tree;
extern Object Qcount;
extern Object Qcount_if;
extern Object Qdecode_universal_time;
extern Object Qdenominator;
extern Object Qdigit_char;
extern Object Qdigit_char_p;
extern Object Qslash;
extern Object Qeighth;
extern Object Qelt;
extern Object Qencode_universal_time;
extern Object Qendp;
extern Object Qeq;
extern Object Qeql;
extern Object Qequal;
extern Object Qequalp;
extern Object Qerror;
extern Object Qevenp;
extern Object Qevery;
extern Object Qexport;
extern Object Qexpt;
extern Object Qfboundp;
extern Object Qfceiling;
extern Object Qfifth;
extern Object Qfile_author;
extern Object Qfile_length;
extern Object Qfile_position;
extern Object Qfile_write_date;
extern Object Qfill;
extern Object Qfill_pointer;
extern Object Qfind;
extern Object Qfind_if;
extern Object Qfind_package;
extern Object Qfind_symbol;
extern Object Qfirst;
extern Object Qfloatp;
extern Object Qfmakunbound;
extern Object Qforce_output;
extern Object Qformat;
extern Object Qfourth;
extern Object Qfresh_line;
extern Object Qfround;
extern Object Qfunctionp;
extern Object Qgentemp;
extern Object Qget;
extern Object Qget_decoded_time;
extern Object Qget_internal_real_time;
extern Object Qget_output_stream_string;
extern Object Qget_universal_time;
extern Object Qgetf;
extern Object Qgethash;
extern Object Qhash_table_count;
extern Object Qidentity;
extern Object Qimport;
extern Object Qinteger_length;
extern Object Qintegerp;
extern Object Qintern;
extern Object Qintersection;
extern Object Qisqrt;
extern Object Qkeywordp;
extern Object Qabs;
extern Object Qrandom;
extern Object Qround;
extern Object Qasin;
extern Object Qlast;
extern Object Qatan;
extern Object Qchar;
extern Object Qclose;
extern Object Qcos;
extern Object Qldb;
extern Object Qdelete;
extern Object Qldiff;
extern Object Qlength;
extern Object Qexp;
extern Object Qffloor;
extern Object Qfloat;
extern Object Qfloor;
extern Object Qftruncate;
extern Object Qlisp_implementation_version;
extern Object Qlist;
extern Object Qlist_length;
extern Object Qlist_star;
extern Object Qlistp;
extern Object Qlisten;
extern Object Qlog;
extern Object Qlogandc1;
extern Object Qlogandc2;
extern Object Qlogand;
extern Object Qlogbitp;
extern Object Qlogcount;
extern Object Qlogior;
extern Object Qlognot;
extern Object Qlogtest;
extern Object Qlogxor;
extern Object Qopen;
extern Object Qlower_case_p;
extern Object Qread;
extern Object Qremove;
extern Object Qsin;
extern Object Qsleep;
extern Object Qsqrt;
extern Object Qtan;
extern Object Qtruncate;
extern Object Qunion;
extern Object Qwrite;
extern Object Qmacro_function;
extern Object Qmacroexpand;
extern Object Qmacroexpand_1;
extern Object Qmake_array;
extern Object Qmake_broadcast_stream;
extern Object Qmake_hash_table;
extern Object Qmake_list;
extern Object Qmake_package;
extern Object Qmake_string;
extern Object Qmake_string_output_stream;
extern Object Qmake_symbol;
extern Object Qmakunbound;
extern Object Qmap;
extern Object Qmapcan;
extern Object Qmapcar;
extern Object Qmaphash;
extern Object Qmax;
extern Object Qmember;
extern Object Qmerge;
extern Object Qmin;
extern Object Qminus;
extern Object Qminusp;
extern Object Qmismatch;
extern Object Qmod;
extern Object Qnbutlast;
extern Object Qnconc;
extern Object Qninth;
extern Object Qnot;
extern Object Qnotany;
extern Object Qnreconc;
extern Object Qnreverse;
extern Object Qnstring_downcase;
extern Object Qnstring_upcase;
extern Object Qnsubst;
extern Object Qnth;
extern Object Qnthcdr;
extern Object Qnull;
extern Object Qnum_eq;
extern Object Qnum_ge;
extern Object Qnum_gt;
extern Object Qnum_le;
extern Object Qnum_lt;
extern Object Qnum_ne;
extern Object Qnumberp;
extern Object Qnumerator;
extern Object Qoddp;
extern Object Qpackage_name;
extern Object Qparse_integer;
extern Object Qpeek_char;
extern Object Qphase;
extern Object Qplusp;
extern Object Qposition;
extern Object Qposition_if;
extern Object Qposition_if_not;
extern Object Qpprint;
extern Object Qprin1;
extern Object Qprinc;
extern Object Qprint;
extern Object Qrassoc;
extern Object Qread_byte;
extern Object Qread_char;
extern Object Qread_char_no_hang;
extern Object Qread_from_string;
extern Object Qread_line;
extern Object Qrem;
extern Object Qremove_duplicates;
extern Object Qremove_if;
extern Object Qremove_if_not;
extern Object Qremprop;
extern Object Qreplace;
extern Object Qrest;
extern Object Qrevappend;
extern Object Qreverse;
extern Object Qroom;
extern Object Qrplaca;
extern Object Qrplacd;
extern Object Qsbit;
extern Object Qscale_float;
extern Object Qschar;
extern Object Qsearch;
extern Object Qsecond;
extern Object Qset;
extern Object Qset_difference;
extern Object Qseventh;
extern Object Qshort_site_name;
extern Object Qsimple_string_p;
extern Object Qsimple_vector_p;
extern Object Qsixth;
extern Object Qsort;
extern Object Qstable_sort;
extern Object Qstreamp;
extern Object Qstring;
extern Object Qstring_capitalize;
extern Object Qstring_downcase;
extern Object Qstring_eq;
extern Object Qstring_equal;
extern Object Qstring_greaterp;
extern Object Qstring_le;
extern Object Qstring_lessp;
extern Object Qstring_lt;
extern Object Qstring_ne;
extern Object Qstring_not_equal;
extern Object Qstring_not_greaterp;
extern Object Qstring_not_lessp;
extern Object Qstring_trim;
extern Object Qstring_upcase;
extern Object Qstringp;
extern Object Qsub1;
extern Object Qsublis;
extern Object Qsubseq;
extern Object Qsubsetp;
extern Object Qsubst;
extern Object Qsubstitute;
extern Object Qsvref;
extern Object Qsxhash;
extern Object Qsymbol_function;
extern Object Qsymbol_name;
extern Object Qsymbol_package;
extern Object Qsymbol_plist;
extern Object Qsymbol_value;
extern Object Qsymbolp;
extern Object Qtenth;
extern Object Qterpri;
extern Object Qthird;
extern Object Qstar;
extern Object Qtree_equal;
extern Object Qtype_of;
extern Object Qtypep;
extern Object Qunintern;
extern Object Qunread_char;
extern Object Qupper_case_p;
extern Object Qvalues;
extern Object Qvalues_list;
extern Object Qvector;
extern Object Qvector_push;
extern Object Qvectorp;
extern Object Qwarn;
extern Object Qwrite_byte;
extern Object Qwrite_char;
extern Object Qwrite_line;
extern Object Qwrite_string;
extern Object Qwrite_to_string;
extern Object Qzerop;

#ifdef USE_PROTOTYPES

extern Object SETF_aref(int,...);
extern Object SETF_bit(int,...);
extern Object SETF_sbit(int,...);
extern Object add1(Object);
extern Object addn(int,...);
extern Object adjoin(int,...);
extern Object alpha_char_p(Object);
extern Object alphanumericp(Object);
extern Object append(int,...);
extern Object apply(int,...);
extern Object aref(int,...);
extern Object array_dimension(Object,Object);
extern Object array_element_type(Object);
extern Object array_has_fill_pointer_p(Object);
extern Object array_rank(Object);
extern Object array_total_size(Object);
extern Object arrayp(Object);
extern Object ash(Object,Object);
extern Object assoc(int,...);
extern Object atom(Object);
extern Object bit(int,...);
extern Object both_case_p(Object);
extern Object boundp(Object);
extern Object breakn(int,...);
extern Object butlast(Object,Object);
extern Object byte(Object,Object);
extern Object byte_position(Object);
extern Object caaaar(Object);
extern Object caaadr(Object);
extern Object caaar(Object);
extern Object caadar(Object);
extern Object caaddr(Object);
extern Object caadr(Object);
extern Object caar(Object);
extern Object cadaar(Object);
extern Object cadadr(Object);
extern Object cadar(Object);
extern Object caddar(Object);
extern Object cadddr(Object);
extern Object caddr(Object);
extern Object cadr(Object);
extern Object car(Object);
extern Object cdaaar(Object);
extern Object cdaadr(Object);
extern Object cdaar(Object);
extern Object cdadar(Object);
extern Object cdaddr(Object);
extern Object cdadr(Object);
extern Object cdar(Object);
extern Object cddaar(Object);
extern Object cddadr(Object);
extern Object cddar(Object);
extern Object cdddar(Object);
extern Object cddddr(Object);
extern Object cdddr(Object);
extern Object cddr(Object);
extern Object cdr(Object);
extern Object ceiling(Object,Object);
extern Object cerrorn(int,...);
extern Object char_code(Object);
extern Object char_downcase(Object);
extern Object char_eqn(int,...);
extern Object char_equaln(int,...);
extern Object char_gen(int,...);
extern Object char_greaterpn(int,...);
extern Object char_gtn(int,...);
extern Object char_int(Object);
extern Object char_len(int,...);
extern Object char_lesspn(int,...);
extern Object char_ltn(int,...);
extern Object char_nen(int,...);
extern Object char_not_equaln(int,...);
extern Object char_upcase(Object);
extern Object character(Object);
extern Object characterp(Object);
extern Object clear_input(Object);
extern Object clrhash(Object);
extern Object code_char(Object);
extern Object coerce(Object,Object);
extern Object compiled_function_p(Object);
extern Object concatenate(int,...);
extern Object cons(Object,Object);
extern Object consp(Object);
extern Object constantp(Object,Object);
extern Object copy_list(Object);
extern Object copy_seq(Object);
extern Object copy_tree(Object);
extern Object count(int,...);
extern Object count_if(int,...);
extern Object decode_universal_time(Object,Object);
extern Object denominator(Object);
extern Object digit_char(Object,Object,Object);
extern Object digit_char_p(Object,Object);
extern Object dividen(int,...);
extern Object eighth(Object);
extern Object elt(Object,Object);
extern Object encode_universal_time(Object,Object,Object,Object,Object,Object,Object);
extern Object endp(Object);
extern Object eq(Object,Object);
extern Object eql(Object,Object);
extern Object equal(Object,Object);
extern Object equalp(Object,Object);
extern Object errorn(int,...);
extern Object evenp(Object);
extern Object every(int,...);
extern Object export(Object,Object);
extern Object expt(Object,Object);
extern Object fboundp(Object);
extern Object fceiling(Object,Object);
extern Object fifth(Object);
extern Object file_author(Object);
extern Object file_length(Object);
extern Object file_position(Object,Object);
extern Object file_write_date(Object);
extern Object fill(int,...);
extern Object fill_pointer(Object);
extern Object find(int,...);
extern Object find_if(int,...);
extern Object find_package(Object);
extern Object find_symbol(Object,Object);
extern Object first(Object);
extern Object floatp(Object);
extern Object fmakunbound(Object);
extern Object force_output(Object);
extern Object formatn(int,...);
extern Object fourth(Object);
extern Object fresh_line(Object);
extern Object fround(Object,Object);
extern Object functionp(Object);
extern Object gentemp(Object,Object);
extern Object get(Object,Object,Object);
extern Object get_decoded_time(void);
extern Object get_internal_real_time(void);
extern Object get_output_stream_string(Object);
extern Object get_universal_time(void);
extern Object getf(Object,Object,Object);
extern Object gethash(Object,Object,Object);
extern Object hash_table_count(Object);
extern Object identity(Object);
extern Object import(Object,Object);
extern Object integer_length(Object);
extern Object integerp(Object);
extern Object intern(Object,Object);
extern Object intersection(int,...);
extern Object isqrt(Object);
extern Object keywordp(Object);
extern Object l_abs(Object);
extern Object l_random(Object,Object);
extern Object l_round(Object,Object);
extern Object lasin(Object);
extern Object last(Object,Object);
extern Object latan(Object,Object);
extern Object lchar(Object,Object);
extern Object lclose(int,...);
extern Object lcos(Object);
extern Object ldb(Object,Object);
extern Object ldelete(int,...);
extern Object ldiff(Object,Object);
extern Object length(Object);
extern Object lexp(Object);
extern Object lffloor(Object,Object);
extern Object lfloat(Object,Object);
extern Object lfloor(Object,Object);
extern Object lftruncate(Object,Object);
extern Object lisp_implementation_version(void);
extern Object list(int,...);
extern Object list_length(Object);
extern Object list_star(int,...);
extern Object listp(Object);
extern Object llisten(Object);
extern Object llog(Object,Object);
extern Object logandc1(Object,Object);
extern Object logandc2(Object,Object);
extern Object logandn(int,...);
extern Object logbitp(Object,Object);
extern Object logcount(Object);
extern Object logiorn(int,...);
extern Object lognot(Object);
extern Object logtest(Object,Object);
extern Object logxorn(int,...);
extern Object lopen(int,...);
extern Object lower_case_p(Object);
extern Object lread(Object,Object,Object,Object);
extern Object lremove(int,...);
extern Object lsin(Object);
extern Object lsleep(Object);
extern Object lsqrt(Object);
extern Object ltan(Object);
extern Object ltruncate(Object,Object);
extern Object lunion(int,...);
extern Object lwrite(int,...);
extern Object macro_function(Object,Object);
extern Object macroexpand(Object,Object);
extern Object macroexpand_1(Object,Object);
extern Object make_array(int,...);
extern Object make_broadcast_stream(int,...);
extern Object make_hash_table(int,...);
extern Object make_list(int,...);
extern Object make_package(int,...);
extern Object make_string(int,...);
extern Object make_string_output_stream(void);
extern Object make_symbol(Object);
extern Object makunbound(Object);
extern Object map(int,...);
extern Object mapcan(int,...);
extern Object mapcar(int,...);
extern Object maphash(Object,Object);
extern Object maxn(int,...);
extern Object member(int,...);
extern Object merge(int,...);
extern Object minn(int,...);
extern Object minusn(int,...);
extern Object minusp(Object);
extern Object mismatch(int,...);
extern Object mod(Object,Object);
extern Object nbutlast(Object,Object);
extern Object nconc(int,...);
extern Object ninth(Object);
extern Object not(Object);
extern Object notany(int,...);
extern Object nreconc(Object,Object);
extern Object nreverse(Object);
extern Object nstring_downcase(int,...);
extern Object nstring_upcase(int,...);
extern Object nsubst(int,...);
extern Object nth(Object,Object);
extern Object nthcdr(Object,Object);
extern Object null(Object);
extern Object num_eqn(int,...);
extern Object num_gen(int,...);
extern Object num_gtn(int,...);
extern Object num_len(int,...);
extern Object num_ltn(int,...);
extern Object num_nen(int,...);
extern Object numberp(Object);
extern Object numerator(Object);
extern Object oddp(Object);
extern Object package_name(Object);
extern Object parse_integer(int,...);
extern Object peek_char(Object,Object,Object,Object,Object);
extern Object phase(Object);
extern Object plusp(Object);
extern Object position(int,...);
extern Object position_if(int,...);
extern Object position_if_not(int,...);
extern Object pprint(Object,Object);
extern Object prin1(Object,Object);
extern Object princ(Object,Object);
extern Object print(Object,Object);
extern Object rassoc(int,...);
extern Object read_byte(Object,Object,Object);
extern Object read_char(Object,Object,Object,Object);
extern Object read_char_no_hang(Object,Object,Object,Object);
extern Object read_from_string(int,...);
extern Object read_line(Object,Object,Object,Object);
extern Object rem(Object,Object);
extern Object remove_duplicates(int,...);
extern Object remove_if(int,...);
extern Object remove_if_not(int,...);
extern Object remprop(Object,Object);
extern Object replace(int,...);
extern Object rest(Object);
extern Object revappend(Object,Object);
extern Object reverse(Object);
extern Object room(Object);
extern Object rplaca(Object,Object);
extern Object rplacd(Object,Object);
extern Object sbit(int,...);
extern Object scale_float(Object,Object);
extern Object schar(Object,Object);
extern Object search(int,...);
extern Object second(Object);
extern Object set(Object,Object);
extern Object set_difference(int,...);
extern Object seventh(Object);
extern Object short_site_name(void);
extern Object simple_string_p(Object);
extern Object simple_vector_p(Object);
extern Object sixth(Object);
extern Object sort(int,...);
extern Object stable_sort(int,...);
extern Object streamp(Object);
extern Object string(Object);
extern Object string_capitalize(int,...);
extern Object string_downcase(int,...);
extern Object string_eq(int,...);
extern Object string_equal(int,...);
extern Object string_greaterp(int,...);
extern Object string_le(int,...);
extern Object string_lessp(int,...);
extern Object string_lt(int,...);
extern Object string_ne(int,...);
extern Object string_not_equal(int,...);
extern Object string_not_greaterp(int,...);
extern Object string_not_lessp(int,...);
extern Object string_trim(Object,Object);
extern Object string_upcase(int,...);
extern Object stringp(Object);
extern Object sub1(Object);
extern Object sublis(int,...);
extern Object subseq(Object,Object,Object);
extern Object subsetp(int,...);
extern Object subst(int,...);
extern Object substitute(int,...);
extern Object svref(Object,Object);
extern Object sxhash(Object);
extern Object symbol_function(Object);
extern Object symbol_name(Object);
extern Object symbol_package(Object);
extern Object symbol_plist(Object);
extern Object symbol_value(Object);
extern Object symbolp(Object);
extern Object tenth(Object);
extern Object terpri(Object);
extern Object third(Object);
extern Object timesn(int,...);
extern Object tree_equal(int,...);
extern Object type_of(Object);
extern Object typep(Object,Object,Object);
extern Object unintern(Object,Object);
extern Object unread_char(Object,Object);
extern Object upper_case_p(Object);
extern Object values(int,...);
extern Object values_list(Object);
extern Object vector(int,...);
extern Object vector_push(Object,Object);
extern Object vectorp(Object);
extern Object warnn(int,...);
extern Object write_byte(Object,Object);
extern Object write_char(Object,Object);
extern Object write_line(int,...);
extern Object write_string(int,...);
extern Object write_to_string(int,...);
extern Object zerop(Object);

#else

extern Object SETF_aref();
extern Object SETF_bit();
extern Object SETF_sbit();
extern Object add1();
extern Object addn();
extern Object adjoin();
extern Object alpha_char_p();
extern Object alphanumericp();
extern Object append();
extern Object apply();
extern Object aref();
extern Object array_dimension();
extern Object array_element_type();
extern Object array_has_fill_pointer_p();
extern Object array_rank();
extern Object array_total_size();
extern Object arrayp();
extern Object ash();
extern Object assoc();
extern Object atom();
extern Object bit();
extern Object both_case_p();
extern Object boundp();
extern Object breakn();
extern Object butlast();
extern Object byte();
extern Object byte_position();
extern Object caaaar();
extern Object caaadr();
extern Object caaar();
extern Object caadar();
extern Object caaddr();
extern Object caadr();
extern Object caar();
extern Object cadaar();
extern Object cadadr();
extern Object cadar();
extern Object caddar();
extern Object cadddr();
extern Object caddr();
extern Object cadr();
extern Object car();
extern Object cdaaar();
extern Object cdaadr();
extern Object cdaar();
extern Object cdadar();
extern Object cdaddr();
extern Object cdadr();
extern Object cdar();
extern Object cddaar();
extern Object cddadr();
extern Object cddar();
extern Object cdddar();
extern Object cddddr();
extern Object cdddr();
extern Object cddr();
extern Object cdr();
extern Object ceiling();
extern Object cerrorn();
extern Object char_code();
extern Object char_downcase();
extern Object char_eqn();
extern Object char_equaln();
extern Object char_gen();
extern Object char_greaterpn();
extern Object char_gtn();
extern Object char_int();
extern Object char_len();
extern Object char_lesspn();
extern Object char_ltn();
extern Object char_nen();
extern Object char_not_equaln();
extern Object char_upcase();
extern Object character();
extern Object characterp();
extern Object clear_input();
extern Object clrhash();
extern Object code_char();
extern Object coerce();
extern Object compiled_function_p();
extern Object concatenate();
extern Object cons();
extern Object consp();
extern Object constantp();
extern Object copy_list();
extern Object copy_seq();
extern Object copy_tree();
extern Object count();
extern Object count_if();
extern Object decode_universal_time();
extern Object denominator();
extern Object digit_char();
extern Object digit_char_p();
extern Object dividen();
extern Object eighth();
extern Object elt();
extern Object encode_universal_time();
extern Object endp();
extern Object eq();
extern Object eql();
extern Object equal();
extern Object equalp();
extern Object errorn();
extern Object evenp();
extern Object every();
extern Object export();
extern Object expt();
extern Object fboundp();
extern Object fceiling();
extern Object fifth();
extern Object file_author();
extern Object file_length();
extern Object file_position();
extern Object file_write_date();
extern Object fill();
extern Object fill_pointer();
extern Object find();
extern Object find_if();
extern Object find_package();
extern Object find_symbol();
extern Object first();
extern Object floatp();
extern Object fmakunbound();
extern Object force_output();
extern Object formatn();
extern Object fourth();
extern Object fresh_line();
extern Object fround();
extern Object functionp();
extern Object gentemp();
extern Object get();
extern Object get_decoded_time();
extern Object get_internal_real_time();
extern Object get_output_stream_string();
extern Object get_universal_time();
extern Object getf();
extern Object gethash();
extern Object hash_table_count();
extern Object identity();
extern Object import();
extern Object integer_length();
extern Object integerp();
extern Object intern();
extern Object intersection();
extern Object isqrt();
extern Object keywordp();
extern Object l_abs();
extern Object l_random();
extern Object l_round();
extern Object lasin();
extern Object last();
extern Object latan();
extern Object lchar();
extern Object lclose();
extern Object lcos();
extern Object ldb();
extern Object ldelete();
extern Object ldiff();
extern Object length();
extern Object lexp();
extern Object lffloor();
extern Object lfloat();
extern Object lfloor();
extern Object lftruncate();
extern Object lisp_implementation_version();
extern Object list();
extern Object list_length();
extern Object list_star();
extern Object listp();
extern Object llisten();
extern Object llog();
extern Object logandc1();
extern Object logandc2();
extern Object logandn();
extern Object logbitp();
extern Object logcount();
extern Object logiorn();
extern Object lognot();
extern Object logtest();
extern Object logxorn();
extern Object lopen();
extern Object lower_case_p();
extern Object lread();
extern Object lremove();
extern Object lsin();
extern Object lsleep();
extern Object lsqrt();
extern Object ltan();
extern Object ltruncate();
extern Object lunion();
extern Object lwrite();
extern Object macro_function();
extern Object macroexpand();
extern Object macroexpand_1();
extern Object make_array();
extern Object make_broadcast_stream();
extern Object make_hash_table();
extern Object make_list();
extern Object make_package();
extern Object make_string();
extern Object make_string_output_stream();
extern Object make_symbol();
extern Object makunbound();
extern Object map();
extern Object mapcan();
extern Object mapcar();
extern Object maphash();
extern Object maxn();
extern Object member();
extern Object merge();
extern Object minn();
extern Object minusn();
extern Object minusp();
extern Object mismatch();
extern Object mod();
extern Object nbutlast();
extern Object nconc();
extern Object ninth();
extern Object not();
extern Object notany();
extern Object nreconc();
extern Object nreverse();
extern Object nstring_downcase();
extern Object nstring_upcase();
extern Object nsubst();
extern Object nth();
extern Object nthcdr();
extern Object null();
extern Object num_eqn();
extern Object num_gen();
extern Object num_gtn();
extern Object num_len();
extern Object num_ltn();
extern Object num_nen();
extern Object numberp();
extern Object numerator();
extern Object oddp();
extern Object package_name();
extern Object parse_integer();
extern Object peek_char();
extern Object phase();
extern Object plusp();
extern Object position();
extern Object position_if();
extern Object position_if_not();
extern Object pprint();
extern Object prin1();
extern Object princ();
extern Object print();
extern Object rassoc();
extern Object read_byte();
extern Object read_char();
extern Object read_char_no_hang();
extern Object read_from_string();
extern Object read_line();
extern Object rem();
extern Object remove_duplicates();
extern Object remove_if();
extern Object remove_if_not();
extern Object remprop();
extern Object replace();
extern Object rest();
extern Object revappend();
extern Object reverse();
extern Object room();
extern Object rplaca();
extern Object rplacd();
extern Object sbit();
extern Object scale_float();
extern Object schar();
extern Object search();
extern Object second();
extern Object set();
extern Object set_difference();
extern Object seventh();
extern Object short_site_name();
extern Object simple_string_p();
extern Object simple_vector_p();
extern Object sixth();
extern Object sort();
extern Object stable_sort();
extern Object streamp();
extern Object string();
extern Object string_capitalize();
extern Object string_downcase();
extern Object string_eq();
extern Object string_equal();
extern Object string_greaterp();
extern Object string_le();
extern Object string_lessp();
extern Object string_lt();
extern Object string_ne();
extern Object string_not_equal();
extern Object string_not_greaterp();
extern Object string_not_lessp();
extern Object string_trim();
extern Object string_upcase();
extern Object stringp();
extern Object sub1();
extern Object sublis();
extern Object subseq();
extern Object subsetp();
extern Object subst();
extern Object substitute();
extern Object svref();
extern Object sxhash();
extern Object symbol_function();
extern Object symbol_name();
extern Object symbol_package();
extern Object symbol_plist();
extern Object symbol_value();
extern Object symbolp();
extern Object tenth();
extern Object terpri();
extern Object third();
extern Object timesn();
extern Object tree_equal();
extern Object type_of();
extern Object typep();
extern Object unintern();
extern Object unread_char();
extern Object upper_case_p();
extern Object values();
extern Object values_list();
extern Object vector();
extern Object vector_push();
extern Object vectorp();
extern Object warnn();
extern Object write_byte();
extern Object write_char();
extern Object write_line();
extern Object write_string();
extern Object write_to_string();
extern Object zerop();

#endif
