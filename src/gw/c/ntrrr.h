/* ntrrr.h -- Header File for ntrrr.c
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

extern Object g2int_direct_structure_method(Object,Object);
extern Object g2int_load_and_initialize_type_description(Object,Object);
extern Object g2int_make_error_code_1(Object,Object);
extern Object g2int_make_permanent_error_code_structure_internal(void);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_reclaim_error_code_1(Object);
extern Object g2int_record_direct_structure_method(Object,Object,Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_regenerate_optimized_constant(Object);

#else

extern Object g2int_direct_structure_method();
extern Object g2int_load_and_initialize_type_description();
extern Object g2int_make_error_code_1();
extern Object g2int_make_permanent_error_code_structure_internal();
extern Object g2int_mutate_global_property();
extern Object g2int_reclaim_error_code_1();
extern Object g2int_record_direct_structure_method();
extern Object g2int_record_system_variable();
extern Object g2int_regenerate_optimized_constant();

#endif

/* variables/constants */
extern Object G2int_chain_of_available_error_codes;
extern Object G2int_error_code_count;
extern Object G2int_error_severity_fatal;
extern Object G2int_error_severity_informational;
extern Object G2int_error_severity_success;
extern Object G2int_error_severity_warning;
extern Object G2int_the_type_description_of_error_code;
