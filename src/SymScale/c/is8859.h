/* is8859.h -- Header File for is8859.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qeq;

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

extern Object direct_structure_method(Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object make_8859_reverse_unicode_map(void);
extern Object make_reverse_8859_unicode_map(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object set_balanced_binary_tree_entry(Object,Object,Object,Object,Object,Object,Object);
extern Object sxhashw(Object);

#else

extern Object direct_structure_method();
extern Object getfq_function_no_default();
extern Object make_8859_reverse_unicode_map();
extern Object make_reverse_8859_unicode_map();
extern Object record_direct_structure_method();
extern Object regenerate_optimized_constant();
extern Object set_balanced_binary_tree_entry();
extern Object sxhashw();

#endif

/* variables/constants */
extern Object N_8859_2_unicode_map;
extern Object N_8859_3_unicode_map;
extern Object N_8859_4_unicode_map;
extern Object N_8859_6_unicode_map;
extern Object N_8859_7_unicode_map;
extern Object N_8859_8_unicode_map;
#define N_8859_code_mask FIX((SI_Long)127L)
#define N_8859_part_size FIX((SI_Long)128L)
