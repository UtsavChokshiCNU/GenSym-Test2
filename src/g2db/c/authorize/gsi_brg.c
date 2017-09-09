/* ========================================================================= */
/*                                                                           */
/* GSI_BRG.C - Bridge Licensing Module                                       */
/*                                                                           */
/* Bridge authorization works in two steps.  During the first step (which    */
/* is implemented in the function stage1), we look for a record in the       */
/* authorization file that applies to the current machine and bridge.  We    */
/* then store needed information from the authorization record as well as    */
/* information about the current machine and bridge in the ok structure.     */
/* During the second step (implemented in stage 2), we validate the info     */
/* in the ok structure.                                                      */
/*                                                                           */
/* ========================================================================= */

/* This file uses the define flag MSDOS rather than WIN32.  MSDOS is really an
obsolete define flag, and is no longer used in code or included in most
makefiles.  (We only support Win32, and no longer support MSDOS as distinct from
WIN32.)  WIN32 is now preferred.  However, we don't want to change MSDOS to
WIN32 everywhere (~6 places) in this file at this time. So here we define MSDOS
if WIN32 is defined. (MHD 6/25/02) */
#if defined(WIN32) && !defined(MSDOS)
#  define MSDOS
#endif

/* Include the appropriate headers for this operating system */
/* --------------------------------------------------------- */
#include <stdio.h>

#if !defined(sun) && !defined(masscomp) && !defined(_SEQUENT_)
#include <stdlib.h>
#endif

#ifdef vms
#include <unixlib.h>
#endif

#if !defined(NeXT) && !defined(vms) && !defined(_CX_UX)
#  include <malloc.h>
#endif

#if defined(hpux) || defined(MSDOS) || defined(vms)
#  include <time.h>
#else
#  include <sys/time.h>
#endif

#if defined(unix)
#  include <time.h>
#  include <sys/time.h>
#endif

#include <ctype.h>
#include <string.h>
/* --------------------------------------------------------- */

/* Define the preprocessor variables that will be needed in the succeeding code */
/* ---------------------------------------------------------------------------- */
#if defined(_IBMR2) || defined(__hpux) || defined(sparcsol) || defined(__osf__)
# if !defined(unix)
#  define unix
# endif
#endif

#ifndef NULL
#define NULL 0L
#endif

#ifdef vms
#define OK_LOGICAL "GSI$ROOT"
#endif

#if defined(unix) || defined(MSDOS)
#define OK_LOGICAL "GSI_ROOT"
#endif

#define OK_FILE_LOWERCASE "gsi.ok"
#define OK_FILE_UPPERCASE "GSI.OK"

#define MAXLINE 256
#define MIXER_PRIME 25173L
#define ERRMID "\nGSI Authorization failed -- Could not fetch machine ID.\n"

#define OK 1L
#define NOT_OK -1L
#define TRUE 1
#define FALSE 0

#define SITE_LICENSE_TOKEN    "SITE:"
/* ---------------------------------------------------------------------------- */


/* ---------------------------------------------------------------- */
/*                           Global Variables:                      */
/* ---------------------------------------------------------------- */
    char                        buffer[128];      /* ~~ NOTE: may need to bump */
                                                  /*    this up if substitute  */
                                                  /*    SITE_LICENSE_TOKEN     */
    char                        vers_upper[MAXLINE];
    char                        majvers[MAXLINE];
    char                        finupper[MAXLINE];
    
     /* global values passed from stage1 to stage2 */
    static struct { char        machine_id[MAXLINE];
                    char        prod[MAXLINE];
                    char        majvers[MAXLINE];
                    char        fin_dir[MAXLINE];
                    char        fin[MAXLINE];
                    long int    weighted_mach_id;
                    long int    weighted_prod;
                    long int    weighted_majvers;
                    long int    universal_start_date;
                    long int    universal_end_date;
                    long int    codes[5];               } ok;
    
    static short int            max_days_in_month[12] = 
                                { 31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31 };


/* -------------------------------------------------------------- */
/*                           Prototypes:                          */
/* -------------------------------------------------------------- */
#if defined(unix) || defined(MSDOS)
    extern char *getenv();
#endif
    extern long g2ext_nsleep(); /* retrieves machine-id whose format may vary
                                   according to platform */
	extern long g2ext_nsleep_next(char *buffer) ;
    
    short       calc_universal_dates(short start_day,  short start_month, short start_year,
                                     short end_day,    short end_month,   short end_year,
                                     long  *start_u_d, long  *end_u_d) ;
    void        f(  long weighted_mach_id,  long weighted_prod, long weighted_majvers, 
                    long start_u_d,         long end_u_d,       long rtn_codes[]) ;
    void        g(  long weighted_mach_id,  long weighted_prod, long weighted_majvers,
                    long start_u_d,         long end_u_d,       long the_codes[]) ;
    
    void        gb_raise_to_uppercase(char *str);
    int         gb_toupper(int c) ;
    int         gb_is_site_machine_id(char *str);
    void        gb_normalize_machine_id(char *str);
    void        major_version(char *ver, char *majver) ;
    void        remove_whitespace(char *str) ;
    long        universal_date(short day, short month, short year) ;
    short       verify_char_dates(  char  *c_start_day, char  *c_start_month,   char *c_start_year,
                                    char  *c_end_day,   char  *c_end_month,     char *c_end_year,
                                    short *s_start_day, short *s_start_month,   short *s_start_year,
                                    short *s_end_day,   short *s_end_month,     short *s_end_year) ;
    short       verify_day(short day, short month, short year) ;
    short       verify_month(char *month) ;
    long int    weighted_value(char *str) ;
    long        xatol(char *str) ;

/* ================================================================== */
/*                                                                    */
/* stage1                                                             */
/*   - process the GSI_ROOT environment variable to find the          */
/*     authorization file                                             */
/*   - store information about the current machine and bridge in      */
/*     the ok structure                                               */      
/*   - Read .ok file until entry found that matches following         */
/*       criteria - standard: machineID + product + version           */
/*                  site    : SITE_TOKEN + product                    */
/*   - Check structure of date entry (does not compare current	      */
/*     date to date range of .ok file) if temporary codes provided    */
/*                                                                    */
/* ================================================================== */
short int stage1(char *product, char *version)
{
    FILE                *fokin;
    char                line[MAXLINE], s[17][MAXLINE];
    char                machID[MAXLINE] ;
    int                 bFirst, noID, haveID ;
#ifdef vms
	register long int	dummy ;
#endif
                         
    register short int  i, j, n;
    static char         *charptr;


    /* -------------------------------------------------- */
    /* Store the bridge name, version, and the machine ID */
    /* in the ok structure                                */
    /* -------------------------------------------------- */
    gb_raise_to_uppercase (strcpy (ok.prod, product));
    gb_raise_to_uppercase (strcpy (vers_upper, version));


    
    /* -------------------------------------------------------------- */
    /* Get the location and name of the authorization file.  Open it. */
    /* -------------------------------------------------------------- */

    /* VMS - decode the logical GSI$ROOT (if it exists) */
    /* ------------------------------------------------ */
#ifdef vms
    strcpy (ok.fin_dir, OK_LOGICAL);
    dummy = gb_probe_logical_name(ok.fin_dir);
    switch (dummy)
    {
        case SS$_NORMAL:    break;
        case SS$_NOTRAN:    printf ("\nGSI Authorization failed -- %s logical variable not set.\n",
                                        ok.fin_dir);
                            return ((short) FALSE);
                            break;
        default:            printf ("\nGSI Authorization failed -- %s logical variable path could not be found -- reason code %d",
                                    ok.fin_dir, dummy);
                            return ((short) FALSE);
                            break;
    }
#endif

    /* UNIX or NT/DOS - decode the environment variable GSI_ROOT */
    /* --------------------------------------------------------- */
#if defined(unix) || defined (MSDOS)
    if ((charptr = getenv (OK_LOGICAL)) == NULL)
    {
        printf ("\nGSI Authorization failed -- %s environment variable not set.\n", OK_LOGICAL);
        return ((short) FALSE);
    }
    strcpy (ok.fin_dir, charptr);


    /* The location of the authorization file is now stored in ok.fin_dir. */
    /* Depending upon the operating system, append /, \, or : to the       */
    /*                specification of the location                        */
    /* ------------------------------------------------------------------- */
#if defined(unix)
    strcat (ok.fin_dir, "/");
#endif
#if defined(MSDOS)
    strcat (ok.fin_dir, "\\");
#endif
#endif
#ifdef vms
    strcat (ok.fin_dir, ":");
#endif

    /* Store the full file specification of the authorization file in   */
    /*                  ok.fin, then try to open it.                    */
    /* ---------------------------------------------------------------- */
    strcpy (ok.fin, ok.fin_dir);
    strcat (ok.fin, OK_FILE_LOWERCASE);
    if ((fokin = (fopen (ok.fin, "r"))) == NULL)
    {
    
    /* UNIX gets a second chance ... try changing the case of the name */
    /* --------------------------------------------------------------- */
#ifdef unix
        strcpy (finupper, ok.fin_dir);
        strcat (finupper, OK_FILE_UPPERCASE);
        if ((fokin = (fopen (finupper, "r"))) == NULL)
        {
#endif

    /* One non-UNIX failure or two UNIX failures means the bridge is not authorized */
    /* ---------------------------------------------------------------------------- */
            printf ("\nGSI Authorization failed -- Cannot read authorization file %s.\n", ok.fin);
            return ((short) FALSE);
#ifdef unix
        } 

     /* The second UNIX try worked.  Save the correct name of the OK file. */
     /* ------------------------------------------------------------------ */
        else
            strcpy (ok.fin, finupper);
#endif
    }



    /*        Try, for the first time, to get a machine ID             */
    /* --------------------------------------------------------------- */
    buffer[0] = '\0';
    noID = g2ext_nsleep ((char *) buffer);  /* get machine ID */
    bFirst = TRUE ;


    /* -------------------------------------------------------- */
    /*                                                          */
    /* Look for a site or machine-specific authorization record */
    /*                                                          */
    /* -------------------------------------------------------- */
    do
    {   
        /* Initialize the ok structure */
        /* --------------------------- */
        ok.universal_start_date = 0L;
        ok.universal_end_date = 1L;
        ok.machine_id[0] = '\0';
    
        /*    Store the machine ID in the ok structure        */
        /* -------------------------------------------------- */
	gb_normalize_machine_id(strcpy(ok.machine_id, buffer));
#ifdef AUTH_DEBUG
	printf("Machine ID: %s  (normalized: %s)\n", buffer, ok.machine_id);
#endif

        /* Remember the first machine ID in case this bridge is not authorized */
        /* ------------------------------------------------------------------- */
        if (bFirst && !noID)
        {
            strcpy(machID, ok.machine_id) ;
        }
        bFirst = FALSE ;
      
        /*      Empty the field storage array    */
        /* ------------------------------------- */
        for (i = 0; i <= 16; i++)
            s[i][0] = '\0';
    
    
        /* -------------------------------------------------------------- */
        /* We are now ready to look for the authorization record for this */
        /* machine, bridge & version.                                     */
        /* -------------------------------------------------------------- */
        while (1)
        {
            /* start_month and end_month should contain 0 if permanent authorization.*/
            short           start_day, end_day, start_month, end_month, start_year, end_year;
            register short  codes_offset;
    
            /* Read the next line. NULL means we didn't find the authorization record. */
            if (fgets (line, sizeof(line), fokin) == NULL)
                break;
    
            /* The expected format of the line and the element of s in which       */
            /* each field should be stored:                                        */
            /*                                                                     */
            /*  Field         Type                                   Storage       */
            /*  -----         ----                                   -------       */
            /*  machine-name  string                                 IGNORED       */
            /*  machine-id    string                                 s[0]          */
            /*  product       string                                 s[1]          */
            /*                                                                     */
            /*  version       string (suggest: Vnumeric.numeric[B])  s[2]          */
            /*    +-> (major) (minor)(beta-or-patch-level)                         */
            /* [                                                                   */
            /*  FROM          FROM                                   s[3]          */
            /*  start-day     numeric                                s[4]          */
            /*  start-month   {JAN | FEB | ...}                      s[5]          */
            /*  start-year    numeric (least signif 2 digits taken)  s[6]          */
            /*  TO            TO                                     s[7]          */
            /*  end-day       numeric                                s[8]          */
            /*  end-month     {JAN | FEB | ...}                      s[9]          */
            /*  end-year      numeric (least signif 2 digits taken)  s[10]         */
            /* ]                                                                   */
            /*  code1         numeric                                s[11] or s[3] */
            /*  code2         numeric                                s[12] or s[4] */
            /*  code3         numeric                                s[13] or s[5] */
            /*  code4         numeric                                s[14] or s[6] */
            /*  code5         numeric                                s[15] or s[7] */
            /* --------------------------------------------------------------------*/
            n = sscanf (line, "%*s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
                        s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8],
                        s[9], s[10], s[11], s[12], s[13], s[14], s[15], s[16]);
#ifdef AUTH_DEBUG
            printf ("\n%d:%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s\n",
                        n, s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8],
                        s[9], s[10], s[11], s[12], s[13], s[14], s[15], s[16]);
#endif

            /* Ignore the line if it doesn't have between 8 and 16 fields */
            /* ---------------------------------------------------------- */
            if (n < 0)
                continue;
            if (n < 8)
            {
                printf ("\nGSI Authorization file line contains too few fields. Line ignored:\n Line: \"%s\"\n", line);
                continue;
            }
            if (n > 16)
            {
                printf ("\nGSI Authorization file line contains too many fields. Line ignored:\n Line: \"%s\"\n", line);
                continue;
            }
            
            /* Force all decoded fields to uppercase so that comparisons              */
            /* don't fail just due to case.  Also, normalize machine ID in element 0. */
            /* ---------------------------------------------------------------------- */
	    gb_normalize_machine_id(s[0]);
            for (i = 1; i <= 15; i++)
		  gb_raise_to_uppercase (s[i]);
            
            
            /* ------------------------------------------------------- */
            /* Test if this record could be the one we are looking for */
            /* ------------------------------------------------------- */
            major_version (s[2], majvers);
            major_version (vers_upper, ok.majvers);
            
            
            /* If this record is not a site authorization, machine ID, */
            /* product name, and version must all match.               */
            /* ------------------------------------------------------- */
            if (!gb_is_site_machine_id(s[0]))
            {
                if (noID || strcmp (s[0], ok.machine_id) || 
                        strcmp (s[1], ok.prod) || strcmp (majvers, ok.majvers))
                    continue;
            }
            
            /* If SITE license, product name and version must match */
            /* ---------------------------------------------------- */
            else 
            {
                if (strcmp (s[1], ok.prod) || strcmp (majvers, ok.majvers))
                    continue;
            }
            
            /* if SITE license then copy site token into */
            /* machine id slot for code comparison       */
            /* ----------------------------------------- */
            if (gb_is_site_machine_id(s[0]))
            {
                strcpy(ok.machine_id,s[0]);
            }
            
            /* ------------------------------------------------------------------ */
            /* If the record is properly formed treat this as the record we want. */
            /* ------------------------------------------------------------------ */
            
            /* If this is a temporary licence: */
            /* ------------------------------- */
            if (!strcmp (s[3], "FROM"))
            {
            
                /* Reject it if it is badly formed */
                /* ------------------------------- */
                if (strcmp (s[7], "TO"))
                {
                    printf ("\nGSI Authorization-- found FROM, but TO is misplaced or missing. Line ignored.\nLine: \"%s\"\n", line);
                    continue;
                }
            
                /* Reject if the dates are not valid */
                /* --------------------------------- */
                if (verify_char_dates (s[4], s[5], s[6], s[8], s[9], s[10],
                          &start_day, &start_month, &start_year,
                          &end_day, &end_month, &end_year) == NOT_OK)
                {
                    printf (" Line ignored.\nLine: \"%s\"\n", line);
                    continue;
                }
            
                codes_offset = 8;		/* the codes start in s[11], not s[3] */
            
            } 
            
            /* If this is a permanent license: */
            /* ------------------------------- */
            else
            {
                codes_offset = 0;		   /* the codes start in s[3] */
            
                /* Reject it if it has extraneous fields */
                /* ------------------------------------- */
                if (n > 8)
                {
                	printf ("\nGSI Authorization-- Too many fields for permanent authorization or FROM misplaced. Line ignored.\nLine: \"%s\"\n", line);
                  	continue;
                }
                
                /* Don't base the validity of this license on the date */
                /* --------------------------------------------------- */
                start_day = end_day = start_month = end_month = start_year = end_year = 0;
            
            } /* end else */
            
            /* Convert the start and end dates to long integers */
            /* ------------------------------------------------ */
            if (calc_universal_dates (start_day, start_month, start_year,
                          end_day, end_month, end_year,
                          &ok.universal_start_date, &ok.universal_end_date) == NOT_OK)
            {
                printf (" Line ignored.\nLine: \"%s\"\n", line);
                continue;
            }
            
            /* Make sure the authorization codes are numeric and  */
            /* store their numeric values in the ok structure.    */
            /* -------------------------------------------------- */
            j = 0;
            for (i = 0; i <= 4; i++)
                if ((ok.codes[i] = xatol (s[3+i+codes_offset])) == NOT_OK)
                {
                    printf ("\nGSI Authorization-- Code number %hd format is bad. Line ignored.\nLine: \"%s\"\n",i+1, line);
                    j = 1;
                    break;
                }
            if (j)
                continue;
            
            /* The current authorization record is the one we are going to pass to stage2 */
            /* -------------------------------------------------------------------------- */
            fclose (fokin);
            return ((short) TRUE);
        
        } /* end while (1) */
    
    
        /* If we were looking for a site authorization record because we were unable   */
        /* to retrieve a machine ID, we're done.  If we do have a machine ID but       */
        /* couldn't find an authorization record, then see if there is another machine */
        /* ID.  If so, look for an authorization record for it.                        */
        /* --------------------------------------------------------------------------- */
        if (noID)
            haveID=FALSE ;
        else
            haveID = !g2ext_nsleep_next(buffer) ;
        if (haveID)
            rewind(fokin) ;
        else  
            fclose (fokin);

    } while (haveID) ;

    /* We were unable to find a record for this product.  Inform   */
    /* the operator that we were either unable to read the machine */
    /* ID or that we didn't find an authorization record for this  */
    /* machine, product, and version.                              */
    /* ----------------------------------------------------------- */
    if (noID)
        printf (ERRMID);
    else
        printf ("\nGSI Authorization -- Could not find valid entry in %s file for machine_id=%s product=%s version=%s\n",
                ok.fin, ok.machine_id, ok.prod, vers_upper);
    return ((short) FALSE) ;
}
/* -------------------------------------------------------------------------------------------------------------------- */

/* ============================================================= */
/*                                                               */
/*  stage2                                                       */
/*   - compare .ok file codes to self-generated codes for        */
/*     machineID + product + version [+ dates] as detailed in    */
/*     stage1                                                    */
/*                                                               */
/* ============================================================= */
short int stage2()
{
    register short int i;
    long int gener_codes[5];

    f ((ok.weighted_mach_id = weighted_value (ok.machine_id)),
       (ok.weighted_prod    = weighted_value (ok.prod)),
       (ok.weighted_majvers = weighted_value (ok.majvers)),
        ok.universal_start_date,
        ok.universal_end_date,
        gener_codes);

    g (ok.weighted_mach_id, ok.weighted_prod, ok.weighted_majvers,
       ok.universal_start_date, ok.universal_end_date, gener_codes);

#ifdef AUTH_DEBUG
    printf("\n");
    printf("Machine:\t%s\n",ok.machine_id);
    printf("Product:\t%s\n",ok.prod);
    printf("Version:\t%s\n\n",ok.majvers);
    printf("CODES: %ld %ld %ld %ld %ld\n",gener_codes[0],gener_codes[1],gener_codes[2],gener_codes[3],gener_codes[4]);
#endif

    for (i = 0; i <= 4; i++)
        if (ok.codes[i] != gener_codes[i])
        {
            printf ("\nGSI failed -- Authorization codes are not correct in %s.\n", ok.fin);
            return ((short) FALSE);
        }
        return ((short) TRUE);
}   




/* there exist problems with the toupper function on some Sun oper. systems. */
int gb_toupper(c)
     int c;
{
  return (c - 'a' + 'A');
}


void gb_raise_to_uppercase(str)
     char *str;
{
  for (; *str; str++)
    if (islower((int) *str))
      *str = (char) gb_toupper((int) *str);
}


void remove_whitespace(str)
     char *str;
{
  char *u;

  for (u = str; *str; str++)
    if ((isprint ((int) *str)) && (!isspace ((int) *str)))
      *u++ = *str;
  *u = '\0';
}

/* gb_isalphanumeric() emulates the common library function isalphanumeric(),
   but as for gb_toupper(), we define this ourselved to avoid having to rely on
   operating system/library support. */

int gb_isalphanumeric(c)
     int c;
{
  int is_alphanumeric;

  is_alphanumeric
    = ((('0' <= c) && (c <= '9')) || (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')));
  return is_alphanumeric;
}



/* gb_is_site_machine_id() is supposed to say if str is a "site"-style machine
ID for a gsi bridge authorization.  This means a string starting with "site:",
not counting case, and ignoring any leading whitespace. */

int gb_is_site_machine_id(str)
     char *str;
{
  char site[] = SITE_LICENSE_TOKEN;
  int i = 0, j = 0, site_token_len = strlen(site), len = strlen(str), code_j;

  while (isspace((int)str[j])) {
    j++;
    if (j >= len)
      return FALSE;
  }

  while ((i < site_token_len) && (j < len)) {
    code_j = str[j];
    
    if (islower(code_j))
      code_j = gb_toupper(code_j);
    
    if (site[i] != code_j)
      return FALSE;
    
    i++;
    j++;
  }
  return TRUE;
}
    
  

/* gb_normalize_machine_id() normalizes str in place so that it can be used to
   for exact case sensitive comparison and for code generation and comparison
   consistent with the code generation done by Gensym order services, in
   particular by the Helplink authorization utility.

   The goal is to avoid confusing mistakes and runarounds caused by the overly
   zealous consideration characters in machine ID's, e.g., spaces,
   capitalization, hyphens, etc.

   For node-specific machine ID's, this normalization achieves compatibility
   with past authorizations which were not subject to interference from
   whitespaces or case sensitivity, but which did have to have the hyphen (-)
   character placed in just the right spot in order for (a) the machine ID to
   match in the OK file, and (b) for the codes generated by Order
   Services/Helplink to match the codes expected by this gsi_brg authorization
   facility.  In all cases, whitespace and all other nonalphanumeric characters
   are eliminated except that hyphens are needed in certain case for certain
   platforms.

   The preprocessor define HYPHENS_IN_NODE_MACHINE_ID is defined below for the
   platforms that require the hyphens to be added when the machine ID is
   normalized. This determination is based on what the g2ext_nsleep() function
   returned per platform prior to the establishment of this normalizing
   practice.  See module nsleep.c.

   Now, if this is a platform that has node-specific machine ID's with hyphens,
   and this is node-specific, put in hyphens between every two characters.


   For non-node-specific ("Site") machine ID's, the code generation has been
   sensitive to the presence or absence of hyphens (-) and colons (:), and these
   do not appear according to any reasonably defined pattern.  Introducing a
   normalization an improved normalization scheme now would introduce
   incompatibilies with previously issued codes.  So for this case we will for
   now stick to the tradition normalization scheme: just strip whitespace
   characters (tabs, spaces) and make the machine ID all uppercase.


   With this new normalization facility, as implemented in this file, we are
   eliminating the requirement for users to have hyphens in the machine ID field
   of a gsi.ok file entry.

   However, a corresponding change needs to be made in the code generation
   software used by Order Services/Helplink in order to free users of the need
   to be careful with hyphens for that application.

   This normalization addresses HQ-4322526 "some operating systems require
   hyphens for bridge authorizations".

   Until the corresponding change is made, note that resolution HQ-4324101 "when
   and when not to use hyphens when generating authorization codes" still
   applies. (MHD 7/1/02)

   Note that in all cases old codes generated by Order Service/Helpdesk will
   continue to work provided they once would have worked in the past with a
   bridge compiled with earlier versions of this software. */

#if defined(vms) || defined(ultrix) || defined(__osf__) || defined(linux)
#  define HYPHENS_IN_NODE_MACHINE_ID
#endif

void gb_normalize_machine_id(str)
     char *str;
{
  int i, j, c;


  /* if this is a site authorization, just punt on normalization and do what
     we've always done, and return right away. */

  if (gb_is_site_machine_id(str)) {
    gb_raise_to_uppercase (str);
    remove_whitespace (str);
    return;
  }


  j = 0;
  for (i = 0; (str[i] != '\0'); i++) {
    c = (int)str[i];
    if (gb_isalphanumeric(c)) { /* allow just alphanumeric characters ... */
      if (islower(c))
	c = gb_toupper(c);
      str[j] = (char)c;
      j++;
    }
  }
  str[j] = '\0';

  /* Now for certain platforms that use MAC addresses as machine IDs, put a
     hyphen (-) between every pair of digits. To do this, copy str into
     temporary buffer buf, then copy back to str with the hyphens added.  Make
     sure the machine ID is not too big to fit (could be from an OK file). We
     know it is not a "site" authorization -- that's checked above.  */
#if defined(HYPHENS_IN_NODE_MACHINE_ID)
  if (((j + ((j/3) * j)) + 1 < MAXLINE))       /* & expansion for -'s fits */
    {
      char buf[MAXLINE];

      strcpy (buf, str);
      j = 0;
      for (i = 0; (buf[i] != '\0'); i++) {
	if ((i != 0) && ((i % 2) == 0)) {
	  str[j] = '-';
	  j++;
	}
	str[j] = buf[i];
	j++;
      }
      str[j] = '\0';
    }
#endif  
}




long int xatol(str)
     char *str;
{
  char *t;

  for (t = str; *t; t++)
    if (!isdigit ((int) *t))
      return (NOT_OK);

  return (atol (str));
}   


short int verify_month(month)
     char *month;
{
  static char month_names[12][4] = {"JAN", "FEB", "MAR",
                                    "APR", "MAY", "JUN",
                                    "JUL", "AUG", "SEP",
                                    "OCT", "NOV", "DEC"};
  register short int i;

  for (i = 0; i <= 11; i++)
    if (!strcmp (month, month_names[i]))
      return ((short) ++i);
  return ((short) NOT_OK);
}   


short int verify_day(day, month, year)
     short int day, month, year;
{
  if (((day > 0) && (day <= max_days_in_month[month-1])) ||
      ((day == 29) && (month == 2) && !(year % 4)))
    return ((short) OK);
  return ((short) NOT_OK);
}


long int universal_date(day, month, year)
     short int day, month, year;
{
  register short int i;
  long int j;

  year = year % 100;
  year = year + ((year < 70) ? 2000 : 1900);
  j = 365 * (year - 1970) + ((year - 1968) / 4) -
      (((month <= 2) && !(year % 4)) ? 1 : 0);
  for (i = 0; i < month - 1; i++)
    j = j + max_days_in_month[i];
  return (j + day - 1);
}


/* ======================================================================= */
/*                                                                         */
/* Convert the authorization start and end dates to two long integers that */
/* can be used for checking the date.                                      */
/*                                                                         */
/* ======================================================================= */
short int calc_universal_dates(short start_day,  short start_month, short start_year,
                               short end_day,    short end_month,   short end_year,
                               long  *start_u_d, long  *end_u_d)
{
    /* If the authorization is permanent, store zeros in the longs */
    /* ----------------------------------------------------------- */
    if ((start_month == 0) && (end_month == 0))
    {
        *start_u_d = 0L;
        *end_u_d = 0L;
    }
    
    /* If the authorization is temporary, base the long values on */
    /* the start and end dates.                                   */
    /* ---------------------------------------------------------- */
    else
    {
        *start_u_d = universal_date (start_day, start_month, start_year);
        *end_u_d = universal_date (end_day, end_month, end_year);
    }
    
    if (*start_u_d > *end_u_d)
    {
        printf ("\nGSI Authorization-- FROM date greater than TO date.\n");
        return ((short) NOT_OK);
    }
    
    return ((short) OK);
}



/* ===================================================================================== */
/*                                                                                       */
/* This function checks the validity of all the date fields in a temporary authorization */
/* record and stores their numeric values work variables that will be used later.        */
/*                                                                                       */
/* ===================================================================================== */
short verify_char_dates(char  *c_start_day, char  *c_start_month,   char *c_start_year,
                        char  *c_end_day,   char  *c_end_month,     char *c_end_year,
                        short *s_start_day, short *s_start_month,   short *s_start_year,
                        short *s_end_day,   short *s_end_month,     short *s_end_year)

{
    if ((*s_start_month = verify_month (c_start_month)) == NOT_OK)
    {
        printf ("\nGSI Authorization-- FROM month is incorrect or in wrong position.\n");
        return ((short) NOT_OK);
    }
    if ((*s_end_month = verify_month (c_end_month)) == NOT_OK)
    {
        printf ("\nGSI Authorization-- TO month is incorrect or in wrong position.\n");
        return ((short) NOT_OK);
    }
    if ((*s_start_year = (short) xatol (c_start_year)) == NOT_OK)
    {
        printf ("\nGSI Authorization-- FROM year is incorrect.\n");
        return ((short) NOT_OK);
    }
    *s_start_year = *s_start_year % 100;
    if ((*s_end_year = (short) xatol (c_end_year)) == NOT_OK)
    {
        printf ("\nGSI Authorization-- TO year is incorrect.\n");
        return ((short) NOT_OK);
    }
    *s_end_year = *s_end_year % 100;
    if (((*s_start_day = (short) xatol (c_start_day)) == NOT_OK) ||
      (verify_day (*s_start_day, *s_start_month, *s_start_year) == NOT_OK))
    {
        printf ("\nGSI Authorization-- FROM day is incorrect.\n");
        return ((short) NOT_OK);
    }
    if (((*s_end_day = (short) xatol (c_end_day)) == NOT_OK) ||
      (verify_day (*s_end_day, *s_end_month, *s_end_year) == NOT_OK))
    {
        printf ("\nGSI Authorization-- TO day is incorrect.\n");
        return ((short) NOT_OK);
    }
    return ((short) OK);
}


/* ============================================================ */
/* Copy just the major version portion (up until the first '.') */
/*                  of "ver" to "majver"                        */
/* ============================================================ */
void major_version(ver, majver)
     char *ver, *majver;
{
    char *s, *t;

    for (s = ver, t = majver; (*s != '.') && (*s != '\0'); *t++ = *s++)
        ;
    *t = '\0';
}


#ifdef vms
#  include <lnmdef.h>
#  include <ssdef.h>
#  include <descrip.h>

int gb_probe_logical_name(logical_name)
     char *logical_name;
{
    struct dsc$descriptor_s logical_name_descriptor;
    struct dsc$descriptor_s destination_descriptor;
    short destination_length;
    char name_table;
    char access_mode;
    char disable_mask = 0;
    char logical_name_string[LNM$C_NAMLENGTH];
    char destination_string[LNM$C_NAMLENGTH];
    
    strcpy (logical_name_string, logical_name);
    logical_name_descriptor.dsc$w_length = strlen(logical_name_string);
    logical_name_descriptor.dsc$a_pointer = logical_name_string;
    logical_name_descriptor.dsc$b_dtype = DSC$K_DTYPE_T;
    logical_name_descriptor.dsc$b_class = DSC$K_CLASS_S;
    
    destination_descriptor.dsc$a_pointer = destination_string;
    destination_descriptor.dsc$b_dtype = DSC$K_DTYPE_T;
    destination_descriptor.dsc$b_class = DSC$K_CLASS_S;
    destination_descriptor.dsc$w_length = LNM$C_NAMLENGTH;
    
    return lib$sys_trnlog (&logical_name_descriptor,
                           &destination_length,
                           &destination_descriptor,
                           &name_table,
                           &access_mode,
                           &disable_mask);
}
#endif /* ifdef vms */


long int weighted_value(char *str)
{
    static long int b = (1L << 26);
    char *t;
    long int j;

    j = 0;
    for (t = str; *t; t++)
        j = ((j << 4) % b) + ((int) *t);

    return (j);
}


void f(weighted_mach_id, weighted_prod, weighted_majvers, start_u_d, end_u_d,
            rtn_codes)
     long int weighted_mach_id, weighted_prod, weighted_majvers, start_u_d, end_u_d,
         rtn_codes[];
{
    static long int modulus = (1L << 23);
    long int mixer_cage[55];
    register short int i;

    for (i = 0; i <= 54; i++)
    {
        mixer_cage[i] = MIXER_PRIME;
        if (!(i % 2))
          mixer_cage[i] = mixer_cage[i] ^ weighted_mach_id;
        if (!(i % 3))
          mixer_cage[i] = mixer_cage[i] ^ weighted_prod;
        if (!(i % 5))
          mixer_cage[i] = mixer_cage[i] ^ weighted_majvers;
        if (!(i % 7))
          mixer_cage[i] = mixer_cage[i] ^ start_u_d;
        if (!(i % 11))
          mixer_cage[i] = mixer_cage[i] ^ end_u_d;
    }
    for (i = 55; i <= 555; i++)
        mixer_cage[i % 55] = (mixer_cage[(i - 24) % 55] +
                          mixer_cage[(i - 55) % 55]) % modulus;
    for (i = 0; i <= 3; i++)
        rtn_codes[i] = mixer_cage[i];
}   


void g(weighted_mach_id, weighted_prod, weighted_majvers, start_u_d, end_u_d,
            the_codes)
     long int weighted_mach_id, weighted_prod, weighted_majvers, start_u_d, end_u_d,
         the_codes[];
{
  long int value = 0L;
  register short int i;
  static long int modulus = (1L << 15);
  static long int prime = MIXER_PRIME;

  value = (weighted_mach_id % modulus) * prime;
  value = (value % modulus) * prime + start_u_d;
  value = (value % modulus) * prime + end_u_d;
  value = (value % modulus) * prime + weighted_prod;
  value = (value % modulus) * prime + weighted_majvers;
  for (i = 0; i <= 3; i++)
    value = (value % modulus) * prime + the_codes[i];
  the_codes[4] = value;
}   



#ifdef NEVER_DEFINE /* not usually included in object code for security reasons.*/
/*                                                                  */
/* gen_codes                                                        */
/*                                                                  */
/* If dates are OK, returns generated codes in a string pre-        */
/* allocated by this function's caller and pointed to by s_codes.   */
/* Inputted dates are in the format "29 FEB 72" or are blank for    */
/* permanent authorization.                                         */
/*                                                                  */

short int gen_codes(mach_id, prod, vers, start_date, end_date, s_codes)
     char *mach_id, *prod, *vers, *start_date, *end_date, *s_codes;
{
  long int gener_codes[5];
  register short int n;
  short int permanent;
  char c_start_day[30], c_start_month[30], c_start_year[30],
       c_end_day[30], c_end_month[30], c_end_year[30], extra[30];
  long int w_mach_id, w_prod, w_majvers, start_u_d, end_u_d;
  short int s_start_day, s_start_month, s_start_year,
           s_end_day, s_end_month, s_end_year;

  c_start_day[0] = c_start_month[0] = c_start_year[0] =
    c_end_day[0] = c_end_month[0] = c_end_year[0] = '\0';
  permanent = 0;

  gb_normalize_machine_id(mach_id);

  gb_raise_to_uppercase (prod);

  gb_raise_to_uppercase (vers);
  major_version(vers, majvers);
  gb_raise_to_uppercase (start_date);
  gb_raise_to_uppercase (end_date);

  if (((n = sscanf (start_date, "%s%s%s%s",
            c_start_day, c_start_month, c_start_year, extra)) <= 2) &&
      (strlen (c_start_day) <= 2) &&
      (sscanf (end_date, "%s%s%s", c_end_day, c_end_month, c_end_year) <= 2) &&
      (strlen (c_end_day) <= 2)) {
    permanent = 1;
    s_start_day = s_start_month = s_start_year =
      s_end_day = s_end_month = s_end_year = 0;
  } else if (n != 3) {
    printf ("GSI Authorization: FROM date is in wrong format.\n");
    return ((short) FALSE);
  } else if ((n = sscanf (end_date, "%s%s%s%s",
              c_end_day, c_end_month, c_end_year, extra)) != 3) {
    printf ("GSI Authorization: TO date is in wrong format.\n");
    return ((short) FALSE);
  }

  if ((!permanent) &&
      (verify_char_dates (c_start_day, c_start_month, c_start_year,
              c_end_day, c_end_month, c_end_year,
              &s_start_day, &s_start_month, &s_start_year,
              &s_end_day, &s_end_month, &s_end_year) == NOT_OK))
    return ((short) FALSE);
  if (calc_universal_dates (s_start_day, s_start_month, s_start_year,
                s_end_day, s_end_month, s_end_year,
                &start_u_d, &end_u_d) == NOT_OK)
    return ((short) FALSE);

  f ((w_mach_id = weighted_value (mach_id)),
     (w_prod    = weighted_value (prod)),
     (w_majvers = weighted_value (majvers)),
     start_u_d,
     end_u_d,
     gener_codes);

  g (w_mach_id,
     w_prod,
     w_majvers,
     start_u_d,
     end_u_d,
     gener_codes);

  sprintf (s_codes, "%ld %ld %ld %ld %ld",
           gener_codes[0],
           gener_codes[1],
           gener_codes[2],
           gener_codes[3],
           gener_codes[4]);
  return ((short) TRUE);
}
#endif /* NEVER_DEFINE */

/* --------------------------------------------------------------- */
/*                                                                 */
/* periodic: If the record that was used to authorize this bridge  */
/*           is temporary, see if the current date falls within    */
/*           the authorized dates.                                 */
/*                                                                 */
/* Note that stage1 must have been successfully called before      */
/*   calling periodic since stage1 is responsible for filling in   */
/*   the ok structure used by periodic.  stage2 also should have   */
/*   been called to make sure the authorization record is valid.   */
/*                                                                 */
/* The authorization code has been modified to work on machines    */
/*   with multiple dongles and/or multiple network cards.          */
/*   However if in the OK file there is an expired but             */
/*   otherwise valid authorization record before                   */
/*   a completely valid authorization record, authorization will   */
/*   fail.  You should therefore remove expired authorization      */
/*   records from the OK file.                                     */
/*                                                                 */
/* --------------------------------------------------------------- */
short int periodic()
{
    long int now_u_d;
    short int periodic_machine_id();

#ifdef vms
    timeb_t atime;
    
    ftime (&atime);
    now_u_d = atime.time / (24 * 3600);
#endif

#ifdef MSDOS
    time_t ltime;

    time (&ltime);
    now_u_d = (long) ltime / (24 * 3600);
#endif

#ifdef unix
    struct timeval tv;
    struct timezone tz;

    gettimeofday (&tv, &tz);
    now_u_d = tv.tv_sec / (24 * 3600);
#endif

#ifdef AUTH_DEBUG
    printf ("\nnow_u_d=%d start=%d end=%d ok_mach=%s\n",
        now_u_d,
        ok.universal_start_date,
        ok.universal_end_date,
        ok.machine_id);
#endif
  
    if ((((ok.universal_start_date == 0) && (ok.universal_end_date == 0)) ||
         ((ok.universal_start_date <= now_u_d) && (ok.universal_end_date >= now_u_d)))
	&& periodic_machine_id())
        return ((short) TRUE);  

    return ((short) FALSE);
}




/* periodic_machine_id() rechecks the the machine ID's on this system
   to match them against that which was used for the original
   authorization. This is a subfunction of periodic().  This serves to
   detect hot-swapping dongles, and also possibly ethernet cards on
   newer plug-and-play systems. If we have a non-node-specific
   authorization ("SITE license"), the machine ID is not checked at
   all, just the dates. */

short int periodic_machine_id ()
{
  int first_time = TRUE, have_id;
  short int t = (short)TRUE, f = (short)FALSE;  
 
#ifdef AUTH_DEBUG
  printf("Periodic Machine-ID test ... ");
#endif

  if (gb_is_site_machine_id(ok.machine_id)) {
#ifdef AUTH_DEBUG
    printf("OK \"site\": %s\n", ok.machine_id);
#endif
    return t;
  }
  for (first_time = TRUE; TRUE; first_time = FALSE) {
    if (first_time == TRUE)
      have_id = !g2ext_nsleep(buffer);
    else
      have_id = !g2ext_nsleep_next(buffer);
#ifdef AUTH_DEBUG
    if (first_time)
      printf("trying %s vs. ... ", ok.machine_id);
#endif
    if (!have_id)
      break;
    gb_normalize_machine_id(buffer);
#ifdef AUTH_DEBUG
    printf("\n  %s ... ", buffer);
#endif
    if (!strcmp(ok.machine_id, buffer)) {
#ifdef AUTH_DEBUG
      printf("OK: %s\n", ok.machine_id);
#endif
      return t;
    }
  }
#ifdef AUTH_DEBUG
  printf("failed.\n");
#endif
  return f;
}
