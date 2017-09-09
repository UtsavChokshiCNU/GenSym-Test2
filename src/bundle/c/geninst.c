/* $Id: geninst.c,v 1.35 2007-07-03 15:40:03 yduj Exp $ */

#include <sys/types.h>
#include <sys/ioctl.h> /* for 4.3BSD alikes (AIX) */
#include <sys/stat.h>  /* For stat() function. */
#include <sys/statvfs.h>

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "codes.h"
#include "gsm.h"
#include "key-common.h"
#include "license.h"
#include "family-descriptor.h"
#include "components.h"

#define PERROR_EXIT(message) do {                                \
  fprintf(stderr, "(%s) %s at \"%s\":%d: %s\n",                  \
      executable, message, __FILE__, __LINE__, strerror(errno)); \
  abort(); } while (0)

#define DEFAULT_TERMINAL_ROWS 24
#define DEFAULT_ROOT "/usr/gensym"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

static char *welcome_banner[] =
{
  "",
  "Gensym Installer " BUNDLE_INSTALLER_VERSION,
  "Copyright (C) 1986-2017 Gensym Corporation.",
  "All Rights Reserved.",
  "",
  NULL
};

extern unsigned char read_buf[];

extern void establish_sigchld_handler();
extern int find_tar_executable(char**);
extern FILE *open_output_pipe_for_command(char*, char**, char*);
extern int wait_for_child_with_heartbeat();
extern int get_system_name(unsigned char, char**);
extern void initialize_crypt();
extern void crypt_buffer(unsigned char*, unsigned char*, int, unsigned int);
extern int read_file_header(FILEHEADER*,FILE*);
extern int read_and_decrypt_gsm_family_file(FILE*,int,unsigned char*,unsigned int);
extern void set_bufptr_for_get_line(unsigned char*);
extern int key_to_keystruct(char*,LICENSE_KEY*);
extern FAMILY_DESCRIPTOR *new_family();
FAMILY_DESCRIPTOR *global_family_desc; /* new. -mhd, 5/25/01 */
extern int parse_family_file(FAMILY_DESCRIPTOR*);
extern int make_watermark_file_g2pwaux (char *directory_path, char *bundle, char *user,
                    char *org, char *key);
extern add_watermark_to_ok_file_g2pwaux (char *ok_namestring, char *bundle, char *user,
                    char *org, char *key);

char *executable;
static struct termios *saved_termios = NULL;


/* An error has occurred, either due to user input or to a system error.
 * Inform the user and terminate execution.
 */
void exit_error(char *msg, int code)
{
    fprintf(stderr, "Error: %s\n", msg);
    if (code != 0) {
        fprintf(stderr, "  Error code: 0x%05x\n", code);
    }
    fprintf(stderr, "Terminating installation\n");
    exit(1);
}

/* Modify the string to trim both leading and trailing whitespace.
 * For trailing whitespace, simply move the null terminator.  For
 * leading whitespace, shift characters left appropriately.
 */
void trim_whitespace(char *str)
{
    char *tailptr;
    char *headptr;

    /* Strip trailing whitespace. */
    tailptr = str + strlen(str) - 1;
    while ( (strlen(str) > 0) && isspace(*tailptr))
        *tailptr-- = '\0';

    /* Pass leading whitespace. */
    headptr = str;
    while (isspace(*headptr))
        headptr++;

    if (headptr == str)
        return;   /* No leading whitespace to trim. */

    /* Strip the leading whitespace by shifting it left. */
    while (*str++ = *headptr++)
        ;  /* empty body */

    return;
}

/* Check whether the named file or directory exists.  This could be more
 * strict about looking at failure types.
 *   return value: 1 if it exists, 0 if not
 */
int file_exists (char *name)
{
    struct stat s;

    if ( stat(name,&s) == -1)
        return 0;
    else
        return 1;
}

extern void execute_postinstall_step(char * input, char * basedir);

extern int check_for_file(char* filename)
{
  int hack, returnval;
  struct stat s;
  for (hack = 0; hack < 4; hack++) {
    /* HQ-4578352: There's a race somewhere that the file doesn't
       necessarily land on the disk before we need it when the directory
       is NFS mounted.  So we are handicapping this race by trying to look
       for the file before we need it, and sleeping a second if it's not
       there.  If we don't find it by four times, though, we'd better give
       up because maybe there really was a bug and we shouldn't infinite
       loop. --yduJ 6/5/03 */
    if ( returnval = stat(filename,&s) == -1)
      sleep(1);
  }
  return returnval;
}
  
/* Use the rename vector that was created by create_tar_and_rename_vectors
 * to rename files as needed.  The tarv and renamev vectors are parallel
 * vectors.  tarv is needed to determine how many elements there are in
 * renamev.  Because tarv and renamev entries are relative to basedir,
 * the basedir must be prepended.
 */

int rename_files (char *tarv[], char *renamev[], boolean obfuscatev[], char *postinstallv[], char *basedir)
{
    int i;
    int retval;
    int status;
    char fullbase[1024];   /* These are generously large. */
    char oldname[1024];
    char newname[1024];

    /* Precreate the full base directory. */
    strncpy(fullbase, basedir, 256);
    strcat(fullbase,"/");

    retval = SUCCESS;  /* Default value. */
    i = 3;             /* Skip tar command and options. */
    while (tarv[i] != NULL) {
      strcpy(oldname,fullbase);
      strcpy(newname,fullbase);
      strncat(oldname,tarv[i],750);
      if (renamev[i] != NULL) {
	strncat(newname,renamev[i],750);
	if ((status = check_for_file(oldname)) == 0)
	  status = rename(oldname, newname);
	if (status != 0) {
	  retval = FILE_RENAMING_ERROR;
	  fprintf(stderr,"Error: unable to rename %s: ",newname);
	  perror(NULL); /* print actual problem. Too bad perror doesn't take printf args. */
	  break;
	}
      }
      if (obfuscatev[i])
	set_log_file_info((renamev[i] ? newname : oldname),
			     global_family_desc->fd_guid);
      if (postinstallv[i])
	execute_postinstall_step(postinstallv[i],basedir);
      i++;
    }
    return retval;
}

/* Create the tar vector for the tar invocation, and in the same pass
 * create a parallel vector of files for renaming.  To create the filename
 * arguments, walk through the list of selected components and create
 * full-path filenames for each part to be installed.
 *   returns:
 *     return value: SUCCESS or error value
 *     tarv:  Populated with tar command and list of files.  This is
 *            the argv to be passed directly to execve().
 *     renamev: An array parallel to argv.  If an entry is present, it
 *            is to be renamed.  If NULL, no renaming is needed.
 *     obfuscatev: An array parallel to argv.  If an entry is true (1), it
 *            is to be unobfuscated in place.  If false, it's left as is.
 *            Only entries corresponding to non-NULL tarv entries are valid.
 */
int create_tar_and_rename_vectors (char *tarv[],
                                   char *renamev[],
				   boolean obfuscatev[],
				   char* postinstallv[],
                                   LICENSED_COMPONENTS *lc,
                                   unsigned int sysid)
{
    int argi, i;
    COMPONENT *cmpt;
    PART *prt;
    FILE_DATA *flist;

    /* a really bad idea manifested itself here.  To wit, we used to try to
       obscure the program name, but tar objected on Alpha OSF. */
    tarv[0] = NULL;
#ifndef DONT_BE_QUIET
    tarv[1] = strdup("xfo");
#else
    tarv[1] = strdup("xvfo");
#endif
    tarv[2] = strdup("-");

    for (i=0; i<3; i++) {
        renamev[i] = NULL;
    }

    argi = 3;
    for (i=0; i<NUMBER_OF_COMPONENTS; i++) {
        cmpt = lc->components[i].component;
        if ( (cmpt == NULL) || !(lc->components[i].selected) )
            continue;
        for (prt = cmpt->cp_first_part; prt!=NULL; prt=prt->pt_next_part) {
            if ( !available_on_os(prt,(int)sysid) )
                continue;   /* part not available on platform */
            flist = prt->pt_first_file_data;
	    /* postinstall code should really be per file, to go along with the tar vector. */
	    if (prt->pt_postinstall_code)
	      postinstallv[argi] = strdup(prt->pt_postinstall_code);
	    else
	      postinstallv[argi] = NULL;
            while (flist != NULL) {
	        obfuscatev[argi] = flist->fd_obfuscate;
                renamev[argi] = NULL;  /* preset default value */
                if (flist->fd_source_name == NULL) {
                    if (flist->fd_destination_directory == NULL)
                        /* Could only happen if parser allowed illegal case.*/
                        break;  
                    tarv[argi] = strdup(flist->fd_destination_directory);
                } else if (flist->fd_destination_directory != NULL) {
                    /* The destination directory is non-empty. */
                    tarv[argi] = (char *)malloc((size_t)
                        (strlen(flist->fd_destination_directory)
                        + strlen(flist->fd_source_name) + 2));
                    strcpy(tarv[argi], flist->fd_destination_directory);
                    strcat(tarv[argi], "/"); /* directory separator */
                    /* Take care of the renamed file. */
                    if (flist->fd_destination_name != NULL) {
                        renamev[argi] = (char *)malloc((size_t)
                            (strlen(tarv[argi])
                            + strlen(flist->fd_destination_name) + 1));
                        strcpy(renamev[argi],tarv[argi]);
                        strcat(renamev[argi],flist->fd_destination_name);
                    }
                    /* Finish creating the tarv name. */
                    strcat(tarv[argi], flist->fd_source_name);
                } else {
                    /* The destination directory is the top-level directory.*/
                    tarv[argi] = strdup(flist->fd_source_name);
                    /* Take care of the renamed file. */
                    if (flist->fd_destination_name != NULL) {
                        renamev[argi] = strdup(flist->fd_destination_name);
                    }
                }
                argi++;
                if (argi > MAX_ARGS_TO_TAR-2) /* Last tarv must be NULL */
                    return TAR_ARGS_EXCEEDED; /* There should be enough.*/
                flist = flist->fd_next_file_data;
            }
        }
    }
    tarv[argi] = NULL;   /* Terminate the argument lists. */
    renamev[argi] = NULL;
    return SUCCESS;
}

/* This takes care of the details of spawning tar with the needed
 * files/directories as arguments, piping the tar file to the
 * spawned process, and printing a heartbeat to show progress.
 */
int run_tar_on_pipe (char *argvector[],
                     FILE *gsm_infile,
                     char *workingdir,
                     unsigned int xor_mask)
{
    unsigned char crypt_buf[ACTUAL_PRECRYPT_BUFFER_SIZE];
    size_t bytes_written;
    size_t bytes_read;
    FILE *outpipe;
    char *tarcmd = NULL;
    int status;
    int i;

    status = find_tar_executable(&tarcmd);
    if ((status != SUCCESS) || (tarcmd == NULL)) {
        return NO_TAR_EXECUTABLE_FOUND;
    }

    argvector[0] = strdup(tarcmd);

    outpipe = open_output_pipe_for_command(tarcmd, argvector, workingdir);
    if (outpipe == NULL) {
        return SPAWN_ERROR;
    }

    initialize_crypt();
    while (!feof(gsm_infile)) {
        printf("*");       /* active heartbeat */
        fflush(stdout);
        bytes_read = fread(read_buf, 1, PRECRYPT_BUFFER_SIZE, gsm_infile);
        if (bytes_read <= 0) {
            return GSM_FILE_TAR_READ;
        }
        crypt_buffer(read_buf, crypt_buf, bytes_read,
            xor_mask); /* Encrypt the buffer.*/
        bytes_written = fwrite(crypt_buf, 1, bytes_read, outpipe);
        if (bytes_written != (size_t) bytes_read) {
            /* We've found that hpux will close the pipe early for large
             * files when nothing remains except nulls, so we check for
             * this condition and ignore it.  */
            for (i=bytes_written; i<bytes_read; i++)
                if (crypt_buf[i] != 0) {
                    fclose(outpipe);
                    return TAR_PIPE_WRITE;
                }
        }
    }
    fclose(outpipe);
    return wait_for_child_with_heartbeat();
}

void
tty_cbreak()
{
  struct termios term;

  if (!(saved_termios = (struct termios *)malloc(sizeof(struct termios))))
    PERROR_EXIT("malloc");

  if (tcgetattr(fileno(stdin), &term) < 0)
    return;

  memcpy(saved_termios, &term, sizeof(struct termios));
  term.c_lflag &= ~(ECHO | ICANON);
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;

  tcsetattr(fileno(stdin), TCSAFLUSH, &term);

  return;
}

void
tty_reset()
{
  if (saved_termios) {
    tcsetattr(fileno(stdout), TCSAFLUSH, saved_termios);
    free(saved_termios);
    saved_termios = NULL;
  }

  return;
}

/*ARGSUSED*/
static void
sigint_handler(int signal)
{
  tty_reset();
  
  exit(1);
}

#define qa_secret_automation geninst2
static int qa_secret_automation = 0;

void
print_license_agreement (char **license_text)
{
  struct winsize win;
  char **cptr = license_text;
  int i = 0, row;

  if (qa_secret_automation)
    row = 1000;
  else
    if (ioctl(fileno(stdout), TIOCGWINSZ, &win) == -1)
      row = DEFAULT_TERMINAL_ROWS;
    else 
      row = win.ws_row;
  
  putchar('\n');

  if (!qa_secret_automation)
    tty_cbreak();

  do {
    puts(*cptr++);

    if (++i == (row - 1)) {
      printf(" - NEXT PAGE - ");
      getchar(); 
      i = 0;
      putchar('\n');
    }
  } while (*cptr != NULL);

  if (!qa_secret_automation)
    tty_reset();

  putchar('\n');

  return;
}

char *
solicit_and_create_installation_directory(LICENSED_COMPONENTS *lc)
{
  char cbuf[_POSIX_MAX_INPUT], default_path[_POSIX_PATH_MAX], *effective_path;

  memset(cbuf, 0, sizeof(cbuf)); 
  memset(default_path, 0, sizeof(default_path));
  sprintf(default_path, "%s/%s", DEFAULT_ROOT, lc->family->fd_directory_name);

  for (;;) {
    printf("Enter installation directory (q to quit) [%s] : ", default_path);
    if (!fgets(cbuf, sizeof(cbuf) - 1, stdin))
      continue;
        
    trim_whitespace(cbuf); /* also takes care of final LF */
    if (!strcasecmp(cbuf, "q")) {
      printf("Terminating installation at user's request.\n");
      exit(1);
    }
        
    if (strlen(cbuf) == 0) /* the user accepted the default path */
      strcpy(cbuf, default_path);

    if (!(effective_path = (char *)malloc(sizeof(char) * strlen(cbuf) + 1))) 
      PERROR_EXIT("malloc");
    else
      strcpy(effective_path, cbuf);

    if (create_directories_recursively(effective_path)) {
      printf("Sorry, the directory \"%s\" could not be created.\n", effective_path);
      continue;
    }
     
    if (create_directories_recursively(effective_path) || access(effective_path, W_OK))
      if (errno == EACCES || errno == EROFS) {
	printf("Sorry, the directory \"%s\" does not appear to be writeable.\n", effective_path);
	continue;
      } else
	PERROR_EXIT("access");
      
    else
      break; /* success */

    free(effective_path);
  }

  return effective_path;
}

void
loosely_validate_free_space(char *install_path, FILE *gsm_file)
{
  struct stat buf;
  struct statvfs vfsbuf;

  /* first get the size of our file.  The files to be unpacked are approximately
     the same, since we're not compressing */
  if (fstat(fileno(gsm_file), &buf))
    PERROR_EXIT("fstat");
  
  /* now get the information about the file system itself */
  if (statvfs(install_path, &vfsbuf))
    PERROR_EXIT("statvfs");

  /* file system information (vfsbuf.f_bavail) is in blocks, and file size
     information (buf.st_size) is in bytes.  So divide the file size to compare. */
  if ((buf.st_size / vfsbuf.f_bsize) > vfsbuf.f_bavail) {
    printf("There is not enough free space in \"%s\" to perform a full install.\n", install_path);
    if (!yes_or_no_p("Do you still wish to continue?")) {
      printf("Prematurely exiting at the user's request.\n");
      exit(1);
    }
  /* Note: We used to multiply blocks by blocksize to get bytes to do the
     comparison.  But that had problems when the amount of free space was more
     than 2GB: HQ-3961566 "Linux installation gets not enough free space error
     message".  So now we use blocks for the comparison.  Note that someone who
     had enough terabytes in their file system might run into this problem even
     using the blocks comparison.  "Enough" depends on the filesystem's
     preferred block size, so might be as little as 1TB or as much as 16TB. */
  }

  return;
}

/* Print information about bundle name and platform. */
void print_licensed_product_banner(unsigned char sysid, char *bdl_name)
{
    char *system_name;
    int status;

    status = get_system_name(sysid,&system_name);

    printf("\n\n\nYou are licensed to install %s for %s\n\n",
        bdl_name, system_name);
}

/* Determine whether the key's fields correspond to those in the header.
 * Exit if not.
 */
void validate_key_against_header_or_exit(FILEHEADER *h, LICENSE_KEY *k)
{
    int error_code;

    error_code = SUCCESS;

    if (h->installer_version != k->installer_version)
        error_code = KEY_HEADER_INSTALLER_MISMATCH;

    if (h->family_id != k->family_id)
        error_code = KEY_HEADER_FAMILY_MISMATCH;

    if (h->system_id != k->system_id)
        error_code = KEY_HEADER_SYSTEM_MISMATCH;

    if (error_code != SUCCESS)
        exit_error("Key is invalid for the .gsm file", error_code);
}

/* Determine whether the key's installer version and family_id correspond
 * to those of the family file (and of the header, which has already been
 * checked against the key).
 */
void validate_key_against_family_or_exit(FAMILY_DESCRIPTOR *f, LICENSE_KEY *k)
{
    int error_code;

    error_code = SUCCESS;

    if ((unsigned char)(f->fd_id) != k->family_id)
        error_code = KEY_TO_FAMILY_ID_MISMATCH;

    if (f->fd_installer_version != k->installer_version)
        error_code = KEY_TO_FAMILY_INSTALLER_MISMATCH;

    if (error_code != SUCCESS)
        exit_error("Key is invalid for the .gsm file", error_code);
}

/* Use the fields from the key to identify the fields of the family
 * descriptor structure that are licensed, and set them in
 * the licensed component structure.  Return an appropriate error
 * code if the fields are not defined in the family file.
 */
int populate_license_components(FAMILY_DESCRIPTOR *f,
                                LICENSE_KEY *k,
                                LICENSED_COMPONENTS *lc)
{
    BUNDLE *bdl;
    COMPONENT *cmpt;
    int i;

    lc->family = f;
    bdl = f->fd_first_bundle;
    while (bdl != NULL) {
        if ((unsigned char)(bdl->bdl_id) == k->bundle_id) {
            lc->bundle = bdl;
            break;
        }
        bdl = bdl->bdl_next_bundle;
    }

    if (bdl == NULL)
        return BUNDLE_NOT_IN_FAMILY;

    /* Initialize components to empty. */
    for (i=0; i<NUMBER_OF_COMPONENTS; i++) {
        lc->components[i].component = NULL;
        lc->components[i].selected  = 0;
    }

    cmpt = bdl->bdl_first_component;
    while (cmpt != NULL) {
        i = cmpt->cp_index;
        if (i<0 || i>NUMBER_OF_COMPONENTS-1)
            return BAD_COMPONENT_INDEX_FOUND;
        if (k->components[i]) {   /* if licensed, add it */
            lc->components[i].component = cmpt;
            lc->components[i].selected = 1;
        }
        cmpt = cmpt->cp_next_component;
    }

    return SUCCESS;
}

/* Get the directory and name of the gensym.gsm file from the user,
 * check for its existence, then open it.
 *   return value:  file descriptor of opened .gsm file.
 */
FILE *solicit_and_open_gsm_file_or_exit()
{
    char *defaultgsm;
    char *gsmfile;
    FILE *gsmfd;

    defaultgsm = "/cdrom/gensym.gsm";  /* Normal Unix default. */

    /* Override the default if appropriate. */
#   ifdef WIN32
        defaultgsm = "d:\\gensym.gsm";  /* For development only */
#   endif
#   ifdef __hp9000s800
        defaultgsm = "/cdrom/GENSYM.GSM;1";
#   endif
#   ifdef sparc
        defaultgsm = "/cdrom/cdrom0/gensym.gsm";
#   endif

    gsmfile = (char*)malloc(256);
    while (1) {
        printf("Enter installation file (q to quit) [%s] : ",
            defaultgsm);
        fgets(gsmfile, 254, stdin);
        
        trim_whitespace(gsmfile); /* also takes care of final LF */
        
        if ( (strlen(gsmfile) == 1)
              && (gsmfile[0] == 'q' || gsmfile[0] == 'Q') ) {
            printf("Terminating installation at user's request.\n");
            exit(0);
        }
        
        if (strlen(gsmfile) == 0) {
            strcpy(gsmfile, defaultgsm);
        }

        if ( file_exists(gsmfile) ) {
                gsmfd = fopen(gsmfile,"rb");
                if (gsmfd != NULL)
                    break; /* Good file. */
                else
                    printf("Error: unable to open file: %s\n", gsmfile);
        } else {
            printf("Error: file %s not found\n", gsmfile);
        }
    }

    return gsmfd;
}

/* Get the license_key from the user, check its integrity, and
 * convert it to a readable structure.  Allow at most 5 attempts
 * before giving up, but increase the wait between each attempt
 * to prevent programmatic code cracking.
 */
void solicit_key_from_user_or_exit(LICENSE_KEY *kstruct,
                                   char *key_string)
{
    static int attempts = 0;
    int status;
    char key[DIGITS_PLUS_FILLER_IN_KEY+2]; /* For newline and null. */

    while (attempts < 5) {
      /* This used to say "25-digit" for the FCS, but it was decided by
	 consensus that "25-character" captured the desire for both digits and
	 letters, without making too many users think the hyphens (-) counted as
	 characters.  Though some may still find "character" confusing, it's
	 better than digit, -mhd, 10/24/00 */
        printf("\nEnter your 25-character license key (q to quit): ");
        fgets(key, DIGITS_PLUS_FILLER_IN_KEY, stdin);

        trim_whitespace(key); /* also takes care of final LF */

        if (strlen(key) == 0)
            continue;

        if ( (strlen(key) == 1)  && (key[0] == 'q' || key[0] == 'Q') ) {
            printf("Terminating installation at user's request.\n");
            exit(0);
        }
       
        status = key_to_keystruct(key, kstruct);
        if (status == SUCCESS) {
            strcpy(key_string,key); /* to return it */
            return;
        }

        /* Provide feedback on possible errors. */
        switch (status) {
        case KEY_STRING_TOO_LONG:
        case KEY_TOO_MANY_DIGITS:
        case KEY_TOO_FEW_DIGITS:
            printf("  Error: key must have form aaaaa-aaaaa-aaaaa-aaaaa-aaaaa\n");
            printf("  where each 'a' is a letter or number.\n");
            break;
        case KEY_ILLEGAL_CHARACTER:
            printf("  Error: key contains illegal character\n");
            printf("  It should have form aaaaa-aaaaa-aaaaa-aaaaa-aaaaa\n");
            printf("  where each 'a' is a letter or number.\n");
            break;
        default:
            printf("  Error: invalid key\n");
            printf("  It should have form aaaaa-aaaaa-aaaaa-aaaaa-aaaaa\n");
            printf("  where each 'a' is a letter or number.\n");
            break;
        }
        attempts++;
    }
    exit_error("Too many unsuccessful tries to enter key", status);
}

/* Provide the user the mechanism to select components for a customized
 * installation.
 */
void solicit_customized_install_or_exit(LICENSED_COMPONENTS *lc)
{
    int selections[NUMBER_OF_COMPONENTS+1];
    char response[12];
    int number_of_selections;
    int selections_made;
    COMPONENT_SELECTION *cs;
    char *error_msg;
    int v, set_to;
    int i;

    /* Set up the array "selections" with licensible components. */
    number_of_selections = 0;
    for (i=0; i<NUMBER_OF_COMPONENTS; i++) {
        if (lc->components[i].component != NULL) {
            number_of_selections++;
            selections[number_of_selections] = i; /* entry 0 is not used.*/
        }
    }

    error_msg = "";
    while(1) {
        selections_made = 0;  /* false */
        printf("\n\n\n\nComponents with * are selected:\n");
        for (i=1; i<=number_of_selections; i++) {
            cs = &(lc->components[selections[i]]);
            printf("     %c %2d. %s\n",
                (cs->selected) ? '*' : ' ', /* * if selected, else a space.*/
                i,
                cs->component->cp_name);
            if (cs->selected)
                selections_made = 1;  /* true */
        }
        printf("%s\n",error_msg);  /* normally empty */
        error_msg = "";
        printf("Enter 'install' to install the selected components\n");
        printf("      'sa' to select all,   's#' to select one #,\n");
        printf("      'da' to deselect all, 'd#' to deselect one #, where # is 1, 2, ...\n");
        printf("        (q to quit) [sa] : ");
        fgets(response,10, stdin);
        
        trim_whitespace(response); /* also takes care of final LF */

        if (response[0] == 'd' || response[0] == 'D') { /* for concise code */
            set_to = 0;
        } else {
            set_to = 1;
        }

        if (strcasecmp(response,"install") == 0) {
            if (selections_made)
                return;
            else
                error_msg = "*** You must select at least one component ***";
        } else if (response[0] == 'q' ||
		   response[0] == 'Q' ) {
	  printf("Installation will be terminated.\nDo you really want to quit without installing anything? (y or n) ");
	  fgets(response,10, stdin);
	  trim_whitespace(response); /* also takes care of final LF */
	  if (response[0] == 'y' ||
	      response[0] == 'Y' ) {
	    printf("Terminating installation at user's request.\n");
	    exit(0);
	  } else
	    printf("Installation not terminated, continuing.");
        } else if (strcasecmp(response,"sa") == 0
              || strcasecmp(response,"da") == 0 ) {
            for (i=1; i<=number_of_selections; i++)
                lc->components[selections[i]].selected = set_to;
        } else if ( response[0] == 's'
              ||    response[0] == 'S'
              ||    response[0] == 'd'
              ||    response[0] == 'D' ) {
            v = atoi(&response[1]);
            if (v < 1 || v > number_of_selections)
                error_msg = "*** # is an invalid selection ***";
            else
                lc->components[selections[v]].selected = set_to;
        } else if (strlen(response) == 0) {
	  error_msg = "*** Enter the word 'install' to begin installation ***";
	} else {
            error_msg = "*** Invalid response ***";
        }
    }
}

/* Provide the user with a description of what will be installed,
 * including the bundle name and a list of licensed components.
 * Check whether the user wishes to install them all or wants
 * a custom installation.
 *
 * return value:  1 to install all licensed components
 *                0 for custom install
 * 
 */
int solicit_for_standard_install_or_exit(LICENSED_COMPONENTS *lc)
{
    char response[10];
    int i;

    /* Print the family name and list of licensed components. */
    printf("\n\n\n\nYou are about to install the following licensed components\n");
    printf("from %s:\n\n",lc->bundle->bdl_name);
    for (i=0; i<NUMBER_OF_COMPONENTS; i++) {
        if (lc->components[i].component != NULL)
            printf("     * %s\n", lc->components[i].component->cp_name);
    }

    /* Prompt the user for a full or custom installation. */
    while (1) {
        printf("\nEnter A to install all components\n");
        printf("   or C to customize your installation (q to quit) [A] : ");
        fgets(response,8, stdin);
        
        trim_whitespace(response); /* also takes care of final LF */

        if (strlen(response) == 0)
            return 1;           /* Full installation by default. */
        
        if (strlen(response) != 1) {
            printf("*** Invalid response ***\n");
            continue;
        }

        if (response[0] == 'q' || response[0] == 'Q') {
            printf("Terminating installation at user's request.\n");
            exit(0);
        }
        if (response[0] == 'a' || response[0] == 'A') {
            return 1;   /* Full installation. */
        }
        if (response[0] == 'c' || response[0] == 'C') {
            return 0;   /* Custom installation. */
        }
        printf("*** Invalid response ***\n");
    }
}

/* Obtain name and company of person installing the software.
 */
void solicit_name_and_company(char *person, char *company)
{
    while (1) {
        printf("\nEnter your full name or the full name of the person\n");
        printf("for whom you are installing this software : ");
        fgets(person, MAX_NAME_SIZE - 2, stdin);
        trim_whitespace(person); /* also takes care of final LF */
        if (strlen(person) > 2)
            break;
        printf("*** Invalid name ***\n");
    }

    while (1) {
        printf("\nEnter the name of your company or organization : ");
        fgets(company, MAX_NAME_SIZE - 2, stdin);
        trim_whitespace(company); /* also takes care of final LF */
        if (strlen(company) > 2)
            break;
        printf("*** Invalid name ***\n");
    }
}

/* Iterates through the selected licensed components to determine
 * whether ok-file watermarking is needed
 *   return value: 0 if some selected component has an ok file,
 *      1 otherwise
 */
int ok_watermark_is_needed (LICENSED_COMPONENTS *lc)
{
    COMPONENT_SELECTION *cs;
    int i;

    for (i=0; i<NUMBER_OF_COMPONENTS; i++) {
        cs = &lc->components[i];
        if (cs->component != NULL
            && cs->component->cp_watermark != NULL
            && cs->selected)
            return 1;  /* found one */
        cs++;
    }
    return 0; /* none found */
}


/* Try to delete preexisting files in an installation.  Called from
   verify_readiness_of_installation_directory_or_exit below.  For simplicity,
   uses system on rm -rf.  If rm fails, it returns a positive value, so caller
   can just test for that.  It also prints error messages. */
int try_to_delete(char *existv[]) 
{
  int i, result = 0;
  char command[1024];
  
  for (i = 0; existv[i] != NULL; i++) {
    sprintf(command,"rm -rf %s",existv[i]);
    result = result | system(command);
  }
  return result;
}

/* Check whether any files to be installed or renamed already exist,
 * and if so, give the user the opportunity to move them out of the way.
 */
void verify_readiness_of_installation_directory_or_exit(char *tarv[],
                                                        char *renamev[],
                                                        char *basedir)
{
    int i, existindex, x;
    int installok = 1;
    int verified;
    int status;
    char *filename;
    char namebuf[1024];
    char response[50];
    char *existv[MAX_ARGS_TO_TAR];

    memset(existv,0,sizeof(existv));

    while (1) {
        printf("\n");  /* Separator for files listed below. */
        verified = 1;   /* Assume that verification will succeed. */
        i = 3;  /* Skip tar command and options. */
        existindex = 0;
        /* Check for both the original file and the renamed file.  Check
         * for renamed file only if appropriate. */
        while ( (filename = tarv[i]) != NULL ) {
            for (x = 0; x < 2; x++) { /* for both original and renamed */
                if (x == 0)
                    filename = tarv[i];
                else {
                    filename = renamev[i];
                    if (filename == NULL )
                        continue;           /* no renaming */
                }
                strncpy(namebuf,basedir,256);
                strcat(namebuf,"/");
                strncat(namebuf,filename,750);
                if ( file_exists(namebuf) ) {
                    if (existv[existindex] != NULL)
                      /* It's possible this is not the first time thru the loop */
                      free(existv[existindex]);
                    existv[existindex] = (char*)malloc(strlen(namebuf)+1);
                    strcpy(existv[existindex],namebuf);
                    printf("*** File or directory %s already exists\n",
                        namebuf);
                    existindex++;
                    verified = 0;   /* Verification failed. */
                }
            }
            i++;
        }
        if (verified) {
            /* In case the user removed the installation directory,
             * recreate it if possible.
             */
            if ( file_exists(basedir) )
                return;   /* All is fine. */
            else {
                printf("Creating directory %s ...\n",basedir);
                status = programatic_create_directory(basedir);
                if (status != SUCCESS || ! file_exists(basedir) ) {
                    printf("\nError: Unable to create directory %s\n",
                        basedir);
                    printf("Please create the directory by hand in a separate");
                    printf(" login shell.\n");
                    installok = 0;
                } else {
                    return;  /* Fine, but with recreated directory. */
                }
            }
        } else {  /* There are files in the way. */
            printf("\n  WARNING: The file(s) listed above already exist in the\n");
            printf("target directory.  These files will be removed and reinstalled\n");
            printf("during the installation process.  Enter 'install' to the prompt\n");
            printf("below to delete and overwrite these files, or 'q' to quit.\n");
        }

        while (1) {
            printf("\nType 'install' to continue installation overwriting existing files\n");
            printf("     Or press enter to re-verify directory\n");
            printf("     or type q to quit: ");
            fgets(response, 49, stdin);
        
            trim_whitespace(response); /* also takes care of final LF */
        
            if ( (strlen(response) == 1)
                && (response[0] == 'q' || response[0] == 'Q') ) {
                printf("Terminating installation at user's request.\n");
                exit(0);
            }

            if (strcasecmp(response,"install") == 0) {
                if (installok) {
                     if (try_to_delete(existv) != 0) { /* Manual delete to get error messages */
                       printf("Problems occurred during file deletion.  Files may not get reinstalled properly.\n");
                       printf("You may continue anyway by typing 'install' again, or 'q' to quit:  ");
                       fgets(response, 49, stdin);
                       trim_whitespace(response);
                       if ( (strlen(response) == 1)
                            && (response[0] == 'q' || response[0] == 'Q') ) {
                         printf("Terminating installation at user's request.\n");
                         exit(0);
                       } else {
                         if (strcasecmp(response,"install") == 0) {
                           for (i = 0; existv[i] != NULL; i++)
                             free(existv[i]);
                           return; /* They said it, they meant it. */
                         } else
                           break; /* Run 'round thru the loop again and give another chance. */
                       }
                     }
                     /* looks like it's OK. */
                     for (i = 0; existv[i] != NULL; i++)
                       free(existv[i]);
                     return;    /* They said it was OK, and we're OK on install dir */

                } else
                    break;     /* We need to reverify install directory, so loop */
            }

            if (strlen(response) == 0)
                break;   /* Continue loop to verify files again. */
            else
                printf("*** Invalid response ***\n");  /* Prompt again. */
        }
    }
}

/* Check whether the installed files now exist.  Print an error
 * message for each missing file.
 *   return value: SUCCESS or FAILURE
 */
int verify_installation_of_files(char *tarv[],
                                 char *renamev[],
                                 char *basedir)
{
    int i;
    int retval;
    char *filename;
    char namebuf[1024];
   
    retval = SUCCESS;   /* Assume that verification will succeed. */
    i = 3;              /* Skip tar command and options. */
    while (tarv[i] != NULL) {
        if (renamev[i] != NULL)
            filename = renamev[i];
        else
            filename = tarv[i];
        strncpy(namebuf,basedir,256);
        strcat(namebuf,"/");
        strncat(namebuf,filename,750);
        if ( !file_exists(namebuf) ) {
            printf("Error: file or directory %s was not installed\n",
                namebuf);
            retval = FAILURE;   /* Verification failed. */
        }
        i++;
    }
    
    return retval;  
}

#define PRINT_BOX_MARGIN(c, s)             \
  do {                                     \
    int i;                                 \
    for (i = 0; i != c; i++) putc(' ', s); \
  } while (0)

/* formats the string vector sv in a "box" of character c */
void
box(char **sv, char c, FILE *stream)
{
  int i, j, max = 0;

  for (i = 0; sv[i] != NULL; i++) {
    size_t l = strlen(sv[i]);
    if (l > max) max = (int) l;
  }

  PRINT_BOX_MARGIN(4, stream);
  for (i = 0; i != max + 4; i++) putc(c, stream);
  putc('\n', stream);

  for (i = 0; sv[i] != NULL; i++) {
    size_t l = strlen(sv[i]);

    PRINT_BOX_MARGIN(4, stream);
    fprintf(stream, "%c %s", c, sv[i]);

    for (j = max - l; j != 0; j--)
      putc(' ', stream);

    fprintf(stream, " %c\n", c);
  }

  PRINT_BOX_MARGIN(4, stream);
  for (i = 0; i != max + 4; i++) putc(c, stream);
  putc('\n', stream);

  return;
}

void print_welcome_banner()
{
  putchar('\n');
  box(welcome_banner, '+', stdout);
  putchar('\n');
}

int
yes_or_no_p(char *prompt)
{
  char cbuf[50], str[50];
  
  printf("%s ", prompt);
  fgets(cbuf, sizeof(cbuf), stdin);
  sscanf(cbuf, "%s", str);

  if (!strcasecmp(str, "yes"))
    return 1;
  else if (!strcasecmp(str, "no"))
    return 0;
  else {
    printf("Please type Yes or No.\n");
    return(yes_or_no_p(prompt));
  }
}

#define REMOVE_TRAILING_SLASHES(string) {  \
    int i;                                 \
    for (i = strlen(string)-1; i != 0; i--)  \
      if (string[i] == '/')                \
	string[i] = '\0';                  \
      else                                 \
	break; }

int
programatic_create_directory(char *path)
{
  mode_t mode = (S_IRWXU | S_IRWXG | S_IRWXO) & ~umask(0);

  if (!strcmp(path, "/"))
    return 1;

  REMOVE_TRAILING_SLASHES(path);

  if (mkdir(path, mode))
    return 1;

  return 0;
}

int
create_directories_recursively_1(char *path, mode_t mode)
{
  struct stat buf;
  char *cptr = path;
  int done = 0;

  while (!done) {
    cptr += strspn(cptr, "/");
    cptr += strcspn(cptr, "/");

    done = (*cptr == '\0');
    *cptr = '\0';

    if (stat(path, &buf))
      if (errno != ENOENT || mkdir(path, mode))
	return 1;
                    
    *cptr = '/';
  }

  return 0;
}

int
create_directories_recursively(char *path)
{
  mode_t mode = (S_IRWXU | S_IRWXG | S_IRWXO) & ~umask(0);
  char *working_path;
  int err;

  if (!strcmp(path, "/"))
    return 1;

  REMOVE_TRAILING_SLASHES(path);
  
  if (!(working_path = (char *)malloc(sizeof(char) * (strlen(path) + 1))))
    PERROR_EXIT("malloc");

  strcpy(working_path, path);
  
  if ((err = create_directories_recursively_1(working_path, mode)))
    if (strcmp(working_path, path))
      fprintf(stderr, "Could not create \"%s\".\n", working_path);

  free(working_path);
  return err;
}

/* Perform all steps of the Unix command-line driven installation.
 */
void geninst (int argc, char *argv[])
{
    /* instances */
    FILEHEADER header;
    LICENSED_COMPONENTS licensed;
    LICENSE_KEY keystruct;
    char watermark_base[1024];
    char watermark_file[1024];
    char *tarvector[MAX_ARGS_TO_TAR];
    char *renamevector[MAX_ARGS_TO_TAR];
    boolean obfuscatevector[MAX_ARGS_TO_TAR];
    char *postinstallvector[MAX_ARGS_TO_TAR];
    char person_name[MAX_NAME_SIZE];
    char company_name[MAX_NAME_SIZE];
    char key[DIGITS_PLUS_FILLER_IN_KEY];

    /* pointers and primitives */
    FAMILY_DESCRIPTOR *family_desc;
    FILE *gsm_infile;
    char *workingdir;
    int status;
    int renaming_status;
    int watermark_status;
    int tar_status;
    COMPONENT_SELECTION *selection;
    int i;

    /* Bomb if we aren't being used through a terminal, unless we're secret
       gensym hackers.  Original code to bomb added in edit 1.8, we believe it
       was to slow down brute force attempts to guess license keys, but the
       commit log doesn't say.  However, it also prevents automated testing.
       The word "automatic" here is chosen because it already appears in the
       output of "strings" and so is not a tempting target.  A better test
       would be to enforce some minimum time of execution. */
    if ((argc < 2 ||
	 strcmp(argv[1],"automatic") != 0)
	&& isatty(fileno(stdin)) == 0)
      exit(1);
    else
      qa_secret_automation = 1;

    /********/
    /* Print installation welcome and instructions. */
    print_welcome_banner();

    /********/
    /* Solicit the location of the .gsm file */
    gsm_infile = solicit_and_open_gsm_file_or_exit();

    /********/
    /* Read and check basic integrity of the file header. */
    status = read_file_header(&header, gsm_infile);
    if (status != SUCCESS)
        exit_error("while reading .gsm file", status);

    /********/
    /* Solicit key from user, unpack it, and check integrity.
     * Exit if user fails to enter a valid key.  The key is
     * returned as a string for use in watermarking, below.
     */
    solicit_key_from_user_or_exit(&keystruct, key);
    
    /********/
    /* Check that key fields match file header fields. */
    validate_key_against_header_or_exit(&header,&keystruct);

    {
      char **license;

      switch (keystruct.family_id) {
      case NETSLEUTH_FAMILY_ID:
	license = netsleuth_license_verbiage;
	break;
      default:
	license = generic_license_verbiage;
      }

      print_license_agreement(license);
      if (!yes_or_no_p ("Do you accept all the terms of the preceding License Agreement?\nIf you type \"No\", the setup will close.\nTo install G2, you must accept this agreement.\n(Yes or No):")) {
	printf("Installation terminated.\n");
        fflush(stdout);
	exit(-1);
      }
      
    }
    
    /********/
    /* Read the family file and check that it is a string of characters. */
    status = read_and_decrypt_gsm_family_file(gsm_infile,
        header.family_file_length,
        read_buf,
        header.crypt_mask);
    if (status != SUCCESS) {
        exit_error("while reading .gsm file", status);
    }
    set_bufptr_for_get_line(read_buf);  /* For get_line()/parser use. */

    /********/
    /* Parse the family file. */
    family_desc = new_family();
    status = parse_family_file(family_desc);
    if (status != SUCCESS)
        exit_error("while reading .gsm file", FAMILY_FILE_PARSE_ERROR);
    global_family_desc = family_desc;

    /********/
    /* Check that family file fields matches key's fields (and header's). */
    validate_key_against_family_or_exit(family_desc, &keystruct);

    /********/
    /* Process the family file according to the key fields and build
     * a linked structure of installable components.
     * Be sure to check that the bundle and component numbers are viable.
     */
    status = populate_license_components(family_desc, &keystruct, &licensed);
    if (status != SUCCESS)
        exit_error("license key is not valid for the .gsm file", status);

    /********/
    /* Present information about the bundle to be installed.
     */
    print_licensed_product_banner( (unsigned char) keystruct.system_id,
        licensed.bundle->bdl_name);

    /********/
    /* Get default installation directory from user, and create it if it
     * doesn't already exist.
     */
    workingdir = solicit_and_create_installation_directory(&licensed);

    loosely_validate_free_space(workingdir, gsm_infile);

    /********/
    /* Provide the user with a list of components to be installed.
     * The user may choose the standard (all) or custom (subset)
     * installation. The effect is to set or clear the "selected"
     * field in the LICENSE_KEY entries.  Initially all licensed
     * components are selected.
     */
    if (!solicit_for_standard_install_or_exit(&licensed)) {
        solicit_customized_install_or_exit(&licensed);
    }

    /********/
    /* Create the tar argument list from the list of components. This
     * also creates a parallel list of files to be renamed. */
    status = create_tar_and_rename_vectors(tarvector, renamevector, obfuscatevector,
        postinstallvector, &licensed, keystruct.system_id);

    /* Check the list for preexisting files or directories, and if some
     * are found, warn the user to move them out of the way.
     */
    verify_readiness_of_installation_directory_or_exit(tarvector,
        renamevector, workingdir);

    /********/
    /* Get the name and company of the person installing the software.
     */
    solicit_name_and_company(person_name, company_name);

    /********/
    /* Perform installation by running tar on the list of files.
     * First we set up a signal handler to prevent termination
     * if tar stops abnormally. */
    establish_sigchld_handler();  /*  Assume success. */

    printf("\nBeginning installation of files...\n");
    tar_status = run_tar_on_pipe (tarvector,
        gsm_infile, workingdir, header.crypt_mask);
    printf("\n");  /* To end the * heartbeat. */
    if (tar_status != SUCCESS && tar_status != TAR_PIPE_WRITE)
        exit_error("while processing .gsm file", tar_status);

    /********/
    /* We're done with the .gsm file, so close it. */
    fclose(gsm_infile);

    /********/
    /* Go through the installed files and rename them as needed.  Then
     * check the status of the installation and inform the user of
     * success or failure as appropriate.
     */
    renaming_status = rename_files(tarvector, renamevector, obfuscatevector, postinstallvector, workingdir);

    /********/
    /* Check whether the specified parts have been installed and print
     * a list of unfound files.
     */
    status = verify_installation_of_files(tarvector,
        renamevector, workingdir);

    /********/
    /* Run the watermark facility.  It is applied generally for the
     * installation and then individually for each ok file as needed.
     */
    strcpy(watermark_base, workingdir);
    strcat(watermark_base,"/");
    /* Create the watermark.txt file. */
    watermark_status = make_watermark_file_g2pwaux(watermark_base,
        licensed.bundle->bdl_name,
        person_name,
        company_name,
        key);

    /* Watermark the ok files. */
    if ( ok_watermark_is_needed(&licensed) ) {
        for (i=0; i<NUMBER_OF_COMPONENTS; i++) {
            selection = &licensed.components[i];
            if (selection->component != NULL
                && selection->component->cp_watermark != NULL
                && selection->selected) {
                  strcpy(watermark_file, watermark_base);
                  strncat(watermark_file,
                      selection->component->cp_watermark,1024);
                  watermark_status = add_watermark_to_ok_file_g2pwaux(watermark_file,
                      licensed.bundle->bdl_name,
                      person_name,
                      company_name,
                      key);
            }
        }
    }

    /********/
    /* If tar failed, let the user know.
     */
    if (tar_status == TAR_PIPE_WRITE) {
        fprintf(stderr, "\nInstallation of some files may not have succeeded\n");
        fprintf(stderr, "because the .gsm file was not read fully.  Although\n");
        fprintf(stderr, "the installation may still have been successful,\n");
        fprintf(stderr, "please contact Gensym Support to note the problem.\n");
    }

    /* If the verification failed, let the user know.
     */
    if (status != SUCCESS) {
        fprintf(stderr, "\nThe files listed above were not installed, either\n");
        fprintf(stderr, "because the installation directory was not writable or\n");
        fprintf(stderr, "because the files were missing from the installation file.\n");
        fprintf(stderr, "If the files were missing, please contact Gensym Support.\n");
        fprintf(stderr, "*** Installation did not succeed. ***\n");
    } else {
        printf("Installation complete.\n");  /* Successful installation. */
    }
}

int
main (int argc, char *argv[])
{
  executable = argv[0];

  if (signal(SIGINT, sigint_handler) == SIG_ERR)
    PERROR_EXIT("signal");

  geninst(argc,argv);

  return 0;
}

