/* userfuns.c -- Function linking code for Lisp-to-C Translator
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "userfuns.h"

void initfuns()
{
    SET_SETF_FUNCTION(Qaref,
	STATIC_FUNCTION(SETF_aref,NIL,TRUE,2,2));
    SET_SETF_FUNCTION(Qbit,
	STATIC_FUNCTION(SETF_bit,NIL,TRUE,2,2));
    SET_SETF_FUNCTION(Qsbit,
	STATIC_FUNCTION(SETF_sbit,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qadd1,
	STATIC_FUNCTION(add1,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qplus,
	STATIC_FUNCTION(addn,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qadjoin,
	STATIC_FUNCTION(adjoin,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qalpha_char_p,
	STATIC_FUNCTION(alpha_char_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qalphanumericp,
	STATIC_FUNCTION(alphanumericp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qappend,
	STATIC_FUNCTION(append,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qapply,
	STATIC_FUNCTION(apply,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qaref,
	STATIC_FUNCTION(aref,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qarray_dimension,
	STATIC_FUNCTION(array_dimension,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qarray_element_type,
	STATIC_FUNCTION(array_element_type,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qarray_has_fill_pointer_p,
	STATIC_FUNCTION(array_has_fill_pointer_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qarray_rank,
	STATIC_FUNCTION(array_rank,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qarray_total_size,
	STATIC_FUNCTION(array_total_size,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qarrayp,
	STATIC_FUNCTION(arrayp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qash,
	STATIC_FUNCTION(ash,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qassoc,
	STATIC_FUNCTION(assoc,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qatom,
	STATIC_FUNCTION(atom,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qbit,
	STATIC_FUNCTION(bit,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qboth_case_p,
	STATIC_FUNCTION(both_case_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qboundp,
	STATIC_FUNCTION(boundp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qbreak,
	STATIC_FUNCTION(breakn,NIL,TRUE,0,1));
    SET_SYMBOL_FUNCTION(Qbutlast,
	STATIC_FUNCTION(butlast,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qbyte,
	STATIC_FUNCTION(byte,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qbyte_position,
	STATIC_FUNCTION(byte_position,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaaaar,
	STATIC_FUNCTION(caaaar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaaadr,
	STATIC_FUNCTION(caaadr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaaar,
	STATIC_FUNCTION(caaar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaadar,
	STATIC_FUNCTION(caadar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaaddr,
	STATIC_FUNCTION(caaddr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaadr,
	STATIC_FUNCTION(caadr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaar,
	STATIC_FUNCTION(caar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcadaar,
	STATIC_FUNCTION(cadaar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcadadr,
	STATIC_FUNCTION(cadadr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcadar,
	STATIC_FUNCTION(cadar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaddar,
	STATIC_FUNCTION(caddar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcadddr,
	STATIC_FUNCTION(cadddr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcaddr,
	STATIC_FUNCTION(caddr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcadr,
	STATIC_FUNCTION(cadr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcar,
	STATIC_FUNCTION(car,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdaaar,
	STATIC_FUNCTION(cdaaar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdaadr,
	STATIC_FUNCTION(cdaadr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdaar,
	STATIC_FUNCTION(cdaar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdadar,
	STATIC_FUNCTION(cdadar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdaddr,
	STATIC_FUNCTION(cdaddr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdadr,
	STATIC_FUNCTION(cdadr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdar,
	STATIC_FUNCTION(cdar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcddaar,
	STATIC_FUNCTION(cddaar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcddadr,
	STATIC_FUNCTION(cddadr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcddar,
	STATIC_FUNCTION(cddar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdddar,
	STATIC_FUNCTION(cdddar,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcddddr,
	STATIC_FUNCTION(cddddr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdddr,
	STATIC_FUNCTION(cdddr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcddr,
	STATIC_FUNCTION(cddr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcdr,
	STATIC_FUNCTION(cdr,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qceiling,
	STATIC_FUNCTION(ceiling,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qcerror,
	STATIC_FUNCTION(cerrorn,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qchar_code,
	STATIC_FUNCTION(char_code,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_downcase,
	STATIC_FUNCTION(char_downcase,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_eq,
	STATIC_FUNCTION(char_eqn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_equal,
	STATIC_FUNCTION(char_equaln,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_ge,
	STATIC_FUNCTION(char_gen,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_greaterp,
	STATIC_FUNCTION(char_greaterpn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_gt,
	STATIC_FUNCTION(char_gtn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_int,
	STATIC_FUNCTION(char_int,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_le,
	STATIC_FUNCTION(char_len,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_lessp,
	STATIC_FUNCTION(char_lesspn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_lt,
	STATIC_FUNCTION(char_ltn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_ne,
	STATIC_FUNCTION(char_nen,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_not_equal,
	STATIC_FUNCTION(char_not_equaln,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qchar_upcase,
	STATIC_FUNCTION(char_upcase,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcharacter,
	STATIC_FUNCTION(character,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcharacterp,
	STATIC_FUNCTION(characterp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qclear_input,
	STATIC_FUNCTION(clear_input,NIL,FALSE,0,1));
    SET_SYMBOL_FUNCTION(Qclrhash,
	STATIC_FUNCTION(clrhash,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcode_char,
	STATIC_FUNCTION(code_char,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcoerce,
	STATIC_FUNCTION(coerce,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qcompiled_function_p,
	STATIC_FUNCTION(compiled_function_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qconcatenate,
	STATIC_FUNCTION(concatenate,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qcons,
	STATIC_FUNCTION(cons,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qconsp,
	STATIC_FUNCTION(consp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qconstantp,
	STATIC_FUNCTION(constantp,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qcopy_list,
	STATIC_FUNCTION(copy_list,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcopy_seq,
	STATIC_FUNCTION(copy_seq,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcopy_tree,
	STATIC_FUNCTION(copy_tree,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcount,
	STATIC_FUNCTION(count,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qcount_if,
	STATIC_FUNCTION(count_if,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qdecode_universal_time,
	STATIC_FUNCTION(decode_universal_time,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qdenominator,
	STATIC_FUNCTION(denominator,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qdigit_char,
	STATIC_FUNCTION(digit_char,NIL,FALSE,1,3));
    SET_SYMBOL_FUNCTION(Qdigit_char_p,
	STATIC_FUNCTION(digit_char_p,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qslash,
	STATIC_FUNCTION(dividen,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qeighth,
	STATIC_FUNCTION(eighth,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qelt,
	STATIC_FUNCTION(elt,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qencode_universal_time,
	STATIC_FUNCTION(encode_universal_time,NIL,FALSE,6,7));
    SET_SYMBOL_FUNCTION(Qendp,
	STATIC_FUNCTION(endp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qeq,
	STATIC_FUNCTION(eq,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qeql,
	STATIC_FUNCTION(eql,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qequal,
	STATIC_FUNCTION(equal,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qequalp,
	STATIC_FUNCTION(equalp,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qerror,
	STATIC_FUNCTION(errorn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qevenp,
	STATIC_FUNCTION(evenp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qevery,
	STATIC_FUNCTION(every,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qexport,
	STATIC_FUNCTION(export,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qexpt,
	STATIC_FUNCTION(expt,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qfboundp,
	STATIC_FUNCTION(fboundp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfceiling,
	STATIC_FUNCTION(fceiling,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qfifth,
	STATIC_FUNCTION(fifth,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfile_author,
	STATIC_FUNCTION(file_author,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfile_length,
	STATIC_FUNCTION(file_length,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfile_position,
	STATIC_FUNCTION(file_position,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qfile_write_date,
	STATIC_FUNCTION(file_write_date,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfill,
	STATIC_FUNCTION(fill,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qfill_pointer,
	STATIC_FUNCTION(fill_pointer,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfind,
	STATIC_FUNCTION(find,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qfind_if,
	STATIC_FUNCTION(find_if,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qfind_package,
	STATIC_FUNCTION(find_package,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfind_symbol,
	STATIC_FUNCTION(find_symbol,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qfirst,
	STATIC_FUNCTION(first,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfloatp,
	STATIC_FUNCTION(floatp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfmakunbound,
	STATIC_FUNCTION(fmakunbound,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qforce_output,
	STATIC_FUNCTION(force_output,NIL,FALSE,0,1));
    SET_SYMBOL_FUNCTION(Qformat,
	STATIC_FUNCTION(formatn,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qfourth,
	STATIC_FUNCTION(fourth,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfresh_line,
	STATIC_FUNCTION(fresh_line,NIL,FALSE,0,1));
    SET_SYMBOL_FUNCTION(Qfround,
	STATIC_FUNCTION(fround,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qfunctionp,
	STATIC_FUNCTION(functionp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qgentemp,
	STATIC_FUNCTION(gentemp,NIL,FALSE,0,2));
    SET_SYMBOL_FUNCTION(Qget,
	STATIC_FUNCTION(get,NIL,FALSE,2,3));
    SET_SYMBOL_FUNCTION(Qget_decoded_time,
	STATIC_FUNCTION(get_decoded_time,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qget_internal_real_time,
	STATIC_FUNCTION(get_internal_real_time,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qget_output_stream_string,
	STATIC_FUNCTION(get_output_stream_string,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qget_universal_time,
	STATIC_FUNCTION(get_universal_time,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgetf,
	STATIC_FUNCTION(getf,NIL,FALSE,2,3));
    SET_SYMBOL_FUNCTION(Qgethash,
	STATIC_FUNCTION(gethash,NIL,FALSE,2,3));
    SET_SYMBOL_FUNCTION(Qhash_table_count,
	STATIC_FUNCTION(hash_table_count,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qidentity,
	STATIC_FUNCTION(identity,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qimport,
	STATIC_FUNCTION(import,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qinteger_length,
	STATIC_FUNCTION(integer_length,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qintegerp,
	STATIC_FUNCTION(integerp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qintern,
	STATIC_FUNCTION(intern,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qintersection,
	STATIC_FUNCTION(intersection,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qisqrt,
	STATIC_FUNCTION(isqrt,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qkeywordp,
	STATIC_FUNCTION(keywordp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qabs,
	STATIC_FUNCTION(l_abs,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qrandom,
	STATIC_FUNCTION(l_random,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qround,
	STATIC_FUNCTION(l_round,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qasin,
	STATIC_FUNCTION(lasin,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qlast,
	STATIC_FUNCTION(last,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qatan,
	STATIC_FUNCTION(latan,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qchar,
	STATIC_FUNCTION(lchar,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qclose,
	STATIC_FUNCTION(lclose,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qcos,
	STATIC_FUNCTION(lcos,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qldb,
	STATIC_FUNCTION(ldb,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qdelete,
	STATIC_FUNCTION(ldelete,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qldiff,
	STATIC_FUNCTION(ldiff,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qlength,
	STATIC_FUNCTION(length,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qexp,
	STATIC_FUNCTION(lexp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qffloor,
	STATIC_FUNCTION(lffloor,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qfloat,
	STATIC_FUNCTION(lfloat,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qfloor,
	STATIC_FUNCTION(lfloor,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qftruncate,
	STATIC_FUNCTION(lftruncate,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qlisp_implementation_version,
	STATIC_FUNCTION(lisp_implementation_version,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qlist,
	STATIC_FUNCTION(list,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qlist_length,
	STATIC_FUNCTION(list_length,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qlist_star,
	STATIC_FUNCTION(list_star,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qlistp,
	STATIC_FUNCTION(listp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qlisten,
	STATIC_FUNCTION(llisten,NIL,FALSE,0,1));
    SET_SYMBOL_FUNCTION(Qlog,
	STATIC_FUNCTION(llog,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qlogandc1,
	STATIC_FUNCTION(logandc1,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qlogandc2,
	STATIC_FUNCTION(logandc2,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qlogand,
	STATIC_FUNCTION(logandn,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qlogbitp,
	STATIC_FUNCTION(logbitp,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qlogcount,
	STATIC_FUNCTION(logcount,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qlogior,
	STATIC_FUNCTION(logiorn,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qlognot,
	STATIC_FUNCTION(lognot,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qlogtest,
	STATIC_FUNCTION(logtest,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qlogxor,
	STATIC_FUNCTION(logxorn,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qopen,
	STATIC_FUNCTION(lopen,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qlower_case_p,
	STATIC_FUNCTION(lower_case_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qread,
	STATIC_FUNCTION(lread,NIL,FALSE,0,4));
    SET_SYMBOL_FUNCTION(Qremove,
	STATIC_FUNCTION(lremove,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qsin,
	STATIC_FUNCTION(lsin,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsleep,
	STATIC_FUNCTION(lsleep,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsqrt,
	STATIC_FUNCTION(lsqrt,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qtan,
	STATIC_FUNCTION(ltan,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qtruncate,
	STATIC_FUNCTION(ltruncate,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qunion,
	STATIC_FUNCTION(lunion,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qwrite,
	STATIC_FUNCTION(lwrite,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qmacro_function,
	STATIC_FUNCTION(macro_function,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qmacroexpand,
	STATIC_FUNCTION(macroexpand,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qmacroexpand_1,
	STATIC_FUNCTION(macroexpand_1,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qmake_array,
	STATIC_FUNCTION(make_array,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qmake_broadcast_stream,
	STATIC_FUNCTION(make_broadcast_stream,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qmake_hash_table,
	STATIC_FUNCTION(make_hash_table,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qmake_list,
	STATIC_FUNCTION(make_list,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qmake_package,
	STATIC_FUNCTION(make_package,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qmake_string,
	STATIC_FUNCTION(make_string,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qmake_string_output_stream,
	STATIC_FUNCTION(make_string_output_stream,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmake_symbol,
	STATIC_FUNCTION(make_symbol,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmakunbound,
	STATIC_FUNCTION(makunbound,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmap,
	STATIC_FUNCTION(map,NIL,TRUE,3,3));
    SET_SYMBOL_FUNCTION(Qmapcan,
	STATIC_FUNCTION(mapcan,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qmapcar,
	STATIC_FUNCTION(mapcar,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qmaphash,
	STATIC_FUNCTION(maphash,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qmax,
	STATIC_FUNCTION(maxn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qmember,
	STATIC_FUNCTION(member,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qmerge,
	STATIC_FUNCTION(merge,NIL,TRUE,4,4));
    SET_SYMBOL_FUNCTION(Qmin,
	STATIC_FUNCTION(minn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qminus,
	STATIC_FUNCTION(minusn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qminusp,
	STATIC_FUNCTION(minusp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmismatch,
	STATIC_FUNCTION(mismatch,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qmod,
	STATIC_FUNCTION(mod,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qnbutlast,
	STATIC_FUNCTION(nbutlast,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qnconc,
	STATIC_FUNCTION(nconc,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qninth,
	STATIC_FUNCTION(ninth,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qnot,
	STATIC_FUNCTION(not,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qnotany,
	STATIC_FUNCTION(notany,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qnreconc,
	STATIC_FUNCTION(nreconc,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qnreverse,
	STATIC_FUNCTION(nreverse,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qnstring_downcase,
	STATIC_FUNCTION(nstring_downcase,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qnstring_upcase,
	STATIC_FUNCTION(nstring_upcase,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qnsubst,
	STATIC_FUNCTION(nsubst,NIL,TRUE,3,3));
    SET_SYMBOL_FUNCTION(Qnth,
	STATIC_FUNCTION(nth,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qnthcdr,
	STATIC_FUNCTION(nthcdr,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qnull,
	STATIC_FUNCTION(null,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qnum_eq,
	STATIC_FUNCTION(num_eqn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qnum_ge,
	STATIC_FUNCTION(num_gen,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qnum_gt,
	STATIC_FUNCTION(num_gtn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qnum_le,
	STATIC_FUNCTION(num_len,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qnum_lt,
	STATIC_FUNCTION(num_ltn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qnum_ne,
	STATIC_FUNCTION(num_nen,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qnumberp,
	STATIC_FUNCTION(numberp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qnumerator,
	STATIC_FUNCTION(numerator,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qoddp,
	STATIC_FUNCTION(oddp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qpackage_name,
	STATIC_FUNCTION(package_name,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qparse_integer,
	STATIC_FUNCTION(parse_integer,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qpeek_char,
	STATIC_FUNCTION(peek_char,NIL,FALSE,0,5));
    SET_SYMBOL_FUNCTION(Qphase,
	STATIC_FUNCTION(phase,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qplusp,
	STATIC_FUNCTION(plusp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qposition,
	STATIC_FUNCTION(position,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qposition_if,
	STATIC_FUNCTION(position_if,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qposition_if_not,
	STATIC_FUNCTION(position_if_not,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qpprint,
	STATIC_FUNCTION(pprint,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qprin1,
	STATIC_FUNCTION(prin1,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qprinc,
	STATIC_FUNCTION(princ,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qprint,
	STATIC_FUNCTION(print,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qrassoc,
	STATIC_FUNCTION(rassoc,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qread_byte,
	STATIC_FUNCTION(read_byte,NIL,FALSE,1,3));
    SET_SYMBOL_FUNCTION(Qread_char,
	STATIC_FUNCTION(read_char,NIL,FALSE,0,4));
    SET_SYMBOL_FUNCTION(Qread_char_no_hang,
	STATIC_FUNCTION(read_char_no_hang,NIL,FALSE,0,4));
    SET_SYMBOL_FUNCTION(Qread_from_string,
	STATIC_FUNCTION(read_from_string,NIL,TRUE,1,3));
    SET_SYMBOL_FUNCTION(Qread_line,
	STATIC_FUNCTION(read_line,NIL,FALSE,0,4));
    SET_SYMBOL_FUNCTION(Qrem,
	STATIC_FUNCTION(rem,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qremove_duplicates,
	STATIC_FUNCTION(remove_duplicates,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qremove_if,
	STATIC_FUNCTION(remove_if,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qremove_if_not,
	STATIC_FUNCTION(remove_if_not,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qremprop,
	STATIC_FUNCTION(remprop,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qreplace,
	STATIC_FUNCTION(replace,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qrest,
	STATIC_FUNCTION(rest,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qrevappend,
	STATIC_FUNCTION(revappend,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qreverse,
	STATIC_FUNCTION(reverse,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qroom,
	STATIC_FUNCTION(room,NIL,FALSE,0,1));
    SET_SYMBOL_FUNCTION(Qrplaca,
	STATIC_FUNCTION(rplaca,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qrplacd,
	STATIC_FUNCTION(rplacd,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qsbit,
	STATIC_FUNCTION(sbit,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qscale_float,
	STATIC_FUNCTION(scale_float,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qschar,
	STATIC_FUNCTION(schar,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qsearch,
	STATIC_FUNCTION(search,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qsecond,
	STATIC_FUNCTION(second,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qset,
	STATIC_FUNCTION(set,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qset_difference,
	STATIC_FUNCTION(set_difference,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qseventh,
	STATIC_FUNCTION(seventh,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qshort_site_name,
	STATIC_FUNCTION(short_site_name,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qsimple_string_p,
	STATIC_FUNCTION(simple_string_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsimple_vector_p,
	STATIC_FUNCTION(simple_vector_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsixth,
	STATIC_FUNCTION(sixth,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsort,
	STATIC_FUNCTION(sort,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstable_sort,
	STATIC_FUNCTION(stable_sort,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstreamp,
	STATIC_FUNCTION(streamp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qstring,
	STATIC_FUNCTION(string,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qstring_capitalize,
	STATIC_FUNCTION(string_capitalize,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qstring_downcase,
	STATIC_FUNCTION(string_downcase,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qstring_eq,
	STATIC_FUNCTION(string_eq,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_equal,
	STATIC_FUNCTION(string_equal,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_greaterp,
	STATIC_FUNCTION(string_greaterp,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_le,
	STATIC_FUNCTION(string_le,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_lessp,
	STATIC_FUNCTION(string_lessp,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_lt,
	STATIC_FUNCTION(string_lt,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_ne,
	STATIC_FUNCTION(string_ne,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_not_equal,
	STATIC_FUNCTION(string_not_equal,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_not_greaterp,
	STATIC_FUNCTION(string_not_greaterp,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_not_lessp,
	STATIC_FUNCTION(string_not_lessp,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_trim,
	STATIC_FUNCTION(string_trim,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qstring_upcase,
	STATIC_FUNCTION(string_upcase,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qstringp,
	STATIC_FUNCTION(stringp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsub1,
	STATIC_FUNCTION(sub1,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsublis,
	STATIC_FUNCTION(sublis,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qsubseq,
	STATIC_FUNCTION(subseq,NIL,FALSE,2,3));
    SET_SYMBOL_FUNCTION(Qsubsetp,
	STATIC_FUNCTION(subsetp,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qsubst,
	STATIC_FUNCTION(subst,NIL,TRUE,3,3));
    SET_SYMBOL_FUNCTION(Qsubstitute,
	STATIC_FUNCTION(substitute,NIL,TRUE,3,3));
    SET_SYMBOL_FUNCTION(Qsvref,
	STATIC_FUNCTION(svref,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qsxhash,
	STATIC_FUNCTION(sxhash,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsymbol_function,
	STATIC_FUNCTION(symbol_function,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsymbol_name,
	STATIC_FUNCTION(symbol_name,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsymbol_package,
	STATIC_FUNCTION(symbol_package,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsymbol_plist,
	STATIC_FUNCTION(symbol_plist,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsymbol_value,
	STATIC_FUNCTION(symbol_value,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsymbolp,
	STATIC_FUNCTION(symbolp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qtenth,
	STATIC_FUNCTION(tenth,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qterpri,
	STATIC_FUNCTION(terpri,NIL,FALSE,0,1));
    SET_SYMBOL_FUNCTION(Qthird,
	STATIC_FUNCTION(third,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qstar,
	STATIC_FUNCTION(timesn,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qtree_equal,
	STATIC_FUNCTION(tree_equal,NIL,TRUE,2,2));
    SET_SYMBOL_FUNCTION(Qtype_of,
	STATIC_FUNCTION(type_of,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qtypep,
	STATIC_FUNCTION(typep,NIL,FALSE,2,3));
    SET_SYMBOL_FUNCTION(Qunintern,
	STATIC_FUNCTION(unintern,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qunread_char,
	STATIC_FUNCTION(unread_char,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qupper_case_p,
	STATIC_FUNCTION(upper_case_p,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qvalues,
	STATIC_FUNCTION(values,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qvalues_list,
	STATIC_FUNCTION(values_list,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qvector,
	STATIC_FUNCTION(vector,NIL,TRUE,0,0));
    SET_SYMBOL_FUNCTION(Qvector_push,
	STATIC_FUNCTION(vector_push,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qvectorp,
	STATIC_FUNCTION(vectorp,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qwarn,
	STATIC_FUNCTION(warnn,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qwrite_byte,
	STATIC_FUNCTION(write_byte,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qwrite_char,
	STATIC_FUNCTION(write_char,NIL,FALSE,1,2));
    SET_SYMBOL_FUNCTION(Qwrite_line,
	STATIC_FUNCTION(write_line,NIL,TRUE,1,2));
    SET_SYMBOL_FUNCTION(Qwrite_string,
	STATIC_FUNCTION(write_string,NIL,TRUE,1,2));
    SET_SYMBOL_FUNCTION(Qwrite_to_string,
	STATIC_FUNCTION(write_to_string,NIL,TRUE,1,1));
    SET_SYMBOL_FUNCTION(Qzerop,
	STATIC_FUNCTION(zerop,NIL,FALSE,1,1));
}

void user_initfuns()
{
}
