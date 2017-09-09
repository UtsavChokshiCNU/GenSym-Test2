/* ostme.h -- Header File for ostme.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
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

extern Object c_get_current_time_zone(Object,Object);
extern Object chestnut_floorf_function(Object,Object);
extern Object chestnut_modf_function(Object,Object);
extern Object copy_text_string(Object);
extern Object copy_wide_string_given_length(Object,Object);
extern Object gensym_decode_unix_time(Object);
extern Object get_current_time_zone(void);
extern Object make_gensym_time_array(void);
extern Object make_wide_string_function(Object);
extern Object reclaim_wide_string(Object);
extern Object time_zone_in_hours(void);

#else

extern Object c_get_current_time_zone();
extern Object chestnut_floorf_function();
extern Object chestnut_modf_function();
extern Object copy_text_string();
extern Object copy_wide_string_given_length();
extern Object gensym_decode_unix_time();
extern Object get_current_time_zone();
extern Object make_gensym_time_array();
extern Object make_wide_string_function();
extern Object reclaim_wide_string();
extern Object time_zone_in_hours();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_time_array, Qgensym_time_array);
extern Object Global_daylight_saving_time_adjustment;
extern Object N_2_to_31_plus_62_years;
extern Object N_68_years_in_seconds;
extern Object Seconds_from_1900_to_1990;
