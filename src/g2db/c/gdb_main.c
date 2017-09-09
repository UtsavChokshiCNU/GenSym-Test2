/***************************************************************************
:
:  gdb_main.c  --  main subroutine for G2-Database Bridges
:
:  Although this software has been extensively tested, Gensym cannot
:  guarantee error-free performance in all applications.  Accordingly,
:  use of the software is at the customer's sole risk.
:
:                                                                     JUL96
:..........................................................................*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#if defined(UNICODE)
#include <wchar.h>
#endif

#include "gsi_main.h"  
#include "gdb_globals.h"
#include "gdb_utils.h"

extern void signal_handler();
extern void check_triggers();
extern void poll_check();
extern void init_stmt_handle();

/* Build code may be supplied as either a preprocessor definition
or embedded within the GDB_VER e.g. 6_0r2_e13 */
#ifndef BUILD_CODE
#include "build_code.h"
#endif

/* Bridge version must be supplied as a preprocessor definition
in format: 6_0B0 or 6_1R0. Also, a build code may be specified 
e.g. 6_1R0_H07 */
#ifndef GDB_VER
    #define GDB_VER "V12_0r0"
#endif

/* The major version of the database libraries that are used in */
/* the creation of this program, must be provided. It will be   */
/* displayed on the bridge's title line.                        */
/* ------------------------------------------------------------ */
#ifndef DB_VER
    #error Major version of database (DB_VER) not specified.
    #define DB_VER ""
#endif

/* The version of the GSI that is used in the creation of this  */
/* program, must be provided.  It will be displayed on the      */
/* bridge's title line.                                         */
/* ------------------------------------------------------------ */
#ifndef GSI_VER
    #define GSI_VER "12.0"
#endif

/* The type of database this bridge will communicate with must  */
/* be specifed.  It will be displayed on the bridges's title    */
/* line and used for authorization.                             */
/* ------------------------------------------------------------ */
#ifndef DB_TYPE
    #error Database type (DB_TYPE) not specified.
    #define DB_TYPE "?"
#endif

#ifndef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM ""
#endif
#ifdef mips
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "DECStation/Ultrix"
#endif
#if (defined(sun4) || defined(sparc))
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Sun SparcStation"
#endif                                                                   
#ifdef sparcsol
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "SparcStation/Solaris"
#endif
#ifdef vms
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Vax/OpenVMS"
#endif
#ifdef __alpha
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Alpha/OpenVMS"
#endif
#ifdef hp9000s700
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "HP9000s700"
#endif
#ifdef hp9000s800
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "HP9000s800"
#endif
#ifdef _IBMR2
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "IBM RS6000"
#endif
#ifdef linux
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Linux"
#endif
#ifdef alphaosf
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Alpha/OSF"
#endif
#if (defined(WIN32) && !defined(__alpha))
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Windows"
#endif
#if (defined(WIN32) && defined(__alpha))
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Alpha Windows NT"
#endif

BRIDGE_INFO  bridge_info;
long  max_value_array_size = DFLT_VALUE_ARRAY_SZ;
long  max_col_array_size = DFLT_COLUMN_ARRAY_SZ;
long  gdb_charset = DFLT_DB_CHARSET;
long  gdb_poll_check = FALSE;
long  gdb_shutdown_on_disconnect = FALSE ;

gsi_int main(int argc, char *argv[])
{   
    extern short stage1(),stage2();
    gsi_int status = GSI_ACCEPT;
    char   *ptr1,*ptr2;
    /* GENSYMCID-607: Fix licensing issues for all G2 bridges
       Note: we declare them as static to force their memory initialized to zero.
       -- Chun Tian (binghe) / Glority, 2011/11/21 */
    static char bridge_ver[20];
    static char maj_ver[3];
    static char min_ver[3];
    static char mod_ver[4];
    static char mod_char[11]; /* "Diagnostic" + 1 = 11 */
    static char build_ver[5];
    static char gdb_ver[20];
    static char db_ver[6];
    static char gsi_ver[6];
    int     n,x;
    char  **xargv;
    int     xargc;
    char    tmpCharset[MAX_CHARSET_NAME_LEN];
    
/*
 *  Specify GSI run-time options, if any...
 *
 *  GSI uses D_FLOAT for VAX/VMS, and IEEE_FLOAT for Alpha/OpenVMS by default. 
 *  G_FLOAT may be specified at compile time by using the appropriate /"float"
 *  compiler arguments. In the code below the selection of floating point format
 *  is automated for VMS platforms via the use of the symbol CC$gfloat. CC$gfloat
 *  is set to 1 when this file has been compiled with the /G_FLOAT option, and is
 *  set to 1 by default on Alpha's (IEEE is the default for all GSI example code).
 *
 *  Although off by default, GSI_ONE_CYCLE is explicitly reset to 
 *  demonstrate how options are turned off.
 */

#if defined(vms)
#if defined(CC$mixed_float) /* && !defined(__alpha) */
  gsi_set_option(GSI_USE_GFLOATS);
#endif
#endif

#if defined(GSI_IGNORE_USER_RPC_ERRORS)
  /* This prevents gsi-run-loop-abort on 'return (GSI_FAIL)' from user rpcs */
  gsi_set_option(GSI_IGNORE_USER_RPC_ERRORS);
#endif

#if defined(GSI_TRAP_NETWORK_ERRORS)
  /* This prevents gsi-run-loop-abort on network type errors */
  gsi_set_option(GSI_TRAP_NETWORK_ERRORS);
#endif

  /* Enables GSI API functions to access symbols efficiently */
  /*gsi_set_option(GSI_NEW_SYMBOL_API);*/

/*
 *  Set the version control variables to the values defined in gsi_main.h. 
 *  Though optional, this is recommended to ensure version consistency between
 *  the GSI object libraries, and the include file used to compile your
 *  application code.
 */
#if GSI_INCLUDE_MAJ_VER_NUM > 5L
  gsi_set_include_file_version(GSI_INCLUDE_MAJ_VER_NUM, GSI_INCLUDE_MIN_VER_NUM, GSI_INCLUDE_REV_VER_NUM);
  GSI_SET_OPTIONS_FROM_COMPILE();
#else
  gsi_include_file_major_version = GSI_INCLUDE_MAJ_VER_NUM;
  gsi_include_file_minor_version = GSI_INCLUDE_MIN_VER_NUM;
  gsi_include_file_revision_version = GSI_INCLUDE_REV_VER_NUM;
#endif

/*
 *  Set the Bridge and version information.
 */

    if (strcmp(BUILD_CODE,"") != 0) 
    {
		strncpy(build_ver,BUILD_CODE,4);
        as_upper_case(build_ver) ;
	}
	if (strcmp(GDB_VER,"") != 0) 
	{
		strncpy(gdb_ver,GDB_VER,19);
        as_upper_case(gdb_ver) ;
		ptr1 = gdb_ver;
	}
    else 
    {
		printf("\n\nBridge Version has not been specified (GDB_VER).\n\n");
		return 0;
	}

	if (strcmp(DB_VER,"") != 0)
	{
		strncpy(db_ver, DB_VER, 5) ;
        as_upper_case(db_ver) ;
	}
	else
	{
		printf("\n\nDatabase Version has not been specified (DB_VER).\n\n");
		return 0;
	}


	if (strcmp(GSI_VER,"") != 0)
	{
		strncpy(gsi_ver, GSI_VER, 4) ;
        as_upper_case(gsi_ver) ;
	}
	else
	{
		printf("\n\nGSI version has not been specified (GSI_VER).\n\n");
		return 0;
	}

	
	if (*ptr1 == 'V')
		ptr1++;
	ptr2 = maj_ver;
	n = 0;
	while (*ptr1 != 0)
	{
		*ptr2++ = *ptr1++;
		if (*ptr1 == '_' || *ptr1 == '-' || *ptr1 == '.')
		{
			*ptr2 = '\0';
			if (!min_ver[0])
				ptr2 = min_ver;
			else
			{
				if (!build_ver[0])
					ptr2 = build_ver;
				else
					break;
			}
			ptr1++;  
		}
		if (!mod_ver[0] && (*ptr1 == 'B' || *ptr1 == 'R' || *ptr1 == 'A' || *ptr1 == 'D') ) 
		{
			*ptr2 = 0;
			if (*ptr1 == 'A') strcpy(mod_char,"Alpha Rev");
			if (*ptr1 == 'B') strcpy(mod_char,"Beta Rev");
			if (*ptr1 == 'R') strcpy(mod_char,"Rev");
			if (*ptr1 == 'D') strcpy(mod_char,"Diagnostic") ;
			ptr1++;
			ptr2 = mod_ver;
		}
	}
	*ptr2 = 0;
	if (build_ver[0] == 0)
	{
		printf("\n\nBridge Build Version has not been specified (BUILD_CODE).\n\n");
		return 0;
	}

	sprintf(bridge_info.bridge_name,"G2-%s", DB_TYPE);
	sprintf(bridge_info.bridge_version,"%s.%s %s %s (%s-%s-%s)",
		maj_ver, min_ver, mod_char, mod_ver, build_ver, gsi_ver, db_ver);
	sprintf(bridge_ver,"V%s.%s", maj_ver, min_ver);

	printf("\n-----------------------------------------------------------\n");
	printf("Starting %s %s Bridge   Version %s\n for %s",
	bridge_info.bridge_name, DB_VER, bridge_info.bridge_version, BRIDGE_PLATFORM );
#ifdef PROTOTYPE
	printf("   (Prototype for: %s)",PROTOTYPE);
#endif
	printf("\n");
	printf("-----------------------------------------------------------");


	strncpy(bridge_info.bridge_platform,BRIDGE_PLATFORM,MAX_BRIDGE_PLATFORM_LEN);


/*
 *  Check Authorization
 */
    if (stage1(bridge_info.bridge_name,bridge_ver) != TRUE)
      exit(1);
    if (stage2() != TRUE)
      exit(1);

/*
 *  Look for custom command-line arguments. Custom args must be removed from argv
 *  prior to passing on to gsi_start.
 */
    if (argc > 1) 
    {
      xargc = 0;
      xargv = (char **)calloc(argc,sizeof(char *));
      for (n=0;n<argc;n++)
      {
        /* -HELP */
        if(!strcmpci(argv[n],"-HELP")) 
        {
          printf("\n\n");
          printf("Startup Options:\n");
          printf("----------------\n");
          printf("  -maxrows     <integer>\n");
          printf("  -maxcols     <integer>\n"); 
          printf("  -charset     <name>\n"); 
          for (x=1;x<MAX_CHARSET_TYPES;x++)
            printf("      %s\n",DB_CHARSET_NAME[x]);
          printf("  -poll_check\n");
          printf("  -shutdown_on_disconnect\n");
          printf("\n"); 
        }
        /* -MAXROWS */
        if(!strcmpci(argv[n],"-MAXROWS")) 
        { 
            if (n < argc-1) 
            {
                if (*argv[n+1] != '-') 
                {
              max_value_array_size = atol(argv[n+1]);
              if (max_value_array_size <= 0)
                max_value_array_size = DFLT_VALUE_ARRAY_SZ;                
              n++;
            }
          }
          continue;
        }
        /* -MAXCOLS */
        if(!strcmpci(argv[n],"-MAXCOLS")) 
        { 
            if (n < argc-1) 
            {
                if (*argv[n+1] != '-') 
                {
              max_col_array_size = atol(argv[n+1]);
              if (max_col_array_size <= 0)
                max_col_array_size = DFLT_COLUMN_ARRAY_SZ;                
              n++;
            }
          }
          continue;
        }
        /* -CHARSET */
        if(!strcmpci(argv[n],"-CHARSET")) 
        { 
            if (n < argc-1) 
            {
                if (*argv[n+1] != '-') 
                {
              gdb_charset = INVALID_DB_CHARSET;
              strncpy(tmpCharset,argv[n+1],MAX_CHARSET_NAME_LEN);
                    for (x=0; x<MAX_CHARSET_TYPES; x++) 
                    {
                if (!strcmpci(tmpCharset,DB_CHARSET_NAME[x]))
                  gdb_charset = x;
              }
                    if (gdb_charset == INVALID_DB_CHARSET) 
                    {
                printf("\n\n================================================\n");
                printf("ERROR::INVALID STRING CONVERSION STYLE SPECIFIED\n");
#if defined(WIN32)
		printf("--> %s\n\n", _strupr(tmpCharset));
#else
		printf("--> %s\n\n", tmpCharset);
#endif
                printf("Valid Conversion Styles:\n");
                printf("------------------------\n");
                for (x=1;x<MAX_CHARSET_TYPES;x++)
                  printf("  %s\n",DB_CHARSET_NAME[x]);
                printf("================================================\n");
                exit(0);
              }
              n++;
            }
          }
          continue;
        }
        /* -POLL_CHECK */
        if(!strcmpci(argv[n],"-POLL_CHECK")) 
        { 
          gdb_poll_check = TRUE;
          continue;
        }

        /* -SHUTDOWN_ON_DISCONNECT */
        if(!strcmpci(argv[n],"-SHUTDOWN_ON_DISCONNECT"))
        { 
            gdb_shutdown_on_disconnect = TRUE;
            continue;
        }

        /* load non-custom args into xargv for use by gsi_start */
        xargv[xargc] = argv[n];
        xargc++;
      }
    }
    else 
    {
      xargv = argv;
      xargc = argc;
    }

    init_stmt_handle();
/*
 *  Initialize GSI and enter the event handler loop.
 */

/*  Delay setting ONE_CYCLE mode so that we can be sure that bridge startup has
 *  occured. This helps avoid a bug in GSI that results in the bridge hanging
 *  when -tcpipexact is used and the port is in use. The runloop_status flag is
 *  set to 0 in gsi_initialize_context. This hack insures that the bridge has 
 *  started on the desired port and is not hung (5.0r0).
 */

    gsi_set_option(GSI_ONE_CYCLE); /* set 1 cycle mode */

/*  When in CONTINUOUS mode, GSI never returns from gsi_start unless there is 
 *  a program error. When in ONE_CYCLE mode, gsi immediately returns from 
 *  gsi_start. Therefore, gsi_run_loop must be called within a loop to prevent
 *  gsi from exiting the program. 
 */

    gsi_start(xargc, xargv);

/*  Check global error flag which should have been set by gsi_start(). If there 
 *  has been an error, then exit. This helps avoid a problem with -tcpipexact
 *  (5.0r1). 
 */
    if (gsi_last_error() != 0)
      return 0;

/*  
 *  Begin the 'run-loop'
 */
    while (1) /*runloop_status == 0)*/
    {
      gsi_pause();
      gsi_run_loop();
      check_triggers();
      poll_check();
    }
  return 0;

} /* end main */
