/* ntwrks.h -- Header File for ntwrks.c
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

extern Object c_get_connection_pathname(Object,Object,Object);
extern Object c_get_network_listener(Object,Object,Object);
extern Object c_network_connect(Object,Object,Object,Object);
extern Object c_set_connection_pathname(Object,Object);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object get_nth_network_address(Object,Object,Object);
extern Object gethostname_1(Object,Object);
extern Object network_connect(int,...);
extern Object reclaim_gensym_string(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object set_up_secure_icp(int,...);

#else

extern Object c_get_connection_pathname();
extern Object c_get_network_listener();
extern Object c_network_connect();
extern Object c_set_connection_pathname();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object get_nth_network_address();
extern Object gethostname_1();
extern Object network_connect();
extern Object reclaim_gensym_string();
extern Object record_system_variable();
extern Object set_up_secure_icp();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_time_units_of_sleep_this_clock_tick, Qfixnum_time_units_of_sleep_this_clock_tick);
DECLARE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Record_fixnum_time_units_of_sleep_this_clock_tick_qm, Qrecord_fixnum_time_units_of_sleep_this_clock_tick_qm);
extern Object Secure_icp_default_p;
extern Object Secure_icp_initialized_p;
