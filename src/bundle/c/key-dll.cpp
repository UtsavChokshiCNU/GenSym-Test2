#include "InstUtilDLL.h"

/**************************************************************************/
/* Global variables used by the external API at the end of this file.
 */
static LICENSE_KEY lic_key;   /* Holds single instance of a license key.*/
static int lic_key_initialized = 0;  /* Whether key has been initialized.*/
static int current_component_index = -1; /* For the component iterator. */

/****************************************************************************/
/* The functions below define the external interface to allow this C module
 * to serve as a single-instance object.  It uses a few static global
 * variables.
 */

/* Take a license key as input and decode it.
 * Outputs:
 *    return value: SUCCESS or non-zero error value
 *    global lic_key: populated if key is valid.
 *    global lic_key_initialized: 1 if key is valid.
 */
int initialize_license_key (char *key)
{
    int status;

    lic_key_initialized = 0;  /* Reset to allow successive keys. */
    current_component_index = -1;

    status = key_to_keystruct(key, &lic_key);
    if (status == SUCCESS)
        lic_key_initialized = 1;

    return status;
}

int get_installer_version()
{
    if (lic_key_initialized)
        return (int)lic_key.installer_version;
    else
        return -1;
}

int get_familyid()
{
    if (lic_key_initialized)
        return (int)lic_key.family_id;
    else
        return -1;
}

int get_bundleid()
{
    if (lic_key_initialized)
        return (int)lic_key.bundle_id;
    else
        return -1;
}

int get_systemid()
{
    if (lic_key_initialized)
        return (int)lic_key.system_id;
    else
		return -1;
}

int get_first_component_index()
{
    if (!lic_key_initialized)
        return -1;

    current_component_index = 0;
    if (lic_key.components[0] == 1)
        return 0;
    else
        return get_next_component_index();
}

/* Use the global current_component_index to find the next licensed component
 * in the global lic_key and return the index.  If all licensed components have
 * been returned already, set current_component_index to -1 and return -1.
 */
int get_next_component_index()
{
    if (!lic_key_initialized || current_component_index == -1)
        return -1;

    current_component_index++;
    while (current_component_index < NUMBER_OF_COMPONENTS - 1) {
        if (lic_key.components[current_component_index] == 1)
            return current_component_index;
        current_component_index++;
    }

    current_component_index = -1;
    return -1;
}

#if 0
/* A simple test for checking the interface in isolation. */
void test_key_interface(char *key)
{
    int index;
    int status;

    status = initialize_license_key(key);
    if (status != SUCCESS) {
        printf("bad key\n");
        return;
    }
    printf("family id: %d\n",get_familyid());
    printf("bundle id: %d\n",get_bundleid());
    printf("system id: %d\n",get_systemid());
    printf("component indices are: \n");

    index = get_first_component_index();
    while (index != -1) {
        printf("%d ",index);
        index = get_next_component_index();
    }
    printf("\n");
    
}
#endif
