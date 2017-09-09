/* btstrp.h -- Header File for btstrp.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qand;
extern Object Qnot;
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

extern Object g2int_add_to_directory_list_for_bootstrapping(Object,Object);
extern Object g2int_declare_system_1(int,...);
extern Object g2int_directory_for_bootstrap(Object);
extern Object g2int_eval_feature(Object);
extern Object g2int_gensym(int,...);
extern Object g2int_get_binary_file_type(Object,Object,Object);
extern Object g2int_get_default_binary_file_type(Object,Object,Object);
extern Object g2int_get_default_binary_pathname_name(Object,Object,Object);
extern Object g2int_get_default_include_test(Object,Object,Object,Object);
extern Object g2int_get_default_local_directory_namestring(Object,Object,Object);
extern Object g2int_get_default_local_file_type(Object,Object,Object);
extern Object g2int_get_default_local_pathname_name(Object,Object,Object);
extern Object g2int_get_default_master_directory_namestring(Object,Object,Object);
extern Object g2int_get_default_master_file_type(Object,Object,Object);
extern Object g2int_get_default_master_pathname_name(Object,Object,Object);
extern Object g2int_get_file_property(Object,Object,Object,Object);
extern Object g2int_get_local_file_type(Object,Object,Object);
extern Object g2int_get_system_major_version(Object);
extern Object g2int_get_system_minor_version(Object);
extern Object g2int_install_all_file_properties_from_alist(Object,Object,Object,Object);
extern Object g2int_install_all_file_properties_from_plist(Object,Object,Object,Object);
extern Object g2int_install_file_properties_for_file_name_or_description(Object,Object,Object,Object);
extern Object g2int_install_file_properties_for_system(Object,Object,Object,Object);
extern Object g2int_launch_system(Object);
extern Object g2int_machine_model(void);
extern Object g2int_make_an_alist_of_file_property_defaults(Object);
extern Object g2int_new_directory_for_bootstrap(Object);
extern Object g2int_non_optional_or_included_optional_module_p(Object,Object,Object);
extern Object g2int_normalize_module_name_or_description(Object);
extern Object g2int_open_editor_stream_or_bitsink(Object);
extern Object g2int_set_file_property(Object,Object,Object,Object,Object);
extern Object g2int_set_system_version(Object,Object);
extern Object g2int_stable_list_union(Object,Object);
extern Object g2int_string_or_symbol_equal(Object,Object);
extern Object g2int_supports_editor_stream_p(void);
extern Object g2int_system_p(Object);
extern Object g2int_write_system_version(Object);

#else

extern Object g2int_add_to_directory_list_for_bootstrapping();
extern Object g2int_declare_system_1();
extern Object g2int_directory_for_bootstrap();
extern Object g2int_eval_feature();
extern Object g2int_gensym();
extern Object g2int_get_binary_file_type();
extern Object g2int_get_default_binary_file_type();
extern Object g2int_get_default_binary_pathname_name();
extern Object g2int_get_default_include_test();
extern Object g2int_get_default_local_directory_namestring();
extern Object g2int_get_default_local_file_type();
extern Object g2int_get_default_local_pathname_name();
extern Object g2int_get_default_master_directory_namestring();
extern Object g2int_get_default_master_file_type();
extern Object g2int_get_default_master_pathname_name();
extern Object g2int_get_file_property();
extern Object g2int_get_local_file_type();
extern Object g2int_get_system_major_version();
extern Object g2int_get_system_minor_version();
extern Object g2int_install_all_file_properties_from_alist();
extern Object g2int_install_all_file_properties_from_plist();
extern Object g2int_install_file_properties_for_file_name_or_description();
extern Object g2int_install_file_properties_for_system();
extern Object g2int_launch_system();
extern Object g2int_machine_model();
extern Object g2int_make_an_alist_of_file_property_defaults();
extern Object g2int_new_directory_for_bootstrap();
extern Object g2int_non_optional_or_included_optional_module_p();
extern Object g2int_normalize_module_name_or_description();
extern Object g2int_open_editor_stream_or_bitsink();
extern Object g2int_set_file_property();
extern Object g2int_set_system_version();
extern Object g2int_stable_list_union();
extern Object g2int_string_or_symbol_equal();
extern Object g2int_supports_editor_stream_p();
extern Object g2int_system_p();
extern Object g2int_write_system_version();

#endif

/* variables/constants */
extern Object G2int_ab_package_1;
extern Object G2int_ab_system_pathname;
extern Object G2int_alist_of_file_property_base_defaults;
extern Object G2int_alist_of_system_file_class_descriptions;
extern Object G2int_all_modules_of_all_systems;
extern Object G2int_all_systems;
extern Object G2int_allow_development_compile_p;
#define G2int_alpha_release_quality FIX((SI_Long)1L)
#define G2int_alphant_code FIX((SI_Long)24L)
#define G2int_alphaosf_code FIX((SI_Long)23L)
#define G2int_alphavms_code FIX((SI_Long)17L)
#define G2int_aviion_code FIX((SI_Long)3L)
#define G2int_beta_release_quality FIX((SI_Long)2L)
extern Object G2int_bootstrap_information;
extern Object G2int_current_directory_of_binary_truenames;
extern Object G2int_current_directory_of_source_truenamesqm;
extern Object G2int_current_module_lisp_binary_filename;
extern Object G2int_current_module_source_filename;
extern Object G2int_current_moduleqm;
extern Object G2int_current_system_being_loaded;
#define G2int_decstation_code FIX((SI_Long)7L)
extern Object G2int_do_not_load_modules_p;
#define G2int_dos_code FIX((SI_Long)2L)
extern Object G2int_filename_of_module_being_loadedqm;
extern Object G2int_g2_machine_type;
extern Object G2int_g2_operating_system;
#define G2int_harris_code FIX((SI_Long)21L)
#define G2int_hp9000s300_code FIX((SI_Long)9L)
#define G2int_hp9000s400_code FIX((SI_Long)10L)
#define G2int_hp9000s700_code FIX((SI_Long)11L)
#define G2int_hp9000s800_code FIX((SI_Long)12L)
#define G2int_hpia_code FIX((SI_Long)30L)
#define G2int_i386_code FIX((SI_Long)1L)
#define G2int_intelnt_code FIX((SI_Long)25L)
#define G2int_intelsol_code FIX((SI_Long)31L)
extern Object G2int_last_bootstrap_modeqm;
extern Object G2int_least_positive_normalized_gensym_float;
#define G2int_linux_code FIX((SI_Long)28L)
#define G2int_mac_code FIX((SI_Long)29L)
extern Object G2int_machine_model_var;
extern Object G2int_macroexpanding_for_instruction_expander;
extern Object G2int_making_distribution_systemqm;
#define G2int_masscomp_code FIX((SI_Long)8L)
extern Object G2int_most_negative_gensym_float;
extern Object G2int_most_positive_gensym_float;
extern Object G2int_most_recent_defun_warned_for_catchqm;
extern Object G2int_most_recent_defun_warned_for_unwind_protectqm;
#define G2int_motorola_code FIX((SI_Long)18L)
#define G2int_ncr_code FIX((SI_Long)26L)
#define G2int_nec_code FIX((SI_Long)22L)
#define G2int_next_code FIX((SI_Long)6L)

/* An output stream used by Boot-System as a `null device' when silent operation is needed. */
extern Object G2int_null_io;
extern Object G2int_override_eliminate_for_gsi_no_utf_g_p;
extern Object G2int_override_eliminate_for_gsi_p;
extern Object G2int_pathname_for_distribution_binariesqm;
#define G2int_prototype_release_quality FIX((SI_Long)0L)
#define G2int_release_quality FIX((SI_Long)3L)
#define G2int_rs6000_code FIX((SI_Long)13L)
#define G2int_sequent_code FIX((SI_Long)5L)
#define G2int_sgi_code FIX((SI_Long)4L)
extern Object G2int_source_directory_name;
#define G2int_sparcsol_code FIX((SI_Long)16L)
#define G2int_stratus_code FIX((SI_Long)20L)
#define G2int_sun3_code FIX((SI_Long)14L)
#define G2int_sun4_code FIX((SI_Long)15L)
extern Object G2int_use_directory_lists_for_bootstrappingqm;
#define G2int_vms_code FIX((SI_Long)19L)
#define G2int_windows95_code FIX((SI_Long)27L)
