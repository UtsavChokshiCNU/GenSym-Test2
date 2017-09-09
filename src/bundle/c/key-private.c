#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "codes.h"
#include "key-common.h"

extern unsigned int generate_random_nibbles(int);
extern unsigned int checksum_of_digits(unsigned int *digits);

/* Print the contents of the license_key in an easy to read way. */
void print_license_key(LICENSE_KEY *kstruct)
{
    int i,j;

    printf("key struct contents:\n--------------------\n");
    printf(" installer_version: %d\n",kstruct->installer_version);
    printf(" family_id: %d\n", kstruct->family_id);
    printf(" bundle_id: %d\n", kstruct->bundle_id);
    printf(" system_id: %d\n", kstruct->system_id);
    for (i=0;i<4;i++) {
        for (j=0;j<NUMBER_OF_COMPONENT_NIBBLES;j++)
            printf(" %02d", NUMBER_OF_COMPONENT_NIBBLES*i + j);
        printf("\n");
        for (j=0;j<NUMBER_OF_COMPONENT_NIBBLES;j++)
            printf("  %1d", kstruct->components[NUMBER_OF_COMPONENT_NIBBLES*i+j]);
        printf("\n");
    }
    for (i=NUMBER_OF_BASE_COMPONENTS;i<NUMBER_OF_COMPONENTS;i++)
      printf(" %02d", i);
    printf("\n");
    for (i=NUMBER_OF_BASE_COMPONENTS;i<NUMBER_OF_COMPONENTS;i++)
      printf("  %1d", kstruct->components[i]);
    printf("\n");
}

/* This is the inverse of words_to_keystruct.  It takes a license key
 * structure as input and sets the appropriate bits within the words.
 * Random fields are generated as needed.
 */
void keystruct_to_words (unsigned int *words, LICENSE_KEY *kstruct) {
    int i,j;
    unsigned int comps = 0;

    words[0] = kstruct->installer_version;
    words[1] = kstruct->family_id;
    words[2] = kstruct->bundle_id;
    words[3] = kstruct->system_id;

    /* First we fill in the "final" components in the two spare nibbles */

    for (i=NUMBER_OF_BASE_COMPONENTS;i<NUMBER_OF_COMPONENTS;i++) {
      comps = comps << 1;
      if (kstruct->components[i])
	comps = comps | 0x1;
    }
    if (comps)
      words[0] = words[0] | 0x80;
    else
      comps = generate_random_nibbles(1);

    words[2] = words[2] | (comps & 0xf0);
    words[3] = words[3] | ((comps & 0xf) << 4);

    for (i=0; i<4; i++) {
        comps = 0;
        for (j=NUMBER_OF_COMPONENT_NIBBLES-1; j>=0; j--) {
            comps = comps << 1;  /* has no effect first time */
            if (kstruct->components[i*NUMBER_OF_COMPONENT_NIBBLES + j])
                comps = comps | 0x1;
        }
        if (comps)
            comps = (comps << 1) | 0x1;  /* and set used bit */
        else
            comps = generate_random_nibbles(4) & 0xfffe; /* clear used bit */

        words[i] = words[i] | (comps<<8); /* place comps in bits 8 thru 23 */
    }
}

/* This is the inverse of digits_to_words above.  It takes the nibbles
 * from the words arrays and places them in the digits array.  Each word
 * of the word array is first decoded using the mask.
 */
void words_to_digits (unsigned int *digits,
                      unsigned int *words,
                      unsigned int mask) {
    int i,j;
    unsigned int word;

    for (i=0; i<NUMBER_OF_WORDS; i++) {
        word = words[i] ^ mask;
        for (j=0; j<6; j++) {
            digits[6*i+j] = word & 0xf;
            word = word >> 4;
        }
    }
}

/* This is the inverse of digits_to_mask.  It puts bit 4 into each of
 * the digits.  It assumes that bit 4 is clear for each digit.
 */
void mask_into_digits (unsigned int *digits, unsigned int mask)
{
    int i;

    for (i=0; i<DATA_DIGITS_IN_KEY; i++) {
        digits[i] = digits[i] | ((mask & 0x1) << 4);
        mask = mask >> 1;
    }
}
/* This takes an array of (25) 5-bit digits and encodes them as a 25-char
 * license key separated by hyphens.  The key has form
 * xxxxx-xxxxx-xxxxx-xxxxx-xxxxx, where each x is "encrypted" through
 * the chartrans array, defined above.
 */



void digits_to_key (char *chars, unsigned int *digits)
{
  int i, brk, chars_index = 0;

  for (i = 0, brk = 1; i < DIGITS_IN_KEY; i++, brk = (brk + 1) % 5) {
    chars[chars_index++] = chartrans[digits[i]];
    if ((brk == 0) && (i < DIGITS_IN_KEY-1))
      chars[chars_index++] = '-';
  }

  chars[chars_index] = '\0';
}

/* This is a composite function that uses the helper functions
 * above to create a license key from the information in the key struct.
 */
void keystruct_to_key (char *key, LICENSE_KEY *kstruct)
{
    unsigned int words[NUMBER_OF_WORDS];
    unsigned int int_buf[DIGITS_IN_KEY];
    unsigned int mask;

    keystruct_to_words(words,kstruct);
    mask = generate_random_nibbles(6);
    words_to_digits(int_buf, words, mask);
    mask_into_digits(int_buf, mask);
    int_buf[DIGITS_IN_KEY-1] = checksum_of_digits(int_buf);
    digits_to_key(key,int_buf);
}
