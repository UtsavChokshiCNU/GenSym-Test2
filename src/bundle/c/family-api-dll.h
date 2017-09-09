/* This is only to be included in a C++ file for DLL exportation.*/


/* DLL entry points: */
extern "C" __declspec(dllexport)  BSTR initialize_family_file(char* filename);
/* Implementing C function:*/
extern "C" extern char * open_and_parse_family_file(char *filename);

/* We define the DLL entry point (get_whatever) and the implementing C function (whatever) */
#define def_bundle_strfun(NAME) extern "C" __declspec(dllexport) BSTR get_##NAME();\
extern "C" extern char* NAME();
#define def_bundle_intfun(NAME) extern "C" __declspec(dllexport) int get_##NAME();\
extern "C" extern int NAME();
/* Family structure interesting slots */
def_bundle_intfun(family_installer_version)
def_bundle_intfun(family_id)
def_bundle_strfun(family_splash_screen)
def_bundle_strfun(family_readme)
def_bundle_strfun(family_license)
def_bundle_strfun(family_guid)
def_bundle_strfun(family_version)
def_bundle_strfun(family_directory)
def_bundle_intfun(family_os_availability)
def_bundle_strfun(family_prev_vers)

/* Bundle structure interesting slots */
def_bundle_strfun(next_bundle)
def_bundle_strfun(bundle_version)
def_bundle_intfun(bundle_id)
def_bundle_intfun(bundle_os_availability)
def_bundle_strfun(bundle_directory)
def_bundle_intfun(bundle_typical)

/* Component structure interesting slots */
def_bundle_strfun(next_component)
def_bundle_intfun(component_index)
def_bundle_intfun(component_typical)
def_bundle_strfun(component_watermark)
def_bundle_intfun(component_os_availability)

/* Part structure interesting slots */
def_bundle_strfun(next_part)
def_bundle_strfun(part_postinstall)
def_bundle_strfun(part_preinstall)
def_bundle_strfun(part_uninstall)
def_bundle_intfun(part_register)
def_bundle_intfun(part_os_availability)

/* environment variable structure interesting slots */
def_bundle_strfun(next_env_var)
def_bundle_strfun(env_var_value)
def_bundle_intfun(env_var_effect)

/* file data structure interesting slots */
def_bundle_intfun(next_file_data)
def_bundle_strfun(file_data_sourcename)
def_bundle_strfun(file_data_sourcedir)
def_bundle_strfun(file_data_destdir)
def_bundle_strfun(file_data_destname)
def_bundle_intfun(file_data_obfuscate)

/* registration structure interesting slots */
def_bundle_strfun(next_registration)
def_bundle_strfun(registration_path)
def_bundle_strfun(registration_key)
def_bundle_strfun(registration_value)

/* shortcut interesting slots */
def_bundle_strfun(next_shortcut)
def_bundle_strfun(shortcut_folder)
def_bundle_strfun(shortcut_subfolder)
def_bundle_strfun(shortcut_subsubfolder)
def_bundle_strfun(shortcut_directory)
def_bundle_strfun(shortcut_target_name)
def_bundle_strfun(shortcut_parameters)
def_bundle_strfun(shortcut_icon_file)
def_bundle_intfun(shortcut_icon_index)
def_bundle_intfun(shortcut_type)
def_bundle_intfun(shortcut_run_style)

/* "previous version" interesting slot */
def_bundle_strfun(prev_version_guid)
