/* os-mem.h -- Header File for os-mem.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
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

extern Object announce_region_sizes(Object);
extern Object bytes_allocated_for_image_tiles(void);
extern Object bytes_per_double_float_simple_array(Object);
extern Object bytes_per_long_simple_array(Object);
extern Object bytes_per_simple_string(Object);
extern Object bytes_per_simple_vector(Object);
extern Object bytes_per_typed_simple_array(Object,Object);
extern Object bytes_per_unsigned_byte_16_simple_array(Object);
extern Object bytes_per_unsigned_byte_8_simple_array(Object);
extern Object check_for_region_deficits(Object);
extern Object exit_lisp_process(int,...);
extern Object format_into_string_grouping_thousands(Object);
extern Object g2_memory_available(void);
extern Object g2_memory_available_as_float(void);
extern Object g2_memory_size(void);
extern Object g2_memory_size_as_float(void);
extern Object g2_memory_usage(void);
extern Object g2_memory_usage_as_float(void);
extern Object g2_region_memory_available(Object);
extern Object g2_region_memory_available_as_float(Object);
extern Object g2_region_memory_size(Object);
extern Object g2_region_memory_size_as_float(Object);
extern Object g2_region_memory_usage(Object);
extern Object g2_region_memory_usage_as_float(Object);
extern Object get_command_line_keyword_argument_as_memory_size(int,...);
extern Object initialize_all_region_info(Object);
extern Object initialize_memory_for_region(Object,Object);
extern Object make_region_info(Object,Object,Object,Object);
extern Object maximum_bytes_for_image_tiles(void);
extern Object read_memory_size_for_gensym_environment_variable(Object);
extern Object region_is_preallocated_p(Object);
extern Object reject_proposed_region_size(Object,Object,Object,Object,Object);
extern Object report_memory_usage(Object);
extern Object right_justify_in_column(Object,Object);
extern Object set_up_lisp_memory_management(Object);

#else

extern Object announce_region_sizes();
extern Object bytes_allocated_for_image_tiles();
extern Object bytes_per_double_float_simple_array();
extern Object bytes_per_long_simple_array();
extern Object bytes_per_simple_string();
extern Object bytes_per_simple_vector();
extern Object bytes_per_typed_simple_array();
extern Object bytes_per_unsigned_byte_16_simple_array();
extern Object bytes_per_unsigned_byte_8_simple_array();
extern Object check_for_region_deficits();
extern Object exit_lisp_process();
extern Object format_into_string_grouping_thousands();
extern Object g2_memory_available();
extern Object g2_memory_available_as_float();
extern Object g2_memory_size();
extern Object g2_memory_size_as_float();
extern Object g2_memory_usage();
extern Object g2_memory_usage_as_float();
extern Object g2_region_memory_available();
extern Object g2_region_memory_available_as_float();
extern Object g2_region_memory_size();
extern Object g2_region_memory_size_as_float();
extern Object g2_region_memory_usage();
extern Object g2_region_memory_usage_as_float();
extern Object get_command_line_keyword_argument_as_memory_size();
extern Object initialize_all_region_info();
extern Object initialize_memory_for_region();
extern Object make_region_info();
extern Object maximum_bytes_for_image_tiles();
extern Object read_memory_size_for_gensym_environment_variable();
extern Object region_is_preallocated_p();
extern Object reject_proposed_region_size();
extern Object report_memory_usage();
extern Object right_justify_in_column();
extern Object set_up_lisp_memory_management();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(All_region_info, Qall_region_info);
#define Bytes_per_rtl_double FIX((SI_Long)8L)
#define Bytes_per_rtl_int64 FIX((SI_Long)8L)
extern Object Bytes_per_rtl_ptr;
extern Object Default_bytes_for_renderings;
#define Default_memory_tab_setting FIX((SI_Long)30L)
#define Desired_memory_tab_setting FIX((SI_Long)45L)
DECLARE_VARIABLE_WITH_SYMBOL(G2_machine_type, Qg2_machine_type);
DECLARE_VARIABLE_WITH_SYMBOL(Is_g2_enterprise_qm, Qis_g2_enterprise_qm);
#define Measured_memory_tab_setting FIX((SI_Long)60L)
extern Object Minimum_bytes_for_renderings;
#define Minimum_memory_tab_setting FIX((SI_Long)15L)
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_memory_regions, Qnumber_of_memory_regions);
DECLARE_VARIABLE_WITH_SYMBOL(Out_of_memory_handler, Qout_of_memory_handler);
DECLARE_VARIABLE_WITH_SYMBOL(Region_1_info, Qregion_1_info);
DECLARE_VARIABLE_WITH_SYMBOL(Region_2_info, Qregion_2_info);
DECLARE_VARIABLE_WITH_SYMBOL(Region_3_info, Qregion_3_info);
#define Size_of_chunks_for_allocate_to_target FIX((SI_Long)4000000L)
DECLARE_VARIABLE_WITH_SYMBOL(Unrecoverable_error_p, Qunrecoverable_error_p);
