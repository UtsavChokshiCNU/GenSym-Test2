/* is2022.h -- Header File for is2022.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcar;
extern Object Ktest;

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

extern Object equalw(Object,Object);
extern Object length_of_wide_string_greater_p(Object,Object);
extern Object sort_list(Object,Object,Object);
extern Object stringw(Object);

#else

extern Object equalw();
extern Object length_of_wide_string_greater_p();
extern Object sort_list();
extern Object stringw();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(All_supported_2022_escape_sequences, Qall_supported_2022_escape_sequences);
