/* load.h -- Header File for load.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qload_pathname;
extern Object Qarray;
extern Object Qfloat;
extern Object Qinteger;
extern Object Qlist;
extern Object Knicknames;
extern Object Qsymbol;
extern Object Kuse;

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

extern Object g2int_use_dates_instead_of_versions_p(void);

#else

extern Object g2int_use_dates_instead_of_versions_p();

#endif

/* variables/constants */
extern Object G2int_ab_system_pathname;
extern Object G2int_bootstrap_information;
extern Object G2int_default_sandbox_location;
extern Object G2int_default_sandbox_name;
extern Object G2int_default_spin_id;
extern Object G2int_dest_directory_name;
extern Object G2int_file_naming_specific_dest_directory;
extern Object G2int_file_naming_specific_source_directory;
extern Object G2int_file_naming_spin_id;
extern Object G2int_file_naming_tools_directory;
extern Object G2int_lisp_memory_expandedqm;
extern Object G2int_list_for_import;
extern Object G2int_source_directory_name;
extern Object G2int_starfasl_extensionstar;
extern Object G2int_toolsdir_name;
extern Object G2int_user_package_in_this_lisp;
extern Object ab_G2int_dummy_var;
