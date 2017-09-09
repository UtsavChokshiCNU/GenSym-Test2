#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codes.h"
#include "gsm.h"
#include "family-descriptor.h"

extern void randomize_seed();
extern unsigned int generate_random_nibbles(int);

extern void set_bufptr_for_get_line(unsigned char*);
extern unsigned char read_buf[ACTUAL_PRECRYPT_BUFFER_SIZE];
extern FAMILY_DESCRIPTOR *new_family();
extern int parse_family_file(FAMILY_DESCRIPTOR*);

/* This maps the system name into a well defined integer.
 */
unsigned char translate_system_name(char *system_name)
{
    if (strcmp(system_name,"sparcsol") == 0)
        return (SPARCSOL_CODE);
    else if (strcmp(system_name,"rs6000") == 0)
        return (RS6000_CODE);
    else if (strcmp(system_name,"hpux") == 0)
        return (HPUX_CODE);
    else if (strcmp(system_name,"linux") == 0)
        return (LINUX_CODE);
    else if (strcmp(system_name,"linux64") == 0)
        return (LINUX64_CODE);
    else if (strcmp(system_name,"alphaosf") == 0)
        return (ALPHAOSF_CODE);
    else if (strcmp(system_name,"hpia64") == 0)
        return (HPIA64_CODE);
    else {
        printf("Unrecognized system: %s\n",system_name);
        printf("  It must be sparcsol, rs6000, hpux, hpia64, linux, linux64 or alphaosf\n");
        exit(1);
    }

}
/* Open, encrypt, and write the tar file into the .gsm file.
 */
int read_encrypt_and_write_tar_file(char *tarname,
                                    FILE *gsm_outfile,
                                    unsigned int xor_mask)
{
    unsigned char crypt_buf[ACTUAL_PRECRYPT_BUFFER_SIZE];
    size_t bytes_written;
    size_t bytes_read;
    FILE *fp;

    fp = fopen(tarname,"rb");
    if (fp == NULL) {
        fprintf(stderr,"Could not open %s for reading\n", tarname);
        return TAR_FILE_OPEN;
    }

    initialize_crypt();
    while (!feof(fp)) {
        bytes_read = fread(read_buf, 1, PRECRYPT_BUFFER_SIZE, fp);
        if (bytes_read <= 0) {
            fprintf(stderr,"Error while reading the tar file.\n");
            return FAILURE;
        }
        crypt_buffer(read_buf, crypt_buf, bytes_read,
            xor_mask); /* Encrypt the buffer.*/
        bytes_written = fwrite(crypt_buf, 1, bytes_read, gsm_outfile);
        if (bytes_written != (size_t) bytes_read) {
            fprintf(stderr,"Error while writing the encrypted tar file.\n");
            return FAILURE;
        }
    }
    fclose(fp);
    return SUCCESS;
}

/* Encrypt the family file using the crypt mask, then write it out.
 * When this is called, the family file has already been read and
 * preprocessed to assure that it will match the header.
 *   inputs:
 *     buf and buflen: buffer with unencrypted family file
 *     outfile:  output .gsm file
 *   return value:
 *     SUCCESS or FAILURE (could not write buffer to output file)
 */
int encrypt_and_write_family_file(unsigned char *buf,
                                  int buflen,
                                  FILE *outfile,
                                  unsigned int xor_mask)
{
    unsigned char crypt_buf[ACTUAL_PRECRYPT_BUFFER_SIZE];
    size_t bytes_written;

    initialize_crypt();
    crypt_buffer(buf, crypt_buf, buflen, xor_mask); /* encrypt the buffer */

    bytes_written = fwrite(crypt_buf, 1, buflen, outfile);
    if (bytes_written == (size_t) buflen) {
        return SUCCESS;
    } else {
        fprintf(stderr,"Error while writing the encrypted family file\n");
        return FAILURE;
    }
}

/* This opens the family file and reads it into buf.  It
 * sets the global family_file_length so that it can be used as
 * needed.  It then determines that the file is effectively a single
 * string whose buffer is terminated by \0.
 *   return value:  
 *      positive - number of bytes read
 *      -<error value> - values indicating file errors
 */       
int read_family_file(char *filename, unsigned char *buf, int bufsize)
{
    FILE *fp;
    int bytes_read;

    fp = fopen(filename,"r");
    if (fp == NULL) {
        fprintf(stderr,"Could not open %s for reading\n", filename);
        return -FAMILY_FILE_OPEN;
    }

    bytes_read = fread(buf, 1, bufsize, fp);
    if ( (bytes_read == bufsize)  || !feof(fp) ) {
        fprintf(stderr, "Family file, %s, is too large for buffer\n",
            filename);
        fclose(fp);
        return -FAMILY_FILE_TOO_LONG;
    } else if (ferror(fp)) {
        fprintf(stderr, "An error occurred while reading family file %s\n",
            filename);
        return -FAMILY_FILE_OPEN;
    }

    fclose(fp); /* We're done with the file. */

    buf[bytes_read] = '\0';  /* terminate input string */
    if ( (int)strlen((const char *)buf) < (bytes_read - 1) ) {
        fprintf(stderr, "Family file, %s, is not well formed\n", filename);
        return -FAMILY_FILE_INTEGRITY;
    }

    return bytes_read;
}

/* Create the header and write it to the output file.*/

void write_file_header(FILEHEADER header,
                      FILE *outfile)
{
    int i;
    unsigned int mask_buf;
    unsigned char header_bytes[HEADER_LENGTH + 4]; /* extra bytes for xor */

    unpack_bytes(header.magic_number, &header_bytes[MAGIC_NUMBER_INDEX]);
    header_bytes[SYSTEM_ID_INDEX] = header.system_id;
    header_bytes[FAMILY_ID_INDEX] = header.family_id;
    header_bytes[INSTALLER_VERSION_INDEX] = header.installer_version;
    unpack_bytes(header.family_file_length,
        &header_bytes[FAMILY_FILE_LENGTH_INDEX]);
    unpack_bytes((header.crypt_mask)<<1, &header_bytes[CRYPT_MASK_INDEX]);

    /* Encrypt all header bytes except the first four.   Note that the final
     * bytes of header_bytes may be encrypted but not used.
     */
    for (i=1; i<(HEADER_LENGTH+4)/4; i++) {
        mask_buf = pack_bytes(&header_bytes[4*i]);
        unpack_bytes(HEADER_XOR ^ mask_buf, &header_bytes[4*i]);
    }

    for (i=0; i<HEADER_LENGTH; i++) {
        putc(header_bytes[i], outfile);
    }

}

/* Prints the header content in a viewable form.
 */
void print_file_header(FILEHEADER *header)
{
    printf("magic number:       %08x\n",header->magic_number);
    printf("system ID:          %d\n",  header->system_id);
    printf("family ID:          %d\n",  header->family_id);
    printf("installer version:  %d\n",  header->installer_version);
    printf("family file length: %08x\n",header->family_file_length);
    printf("crypt mask:         %08x\n",header->crypt_mask);
    printf("\n");
}

/* Encrypt both the family file and the tarfile, and write
 * the encrypted bits to the output file.
 * The family file and tar file are encrypted separately; i.e., the
 * encryption is restarted for both rather than to make a continous
 * transition from one to the other.  This allows the tarfile to be\
 * read repeatedly if necessary.
 * On entry, all needed files are already opened to assure existence.
 */
int create_gsm_file(unsigned char sysid,
                    char *family_filename,
                    char *tarfilename,
                    char *gsmfile)
{
    FILEHEADER header;
    FILE *outfile;
    FAMILY_DESCRIPTOR *family_desc;

    int ff_length;
    int status;

    outfile = fopen(gsmfile,"wb");
    if (outfile == NULL) {
        printf("Failed to open output file, %s, for writing\n", gsmfile);
        exit(1);
    };
    
    ff_length = read_family_file(family_filename,
        read_buf, PRECRYPT_BUFFER_SIZE);

    if (ff_length < 0) {
        fprintf(stderr,"Error processing family file.  Exiting.\n");
        exit(1);
    }
    
    set_bufptr_for_get_line(read_buf);

    /* Process family file to get family_id, installer version, etc.*/
    family_desc = new_family();
    status = parse_family_file(family_desc);
    if (status != SUCCESS) {
        fprintf(stderr,"Parsing error while processing family file. Please\n");
        fprintf(stderr,"notify manager of family file.  Exiting.\n");
        exit(1);
    }

    randomize_seed();

    header.magic_number = GENSYM_MAGIC_NUMBER;
    header.installer_version = INSTALLER_VERSION;
    header.family_id = (unsigned char)family_desc->fd_id;
    header.system_id = sysid;
    
    header.crypt_mask = generate_random_nibbles(8) & 0x7fffffff; /* 31 bits */
    header.family_file_length = ff_length;

    write_file_header(header, outfile);

    status = encrypt_and_write_family_file(read_buf,
        ff_length,
        outfile,
        header.crypt_mask);

    if (status != SUCCESS) {
        fprintf(stderr,"Error writing family file to gsm file. Exiting.\n");
        exit(1);
    }

    status = read_encrypt_and_write_tar_file(tarfilename,
        outfile, header.crypt_mask);

    if (status != SUCCESS) {
        fprintf(stderr,"Error writing tar file to gsm file. Exiting.\n");
        exit(1);
    }

    fclose (outfile);

    return(0);
}

/* This function is for testing only.  It reads, decrypts and writes the
 * .gsm embedded tar file to tarname.  The written file can then be compared
 * to the original, which should be identical.
 */
int read_decrypt_and_write_gsm_tar_file (FILE *infile,
                                         unsigned int xor_mask,
                                         char *tarname)
{
    unsigned char crypt_buf[ACTUAL_PRECRYPT_BUFFER_SIZE];
    FILE *fp;
    int bytes_read, bytes_written;

    fp = fopen(tarname,"wb");
    if (fp == NULL) {
        fprintf(stderr,"Could not open %s for writing\n", tarname);
        exit(1);
    }

    initialize_crypt();
    while (!feof(infile)) {
        bytes_read = fread(read_buf, 1, PRECRYPT_BUFFER_SIZE, infile);
        if (bytes_read <= 0) {
            fprintf(stderr,"Error while reading tar from the .gsm file.\n");
            exit(1);
        }
        crypt_buffer(read_buf, crypt_buf, bytes_read,
            xor_mask); /* Decrypt the buffer.*/
        bytes_written = fwrite(crypt_buf, 1, bytes_read, fp);
        if (bytes_written != bytes_read) {
            fprintf(stderr,"Error while writing the test tar file.\n");
            exit(1);
        }
    }
    fclose(fp);
    return SUCCESS;
}


/* This is for testing and general utility.  It unpacks the gsm file.
 * The header is printed on the display, and the family file and
 * tar file are written into the specified files.  The family file and
 * tar file should be identical to the originals.
 */
void unbundle (int argc, char *argv[])
{
    FILE *outfile;
    FILE *infile;
    int status;
    FILEHEADER header;
    unsigned char ffbuf[ACTUAL_PRECRYPT_BUFFER_SIZE];

    if (argc != 4) {
        printf("Usage: unbundle <gsm_file> <family_file> <tar_file>\n");
        printf("   gsm_file is input and family and tar files are output\n");
        exit(1);
    }

    infile = fopen(argv[1],"rb");
    if (infile == NULL) {
        printf("Failed to open input file: %s\n", argv[1]);
        exit(1);
    };

    status = read_file_header(&header, infile);
    printf("Header is:\n");
    print_file_header(&header);

    status = read_and_decrypt_gsm_family_file(infile,
        header.family_file_length,
        ffbuf,
        header.crypt_mask);

    if (status != SUCCESS) {
        fprintf(stderr,"Failed to read and decrypt family file");
    }

    /* Write the family file out for comparison. */
    outfile = fopen(argv[2],"wb");
    if (outfile == NULL) {
        printf("Failed to open output file: %s\n", argv[2]);
        exit(1);
    };

    fprintf(outfile,"%s",ffbuf);
    fclose(outfile);

    /* Extract and write the tar file. */
    read_decrypt_and_write_gsm_tar_file(infile, header.crypt_mask, argv[3]);

    fclose(infile);
}

/*  This is the top-level function that creates a bundle. */
void createbundle (int argc, char *argv[])
{
    int status;

    if (argc != 4) {
        printf("Usage: bundle <family_file> <tar_file> <system_name>\n");
        printf("   A file called gensym.gsm is created as output\n");
        exit(1);
    }

    status = create_gsm_file(translate_system_name(argv[3]),
        argv[1], argv[2], "gensym.gsm");
}
