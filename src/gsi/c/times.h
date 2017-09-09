/* times.h -- Header File for times.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qsecond;
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

extern Object g2int_bytes_per_double_float_simple_array(Object);
extern Object g2int_chestnut_floorf_function(Object,Object);
extern Object g2int_compute_unix_time_offset(void);
extern Object g2int_copy_list_using_gensym_conses_1(Object);
extern Object g2int_copyright_boilerplate_lines_of_text_1(void);
extern Object g2int_copyright_boilerplate_lines_of_text_2(void);
extern Object g2int_decode_unix_time_as_managed_float(Object);
extern Object g2int_encode_universal_date(Object,Object,Object);
extern Object g2int_encode_unix_date(Object,Object,Object);
extern Object g2int_encode_unix_time_after_failure(Object,Object,Object,Object,Object,Object);
extern Object g2int_extend_current_gensym_string(int,...);
extern Object g2int_generate_float_vector(Object);
extern Object g2int_gensym_decode_unix_time(Object);
extern Object g2int_gensym_encode_unix_time_as_gensym_float(Object,Object,Object,Object,Object,Object);
extern Object g2int_gensym_encode_unix_time_as_managed_float(Object,Object,Object,Object,Object,Object);
extern Object g2int_gensym_list_2(Object,Object);
extern Object g2int_get_current_year(void);
extern Object g2int_get_decoded_real_time(void);
extern Object g2int_get_universal_date(void);
extern Object g2int_get_unix_time_to_the_second_as_managed_float(void);
extern Object g2int_leap_year_p(Object);
extern Object g2int_make_copyright_boilerplate_lines_of_text_for_tw(void);
extern Object g2int_make_gensym_list_1(Object);
extern Object g2int_nanp(Object);
extern Object g2int_null_or_zero_p(Object);
extern Object g2int_print_day_of_week_and_hour(Object,Object);
extern Object g2int_print_decoded_date(Object,Object,Object);
extern Object g2int_print_decoded_time(Object,Object,Object,Object,Object,Object);
extern Object g2int_print_decoded_time_of_day(Object,Object,Object);
extern Object g2int_print_hour_and_minute(Object,Object);
extern Object g2int_print_minute_and_second(Object,Object);
extern Object g2int_print_month_and_date(Object,Object);
extern Object g2int_print_month_and_year(Object,Object);
extern Object g2int_print_relative_days(Object);
extern Object g2int_print_relative_hours(Object);
extern Object g2int_print_relative_hours_and_minutes(Object,Object);
extern Object g2int_print_relative_time(Object);
extern Object g2int_print_relative_weeks(Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_select_am_or_pm(int,...);
extern Object g2int_select_day_of_week_string(Object);
extern Object g2int_select_month_string(Object);
extern Object g2int_tformat(int,...);
extern Object g2int_tformat_text_string(int,...);
extern Object g2int_twrite_beginning_of_wide_string(Object,Object);
extern Object g2int_twrite_general_string(Object);
extern Object g2int_twrite_positive_fixnum(Object);
extern Object g2int_twrite_symbol(int,...);
extern Object g2int_twrite_wide_character(Object);
extern Object g2int_valid_date_for_month_p(Object,Object,Object);
extern Object g2int_write_floating_point_number(int,...);
extern Object g2int_write_floating_point_number_simple_c_format(int,...);

#else

extern Object g2int_bytes_per_double_float_simple_array();
extern Object g2int_chestnut_floorf_function();
extern Object g2int_compute_unix_time_offset();
extern Object g2int_copy_list_using_gensym_conses_1();
extern Object g2int_copyright_boilerplate_lines_of_text_1();
extern Object g2int_copyright_boilerplate_lines_of_text_2();
extern Object g2int_decode_unix_time_as_managed_float();
extern Object g2int_encode_universal_date();
extern Object g2int_encode_unix_date();
extern Object g2int_encode_unix_time_after_failure();
extern Object g2int_extend_current_gensym_string();
extern Object g2int_generate_float_vector();
extern Object g2int_gensym_decode_unix_time();
extern Object g2int_gensym_encode_unix_time_as_gensym_float();
extern Object g2int_gensym_encode_unix_time_as_managed_float();
extern Object g2int_gensym_list_2();
extern Object g2int_get_current_year();
extern Object g2int_get_decoded_real_time();
extern Object g2int_get_universal_date();
extern Object g2int_get_unix_time_to_the_second_as_managed_float();
extern Object g2int_leap_year_p();
extern Object g2int_make_copyright_boilerplate_lines_of_text_for_tw();
extern Object g2int_make_gensym_list_1();
extern Object g2int_nanp();
extern Object g2int_null_or_zero_p();
extern Object g2int_print_day_of_week_and_hour();
extern Object g2int_print_decoded_date();
extern Object g2int_print_decoded_time();
extern Object g2int_print_decoded_time_of_day();
extern Object g2int_print_hour_and_minute();
extern Object g2int_print_minute_and_second();
extern Object g2int_print_month_and_date();
extern Object g2int_print_month_and_year();
extern Object g2int_print_relative_days();
extern Object g2int_print_relative_hours();
extern Object g2int_print_relative_hours_and_minutes();
extern Object g2int_print_relative_time();
extern Object g2int_print_relative_weeks();
extern Object g2int_record_system_variable();
extern Object g2int_select_am_or_pm();
extern Object g2int_select_day_of_week_string();
extern Object g2int_select_month_string();
extern Object g2int_tformat();
extern Object g2int_tformat_text_string();
extern Object g2int_twrite_beginning_of_wide_string();
extern Object g2int_twrite_general_string();
extern Object g2int_twrite_positive_fixnum();
extern Object g2int_twrite_symbol();
extern Object g2int_twrite_wide_character();
extern Object g2int_valid_date_for_month_p();
extern Object g2int_write_floating_point_number();
extern Object g2int_write_floating_point_number_simple_c_format();

#endif

/* variables/constants */
extern Object G2int_available_gensym_conses;
extern Object G2int_copyright_boilerplate_lines_of_text_1;
extern Object G2int_copyright_boilerplate_lines_of_text_2;
extern Object G2int_created_simple_float_array_pool_arrays;
extern Object G2int_current_gensym_string;
extern Object G2int_current_twriting_output_type;
extern Object G2int_days_before_this_month;
extern Object G2int_disclaimer_for_licensing_and_authorization;
extern Object G2int_disclaimer_for_release_quality_software;
extern Object G2int_fill_pointer_for_current_gensym_string;
extern Object G2int_global_daylight_saving_time_adjustment;
extern Object G2int_restricted_rights_legend;
extern Object G2int_seconds_from_1900_to_1970;
#define G2int_seconds_per_day FIX((SI_Long)86400L)
extern Object G2int_simple_float_array_pool_memory_usage;
extern Object G2int_total_length_of_current_gensym_string;
extern Object G2int_unix_time_offset_for_encoding;
extern Object G2int_unix_time_offset_was_computedqm;
extern Object G2int_vector_of_simple_float_array_pools;
extern Object G2int_year_at_compilation_time;
