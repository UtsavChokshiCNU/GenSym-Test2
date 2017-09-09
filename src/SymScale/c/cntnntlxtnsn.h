/* cntnntlxtnsn.h -- Header File for cntnntlxtnsn.c
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

extern Object kb_g2nke_historical_mean(Object,Object,Object);
extern Object kb_g2nke_historical_variance(Object,Object,Object);
extern Object make_evaluation_quantity(Object);
extern Object mutate_global_property(Object,Object,Object);

#else

extern Object kb_g2nke_historical_mean();
extern Object kb_g2nke_historical_variance();
extern Object make_evaluation_quantity();
extern Object mutate_global_property();

#endif

/* variables/constants */
