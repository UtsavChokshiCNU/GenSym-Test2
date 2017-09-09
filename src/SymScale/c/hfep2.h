/* hfep2.h -- Header File for hfep2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Kinitial_contents;

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

extern Object allocate_byte_vector_16(Object);
extern Object bytes_per_simple_vector(Object);
extern Object clear_optimized_constants(void);
extern Object copy_out_current_wide_string(void);
extern Object direct_structure_method(Object,Object);
extern Object hfep_chgroup(Object);
extern Object hfep_hanc_type_structure_memory_usage(void);
extern Object hfep_into_hanc(Object);
extern Object hfep_intoksc2c(Object,Object,Object,Object);
extern Object hfep_intoksc2s(Object);
extern Object hfep_mixconso(Object,Object);
extern Object hfep_mixvowel(Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_hfep_hanc_type_1(void);
extern Object make_hfep_hanc_type_function(void);
extern Object make_permanent_hfep_hanc_type_structure_internal(void);
extern Object make_thread_array(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_hfep_hanc_type_count(void);
extern Object push_optimized_constant(Object);
extern Object reclaim_hfep_hanc_type_1(Object);
extern Object reclaim_hfep_hanc_type_function(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object reset_hfep_hanc_type_instance(Object);
extern Object run_hfep_automaton(Object);
extern Object shift_hfep_cchar_to_nchar_and_reset_cchar(void);
extern Object tformat(int,...);
extern Object update_object_pool_meters_list(Object);

#else

extern Object allocate_byte_vector_16();
extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object copy_out_current_wide_string();
extern Object direct_structure_method();
extern Object hfep_chgroup();
extern Object hfep_hanc_type_structure_memory_usage();
extern Object hfep_into_hanc();
extern Object hfep_intoksc2c();
extern Object hfep_intoksc2s();
extern Object hfep_mixconso();
extern Object hfep_mixvowel();
extern Object load_and_initialize_type_description();
extern Object make_hfep_hanc_type_1();
extern Object make_hfep_hanc_type_function();
extern Object make_permanent_hfep_hanc_type_structure_internal();
extern Object make_thread_array();
extern Object mutate_global_property();
extern Object outstanding_hfep_hanc_type_count();
extern Object push_optimized_constant();
extern Object reclaim_hfep_hanc_type_1();
extern Object reclaim_hfep_hanc_type_function();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object reset_hfep_hanc_type_instance();
extern Object run_hfep_automaton();
extern Object shift_hfep_cchar_to_nchar_and_reset_cchar();
extern Object tformat();
extern Object update_object_pool_meters_list();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_hfep_hanc_types, Qchain_of_available_hfep_hanc_types);
extern Object Chain_of_available_hfep_hanc_types_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_hfep_c_act, Qcurrent_hfep_c_act);
DECLARE_VARIABLE_WITH_SYMBOL(Current_hfep_c_state, Qcurrent_hfep_c_state);
DECLARE_VARIABLE_WITH_SYMBOL(Current_hfep_cchar, Qcurrent_hfep_cchar);
DECLARE_VARIABLE_WITH_SYMBOL(Current_hfep_nchar, Qcurrent_hfep_nchar);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
#define Hfep_a FIX((SI_Long)107L)
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_action, Qhfep_action);
#define Hfep_ai FIX((SI_Long)111L)
#define Hfep_b FIX((SI_Long)113L)
#define Hfep_b_s FIX((SI_Long)67L)
#define Hfep_bb FIX((SI_Long)81L)
#define Hfep_c FIX((SI_Long)99L)
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_cho_ksc2c, Qhfep_cho_ksc2c);
#define Hfep_d FIX((SI_Long)101L)
#define Hfep_dd FIX((SI_Long)69L)
#define Hfep_done FIX((SI_Long)2L)
#define Hfep_e FIX((SI_Long)112L)
#define Hfep_eo FIX((SI_Long)106L)
#define Hfep_eoln FIX((SI_Long)10L)
#define Hfep_error FIX((SI_Long)4L)
#define Hfep_esc FIX((SI_Long)27L)
#define Hfep_eu FIX((SI_Long)109L)
#define Hfep_eu_i FIX((SI_Long)77L)
#define Hfep_g FIX((SI_Long)114L)
#define Hfep_g_s FIX((SI_Long)83L)
#define Hfep_gg FIX((SI_Long)82L)
#define Hfep_go_on FIX((SI_Long)1L)
#define Hfep_h FIX((SI_Long)103L)
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_hanc_type_count, Qhfep_hanc_type_count);
#define Hfep_i FIX((SI_Long)108L)
#define Hfep_j FIX((SI_Long)119L)
#define Hfep_jj FIX((SI_Long)87L)
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_jong_ksc2c, Qhfep_jong_ksc2c);
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_jung_ksc2c, Qhfep_jung_ksc2c);
#define Hfep_k FIX((SI_Long)122L)
#define Hfep_ks_size FIX((SI_Long)2390L)
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_ksc2cs, Qhfep_ksc2cs);
#define Hfep_m FIX((SI_Long)97L)
#define Hfep_n FIX((SI_Long)115L)
#define Hfep_n_h FIX((SI_Long)72L)
#define Hfep_n_j FIX((SI_Long)74L)
#define Hfep_none FIX((SI_Long)0L)
#define Hfep_null FIX((SI_Long)0L)
#define Hfep_null_code FIX((SI_Long)0L)
#define Hfep_o FIX((SI_Long)104L)
#define Hfep_o_a FIX((SI_Long)75L)
#define Hfep_o_ai FIX((SI_Long)72L)
#define Hfep_o_i FIX((SI_Long)76L)
#define Hfep_oo FIX((SI_Long)100L)
#define Hfep_p FIX((SI_Long)118L)
#define Hfep_r FIX((SI_Long)102L)
#define Hfep_r_b FIX((SI_Long)65L)
#define Hfep_r_g FIX((SI_Long)71L)
#define Hfep_r_h FIX((SI_Long)70L)
#define Hfep_r_m FIX((SI_Long)77L)
#define Hfep_r_p FIX((SI_Long)86L)
#define Hfep_r_s FIX((SI_Long)78L)
#define Hfep_r_t FIX((SI_Long)66L)
#define Hfep_s FIX((SI_Long)116L)
#define Hfep_spc FIX((SI_Long)32L)
#define Hfep_ss FIX((SI_Long)84L)
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_state, Qhfep_state);
#define Hfep_t FIX((SI_Long)120L)
#define Hfep_u FIX((SI_Long)110L)
#define Hfep_u_e FIX((SI_Long)78L)
#define Hfep_u_eo FIX((SI_Long)74L)
#define Hfep_u_i FIX((SI_Long)66L)
#define Hfep_wrong FIX((SI_Long)3L)
#define Hfep_ya FIX((SI_Long)105L)
#define Hfep_yai FIX((SI_Long)79L)
#define Hfep_ye FIX((SI_Long)80L)
#define Hfep_yeo FIX((SI_Long)117L)
#define Hfep_yo FIX((SI_Long)121L)
#define Hfep_yu FIX((SI_Long)98L)
extern Object The_type_description_of_hfep_hanc_type;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
