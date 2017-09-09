#ifndef __OBFUSCATE_H
#define __OBFUSCATE_H

/* NOTE ON USE OF A DEVIOUS NAME:

   What we mean: unobfuscate_in_place
   What we use/what strings on our object code reveals : set_log_file_info

   The actual name still appears literally in two other places.  (1)
   set_log_file_info appears literally as the value for POSTINSTALL_OBFUSCATOR
   in ISProject.c; and (2) set_log_file_info appears literally as a prototype
   declaration in the InstallShield Setup.rul function.  */

#ifdef	__cplusplus
extern "C" {
#endif

#define standard_base_reference 27
#define base_modulus 3989
#define DECRYPT_DIRECTION -1
#define ENCRYPT_DIRECTION 1
#define char_code_decrypt(char_code) char_code_crypt(char_code, DECRYPT_DIRECTION)
#define char_code_encrypt(char_code) char_code_crypt(char_code, ENCRYPT_DIRECTION)

long derive_base_reference_from_seed_string(const char *);
void init_crypt(long);
int char_code_crypt(int, int);
void crypt_copy_stream_to_eof (FILE *, FILE *, int);
void crypt_file_in_place(char *, char *, int);

#ifndef WIN32
void set_log_file_info(char *, char *);
#else
__declspec(dllexport) void set_log_file_info(char *, char *);
#endif

#ifdef	__cplusplus
}
#endif

#endif /* __OBFUSCATE_H */

