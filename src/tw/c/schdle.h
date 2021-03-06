/* schdle.h -- Header File for schdle.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qmost_positive_fixnum;
extern Object Qunsigned_byte;
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

extern Object adjust_task_times_after_clock_discontinuity(Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_managed_float_box(void);
extern Object allocate_managed_simple_float_array(Object);
extern Object allocated_named_gensym_structure_p(Object);
extern Object bytes_per_simple_vector(Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object cancel_g2_running_tasks(void);
extern Object clear_g2_schedule(void);
extern Object clear_optimized_constants(void);
extern Object copy_out_current_wide_string(void);
extern Object current_g2_run_state(void);
extern Object defer_current_g2_running_tasks(void);
extern Object delete_future_task_queue_for_task(Object);
extern Object dequeue_and_execute_next_task(void);
extern Object dequeue_next_task(void);
extern Object direct_structure_method(Object,Object);
extern Object enqueue_scheduler_events_if_necessary(Object);
extern Object execute_task_and_reschedule(Object);
extern Object execute_task_out_of_order_1(Object);
extern Object extend_current_gensym_string(int,...);
extern Object future_task_queue_holder_structure_memory_usage(void);
extern Object future_task_schedule_2(Object);
extern Object g2_event_ready_p(void);
extern Object gensym_cons_1(Object,Object);
extern Object get_name_for_function(Object);
extern Object get_or_create_future_task_queue_for_task(Object);
extern Object get_pending_network_events(void);
extern Object getfq_function_no_default(Object,Object);
extern Object initialize_scheduler(void);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_empty_constant_queue(void);
extern Object make_future_task_queue_holder_1_1(void);
extern Object make_gensym_list_1(Object);
extern Object make_permanent_future_task_queue_holder_structure_internal(void);
extern Object make_permanent_queue_element_structure_internal(void);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_schedule_task_1(Object);
extern Object milliseconds_to_next_scheduler_event(void);
extern Object milliseconds_to_next_task(void);
extern Object mutate_global_property(Object,Object,Object);
extern Object next_scheduled_task_for_function(Object,Object);
extern Object note_scheduling_task_1(Object,Object);
extern Object outstanding_future_task_queue_holder_count(void);
extern Object outstanding_schedule_task_count(void);
extern Object print_random_object_prefix(Object,Object);
extern Object print_random_object_suffix(Object,Object);
extern Object print_schedule_task(Object,Object,Object);
extern Object print_schedule_to_string_list(Object);
extern Object push_optimized_constant(Object);
extern Object reclaim_constant_queue(Object);
extern Object reclaim_future_task_queue_holder(Object);
extern Object reclaim_future_task_queue_holder_1_1(Object);
extern Object reclaim_schedule_task_1(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_simple_gensym_string(Object);
extern Object reclaim_text_string(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object requeue_deferred_running_tasks(void);
extern Object schedule_task_structure_memory_usage(void);
extern Object scheduler_time_lag(Object);
extern Object task_queue_descriptions(Object);
extern Object tasks_deferred_until_resumption_qm(void);
extern Object tasks_enqueued_for_current_execution_qm(void);
extern Object text_string_length(Object);
extern Object tformat(int,...);
extern Object tick_the_clock_for_tw_or_gsi(void);
extern Object time_slice_expired_p(void);
extern Object time_slice_expired_p_given_time(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_debug_computation_instance_or_object(Object);
extern Object twrite_debug_object(Object);
extern Object twrite_general_string(Object);
extern Object twrite_schedule_task(Object);
extern Object twrite_schedule_task_header(void);
extern Object twrite_wide_character(Object);
extern Object type_name_of_named_simple_vector(Object);
extern Object unpack_future_tasks_into_current_task_queues(Object);
extern Object update_object_pool_meters_list(Object);
extern Object write_floating_point_number(int,...);

#else

extern Object adjust_task_times_after_clock_discontinuity();
extern Object allocate_byte_vector_16();
extern Object allocate_managed_float_box();
extern Object allocate_managed_simple_float_array();
extern Object allocated_named_gensym_structure_p();
extern Object bytes_per_simple_vector();
extern Object c_native_clock_ticks_or_cache();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object cancel_g2_running_tasks();
extern Object clear_g2_schedule();
extern Object clear_optimized_constants();
extern Object copy_out_current_wide_string();
extern Object current_g2_run_state();
extern Object defer_current_g2_running_tasks();
extern Object delete_future_task_queue_for_task();
extern Object dequeue_and_execute_next_task();
extern Object dequeue_next_task();
extern Object direct_structure_method();
extern Object enqueue_scheduler_events_if_necessary();
extern Object execute_task_and_reschedule();
extern Object execute_task_out_of_order_1();
extern Object extend_current_gensym_string();
extern Object future_task_queue_holder_structure_memory_usage();
extern Object future_task_schedule_2();
extern Object g2_event_ready_p();
extern Object gensym_cons_1();
extern Object get_name_for_function();
extern Object get_or_create_future_task_queue_for_task();
extern Object get_pending_network_events();
extern Object getfq_function_no_default();
extern Object initialize_scheduler();
extern Object load_and_initialize_type_description();
extern Object make_empty_constant_queue();
extern Object make_future_task_queue_holder_1_1();
extern Object make_gensym_list_1();
extern Object make_permanent_future_task_queue_holder_structure_internal();
extern Object make_permanent_queue_element_structure_internal();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_schedule_task_1();
extern Object milliseconds_to_next_scheduler_event();
extern Object milliseconds_to_next_task();
extern Object mutate_global_property();
extern Object next_scheduled_task_for_function();
extern Object note_scheduling_task_1();
extern Object outstanding_future_task_queue_holder_count();
extern Object outstanding_schedule_task_count();
extern Object print_random_object_prefix();
extern Object print_random_object_suffix();
extern Object print_schedule_task();
extern Object print_schedule_to_string_list();
extern Object push_optimized_constant();
extern Object reclaim_constant_queue();
extern Object reclaim_future_task_queue_holder();
extern Object reclaim_future_task_queue_holder_1_1();
extern Object reclaim_schedule_task_1();
extern Object reclaim_schedule_task_args();
extern Object reclaim_simple_gensym_string();
extern Object reclaim_text_string();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object requeue_deferred_running_tasks();
extern Object schedule_task_structure_memory_usage();
extern Object scheduler_time_lag();
extern Object task_queue_descriptions();
extern Object tasks_deferred_until_resumption_qm();
extern Object tasks_enqueued_for_current_execution_qm();
extern Object text_string_length();
extern Object tformat();
extern Object tick_the_clock_for_tw_or_gsi();
extern Object time_slice_expired_p();
extern Object time_slice_expired_p_given_time();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_debug_computation_instance_or_object();
extern Object twrite_debug_object();
extern Object twrite_general_string();
extern Object twrite_schedule_task();
extern Object twrite_schedule_task_header();
extern Object twrite_wide_character();
extern Object type_name_of_named_simple_vector();
extern Object unpack_future_tasks_into_current_task_queues();
extern Object update_object_pool_meters_list();
extern Object write_floating_point_number();

#endif

/* variables/constants */
extern Object Available_gensym_conses;
extern Object Backtrace_stack_for_internal_error;
extern Object Chain_of_available_future_task_queue_holders;
extern Object Chain_of_available_queue_elements;
extern Object Chain_of_available_schedule_tasks;
extern Object Current_g2_time;
extern Object Current_gensym_string;
extern Object Current_real_time;
extern Object Current_schedule_task;
extern Object Current_system_name;
extern Object Current_task_queue_vector;
extern Object Current_twriting_output_type;
extern Object Current_wide_string;
extern Object Current_wide_string_list;
extern Object Deferred_task_queue_vector;
extern Object Fill_pointer_for_current_gensym_string;
extern Object Fill_pointer_for_current_wide_string;
extern Object Future_g2_time_tasks;
extern Object Future_real_time_tasks;
extern Object Future_task_queue_holder_count;
extern Object Future_task_queue_marker;
extern Object Gensym_base_time_as_managed_float;
extern Object Gensym_time;
extern Object Gsi_maximum_idle_interval;
#define Higher_than_any_priority FIX((SI_Long)-1L)
#define Highest_system_priority FIX((SI_Long)0L)
#define Highest_user_priority FIX((SI_Long)1L)
#define How_many_priorities_qm FIX((SI_Long)10L)
extern Object Immediate_task_queue;
extern Object Index_of_top_of_backtrace_stack;
#define Lower_than_any_priority FIX((SI_Long)12L)
#define Lowest_system_priority FIX((SI_Long)11L)
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
extern Object Maximum_time_slice_size;
extern Object Priority_of_current_task;
extern Object Priority_of_next_task;
#define Schedule_task_arg_limit FIX((SI_Long)4L)

/* slot offset for SCHEDULE-TASK-ARG-1 in structure SCHEDULE-TASK */
#define Schedule_task_arg_offset FIX((SI_Long)11L)
extern Object Schedule_task_count;
extern Object Scheduler_has_been_initialized_p;
extern Object Seconds_from_1900_to_1970;
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object Structure_being_reclaimed;
extern Object System_has_aborted;
extern Object System_has_paused;
extern Object System_is_running;
extern Object The_g2_defstruct_package;
extern Object The_type_description_of_future_task_queue_holder;
extern Object The_type_description_of_schedule_task;
extern Object Time_slice_start_time;
extern Object Time_to_check_network_events;
extern Object Total_length_of_current_gensym_string;
extern Object Total_length_of_current_wide_string;
