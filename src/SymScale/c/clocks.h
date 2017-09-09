/* clocks.h -- Header File for clocks.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
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

extern Object add_delta_time_to_variables_and_parameters(Object);
extern Object adjust_g2_clock_times_after_discontinuity_1(Object);
extern Object adjust_task_times_after_clock_discontinuity(Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object change_current_time_in_nupec_catch_up_mode(Object);
extern Object decode_gensym_time(Object);
extern Object encode_gensym_time(Object,Object,Object,Object,Object,Object);
extern Object encode_unix_time_after_failure(Object,Object,Object,Object,Object,Object);
extern Object g2_time_clock_discontinuity(Object);
extern Object generate_float_vector(Object);
extern Object gensym_decode_unix_time(Object);
extern Object get_real_gensym_time(void);
extern Object initialize_gensym_time(void);
extern Object milliseconds_to_next_task(void);
extern Object minimum_scheduling_interval_function(Object);
extern Object partition_managed_float(Object);
extern Object preset_gensym_time_for_initialization(void);
extern Object real_time_clock_discontinuity(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object same_gensym_date_p(Object,Object);
extern Object scheduler_mode_function(Object);
extern Object tick_the_clock_for_tw_or_gsi(void);
extern Object tick_the_g2_fast_time_clock(Object);
extern Object tick_the_g2_real_time_clock(Object);
extern Object tick_the_g2_simulated_time_clock(Object);
extern Object tick_the_nupec_catch_up_clock(Object);
extern Object tick_the_real_time_clock(Object);
extern Object unpack_future_tasks_into_current_task_queues(Object);
extern Object update_g2_time_to_tick_after_scheduling_change(void);
extern Object update_trend_charts_for_clock_discontinuity(Object);

#else

extern Object add_delta_time_to_variables_and_parameters();
extern Object adjust_g2_clock_times_after_discontinuity_1();
extern Object adjust_task_times_after_clock_discontinuity();
extern Object allocate_byte_vector_16();
extern Object bytes_per_double_float_simple_array();
extern Object c_native_clock_ticks_or_cache();
extern Object change_current_time_in_nupec_catch_up_mode();
extern Object decode_gensym_time();
extern Object encode_gensym_time();
extern Object encode_unix_time_after_failure();
extern Object g2_time_clock_discontinuity();
extern Object generate_float_vector();
extern Object gensym_decode_unix_time();
extern Object get_real_gensym_time();
extern Object initialize_gensym_time();
extern Object milliseconds_to_next_task();
extern Object minimum_scheduling_interval_function();
extern Object partition_managed_float();
extern Object preset_gensym_time_for_initialization();
extern Object real_time_clock_discontinuity();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object record_system_variable();
extern Object same_gensym_date_p();
extern Object scheduler_mode_function();
extern Object tick_the_clock_for_tw_or_gsi();
extern Object tick_the_g2_fast_time_clock();
extern Object tick_the_g2_real_time_clock();
extern Object tick_the_g2_simulated_time_clock();
extern Object tick_the_nupec_catch_up_clock();
extern Object tick_the_real_time_clock();
extern Object unpack_future_tasks_into_current_task_queues();
extern Object update_g2_time_to_tick_after_scheduling_change();
extern Object update_trend_charts_for_clock_discontinuity();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_real_time, Qcurrent_real_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_time_of_last_g2_tick, Qfixnum_time_of_last_g2_tick);
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_time_of_last_real_time_tick, Qfixnum_time_of_last_real_time_tick);
extern Object Fixnum_time_units_per_second;
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_time_until_g2_time_tick, Qfixnum_time_until_g2_time_tick);
#define Fixnum_time_until_real_time_tick FIX((SI_Long)1L)
DECLARE_VARIABLE_WITH_SYMBOL(Force_clock_tick, Qforce_clock_tick);
extern Object Future_g2_time_tasks;
extern Object Future_real_time_tasks;
DECLARE_VARIABLE_WITH_SYMBOL(G2_time_at_start, Qg2_time_at_start);
DECLARE_VARIABLE_WITH_SYMBOL(G2_time_at_start_as_text_string, Qg2_time_at_start_as_text_string);
DECLARE_VARIABLE_WITH_SYMBOL(G2_time_to_tick_p_base, Qg2_time_to_tick_p_base);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_base_time_as_managed_float, Qgensym_base_time_as_managed_float);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_time, Qgensym_time);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_time_at_start, Qgensym_time_at_start);
extern Object Global_daylight_saving_time_adjustment;
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_non_real_time_clock_ticks_qm, Qinhibit_non_real_time_clock_ticks_qm);
#define Most_negative_fixnum32 FIX((SI_Long)-536870912L)
extern Object Most_negative_fixnum_as_float;
extern Object Most_positive_fixnum_as_float;
DECLARE_VARIABLE_WITH_SYMBOL(Most_recent_g2_time, Qmost_recent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Nupec_catch_up_mode_caught_up_qm, Qnupec_catch_up_mode_caught_up_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Real_time_of_last_g2_tick, Qreal_time_of_last_g2_tick);
DECLARE_VARIABLE_WITH_SYMBOL(Real_time_to_tick_p_base, Qreal_time_to_tick_p_base);
extern Object Seconds_from_1900_to_1970;
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
extern Object Some_time_ago;
DECLARE_VARIABLE_WITH_SYMBOL(System_has_paused, Qsystem_has_paused);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(Timing_parameters, Qtiming_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Warmboot_current_time, Qwarmboot_current_time);
DECLARE_VARIABLE_WITH_SYMBOL(Warmboot_simulated_time, Qwarmboot_simulated_time);
DECLARE_VARIABLE_WITH_SYMBOL(Warmbooting_qm, Qwarmbooting_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Warmbooting_with_catch_up_qm, Qwarmbooting_with_catch_up_qm);
