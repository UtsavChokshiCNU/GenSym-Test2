/* is8859.c
 * Input file:  iso8859.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "is8859.h"


Object N_8859_2_unicode_map = UNBOUND;

Object N_8859_3_unicode_map = UNBOUND;

Object N_8859_4_unicode_map = UNBOUND;

Object N_8859_6_unicode_map = UNBOUND;

Object N_8859_7_unicode_map = UNBOUND;

Object N_8859_8_unicode_map = UNBOUND;

static Object Qgraphic_character_set;  /* graphic-character-set */

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* MAKE-REVERSE-8859-UNICODE-MAP */
Object make_reverse_8859_unicode_map(n_8859_graphic_character_set_name)
    Object n_8859_graphic_character_set_name;
{
    Object graphic_character_set, reverse_map, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long i, gensymed_symbol_2, temp;

    x_note_fn_call(29,0);
    graphic_character_set = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(n_8859_graphic_character_set_name),
	    Qgraphic_character_set);
    reverse_map = make_8859_reverse_unicode_map();
    i = (SI_Long)0L;
  next_loop:
    if (i >= IFIX(N_8859_part_size))
	goto end_loop;
    gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)18L);
    gensymed_symbol_1 = graphic_character_set;
    gensymed_symbol_2 = i;
    gensymed_symbol = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    FIX(gensymed_symbol_2));
    gensymed_symbol_2 = IFIX(sxhashw(gensymed_symbol));
    temp = gensymed_symbol_2 % (SI_Long)43L;
    set_balanced_binary_tree_entry(SVREF(reverse_map,FIX(temp)),Qeq,Nil,T,
	    gensymed_symbol,FIX(gensymed_symbol_2),FIX(i));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(reverse_map);
}

/* MAP-CODE-TO-UNICODE-FOR-ISO-8859-1 */
Object map_code_to_unicode_for_iso_8859_1(iso_8859_1,code)
    Object iso_8859_1, code;
{
    x_note_fn_call(29,1);
    return VALUES_1(FIX((SI_Long)128L + IFIX(code)));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-ISO-8859-1 */
Object map_unicode_to_code_if_any_for_iso_8859_1(iso_8859_1,
	    unicode_wide_character)
    Object iso_8859_1, unicode_wide_character;
{
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(29,2);
    arg = (SI_Long)160L;
    arg_1 = IFIX(unicode_wide_character);
    arg_2 = (SI_Long)255L;
    if (arg <= arg_1 && arg_1 <= arg_2)
	return VALUES_1(FIXNUM_LOGAND(unicode_wide_character,
		N_8859_code_mask));
    else
	return VALUES_1(Nil);
}

/* MAP-CODE-TO-UNICODE-FOR-ISO-8859-5 */
Object map_code_to_unicode_for_iso_8859_5(iso_8859_5,code)
    Object iso_8859_5, code;
{
    SI_Long character_1, temp;

    x_note_fn_call(29,3);
    character_1 = (SI_Long)128L + IFIX(code);
    temp = character_1;
    if ( !((SI_Long)0L <= temp && temp <= (SI_Long)255L))
	return VALUES_1(FIX((SI_Long)1024L + (IFIX(code) - (SI_Long)32L)));
    else
	switch ((unsigned char)temp) {
	  case 160:
	    return VALUES_1(FIX((SI_Long)160L));
	  case 173:
	    return VALUES_1(FIX((SI_Long)173L));
	  case 240:
	    return VALUES_1(FIX((SI_Long)8470L));
	  case 253:
	    return VALUES_1(FIX((SI_Long)167L));
	  default:
	    return VALUES_1(FIX((SI_Long)1024L + (IFIX(code) - (SI_Long)32L)));
	}
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-ISO-8859-5 */
Object map_unicode_to_code_if_any_for_iso_8859_5(iso_8859_5,
	    unicode_wide_character)
    Object iso_8859_5, unicode_wide_character;
{
    Object temp;
    SI_Long cyrillic_block_offset, code, offset_code;

    x_note_fn_call(29,4);
    temp = unicode_wide_character;
    if ( !(FIXNUM_LE(FIX((SI_Long)-32768L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)32767L)))) {
	cyrillic_block_offset = (SI_Long)1024L;
	code = IFIX(unicode_wide_character);
	offset_code = code - cyrillic_block_offset;
	if ((SI_Long)0L <= offset_code && offset_code <= (SI_Long)95L)
	    return VALUES_1(FIX((SI_Long)32L + offset_code));
	else
	    return VALUES_1(Nil);
    }
    else
	switch (INTEGER_TO_SHORT(temp)) {
	  case 160:
	    return VALUES_1(FIX((SI_Long)32L));
	  case 173:
	    return VALUES_1(FIX((SI_Long)45L));
	  case 8470:
	    return VALUES_1(FIX((SI_Long)112L));
	  case 167:
	    return VALUES_1(FIX((SI_Long)125L));
	  default:
	    cyrillic_block_offset = (SI_Long)1024L;
	    code = IFIX(unicode_wide_character);
	    offset_code = code - cyrillic_block_offset;
	    if ((SI_Long)0L <= offset_code && offset_code <= (SI_Long)95L)
		return VALUES_1(FIX((SI_Long)32L + offset_code));
	    else
		return VALUES_1(Nil);
	}
}

/* MAP-CODE-TO-UNICODE-FOR-ISO-8859-9 */
Object map_code_to_unicode_for_iso_8859_9(iso_8859_9,code)
    Object iso_8859_9, code;
{
    SI_Long character_1, temp;

    x_note_fn_call(29,5);
    character_1 = (SI_Long)128L + IFIX(code);
    temp = character_1;
    if ( !((SI_Long)0L <= temp && temp <= (SI_Long)255L))
	return VALUES_1(FIX(character_1));
    else
	switch ((unsigned char)temp) {
	  case 208:
	    return VALUES_1(FIX((SI_Long)286L));
	  case 221:
	    return VALUES_1(FIX((SI_Long)304L));
	  case 222:
	    return VALUES_1(FIX((SI_Long)350L));
	  case 240:
	    return VALUES_1(FIX((SI_Long)287L));
	  case 253:
	    return VALUES_1(FIX((SI_Long)305L));
	  case 254:
	    return VALUES_1(FIX((SI_Long)351L));
	  case 255:
	    return VALUES_1(FIX((SI_Long)255L));
	  default:
	    return VALUES_1(FIX(character_1));
	}
}

void iso8859_INIT()
{
    Object map_code_to_unicode_for_iso_8859_1_1;
    Object map_unicode_to_code_if_any_for_iso_8859_1_1, svref_arg_1;
    Object svref_new_value, map_code_to_unicode_for_iso_8859_5_1;
    Object map_unicode_to_code_if_any_for_iso_8859_5_1;
    Object map_code_to_unicode_for_iso_8859_9_1;
    Object Qiso_8859_10, AB_package, Qiso_8859_9, Qmap_code_to_unicode;
    Object Qiso_8859_8, Qiso_8859_7, Qiso_8859_6, Qiso_8859_5;
    Object Qmap_unicode_to_code_if_any, Qiso_8859_4, Qiso_8859_3, Qiso_8859_2;
    Object Qiso_8859_1, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, string_constant_4, string_constant_3;
    Object string_constant_2, string_constant_1;

    x_note_fn_call(29,6);
    SET_PACKAGE("AB");
    string_constant = 
	    STATIC_STRING("+3*Sy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bx");
    string_constant_1 = 
	    STATIC_STRING("vy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3*Sy300y37Ky31-y3*Wy30vy31My3*Zy3*ay31Sy31Qy31Wy31ry3*fy31vy31ty3*iy301y37Ny31*y3*my30wy31N");
    string_constant_2 = 
	    STATIC_STRING("y373y3*qy31Ty31Ry31Xy31sy37Py31wy31uy31Gy3=-y3=*y30*y3=0y30ry302y3=3y308y3=5y30Ky3=7y30My3=9y3=Ay30Ay30Cy31=y313y3=Fy3=Gy31Cy3=I");
    string_constant_3 = 
	    STATIC_STRING("y3=Jy31Ky31gy3=My31iy3=Oy3=Py31Uy3=Ry31Hy3=Ty3=Uy30=y3=Wy30sy303y3=Zy309y3=by30Ly3=dy30Ny3=fy3=gy30By30Dy310y314y3=ly3=my31Dy3=o");
    string_constant_4 = 
	    STATIC_STRING("y3=py31Ly31hy3=sy31jy3=uy3=vy31Vy37Lykkkkkkkkkkkkkkkkkkkkkkkkkkkkkk3*+y3A++y");
    N_8859_2_unicode_map = 
	    regenerate_optimized_constant(LIST_5(string_constant,
	    string_constant_1,string_constant_2,string_constant_3,
	    string_constant_4));
    string_constant_5 = 
	    STATIC_STRING("vy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3*Sy30Yy37Ky3*Vy3*Wy3Bxvy30Wy3*Zy3*ay30iy31Qy30Qy30my3*fy3Bxvy31ty3*iy30Zy3*ky3*ly3*my3*ny3");
    string_constant_6 = 
	    STATIC_STRING("0Xy3*py3*qy30jy31Ry30Ry30ny3*vy3Bxvy31uy3=+y3=-y3=*y3Bxvy3=0y306y304y3=3y3=4y3=5y3=6y3=7y3=8y3=9y3=Ay3=By3Bxvy3=Dy3=Ey3=Fy3=Gy30");
    string_constant_7 = 
	    STATIC_STRING("Sy3=Iy3=Jy30Oy3=Ly3=My3=Ny3=Oy31ey31Oy3=Ry3=Sy3=Ty3=Uy3Bxvy3=Wy307y305y3=Zy3=ay3=by3=cy3=dy3=ey3=fy3=gy3=hy3Bxvy3=jy3=ky3=ly3=my");
    string_constant_8 = 
	    STATIC_STRING("30Ty3=oy3=py30Py3=ry3=sy3=ty3=uy31fy31Py37Lykkkkkkkkkkkkkkkkkkkkkkkkkkkkkk3*+y3A++y");
    N_8859_3_unicode_map = 
	    regenerate_optimized_constant(LIST_5(string_constant,
	    string_constant_5,string_constant_6,string_constant_7,
	    string_constant_8));
    string_constant_9 = 
	    STATIC_STRING("vy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3*Sy300y30qy31Iy3*Wy30ay30ty3*Zy3*ay31Sy30Ey30Uy31Yy3*fy31vy3*hy3*iy301y37Ny31Jy3*my30by30u");
    string_constant_10 = 
	    STATIC_STRING("y373y3*qy31Ty30Fy30Vy31Zy316y31wy317y30+y3=-y3=*y3==y3=0y3=1y3=2y30gy308y3=5y30Ky3=7y30Iy3=9y3=Ay30cy30Cy311y318y30oy3=Gy3=Hy3=I");
    string_constant_11 = 
	    STATIC_STRING("y3=Jy3=Ky31ky3=My3=Ny3=Oy31ay31cy3=Ry30-y3=Ty3=Uy3=Vy3=Wy3=Xy3=Yy30hy309y3=by30Ly3=dy30Jy3=fy3=gy30dy30Dy312y319y30py3=my3=ny3=o");
    string_constant_12 = 
	    STATIC_STRING("y3=py3=qy31ly3=sy3=ty3=uy31by31dy37Lykkkkkkkkkkkkkkkkkkkkkkkkkkkkkk3*+y3A++y");
    N_8859_4_unicode_map = 
	    regenerate_optimized_constant(LIST_5(string_constant,
	    string_constant_9,string_constant_10,string_constant_11,
	    string_constant_12));
    string_constant_13 = 
	    STATIC_STRING("vy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3*Sy3Bxvy3Bxvy3Bxvy3*Wy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3K8y3*fy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy");
    string_constant_14 = 
	    STATIC_STRING("3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3KNy3Bxvy3Bxvy3Bxvy3KRy3Bxvy3KTy3KUy3KVy3KWy3KXy3KYy3KZy3Kay3Kby3Kcy3Kdy3Key3Kfy3Kgy3Khy");
    string_constant_15 = 
	    STATIC_STRING("3Kiy3Kjy3Kky3Kly3Kmy3Kny3Koy3Kpy3Kqy3Kry3Ksy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3L+y3L-y3L*y3L=y3L0y3L1y3L2y3L3y3L4y3L5y3L6y3L7y3L8y3L9y3LA");
    string_constant_16 = 
	    STATIC_STRING("y3LBy3LCy3LDy3LEy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvykkkkkkkkkkkkkkkkkkkkkkkkkkkkkk3*+y3A++y");
    N_8859_6_unicode_map = 
	    regenerate_optimized_constant(LIST_5(string_constant,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16));
    string_constant_17 = 
	    STATIC_STRING("vy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3*Sy36vy36uy3*Vy3Bxvy3Bxvy3*Yy3*Zy3*ay3*by3Bxvy3*dy3*ey3*fy3Bxvy3*+Hy3*iy3*jy3*ky3*ly3A0y3A");
    string_constant_18 = 
	    STATIC_STRING("1y3A2y3*py3A4y3A5y3A6y3*ty3A8y3*vy3AAy3ABy3ACy3ADy3AEy3AFy3AGy3AHy3AIy3AJy3AKy3ALy3AMy3ANy3AOy3APy3AQy3ARy3ASy3ATy3Bxvy3AVy3AWy3");
    string_constant_19 = 
	    STATIC_STRING("AXy3AYy3AZy3Aay3Aby3Acy3Ady3Aey3Afy3Agy3Ahy3Aiy3Ajy3Aky3Aly3Amy3Any3Aoy3Apy3Aqy3Ary3Asy3Aty3Auy3Avy3Awy3Axy3B+y3B-y3B*y3B=y3B0y3");
    string_constant_20 = 
	    STATIC_STRING("B1y3B2y3B3y3B4y3B5y3B6y3B7y3B8y3B9y3BAy3Bxvykkkkkkkkkkkkkkkkkkkkkkkkkkkkkk3*+y3A++y");
    N_8859_7_unicode_map = 
	    regenerate_optimized_constant(LIST_5(string_constant,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20));
    string_constant_21 = 
	    STATIC_STRING("vy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3*Sy3Bxvy3*Uy3*Vy3*Wy3*Xy3*Yy3*Zy3*ay3*by3=Jy3*dy3*ey3*fy3*gy3*+wy3*iy3*jy3*ky3*ly3*my3*ny3");
    string_constant_22 = 
	    STATIC_STRING("*oy3*py3*qy3*ry3=py3*ty3*uy3*vy3*wy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bx");
    string_constant_23 = 
	    STATIC_STRING("vy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvy3*+Jy3JCy3JDy3JEy3JFy3JGy3JHy3JIy3JJy3JKy3JLy3JMy3JNy3JOy3JPy");
    string_constant_24 = 
	    STATIC_STRING("3JQy3JRy3JSy3JTy3JUy3JVy3JWy3JXy3JYy3JZy3Jay3Jby3Jcy3Bxvy3Bxvy3Bxvy3Bxvy3Bxvykkkkkkkkkkkkkkkkkkkkkkkkkkkkkk3*+y3A++y");
    N_8859_8_unicode_map = 
	    regenerate_optimized_constant(LIST_5(string_constant,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24));
    AB_package = STATIC_PACKAGE("AB");
    Qgraphic_character_set = STATIC_SYMBOL("GRAPHIC-CHARACTER-SET",AB_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    Qmap_code_to_unicode = STATIC_SYMBOL("MAP-CODE-TO-UNICODE",AB_package);
    Qiso_8859_1 = STATIC_SYMBOL("ISO-8859-1",AB_package);
    map_code_to_unicode_for_iso_8859_1_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_iso_8859_1,NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qiso_8859_1,
	    map_code_to_unicode_for_iso_8859_1_1);
    Qmap_unicode_to_code_if_any = 
	    STATIC_SYMBOL("MAP-UNICODE-TO-CODE-IF-ANY",AB_package);
    map_unicode_to_code_if_any_for_iso_8859_1_1 = 
	    STATIC_FUNCTION(map_unicode_to_code_if_any_for_iso_8859_1,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_unicode_to_code_if_any,Qiso_8859_1,
	    map_unicode_to_code_if_any_for_iso_8859_1_1);
    Qiso_8859_2 = STATIC_SYMBOL("ISO-8859-2",AB_package);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_2),
	    Qgraphic_character_set);
    svref_new_value = N_8859_2_unicode_map;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_2),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_2);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Qiso_8859_3 = STATIC_SYMBOL("ISO-8859-3",AB_package);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_3),
	    Qgraphic_character_set);
    svref_new_value = N_8859_3_unicode_map;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_3),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_3);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Qiso_8859_4 = STATIC_SYMBOL("ISO-8859-4",AB_package);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_4),
	    Qgraphic_character_set);
    svref_new_value = N_8859_4_unicode_map;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_4),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_4);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Qiso_8859_5 = STATIC_SYMBOL("ISO-8859-5",AB_package);
    map_code_to_unicode_for_iso_8859_5_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_iso_8859_5,NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qiso_8859_5,
	    map_code_to_unicode_for_iso_8859_5_1);
    map_unicode_to_code_if_any_for_iso_8859_5_1 = 
	    STATIC_FUNCTION(map_unicode_to_code_if_any_for_iso_8859_5,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_unicode_to_code_if_any,Qiso_8859_5,
	    map_unicode_to_code_if_any_for_iso_8859_5_1);
    Qiso_8859_6 = STATIC_SYMBOL("ISO-8859-6",AB_package);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_6),
	    Qgraphic_character_set);
    svref_new_value = N_8859_6_unicode_map;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_6),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_6);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Qiso_8859_7 = STATIC_SYMBOL("ISO-8859-7",AB_package);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_7),
	    Qgraphic_character_set);
    svref_new_value = N_8859_7_unicode_map;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_7),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_7);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Qiso_8859_8 = STATIC_SYMBOL("ISO-8859-8",AB_package);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_8),
	    Qgraphic_character_set);
    svref_new_value = N_8859_8_unicode_map;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_8),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_8);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Qiso_8859_9 = STATIC_SYMBOL("ISO-8859-9",AB_package);
    map_code_to_unicode_for_iso_8859_9_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_iso_8859_9,NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qiso_8859_9,
	    map_code_to_unicode_for_iso_8859_9_1);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_9),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_9);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Qiso_8859_10 = STATIC_SYMBOL("ISO-8859-10",AB_package);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_10),
	    Qgraphic_character_set);
    svref_new_value = N_8859_4_unicode_map;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_10),
	    Qgraphic_character_set);
    svref_new_value = make_reverse_8859_unicode_map(Qiso_8859_10);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
}
