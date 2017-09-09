/* clocks.h -- Header File for clocks.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

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

extern Object g2int_adjust_g2_clock_times_after_discontinuity_1(Object);
extern Object g2int_adjust_task_times_after_clock_discontinuity(Object,Object);
extern Object g2int_allocate_byte_vector_16(Object);
extern Object g2int_bytes_per_double_float_simple_array(Object);
extern Object g2int_c_native_clock_ticks_or_cache(Object,Object);
extern Object g2int_change_current_time_in_nupec_catch_up_mode(Object);
extern Object g2int_decode_gensym_time(Object);
extern Object g2int_encode_gensym_time(Object,Object,Object,Object,Object,Object);
extern Object g2int_encode_unix_time_after_failure(Object,Object,Object,Object,Object,Object);
extern Object g2int_g2_time_clock_discontinuity(Object);
extern Object g2int_generate_float_vector(Object);
extern Object g2int_gensym_decode_unix_time(Object);
extern Object g2int_get_real_gensym_time(void);
extern Object g2int_initialize_gensym_time(void);
extern Object g2int_milliseconds_to_next_task(void);
extern Object g2int_partition_managed_float(Object);
extern Object g2int_preset_gensym_time_for_initialization(void);
extern Object g2int_real_time_clock_discontinuity(Object);
extern Object g2int_reclaim_managed_simple_float_array_of_length_1(Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_same_gensym_date_p(Object,Object);
extern Object g2int_tick_the_clock_for_tw_or_gsi(void);
extern Object g2int_tick_the_g2_fast_time_clock(Object);
extern Object g2int_tick_the_g2_real_time_clock(Object);
extern Object g2int_tick_the_g2_simulated_time_clock(Object);
extern Object g2int_tick_the_nupec_catch_up_clock(Object);
extern Object g2int_tick_the_real_time_clock(Object);
extern Object g2int_unpack_future_tasks_into_current_task_queues(Object);
extern Object g2int_update_g2_time_to_tick_after_scheduling_change(void);

#else

extern Object g2int_adjust_g2_clock_times_after_discontinuity_1();
extern Object g2int_adjust_task_times_after_clock_discontinuity();
extern Object g2int_allocate_byte_vector_16();
extern Object g2int_bytes_per_double_float_simple_array();
extern Object g2int_c_native_clock_ticks_or_cache();
extern Object g2int_change_current_time_in_nupec_catch_up_mode();
extern Object g2int_decode_gensym_time();
extern Object g2int_encode_gensym_time();
extern Object g2int_encode_unix_time_after_failure();
extern Object g2int_g2_time_clock_discontinuity();
extern Object g2int_generate_float_vector();
extern Object g2int_gensym_decode_unix_time();
extern Object g2int_get_real_gensym_time();
extern Object g2int_initialize_gensym_time();
extern Object g2int_milliseconds_to_next_task();
extern Object g2int_partition_managed_float();
extern Object g2int_preset_gensym_time_for_initialization();
extern Object g2int_real_time_clock_discontinuity();
extern Object g2int_reclaim_managed_simple_float_array_of_length_1();
extern Object g2int_record_system_variable();
extern Object g2int_same_gensym_date_p();
extern Object g2int_tick_the_clock_for_tw_or_gsi();
extern Object g2int_tick_the_g2_fast_time_clock();
extern Object g2int_tick_the_g2_real_time_clock();
extern Object g2int_tick_the_g2_simulated_time_clock();
extern Object g2int_tick_the_nupec_catch_up_clock();
extern Object g2int_tick_the_real_time_clock();
extern Object g2int_unpack_future_tasks_into_current_task_queues();
extern Object g2int_update_g2_time_to_tick_after_scheduling_change();

#endif

/* variables/constants */
extern Object G2int_available_gensym_conses;
extern Object G2int_created_simple_float_array_pool_arrays;
extern Object G2int_current_g2_time;
extern Object G2int_current_real_time;
extern Object G2int_fixnum_time_of_last_g2_tick;
extern Object G2int_fixnum_time_of_last_real_time_tick;
extern Object G2int_fixnum_time_units_per_second;
extern Object G2int_fixnum_time_until_g2_time_tick;
#define G2int_fixnum_time_until_real_time_tick FIX((SI_Long)1L)
extern Object G2int_force_clock_tick;
extern Object G2int_future_g2_time_tasks;
extern Object G2int_future_real_time_tasks;
extern Object G2int_g2_time_at_start;
extern Object G2int_g2_time_at_start_as_text_string;
extern Object G2int_g2_time_to_tick_p_base;
extern Object G2int_gensym_base_time_as_managed_float;
extern Object G2int_gensym_time;
extern Object G2int_gensym_time_at_start;
extern Object G2int_global_daylight_saving_time_adjustment;
extern Object G2int_inhibit_non_real_time_clock_ticksqm;
#define G2int_most_negative_fixnum32 FIX((SI_Long)-536870912L)
extern Object G2int_most_negative_fixnum_as_float;
extern Object G2int_most_positive_fixnum_as_float;
extern Object G2int_most_recent_g2_time;
extern Object G2int_nupec_catch_up_mode_caught_upqm;
extern Object G2int_real_time_of_last_g2_tick;
extern Object G2int_real_time_to_tick_p_base;
extern Object G2int_seconds_from_1900_to_1970;
extern Object G2int_simple_float_array_pool_memory_usage;
extern Object G2int_starsome_time_agostar;
extern Object G2int_system_has_paused;
extern Object G2int_system_is_running;
extern Object G2int_vector_of_simple_float_array_pools;
extern Object G2int_warmboot_current_time;
extern Object G2int_warmboot_simulated_time;
extern Object G2int_warmbooting_with_catch_upqm;
extern Object G2int_warmbootingqm;
