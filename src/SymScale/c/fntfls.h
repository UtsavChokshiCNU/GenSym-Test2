/* fntfls.h -- Header File for fntfls.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qunsigned_byte;

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

extern Object assq_function(Object,Object);
extern Object copy_gensym_pathname(Object);
extern Object copy_text_string(Object);
extern Object copy_text_string_with_case_conversion(Object,Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_make_pathname_with_copied_components(Object,Object,Object,Object,Object,Object,Object);
extern Object gensym_namestring(int,...);
extern Object get_asian_font_file_name(Object);
extern Object get_command_line_keyword_argument(int,...);
extern Object get_font_file_directory_pathname(void);
extern Object get_font_file_name(Object);
extern Object get_gensym_environment_variable(Object);
extern Object get_new_directory_pathname_dwim(Object);
extern Object ksc_to_gensym_ksc(Object);
extern Object make_empty_gensym_pathname(void);
extern Object merge_series_of_pathnames(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_pathname(Object);
extern Object reclaim_text_string(Object);
extern Object text_string_p(Object);
extern Object tformat_text_string(int,...);

#else

extern Object assq_function();
extern Object copy_gensym_pathname();
extern Object copy_text_string();
extern Object copy_text_string_with_case_conversion();
extern Object gensym_cons_1();
extern Object gensym_make_pathname_with_copied_components();
extern Object gensym_namestring();
extern Object get_asian_font_file_name();
extern Object get_command_line_keyword_argument();
extern Object get_font_file_directory_pathname();
extern Object get_font_file_name();
extern Object get_gensym_environment_variable();
extern Object get_new_directory_pathname_dwim();
extern Object ksc_to_gensym_ksc();
extern Object make_empty_gensym_pathname();
extern Object merge_series_of_pathnames();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_pathname();
extern Object reclaim_text_string();
extern Object text_string_p();
extern Object tformat_text_string();

#endif

/* variables/constants */
extern Object Asian_font_reading_information;
extern Object Chinesettf_font_filename;
extern Object Hangul16_font_filename;
extern Object Hangul24_font_filename;
extern Object Hangul_star_font_filename;
extern Object Hangulttf_font_filename;
extern Object Kanji16_font_filename;
extern Object Kanji24_font_filename;
extern Object Kanji_star_font_filename;
extern Object Minm_star_font_filename;
DECLARE_VARIABLE_WITH_SYMBOL(Process_specific_system_pathname, Qprocess_specific_system_pathname);
