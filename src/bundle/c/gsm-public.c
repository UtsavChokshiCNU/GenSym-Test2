#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codes.h"
#include "gsm.h"

extern void randomize_seed();
extern unsigned int generate_random_nibbles(int);

unsigned char read_buf[ACTUAL_PRECRYPT_BUFFER_SIZE];
static unsigned char *family_file_bufptr;  /* Needed by get_line() */

/* Translate the system id to a string.   Create and return the string.
 *   Returns:
 *      return_name:  a new string containing the system name
 *      return value:  SUCCESS if sysid is valid, FAILURE if not
 */
int get_system_name(unsigned char sysid, char **return_name)
{
    char *sysnameptr;
    int retval;

    retval = SUCCESS;
    switch(sysid) {
    case INTELNT_CODE:
        sysnameptr = "NT/Windows 2000";
        break;
    case SPARCSOL_CODE:
        sysnameptr = "Solaris";
        break;
    case RS6000_CODE:
        sysnameptr = "AIX";
        break;
    case HPUX_CODE:
        sysnameptr = "PA-RISC HP-UX";
        break;
    case LINUX_CODE:
        sysnameptr = "Linux";
        break;
    case LINUX64_CODE:
        sysnameptr = "Linux x86_64";
        break;
    case ALPHAOSF_CODE:
        sysnameptr = "Alpha/OSF";
        break;
    case HPIA64_CODE:
        sysnameptr = "Itanium HP-UX";
        break;
    default:
        sysnameptr = "unknown system";
        retval = FAILURE;
    }

    *return_name = (char *)malloc(18);
    strcpy(*return_name, sysnameptr);
    return retval;
}

/* Unfortunately the following must be global to allow it to be
 * reset externally. */

static int reset_crypt = 1;

/* Causes crypt() to restart (discarding any partial cryptions)/
 */
void initialize_crypt() {

    reset_crypt = 1;
}

/* Description:
 *   This takes either 3 or 4 bytes as input in an array,
 *   applies the 31-bit XOR to them and returns 3 or 4 xor'd bytes.
 *   Because only 31 bits are XOR'd, this function retains the excess bit(s)
 *   for use in the next XOR operation.
 * Inputs:
 *     inbytes[]: an array of three or four bytes
 * Outputs:
 *     outbytes[]: the xor'd bytes
 *     bytes_needed_next: the number of bytes needed for the next call
 *     return value: the number of bytes processed (either 3 or 4)
 * Notes:
 *   This is amazingly complex for something so conceptually simple.  Some
 *   hints if analzying this:
 *   - The input pattern repeats every 8 bytes.  Calls 1 through 7 need
 *     4 bytes, and call 8 needs only 3.  The first call returns 3
 *     bytes and the remaining 7 calls return 4 bytes.  After 8 calls,
 *     31 bytes have been passed, and 31 have been returned.
 *   - The saved_xored_bits and kept_bits together form the xored byte
 *     that is retained/split between calls.  In successive calls, the
 *     number of saved_xored/kept bits is 0/0, 1/7, 2/6, 3/5, 4/4, 5/3, 6/2,
 *     7/1, then 0/0 again.  The final 0/0 is because only 3 bytes are passed
 *     in the 8th call (the 7/1 call).
 *   - Just in case it's not obvious, using the same xor mask twice
 *     gives back the original value.  Thus,this function is used both
 *     for encrypting and decrypting.
 */

int g2crypt(unsigned char inbytes[],
          unsigned char outbytes[],
          unsigned int xor_mask,
          int *bytes_needed_next) {

   static int total_bits_kept;            /* Values retained */
   static unsigned int kept_bits;         /* from the previous call. */
   static unsigned int saved_xored_bits;

   unsigned int bit_buffer, tmp_buffer;
   int prior_total_bits_kept;
   int current_fill_position;
   int bits_in_last_byte;
   int outbytes_index;
   int i, x;
   
   if (reset_crypt) {
     reset_crypt = 0; 
     total_bits_kept = 0;
     kept_bits = 0;
     saved_xored_bits = 0;
   }

   prior_total_bits_kept = total_bits_kept;  /* Needed after xoring */
   current_fill_position = total_bits_kept;

   /* Fill bit_buffer with the unxored bits, first with the
    * saved, unexored bits, then with the new bytes.  The final
    * byte may be partially used. */

   bit_buffer = kept_bits;    /* 0 if current_fill_position is 0. */
   for (i=0; i<3; i++) {      /* At most 7 bits are "kept", so at least 24 */                         
     tmp_buffer = inbytes[i]; /* more are needed. */
     bit_buffer = bit_buffer | (tmp_buffer << current_fill_position);
     current_fill_position += 8;
   } 

   bits_in_last_byte = 31 - current_fill_position;
   total_bits_kept = (8 - bits_in_last_byte) % 8;   /* For the next call.*/
   if (bits_in_last_byte > 0) { /* Break the last byte if appropriate */
     tmp_buffer = inbytes[3];
     bit_buffer = bit_buffer | ((tmp_buffer << (32 - bits_in_last_byte)) >> 1);
     kept_bits = (inbytes[3] >> bits_in_last_byte); /* For the next call.*/
   } else {
     kept_bits = 0;
   }

   /* Xor the bits. */
   bit_buffer = bit_buffer ^ xor_mask;

   /* Finally we extract the xored bits into the output array.
    * If there are leftover bits from the last call, these are
    * first merged into the l.s. byte.
    */

   x = prior_total_bits_kept; /* x is the bit index */
   outbytes_index = 0;
   if (x > 0) { /* Merge previously xored bits. */
       outbytes[outbytes_index] = ((bit_buffer << (32 - x)) >> 24) | saved_xored_bits;
       outbytes_index++;
   }

   do  {  /* Get as many full bytes as possible. */
     x = x + 8;
     outbytes[outbytes_index] = ((bit_buffer << (32 - x)) >> 24);
     outbytes_index++;
   } while (x + 8 <= 31);

   saved_xored_bits = (bit_buffer >> x);  /* For the next call. */

   *bytes_needed_next = (total_bits_kept == 7) ? 3 : 4;
   return outbytes_index;

}

/* Encrypt the bytes in inbuf into the buffer outbuf.
 * Notes:
 *   inbuf must have at least 4 more bytes than inbuf_count to allow for
 *     encryption of the final byte if it does not fall on an 8-byte boundary.
 *   outbuf must be at least as long as inbuf.
 */
void crypt_buffer(unsigned char *inbuf,
                  unsigned char *outbuf,
                  int inbuf_count,
                  unsigned int xor_mask)
{
    int bytes_to_provide, bytes_provided, count;
    int inbuf_index;
    int outbuf_index;

    bytes_to_provide = 4;
    inbuf_index = 0;
    outbuf_index = 0;
    while (inbuf_index + bytes_to_provide <= inbuf_count) {
        bytes_provided = bytes_to_provide;
        count = g2crypt(inbuf + inbuf_index,
            outbuf + outbuf_index,
            xor_mask,
            &bytes_to_provide);
        inbuf_index += bytes_provided;
        outbuf_index += count;
    }
    /* End game: Flush any remaining bytes into crypted_buffer.  This should
     * only happen at the end of a file because the full-buffer size was set
     * to prevent remaining bytes.
     */
    if (outbuf_index < inbuf_count) {
        count = g2crypt(inbuf + inbuf_index,
            outbuf + outbuf_index,
            xor_mask,
            &bytes_to_provide);
    }
}

/* Sets family_file_bufptr, which is used by get_line to read lines
 * from the family file.
 */
void set_bufptr_for_get_line(unsigned char *ptr)
{
    family_file_bufptr = ptr;
}

/* This reads the encrypted family file from the gsm file, decrypts
 * it, and returns a pointer to the decrypted buffer.  It is assumed
 * that "file_length" is less than the buffer's lengths.
 *   Input:
 *     infile: the gsm file from which the header has already been read
 *     file_length:  number of bytes in family file
 *     crypt_buf:  a buffer into which to decrypt the file
 *     xor_mask: the decryption mask
 *   Return value:
 *     SUCCESS or <file error>
 */
int read_and_decrypt_gsm_family_file (FILE *infile,
                                      int file_length,
                                      unsigned char *crypt_buf,
                                      unsigned int xor_mask)
{
    unsigned char inbuf[ACTUAL_PRECRYPT_BUFFER_SIZE];

    int bytes_read;
    int viable_length;

    bytes_read = fread(inbuf, 1, file_length, infile);
    if (bytes_read != file_length) {
        return EARLY_GSM_EOF;
    }

    /* Decrypt the buffer. */
    initialize_crypt();
    crypt_buffer(inbuf, crypt_buf, file_length, xor_mask);

    crypt_buf[file_length] = '\0';  /* Terminate file as text string. */

    /* Check that the family file really is a string. */
    /* printf("Family file content:\n%s", crypt_buf); */
    
    viable_length = strlen((const char *)crypt_buf);
    if (viable_length != file_length) {
        return FAMILY_FILE_INTEGRITY;
    }

    return SUCCESS;
}

/* This is called (only) by the parser to get the next line of
 * characters from the family file buffer.  It is basically fgets
 * applied to the global family file buffer.
 *   globals:
 *     family_file_bufptr: set by read_family_file()
 *   return value:
 *      positive - number of characters in line
 *      0 - end of buffer
 *      <error value> - LINE_TOO_LONG 
 */
int get_line(char *linebuf, int linebufsize)
{
    int len;
    unsigned char c;

    len = 0;
    /* Skip leading blank-line delimiters */
    c = *family_file_bufptr;
    while (c == '\n' || c == '\014') {
        family_file_bufptr++;
        c = *family_file_bufptr;
    }
    /* Copy characters into buffer until end-of-line or end-of-buffer. */
    while (c != '\n' && c != '\014') {
        if (c == '\0')
            break;
        if (len >= linebufsize-1) { /* Need room for string terminator. */
            linebuf[linebufsize-1]='\0';
            return LINE_TOO_LONG;
        }
        linebuf[len++] = c;
        family_file_bufptr++;
        c = *family_file_bufptr;
    }
    linebuf[len] = '\0';
    return len;
}

/* Treat a 4-byte array as a little endian int.  Pack
 * the bytes and return them.
 */
unsigned int pack_bytes(unsigned char arr[4])
{
    int i;
    unsigned int bitbuf;

    bitbuf = 0;

    /* Pack the bits. */
    for (i=3; i>=0; i--) {
        bitbuf = bitbuf << 8;    /* Does nothing first time through. */
        bitbuf = bitbuf | arr[i];
    }

    return bitbuf;
}

/* The unsigned int is 4 bytes in little endian order.  Unpack
 * them into the array.
 */
void unpack_bytes(unsigned int packed, unsigned char arr[4])
{
    int i;
    for (i=0; i<4; i++) {
        arr[i] = packed & 0xff;
        packed = packed >> 8;
    }
    
}

/* Read the header bytes from the file and do sanity checks on correctness
 * at various stages.
 */
int read_file_header(FILEHEADER *header, FILE *infile)
{
    int i;
    unsigned int mask_buf;
    unsigned char header_bytes[HEADER_LENGTH + 4]; /* extra bytes for xor */
    size_t bytes_read;

    bytes_read = fread(header_bytes, 1, 15, infile);
    if (bytes_read != 15) {
        return EARLY_EOF;
    }

    if ((header->magic_number = pack_bytes(&header_bytes[MAGIC_NUMBER_INDEX]))
        != GENSYM_MAGIC_NUMBER) {
        return BAD_MAGIC_NUMBER;
    }

    /* Decrypt all header bytes except the first four.  Note that
     * header_bytes[15] is decrypted but not used.
     */
    for (i=1; i<(HEADER_LENGTH+4)/4; i++) {
        mask_buf = pack_bytes(&header_bytes[4*i]);
        unpack_bytes(HEADER_XOR ^ mask_buf, &header_bytes[4*i]);
    }

    /* Populate the header structure */
    header->system_id = header_bytes[SYSTEM_ID_INDEX];
    header->family_id = header_bytes[FAMILY_ID_INDEX];
    header->installer_version = header_bytes[INSTALLER_VERSION_INDEX];
    header->family_file_length
        = pack_bytes(&header_bytes[FAMILY_FILE_LENGTH_INDEX]);
    header->crypt_mask = pack_bytes(&header_bytes[CRYPT_MASK_INDEX]) >> 1;

    return SUCCESS;
}
