/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      cstreams.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Ong, Peng Tsin
 +
 + Description: This module contains stream-related C functions
 +
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +   ??????? Function existence is questionable.
 +
 +   A function banner may contain the following:
 +      Multiply Defined    Function appears multiple times, each definition
 +                          for an #ifdef specified platform.
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      FUNCTION GROUP - Stream Functions
 +      g2ext_g2_stream_open ()             0000000
 +      g2ext_g2_stream_open_s16 ()         0000000
 +      g2ext_str_close ()                  0000000
 +      g2ext_str_read_char ()              0000000
 +      g2ext_str_read_non_cr_char ()       0000000
 +      g2ext_g2_stream_read_string ()      0000000
 +      g2ext_str_write_char ()             0000000
 +      g2ext_str_write_string ()           0000000
 +      g2ext_g2_stream_write_buffer ()     0000000
 +      g2ext_g2_stream_write_wide_buffer ()         0000000
 +      g2ext_str_flush ()                  0000000
 +      g2ext_str_sync()                    0000000
 +      g2ext_str_file_length ()            0000000
 +      g2ext_str_file_non_empty ()         0000000
 +      g2ext_str_get_file_position()       0000000
 +      g2ext_str_set_file_position()       0000000
 +      g2ext_str_flip_bidir_mode() 0000000
 +      g2ext_str_eof_p()                   0000000
 +
 +   Section:      FUNCTION GROUP - Directory Functions
 +      g2ext_str_get_default_dir()         0000000 Mixed Ifdefs
 +      g2ext_str_change_default_dir()      0000000 Multiply Defined
 +      g2ext_str_directory_p()             0000000 Multiply Defined
 +      g2ext_str_initdir()                 0000000 Mixed Ifdefs
 +      g2ext_str_opendir()                 0000000 Multiply Defined
 +      g2ext_str_closedir()                0000000 Mixed Ifdefs
 +      g2ext_str_readdir_filtered()        1111111 Multiply Defined
 +      g2ext_str_readdir()                 0000000
 +      g2ext_str_read_subdirs()            0000000
 +
 +   Section:      FUNCTION GROUP - Logical Device Functions
 +      g2ext_str_open_device_list()        0000000 Multiply Defined
 +      g2ext_str_get_next_device()         0000000 Multiply Defined
 *
 +   Section:      FUNCTION GROUP - File Functions
 +      g2ext_str_rename_file()             0000000 Multiply Defined
 +      g2ext_str_rename_file_s16()         0000000 Multiply Defined
 +      g2ext_str_copy_file()		    0000000 Multiply Defined
 +      g2ext_str_copy_file_s16()	    0000000 Multiply Defined
 +      g2ext_str_file_timestamp()          0000000
 +      g2ext_str_get_version()             0000000 Multiply Defined
 +      g2ext_str_get_device()              0000000 Multiply Defined
 +      g2ext_str_delete_file()             0000000 Mixed Ifdefs
 +      g2ext_str_delete_file_s16()         0000000 Mixed Ifdefs
 +
 +   Section:      FUNCTION GROUP - File System Info Functions
 +      g2ext_str_avail_disk_space()        0000000 Multiply Defined
 +      g2ext_str_logical_name_p()          0000000 Multiply Defined
 +      g2ext_str_max_filename()            0000000 Mixed Ifdefs
 +      g2ext_g2_stream_get_error_number ()          0000000 Mixed Ifdefs
 +
 + External Interface:
 +      long g2ext_g2_stream_open (pathname_string, open_mode)
 +                 Opens a file in the specified mode.
 +
 +      long g2ext_str_close (stream_index)
 +                 Close a specified stream.
 +
 +      long g2ext_str_read_char (stream_index)
 +                 Reads a char from the specified stream.
 +
 +      long g2ext_str_read_non_cr_char (stream_index)
 +                 Reads character from file that uses {\r\n} or
 +                 {\n\r} to separate lines
 +
 +      long g2ext_g2_stream_read_string (stream_index, string,
 +                                  number_of_characters, start_index)
 +                 Read chars from stream into buffer.
 +
 +      long g2ext_str_write_char (character, stream_index)
 +                 Write a single char to the given stream
 +
 +      long g2ext_str_write_string (string, stream_index, write_newline_p)
 +                 Write string to stream with conditional newline.
 +
 +      long g2ext_g2_stream_write_buffer (stream_index, buffer,
 +                                   number_of_characters, start_index)
 +                 Write given number of chars from buffer to stream.
 *
 +      long g2ext_g2_stream_write_wide_buffer (stream_index, buffer,
 +                                        number_of_characters, start_index)
 +                 Write given number of unsigned shorts from buffer to stream.
 +
 +      long g2ext_str_flush (stream_index)
 +                 Flush a given stream.
 +
 +      long g2ext_str_sync(stream_index)
 +                 Ensure output stream is written to disk.
 +
 +      long g2ext_str_file_length (stream_index)
 +                 Determine length of file (in bytes).
 *
 +      long g2ext_str_file_non_empty (stream_index)
 +                 Determine whether file is or is not zero-length
 +
 +      long g2ext_str_get_file_position (stream_index)
 +                 Returns current file position (byte offset from beginning.)
 +
 +      long g2ext_str_set_file_position (stream_index, new_position,
 +                                                 seek_mode)
 +                 Set file position to offset from given position
 +
 +      long g2ext_str_flip_bidir_mode (stream_index)
 +                 Called between read/write accesses on a stream.
 +
 +      long g2ext_str_eof_p (stream_index)
 +                 Indicate whether stream pointer has reached EOF.
 +
 +      long g2ext_str_get_default_dir(buff)
 +                 Gets the current working directory name.
 +
 +      long g2ext_str_change_default_dir (new_directory)
 +                 Change cwd to specified dir.
 +
 +      long g2ext_str_directory_p(fname)
 +                 Determine whether given file/pathname is a directory.
 +
 +      long  g2ext_str_initdir()
 +                 Initialize the reusable data structures used to read
 +                 the directory.
 +
 +      long g2ext_str_opendir(dirspec, filespec)
 +                 Sets up the search structures to find files in the
 +                 named directory
 +
 +      long  g2ext_str_closedir()
 +                 Cleans up the interface to the directory.
 +
 +      long g2ext_str_readdir_filtered(buff,dirs_only_p,include_version_p,include_unreadable_p)
 +                 TBA
 +
 +      long g2ext_str_readdir(buff, include_version_p)
 +                 Writes the next filename into string buffer
 +
 +      long g2ext_str_read_subdirs(buff, include_version_p)
 +                 TBA
 +
 +      long g2ext_str_open_device_list()
 *                 Initializes list of logical device names
 *
 +      long g2ext_str_get_next_device(buff)
 *                 Gets name of next available logical device
 *
 +      long  g2ext_str_rename_file(old_filename, new_filename)
 +                 Change the name of a file.
 +
 +      long  g2ext_str_copy_file(old_filename, new_filename)
 +                 Copy a file.
 +
 +      long  g2ext_str_file_timestamp(fname, mode)
 +                 Get specified timestamp for a file.
 +
 +      long g2ext_str_get_version(filespec)
 +                 Gets file version number (VMS only, all others no-op)
 +
 +      long g2ext_str_get_device(filespec, buff)
 +                 Gets file device name (VMS only, all others no-op)
 +
 +      long  g2ext_str_delete_file(filename)
 +                 Delete the specified file.
 +
 +      Gensym_Long g2ext_str_avail_disk_space(dirstring)
 +                 Returns available disk space value.
 +
 +      long g2ext_str_logical_name_p(buffer)
 +                 Gets value of a system logical name. VMS only,others no-op.
 +
 +      long  g2ext_str_max_filename(dirname)
 +                 Get filename length restrictions for a given path.
 +
 +      long g2ext_g2_stream_get_error_number ()
 +                 Return current value of errno
 +
 + Dependencies:
 +   g2ext_map_g2pointer_to_cpointer()
 +
 + Notes:
 *
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   01/14/94,mpc: Structural reorganization to improve code legibility,
 +                portability, and maintainability.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <limits.h>
#include "cprim.h"

         /***** Included by ALL platforms *****/
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <fcntl.h>
#include <assert.h> 

         /***** These are included by WIN32 platforms *****/
#if defined(WIN32)
#    include <windef.h>
#    include <winbase.h>
#    include <direct.h>
#endif

         /***** These are included by unix platforms *****/
#ifdef unix

#   include <unistd.h>  /* For g2ext_str_max_filename() and getgroups(). */
#   include <dirent.h>

#   if defined(Platform_Solaris) || defined(Platform_Linux)
#       include <sys/statvfs.h>
#   endif

#   if defined(_IBMR2) || defined(sgi) || defined(linux)
#       include <sys/statfs.h>
#   endif

#   if defined (__hpux)
#       include <sys/vfs.h>
#   endif

#   if defined(__osf__) || defined(__APPLE__)
#       include <sys/param.h>
#       include <sys/mount.h>
#   endif

#endif /* unix */

#include "common_config.h"

extern long g2ext_g2_stream_get_error_number(/* void */);
extern long g2ext_str_eof_p(/* long */);
extern long g2ext_str_close(/* long */);
extern long g2ext_str_flush(/* long */);
extern long g2ext_str_sync(/* long */);
extern long g2ext_g2_stream_open(/* char *, long */);
extern long g2ext_g2_stream_open_s16(/* g2chr16_t *, long */);
extern long g2ext_str_flip_bidir_mode(/* long */);
extern long g2ext_str_read_char(/* long */);
extern long g2ext_str_read_non_cr_char(/* long */);
extern long g2ext_g2_stream_read_string(/* long, char *, long, long */);
extern long g2ext_str_write_char(/* long, char * */);
extern long g2ext_str_write_string(/* char *, long, long */);
extern long g2ext_g2_stream_write_buffer(/* long, char *, long, long */);
extern long g2ext_str_delete_file(/* char */);
extern long g2ext_str_delete_file_s16(/* g2chr16_t */);
extern long g2ext_str_rename_file(/* char *, char * */);
extern long g2ext_str_rename_file_s16(/* g2chr16_t *, g2chr16_t * */);
extern long g2ext_str_copy_file(/* char *, char * */);
extern long g2ext_str_copy_file_s16(/* g2chr16_t *, g2chr16_t * */);
extern long g2ext_str_initdir(/* void */);
extern long g2ext_str_opendir(/* char *, char * */);
extern long g2ext_str_closedir(/* void */);
extern long g2ext_str_readdir(/* char *, long, long */);
extern long g2ext_str_read_subdirs(/* char *, long */);
extern long g2ext_str_directory_p(/* char * */);
extern long g2ext_str_file_access_check(/* char *, long */);
extern long g2ext_str_get_default_dir(/* char * */);
extern long g2ext_str_change_default_dir(/* char */);
extern long g2ext_str_file_length(/* long */);
extern long g2ext_str_file_non_empty(/* long */);
extern long g2ext_str_set_file_position(/* long, long, long */);
extern long g2ext_str_get_file_position(/* long */);
extern long g2ext_str_get_version(/* char */);
extern long g2ext_str_get_device(/* char *, char * */);
extern Gensym_Long g2ext_str_avail_disk_space(/* char * */);
extern double g2ext_str_file_timestamp(/* char *, long */);
extern long g2ext_str_logical_name_p(/* char * */);
extern long g2ext_str_max_filename(/* char * */);

extern void g2ext_unset_too_many_fds();
extern Gensym_Long g2ext_g2_clock_ticks();
extern long g2ext_g2_clock_ticks_per_second();
extern long g2ext_sys_sleep();
extern int g2ext_save_backtrace_into_array();


extern int g2ext_too_many_fds;


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define MAX_DIR_SIZE 255

#define MAX_DEVICE_SIZE 255

#define ERROR_CREATING_DISK_QUERY -10L

#ifndef SEEK_SET
#   define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#   define SEEK_CUR 1
#endif

#ifndef SEEK_END
#  define SEEK_END 2
#endif


#define NOTICE_FD_CLOSE() if(g2ext_too_many_fds)g2ext_unset_too_many_fds()

#if defined(WIN32)
#   ifndef S_ISDIR
#      define S_ISDIR(M) ((M & S_IFMT) == S_IFDIR)
#   endif
#endif

#define NO_ERROR_CODE 0
#define NO_FILENAME_LIMIT 0
#define PATHCONF_FAILURE_OR_NO_LIMIT -1
#define FILENAME_LIMIT_GOT_NON_DIR -2
#define ERROR_GETTING_FILENAME_LIMIT -1

#if defined(unix)
   DIR    *g2ext_dir_structure;
#else
#  if defined(WIN32)
      HANDLE  g2ext_dir_structure;
#  endif
#endif

#define TICK_MASK 0x7fffffffL

#define DEFAULT_FILE_OPERATION_TIMEOUT "0.020"

#define MS_TO_SLEEP_BEFORE_COPY_FOR_RENAME 25

#define GET_LOGICAL_DRIVES_FAILURE 0


#ifndef ETIMEDOUT
#define ETIMEDOUT EINTR
#endif
#ifndef ERESTART
#define ERESTART EINTR
#endif

#define RESTARTABLE_ERROR(errno) (errno == EINTR || errno == ETIMEDOUT || errno == ERESTART)

/* The macro ENSURE_NORMAL_UCS_2_BYTE_ORDER (dst, wide_string, length) returns
   a pointer to (2 X length) octets (char's) in memory that are equivalent
   to wide_string, but appear in normal UCS-2 byte order when
   looked at as a series of octets (= char's, bytes, 8-bit entities, etc.).

   (Note that the code below, a, b, and c are substituted as variable names
   for dst, wide_string, and length, respectively.)

   This is a noop on big-endian platforms, and a relatively costly
   operation on little-endian platforms.  It just returns wide_string in
   this case.

   On little-endian platforms, it copies length characters from wide_string
   into dst, which should point to enough available memory, with the
   big-endian byte order.

   This is intended for use with Unicode "wide strings", which are represented
   as (unsigned short *) arrays.  The term "UCS-2" is from Unicode/ISO-10646
   terminology and means Universal Character Set 2-octet format.

   (MHD 6/12/97)
*/
#if !BIG_ENDIAN_P
#  define ENSURE_NORMAL_UCS_2_BYTE_ORDER(a,b,c)  (char *)ucs_2_byte_swap((char *)a,(char *)b,(c << 1))
#  define REQUIRES_SWAP_FOR_NORMAL_UCS_2_BYTE_ORDER 1
#else
#  define ENSURE_NORMAL_UCS_2_BYTE_ORDER(a,b,c)  (char *)(b)
#  define REQUIRES_SWAP_FOR_NORMAL_UCS_2_BYTE_ORDER 0
#endif

#define WIDE_STRING_BUFFER_CHUNK_SIZE 1024



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
char g2ext_dir_buff[256];
long g2ext_dirname_length;

long g2ext_file_operation_retry_count = 0;
long g2ext_file_operation_interrupt_count = 0;
long g2ext_file_operation_retry_timeout = 0;
static int file_operation_retry_timeout_check_environment = TRUE;

static int debug_file_errors_do_env_check = TRUE;
static int debug_file_errors_do_debug = FALSE;

static unsigned short wide_string_buffer_chunk[WIDE_STRING_BUFFER_CHUNK_SIZE];


#ifdef WIN32
static DWORD current_device_list;
static DWORD current_device_list_mask;
static long current_device_list_index;
static char win32_device_names[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char global_last_filename[MAX_PATH];
#endif



#if defined(WIN32)
     typedef WIN32_FIND_DATA dir_entry_type;
#  define dir_entry_filename(dir_entry) ((dir_entry).cFileName)
#else
     typedef struct dirent dir_entry_type;
#  define dir_entry_filename(dir_entry) ((dir_entry).d_name)
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Stream Functions
 %
 % Description:
 %      These functions perform actions on streams
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * char *ucs_2_byte_swap(char *dst, char *src, long len)
 *
 *   Input Arguments:
 *     dst: destination address to copy to.
 *     src: Source address to copy from
 *     len: length of buffer to byte swap
 *   Returns:
 *     return value:
 *   Notes:
 *     Assumes len is even.
 *****************************************************************************/
#if !BIG_ENDIAN_P
static char *ucs_2_byte_swap (dst, src, len)
     char *dst;
     char *src;
     long len;
{
    char *dst_ptr, *src_ptr, c1, c2;
    long pos = 0;

    src_ptr = src;
    dst_ptr = dst;
    while (pos < len) {
        c1 = *src_ptr;
        c2 = *(src_ptr + 1);
        *dst_ptr = c2;
        *(dst_ptr+1) = c1;
        dst_ptr = dst_ptr + 2;
        src_ptr = src_ptr + 2;
        pos = pos + 2;
    }
    return (dst);
}
#endif


static void log_file_error(long number, FILE *f, char const* name, long retry)
{
    long i;
    void *bt[7];
    long count = g2ext_save_backtrace_into_array(bt, sizeof bt/sizeof bt[0], 1);
    if (retry) {
        printf("(errno=%ld) ", number);
    }
    else {
        printf(" errno=%ld  ", number);
    }
    if (f != NULL) {
        printf("fd=%d ", fileno(f));
    }
    if (name) {
        printf("name=\"%s\" ",name);
    }
    for (i = 0; i < count; ++i) {
        printf(" %p", bt[i]);
    }
    puts("");

    fflush(stdout);
}

static void log_file_error_s16(long number, FILE *f, g2chr16_t const* name, long retry)
{
    long i;
    void *bt[7];
    long count = g2ext_save_backtrace_into_array(bt, sizeof bt/sizeof bt[0], 1);
    if (retry) {
        printf("(errno=%ld) ", number);
    }
    else {
        printf(" errno=%ld  ", number);
    }
    if (f != NULL) {
        printf("fd=%d ", fileno(f));
    }
    if (name) {
        char *s = g2_s16dup2mbs(name);
        if (s != NULL) {
            printf("name='%s' ", s);
            free(s);
        }
        else {
            printf("name=??? ");
        }
    }
    for (i = 0; i < count; ++i) {
        printf(" %p", bt[i]);
    }
    puts("");

    fflush(stdout);
}

static int debug_file_errors()
{
  if (debug_file_errors_do_env_check) {
    char *value = getenv("G2_TRACE_FILE_OPERATION_ERRORS");
    debug_file_errors_do_debug = value != 0;
    debug_file_errors_do_env_check = FALSE;
  }
  return debug_file_errors_do_debug;
}

long g2ext_set_file_operation_retry_timeout(value)
  char *value;
{
  long milliseconds = (long)(atof(value) * 1000.0);

  if (milliseconds < 0)
    g2ext_file_operation_retry_timeout = -1;
  else
    g2ext_file_operation_retry_timeout = (g2ext_g2_clock_ticks_per_second() * milliseconds + 999)/1000;
  file_operation_retry_timeout_check_environment = FALSE;
  return 0;
}

long g2ext_get_file_operation_retry_timeout()
{
  if (file_operation_retry_timeout_check_environment) {
    char *value = getenv("G2_FILE_OPERATION_TIMEOUT");
    g2ext_set_file_operation_retry_timeout(value?value:DEFAULT_FILE_OPERATION_TIMEOUT);
  }
  return g2ext_file_operation_retry_timeout;
}

long g2ext_retry_file_operation(
    long (*function)(FILE*, char*, void*, void*),
    FILE* stream_arg,
    char* name_arg,
    void* arg3,
    void* arg4
    )
{
    long first_retry_time_in_ticks = 0;
    int first_call = TRUE;
    long success = FALSE;
    long last_retry_errno = 0;
    const long timeout = g2ext_get_file_operation_retry_timeout();

    for (;;) {
        errno = 0;
        success = (*function)(stream_arg, name_arg, arg3, arg4);
        if (success || !RESTARTABLE_ERROR(errno) || (timeout == 0)) {
            break;
        }
        if (timeout >= 0) {
            if (first_call) {
                first_call = FALSE;
                first_retry_time_in_ticks = g2ext_g2_clock_ticks(TICK_MASK);
            }
            else if (timeout <= (TICK_MASK & (g2ext_g2_clock_ticks(TICK_MASK) - first_retry_time_in_ticks))) {
                break;
            }
        }
        if ((errno != last_retry_errno) && debug_file_errors()) {
            log_file_error(errno, stream_arg, name_arg, TRUE);
        }
        last_retry_errno = errno;
        ++g2ext_file_operation_retry_count;
        g2ext_sys_sleep(10L);
    }

    if (!success && (errno != 0)) {
        if (debug_file_errors()) {
            log_file_error(errno, stream_arg, name_arg, FALSE);
        }
        if (RESTARTABLE_ERROR(errno)) {
            ++g2ext_file_operation_interrupt_count;
        }
    }
    return success;
}

long g2ext_retry_file_operation_s16(
    long (*function)(FILE*, g2chr16_t*, void*, void*),
    FILE *stream_arg,
    g2chr16_t *name_arg,
    void *arg3,
    void *arg4
    )
{
    long first_retry_time_in_ticks = 0;
    int first_call = TRUE;
    long success = FALSE;
    long last_retry_errno = 0;
    const long timeout = g2ext_get_file_operation_retry_timeout();

    for (;;) {
        errno = 0;
        success = (*function)(stream_arg, name_arg, arg3, arg4);
        if (success || !RESTARTABLE_ERROR(errno) || (timeout == 0)) {
            break;
        }
        if (timeout >= 0) {
            if (first_call) {
                first_call = FALSE;
                first_retry_time_in_ticks = g2ext_g2_clock_ticks(TICK_MASK);
            }
            else if (timeout <= (TICK_MASK & (g2ext_g2_clock_ticks(TICK_MASK) - first_retry_time_in_ticks))) {
                break;
            }
        }
        if ((errno != last_retry_errno) && debug_file_errors()) {
            log_file_error_s16(errno, stream_arg, name_arg, TRUE);
        }
        last_retry_errno = errno;
        ++g2ext_file_operation_retry_count;
        g2ext_sys_sleep(10L);
    }

    if (!success && (errno != 0)) {
        if (debug_file_errors()) {
            log_file_error_s16(errno, stream_arg, name_arg, FALSE);
        }
        if (RESTARTABLE_ERROR(errno)) {
            ++g2ext_file_operation_interrupt_count;
        }
    }
    return success;
}

/** Checks for the existence of a file @p name. Other arguments are
    ignored - they exist because this is used as a callback.

    @return 1 if file exists, 0 otherwise
*/
static long probe_file_s16(FILE *stream, g2chr16_t* name, void *a3, void *a4)
{
    int result;

    if (*name == 0) {
        return 0L;
    }
#ifdef WIN32
    {
        struct _stat stat_buffer;
        g2chr16_t dirseps[] = { '\\', '/', '\0' };
        size_t length = g2pvt_s16len(name);
        if (g2pvt_s16chr(dirseps, name[length-1]) != NULL) {
            g2chr16_t *chomped = g2pvt_dup_chomps16_ex(name, length, dirseps);
            if (NULL == chomped) {
                return 0L;
            }
            result = _wstat(chomped, &stat_buffer);
            free(chomped);
        }
        else {
            result = _wstat(name, &stat_buffer);
        }
        return (result != 0) ? 0L : !S_ISDIR(stat_buffer.st_mode);
    }
#else
    {
        struct stat stat_buffer;
        char *s = g2_s16dup2mbs(name);
        if (NULL == s) {
            return 0L;
        }
        result = stat(s, &stat_buffer);
        free(s);

        return !result;
    }
#endif
}

/** Checks for the existence of a file @p name. Other arguments are
    ignored - they exist because this is used as a callback.

    @return 1 if file exists, 0 otherwise
*/
static long probe_file(FILE *stream, char* name, void *a3, void *a4)
{
    int result;

    if (*name == 0) {
        return 0L;
    }
#ifdef WIN32
    {
        struct _stat stat_buffer;
        char dirseps[] = { '\\', '/', '\0' };
	
        size_t length = strlen(name);
        if (strchr(dirseps, name[length-1]) != NULL) {
            char *chomped = g2pvt_dup_chomp_ex(name, length, dirseps);
            if (NULL == chomped) {
                return 0L;
            }
            result = _stat(chomped, &stat_buffer);
            free(chomped);
        }
        else {
            result = _stat(name, &stat_buffer);
        }
        return (result != 0) ? 0L : !S_ISDIR(stat_buffer.st_mode);
    }
#else
    {
        struct stat stat_buffer;
        return !stat(name, &stat_buffer);
    }
#endif
}

long g2ext_g2_probe_file(char *pathname)
{
  if (g2ext_retry_file_operation(probe_file, (FILE *) NULL, pathname, NULL, NULL))
  {
    return SUCCESS;
  }
  else
  {	  
    return FAILURE;
  }
}

long g2ext_g2_probe_file_s16(g2chr16_t *pathname)
{
  if (g2ext_retry_file_operation_s16(probe_file_s16, NULL, pathname, NULL, NULL))
  {
    return SUCCESS;
  }
  else
  {	  
    return FAILURE;
  }
}

/*****************************************************************************
 * long g2ext_g2_stream_open (pathname_string, open_mode)
 *
 *   Description:
 *     Opens a file in the specified mode.
 *   Input Arguments:
 *     pathname_string:  A vaild file pathname
 *     open_mode:        0 - Read, 1 - Write, 2 - Append, 3 - Read/Write
 *             binary:   4 - Read, 5 - Write, 6 - Append, 7 - Read/Write
 *   Returns:
 *     return value: (long) valid stream pointer or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
static long g2_stream_open_1 (stream_arg, pathname_string, stream_ptr, fopen_mode)
  FILE *stream_arg;
  char *pathname_string;
  FILE **stream_ptr;
  char *fopen_mode;
{
  return 0 != (*stream_ptr = GFOPEN(pathname_string, fopen_mode));
}

long g2ext_g2_stream_open (pathname_string, open_mode)
     char        *pathname_string;
     long           open_mode;
{
  FILE        *stream;
  char  *fopen_mode = 0;

  if (0 == strlen(pathname_string)) {
    errno = ENOENT;
#ifdef WIN32
    SetLastError(ENOENT);
#endif
    if (debug_file_errors()) {
      log_file_error(errno, NULL, pathname_string, FALSE);
    }
    return FAILURE;
  }

  switch (open_mode) {
  case 0: fopen_mode = "r"; break;
  case 1: fopen_mode = "w"; break;
  case 2: fopen_mode = "a"; break;
  case 3: fopen_mode = "r+"; break;
#if defined(WIN32)
  case 4: fopen_mode = "rb"; break;
  case 5: fopen_mode = "wb"; break;
  case 6: fopen_mode = "ab"; break;
  case 7: fopen_mode = "r+b"; break;
#else
  case 4: fopen_mode = "r"; break;
  case 5: fopen_mode = "w"; break;
  case 6: fopen_mode = "a"; break;
  case 7: fopen_mode = "r+"; break;
#endif
  }

  if (g2ext_retry_file_operation(g2_stream_open_1, (FILE *) NULL, pathname_string,
                                 (void *) &stream, fopen_mode)) {
    return g2ext_cache_cpointer((Gensym_Long) stream);
  } else
    return FAILURE;
}

#if defined(WIN32)
static long g2_stream_open_s16 (FILE *stream_arg, g2chr16_t *pathname_string, FILE **stream_ptr, wchar_t *fopen_mode)
{
    return 0 != (*stream_ptr = _wfopen(pathname_string, fopen_mode));
}

long g2ext_g2_stream_open_s16 (g2chr16_t *pathname_string, long open_mode)
{
    FILE *stream;
    wchar_t *fopen_mode = 0;

    if (0 == g2pvt_s16len(pathname_string)) {
        errno = ENOENT;
        SetLastError(ENOENT);

        if (debug_file_errors()) {
		log_file_error_s16(errno, NULL, pathname_string, FALSE);
        }
        return FAILURE;
    }

    switch (open_mode) {
        case 0: fopen_mode = L"r"; break;
        case 1: fopen_mode = L"w"; break;
        case 2: fopen_mode = L"a"; break;
        case 3: fopen_mode = L"r+"; break;
        case 4: fopen_mode = L"rb"; break;
        case 5: fopen_mode = L"wb"; break;
        case 6: fopen_mode = L"ab"; break;
        case 7: fopen_mode = L"r+b"; break;
    }

    assert(fopen_mode != 0);

    if (g2ext_retry_file_operation_s16(g2_stream_open_s16, (FILE *) NULL, pathname_string,
                                        (void *) &stream, fopen_mode)) 
    {
        return g2ext_cache_cpointer((Gensym_Long) stream);
    } 
    else
    {
        return FAILURE;
    }
}
#else
static long g2_stream_open_s16 (FILE *stream_arg, g2chr16_t *pathname_string, FILE **stream_ptr, char *fopen_mode)
{   
    char *mbPathnameString = g2_s16dup2mbs(pathname_string);

    if (NULL == mbPathnameString) {
        return 0L;
    }

    long result = (0 != (*stream_ptr = GFOPEN(mbPathnameString, fopen_mode)));
    free(mbPathnameString);

    return result;
}

long g2ext_g2_stream_open_s16 (g2chr16_t *pathname_string, long open_mode)
{
    FILE *stream;
    char *fopen_mode = 0;
    long result;

    if (0 == g2pvt_s16len(pathname_string)) {
        errno = ENOENT;
        if (debug_file_errors()) {
            log_file_error_s16(errno, NULL, pathname_string, FALSE);
        }

        return FAILURE;
    }

    switch (open_mode) {
        case 0: fopen_mode = "r"; break;
        case 1: fopen_mode = "w"; break;
        case 2: fopen_mode = "a"; break;
        case 3: fopen_mode = "r+"; break;
        case 4: fopen_mode = "r"; break;
        case 5: fopen_mode = "w"; break;
        case 6: fopen_mode = "a"; break;
        case 7: fopen_mode = "r+"; break;
    }

    assert(fopen_mode != 0);

    if (g2ext_retry_file_operation_s16(g2_stream_open_s16, (FILE *) NULL, pathname_string,
                                    (void *) &stream, fopen_mode)) {
        result = g2ext_cache_cpointer((Gensym_Long) stream);
    } 
    else {
        result = FAILURE;
    }

    return result;
}
#endif



/*****************************************************************************
 * long g2ext_str_close (stream_index)
 *
 *   Description:
 *     Close a specified stream.
 *   Input Arguments:
 *     stream_index:  A valid stream pointer
 *   Returns:
 *     return value: (long) 0 on success, EOF if any error was detected
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_close (stream_index)
     long        stream_index;
{
    FILE *stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_index);

    g2ext_decache_g2pointer( stream_index );
    NOTICE_FD_CLOSE();
    return GFCLOSE(stream);
}




/*****************************************************************************
 * long g2ext_str_read_char (stream_index)
 *
 *   Description:
 *     Reads a char from the specified stream.
 *   Input Arguments:
 *     stream_index:  A valid stream pointer
 *   Returns:
 *     return value: (long) character read or FAILURE.
 *   Notes:
 *      Assumes that EOF is not a readable character.
 *   Modifications:
 *
 *****************************************************************************/
static long cc_g2_stream_read_char_1 (stream, name_arg, character_ptr, arg4)
  FILE *stream;
  char *name_arg;
  long *character_ptr;
  void *arg4;
{
  return EOF != (*character_ptr = fgetc(stream));
}

long g2ext_str_read_char (stream_index)
     long        stream_index;
{
  FILE *stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_index);
  long character;

  if (g2ext_retry_file_operation(cc_g2_stream_read_char_1, stream, NULL,
                                 (void *)&character, NULL))
    return character;
  else
    return FAILURE;
}




/*****************************************************************************
 * long g2ext_str_unread_char (char_as_long, stream_index)
 *
 *   Description:
 *     Puts a char back into the specified stream.
 *   Input Arguments:
 *     char_as_long:  A long containing the character to put back
 *     stream_index:  A valid stream pointer
 *   Returns:
 *     return value: SUCCESS or FAILURE.
 *   Notes:
 *     Unreading a character that was not the last one read will fail.
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_unread_char (char_as_long, stream_index)
     long       char_as_long;
     long        stream_index;
{
    FILE   *stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_index);
    int     char_as_int = (int) char_as_long;
    int     ungetc_result;

    ungetc_result = ungetc(char_as_int, stream);

    if (ungetc_result == EOF)
        return ( FAILURE );
    else
        return ( SUCCESS );
}


/*****************************************************************************
 * long g2ext_str_read_non_cr_char (stream_index)
 *
 *   Description:
 *     Reads character from file that uses {\r\n} or {\n\r} to separate lines
 *   Input Arguments:
 *     stream_index:  A valid stream pointer
 *   Returns:
 *     return value: (long) character read or FAILURE
 *   Notes:
 *      Assumes that EOF is not a readable character.
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_read_non_cr_char (stream_index)
     long stream_index;
{
  register long  character;

  character = g2ext_str_read_char(stream_index);

  switch (character) {
  case FAILURE:
    return (FAILURE);
  case '\n':
    if ((character = g2ext_str_read_char(stream_index)) != '\r')
      g2ext_str_unread_char(character, stream_index);
    return ((long) '\n');
  case '\r':
    if ((character = g2ext_str_read_char(stream_index)) == '\n') {
      return ((long) '\n');
    } else {
      g2ext_str_unread_char(character, stream_index);
      return ((long) '\r');
    }
  default:
    return (character);
  }
}




/*****************************************************************************
 * long g2ext_g2_stream_read_string (stream_index, string,
 *                             number_of_characters, start_index)
 *
 *   Description:
 *     Read chars from stream into buffer.
 *   Input Arguments:
 *     stream_index:         A valid stream pointer
 *     string:               Buffer to read into
 *     number_of_characters: Number of chars to read from stream
 *     start_index:          Index in string buffer to place characters
 *   Returns:
 *     string:        If success, will place number_of_characters at buffer
 *                     location start_index.
 *     return value: (long) number of characters read, 0 on EOF or error.
 *   Notes:
 *     Assumes that EOF is not a readable character.
 *   Modifications:
 *
 *****************************************************************************/
static long g2_stream_read_string_1 (stream, name_arg, start_ptr, end)
  FILE *stream;
  char *name_arg;
  char **start_ptr;
  char *end;
{
  char *start = *start_ptr;
  start += fread(start, 1, end - start, stream);
  *start_ptr = start;
  return start == end;
}

long g2ext_g2_stream_read_string (stream_index, string,
                            number_of_characters, start_index)
     long        stream_index;
     char        string[];
     long        number_of_characters;
     long        start_index;
{
  char *start = &string[start_index];
  char *original_start = start;
  char *end = start + number_of_characters;
  FILE *stream = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

  g2ext_retry_file_operation(g2_stream_read_string_1, stream, NULL,
                             (void *)&start, end);
  return start - original_start;
}

/*****************************************************************************
 * long g2ext_g2_stream_read_octets_wide (stream_index, string,
 *                                        number_of_characters, start_index)
 *
 *   Description:
 *     Read chars from stream into a wide-string (unsigned short) buffer.
 *   Input Arguments:
 *     stream_index:         A valid stream pointer
 *     string:               an array of unsigned shorts, the buffer to read into
 *     number_of_characters: Number of chars to read from stream
 *     start_index:          Index in string buffer to place characters
 *   Returns:
 *     string:        If success, will place number_of_characters at buffer
 *                     location start_index.
 *     return value: (long) number of characters read, 0 on EOF or error.
 *   Notes:
 *     Assumes that EOF is not a readable character.
 *   Modifications:
 *
 *****************************************************************************/
static long g2_stream_read_octets_wide_1 (stream, name_arg, start_ptr, end)
  FILE *stream;
  unsigned short *name_arg;
  unsigned short **start_ptr;
  unsigned short *end;
{
  unsigned short *start = *start_ptr;
  unsigned char *start_char = (unsigned char *)start;
  int number_of_bytes_in_buffer = (char *)end - (char *)start;
  int number_of_characters_to_read = number_of_bytes_in_buffer >> 1;
  int number_of_characters_read = fread(start_char, 1, number_of_characters_to_read, stream);
  int i;
  for (i=number_of_characters_read-1; i>=0; i--)
      start[i] = start_char[i];
  start += number_of_characters_read;
  *start_ptr = start;
  return start == end;
}

long g2ext_g2_stream_read_octets_wide (stream_index, string,
                                       number_of_characters, start_index)
     long        stream_index;
     unsigned short        string[];
     long        number_of_characters;
     long        start_index;
{
  unsigned short *start = &string[start_index];
  unsigned short *original_start = start;
  unsigned short *end = start + number_of_characters;
  FILE *stream = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

  g2ext_retry_file_operation(g2_stream_read_octets_wide_1, stream, NULL,
                             (void *)&start, (void *)end);
  return start - original_start;
}



/*****************************************************************************
 * long g2ext_g2_stream_read_wide_buffer (stream_index, wide_string_buffer,
 *                                        number_of_characters, start_index)
 *
 *   Description:
 *     Read given number of chars into wide_string_buffer from stream.
 *   Input Arguments:
 *     stream_index:         A valid stream pointer
 *     wide_string_buffer:  (unsigned short *) wide_string_buffer to read into
 *     number_of_characters: Count of chars to be read.
 *     start_index:          Wide_String_Buffer starting location
 *   Returns:
 *     return value: (long) number of chars read
 *   Notes: - This function always reads from "normal UCS-2" order, i.e., with byte
 *            order as MSB first, LSB second.
 *          - Has some machine-specific behavior for byte-order (encapsulated in
 *            a macro)
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_g2_stream_read_wide_buffer (stream_index, wide_string_buffer,
                                       number_of_16_bit_characters, start_index)
     long             stream_index;
     unsigned short *wide_string_buffer;
     long             number_of_16_bit_characters;
     long             start_index;
{
  int i, size, total = 0;

  for (i = 0; i < number_of_16_bit_characters; i = i + WIDE_STRING_BUFFER_CHUNK_SIZE) {
    size = ((WIDE_STRING_BUFFER_CHUNK_SIZE < (number_of_16_bit_characters - i))
            ? WIDE_STRING_BUFFER_CHUNK_SIZE : (number_of_16_bit_characters - i));
    total
      += g2ext_g2_stream_read_string(stream_index,
                                     (char *) (REQUIRES_SWAP_FOR_NORMAL_UCS_2_BYTE_ORDER?
                                               &wide_string_buffer_chunk[0]:
                                               &wide_string_buffer[start_index + i]),
                                     (size << 1),
                                     0);
    ENSURE_NORMAL_UCS_2_BYTE_ORDER(&wide_string_buffer[start_index + i],
                                   &wide_string_buffer_chunk[0],
                                   size);

  };
  return (total >> 1);                /* Number of wide characters = half of total */
}




/*****************************************************************************
 * long g2ext_str_write_char (character, stream_index)
 *
 *   Description:
 *     Write a single char to the given stream
 *   Input Arguments:
 *     character:     Char to be written
 *     stream_index:  A valid stream pointer
 *   Returns:
 *     return value: (long) value written or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
static long cc_g2_stream_write_char_1 (stream, name_arg, result_ptr, character)
  FILE *stream;
  char *name_arg;
  long *result_ptr;
  long character;
{
  return EOF != (*result_ptr = fputc((int)character, stream));
}

long g2ext_str_write_char (character, stream_index)
     long character;
     long stream_index;
{
  long  result;
  FILE *stream = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

  if (g2ext_retry_file_operation(cc_g2_stream_write_char_1, stream, NULL,
                                 (void *)&result, (void *)character))
    return result;
  else
    return FAILURE;
}




/*****************************************************************************
 * long g2ext_str_write_string (string, stream_index, write_newline_p)
 *
 *   Description:
 *     Write string to stream with conditional newline.
 *   Input Arguments:
 *     string:          Char string to be written
 *     stream_index:    A valid stream pointer
 *     write_newline_p: Boolean flag, non-zero means write a newline to stream
 *   Returns:
 *     return value: (long) number of chars written or EOF on failure
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_g2_stream_write_buffer();

long g2ext_str_write_string (string, stream_index, write_newline_p)
     char *string;
     long stream_index;
     long write_newline_p;
{
  long first_result
    = g2ext_g2_stream_write_buffer (stream_index, string, strlen(string), 0);
  long second_result = 0;

  if (errno == 0 && write_newline_p &&
      (FAILURE != g2ext_str_write_char('\n', stream_index)))
    second_result = 1;

  return first_result + second_result;
}



/*****************************************************************************
 * long g2ext_g2_stream_write_buffer (stream_index, buffer,
 *                              number_of_characters, start_index)
 *
 *   Description:
 *     Write given number of chars from buffer to stream.
 *   Input Arguments:
 *     stream_index:         A valid stream pointer
 *     buffer:               Char buffer to write from
 *     number_of_characters: Count of chars to be written.
 *     start_index:          Buffer starting location
 *   Returns:
 *     return value: (long) number of chars written
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
static long g2_stream_write_buffer_1 (stream, name_arg, start_ptr, end)
  FILE *stream;
  char *name_arg;
  char **start_ptr;
  char *end;
{
  char *start = *start_ptr;
  start += fwrite(start, 1, end - start, stream);
  *start_ptr = start;
  return start == end;
}

long g2ext_g2_stream_write_buffer (stream_index, buffer,
                             number_of_characters, start_index)
     long        stream_index;
     char      *buffer;
     long        number_of_characters;
     long        start_index;
{
  char *start = &buffer[start_index];
  char *original_start = start;
  char *end = start + number_of_characters;
  FILE *stream = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

  g2ext_retry_file_operation(g2_stream_write_buffer_1, stream, NULL,
                             (void *)&start, end);
  return start - original_start;
}




/*****************************************************************************
 * long g2ext_g2_stream_write_wide_buffer (stream_index, wide_string_buffer,
 *                                          number_of_characters, start_index)
 *
 *   Description:
 *     Write given number of chars from wide_string_buffer to stream.
 *   Input Arguments:
 *     stream_index:         A valid stream pointer
 *     wide_string_buffer:  (unsigned short *) wide_string_buffer to write from
 *     number_of_characters: Count of chars to be written.
 *     start_index:          Wide_String_Buffer starting location
 *   Returns:
 *     return value: (long) number of chars written
 *   Notes: - This function always emits in "normal UCS-2" order, i.e., with byte
 *            order as MSB first, LSB second.
 *          - Has some machine-specific behavior for byte-order (encapsulated in
 *            a macro)
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_g2_stream_write_wide_buffer (stream_index, wide_string_buffer,
                                         number_of_16_bit_characters, start_index)
     long             stream_index;
     unsigned short *wide_string_buffer;
     long             number_of_16_bit_characters;
     long             start_index;
{
  int i, size, total = 0;

  for (i = 0; i < number_of_16_bit_characters; i = i + WIDE_STRING_BUFFER_CHUNK_SIZE) {
    size = ((WIDE_STRING_BUFFER_CHUNK_SIZE < (number_of_16_bit_characters - i))
            ? WIDE_STRING_BUFFER_CHUNK_SIZE : (number_of_16_bit_characters - i));
    ENSURE_NORMAL_UCS_2_BYTE_ORDER(&wide_string_buffer_chunk[0],
                                   &wide_string_buffer[start_index + i],
                                   size);
    total
      += g2ext_g2_stream_write_buffer(stream_index,
                                      (char *) (REQUIRES_SWAP_FOR_NORMAL_UCS_2_BYTE_ORDER?
                                                &wide_string_buffer_chunk[0]:
                                                &wide_string_buffer[start_index + i]),
                                      (size << 1),
                                      0);
  };
  return(total >> 1);                /* Number of wide characters = half of total */
}




/*****************************************************************************
 * long g2ext_str_flush (stream_index)
 *
 *   Description:
 *     Flush a given stream.
 *   Input Arguments:
 *     stream_index: A valid stream pointer
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
static long cc_g2_stream_flush_1 (stream, name_arg, arg3, arg4)
  FILE *stream;
  char *name_arg;
  void *arg3;
  void *arg4;
{
  return 0 == fflush(stream);
}

long g2ext_str_flush (stream_index)
     long stream_index;
{
  long stream = g2ext_map_g2pointer_to_cpointer(stream_index);

  if (g2ext_retry_file_operation(cc_g2_stream_flush_1, (FILE *) stream, NULL, NULL, NULL))
    return SUCCESS;
  else
    return FAILURE;
}




/*****************************************************************************
 * long g2ext_str_sync(stream_index)
 *
 *   Description:
 *     Ensure output stream is written to disk.
 *   Input Arguments:
 *     stream_index: A valid stream pointer
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *     4/29/91, jh:  g2_stream_sync makes the best attempt possible to make
 *          sure a file is written to disk.  It is distinct from
 *          g2_stream_flush, which only makes sure that the output buffers are
 *          emptied.  g2_stream_flush makes no guarantee that the contents of
 *          the buffers have ended up on disk.
 *                    The reason behind this distinction is that some UNIXes
 *          use a technique called "delayed write".  With this technique, file
 *          contents are sometimes kept in kernel memory to maximize throughput.
 *          Thus file contents could be lost even though the program thinks it
 *          has flushed everything to disk.
 *     1/11/94, mpc: WIN32 platforms do not have fsync(), so we fflush() as a
 *          safety.
 *   Modifications:
 *
 *****************************************************************************/
#if !defined(WIN32)
static long cc_g2_stream_sync_1 (stream, name_arg, arg3, arg4)
  FILE *stream;
  char *name_arg;
  void *arg3;
  void *arg4;
{
  return 0 == fsync(fileno(stream));
}
#endif


long g2ext_str_sync(stream_index)
     long stream_index;
{
#if defined(WIN32)
  long status = g2ext_str_flush(stream_index);

  return status;
#else
  long stream = g2ext_map_g2pointer_to_cpointer(stream_index);

  if (g2ext_retry_file_operation(cc_g2_stream_sync_1, (FILE *)stream, NULL, NULL, NULL))
    return SUCCESS;
  else
    return FAILURE;
#endif
}


/*****************************************************************************
 * long g2ext_str_file_length (stream_index)
 *
 *   Description:
 *     Determine length of file (in bytes).
 *   Input Arguments:
 *     stream_index: A valid stream pointer
 *   Returns:
 *     return value: (long) Length of file (in bytes) or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_file_length (stream_index)
     long stream_index;
{
    long  old_position;
    long  file_length = FAILURE;
    FILE  *file_descriptor = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

    /* Save current file position.*/
    old_position = ftell(file_descriptor);

    if (fseek(file_descriptor, 0, SEEK_END) == 0) {

        /* Get byte count offset from beginning of file. (length) */
        file_length = ftell(file_descriptor);

        /* Reset file position. */
        fseek(file_descriptor, old_position, SEEK_SET);
    }

    return(file_length);
}


/*****************************************************************************
 * long g2ext_str_file_non_empty (stream_index)
 *
 *   Description:
 *     Return 1 if the file is zero length, 0 if it is longer than zero length,
 *     and FAILURE if an error occurred.  Needed because file length may return
 *     a value greater than 2^29.
 *   Input Arguments:
 *     stream_index: A valid stream pointer
 *   Returns:
 *     return value: As above
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_file_non_empty (stream_index)
  long stream_index;
{
  long length;
  length = g2ext_str_file_length(stream_index);
  if (length > 0)
    return 1;
  else if (length == 0)
    return 0;
  else
    return length; /* Possible error condition return */
}


/*****************************************************************************
 * long g2ext_str_get_file_position (stream_index)
 *
 *   Description:
 *     Returns current file position (as a byte offset from beginning.)
 *   Input Arguments:
 *     stream_index: A valid stream pointer
 *   Returns:
 *     return value: (long) Current file position.
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_get_file_position (stream_index)
     long    stream_index;
{
    long   position;
    FILE   *file_descriptor = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

    /* flush output device before query */
    fseek(file_descriptor, 0L, SEEK_CUR);

    position = ftell(file_descriptor);

    return(position);
}




/*****************************************************************************
 * long g2ext_str_set_file_position (stream_index, new_position, seek_mode)
 *
 *   Description:
 *     Set file position to offset from given position
 *   Input Arguments:
 *     stream_index: A valid stream pointer
 *     new_position: Byte count to offset
 *     seek_mode:    Where to offset from, Beginning, Current, or End
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_set_file_position (stream_index, new_position, seek_mode)
     long stream_index;
     long new_position;
     long seek_mode;
{
    long    seek_result = -1;
    FILE   *file_descriptor = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

    switch (seek_mode) {
    case 0:
        seek_result = fseek(file_descriptor, new_position, SEEK_SET);
        break;

    case 1:
        seek_result = fseek(file_descriptor, new_position, SEEK_CUR);
        break;

    case 2:
        seek_result = fseek(file_descriptor, new_position, SEEK_END);
        break;
    }

    if (seek_result == 0)
        return SUCCESS;
    else
        return FAILURE;
}




/*****************************************************************************
 * long g2ext_str_flip_bidir_mode (stream_index)
 *
 *   Description:
 *     Called between read/write accesses on a stream.
 *   Input Arguments:
 *     stream_index: A valid stream pointer
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *     g2_stream_flip_bidirectional_mode must be called between accesses to a
 *      bidirectional stream which differ in direction, i.e.,between input
 *      operations and output operations or vice versa.  The necessity for this
 *      is mentioned in Harbison & Steele (p 313).  We want it to be as much of
 *      a no-op as possible, though it is still probably too costly to call at
 *      every read-char.
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_flip_bidir_mode (stream_index)
     long     stream_index;
{
    FILE  *file_descriptor = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

    fseek(file_descriptor, 0L, SEEK_CUR);
    return 0L;
}




/*****************************************************************************
 * long g2ext_str_eof_p (stream_index)
 *
 *   Description:
 *     Indicate whether stream pointer has reached EOF.
 *   Input Arguments:
 *     stream_index: A valid stream pointer.
 *   Returns:
 *     return value: (long) 0 if at EOF, non-zero otherwise
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long int g2ext_str_eof_p (stream_index)
  long stream_index;
{
    return ((long) feof((FILE *)g2ext_map_g2pointer_to_cpointer(stream_index)));
}




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Directory Functions
 %
 % Description:
 %      These functions perform actions on directories.
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*****************************************************************************
 * long g2ext_str_get_default_dir(buff)
 *
 *   Description:
 *     Gets the current working directory name.
 *   Input Arguments:
 *     buff:  A char buffer large enough for MAX_DIR_SIZE chars.
 *   Returns:
 *     buff:         On success, contains the cwd string.
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_get_default_dir(buff)
     char     *buff;
{
    char   *result;
#if defined(WIN32)
    char* delimiter = "\\";
#elif defined(unix)
    char* delimiter = "/";
#endif

    result = (char *)getcwd(buff, MAX_DIR_SIZE);

    if (result != (char *) NULL) {
#if defined(WIN32) || defined (unix)
      if (result[strlen(result) -1 ] != *delimiter)
        strcat(result, delimiter);
#endif
       return(SUCCESS);
    } else {
        return(FAILURE);
    }
}


/*****************************************************************************
 * long g2ext_str_change_default_dir (new_directory)
 *
 *   Description:
 *     Change cwd to specified dir.
 *   Input Arguments:
 *     new_directory:  A vaild directory path name.
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *   Modifications:
 *       5/9/97, apahooja: Don't remove a trailing backslash
 *     preceded immediately by ':' as this represents paths of the form "c:\"
 *     implying the top level directory. If the only backslash after ':' is
 *     removed, windows does not recognize it as a valid path. We are also
 *     careful about cases like "\", "\\", etc.
 *       6/10/94, mpc: Made Win32 version of this function due to problems
 *     with chdir() on NT. NT needs double "\" and no trailing "\" in order
 *     to function properly.
 *       12/14/94, mpc: Remove code which replaced "\" with "\\".  It was
 *     not needed and due to the way C interprets "\\", didn't perform as
 *     advertised.
 *****************************************************************************/
#if defined(WIN32)
long g2ext_str_change_default_dir (new_directory)
     char   *new_directory;
{
    char newdir[512], *p;
    int retval;

    strcpy(newdir, new_directory);

    /* Strip off trailing delimiter(s). chdir() does not work with them. */
    for (p = newdir;
         (strlen(p) > 1) && (p[strlen(p)-1] == '\\') && (p[strlen(p)-2] != ':');
         p[strlen(p)-1] = '\0' );

    retval = ((chdir(newdir) == 0)  ?  SUCCESS : FAILURE );

    return (retval);
}
#else
long g2ext_str_change_default_dir (new_directory)
     char   *new_directory;
{
    return ( (chdir(new_directory) == 0)  ?  SUCCESS : FAILURE );
}

#endif


/*****************************************************************************
 * long g2ext_str_directory_p(fname)
 *
 *   Description:
 *     Determine whether given file/pathname is a directory.
 *   Input Arguments:
 *     fname: File pathname
 *   Returns:
 *     return value: (long) 1 if ISDIR, 0 if not, FAILURE on error
 *   Notes:
 *   Modifications:
 *       6/10/94, mpc: Made Win32 version of this function due to problems
 *     with stat() on NT. NT needs no trailing "\" in order to function properly.
 *     2/07, yduJ: Return 0 if path is too long; bug HQ-5449349.
 *****************************************************************************/
#if defined(WIN32)
long g2ext_str_directory_p(char *fname)
{
    long result;
    struct _stat stat_buffer;
    size_t length = strlen(fname);

    if (0 == length) {
        return FAILURE;
    }
    if (strchr("\\/", fname[length-1]) != NULL) {
        char *chomped = g2pvt_dup_chomp_ex(fname, length, "\\/");
        if (NULL == chomped) {
            return FAILURE;
        }
        result = _stat(chomped, &stat_buffer);
        free(chomped);
    }
    else {
        result = _stat(fname, &stat_buffer);
    }
    return (result != 0) ? FAILURE : S_ISDIR(stat_buffer.st_mode);
}
#else
static long cc_g2_stream_directory_p_1 (stream_arg, fname, stat_ptr, arg4)
  FILE *stream_arg;
  char *fname;
  struct stat *stat_ptr;
  void *arg4;
{
  return -1 != stat(fname,stat_ptr);
}

long g2ext_str_directory_p(fname)
     char *fname;
{
  struct stat s;

  if (g2ext_retry_file_operation(cc_g2_stream_directory_p_1, NULL, fname, (void*)&s, NULL))
    return S_ISDIR(s.st_mode) ?  1 : 0L;
  else
    return FAILURE;
}

#endif


/*****************************************************************************
 * long  g2ext_str_initdir()
 *
 *   Description:
 *     Initialize the reusable data structures used to read the directory.
 *   Input Arguments:
 *     none
 *   Returns:
 *     return value: (long) 1L
 *   Notes:
 *     Called once per the life of the process. Currently a NOP in UNIX,
 *       but is necessary in VMS.
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_initdir()
{
  return(1L);
}


/*****************************************************************************
 * long g2ext_str_opendir(dirspec, filespec)
 *
 *   Description:
 *     Sets up the search structures to find files in the named directory
 *   Input Arguments:
 *     dirspec:  A valid directory name string.
 *     filespec: File name pattern to match within the dir.
 *   Returns:
 *     return value: (long) 1L on success, else 0L
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
#if defined (WIN32)
long g2ext_str_opendir(dirspec, filespec)
     char     *dirspec, *filespec;
{
    char            temp_buf[1024];
    WIN32_FIND_DATA fileinfo;

    global_last_filename[0] = 0;
    strcpy(g2ext_dir_buff, dirspec);
    g2ext_dirname_length = strlen(dirspec);

    strcpy(temp_buf, dirspec);
    strcat(temp_buf, filespec);

    /* open directory structure, return 0 for failure */
    g2ext_dir_structure = FindFirstFile(temp_buf, &fileinfo);
    if (g2ext_dir_structure == INVALID_HANDLE_VALUE)
        return(0L);

    if (strcmp(fileinfo.cFileName, ".")) {
      strcpy(global_last_filename, fileinfo.cFileName);
    }
    return(1L);

} /* g2_stream_opendir */

#else /* Unix version */

long g2ext_str_opendir(dirspec, filespec)
     char     *dirspec, *filespec;
{
    strcpy(g2ext_dir_buff, dirspec);
    g2ext_dirname_length = strlen(dirspec);

    /* open directory structure, return 0 for failure */
    g2ext_dir_structure = opendir(dirspec);
    if (g2ext_dir_structure == NULL)
        return(0L);
    return(1L);

} /* g2_stream_opendir */
#endif /* win32 */



/*****************************************************************************
 * long  g2ext_str_closedir()
 *
 *   Description:
 *    Cleans up the interface to the directory.
 *   Input Arguments:
 *     none
 *   Returns:
 *     return value: (long) 1L
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_closedir()
{
#   if defined(WIN32)
        FindClose(g2ext_dir_structure);
#   else
        NOTICE_FD_CLOSE();
        closedir(g2ext_dir_structure);
#   endif

    return(1L);
}

/*****************************************************************************
 * long cc_g2_stream_readdir_filtered_1 (stream_arg, name_arg, dir_entry_ptr, arg4)
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
static long cc_g2_stream_readdir_filtered_1 (stream_arg, name_arg, dir_entry_ptr, arg4)
  FILE *stream_arg;
  char *name_arg;
  dir_entry_type **dir_entry_ptr;
  void *arg4;
{
#if defined(WIN32)
  if (global_last_filename[0]) {
    strcpy((*dir_entry_ptr)->cFileName, global_last_filename);
    global_last_filename[0] = 0;
    return TRUE;
  } else
    return 0 != FindNextFile(g2ext_dir_structure, *dir_entry_ptr);
#else
  return NULL != (*dir_entry_ptr = readdir(g2ext_dir_structure));
#endif
}



/*****************************************************************************
 * long g2ext_str_readdir_filtered(buff, dirs_only_p, include_version_p, include_unreadable_p)
 *
 *   Description:
 *     TBA
 *   Input Arguments:
 *     buff:
 *     dirs_only_p:
 *     include_version_p:
 *   Returns:
 *     return value: (long)
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_readdir_filtered(buff, dirs_only_p, include_version_p, include_unreadable_p)
     char     *buff;
     long     dirs_only_p;
     long     include_version_p; /* ignored */
     long     include_unreadable_p;
{
#if defined(WIN32)
  dir_entry_type dir_entry;
  dir_entry_type *dir_entry_ptr = &dir_entry;
#else
  dir_entry_type *dir_entry_ptr;
#endif
  while (g2ext_retry_file_operation(cc_g2_stream_readdir_filtered_1, (FILE *)NULL,
                                    NULL, (void *) &dir_entry_ptr, NULL)) {
    strcpy(buff, dir_entry_filename(*dir_entry_ptr));
    if (!include_unreadable_p) {
      strcpy(g2ext_dir_buff+g2ext_dirname_length, buff);
      if (1 != g2ext_str_file_access_check(g2ext_dir_buff,0))
        continue;
    }
    if (dirs_only_p) {
      strcpy(g2ext_dir_buff+g2ext_dirname_length, buff);
      if (1 != g2ext_str_directory_p(g2ext_dir_buff))
        continue;
    }
    return (1L);
  }
  return (0L);
}



/*****************************************************************************
 * long g2ext_str_readdir(buff, include_version_p)
 *
 *   Description:
 *     Writes the next filename into string buffer
 *   Input Arguments:
 *     buff:              buffer to hold filename
 *     include_version_p: Flag to request (vms) version info.
 *   Returns:
 *     buff:          Filename string on success
 *     return value: (long)
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_readdir(buff, include_version_p, include_unreadable_p)
     char     *buff;
     long      include_version_p, include_unreadable_p;
{
    return (g2ext_str_readdir_filtered(buff, (long)0, include_version_p, include_unreadable_p));
}




/*****************************************************************************
 * long g2ext_str_read_subdirs(buff, include_version_p)
 *
 *   Description:
 *     TBA
 *   Input Arguments:
 *     buff:
 *     include_version_p: Flag to request (vms) version info.
 *   Returns:
 *     return value: (long)
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_read_subdirs(buff, include_version_p, include_unreadable_p)
     char     *buff;
     long      include_version_p, include_unreadable_p;
{
    return (g2ext_str_readdir_filtered(buff, (long)1, include_version_p, include_unreadable_p));
}




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Logical Device Functions
 %
 % Description:
 %      These functions perform actions on logical devices
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 *      long g2ext_str_open_device_list()
 *
 *   Description:
 *     Initializes list of logical device names
 *   Input Arguments:
 *     none
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *     jh, 10/1/96.  This function is currently (jh, 10/1/96) implemented only
 *          on Windows/NT.
 *   Modifications:
 *
 *****************************************************************************/
#if defined(WIN32)
long g2ext_str_open_device_list()
{
 current_device_list = GetLogicalDrives();
 if (GET_LOGICAL_DRIVES_FAILURE == current_device_list)
  return FAILURE;
 else {
   current_device_list_mask = 1;
   current_device_list_index = 0;
   return SUCCESS;
 }
}
#else /* any platform except WIN32 */
long g2ext_str_open_device_list()
{
 return FAILURE;
}

#endif

/*****************************************************************************
 +      long g2ext_str_get_next_device(buff)
 *
 *   Description:
 *     Gets name of next available logical device
 *   Input Arguments:
 *     buff: A char buffer large enough for MAX_DEVICE_SIZE chars.
 *   Returns:
 *     buff:         On success, contains the name of the device.
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *     jh, 10/1/96.  This function is currently (jh, 10/1/96) implemented only
 *          on Windows/NT.
 *   Modifications:
 *
 *****************************************************************************/
#if defined(WIN32)
long g2ext_str_get_next_device(buff)
     char     *buff;
{
 long   result = FAILURE;

 while (current_device_list_mask) {
   if (current_device_list_mask & current_device_list) {
     sprintf(buff, "%c:", win32_device_names[current_device_list_index]);
     result = SUCCESS;
   }
   current_device_list_mask <<= 1;
   current_device_list_index++;
   if (SUCCESS == result) break;
  }
 return result;
}
#else /* any platform except WIN32 */
long g2ext_str_get_next_device(buff)
     char     *buff;
{
 return FAILURE;
}

#endif



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - File Functions
 %
 % Description:
 %      These functions perform actions on files
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * long  g2ext_str_rename_file(old_filename, new_filename)
 *
 *   Description:
 *     Change the name of a file.
 *   Input Arguments:
 *     old_filename:  Valid, existing file name
 *     new_filename:  the new, valid file name
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *   Modifications:
 *     11/22/94, mpc: Made this function multiply defined to to differing
 *          behavior on the rename() function on MS OS's. According to ANSI,
 *          if the target of a rename already exists then the behavior is
 *          implementation defined. In Windows and NT, this means failure.
 *          Since this is a sys-proc for our users we must make it appear to
 *          act the same. If the target exists, we rename it to a tempname,
 *          rename the desired file. It successful, delete the tempfile else
 *          restore the original targetfile.
 *     1/13/07, jv: we don't need to roll our own.  Windows' implementation of
 *          the POSIX function rename() may not be identical to our Unix's, but
 *          we can get the desired behavior using the Win32 API function
 *          MoveFileEx and supplying the flag MOVEFILE_REPLACE_EXISTING.
 *****************************************************************************/
#if defined(WIN32)
long g2ext_str_rename_file(old_filename, new_filename)
     char     *old_filename, *new_filename;
{
    long   success_code;
    BOOL   success_p;
    FILE   *stream;

    /* Check if source file exists by attempting an GFOPEN(). */
    stream = GFOPEN(old_filename, "r");
    if (stream)
        GFCLOSE(stream);
    else
        return (FAILURE);

    success_code = MoveFileEx(old_filename, new_filename, MOVEFILE_COPY_ALLOWED);
    if (success_code != 0L) {
      return SUCCESS;
    }
    if (ERROR_SHARING_VIOLATION != GetLastError()) {
      return FAILURE;
    }
    Sleep(MS_TO_SLEEP_BEFORE_COPY_FOR_RENAME);
    success_p = CopyFile(old_filename, new_filename, FALSE);
    if (success_p) {
      /* At this point, we really expect this to fail, but give it a shot.
       * Note, we are going to consider the "rename" a "success" whether
       * or not we're able to delete the old file.  -jv, 4/26/07
       */
      success_p = DeleteFile(old_filename);
      if (!success_p) {
	fprintf(stdout, "Error during rename: unable to delete file \"%s\"\n", old_filename);
      }
      return SUCCESS;
    }
    return FAILURE;
}
#else
static long cc_g2_stream_rename_file_1 (stream_arg, filename, arg3, arg4)
  FILE *stream_arg;
  char *filename;
  void *arg3;
  void *arg4;
{
  FILE *stream = GFOPEN(filename, "r");
  if (stream) GFCLOSE(stream);
  return stream != 0;
}

long g2ext_str_rename_file(old_filename, new_filename)
     char     *old_filename, *new_filename;
{
  if (g2ext_retry_file_operation(cc_g2_stream_rename_file_1, NULL, old_filename, NULL, NULL) &&
      0 == rename(old_filename, new_filename))
    return (SUCCESS);
  else
    return (FAILURE);
}
#endif

#if defined(WIN32)
long g2ext_str_rename_file_s16(g2chr16_t *old_filename, g2chr16_t *new_filename)
{
    long   success_code;
    BOOL   success_p;
    FILE   *stream;

    /* Check if source file exists by attempting an GFOPEN(). */
    if (stream = _wfopen(old_filename, L"r"))
        GFCLOSE(stream);
    else
        return FAILURE;

    success_code = MoveFileExW(old_filename, new_filename, MOVEFILE_COPY_ALLOWED);
    if (success_code != 0L) {
      return SUCCESS;
    }
    if (ERROR_SHARING_VIOLATION != GetLastError()) {
      return FAILURE;
    }
    Sleep(MS_TO_SLEEP_BEFORE_COPY_FOR_RENAME);
    success_p = CopyFileW(old_filename, new_filename, FALSE);
    if (success_p) {
      /* At this point, we really expect this to fail, but give it a shot.
       * Note, we are going to consider the "rename" a "success" whether
       * or not we're able to delete the old file.  -jv, 4/26/07
       */
      success_p = DeleteFileW(old_filename);
      if (!success_p) {
	fprintf(stdout, "Error during rename: unable to delete file \"%s\"\n", old_filename);
      }
      return SUCCESS;
    }
    return FAILURE;
}
#else
long g2ext_str_rename_file_s16(g2chr16_t *old_filename, g2chr16_t *new_filename)
{
  char *mbOldFilename = g2_s16dup2mbs(old_filename);  
  char *mbNewFilename;
  long result;

  if (NULL == mbOldFilename) {
    return 0L;
  }

  mbNewFilename = g2_s16dup2mbs(new_filename);
  if (NULL == mbNewFilename) {
    free(mbOldFilename);
    return 0L;
  }

  if (g2ext_retry_file_operation_s16(cc_g2_stream_rename_file_1, NULL, mbOldFilename, NULL, NULL) &&
      0 == rename(mbOldFilename, mbNewFilename))
    result = SUCCESS;
  else
    result = FAILURE;

  free(mbOldFilename);
  free(mbNewFilename);
  return result;
}
#endif


/*****************************************************************************
 * long  g2ext_str_copy_file(old_filename, new_filename)
 *
 *   Description:
 *     Copy an existing file.
 *   Input Arguments:
 *     old_filename:  Valid, existing file name
 *     new_filename:  the new, valid file name
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *****************************************************************************/
#if defined(WIN32)
long g2ext_str_copy_file(old_filename, new_filename)
     char     *old_filename, *new_filename;
{
    long   success_code;
    FILE   *stream;
    
    /* Check if source file exists by attempting an GFOPEN(). */
    stream = GFOPEN(old_filename, "r");
    if (stream) {
        GFCLOSE(stream);
    }
    else {
        return FAILURE;
    }

    success_code = CopyFile(old_filename, new_filename, FALSE);
    if (success_code != 0L) {
      return SUCCESS;
    }
    if (ERROR_SHARING_VIOLATION != GetLastError()) {
      return FAILURE;
    }
    return FAILURE;
}
#else
long g2ext_str_copy_file(char *old_filename, char *new_filename)
{
  FILE *outFile, *inFile;
  int Byte;

  /* Check if source file exists by attempting an GFOPEN(). */
  inFile = GFOPEN(old_filename, "rb");
  if (inFile == NULL) 
  {
    return FAILURE;
  }

  /* Check if dist file can be opened for writing */
  outFile = GFOPEN(new_filename, "wb");
  if (outFile == NULL)
  {
    GFCLOSE(inFile);
    return FAILURE;
  }

  /* Copy the bytes from inFile to outFile (source to destination)*/
  while(1)
  {
    Byte = fgetc(inFile);
    if (Byte != EOF)
    {
      fputc(Byte, outFile);
    }
    else
    {
      break;
    }
  }

  GFCLOSE(inFile);
  GFCLOSE(outFile);
  return SUCCESS;
}
#endif

#if defined(WIN32)
long g2ext_str_copy_file_s16(g2chr16_t *old_filename, g2chr16_t *new_filename)
{
    long   success_code;
    FILE   *stream;
    
    /* Check if source file exists by attempting an GFOPEN(). */
    stream = _wfopen(old_filename, L"r");
    if (stream)
        GFCLOSE(stream);
    else
        return FAILURE;

    success_code = CopyFileW(old_filename, new_filename, FALSE);
    if (success_code != 0L) {
      return SUCCESS;
    }
    if (ERROR_SHARING_VIOLATION != GetLastError()) {
      return FAILURE;
    }
    return FAILURE;
}
#else
long g2ext_str_copy_file_s16(g2chr16_t *old_filename, g2chr16_t *new_filename)
{
  int Byte;
  FILE *outFile, *inFile;
  long result;
  char *mbNewFilename;
  char *mbOldFilename = g2_s16dup2mbs(old_filename);
  
  if (NULL == mbOldFilename) {
    return 0L;
  }

  mbNewFilename = g2_s16dup2mbs(new_filename);
  if (NULL == mbNewFilename) {
    free(mbOldFilename);
    return 0L;
  }

  /* Check if source file exists by attempting an GFOPEN() */
  inFile = GFOPEN(mbOldFilename, "rb");
  free(mbOldFilename);

  if (inFile == NULL) {
    free(mbNewFilename);
    return FAILURE;
  }

  /* Check if dist file can be opened for writing */
  outFile = GFOPEN(mbNewFilename, "wb");
  free(mbNewFilename);
  if (NULL == outFile) {
    GFCLOSE(inFile);
    return FAILURE;
  }

  /* Copy the bytes from inFile to outFile (source to destination)*/
  while(1)
  {
    Byte = fgetc(inFile);
    if (Byte != EOF)
    {
        fputc(Byte, outFile);
    }
    else
    {
        break;
    }
  }

  GFCLOSE(inFile);
  GFCLOSE(outFile);
  return SUCCESS;
}
#endif

/*****************************************************************************
 * long  g2ext_str_file_timestamp(fname, mode)
 *
 *   Description:
 *     Get specified timestamp for a file.
 *   Input Arguments:
 *     fname:  A valid, existing file.
 *     mode:   0 for modification time - last date file was opened or written
 *             1 for access time - last date file was opened/read/written
 *             2 for status time - last date a file was opened/written/renamed
 *                                   or had its permissions changed
 *   Returns:
 *     return value: (long) Requested timestamp or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
static long cc_g2_stream_file_timestamp_1 (stream_arg, filename, stat_ptr, arg4)
  FILE *stream_arg;
  char *filename;
  struct stat *stat_ptr;
  void *arg4;
{
  long status = stat(filename,stat_ptr);
  /*Alpha stat() uses -2 to mean permission violation*/
  return status != -1 && status != -2;
}

double g2ext_str_file_timestamp(fname, mode)
     char     *fname;
     long      mode;
{
  struct stat  s;

  if (mode < 0 || mode > 2)
    return (double) FAILURE;
  if (g2ext_retry_file_operation(cc_g2_stream_file_timestamp_1, (FILE *) NULL,
                                 fname, (void *)&s, NULL))
    switch (mode) {
    case 0:
      return (double) s.st_mtime;
    case 1:
      return (double) s.st_atime;
    case 2:
      return (double) s.st_ctime;
    default:                        /* Can't happen. hush C compiler. */
      return (double) FAILURE;
    }
  else
    return (double) FAILURE;
}

#if defined(unix)
static gid_t *groups = 0;
static long groups_count = 0;

static int check_groups(file_gid)
     long file_gid;
{
  int i;
  if (file_gid == getgid()) return 1;
  if (groups == 0) {
    groups = (gid_t *)malloc(sizeof(gid_t)*NGROUPS_MAX);
    groups_count = getgroups(NGROUPS_MAX, groups);
  }
  for (i=0; i<groups_count; i++)
    if (groups[i] == file_gid) return 1;
  return 0;
}
#endif

long g2ext_str_file_access_check(fname, mode)
     char     *fname;
     long      mode;
{
#if defined(unix)
  struct stat s;
  int masked_mode;
  int mask = 0;

  if (mode < 0 || mode > 2)
    return -1;
  if (g2ext_retry_file_operation(cc_g2_stream_file_timestamp_1, NULL, fname, (void *)&s, NULL)) {
    switch (mode) {
    case 0: mask = S_IRUSR | S_IRGRP | S_IROTH; break;
    case 1: mask = S_IWUSR | S_IWGRP | S_IWOTH; break;
    case 2: mask = S_IXUSR | S_IXGRP | S_IXOTH; break;
    default: break; /* AlphaOSF optimizer dies without this line */
    }
    masked_mode = mask & s.st_mode;
    if (s.st_uid == getuid())
      return (masked_mode & S_IRWXU) ? 1 : 0;
    else if (check_groups(s.st_gid))
      return (masked_mode & S_IRWXG) ? 1 : 0;
    else
      return (masked_mode & S_IRWXO) ? 1 : 0;
  } else
    return -1;
#else
#  if defined(WIN32)
  long attrs;

  /* Maybe use GetFileSecurity */
  if (mode < 0 || mode > 2)
    return -1;
  attrs = GetFileAttributes(fname);
  switch (mode) {
  case 0: return 1;
  case 1: return (attrs & FILE_ATTRIBUTE_READONLY) ? 0 : 1;
  case 2: return (attrs & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
  }
#  endif
  return -1;
#endif
}

long g2ext_directory_contains_directory(containing_directory, contained_directory)
    char *containing_directory;
    char *contained_directory;
{
#if defined(unix)
  dev_t root_dev, current_dev, containing_dev;
  ino_t root_ino, current_ino, containing_ino;
  struct stat st;
  char current_directory[512];
  int current_len;

  if (stat(containing_directory, &st) < 0) return FALSE;
  containing_dev = st.st_dev;
  containing_ino = st.st_ino;

  if (stat ("/", &st) < 0) return FALSE;
  root_dev = st.st_dev;
  root_ino = st.st_ino;

  strcpy(current_directory, contained_directory);
  current_len = strlen(contained_directory);

  while (TRUE) {
    if (stat(current_directory, &st) < 0) break; /* note that stat follows soft links */
    current_dev = st.st_dev;
    current_ino = st.st_ino;
    if (current_dev != containing_dev) return FALSE; /* since there are no hard links between devices */
    if (current_ino == containing_ino) return TRUE;
    if (current_dev == root_dev && current_ino == root_ino) break;
    if (current_len > 500) break;
    strcpy(current_directory + current_len, "../");
    current_len += 3;
  }
  return FALSE;
#else
  int i, c1, c2, len = strlen(containing_directory);
  for (i=0; i<len; i++) {
    c1 = containing_directory[i];
    c2 = contained_directory[i];
    if (islower(c1)) c1 = toupper(c1);
    if (islower(c2)) c2 = toupper(c2);
    if (c1 != c2) return FALSE;
  }
  return TRUE;
#endif
}


/*****************************************************************************
 * long g2ext_str_get_version(filespec)
 *
 *   Description:
 *     Gets file version number (VMS only, all others no-op)
 *   Input Arguments:
 *     filespec: A valid file spec.
 *   Returns:
 *     return value: (long) version number or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_get_version(filespec)
     char     *filespec;
{
    return (FAILURE);
}




/*****************************************************************************
 * long g2ext_str_get_device(filespec, buff)
 *
 *   Description:
 *     Gets file device name (VMS only, all others no-op)
 *   Input Arguments:
 *     filespec: A valid file spec.
 *     buff:     buffer to pass back device name
 *   Returns:
 *     buff:         on success, the device name
 *     return value: (long) version number or FAILURE
 *   Notes:
 *     jh, 6/6/91.  Added g2ext_str_get_device for foreign function server,
 *          which has to spawn a process and pass it command-line args. VMS
 *          needs the full pathname, including device name, to do this.
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_get_device(filespec, buff)
     char     *filespec, *buff;
{
    return (FAILURE);
}


/* /home/rh/gnu/cvs-1.9/src/lock.c */
/* /home/xemacs/xemacs-21.0/src/filelock.c */

long g2ext_str_get_write_lock(filespec, g2_identification, buffer)
   char *filespec;
   char *g2_identification;
   char *buffer;
{
/*
  strcpy(buffer,"Write locking is not supported");
  return 0;
*/
  return 1;
}

long g2ext_str_release_write_lock(filespec, g2_identification)
   char *filespec;
   char *g2_identification;
{
  return 0;
}




/*****************************************************************************
 * long  g2ext_str_delete_file(filename)
 *
 *   Description:
 *     Delete the specified file.
 *   Input Arguments:
 *     filename: A valid file name
 *   Returns:
 *     return value: (long) SUCCESS or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_delete_file(filename)
     char     *filename;
{
  long success_code = unlink(filename);

  if (success_code == SUCCESS)
    return(SUCCESS);
  else
    return(FAILURE);
}

#if defined (WIN32)  
long g2ext_str_delete_file_s16(g2chr16_t * filename) 
{
    return (_wunlink(filename) == 0) ? SUCCESS : FAILURE;
}
#else
long g2ext_str_delete_file_s16(g2chr16_t * filename) 
{	
    char *s = g2_s16dup2mbs(filename);
    long success_code;
    
    if (NULL == s) {
        return 0L;
    }
    success_code = unlink(s);
    free(s);

  if (success_code == SUCCESS)
    return SUCCESS;
  else
    return FAILURE;
}
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP -  File System Info Functions
 %
 % Description:
 %      These functions gather various file system information
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*****************************************************************************
 * Gensym_Long g2ext_str_avail_disk_space(dirstring)
 *
 *   Description:
 *     Returns available disk space value.
 *   Input Arguments:
 *     dirstring: A valid directory path.
 *   Returns:
 *     return value: (long) Amount of free disk space, or FAILURE
 *   Notes:
 *     3/5/93, jh:  Each (non-vms)platform seems to have statfs(), but each
 *          puts the guts in a different include file, and some platforms
 *          take a different argument list.
 *     2/9/99, dkuznick: Some/most platforms use an unsigned long for the
 *          freeblocks value which can overflow long, so we a) make sure there's
 *          room to receive the value, and b) take care to return
 *          IMOST_POSITIVE_FIXNUM if the real value is too big (which we should
 *          do regardless of the signed/unsigned issue, since these days it's easy to
 *          imagine more than IMOST_POSITIVE_FIXNUM free blocks of diskspace.
 *
 *****************************************************************************/

#if defined(WIN32)
/* Notes on overflow: by taking three longs and multiplying them
 * together, we can certainly overflow a long, which is what this
 * function returns.  Of course, we know, however, that when Lisp
 * receives that value, even a long is too large.  It needs to fit
 * into a fixnum.  So, get the number of free bytes by using a
 * double to hold the value, and compare it with MOST_POSITIVE_FIXNUM.
 * There's no need to check if the value would fit into a long.
 *
 * There are three formats of pathnames that I know of on Windows:
 *   (1) unqualified, e.g., \bt\ab\kbs
 *         (can be relative or absolute)
 *   (2) disk-qualified, e.g., k:\bt\ab\kbs
 *   (3) network-node-qualified, e.g., \\gensym4\\bt\ab\kbs
 *         (aka, UNC, Universal Naming Convention)
 *   (4) something else, an error or something I can't think of
 * To get the root directory, we have to figure out which format
 * it is.  Then we do the following:
 *   (1) use "\"
 *   (2) use "<drive-letter>:\"
 *   (3) give it a shot
 *   (4) give it a shot anyway
 * - jv 11/7/99
 */
Gensym_Long g2ext_str_avail_disk_space(pathname)
     char     *pathname;
{
  BOOL status, obtainedRoot;
  DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters,
    TotalNumberOfClusters; /* ignored */
  char lpRootPathName[4];
  char firstChar;
  double NumberOfFreeBytes;
  Gensym_Long result;

  firstChar = pathname[0];
  obtainedRoot = FALSE;
  if ((firstChar == '\\') && (pathname[1] != '\\')) {
      /* if pathname[1] == '\', then it's network-qualified,
       * so don't get here.  */
      lpRootPathName[0] = '\\';
      lpRootPathName[1] = 0;
      obtainedRoot = TRUE;
  } else if ((((firstChar >= 'a') && (firstChar <= 'z')) ||
              ((firstChar >= 'A') && (firstChar <= 'Z'))) &&
             (pathname[1] == ':') &&
             (pathname[2] == '\\')) {
      strncpy(lpRootPathName, pathname, 3);
      lpRootPathName[3] = 0;
      obtainedRoot = TRUE;
  }

  status = GetDiskFreeSpace((obtainedRoot ? lpRootPathName : pathname),
                            &SectorsPerCluster, &BytesPerSector,
                            &NumberOfFreeClusters, &TotalNumberOfClusters);
  if (!status) {
    return ERROR_CREATING_DISK_QUERY;
  }
  NumberOfFreeBytes = (float) NumberOfFreeClusters *
    (float) SectorsPerCluster * (float) BytesPerSector;
  if (NumberOfFreeBytes > IMOST_POSITIVE_FIXNUM)
    return IMOST_POSITIVE_FIXNUM;
  result = (Gensym_Long) NumberOfFreeBytes;
  return result;
}
#endif

#if defined(unix)
Gensym_Long g2ext_str_avail_disk_space(pathname)
     char     *pathname;
{
    int   statfs_status;
    unsigned long  freeblocks;

#   if defined(_osf__)
       struct fs_data statfs_buffer;
#   elif defined(Platform_Solaris) || defined(Platform_Linux)
       struct statvfs statfs_buffer;
#   else /* HP-UX _IBMR2 SGI */
       struct statfs statfs_buffer;
#   endif


#   if defined(Platform_Solaris) || defined(Platform_Linux)
       statfs_status = statvfs(pathname, &statfs_buffer);
#   else
#      if defined(sgi)
          statfs_status = statfs(pathname, &statfs_buffer,
                                 sizeof (struct statfs), 0);
#      else
          statfs_status = statfs(pathname, &statfs_buffer);
#      endif
#   endif

    if (statfs_status == -1) {
        return ERROR_CREATING_DISK_QUERY;
    }


#   if defined(_osf__)
       freeblocks = statfs_buffer.fd_req.bfreen;
#   else
#      ifdef sgi
          freeblocks = statfs_buffer.f_bfree;
#      else
          freeblocks = statfs_buffer.f_bavail;
#      endif
#   endif

    return MIN(IMOST_POSITIVE_FIXNUM, freeblocks);
}

#endif



/*****************************************************************************
 * long g2ext_str_logical_name_p(buffer)
 *
 *   Description:
 *     Gets value of a system logical name. VMS only, others no-op.
 *   Input Arguments:
 *     buffer: Location large enough to hold translated logical
 *   Returns:
 *     buffer:       On success, the translated logical.
 *     return value: (long) 1L on success, otherwise 0L.
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_logical_name_p(buffer)
     char     *buffer;
{
    return (0L);
}



/*****************************************************************************
 * long  g2ext_str_max_filename(dirname)
 *
 *   Description:
 *     Get filename length restrictions for a given path.
 *   Input Arguments:
 *     dirname:  A valid directory path name
 *   Returns:
 *     return value: (long)
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_max_filename(dirname)
     char     *dirname;
{
    int max_namlen = NO_FILENAME_LIMIT;

#  if defined(WIN32)
    max_namlen = _MAX_FNAME;
#   endif

    return max_namlen;
}


/*****************************************************************************
 * long g2ext_make_unique_filename (char *id_suggestion,
 *                                  long buffer_size,
 *                                  char *buffer)
 *
 *   Description:
 *     Generate a unique filename, return it in the buffer suplied.
 *   Input Arguments:
 *     id_suggestion: a string which the temp file name might contain;
 *       can be ignored
 *     buffer_size: the size of the supplied buffer
 *     buffer: a place into which to write the file name
 *   Returns:
 *     return value: 1 on success, <0 on failure
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
#if defined(WIN32)
long g2ext_make_unique_filename (char *id_suggestion,
                                 long buffer_size,
                                 char *buffer)
{
  UINT rval;
  char tempdir[MAX_PATH];

  if (buffer_size < MAX_PATH) {
    return -1;
  }

  rval = GetTempPath (MAX_PATH, tempdir);
  if (rval == 0) {
    return -2;
  }

  rval = GetTempFileName(tempdir, id_suggestion, 0, buffer);

  if (rval == 0) {
    return -2;
  }
  return 1;  /* success */
}
#else
long g2ext_make_unique_filename (char *id_suggestion,
                                 long buffer_size,
                                 char *buffer)
{
  char fileName[FILENAME_MAX];
  int fileLength = L_tmpnam + strlen(id_suggestion) + 1;

  // Check whether buffer size is enough for result
  if (buffer_size < fileLength)
    return -1;
  // Check whether suggestion is too long for FILENAME_MAX (also internal buffer)
  if (fileLength > FILENAME_MAX)
    return -1;
  // Generate name
  sprintf(fileName, "%sXXXXXX", id_suggestion, strlen(id_suggestion));
  int handle = mkstemp(fileName);   
  // Return error if it was no possible to generate the name
  if (handle < 0)
    return -2;
  // Success
  strcpy(buffer, fileName);
  close(handle);
  // #Note: This might seem silly, but it's necessary to avoid using mktmp or 
  // tempname and keep the interface to the rest of the code, also avoid the 
  // possible problems of creating our own random temporary filename generator.
  remove(fileName);
  return 1;
}
#endif


/*****************************************************************************
 * long g2ext_g2_stream_get_error_number ()
 *
 *   Description:
 *     Return current value of errno
 *   Input Arguments:
 *     none
 *   Returns:
 *     return value: (long) errno value
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_g2_stream_get_error_number ()
{
       return errno;
}


/*****************************************************************************
 * long g2ext_create_directory (dirname, create_parents, mask)
 *
 *   Description:
 *     Create the requested directory
 *   Input Arguments:
 *     The name of the directory to be created
 *     Whether to create intervening directories
 *     Mask is presently unused, for future expansion
 *   Returns:
 *     return value: TRUE if directory was created or existed, FALSE otherwise
 *   Modifications:
 *     yduJ, 4/29/05: added code to implement the create_parents param.
 *                    Split into more functions: added create_directory_internal
 *                    and translate_mask (which currently uses umask in unix and
 *                    inherited SECURITY_ATTRIBUTES in windows, but is just a
 *                    stub for future expansion.)
 *
 *   Notes: create_directory_internal returns 1 if it created the directory,
 *          0 if it already existed, -1 if it failed to create it or got an
 *          error while creating, and -2 for the special windows try-again value
 *          (see below).
 *
 *****************************************************************************/
#if defined(WIN32)
static long create_directory_internal (dirname, psaAttr)
char * dirname;
SECURITY_ATTRIBUTES *psaAttr;
{
  BOOL status;
  DWORD errorcode, attributes;

  attributes = GetFileAttributes(dirname);
  if (attributes == 0xFFFFFFFF) {
    errorcode = GetLastError();
    if (errorcode == ERROR_INVALID_NAME) {
      /* For invalid name we return -2, meaning that if it's the first
         part of \\nethost\netdrive (\\nethost) which gives us a file
         syntax error, but the next time we're called
         (\\nethost\netdrive) we'll succeed in finding the attributes
         of this file.  g2ext_create_directory can figure out what to
         do if it never tries again (failure is the right answer.) */
      return -2;
    } else if (errorcode != ERROR_FILE_NOT_FOUND) {
      /* File not found, we want to fall through and create.
         Other errors, just fail. */
      return -1;
    }
  } else {
    if (attributes & FILE_ATTRIBUTE_DIRECTORY) {
      return 0; /* already a directory.  Succeed. */
    } else {
      return -1; /* Not a directory, fail. */
    }
  }

  status = CreateDirectory(dirname, psaAttr);

  if (status == 0)
    return -1;
  else
    return 1;
}

/* This is slightly convoluted because we want the modeattr local in
   g2ext_create_directory to not need &'ing when calling create_directory_internal,
   so we take the pointer here and modify and return it.  Then it can be locally
   declared in the win32 portion of g2ext_create_directory so no memory
   management is required. */
static SECURITY_ATTRIBUTES *translate_mask(mask,psaAttr)
char *mask;
SECURITY_ATTRIBUTES *psaAttr;
{
  psaAttr->nLength = sizeof(SECURITY_ATTRIBUTES);
  psaAttr->lpSecurityDescriptor = NULL;
  psaAttr->bInheritHandle = TRUE;
  return psaAttr;
}

#else

static long create_directory_internal (dirname, mask)
char *dirname;
mode_t mask;
{
  struct stat statbuffer;
  long status;

  if (stat(dirname, &statbuffer) == 0) {
    if (statbuffer.st_mode & S_IFDIR)
      return 0; /* File found and was a directory. */
    else
      return -1;  /* File found but not a directory.  Fail. */
  } else {
    if (errno == ENOENT) { /* Stat failed because file not there.  Create. */
      status = mkdir(dirname, mask);
      if (status != 0)
        return -1; /* Directory creation failed */
      else
        return 1;
    } else  /* Stat failed for some other reason.  Fail. */
      return -1;
  }
}

static mode_t translate_mask(mask)
char *mask;
{
  mode_t mmask;
  /* in the future we will do something with the mask variable, first checking
     the value is "umask" before doing the following, and do other things with
     other values. */
  mmask = umask(0); /* determine umask, clobbering current value. */
  umask(mmask);     /* Now set it back to what we learned. */
  mmask = 0777 ^ mmask; /* and now XOR it */
  return mmask;
}

#endif

long g2ext_create_directory (dirname, create_parents, mask)
char *dirname;
long create_parents;
char *mask;
{
  long status;

  char path_components[MAX_DIR_SIZE], *next_component, *current_path, *pathptr;

#ifdef WIN32
  char *delimiter = "\\";

  SECURITY_ATTRIBUTES saAttr;
  SECURITY_ATTRIBUTES *modeattr;

  modeattr = translate_mask(mask,&saAttr);
#else
  char *delimiter = "/";

  mode_t modeattr;
  modeattr = translate_mask(mask);

#endif

  if (create_parents) {
    /* Avoid buffer overruns or creating truncated directory names. */
    if (strlen(dirname) > MAX_DIR_SIZE)
      return FALSE;

    /* This silliness to avoid complaints from Intel compiler */
    pathptr = (char*)&path_components;
    current_path = pathptr;

    memset(path_components,0,MAX_DIR_SIZE);

    for (next_component = dirname; *next_component; next_component++) {
      if (*next_component == *delimiter &&
          /* don't try to create the empty string: */
          current_path != pathptr) {
        status = create_directory_internal(pathptr, modeattr);
        if (status == -1)
          return FALSE;
      }
      *current_path = *next_component;
      current_path++;
    }
    current_path--;
    if (*current_path != *delimiter) {
      /* If it's got a trailing slash, we tried to make the last one above.
         Otherwise, we didn't, and better do it now.  Is there a better way? */
      status = create_directory_internal(pathptr, modeattr);
    }
  } else { /* Don't create parents, just give it a go. */
    status = create_directory_internal(dirname, modeattr);
  }
  if (status >= 0)
    return TRUE;
  else
    return FALSE;
}




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Emitting Performance Information
 %
 % Description:
 %   These functions are used for performance data, and so are not particularly
 %   concerning streams.  However, they write their data out into streams, and
 %   there's no other terribly obvious place to put them, so they live here.
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

static char buffer_for_time_string[50];

static char *current_time_of_day_no_newline()
{
  char *time_string = buffer_for_time_string;
  time_t now_universal_time;
  struct tm *now_local_time_structure;
  int hour, result = 0;

  now_universal_time = time(NULL);

  if (now_universal_time != -1) {
    now_local_time_structure = localtime(&now_universal_time);
    if (now_local_time_structure) {
      hour = (now_local_time_structure->tm_hour % 12);
      if (hour == 0) hour = 12;
      result = sprintf(time_string, "%d:%02d:%02d %s",
                       hour, now_local_time_structure->tm_min,
                       now_local_time_structure->tm_sec,
                       (now_local_time_structure->tm_hour < 12) ? "a.m." : "p.m.");
    }
  }
  if (!result) {
    time_string[0] = '\0';
  }
  return time_string;
}


#ifndef WIN32
#  define UNIX_PERFORMANCE_FREQUENCY 10000
#  define LONGEST_PERMISSABLE_PERFORMANCE_MESSAGE 1024

extern double g2ext_unix_time_as_float();

/*****************************************************************************
 * long g2ext_performance_frequency (long stream_handle, long message_number)
 *
 *   Description: implements the system procedure g2-performance-frequency on
 *     Unix.  Since "Unix" (in general, anyway) does not actually have a high-
 *     performance counter, we kind of pick one arbitrarily.
 *   Input Arguments: a stream to write the information to.  It is assumed
 *     this will be the G2 trace logfile.
 *   Returns: the frequency (in addition to writing it out)
 *   Notes: if we find certain flavors of Unix provide higher resolution
 *     timing information, this can be expanded to more specific functionality.
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_performance_frequency (long stream_handle, long message_number)
{
  if (stream_handle != -1) {
    FILE *stream;

    stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_handle);
    if (stream != NULL) {
      int indentation, i;

      indentation = (int)ceil(log10(message_number+1));
      fputc('#', stream);
      for (i=0; i<indentation; i++) fputc('-', stream);
      fprintf(stream, "   %s   Performance Frequency: %d\n\n",
              current_time_of_day_no_newline(),
              UNIX_PERFORMANCE_FREQUENCY);
    }
  }

  return UNIX_PERFORMANCE_FREQUENCY;
}


/*****************************************************************************
 * double g2ext_emit_performance_counter (unsigned short *message,
 *                                       long message_number, long stream_handle)
 *
 *   Description: emits an as-precise-as-possible timestamp, in units described
 *     by the performance frequency (obtained by calling the above function):
 *     to standard output, and to a stream, if given
 *   Input Arguments: a textual message to precede the counter in the output,
 *     and an optional, additional stream to write the information to.  It is
 *     assumed this will be the G2 trace logfile.
 *   Returns: the low-order 29 bits of the timestamp
 *   Notes: if we find certain flavors of Unix provide higher resolution
 *     timing information, this can be expanded to more specific functionality.
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
double g2ext_emit_performance_counter (unsigned short *message,
                                       long message_number, long stream_handle)
{
  double unix_counter;
  int length = 0;
  char chr;
  unsigned short *ptr;
  FILE *stream = NULL;

  unix_counter = g2ext_unix_time_as_float() * (float) UNIX_PERFORMANCE_FREQUENCY;

  if (stream_handle != -1) {
    stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_handle);
    if (stream != NULL) {
      int indentation, i;

      indentation = (int)ceil(log10(message_number+1));
      fputc('#', stream);
      for (i=0; i<indentation; i++) fputc('-', stream);
      fprintf(stream, "   %s   ", current_time_of_day_no_newline());
    }
  }

  fprintf(stdout, "High Precision Counter: %lf\n", unix_counter);
  if (stream != NULL) {
    fprintf(stream, "High Precision Counter: %lf\n", unix_counter);
  }

  ptr = message;
  while (*ptr && (length < LONGEST_PERMISSABLE_PERFORMANCE_MESSAGE)) {
    chr = (*ptr == 8232) ? '\n' : *ptr;
    fputc(chr, stdout);
    if (stream != NULL) {
      fputc(chr, stream);
    }
    /* Note: definitely do not want to fflush here! */
    ptr++;
    length++;
  }
  fputc('\n', stdout);
  if (stream != NULL) {
    fputc('\n', stream);
    fputc('\n', stream);
  }

  return (double) unix_counter;
}


/*****************************************************************************
 * double g2ext_report_performance_counter ()
 *
 *   Description:
 *   Input Arguments: none
 *   Returns: the high-performance counter as a double float
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
double g2ext_report_performance_counter ()
{
  double unix_counter;

  unix_counter = g2ext_unix_time_as_float() * (double) UNIX_PERFORMANCE_FREQUENCY;

  return (double) unix_counter;
}

#endif


#ifdef WIN32
#  define QPCBUFSIZE 200

static char qpcbuf[QPCBUFSIZE];

/*****************************************************************************
 * long g2ext_performance_frequency (long stream_handle, long message_number)
 *
 *   Description: implements the system procedure g2-performance-frequency on
 *     Windows.
 *   Input Arguments: a stream to write the information to.  It is assumed
 *     this will be the G2 trace logfile.
 *   Returns: the frequency, if we can obtain it and it can fit into 29 bits;
 *     -1 otherwise
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_performance_frequency (long stream_handle, long message_number)
{
  LARGE_INTEGER frequency = {0, 0};
  FILE *stream = (FILE *)NULL;
  BOOL success_p = FALSE;

  if (stream_handle != -1) {
    stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_handle);
  }
  success_p = QueryPerformanceFrequency(&frequency);

  if (!success_p) {
    fprintf(stdout, "Unable to obtain performance frequency\n");
    if (stream != (FILE *)NULL) {
      int indentation, i;

      indentation = (int)ceil(log10(message_number+1));
      fputc('#', stream);
      for (i=0; i<indentation; i++) fputc('-', stream);
      fprintf(stream, "   %s   Unable to obtain performance frequency\n\n",
              current_time_of_day_no_newline());
    }
    return -1;
  }

  fprintf(stdout, "Performance Frequency: %I64u\n", frequency.QuadPart);
  if (stream != (FILE *)NULL) {
    int indentation, i;

    indentation = (int)ceil(log10(message_number+1));
    fputc('#', stream);
    for (i=0; i<indentation; i++) fputc('-', stream);
    fprintf(stream, "   %s   Performance Frequency: %I64u\n\n",
            current_time_of_day_no_newline(),
            frequency.QuadPart);
  }

  success_p = (frequency.QuadPart < 0x1FFFFFFF);
  if (success_p) {
    return (long) frequency.QuadPart;
  }
  return -1;
}


/*****************************************************************************
 * double g2ext_emit_performance_counter (unsigned short *message,
 *                                       long message_number, long stream_handle)
 *
 *   Description: emits a hig-precision timestamp, in units described
 *     by the performance frequency (obtained by calling the above function):
 *     to standard output, and to a stream, if given
 *   Input Arguments: a textual message to precede the counter in the output,
 *     and an optional, additional stream to write the information to.  It is
 *     assumed this will be the G2 trace logfile.
 *   Returns: the low-order 29 bits of the timestamp, assuming it can be
 *      obtained; -1 if it cannot
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
double g2ext_emit_performance_counter (unsigned short *message,
                                       long message_number, long stream_handle)
{
  static LARGE_INTEGER latest_count = {0, 0};
  FILE *stream = NULL;
  char chr;
  unsigned short *ptr;
  BOOL success_p = FALSE;

  if (stream_handle != -1) {
    stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_handle);
  }

  success_p = QueryPerformanceCounter(&latest_count);
  if (!success_p) {
    fprintf(stdout, "Unable to obtain performance counter\n");
    if (stream != (FILE *)NULL) {
      int indentation, i;

      indentation = (int)ceil(log10(message_number+1));
      fputc('#', stream);
      for (i=0; i<indentation; i++) fputc('-', stream);
      fprintf(stream, "   %s   Unable to obtain performance counter\n\n",
              current_time_of_day_no_newline());
    }
    return -1;
  }

  fprintf(stdout, "High Precision Counter: %I64u\n",
          latest_count.QuadPart);
  if (stream != NULL) {
    int indentation, i;

    indentation = (int)ceil(log10(message_number+1));
    fputc('#', stream);
    for (i=0; i<indentation; i++) fputc('-', stream);
    fprintf(stream, "   %s   High Precision Counter: %I64u\n",
            current_time_of_day_no_newline(),
            latest_count.QuadPart);
  }

  ptr = message;
  while (*ptr) {
    chr = (*ptr == 8232) ? '\n' : *ptr;
    fputc(chr, stdout);
    if (stream != NULL) {
      fputc(chr, stream);
    }
    /* Note: definitely do not want to fflush here! */
    ptr++;
  }
  fputc('\n', stdout);
  if (stream != NULL) {
    fputc('\n', stream);
    fputc('\n', stream);
  }

  return (double) latest_count.QuadPart;
}


/*****************************************************************************
 * double g2ext_report_performance_counter ()
 *
 *   Description:
 *   Input Arguments: none
 *   Returns: the high-performance counter as a double float
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
double g2ext_report_performance_counter ()
{
  static LARGE_INTEGER latest_count = {0, 0};
  BOOL success_p = FALSE;

  success_p = QueryPerformanceCounter(&latest_count);
  if (success_p) {
    return (double) latest_count.QuadPart;
  } else {
    fprintf(stdout, "Unable to obtain performance counter\n");
    return (double) -1.0;
  }
}

#endif /* WIN32 */
