#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>     /* For randomize_seed() */

/* Use epoch seconds to seed the random number generator randomly. */
void randomize_seed()
{
    time_t t;

    t = time(&t);
    srand((unsigned int) t);
}

/* This uses the rand() function to produce a random value of up
 * to 8 nibbles (32 bits).  It is assumed that rand() has been
 * seeded elsewhere.
 */
unsigned int generate_random_nibbles (int number_of_nibbles)
{
    int i;
    unsigned int value;

    if (number_of_nibbles > 8)
        number_of_nibbles = 8;

    value = 0;
    for (i=0; i<number_of_nibbles; i++) {
        value = value << 4;  /* has no effect first time */
        value = value | (rand() & 0xf);
    }
    return value;
}
