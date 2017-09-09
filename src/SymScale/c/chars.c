/* chars.c
 * Input file:  characters.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "chars.h"


Object Maximum_suggested_length_for_simple_gensym_strings = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Roman_font_special_character_code_map, Qroman_font_special_character_code_map);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_latin1_special_character_code_map, Qiso_latin1_special_character_code_map);

DEFINE_VARIABLE_WITH_SYMBOL(Reverse_iso_latin1_special_character_code_map, Qreverse_iso_latin1_special_character_code_map);

Object Jis_last_contiguous_code = UNBOUND;

/* GENSYM-JIS-CODE-TO-CONTIGUOUS */
Object gensym_jis_code_to_contiguous(code)
    Object code;
{
    Object offset_qm;
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,0);
    high_byte = IFIX(code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(Jis_low_byte_offset);
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
Object legal_gensym_jis_character_code_p(gensym_jis_code)
    Object gensym_jis_code;
{
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,1);
    high_byte = IFIX(gensym_jis_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(gensym_jis_code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(Jis_low_byte_offset);
    low_byte = gensymed_symbol - gensymed_symbol_1;
    if (IFIX(Jis_high_byte_min) <= high_byte && high_byte <= 
	    IFIX(Jis_high_byte_max) && IFIX(Jis_low_byte_min) <= low_byte 
	    && low_byte <= IFIX(Jis_low_byte_max))
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
Object jis_to_shift_jis(code_init)
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

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_ksc_codes, Qnumber_of_ksc_codes);

/* KSC-TO-GENSYM-KSC */
Object ksc_to_gensym_ksc(ksc_code)
    Object ksc_code;
{
    SI_Long high_byte, gensymed_symbol, low_byte;

    x_note_fn_call(14,3);
    high_byte = IFIX(ksc_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(ksc_code) & (SI_Long)255L;
    low_byte = gensymed_symbol;
    return VALUES_1(FIX((high_byte << (SI_Long)8L) + 
	    (IFIX(Ksc_low_byte_offset) + low_byte)));
}

/* KS2-BYTES-TO-KSC5601 */
Object ks2_bytes_to_ksc5601(ks2_high_byte,ks2_low_byte)
    Object ks2_high_byte, ks2_low_byte;
{
    x_note_fn_call(14,4);
    return VALUES_1(FIX((IFIX(ks2_high_byte) + (SI_Long)-128L << 
	    (SI_Long)8L) + (IFIX(ks2_low_byte) + (SI_Long)-128L)));
}

/* CONVERT-2-BYTE-TO-GENSYM-KSC5601 */
Object convert_2_byte_to_gensym_ksc5601(ks2_high_byte_character,
	    ks2_low_byte_character)
    Object ks2_high_byte_character, ks2_low_byte_character;
{
    x_note_fn_call(14,5);
    return ksc_to_gensym_ksc(ks2_bytes_to_ksc5601(CHAR_CODE(ks2_high_byte_character),
	    CHAR_CODE(ks2_low_byte_character)));
}

/* GENSYM-KSC-TO-KSC */
Object gensym_ksc_to_ksc(gensym_ksc_code)
    Object gensym_ksc_code;
{
    SI_Long high_byte, gensymed_symbol, low_byte;

    x_note_fn_call(14,6);
    high_byte = IFIX(gensym_ksc_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(gensym_ksc_code) & (SI_Long)255L;
    low_byte = gensymed_symbol;
    return VALUES_1(FIX((high_byte << (SI_Long)8L) + (low_byte - 
	    IFIX(Ksc_low_byte_offset))));
}

Object Ksc_last_contiguous_code = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Ksc_contiguous_character_group_lengths, Qksc_contiguous_character_group_lengths);

/* GENSYM-KSC-CODE-TO-CONTIGUOUS */
Object gensym_ksc_code_to_contiguous(code)
    Object code;
{
    Object offset_qm;
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,7);
    high_byte = IFIX(code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(Ksc_low_byte_offset);
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
Object legal_gensym_ksc_character_code_p(gensym_ksc_code)
    Object gensym_ksc_code;
{
    SI_Long high_byte, gensymed_symbol, gensymed_symbol_1, low_byte;

    x_note_fn_call(14,8);
    high_byte = IFIX(gensym_ksc_code) >>  -  - (SI_Long)8L;
    gensymed_symbol = IFIX(gensym_ksc_code) & (SI_Long)255L;
    gensymed_symbol_1 = IFIX(Ksc_low_byte_offset);
    low_byte = gensymed_symbol - gensymed_symbol_1;
    if (IFIX(Ksc_high_byte_min) <= high_byte && high_byte <= 
	    IFIX(Ksc_high_byte_max) && IFIX(Ksc_low_byte_min) <= low_byte 
	    && low_byte <= IFIX(Ksc_low_byte_max))
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

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_offset_for_gensym_cyrillic, Qunicode_offset_for_gensym_cyrillic);

/* ISO-8859-5-TO-GENSYM-CYRILLIC */
Object iso_8859_5_to_gensym_cyrillic(iso_8859_5_character_code)
    Object iso_8859_5_character_code;
{
    Object temp;

    x_note_fn_call(14,9);
    temp = FIXNUM_ADD(FIXNUM_ADD(Gensym_cyrillic_character_block_start,
	    Iso_8859_5_offset_within_cyrillic_character_block),
	    iso_8859_5_character_code);
    return VALUES_1(temp);
}

Object Cyrillic_character_a_list = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Msw_cyrillic_code_map, Qmsw_cyrillic_code_map);

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_index_to_slavic_font_direct_index_map, Qunicode_index_to_slavic_font_direct_index_map);

Object Cyrillic_gensym_character_code_for_key_name_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Key_cap_to_gensym_cyrillic_character_code_map, Qkey_cap_to_gensym_cyrillic_character_code_map);

/* UTILIZE-CYRILLIC-CHARACTER-A-LIST */
Object utilize_cyrillic_character_a_list()
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
    ab_loop_list_ = Cyrillic_character_a_list;
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
	utilize_cyrillic_character_a_list_1(FIX(code_1),FIX(msw_code_qm_1),
		name_qm_1,FIX(direct_index_qm_1),key_name_qm_1,key_cap_qm_1);
	ab_loop_iter_flag_ = Nil;
	code_1 = code_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else
	utilize_cyrillic_character_a_list_1(code,msw_code_qm,name_qm,
		direct_index_qm,key_name_qm,key_cap_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qcyrillic_gensym_character_code_for_key_name;  /* cyrillic-gensym-character-code-for-key-name */

/* UTILIZE-CYRILLIC-CHARACTER-A-LIST-1 */
Object utilize_cyrillic_character_a_list_1(code,msw_code_qm,name_qm,
	    direct_index_qm,key_name_qm,key_cap_qm)
    Object code, msw_code_qm, name_qm, direct_index_qm, key_name_qm;
    Object key_cap_qm;
{
    Object svref_arg_1, svref_arg_2;

    x_note_fn_call(14,11);
    svref_arg_1 = Msw_cyrillic_code_map;
    svref_arg_2 = FIXNUM_MINUS(code,Unicode_cyrillic_character_block_start);
    SVREF(svref_arg_1,svref_arg_2) = msw_code_qm;
    svref_arg_1 = Unicode_index_to_slavic_font_direct_index_map;
    svref_arg_2 = FIXNUM_MINUS(code,Unicode_cyrillic_character_block_start);
    SVREF(svref_arg_1,svref_arg_2) = direct_index_qm;
    if (key_name_qm)
	mutate_global_property(key_name_qm,FIXNUM_ADD(FIXNUM_MINUS(code,
		Unicode_cyrillic_character_block_start),
		Gensym_cyrillic_character_block_start),
		Qcyrillic_gensym_character_code_for_key_name);
    if (key_cap_qm) {
	svref_arg_1 = Key_cap_to_gensym_cyrillic_character_code_map;
	svref_arg_2 = CHAR_CODE(key_cap_qm);
	SVREF(svref_arg_1,svref_arg_2) = code;
    }
    return VALUES_1(Nil);
}

Object Gensym_unicode_row_correspondences = UNBOUND;

Object Gensym_to_unicode_full_row_map = UNBOUND;

Object Unicode_to_gensym_full_row_map = UNBOUND;

/* MAP-UNICODE-TO-EXTENDED-UTF-G-CHARACTERS */
Object map_unicode_to_extended_utf_g_characters(unicode)
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
Object map_extended_utf_g_characters_to_unicode(high_half,low_half)
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

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_offset_for_gensym_letterlike_symbol, Qunicode_offset_for_gensym_letterlike_symbol);

/* UNICODE-LETTERLIKE-SYMBOL-P */
Object unicode_letterlike_symbol_p(unicode)
    Object unicode;
{
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(14,14);
    arg = (SI_Long)4352L;
    arg_1 = IFIX(FIXNUM_ADD(unicode,
	    Unicode_offset_for_gensym_letterlike_symbol));
    arg_2 = (SI_Long)4607L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_offset_for_gensym_general_punctuation, Qunicode_offset_for_gensym_general_punctuation);

/* UNICODE-GENERAL-PUNCTUATION-CHARACTER-P */
Object unicode_general_punctuation_character_p(unicode)
    Object unicode;
{
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(14,15);
    arg = (SI_Long)4096L;
    arg_1 = IFIX(FIXNUM_ADD(unicode,
	    Unicode_offset_for_gensym_general_punctuation));
    arg_2 = (SI_Long)4351L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* ALPHABETIC-GENSYM-CHARACTER-P */
Object alphabetic_gensym_character_p(character_or_character_code,
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
		    arg = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9057L)));
		    arg_1 = IFIX(character_or_character_code);
		    arg_2 = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9082L)));
		    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		}
		if (temp);
		else {
		    arg = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9569L)));
		    arg_1 = IFIX(character_or_character_code);
		    arg_2 = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9592L)));
		    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		}
		if (temp);
		else {
		    arg = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)11345L)));
		    arg_1 = IFIX(character_or_character_code);
		    arg_2 = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)11377L)));
		    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		}
		if (temp);
		else {
		    unicode_index = 
			    FIXNUM_MINUS(character_or_character_code,
			    Gensym_cyrillic_character_block_start);
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
			arg = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9025L)));
			arg_1 = IFIX(character_or_character_code);
			arg_2 = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9050L)));
			temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : 
				Qnil;
		    }
		    if (temp);
		    else {
			arg = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9537L)));
			arg_1 = IFIX(character_or_character_code);
			arg_2 = IFIX(ksc_to_gensym_ksc(FIX((SI_Long)9560L)));
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
				Gensym_cyrillic_character_block_start);
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
Object numeric_gensym_character_p(character_or_character_code,
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
		    start = ksc_to_gensym_ksc(FIX((SI_Long)9008L));
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
Object alphanumeric_gensym_character_p(character_or_character_code,
	    escape_character_qm)
    Object character_or_character_code, escape_character_qm;
{
    Object temp;

    x_note_fn_call(14,18);
    temp = alphabetic_gensym_character_p(character_or_character_code,
	    escape_character_qm);
    if (temp);
    else
	temp = numeric_gensym_character_p(character_or_character_code,
		escape_character_qm);
    return VALUES_1(temp);
}

/* MAKE-GENSYM-CHARACTER-STRING */
Object make_gensym_character_string(character_or_character_code,
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
	gensym_string = obtain_simple_gensym_string(FIX((SI_Long)1L));
	SET_SCHAR(gensym_string,FIX((SI_Long)0L),character_or_character_code);
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	gensym_string = 
		obtain_simple_gensym_string(IFIX(character_or_character_code) 
		>>  -  - (SI_Long)13L == (SI_Long)1L ? FIX((SI_Long)3L) : 
		FIX((SI_Long)4L));
	index_1 = (SI_Long)0L;
	gensymed_symbol = character_or_character_code;
	gensymed_symbol_1 = gensym_string;
	gensymed_symbol_2 = T;
	result = chestnut_floorf_function(FIX(IFIX(gensymed_symbol) & 
		(SI_Long)8191L),FIX((SI_Long)95L));
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
	gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2L));
	SET_SCHAR(gensym_string,FIX((SI_Long)0L),escape_character_qm);
	SET_SCHAR(gensym_string,FIX((SI_Long)1L),character_or_character_code);
    }
    return VALUES_1(gensym_string);
}

/* UNICODE-LINE-SEPARATOR-FUNCTION */
Object unicode_line_separator_function()
{
    x_note_fn_call(14,20);
    return VALUES_1(FIX((SI_Long)8232L));
}

/* UNICODE-TAB-FUNCTION */
Object unicode_tab_function()
{
    x_note_fn_call(14,21);
    return VALUES_1(FIX((SI_Long)9L));
}

/* MAKE-CJK-CODE-MAPPING-VECTOR */
Object make_cjk_code_mapping_vector()
{
    x_note_fn_call(14,22);
    return make_array(5,FIX((SI_Long)307L),Kelement_type,T,
	    Kinitial_element,Nil);
}

/* SET-CJK-CODE-MAPPING */
Object set_cjk_code_mapping(cjk_code,cjk_code_mapping_vector,
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

Object Unicode_jis_x_0208_mapping_hand_edits = UNBOUND;

/* LEGAL-GENSYM-STRING-P */
Object legal_gensym_string_p varargs_1(int, n)
{
    Object string_1;
    Object start, end_qm, temp, character_1, gensymed_symbol;
    SI_Long end_1, i, j, character_index, arg, arg_1, arg_2, ascii_code;
    SI_Long temp_3;
    char string_is_simple_qm;
    char temp_1;
    char temp_2, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(14,24);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    start = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     FIX((SI_Long)0L);
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    temp = end_qm;
    if (temp);
    else
	temp = string_is_simple_qm ? SIMPLE_ARRAY_ANY_1_LENGTH(string_1) : 
		length(string_1);
    end_1 = IFIX(temp);
    i = IFIX(start);
    j = (SI_Long)0L;
    character_1 = Nil;
    character_index = (SI_Long)0L;
  next_loop:
    character_index = i;
    if (i >= end_1)
	return VALUES_1(T);
    temp = string_is_simple_qm ? CHR(ISCHAR(string_1,i)) : 
	    CHR(ICHAR(string_1,i));
    i = i + (SI_Long)1L;
    character_1 = temp;
    switch (ICHAR_CODE(character_1)) {
      case '@':
	if (i < end_1) {
	    temp_1 = string_is_simple_qm ? ISCHAR(string_1,i) : 
		    ICHAR(string_1,i);
	    i = i + (SI_Long)1L;
	    switch (temp_1) {
	      case 'P':
	      case 'L':
		temp = T;
		break;
	      default:
		temp = Nil;
		break;
	    }
	}
	else
	    temp = Nil;
	break;
      case '~':
	if (i < end_1) {
	    arg = (SI_Long)32L;
	    temp_1 = string_is_simple_qm ? ISCHAR(string_1,i) : 
		    ICHAR(string_1,i);
	    i = i + (SI_Long)1L;
	    character_1 = CHAR_TO_CHARACTER(temp_1);
	    arg_1 = IFIX(CHAR_INT(character_1));
	    arg_2 = (SI_Long)126L;
	    temp_2 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp = temp_2 ? ISVREF(Roman_font_special_character_code_map,
		IFIX(CHAR_INT(character_1)) - (SI_Long)32L) : Nil;
	break;
      case '\\':
	j = i;
	if (i < end_1) {
	    arg = (SI_Long)32L;
	    temp_1 = string_is_simple_qm ? ISCHAR(string_1,i) : 
		    ICHAR(string_1,i);
	    i = i + (SI_Long)1L;
	    character_1 = CHAR_TO_CHARACTER(temp_1);
	    arg_1 = IFIX(CHAR_INT(character_1));
	    arg_2 = (SI_Long)126L;
	    temp_2 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? i < end_1 : TRUEP(Nil)) {
	    arg = (SI_Long)32L;
	    temp_1 = string_is_simple_qm ? ISCHAR(string_1,i) : 
		    ICHAR(string_1,i);
	    i = i + (SI_Long)1L;
	    arg_1 = IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
	    arg_2 = (SI_Long)126L;
	    temp_2 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_2 =  !(IFIX(CHAR_INT(character_1)) < (SI_Long)40L);
	    if (temp_2);
	    else if (i < end_1) {
		arg = (SI_Long)32L;
		temp_1 = string_is_simple_qm ? ISCHAR(string_1,i) : 
			ICHAR(string_1,i);
		i = i + (SI_Long)1L;
		arg_1 = IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
		arg_2 = (SI_Long)126L;
		temp_2 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    gensymed_symbol = string_1;
	    gensymed_symbol_1 = string_is_simple_qm;
	    temp_1 = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,j) : 
		    ICHAR(gensymed_symbol,j);
	    j = j + (SI_Long)1L;
	    ascii_code = IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
	    if (ascii_code < (SI_Long)40L) {
		temp_3 = ascii_code << (SI_Long)13L;
		temp_1 = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,j) : 
			ICHAR(gensymed_symbol,j);
		j = j + (SI_Long)1L;
		temp_3 = temp_3 + (SI_Long)95L * 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
		temp_1 = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,j) : 
			ICHAR(gensymed_symbol,j);
		j = j + (SI_Long)1L;
		temp_3 = temp_3 + 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1))) + 
			(SI_Long)-265976L;
	    }
	    else {
		temp_3 = (SI_Long)95L * ascii_code;
		temp_1 = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,j) : 
			ICHAR(gensymed_symbol,j);
		j = j + (SI_Long)1L;
		temp_3 = temp_3 + 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1))) + 
			(SI_Long)4360L;
	    }
	    temp = temp_3 < (SI_Long)65536L ? T : Nil;
	}
	else
	    temp = Nil;
	break;
      default:
	arg = (SI_Long)32L;
	arg_1 = IFIX(CHAR_INT(character_1));
	arg_2 = (SI_Long)126L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
	break;
    }
    if ( !TRUEP(temp))
	return VALUES_2(Nil,FIX(character_index));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Char_backspace = UNBOUND;

Object Char_tab = UNBOUND;

Object Char_linefeed = UNBOUND;

Object Char_page = UNBOUND;

Object Char_return = UNBOUND;

Object Char_rubout = UNBOUND;

Object Char_control_at = UNBOUND;

Object Char_control_a = UNBOUND;

Object Char_control_b = UNBOUND;

Object Char_control_c = UNBOUND;

Object Char_control_d = UNBOUND;

Object Char_control_e = UNBOUND;

Object Char_control_f = UNBOUND;

Object Char_control_g = UNBOUND;

Object Char_control_h = UNBOUND;

Object Char_control_i = UNBOUND;

Object Char_control_j = UNBOUND;

Object Char_control_k = UNBOUND;

Object Char_control_l = UNBOUND;

Object Char_control_m = UNBOUND;

Object Char_control_n = UNBOUND;

Object Char_control_o = UNBOUND;

Object Char_control_p = UNBOUND;

Object Char_control_q = UNBOUND;

Object Char_control_r = UNBOUND;

Object Char_control_s = UNBOUND;

Object Char_control_t = UNBOUND;

Object Char_control_u = UNBOUND;

Object Char_control_v = UNBOUND;

Object Char_control_w = UNBOUND;

Object Char_control_x = UNBOUND;

Object Char_control_y = UNBOUND;

Object Char_control_z = UNBOUND;

Object Char_control_obt = UNBOUND;

Object Char_control_backslash = UNBOUND;

Object Char_control_cbt = UNBOUND;

Object Char_control_ct = UNBOUND;

Object Char_control__ = UNBOUND;

Object Char_escape = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Whitespace_characters, Qwhitespace_characters);

DEFINE_VARIABLE_WITH_SYMBOL(Whitespace_wide_characters, Qwhitespace_wide_characters);

void characters_INIT()
{
    Object temp, the_array, char_qm, code_qm, vector_1, x, ab_loop_list_, g;
    Object u_1, ab_loop_iter_flag_;
    SI_Long gensymed_symbol, i, ab_loop_bind_, g_row, u_row;
    Object list_constant_11, list_constant_10, Qchar_escape, AB_package;
    Object Qchar_control__, Qchar_control_ct, Qchar_control_cbt;
    Object Qchar_control_backslash, Qchar_control_obt, Qchar_control_z;
    Object Qchar_control_y, Qchar_control_x, Qchar_control_w, Qchar_control_v;
    Object Qchar_control_u, Qchar_control_t, Qchar_control_s, Qchar_control_r;
    Object Qchar_control_q, Qchar_control_p, Qchar_control_o, Qchar_control_n;
    Object Qchar_control_m, Qchar_control_l, Qchar_control_k, Qchar_control_j;
    Object Qchar_control_i, Qchar_control_h, Qchar_control_g, Qchar_control_f;
    Object Qchar_control_e, Qchar_control_d, Qchar_control_c, Qchar_control_b;
    Object Qchar_control_a, Qchar_control_at, Qchar_rubout, Qchar_return;
    Object Qchar_page, Qchar_linefeed, Qchar_tab, Qchar_backspace;
    Object Qunicode_thai_glyph_variants_end;
    Object Qunicode_thai_glyph_variants_start;
    Object Qunicode_thai_character_block_end;
    Object Qunicode_thai_character_block_start;
    Object Qunicode_hebrew_precomposed_character_block_end;
    Object Qunicode_hebrew_precomposed_character_block_start;
    Object Qunicode_hebrew_character_block_end;
    Object Qunicode_hebrew_character_block_start, list_constant_9;
    Object list_constant_8, list_constant_7, list_constant_6, list_constant_5;
    Object list_constant_4, list_constant_3, list_constant_2;
    Object Qunicode_general_punctuation_character_block_start;
    Object Qgensym_general_punctuation_character_block_start;
    Object Qunicode_letterlike_symbol_block_start;
    Object Qgensym_letterlike_symbol_block_start, list_constant_1;
    Object Qinvalid_gensym_full_row, Qinvalid_unicode_full_row;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5;
    Object Qiso_8859_5_offset_within_cyrillic_character_block;
    Object Qunicode_cyrillic_character_block_start;
    Object Qnumber_of_contiguous_gb2312_codes, Qgb_low_byte_max;
    Object Qgb_low_byte_min, Qgb_high_byte_max, Qgb_high_byte_min;
    Object list_constant, Qksc_last_contiguous_code, Qksc_undefined_start;
    Object Qksc_hanja_start, Qksc_hangul_start, Qksc_symbols_1_start;
    Object Qksc_low_byte_max, Qksc_low_byte_min, Qksc_high_byte_max;
    Object Qksc_high_byte_min, Qksc_low_byte_offset, Qjis_low_byte_offset;
    Object Qjis_low_byte_max, Qjis_low_byte_min, Qjis_high_byte_max;
    Object Qjis_high_byte_min, Qjis_last_contiguous_code, Qjis_undefined_start;
    Object Qjis_level_2_kanji_start, Qjis_level_1_kanji_start;
    Object Qjis_ruled_line_elements_start, Qjis_lower_case_cyrillic_start;
    Object Qjis_upper_case_cyrillic_start, Qjis_lower_case_greek_start;
    Object Qjis_upper_case_greek_start, Qjis_katakana_start;
    Object Qjis_hiragana_start, Qjis_lower_case_roman_start;
    Object Qjis_upper_case_roman_start, Qjis_numbers_start;
    Object Qjis_symbols_90_5_start, Qjis_symbols_90_4_start;
    Object Qjis_symbols_90_3_start, Qjis_symbols_90_2_start;
    Object Qjis_symbols_90_1_start, Qjis_symbols_2_start, Qjis_symbols_1_start;
    Object Qjis_lower_case_cyrillic_offset, Qjis_lower_case_greek_offset;
    Object Qjis_lower_case_roman_offset, Qjis_upper_case_roman_offset;
    Object Qjis_numbers_offset, Qjis_symbols_90_5_offset;
    Object Qjis_symbols_90_4_offset, Qjis_symbols_90_3_offset;
    Object Qjis_symbols_90_2_offset, Qjis_symbols_90_1_offset;
    Object Qjis_undefined_byte, Qjis_level_2_kanji_high_byte;
    Object Qjis_level_1_kanji_high_byte, Qjis_ruled_line_elements_high_byte;
    Object Qjis_cyrillic_high_byte, Qjis_greek_high_byte;
    Object Qjis_katakana_high_byte, Qjis_hiragana_high_byte;
    Object Qjis_roman_high_byte, Qjis_symbols_2_high_byte;
    Object Qjis_symbols_1_high_byte, Qgensym_cyrillic_character_block_start;
    Object string_constant_4, string_constant_3, string_constant_2;
    Object string_constant_1, string_constant, Kascii;

    x_note_fn_call(14,25);
    SET_PACKAGE("AB");
    Kascii = STATIC_SYMBOL("ASCII",Pkeyword);
    temp = adjoin(2,Kascii,Features);
    Features = temp;
    Maximum_suggested_length_for_simple_gensym_strings = FIX((SI_Long)64L);
    string_constant = 
	    STATIC_STRING("13-Sy03*Uy03*ay3*by3*Qy3*cy0003*dy000003*Fy3*Gy3*Hy3*Iy3*Jy3*Ky3*Ly3*My3*1y3*2y3*Ry3*Sy3*Xy03*Yy3*Ty3-+ylmnop3*0yq3*6yrs003*4ytu");
    string_constant_1 = 
	    STATIC_STRING("vwx03**yyz3*-y3*Ay3*Cy3*Ey03-Oy00003Cy3Dy3Ey3Fy3Gy3*=y3Hy3*5y3Iy3Jy003*3y3Ky3Ly3My3Ny3Oy3Ry3*8y3Py3Qy3*+y3*By3*7y3*Dy03*9y03-wy0");
    if (Roman_font_special_character_code_map == UNBOUND)
	Roman_font_special_character_code_map = make_array(3,
		FIX((SI_Long)96L),Kinitial_contents,
		regenerate_optimized_constant(LIST_2(string_constant,
		string_constant_1)));
    string_constant_2 = 
	    STATIC_STRING("130+y00000000000000000000000000000000000000000000000000000000000000006@0000000000000000000000000006\\0000000000000000000000000000");
    string_constant_3 = 
	    STATIC_STRING("000006~00000000000000000000000000000000006!6%6#06$0006|06<006;0000000000006>0006\?6M6B6D656A6R6X6C6G6E6F616H6I6J6306N6Y6P6Q676O06");
    string_constant_4 = 
	    STATIC_STRING("T6Z6V696U006s6m6b6d646a6r6x6c6g6e6f606h6i6j6206n6y6p6q666o06t6z6v686u000");
    if (Iso_latin1_special_character_code_map == UNBOUND)
	Iso_latin1_special_character_code_map = make_array(3,
		FIX((SI_Long)256L),Kinitial_contents,
		regenerate_optimized_constant(LIST_3(string_constant_2,
		string_constant_3,string_constant_4)));
    if (Reverse_iso_latin1_special_character_code_map == UNBOUND) {
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
	Reverse_iso_latin1_special_character_code_map = the_array;
    }
    i = (SI_Long)0L;
    char_qm = Nil;
    code_qm = Nil;
  next_loop_1:
    if (i >= (SI_Long)256L)
	goto end_loop_1;
    char_qm = ISVREF(Iso_latin1_special_character_code_map,i);
    code_qm = char_qm ? CHAR_CODE(char_qm) : Nil;
    if (code_qm) {
	temp = Reverse_iso_latin1_special_character_code_map;
	SVREF(temp,code_qm) = FIX(i);
    }
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    AB_package = STATIC_PACKAGE("AB");
    Qgensym_cyrillic_character_block_start = 
	    STATIC_SYMBOL("GENSYM-CYRILLIC-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qgensym_cyrillic_character_block_start,
	    FIX((SI_Long)8192L));
    Qjis_symbols_1_high_byte = STATIC_SYMBOL("JIS-SYMBOLS-1-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_1_high_byte,FIX((SI_Long)33L));
    Qjis_symbols_2_high_byte = STATIC_SYMBOL("JIS-SYMBOLS-2-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_2_high_byte,FIX((SI_Long)34L));
    Qjis_roman_high_byte = STATIC_SYMBOL("JIS-ROMAN-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qjis_roman_high_byte,FIX((SI_Long)35L));
    Qjis_hiragana_high_byte = STATIC_SYMBOL("JIS-HIRAGANA-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_hiragana_high_byte,FIX((SI_Long)36L));
    Qjis_katakana_high_byte = STATIC_SYMBOL("JIS-KATAKANA-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_katakana_high_byte,FIX((SI_Long)37L));
    Qjis_greek_high_byte = STATIC_SYMBOL("JIS-GREEK-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qjis_greek_high_byte,FIX((SI_Long)38L));
    Qjis_cyrillic_high_byte = STATIC_SYMBOL("JIS-CYRILLIC-HIGH-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_cyrillic_high_byte,FIX((SI_Long)39L));
    Qjis_ruled_line_elements_high_byte = 
	    STATIC_SYMBOL("JIS-RULED-LINE-ELEMENTS-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qjis_ruled_line_elements_high_byte,FIX((SI_Long)40L));
    Qjis_level_1_kanji_high_byte = 
	    STATIC_SYMBOL("JIS-LEVEL-1-KANJI-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qjis_level_1_kanji_high_byte,FIX((SI_Long)48L));
    Qjis_level_2_kanji_high_byte = 
	    STATIC_SYMBOL("JIS-LEVEL-2-KANJI-HIGH-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qjis_level_2_kanji_high_byte,FIX((SI_Long)80L));
    Qjis_undefined_byte = STATIC_SYMBOL("JIS-UNDEFINED-BYTE",AB_package);
    SET_SYMBOL_VALUE(Qjis_undefined_byte,FIX((SI_Long)117L));
    Qjis_symbols_90_1_offset = STATIC_SYMBOL("JIS-SYMBOLS-90-1-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_1_offset,FIX((SI_Long)25L));
    Qjis_symbols_90_2_offset = STATIC_SYMBOL("JIS-SYMBOLS-90-2-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_2_offset,FIX((SI_Long)41L));
    Qjis_symbols_90_3_offset = STATIC_SYMBOL("JIS-SYMBOLS-90-3-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_3_offset,FIX((SI_Long)59L));
    Qjis_symbols_90_4_offset = STATIC_SYMBOL("JIS-SYMBOLS-90-4-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_4_offset,FIX((SI_Long)81L));
    Qjis_symbols_90_5_offset = STATIC_SYMBOL("JIS-SYMBOLS-90-5-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_5_offset,FIX((SI_Long)93L));
    Qjis_numbers_offset = STATIC_SYMBOL("JIS-NUMBERS-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qjis_numbers_offset,FIX((SI_Long)15L));
    Qjis_upper_case_roman_offset = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-ROMAN-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qjis_upper_case_roman_offset,FIX((SI_Long)32L));
    Qjis_lower_case_roman_offset = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-ROMAN-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qjis_lower_case_roman_offset,FIX((SI_Long)64L));
    Qjis_lower_case_greek_offset = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-GREEK-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qjis_lower_case_greek_offset,FIX((SI_Long)32L));
    Qjis_lower_case_cyrillic_offset = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-CYRILLIC-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qjis_lower_case_cyrillic_offset,FIX((SI_Long)48L));
    Qjis_symbols_1_start = STATIC_SYMBOL("JIS-SYMBOLS-1-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_1_start,FIX((SI_Long)0L));
    Qjis_symbols_2_start = STATIC_SYMBOL("JIS-SYMBOLS-2-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_2_start,FIX((SI_Long)94L));
    Qjis_symbols_90_1_start = STATIC_SYMBOL("JIS-SYMBOLS-90-1-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_1_start,FIX((SI_Long)108L));
    Qjis_symbols_90_2_start = STATIC_SYMBOL("JIS-SYMBOLS-90-2-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_2_start,FIX((SI_Long)116L));
    Qjis_symbols_90_3_start = STATIC_SYMBOL("JIS-SYMBOLS-90-3-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_3_start,FIX((SI_Long)123L));
    Qjis_symbols_90_4_start = STATIC_SYMBOL("JIS-SYMBOLS-90-4-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_4_start,FIX((SI_Long)138L));
    Qjis_symbols_90_5_start = STATIC_SYMBOL("JIS-SYMBOLS-90-5-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_symbols_90_5_start,FIX((SI_Long)146L));
    Qjis_numbers_start = STATIC_SYMBOL("JIS-NUMBERS-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_numbers_start,FIX((SI_Long)147L));
    Qjis_upper_case_roman_start = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-ROMAN-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_upper_case_roman_start,FIX((SI_Long)157L));
    Qjis_lower_case_roman_start = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-ROMAN-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_lower_case_roman_start,FIX((SI_Long)183L));
    Qjis_hiragana_start = STATIC_SYMBOL("JIS-HIRAGANA-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_hiragana_start,FIX((SI_Long)209L));
    Qjis_katakana_start = STATIC_SYMBOL("JIS-KATAKANA-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_katakana_start,FIX((SI_Long)292L));
    Qjis_upper_case_greek_start = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-GREEK-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_upper_case_greek_start,FIX((SI_Long)378L));
    Qjis_lower_case_greek_start = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-GREEK-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_lower_case_greek_start,FIX((SI_Long)402L));
    Qjis_upper_case_cyrillic_start = 
	    STATIC_SYMBOL("JIS-UPPER-CASE-CYRILLIC-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_upper_case_cyrillic_start,FIX((SI_Long)426L));
    Qjis_lower_case_cyrillic_start = 
	    STATIC_SYMBOL("JIS-LOWER-CASE-CYRILLIC-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_lower_case_cyrillic_start,FIX((SI_Long)459L));
    Qjis_ruled_line_elements_start = 
	    STATIC_SYMBOL("JIS-RULED-LINE-ELEMENTS-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_ruled_line_elements_start,FIX((SI_Long)492L));
    Qjis_level_1_kanji_start = STATIC_SYMBOL("JIS-LEVEL-1-KANJI-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_level_1_kanji_start,FIX((SI_Long)524L));
    Qjis_level_2_kanji_start = STATIC_SYMBOL("JIS-LEVEL-2-KANJI-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_level_2_kanji_start,FIX((SI_Long)3489L));
    Qjis_undefined_start = STATIC_SYMBOL("JIS-UNDEFINED-START",AB_package);
    SET_SYMBOL_VALUE(Qjis_undefined_start,FIX((SI_Long)6879L));
    Qjis_last_contiguous_code = STATIC_SYMBOL("JIS-LAST-CONTIGUOUS-CODE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjis_last_contiguous_code,
	    Jis_last_contiguous_code);
    SET_SYMBOL_VALUE(Qjis_last_contiguous_code,
	    FIXNUM_SUB1(Jis_undefined_start));
    Qjis_high_byte_min = STATIC_SYMBOL("JIS-HIGH-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qjis_high_byte_min,FIX((SI_Long)33L));
    Qjis_high_byte_max = STATIC_SYMBOL("JIS-HIGH-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qjis_high_byte_max,FIX((SI_Long)116L));
    Qjis_low_byte_min = STATIC_SYMBOL("JIS-LOW-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qjis_low_byte_min,FIX((SI_Long)33L));
    Qjis_low_byte_max = STATIC_SYMBOL("JIS-LOW-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qjis_low_byte_max,FIX((SI_Long)126L));
    Qjis_low_byte_offset = STATIC_SYMBOL("JIS-LOW-BYTE-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qjis_low_byte_offset,FIX((SI_Long)0L));
    if (Number_of_ksc_codes == UNBOUND)
	Number_of_ksc_codes = FIX((SI_Long)8224L);
    Qksc_low_byte_offset = STATIC_SYMBOL("KSC-LOW-BYTE-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qksc_low_byte_offset,FIX((SI_Long)94L));
    Qksc_high_byte_min = STATIC_SYMBOL("KSC-HIGH-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qksc_high_byte_min,FIX((SI_Long)33L));
    Qksc_high_byte_max = STATIC_SYMBOL("KSC-HIGH-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qksc_high_byte_max,FIX((SI_Long)125L));
    Qksc_low_byte_min = STATIC_SYMBOL("KSC-LOW-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qksc_low_byte_min,FIX((SI_Long)33L));
    Qksc_low_byte_max = STATIC_SYMBOL("KSC-LOW-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qksc_low_byte_max,FIX((SI_Long)126L));
    Qksc_symbols_1_start = STATIC_SYMBOL("KSC-SYMBOLS-1-START",AB_package);
    SET_SYMBOL_VALUE(Qksc_symbols_1_start,FIX((SI_Long)0L));
    Qksc_hangul_start = STATIC_SYMBOL("KSC-HANGUL-START",AB_package);
    SET_SYMBOL_VALUE(Qksc_hangul_start,FIX((SI_Long)986L));
    Qksc_hanja_start = STATIC_SYMBOL("KSC-HANJA-START",AB_package);
    SET_SYMBOL_VALUE(Qksc_hanja_start,FIX((SI_Long)3336L));
    Qksc_undefined_start = STATIC_SYMBOL("KSC-UNDEFINED-START",AB_package);
    SET_SYMBOL_VALUE(Qksc_undefined_start,FIX((SI_Long)8224L));
    Qksc_last_contiguous_code = STATIC_SYMBOL("KSC-LAST-CONTIGUOUS-CODE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qksc_last_contiguous_code,
	    Ksc_last_contiguous_code);
    SET_SYMBOL_VALUE(Qksc_last_contiguous_code,
	    FIXNUM_SUB1(Ksc_undefined_start));
    list_constant = STATIC_LIST((SI_Long)21L,FIX((SI_Long)94L),
	    FIX((SI_Long)69L),FIX((SI_Long)94L),FIX((SI_Long)94L),
	    FIX((SI_Long)10L),FIX((SI_Long)10L),FIX((SI_Long)24L),
	    FIX((SI_Long)24L),FIX((SI_Long)68L),FIX((SI_Long)79L),
	    FIX((SI_Long)4L),FIX((SI_Long)1L),FIX((SI_Long)8L),
	    FIX((SI_Long)78L),FIX((SI_Long)94L),FIX((SI_Long)83L),
	    FIX((SI_Long)86L),FIX((SI_Long)33L),FIX((SI_Long)33L),
	    FIX((SI_Long)2350L),FIX((SI_Long)4888L));
    if (Ksc_contiguous_character_group_lengths == UNBOUND)
	Ksc_contiguous_character_group_lengths = list_constant;
    Qgb_high_byte_min = STATIC_SYMBOL("GB-HIGH-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qgb_high_byte_min,FIX((SI_Long)33L));
    Qgb_high_byte_max = STATIC_SYMBOL("GB-HIGH-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qgb_high_byte_max,FIX((SI_Long)119L));
    Qgb_low_byte_min = STATIC_SYMBOL("GB-LOW-BYTE-MIN",AB_package);
    SET_SYMBOL_VALUE(Qgb_low_byte_min,FIX((SI_Long)33L));
    Qgb_low_byte_max = STATIC_SYMBOL("GB-LOW-BYTE-MAX",AB_package);
    SET_SYMBOL_VALUE(Qgb_low_byte_max,FIX((SI_Long)126L));
    Qnumber_of_contiguous_gb2312_codes = 
	    STATIC_SYMBOL("NUMBER-OF-CONTIGUOUS-GB2312-CODES",AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_contiguous_gb2312_codes,FIX((SI_Long)8178L));
    Qunicode_cyrillic_character_block_start = 
	    STATIC_SYMBOL("UNICODE-CYRILLIC-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qunicode_cyrillic_character_block_start,
	    FIX((SI_Long)1024L));
    Qiso_8859_5_offset_within_cyrillic_character_block = 
	    STATIC_SYMBOL("ISO-8859-5-OFFSET-WITHIN-CYRILLIC-CHARACTER-BLOCK",
	    AB_package);
    SET_SYMBOL_VALUE(Qiso_8859_5_offset_within_cyrillic_character_block,
	    FIX((SI_Long)0L));
    if (Unicode_offset_for_gensym_cyrillic == UNBOUND)
	Unicode_offset_for_gensym_cyrillic = 
		FIXNUM_MINUS(Gensym_cyrillic_character_block_start,
		Unicode_cyrillic_character_block_start);
    string_constant_5 = 
	    STATIC_STRING("13Ty1m3C+y01q3C-y3*ay5mIO3*3y83tcy6~1p3C*y3*+y5nDJE3-Uy83-EGy1p3C=y3*-y5nGJE3-Vy83-75y1p3C0y3*cy5lE3*5y83-GEy1p3C1y3*vy5nDZE3*Oy");
    string_constant_6 = 
	    STATIC_STRING("83-74y1p3C2y3*ky5lI3*Dy83-GDy1p3C3y3*hy5mYI3*Ay83-GFy1p3C4y3*Vy5mJE3**y83tdy1p3C5y3*6y5nLJE3-dy83tfy1p3C6y3*8y5nNJE3-fy83tgy1p3C");
    string_constant_7 = 
	    STATIC_STRING("7y3*Ay5oTSHE3-hy83-EHy1p3C8y3*9y5nKJE3-gy83-76y1m3C9y01p3CAy3*Ty5rSHORT U3*+y83rCy1p3CBy3*By5oDZHE3-iy83tPy1q1m3CCy3DBy1m3=+y3=x");
    string_constant_8 = 
	    STATIC_STRING("y13--y5lA5mBE5mVE5mGE5mDE5mIE5nZHE5mZE5mII5sSHORT II5mKA5mEL5mEM5mEN5lO5mPE5mER5mES5mTE5lU5mEF5nKHA5nTSE5nCHE5nSHA5pSHCHA5tHARD ");
    string_constant_9 = 
	    STATIC_STRING("SIGN5oYERI5tSOFT SIGN5uREVERSED E5mIU5mIA5la5mbe5mve5mge5mde5mie5nzhe5mze5mii5sshort ii5mka5mel5mem5men5lo5mpe5mer5mes5mte5lu5me");
    string_constant_10 = 
	    STATIC_STRING("f5nkha5ntse5nche5nsha5pshcha5thard sign5oyeri5tsoft sign5xreversed sign5ureversed e5miu5mia1m3*Ry3=Qy13-+y83tLy83tMy83tqy83tXy83");
    string_constant_11 = 
	    STATIC_STRING("tOy83tby83tvy83tuy83tay83tly83tey83tSy83tTy83tUy83thy83tiy83tVy83tWy83tny83tpy83tRy83tYy83toy83tNy83tjy83tky83tZy83tsy83tmy83tQy");
    string_constant_12 = 
	    STATIC_STRING("83tty83try83twy83txy83uPy83u6y83u-y83uAy83uUy83uTy83u9y83uKy83uDy83u1y83u2y83u3y83uGy83uHy83u4y83u5y83uMy83uOy83u0y83u7y83uNy83u");
    string_constant_13 = 
	    STATIC_STRING("+y83uIy83uJy83u8y83uRy83uLy83u=y83uSy83uQy13-+y6F6<6D6U6L6T6:6P6B6Q6R6K6V6Y6J6G6H6C6N6E6A6{6W6X6I6O6}6S6M6\"6>6Z6f6,6d6u6l6t6;6p6");
    string_constant_14 = 
	    STATIC_STRING("b6q6r6k6v6y6j6g6h6c6n6e6a6[6w6x6i6o6]6s6m6\'6.6z1m3DCy01q3DDy3*qy5mio3*Jy83uBy6`1p3DEy3*Cy5ndje3-jy83-EIy1p3DFy3*=y5ngje3-Xy83-78");
    string_constant_15 = 
	    STATIC_STRING("y1p3DGy3*sy5le3*Ly83-GHy1p3DHy3*wy5ndze3*Py83-77y1p3DIy3*ly5li3*Ey83-GGy1p3DJy3*xy5myi3*Qy83-GIy1p3DKy3*uy5mje3*Ny83uCy1p3DLy3*M");
    string_constant_16 = 
	    STATIC_STRING("y5nlje3-sy83uEy1p3DMy3*Oy5nnje3-uy83uFy1p3DNy3*Qy5otshe3-wy83-EJy1p3DOy3*Py5nkje3-vy83-79y1m3DPy01p3DQy3*Uy5rshort u3*-y83rCy1p3");
    string_constant_17 = STATIC_STRING("DRy3*Cy5odzhe3-xy83u*y");
    Cyrillic_character_a_list = regenerate_optimized_constant(list(13,
	    string_constant_5,string_constant_6,string_constant_7,
	    string_constant_8,string_constant_9,string_constant_10,
	    string_constant_11,string_constant_12,string_constant_13,
	    string_constant_14,string_constant_15,string_constant_16,
	    string_constant_17));
    if (Msw_cyrillic_code_map == UNBOUND) {
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
	Msw_cyrillic_code_map = the_array;
    }
    if (Unicode_index_to_slavic_font_direct_index_map == UNBOUND) {
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
	Unicode_index_to_slavic_font_direct_index_map = the_array;
    }
    Qcyrillic_gensym_character_code_for_key_name = 
	    STATIC_SYMBOL("CYRILLIC-GENSYM-CHARACTER-CODE-FOR-KEY-NAME",
	    AB_package);
    Cyrillic_gensym_character_code_for_key_name_prop = 
	    Qcyrillic_gensym_character_code_for_key_name;
    if (Key_cap_to_gensym_cyrillic_character_code_map == UNBOUND) {
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
	Key_cap_to_gensym_cyrillic_character_code_map = the_array;
    }
    utilize_cyrillic_character_a_list();
    string_constant_18 = 
	    STATIC_STRING("13Vy1mkk1mll1mmm1mnn1m3Syo1mop1mpq1mqt1mru1msv1mtw1mux1mvy1mw3Cy1mx3Dy1my3Qy1mz3Ry1m3Cy3Sy1m3Dy3Ty1m3Ey3Uy1m3Fy3Vy1m3Gy3Wy1m3Hy3");
    string_constant_19 = 
	    STATIC_STRING("Xy1m3Iy3Yy1m3Jy3Zy1m3Ky3iy1m3Ly3jy1m3My3ky1m3Ny3ly1m1m3-xy3=cy1m3my3*Ry1m1m3=ry3=sy1m3=ry3=sy1m3=ty3=ty1m1m3=uy3=vy1m3=uy3=vy1m3");
    string_constant_20 = STATIC_STRING("=wy3=wy1m3=xy3=xy");
    Gensym_unicode_row_correspondences = 
	    regenerate_optimized_constant(LIST_3(string_constant_18,
	    string_constant_19,string_constant_20));
    Qinvalid_unicode_full_row = STATIC_SYMBOL("INVALID-UNICODE-FULL-ROW",
	    AB_package);
    SET_SYMBOL_VALUE(Qinvalid_unicode_full_row,FIX((SI_Long)7L));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    vector_1 = make_array(5,FIX((SI_Long)256L),Kelement_type,
	    list_constant_1,Kinitial_element,Invalid_unicode_full_row);
    x = Nil;
    ab_loop_list_ = Gensym_unicode_row_correspondences;
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
    Gensym_to_unicode_full_row_map = vector_1;
    goto end_1;
    Gensym_to_unicode_full_row_map = Qnil;
  end_1:;
    Qinvalid_gensym_full_row = STATIC_SYMBOL("INVALID-GENSYM-FULL-ROW",
	    AB_package);
    SET_SYMBOL_VALUE(Qinvalid_gensym_full_row,FIX((SI_Long)246L));
    vector_1 = make_array(5,FIX((SI_Long)256L),Kelement_type,
	    list_constant_1,Kinitial_element,Invalid_gensym_full_row);
    x = Nil;
    ab_loop_list_ = Gensym_unicode_row_correspondences;
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
    Unicode_to_gensym_full_row_map = vector_1;
    goto end_2;
    Unicode_to_gensym_full_row_map = Qnil;
  end_2:;
    Qgensym_letterlike_symbol_block_start = 
	    STATIC_SYMBOL("GENSYM-LETTERLIKE-SYMBOL-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qgensym_letterlike_symbol_block_start,
	    FIX((SI_Long)4352L));
    Qunicode_letterlike_symbol_block_start = 
	    STATIC_SYMBOL("UNICODE-LETTERLIKE-SYMBOL-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qunicode_letterlike_symbol_block_start,
	    FIX((SI_Long)8448L));
    if (Unicode_offset_for_gensym_letterlike_symbol == UNBOUND)
	Unicode_offset_for_gensym_letterlike_symbol = 
		FIXNUM_MINUS(Gensym_letterlike_symbol_block_start,
		Unicode_letterlike_symbol_block_start);
    Qgensym_general_punctuation_character_block_start = 
	    STATIC_SYMBOL("GENSYM-GENERAL-PUNCTUATION-CHARACTER-BLOCK-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qgensym_general_punctuation_character_block_start,
	    FIX((SI_Long)4096L));
    Qunicode_general_punctuation_character_block_start = 
	    STATIC_SYMBOL("UNICODE-GENERAL-PUNCTUATION-CHARACTER-BLOCK-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qunicode_general_punctuation_character_block_start,
	    FIX((SI_Long)8192L));
    if (Unicode_offset_for_gensym_general_punctuation == UNBOUND)
	Unicode_offset_for_gensym_general_punctuation = 
		FIXNUM_MINUS(Gensym_general_punctuation_character_block_start,
		Unicode_general_punctuation_character_block_start);
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
    Unicode_jis_x_0208_mapping_hand_edits = list_constant_9;
    Qunicode_hebrew_character_block_start = 
	    STATIC_SYMBOL("UNICODE-HEBREW-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qunicode_hebrew_character_block_start,
	    FIX((SI_Long)1456L));
    Qunicode_hebrew_character_block_end = 
	    STATIC_SYMBOL("UNICODE-HEBREW-CHARACTER-BLOCK-END",AB_package);
    SET_SYMBOL_VALUE(Qunicode_hebrew_character_block_end,FIX((SI_Long)1524L));
    Qunicode_hebrew_precomposed_character_block_start = 
	    STATIC_SYMBOL("UNICODE-HEBREW-PRECOMPOSED-CHARACTER-BLOCK-START",
	    AB_package);
    SET_SYMBOL_VALUE(Qunicode_hebrew_precomposed_character_block_start,
	    FIX((SI_Long)64285L));
    Qunicode_hebrew_precomposed_character_block_end = 
	    STATIC_SYMBOL("UNICODE-HEBREW-PRECOMPOSED-CHARACTER-BLOCK-END",
	    AB_package);
    SET_SYMBOL_VALUE(Qunicode_hebrew_precomposed_character_block_end,
	    FIX((SI_Long)64335L));
    Qunicode_thai_character_block_start = 
	    STATIC_SYMBOL("UNICODE-THAI-CHARACTER-BLOCK-START",AB_package);
    SET_SYMBOL_VALUE(Qunicode_thai_character_block_start,FIX((SI_Long)3584L));
    Qunicode_thai_character_block_end = 
	    STATIC_SYMBOL("UNICODE-THAI-CHARACTER-BLOCK-END",AB_package);
    SET_SYMBOL_VALUE(Qunicode_thai_character_block_end,FIX((SI_Long)3711L));
    Qunicode_thai_glyph_variants_start = 
	    STATIC_SYMBOL("UNICODE-THAI-GLYPH-VARIANTS-START",AB_package);
    SET_SYMBOL_VALUE(Qunicode_thai_glyph_variants_start,FIX((SI_Long)63232L));
    Qunicode_thai_glyph_variants_end = 
	    STATIC_SYMBOL("UNICODE-THAI-GLYPH-VARIANTS-END",AB_package);
    SET_SYMBOL_VALUE(Qunicode_thai_glyph_variants_end,FIX((SI_Long)63247L));
    Qchar_backspace = STATIC_SYMBOL("CHAR-BACKSPACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_backspace,Char_backspace);
    SET_SYMBOL_VALUE(Qchar_backspace,CODE_CHAR(FIX((SI_Long)8L)));
    Qchar_tab = STATIC_SYMBOL("CHAR-TAB",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_tab,Char_tab);
    SET_SYMBOL_VALUE(Qchar_tab,CODE_CHAR(FIX((SI_Long)9L)));
    Qchar_linefeed = STATIC_SYMBOL("CHAR-LINEFEED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_linefeed,Char_linefeed);
    SET_SYMBOL_VALUE(Qchar_linefeed,CODE_CHAR(FIX((SI_Long)10L)));
    Qchar_page = STATIC_SYMBOL("CHAR-PAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_page,Char_page);
    SET_SYMBOL_VALUE(Qchar_page,CODE_CHAR(FIX((SI_Long)12L)));
    Qchar_return = STATIC_SYMBOL("CHAR-RETURN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_return,Char_return);
    SET_SYMBOL_VALUE(Qchar_return,CODE_CHAR(FIX((SI_Long)13L)));
    Qchar_rubout = STATIC_SYMBOL("CHAR-RUBOUT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_rubout,Char_rubout);
    SET_SYMBOL_VALUE(Qchar_rubout,CODE_CHAR(FIX((SI_Long)127L)));
    Qchar_control_at = STATIC_SYMBOL("CHAR-CONTROL-@",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_at,Char_control_at);
    SET_SYMBOL_VALUE(Qchar_control_at,CODE_CHAR(FIX((SI_Long)0L)));
    Qchar_control_a = STATIC_SYMBOL("CHAR-CONTROL-A",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_a,Char_control_a);
    SET_SYMBOL_VALUE(Qchar_control_a,CODE_CHAR(FIX((SI_Long)1L)));
    Qchar_control_b = STATIC_SYMBOL("CHAR-CONTROL-B",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_b,Char_control_b);
    SET_SYMBOL_VALUE(Qchar_control_b,CODE_CHAR(FIX((SI_Long)2L)));
    Qchar_control_c = STATIC_SYMBOL("CHAR-CONTROL-C",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_c,Char_control_c);
    SET_SYMBOL_VALUE(Qchar_control_c,CODE_CHAR(FIX((SI_Long)3L)));
    Qchar_control_d = STATIC_SYMBOL("CHAR-CONTROL-D",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_d,Char_control_d);
    SET_SYMBOL_VALUE(Qchar_control_d,CODE_CHAR(FIX((SI_Long)4L)));
    Qchar_control_e = STATIC_SYMBOL("CHAR-CONTROL-E",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_e,Char_control_e);
    SET_SYMBOL_VALUE(Qchar_control_e,CODE_CHAR(FIX((SI_Long)5L)));
    Qchar_control_f = STATIC_SYMBOL("CHAR-CONTROL-F",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_f,Char_control_f);
    SET_SYMBOL_VALUE(Qchar_control_f,CODE_CHAR(FIX((SI_Long)6L)));
    Qchar_control_g = STATIC_SYMBOL("CHAR-CONTROL-G",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_g,Char_control_g);
    SET_SYMBOL_VALUE(Qchar_control_g,CODE_CHAR(FIX((SI_Long)7L)));
    Qchar_control_h = STATIC_SYMBOL("CHAR-CONTROL-H",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_h,Char_control_h);
    SET_SYMBOL_VALUE(Qchar_control_h,CODE_CHAR(FIX((SI_Long)8L)));
    Qchar_control_i = STATIC_SYMBOL("CHAR-CONTROL-I",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_i,Char_control_i);
    SET_SYMBOL_VALUE(Qchar_control_i,CODE_CHAR(FIX((SI_Long)9L)));
    Qchar_control_j = STATIC_SYMBOL("CHAR-CONTROL-J",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_j,Char_control_j);
    SET_SYMBOL_VALUE(Qchar_control_j,CODE_CHAR(FIX((SI_Long)10L)));
    Qchar_control_k = STATIC_SYMBOL("CHAR-CONTROL-K",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_k,Char_control_k);
    SET_SYMBOL_VALUE(Qchar_control_k,CODE_CHAR(FIX((SI_Long)11L)));
    Qchar_control_l = STATIC_SYMBOL("CHAR-CONTROL-L",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_l,Char_control_l);
    SET_SYMBOL_VALUE(Qchar_control_l,CODE_CHAR(FIX((SI_Long)12L)));
    Qchar_control_m = STATIC_SYMBOL("CHAR-CONTROL-M",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_m,Char_control_m);
    SET_SYMBOL_VALUE(Qchar_control_m,CODE_CHAR(FIX((SI_Long)13L)));
    Qchar_control_n = STATIC_SYMBOL("CHAR-CONTROL-N",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_n,Char_control_n);
    SET_SYMBOL_VALUE(Qchar_control_n,CODE_CHAR(FIX((SI_Long)14L)));
    Qchar_control_o = STATIC_SYMBOL("CHAR-CONTROL-O",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_o,Char_control_o);
    SET_SYMBOL_VALUE(Qchar_control_o,CODE_CHAR(FIX((SI_Long)15L)));
    Qchar_control_p = STATIC_SYMBOL("CHAR-CONTROL-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_p,Char_control_p);
    SET_SYMBOL_VALUE(Qchar_control_p,CODE_CHAR(FIX((SI_Long)16L)));
    Qchar_control_q = STATIC_SYMBOL("CHAR-CONTROL-Q",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_q,Char_control_q);
    SET_SYMBOL_VALUE(Qchar_control_q,CODE_CHAR(FIX((SI_Long)17L)));
    Qchar_control_r = STATIC_SYMBOL("CHAR-CONTROL-R",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_r,Char_control_r);
    SET_SYMBOL_VALUE(Qchar_control_r,CODE_CHAR(FIX((SI_Long)18L)));
    Qchar_control_s = STATIC_SYMBOL("CHAR-CONTROL-S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_s,Char_control_s);
    SET_SYMBOL_VALUE(Qchar_control_s,CODE_CHAR(FIX((SI_Long)19L)));
    Qchar_control_t = STATIC_SYMBOL("CHAR-CONTROL-T",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_t,Char_control_t);
    SET_SYMBOL_VALUE(Qchar_control_t,CODE_CHAR(FIX((SI_Long)20L)));
    Qchar_control_u = STATIC_SYMBOL("CHAR-CONTROL-U",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_u,Char_control_u);
    SET_SYMBOL_VALUE(Qchar_control_u,CODE_CHAR(FIX((SI_Long)21L)));
    Qchar_control_v = STATIC_SYMBOL("CHAR-CONTROL-V",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_v,Char_control_v);
    SET_SYMBOL_VALUE(Qchar_control_v,CODE_CHAR(FIX((SI_Long)22L)));
    Qchar_control_w = STATIC_SYMBOL("CHAR-CONTROL-W",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_w,Char_control_w);
    SET_SYMBOL_VALUE(Qchar_control_w,CODE_CHAR(FIX((SI_Long)23L)));
    Qchar_control_x = STATIC_SYMBOL("CHAR-CONTROL-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_x,Char_control_x);
    SET_SYMBOL_VALUE(Qchar_control_x,CODE_CHAR(FIX((SI_Long)24L)));
    Qchar_control_y = STATIC_SYMBOL("CHAR-CONTROL-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_y,Char_control_y);
    SET_SYMBOL_VALUE(Qchar_control_y,CODE_CHAR(FIX((SI_Long)25L)));
    Qchar_control_z = STATIC_SYMBOL("CHAR-CONTROL-Z",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_z,Char_control_z);
    SET_SYMBOL_VALUE(Qchar_control_z,CODE_CHAR(FIX((SI_Long)26L)));
    Qchar_control_obt = STATIC_SYMBOL("CHAR-CONTROL-[",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_obt,Char_control_obt);
    SET_SYMBOL_VALUE(Qchar_control_obt,CODE_CHAR(FIX((SI_Long)27L)));
    Qchar_control_backslash = STATIC_SYMBOL("CHAR-CONTROL-BACKSLASH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_backslash,Char_control_backslash);
    SET_SYMBOL_VALUE(Qchar_control_backslash,CODE_CHAR(FIX((SI_Long)28L)));
    Qchar_control_cbt = STATIC_SYMBOL("CHAR-CONTROL-]",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_cbt,Char_control_cbt);
    SET_SYMBOL_VALUE(Qchar_control_cbt,CODE_CHAR(FIX((SI_Long)29L)));
    Qchar_control_ct = STATIC_SYMBOL("CHAR-CONTROL-^",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control_ct,Char_control_ct);
    SET_SYMBOL_VALUE(Qchar_control_ct,CODE_CHAR(FIX((SI_Long)30L)));
    Qchar_control__ = STATIC_SYMBOL("CHAR-CONTROL-_",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_control__,Char_control__);
    SET_SYMBOL_VALUE(Qchar_control__,CODE_CHAR(FIX((SI_Long)31L)));
    Qchar_escape = STATIC_SYMBOL("CHAR-ESCAPE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchar_escape,Char_escape);
    SET_SYMBOL_VALUE(Qchar_escape,CODE_CHAR(FIX((SI_Long)27L)));
    list_constant_10 = STATIC_LIST((SI_Long)6L,CHR(' '),CHR('\n'),
	    CHR('\t'),CHR('\f'),CHR('\r'),CHR('\n'));
    if (Whitespace_characters == UNBOUND)
	Whitespace_characters = list_constant_10;
    list_constant_11 = STATIC_LIST((SI_Long)6L,FIX((SI_Long)32L),
	    FIX((SI_Long)10L),FIX((SI_Long)9L),FIX((SI_Long)12L),
	    FIX((SI_Long)13L),FIX((SI_Long)10L));
    if (Whitespace_wide_characters == UNBOUND)
	Whitespace_wide_characters = list_constant_11;
}
