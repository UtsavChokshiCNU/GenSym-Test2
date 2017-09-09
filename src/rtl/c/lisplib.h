/*
 * lisplib.h - C kernel externs
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 */


#ifdef SI_VARIADIC_KEYWORD_FUNCTIONS
#define RESTORE_SI_VARIADIC_KEYWORD_FUNCTIONS
#undef SI_VARIADIC_KEYWORD_FUNCTIONS
#endif
#include "varkey.h"

/* See initfuns.h and initvars.h, for the functions and variables */
/* that are known to the translator. */

/* Chapter 13 - Characters */
/* extern Object Char_code_limit; */
extern Object Char_font_limit;
extern Object Char_bits_limit;
extern Object Char_control_bit;
extern Object Char_meta_bit;
extern Object Char_super_bit;
extern Object Char_hyper_bit;

/* Chapter 20 - The Evaluator */
extern Object Eval_hook;
extern Object Apply_hook;

/* Chapter 24 - Errors */
extern Object Break_on_warnings;

/* Chapter 25 - Miscellaneous Features */
extern Object Time_zone;

/* Global Variables */
extern Object List_of_packages;
extern Object Modules;
extern Object Standard_readtable;

/* Constants */
extern Object Most_positive_fixnum;
extern Object Most_negative_fixnum;
extern Object Lambda_parameters_limit;

/*
extern Object Multiple_values_limit;
extern Object Call_arguments_limit;
extern Object Array_rank_limit;
extern Object Array_dimension_limit;
extern Object Array_total_size_limit;
extern Object Boole_clr;
extern Object Boole_and;
extern Object Boole_andc1;
extern Object Boole_2;
extern Object Boole_andc2;
extern Object Boole_1;
extern Object Boole_xor;
extern Object Boole_ior;
extern Object Boole_nor;
extern Object Boole_eqv;
extern Object Boole_c1;
extern Object Boole_orc1;
extern Object Boole_c2;
extern Object Boole_orc2;
extern Object Boole_nand;
extern Object Boole_set;
*/

/*
 * Advertized language extensions
 */

extern Object Area_overflow_function;


#ifdef USE_PROTOTYPES

/* Chapter 6 - Predicates */
extern Object commonp(Object object);

/* Chapter 7 - Control structure */
#if SI_SUPPORT_CLOS == 0
extern Object funcall0(Object func);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern Object funcall3(Object func, Object arg1, Object arg2, Object arg3);
#endif
extern Object apply1(Object func, Object arglist);
extern Object apply2(Object func, Object arg1, Object arglist);
extern Object apply3(Object func, Object arg1, Object arg2, Object arglist);
extern Object list_values(Object x);
extern Object multiple_value_list_n(Object n, Object value1);

/* Chapter 8 - Macros */

/* Chapter 9 - Declarations */
extern Object proclaim(Object decl_spec);

/* Chapter 10 - Symbols */

/* Chapter 11 - Packages */
/*
extern Object do_symbols_start();
extern Object do_symbols_next();
extern Object do_external_symbols_start();
extern Object do_external_symbols_next();
extern Object do_all_symbols_start();
extern Object do_all_symbols_next();
extern Object unexport();
extern Object shadowing_import();
extern Object shadow();
extern Object unuse_package();
extern Object provide();
extern Object require();
*/
extern Object in_package(Object pkg_name, Object nicknames, Object uses);
extern Object unintern(Object symbol, Object pkg);
extern Object find_all_symbols(Object x1);
extern Object set_use_list(Object pkg, Object use_list);
extern Object set_used_by_list(Object pkg, Object used_by_list);
extern Object set_nicknames(Object pkg, Object nicknames);
extern Object set_shadowing_symbols(Object pkg, Object shadowing_symbols);

/* Chapter 12 - Numbers */
extern Object num_eq(Object a, Object b);
extern Object num_eqr(Object a, Object b);
extern Object num_ne(Object a, Object b);
extern Object num_ner(Object a, Object b);
extern Object num_lt(Object a, Object b);
extern Object num_ltr(Object a, Object b);
extern Object num_gt(Object a, Object b);
extern Object num_gtr(Object a, Object b);
extern Object num_le(Object a, Object b);
extern Object num_ler(Object a, Object b);
extern Object num_ge(Object a, Object b);
extern Object num_ger(Object a, Object b);
extern Object lmax(Object a, Object b);
extern Object lmaxr(Object a, Object b);
extern Object lmin(Object a, Object b);
extern Object lminr(Object a, Object b);
extern Object add(Object a, Object b);
extern Object addr(Object a);
extern Object negate(Object a);
extern Object minus(Object a, Object b);
extern Object minusr(Object a, Object b);
extern Object ltimes(Object a, Object b);
extern Object timesr(Object a);
extern Object divide(Object a, Object b);
extern Object divider(Object a, Object b);
extern Object conjugate(Object a);
extern Object gcd(Object a, Object b);
extern Object gcdr(Object a);
extern Object lcm(Object a, Object b);
extern Object lcmr(Object a);
extern Object lfloor_1(Object x, Object y);
extern Object logior(Object a, Object b);
extern Object logiorr(Object a);
extern Object logxor(Object a, Object b);
extern Object logxorr(Object a);
extern Object logand(Object a, Object b);
extern Object logandr(Object a);
extern Object logeqv(Object a, Object b);
extern Object logeqvr(Object a);
extern Object reciprocal(Object x);

/* Chapter 13 - Characters */
extern Object whitespace_char_p(Object c);
extern Object string_char_p(Object c);
extern Object char_eq(Object a, Object b);
extern Object char_eqr(Object a, Object b);
extern Object char_ne(Object a, Object b);
extern Object char_ner(Object a, Object b);
extern Object char_lt(Object a, Object b);
extern Object char_ltr(Object a, Object b);
extern Object char_gt(Object a, Object b);
extern Object char_gtr(Object a, Object b);
extern Object char_le(Object a, Object b);
extern Object char_ler(Object a, Object b);
extern Object char_ge(Object a, Object b);
extern Object char_ger(Object a, Object b);
extern Object char_equal(Object a, Object b);
extern Object char_equalr(Object a, Object b);
extern Object char_not_equal(Object a, Object b);
extern Object char_not_equalr(Object a, Object b);
extern Object char_lessp(Object a, Object b);
extern Object char_lesspr(Object a, Object b);
extern Object char_greaterp(Object a, Object b);
extern Object char_greaterpr(Object a, Object b);
extern Object char_not_greaterp(Object a, Object b);
extern Object char_not_greaterpr(Object a, Object b);
extern Object char_not_lessp(Object a, Object b);
extern Object char_not_lesspr(Object a, Object b);
extern Object char_bits(Object c);
extern Object char_font(Object c);
extern Object make_char(Object c, Object bits, Object font);
extern Object int_char(Object n);
extern Object char_bit(Object c, Object bitname);
extern Object set_char_bit(Object c, Object name, Object newvalue);

/* Chapter 14 - Sequences */
extern Object set_subseq(Object x1, Object x2, Object x3, Object x4);
extern Object set_subseq1(Object seq, Object lstart, Object new_seq);
extern Object set_subseq2(Object seq, Object lstart, Object lend, 
			  Object new_seq);
extern long ilength(Object sequence);

/* Chapter 15 - Lists */
extern Object ncons1(Object a);
extern Object m_nthcdr(long n, Object list);
extern Object nconc2(Object list1, Object list2);
extern Object member_se(Object item, Object list, 
			Object test, Object test_not, Object key, 
			Object start, Object end);  /* support function */
extern Object member_odd(Object v, Object l);

extern Object member_eq(Object item, Object list);
extern Object member_eql(Object item, Object list);
extern Object member_equal(Object item, Object list);
extern Object assoc_eq(Object key, Object alist);
extern Object assoc_eql(Object key, Object alist);
extern Object assoc_equal(Object key, Object alist);
extern Object delete_eq(Object item, Object list);
extern Object delete_eql(Object item, Object list);
extern Object delete_equal(Object item, Object list);

/* Chapter 16 - Hash Tables */
extern Object sethash(Object key, Object hash_table, Object value, 
		      Object ignore);

/* Chapter 17 - Arrays */
extern Object make_vector(Object size, Object initial_element);  /* ext */

extern Object aref0(Object arr);
extern Object aref1(Object arr, Object s1);
extern Object aref2(Object arr, Object s1, Object s2);
extern Object aref3(Object arr, Object s1, Object s2, Object s3);
extern Object aref4(Object arr, Object s1, Object s2, Object s3, Object s4);
extern Object aref5(Object arr, Object s1, Object s2, Object s3, Object s4, 
		    Object s5);
extern Object aref6(Object arr, Object s1, Object s2, Object s3, Object s4, 
		    Object s5, Object s6);
extern Object aref7(Object arr, Object s1, Object s2, Object s3, Object s4, 
		    Object s5, Object s6, Object s7);
extern Object set_aref0(Object arr, Object new_elem);
extern Object set_aref1(Object a, Object i, Object v);
extern Object set_aref2(Object a, Object i1, Object i2, Object v);
extern Object set_aref3(Object arr, Object s1, Object s2, Object s3, 
			Object new_elem);
extern Object set_aref4(Object arr, Object s1, Object s2, Object s3, 
			Object s4, Object new_elem);
extern Object set_aref5(Object arr, Object s1, Object s2, Object s3, 
			Object s4, Object s5, Object new_elem);
extern Object set_aref6(Object arr, Object s1, Object s2, Object s3, 
			Object s4, Object s5, Object s6, Object new_elem);
extern Object set_aref7(Object arr, Object s1, Object s2, Object s3, 
			Object s4, Object s5, Object s6, Object s7, 
			Object new_elem);


extern Object setf_fill_pointer(Object arr, Object fillptr);

/* Chapter 18 - Strings */

/* Chapter 20 - The Evaluator */
extern Object evalhook(Object form, 
		       Object evalhookfn, Object applyhookfn, Object env);
extern Object applyhook(Object function, Object args, 
			Object evalhookfn, Object applyhookfn, Object env);

/* Chapter 21 - Streams */
extern Object make_synonym_stream(Object symbol);

/* Chapter 22 - Input/Output */
extern Object make_dispatch_macro_character(Object x1);
extern Object get_dispatch_macro_character(Object disp_char, Object sub_char,
					   Object readtable);
extern Object set_dispatch_macro_character(Object disp_char, Object sub_char,
					   Object func, Object readtable);
extern Object format(int n, Object destination, char *control_string, ...);
extern Object y_or_n_p(int n, char *format_string, ...);
extern Object yes_or_no_p(int n, char *format_string, ...);

/* Chapter 23 - File System Interface */
extern Object load(Object filename, Object verbose, Object printarg, 
		   Object if_does_not_exist);

/* Chapter 24 - Errors */
extern Object warn(int n, char *lstr, ...);
extern Object lbreak(int n, char *lstr, ...);
extern Object list_error(Object obj);
extern Object error(int n, char *lstr, ...);
extern Object cerror(int n, char *cstr, char *estr, ...);

/* Chapter 25 - Miscellaneous Features */
extern Object compile(char *, char *, char *);
extern Object inspect(Object object);
extern Object describe(Object object);
extern Object machine_type(void);
extern Object machine_version(void);
extern Object machine_instance(void);
extern Object software_version(void);
/*
extern Object compile_file();
extern Object disassemble();
extern Object ed();
extern Object dribble();
extern Object apropos();
extern Object apropos_list();
extern Object software_type();
*/

/*
 * Advertized language extensions
 */

extern Object total_memory_allocatable(void);


#ifdef GCLISP
extern Object file_info(Object pathnm);
#endif
extern Object lexit(Object code);		/* ? */
extern Object PCTpointer(Object object);	/* every Lisp's favorite extension */

/* Lucid extension */
extern Object string_append2(Object a, Object b);
extern Object string_appendr(Object sequences);

/*
 * Called from init.c
 */

extern void init_heaps(void);
extern void initsyms_top_level(void);
extern void backquot_top_level(void);
extern void heap_command_line(int argc, char **argv);

/*
 * Auxiliary functions and variables required by translated C code or C
 * macros or used internally in runtime library
 */

extern Object make_structure(long n, ...);

/* coerce.c */
extern Object clong_to_bignum(SI_Long a);
extern double object_to_cdouble(Object n);
extern Object cdouble_to_double(double a);
extern Object clong_to_int64(SI_Long a);
extern Object cint64_to_int64(SI_int64 a);
extern SI_int64 integer_to_int64(Object n);

/* heap.c */

/* numbers.c */

extern SI_Long expt_long(SI_Long x, SI_Long y);
extern int logcount_long(SI_Long a);


/* non-variadic versions of variadic keyword functions */
extern Object adjoin(Object item, Object list, Object test, Object test_not,
		     Object key);
extern Object adjust_array(Object array, Object new_dimensions,
			   Object element_type, Object initial_element,
			   Object initial_contents, Object fill_pointer,
			   Object displaced_to, Object displaced_index_offset);
extern Object assoc(Object item, Object a_list,
		    Object test, Object test_not, Object key);
extern Object assoc_if(Object pred, Object a_list, Object key);
extern Object assoc_if_not(Object pred, Object a_list, Object key);
extern Object lclose(Object stream, Object abort);
extern Object count(Object item, Object seq, Object from_end,
		    Object test, Object test_not,
		    Object lstart, Object lend, Object key);
extern Object count_if(Object test, Object seq, Object from_end,
		       Object lstart, Object lend, Object key);
extern Object count_if_not(Object test, Object seq, Object from_end,
			   Object lstart, Object lend, Object key);
extern Object ldelete(Object item, Object seq, Object from_end,
		      Object test, Object test_not,
		      Object lstart, Object lend,
		      Object lcount, Object key);
extern Object delete_duplicates(Object seq, Object from_end,
				Object test, Object test_not,
				Object lstart, Object lend, Object key);
extern Object delete_if(Object test, Object seq, Object from_end,
			Object start, Object end,
			Object count, Object key);
extern Object delete_if_not(Object test, Object seq, Object from_end,
			    Object start, Object end,
			    Object count, Object key);
extern Object fill(Object seq, Object item, Object lstart, Object lend);
extern Object find(Object item, Object seq, Object from_end, Object test,
		   Object test_not, Object lstart, Object lend, Object key);
extern Object find_if(Object test, Object seq, Object from_end,
		      Object lstart, Object lend, Object key);
extern Object find_if_not(Object test, Object seq, Object from_end,
			  Object lstart, Object lend, Object key);
extern Object intersection(Object list1, Object list2, Object test,
			   Object test_not, Object key);
extern Object load_run(Object filename, Object verbose, Object printarg,
		       Object if_does_not_exist);
extern Object make_array(Object dimensions, Object element_type,
			 Object initial_element, Object initial_contents,
			 Object adjustable, Object fill_pointer,
			 Object displaced_to, Object displaced_index_offset);
extern Object make_malloced_array(long length);
extern Object make_malloced_string(long length);
extern Object free_malloced_array_internal(Object array);
extern Object make_hash_table(Object test, Object size, Object rehash_size,
			      Object rehash_threshold);
extern Object make_list(Object lsize, Object initial_element);
extern Object make_package(Object pkg_name, Object nicknames, Object use);
extern Object make_pathname(Object host, Object device, Object directory,
			    Object name, Object type, Object version,
			    Object defaults);
extern Object make_sequence(Object type, Object lsize, Object initial_element);
extern Object make_string(Object size, Object initial_element);
extern Object member(Object item, Object list,
		     Object test, Object test_not, Object key);
extern Object member_if(Object pred, Object list, Object key);
extern Object member_if_not(Object pred, Object list, Object key);
extern Object merge(Object result_type, Object seq1, Object seq2, Object pred,
		    Object key);
extern Object mismatch(Object seq1, Object seq2, Object from_end,
		       Object test, Object test_not, Object key,
		       Object lstart1, Object lstart2,
		       Object lend1, Object lend2);
extern Object nintersection(Object list1, Object list2,
			    Object test, Object test_not, Object key);
extern Object nset_difference(Object list1, Object list2,
			      Object test, Object test_not, Object key);
extern Object nset_exclusive_or(Object list1, Object list2,
				Object test, Object test_not, Object key);
extern Object nstring_capitalize(Object str, Object start, Object end);
extern Object nstring_downcase(Object str, Object start, Object end);
extern Object nstring_upcase(Object str, Object start, Object end);
extern Object nsublis(Object alist, Object tree,
		      Object test, Object test_not, Object key);
extern Object nsubst(Object aNew, Object old, Object tree,
		     Object test, Object test_not, Object key);
extern Object nsubst_if(Object aNew, Object test, Object tree, Object key);
extern Object nsubst_if_not(Object aNew, Object test, Object tree, Object key);
extern Object nsubstitute(Object newitem, Object olditem, Object seq,
			  Object from_end, Object test, Object test_not,
			  Object lstart, Object lend, Object lcount,
			  Object key);
extern Object nsubstitute_if(Object newitem, Object test, Object seq,
			     Object from_end, Object lstart, Object lend,
			     Object lcount, Object key);
extern Object nsubstitute_if_not(Object newitem, Object test, Object seq,
				 Object from_end, Object lstart, Object lend,
				 Object lcount, Object key);
extern Object nunion(Object list1, Object list2,
		     Object test, Object test_not, Object key);
extern Object lopen(Object filename, Object direction, Object element_type,
		    Object if_exists, Object if_does_not_exist);
extern Object parse_integer(Object string, Object start, Object end,
			    Object radix, Object junk_allowed);
extern Object parse_namestring(Object thing, Object host, Object defaults,
			       Object start, Object end, Object junk_allowed);
extern Object position(Object item, Object seq, Object from_end,
		       Object test, Object test_not,
		       Object lstart, Object lend, Object key);
extern Object position_if(Object test, Object seq, Object from_end,
			  Object lstart, Object lend, Object key);
extern Object position_if_not(Object test, Object seq, Object from_end,
			      Object lstart, Object lend, Object key);
extern Object rassoc(Object item, Object a_list,
		     Object test, Object test_not, Object key);
extern Object rassoc_if(Object pred, Object a_list, Object key);
extern Object rassoc_if_not(Object pred, Object a_list, Object key);
extern Object read_from_string(Object string, Object eof_error_p,
			       Object eof_value, Object start, Object end,
			       Object preserve_whitespace);
extern Object reduce(Object function, Object sequence, Object from_end,
		     Object lstart, Object lend, Object initial_value);
extern Object lremove(Object item, Object seq, Object from_end,
		      Object test, Object test_not,
		      Object lstart, Object lend,
		      Object lcount, Object key);
extern Object remove_duplicates(Object seq, Object from_end,
				Object test, Object test_not,
				Object lstart, Object lend,
				Object key);
extern Object remove_if(Object test, Object sequence, Object from_end,
			Object start, Object end, Object count, Object key);
extern Object remove_if_not(Object test, Object sequence, Object from_end,
			    Object start, Object end, Object count,
			    Object key);
extern Object replace(Object sequence1, Object sequence2,
		      Object lstart1, Object lend1,
		      Object lstart2, Object lend2);
extern Object search(Object seq1, Object seq2, Object from_end,
		     Object test, Object test_not, Object key,
		     Object lstart1, Object lstart2,
		     Object lend1, Object lend2);
extern Object set_difference(Object list1, Object list2,
			     Object test, Object test_not, Object key);
extern Object set_exclusive_or(Object list1, Object list2,
			       Object test, Object test_not, Object key);
extern Object sort(Object seq, Object pred, Object key);
extern Object stable_sort(Object seq, Object pred, Object key);
extern Object string_capitalize(Object str, Object start, Object end);
extern Object string_downcase(Object str, Object start, Object end);
extern Object string_equal(Object string1, Object string2,
			   Object start1, Object end1,
			   Object start2, Object end2);
extern Object string_greaterp(Object string1, Object string2,
			      Object start1, Object end1,
			      Object start2, Object end2);
extern Object string_lessp(Object string1, Object string2,
			   Object start1, Object end1,
			   Object start2, Object end2);
extern Object string_not_equal(Object string1, Object string2,
			       Object start1, Object end1,
			       Object start2, Object end2);
extern Object string_not_greaterp(Object string1, Object string2,
				  Object start1, Object end1,
				  Object start2, Object end2);
extern Object string_not_lessp(Object string1, Object string2,
			       Object start1, Object end1,
			       Object start2, Object end2);
extern Object string_upcase(Object str, Object start, Object end);
extern Object string_ne(Object string1, Object string2,
			Object start1, Object end1,
			Object start2, Object end2);
extern Object string_lt(Object string1, Object string2,
			Object start1, Object end1,
			Object start2, Object end2);
extern Object string_le(Object string1, Object string2,
			Object start1, Object end1,
			Object start2, Object end2);
extern Object string_eq(Object string1, Object string2,
			Object start1, Object end1,
			Object start2, Object end2);
extern Object string_gt(Object string1, Object string2,
			Object start1, Object end1,
			Object start2, Object end2);
extern Object string_ge(Object string1, Object string2,
			Object start1, Object end1,
			Object start2, Object end2);
extern Object sublis(Object alist, Object tree,
		     Object test, Object test_not,
		     Object key);
extern Object subsetp(Object list1, Object list2,
		      Object test, Object test_not, Object key);
extern Object subst(Object aNew, Object old, Object tree,
		    Object test, Object test_not, Object key);
extern Object subst_if(Object aNew, Object test, Object tree, Object key);
extern Object subst_if_not(Object aNew, Object test, Object tree, Object key);
extern Object substitute(Object newitem, Object olditem, Object seq,
			 Object from_end,
			 Object test, Object test_not,
			 Object lstart, Object lend, Object lcount,
			 Object key);
extern Object substitute_if(Object newitem, Object test, Object seq,
			    Object from_end, Object start, Object end,
			    Object count, Object key);
extern Object substitute_if_not(Object newitem, Object test, Object seq,
				Object from_end, Object start, Object end,
				Object count, Object key);
extern Object tree_equal(Object x, Object y, Object test, Object test_not);
extern Object lunion(Object list1, Object list2,
		     Object test, Object test_not, Object key);
extern Object lwrite(Object object, Object stream, Object pescape,
		     Object pradix, Object pbase, Object pcircle,
		     Object ppretty, Object plevel, Object plength,
		     Object pcase, Object pgensym, Object parray);
extern Object write_line(Object string, Object output_stream,
			 Object start, Object end);
extern Object write_string(Object string, Object output_stream,
			   Object start, Object end);
extern Object write_to_string(Object object, Object pescape, Object pradix,
			      Object pbase, Object pcircle, Object ppretty,
			      Object plevel, Object plength, Object pcase,
			      Object pgensym, Object parray);

#else

/* Chapter 6 - Predicates */
extern Object commonp();

/* Chapter 7 - Control structure */
#if SI_SUPPORT_CLOS == 0
extern Object funcall0();
extern Object funcall1();
extern Object funcall2();
extern Object funcall3();
#endif
extern Object apply1();
extern Object apply2();
extern Object apply3();
extern Object multiple_value_list_n();

/* Chapter 8 - Macros */

/* Chapter 9 - Declarations */
extern Object proclaim();

/* Chapter 10 - Symbols */

/* Chapter 11 - Packages */
/*
extern Object do_symbols_start();
extern Object do_symbols_next();
extern Object do_external_symbols_start();
extern Object do_external_symbols_next();
extern Object do_all_symbols_start();
extern Object do_all_symbols_next();
extern Object unexport();
extern Object shadowing_import();
extern Object shadow();
extern Object unuse_package();
extern Object provide();
extern Object require();
*/
extern Object in_package();
extern Object unintern();
extern Object find_all_symbols();
extern Object set_use_list();
extern Object set_used_by_list();
extern Object set_nicknames();
extern Object set_shadowing_symbols();

/* Chapter 12 - Numbers */
extern Object num_eq();
extern Object num_eqr();
extern Object num_ne();
extern Object num_ner();
extern Object num_lt();
extern Object num_ltr();
extern Object num_gt();
extern Object num_gtr();
extern Object num_le();
extern Object num_ler();
extern Object num_ge();
extern Object num_ger();
extern Object lmax();
extern Object lmaxr();
extern Object lmin();
extern Object lminr();
extern Object add();
extern Object addr();
extern Object negate();
extern Object minus();
extern Object minusr();
extern Object ltimes();
extern Object timesr();
extern Object divide();
extern Object divider();
extern Object conjugate();
extern Object gcd();
extern Object gcdr();
extern Object lcm();
extern Object lcmr();
extern Object lfloor_1();
extern Object logior();
extern Object logiorr();
extern Object logxor();
extern Object logxorr();
extern Object logand();
extern Object logandr();
extern Object logeqv();
extern Object logeqvr();
extern Object reciprocal();

/* Chapter 13 - Characters */
extern Object whitespace_char_p();
extern Object string_char_p();
extern Object char_eq();
extern Object char_eqr();
extern Object char_ne();
extern Object char_ner();
extern Object char_lt();
extern Object char_ltr();
extern Object char_gt();
extern Object char_gtr();
extern Object char_le();
extern Object char_ler();
extern Object char_ge();
extern Object char_ger();
extern Object char_equal();
extern Object char_equalr();
extern Object char_not_equal();
extern Object char_not_equalr();
extern Object char_lessp();
extern Object char_lesspr();
extern Object char_greaterp();
extern Object char_greaterpr();
extern Object char_not_greaterp();
extern Object char_not_greaterpr();
extern Object char_not_lessp();
extern Object char_not_lesspr();
extern Object char_bits();
extern Object char_font();
extern Object make_char();
extern Object int_char();
extern Object char_bit();
extern Object set_char_bit();

/* Chapter 14 - Sequences */
extern Object set_subseq();
extern Object set_subseq1();
extern Object set_subseq2();
extern long ilength();

/* Chapter 15 - Lists */
extern Object ncons1();
extern Object m_nthcdr();
extern Object nconc2();
extern Object member_se();  /* support function */
extern Object member_odd();

extern Object member_eq();
extern Object member_eql();
extern Object member_equal();
extern Object assoc_eq();
extern Object assoc_eql();
extern Object assoc_equal();
extern Object delete_eq();
extern Object delete_eql();
extern Object delete_equal();

/* Chapter 16 - Hash Tables */
extern Object sethash();

/* Chapter 17 - Arrays */
extern Object make_vector();  /* ext */

extern Object aref0();
extern Object aref1();
extern Object aref2();
extern Object aref3();
extern Object aref4();
extern Object aref5();
extern Object aref6();
extern Object aref7();
extern Object set_aref0();
extern Object set_aref1();
extern Object set_aref2();
extern Object set_aref3();
extern Object set_aref4();
extern Object set_aref5();
extern Object set_aref6();
extern Object set_aref7();


extern Object setf_fill_pointer();

/* Chapter 18 - Strings */

/* Chapter 20 - The Evaluator */
extern Object evalhook();
extern Object applyhook();

/* Chapter 21 - Streams */
extern Object make_synonym_stream();

/* Chapter 22 - Input/Output */
extern Object make_dispatch_macro_character();
extern Object get_dispatch_macro_character();
extern Object set_dispatch_macro_character();
extern Object format();
extern Object y_or_n_p();
extern Object yes_or_no_p();

/* Chapter 23 - File System Interface */
extern Object load();

/* Chapter 24 - Errors */
extern Object warn();
extern Object lbreak();
extern Object list_error();
extern Object error();
extern Object cerror();

/* Chapter 25 - Miscellaneous Features */
extern Object compile();
extern Object inspect();
extern Object describe();
extern Object machine_type();
extern Object machine_version();
extern Object machine_instance();
extern Object software_version();
/*
extern Object compile_file();
extern Object disassemble();
extern Object ed();
extern Object dribble();
extern Object apropos();
extern Object apropos_list();
extern Object software_type();
*/

/*
 * Advertized language extensions
 */

extern Object total_memory_allocatable();


#ifdef GCLISP
extern Object file_info();
#endif
extern Object lexit();		/* ? */
extern Object PCTpointer();	/* every Lisp's favorite extension */

/* Lucid extension */
extern Object string_append2();
extern Object string_appendr();

/*
 * Called from init.c
 */

extern void init_heaps();
extern void initsyms_top_level();
extern void backquot_top_level();
extern void heap_command_line();

/*
 * Auxiliary functions and variables required by translated C code or C
 * macros or used internally in runtime library
 */

extern Object make_structure();

/* coerce.c */
extern Object clong_to_bignum();
extern double object_to_cdouble();
extern Object cdouble_to_double();
extern Object clong_to_int64();
extern Object cint64_to_int64();
extern SI_int64 integer_to_int64();

/* heap.c */

/* numbers.c */

extern SI_Long expt_long();
extern int logcount_long();


/* non-variadic versions of variadic keyword functions */
extern Object adjoin();
extern Object adjust_array();
extern Object assoc();
extern Object assoc_if();
extern Object assoc_if_not();
extern Object lclose();
extern Object count();
extern Object count_if();
extern Object count_if_not();
extern Object ldelete();
extern Object delete_duplicates();
extern Object delete_if();
extern Object delete_if_not();
extern Object fill();
extern Object find();
extern Object find_if();
extern Object find_if_not();
extern Object intersection();
extern Object load_run();
extern Object make_array();
extern Object make_malloced_array();
extern Object make_malloced_string();
extern void   free_malloced_array_internal();
extern Object make_hash_table();
extern Object make_list();
extern Object make_package();
extern Object make_pathname();
extern Object make_sequence();
extern Object make_string();
extern Object member();
extern Object member_if();
extern Object member_if_not();
extern Object merge();
extern Object mismatch();
extern Object nintersection();
extern Object nset_difference();
extern Object nset_exclusive_or();
extern Object nstring_capitalize();
extern Object nstring_downcase();
extern Object nstring_upcase();
extern Object nsublis();
extern Object nsubst();
extern Object nsubst_if();
extern Object nsubst_if_not();
extern Object nsubstitute();
extern Object nsubstitute_if();
extern Object nsubstitute_if_not();
extern Object nunion();
extern Object lopen();
extern Object parse_integer();
extern Object parse_namestring();
extern Object position();
extern Object position_if();
extern Object position_if_not();
extern Object rassoc();
extern Object rassoc_if();
extern Object rassoc_if_not();
extern Object read_from_string();
extern Object reduce();
extern Object lremove();
extern Object remove_duplicates();
extern Object remove_if();
extern Object remove_if_not();
extern Object replace();
extern Object search();
extern Object set_difference();
extern Object set_exclusive_or();
extern Object sort();
extern Object stable_sort();
extern Object string_capitalize();
extern Object string_downcase();
extern Object string_equal();
extern Object string_greaterp();
extern Object string_lessp();
extern Object string_not_equal();
extern Object string_not_greaterp();
extern Object string_not_lessp();
extern Object string_upcase();
extern Object string_ne();
extern Object string_lt();
extern Object string_le();
extern Object string_eq();
extern Object string_gt();
extern Object string_ge();
extern Object sublis();
extern Object subsetp();
extern Object subst();
extern Object subst_if();
extern Object subst_if_not();
extern Object substitute();
extern Object substitute_if();
extern Object substitute_if_not();
extern Object tree_equal();
extern Object lunion();
extern Object lwrite();
extern Object write_line();
extern Object write_string();
extern Object write_to_string();

#endif

#ifdef RESTORE_SI_VARIADIC_KEYWORD_FUNCTIONS
#define SI_VARIADIC_KEYWORD_FUNCTIONS
#endif
#include "varkey.h"
