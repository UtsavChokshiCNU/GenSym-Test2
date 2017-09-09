#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#include <shlwapi.h>
#endif

#include "tag-value-parser.h"
#include "family-descriptor.h"
#include "family-file-reader.h"
#include "codes.h"

/* See also comments in family-api-dll.c.
 *
 * This file is the implementation of the code to walk through a family file
 * that VB will call. Basically we just maintain a "current whatever" pointer,
 * and provide friendly accessors to its slots.  

 * All of the "next" functions will return the name of the item, and will deal
 * with whether you need to access the first/next structure slot.  They will
 * NULL out subpointers to their particular element so that the next pointers
 * will do the right thing.
 *
 * Unfortunately VB doesn't seem to distinguish between NULL and the actual
 * empty string, so if something doesn't have a name, it'll be thought as the
 * LAST pointer in the list.  So, everything better have a name.
 *
 */

/* To compile a standalone test program, do
   cl -DDO_MAIN family-api-impl.c family-file-reader.c tag-value-parser.c
*/

FILE *fp;

FAMILY_DESCRIPTOR *current_family = NULL;
BUNDLE *current_bundle = NULL;
COMPONENT *current_component = NULL;
PART *current_part = NULL;
PREV_VERSION *current_version = NULL;
ENV_VAR *current_env_var = NULL;
FILE_DATA *current_file_data = NULL;
SHORTCUT *current_shortcut = NULL;
REGISTRATION *current_registration = NULL;


#define CAREFUL_STR_RETURN(variable,slot) {if (variable == NULL ) return NULL; else return variable->slot;}
#define CAREFUL_INT_RETURN(variable,slot) {if (variable == NULL) return -1; else return variable->slot;}

char * open_and_parse_family_file (char * filename) 
{
  int status;
  fp = fopen(filename, "r");
  if (fp==NULL) {
    return "Error opening file";
  }
  current_family = new_family();

  status = parse_family_file(current_family);
  fclose(fp);

  if (status != 0)
    return "Error reading family file.";
  CAREFUL_STR_RETURN(current_family,fd_name);
}

/* This function is required by tag-value-parser.c, and this bogus
   implementation is lifted from serialize-family-file.c.  I don't understand
   why it works.  But I'm too lazy to figure it out. */
int get_line (buffer, max_length)
char* buffer;
int max_length;
{
  if ( fgets( buffer, max_length, fp) )
    return 2; /* punt on proper implementation */
  else
    return 0;
}

/* Family structure interesting slots */
int family_installer_version()
{
  CAREFUL_INT_RETURN(current_family,fd_installer_version);
}

int family_id()
{
  CAREFUL_INT_RETURN(current_family,fd_id);
}

char* family_splash_screen()
{
  CAREFUL_STR_RETURN(current_family,fd_splash_screen);
}

char* family_readme()
{
  CAREFUL_STR_RETURN(current_family,fd_readme);
}

char* family_license()
{
  CAREFUL_STR_RETURN(current_family,fd_license_text);
}

char* family_guid()
{
  CAREFUL_STR_RETURN(current_family,fd_guid);
}

char* family_version()
{
  CAREFUL_STR_RETURN(current_family,fd_version);
}

char* family_directory()
{
  CAREFUL_STR_RETURN(current_family,fd_directory_name);
}

/* We only care if it's available on intel for this purpose, so just true or false. */
int family_os_availability()
{
  if (current_family != NULL)
    return check_bit(current_family->fd_os_availability, INTELNT_CODE) ? FALSE : TRUE;
  else
    return FALSE;
}

char* family_prev_vers()
{
  if (current_version == NULL)
    current_version = current_family->fd_prev_versions;
  else
    current_version = current_version->pv_next;
  CAREFUL_STR_RETURN(current_version,pv_version);
}

char* prev_version_guid()
{
  CAREFUL_STR_RETURN(current_version,pv_guid);
}

/* Bundle structure interesting slots */
char* next_bundle()
{
  if (current_bundle == NULL)
    current_bundle = current_family->fd_first_bundle;
  else
    current_bundle = current_bundle->bdl_next_bundle;
  current_component = NULL;
  CAREFUL_STR_RETURN(current_bundle,bdl_name);
}

char* bundle_version()
{
  CAREFUL_STR_RETURN(current_bundle,bdl_version);
}

int bundle_id()
{
  CAREFUL_INT_RETURN(current_bundle,bdl_id);
}

int bundle_os_availability()
{
  if (current_bundle != NULL)
    return check_bit(current_bundle->bdl_os_availability, INTELNT_CODE) ? FALSE : TRUE;
  else
    return FALSE;
}

char* bundle_directory()
{
  CAREFUL_STR_RETURN(current_bundle,bdl_directory_name);
}

int bundle_typical()
{
  CAREFUL_INT_RETURN(current_bundle,bdl_typical_only);
}


/* Component structure interesting slots */
char* next_component()
{
  if (current_component == NULL)
    current_component = current_bundle->bdl_first_component;
  else
    current_component = current_component->cp_next_component;
  current_part = NULL;
  CAREFUL_STR_RETURN(current_component,cp_name);
}

int component_index()
{
  CAREFUL_INT_RETURN(current_component,cp_index);
}

int component_typical()
{
  CAREFUL_INT_RETURN(current_component,cp_typical);
}

char* component_watermark()
{
  CAREFUL_STR_RETURN(current_component,cp_watermark);
}

int component_os_availability()
{
  if (current_family != NULL)
    return check_bit(current_component->cp_os_availability, INTELNT_CODE) ? FALSE : TRUE;
  else
    return FALSE;
}


/* Part structure interesting slots */
char* next_part()
{
  if (current_part == NULL)
    current_part = current_component->cp_first_part;
  else
    current_part = current_part->pt_next_part;
  current_shortcut = NULL;
  current_env_var = NULL;
  current_file_data = NULL;
  current_registration = NULL;
  CAREFUL_STR_RETURN(current_part,pt_name);
}

char* part_postinstall()
{
  CAREFUL_STR_RETURN(current_part,pt_postinstall_code);
}

char* part_preinstall()
{
  CAREFUL_STR_RETURN(current_part,pt_preinstall_code);
}

char* part_uninstall()
{
  CAREFUL_STR_RETURN(current_part,pt_uninstall_code);
}

int part_register()
{
  CAREFUL_INT_RETURN(current_part,pt_register);
}

int part_os_availability()
{
  if (current_part != NULL)
    return available_on_os(current_part, INTELNT_CODE);
  else
    return FALSE;
}


/* environment variable structure interesting slots */
char* next_env_var()
{
  if (current_env_var == NULL)
    current_env_var = current_part->pt_first_env_var;
  else
    current_env_var = current_env_var->ev_next_env_var;
  CAREFUL_STR_RETURN(current_env_var,ev_name);

}

char* env_var_value()
{
  CAREFUL_STR_RETURN(current_env_var,ev_value);
}

int env_var_effect()
{
  CAREFUL_INT_RETURN(current_env_var,ev_effect);
}


/* file data structure interesting slots */

/* This has to be done differently because source name will be NIL if it's a
   directory we have.  The caller has to decide what to do, so we just return 1
   to mean there is one or 0 to mean end of list. */
int next_file_data()
{
  if (current_file_data == NULL)
    current_file_data = current_part->pt_first_file_data;
  else
    current_file_data = current_file_data->fd_next_file_data;
  if (current_file_data)
    return 1;
  else
    return 0;
}

char* file_data_sourcename()
{
  CAREFUL_STR_RETURN(current_file_data,fd_source_name);
}

char* file_data_sourcedir()
{
  CAREFUL_STR_RETURN(current_file_data,fd_source_directory);
}

char* file_data_destdir()
{
  CAREFUL_STR_RETURN(current_file_data,fd_destination_directory);
}

char* file_data_destname()
{
  CAREFUL_STR_RETURN(current_file_data,fd_destination_name);
}

int file_data_obfuscate()
{
  CAREFUL_INT_RETURN(current_file_data,fd_obfuscate);
}


/* registration structure interesting slots */
char* next_registration()
{
  if (current_registration == NULL)
    current_registration = current_part->pt_first_reg_object;
  else
    current_registration = current_registration->rg_next_reg_object;
  CAREFUL_STR_RETURN(current_registration,rg_name);
}

char* registration_path()
{
  CAREFUL_STR_RETURN(current_registration,rg_path);
}

char* registration_key()
{
  CAREFUL_STR_RETURN(current_registration,rg_key_name);
}

char* registration_value()
{
  CAREFUL_STR_RETURN(current_registration,rg_value);
}


/* shortcut interesting slots */
char* next_shortcut()
{
  if (current_shortcut == NULL)
    current_shortcut = current_part->pt_first_shortcut;
  else
    current_shortcut = current_shortcut->sc_next_shortcut;
  CAREFUL_STR_RETURN(current_shortcut,sc_display_name);
}

char* shortcut_folder()
{
  CAREFUL_STR_RETURN(current_shortcut,sc_folder);
}

char* shortcut_subfolder()
{
  CAREFUL_STR_RETURN(current_shortcut,sc_subfolder);
}

char* shortcut_subsubfolder()
{
  CAREFUL_STR_RETURN(current_shortcut,sc_subsubfolder);
}

char* shortcut_directory()
{
  CAREFUL_STR_RETURN(current_shortcut,sc_directory);
}

char* shortcut_target_name()
{
  CAREFUL_STR_RETURN(current_shortcut,sc_target_name);
}

char* shortcut_parameters()
{
  CAREFUL_STR_RETURN(current_shortcut,sc_parameters);
}

char* shortcut_icon_file()
{
  CAREFUL_STR_RETURN(current_shortcut,sc_icon_file);
}

int shortcut_icon_index()
{
  CAREFUL_INT_RETURN(current_shortcut,sc_icon_index);
}

int shortcut_type()
{
  CAREFUL_INT_RETURN(current_shortcut,sc_type);
}

int shortcut_run_style()
{
  CAREFUL_INT_RETURN(current_shortcut,sc_run_style);
}




#ifdef DO_MAIN
main()
{
  char* message;
  message = open_and_parse_family_file("c:\\bt\\yduj\\tools\\datafiles\\families\\tw2-12r6.fam");
  printf(message);
}
#endif
