/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:       g2passwd.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Ben Hyde, David McDonald
 +
 + Description: This is the main module of a program used by the G2 user at a
 +              "secure" site when he wants to change or initialize his
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

#include <ctype.h>     /* character  macros */
#include <string.h>    /* string compair etc. */
#include <setjmp.h>    /* setjmp/longjmp */
#include <stdlib.h>    /* exit */

      /*** Define PROTOTYPES for the benefit of md5_all.h ***/
#include "md5_all.h"   /* md5 hashing */
#include "cprim.h"


      /*** Two platform flavors: unix and WIN32 ***/
#ifdef unix
#  include <termios.h>   /* echo/noecho (struct termios) */
#  include <unistd.h>
#endif                /* unix */

#ifdef WIN32
#  include <windows.h>
#endif  /* WIN32 */




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
#  define PROTOTYPE_ARGS(args) args
#else
#  define PROTOTYPE_ARGS(args) ()
#endif


extern FILE *g2pw_ok_file;
extern int   g2pw_g2_password_is_32_X;
extern jmp_buf g2pw_error_env;        /*  for setjmp/longjmp; defined global in g2pwaux.c */


/*** Forward Function Declarations ***/

int set_up_g2passwd_jump();

/* Top level structure */
void g2pw_validate_input
        PROTOTYPE_ARGS((char *user_name, char *old_password, char *old_password_hashed,
                                        char *new_password1, char *new_password2));

void g2pw_lookup_old_input
        PROTOTYPE_ARGS((char *user_name, char *old_password_hashed));

void g2pw_write_ok_file_password_etc
         PROTOTYPE_ARGS((char *, char *, int));

void g2pw_add_user_entry
         PROTOTYPE_ARGS((char *file_name, char *user_name, char *new_password_hashed,
                        char *mode_list, char *password_decay_date));

void g2pw_modify_decay_date
     PROTOTYPE_ARGS((char *file_name, char *user_name, char *password_decay_date));

void g2pw_delete_user_entry
         PROTOTYPE_ARGS((char *ok_file_name, char *tmp_file_name, char *user_name));


/* Input */
forward_static void prompt_and_get PROTOTYPE_ARGS((char *prompt,
                                                   char *result,
                                                   boolean echo_p,
                                                   char *testing_argument));
forward_static void get_string PROTOTYPE_ARGS((char *result, boolean echo));
forward_static void compute_password_hash
        PROTOTYPE_ARGS((char *user_name,
                        char *incomming_password,
                        char *hashed_password));
void g2pw_revise_ok_file PROTOTYPE_ARGS((char *name,
                                                   char *hashed_password));

void g2pw_new_revise_ok_file
        PROTOTYPE_ARGS((char *, char *));

forward_static void change_password_to_lowercase
        PROTOTYPE_ARGS((char *));
forward_static void canonicalize_user_name
        PROTOTYPE_ARGS((char *, char *));



/* Shutdown */
void g2pw_darn  PROTOTYPE_ARGS((char *why));
void g2pw_darn1 PROTOTYPE_ARGS((char *why, void *arg));

/* Lexer */
forward_static void initialize_reader  PROTOTYPE_ARGS((char *name_of_ok_file));

void g2pw_init_reader PROTOTYPE_ARGS((char *file_name));
boolean g2pw_scan_text PROTOTYPE_ARGS((char *text));


/* Low Level Terminal I/O */

forward_static void ttycbreak PROTOTYPE_ARGS((void));
forward_static void ttynorm PROTOTYPE_ARGS((void));
forward_static int getch PROTOTYPE_ARGS((void));
forward_static void putch PROTOTYPE_ARGS((char c));

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
#define G2PW_GOOD_RESULT 111
#define G2PW_AREYOUTHERE_ARG "-areyouthere"


/* Cases in the toplevel dispatch */
#define SET_PASSWORD 1
#define ADD_USER 2
#define MODIFY_DECAY_DATE 3
#define DELETE_USER 4



/*** Top Level Routines ***/

/*
 * The function `main' finds the ok file, interacts with the user on standard
 * input, valdates is inputs, and finally edits the ok file. Subfunctions are
 * allowed to do non-local exits via calls upon g2pw_darn.  (These no longer call
 * exit indirectly, but do return control to the top-level entry point.)
 */


static int g2passwd_main(argc, argv)  /* VMS doesn't like a main to be void */
int argc;
char *argv[];
{

  char user_name[500], old_password[500];
  char canonical_user_name[500];
  char new_password_1[500], new_password_2[500];
  char old_password_hashed[500], new_password_hashed[500];
  char operation_name[50], mode_list[1000], password_decay_date[50];
  int ignored_error_code;
  int what_to_do;
  int empty_password = FALSE;
  int replacing_password = FALSE;
  int pre_allocated_space = FALSE;

  if (FALSE) /* debug the argument count and what they are. */
  { int i;
    printf("Arg count = %d\n", argc);
        for(i=0; i<argc; i++) {
          printf("\nArg %d = %s", i, argv[i]);
        }
  }

  if (argc!=2 && argc!=4 && argc!=5 && argc!=7 ){
        /* the argc==2 case is the public case, the rest are internal */
    g2pw_darn("One argument required, the OK file name");
  }

  what_to_do = SET_PASSWORD; /* default */


  /* handle special protocol to tell Lisp module SEQUENCES2 we're g2passwd */
  if (strcmp(argv[1], G2PW_AREYOUTHERE_ARG) == 0)
    return(G2PW_GOOD_RESULT);


  if (argc!=2) /* useful log output when driven programmatically */
    printf("\ng2passwd operating on %s\n", argv[1]);


  if (argc==2)
    {
      /* Discuss this with the user. */
      ttycbreak();   /* Go into noecho/single character mode */
                                /* from here to the following
                                 * ttynorm, code in the dynamic
                                 * extent of this function must
                                 * must restore the terminal
                                 * using ttynorm() before any
                                 * "exit" (calling g2pw_darn, g2pw_darn1).
                                 */
      prompt_and_get("User name: ",
                     user_name, TRUE, (argc==5?argv[2]:NULL));
      prompt_and_get("Current Password: ",
                     old_password,  FALSE, (argc==5?argv[3]:NULL));
      prompt_and_get("New Password: ",
                     new_password_1, FALSE, (argc==5?argv[4]:NULL));
      prompt_and_get("New Password again: ",
                     new_password_2, FALSE, (argc==5?argv[4]:NULL));
      ttynorm();     /* Restore the terminal to saved setting */

      canonicalize_user_name(user_name, canonical_user_name);
      if(strlen(old_password)>0)
        {
          change_password_to_lowercase (old_password);
          compute_password_hash(user_name, old_password, old_password_hashed);
        }
      else
        strcpy(old_password_hashed, "\"\"");

      initialize_reader(argv[1]);
      g2pw_validate_input(user_name, old_password, old_password_hashed,
                     new_password_1, new_password_2);

          canonicalize_user_name (user_name, canonical_user_name);
      change_password_to_lowercase (new_password_1);
      compute_password_hash(canonical_user_name, new_password_1, new_password_hashed);
    }

  else if (argc==4)
    {
      /* Signature for programmatically setting initial, empty passwords. */
      strcpy(user_name, argv[2]);
      strcpy(old_password_hashed, "\"\"");
      strcpy(new_password_hashed, argv[3]);
          empty_password = TRUE;

      initialize_reader(argv[1]);
      g2pw_lookup_old_input(user_name, old_password_hashed);
    }

  else if (argc==5)
    {
          /* Signature for changing passwords programmatically. */
      strcpy(user_name, argv[2]);
      strcpy(old_password_hashed, argv[3]);
      strcpy(new_password_hashed, argv[4]);
      replacing_password = TRUE;

      initialize_reader(argv[1]);
      g2pw_lookup_old_input(user_name, old_password_hashed);
    }

  else if (argc==7)
    {
          /* Signature for general purpose operations. */
          strcpy(operation_name, argv[2]);
          strcpy(user_name, argv[3]);
          strcpy(new_password_hashed, argv[4]);
          strcpy(mode_list, argv[5]);
          strcpy(password_decay_date, argv[6]);

      /* going through this int middle-man might be wasteful, oh well. */
          if (!strcmp(operation_name,"add"))
                  what_to_do = ADD_USER;
          else if (!strcmp(operation_name,"modify-decay-date"))
                  what_to_do = MODIFY_DECAY_DATE;
          else if (!strcmp(operation_name,"delete"))
                  what_to_do = DELETE_USER;
          else g2pw_darn("unknown operation");
        }

  else
    {
      g2pw_darn("unknown signature");
    }



  /* Act on what we've extracted from the signatures */

  if (what_to_do==SET_PASSWORD) {

          /* Changing the password involves modifying the OK file, either
          by replacing an existing password (always 32 characters long)
          or by filling the gap between the two double quote characters
          of an empty string ("") with a 32 character password. In this
          filling case we will need to extend the file, which is a
          moderately complex operation involving a lot of buffering and
          writing done by write_string_expanding_ok_file. These two cases
          are differentiated by passing along a parameter indicating the
          number of spaces within the file that are already occupied by
          a password: 32 in the replacement case and 0 in the fill case.
          In the interactive case, the old_password is taken from the
          user and will be >0 if they already have a password.
          In the programmatic case we use two explicit flags. The final
          else clause below corresponds to the interactive case where
          the user's initial password is "".
          */
          if (empty_password)
                   pre_allocated_space = FALSE;
          else if (replacing_password)
                   pre_allocated_space = TRUE;
          else if ((strlen(old_password)>0)
               || (g2pw_g2_password_is_32_X == 1))
                   pre_allocated_space = TRUE;
      else pre_allocated_space = FALSE;        

    g2pw_write_ok_file_password_etc
      (new_password_hashed,
       argv[1],  /* file_name */
       (pre_allocated_space
        ? 32 : 0));

    ignored_error_code = fclose(g2pw_ok_file);
    return 0;                        /* 0 indicates success */
  }


  else if (what_to_do==ADD_USER)
  {
        initialize_reader(argv[1]);
        g2pw_add_user_entry
          (argv[1], /* file name */
           user_name, new_password_hashed, mode_list, password_decay_date);
        return 0;
  }

  else if (what_to_do==MODIFY_DECAY_DATE)
  {
        initialize_reader(argv[1]);
        g2pw_modify_decay_date
          (argv[1], user_name, password_decay_date);
        return 0;
  }

  else if (what_to_do==DELETE_USER)
  {
        g2pw_delete_user_entry
          (argv[1], /* name of ok file */
           argv[4], /* name of the temp file */
           user_name);
        return 0;
  } else {
    g2pw_darn("unknown operation"); /* Not reached, paranoia. */
    return -1;                        /* Also not reached, since g2pw_darn longjmps */
  }
}



extern int main(argc, argv)  /* VMS doesn't like a main to be void */
int argc;
char *argv[];
{

  int status;

  status = setjmp(g2pw_error_env);
  if (status != 0)
    exit(status); /* error */
  status = g2passwd_main(argc, argv);

  exit(status);                        /* exit with status */
  return(0);                        /* return unreachable; this gags the compiler */
}

/** initialize_reader is a subroutine that encasulates setup operations
    that is needed by every action that uses the standard file i/o
        abstractions, e.g. set_password. It also does a sanity check on
        the file */

static void initialize_reader (name_of_ok_file)
char *name_of_ok_file;
{
  g2pw_init_reader(name_of_ok_file);

  if(!g2pw_scan_text("begin g2-ok-file")){
    g2pw_darn("An OK file must begin with \"begin g2-ok-file\"");
  }
}




/* This is the fix for HQ-1427744 - change the g2password to upper case. */

static void change_password_to_lowercase (new_password)
  char new_password[500];
{
  int i = 0;

  while (new_password[i] != '\0')
    {
     new_password[i] = tolower (new_password[i]);
     i++;
    }
}

/* This is the fix for HQ-3394703 - to allow mixed case user names to
   be handled the same way as they are within G2. */

static void canonicalize_user_name (user_name, canonical_user_name)
  char user_name[256];
  char canonical_user_name[256];
{
  int i=0;
  while (user_name[i] != '\0')
  {
    canonical_user_name[i] = tolower(user_name[i]);
        i++;
  }
  canonical_user_name[i] = '\0';
}


/*
 * Prompt_and_get reads input from the user, echo is optional.
 * This should be called within a ttycbreak contour.
 **/

static void prompt_and_get(prompt, result, echo_p, testing_argument)
char *prompt, *result;
boolean echo_p;
char *testing_argument;
{
  if ( testing_argument!=NULL ){
    strcpy(result, testing_argument);
    return;
  }
  printf("%s", prompt);
  get_string(result,echo_p);
}

#define Control_C  3
#define BS 8
#define LF 10
#define CR 13
#define Control_Y 25
#define DEL 127

static void get_string(result,echo)
char *result;
boolean echo;
{
  int maxlen = 400;
  int i;
  char c;

  fflush(stdout);
  fflush(stderr);
  i=0;
  for (;;) {
    c = getch();
    if (c == Control_C) g2pw_darn("Interupted");  /* Control C */
    if (c==BS || c==DEL) {
      if (i) {
        if (echo) {
          putch(BS);
          putch(' ');
          putch(BS);
        }
        i--;
      } else {
        putch('\007');
      }
      continue;
    }
    if (c < ' ' && c != LF && c != CR) {
      putch('\007');
      continue;
    }
    if (echo) putch(c);
    if (c==CR) {
      if (echo) putch(LF);
      break;
    }
    if (c==LF) break;
    if (c=='\n') break;
    result[i++] = c;
    if (i >= maxlen) {
      fputs("\007*\n", stderr);        /* -Enough! */
      break;
    }
  } /* for */
  result[i] = '\0';        /* null termination of string */
  if(!echo) putch('\n');
  return;
}






/* Compute_password_hash is a oneway hash of the user's password */

static void compute_password_hash(user_name,
                                  incomming_password,
                                  hashed_password)
char *user_name, *incomming_password, *hashed_password;
{
  g2ext_init_g2_MD5_context(0);
  g2ext_update_g2_MD5_context(0,"user:");
  g2ext_update_g2_MD5_context(0,user_name);
  g2ext_update_g2_MD5_context(0,":password:");
  g2ext_update_g2_MD5_context(0,incomming_password);
  {
    /* Coerce md5 digest into hex string */
    int i;
    char *p;
    unsigned char digest[17];
    g2ext_finalize_g2_MD5_context(0,digest);
    for(i=0,p=(&hashed_password[0]);
        i<16;
        i++,p+=2){
      sprintf(p,"%02x",digest[i]);
    }
  }
}



/**** Low Level Terminal I/O ****/

/*
 * This section implements The two routines used by the code
 * above that reads input.
 *   ttynorm   -- leaves the terminal in some "normal state."
 *   ttycbreak -- leaves the terminal in noecho single character mode.
 **/

/*
 * This code is structured with on routine that is conditionally compiled
 * to work on all platforms.  There are these variations of plaform
 *  - UNIX
 *  - Windows
 *
 * This code is derive from the system.c module of the pgp sources.
 * In there we find - very roughly - three flavors of I/O for unix
 *   1. struct termios
 *   2. struct termio
 *   3. struct sgttyb
 * In this code only have the first case.
 *
 **/

#ifdef unix

/* Global hold the remembered terminal settings */
static struct termios itio, tio;

/*
 * We presume that standard input is a terminal, things
 * will abort gracefully if not.
 **/
#define TTYFD 0

static boolean ttycbreak_p = FALSE;

/*
 * `ttycbreak' is called to place the terminal into single
 * character mode, with echo supressed.
 **/

static void ttycbreak()
{
  if ( tcgetattr(TTYFD, &tio) < 0 ){
    g2pw_darn("Unable to obtain current terminal settings");
  }
  itio = tio;  /* Save for retore in ttynorm() */
  tio.c_cc[VMIN] = 1;
  tio.c_cc[VTIME] = 0;
  tio.c_lflag &= ~(ECHO|ICANON);
  tcsetattr (TTYFD, TCSAFLUSH, &tio);
  ttycbreak_p = TRUE;
}


/*
 * `ttynorm' is called to restore the terminal's settings.
 * This is the inverse of ttycbreak.
 **/

static void ttynorm()
{
    if (ttycbreak_p){
    tcsetattr (TTYFD, TCSAFLUSH, &itio);
  }
}


/*
 * `getch' returns a single character's char code from the i/o TTY as an int,
 * returning a negitive is something is broken.
 **/

static int getch()
{
        char c;
        int read_result;

        read_result = read(TTYFD, &c, 1);
        if(read_result==1) return (int)c;
        else return read_result;
}

/* `putch' outputs a single character to the TTY */

static void putch(c)
char c;
{
  putc(c,stdout);
  fflush(stdout);
}

#endif /* unix */


#ifdef WIN32


static HANDLE hStdout, hStdin;
static DWORD fdsOldMode;
static boolean ttycbreak_p = FALSE;
/* `ttycbreak' for WIN32 -- see unix for doc. */

static void ttycbreak()
{
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  if ( hStdin == INVALID_HANDLE_VALUE
       || hStdout == INVALID_HANDLE_VALUE ){
    g2pw_darn("Unable to get handle to console");
  }
  if(!GetConsoleMode(hStdin, &fdsOldMode)){
    g2pw_darn("Unable to obtain the console's modes");
  }
  if(!SetConsoleMode(hStdin,
                     fdsOldMode
                     & ~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT))){
    g2pw_darn("Unable to set the console's modes");
  }
  ttycbreak_p = TRUE;
}

/* `ttynorm' for WIN32 -- see unix for doc. */

static void ttynorm()
{
  if(ttycbreak_p){
    ttycbreak_p=FALSE;
    if(!SetConsoleMode(hStdin, fdsOldMode)){
      g2pw_darn("Unable to reset the console's modes");
    }
  }
}

/* `getch'  for WIN32 -- see unix for doc. */

static int getch()
{
  char chBuffer[10];
  DWORD cRead;

  if(!ReadFile(hStdin, chBuffer, 1, &cRead, NULL)){
    g2pw_darn("Unable to read characters from console");
  }
  return (int)(chBuffer[0]);
}

/* `putch' for WIN32 -- see unix for doc. */

static void putch(c)
char c;
{
  char chBuffer[10];
  DWORD cRead = 1;
  DWORD cWritten;

  chBuffer[0]=c;
  if(!WriteFile(hStdout, chBuffer, cRead, &cWritten, NULL)){
    g2pw_darn("Unable to write characters to console.");
  }
}

#endif /* WIN32 */
