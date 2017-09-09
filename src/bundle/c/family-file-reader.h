#include <stdio.h>
#include "family-descriptor.h"

int parse_family_file (FAMILY_DESCRIPTOR *family);
extern int available_on_os (PART*, int);
extern int check_bit(int mask, int bit_number);
FAMILY_DESCRIPTOR* new_family ();
