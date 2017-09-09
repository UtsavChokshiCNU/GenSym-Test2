/* schdle.h -- Header File for schdle.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qmost_positive_fixnum;
extern Object Qvector;

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

extern Object g2int_abort(int,...);
extern Object g2int_adjust_task_times_after_clock_discontinuity(Object,Object);
extern Object g2int_allocate_managed_float_box(void);
extern Object g2int_allocate_managed_simple_float_array(Object);
extern Object g2int_allocated_named_gensym_structure_p(Object);
extern Object g2int_c_native_clock_ticks_or_cache(Object,Object);
extern Object g2int_cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object g2int_cancel_g2_running_tasks(void);
extern Object g2int_clear_g2_schedule(void);
extern Object g2int_clear_optimized_constants(void);
extern Object g2int_current_g2_run_state(void);
extern Object g2int_defer_current_g2_running_tasks(void);
extern Object g2int_delete_future_task_queue_for_task(Object);
extern Object g2int_dequeue_and_execute_next_task(void);
extern Object g2int_dequeue_next_task(void);
extern Object g2int_direct_structure_method(Object,Object);
extern Object g2int_enqueue_scheduler_events_if_necessary(Object);
extern Object g2int_execute_task_and_reschedule(Object);
extern Object g2int_execute_task_out_of_order_1(Object);
extern Object g2int_future_task_schedule_2(Object);
extern Object g2int_g2_event_ready_p(void);
extern Object g2int_get_or_create_future_task_queue_for_task(Object);
extern Object g2int_get_pending_network_events(void);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_initialize_scheduler(void);
extern Object g2int_load_and_initialize_type_description(Object,Object);
extern Object g2int_make_empty_constant_queue(void);
extern Object g2int_make_future_task_queue_holder_1_1(void);
extern Object g2int_make_permanent_future_task_queue_holder_structure_internal(void);
extern Object g2int_make_permanent_queue_element_structure_internal(void);
extern Object g2int_make_permanent_schedule_task_structure_internal(void);
extern Object g2int_make_schedule_task_1(Object);
extern Object g2int_milliseconds_to_next_scheduler_event(void);
extern Object g2int_milliseconds_to_next_task(void);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_next_scheduled_task_for_function(Object,Object);
extern Object g2int_note_scheduling_task_1(Object,Object);
extern Object g2int_print_schedule_task(Object,Object,Object);
extern Object g2int_push_optimized_constant(Object);
extern Object g2int_reclaim_constant_queue(Object);
extern Object g2int_reclaim_future_task_queue_holder(Object);
extern Object g2int_reclaim_future_task_queue_holder_1_1(Object);
extern Object g2int_reclaim_schedule_task_1(Object);
extern Object g2int_reclaim_schedule_task_args(Object);
extern Object g2int_record_direct_structure_method(Object,Object,Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_regenerate_optimized_constant(Object);
extern Object g2int_requeue_deferred_running_tasks(void);
extern Object g2int_scheduler_time_lag(Object);
extern Object g2int_tasks_deferred_until_resumptionqm(void);
extern Object g2int_tasks_enqueued_for_current_executionqm(void);
extern Object g2int_tformat(int,...);
extern Object g2int_tick_the_clock_for_tw_or_gsi(void);
extern Object g2int_time_slice_expired_p(void);
extern Object g2int_time_slice_expired_p_given_time(Object);
extern Object g2int_twrite_schedule_task_header(void);
extern Object g2int_type_name_of_named_simple_vector(Object);
extern Object g2int_unpack_future_tasks_into_current_task_queues(Object);

#else

extern Object g2int_abort();
extern Object g2int_adjust_task_times_after_clock_discontinuity();
extern Object g2int_allocate_managed_float_box();
extern Object g2int_allocate_managed_simple_float_array();
extern Object g2int_allocated_named_gensym_structure_p();
extern Object g2int_c_native_clock_ticks_or_cache();
extern Object g2int_cancel_and_reclaim_scheduled_queue_element_1();
extern Object g2int_cancel_g2_running_tasks();
extern Object g2int_clear_g2_schedule();
extern Object g2int_clear_optimized_constants();
extern Object g2int_current_g2_run_state();
extern Object g2int_defer_current_g2_running_tasks();
extern Object g2int_delete_future_task_queue_for_task();
extern Object g2int_dequeue_and_execute_next_task();
extern Object g2int_dequeue_next_task();
extern Object g2int_direct_structure_method();
extern Object g2int_enqueue_scheduler_events_if_necessary();
extern Object g2int_execute_task_and_reschedule();
extern Object g2int_execute_task_out_of_order_1();
extern Object g2int_future_task_schedule_2();
extern Object g2int_g2_event_ready_p();
extern Object g2int_get_or_create_future_task_queue_for_task();
extern Object g2int_get_pending_network_events();
extern Object g2int_getfq_function_no_default();
extern Object g2int_initialize_scheduler();
extern Object g2int_load_and_initialize_type_description();
extern Object g2int_make_empty_constant_queue();
extern Object g2int_make_future_task_queue_holder_1_1();
extern Object g2int_make_permanent_future_task_queue_holder_structure_internal();
extern Object g2int_make_permanent_queue_element_structure_internal();
extern Object g2int_make_permanent_schedule_task_structure_internal();
extern Object g2int_make_schedule_task_1();
extern Object g2int_milliseconds_to_next_scheduler_event();
extern Object g2int_milliseconds_to_next_task();
extern Object g2int_mutate_global_property();
extern Object g2int_next_scheduled_task_for_function();
extern Object g2int_note_scheduling_task_1();
extern Object g2int_print_schedule_task();
extern Object g2int_push_optimized_constant();
extern Object g2int_reclaim_constant_queue();
extern Object g2int_reclaim_future_task_queue_holder();
extern Object g2int_reclaim_future_task_queue_holder_1_1();
extern Object g2int_reclaim_schedule_task_1();
extern Object g2int_reclaim_schedule_task_args();
extern Object g2int_record_direct_structure_method();
extern Object g2int_record_system_variable();
extern Object g2int_regenerate_optimized_constant();
extern Object g2int_requeue_deferred_running_tasks();
extern Object g2int_scheduler_time_lag();
extern Object g2int_tasks_deferred_until_resumptionqm();
extern Object g2int_tasks_enqueued_for_current_executionqm();
extern Object g2int_tformat();
extern Object g2int_tick_the_clock_for_tw_or_gsi();
extern Object g2int_time_slice_expired_p();
extern Object g2int_time_slice_expired_p_given_time();
extern Object g2int_twrite_schedule_task_header();
extern Object g2int_type_name_of_named_simple_vector();
extern Object g2int_unpack_future_tasks_into_current_task_queues();

#endif

/* variables/constants */
extern Object G2int_available_gensym_conses;
extern Object G2int_backtrace_stack_for_internal_error;
extern Object G2int_chain_of_available_future_task_queue_holders;
extern Object G2int_chain_of_available_queue_elements;
extern Object G2int_chain_of_available_schedule_tasks;
extern Object G2int_current_g2_time;
extern Object G2int_current_real_time;
extern Object G2int_current_schedule_task;
extern Object G2int_current_system_name;
extern Object G2int_current_task_queue_vector;
extern Object G2int_deferred_task_queue_vector;
extern Object G2int_future_g2_time_tasks;
extern Object G2int_future_real_time_tasks;
extern Object G2int_future_task_queue_holder_count;
extern Object G2int_future_task_queue_marker;
extern Object G2int_gsi_maximum_idle_interval;
#define G2int_higher_than_any_priority FIX((SI_Long)-1L)
#define G2int_highest_system_priority FIX((SI_Long)0L)
#define G2int_highest_user_priority FIX((SI_Long)1L)
#define G2int_how_many_prioritiesqm FIX((SI_Long)10L)
extern Object G2int_immediate_task_queue;
extern Object G2int_index_of_top_of_backtrace_stack;
#define G2int_lower_than_any_priority FIX((SI_Long)12L)
#define G2int_lowest_system_priority FIX((SI_Long)11L)
extern Object G2int_maximum_index_in_backtrace_stack_for_internal_error;
extern Object G2int_maximum_time_slice_size;
extern Object G2int_priority_of_current_task;
extern Object G2int_priority_of_next_task;
#define G2int_schedule_task_arg_limit FIX((SI_Long)4L)

/* slot offset for SCHEDULE-TASK-ARG-1 in structure SCHEDULE-TASK */
#define G2int_schedule_task_arg_offset FIX((SI_Long)11L)
extern Object G2int_schedule_task_count;
extern Object G2int_scheduler_has_been_initialized_p;
#define G2int_size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object G2int_structure_being_reclaimed;
extern Object G2int_system_has_aborted;
extern Object G2int_system_has_paused;
extern Object G2int_system_is_running;
extern Object G2int_the_g2_defstruct_package;
extern Object G2int_the_type_description_of_future_task_queue_holder;
extern Object G2int_the_type_description_of_schedule_task;
extern Object G2int_time_slice_start_time;
extern Object G2int_time_to_check_network_events;
