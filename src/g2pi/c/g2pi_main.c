/* -*- Mode: C -*-
 *
 * Module GSI_MAIN
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Paul V. Lindenfelzer
 *
 * Rev  Date     Author    Notes
 * 001  12Apr95  P.Hill    Converted to use GSI 3.2. for G2-PI V2.0 
 * 002  02Feb96  P.Hill    Added code for using new PI-API for G2-PI V2.0 
 * 003  24Apr96  P.Hill    Ported the code to Alpha OpenVMS 
 * 004  19Feb02  T.LEE     Upgraded to use GSI 5.1
 * 005  11Oct02  D.Westen  Generate heading from environment. Remove
 *                         option to use GSI 3.
 * 006  27Mar03  D.Westen  Increased limit on number of contexts to 50
 * 007  22Aug03  D.Westen  Report non-zero istat when reading real values
 */
/* ***********************************************************************

	File: gsi_main()

	this file is solely provided for systems that require
	a preprocessor have access to the main routine. This function
	call calls the main routine that does the actual main processing.


   ****************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#ifdef vms
#include <file.h>
#endif

#include "pilogex.h"
#include "CmdLine.h"
#include "gsi_main.h"
#include "osipi.h"
#include "osipi_bridge.h"
#include "log.h"
#include "piapi.h"
#include "gsi_brg.h"
#include "gsi_pi_utils.h"
 
#define LOW_MARK 10

#define OSIPI_PRODUCT "G2-PI"
#ifdef vms
# define OSIPI_PLATFORM "Vax/OpenVMS"
#endif
#ifdef __alpha
# define OSIPI_PLATFORM "Alpha/OpenVMS"
#endif
#ifdef hp9000s700
# define OSIPI_PLATFORM "HP9000s700"
#endif
#ifdef WIN32
# define OSIPI_PLATFORM "Windows"
#endif

#include "build_code.h"

/* Bridge version must be supplied as a preprocessor definition
in format: 6_0B0 or 6_1R0. Also, a build code may be specified 
e.g. 6_1R0_H07 */
#ifndef PIB_VER
    #error Bridge version (PIB_VER) not specified.
    #define PIB_VER ""
#endif

#define  MAX_BRIDGE_VER_LEN         30L
#define  MAX_BRIDGE_PLATFORM_LEN    25L

struct {    char  bridge_version[MAX_BRIDGE_VER_LEN];
            char  bridge_platform[MAX_BRIDGE_PLATFORM_LEN]; } bridge_info;

extern long WriteEnable;

int main (argc, argv)
  int argc;
  char *argv[];
{
    char        *bridge_name=OSIPI_PRODUCT; /* reflects name change */
    char        name[33], address[33] ;
    int32       pistatus;
    int32       bufSize ;
    int32       booConnected ;
    void        *p ;
    char        *ptr1,*ptr2;
    char        bridge_ver[32];
    char        maj_ver[8];
    char        min_ver[3];
    char        mod_ver[4];
    char        mod_char[10];
    char        build_ver[5];
    char        gdb_ver[20];
    char        gsi_ver[8];
    int         n ;
    

    CtxCfg  *pCtxCfg ;

    gsi_reset_option(GSI_STRING_CHECK);
    gsi_reset_option(GSI_ONE_CYCLE);

    /* Set the float option for GSI */
#ifdef vms
#if CC$gfloat
    gsi_set_option( GSI_USE_GFLOATS );
#endif
#endif

/*
 *  Set the Bridge and version information.
 */
	min_ver[0] = mod_ver[0] = build_ver[4] = gdb_ver[19] = gsi_ver[4] = 0;


	if (strcmp(BUILD_CODE,"") != 0)
   {
		strncpy(build_ver,BUILD_CODE,4);
		upper_case(build_ver);
	}
	if (strcmp(PIB_VER,"") != 0) 
	{
		strncpy(gdb_ver,PIB_VER,19);
		upper_case(gdb_ver);
		ptr1 = gdb_ver;
	}
	else 
    {
		printf("\n\nBridge Version has not been specified (PIB_VER).\n\n");
		return 0;
	}
	if (strcmp(GSI_VER,"") != 0)
	{
		strncpy(gsi_ver, GSI_VER, 4) ;
		upper_case(gsi_ver) ;
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
		if (!mod_ver[0] && (*ptr1 == 'B' || *ptr1 == 'R' || *ptr1 == 'A') ) 
		{
			*ptr2 = 0;
			if (*ptr1 == 'A') strcpy(mod_char,"Alpha Rev");
			if (*ptr1 == 'B') strcpy(mod_char,"Beta Rev");
			if (*ptr1 == 'R') strcpy(mod_char,"Rev");
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

	sprintf(bridge_info.bridge_version,"%s.%s %s %s (%s-%s)",maj_ver,min_ver,mod_char,mod_ver,build_ver,gsi_ver);
	sprintf(bridge_ver,"V%s.%s", maj_ver, min_ver);

	printf("\n-----------------------------------------------------------\n");
	printf("Starting G2PI Bridge   Version %s\n for %s",
	bridge_info.bridge_version, OSIPI_PLATFORM );
#ifdef PROTOTYPE
	printf("   (Prototype for: %s)",PROTOTYPE);
#endif
	printf("\n");
	printf("-----------------------------------------------------------\n");


/*  Set version control variables to allow the GSI engine to
    check include file versions against GSI library version.
    ---------------------------------------------------------*/
	  gsi_set_include_file_version(GSI_INCLUDE_MAJ_VER_NUM, 
					   GSI_INCLUDE_MIN_VER_NUM, 
					   GSI_INCLUDE_REV_VER_NUM);
	  GSI_SET_OPTIONS_FROM_COMPILE();
	  gsi_set_option(GSI_STRING_CHECK) ;

  /* check for authorization */
    if( stage1(bridge_name, bridge_ver) != TRUE )
        exit(1);
    if( stage2() != TRUE )
        exit(1);

    /* We need to set the logging defaults for the context-less case */
    /* before processing the initializaton commands.                 */
    /* ------------------------------------------------------------- */
    pCtxCfg = &CtxCfgs[MAXCONTEXTS] ;
    pCtxCfg->log_level =     defLogLev ; 
    pCtxCfg->log_to_screen = defScreenLog ;
    pCtxCfg->log_to_file =   defFileLog ;
    pCtxCfg->log_to_mb =     FALSE ;
    pCtxCfg->log_to_g2 =     FALSE ;
    pCtxCfg->log_to_pi =     defPILog ;


    /* Scan command line arguments before passing them to GSI */
    /* ------------------------------------------------------ */
    procCmdLine(argc, argv, TRUE) ;

    /* Get information about default server */
    /* ------------------------------------ */
    bufSize = STRSZ-1 ;
    pistatus = piut_netserverinfo(name, 32, address, 32, &booConnected) ;
    if (pistatus)
    {
        printf( "ERROR: %ld  Unable to retrieve server information\n", pistatus );
        exit( 2 );
    }
    printf( "Connected to %s (%s)\n", name, address );


    /* Begin creating list of servers */
    /* ------------------------------ */
    name[sizeof(name)-1] = address[sizeof(address)-1] = '\0';
    p = malloc(sizeof(serverInfo)) ;
    if (p != NULL)
    {
        gServer = (serverInfo *)p ;
        p = malloc(strlen(name)+1) ;
        if (p != NULL)
        {
            strcpy(p, name) ;
            gServer->srvrName = (char *)p ;
            gServer->fLoggedIn = FALSE ;
            gServer->fUser = FALSE ;
            gServer->fPW = FALSE ;
            gNrServers = 1 ;
        }
    }
    if (p == NULL)
    {
        printf( "ERROR: Unable to allocate memory for server data\n");
        exit( 3 );
    }

    if (loadServerInfo())
        gsi_start(nrArgsForGSI, argsForGSI); /* starts the GSI process */

    piut_disconnect() ;
    exit (0);
}
