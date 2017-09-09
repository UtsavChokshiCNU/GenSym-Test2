#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "codes.h"
#include "key-common.h"


/**************************************************************************/
/* The utility functions of this module are below.
 */

/* Create a 5-digit checksum, using xor, of the digits containing data.
 */
unsigned int checksum_of_digits(unsigned int *digits)
{
    int i;
    unsigned int checksum;

    checksum = 0;

    for (i=0; i<DATA_DIGITS_IN_KEY; i++) {
        checksum = checksum ^ digits[i];
    }
    return checksum;
}

/* This is a specially hardcoded function that extracts the fields from
 * the 4 24-bit words.  Each word has bits
 *     cccc cccc cccc cccu eeee dddd
 * c* are fifteen bits, each of which indicates whether the corresponding
 * component is licensed.  u indicates whether the c* are used.  If not, the
 * values of c* are random, to help obscure an otherwise sparse array.
 * To add 8 more components, the value of eeee is used in words 2 and 3 for
 * components.  dddd is used for bundle id and system id (limiting these values
 * to a max of 15).
 * eeeedddd is a 7-bit value for the installer version in word 0, with the first
 * bit (first e) being the "is used" bit for the extra 8 components, otherwise
 * some of those bits are also randomized.  For backwards compatibility
 * purposes, we do not randomize the extra bits in bundle ID if they are
 * unused.
 */
void words_to_keystruct (unsigned int *words, LICENSE_KEY *kstruct) {
    int i,j;
    unsigned int comps;

    kstruct->installer_version = words[0] & 0x7f;   /* 7 bits; 8th is for "is-used" in spare bits */
    kstruct->family_id         = words[1] & 0xff;   /* 8 bits */
    kstruct->bundle_id         = words[2] & 0xf;    /* 4 bits */
    kstruct->system_id         = words[3] & 0xf;    /* 4 bits */

    for (i=0; i<NUMBER_OF_COMPONENTS; i++)  /* preinitialize all to unlicensed */
        kstruct->components[i] = 0;

    for (i=0; i<4; i++) {
        if (words[i] & 0x100) { /* if component bits are used */
            comps = words[i] >> 9;
            for (j=0; j<NUMBER_OF_COMPONENT_NIBBLES; j++) {
                kstruct->components[i*NUMBER_OF_COMPONENT_NIBBLES + j] = comps & 0x1;
                comps = comps >> 1;
            }
        }
    }
    /* Now go get the additional 8 components from the two spare nibbles */
    if (words[0] & 0x80) {
      comps = (words[2] & 0xf0) | ((words[3] & 0xf0) >> 4);
      for (i=NUMBER_OF_COMPONENTS-1;i>=NUMBER_OF_BASE_COMPONENTS;i--) {
	kstruct->components[i] = comps & 0x1;
	comps = comps >> 1;
      }
    }
}

/* From the array of 5-bit digits, this takes the 4-bit content and places
 * it in four 24-bit words.  The order is effectively little endian.  I.e.,
 * each 4-bit nibble is numbered 0 to 23.  Nibble 0 is placed in the least
 * significant nibble of word 0, etc. Each word is encoded using the mask.
 */
void digits_to_words (unsigned int *digits,
                      unsigned int *words,
                      unsigned int mask) {
    int i,j;

    for (i=0; i<NUMBER_OF_WORDS; i++) {
        words[i] = 0;
        for (j=5; j>=0; j--
            ) {
        /*  printf("integrating 6*i+j: %d, value %03x\n",
                6*i+j, digits[6*i+j] & 0xf); */
            words[i] = (words[i]<<4) | (digits[6*i+j] & 0xf);
        }
        words[i] = words[i] ^ mask;
    }
}

/* The mask is bit 4 (the most significant bit) of each 5-bit data digit
 * (the checksum digit is excluded). It is cleared before being populated.
 * digits[DIGITS_IN_KEY] provides the most significant mask bit, while
 * digits[0] provides the least significant mask bit.
 */
unsigned int digits_to_mask (unsigned int *digits) {
    int i;
    unsigned int mask;

    mask = 0;

    for (i=DATA_DIGITS_IN_KEY-1; i>=0; i--) {
        mask = (mask<<1) | (digits[i]>>4);
    }
    return mask;
}

/* This is the inverse of digits_to_key.  It takes the user's input
 * of the 25-char license key and translates it into an array of 5-bit
 * integers.  We allow the input to contain arbitrary hyphens and whitespace,
 * but we limit the length just for sanity's sake.
 */
int key_to_digits (char *chars, unsigned int *digits)
{
    int i;
    int digits_index;
    char c;

    if (chars == NULL) 
        return KEY_NULL_STRING;

    if (strlen(chars) > DIGITS_PLUS_FILLER_IN_KEY) /* allow some whitespace */
        return KEY_STRING_TOO_LONG;

    digits_index = 0;
    while ((c = *chars++) != '\0') {
        if (isdigit(c) || isalpha(c)) {
            if (digits_index > DIGITS_IN_KEY - 1)
                return KEY_TOO_MANY_DIGITS;  /* too many characters */
            if (isupper(c))
                c = tolower(c);
            for (i=0; i<32; i++) {
                if (c == chartrans[i]) {
                    digits[digits_index++] = i;
                    break;
                }
            }
            if (i == 32)    
                return KEY_INVALID_ALPHANUM;  /* not in chartrans[] */
        } else if (!isspace(c) && c != '-') 
            return KEY_ILLEGAL_CHARACTER; /* not a valid license character */
    }
    if (digits_index != DIGITS_IN_KEY) /* too few characters */
        return KEY_TOO_FEW_DIGITS;
    return SUCCESS;
}

/* This takes a user-input key string and uses the helper functions
 * above to convert it to a structure containing the same info.  This
 * is the inverse of the previous function.  Because the user can make
 * mistakes or try to break the code, this also performs various error
 * checks on integrity.
 */
int key_to_keystruct(char *key, LICENSE_KEY *kstruct)
{
    unsigned int words[NUMBER_OF_WORDS];
    unsigned int int_buf[DIGITS_IN_KEY];
    unsigned int mask;
    int status;

    status = key_to_digits(key, int_buf);
    if (status != SUCCESS)
        return status;   /* key is badly formed */

    if (checksum_of_digits(int_buf) != int_buf[DIGITS_IN_KEY-1])
        return KEY_BAD_CHECKSUM;   /* checksum was bad */

    mask = digits_to_mask (int_buf);
    digits_to_words(int_buf, words, mask);
    words_to_keystruct(words, kstruct);

    return SUCCESS;
}
