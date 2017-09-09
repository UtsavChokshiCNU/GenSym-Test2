/* os-mem.h -- Header File for os-mem.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcharacter;
extern Object Qdouble_float;
extern Object Kdynamic;
extern Object Kinitial_element;
extern Object Qsingle_float;
extern Object Kstatic;
extern Object Qstring;
extern Object Qstring_char;
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

extern Object g2int_announce_region_sizes(Object);
extern Object g2int_bytes_allocated_for_image_tiles(void);
extern Object g2int_bytes_per_double_float_simple_array(Object);
extern Object g2int_bytes_per_long_simple_array(Object);
extern Object g2int_bytes_per_simple_string(Object);
extern Object g2int_bytes_per_simple_vector(Object);
extern Object g2int_bytes_per_typed_simple_array(Object,Object);
extern Object g2int_bytes_per_unsigned_byte_16_simple_array(Object);
extern Object g2int_bytes_per_unsigned_byte_8_simple_array(Object);
extern Object g2int_check_for_region_deficits(Object);
extern Object g2int_exit_lisp_process(int,...);
extern Object g2int_format_into_string_grouping_thousands(Object);
extern Object g2int_g2_memory_available(void);
extern Object g2int_g2_memory_available_as_float(void);
extern Object g2int_g2_memory_size(void);
extern Object g2int_g2_memory_size_as_float(void);
extern Object g2int_g2_memory_usage(void);
extern Object g2int_g2_memory_usage_as_float(void);
extern Object g2int_g2_region_memory_available(Object);
extern Object g2int_g2_region_memory_available_as_float(Object);
extern Object g2int_g2_region_memory_size(Object);
extern Object g2int_g2_region_memory_size_as_float(Object);
extern Object g2int_g2_region_memory_usage(Object);
extern Object g2int_g2_region_memory_usage_as_float(Object);
extern Object g2int_get_command_line_keyword_argument_as_memory_size(int,...);
extern Object g2int_gsi_option_is_set_p(Object);
extern Object g2int_initialize_all_region_info(Object);
extern Object g2int_initialize_memory_for_region(Object,Object);
extern Object g2int_make_region_info(Object,Object,Object,Object);
extern Object g2int_maximum_bytes_for_image_tiles(void);
extern Object g2int_read_memory_size_for_gensym_environment_variable(Object);
extern Object g2int_region_is_preallocated_p(Object);
extern Object g2int_reject_proposed_region_size(Object,Object,Object,Object,Object);
extern Object g2int_report_memory_usage(Object);
extern Object g2int_right_justify_in_column(Object,Object);
extern Object g2int_set_up_lisp_memory_management(Object);

#else

extern Object g2int_announce_region_sizes();
extern Object g2int_bytes_allocated_for_image_tiles();
extern Object g2int_bytes_per_double_float_simple_array();
extern Object g2int_bytes_per_long_simple_array();
extern Object g2int_bytes_per_simple_string();
extern Object g2int_bytes_per_simple_vector();
extern Object g2int_bytes_per_typed_simple_array();
extern Object g2int_bytes_per_unsigned_byte_16_simple_array();
extern Object g2int_bytes_per_unsigned_byte_8_simple_array();
extern Object g2int_check_for_region_deficits();
extern Object g2int_exit_lisp_process();
extern Object g2int_format_into_string_grouping_thousands();
extern Object g2int_g2_memory_available();
extern Object g2int_g2_memory_available_as_float();
extern Object g2int_g2_memory_size();
extern Object g2int_g2_memory_size_as_float();
extern Object g2int_g2_memory_usage();
extern Object g2int_g2_memory_usage_as_float();
extern Object g2int_g2_region_memory_available();
extern Object g2int_g2_region_memory_available_as_float();
extern Object g2int_g2_region_memory_size();
extern Object g2int_g2_region_memory_size_as_float();
extern Object g2int_g2_region_memory_usage();
extern Object g2int_g2_region_memory_usage_as_float();
extern Object g2int_get_command_line_keyword_argument_as_memory_size();
extern Object g2int_gsi_option_is_set_p();
extern Object g2int_initialize_all_region_info();
extern Object g2int_initialize_memory_for_region();
extern Object g2int_make_region_info();
extern Object g2int_maximum_bytes_for_image_tiles();
extern Object g2int_read_memory_size_for_gensym_environment_variable();
extern Object g2int_region_is_preallocated_p();
extern Object g2int_reject_proposed_region_size();
extern Object g2int_report_memory_usage();
extern Object g2int_right_justify_in_column();
extern Object g2int_set_up_lisp_memory_management();

#endif

/* variables/constants */
extern Object G2int_all_region_info;
#define G2int_bytes_per_rtl_double FIX((SI_Long)8L)
#define G2int_bytes_per_rtl_int64 FIX((SI_Long)8L)
extern Object G2int_bytes_per_rtl_ptr;
extern Object G2int_default_bytes_for_renderings;
#define G2int_default_memory_tab_setting FIX((SI_Long)30L)
#define G2int_desired_memory_tab_setting FIX((SI_Long)45L)
extern Object G2int_g2_machine_type;
extern Object G2int_gsi_suppress_output;
#define G2int_measured_memory_tab_setting FIX((SI_Long)60L)
extern Object G2int_minimum_bytes_for_renderings;
#define G2int_minimum_memory_tab_setting FIX((SI_Long)15L)
extern Object G2int_number_of_memory_regions;
extern Object G2int_out_of_memory_handler;
extern Object G2int_region_1_info;
extern Object G2int_region_2_info;
extern Object G2int_region_3_info;
#define G2int_size_of_chunks_for_allocate_to_target FIX((SI_Long)4000000L)
extern Object G2int_staris_g2_enterpriseqmstar;
extern Object G2int_unrecoverable_error_p;
