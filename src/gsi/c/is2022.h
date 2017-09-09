/* is2022.h -- Header File for is2022.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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

extern Object g2int_equalw(Object,Object);
extern Object g2int_length_of_wide_string_greater_p(Object,Object);
extern Object g2int_sort_list(Object,Object,Object);
extern Object g2int_stringw(Object);

#else

extern Object g2int_equalw();
extern Object g2int_length_of_wide_string_greater_p();
extern Object g2int_sort_list();
extern Object g2int_stringw();

#endif

/* variables/constants */
extern Object G2int_all_supported_2022_escape_sequences;
