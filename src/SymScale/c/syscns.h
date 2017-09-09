/* syscns.h -- Header File for syscns.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qminus;
extern Object Qerror;
extern Object Qtan;
extern Object Qunsigned_byte;

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

extern Object create_icon_description(int,...);
extern Object override_icon_description_for_system_defined_class(int,...);

#else

extern Object create_icon_description();
extern Object override_icon_description_for_system_defined_class();

#endif

/* variables/constants */
