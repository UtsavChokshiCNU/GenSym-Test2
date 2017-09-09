/* This form of "encryption" (better termed "non-human readable format") is
   almost the same as is used by KB saving and loading.  It encrypts only the
   7-bit (ASCII) and 8-bit (Latin1) printing characters.

   Codes for 92 (\) and (128 + 92) (Latin 1's Uppercase U Umlaut) are not
   altered.

   It leaves other characters alone, e.g., newline, NUL, 7- and 8-bit control
   characters characters, etc. This makes it suitable for encrypting text files,
   or pseudo text files such G2 KBs. This would be unsuitable for use in the
   unlikely scenario of encrypting a file consisting only of control characters,
   commas (,), or 8-bit characters.

   This differs from the KB form of encryption only in that it handles 8-bit
   characters, whereas that form of encryption does not deal with them, since
   the are never present in KBs. */

/* For changing unix file permissions:  */
#ifndef WIN32
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "obfuscate.h"

/* Don't use __FILE__ here, since we don't want to reveal the source file, which
   would show up in `strings Gensym.dll` !  To do: base this on whether creating
   a debuggable or a release DLL. -mhd */

#define PERROR_RETURN(message)  do {                  \
  fprintf(stderr, "%s at \"%s\":%d: %s\n",            \
      message, "Gensym.c", __LINE__, strerror(errno)); \
  return; } while (0);


static long base_reference;

long derive_base_reference_from_seed_string (const char *seed_string)
{
  int len = strlen((char *)seed_string);
  int i; char c;
  long r = 0;
  
  for (i = 0; i < len; i++) {
    c = seed_string[i];
    /* Consider only alphanumerics, do not consider case: A-Z, 0-9. */
    r = ((r + ((((('a' <= c) && (c <= 'z'))
		 || (('0' <= c) && (c <= '9')))
		? c
		: ((('A' <= c) && (c <= 'Z'))
		   ? (c + ('a' - 'A'))
		   : 0))))
	 % base_modulus);
  }
  return(r);
}

void init_crypt(long initial_base_reference)
{
  base_reference = initial_base_reference;
}

int char_code_crypt(int char_code, int direction)
{
  int saved_8th_bit = 0x80 & char_code;
  int result_code = 0x7f & char_code;

  if ((result_code != 92) && (32 <= result_code) && (result_code <= 126)) {
    base_reference = (((base_reference * 3943) + 3947) % 3967);
    result_code
      = (result_code - ((result_code < 92) ? 32 : 33)) + (direction * base_reference);
    if ((direction == DECRYPT_DIRECTION) && (result_code < 0)) {
      int remainder_result = (result_code * -1) % 94;
      result_code = ((remainder_result == 0)
		     ? remainder_result
		     : (94 - remainder_result));
    }
    else
      result_code = result_code % 94;
    result_code = result_code + ((result_code <= 59) ? 32 : 33);
  }
  result_code = saved_8th_bit | result_code;
  return (result_code);
} 

void crypt_copy_stream_to_eof (FILE *in, FILE *out, int direction)
{
  int getc_result;
  
  while ((getc_result = fgetc(in)) != EOF) {
    unsigned char ch = char_code_crypt((unsigned char)getc_result, direction);
    if (fputc(ch, out) == EOF)
      break;
  }
}

void crypt_file_in_place(char *filename, char *seed_string, int direction)
{
/* For changing unix file permissions:  */
#ifndef WIN32
  struct stat sb;
  mode_t new_mode = 0;
#endif
  FILE *stream;
  unsigned char *buf;
  size_t character_count, i;

/* For changing unix file permissions:  */
#ifndef WIN32
  if (stat(filename, &sb))
    PERROR_RETURN("stat");

  if (!((new_mode = sb.st_mode) & S_IWUSR)) {
    new_mode = sb.st_mode | S_IWUSR;
    if (chmod(filename, new_mode))
      PERROR_RETURN("chmod");
  }
#endif
  
  if ((stream = fopen(filename, "r+b")) == NULL)
    PERROR_RETURN("fopen");

  if (fseek(stream, 0L, SEEK_END) < 0)
    PERROR_RETURN("setting position to end");

  character_count = ftell(stream);

  if (fseek(stream, 0L, SEEK_SET) < 0)
    PERROR_RETURN("setting position to beginning");
  
  if ((buf = (unsigned char *)malloc(sizeof(unsigned char) * character_count)) == NULL)
    PERROR_RETURN("malloc");
  
  if (!fread(buf, sizeof(unsigned char), character_count, stream))
    PERROR_RETURN("fread");
  
  if (fseek(stream, 0L, SEEK_SET) < 0)
    PERROR_RETURN("setting position to beginning");
  
  init_crypt(derive_base_reference_from_seed_string(seed_string));
  
  for (i = 0; i < character_count; i++)
    buf[i] = char_code_crypt(buf[i], direction);
  
  if (!fwrite(buf, sizeof(unsigned char), character_count, stream))
    PERROR_RETURN("fwrite");

  fclose(stream);

/* For changing unix file permissions:  */
#ifndef WIN32
  if (new_mode != sb.st_mode)
    if (chmod(filename, sb.st_mode))
      PERROR_RETURN("chmod");
#endif
}

void set_log_file_info(char *filename, char *seed_string)
{
  crypt_file_in_place(filename, seed_string, DECRYPT_DIRECTION);
}

#ifdef TEST_MAIN
int main (int argc, char *argv[])
{
  set_log_file_info(argv[1], argv[2]);
  return 0;
}
#endif
