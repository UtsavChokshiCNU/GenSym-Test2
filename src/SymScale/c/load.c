/* load.c
 * Input file:  load.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "load.h"


DEFINE_VARIABLE_WITH_SYMBOL(ab_Dummy_var, Qab_dummy_var);

DEFINE_VARIABLE_WITH_SYMBOL(User_package_in_this_lisp, Quser_package_in_this_lisp);

DEFINE_VARIABLE_WITH_SYMBOL(List_for_import, Qlist_for_import);

DEFINE_VARIABLE_WITH_SYMBOL(Bootstrap_information, Qbootstrap_information);

DEFINE_VARIABLE_WITH_SYMBOL(Ab_system_pathname, Qab_system_pathname);

Object File_naming_spin_id = UNBOUND;

Object File_naming_specific_source_directory = UNBOUND;

Object File_naming_specific_dest_directory = UNBOUND;

Object File_naming_tools_directory = UNBOUND;

Object Default_sandbox_location = UNBOUND;

Object Default_spin_id = UNBOUND;

Object Default_sandbox_name = UNBOUND;

Object Source_directory_name = UNBOUND;

Object Dest_directory_name = UNBOUND;

Object Toolsdir_name = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Fasl_extension, Qfasl_extension);

/* USE-DATES-INSTEAD-OF-VERSIONS-P */
Object use_dates_instead_of_versions_p()
{
    x_note_fn_call(0,0);
    return VALUES_1( !TRUEP(SIXTH(Bootstrap_information)) ? T : Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Lisp_memory_expanded_qm, Qlisp_memory_expanded_qm);

void load_INIT()
{
    Object tcl_user_ab_package_name, tcl_user_ab_package_use_list;
    Object tcl_user_extant_ab_package_qm, list0, result_1, last_1, temp;
    Object new_last, tcl_user_extant_ab_package_use_list;
    Object star_features_star_new_value, symbol_from_ab_package;
    Object package_of_symbol;
    Object list_constant_19, Qdowncase, string_constant_15, string_constant_14;
    Object string_constant_13, AB_package, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_2, Kvanilla, Kno_macros, string_constant_5;
    Object string_constant_4, string_constant_1, string_constant_3;
    Object list_constant_18, list_constant_17, list_constant_16;
    Object list_constant_15, list_constant_14, list_constant_13;
    Object list_constant_12, list_constant_11, list_constant_10;
    Object list_constant_9, list_constant_8, list_constant_7, list_constant_6;
    Object list_constant_5, list_constant_4, list_constant_3, list_constant_2;
    Object list_constant_1, list_constant, string_constant;

    x_note_fn_call(0,1);
    SET_PACKAGE("TCL-USER");
    if (ab_Dummy_var == UNBOUND)
	ab_Dummy_var = adjust_area_target_sizes(FIX((SI_Long)3300L),
		FIX((SI_Long)4750L),"AB");
    string_constant_1 = STATIC_STRING("AB-LISP");
    string_constant = STATIC_STRING("TCL");
    list_constant = STATIC_CONS(string_constant,Qnil);
    if ( !TRUEP(find_package(string_constant_1)))
	make_package(5,string_constant_1,Knicknames,Nil,Kuse,list_constant);
    list_constant_1 = STATIC_CONS(Qzerop,Qnil);
    list_constant_2 = STATIC_LIST_STAR((SI_Long)32L,Qtruncate,Qtype,
	    Qtype_of,Qtypecase,Qtypep,Qsigned_byte,Qunion,Qunintern,
	    Qunless,Qunread_char,Qunsigned_byte,Quntrace,Qupper_case_p,
	    Qvalues,Qvalues_list,Qvariable,Qvector,Qvectorp,Qvector_push,
	    Qwarn,Qwhen,Qwith_open_file,Qwith_open_stream,
	    Qwith_output_to_string,Qwith_input_from_string,Qwrite,
	    Qwrite_byte,Qwrite_char,Qwrite_line,Qwrite_string,
	    Qwrite_to_string,list_constant_1);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)32L,Qstring_upcase,
	    Qstring_ne,Qstring_lt,Qstring_le,Qstring_eq,Qstringp,Qsublis,
	    Qsubseq,Qsubsetp,Qsubst,Qsubstitute,Qsvref,Qsxhash,Qsymbol,
	    Qsymbol_function,Qsymbol_name,Qsymbol_package,Qsymbol_plist,
	    Qsymbol_value,Qsymbolp,Qt,Qtagbody,Qtan,Qtenth,Qterpri,Qthe,
	    Qthird,Qthrow,Qtime,Qtrace,Qtree_equal,list_constant_2);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)32L,Qshort_float,
	    Qshort_site_name,Qsimple_array,Qsimple_string,Qsimple_string_p,
	    Qsimple_vector,Qsimple_vector_p,Qsin,Qsingle_float,Qsixth,
	    Qsleep,Qsort,Qspace,Qspecial,Qspecial_operator_p,Qspeed,Qsqrt,
	    Qstable_sort,Qstep,Qstream,Qstreamp,Qstring,Qstring_capitalize,
	    Qstring_downcase,Qstring_equal,Qstring_greaterp,Qstring_lessp,
	    Qstring_not_equal,Qstring_not_greaterp,Qstring_not_lessp,
	    Qstring_trim,list_constant_3);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)32L,Qremove_duplicates,
	    Qremove_if,Qremove_if_not,Qremprop,Qreplace,Qrest,Qreturn,
	    Qreturn_from,Qrevappend,Qreverse,Qroom,Qrotatef,Qround,Qrplaca,
	    Qrplacd,Qsafety,Qsatisfies,Qsbit,Qscale_float,Qschar,Qsearch,
	    Qsecond,Qsequence,Qset,Qset_difference,Qsetf,Qsetq,Qseventh,
	    Qshadow,Qshadowing_import,Qshiftf,list_constant_4);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)32L,Qposition,Qposition_if,
	    Qposition_if_not,Qpprint,Qprin1,Qprinc,Qprint,Qproclaim,Qprog,
	    Qprog_star,Qprog1,Qprog2,Qprogn,Qprogv,Qpsetf,Qpsetq,Qpush,
	    Qpushnew,Qquote,Qrandom,Qrassoc,Qratio,Qread,Qread_byte,
	    Qread_char,Qread_char_no_hang,Qread_from_string,Qread_line,
	    Qrem,Qremf,Qremove,list_constant_5);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)32L,Qmultiple_value_prog1,
	    Qmultiple_value_setq,Qmultiple_values_limit,Qnbutlast,Qnconc,
	    Qninth,Qnot,Qnotany,Qnreconc,Qnreverse,Qnstring_downcase,
	    Qnstring_upcase,Qnsubst,Qnth,Qnthcdr,Qnull,Qnumber,Qnumberp,
	    Qnumerator,Qoddp,Qopen,Qoptimize,Qotherwise,Qpackage_type,
	    Qpackage_name,Qparse_integer,Qpeek_char,Qphase,Qpi,Qplusp,Qpop,
	    list_constant_6);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)32L,Qmacro_function,
	    Qmacroexpand,Qmacroexpand_1,Qmacrolet,Qmake_array,
	    Qmake_broadcast_stream,Qmake_hash_table,Qmake_list,
	    Qmake_package,Qmake_string,Qmake_string_output_stream,
	    Qmake_symbol,Qmake_synonym_stream,Qmakunbound,Qmap,Qmapcar,
	    Qmapcan,Qmaphash,Qmax,Qmember,Qmerge,Qmin,Qminusp,Qmismatch,
	    Qmod,Qmost_negative_double_float,Qmost_negative_fixnum,
	    Qmost_positive_double_float,Qmost_positive_fixnum,
	    Qmultiple_value_call,Qmultiple_value_list,list_constant_7);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)32L,Qlambda,
	    Qlambda_list_keywords,Qlast,Qldb,Qldiff,
	    Qleast_positive_double_float,Qleast_positive_single_float,
	    Qlength,Qlisp_implementation_version,Qlist,Qlist_star,
	    Qlist_length,Qlisten,Qlistp,Qload,Qload_time_value,Qlocally,
	    Qlog,Qlogand,Qlogandc1,Qlogandc2,Qlogbitp,Qlogcount,Qlogior,
	    Qlognot,Qlogtest,Qlogxor,Qlong_float,Qlower_case_p,
	    Qmachine_instance,Qmachine_type,list_constant_8);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)32L,Qfunctionp,Qgentemp,
	    Qget,Qget_decoded_time,Qget_internal_real_time,
	    Qget_output_stream_string,Qget_setf_expansion,
	    Qget_universal_time,Qgetf,Qgethash,Qgo,Qhash_table,
	    Qhash_table_count,Qidentity,Qignorable,Qignore,Qimport,
	    Qin_package,Qincf,Qinline,Qinspect,Qinteger,Qinteger_length,
	    Qintegerp,Qintern,Qinternal_time_units_per_second,
	    Qintersection,Qisqrt,Qkeyword,Qkeywordp,Qlabels,list_constant_9);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)32L,Qevery,Qexp,Qexport,
	    Qexpt,Qfboundp,Qfceiling,Qffloor,Qfifth,Qfile_author,
	    Qfile_length,Qfile_position,Qfile_write_date,Qfill,
	    Qfill_pointer,Qfind,Qfind_if,Qfind_package,Qfind_symbol,Qfirst,
	    Qfixnum,Qflet,Qfloat,Qfloatp,Qfloor,Qfmakunbound,Qforce_output,
	    Qfourth,Qfresh_line,Qfround,Qftruncate,Qfunction,list_constant_10);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)32L,Qdefsetf,Qdefstruct,
	    Qdeftype,Qdefvar,Qdelete,Qdenominator,Qdigit_char,
	    Qdigit_char_p,Qdisassemble,Qdo,Qdo_star,Qdo_all_symbols,
	    Qdo_symbols,Qdolist,Qdotimes,Qdouble_float,Qdribble,Qecase,Qed,
	    Qeighth,Qelt,Qencode_universal_time,Qendp,Qeq,Qeql,Qequal,
	    Qequalp,Qerror,Qeval,Qeval_when,Qevenp,list_constant_11);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)32L,Qchar_gt,Qchar_le,
	    Qchar_ge,Qcharacter,Qcharacterp,Qclear_input,Qclose,Qclrhash,
	    Qcode_char,Qcoerce,Qcompilation_speed,Qcompile,Qcompile_file,
	    Qcompiled_function,Qcompiled_function_p,Qconcatenate,Qcond,
	    Qcons,Qconsp,Qconstantp,Qcopy_list,Qcopy_seq,Qcopy_tree,Qcos,
	    Qcount,Qcount_if,Qdecf,Qdeclaration,Qdeclare,
	    Qdecode_universal_time,Qdefconstant,list_constant_12);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)32L,Qcase,Qcdaaar,Qcdaadr,
	    Qcdaar,Qcdadar,Qcdaddr,Qcdadr,Qcdar,Qcddaar,Qcddadr,Qcddar,
	    Qcdddar,Qcddddr,Qcdddr,Qcddr,Qcdr,Qceiling,Qcerror,Qchar,
	    Qchar_code,Qchar_code_limit,Qchar_downcase,Qchar_equal,
	    Qchar_greaterp,Qchar_int,Qchar_lessp,Qchar_not_equal,
	    Qchar_upcase,Qchar_eq,Qchar_ne,Qchar_lt,list_constant_13);
    list_constant_15 = STATIC_LIST_STAR((SI_Long)32L,Qarrayp,Qash,Qasin,
	    Qassert,Qassoc,Qatan,Qatom,Qbignum,Qbit,Qblock,Qboth_case_p,
	    Qboundp,Qbreak,Qbutlast,Qbyte,Qbyte_position,Qcaaaar,Qcaaadr,
	    Qcaaar,Qcaadar,Qcaaddr,Qcaadr,Qcaar,Qcadaar,Qcadadr,Qcadar,
	    Qcaddar,Qcadddr,Qcaddr,Qcadr,Qcar,list_constant_14);
    list_constant_16 = STATIC_LIST_STAR((SI_Long)32L,Qplus,Qplus_plus,
	    Qplus_plus_plus,Qminus,Qslash,Qslashslash,Qslashslashslash,
	    Qnum_ne,Qadd1,Qsub1,Qnum_lt,Qnum_le,Qnum_eq,Qnum_gt,Qnum_ge,
	    Qabs,Qadjoin,Qalpha_char_p,Qalphanumericp,Qand,Qappend,Qapply,
	    Qapropos,Qaref,Qarray,Qarray_dimension,Qarray_element_type,
	    Qarray_has_fill_pointer_p,Qarray_rank,Qarray_total_size,
	    Qarray_total_size_limit,list_constant_15);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)32L,Qand_allow_other_keys,
	    Qand_aux,Qand_body,Qand_environment,Qand_key,Qand_optional,
	    Qand_rest,Qand_whole,Qstar,Qstar_star,Qstar_star_star,
	    Qdebug_io,Qdefault_pathname_defaults,Qerror_output,Qfeatures,
	    Qpackage_variable,Qprint_array,Qprint_base,Qprint_case,
	    Qprint_circle,Qprint_escape,Qprint_length,Qprint_level,
	    Qprint_pretty,Qprint_radix,Qread_base,
	    Qread_default_float_format,Qreadtable_variable,Qstandard_input,
	    Qstandard_output,Qterminal_io,list_constant_16);
    export(list_constant_17,find_package(string_constant_1));
    string_constant_2 = STATIC_STRING("AB");
    list_constant_18 = STATIC_CONS(string_constant_1,Qnil);
    tcl_user_ab_package_name = string_constant_2;
    tcl_user_ab_package_use_list = list_constant_18;
    tcl_user_extant_ab_package_qm = find_package(string_constant_2);
    if (tcl_user_extant_ab_package_qm) {
	list0 = package_use_list(tcl_user_extant_ab_package_qm);
	result_1 = Nil;
	last_1 = Nil;
	for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	    temp = package_name(CAR(list0));
	    new_last = CONS(temp,Nil);
	    if (result_1)
		M_CDR(last_1) = new_last;
	    else
		result_1 = new_last;
	    last_1 = new_last;
	}
	tcl_user_extant_ab_package_use_list = result_1;
	if (set_exclusive_or(4,tcl_user_ab_package_use_list,
		tcl_user_extant_ab_package_use_list,Ktest,
		SYMBOL_FUNCTION(Qequal)))
	    error((SI_Long)2L,
		    "CREATE-AB-PACKAGE: Bad use-list ~s for extant AB package.  You will certainly lose.",
		    tcl_user_extant_ab_package_use_list);
    }
    else
	make_package(5,tcl_user_ab_package_name,Knicknames,Nil,Kuse,
		tcl_user_ab_package_use_list);
    string_constant_3 = STATIC_STRING("NIL");
    import(LIST_1(find_symbol(string_constant_3,string_constant_1)),
	    find_package(string_constant_2));
    SET_PACKAGE("AB");
    string_constant_4 = STATIC_STRING("TCL-USER");
    if (User_package_in_this_lisp == UNBOUND)
	User_package_in_this_lisp = find_package(string_constant_4);
    if (List_for_import == UNBOUND)
	List_for_import = make_list(1,FIX((SI_Long)1L));
    string_constant_5 = STATIC_STRING("G2-DEFSTRUCT-STRUCTURE-NAME");
    if ( !TRUEP(find_package(string_constant_5)))
	make_package(5,string_constant_5,Knicknames,Nil,Kuse,Nil);
    Kno_macros = STATIC_SYMBOL("NO-MACROS",Pkeyword);
    star_features_star_new_value = adjoin(2,Kno_macros,Features);
    Features = star_features_star_new_value;
    Kvanilla = STATIC_SYMBOL("VANILLA",Pkeyword);
    star_features_star_new_value = adjoin(2,Kvanilla,Features);
    Features = star_features_star_new_value;
    AB_package = STATIC_PACKAGE("AB");
    Qab_system_pathname = STATIC_SYMBOL("AB-SYSTEM-PATHNAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qab_system_pathname,Ab_system_pathname);
    symbol_from_ab_package = Qab_system_pathname;
    package_of_symbol = SYMBOL_PACKAGE(symbol_from_ab_package);
    if ( !EQ(find_package(string_constant_2),package_of_symbol))
	error((SI_Long)3L,
		"IMPORT-INTO-USER-PACKAGE:\n                      can only import from AB package, but symbol ~s is in the ~s package.",
		symbol_from_ab_package,package_name(package_of_symbol));
    import(Qload_pathname,_);
    string_constant_6 = STATIC_STRING("buildroot.dat");
    File_naming_spin_id = string_constant_6;
    string_constant_7 = STATIC_STRING("srcbox.dat");
    File_naming_specific_source_directory = string_constant_7;
    string_constant_8 = STATIC_STRING("dstbox.dat");
    File_naming_specific_dest_directory = string_constant_8;
    string_constant_9 = STATIC_STRING("toolsdir.dat");
    File_naming_tools_directory = string_constant_9;
    string_constant_10 = STATIC_STRING("/bt");
    Default_sandbox_location = string_constant_10;
    string_constant_11 = STATIC_STRING("ab");
    Default_spin_id = string_constant_11;
    Default_sandbox_name = format((SI_Long)4L,Nil,"~A/~A",
	    Default_sandbox_location,Default_spin_id);
    Source_directory_name = Nil;
    Dest_directory_name = Nil;
    Toolsdir_name = Nil;
    string_constant_12 = STATIC_STRING("wx64fsl");
    if (Fasl_extension == UNBOUND)
	Fasl_extension = string_constant_12;
    string_constant_13 = STATIC_STRING("lisp");
    string_constant_14 = STATIC_STRING("kb");
    string_constant_15 = STATIC_STRING("kl");
    Qdowncase = STATIC_SYMBOL("DOWNCASE",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qnil,Qnil);
    Bootstrap_information = list_star(8,Fasl_extension,string_constant_13,
	    string_constant_14,string_constant_15,Qdowncase,Qnil,
	    Load_pathname,list_constant_19);
    if (Lisp_memory_expanded_qm == UNBOUND)
	Lisp_memory_expanded_qm = Nil;
}
