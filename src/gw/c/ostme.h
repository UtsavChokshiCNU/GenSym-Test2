/* ostme.h -- Header File for ostme.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Kelement_type;
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

extern Object g2int_c_get_current_time_zone(Object,Object);
extern Object g2int_chestnut_floorf_function(Object,Object);
extern Object g2int_chestnut_modf_function(Object,Object);
extern Object g2int_copy_text_string(Object);
extern Object g2int_copy_wide_string_given_length(Object,Object);
extern Object g2int_gensym_decode_unix_time(Object);
extern Object g2int_get_current_time_zone(void);
extern Object g2int_make_gensym_time_array(void);
extern Object g2int_make_wide_string_function(Object);
extern Object g2int_reclaim_wide_string(Object);
extern Object g2int_time_zone_in_hours(void);

#else

extern Object g2int_c_get_current_time_zone();
extern Object g2int_chestnut_floorf_function();
extern Object g2int_chestnut_modf_function();
extern Object g2int_copy_text_string();
extern Object g2int_copy_wide_string_given_length();
extern Object g2int_gensym_decode_unix_time();
extern Object g2int_get_current_time_zone();
extern Object g2int_make_gensym_time_array();
extern Object g2int_make_wide_string_function();
extern Object g2int_reclaim_wide_string();
extern Object g2int_time_zone_in_hours();

#endif

/* variables/constants */
extern Object G2int_2_to_31_plus_62_years;
extern Object G2int_68_years_in_seconds;
extern Object G2int_gensym_time_array;
extern Object G2int_global_daylight_saving_time_adjustment;
