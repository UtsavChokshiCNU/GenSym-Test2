#include "speedo.h"
#include "fino.h"
#include "stdef.h"




FUNCTION void set_keys(cust_no, init_key, keys)
ufix16 cust_no;   /* Customer number */                               
ufix16 init_key;  /* Master encryption key */
ufix8  *keys;     /* Encryption key array */

/* 
 * Sets encryption keys for font generation.
 * Note that key generation may only depend on the first 240 bytes of the generated font
 */
{
ufix16 key;

ufix8  next_key();

if (cust_no)                /* Customer number non-zero? */
    {
    key = init_key;         /* Use standard decryption key */

    keys[1] = next_key(&key);
    keys[2] = next_key(&key);
    keys[3] = next_key(&key) & 0x03;
    keys[4] = next_key(&key);
    keys[5] = next_key(&key);
    keys[6] = next_key(&key);
    keys[7] = next_key(&key);
    keys[8] = next_key(&key);
    }
else                        /* Zero customer number - no encryption */
    {
    keys[1] = keys[2] = keys[3] = keys[4] = keys[5] = keys[6] = keys[7] = keys[8] = 0; 
    }
}


FUNCTION ufix8 next_key(pkey)
ufix16 *pkey;
/*
 * Scrambles *pkey in a pseudo-random way.
 * Returns a ufix8 key value extracted from *pkey.
 */
{
ufix32 key;
fix15  i;

key = *pkey;
key = key * 78231 + 23805;
*pkey = key;
return (ufix8)((key >> 3) & 0xff);
}
