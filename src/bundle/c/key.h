/* This file contains the definitions needed for processing license keys.
 */

extern int initialize_license_key (char*);
extern int get_installer_version();
extern int get_familyid();
extern int get_bundleid();
extern int get_systemid();
extern int get_first_component_index();
extern int get_next_component_index();

#include "key-common.h"
