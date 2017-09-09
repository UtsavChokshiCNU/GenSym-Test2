/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:       g2pwaux.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Ben Hyde, David McDonald
 +
 + Description: This is the auxiliary module of a program used by the G2 user at
 +              a "secure" site when he wants to change or initialize his
 *               password.  It edits the g2.ok file in place.
 +
 + Key:
 +   (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - Password Functions
 +
 + External Interface:
 +
 + Dependencies:
 +      Includes cprim.h and md5_all.h
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <stdlib.h>    /* standard library functions */
#include <ctype.h>     /* character  macros */
#include <errno.h>     /* errno */
#include <string.h>    /* string compare etc. */
#include <setjmp.h>    /* setjmp/longjmp */
// added by SoftServe
#if defined (WIN32)
#include <io.h>
#include <dos.h>
#include <time.h>
#endif
// end of SoftServe changes
      /*** Define PROTOTYPES for the benefit of md5_all.h ***/
#include "md5_all.h"   /* md5 hashing */

      /*** Two platform flavors: unix and WIN32 ***/
#ifdef unix
#  include <termios.h>   /* echo/noecho (struct termios) */
#endif                /* unix */

#ifdef WIN32
#  include <windows.h>
#endif  /* WIN32 */

#include "cprim.h"     /* platform coding convensions */

/*** Overview ***/

/*
 * Overview: This is the main module of a program used
 * by the G2 user at a "secure" site when he wants to
 * change or initialise his password.  It edits the
 * g2.ok file in place.
 *
 * It prompts the user for his name, old and new
 * password.  Turning off echo at approprate times.  It
 * then opens the ok file, as given in the first
 * argument, and finds the user in there.  It replaces
 * the password.  It will decline to replace the
 * password if the old one doesn't match.  A password
 * of all X always matches.
 *
 * We read the entire ok file.  We catch a few syntax
 * and other errors but we don't attempt to catch them all.
 *
 * When we find the old password in the file we note
 * it's position in the file and then after we have
 * read the entire file we fseek back to that and
 * revise the password in place.  There is the small
 * chance that the password would span two disk blocks
 * and the write would fail between them.  That would
 * create a corrupted ok file, for that user's entry.
 * */



/*** Coding Convensions ***/

/*
 * - Output is all done with the model that presumes that the
 * cursor is at the beginning of a fresh line.
 * - All symbols are spelled in lowercase using underscore between
 * the whole english words.
 * - braces are always used on for the bodies of else clauses,
 * except when the then clause fits on one line and there is no else.
 * - Code is usually top down, forward declarations are used to
 * enable that.
 * - Declarations and definitions use identical parameter names.
 * - Modules are delimited by single line comments beginning with
 * three stars.
 **/


/*
 * The macro `forward_static' expands to static.  It is used
 * in place of static in function declartions written to allow
 * a function to be used prior to being defined in this file.
 */

#define forward_static static

/*
 * The macro boolean expands to the type int.  It is used to
 * declare locations who's value is treated as a boolean.
 */

#define boolean int

/*
 *`PROTOTYPE_ARGS' is used in prototype declarations so that
 * we can compile when we encounter a olde C compiler.
 */

#ifdef __STDC__
#define PROTOTYPE_ARGS(args) args
#else
#define PROTOTYPE_ARGS(args) ()
#endif

FILE *g2pw_ok_file;
int   g2pw_g2_password_is_32_X;


/*** Static Global Variables ***/

/* File globals use to hold the I/O streams of the process */

static long password_location; /* set: validate, used: g2pw_revise_ok_file */
static long password_change_date_location = -1;        /* non-negative iff found */
static long password_change_date_end = -1;        /* non-negative iff found */
static long end_user_entry;
static long beginning_of_most_recent_end;

#define G2PW_MAX_TIME_STRSIZE 256   /* ample room */
static char current_time_string[G2PW_MAX_TIME_STRSIZE]; /* used to return the current time */

jmp_buf g2pw_error_env;        /*  for setjmp/longjmp */

static boolean eol_is_known = FALSE;
static boolean eol_is_CRLF  = FALSE; /* implies that it's \n */
static char *eol = "\n"; /* default before skip_whitespace_or_comment sets it */


/*** Forward Function Declarations ***/

/* Top level structure */
void g2pw_validate_input PROTOTYPE_ARGS((char *user_name,
                                                   char *old_password,
                                                   char *old_password_hashed,
                                                   char *new_password1,
                                                   char *new_password2));

void g2pw_lookup_old_input PROTOTYPE_ARGS((char *user_name,
                                                     char *old_password_hashed));

int g2pw_change_pwd_main
PROTOTYPE_ARGS((char *file_name, char *user_name, char *old_password_hashed,
                            char *new_password_hashed));

void g2pw_locate_final_user_entry
PROTOTYPE_ARGS(( ));

boolean read_though_user_entry_recording_end_location
PROTOTYPE_ARGS(( ));

void g2pw_modify_decay_date
PROTOTYPE_ARGS((char *file_name, char *user_name, char *new_password_decay_date));

void lookup_user_and_password_validity_entry
PROTOTYPE_ARGS((char *user_name));

boolean read_entry_of_target_user_for_password_validity
PROTOTYPE_ARGS((char *user_name));



/* Input */

void g2pw_revise_ok_file PROTOTYPE_ARGS((char *name,
                                                   char *hashed_password));
void g2pw_new_revise_ok_file PROTOTYPE_ARGS((char *, char *));
void g2pw_write_ok_file_password_etc PROTOTYPE_ARGS((char *, char *, int));

void g2pw_add_user_entry
        PROTOTYPE_ARGS((char *file_name, char *user_name, char *new_password_hashed,
                        char *mode_list, char *password_decay_date));

void g2pw_delete_user_entry
        PROTOTYPE_ARGS((char *ok_file_name, char *tmp_file_name, char *user_name));



/* Shutdown */
forward_static void darn  PROTOTYPE_ARGS((char *why));
forward_static void darn1 PROTOTYPE_ARGS((char *why, void *arg));
void g2pw_darn  PROTOTYPE_ARGS((char *why));
void g2pw_darn1 PROTOTYPE_ARGS((char *why, void *arg));

/* Parsing */
forward_static boolean read_user_entry
PROTOTYPE_ARGS((boolean already_saw_desired_user,
                                char *user_name_to_seek,
                                char *hashed_old_password));

/* Lexer */
forward_static void    open_g2ok_file PROTOTYPE_ARGS((char *file_name));
void                   g2pw_init_reader PROTOTYPE_ARGS((char *file_name));
forward_static boolean scan_input_pending PROTOTYPE_ARGS((void));
forward_static int     count_chars_to_end_of_line PROTOTYPE_ARGS((void));
boolean                g2pw_scan_text PROTOTYPE_ARGS((char *text));
forward_static void    scan_token_and_match_or_fail PROTOTYPE_ARGS((char *text_to_match,
                                                 char *error_string));
forward_static char    *scan_yank PROTOTYPE_ARGS((void));
forward_static int     scan_token PROTOTYPE_ARGS((void));
forward_static boolean scan_match PROTOTYPE_ARGS((char *text_to_match));
forward_static boolean scan_token_and_match PROTOTYPE_ARGS((char *text_to_match));
forward_static long    scan_token_ftell PROTOTYPE_ARGS((void));
forward_static long    scan_token_ftell_right_end PROTOTYPE_ARGS((void));



/* Variables for file i/o and tokenizing support */

/* Both "BUFFER_MAX" and "READ_SIZE" are changed for a temporary fix
 * of HQ-1507796. Before this will cause g2passwd.exe break on VMS.
 */

#define READ_SIZE 4096

/* We theoretically may have to copy all of the old amount read into the new.
 * See advance_file_reader.  We should probably be mallocing this as we go
 * rather than allocating a big chunk like this.
 */
#define BUFFER_MAX (READ_SIZE * 2 + 1)
static char ok_file_buffer[BUFFER_MAX];
static char *buffer_top_mark;
static char *buffer_bottom_mark;
static char *left_of_parsing;
static char *right_of_parsing;
static boolean file_is_done;


/*** Definition enabling the -Wall switch ***/

/*
 * The switch -Wall is used in gnu cc to provide a more
 * fastidious compiler with better type checking etc.
 * Using it requires that I establish some declarations
 * so the module will compile with no warnings.  These
 * probably only work on sunos.
 */

#ifdef USING_WALL
extern FILE *fopen();
extern int fclose();
extern int fread();
extern int fwrite();
extern long ftell();
extern int unlink();
extern int fflush();
extern void printf();
extern void fseek();
extern void stty();
#endif   /* USING_WALL */


#define EOF_TOKEN -1
#define UNIMPORTANT_TOKEN 1
#define STRING_TOKEN 2
#define SEMICOLON_TOKEN 3
#define COLON_TOKEN 4
#define SYMBOL_TOKEN 5
#define NUMBER_TOKEN UNIMPORTANT_TOKEN
#define LIST_TOKEN UNIMPORTANT_TOKEN


int g2pw_change_pwd(file_name, user_name, old_password_hashed, new_password_hashed)
char *file_name, *user_name, *old_password_hashed, *new_password_hashed;
{
  int status;

  status = setjmp(g2pw_error_env);
  if (status != 0)
    return(status); /* error */
  status = g2pw_change_pwd_main(file_name, user_name, old_password_hashed, new_password_hashed);
  return(status);
}

int g2pw_change_pwd_main(file_name, user_name, old_password_hashed, new_password_hashed)
char *file_name, *user_name, *old_password_hashed, *new_password_hashed;
{
  int ignored_error_code;
  g2pw_init_reader(file_name);
  if(!g2pw_scan_text("begin g2-ok-file"))
    g2pw_darn1("OK file %s is invalid. It must begin with \"begin g2-ok-file\".", file_name);
  g2pw_lookup_old_input(user_name, old_password_hashed);
  g2pw_write_ok_file_password_etc(new_password_hashed, file_name, 32);
  ignored_error_code = fclose(g2pw_ok_file);
  return 0;                        /* 0 indicates success */
}




/* write_string_expanding_ok_file expands g2pw_ok_file and then writes to it.  It
   first expands the file starting at allocation_end_location if needed to
   fit string_to_write in.  Then it writes string_to_write.
   Then, unless padchar is NUL ('\0'), it writes padchar as many times
   as needed until all character positions up to allocation_end_location
   have been written.  If padding is irrelevant or should not be used,
   padchar should be supplied as NUL ('\0').
   */

#define G2PW_MAX_N_EXPANSION_CHARS 256

void write_string_expanding_ok_file(string_to_write, file_name,
                                                    file_scan_location, allocation_end_location,
                                                                    padchar)
char *string_to_write, *file_name;
long file_scan_location, allocation_end_location;
char padchar;
{
  char next_char = '\0';
  char file_buffer1[G2PW_MAX_N_EXPANSION_CHARS], file_buffer2[G2PW_MAX_N_EXPANSION_CHARS];
  int buffer_pointer, counter;
  int buffer_status = -1;
  int string_length = strlen(string_to_write);
  int n_expansion_chars = ((file_scan_location + string_length)
                                                         - allocation_end_location); /* neg. ok */
  int n_padchars = ((allocation_end_location - file_scan_location)
                                         - string_length); /* neg. ok */
  /*
   * -1, file end reached, last effective contents in file_buffer1
   * -2, file end not reached, last effective contents in file_buffer2
   *  1, file end reached, last effective contents in file_buffer1
   *  2, file end not reached, last effective contents in file_buffer2
   **/

  if (n_expansion_chars > G2PW_MAX_N_EXPANSION_CHARS)
    darn1("Internal error -- cannot expand by more than 256 chars to insert %s",
          string_to_write);


  if ((file_scan_location + string_length) > allocation_end_location)
  {
    /* Initialize the file_buffer1, file_buffer2 and the buffer_status. */

        /* Move to where we're going to add the string. */
    fseek(g2pw_ok_file, allocation_end_location, 0L);
    buffer_status = 1;

        /* Copy n_expansion_chars worth of what follows in the file into
           file_buffer1, moving the buffer_pointer along with you. Stop at
           eof if that's reached befor the count is finished. */
    counter = 0;
    buffer_pointer = 0;
    while (!feof(g2pw_ok_file) && (counter < n_expansion_chars))
      {
                next_char = getc (g2pw_ok_file);
                file_buffer1[buffer_pointer] = next_char;
                buffer_pointer++;
                counter++;
      }
        /* Make file_buffer1 into a null-delimited string, backing up
           if necessary because we had reached the eof while copying. */
    if (feof(g2pw_ok_file))
      {
                buffer_status = -1;
                file_buffer1[buffer_pointer-1] = '\0';
      }
    else
      file_buffer1[buffer_pointer] = '\0';


        /* Copy out the next n_expansion_chars from the file into file_buffer2
           and make it into a string. */
    counter = 0;
    buffer_pointer = 0;
    while (!feof(g2pw_ok_file) && (counter < n_expansion_chars))
      {
        next_char = getc (g2pw_ok_file);
        file_buffer2[buffer_pointer] = next_char;
        buffer_pointer++;
        counter++;
      }

    if (feof(g2pw_ok_file) && buffer_status != -1)
      {
        buffer_status = -2;
        file_buffer2[buffer_pointer-1] = '\0';
      }
    else
      file_buffer2[buffer_pointer] = '\0';
  } /* end of if (file_scan_location + string_length) > allocation_end_location */




  /* Insert the timestamp or the new password into the OK file. */
  fseek(g2pw_ok_file, file_scan_location, 0L);
  fwrite(string_to_write, sizeof(char), string_length, g2pw_ok_file);

  /* Pad out with padchar if necessary. */
  if (padchar != '\0') {
      for (counter = 0; (counter < n_padchars); counter++) {
          fwrite(&padchar, sizeof(char), 1, g2pw_ok_file);
      }
  }


  file_scan_location = allocation_end_location;

  /* If we have to expand, do so. N.b. this goes to the end of the function. */
  if (n_expansion_chars > 0) {

     if (buffer_status == -1 || buffer_status == -2) {
                file_scan_location = file_scan_location + n_expansion_chars;
                fseek(g2pw_ok_file, file_scan_location, 0L);

                for (counter = 0; counter<n_expansion_chars; counter++) {
                        next_char = file_buffer1[counter];
                        if (next_char == '\0')
                          break;
                        putc (next_char, g2pw_ok_file);
                }
                
                if (buffer_status == -1)
                  return;

                counter = 0;
                next_char = file_buffer2[counter];
                while (next_char != '\0') {
                  putc (next_char, g2pw_ok_file);
                  counter++;
                   next_char = file_buffer2[counter];
                }
                return;
         }
        

    for (;;)
      {
        file_scan_location = file_scan_location + n_expansion_chars;
        fseek(g2pw_ok_file, file_scan_location, 0L);

        counter = 0;
        switch (buffer_status)
          {
          case 1:
            next_char = file_buffer1[counter];
            counter++;
            break;
          case 2:
            next_char = file_buffer2[counter];
            counter++;
            break;
          default:
            break;
          }

        while (next_char != '\0')
          {
            putc (next_char, g2pw_ok_file);
            switch (buffer_status)
              {
              case 1:
                next_char = file_buffer1[counter];
                counter++;
                break;
              case 2:
                next_char = file_buffer2[counter];
                counter++;
                break;
              default:
                break;
              }
          }

        /* Jump! */
        fseek(g2pw_ok_file, file_scan_location+n_expansion_chars, 0L);

        /* Read */
        buffer_pointer = 0;
        while (!feof(g2pw_ok_file) && buffer_pointer<n_expansion_chars)
          {
            next_char = getc (g2pw_ok_file);
            if (buffer_status == 1)
              file_buffer1[buffer_pointer] = next_char;
            else
              file_buffer2[buffer_pointer] = next_char;
            buffer_pointer++;
          }

        if (feof(g2pw_ok_file))
          {
            if (buffer_status == 1)
              {
                file_buffer1[buffer_pointer-1] = '\0';
                buffer_status = -1;
              }
            else
              {
                file_buffer2[buffer_pointer-1] = '\0';
                buffer_status = -2;
              }
            break;
          }

        switch (buffer_status)
          {
          case 1:
            file_buffer1[buffer_pointer] = '\0';
            buffer_status = 2;
            break;
          case 2:
            file_buffer2[buffer_pointer] = '\0';
            buffer_status = 1;
            break;
          }
      } /* for loop. */



    fseek(g2pw_ok_file, file_scan_location+n_expansion_chars, 0L);

    /*  printf ("\nHere, %d, buffer1, %s, buffer2, %s", buffer_status, file_buffer1, file_buffer2); */

    switch (buffer_status)
      {
      case -1:
        counter = 0;
        next_char = file_buffer2[counter];
        while (next_char != '\0')
          {
            putc (next_char, g2pw_ok_file);
            counter++;
            next_char = file_buffer2[counter];
          }
        counter = 0;
        next_char = file_buffer1[counter];
        while (next_char != '\0')
          {
            putc (next_char, g2pw_ok_file);
            counter++;
            next_char = file_buffer1[counter];
          }
        break;
      case -2:
        counter = 0;
        next_char = file_buffer1[counter];
        while (next_char != '\0')
          {
            putc (next_char, g2pw_ok_file);
            counter++;
            next_char = file_buffer1[counter];
          }
        counter = 0;
        next_char = file_buffer2[counter];
        while (next_char != '\0')
          {
            putc (next_char, g2pw_ok_file);
            counter++;
            next_char = file_buffer2[counter];
          }
        break;
      }
  } /* end of if <more than 0 expansion characters (after writing)> */
}





/*
 * G2pw_new_revise_ok_file allows the administrator include a null
 * string as user's default password.
 **/

/* OBSOLETE! -- mhd, 3/6/98 */

void g2pw_new_revise_ok_file (hashed_password, file_name)
char *hashed_password, *file_name;
{
  write_string_expanding_ok_file(hashed_password, file_name,
                                 password_location, password_location, '\0');
}





/* get_password_change_date_string returns a string with the time
   in a format like this:

      " -- change date: Fri Mar 06 16:28:15 EST 1998"

   The year is always printed in full (4-digit) format, thus
   avoiding even the appearance of a "Y2K" issue.

   The string may be from a reusable buffer, so if you want to store
   the string contents for later use, it has to be copied.

   The exact representation may be subject to some variation based
   on the formatting of the OS and the values of some environment
   variable, especially on localization settings.  This uses the
   time package's strftime() function print the time with this
   format string: "%a %b %d %X %Z %Y".  It's probable, for
   example, that in Japan the names of months and days will be
   in Japanese in a double-byte encoding of JIS.

   If a time string can't be gotten for any reason, a brief
   message is printed in square brackets ([]) instead of the time.

   Note: Microsoft has a wide-character version of the time functions,
   but we don't currently handle wide characters in our g2.ok
   file, so it cannot be considered at this time.

   This code work should work on all current platforms (unix,
   WIN32, and VMS).
   */

char *get_password_change_date_string ()
{
  time_t now_universal_time;
  struct tm *now_local_time_structure;
  size_t result;
  char *time_format = " -- change date: %a %b %d %X %Z %Y";

  now_universal_time = time(NULL);
  now_local_time_structure = localtime(&now_universal_time);
  result = strftime (current_time_string, G2PW_MAX_TIME_STRSIZE,
                     time_format, now_local_time_structure);
  if (result < 1)   /* assume 0 for "didn't fit"; -1 for error */
    return(" -- change date: [unknown; time unavailable]");
  else
    {
      current_time_string[result] = '\0'; /* set NUL marking end of string */
      return(current_time_string);
    }
}



/* g2pw_write_ok_file_password_etc ... replacement for obsolete
   g2pw_new_revise_ok_file and g2pw_revise_ok_file
   */
void g2pw_write_ok_file_password_etc(hashed_password, file_name, n_chars_preallocated)
char *hashed_password, *file_name;
int n_chars_preallocated;
{
  char *date_string = get_password_change_date_string();


  /* Write the change date, which will always have come later in the file
     after the password, and then we'll "move up" in the file
     to do the password, since doing so could shift stuff "over" our location.
     */
  if (password_change_date_location > -1) /* always now in practice */
    write_string_expanding_ok_file
      (date_string,
       file_name,
       password_change_date_location,
       password_change_date_end,
       ' ');

  write_string_expanding_ok_file
    (hashed_password,
         file_name,
     password_location,
     (password_location + n_chars_preallocated),
     ' ');
}


/* g2pw_validate_input looks over the user's input and guards agains errors. */

/* Validate_input looks over the user's input and guards agains errors. */

void g2pw_validate_input(user_name,
                           old_password, old_password_hashed,
                           new_password1, new_password2)
char *user_name,
  *old_password, *old_password_hashed,
  *new_password1, *new_password2;
{
  /* Check that he typed the new one the same way both times. */
  if ( strcmp(new_password1, new_password2) )
    darn("New password must be the same both times it is entered");

  if(strlen(new_password1)<=3)
    darn("The new password must have at least four characters in it");

  { /* Approve the lexical structure of the new password. */
    register char *p, c;;
    for( p=new_password1; *p!='\000'; p++ )
    {
      c = *p;
      if ( ! (isalpha(c) || isdigit(c)) )
        darn("New password must consist of only these characters: a-z, A-Z, or 0-9");
                                /* Fixed the English: the above had previously
                                   been "... must be consist ..." -mhd, 2/23/98 */
    }
  }

  g2pw_lookup_old_input (user_name, old_password_hashed);
}




/* Parse the file, find this user, check against old
 * password, remember were it was for latter rewrite. */

void g2pw_lookup_old_input (user_name, old_password_hashed)
char *user_name, *old_password_hashed;
{
  /*
   * Modified the While condition to include not(saw_user) so
   * that the loop would be exited on the first successful
   * entry for the user. This fixes a bug involving which
   * password is subsequently modified (HQ-1229222), ddm 3/11/97
   **/
  boolean saw_user = FALSE;
  while ( scan_input_pending() && !saw_user )
    {
      if(scan_token_and_match("begin")
                  && scan_token_and_match("user")
                  && read_user_entry(saw_user, user_name, old_password_hashed))
        saw_user=TRUE;
    }
  if(!saw_user) darn("This user does not appear in the ok file");
}







/*** Adding new users **/

void g2pw_add_user_entry
     (file_name, user_name, new_password_hashed, mode_list, password_decay_date)
char *file_name, *user_name, *new_password_hashed, *mode_list, *password_decay_date;
{
        int ignored_error_code;
        char the_entry[500]; /* later give it a realistic value as a constant */

        /* Default location immediately after the first line of the file,
           which is where we presently are given the call to initialize_reader. */
    end_user_entry = scan_token_ftell_right_end();

        /* Find the end of the last user entry in the file and store it in
           end_user_entry */
        g2pw_locate_final_user_entry();

        /* Compose the entry */
        sprintf(the_entry,
"begin user\
%s  name: %s;\
%s  password: \"%s\";\
%s  permitted-user-modes: %s;\
%s  password-validity: %s;\
%send user%s\
%s",
eol, user_name,
eol, new_password_hashed,
eol, mode_list,
eol, password_decay_date,
eol, eol,
eol);

        /* Open things up and fit it in */
        write_string_expanding_ok_file
                (the_entry, file_name, end_user_entry, end_user_entry, '\0');

        ignored_error_code = fclose(g2pw_ok_file);
}


/* Parse the file, find the end of the last user entry, remember
 * it so we can add a new entry right after it. */

void g2pw_locate_final_user_entry ()
{
        boolean saw_some_user = FALSE;
        while (TRUE)
        {
          int token_type;

          token_type = scan_token();
          if(token_type == EOF_TOKEN)
            return; /* use default */

          if (scan_match("file-format-version")) {
                /* update default */
                count_chars_to_end_of_line();
                end_user_entry = scan_token_ftell_right_end();
          }

          if(scan_match("begin")) {
                if(scan_token_and_match("user"))
          saw_some_user = read_though_user_entry_recording_end_location();
          }
          else if(scan_match("end")) {
                beginning_of_most_recent_end = scan_token_ftell();
                if(scan_token_and_match("g2-ok-file"))
          break; /* reached the end of the file */
          }
        }
        /* record some default location if necessary */
        if(!saw_some_user) {
      end_user_entry = beginning_of_most_recent_end;
        }
}

/*
Added by SoftServe
Declare function before it will be used.
*/
#if defined (unix)
	static int count_spaces();
#endif
/*
 End of changes
*/

/** Starting just after the 'begin user' line, read through to the
 *  end of the entry, recording the location of the end of the line
 *  of the 'end user' line. */

boolean read_though_user_entry_recording_end_location()
{
  while(TRUE)
  {
        int token_counter = 0;
        int token_type;
        
        token_type = scan_token();

        if(token_type == EOF_TOKEN)
          darn("File is malformed, a user entry had no \"end user\"");
        if(++token_counter > 30)
          darn("File is malformed, implausible number of tokens in user entry");

        if( scan_match("end") && scan_token_and_match("user"))
        {
          end_user_entry = scan_token_ftell_right_end() + count_spaces();
          return TRUE;
        }
  }
}









/*** Modifying the password decay date ***/

static long password_validity_location_start;
static long password_validity_location_end;
static long password_validity_default_location;
static boolean user_entry_has_pswd_validity_entry = FALSE;


void g2pw_modify_decay_date (file_name, user_name, new_password_decay_date)
char *file_name, *user_name, *new_password_decay_date;
{
  char default_line[100];

  /* find it */
  lookup_user_and_password_validity_entry(user_name);

  /* write over it */
  if(user_entry_has_pswd_validity_entry)
    write_string_expanding_ok_file
      (new_password_decay_date, file_name,
       password_validity_location_start, password_validity_location_end,
       '\0');

  else {
    sprintf(default_line, "  password-validity: %s;%s",
            new_password_decay_date, eol);
    write_string_expanding_ok_file
      (default_line, file_name,
       password_validity_default_location, password_validity_default_location,
       '\0');
  }
}


/* Loop through all the users calling the tailored user-entry sweeper
   for the location (or not) of this user's password-validation field. */
void lookup_user_and_password_validity_entry (user_name)
char *user_name;
{
  while (TRUE)
  {
        scan_token();

        if(scan_match("begin")) {
          if(scan_token_and_match("user"))
            if (read_entry_of_target_user_for_password_validity(user_name))
              break;
        }
        if(file_is_done)
          darn1("Could not find a user entry for %s", user_name);
  }
}

/* Is this entry the one we're looking for, and if so, what is the
   location of its password_validity entry if any. */
boolean read_entry_of_target_user_for_password_validity(user_name)
char *user_name;
{
  int token_counter = 0;
  int token_type;
  char* token_buffer;
  boolean correct_user = FALSE;

  while(TRUE)
  {
    token_type = scan_token();

    if(token_type == EOF_TOKEN)
      darn("File is malformed, a user entry had no \"end user\"");
    if(++token_counter > 30)
      darn("File is malformed, implausible number of tokens in user entry");

    if(scan_match("name")) /* check syntax and see if it's the one we're after */
      {
        scan_token_and_match_or_fail
          (":","File malformed: name attribute must have colon following");
        token_type = scan_token();
        if(token_type != SYMBOL_TOKEN)
          darn("File is malformed, a user name must be a symbol");
        
        token_buffer = scan_yank();
        /* printf("Reading entry for %s\n", token_buffer); */
        if( strcmp(token_buffer, user_name)==0 )
          {
            free (token_buffer);
            correct_user = TRUE;
          }
        else
          {
            free (token_buffer);
            return FALSE;
          }
      }

    if(scan_match("password-validity")
       && correct_user==TRUE ) /* makes the assumption they're normally ordered */
      {
        scan_token_and_match_or_fail
          (":","File malformed: name attribute must have colon following");
        
        /* wrap the 'parser' (character scanner) around the value */
        token_type = scan_token();
        /* Don't bother to check the type, we're the only ones who can create
           this type of attribute just now. */
        
        password_validity_location_start = scan_token_ftell();
        password_validity_location_end = scan_token_ftell_right_end();
        user_entry_has_pswd_validity_entry = TRUE;
        return TRUE;
      }

    if(scan_match("end"))
      {
        if(correct_user==TRUE) {
          password_validity_default_location = scan_token_ftell();
          user_entry_has_pswd_validity_entry = FALSE;
          return TRUE;
        }
        else
          return FALSE;
      }
  }
}





/*** OK File Reading and Parsing ***/

/*
 *`Funny_password_match_p' takes a string token of the right length
 * and matchs it against the hashed old password
 **/

static boolean funny_password_match_p(token_buffer, hashed_old_password)
char *token_buffer;
char *hashed_old_password;
{
  int i;
  char *p1=token_buffer+1;
  char *p2=hashed_old_password;

  for(i=0; i<32; i++){
    if(*p1++!=*p2++)return FALSE;
  }
  return TRUE;
}


/*
 * `New_funny_password_match_p' takes a string token of the right length
 * and matchs it against the hashed old password
 **/


static boolean new_funny_password_match_p(token_buffer, hashed_old_password)
char *token_buffer;
char *hashed_old_password;
{
  if (*token_buffer==*hashed_old_password)
    return TRUE;
  else
    return FALSE;
}



void record_password_location ()
{
  password_location = scan_token_ftell()+1;

  scan_token_and_match_or_fail
    (";", "File malformed: attribute:value must have semicolon (;) following");

  /* get the start and end location between one past the ";" and
     the end of line:
     */
  password_change_date_location = scan_token_ftell()+1;
  password_change_date_end
    = (password_change_date_location
       + count_chars_to_end_of_line());        /* note side effect: moves file pos to eol */
}



/*
 * `Read_user_entry' is called whenever the main reading
 * loop encounters "begin user" token pair. Presumably
 * the read head will read the next token following.
 **/

static boolean read_user_entry(already_saw_desired_user,
                               user_name_to_seek,
                               hashed_old_password)
boolean already_saw_desired_user;
char *user_name_to_seek;
char *hashed_old_password;
{
  int token_counter = 0;
  boolean password_match = FALSE;
  boolean user_match = FALSE;
  int token_type;
  char* token_buffer;

  while(TRUE)
  {
    token_type = scan_token();

    if(EOF_TOKEN == token_type)
      darn("File is malformed, a user entry had no \"end user\"");

    if(++token_counter>30)
      darn("File is malformed, a user entry was too large");

    if(scan_match("end"))
      break;

    if(scan_match("name"))
    {
      if(user_match)
        darn("Malformed file: this user has two \"name\" attributes");

      scan_token_and_match_or_fail(":","File malformed: name attribute must have colon following");
      if(SYMBOL_TOKEN!=scan_token())
        darn("File is malformed, a user name must be a symbol");

      token_buffer = scan_yank();

      if(strcmp(token_buffer, user_name_to_seek)==0)
      {
        if(already_saw_desired_user)
          darn("This user appears multiple times in the file");
        user_match=TRUE;
      }

      free (token_buffer);        /* Technically, we should also do a free before
                                   the "darn" above since that does a longjmp
                                   and exit, but in the interest of
                                   simplicity... -dkuznick, 2/26/02 */
    }

    if(scan_match("password")){
      if(password_match){
        darn("Malformed file: this user has two \"password\" attributes");
      }
      scan_token_and_match_or_fail(":","File malformed: password attribute must have colon following");
      if(STRING_TOKEN!=scan_token()){
        darn("File is malformed, a password name must be a string");
      }

      /*
       * This is changed to adapt the '0' X character in the password,
       * -- April 28, 1997
       **/
      token_buffer = scan_yank();
      if (strcmp (token_buffer, "\"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\"") == 0)
        {
        g2pw_g2_password_is_32_X = 1;
        password_match = TRUE;
        record_password_location();
        }
      else
      {
        g2pw_g2_password_is_32_X = 0;
        switch (strlen(token_buffer))
        {
        case 34 :
          if (funny_password_match_p(token_buffer, hashed_old_password))
          {
            password_match = TRUE;
            record_password_location();
              }
          break;

        case 2 :
          if (new_funny_password_match_p(token_buffer, hashed_old_password))
          {
            password_match = TRUE;
            record_password_location();
          }
          break;

        default :
          {
            printf("WARNING: File malformed. The password %s is malformed.\n",token_buffer);
            printf("WARNING: Encoded password must be either 0 or 32 characters, but this is %d.\n", (int)strlen(token_buffer));
            /* printf("WARNING: Encoded must be either 0 or 32 characters, this is %d.\n", (int)strlen(token_buffer));
               -- previous version commented out. (MHD 2/23/97)
             */
          }
          break;
        }
      }

      free (token_buffer);

    }
  }

  if (user_match&&password_match)
    return TRUE;
  if (user_match)
    darn("Old password did not match");
  return FALSE;
}




/*** Deleting User Entries **

We delete user entries by copying the ok file and omitting the
indicated entry. The entry point, g2pw_delete_user_entry, does
the file and stream management. The main copy routine passes
everything through until it sees the start of a user entry,
when it calls copy_user_entry_if_not_target to do the heavy
lifting. This comes down to buffering the whole user entry
while we check to see if it's the target we are to omit.
That involves first calling line_contains_user_entry so we
only look closely at lines that have "name:" in them, and
then using user_line_of_targeted_user to actually do the check
against the user_name.
*/

#define LINESIZE 256
#define MAX_USER_NAME 200
#define USER_ENTRY_MAX_LINES 32

boolean line_contains_user_entry (line)
char *line;
{
  char *target = "name:";
  if (strstr(line, target) != NULL)
    return TRUE;
  else
    return FALSE;
}


boolean user_line_of_targeted_user (line, user_name, line_count)
char *line, *user_name;
int line_count;
{
  char *p;
  int i, length;
  char q[MAX_USER_NAME];

  /* First walk up to the colon, which we know has to be present
     or we wouldn't have been called. */
  for (i=0; i<line_count; i++) {
   if (line[i] == ':')
        break;
  }
  /* Then scarf up any interveening spaces. */
  i++;
  for (;i<line_count;i++) {
   if (! (line[i]==' ')) {
     break;
    }
  }
  /* Then test whether the remainder of the line up to the semicolon
     matches the user_name. */
  p = &line[i];
  length = strcspn(p, ";");
  strncpy(q, p, length);
  q[length] = (char)NULL;
  if (strcmp(q, user_name) == 0)
        return TRUE;
  else
    return FALSE;
}


/* g2pw_get_a_line reads a line of text, but not more than max_length (which
should be an integer >= 1) into line, and discards the CRLF or LF at the end of
a line.  If it encounters the end of file, and no characters have been put into line,
it returns NULL.

g2pw_put_a_line writes a line of text and then adds the appropriate end-of-line
characters.
*/

char *g2pw_get_a_line (line, max_length, from_stream)
char *line;
int max_length;
FILE *from_stream;
{
  char next_char; int i;

  i = 0;
  while (((next_char = getc(from_stream)) != EOF) && (i < (max_length - 1))) {
    if ((next_char != '\n') && (next_char != '\r')) {
      line[i] = next_char;
      i = i + 1;
    }
    if (next_char == '\n')
      break;
  }
  if ((i == 0) && next_char == EOF)
    return(NULL);
  else {
    line[i] = '\0';
    return(line);
  }
}


void g2pw_put_a_line (string, to_stream)
char *string;
FILE *to_stream;
{
  int i; char c;

  i = 0;
  while ((c = string[i]) != '\0') {
    putc(c, to_stream);
    i = i + 1;
  }

  /* Well, you'd think a CR would be needed before the LF on Windows/DOS, but it
     seems stream handles this automatically by putting the leading CR before
     the LF. (MHD 10/18/00) */
  putc('\n', to_stream);
}



void copy_user_entry_if_not_target (from, to, user_name, line)
FILE *from, *to;
char *user_name, *line;
{
  char buffered_lines[USER_ENTRY_MAX_LINES][LINESIZE];
  char *current_line = line;
  boolean is_target = FALSE;
  int line_index = 1;                /* starts after first argument line */
  int i;

  strcpy(buffered_lines[0], line);
  for (;;) {
    if (line_index >= USER_ENTRY_MAX_LINES)
      darn("User entry has too many lines to copy");
    if (g2pw_get_a_line(buffered_lines[line_index], LINESIZE - 1, from) == NULL)
      darn("EOF reached while inside user entry");
    current_line = buffered_lines[line_index];
    line_index = line_index + 1;
    if (line_contains_user_entry(current_line))
      is_target
        = user_line_of_targeted_user(current_line, user_name, strlen(current_line));
	if (strncmp(current_line, "end user", 8) == 0) {
	  g2pw_get_a_line(buffered_lines[line_index], LINESIZE - 1, from);
	  line_index = line_index + 1;
      break;
	}
  }
  if (!is_target) {
    for (i = 0; i < line_index; i++) {
      g2pw_put_a_line(buffered_lines[i], to);
    }
  }
}




void copy_all_but_target_user (from, to, user_name)
FILE *from, *to;
char *user_name;
{
  char line[LINESIZE];

  while (g2pw_get_a_line(line, LINESIZE - 1, from) != NULL)
  {
    if (strncmp(line, "begin user", 10) == 0)
      copy_user_entry_if_not_target(from, to, user_name, line);
    else
      g2pw_put_a_line(line, to);
  }
}


void g2pw_delete_user_entry
     (ok_file_name, tmp_file_name, user_name)
char *ok_file_name, *tmp_file_name, *user_name;
{
  FILE *tmp_file;
  unsigned int i = 0;
  int k = 1;
  time_t t;
  open_g2ok_file(ok_file_name);
  tmp_file = fopen(tmp_file_name, "w");
  if (! tmp_file)
        darn1("Unable to open the temporary ok file \"%s\"", tmp_file_name);

  copy_all_but_target_user(g2pw_ok_file, tmp_file, user_name);
  
  fclose(g2pw_ok_file);

  fclose(tmp_file);
  
  remove(ok_file_name);
  // modified by SoftServe 
  if (access(tmp_file_name, 0) == 0) 
  {
  do {
      t = 0;
  if (i > 1) 
  {
	  do {
	  t = time(NULL);
	  } while (t == time(NULL));
  }
  k = rename(tmp_file_name, ok_file_name);
  i ++;
  } while ((access(tmp_file_name, 0) == 0) && (access(ok_file_name, 0) != 0) && (i < 5) && (k != 0));
  }
  i = 0;
  while ((access(tmp_file_name, 0) == 0) && (i < 10))
  {
  remove(tmp_file_name);
  i++;
  }
  // end of SoftServe changes
  }




/*** File I/O and Tokenizing Support ***/

static void advance_file_reader()
{
  /* Slide the characters down in file buffer */
  int cnt;    /* = buffer_bottom_mark-buffer_top_mark; */

  /* The following line is to protect the current state of the parse */
  strncpy(ok_file_buffer, left_of_parsing, right_of_parsing-left_of_parsing);
  cnt = right_of_parsing-left_of_parsing;
  /* buffer_top_mark -= cnt;
     buffer_bottom_mark -= cnt;
     left_of_parsing -= cnt;
     right_of_parsing -= cnt;

  This is to fix a historical bug that will crash the g2passwd.exe while
  manipulating large OK file. -- jwang */

  buffer_bottom_mark = buffer_top_mark + cnt;
  left_of_parsing = buffer_top_mark;
  right_of_parsing = buffer_bottom_mark;

  /* Read more if possible */
  if(feof(g2pw_ok_file)) file_is_done=TRUE;
  if(!file_is_done){
  again:
    errno = 0;
    cnt = fread(buffer_bottom_mark, sizeof(char), READ_SIZE, g2pw_ok_file);
    if(cnt == 0 && errno != 0){
      if (errno == EINTR) {
        clearerr(g2pw_ok_file);
        goto again;
      }
      darn("An error occured reading the ok file");
    }
    buffer_bottom_mark += cnt;
  }
}


static void open_g2ok_file(file_name)
char *file_name;
{
  /*
   * Suppress translations involving carraige returns and line-feed
   * characters on WIN32 platforms. On VMS, use stream context, maximum line length 32k.
   **/
#ifdef WIN32
  g2pw_ok_file = fopen(file_name,"r+b");
#else
  g2pw_ok_file = fopen(file_name,"r+");
#endif /* WIN32 */

  if (! g2pw_ok_file){
    darn1("Unable to open \"%s\" as a G2 OK file", file_name);
  }
}

void g2pw_init_reader(file_name)
char *file_name;
{
  open_g2ok_file(file_name);
  buffer_top_mark = ok_file_buffer;
  buffer_bottom_mark = buffer_top_mark;
  left_of_parsing = buffer_top_mark;
  right_of_parsing = buffer_top_mark;
  file_is_done = FALSE;
  advance_file_reader();
}

static boolean scan_input_pending()
{
  return !file_is_done;
}

static long scan_token_ftell()
{
  long file_position_of_bottom_of_buffer = ftell(g2pw_ok_file);
  int span_to_bottom_of_buffer = buffer_bottom_mark - left_of_parsing;
  return file_position_of_bottom_of_buffer - (long)span_to_bottom_of_buffer;
}

static long scan_token_ftell_right_end()
{
  long file_position_of_bottom_of_buffer = ftell(g2pw_ok_file);
  int span_to_bottom_of_buffer = buffer_bottom_mark - right_of_parsing;
  return file_position_of_bottom_of_buffer - (long)span_to_bottom_of_buffer;
}

static char scan_getchar()
{
  if(right_of_parsing>=buffer_bottom_mark && ! file_is_done){
    advance_file_reader();
  }
  if(right_of_parsing>=buffer_bottom_mark){
    return '\000';
  }
  return *right_of_parsing++;
}


static void scan_ungetchar(c)
char c;
{
  *--right_of_parsing=c;
}


/* This returns a fresh copy which must be freed by the caller */
static char *scan_yank()
{
  int length = right_of_parsing - left_of_parsing + sizeof(char);
  char *result = (char *) malloc(length * sizeof(char));
  char *p1 = left_of_parsing;
  char *p2 = result;

  if (NULL == result)
    darn("Couldn't malloc in scan_yank");
  while (p1<right_of_parsing)
    *p2++=(*p1++);
  *p2='\000';
  return result;
}

/* scan_match checks if the text given matchs the most recent scan */

static boolean scan_match(text_to_match)
char *text_to_match;
{
  char *p1 = left_of_parsing;
  char *p2 = text_to_match;
  while(TRUE){
    char c = *p2++;
    if(p1==right_of_parsing && c=='\000') return TRUE;
    if(right_of_parsing<=p1) return FALSE;
    if(c!=*p1++) return FALSE;
    if(c=='\000')return FALSE;
  }
}




#define BEGIN_SCAN {\
    char * saved_left_of_parsing = left_of_parsing; \
    char * saved_right_of_parsing = right_of_parsing; \
    left_of_parsing = right_of_parsing

#define END_SCAN \
      buffer_top_mark=left_of_parsing; \
      return TRUE; \
    fail:  \
      left_of_parsing = saved_left_of_parsing;  \
      right_of_parsing = saved_right_of_parsing; \
      return FALSE; \
    }


/* count_chars_to_end_of_line moves the scan to the (beginning of) an end of line
character or sequence of characters (or an end of file), and returns the number
of times it could advance before the end of the line.  Note that reaching
the end of the file counts as reaching the end of the line.

Note the important side effect that this also moves the position of the scan to
the position of the end of the line.

This is liberal in what it accepts as an end-of-line character, in that either
LF or CR look like the beginning of an end of a line character or character
sequence.  (If this is ever changed to handle Unicode files (16-bit chars),
it should include Unicode Line Separator and Unicode Paragraph Separator
in addition to CR and LF.)
*/

#define G2PW_LF 10
#define G2PW_CR 13
#define G2PW_MAX_CHARS_TO_EOL 50000

static int count_chars_to_end_of_line()
{
  char c;
  boolean reached_eol;
  int count = 0;

  left_of_parsing = right_of_parsing;
  while ((c=scan_getchar())) {
    reached_eol = ((c==G2PW_LF) || (c==G2PW_CR) || (c=='\000'));
    if(reached_eol) {
      scan_ungetchar(c);
      break;
    }
    count = count + 1;
    if (count > G2PW_MAX_CHARS_TO_EOL)
      darn("Can't handle more than 50000 characters at the end of a line.");
  }
  return(count);
}


static boolean skip_whitespace_or_comment()
{
  left_of_parsing = right_of_parsing;
  {
    char c;
    while ((c=scan_getchar()))
        {
      if(c==' ')continue;
      if(c=='\n')continue;
      if(c=='\t')continue;
      if(c=='\r')
          { /* if this is running on, e.g, a wintel box then the EOL is indicated
                   by two characters, and our output has to appreciate this, so we
                   look and set a flag accordingly. (On a Mac it would just be a \r
                   by itself, but they're not an issue these days.) */
                char c2;
                if( !eol_is_known )
                {
                  c2 = scan_getchar();
               if(c2=='\n') {
                        eol = "\r\n";
                        eol_is_CRLF = TRUE; /* it's false by default */
                  }
                  else {
            eol = "\n";
                        scan_ungetchar(c2);
                  }
                eol_is_known = TRUE;
            }
            continue;
          }
      if(c=='-')
          { /* check whether we've started a comment and if so, clear
                   the rest of the line (or up to the eof) and then continue looping */
                char c2 = scan_getchar();
                if(c2=='-')
                {
                 do {
                   c=scan_getchar();
                 } while ( c!='\n' && c!='\r' && c!='\000');
                }
                continue;
          }
      scan_ungetchar(c);
      break;
    }
  }
  return TRUE;
}



boolean g2pw_scan_text(text)
char *text;
{
  char c,c2,*p=text;
  BEGIN_SCAN;
  do {
    c=(*p++);
    if(c=='\000')break;
    c2 = scan_getchar();
    if(c2!=c) goto fail;
  } while(1);
  END_SCAN;
}



static boolean scan_list_1(depth)
int depth;
{
  char c;
  while (TRUE){
    c=scan_getchar();
    if(c=='(') scan_list_1(depth+1);
    if(c==')') return TRUE;
    if(c=='\000') return TRUE;
  }
}



static boolean scan_list()
{
  left_of_parsing = right_of_parsing;
  /*  buffer_top_mark=left_of_parsing; */
  scan_getchar(); /* Over open paren. */

  scan_list_1(1);
  return TRUE;
}



static boolean scan_string()
{
  char c;
  left_of_parsing = right_of_parsing;
  /* buffer_top_mark=left_of_parsing; */
  scan_getchar(); /* right quote */
  do { c=scan_getchar(); } while (c && c!='"');
  return TRUE;
}



static boolean scan_digits()
{
  char c;
  left_of_parsing = right_of_parsing;
  /* buffer_top_mark=left_of_parsing; */
  do { c=scan_getchar(); } while (c&&isdigit(c));
  return TRUE;
}



static boolean scan_symbol()
{
  char c;
  left_of_parsing = right_of_parsing;
  /* buffer_top_mark=left_of_parsing; */
  do { c=scan_getchar(); } while (c&&(isdigit(c)
                                      ||isalpha(c)
                                      ||c=='-'
                                      ||c=='_'
                                      ||c=='.'
                                      ||c=='?'));
  scan_ungetchar(c);
  return TRUE;
}

static int count_spaces()
{
  char c;
  int count = -1;
  left_of_parsing = right_of_parsing;
  do {
	  c=scan_getchar();
	  ++count;
  } while (c && (c=='\n' || c=='\r' || c==' ' || c=='\t'));
  scan_ungetchar(c);
  return count;
}


static int scan_token()
{
  char c;
  skip_whitespace_or_comment();
  c = scan_getchar();
  if (c=='"'){
    scan_ungetchar(c);
    scan_string();
    return STRING_TOKEN;
  } else if (c=='(') {
    scan_ungetchar(c);
    scan_list();
    return LIST_TOKEN;
  } else if (c==':') {
    return COLON_TOKEN;
  } else if (c==';') {
    return SEMICOLON_TOKEN;
  } else if (isdigit(c)){
    scan_ungetchar(c);
    scan_digits();
    return NUMBER_TOKEN;
  } else if (isalpha(c)){
    scan_ungetchar(c);
    scan_symbol();
    return SYMBOL_TOKEN;
  } else if (c=='\000'){
    return EOF_TOKEN;
  } else {
     darn("Ok file is malformed");
  }
  /* Unreachable */
  return 0;
}



static boolean scan_token_and_match(text_to_match)
char *text_to_match;
{
  scan_token();
  return scan_match(text_to_match);
}



static void scan_token_and_match_or_fail(text_to_match, why_fail)
char *text_to_match;
char *why_fail;
{
  if(!scan_token_and_match(text_to_match)){
    darn(why_fail);
  }
}



/*** Setting up a Jump ***/

int set_up_g2passwd_jump ()
{
  return setjmp(g2pw_error_env);
}




/*** Shutdown ***/


/* Darn exits the program telling the user how sad we are. The arg why
   is a string giving the reason in a brief piece of English text.
   Darn1 is similar, but why should be a format control string which
   uses a single arg, both of which are supplied to printf.  This
   longjmp's control back to ...[!].  The calling
   function's status result will be a positive integer, at present
   always 1, but conceivably in a future version an error code.
   The positiveness of the status result indicates an error condition
   that's been reported to the user on the terminal.
   */

static void darn(why)
char *why;
{
  printf("\nERROR: %s.\n", why);
  longjmp(g2pw_error_env, 1);        /* error */
}


/* Darn1 is darn with a single printf argument. */
static void darn1(why, arg)
char *why;
void *arg;
{
  printf("\nERROR: ");
  printf(why, arg);
  printf(".\n");
  longjmp(g2pw_error_env, 1);        /* error */
}


/* exported versions: */
void g2pw_darn(why)
char *why;
{
  darn(why);
}

void g2pw_darn1(why, arg)
char *why;
void *arg;
{
  darn1(why, arg);
}
