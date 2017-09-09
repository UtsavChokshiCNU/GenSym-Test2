/* btstrp.h -- Header File for btstrp.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qand;
extern Object Kchestnut;
extern Object Qcompile;
extern Object Kdefaults;
extern Object Kdirectory;
extern Object Khost;
extern Object Kname;
extern Object Knewest;
extern Object Qnot;
extern Object Ktest;
extern Object Ktype;
extern Object Kversion;
extern Object Kwild;

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

extern Object ab_gensym(int,...);
extern Object add_to_directory_list_for_bootstrapping(Object,Object);
extern Object check_boot_system_options(Object,Object);
extern Object check_last_bootstrap_mode(Object,Object);
extern Object choose_appropriate_binary_directory(Object);
extern Object declare_system_1(int,...);
extern Object directory_for_bootstrap(Object);
extern Object eval_feature(Object);
extern Object extract_list_of_optional_modules(Object,Object);
extern Object extract_pathname_for_distribution_binaries(Object,Object);
extern Object extract_pathname_for_non_distribution_binaries(Object,Object,Object);
extern Object get_binary_file_type(Object,Object,Object);
extern Object get_default_binary_directory_namestring(Object,Object,Object);
extern Object get_default_binary_file_type(Object,Object,Object);
extern Object get_default_binary_pathname_name(Object,Object,Object);
extern Object get_default_include_test(Object,Object,Object,Object);
extern Object get_default_local_directory_namestring(Object,Object,Object);
extern Object get_default_local_file_type(Object,Object,Object);
extern Object get_default_local_pathname_name(Object,Object,Object);
extern Object get_default_master_directory_namestring(Object,Object,Object);
extern Object get_default_master_file_type(Object,Object,Object);
extern Object get_default_master_pathname_name(Object,Object,Object);
extern Object get_file_property(Object,Object,Object,Object);
extern Object get_file_write_date_from_directory_list(Object,Object);
extern Object get_local_file_type(Object,Object,Object);
extern Object get_quality_and_revision_of_revision_string(Object);
extern Object get_quality_and_revision_of_system_version(Object);
extern Object get_system_major_version(Object);
extern Object get_system_minor_version(Object);
extern Object include_for_load_p(Object,Object,Object);
extern Object install_all_file_properties_from_alist(Object,Object,Object,Object);
extern Object install_all_file_properties_from_plist(Object,Object,Object,Object);
extern Object install_file_properties_for_file_name_or_description(Object,Object,Object,Object);
extern Object install_file_properties_for_system(Object,Object,Object,Object);
extern Object launch_system(Object);
extern Object machine_model(void);
extern Object make_an_alist_of_file_property_defaults(Object);
extern Object make_module_filename(int,...);
extern Object make_system_c_file_object_namestring(int,...);
extern Object make_system_pathname(int,...);
extern Object new_directory_for_bootstrap(Object);
extern Object non_optional_or_included_optional_module_p(Object,Object,Object);
extern Object normalize_module_name_or_description(Object);
extern Object normalize_system_name(Object);
extern Object older_or_same_version_p(int,...);
extern Object open_editor_stream_or_bitsink(Object);
extern Object pathnames_similar_p(Object,Object);
extern Object set_file_property(Object,Object,Object,Object,Object);
extern Object set_system_version(Object,Object);
extern Object signal_forward_reference(Object);
extern Object stable_list_union(Object,Object);
extern Object stand_in_for_forwardly_referenced_function(int,...);
extern Object string_for_binary_file_name_and_type(Object,Object,Object);
extern Object string_for_binary_file_namestring(Object,Object,Object);
extern Object string_for_file_name_and_type(Object,Object,Object);
extern Object string_for_file_namestring(Object,Object,Object,Object);
extern Object string_for_local_file_namestring(Object,Object,Object);
extern Object string_for_master_file_name_and_type(Object,Object,Object);
extern Object string_for_master_file_namestring(Object,Object,Object);
extern Object string_or_symbol_equal(Object,Object);
extern Object supports_editor_stream_p(void);
extern Object system_binary_pathname_qm(Object);
extern Object system_p(Object);
extern Object system_revision_greater_p(Object,Object);
extern Object system_version_greater_p(Object,Object);
extern Object text_string_p(Object);
extern Object translate_binary_directory_or_default(Object,Object);
extern Object use_dates_instead_of_versions_p(void);
extern Object write_system_version(Object);
extern Object write_system_version_to_string(Object);

#else

extern Object ab_gensym();
extern Object add_to_directory_list_for_bootstrapping();
extern Object check_boot_system_options();
extern Object check_last_bootstrap_mode();
extern Object choose_appropriate_binary_directory();
extern Object declare_system_1();
extern Object directory_for_bootstrap();
extern Object eval_feature();
extern Object extract_list_of_optional_modules();
extern Object extract_pathname_for_distribution_binaries();
extern Object extract_pathname_for_non_distribution_binaries();
extern Object get_binary_file_type();
extern Object get_default_binary_directory_namestring();
extern Object get_default_binary_file_type();
extern Object get_default_binary_pathname_name();
extern Object get_default_include_test();
extern Object get_default_local_directory_namestring();
extern Object get_default_local_file_type();
extern Object get_default_local_pathname_name();
extern Object get_default_master_directory_namestring();
extern Object get_default_master_file_type();
extern Object get_default_master_pathname_name();
extern Object get_file_property();
extern Object get_file_write_date_from_directory_list();
extern Object get_local_file_type();
extern Object get_quality_and_revision_of_revision_string();
extern Object get_quality_and_revision_of_system_version();
extern Object get_system_major_version();
extern Object get_system_minor_version();
extern Object include_for_load_p();
extern Object install_all_file_properties_from_alist();
extern Object install_all_file_properties_from_plist();
extern Object install_file_properties_for_file_name_or_description();
extern Object install_file_properties_for_system();
extern Object launch_system();
extern Object machine_model();
extern Object make_an_alist_of_file_property_defaults();
extern Object make_module_filename();
extern Object make_system_c_file_object_namestring();
extern Object make_system_pathname();
extern Object new_directory_for_bootstrap();
extern Object non_optional_or_included_optional_module_p();
extern Object normalize_module_name_or_description();
extern Object normalize_system_name();
extern Object older_or_same_version_p();
extern Object open_editor_stream_or_bitsink();
extern Object pathnames_similar_p();
extern Object set_file_property();
extern Object set_system_version();
extern Object signal_forward_reference();
extern Object stable_list_union();
extern Object stand_in_for_forwardly_referenced_function();
extern Object string_for_binary_file_name_and_type();
extern Object string_for_binary_file_namestring();
extern Object string_for_file_name_and_type();
extern Object string_for_file_namestring();
extern Object string_for_local_file_namestring();
extern Object string_for_master_file_name_and_type();
extern Object string_for_master_file_namestring();
extern Object string_or_symbol_equal();
extern Object supports_editor_stream_p();
extern Object system_binary_pathname_qm();
extern Object system_p();
extern Object system_revision_greater_p();
extern Object system_version_greater_p();
extern Object text_string_p();
extern Object translate_binary_directory_or_default();
extern Object use_dates_instead_of_versions_p();
extern Object write_system_version();
extern Object write_system_version_to_string();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Ab_package_1, Qab_package_1);
DECLARE_VARIABLE_WITH_SYMBOL(Ab_system_pathname, Qab_system_pathname);
extern Object Alist_of_file_property_base_defaults;
extern Object Alist_of_system_file_class_descriptions;
extern Object All_modules_of_all_systems;
DECLARE_VARIABLE_WITH_SYMBOL(All_systems, Qall_systems);
extern Object Allow_development_compile_p;
#define Alpha_release_quality FIX((SI_Long)1L)
#define Alphant_code FIX((SI_Long)24L)
#define Alphaosf_code FIX((SI_Long)23L)
#define Alphavms_code FIX((SI_Long)17L)
#define Aviion_code FIX((SI_Long)3L)
#define Beta_release_quality FIX((SI_Long)2L)
DECLARE_VARIABLE_WITH_SYMBOL(Bootstrap_information, Qbootstrap_information);
DECLARE_VARIABLE_WITH_SYMBOL(Current_directory_of_binary_truenames, Qcurrent_directory_of_binary_truenames);
DECLARE_VARIABLE_WITH_SYMBOL(Current_directory_of_source_truenames_qm, Qcurrent_directory_of_source_truenames_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_module_lisp_binary_filename, Qcurrent_module_lisp_binary_filename);
DECLARE_VARIABLE_WITH_SYMBOL(Current_module_qm, Qcurrent_module_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_module_source_filename, Qcurrent_module_source_filename);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_being_loaded, Qcurrent_system_being_loaded);
#define Decstation_code FIX((SI_Long)7L)
DECLARE_VARIABLE_WITH_SYMBOL(Do_not_load_modules_p, Qdo_not_load_modules_p);
#define Dos_code FIX((SI_Long)2L)
DECLARE_VARIABLE_WITH_SYMBOL(Filename_of_module_being_loaded_qm, Qfilename_of_module_being_loaded_qm);
DECLARE_VARIABLE_WITH_SYMBOL(G2_machine_type, Qg2_machine_type);
DECLARE_VARIABLE_WITH_SYMBOL(G2_operating_system, Qg2_operating_system);
#define Harris_code FIX((SI_Long)21L)
#define Hp9000s300_code FIX((SI_Long)9L)
#define Hp9000s400_code FIX((SI_Long)10L)
#define Hp9000s700_code FIX((SI_Long)11L)
#define Hp9000s800_code FIX((SI_Long)12L)
#define Hpia_code FIX((SI_Long)30L)
#define I386_code FIX((SI_Long)1L)
#define Intelnt_code FIX((SI_Long)25L)
#define Intelsol_code FIX((SI_Long)31L)
DECLARE_VARIABLE_WITH_SYMBOL(Last_bootstrap_mode_qm, Qlast_bootstrap_mode_qm);
extern Object Least_positive_normalized_gensym_float;
#define Linux_code FIX((SI_Long)28L)
#define Mac_code FIX((SI_Long)29L)
DECLARE_VARIABLE_WITH_SYMBOL(Machine_model_var, Qmachine_model_var);
DECLARE_VARIABLE_WITH_SYMBOL(Macroexpanding_for_instruction_expander, Qmacroexpanding_for_instruction_expander);
DECLARE_VARIABLE_WITH_SYMBOL(Making_distribution_system_qm, Qmaking_distribution_system_qm);
#define Masscomp_code FIX((SI_Long)8L)
extern Object Most_negative_gensym_float;
extern Object Most_positive_gensym_float;
DECLARE_VARIABLE_WITH_SYMBOL(Most_recent_defun_warned_for_catch_qm, Qmost_recent_defun_warned_for_catch_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Most_recent_defun_warned_for_unwind_protect_qm, Qmost_recent_defun_warned_for_unwind_protect_qm);
#define Motorola_code FIX((SI_Long)18L)
#define Ncr_code FIX((SI_Long)26L)
#define Nec_code FIX((SI_Long)22L)
#define Next_code FIX((SI_Long)6L)

/* An output stream used by Boot-System as a `null device' when silent operation is needed. */
extern Object Null_io;
DECLARE_VARIABLE_WITH_SYMBOL(Override_eliminate_for_gsi_no_utf_g_p, Qoverride_eliminate_for_gsi_no_utf_g_p);
DECLARE_VARIABLE_WITH_SYMBOL(Override_eliminate_for_gsi_p, Qoverride_eliminate_for_gsi_p);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_distribution_binaries_qm, Qpathname_for_distribution_binaries_qm);
extern Object Positive_bits_per_fixnum;
#define Prototype_release_quality FIX((SI_Long)0L)
#define Release_quality FIX((SI_Long)3L)
#define Rs6000_code FIX((SI_Long)13L)
#define Sequent_code FIX((SI_Long)5L)
#define Sgi_code FIX((SI_Long)4L)
extern Object Source_directory_name;
#define Sparcsol_code FIX((SI_Long)16L)
#define Stratus_code FIX((SI_Long)20L)
#define Sun3_code FIX((SI_Long)14L)
#define Sun4_code FIX((SI_Long)15L)
DECLARE_VARIABLE_WITH_SYMBOL(Use_directory_lists_for_bootstrapping_qm, Quse_directory_lists_for_bootstrapping_qm);
#define Vms_code FIX((SI_Long)19L)
#define Windows95_code FIX((SI_Long)27L)
