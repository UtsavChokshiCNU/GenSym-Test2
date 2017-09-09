/* systm.h -- Header File for systm.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qnot;

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

extern Object g2int_declare_system_1(int,...);
extern Object g2int_launch_g2_image(void);
extern Object g2int_launch_system(Object);
extern Object g2int_launch_telewindows_image(void);
extern Object g2int_set_system_version(Object,Object);

#else

extern Object g2int_declare_system_1();
extern Object g2int_launch_g2_image();
extern Object g2int_launch_system();
extern Object g2int_launch_telewindows_image();
extern Object g2int_set_system_version();

#endif

/* variables/constants */
extern Object G2int_all_systems;
extern Object G2int_bootstrap_information;
extern Object G2int_development_world_save_p;
