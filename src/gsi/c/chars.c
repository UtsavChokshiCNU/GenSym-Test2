/* chars.c
 * Input file:  characters.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "chars.h"


Object G2int_maximum_suggested_length_for_simple_gensym_strings = UNBOUND;

Object G2int_roman_font_special_character_code_map = UNBOUND;

Object G2int_iso_latin1_special_character_code_map = UNBOUND;

Object G2int_reverse_iso_latin1_special_character_code_map = UNBOUND;

Object G2int_jis_last_contiguous_code = UNBOUND;

/* GENSYM-JIS-CODE-TO-CONTIGUOUS */
Object g2int_gensym_jis_code_to_contiguous(code)
    Object code;
{
    Object offset_qm;
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,0);
    high_byte = IFIX(code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(G2int_jis_low_byte_offset);
    low_byte = gensymed_symbol - gensymed_symbol_1;
    if ((SI_Long)33L <= high_byte && high_byte <= (SI_Long)116L && 
	    (SI_Long)33L <= low_byte && low_byte <= (SI_Long)126L) {
	if (high_byte <= (SI_Long)41L) {
	    if (high_byte <= (SI_Long)37L) {
		if (high_byte <= (SI_Long)35L) {
		    if (high_byte <= (SI_Long)34L) {
			if ((SI_Long)34L == high_byte) {
			    if (low_byte < (SI_Long)47L)
				offset_qm = FIX((SI_Long)0L);
			    else if (low_byte <= (SI_Long)57L)
				offset_qm = Nil;
			    else if (low_byte < (SI_Long)66L)
				offset_qm = FIX((SI_Long)-11L);
			    else if (low_byte <= (SI_Long)73L)
				offset_qm = Nil;
			    else if (low_byte < (SI_Long)81L)
				offset_qm = FIX((SI_Long)-19L);
			    else if (low_byte <= (SI_Long)91L)
				offset_qm = Nil;
			    else if (low_byte < (SI_Long)107L)
				offset_qm = FIX((SI_Long)-30L);
			    else if (low_byte <= (SI_Long)113L)
				offset_qm = Nil;
			    else if (low_byte < (SI_Long)122L)
				offset_qm = FIX((SI_Long)-37L);
			    else if (low_byte <= (SI_Long)125L)
				offset_qm = Nil;
			    else
				offset_qm = FIX((SI_Long)-41L);
			}
			else
			    offset_qm = FIX((SI_Long)0L);
		    }
		    else if ((SI_Long)35L == high_byte) {
			if (low_byte < (SI_Long)33L)
			    offset_qm = FIX((SI_Long)-41L);
			else if (low_byte <= (SI_Long)47L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)58L)
			    offset_qm = FIX((SI_Long)-56L);
			else if (low_byte <= (SI_Long)64L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)91L)
			    offset_qm = FIX((SI_Long)-63L);
			else if (low_byte <= (SI_Long)96L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)123L)
			    offset_qm = FIX((SI_Long)-69L);
			else if (low_byte <= (SI_Long)126L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-73L);
		    }
		    else
			offset_qm = FIX((SI_Long)-41L);
		}
		else if (high_byte <= (SI_Long)36L) {
		    if ((SI_Long)36L == high_byte) {
			if (low_byte < (SI_Long)116L)
			    offset_qm = FIX((SI_Long)-73L);
			else if (low_byte <= (SI_Long)126L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-84L);
		    }
		    else
			offset_qm = FIX((SI_Long)-73L);
		}
		else if ((SI_Long)37L == high_byte) {
		    if (low_byte < (SI_Long)119L)
			offset_qm = FIX((SI_Long)-84L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-92L);
		}
		else
		    offset_qm = FIX((SI_Long)-84L);
	    }
	    else if (high_byte <= (SI_Long)39L) {
		if (high_byte <= (SI_Long)38L) {
		    if ((SI_Long)38L == high_byte) {
			if (low_byte < (SI_Long)57L)
			    offset_qm = FIX((SI_Long)-92L);
			else if (low_byte <= (SI_Long)64L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)89L)
			    offset_qm = FIX((SI_Long)-100L);
			else if (low_byte <= (SI_Long)126L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-138L);
		    }
		    else
			offset_qm = FIX((SI_Long)-92L);
		}
		else if ((SI_Long)39L == high_byte) {
		    if (low_byte < (SI_Long)66L)
			offset_qm = FIX((SI_Long)-138L);
		    else if (low_byte <= (SI_Long)80L)
			offset_qm = Nil;
		    else if (low_byte < (SI_Long)114L)
			offset_qm = FIX((SI_Long)-153L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-166L);
		}
		else
		    offset_qm = FIX((SI_Long)-138L);
	    }
	    else if (high_byte <= (SI_Long)40L) {
		if ((SI_Long)40L == high_byte) {
		    if (low_byte < (SI_Long)65L)
			offset_qm = FIX((SI_Long)-166L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-228L);
		}
		else
		    offset_qm = FIX((SI_Long)-166L);
	    }
	    else if ((SI_Long)41L == high_byte) {
		if (low_byte < (SI_Long)33L)
		    offset_qm = FIX((SI_Long)-228L);
		else if (low_byte <= (SI_Long)126L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-322L);
	    }
	    else
		offset_qm = FIX((SI_Long)-228L);
	}
	else if (high_byte <= (SI_Long)45L) {
	    if (high_byte <= (SI_Long)43L) {
		if (high_byte <= (SI_Long)42L) {
		    if ((SI_Long)42L == high_byte) {
			if (low_byte < (SI_Long)33L)
			    offset_qm = FIX((SI_Long)-322L);
			else if (low_byte <= (SI_Long)126L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-416L);
		    }
		    else
			offset_qm = FIX((SI_Long)-322L);
		}
		else if ((SI_Long)43L == high_byte) {
		    if (low_byte < (SI_Long)33L)
			offset_qm = FIX((SI_Long)-416L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-510L);
		}
		else
		    offset_qm = FIX((SI_Long)-416L);
	    }
	    else if (high_byte <= (SI_Long)44L) {
		if ((SI_Long)44L == high_byte) {
		    if (low_byte < (SI_Long)33L)
			offset_qm = FIX((SI_Long)-510L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-604L);
		}
		else
		    offset_qm = FIX((SI_Long)-510L);
	    }
	    else if ((SI_Long)45L == high_byte) {
		if (low_byte < (SI_Long)33L)
		    offset_qm = FIX((SI_Long)-604L);
		else if (low_byte <= (SI_Long)126L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-698L);
	    }
	    else
		offset_qm = FIX((SI_Long)-604L);
	}
	else if (high_byte <= (SI_Long)47L) {
	    if (high_byte <= (SI_Long)46L) {
		if ((SI_Long)46L == high_byte) {
		    if (low_byte < (SI_Long)33L)
			offset_qm = FIX((SI_Long)-698L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-792L);
		}
		else
		    offset_qm = FIX((SI_Long)-698L);
	    }
	    else if ((SI_Long)47L == high_byte) {
		if (low_byte < (SI_Long)33L)
		    offset_qm = FIX((SI_Long)-792L);
		else if (low_byte <= (SI_Long)126L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-886L);
	    }
	    else
		offset_qm = FIX((SI_Long)-792L);
	}
	else if (high_byte <= (SI_Long)79L) {
	    if ((SI_Long)79L == high_byte) {
		if (low_byte < (SI_Long)84L)
		    offset_qm = FIX((SI_Long)-886L);
		else if (low_byte <= (SI_Long)126L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-929L);
	    }
	    else
		offset_qm = FIX((SI_Long)-886L);
	}
	else if (high_byte <= (SI_Long)116L) {
	    if ((SI_Long)116L == high_byte) {
		if (low_byte < (SI_Long)39L)
		    offset_qm = FIX((SI_Long)-929L);
		else if (low_byte <= (SI_Long)126L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-1017L);
	    }
	    else
		offset_qm = FIX((SI_Long)-929L);
	}
	else
	    offset_qm = FIX((SI_Long)-929L);
	if (offset_qm)
	    return VALUES_1(FIX(IFIX(offset_qm) + (high_byte - 
		    (SI_Long)33L) * (SI_Long)94L + (low_byte - (SI_Long)33L)));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* LEGAL-GENSYM-JIS-CHARACTER-CODE-P */
Object g2int_legal_gensym_jis_character_code_p(gensym_jis_code)
    Object gensym_jis_code;
{
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,1);
    high_byte = IFIX(gensym_jis_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(gensym_jis_code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(G2int_jis_low_byte_offset);
    low_byte = gensymed_symbol - gensymed_symbol_1;
    if (IFIX(G2int_jis_high_byte_min) <= high_byte && high_byte <= 
	    IFIX(G2int_jis_high_byte_max) && IFIX(G2int_jis_low_byte_min) 
	    <= low_byte && low_byte <= IFIX(G2int_jis_low_byte_max))
	return VALUES_1( !(high_byte <= (SI_Long)41L ? (high_byte <= 
		(SI_Long)37L ? (high_byte <= (SI_Long)35L ? (high_byte <= 
		(SI_Long)34L ? ((SI_Long)34L == high_byte ? (SI_Long)47L 
		<= low_byte && low_byte <= (SI_Long)57L || (SI_Long)66L <= 
		low_byte && low_byte <= (SI_Long)73L || (SI_Long)81L <= 
		low_byte && low_byte <= (SI_Long)91L || (SI_Long)107L <= 
		low_byte && low_byte <= (SI_Long)113L || (SI_Long)122L <= 
		low_byte && low_byte <= (SI_Long)125L : TRUEP(Nil)) : 
		(SI_Long)35L == high_byte ? (SI_Long)33L <= low_byte && 
		low_byte <= (SI_Long)47L || (SI_Long)58L <= low_byte && 
		low_byte <= (SI_Long)64L || (SI_Long)91L <= low_byte && 
		low_byte <= (SI_Long)96L || (SI_Long)123L <= low_byte && 
		low_byte <= (SI_Long)126L : TRUEP(Nil)) : high_byte <= 
		(SI_Long)36L ? ((SI_Long)36L == high_byte ? (SI_Long)116L 
		<= low_byte && low_byte <= (SI_Long)126L : TRUEP(Nil)) : 
		(SI_Long)37L == high_byte ? (SI_Long)119L <= low_byte && 
		low_byte <= (SI_Long)126L : TRUEP(Nil)) : high_byte <= 
		(SI_Long)39L ? (high_byte <= (SI_Long)38L ? ((SI_Long)38L 
		== high_byte ? (SI_Long)57L <= low_byte && low_byte <= 
		(SI_Long)64L || (SI_Long)89L <= low_byte && low_byte <= 
		(SI_Long)126L : TRUEP(Nil)) : (SI_Long)39L == high_byte ? 
		(SI_Long)66L <= low_byte && low_byte <= (SI_Long)80L || 
		(SI_Long)114L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)40L ? ((SI_Long)40L == 
		high_byte ? (SI_Long)65L <= low_byte && low_byte <= 
		(SI_Long)126L : TRUEP(Nil)) : (SI_Long)41L == high_byte ? 
		(SI_Long)33L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)45L ? (high_byte <= 
		(SI_Long)43L ? (high_byte <= (SI_Long)42L ? ((SI_Long)42L 
		== high_byte ? (SI_Long)33L <= low_byte && low_byte <= 
		(SI_Long)126L : TRUEP(Nil)) : (SI_Long)43L == high_byte ? 
		(SI_Long)33L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)44L ? ((SI_Long)44L == 
		high_byte ? (SI_Long)33L <= low_byte && low_byte <= 
		(SI_Long)126L : TRUEP(Nil)) : (SI_Long)45L == high_byte ? 
		(SI_Long)33L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)47L ? (high_byte <= 
		(SI_Long)46L ? ((SI_Long)46L == high_byte ? (SI_Long)33L 
		<= low_byte && low_byte <= (SI_Long)126L : TRUEP(Nil)) : 
		(SI_Long)47L == high_byte ? (SI_Long)33L <= low_byte && 
		low_byte <= (SI_Long)126L : TRUEP(Nil)) : high_byte <= 
		(SI_Long)79L ? ((SI_Long)79L == high_byte ? (SI_Long)84L 
		<= low_byte && low_byte <= (SI_Long)126L : TRUEP(Nil)) : 
		high_byte <= (SI_Long)116L ? ((SI_Long)116L == high_byte ? 
		(SI_Long)39L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : TRUEP(Nil)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* JIS-TO-SHIFT-JIS */
Object g2int_jis_to_shift_jis(code_init)
    Object code_init;
{
    Object flag_qm;
    SI_Long code, j1_1, gensymed_symbol, j2, sj1, plus, sj, incf_arg;

    x_note_fn_call(14,2);
    code = IFIX(code_init);
    j1_1 = (code & (SI_Long)65280L) >>  -  - (SI_Long)8L;
    gensymed_symbol = code & (SI_Long)255L;
    j2 = gensymed_symbol;
    sj1 = j1_1 - (SI_Long)33L;
    plus = j1_1 > (SI_Long)94L ? (SI_Long)49408L : (SI_Long)33024L;
    flag_qm = Nil;
    if ((SI_Long)1L == ((SI_Long)1L & sj1)) {
	sj1 = sj1 - (SI_Long)1L;
	flag_qm = T;
    }
    sj = (sj1 >>  -  - (SI_Long)1L << (SI_Long)8L) + plus;
    if (flag_qm) {
	incf_arg = j2 + (SI_Long)126L;
	sj = sj + incf_arg;
    }
    else if (j2 <= (SI_Long)95L) {
	incf_arg = j2 + (SI_Long)31L;
	sj = sj + incf_arg;
    }
    else if (j2 >= (SI_Long)96L) {
	incf_arg = j2 + (SI_Long)32L;
	sj = sj + incf_arg;
    }
    return VALUES_1(FIX(sj));
}

Object G2int_number_of_ksc_codes = UNBOUND;

/* KSC-TO-GENSYM-KSC */
Object g2int_ksc_to_gensym_ksc(ksc_code)
    Object ksc_code;
{
    SI_Long high_byte, gensymed_symbol, low_byte;

    x_note_fn_call(14,3);
    high_byte = IFIX(ksc_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(ksc_code) & (SI_Long)255L;
    low_byte = gensymed_symbol;
    return VALUES_1(FIX((high_byte << (SI_Long)8L) + 
	    (IFIX(G2int_ksc_low_byte_offset) + low_byte)));
}

/* KS2-BYTES-TO-KSC5601 */
Object g2int_ks2_bytes_to_ksc5601(ks2_high_byte,ks2_low_byte)
    Object ks2_high_byte, ks2_low_byte;
{
    x_note_fn_call(14,4);
    return VALUES_1(FIX((IFIX(ks2_high_byte) + (SI_Long)-128L << 
	    (SI_Long)8L) + (IFIX(ks2_low_byte) + (SI_Long)-128L)));
}

/* CONVERT-2-BYTE-TO-GENSYM-KSC5601 */
Object g2int_convert_2_byte_to_gensym_ksc5601(ks2_high_byte_character,
	    ks2_low_byte_character)
    Object ks2_high_byte_character, ks2_low_byte_character;
{
    x_note_fn_call(14,5);
    return g2int_ksc_to_gensym_ksc(g2int_ks2_bytes_to_ksc5601(CHAR_CODE(ks2_high_byte_character),
	    CHAR_CODE(ks2_low_byte_character)));
}

/* GENSYM-KSC-TO-KSC */
Object g2int_gensym_ksc_to_ksc(gensym_ksc_code)
    Object gensym_ksc_code;
{
    SI_Long high_byte, gensymed_symbol, low_byte;

    x_note_fn_call(14,6);
    high_byte = IFIX(gensym_ksc_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(gensym_ksc_code) & (SI_Long)255L;
    low_byte = gensymed_symbol;
    return VALUES_1(FIX((high_byte << (SI_Long)8L) + (low_byte - 
	    IFIX(G2int_ksc_low_byte_offset))));
}

Object G2int_ksc_last_contiguous_code = UNBOUND;

Object G2int_ksc_contiguous_character_group_lengths = UNBOUND;

/* GENSYM-KSC-CODE-TO-CONTIGUOUS */
Object g2int_gensym_ksc_code_to_contiguous(code)
    Object code;
{
    Object offset_qm;
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,7);
    high_byte = IFIX(code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(G2int_ksc_low_byte_offset);
    low_byte = gensymed_symbol - gensymed_symbol_1;
    if ((SI_Long)33L <= high_byte && high_byte <= (SI_Long)125L && 
	    (SI_Long)33L <= low_byte && low_byte <= (SI_Long)126L) {
	if (high_byte <= (SI_Long)44L) {
	    if (high_byte <= (SI_Long)39L) {
		if (high_byte <= (SI_Long)37L) {
		    if (high_byte <= (SI_Long)34L) {
			if ((SI_Long)34L == high_byte) {
			    if (low_byte < (SI_Long)102L)
				offset_qm = FIX((SI_Long)0L);
			    else if (low_byte <= (SI_Long)126L)
				offset_qm = Nil;
			    else
				offset_qm = FIX((SI_Long)-25L);
			}
			else
			    offset_qm = FIX((SI_Long)0L);
		    }
		    else if ((SI_Long)37L == high_byte) {
			if (low_byte < (SI_Long)43L)
			    offset_qm = FIX((SI_Long)-25L);
			else if (low_byte <= (SI_Long)47L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)58L)
			    offset_qm = FIX((SI_Long)-30L);
			else if (low_byte <= (SI_Long)64L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)89L)
			    offset_qm = FIX((SI_Long)-37L);
			else if (low_byte <= (SI_Long)96L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)121L)
			    offset_qm = FIX((SI_Long)-45L);
			else if (low_byte <= (SI_Long)126L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-51L);
		    }
		    else
			offset_qm = FIX((SI_Long)-25L);
		}
		else if (high_byte <= (SI_Long)38L) {
		    if ((SI_Long)38L == high_byte) {
			if (low_byte < (SI_Long)101L)
			    offset_qm = FIX((SI_Long)-51L);
			else if (low_byte <= (SI_Long)126L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-77L);
		    }
		    else
			offset_qm = FIX((SI_Long)-51L);
		}
		else if ((SI_Long)39L == high_byte) {
		    if (low_byte < (SI_Long)112L)
			offset_qm = FIX((SI_Long)-77L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-92L);
		}
		else
		    offset_qm = FIX((SI_Long)-77L);
	    }
	    else if (high_byte <= (SI_Long)42L) {
		if (high_byte <= (SI_Long)40L) {
		    if ((SI_Long)40L == high_byte) {
			if (low_byte < (SI_Long)37L)
			    offset_qm = FIX((SI_Long)-92L);
			else if (low_byte <= (SI_Long)37L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)39L)
			    offset_qm = FIX((SI_Long)-93L);
			else if (low_byte <= (SI_Long)39L)
			    offset_qm = Nil;
			else if (low_byte < (SI_Long)48L)
			    offset_qm = FIX((SI_Long)-94L);
			else if (low_byte <= (SI_Long)48L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-95L);
		    }
		    else
			offset_qm = FIX((SI_Long)-92L);
		}
		else if ((SI_Long)42L == high_byte) {
		    if (low_byte < (SI_Long)116L)
			offset_qm = FIX((SI_Long)-95L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-106L);
		}
		else
		    offset_qm = FIX((SI_Long)-95L);
	    }
	    else if (high_byte <= (SI_Long)43L) {
		if ((SI_Long)43L == high_byte) {
		    if (low_byte < (SI_Long)119L)
			offset_qm = FIX((SI_Long)-106L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-114L);
		}
		else
		    offset_qm = FIX((SI_Long)-106L);
	    }
	    else if ((SI_Long)44L == high_byte) {
		if (low_byte < (SI_Long)66L)
		    offset_qm = FIX((SI_Long)-114L);
		else if (low_byte <= (SI_Long)80L)
		    offset_qm = Nil;
		else if (low_byte < (SI_Long)114L)
		    offset_qm = FIX((SI_Long)-129L);
		else if (low_byte <= (SI_Long)126L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-142L);
	    }
	    else
		offset_qm = FIX((SI_Long)-114L);
	}
	else if (high_byte <= (SI_Long)73L) {
	    if (high_byte <= (SI_Long)46L) {
		if (high_byte <= (SI_Long)45L) {
		    if ((SI_Long)45L == high_byte) {
			if (low_byte < (SI_Long)33L)
			    offset_qm = FIX((SI_Long)-142L);
			else if (low_byte <= (SI_Long)126L)
			    offset_qm = Nil;
			else
			    offset_qm = FIX((SI_Long)-236L);
		    }
		    else
			offset_qm = FIX((SI_Long)-142L);
		}
		else if ((SI_Long)46L == high_byte) {
		    if (low_byte < (SI_Long)33L)
			offset_qm = FIX((SI_Long)-236L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-330L);
		}
		else
		    offset_qm = FIX((SI_Long)-236L);
	    }
	    else if (high_byte <= (SI_Long)47L) {
		if ((SI_Long)47L == high_byte) {
		    if (low_byte < (SI_Long)33L)
			offset_qm = FIX((SI_Long)-330L);
		    else if (low_byte <= (SI_Long)126L)
			offset_qm = Nil;
		    else
			offset_qm = FIX((SI_Long)-424L);
		}
		else
		    offset_qm = FIX((SI_Long)-330L);
	    }
	    else if ((SI_Long)73L == high_byte) {
		if (low_byte < (SI_Long)33L)
		    offset_qm = FIX((SI_Long)-424L);
		else if (low_byte <= (SI_Long)126L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-518L);
	    }
	    else
		offset_qm = FIX((SI_Long)-424L);
	}
	else if (high_byte <= (SI_Long)126L) {
	    if ((SI_Long)126L == high_byte) {
		if (low_byte < (SI_Long)33L)
		    offset_qm = FIX((SI_Long)-518L);
		else if (low_byte <= (SI_Long)33L)
		    offset_qm = Nil;
		else
		    offset_qm = FIX((SI_Long)-519L);
	    }
	    else
		offset_qm = FIX((SI_Long)-518L);
	}
	else
	    offset_qm = FIX((SI_Long)-518L);
	if (offset_qm)
	    return VALUES_1(FIX(IFIX(offset_qm) + (high_byte - 
		    (SI_Long)33L) * (SI_Long)94L + (low_byte - (SI_Long)33L)));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* LEGAL-GENSYM-KSC-CHARACTER-CODE-P */
Object g2int_legal_gensym_ksc_character_code_p(gensym_ksc_code)
    Object gensym_ksc_code;
{
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,8);
    high_byte = IFIX(gensym_ksc_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(gensym_ksc_code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(G2int_ksc_low_byte_offset);
    low_byte = gensymed_symbol - gensymed_symbol_1;
    if (IFIX(G2int_ksc_high_byte_min) <= high_byte && high_byte <= 
	    IFIX(G2int_ksc_high_byte_max) && IFIX(G2int_ksc_low_byte_min) 
	    <= low_byte && low_byte <= IFIX(G2int_ksc_low_byte_max))
	return VALUES_1( !(high_byte <= (SI_Long)44L ? (high_byte <= 
		(SI_Long)39L ? (high_byte <= (SI_Long)37L ? (high_byte <= 
		(SI_Long)34L ? ((SI_Long)34L == high_byte ? (SI_Long)102L 
		<= low_byte && low_byte <= (SI_Long)126L : TRUEP(Nil)) : 
		(SI_Long)37L == high_byte ? (SI_Long)43L <= low_byte && 
		low_byte <= (SI_Long)47L || (SI_Long)58L <= low_byte && 
		low_byte <= (SI_Long)64L || (SI_Long)89L <= low_byte && 
		low_byte <= (SI_Long)96L || (SI_Long)121L <= low_byte && 
		low_byte <= (SI_Long)126L : TRUEP(Nil)) : high_byte <= 
		(SI_Long)38L ? ((SI_Long)38L == high_byte ? (SI_Long)101L 
		<= low_byte && low_byte <= (SI_Long)126L : TRUEP(Nil)) : 
		(SI_Long)39L == high_byte ? (SI_Long)112L <= low_byte && 
		low_byte <= (SI_Long)126L : TRUEP(Nil)) : high_byte <= 
		(SI_Long)42L ? (high_byte <= (SI_Long)40L ? ((SI_Long)40L 
		== high_byte ? (SI_Long)37L <= low_byte && low_byte <= 
		(SI_Long)37L || (SI_Long)39L <= low_byte && low_byte <= 
		(SI_Long)39L || (SI_Long)48L <= low_byte && low_byte <= 
		(SI_Long)48L : TRUEP(Nil)) : (SI_Long)42L == high_byte ? 
		(SI_Long)116L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)43L ? ((SI_Long)43L == 
		high_byte ? (SI_Long)119L <= low_byte && low_byte <= 
		(SI_Long)126L : TRUEP(Nil)) : (SI_Long)44L == high_byte ? 
		(SI_Long)66L <= low_byte && low_byte <= (SI_Long)80L || 
		(SI_Long)114L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)73L ? (high_byte <= 
		(SI_Long)46L ? (high_byte <= (SI_Long)45L ? ((SI_Long)45L 
		== high_byte ? (SI_Long)33L <= low_byte && low_byte <= 
		(SI_Long)126L : TRUEP(Nil)) : (SI_Long)46L == high_byte ? 
		(SI_Long)33L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)47L ? ((SI_Long)47L == 
		high_byte ? (SI_Long)33L <= low_byte && low_byte <= 
		(SI_Long)126L : TRUEP(Nil)) : (SI_Long)73L == high_byte ? 
		(SI_Long)33L <= low_byte && low_byte <= (SI_Long)126L : 
		TRUEP(Nil)) : high_byte <= (SI_Long)126L ? ((SI_Long)126L 
		== high_byte ? (SI_Long)33L <= low_byte && low_byte <= 
		(SI_Long)33L : TRUEP(Nil)) : TRUEP(Nil)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

Object G2int_unicode_offset_for_gensym_cyrillic = UNBOUND;

/* ISO-8859-5-TO-GENSYM-CYRILLIC */
Object g2int_iso_8859_5_to_gensym_cyrillic(iso_8859_5_character_code)
    Object iso_8859_5_character_code;
{
    Object temp;

    x_note_fn_call(14,9);
    temp = 
	    FIXNUM_ADD(FIXNUM_ADD(G2int_gensym_cyrillic_character_block_start,
	    G2int_iso_8859_5_offset_within_cyrillic_character_block),
	    iso_8859_5_character_code);
    return VALUES_1(temp);
}

Object G2int_cyrillic_character_a_list = UNBOUND;

Object G2int_msw_cyrillic_code_map = UNBOUND;

Object G2int_unicode_index_to_slavic_font_direct_index_map = UNBOUND;

Object G2int_cyrillic_gensym_character_code_for_key_name_prop = UNBOUND;

Object G2int_key_cap_to_gensym_cyrillic_character_code_map = UNBOUND;

/* UTILIZE-CYRILLIC-CHARACTER-A-LIST */
Object g2int_utilize_cyrillic_character_a_list()
{
    Object code, msw_code_qm, name_qm, direct_index_qm, key_name_qm;
    Object key_cap_qm, ab_loop_list_, ab_loop_desetq_, temp, name_qm_1;
    Object ab_loop_list__1, key_name_qm_1, ab_loop_list__2, key_cap_qm_1;
    Object ab_loop_list__3, ab_loop_iter_flag_;
    SI_Long code_1, ab_loop_bind_, msw_code_qm_1, direct_index_qm_1;

    x_note_fn_call(14,10);
    code = Nil;
    msw_code_qm = Nil;
    name_qm = Nil;
    direct_index_qm = Nil;
    key_name_qm = Nil;
    key_cap_qm = Nil;
    ab_loop_list_ = G2int_cyrillic_character_a_list;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    code = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    msw_code_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    name_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    direct_index_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    key_name_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    key_cap_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(code)) {
	code_1 = IFIX(FIRST(code));
	ab_loop_bind_ = IFIX(SECOND(code));
	msw_code_qm_1 = IFIX(FIRST(msw_code_qm));
	name_qm_1 = Nil;
	ab_loop_list__1 = name_qm;
	direct_index_qm_1 = IFIX(FIRST(direct_index_qm));
	key_name_qm_1 = Nil;
	ab_loop_list__2 = key_name_qm;
	key_cap_qm_1 = Nil;
	ab_loop_list__3 = key_cap_qm;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (code_1 > ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    msw_code_qm_1 = msw_code_qm_1 + (SI_Long)1L;
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	name_qm_1 = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_iter_flag_))
	    direct_index_qm_1 = direct_index_qm_1 + (SI_Long)1L;
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_1;
	key_name_qm_1 = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	if ( !TRUEP(ab_loop_list__3))
	    goto end_loop_1;
	key_cap_qm_1 = M_CAR(ab_loop_list__3);
	ab_loop_list__3 = M_CDR(ab_loop_list__3);
	g2int_utilize_cyrillic_character_a_list_1(FIX(code_1),
		FIX(msw_code_qm_1),name_qm_1,FIX(direct_index_qm_1),
		key_name_qm_1,key_cap_qm_1);
	ab_loop_iter_flag_ = Nil;
	code_1 = code_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else
	g2int_utilize_cyrillic_character_a_list_1(code,msw_code_qm,name_qm,
		direct_index_qm,key_name_qm,key_cap_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qg2int_cyrillic_gensym_character_code_for_key_name;  /* cyrillic-gensym-character-code-for-key-name */

/* UTILIZE-CYRILLIC-CHARACTER-A-LIST-1 */
Object g2int_utilize_cyrillic_character_a_list_1(code,msw_code_qm,name_qm,
	    direct_index_qm,key_name_qm,key_cap_qm)
    Object code, msw_code_qm, name_qm, direct_index_qm, key_name_qm;
    Object key_cap_qm;
{
    Object svref_arg_1, svref_arg_2;

    x_note_fn_call(14,11);
    svref_arg_1 = G2int_msw_cyrillic_code_map;
    svref_arg_2 = FIXNUM_MINUS(code,
	    G2int_unicode_cyrillic_character_block_start);
    SVREF(svref_arg_1,svref_arg_2) = msw_code_qm;
    svref_arg_1 = G2int_unicode_index_to_slavic_font_direct_index_map;
    svref_arg_2 = FIXNUM_MINUS(code,
	    G2int_unicode_cyrillic_character_block_start);
    SVREF(svref_arg_1,svref_arg_2) = direct_index_qm;
    if (key_name_qm)
	g2int_mutate_global_property(key_name_qm,
		FIXNUM_ADD(FIXNUM_MINUS(code,
		G2int_unicode_cyrillic_character_block_start),
		G2int_gensym_cyrillic_character_block_start),
		Qg2int_cyrillic_gensym_character_code_for_key_name);
    if (key_cap_qm) {
	svref_arg_1 = G2int_key_cap_to_gensym_cyrillic_character_code_map;
	svref_arg_2 = CHAR_CODE(key_cap_qm);
	SVREF(svref_arg_1,svref_arg_2) = code;
    }
    return VALUES_1(Nil);
}

Object G2int_gensym_unicode_row_correspondences = UNBOUND;

Object G2int_gensym_to_unicode_full_row_map = UNBOUND;

Object G2int_unicode_to_gensym_full_row_map = UNBOUND;

/* MAP-UNICODE-TO-EXTENDED-UTF-G-CHARACTERS */
Object g2int_map_unicode_to_extended_utf_g_characters(unicode)
    Object unicode;
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(14,12);
    temp = FIX((SI_Long)63232L + (IFIX(unicode) >>  -  - (SI_Long)8L));
    gensymed_symbol = (SI_Long)63488L;
    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
    return VALUES_2(temp,FIX(gensymed_symbol + gensymed_symbol_1));
}

/* MAP-EXTENDED-UTF-G-CHARACTERS-TO-UNICODE */
Object g2int_map_extended_utf_g_characters_to_unicode(high_half,low_half)
    Object high_half, low_half;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(14,13);
    gensymed_symbol = IFIX(high_half) & (SI_Long)255L;
    gensymed_symbol_1 = (SI_Long)8L;
    gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
    gensymed_symbol = IFIX(low_half) & (SI_Long)255L;
    return VALUES_1(FIX(gensymed_symbol_1 + gensymed_symbol));
}

Object G2int_unicode_offset_for_gensym_letterlike_symbol = UNBOUND;

/* UNICODE-LETTERLIKE-SYMBOL-P */
Object g2int_unicode_letterlike_symbol_p(unicode)
    Object unicode;
{
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(14,14);
    arg = (SI_Long)4352L;
    arg_1 = IFIX(FIXNUM_ADD(unicode,
	    G2int_unicode_offset_for_gensym_letterlike_symbol));
    arg_2 = (SI_Long)4607L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

Object G2int_unicode_offset_for_gensym_general_punctuation = UNBOUND;

/* UNICODE-GENERAL-PUNCTUATION-CHARACTER-P */
Object g2int_unicode_general_punctuation_character_p(unicode)
    Object unicode;
{
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(14,15);
    arg = (SI_Long)4096L;
    arg_1 = IFIX(FIXNUM_ADD(unicode,
	    G2int_unicode_offset_for_gensym_general_punctuation));
    arg_2 = (SI_Long)4351L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* ALPHABETIC-GENSYM-CHARACTER-P */
Object g2int_alphabetic_gensym_character_p(character_or_character_code,
	    escape_character_qm)
    Object character_or_character_code, escape_character_qm;
{
    Object temp, unicode_index;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(14,16);
    if (escape_character_qm) {
	if ( !CHARACTERP(escape_character_qm))
	    temp = Nil;
	else
	    switch (ICHAR_CODE(escape_character_qm)) {
	      case '~':
		temp = ALPHANUMERICP(character_or_character_code) ? T : Nil;
		break;
	      case '\\':
		temp = (SI_Long)9057L <= IFIX(character_or_character_code) 
			? (IFIX(character_or_character_code) <= 
			(SI_Long)9082L ? T : Nil) : Qnil;
		if (temp);
		else
		    temp = (SI_Long)9793L <= 
			    IFIX(character_or_character_code) ? 
			    (IFIX(character_or_character_code) <= 
			    (SI_Long)9816L ? T : Nil) : Qnil;
		if (temp);
		else
		    temp = (SI_Long)10065L <= 
			    IFIX(character_or_character_code) ? 
			    (IFIX(character_or_character_code) <= 
			    (SI_Long)10097L ? T : Nil) : Qnil;
		if (temp);
		else {
		    arg = IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9057L)));
		    arg_1 = IFIX(character_or_character_code);
		    arg_2 = IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9082L)));
		    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		}
		if (temp);
		else {
		    arg = IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9569L)));
		    arg_1 = IFIX(character_or_character_code);
		    arg_2 = IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9592L)));
		    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		}
		if (temp);
		else {
		    arg = IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)11345L)));
		    arg_1 = IFIX(character_or_character_code);
		    arg_2 = 
			    IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)11377L)));
		    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		}
		if (temp);
		else {
		    unicode_index = 
			    FIXNUM_MINUS(character_or_character_code,
			    G2int_gensym_cyrillic_character_block_start);
		    temp = (SI_Long)48L <= IFIX(unicode_index) ? 
			    (IFIX(unicode_index) <= (SI_Long)79L ? T : 
			    Nil) : Qnil;
		    if (temp);
		    else
			temp = (SI_Long)81L <= IFIX(unicode_index) ? 
				(IFIX(unicode_index) <= (SI_Long)92L ? T : 
				Nil) : Qnil;
		    if (temp);
		    else
			temp = (SI_Long)94L <= IFIX(unicode_index) ? 
				(IFIX(unicode_index) <= (SI_Long)95L ? T : 
				Nil) : Qnil;
		    if (temp);
		    else
			temp = (SI_Long)96L <= IFIX(unicode_index) && 
				IFIX(unicode_index) <= (SI_Long)127L ? 
				(FIXNUM_ODDP(unicode_index) ? T : Nil) : Qnil;
		}
		if (temp);
		else {
		    temp = (SI_Long)9025L <= 
			    IFIX(character_or_character_code) ? 
			    (IFIX(character_or_character_code) <= 
			    (SI_Long)9050L ? T : Nil) : Qnil;
		    if (temp);
		    else
			temp = (SI_Long)9761L <= 
				IFIX(character_or_character_code) ? 
				(IFIX(character_or_character_code) <= 
				(SI_Long)9784L ? T : Nil) : Qnil;
		    if (temp);
		    else
			temp = (SI_Long)10017L <= 
				IFIX(character_or_character_code) ? 
				(IFIX(character_or_character_code) <= 
				(SI_Long)10049L ? T : Nil) : Qnil;
		    if (temp);
		    else {
			arg = 
				IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9025L)));
			arg_1 = IFIX(character_or_character_code);
			arg_2 = 
				IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9050L)));
			temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : 
				Qnil;
		    }
		    if (temp);
		    else {
			arg = 
				IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9537L)));
			arg_1 = IFIX(character_or_character_code);
			arg_2 = 
				IFIX(g2int_ksc_to_gensym_ksc(FIX((SI_Long)9560L)));
			temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : 
				Qnil;
		    }
		    if (temp);
		    else
			temp = (SI_Long)10017L <= 
				IFIX(character_or_character_code) ? 
				(IFIX(character_or_character_code) <= 
				(SI_Long)10049L ? T : Nil) : Qnil;
		    if (temp);
		    else {
			unicode_index = 
				FIXNUM_MINUS(character_or_character_code,
				G2int_gensym_cyrillic_character_block_start);
			temp = (SI_Long)16L <= IFIX(unicode_index) ? 
				(IFIX(unicode_index) <= (SI_Long)47L ? T : 
				Nil) : Qnil;
			if (temp);
			else
			    temp = (SI_Long)1L <= IFIX(unicode_index) ? 
				    (IFIX(unicode_index) <= (SI_Long)12L ? 
				    T : Nil) : Qnil;
			if (temp);
			else
			    temp = (SI_Long)14L <= IFIX(unicode_index) ? 
				    (IFIX(unicode_index) <= (SI_Long)15L ? 
				    T : Nil) : Qnil;
			if (temp);
			else
			    temp = (SI_Long)96L <= IFIX(unicode_index) && 
				    IFIX(unicode_index) <= (SI_Long)127L ? 
				    (FIXNUM_EVENP(unicode_index) ? T : 
				    Nil) : Qnil;
		    }
		}
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    else
	temp = ALPHA_CHAR_P(character_or_character_code) ? T : Nil;
    return VALUES_1(temp);
}

/* NUMERIC-GENSYM-CHARACTER-P */
Object g2int_numeric_gensym_character_p(character_or_character_code,
	    escape_character_qm)
    Object character_or_character_code, escape_character_qm;
{
    Object temp, start;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(14,17);
    if (escape_character_qm) {
	if ( !CHARACTERP(escape_character_qm))
	    temp = Nil;
	else
	    switch (ICHAR_CODE(escape_character_qm)) {
	      case '\\':
		temp = (SI_Long)9008L <= IFIX(character_or_character_code) 
			? (IFIX(character_or_character_code) <= 
			(SI_Long)9017L ? T : Nil) : Qnil;
		if (temp);
		else {
		    start = g2int_ksc_to_gensym_ksc(FIX((SI_Long)9008L));
		    arg = IFIX(start);
		    arg_1 = IFIX(character_or_character_code);
		    arg_2 = IFIX(start) + (SI_Long)10L - (SI_Long)1L;
		    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		}
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    else
	temp = digit_char_p(character_or_character_code,_);
    return VALUES_1(temp);
}

/* ALPHANUMERIC-GENSYM-CHARACTER-P */
Object g2int_alphanumeric_gensym_character_p(character_or_character_code,
	    escape_character_qm)
    Object character_or_character_code, escape_character_qm;
{
    Object temp;

    x_note_fn_call(14,18);
    temp = g2int_alphabetic_gensym_character_p(character_or_character_code,
	    escape_character_qm);
    if (temp);
    else
	temp = 
		g2int_numeric_gensym_character_p(character_or_character_code,
		escape_character_qm);
    return VALUES_1(temp);
}

/* MAKE-GENSYM-CHARACTER-STRING */
Object g2int_make_gensym_character_string(character_or_character_code,
	    escape_character_qm)
    Object character_or_character_code, escape_character_qm;
{
    Object gensym_string, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, quotient, remainder_1;
    SI_Long index_1;
    char gensymed_symbol_3;
    Object result;

    x_note_fn_call(14,19);
    gensym_string = Nil;
    if ( !TRUEP(escape_character_qm)) {
	gensym_string = g2int_obtain_simple_gensym_string(FIX((SI_Long)1L));
	SET_SCHAR(gensym_string,FIX((SI_Long)0L),character_or_character_code);
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	gensym_string = 
		g2int_obtain_simple_gensym_string(IFIX(character_or_character_code) 
		>>  -  - (SI_Long)13L == (SI_Long)1L ? FIX((SI_Long)3L) : 
		FIX((SI_Long)4L));
	index_1 = (SI_Long)0L;
	gensymed_symbol = character_or_character_code;
	gensymed_symbol_1 = gensym_string;
	gensymed_symbol_2 = T;
	result = g2int_chestnut_floorf_function(FIX(IFIX(gensymed_symbol) 
		& (SI_Long)8191L),FIX((SI_Long)95L));
	MVS_2(result,quotient,remainder_1);
	gensymed_symbol_3 = '\\';
	if (gensymed_symbol_2)
	    SET_ISCHAR(gensymed_symbol_1,index_1,gensymed_symbol_3);
	else
	    SET_ICHAR(gensymed_symbol_1,index_1,gensymed_symbol_3);
	index_1 = index_1 + (SI_Long)1L;
	if ( !(IFIX(gensymed_symbol) >>  -  - (SI_Long)13L == (SI_Long)1L)) {
	    gensymed_symbol = CODE_CHAR(FIX((IFIX(gensymed_symbol) >>  -  
		    - (SI_Long)13L) + (SI_Long)32L));
	    if (gensymed_symbol_2)
		SET_ISCHAR(gensymed_symbol_1,index_1,
			ICHAR_CODE(gensymed_symbol));
	    else
		SET_ICHAR(gensymed_symbol_1,index_1,
			ICHAR_CODE(gensymed_symbol));
	    index_1 = index_1 + (SI_Long)1L;
	}
	gensymed_symbol = CODE_CHAR(FIX(IFIX(quotient) + (SI_Long)40L));
	if (gensymed_symbol_2)
	    SET_ISCHAR(gensymed_symbol_1,index_1,ICHAR_CODE(gensymed_symbol));
	else
	    SET_ICHAR(gensymed_symbol_1,index_1,ICHAR_CODE(gensymed_symbol));
	index_1 = index_1 + (SI_Long)1L;
	gensymed_symbol = CODE_CHAR(FIX(IFIX(remainder_1) + (SI_Long)32L));
	if (gensymed_symbol_2)
	    SET_ISCHAR(gensymed_symbol_1,index_1,ICHAR_CODE(gensymed_symbol));
	else
	    SET_ICHAR(gensymed_symbol_1,index_1,ICHAR_CODE(gensymed_symbol));
	index_1 = index_1 + (SI_Long)1L;
    }
    else {
	gensym_string = g2int_obtain_simple_gensym_string(FIX((SI_Long)2L));
	SET_SCHAR(gensym_string,FIX((SI_Long)0L),escape_character_qm);
	SET_SCHAR(gensym_string,FIX((SI_Long)1L),character_or_character_code);
    }
    return VALUES_1(gensym_string);
}

/* UNICODE-LINE-SEPARATOR-FUNCTION */
Object g2int_unicode_line_separator_function()
{
    x_note_fn_call(14,20);
    return VALUES_1(FIX((SI_Long)8232L));
}

/* UNICODE-TAB-FUNCTION */
Object g2int_unicode_tab_function()
{
    x_note_fn_call(14,21);
    return VALUES_1(FIX((SI_Long)9L));
}

/* MAKE-CJK-CODE-MAPPING-VECTOR */
Object g2int_make_cjk_code_mapping_vector()
{
    x_note_fn_call(14,22);
    return make_array(5,FIX((SI_Long)307L),Kelement_type,T,
	    Kinitial_element,Nil);
}

/* SET-CJK-CODE-MAPPING */
Object g2int_set_cjk_code_mapping(cjk_code,cjk_code_mapping_vector,
	    corresponding_code_qm)
    Object cjk_code, cjk_code_mapping_vector, corresponding_code_qm;
{
    Object svref_new_value, temp_1;
    SI_Long temp;
    XDeclare_area(1);

    x_note_fn_call(14,23);
    if (PUSH_AREA(Dynamic_area,0)) {
	temp = IFIX(cjk_code) % (SI_Long)307L;
	svref_new_value = set_getf(ISVREF(cjk_code_mapping_vector,temp),
		cjk_code,corresponding_code_qm);
	ISVREF(cjk_code_mapping_vector,temp) = svref_new_value;
	temp_1 = corresponding_code_qm;
    }
    POP_AREA(0);
    return VALUES_1(temp_1);
}

Object G2int_unicode_jis_x_0208_mapping_hand_edits = UNBOUND;

Object G2int_char_backspace = UNBOUND;

Object G2int_char_tab = UNBOUND;

Object G2int_char_linefeed = UNBOUND;

Object G2int_char_page = UNBOUND;

Object G2int_char_return = UNBOUND;

Object G2int_char_rubout = UNBOUND;

Object G2int_char_control_at = UNBOUND;

Object G2int_char_control_a = UNBOUND;

Object G2int_char_control_b = UNBOUND;

Object G2int_char_control_c = UNBOUND;

Object G2int_char_control_d = UNBOUND;

Object G2int_char_control_e = UNBOUND;

Object G2int_char_control_f = UNBOUND;

Object G2int_char_control_g = UNBOUND;

Object G2int_char_control_h = UNBOUND;

Object G2int_char_control_i = UNBOUND;

Object G2int_char_control_j = UNBOUND;

Object G2int_char_control_k = UNBOUND;

Object G2int_char_control_l = UNBOUND;

Object G2int_char_control_m = UNBOUND;

Object G2int_char_control_n = UNBOUND;

Object G2int_char_control_o = UNBOUND;

Object G2int_char_control_p = UNBOUND;

Object G2int_char_control_q = UNBOUND;

Object G2int_char_control_r = UNBOUND;

Object G2int_char_control_s = UNBOUND;

Object G2int_char_control_t = UNBOUND;

Object G2int_char_control_u = UNBOUND;

Object G2int_char_control_v = UNBOUND;

Object G2int_char_control_w = UNBOUND;

Object G2int_char_control_x = UNBOUND;

Object G2int_char_control_y = UNBOUND;

Object G2int_char_control_z = UNBOUND;

Object G2int_char_control_obt = UNBOUND;

Object G2int_char_control_backslash = UNBOUND;

Object G2int_char_control_cbt = UNBOUND;

Object G2int_char_control_ct = UNBOUND;

Object G2int_char_control__ = UNBOUND;

Object G2int_char_escape = UNBOUND;

Object G2int_whitespace_characters = UNBOUND;

Object G2int_whitespace_wide_characters = UNBOUND;

void characters_INIT()
{
    Object temp, the_array, char_qm, code_qm, vector_1, x, ab_loop_list_, g;
    Object u_1, ab_loop_iter_flag_;
    SI_Long gensymed_symbol, i, ab_loop_bind_, g_row, u_row;
    Object list_constant_11, list_constant_10, Qg2int_char_escape, AB_package;
    Object Qg2int_char_control__, Qg2int_char_control_ct;
    Object Qg2int_char_control_cbt, Qg2int_char_control_backslash;
    Object Qg2int_char_control_obt, Qg2int_char_control_z;
    Object Qg2int_char_control_y, Qg2int_char_control_x, Qg2int_char_control_w;
    Object Qg2int_char_control_v, Qg2int_char_control_u, Qg2int_char_control_t;
    Object Qg2int_char_control_s, Qg2int_char_control_r, Qg2int_char_control_q;
    Object Qg2int_char_control_p, Qg2int_char_control_o, Qg2int_char_control_n;
    Object Qg2int_char_control_m, Qg2int_char_control_l, Qg2int_char_control_k;
    Object Qg2int_char_control_j, Qg2int_char_control_i, Qg2int_char_control_h;
    Object Qg2int_char_control_g, Qg2int_char_control_f, Qg2int_char_control_e;
    Object Qg2int_char_control_d, Qg2int_char_control_c, Qg2int_char_control_b;
    Object Qg2int_char_control_a, Qg2int_char_control_at, Qg2int_char_rubout;
    Object Qg2int_char_return, Qg2int_char_page, Qg2int_char_linefeed;
    Object Qg2int_char_tab, Qg2int_char_backspace;
    Object Qg2int_unicode_thai_glyph_variants_end;
    Object Qg2int_unicode_thai_glyph_variants_start;
    Object Qg2int_unicode_thai_character_block_end;
    Object Qg2int_unicode_thai_character_block_start;
    Object Qg2int_unicode_hebrew_precomposed_character_block_end;
    Object Qg2int_unicode_hebrew_precomposed_character_block_start;
    Object Qg2int_unicode_hebrew_character_block_end;
    Object Qg2int_unicode_hebrew_character_block_start, list_constant_9;
    Object list_constant_8, list_constant_7, list_constant_6, list_constant_5;
    Object list_constant_4, list_constant_3, list_constant_2;
    Object Qg2int_unicode_general_punctuation_character_block_start;
    Object Qg2int_gensym_general_punctuation_character_block_start;
    Object Qg2int_unicode_letterlike_symbol_block_start;
    Object Qg2int_gensym_letterlike_symbol_block_start, list_constant_1;
    Object Qg2int_invalid_gensym_full_row, Qg2int_invalid_unicode_full_row;
    Object string_constant_7, string_constant_6, string_constant_5;
    Object Qg2int_iso_8859_5_offset_within_cyrillic_character_block;
    Object Qg2int_unicode_cyrillic_character_block_start;
    Object Qg2int_number_of_contiguous_gb2312_codes, Qg2int_gb_low_byte_max;
    Object Qg2int_gb_low_byte_min, Qg2int_gb_high_byte_max;
    Object Qg2int_gb_high_byte_min, list_constant;
    Object Qg2int_ksc_last_contiguous_code, Qg2int_ksc_undefined_start;
    Object Qg2int_ksc_hanja_start, Qg2int_ksc_hangul_start;
    Object Qg2int_ksc_symbols_1_start, Qg2int_ksc_low_byte_max;
    Object Qg2int_ksc_low_byte_min, Qg2int_ksc_high_byte_max;
    Object Qg2int_ksc_high_byte_min, Qg2int_ksc_low_byte_offset;
    Object Qg2int_jis_low_byte_offset, Qg2int_jis_low_byte_max;
    Object Qg2int_jis_low_byte_min, Qg2int_jis_high_byte_max;
    Object Qg2int_jis_high_byte_min, Qg2int_jis_last_contiguous_code;
    Object Qg2int_jis_undefined_start, Qg2int_jis_level_2_kanji_start;
    Object Qg2int_jis_level_1_kanji_start;
    Object Qg2int_jis_ruled_line_elements_start;
    Object Qg2int_jis_lower_case_cyrillic_start;
    Object Qg2int_jis_upper_case_cyrillic_start;
    Object Qg2int_jis_lower_case_greek_start;
    Object Qg2int_jis_upper_case_greek_start, Qg2int_jis_katakana_start;
    Object Qg2int_jis_hiragana_start, Qg2int_jis_lower_case_roman_start;
    Object Qg2int_jis_upper_case_roman_start, Qg2int_jis_numbers_start;
    Object Qg2int_jis_symbols_90_5_start, Qg2int_jis_symbols_90_4_start;
    Object Qg2int_jis_symbols_90_3_start, Qg2int_jis_symbols_90_2_start;
    Object Qg2int_jis_symbols_90_1_start, Qg2int_jis_symbols_2_start;
    Object Qg2int_jis_symbols_1_start, Qg2int_jis_lower_case_cyrillic_offset;
    Object Qg2int_jis_lower_case_greek_offset;
    Object Qg2int_jis_lower_case_roman_offset;
    Object Qg2int_jis_upper_case_roman_offset, Qg2int_jis_numbers_offset;
    Object Qg2int_jis_symbols_90_5_offset, Qg2int_jis_symbols_90_4_offset;
    Object Qg2int_jis_symbols_90_3_offset, Qg2int_jis_symbols_90_2_offset;
    Object Qg2int_jis_symbols_90_1_offset, Qg2int_jis_undefined_byte;
    Object Qg2int_jis_level_2_kanji_high_byte;
    Object Qg2int_jis_level_1_kanji_high_byte;
    Object Qg2int_jis_ruled_line_elements_high_byte;
    Object Qg2int_jis_cyrillic_high_byte, Qg2int_jis_greek_high_byte;
    Object Qg2int_jis_katakana_high_byte, Qg2int_jis_hiragana_high_byte;
    Object Qg2int_jis_roman_high_byte, Qg2int_jis_symbols_2_high_byte;
    Object Qg2int_jis_symbols_1_high_byte;
    Object Qg2int_gensym_cyrillic_character_block_start, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant_1;
    Object string_constant, Kascii;

    x_note_fn_call(14,24);
    SET_PACKAGE("AB");
    Kascii = STATIC_SYMBOL("ASCII",Pkeyword);
    temp = adjoin(2,Kascii,Features);
    Features = temp;
    G2int_maximum_suggested_length_for_simple_gensym_strings = 
	    FIX((SI_Long)64L);
    string_constant = 
	    STATIC_STRING("13-Sy03*Uy03*ay3*by3*Qy3*cy0003*dy000003*Fy3*Gy3*Hy3*Iy3*Jy3*Ky3*Ly3*My3*1y3*2y3*Ry3*Sy3*Xy03*Yy3*Ty3-+ylmnop3*0yq3*6yrs003*4ytu");
    string_constant_1 = 
	    STATIC_STRING("vwx03**yyz3*-y3*Ay3*Cy3*Ey03-Oy00003Cy3Dy3Ey3Fy3Gy3*=y3Hy3*5y3Iy3Jy003*3y3Ky3Ly3My3Ny3Oy3Ry3*8y3Py3Qy3*+y3*By3*7y3*Dy03*9y03-wy0");
    if (G2int_roman_font_special_character_code_map == UNBOUND)
	G2int_roman_font_special_character_code_map = make_array(3,
		FIX((SI_Long)96L),Kinitial_contents,
		g2int_regenerate_optimized_constant(LIST_2(string_constant,
		string_constant_1)));
    string_constant_2 = 
	    STATIC_STRING("130+y00000000000000000000000000000000000000000000000000000000000000006@0000000000000000000000000006\\0000000000000000000000000000");
    string_constant_3 = 
	    STATIC_STRING("000006~00000000000000000000000000000000006!6%6#06$0006|06<006;0000000000006>0006\?6M6B6D656A6R6X6C6G6E6F616H6I6J6306N6Y6P6Q676O06");
    string_constant_4 = 
	    STATIC_STRING("T6Z6V696U006s6m6b6d646a6r6x6c6g6e6f606h6i6j6206n6y6p6q666o06t6z6v686u000");
    if (G2int_iso_latin1_special_character_code_map == UNBOUND)
	G2int_iso_latin1_special_character_code_map = make_array(3,
		FIX((SI_Long)256L),Kinitial_contents,
		g2int_regenerate_optimized_constant(LIST_3(string_constant_2,
		string_constant_3,string_constant_4)));
    if (G2int_reverse_iso_latin1_special_character_code_map == UNBOUND) {
	gensymed_symbol = (SI_Long)256L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	G2int_reverse_iso_latin1_special_character_code_map = the_array;
    }
    i = (SI_Long)0L;
    char_qm = Nil;
    code_qm = Nil;
  next_loop_1:
    if (i >= (SI_Long)256L)
	goto end_loop_1;
    char_qm = ISVREF(G2int_iso_latin1_special_character_code_map,i);
    code_qm = char_qm ? CHAR_CODE(char_qm) : Nil;
    if (code_qm) {
	temp = G2int_reverse_iso_latin1_special_character_code_map;
	SVREF(temp,code_qm) = FIX(i);
    }
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_gensym_cyrillic_character_block_start = 
	    STATIC_SYMBOL("GENSYM-CYRILLIC-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gensym_cyrillic_character_block_start,
	    FIX((SI_Long)8192L));
    Qg2int_jis_symbols_1_high_byte = 
	    STATIC_SYMBOL("JIS-SYMBOLS-1-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_1_high_byte,FIX((SI_Long)33L));
    Qg2int_jis_symbols_2_high_byte = 
	    STATIC_SYMBOL("JIS-SYMBOLS-2-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_2_high_byte,FIX((SI_Long)34L));
    Qg2int_jis_roman_high_byte = STATIC_SYMBOL("JIS-ROMAN-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_roman_high_byte,FIX((SI_Long)35L));
    Qg2int_jis_hiragana_high_byte = STATIC_SYMBOL("JIS-HIRAGANA-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_hiragana_high_byte,FIX((SI_Long)36L));
    Qg2int_jis_katakana_high_byte = STATIC_SYMBOL("JIS-KATAKANA-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_katakana_high_byte,FIX((SI_Long)37L));
    Qg2int_jis_greek_high_byte = STATIC_SYMBOL("JIS-GREEK-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_greek_high_byte,FIX((SI_Long)38L));
    Qg2int_jis_cyrillic_high_byte = STATIC_SYMBOL("JIS-CYRILLIC-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_cyrillic_high_byte,FIX((SI_Long)39L));
    Qg2int_jis_ruled_line_elements_high_byte = 
	    STATIC_SYMBOL("JIS-RULED-LINE-ELEMENTS-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_ruled_line_elements_high_byte,
	    FIX((SI_Long)40L));
    Qg2int_jis_level_1_kanji_high_byte = 
	    STATIC_SYMBOL("JIS-LEVEL-1-KANJI-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_level_1_kanji_high_byte,FIX((SI_Long)48L));
    Qg2int_jis_level_2_kanji_high_byte = 
	    STATIC_SYMBOL("JIS-LEVEL-2-KANJI-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_level_2_kanji_high_byte,FIX((SI_Long)80L));
    Qg2int_jis_undefined_byte = STATIC_SYMBOL("JIS-UNDEFINED-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_undefined_byte,FIX((SI_Long)117L));
    Qg2int_jis_symbols_90_1_offset = 
	    STATIC_SYMBOL("JIS-SYMBOLS-90-1-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_1_offset,FIX((SI_Long)25L));
    Qg2int_jis_symbols_90_2_offset = 
	    STATIC_SYMBOL("JIS-SYMBOLS-90-2-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_2_offset,FIX((SI_Long)41L));
    Qg2int_jis_symbols_90_3_offset = 
	    STATIC_SYMBOL("JIS-SYMBOLS-90-3-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_3_offset,FIX((SI_Long)59L));
    Qg2int_jis_symbols_90_4_offset = 
	    STATIC_SYMBOL("JIS-SYMBOLS-90-4-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_4_offset,FIX((SI_Long)81L));
    Qg2int_jis_symbols_90_5_offset = 
	    STATIC_SYMBOL("JIS-SYMBOLS-90-5-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_5_offset,FIX((SI_Long)93L));
    Qg2int_jis_numbers_offset = STATIC_SYMBOL("JIS-NUMBERS-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_numbers_offset,FIX((SI_Long)15L));
    Qg2int_jis_upper_case_roman_offset = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-ROMAN-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_upper_case_roman_offset,FIX((SI_Long)32L));
    Qg2int_jis_lower_case_roman_offset = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-ROMAN-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_lower_case_roman_offset,FIX((SI_Long)64L));
    Qg2int_jis_lower_case_greek_offset = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-GREEK-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_lower_case_greek_offset,FIX((SI_Long)32L));
    Qg2int_jis_lower_case_cyrillic_offset = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-CYRILLIC-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_lower_case_cyrillic_offset,FIX((SI_Long)48L));
    Qg2int_jis_symbols_1_start = STATIC_SYMBOL("JIS-SYMBOLS-1-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_1_start,FIX((SI_Long)0L));
    Qg2int_jis_symbols_2_start = STATIC_SYMBOL("JIS-SYMBOLS-2-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_2_start,FIX((SI_Long)94L));
    Qg2int_jis_symbols_90_1_start = STATIC_SYMBOL("JIS-SYMBOLS-90-1-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_1_start,FIX((SI_Long)108L));
    Qg2int_jis_symbols_90_2_start = STATIC_SYMBOL("JIS-SYMBOLS-90-2-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_2_start,FIX((SI_Long)116L));
    Qg2int_jis_symbols_90_3_start = STATIC_SYMBOL("JIS-SYMBOLS-90-3-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_3_start,FIX((SI_Long)123L));
    Qg2int_jis_symbols_90_4_start = STATIC_SYMBOL("JIS-SYMBOLS-90-4-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_4_start,FIX((SI_Long)138L));
    Qg2int_jis_symbols_90_5_start = STATIC_SYMBOL("JIS-SYMBOLS-90-5-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_symbols_90_5_start,FIX((SI_Long)146L));
    Qg2int_jis_numbers_start = STATIC_SYMBOL("JIS-NUMBERS-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_numbers_start,FIX((SI_Long)147L));
    Qg2int_jis_upper_case_roman_start = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-ROMAN-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_upper_case_roman_start,FIX((SI_Long)157L));
    Qg2int_jis_lower_case_roman_start = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-ROMAN-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_lower_case_roman_start,FIX((SI_Long)183L));
    Qg2int_jis_hiragana_start = STATIC_SYMBOL("JIS-HIRAGANA-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_hiragana_start,FIX((SI_Long)209L));
    Qg2int_jis_katakana_start = STATIC_SYMBOL("JIS-KATAKANA-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_katakana_start,FIX((SI_Long)292L));
    Qg2int_jis_upper_case_greek_start = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-GREEK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_upper_case_greek_start,FIX((SI_Long)378L));
    Qg2int_jis_lower_case_greek_start = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-GREEK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_lower_case_greek_start,FIX((SI_Long)402L));
    Qg2int_jis_upper_case_cyrillic_start = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-CYRILLIC-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_upper_case_cyrillic_start,FIX((SI_Long)426L));
    Qg2int_jis_lower_case_cyrillic_start = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-CYRILLIC-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_lower_case_cyrillic_start,FIX((SI_Long)459L));
    Qg2int_jis_ruled_line_elements_start = 
	    STATIC_SYMBOL("JIS-RULED-LINE-ELEMENTS-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_ruled_line_elements_start,FIX((SI_Long)492L));
    Qg2int_jis_level_1_kanji_start = 
	    STATIC_SYMBOL("JIS-LEVEL-1-KANJI-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_level_1_kanji_start,FIX((SI_Long)524L));
    Qg2int_jis_level_2_kanji_start = 
	    STATIC_SYMBOL("JIS-LEVEL-2-KANJI-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_level_2_kanji_start,FIX((SI_Long)3489L));
    Qg2int_jis_undefined_start = STATIC_SYMBOL("JIS-UNDEFINED-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_undefined_start,FIX((SI_Long)6879L));
    Qg2int_jis_last_contiguous_code = 
	    STATIC_SYMBOL("JIS-LAST-CONTIGUOUS-CODE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_jis_last_contiguous_code,
	    G2int_jis_last_contiguous_code);
    SET_SYMBOL_VALUE(Qg2int_jis_last_contiguous_code,
	    FIXNUM_SUB1(G2int_jis_undefined_start));
    Qg2int_jis_high_byte_min = STATIC_SYMBOL("JIS-HIGH-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_high_byte_min,FIX((SI_Long)33L));
    Qg2int_jis_high_byte_max = STATIC_SYMBOL("JIS-HIGH-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_high_byte_max,FIX((SI_Long)116L));
    Qg2int_jis_low_byte_min = STATIC_SYMBOL("JIS-LOW-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_low_byte_min,FIX((SI_Long)33L));
    Qg2int_jis_low_byte_max = STATIC_SYMBOL("JIS-LOW-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_low_byte_max,FIX((SI_Long)126L));
    Qg2int_jis_low_byte_offset = STATIC_SYMBOL("JIS-LOW-BYTE-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_low_byte_offset,FIX((SI_Long)0L));
    if (G2int_number_of_ksc_codes == UNBOUND)
	G2int_number_of_ksc_codes = FIX((SI_Long)8224L);
    Qg2int_ksc_low_byte_offset = STATIC_SYMBOL("KSC-LOW-BYTE-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_low_byte_offset,FIX((SI_Long)94L));
    Qg2int_ksc_high_byte_min = STATIC_SYMBOL("KSC-HIGH-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_high_byte_min,FIX((SI_Long)33L));
    Qg2int_ksc_high_byte_max = STATIC_SYMBOL("KSC-HIGH-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_high_byte_max,FIX((SI_Long)125L));
    Qg2int_ksc_low_byte_min = STATIC_SYMBOL("KSC-LOW-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_low_byte_min,FIX((SI_Long)33L));
    Qg2int_ksc_low_byte_max = STATIC_SYMBOL("KSC-LOW-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_low_byte_max,FIX((SI_Long)126L));
    Qg2int_ksc_symbols_1_start = STATIC_SYMBOL("KSC-SYMBOLS-1-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_symbols_1_start,FIX((SI_Long)0L));
    Qg2int_ksc_hangul_start = STATIC_SYMBOL("KSC-HANGUL-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_hangul_start,FIX((SI_Long)986L));
    Qg2int_ksc_hanja_start = STATIC_SYMBOL("KSC-HANJA-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_hanja_start,FIX((SI_Long)3336L));
    Qg2int_ksc_undefined_start = STATIC_SYMBOL("KSC-UNDEFINED-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ksc_undefined_start,FIX((SI_Long)8224L));
    Qg2int_ksc_last_contiguous_code = 
	    STATIC_SYMBOL("KSC-LAST-CONTIGUOUS-CODE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ksc_last_contiguous_code,
	    G2int_ksc_last_contiguous_code);
    SET_SYMBOL_VALUE(Qg2int_ksc_last_contiguous_code,
	    FIXNUM_SUB1(G2int_ksc_undefined_start));
    list_constant = STATIC_LIST((SI_Long)21L,FIX((SI_Long)94L),
	    FIX((SI_Long)69L),FIX((SI_Long)94L),FIX((SI_Long)94L),
	    FIX((SI_Long)10L),FIX((SI_Long)10L),FIX((SI_Long)24L),
	    FIX((SI_Long)24L),FIX((SI_Long)68L),FIX((SI_Long)79L),
	    FIX((SI_Long)4L),FIX((SI_Long)1L),FIX((SI_Long)8L),
	    FIX((SI_Long)78L),FIX((SI_Long)94L),FIX((SI_Long)83L),
	    FIX((SI_Long)86L),FIX((SI_Long)33L),FIX((SI_Long)33L),
	    FIX((SI_Long)2350L),FIX((SI_Long)4888L));
    if (G2int_ksc_contiguous_character_group_lengths == UNBOUND)
	G2int_ksc_contiguous_character_group_lengths = list_constant;
    Qg2int_gb_high_byte_min = STATIC_SYMBOL("GB-HIGH-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gb_high_byte_min,FIX((SI_Long)33L));
    Qg2int_gb_high_byte_max = STATIC_SYMBOL("GB-HIGH-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gb_high_byte_max,FIX((SI_Long)119L));
    Qg2int_gb_low_byte_min = STATIC_SYMBOL("GB-LOW-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gb_low_byte_min,FIX((SI_Long)33L));
    Qg2int_gb_low_byte_max = STATIC_SYMBOL("GB-LOW-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gb_low_byte_max,FIX((SI_Long)126L));
    Qg2int_number_of_contiguous_gb2312_codes = 
	    STATIC_SYMBOL("NUMBER-OF-CONTIGUOUS-GB2312-CODES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_contiguous_gb2312_codes,
	    FIX((SI_Long)8178L));
    Qg2int_unicode_cyrillic_character_block_start = 
	    STATIC_SYMBOL("UNICODE-CYRILLIC-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_cyrillic_character_block_start,
	    FIX((SI_Long)1024L));
    Qg2int_iso_8859_5_offset_within_cyrillic_character_block = 
	    STATIC_SYMBOL("ISO-8859-5-OFFSET-WITHIN-CYRILLIC-CHARACTER-BLOCK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_iso_8859_5_offset_within_cyrillic_character_block,
	    FIX((SI_Long)0L));
    if (G2int_unicode_offset_for_gensym_cyrillic == UNBOUND)
	G2int_unicode_offset_for_gensym_cyrillic = 
		FIXNUM_MINUS(G2int_gensym_cyrillic_character_block_start,
		G2int_unicode_cyrillic_character_block_start);
    G2int_cyrillic_character_a_list = Nil;
    if (G2int_msw_cyrillic_code_map == UNBOUND) {
	gensymed_symbol = (SI_Long)128L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	G2int_msw_cyrillic_code_map = the_array;
    }
    if (G2int_unicode_index_to_slavic_font_direct_index_map == UNBOUND) {
	gensymed_symbol = (SI_Long)128L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop_3:
	if (i >= ab_loop_bind_)
	    goto end_loop_3;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	G2int_unicode_index_to_slavic_font_direct_index_map = the_array;
    }
    Qg2int_cyrillic_gensym_character_code_for_key_name = 
	    STATIC_SYMBOL("CYRILLIC-GENSYM-CHARACTER-CODE-FOR-KEY-NAME",
	    AB_package);
    G2int_cyrillic_gensym_character_code_for_key_name_prop = 
	    Qg2int_cyrillic_gensym_character_code_for_key_name;
    if (G2int_key_cap_to_gensym_cyrillic_character_code_map == UNBOUND) {
	gensymed_symbol = (SI_Long)128L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop_4:
	if (i >= ab_loop_bind_)
	    goto end_loop_4;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
	G2int_key_cap_to_gensym_cyrillic_character_code_map = the_array;
    }
    g2int_utilize_cyrillic_character_a_list();
    string_constant_5 = 
	    STATIC_STRING("13Vy1mkk1mll1mmm1mnn1m3Syo1mop1mpq1mqt1mru1msv1mtw1mux1mvy1mw3Cy1mx3Dy1my3Qy1mz3Ry1m3Cy3Sy1m3Dy3Ty1m3Ey3Uy1m3Fy3Vy1m3Gy3Wy1m3Hy3");
    string_constant_6 = 
	    STATIC_STRING("Xy1m3Iy3Yy1m3Jy3Zy1m3Ky3iy1m3Ly3jy1m3My3ky1m3Ny3ly1m1m3-xy3=cy1m3my3*Ry1m1m3=ry3=sy1m3=ry3=sy1m3=ty3=ty1m1m3=uy3=vy1m3=uy3=vy1m3");
    string_constant_7 = STATIC_STRING("=wy3=wy1m3=xy3=xy");
    G2int_gensym_unicode_row_correspondences = 
	    g2int_regenerate_optimized_constant(LIST_3(string_constant_5,
	    string_constant_6,string_constant_7));
    Qg2int_invalid_unicode_full_row = 
	    STATIC_SYMBOL("INVALID-UNICODE-FULL-ROW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_invalid_unicode_full_row,FIX((SI_Long)7L));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    vector_1 = make_array(5,FIX((SI_Long)256L),Kelement_type,
	    list_constant_1,Kinitial_element,G2int_invalid_unicode_full_row);
    x = Nil;
    ab_loop_list_ = G2int_gensym_unicode_row_correspondences;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(THIRD(x))) {
	g = FIRST(x);
	u_1 = SECOND(x);
	if (CONSP(g)) {
	    g_row = IFIX(FIRST(g));
	    ab_loop_bind_ = IFIX(SECOND(g));
	    u_row = IFIX(FIRST(u_1));
	    ab_loop_iter_flag_ = T;
	  next_loop_6:
	    if (g_row > ab_loop_bind_)
		goto end_loop_6;
	    if ( !TRUEP(ab_loop_iter_flag_))
		u_row = u_row + (SI_Long)1L;
	    set_aref1(vector_1,FIX(g_row),FIX(u_row));
	    ab_loop_iter_flag_ = Nil;
	    g_row = g_row + (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	}
	else
	    set_aref1(vector_1,g,u_1);
    }
    goto next_loop_5;
  end_loop_5:
    G2int_gensym_to_unicode_full_row_map = vector_1;
    goto end;
    G2int_gensym_to_unicode_full_row_map = Qnil;
  end:;
    Qg2int_invalid_gensym_full_row = 
	    STATIC_SYMBOL("INVALID-GENSYM-FULL-ROW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_invalid_gensym_full_row,FIX((SI_Long)246L));
    vector_1 = make_array(5,FIX((SI_Long)256L),Kelement_type,
	    list_constant_1,Kinitial_element,G2int_invalid_gensym_full_row);
    x = Nil;
    ab_loop_list_ = G2int_gensym_unicode_row_correspondences;
  next_loop_7:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_7;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(THIRD(x))) {
	g = FIRST(x);
	u_1 = SECOND(x);
	if (CONSP(g)) {
	    g_row = IFIX(FIRST(g));
	    ab_loop_bind_ = IFIX(SECOND(g));
	    u_row = IFIX(FIRST(u_1));
	    ab_loop_iter_flag_ = T;
	  next_loop_8:
	    if (g_row > ab_loop_bind_)
		goto end_loop_8;
	    if ( !TRUEP(ab_loop_iter_flag_))
		u_row = u_row + (SI_Long)1L;
	    set_aref1(vector_1,FIX(u_row),FIX(g_row));
	    ab_loop_iter_flag_ = Nil;
	    g_row = g_row + (SI_Long)1L;
	    goto next_loop_8;
	  end_loop_8:;
	}
	else
	    set_aref1(vector_1,u_1,g);
    }
    goto next_loop_7;
  end_loop_7:
    G2int_unicode_to_gensym_full_row_map = vector_1;
    goto end_1;
    G2int_unicode_to_gensym_full_row_map = Qnil;
  end_1:;
    Qg2int_gensym_letterlike_symbol_block_start = 
	    STATIC_SYMBOL("GENSYM-LETTERLIKE-SYMBOL-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gensym_letterlike_symbol_block_start,
	    FIX((SI_Long)4352L));
    Qg2int_unicode_letterlike_symbol_block_start = 
	    STATIC_SYMBOL("UNICODE-LETTERLIKE-SYMBOL-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_letterlike_symbol_block_start,
	    FIX((SI_Long)8448L));
    if (G2int_unicode_offset_for_gensym_letterlike_symbol == UNBOUND)
	G2int_unicode_offset_for_gensym_letterlike_symbol = 
		FIXNUM_MINUS(G2int_gensym_letterlike_symbol_block_start,
		G2int_unicode_letterlike_symbol_block_start);
    Qg2int_gensym_general_punctuation_character_block_start = 
	    STATIC_SYMBOL("GENSYM-GENERAL-PUNCTUATION-CHARACTER-BLOCK-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gensym_general_punctuation_character_block_start,
	    FIX((SI_Long)4096L));
    Qg2int_unicode_general_punctuation_character_block_start = 
	    STATIC_SYMBOL("UNICODE-GENERAL-PUNCTUATION-CHARACTER-BLOCK-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_general_punctuation_character_block_start,
	    FIX((SI_Long)8192L));
    if (G2int_unicode_offset_for_gensym_general_punctuation == UNBOUND)
	G2int_unicode_offset_for_gensym_general_punctuation = 
		FIXNUM_MINUS(G2int_gensym_general_punctuation_character_block_start,
		G2int_unicode_general_punctuation_character_block_start);
    list_constant_2 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)65340L),
	    FIX((SI_Long)8512L),FIX((SI_Long)92L),Qt);
    list_constant_3 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)65374L),
	    FIX((SI_Long)8513L),FIX((SI_Long)12316L));
    list_constant_4 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)8741L),
	    FIX((SI_Long)8514L),FIX((SI_Long)8214L));
    list_constant_5 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)65293L),
	    FIX((SI_Long)8541L),FIX((SI_Long)8722L));
    list_constant_6 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)65504L),
	    FIX((SI_Long)8561L),FIX((SI_Long)162L));
    list_constant_7 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)65505L),
	    FIX((SI_Long)8562L),FIX((SI_Long)163L));
    list_constant_8 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)65506L),
	    FIX((SI_Long)8780L),FIX((SI_Long)172L));
    list_constant_9 = STATIC_LIST((SI_Long)7L,list_constant_2,
	    list_constant_3,list_constant_4,list_constant_5,
	    list_constant_6,list_constant_7,list_constant_8);
    G2int_unicode_jis_x_0208_mapping_hand_edits = list_constant_9;
    Qg2int_unicode_hebrew_character_block_start = 
	    STATIC_SYMBOL("UNICODE-HEBREW-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_hebrew_character_block_start,
	    FIX((SI_Long)1456L));
    Qg2int_unicode_hebrew_character_block_end = 
	    STATIC_SYMBOL("UNICODE-HEBREW-CHARACTER-BLOCK-END",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_hebrew_character_block_end,
	    FIX((SI_Long)1524L));
    Qg2int_unicode_hebrew_precomposed_character_block_start = 
	    STATIC_SYMBOL("UNICODE-HEBREW-PRECOMPOSED-CHARACTER-BLOCK-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_hebrew_precomposed_character_block_start,
	    FIX((SI_Long)64285L));
    Qg2int_unicode_hebrew_precomposed_character_block_end = 
	    STATIC_SYMBOL("UNICODE-HEBREW-PRECOMPOSED-CHARACTER-BLOCK-END",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_hebrew_precomposed_character_block_end,
	    FIX((SI_Long)64335L));
    Qg2int_unicode_thai_character_block_start = 
	    STATIC_SYMBOL("UNICODE-THAI-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_thai_character_block_start,
	    FIX((SI_Long)3584L));
    Qg2int_unicode_thai_character_block_end = 
	    STATIC_SYMBOL("UNICODE-THAI-CHARACTER-BLOCK-END",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_thai_character_block_end,
	    FIX((SI_Long)3711L));
    Qg2int_unicode_thai_glyph_variants_start = 
	    STATIC_SYMBOL("UNICODE-THAI-GLYPH-VARIANTS-START",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_thai_glyph_variants_start,
	    FIX((SI_Long)63232L));
    Qg2int_unicode_thai_glyph_variants_end = 
	    STATIC_SYMBOL("UNICODE-THAI-GLYPH-VARIANTS-END",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_thai_glyph_variants_end,
	    FIX((SI_Long)63247L));
    Qg2int_char_backspace = STATIC_SYMBOL("CHAR-BACKSPACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_backspace,G2int_char_backspace);
    SET_SYMBOL_VALUE(Qg2int_char_backspace,CODE_CHAR(FIX((SI_Long)8L)));
    Qg2int_char_tab = STATIC_SYMBOL("CHAR-TAB",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_tab,G2int_char_tab);
    SET_SYMBOL_VALUE(Qg2int_char_tab,CODE_CHAR(FIX((SI_Long)9L)));
    Qg2int_char_linefeed = STATIC_SYMBOL("CHAR-LINEFEED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_linefeed,G2int_char_linefeed);
    SET_SYMBOL_VALUE(Qg2int_char_linefeed,CODE_CHAR(FIX((SI_Long)10L)));
    Qg2int_char_page = STATIC_SYMBOL("CHAR-PAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_page,G2int_char_page);
    SET_SYMBOL_VALUE(Qg2int_char_page,CODE_CHAR(FIX((SI_Long)12L)));
    Qg2int_char_return = STATIC_SYMBOL("CHAR-RETURN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_return,G2int_char_return);
    SET_SYMBOL_VALUE(Qg2int_char_return,CODE_CHAR(FIX((SI_Long)13L)));
    Qg2int_char_rubout = STATIC_SYMBOL("CHAR-RUBOUT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_rubout,G2int_char_rubout);
    SET_SYMBOL_VALUE(Qg2int_char_rubout,CODE_CHAR(FIX((SI_Long)127L)));
    Qg2int_char_control_at = STATIC_SYMBOL("CHAR-CONTROL-@",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_at,G2int_char_control_at);
    SET_SYMBOL_VALUE(Qg2int_char_control_at,CODE_CHAR(FIX((SI_Long)0L)));
    Qg2int_char_control_a = STATIC_SYMBOL("CHAR-CONTROL-A",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_a,G2int_char_control_a);
    SET_SYMBOL_VALUE(Qg2int_char_control_a,CODE_CHAR(FIX((SI_Long)1L)));
    Qg2int_char_control_b = STATIC_SYMBOL("CHAR-CONTROL-B",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_b,G2int_char_control_b);
    SET_SYMBOL_VALUE(Qg2int_char_control_b,CODE_CHAR(FIX((SI_Long)2L)));
    Qg2int_char_control_c = STATIC_SYMBOL("CHAR-CONTROL-C",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_c,G2int_char_control_c);
    SET_SYMBOL_VALUE(Qg2int_char_control_c,CODE_CHAR(FIX((SI_Long)3L)));
    Qg2int_char_control_d = STATIC_SYMBOL("CHAR-CONTROL-D",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_d,G2int_char_control_d);
    SET_SYMBOL_VALUE(Qg2int_char_control_d,CODE_CHAR(FIX((SI_Long)4L)));
    Qg2int_char_control_e = STATIC_SYMBOL("CHAR-CONTROL-E",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_e,G2int_char_control_e);
    SET_SYMBOL_VALUE(Qg2int_char_control_e,CODE_CHAR(FIX((SI_Long)5L)));
    Qg2int_char_control_f = STATIC_SYMBOL("CHAR-CONTROL-F",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_f,G2int_char_control_f);
    SET_SYMBOL_VALUE(Qg2int_char_control_f,CODE_CHAR(FIX((SI_Long)6L)));
    Qg2int_char_control_g = STATIC_SYMBOL("CHAR-CONTROL-G",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_g,G2int_char_control_g);
    SET_SYMBOL_VALUE(Qg2int_char_control_g,CODE_CHAR(FIX((SI_Long)7L)));
    Qg2int_char_control_h = STATIC_SYMBOL("CHAR-CONTROL-H",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_h,G2int_char_control_h);
    SET_SYMBOL_VALUE(Qg2int_char_control_h,CODE_CHAR(FIX((SI_Long)8L)));
    Qg2int_char_control_i = STATIC_SYMBOL("CHAR-CONTROL-I",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_i,G2int_char_control_i);
    SET_SYMBOL_VALUE(Qg2int_char_control_i,CODE_CHAR(FIX((SI_Long)9L)));
    Qg2int_char_control_j = STATIC_SYMBOL("CHAR-CONTROL-J",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_j,G2int_char_control_j);
    SET_SYMBOL_VALUE(Qg2int_char_control_j,CODE_CHAR(FIX((SI_Long)10L)));
    Qg2int_char_control_k = STATIC_SYMBOL("CHAR-CONTROL-K",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_k,G2int_char_control_k);
    SET_SYMBOL_VALUE(Qg2int_char_control_k,CODE_CHAR(FIX((SI_Long)11L)));
    Qg2int_char_control_l = STATIC_SYMBOL("CHAR-CONTROL-L",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_l,G2int_char_control_l);
    SET_SYMBOL_VALUE(Qg2int_char_control_l,CODE_CHAR(FIX((SI_Long)12L)));
    Qg2int_char_control_m = STATIC_SYMBOL("CHAR-CONTROL-M",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_m,G2int_char_control_m);
    SET_SYMBOL_VALUE(Qg2int_char_control_m,CODE_CHAR(FIX((SI_Long)13L)));
    Qg2int_char_control_n = STATIC_SYMBOL("CHAR-CONTROL-N",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_n,G2int_char_control_n);
    SET_SYMBOL_VALUE(Qg2int_char_control_n,CODE_CHAR(FIX((SI_Long)14L)));
    Qg2int_char_control_o = STATIC_SYMBOL("CHAR-CONTROL-O",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_o,G2int_char_control_o);
    SET_SYMBOL_VALUE(Qg2int_char_control_o,CODE_CHAR(FIX((SI_Long)15L)));
    Qg2int_char_control_p = STATIC_SYMBOL("CHAR-CONTROL-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_p,G2int_char_control_p);
    SET_SYMBOL_VALUE(Qg2int_char_control_p,CODE_CHAR(FIX((SI_Long)16L)));
    Qg2int_char_control_q = STATIC_SYMBOL("CHAR-CONTROL-Q",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_q,G2int_char_control_q);
    SET_SYMBOL_VALUE(Qg2int_char_control_q,CODE_CHAR(FIX((SI_Long)17L)));
    Qg2int_char_control_r = STATIC_SYMBOL("CHAR-CONTROL-R",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_r,G2int_char_control_r);
    SET_SYMBOL_VALUE(Qg2int_char_control_r,CODE_CHAR(FIX((SI_Long)18L)));
    Qg2int_char_control_s = STATIC_SYMBOL("CHAR-CONTROL-S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_s,G2int_char_control_s);
    SET_SYMBOL_VALUE(Qg2int_char_control_s,CODE_CHAR(FIX((SI_Long)19L)));
    Qg2int_char_control_t = STATIC_SYMBOL("CHAR-CONTROL-T",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_t,G2int_char_control_t);
    SET_SYMBOL_VALUE(Qg2int_char_control_t,CODE_CHAR(FIX((SI_Long)20L)));
    Qg2int_char_control_u = STATIC_SYMBOL("CHAR-CONTROL-U",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_u,G2int_char_control_u);
    SET_SYMBOL_VALUE(Qg2int_char_control_u,CODE_CHAR(FIX((SI_Long)21L)));
    Qg2int_char_control_v = STATIC_SYMBOL("CHAR-CONTROL-V",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_v,G2int_char_control_v);
    SET_SYMBOL_VALUE(Qg2int_char_control_v,CODE_CHAR(FIX((SI_Long)22L)));
    Qg2int_char_control_w = STATIC_SYMBOL("CHAR-CONTROL-W",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_w,G2int_char_control_w);
    SET_SYMBOL_VALUE(Qg2int_char_control_w,CODE_CHAR(FIX((SI_Long)23L)));
    Qg2int_char_control_x = STATIC_SYMBOL("CHAR-CONTROL-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_x,G2int_char_control_x);
    SET_SYMBOL_VALUE(Qg2int_char_control_x,CODE_CHAR(FIX((SI_Long)24L)));
    Qg2int_char_control_y = STATIC_SYMBOL("CHAR-CONTROL-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_y,G2int_char_control_y);
    SET_SYMBOL_VALUE(Qg2int_char_control_y,CODE_CHAR(FIX((SI_Long)25L)));
    Qg2int_char_control_z = STATIC_SYMBOL("CHAR-CONTROL-Z",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_z,G2int_char_control_z);
    SET_SYMBOL_VALUE(Qg2int_char_control_z,CODE_CHAR(FIX((SI_Long)26L)));
    Qg2int_char_control_obt = STATIC_SYMBOL("CHAR-CONTROL-[",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_obt,G2int_char_control_obt);
    SET_SYMBOL_VALUE(Qg2int_char_control_obt,CODE_CHAR(FIX((SI_Long)27L)));
    Qg2int_char_control_backslash = STATIC_SYMBOL("CHAR-CONTROL-BACKSLASH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_backslash,
	    G2int_char_control_backslash);
    SET_SYMBOL_VALUE(Qg2int_char_control_backslash,
	    CODE_CHAR(FIX((SI_Long)28L)));
    Qg2int_char_control_cbt = STATIC_SYMBOL("CHAR-CONTROL-]",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_cbt,G2int_char_control_cbt);
    SET_SYMBOL_VALUE(Qg2int_char_control_cbt,CODE_CHAR(FIX((SI_Long)29L)));
    Qg2int_char_control_ct = STATIC_SYMBOL("CHAR-CONTROL-^",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control_ct,G2int_char_control_ct);
    SET_SYMBOL_VALUE(Qg2int_char_control_ct,CODE_CHAR(FIX((SI_Long)30L)));
    Qg2int_char_control__ = STATIC_SYMBOL("CHAR-CONTROL-_",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_control__,G2int_char_control__);
    SET_SYMBOL_VALUE(Qg2int_char_control__,CODE_CHAR(FIX((SI_Long)31L)));
    Qg2int_char_escape = STATIC_SYMBOL("CHAR-ESCAPE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_char_escape,G2int_char_escape);
    SET_SYMBOL_VALUE(Qg2int_char_escape,CODE_CHAR(FIX((SI_Long)27L)));
    list_constant_10 = STATIC_LIST((SI_Long)6L,CHR(' '),CHR('\n'),
	    CHR('\t'),CHR('\f'),CHR('\r'),CHR('\n'));
    if (G2int_whitespace_characters == UNBOUND)
	G2int_whitespace_characters = list_constant_10;
    list_constant_11 = STATIC_LIST((SI_Long)6L,FIX((SI_Long)32L),
	    FIX((SI_Long)10L),FIX((SI_Long)9L),FIX((SI_Long)12L),
	    FIX((SI_Long)13L),FIX((SI_Long)10L));
    if (G2int_whitespace_wide_characters == UNBOUND)
	G2int_whitespace_wide_characters = list_constant_11;
}
