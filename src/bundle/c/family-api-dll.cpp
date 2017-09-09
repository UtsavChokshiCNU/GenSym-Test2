#include <ole2.h>
#include "family-api-dll.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>


/**************************************************************************
 *
 * Functions for parsing the family file via the dll
 * 
 **************************************************************************/

BSTR returnstring;
#define RETURN_BSTR(charstar) returnstring = SysAllocStringByteLen(charstar, strlen(charstar)); return returnstring;

BSTR initialize_family_file(char* filename)
{
  BSTR returnstring;
  LPSTR message;
  message = open_and_parse_family_file(filename);
  RETURN_BSTR(message);
}

/*
 * What's going on here is that C++ and C don't really get along very well, and
 * the bundle structures are all defined for C.  In this DLL, we want to provide
 * functions to be used by Visual Basic, and I'm not sure if I can just do it in
 * C directly; all the rest are in C++.  So, I'm making a lot of glue.  I need to
 * keep a lot of "current pointer" information, so that I can just have Visual
 * Basic call accessories based on "the next one" and "the current one", rather
 * than trying to deal with C structures in Visual Basic (which is possible, but
 * the pointers are just type Long, so I'd have to have accessors anyway, and
 * this way I don't have to deal with the family file types in C++).
 *
 */



/* def_bundle_strop (xxx) defines get_xxx to call xxx, defined in
   family-api-impl.c, and repackages the return value.  def_bundle_intop
   similarly, but the return value does not need repackaging */

#define def_bundle_strop(NAME) BSTR get_##NAME()\
{ BSTR returnstring;\
  char *internal;\
  internal = NAME();\
  if (internal != NULL) {\
    RETURN_BSTR(internal);\
  }\
  else return NULL; }

#define def_bundle_intop(NAME) int get_##NAME() { return NAME(); }

/* Family structure interesting slots */
def_bundle_intop(family_installer_version)
def_bundle_intop(family_id)
def_bundle_strop(family_splash_screen)
def_bundle_strop(family_readme)
def_bundle_strop(family_license)
def_bundle_strop(family_guid)
def_bundle_strop(family_version)
def_bundle_strop(family_directory)
def_bundle_intop(family_os_availability)
def_bundle_strop(family_prev_vers)

/* Bundle structure interesting slots */
def_bundle_strop(next_bundle)
def_bundle_strop(bundle_version)
def_bundle_intop(bundle_id)
def_bundle_intop(bundle_os_availability)
def_bundle_strop(bundle_directory)
def_bundle_intop(bundle_typical)

/* Component structure interesting slots */
def_bundle_strop(next_component)
def_bundle_intop(component_index)
def_bundle_intop(component_typical)
def_bundle_strop(component_watermark)
def_bundle_intop(component_os_availability)

/* Part structure interesting slots */
def_bundle_strop(next_part)
def_bundle_strop(part_postinstall)
def_bundle_strop(part_preinstall)
def_bundle_strop(part_uninstall)
def_bundle_intop(part_register)
def_bundle_intop(part_os_availability)

/* environment variable structure interesting slots */
def_bundle_strop(next_env_var)
def_bundle_strop(env_var_value)
def_bundle_intop(env_var_effect)

/* file data structure interesting slots */
def_bundle_intop(next_file_data)
def_bundle_strop(file_data_sourcename)
def_bundle_strop(file_data_sourcedir)
def_bundle_strop(file_data_destdir)
def_bundle_strop(file_data_destname)
def_bundle_intop(file_data_obfuscate)

/* registration structure interesting slots */
def_bundle_strop(next_registration)
def_bundle_strop(registration_path)
def_bundle_strop(registration_key)
def_bundle_strop(registration_value)

/* shortcut interesting slots */
def_bundle_strop(next_shortcut)
def_bundle_strop(shortcut_folder)
def_bundle_strop(shortcut_subfolder)
def_bundle_strop(shortcut_subsubfolder)
def_bundle_strop(shortcut_directory)
def_bundle_strop(shortcut_target_name)
def_bundle_strop(shortcut_parameters)
def_bundle_strop(shortcut_icon_file)
def_bundle_intop(shortcut_icon_index)
def_bundle_intop(shortcut_type)
def_bundle_intop(shortcut_run_style)

/* "previous version" interesting slot */
def_bundle_strop(prev_version_guid)
