/*******************************************************************************
 * This file, g2pwaux.c, is the same file as used in the g2passwd program,
 * adapted for use in creating watermarks by adding a single new void function,
 * make_watermark. Not all of the rest of it is needed, though a nontrivial part
 * is, particularly for making modifications to the OK file. It seems best for
 * long term maintenance to keep the file intact.   ddm 8/15/00
 *
 *   --->  Jim Wright. If there's too much baggage in here let me (ddm) know
 *         and we'll figure something out.
 *******************************************************************************/


#include "cprim.h"     /* platform coding convensions (see also cppflags.h) */
#include <ctype.h>     /* character  macros */
#include <string.h>    /* string compair etc. */
#include <stdio.h>     /* printf */
#include <setjmp.h>    /* setjmp/longjmp */
#include <time.h>      /* strftime */

      /*** Define PROTOTYPES for the benifit of md5_all.h ***/
#include "md5_all.h"   /* md5 hashing */

      /*** Three platform flavors: unix, vms, WIN32 ***/
#ifdef unix
#include <termios.h>   /* echo/noecho (struct termios) */
#endif                /* unix */

#ifdef vms
#include <descrip.h>
#include <devdef>
#include <iodef.h>
#include <ttdef.h>
#include <tt2def.h>
#include <dcdef.h>
#include <climsgdef.h>
#include <rms.h>
#include <hlpdef.h>
#endif  /* vms */

#ifdef WIN32
#include <windows.h>
#endif  /* WIN32 */


#ifdef __cplusplus
extern "C" {
#endif

int make_watermark_file (char *, char *, char *, char *, char *);
int add_watermark_to_ok_file (char *, char *, char *, char *, char *);


static char *install_time_string = NULL; /* used for watermarking */

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
static long password_change_date_location = -1;	/* non-negative iff found */
static long password_change_date_end = -1;	/* non-negative iff found */
static long end_user_entry;
static long beginning_of_most_recent_end;

#define G2PW_MAX_TIME_STRSIZE 256   /* ample room */
static char current_time_string[G2PW_MAX_TIME_STRSIZE]; /* used to return the current time */

jmp_buf g2pw_error_env;	/*  for setjmp/longjmp */

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
forward_static void prompt_and_get 
PROTOTYPE_ARGS((char *prompt, char *result,
						   boolean echo_p,
						   char *testing_argument));

forward_static void get_string 
	PROTOTYPE_ARGS((char *result, boolean echo));

forward_static void compute_password_hash 
	PROTOTYPE_ARGS((char *user_name, char *incomming_password, char *hashed_password));

void g2pw_revise_ok_file PROTOTYPE_ARGS((char *name,
						   char *hashed_password));
void g2pw_new_revise_ok_file PROTOTYPE_ARGS((char *, char *));
void g2pw_write_ok_file_password_etc PROTOTYPE_ARGS((char *, char *, int));
forward_static void change_password_to_uppercase PROTOTYPE_ARGS((char *));

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

/* Lexer */
forward_static void    open_g2ok_file PROTOTYPE_ARGS((char *file_name));
void                   g2pw_init_reader PROTOTYPE_ARGS((char *file_name));
forward_static boolean scan_input_pending PROTOTYPE_ARGS((void));
forward_static int     count_chars_to_end_of_line PROTOTYPE_ARGS((void));
boolean                g2pw_scan_text PROTOTYPE_ARGS((char *text));
forward_static void    scan_token_and_match_or_fail PROTOTYPE_ARGS((char *text_to_match, 
						 char *error_string));
forward_static char    *scan_yank PROTOTYPE_ARGS((char *buffer));
forward_static int     scan_token PROTOTYPE_ARGS((void));
forward_static boolean scan_match PROTOTYPE_ARGS((char *text_to_match));
forward_static boolean scan_token_and_match PROTOTYPE_ARGS((char *text_to_match));
forward_static long    scan_token_ftell PROTOTYPE_ARGS((void));
forward_static long    scan_token_ftell_right_end PROTOTYPE_ARGS((void));
forward_static char    trace_scan_match PROTOTYPE_ARGS(());

/* Low Level Terminal I/O */

forward_static void ttycbreak PROTOTYPE_ARGS((void));
forward_static void ttynorm PROTOTYPE_ARGS((void));
forward_static int getch PROTOTYPE_ARGS((void));
forward_static void putch PROTOTYPE_ARGS((char c));


/* Variables for file i/o and tokenizing support */ 

/* Both "BUFFER_MAX" and "READ_SIZE" are changed for a temporary fix 
 * of HQ-1507796. Before this will cause g2passwd.exe break on VMS. 
 */

#define BUFFER_MAX 5124
#define READ_SIZE 4096
static char *ok_file_buffer[BUFFER_MAX];
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
  char ch, file_buffer1[G2PW_MAX_N_EXPANSION_CHARS], file_buffer2[G2PW_MAX_N_EXPANSION_CHARS];
  int buffer_status, buffer_pointer, counter;
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
		ch = getc (g2pw_ok_file);
		file_buffer1[buffer_pointer] = ch;
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
	ch = getc (g2pw_ok_file);
	file_buffer2[buffer_pointer] = ch;
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
			ch = file_buffer1[counter];
			if (ch == '\0')
			  break;
			putc (ch, g2pw_ok_file);
		}
		  
		if (buffer_status == -1)
		  return;

		counter = 0;
		ch = file_buffer2[counter];
		while (ch != '\0') {
		  putc (ch, g2pw_ok_file);
		  counter++;
		   ch = file_buffer2[counter];
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
	    ch = file_buffer1[counter];
	    counter++;
	    break;
	  case 2:  
	    ch = file_buffer2[counter];
	    counter++;
	    break;
	  default:
	    break;
	  }

	while (ch != '\0')
	  {
	    putc (ch, g2pw_ok_file);
	    switch (buffer_status)
	      {
	      case 1:  
		ch = file_buffer1[counter];
		counter++;
		break;
	      case 2:  
		ch = file_buffer2[counter];
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
	    ch = getc (g2pw_ok_file);
	    if (buffer_status == 1)
	      file_buffer1[buffer_pointer] = ch;
	    else
	      file_buffer2[buffer_pointer] = ch;
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
	ch = file_buffer2[counter];
	while (ch != '\0')
	  {
	    putc (ch, g2pw_ok_file);
	    counter++;
	    ch = file_buffer2[counter];
	  }
	counter = 0;
	ch = file_buffer1[counter];
	while (ch != '\0')
	  {
	    putc (ch, g2pw_ok_file);
	    counter++;
	    ch = file_buffer1[counter];
	  }
	break;
      case -2:
	counter = 0;
	ch = file_buffer1[counter];
	while (ch != '\0')
	  {
	    putc (ch, g2pw_ok_file);
	    counter++;
	    ch = file_buffer1[counter];
	  }
	counter = 0;
	ch = file_buffer2[counter];
	while (ch != '\0')
	  {
	    putc (ch, g2pw_ok_file);
	    counter++;
	    ch = file_buffer2[counter];
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

#define DATE_TIME_LEN 24

char *
make_utc_date_string ()
{
  struct tm *utc_tm;
  time_t utc;
  char *cbuf;

  if (time(&utc) != -1)
    if ((utc_tm = gmtime(&utc)))
      if ((cbuf = (char *)malloc(sizeof(char) * DATE_TIME_LEN)))
	if (!strftime(cbuf, DATE_TIME_LEN, "%Y-%m-%d %H:%M:%S UTC", utc_tm))
	  free(cbuf), cbuf = NULL;

  return(cbuf);
}

char *
get_or_make_install_time_string ()
{
  if (install_time_string == NULL)
    install_time_string = make_utc_date_string ();
  return(install_time_string);
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
  char actual_token[500];

  while (TRUE)
  {
	scan_token();
	scan_yank(actual_token);

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
  char token_buffer[500];
  char actual_token[500];
  boolean correct_user = FALSE;

  while(TRUE)
  {
	token_type = scan_token();
	scan_yank(actual_token);

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

	  scan_yank(token_buffer);
	  /* printf("Reading entry for %s\n", token_buffer); */
	  if( strcmp(token_buffer, user_name)==0 )
        correct_user = TRUE;
	  else
		return FALSE;
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
	}

	if(scan_match("end"))
	{
	  if(correct_user==TRUE) {
		password_validity_default_location = scan_token_ftell();
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
#define USER_ENTRY_SIZE 2500

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


void copy_user_entry_if_not_target (from, to, user_name, line)
FILE *from, *to;
char *user_name, *line;
{
  char buffer[USER_ENTRY_SIZE];
  boolean targeted_entry;
  int line_count;

  int count = 0;
  buffer[0] = (char)NULL;

  for (;;)
  {
    line_count = strlen(line);
    count += line_count;
    if (count > USER_ENTRY_SIZE)
	  darn("User entry too large to copy");

	if (line_contains_user_entry(line))
	  targeted_entry = user_line_of_targeted_user(line, user_name, line_count);

	strcat(buffer, line);
	if (strncmp(line, "end user", 8) == 0)
	  break;
    if (fgets(line, LINESIZE - 1, from) == NULL)
	  darn("EOF reached while inside user entry");
  }
  if (! targeted_entry)
    fputs(buffer, to);
}


void copy_all_but_target_user (from, to, user_name)
FILE *from, *to;
char *user_name;
{
  char line[LINESIZE];

  while (fgets(line, LINESIZE - 1, from) != NULL)
  {
	if (strncmp(line, "begin user", 10) == 0)
	  copy_user_entry_if_not_target(from, to, user_name, line);
	else
      fputs(line, to);
  }
}


void g2pw_delete_user_entry
     (ok_file_name, tmp_file_name, user_name)
char *ok_file_name, *tmp_file_name, *user_name;
{
  FILE *tmp_file;

  open_g2ok_file(ok_file_name);
  tmp_file = fopen(tmp_file_name, "w");
  if (! tmp_file)
	darn1("Unable to open the temporary ok file \"%s\"", tmp_file_name);

  copy_all_but_target_user(g2pw_ok_file, tmp_file, user_name);

  fclose(g2pw_ok_file);
  fclose(tmp_file);
  remove(ok_file_name);
  if (rename(tmp_file_name, ok_file_name) != 0)
	darn1("Unable to rename %s to be the ok file", tmp_file_name);
}






/***    Making a watermark file (as part of installing a bundle) ****
*
*  We are calling the record of a successful installation of Gensym *
* software under then new (9/00) 'bundling' scheme a "watermark".  It
* is (1) a file that goes at toplevel in the customer's target
* directory that simply lists who installed what when under what key
* and includes a hash of those facts to inhibit tampering and provide
* us with a means of auditing. (2) Some of those same items are
* copied into the customer's G2 OK file so that the information can
* be presented on the G2 Title Block.
*  ///////////////// this is incorrect (but close) for the 2-entry case /////
* To do this, you call make_watermark with the following seven arguments,
* all of which are strings:
*   (1) The fully qualified pathname of the already-installed G2 OK file
*       including the filename. This file will be modified by this function.
*   (2) The name of the bundle that was installed.
*   (3) The name of the person doing the installation as they entered it.
*   (4) The organization that person belongs to as they entered it.
*   (5) The license key used.
*
* Make_watermark returns 0 if it has run to completion, and returns 1 if
* something went wrong. There is presently no differentiation among the
* possible error returns so there is no way to identify how far through
* the watermark construction process you got before the problem occurred.  */

#define water1 "water"
#define water2 "retaw"
#define water3 "ice"

void hash_watermark (watermark, bundle, user, org, date, key)
char *watermark, *bundle, *user, *org, *date, *key;
{
  g2ext_init_g2_MD5_context(0);
  g2ext_update_g2_MD5_context(0, water1);
  g2ext_update_g2_MD5_context(0, bundle);
  g2ext_update_g2_MD5_context(0, user);
  g2ext_update_g2_MD5_context(0, water2);
  g2ext_update_g2_MD5_context(0, org);
  g2ext_update_g2_MD5_context(0, date);
  g2ext_update_g2_MD5_context(0, key);
  g2ext_update_g2_MD5_context(0, water3);
  {  /* copied from compute_password_hash 
	  for coercing the digest into a hex string */
	  int i;
	  char *p;
	  unsigned char digest[17];
	  g2ext_finalize_g2_MD5_context(0, digest);
	  for (i=0, p=(&watermark[0]); i<16; i++, p+=2) {
		  sprintf(p, "%02x", digest[i]);
	  }
  }
}

void write_watermark_file (directory_path, hash, bundle, user, org, date, key)
char *directory_path, *hash, *bundle, *user, *org, *date, *key;
{
	FILE *file;
	char full_name[500];
	
	strcpy(full_name, directory_path);
	strcat(full_name, "watermark.txt");

	file = fopen(full_name, "w");
	if (!file)
		darn1("Unable to open file to create watermark: \"%s\"", full_name);

	fprintf(file, "# This is an automatically generated file.\n");
	fprintf(file, "# It validates your installation. DO NOT EDIT OR COPY.\n");
	fprintf(file, "Bundle: %s\n", bundle);
	fprintf(file, "Installed by: %s\n", user);
	fprintf(file, "Organization: %s\n", org);
	fprintf(file, "Date installed: %s\n", date);
	fprintf(file, "License key: %s\n", key);
	fprintf(file, "Security code: %s\n", hash);
	fclose(file);
}



int isasciialnum(char c)
{
  if (c > 0 && c < 128)
    return isalnum(c);
  else
    return 0;
}
      

/* add_watermark_to_OK_file() ... Note: it is the caller's responsibility to
ensure there are 499 or fewer characters in the character string org.  If there
are more, the results are undefined, since this may result in a buffer
overflow. */

void add_watermark_to_OK_file (ok_namestring, code, org, key)
char *ok_namestring, *code, *org, *key;
{
	char buff[500];
	char additional_entries[500];
	char *munged_license_key;
	int key_length;
	long position;
	int i;
	int seen_non_digit = 0;	

	g2pw_init_reader(ok_namestring); /* opens the file as g2pw_ok_file */

	/* Find the end of the first machine entry. */
	while (TRUE) {
		scan_token();
		if (scan_match("end")) {
			position = scan_token_ftell();
			if (scan_token_and_match("machine"))
				break;
		}
		if (file_is_done)
			darn("Could not find the end of a machine entry.");				
	}

	
	/* Symbolify the organization */
	for(i=0; i < (int)strlen(org); i++)
	  {
	    if (org[i] == ' ')
	      buff[i] = '-';
	    else if (isasciialnum(org[i]))
	      {
		buff[i] = org[i];
		if (isalpha(org[i]))
		  seen_non_digit = 1;
	      }	    
	    else
	      buff[i] = '_';
	  }
	if (i == 0)
	  {
	    buff[i] = 'x';
	    i++;
	  }
	if (!seen_non_digit)
	  {
	    buff[i] = '_';
	    i++;
	  }
	buff[i] = '\0';

	/* Mung the serial number (license key) so that it isn't usable
	   as an actual installation key (note that this number appears
	   in the Title Block of the G2 and that's a level of security
	   that we care about. This is done by chopping off the last
	   characters from the (normalized) key, removing 15 characters
	   leaves it 10 characters long, which is the present goal as
	   per mhd 9/8/00. */
	key_length = strlen(key);
	munged_license_key = (char *) malloc(key_length * sizeof(char));
	strncpy(munged_license_key, key, key_length - 15);
	munged_license_key[ key_length - 15 ] = '\0';
	/* printf("\nThe original key: '%s'\nThe munged key: '%s'\n", key, munged_license_key); */
	

	/* Now add the additional entries. */
	sprintf(additional_entries,
		"  customer: %s;%s  serial-number: \"%s\";%s  installation-code: \"%s\";%s",
		buff, eol, munged_license_key, eol, code, eol);

	write_string_expanding_ok_file
		(additional_entries, /* string_to_write */
		 ok_namestring,  /* file_name */
		 position,    /* file_scan_location */
		 position,    /* allocation_end_location */
		 '\0');       /* pad char */

	fclose(g2pw_ok_file);
}


char* normalize_license_key (original)
char *original;
{
  char* normalized;
  char c;
  int i = 0;

  normalized = (char *) malloc((strlen(original) + 1) * sizeof(char));
  while ( (c = *original++) != '\0' ) {
    if ( isdigit(c) || isalpha(c) ) {
      c = tolower(c);
      normalized[i] = c;
      i++;
    }
  }
  normalized[i] = '\0';
  return normalized;    
}


/* Returns 0 if its operation is successful. Error returns go out via the
   'darn' mechanism, with a value of 1. */
int make_watermark_file_g2pwaux (directory_path, bundle, user, org, key)
char *directory_path, *bundle, *user, *org, *key;
{
  int status;
  char hash_code[500];
  char *date;
  char *normalized_key;
  
  status = setjmp(g2pw_error_env);
  if (status != 0) 
    return(status); /* error */

  date = get_or_make_install_time_string();
  normalized_key = (char *) normalize_license_key(key);

  hash_watermark (hash_code, bundle, user, org, date, normalized_key);
  write_watermark_file (directory_path, hash_code, bundle, user, org, date, normalized_key);

  return 0;
}


/* Returns 0 if its operation is successful. Error returns go out via the
   'darn' mechanism, with a value of 1. */
int
add_watermark_to_ok_file_g2pwaux (ok_namestring, bundle, user, org, key)
char *ok_namestring, *bundle, *user, *org, *key;
{
  int status;
  char hash_code[500];
  char *date;
  char *normalized_key;
  
  status = setjmp(g2pw_error_env);
  if (status != 0) 
    return(status); /* error */

  date = get_or_make_install_time_string();

  normalized_key = (char *) normalize_license_key(key);
  /* printf("\nThe key is '%s'\nNormalized it is '%s'\n", key, normalized_key); */

  hash_watermark (hash_code, bundle, user, org, date, normalized_key);
  add_watermark_to_OK_file (ok_namestring, hash_code, org, normalized_key);

  return 0;
}










/*** File I/O and Tokenizing Support ***/

static void advance_file_reader()
{
  /* Slide the characters down in file buffer */
  int cnt;    /* = buffer_bottom_mark-buffer_top_mark; */
  strncpy((char*)ok_file_buffer,buffer_top_mark, buffer_bottom_mark-buffer_top_mark);
  /* buffer_top_mark -= cnt; 
     buffer_bottom_mark -= cnt;
     left_of_parsing -= cnt;
     right_of_parsing -= cnt;  

  This is to fix a historical bug that will crash the g2passwd.exe while 
  manipulating large OK file. -- jwang */

  buffer_bottom_mark = buffer_top_mark;
  left_of_parsing = buffer_top_mark;
  right_of_parsing = buffer_top_mark;

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
#ifdef VMS
  g2pw_ok_file = fopen(file_name,"r+","ctx=stm","mrs=32767"); 
#else
  g2pw_ok_file = fopen(file_name,"r+");
#endif /* VMS */
#endif /* WIN32 */
  
  if (! g2pw_ok_file){
    darn1("Unable to open \"%s\" as a G2 OK file", file_name);
  }
}

void g2pw_init_reader(file_name)
char *file_name;
{
  open_g2ok_file(file_name);
  buffer_top_mark = (char*)ok_file_buffer;
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


static char *scan_yank(buffer)
char *buffer;
{
  char *p1 = left_of_parsing;
  char *p2 = buffer;
  while (p1<right_of_parsing)
    *p2++=(*p1++);
  *p2='\000';
  return buffer;
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
				      ||c=='?'));
  scan_ungetchar(c);
  return TRUE;
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
  longjmp(g2pw_error_env, 1);	/* error */
}


/* Darn1 is darn with a single printf argument. */
static void darn1(why, arg)
char *why;
void *arg;
{
  printf("\nERROR: ");
  printf(why, arg);
  printf(".\n");
  longjmp(g2pw_error_env, 1);	/* error */
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

#ifdef __cplusplus
}
#endif
