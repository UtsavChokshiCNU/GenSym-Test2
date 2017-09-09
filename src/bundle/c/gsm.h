/* This file contains definitions needed by the tar bundling and unbundling
 * facilities.   It is used strictly by Unix.
 */

/* The magic number is the first 4 bytes of the file and allows the
 * filetype to be checked easily.
 */
#define GENSYM_MAGIC_NUMBER 0x6D736703    /* \003gsm */

/* The following is used for simple encryption of the
 * bytes of the header.
 */
#define HEADER_XOR 0xBD6A3E5

/* The following struct and #defines determine the layout and contents
 * of the .gsm file header.  Just to scramble things a little, the fields of
 * the structure have a different order than in the file header.
 */
typedef struct fileheader {
    unsigned char installer_version;
    unsigned char family_id;
    unsigned char system_id;
    unsigned int  family_file_length;
    unsigned int  crypt_mask;
    unsigned int  magic_number;
} FILEHEADER;

/* Indices of positions in header file. */
#define MAGIC_NUMBER_INDEX       0
#define SYSTEM_ID_INDEX          4
#define FAMILY_ID_INDEX          5
#define INSTALLER_VERSION_INDEX  6  
#define FAMILY_FILE_LENGTH_INDEX 7
#define CRYPT_MASK_INDEX        11

#define HEADER_LENGTH  (CRYPT_MASK_INDEX + 4)

/* For encryption and decryption of the family file and tar file, the read
 * buffer must have a size that falls on a repeating boundary.  When
 * end-of-file is reached, up to 4 extra bytes are needed to crypt
 * any leftover bits.  These definitions make it easy to manage buffer
 * sizes.
 */
#define PRECRYPT_BUFFER_SIZE (31*32*500)
#define ACTUAL_PRECRYPT_BUFFER_SIZE (PRECRYPT_BUFFER_SIZE+4)
#define CRYPTED_BUFFER_SIZE ACTUAL_PRECRYPT_BUFFER_SIZE

/* The following is not an empirical value (the limit is probably higher),
 * but it simply limits the size of the preallocated array to a
 * generously high value.
 */
#define MAX_ARGS_TO_TAR 2048
#define MAX_NAME_SIZE 256
