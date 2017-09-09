/* ntwrks.h -- Header File for ntwrks.c
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

extern Object g2int_c_get_connection_pathname(Object,Object,Object);
extern Object g2int_c_get_network_listener(Object,Object,Object);
extern Object g2int_c_network_connect(Object,Object,Object,Object);
extern Object g2int_c_set_connection_pathname(Object,Object);
extern Object g2int_copy_foreign_string_arg_if_appropriate(Object);
extern Object g2int_get_nth_network_address(Object,Object,Object);
extern Object g2int_gethostname_1(Object,Object);
extern Object g2int_network_connect(int,...);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_set_up_secure_icp(int,...);

#else

extern Object g2int_c_get_connection_pathname();
extern Object g2int_c_get_network_listener();
extern Object g2int_c_network_connect();
extern Object g2int_c_set_connection_pathname();
extern Object g2int_copy_foreign_string_arg_if_appropriate();
extern Object g2int_get_nth_network_address();
extern Object g2int_gethostname_1();
extern Object g2int_network_connect();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_record_system_variable();
extern Object g2int_set_up_secure_icp();

#endif

/* variables/constants */
extern Object G2int_fixnum_time_units_of_sleep_this_clock_tick;
extern Object G2int_profiling_enabledqm;
extern Object G2int_record_fixnum_time_units_of_sleep_this_clock_tickqm;
extern Object G2int_secure_icp_default_p;
extern Object G2int_secure_icp_initialized_p;
