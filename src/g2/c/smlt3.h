/* smlt3.h -- Header File for smlt3.c
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

extern Object copy_text_string(Object);
extern Object evaluate_designation(Object,Object);
extern Object post_simulation_warning_for_no_value(Object);
extern Object sim_eval_get_value_of_parameter(Object);
extern Object sim_eval_get_value_of_variable(Object);
extern Object sim_eval_variable_for_designation(Object,Object);
extern Object text_string_p(Object);

#else

extern Object copy_text_string();
extern Object evaluate_designation();
extern Object post_simulation_warning_for_no_value();
extern Object sim_eval_get_value_of_parameter();
extern Object sim_eval_get_value_of_variable();
extern Object sim_eval_variable_for_designation();
extern Object text_string_p();

#endif

/* variables/constants */
extern Object Parameter_class_description;
extern Object Simulation_no_value;
extern Object Variable_class_description;
