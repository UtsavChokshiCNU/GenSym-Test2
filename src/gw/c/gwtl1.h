/* gwtl1.h -- Header File for gwtl1.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qstring;

extern Object Pclos;
extern Object Pclos_run;
extern Object Pclosx;
extern Object Pcl;
extern Object Pcl_user;
extern Object Pkeyword;
extern Object Ptrun;
extern Object Ptx;

/* function declarations */

#ifdef USE_PROTOTYPES

extern Object g2int_alarm_p(Object);
extern Object g2int_coerce_into_foreign_string_pad(Object);
extern Object g2int_coerce_into_foreign_string_pad_with_crlf(Object);
extern Object g2int_extend_current_gensym_string(int,...);
extern Object g2int_make_text_safe_for_c(Object);
extern Object g2int_make_text_string_from_c_string_in_foreign_string_pad(void);
extern Object g2int_make_text_string_from_foreign_string_pad(Object);
extern Object g2int_obtain_simple_gensym_string(Object);
extern Object g2int_twrite_text_gensym_pt_to_i_ascii(Object);
extern Object g2int_twrite_text_i_ascii_to_gensym_pt(Object);
extern Object g2int_twrite_wide_character(Object);

#else

extern Object g2int_alarm_p();
extern Object g2int_coerce_into_foreign_string_pad();
extern Object g2int_coerce_into_foreign_string_pad_with_crlf();
extern Object g2int_extend_current_gensym_string();
extern Object g2int_make_text_safe_for_c();
extern Object g2int_make_text_string_from_c_string_in_foreign_string_pad();
extern Object g2int_make_text_string_from_foreign_string_pad();
extern Object g2int_obtain_simple_gensym_string();
extern Object g2int_twrite_text_gensym_pt_to_i_ascii();
extern Object g2int_twrite_text_i_ascii_to_gensym_pt();
extern Object g2int_twrite_wide_character();

#endif

/* variables/constants */
extern Object G2int_current_foreign_string_pad;
extern Object G2int_current_gensym_string;
extern Object G2int_current_twriting_output_type;
extern Object G2int_fill_pointer_for_current_gensym_string;
extern Object G2int_gensym_character_of_iso_latin_1_character;
extern Object G2int_handling_of_iso_latin_1_character;
extern Object G2int_max_of_foreign_string_pad;
extern Object G2int_null_char;
extern Object G2int_null_character_for_c_strings;
extern Object G2int_tilde_escape_to_iso_latin_1_map;
extern Object G2int_total_length_of_current_gensym_string;
