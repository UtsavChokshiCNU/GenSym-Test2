#include <stdio.h>
#include "codes.h"
#include "key-common.h"

void createkey (int argc, char *argv[])
{
    LICENSE_KEY lk;
    unsigned char keystring[30];
    int i;
    int index;
    int status;

    if (argc < 5) {
        printf("Usage: createkey <system_id> <family_id> <bundle_id> <component_indices...>\n");
        exit(1);
    }

    for(i=0; i<NUMBER_OF_COMPONENTS; i++)
        lk.components[i]=0;

    lk.installer_version = INSTALLER_VERSION;
    lk.system_id = atoi(argv[1]);
    lk.family_id = atoi(argv[2]);
    lk.bundle_id = atoi(argv[3]);;
    for (i=4; i<argc; i++) {
        index = atoi(argv[i]);
        if (index < 0 || index > NUMBER_OF_COMPONENTS - 1) {
            printf("illegal component index %d",index);
            exit(1);
        } else {
            lk.components[index] = 1;
        }
    }

    randomize_seed();
    keystruct_to_key(keystring, &lk);
    printf("%s\n",keystring);
}
    
main(int argc, char *argv[])
{
    createkey(argc, argv);
}
