/* $Id: decode-key.c,v 1.5 2006-09-11 16:10:19 yduj Exp $ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codes.h"
#include "key-common.h"

extern int key_to_keystruct(char*,LICENSE_KEY*);

/*
 * Check key integrity and convert it to a readable structure.
 */
int
main(int argc, char *argv[])
{
    LICENSE_KEY kstruct;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: decode-key <key>\n");
        exit(-1);
    }

    status = key_to_keystruct(argv[1], &kstruct);
    if (status != SUCCESS) {
        fprintf(stderr, "Error: Decoding failed with status %05x\n", status);
        exit(-1);
    }

    print_license_key(&kstruct);

    return 0;
}
