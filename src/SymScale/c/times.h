/* times.h -- Header File for times.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
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

extern Object bytes_per_double_float_simple_array(Object);
extern Object chestnut_floorf_function(Object,Object);
extern Object compute_unix_time_offset(void);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object copyright_boilerplate_lines_of_text_1(void);
extern Object copyright_boilerplate_lines_of_text_2(void);
extern Object decode_universal_date(Object);
extern Object decode_unix_time_as_managed_float(Object);
extern Object encode_universal_date(Object,Object,Object);
extern Object encode_unix_date(Object,Object,Object);
extern Object encode_unix_time_after_failure(Object,Object,Object,Object,Object,Object);
extern Object extend_current_gensym_string(int,...);
extern Object generate_float_vector(Object);
extern Object gensym_decode_unix_time(Object);
extern Object gensym_encode_unix_time_as_gensym_float(Object,Object,Object,Object,Object,Object);
extern Object gensym_encode_unix_time_as_managed_float(Object,Object,Object,Object,Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object get_current_year(void);
extern Object get_decoded_real_time(void);
extern Object get_universal_date(void);
extern Object get_unix_time_to_the_second_as_managed_float(void);
extern Object leap_year_p(Object);
extern Object make_copyright_boilerplate_lines_of_text_for_tw(void);
extern Object make_gensym_list_1(Object);
extern Object nanp(Object);
extern Object null_or_zero_p(Object);
extern Object print_day_of_week_and_hour(Object,Object);
extern Object print_decoded_date(Object,Object,Object);
extern Object print_decoded_time(Object,Object,Object,Object,Object,Object);
extern Object print_decoded_time_of_day(Object,Object,Object);
extern Object print_hour_and_minute(Object,Object);
extern Object print_minute_and_second(Object,Object);
extern Object print_month_and_date(Object,Object);
extern Object print_month_and_year(Object,Object);
extern Object print_relative_days(Object);
extern Object print_relative_hours(Object);
extern Object print_relative_hours_and_minutes(Object,Object);
extern Object print_relative_time(Object);
extern Object print_relative_weeks(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object select_am_or_pm(int,...);
extern Object select_day_of_week_string(Object);
extern Object select_month_string(Object);
extern Object tformat(int,...);
extern Object tformat_text_string(int,...);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_general_string(Object);
extern Object twrite_positive_fixnum(Object);
extern Object twrite_symbol(int,...);
extern Object twrite_wide_character(Object);
extern Object valid_date_for_month_p(Object,Object,Object);
extern Object write_floating_point_number(int,...);
extern Object write_floating_point_number_simple_c_format(int,...);

#else

extern Object bytes_per_double_float_simple_array();
extern Object chestnut_floorf_function();
extern Object compute_unix_time_offset();
extern Object copy_list_using_gensym_conses_1();
extern Object copyright_boilerplate_lines_of_text_1();
extern Object copyright_boilerplate_lines_of_text_2();
extern Object decode_universal_date();
extern Object decode_unix_time_as_managed_float();
extern Object encode_universal_date();
extern Object encode_unix_date();
extern Object encode_unix_time_after_failure();
extern Object extend_current_gensym_string();
extern Object generate_float_vector();
extern Object gensym_decode_unix_time();
extern Object gensym_encode_unix_time_as_gensym_float();
extern Object gensym_encode_unix_time_as_managed_float();
extern Object gensym_list_2();
extern Object get_current_year();
extern Object get_decoded_real_time();
extern Object get_universal_date();
extern Object get_unix_time_to_the_second_as_managed_float();
extern Object leap_year_p();
extern Object make_copyright_boilerplate_lines_of_text_for_tw();
extern Object make_gensym_list_1();
extern Object nanp();
extern Object null_or_zero_p();
extern Object print_day_of_week_and_hour();
extern Object print_decoded_date();
extern Object print_decoded_time();
extern Object print_decoded_time_of_day();
extern Object print_hour_and_minute();
extern Object print_minute_and_second();
extern Object print_month_and_date();
extern Object print_month_and_year();
extern Object print_relative_days();
extern Object print_relative_hours();
extern Object print_relative_hours_and_minutes();
extern Object print_relative_time();
extern Object print_relative_weeks();
extern Object record_system_variable();
extern Object select_am_or_pm();
extern Object select_day_of_week_string();
extern Object select_month_string();
extern Object tformat();
extern Object tformat_text_string();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_general_string();
extern Object twrite_positive_fixnum();
extern Object twrite_symbol();
extern Object twrite_wide_character();
extern Object valid_date_for_month_p();
extern Object write_floating_point_number();
extern Object write_floating_point_number_simple_c_format();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Copyright_boilerplate_lines_of_text_1, Qcopyright_boilerplate_lines_of_text_1);
DECLARE_VARIABLE_WITH_SYMBOL(Copyright_boilerplate_lines_of_text_2, Qcopyright_boilerplate_lines_of_text_2);
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
extern Object Days_before_this_month;
extern Object Disclaimer_for_licensing_and_authorization;
extern Object Disclaimer_for_release_quality_software;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
extern Object Global_daylight_saving_time_adjustment;
extern Object Restricted_rights_legend;
extern Object Seconds_from_1900_to_1970;
#define Seconds_per_day FIX((SI_Long)86400L)
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Unix_time_offset_for_encoding, Qunix_time_offset_for_encoding);
DECLARE_VARIABLE_WITH_SYMBOL(Unix_time_offset_was_computed_qm, Qunix_time_offset_was_computed_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Year_at_compilation_time, Qyear_at_compilation_time);
