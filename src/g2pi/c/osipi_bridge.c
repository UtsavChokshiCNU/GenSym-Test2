/*
*******************************************************************************
*
*   File osipi_bridge.c
*    Paul Lindenfelzer
*
*  This file contains the main portion of the PROTOTYPE bridge for the PI
*  connection.  It performs the basic tasks of defining a point for solicited
*  and exception reporting and then gets the data. 
*
* 
*  file: osipi_bridge.c  11-4-92
*
*   This file contains the prototype for a bridge between G2 and a PI database. The 
*   functionality of the bridge is very simple. There are two types of access to the
*   PI database, real-time and historical.  Each pi-point in G2 maps directly to a point
*   in the PI databased. During definition the point is assigned a pi-point number.
*   This number is used for subsequent access to the database. Real-time point access, 
*   one at a time, can also return the external (or PI) timestamp of the point. Historical,
*   access allow the user to get N values of a given point between times A and B. The
*   historical access is accomplish through RPCs. The real-time access uses automatic 
*   or standard GSI.
*
*   1-4-93: Fixed point history functions and added string-timestamp to vector while at
*           Mobil. - pvl
*
*   While the bridge has passed the testing at Mobil, it still should go through a code 
*   and design walk-through.
*
*
* Modifications:
* 09-12-94: Bug fix in gsi_get_data() with build_timestamp. Arg timestamp
*           should have been passed by reference. This was a regression
*           because this bug was caught before the first release. Need to 
*           check CMS.
* 04-20-95  Upgraded to use GSI 3.2 Beta 33.  Replaced all instances of direct
*           reference to the GSI structures with the GSI access functions.
*           Fixed bugs that prevented exception reporting from working.
* 01-16-96  Created a version that makes use of the new PI-API which uses a
*           client/server architecture.  This new release is initially for
*           HP/UX and uses GSI 3.2R1 it should run on any platform that PI
*           supports.
* 08-28-96  Added support for Digital tags.
* 09-04-96  Changed maximum length of tagname to 80 characters
* 02-19-02  Upgraded to use GSI 5.1r9.  Replaced all obselete APIs with GSI5.0's
* 10-10-02  Fixed exception report bug caused by incorrect usage of pointers
*           and addresses.  Use header filer to avoid compiler warnings.
*           Cleaned up parameters to avoid compiler warnings.
* 10-24-02  Major reorganization in preparation for creation of 5.0.
*           Upgrade to GSI 7.0.
* 03-27-03  Fix of assorted bugs in g2pi 5.0 rev. 0 (such as set not working).
*           Modified to allow 100 contexts.
*
* Copyright (C) 1986-2017 Gensym Corporation.,
* 52 Second Ave, Burlington, MA  01803
*******************************************************************************
*/

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#ifdef vms
#include <descrip.h>
#endif

#ifdef WIN32
#include <WinCrypt.h>
#endif

#include "pilogex.h"
#include "gsi_main.h"
#include "gsi_brg.h"
#include "gsi_pi_utils.h"
#include "log.h"
#include "osipi.h"
#include "osipi_bridge.h"
#include "piapi.h"
#include "piapix.h"
#include "undocRPCs.h"

/* ************************** Global Variables *****************************

   The following section declares the global variables used in the osipi 
   bridge.  The data type definitions are in the file osipi.h. Some of the 
   variables declared in this section are referenced in the file gsi_pi_utils.c

   *************************************************************************/

/* The array of structure that describe/define each context's behavior */
/* Provide one extra position for the context-less case.               */
/* ------------------------------------------------------------------- */
CtxCfg                  CtxCfgs[MAXCONTEXTS+1];

/* The list of PI servers is kept here */
/* ----------------------------------- */
int                     gNrServers ;
serverInfo              *gServer = NULL ;
int                     gCurSrvr = -1 ;


/* Variables that are used by reporting by exception */
/* ------------------------------------------------- */
exInfo                  *pExRptInfo ;
int                     *pNrPIPts ;
int                     NrG2Vars = 0 ;
static char             PIText[STRSZ] ;

long                    pistatus;
function_handle_type    ErrorHandle[MAXCONTEXTS];


/*                 Array of commonly needed attributes                */
/* (OBJECT-INDEX, PI-POINT, LAST-RECORDED-PI-TIME, AUX-CODE, AUX-MSG) */
/* ------------------------------------------------------------------ */
gsi_attr            *gAttr ;
gsi_registered_item *gptRet_array;          /*  will allocate MAXPOINTSPERCALL during initialization */

/* ----------------------------------------------------------------------- */
/* Global data for initializing and managing RPC calls that store values   */
/* in the attributes of an object.  At this writing, this is used strictly */
/* for retrieving historical data from the PI server.                      */
/* ----------------------------------------------------------------------- */

/* There should be one such section for each retrieval type: */
/* --------------------------------------------------------- */
#define NR_TV_ATTS 3
gsi_attr    *piHistoryAttr ;   // initialized in gsi_set_up()

/* This is the table that is used by rpc_name_vector to define */
/* the attributes into which retrieved data will be stored.    */
/* For each new retrieval type, you should add an rpcWarDesc   */
/* with the appropriate information to masterRPCtable and      */
/* rpc_name_vector will work correctly for the new type.       */
/* ----------------------------------------------------------- */
typedef struct rpcWorkAreaDesc  {   gsi_char        *typeFld ;
                                    gsi_attr        **vectorArray ;
                                    unsigned short  arraySize ;
                                    unsigned short  timed ; }   rpcWarDesc;

rpcWarDesc  masterRPCtable[] =  {  { "TIMEVECTOR", &piHistoryAttr, NR_TV_ATTS, TRUE } } ;

#define NR_RPC_TYPES sizeof(masterRPCtable)/sizeof(rpcWarDesc)


/* An array for sending messages to G2 */
char            str_temp[STRSZ];

/* Shutting down flag */
/* ------------------ */
short           gShuttingDown = FALSE ;

short           deReging ;


/* ======================================================================== */
/*                                                                          */
/*      Program Initialization ... called when bridge is first started      */
/*                                                                          */
/* ======================================================================== */
void gsi_set_up()
{ 
    int     i, nrAtts ;

    LOGMSG(LLEVDEBUG, "gsi_set_up") ;


    /* Initialize the table of commonly used attributes */
    /* ------------------------------------------------ */
    gAttr = gsi_make_attrs_with_items(NUMPIVECTORS) ;
    gsi_set_attr_name(gAttr[INDEX_POS], OBJ_INDEX_SYMBOL);
    gsi_set_attr_name(gAttr[PIID_POS],  PIID_SYMBOL);
    gsi_set_attr_name(gAttr[LRPT_POS],  LRPT_ATTRIBUTE);
    gsi_set_attr_name(gAttr[AUXCOD_POS],  AUXCOD_ATTR);
    gsi_set_attr_name(gAttr[AUXMSG_POS],  AUXMSG_ATTR);

    gptRet_array = gsi_make_registered_items(MAXPOINTSPERCALL);


    /* For each RPC retrieval type create an array of gsi_attrs with items */
    /* ------------------------------------------------------------------- */
    for (i=0 ; i < NR_RPC_TYPES ; i++)
    {
        nrAtts = masterRPCtable[i].arraySize ;
        *(masterRPCtable[i].vectorArray) = gsi_make_attrs_with_items(nrAtts) ;
    }

    /* Since, at this time, we only have one retrieval type, and since the */
    /* Gensym PI bridge provides predefined variable types with attributes */
    /* for storing the retrieved values, we can save the user work by      */
    /* pre-initializing the program variables used by rpc_get_timed_values */
    /* and rpc_get_interp_values.                                          */
    /* ------------------------------------------------------------------- */
    gsi_set_attr_name(piHistoryAttr[0], "TIMED-VALUE") ;
    gsi_set_attr_name(piHistoryAttr[1], "TIMEDATE-SECONDS") ;
    gsi_set_attr_name(piHistoryAttr[2], "TIMEDATE-TEXT") ;

    /* Flag all (real) contexts as being inactive */
    /* ------------------------------------------ */
    memset(CtxCfgs, 0, sizeof(CtxCfgs)-sizeof(CtxCfg)) ;    



    /* Declare local functions that can be called from G2 */
    /* -------------------------------------------------- */
    gsi_rpc_declare_local(rpc_name_vector,       "NAMETIMEVECTOR" );
    gsi_rpc_declare_local(rpc_get_timed_values,  "GETTIMEDVALS" );
    gsi_rpc_declare_local(rpc_get_interp_values, "GETINTERPVALS" );
    gsi_rpc_declare_local(rpc_get_pisys_time,    "PISYSTIME" );
    gsi_rpc_declare_local(rpc_get_property,      "GET-PROPERTY") ;
    gsi_rpc_declare_local(rpc_set_debug_mode,    "SETDEBUG" );
    gsi_rpc_declare_local(rpc_shutdown,          "SHUTDOWN") ;
    gsi_rpc_declare_local(rpc_read,              "READ") ;
    gsi_rpc_declare_local(rpc_trans_stat,        "TRANSLATE-STATUS") ;
    registerLogRPCs() ; 
    registerUndocumentedRPCs() ;

    /* Install an error handler so we can bypass unwanted GSI error messages */
    /* --------------------------------------------------------------------- */
    gsi_install_error_handler(gsi_error_handler) ;
}



/*
*******************************************************************************
*
* Function:    gsi_get_tcp_port
* Purpose:     gsi_get_tcp_port is provided for UNIX platforms to aquire 
*              a TCP/IP port number for the extension code to use.
*              If this function returns a zero then the port number
*              is expected to be the first argument passed to main.
*              If a hard-coded port number is acceptable then a
*              # define GSI_PORT_NUM XXXXX is the easiest solution.
*              Decnet expects the port number to be passed as a 
*              command line argument.
*
* Reference:   GSI Users Manual, section 4.1.2, page 35
*
*******************************************************************************
*/
long gsi_get_tcp_port() 
{ 
  /* register port number for UNIX systems */ 
  return(0); 
} 


/*
*******************************************************************************
    Function: gsi_initialize_context()
    
    Purpose: This function is called by the gsi extension each 
             time the KB is started or restarted. gsi_initialize_context
             should be used to initialize the external application
             and any data buffers or counters.  
     
    Reference:  GSI Users Manual, section 4.1.3, page 36

    This function is used to parse the initialization string. The
    init_str contains one or more of the following RPIS options.

    B - log to message board - {y, n}
    D - Debugging {y, n, most, all, 0-9 }
    E - echo - {y, n} not case sensitive 
    G - log to G2 procedure - {y, n}
    L - Log to file {y, n} 
    O - Log to screen (output) {y, n}
    P - Log to PI {y , n} 
    S - return the attribute "Last recorded PI time" {y, n}
    T - return data with a PI timestamp {y, n}
    X - do exception reporting {y, n}

*******************************************************************************
*/
gsi_int gsi_initialize_context(init_str, str_len) 
     char *init_str;
     gsi_int str_len; 
{

    CtxCfg              *pCtxCfg; 
    ARG_ELEMENT_STRUCT  init_args[MAXINITARGS]; 
    char                c ;
    int                 num_args,status,ret_status; 
    register int        i, iX, iLL ; 
    short               temp_val, badval ;
    gsi_int             iContext = gsi_current_context() ;
#define ERMSGSZ 80
    char                errorMsg[ERMSGSZ+1] ;

    /* check authorization expiration */
    /* ------------------------------ */
    if( periodic() != TRUE )
    {
        printf( "\n\nG2-OSIPI Bridge Authorization has expired.\n" );
        printf( "Please contact Gensym at (781) 265-7301.\n" );
        fwf=TRUE ; // Force immediate write
        CtxCfgs[iContext].log_to_screen = TRUE ;
        logMsgs(LLEVHIGH, "** ", "%s: Bridge authorization has expired.  Shutting down.", NOW) ;
        exit(1);
    }

    /* If we are shutting down, don't accept this connection */
    /* ----------------------------------------------------- */
    if (gShuttingDown)
    {
        LOGMSG(LLEVHIGH, "Connection refused ... shutdown has been requested.") ;
        return GSI_REJECT ;
    }

    /* Enforce the limit of MAXCONTEXTS contexts */
    /* ----------------------------------------- */
    if (iContext >= MAXCONTEXTS)
    {
        logMsgld(LLEVHIGH, "<* ", "Connection refused ... exceeded limit of %ld connections.", (long)MAXCONTEXTS) ;
        return GSI_REJECT ;
    }

    /*  declare the error handler in G2.  This needs to be done before logging */ 
    /* ----------------------------------------------------------------------- */
    gsi_rpc_declare_remote(&ErrorHandle[iContext],"OSI-ERROR",NULL_PTR, NUMERRARGS,0,iContext);

    /* Get a pointer to the context configuration structure */
    /* and initialize it with the default settings.         */
    /* ---------------------------------------------------- */
    pCtxCfg = &CtxCfgs[iContext];
    pCtxCfg->do_echo = DEF_DO_ECHO ;
    pCtxCfg->do_exception = DEF_DO_EXCEPTION ;
    pCtxCfg->do_timestamp = DEF_DO_TIMESTAMP ;
    pCtxCfg->log_level = defLogLev ;
    pCtxCfg->log_to_file = defFileLog ;
    pCtxCfg->log_to_mb = defMsgBdLog ;
    pCtxCfg->log_to_g2 = defG2ProcLog ;
    pCtxCfg->log_to_pi = defPILog ;
    pCtxCfg->log_to_screen = defScreenLog ;
    
    pCtxCfg->alive = TRUE ;

    /* Full logging is now enabled */
    /* --------------------------- */
    logMsgld(LLEVDEBUG,"== ", "gsi_initialize_context. Context # %ld", iContext );

    /* Decode the initialization string */
    /* -------------------------------- */
    num_args = osi_parse_init(init_str, init_args, (unsigned short)str_len);
    for (i=0; i< num_args; i++)
    {
        switch (init_args[i].key)
        {   
            CASE_PREENTRY('B')
            CASE_ENTRY('b',check_yesno,pCtxCfg->log_to_mb,init_args[i].arg,
                "message board logging");

            CASE_PREENTRY('E')
            CASE_ENTRY('e',check_yesno,pCtxCfg->do_echo,init_args[i].arg,"echo");

            CASE_PREENTRY('G')
            CASE_ENTRY('g',check_yesno,pCtxCfg->log_to_g2,init_args[i].arg,
                 "G2 procedure logging");

            CASE_PREENTRY('L')
            CASE_ENTRY('l',check_yesno,pCtxCfg->log_to_file,init_args[i].arg,
                 "log-to-file");

            CASE_PREENTRY('O')
            CASE_ENTRY('o',check_yesno,pCtxCfg->log_to_screen,init_args[i].arg,
                 "log-to-screen");

            CASE_PREENTRY('P')
            CASE_ENTRY('p',check_yesno,pCtxCfg->log_to_pi,init_args[i].arg,
                "log-to-PI");

            CASE_PREENTRY('T')
            CASE_ENTRY('t',check_yesno,pCtxCfg->do_timestamp,init_args[i].arg,
                "timestamp");

            CASE_PREENTRY('X')
            CASE_ENTRY('x',check_yesno,pCtxCfg->do_exception,init_args[i].arg,
                "exception reporting");

            case 'D':
            case 'd':
                        iX = strlen(init_args[i].arg) ;
                        badval = FALSE ;
                        if (iX == 1)
                        {
                            c = tolower(init_args[i].arg[0]) ;
                            if (isdigit(c))
                                pCtxCfg->log_level = c - '0' ;
                            else if (c == 'y' || c == 't')
                                pCtxCfg->log_level = LLEVDEBUG ;
                            else if (c == 'n' || c == 'f')
                                pCtxCfg->log_level = LLEVNORM ;
                            else
                                badval = TRUE ;
                        }
                        else if (isdigit(init_args[i].arg[1]) && 
                            ((iX == 2 && (iLL=atoi(init_args[i].arg))==50) || (iX == 3 &&
                                 isdigit(init_args[i].arg[2]) && (iLL=atoi(init_args[i].arg))==100)))
                            pCtxCfg->log_level= iLL ;
                        else
                            badval = TRUE ;
                        if (badval)
                            LOGMSG(LLEVHIGH, "Invalid log level in initialization string") ;
                        break ;

            default:    
                        _snprintf(errorMsg, ERMSGSZ, "Invalid key (%c) in initialization string", init_args[i].key) ;
                        LOGMSG(LLEVHIGH, errorMsg);
                        break;
        }

  }


    return (GSI_ACCEPT); 
}

/*
*******************************************************************************
  Function: gsi_receive_registration
  Purpose:  gsi_receive_registration is called by the GSI extension once for 
        each enabled GSI variable, after the KB has been
        started.  This routine is also called whenever G2
        adds to or changes the Attributes Which Identify a 
        Sensor attribute for a GSI variable.
 
  Reference:    GSI Users Manual, section 4.2.2, page 38.
 
  This function first gets the tagname type and finds the point
  description.  

  This function is also responsible for populating the exception reporting list.
  The maximum allowable sensors on the list is MAXEVMPOINTS.  This function 
  simply adds a new number to the list.  There are two arrays used to handle
  this. The first is the PtIdList, the next is PtObjIndexList. If the bridge
  is to report via exceptions then it will store the Pt in the first list and
  the object index in the second. The will also be a global indicator for the
  max PtPointLoc. This will speed up installation of and searching for new 
  points. For future releases this will be changed to a linked list, but for 
  now we are using a simpler method.  The linked list will be much more 
  efficient since we will be able to easily order the Ptids.

*******************************************************************************
*/
void gsi_receive_registration(registration)
    gsi_registration registration;

{
    gsi_attr            ia1 = identifying_attr_of(registration,1);
    gsi_attr            ia2 = identifying_attr_of(registration, 2), *pToAttrs ;
    gsi_registered_item *pRegItem = gsi_make_registered_items(1);
    gsi_attr            *ret_vector = gsi_make_attrs_with_items(NUMPIVECTORS);
    gsi_int             iContext = gsi_current_context(), attrType, nrAttrsBack ;
    gsi_int             statBack = NO_ERR ;

    GsiPiPointStruct    *pi_ptr;
    PIAPI_STRUCT        api_err;
    PI_EVENT            snX ;
    CtxCfg              *ptrCtxState;

    char                *identifying_attribute_value ;
    static char         piTagName[CHARSPERLONGTAG+1];
    int                 nrAts = 1, tellPI=0, i, len, dsrSrv ;
    long                status, num_pts;
    long                ptnr = -1 ;
    char                wrkBuf[STRSZ], srvrName[33], tagName[81], xxx[STRSZ] ;
    char                *pFr, *pTo, c = 'x' ;
    long                my_pi_points[2] = {0};
    short               vtype = 0 ;



    /* Make sure the variable has an identifying attribute that */
    /* defines the associated PI tag.                           */
    /* -------------------------------------------------------- */
    if ((attrType = gsi_type_of(ia1)) != GSI_STRING_TAG &&
               attrType != GSI_SYMBOL_TAG)
    {
        gsi_reclaim_registered_items(pRegItem);
        gsi_reclaim_attrs_with_items(ret_vector);
        LOGMSG(LLEVDEBUG, "gsi_receive_registration") ;
        logMsg(LLEVHIGH,"** ", FALSE, -1, 0, "Unable to register variable. Identifying attribute format error", attrType);
        return;
    }

    /* Print out debugging information if this has been requested */
    /* ---------------------------------------------------------- */
    identifying_attribute_value = (attrType == GSI_STRING_TAG) ? gsi_str_of(ia1) : gsi_sym_of(ia1) ;
    ptrCtxState = (CtxCfg *)&CtxCfgs[iContext];
    sprintf(wrkBuf, "gsi_receive_registration. PI Tag=%s handle=%ld", 
                identifying_attribute_value, gsi_handle_of(registration));
    LOGMSG(LLEVDEBUG,wrkBuf) ;

    /* Associate a gsi_registered_item with the gsi_registration     */
    /* for the object being registered.  We are going to need the    */
    /* gsi_registered_item to set the values of the object-index,    */
    /* pi-point & last-recorded-pi-time attributes of the G2 object. */
    /* ------------------------------------------------------------- */
    gsi_set_handle(*pRegItem, gsi_handle_of(registration));
    vtype = (short)gsi_type_of(registration) ;
    if (vtype != GSI_SYMBOL_TAG)
        gsi_set_type(*pRegItem, vtype) ;
    gsi_set_status(*pRegItem, NO_ERR);


    /* Create a structure for tracking information about both the PI  */
    /* tag and this G2 variable.  Save the address of the structure   */
    /* in gsi_registration structure (so it will be  easy to retrieve */
    /* in other GSI callback functions).                              */
    /* -------------------------------------------------------------- */
    BuildPiPoint(GsiPiPointStruct,1,pi_ptr);
    pi_ptr->pi_srv = pi_ptr->pt_id = -1 ;
    gsi_set_user_data(registration, pi_ptr); 
    if (pi_ptr == 0)
    {
        gsi_reclaim_registered_items(pRegItem);
        gsi_reclaim_attrs_with_items(ret_vector);
        logMsg(LLEVHIGH,"** handle ",FALSE, -1, gsi_handle_of(registration), 
            "Failed to allocate memory for PI/variable info.  Registration failed.",0);
        return;
    }
    pi_ptr->g2_type = gsi_type_of(registration) ;
    pi_ptr->g2_handle = gsi_handle_of(registration);
    pi_ptr->g2_atianr = 0 ;
    pi_ptr->pi_type = 'X' ;
    pi_ptr->pt_id = -1 ;
    pi_ptr->status = NO_ERR ;

    /* Store the handle in the OBJECT-INDEX attribute */
    /* ---------------------------------------------- */
    gsi_set_int(gAttr[INDEX_POS], gsi_handle_of(registration)) ;

    /* Determine if there is a server name */
    /* ----------------------------------- */
    strncpy(wrkBuf, (attrType == GSI_STRING_TAG) ? gsi_str_of(ia1) : gsi_sym_of(ia1), STRSZ-1) ;
    wrkBuf[STRSZ-1]='\0';
    len = strlen(wrkBuf) ;
    pFr = wrkBuf ;
    pTo = srvrName ;
    for (i = 0 ; i < len && i < 32 && (c=*pFr) != ':' ; i++)
        *pTo++ = toupper(*pFr++) ;
    *pTo = '\0' ;

    dsrSrv = 0 ;
    tagName[80] = '\0';

    /* Possible server name : look for the name in the server table */
    /*                        and extract the tag name.             */
    /* ------------------------------------------------------------ */
    if (c == ':')
    {
        for (i = 0 ; i < gNrServers ; i++)
            if (gleich(gServer[i].srvrName, srvrName))
                break ;
        if (i < gNrServers)
        {
            dsrSrv = i ;
            pFr++ ;
            if (strlen(pFr) > 80)
                statBack = PIB_TOOLONG ;
            strncpy(tagName, pFr, 80) ;
        }
    }
    if (c != ':' || i >= gNrServers)
    {
        if (strlen(wrkBuf) > 80)
            statBack = PIB_TOOLONG ;
        strncpy(tagName, wrkBuf, 80) ;
    }


    if (statBack == NO_ERR)
    {
        /* Remember which server is this point's source */
        /* -------------------------------------------- */
        pi_ptr->pi_srv = dsrSrv ;

        /* If necessary, log into the selected server. */
        /* Then switch to it.                          */
        /* ------------------------------------------- */
        statBack = switchToServer(dsrSrv) ;
    }

    if (statBack == NO_ERR)
    {
        /* Get the PI point number */
        /* ----------------------- */
        status = pipt_findpoint(tagName, &ptnr) ;
        pi_ptr->pt_id = ptnr ;
        if (!status)
        {
            /* Store the point number in the PI-POINT attribute */
            /* ------------------------------------------------ */
            gsi_set_int(gAttr[PIID_POS], ptnr) ;
            nrAts++ ;

            /* Get the tag type */
            /* ---------------- */
            statBack = PIPointTypeOf(dsrSrv, ptnr, &(pi_ptr->pi_type) ) ;
            if (statBack == NO_ERR)
            {
                /* Get the initial value if possible */
                /* --------------------------------- */
                snX.bval = xxx ;
                snX.bsize = STRSZ-1 ;
                statBack = ReadPIVal(pi_ptr, &snX);
                snX.bval = xxx ; /* PI function used within ReadPIVal scroggs pointer to text buffer */
                if (statBack == NO_ERR)
                {
                    nrAts++ ;

                    /* Put the PI point value which is stored into snX in pRegItem.          */
                    /* Perform any necessary type conversion.  Timestamp pRegItem if needed. */
                    /* --------------------------------------------------------------------- */
                    PIValToVar(pi_ptr, &snX, pRegItem) ;
                    statBack = gsi_status_of(*pRegItem) ;
                }
            }
        }
        else
            statBack = PIB_NOSUCHTAG ;
    }

    /* If we did not succeed in setting the initial value, use a default value */
    /* ----------------------------------------------------------------------- */
    if (statBack != NO_ERR) 
    {
        switch ( type_of(registration) )
        {
            case GSI_FLOAT64_TAG:   gsi_set_flt(*pRegItem, FLOAT_DEFAULT);
                                    break;
            case GSI_SYMBOL_TAG:    gsi_set_sym(*pRegItem, SYMBOL_DEFAULT);
                                    break ;
            case GSI_STRING_TAG:    gsi_set_str(*pRegItem, SYMBOL_DEFAULT);
                                    break;
            case GSI_INTEGER_TAG:   gsi_set_int(*pRegItem, INTEGER_DEFAULT);
                                    break ;
            case GSI_LOGICAL_TAG:   gsi_set_log(*pRegItem, GSI_FALSE) ;
                                    break ;
        }
        gsi_set_status(*pRegItem, statBack) ;
        pi_ptr->status = statBack ;
        gsi_set_int(gAttr[AUXCOD_POS], 0) ;
        gsi_set_str(gAttr[AUXMSG_POS], "") ;

        if (statBack == PIB_NOSUCHTAG)
            logMsgsld(LLEVHIGH,"** ","Tag \"%s\" not found.  Registration failed (handle %ld)", tagName, pi_ptr->g2_handle) ;
        else if (statBack == PIB_TOOLONG)
            logMsgsld(LLEVHIGH,"** ","Tag starting with \"%s\" is too long.  Registration failed (handle %ld)", tagName, pi_ptr->g2_handle) ;
    }

    /* This is where we return both the initial value and the gathered   */
    /* attribute_values to G2.                                           */
    /* ----------------------------------------------------------------- */
    if (nrAts < 2) gsi_set_int(gAttr[PIID_POS], 0) ;
    if (nrAts < 3) gsi_set_str(gAttr[LRPT_POS], "");
    if (ptrCtxState->do_timestamp)
        gsi_return_timed_attrs(*pRegItem, gAttr, 5, iContext) ;
    else
        gsi_return_attrs(*pRegItem, gAttr, 5, iContext);
 

    /* If we are updating this variable by exception report, we need */
    /* to inform PI and save enough information so * we can find the */
    /* G2 variable when PI gives us this variable's value.           */
    /* ------------------------------------------------------------- */
    if (ptrCtxState->do_exception == TRUE)
    {
        /* Store information about this point and variable */
        /* ----------------------------------------------- */
        if (statBack == NO_ERR && UpdateEventList(pi_ptr, &tellPI) == GSI_SUCCESS)
        {

            /* Tell PI to report value changes */
            /* ------------------------------- */
            if (tellPI)
            {
                num_pts = 1;
                my_pi_points[0] = ptnr;
                pistatus = pisn_evmestablish(&num_pts, my_pi_points);

                /* If the request of PI failed, report it */
                /* -------------------------------------- */
                if (pistatus < 0)
                {
                    logMsg(LLEVHIGH,"** ",FALSE, -1, ptnr, 
                        "Failed to initialize exception reporting for this point", pistatus);
                }

                /* Report the results if either there was an error or a high debug */
                /* level is selected.  (Decision to print made by piapi_error).    */
                /* --------------------------------------------------------------- */
                strcpy( api_err.funct_name, "PISN_EVMESTABLISH" );
                api_err.pi_status = pistatus;
                api_err.pi_point = ptnr;
                api_err.object_ind = gsi_handle_of( registration );
                sprintf (api_err.arguments, "<count = %d> <point = %d>", 
                       num_pts, my_pi_points[0]);
                piapi_error( &api_err );
            }
        }
        else
            logMsg(LLEVHIGH, "** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, 
                "Failed to register variable for exception reporting", tellPI);
    }

    /* Determine if we should return PI attibute values */
    /* ------------------------------------------------ */
    for (i = 2 ; i <= 6 ; i++)
        if (gsi_type_of(gsi_identifying_attr_of(registration, i)) == GSI_STRUCTURE_TAG)
        {
            pi_ptr->g2_atianr = i ;
            break ;
        }

    /* Retrieve the PI attributes */
    /* -------------------------- */
    if (i <= 6 && pi_ptr->status == NO_ERR)
    {
        RetrievePIAttrs(*pRegItem, &nrAttrsBack, &pToAttrs) ;
        if (nrAttrsBack > 0)
        {
            gsi_return_attrs(*pRegItem, pToAttrs, nrAttrsBack, gsi_current_context());        ;
        }
        gsi_reclaim_attrs(pToAttrs) ;        
    }

    gsi_reclaim_registered_items(pRegItem);
    gsi_reclaim_attrs_with_items(ret_vector);

    if (ptrCtxState->log_level >= LLEVMOST)
    {
        sprintf(wrkBuf, "gsi_receive_registration\n<= | pi_point status = %i; pt= %ld; type= %c handle=%d\n",
            pi_ptr->status, ptnr, PITypeToLet(pi_ptr->pi_type), gsi_handle_of(registration));
        logMsg(LLEVMOST,"   ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, wrkBuf, 0) ;
    }
    return;
}


/*
*******************************************************************************
* Function: gsi_receive_deregistrations
* Purpose:  This function is called by the extension whenever
*       G2 wants to stop the external system from sending 
*       data values.  gsi_receive_deregistrations will be called when 
*       a KB is reset or when a GSI variable is disabled 
*       or deleted, or when the Attributes Which Identify 
*       a Sensor change. 
*
* Reference: GSI Users Manual, section 4.2.6, page 40
*       
* The stop_data() routine merely has to remove the exception handling capability
* for this point. However, it only needs to remove it with respect to G2. In
* later versions, for efficiency sake there will be an rpc that will reconfigure
* the exception array.
*
*******************************************************************************
*/
void  gsi_receive_deregistrations(arg_list, count) 
  gsi_registered_item *arg_list; 
  gsi_int count; 
{ 
    register int        i;
    char                dbgLine[STRSZ] ;
    gsi_registered_item *pRegItem;
    CtxCfg              *pCtxState ;
    GsiPiPointStruct    *pi_ptr;
    gsi_int             iContext = gsi_current_context();

    /* Get The System status structure */
    /* ------------------------------- */
    pCtxState = (CtxCfg *)&CtxCfgs[iContext];

    deReging = TRUE ;
    LOGMSG(LLEVDEBUG, "gsi_receive_deregistrations");

    /* Start loop that processes each of the variables being deregistered */
    /* ------------------------------------------------------------------ */
    for (i=0,  pRegItem = arg_list; i < count; i++, pRegItem++)
    {
        /* Whatever we do now, we are going to need the pointer to the       */
        /* GsiPiPointStruct that contains information about the variable/    */
        /* point pair that are now being deregistered.  Extract it from the  */
        /* gsi_registration of the variable.  If for some reason it is not   */
        /* there, we don't have anything else to do for this point.          */
        /* ----------------------------------------------------------------- */
        pi_ptr = gsi_user_data_of(gsi_registration_of(gsi_handle_of(*pRegItem), iContext));
        if (pi_ptr != NULL)
        {
            /* Report deregistration if a high debug level is selected */
            /* ------------------------------------------------------- */
            sprintf(dbgLine, "deregistering G2 variable.  Handle = %ld.  Srvr # %ld.  PI # %ld.",
                pi_ptr->g2_handle, pi_ptr->pi_srv, pi_ptr->pt_id ) ;
            logMsg(LLEVMOST, "   ", FALSE, -1, 0, dbgLine, 0) ;
            
            /* If exception reporting is active, we need to remove the exInfo */
            /* structure that we stored in ExRptInfo so we would know what to */
            /* do when we received a new value.                               */
            /* -------------------------------------------------------------- */
            if (pCtxState->do_exception == TRUE)
            {
                removeExRptInfoFor(pi_ptr);
            }  

            /* Avoid a memory leak */
            /* ------------------- */
            free( pi_ptr );

            /*      Prior versions of this bridge removed pi_ptr from the     */
            /* gsi_registration.  There is no need to do this since GSI will  */
            /* now destroy the gsi_registration.                              */
        }
    }
    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "gsi_receive_deregistrations\n", 0) ;
    deReging = FALSE ;
    return; 
} 


/*
*******************************************************************************
* Function: gsi_get_data
* Purpose:  This function is called by the extension to get 
*       data from the external application.
*
* Reference:    GSI Users Manual, section 4.2.3, page 38
*       
*   Based on review with PI users it does not appear as though there is any
*   advantage to ask for a block of points from pi versus asking for them one
*   at a time.  Therefor this routine will be simple. It will get the values
*   from the list one at a time.
*
*   8-6-93: in an attempt to solve the bizarre Mobil bug where after 3-6 weeks
*   of running without a problem the floating point numbers start to comeback
*   with slightly wrong values. Everyone thinks that there is no way that their
*   stuff (PI or G2) could be wrong so it must be in the bridge. Going with that
*   assumption, half-heartedly, we have added code that can be turned on via a
*   rpc (it just enables the debugger) so that the bridge does not have to be
*   brought down (it appears as though the program needs to be running for a
*   long time for this problem to occur).  We have also tried to simplify the
*   code that asks for the value (e.g. remove the future intended for future
*   use that would allow an array of values to be requested.  Thus in this 
*   routine we do not need the RvalArray, IstatArray or TimeArray). - pvl/
*
*******************************************************************************
*/
void gsi_get_data(arg_list, count) 
  gsi_registered_item *arg_list; 
  gsi_int count; 
{ 

    gsi_registration        *current_ptr;
    gsi_registered_item     *pG2Var ;
    gsi_int                 iContext = gsi_current_context();

    unsigned short          total ;
    register int            i;
    int                     nrAts = 0 ;
    int                     status ;
    short                   LRPTok ;
    
    GsiPiPointStruct        *pInfo;
    PI_EVENT                snX, *pSnap= &snX ;
    CtxCfg                  *pCtxState;

    /* Get the system status */
    /* --------------------- */
    pCtxState = (CtxCfg *)&CtxCfgs[iContext];
    LOGMSG(LLEVDEBUG,"gsi_get_data");

    /* If the context is exception driven, you do not want to solicit values too */
    /* ------------------------------------------------------------------------- */
    if (pCtxState->do_exception == TRUE)
        return ;

    /* Start of loop to process one variable at a time */
    /* ----------------------------------------------- */
    for (i=0, total=0, pG2Var = arg_list; i< count; i++, pG2Var++)
    {
        current_ptr = gsi_registration_of(gsi_handle_of(*pG2Var), iContext);
        if (current_ptr == 0)
        {
            logMsgll(LLEVHIGH, "** ", 
                "Registration for variable with handle %ld, context %ld not found",
                gsi_handle_of(*pG2Var), iContext) ;
            continue ;
        }
        LRPTok = false ; /* Last read PI Time not prepared yet */

        /* get the information structure */
        /* ----------------------------- */
        pInfo = (GsiPiPointStruct *)gsi_user_data_of(gsi_registration_of(gsi_handle_of(*pG2Var), iContext));
        if (pInfo == 0)
        {
            logMsg(LLEVHIGH,"** handle ", FALSE, -1, gsi_handle_of(*pG2Var),
                "PI/variable information for handle/(context) not found", iContext) ;
            status = PIB_NODEF ;
        }
        else if (pInfo->pt_id < 0)
        {
            logMsgll(LLEVALL,"** ", 
                       "get_data: unknown PI point for variable # %ld, context %ld", 
                       pInfo->pt_id, iContext) ;
            continue ;
        }
        else
        {

            /* Read the current PI value */
            /* ------------------------- */
            pSnap->bval = PIText ;
            pSnap->bsize = STRSZ-1 ;
            status = ReadPIVal(pInfo, pSnap) ;
            pSnap->bval = PIText ;
            if (status == NO_ERR)
            {
                LRPTok = TRUE ;
        
                /* Prepare to send the value to G2 */
                /* ------------------------------- */
                PIValToVar(pInfo, pSnap, pG2Var) ;
            }
            else
            {
                gsi_set_status(*pG2Var, status) ;
                gsi_set_int(gAttr[AUXCOD_POS], 0) ;
                gsi_set_str(gAttr[AUXMSG_POS], "") ;
            }
        }

        /* Send it to G2 */
        /* ------------- */
        if (LRPTok)
        {
            if (pCtxState->do_timestamp)
                gsi_return_timed_attrs(*pG2Var, &gAttr[LRPT_POS], 3, iContext);
            else
                gsi_return_attrs(*pG2Var, &gAttr[LRPT_POS], 3, iContext) ;
        }

        total++;
    } /* end of the for loop */

    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "gsi_get_data", 0) ;
    return ;
    
} 
 
/*
*******************************************************************************
* Function: gsi_set_data
* Purpose:  This function is called by the extension to set 
*       the values of external variables.
*
* Reference:    GSI Users Manual, section 4.2.5, page 40
* 
* This function is similar to the get_data routine except that the values are
* put to the database.  The function putsnapshot() is used to write value to
* the system. This function also checks to see if the system has been put in
* echo mode. If it has the value is echoed back to G2 immediately.  
*
* A requirement was added by Mobil to disable the write capability altogether.
*
*******************************************************************************
*/
void gsi_set_data(arg_list, count) 
  gsi_registered_item *arg_list; 
  gsi_int count; 
{ 
    static char         txtBuf[STRSZ] ;

    gsi_registered_item *arg_ptr, *ret_arg_ptr;
    gsi_registration    *current_ptr;
    gsi_int             giX ;
    gsi_int             iContext = gsi_current_context();
    gsi_int             srcType ;
    
    GsiPiPointStruct    *pi_ptr, trick;
    CtxCfg              *systatus;
    PI_EVENT            snapX ;
    static DIG_STRUCT   *first_dnode;

    gsi_char            *txtIn, successMsg[STRSZ], valueStr[STRSZ] ;
    double              fltX ;
    int                 ToPIStat, x ;
    register int        i;
    long                pt_id, piStat;
    long                dig0, digr ;
    long                liX ;
    long                timedate ;
    long                holdTimeDate[6] ;
    short               holdTSF ;
    short               userTS ;
    gsi_int             nrSeqEls ;
    gsi_int             tX ;
    gsi_item            *pSetVals ;
    gsi_char*           strTS ;
    gsi_int             holdIntVal ;
    double              holdFltVal ;
    gsi_symbol          holdSymVal ;

    unsigned short      total, phase ;
    size_t              len ;
    long                relTime ;
    long                uxTime ;
    PITIMESTAMP         udTime ;
        
 
#ifdef vms
  char        digstate[CHARSPERDIGSTATE+1];
  $DESCRIPTOR(digstateD, digstate);
#endif


    /* get the system status */
    systatus = (CtxCfg *)&CtxCfgs[iContext];
    LOGMSG(LLEVDEBUG,"gsi_set_data");


    /* Start of loop that processes one set command per pass */
    /* ----------------------------------------------------- */
    for (i=0, total = 0, arg_ptr = arg_list , ret_arg_ptr = gptRet_array; i < count; i++, arg_ptr++)
    {
        current_ptr = gsi_registration_of(gsi_handle_of(*arg_ptr),iContext);
        if (current_ptr == 0)
        {
            logMsg(LLEVHIGH, "** handle", FALSE, -1, gsi_handle_of(*arg_ptr), "Object not found",0) ;
            continue;
        }

        /* setup return data */
        /* ----------------- */
        gsi_set_handle(*ret_arg_ptr, gsi_handle_of(*arg_ptr));
        gsi_set_status(*ret_arg_ptr, NO_ERR);
        gsi_set_type(*ret_arg_ptr, INTEGER_TAG);
    
        /* get the element */
        pi_ptr = (GsiPiPointStruct *)gsi_user_data_of(gsi_registration_of(gsi_handle_of(*arg_ptr), iContext));
        if (pi_ptr == 0)
        {
            logMsg(LLEVHIGH, "** handle ", FALSE, -1, gsi_handle_of(*arg_ptr),
                "PI/point info missing", 0) ;
            continue;
        }

        if (pi_ptr->status == PIB_NOSUCHTAG || pi_ptr->status == PIB_TOOLONG || pi_ptr->pt_id < 0)
        {
            logMsg(LLEVHIGH,"** handle ",FALSE, -1, gsi_handle_of(*arg_ptr),
                "set failed.  Variable not registered.", 0) ;
            continue;
        } 
        pi_ptr->status = NO_ERR ;
        pt_id = pi_ptr->pt_id;

        if ( !pt_id )
        {
            logMsg(LLEVHIGH,"** handle",FALSE, -1, gsi_handle_of(*arg_ptr),
                "set failed.  Unable to find PI point number.", 0) ;
            continue;
        } 

        srcType = gsi_type_of(*arg_ptr) ;
        ToPIStat = NO_ERR ;
        piStat = 0 ;

        /* Has the user provided a valid timestamp? */
        /* ---------------------------------------- */
        userTS = (srcType == GSI_SEQUENCE_TAG) ;
        if (userTS)
        {
            nrSeqEls = gsi_element_count_of(*arg_ptr) ;
            if (nrSeqEls != 2)
            {
                logMsg(LLEVHIGH,"** ",FALSE, -1, gsi_handle_of(*arg_ptr),
                   "set failed.  Incorrect # of elements in value/timestamp sequence", nrSeqEls) ;
                continue ;
            }
            pSetVals = gsi_elements_of(*arg_ptr) ;
            tX = gsi_type_of(pSetVals[1]) ;
            if (tX != GSI_STRING_TAG)
            {
                logMsg(LLEVHIGH,"** ",FALSE, -1, gsi_handle_of(*arg_ptr),
                   "set failed.  Timestamp is not a string", tX) ;
                continue ;
            }
            strTS = gsi_str_of(pSetVals[1]) ;
            time(&relTime) ;
            liX=pitm_parsetime(strTS, relTime, &uxTime) ;
            if (liX)
            {
                logMsg(LLEVHIGH,"** ",FALSE, -1, gsi_handle_of(*arg_ptr),
                   "set failed.  Invalid timestamp", tX) ;
                continue ;
            }
            pitm_setpitime(&udTime, uxTime, 0) ;

            /* Now that we have the timestamp, force the registered item */
            /* to the value which is the first element of the sequence.  */
            /* --------------------------------------------------------- */
            srcType = gsi_type_of(pSetVals[0]) ;
            switch (srcType)
            {
            case GSI_INTEGER_TAG:   holdIntVal = gsi_int_of(pSetVals[0]);
                                    gsi_clear_item(*arg_ptr) ;
                                    gsi_set_int(*arg_ptr, holdIntVal) ;
                                    break ;
            case GSI_FLOAT64_TAG:   holdFltVal = gsi_flt_of(pSetVals[0]);
                                    gsi_clear_item(*arg_ptr) ;
                                    gsi_set_flt(*arg_ptr, holdFltVal) ;
                                    break ;
            case GSI_LOGICAL_TAG:   holdIntVal = gsi_log_of(pSetVals[0]) ;
                                    gsi_clear_item(*arg_ptr) ;
                                    gsi_set_log(*arg_ptr, holdIntVal) ;
                                    break ;
            case GSI_STRING_TAG:    txtIn = gsi_str_of(pSetVals[0]) ;
                                    gsi_clear_item(*arg_ptr) ;
                                    gsi_set_str(*arg_ptr, txtIn) ;
                                    break ;
            case GSI_SYMBOL_TAG:    holdSymVal = gsi_sym_of(pSetVals[0]) ;
                                    gsi_clear_item(*arg_ptr) ;
                                    gsi_set_sym(*arg_ptr, holdSymVal) ;
                                    break ;
            }

        }


        /* Prepare debug statement explaining request */
        /* ------------------------------------------ */
        sprintf(successMsg,"request to set PI point # %ld to ", pt_id);
        switch (srcType)
        {
            case GSI_INTEGER_TAG:   sprintf(valueStr,"the integer %ld.", gsi_int_of(*arg_ptr));
                                    break ;
            case GSI_FLOAT64_TAG:   sprintf(valueStr,"the float %g.", gsi_flt_of(*arg_ptr));
                                    break ;
            case GSI_LOGICAL_TAG:   sprintf(valueStr,"the truth-value %s.", 
                                        gsi_log_of(*arg_ptr)==GSI_TRUE?"TRUE":"FALSE");
                                    break ;
            case GSI_STRING_TAG:    txtIn = gsi_str_of(*arg_ptr) ;
            case GSI_SYMBOL_TAG:    if (srcType == GSI_SYMBOL_TAG)  txtIn=gsi_sym_of(*arg_ptr) ;
                                    len = strlen(txtIn) ;
                                    if (len <= sizeof(valueStr))
                                        sprintf(valueStr, "\"%s\"") ;
                                    else
                                        sprintf(valueStr, srcType == GSI_STRING_TAG ?
                                                "a text of length %ld" : "a symbol of length %ld",
                                                          len) ;
                                    break ;
            default:                sprintf(valueStr, "a value of type %ld", srcType) ;
        }
        strncat(successMsg, valueStr, STRSZ-1-strlen(successMsg)) ;
        successMsg[STRSZ-1] = '\0' ;
        logMsg(LLEVMOST, "   ", FALSE, -1, 0, successMsg, 0) ;

        /* Perform type conversion, if possible */
        /* ------------------------------------ */
        trick = *pi_ptr ;
        snapX.bval = txtBuf ;
        snapX.istat = 0 ;
        switch (pi_ptr->pi_type)
        {
            case pipInt:    switch(srcType)
                            {
                                case GSI_INTEGER_TAG:   snapX.ival = gsi_int_of(*arg_ptr) ;
                                                        break ;
                                case GSI_FLOAT64_TAG:   fltX = gsi_flt_of(*arg_ptr) ;
                                                        if (fltX >= LONG_MIN && fltX <= LONG_MAX)
                                                            snapX.ival = (long)fltX ;
                                                        else
                                                            ToPIStat = PIB_BADTYPE ;
                                                        break ;
                                case GSI_LOGICAL_TAG:   if (gsi_log_of(*arg_ptr) == GSI_TRUE)
                                                            snapX.ival = -1 ;
                                                        else
                                                            snapX.ival = 0 ;
                                                        break ;
                                case GSI_STRING_TAG:    txtIn = gsi_str_of(*arg_ptr) ;
                                                        x = sscanf(txtIn, "%lg", &fltX) ;
                                                        if (x == 1 && fltX >= LONG_MIN && fltX <= LONG_MAX)
                                                            snapX.ival = (long)fltX ;
                                                        else
                                                            ToPIStat = PIB_BADTYPE ;
                                                        break ;
                                case GSI_SYMBOL_TAG:    txtIn = gsi_sym_of(*arg_ptr) ;
                                                        x = sscanf(txtIn, "%lg", &fltX) ;
                                                        if (x == 1 && fltX >= LONG_MIN && fltX <= LONG_MAX)
                                                            snapX.ival = (long)fltX ;
                                                        else
                                                            ToPIStat = PIB_BADTYPE ;
                                                        break ;

                                default:                ToPIStat = PIB_BADTYPE ;


                            }
                            if (ToPIStat == NO_ERR)
                            {
                                phase = 1 ;
                                if ((ToPIStat=switchToServer(pi_ptr->pi_srv))== NO_ERR)
                                {
                                    phase = 2 ;
                                    if (!(piStat=pisn_putsnapshotx(pi_ptr->pt_id, NULL, &snapX.ival, NULL, NULL, 
                                                                    NULL, NULL, userTS ? &udTime : NULL)))
                                    {
                                        phase = 3 ;
                                        trick.pi_type = pipInt ;
                                        sprintf(successMsg, "set to %ld.", snapX.ival) ;
                                    }
                                }
                                break ;
                         }
                         else
                         {
                             logMsg(LLEVHIGH,"** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, 
                                 "Unable to convert set value to integer.", srcType) ;
                             continue ;
                         }

            case pipFlt:    switch(srcType)
                            {
                                case GSI_INTEGER_TAG:   snapX.drval = (double)gsi_int_of(*arg_ptr) ;
                                                        break ;
                                case GSI_FLOAT64_TAG:   snapX.drval = gsi_flt_of(*arg_ptr) ;
                                                        break ;
                                case GSI_LOGICAL_TAG:   if (gsi_log_of(*arg_ptr) == GSI_TRUE)
                                                            snapX.drval = -1.000 ;
                                                        else
                                                            snapX.drval = 0.0 ;
                                                        break ;
                                case GSI_STRING_TAG:    txtIn = gsi_str_of(*arg_ptr) ;
                                                        x = sscanf(txtIn, "%lg", &fltX) ;
                                                        if (x == 1)
                                                            snapX.drval = fltX ;
                                                        else
                                                            ToPIStat = PIB_BADTYPE ;
                                                        break ;
                                case GSI_SYMBOL_TAG:    txtIn = gsi_sym_of(*arg_ptr) ;
                                                        x = sscanf(txtIn, "%lg", &fltX) ;
                                                        if (x == 1)
                                                            snapX.drval = fltX ;
                                                        else
                                                            ToPIStat = PIB_BADTYPE ;
                                                        break ;
                                default:                ToPIStat = PIB_BADTYPE ;
                            }
                            if (ToPIStat == NO_ERR)
                            {
                                phase = 1 ;
                                if ((ToPIStat=switchToServer(pi_ptr->pi_srv))== NO_ERR)
                                {
                                    phase = 2 ;
                                    if (!(piStat = pisn_putsnapshotx(pi_ptr->pt_id, &snapX.drval, NULL, NULL, NULL, 
                                                                        NULL, NULL, userTS ? &udTime : NULL)))
                                    {
                                        phase = 3 ;
                                        trick.pi_type = pipFlt ;
                                        sprintf(successMsg, "set to %f.", snapX.drval) ;
                                    }
                                }
                                break ;
                            }
                            else
                            {
                                logMsg(LLEVHIGH,"** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, 
                                     "Unable to convert set value to float.", srcType) ;
                                continue ;
                            }

            case pipDig:    switch(srcType)
                            {                          
                                                        /* See if the integer could be the state code */
                                                        /* ------------------------------------------ */
                                case GSI_INTEGER_TAG:   piStat = pipt_digpointers(pi_ptr->pt_id, &dig0, &digr) ;
                                                        if (piStat)
                                                        {
                                                            ToPIStat = PIB_BAD ;
                                                            break ;
                                                        }
                                                        liX = gsi_int_of(*arg_ptr) ;
                                                        if (liX >= 0 && liX < digr)
                                                            snapX.ival = - (liX + dig0) ;
                                                        else
                                                            ToPIStat = PIB_BADVAL ;
                                                        break ;

                                                        /* Translate the state name to its state number */
                                                        /* -------------------------------------------- */
                                case GSI_STRING_TAG:    txtIn = gsi_str_of(*arg_ptr) ;
                                case GSI_SYMBOL_TAG:    if (srcType == GSI_SYMBOL_TAG)
                                                            txtIn = gsi_sym_of(*arg_ptr) ;
                                                        piStat = pipt_digcodefortag(pi_ptr->pt_id,
                                                            &snapX.ival, txtIn) ;
                                                        if (piStat) ToPIStat = PIB_BADVAL ;
                                                        snapX.ival = -snapX.ival ;
                                                        break ;

                                                        /* It doesn't make sense to set a digital tag */
                                                        /* from a float or a boolean value.           */
                                                        /* ------------------------------------------ */
                                case GSI_FLOAT64_TAG:
                                case GSI_LOGICAL_TAG:
                                default:                ToPIStat = PIB_BADTYPE ;
                            }
                            if (ToPIStat == NO_ERR)
                            {
                                phase = 1 ;
                                if ((ToPIStat=switchToServer(pi_ptr->pi_srv))== NO_ERR)
                                {
                                    phase = 2 ;
                                    if (!(piStat = pisn_putsnapshotx(pi_ptr->pt_id, NULL, &snapX.ival, NULL, NULL, 
                                                                        NULL, NULL, userTS ? &udTime : NULL)))
                                    {
                                        phase = 3 ;
                                        sprintf(successMsg, "set to set %d, code %d.", (-snapX.ival) >> 16, 0xFFFF & -snapX.ival) ;
                                        trick.pi_type = pipDig ;
                                        snapX.istat = snapX.ival ;
                                    }
                                }
                                break ;
                            }
                            else
                            {
                                logMsg(LLEVHIGH,"** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, 
                                    "Unable to convert set value to digital.", srcType) ;
                                continue ;
                            }

            case pipTxt:    switch(srcType)
                            {
                                case GSI_INTEGER_TAG:   liX = gsi_int_of(*arg_ptr) ;
                                                        sprintf(txtBuf, "%ld", liX) ;
                                                        break ;
                                case GSI_FLOAT64_TAG:   fltX = gsi_flt_of(*arg_ptr) ;
                                                        sprintf(txtBuf, "%g", fltX) ;
                                                        break ;
                                case GSI_LOGICAL_TAG:   giX = gsi_log_of(*arg_ptr) ;
                                                        if (giX == 0)
                                                            strcpy(txtBuf, "UNKNOWN") ;
                                                        else
                                                            strcpy(txtBuf, (giX < 0) ? "FALSE" : "TRUE") ;
                                                        break ;
                                case GSI_STRING_TAG:    snapX.bval = gsi_str_of(*arg_ptr) ;
                                                        break ;
                                case GSI_SYMBOL_TAG:    snapX.bval = gsi_sym_of(*arg_ptr) ;
                                                        break ;
                                default:                ToPIStat = PIB_BADTYPE ;
                            }
                            if (ToPIStat == NO_ERR)
                            {
                                phase = 1 ;
                                snapX.bsize = strlen(snapX.bval) ;
                                if ((ToPIStat=switchToServer(pi_ptr->pi_srv))== NO_ERR)
                                {
                                    phase = 2 ;
                                    if (!(piStat = pisn_putsnapshotx(pi_ptr->pt_id, NULL, NULL, snapX.bval,
                                                                &snapX.bsize, NULL, NULL, userTS ? &udTime : NULL)))
                                    {
                                        phase = 3 ;
                                        trick.pi_type = pipTxt ;
                                        sprintf(successMsg, "set to code %s.", snapX.bval) ;
                                    }
                                }
                                break ;
                            }
                            else
                            {
                                logMsg(LLEVHIGH,"** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, 
                                     "Unable to convert set value to text.", srcType) ;
                                continue ;
                            }

            case pipTim:    /* Setting timestamp tags is not supported at this time */
                            logMsg(LLEVHIGH,"** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, 
                                    "Setting timestamp is not supported", 0) ;
                            continue ;

            default:        logMsg(LLEVHIGH,"** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, 
                                 "  Unsupported PI Type", pi_ptr->pi_type) ;
                            continue ;


        }
        if (phase == 1)
        {
            logMsg(LLEVHIGH, "** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, "Failed to connect to server", ToPIStat) ;
            continue ;
        }
        if (phase == 2)
        {
            logMsg(LLEVHIGH, "** ", FALSE, pi_ptr->pi_srv, pi_ptr->pt_id, "Failed to set value", piStat) ;
            continue ;
        }

        logMsg(LLEVDEBUG,NULL,FALSE, pi_ptr->pi_srv, pi_ptr->pt_id,successMsg,0);


        /* everything ok add to the echo list */

        /* If echoing was requested and we successfully set the PI point's value, */
        /* use PIValToVar to generate a gsi_registration_item to return the new   */
        /* value to the G2 variable, then do so.                                  */
        /* ---------------------------------------------------------------------- */
        if (systatus->do_echo == TRUE && ToPIStat == NO_ERR && piStat == 0)
        {
            trick.pt_id = pi_ptr->pt_id ;

            holdTSF = 0 ;
            if (userTS)
            {
                timedate = uxTime ;
            }
            else
            {
                timedate = 0 ;
                if (systatus->do_timestamp)
                {
                    /* If we can't retrieve the PI time, temporarily disable timestamping */
                    /* ------------------------------------------------------------------ */
                    if (pitm_servertime(&timedate) <= 0)
                    {
                        holdTSF = systatus->do_timestamp ;
                        systatus->do_timestamp = 0 ;
                    }
                }
                else
                    timedate = pitm_systime() ;
            }

            if (timedate)
            {
                pitm_secint(timedate, holdTimeDate) ; 
                snapX.timestamp.year   = holdTimeDate[2] ;
                snapX.timestamp.month  = holdTimeDate[0] ;
                snapX.timestamp.day    = holdTimeDate[1] ;
                snapX.timestamp.hour   = holdTimeDate[3] ;
                snapX.timestamp.minute = holdTimeDate[4] ;
                snapX.timestamp.second = (double)holdTimeDate[5] ;
            }

            /* Prepare the LAST-RECORDED-PI-TIME attribute */
            /* ------------------------------------------- */
            sprintf(str_temp, "%02d%02d%04d%02d%02d%02d", snapX.timestamp.month,
                snapX.timestamp.day, snapX.timestamp.year, snapX.timestamp.hour,
                snapX.timestamp.minute, (long)snapX.timestamp.second) ;
            gsi_set_str(gAttr[LRPT_POS], str_temp) ;

            PIValToVar(&trick, &snapX, arg_ptr) ;
            if (holdTSF)
                systatus->do_timestamp = holdTSF ;

            /* Send new value & attributes back to G2 */
            /* -------------------------------------- */
            if (systatus->do_timestamp)
                gsi_return_timed_attrs(*arg_ptr, &gAttr[LRPT_POS], 3, iContext);
            else
                gsi_return_attrs(*arg_ptr, &gAttr[LRPT_POS], 3, iContext) ;
        }

        ret_arg_ptr++;
        total++;
    } /* end of the for loop */
    
    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "gsi_set_data", 0) ;
    return; 
} 


/*
*******************************************************************************
* Function: gsi_pause_context
* Purpose:  This function is called by the extension whenever
*       the G2 KB is paused.  This function should notify 
*       the external application that G2 is unable to accept
*       data and to stop transmitting until the KB has been
*       restarted. 
*
* Reference:    GSI Users Manual, section 4.1.4, page 36
*       
*******************************************************************************
*/
void gsi_pause_context() 
{ 
  LOGMSG(LLEVDEBUG,"gsi_pause_context" );
  return ; 
} 
 

/*
*******************************************************************************
* Function: gsi_resume_context
* Purpose:  gsi_resume_context is called by the GSI extension when
*       the associated KB has been resumed.  This function
*       should notify the external system that G2 is back on
*       line and ready to accept data again.
*
* Reference: GSI Users Manual, section 4.1.5, page 36
*       
*******************************************************************************
*/
void gsi_resume_context() 
{ 
  LOGMSG(LLEVDEBUG, "gsi_resume_context" );
  return ; 
} 


/*
*******************************************************************************
* Function: gsi_shutdown_context
* Purpose:  This function is called by the extension when the 
*       associated G2 is shutdown.  This function should 
*       notify the exterenal application that G2 has shutdown 
*       and take the neccessary actions. 
*
* Reference: GSI Users Manual, section 4.1.6, page 37
* This function needs to decide if the system needs to log off of the PI
* database. If So it does.
*
*******************************************************************************
*/ 
void gsi_shutdown_context() 
{   
    short   i, flLater = FALSE ;
    gsi_int iContext = gsi_current_context()  ;

    /* Remember that this context is inactive */
    /* -------------------------------------- */
    CtxCfgs[iContext].alive = FALSE ;

    LOGMSG(LLEVDEBUG,"gsi_shutdown_context");

 
    /* The following code will only be executed if */
    /* a shutdown of the bridge has been requested */
    /* ------------------------------------------- */
    if (!gShuttingDown)
        return ; 

    /* We will only shut down if all contexts are inactive */
    /* --------------------------------------------------- */
    for (i = 0 ; i < MAXCONTEXTS ; i++)
        flLater |= CtxCfgs[i].alive ;
    if (flLater)
    {
        logMsg(LLEVMOST,"   ", FALSE, -1, 0, "Waiting for all contexts to shut down", 0) ;
        return ;
    }

    /* If the log is open, close it */
    /* ---------------------------- */
    LOGMSG(LLEVNORM, "Shutting down bridge at user request") ;
    if (pLog != NULL)
        fclose(pLog) ;

    /* Say goodbye to PI */
    /* ----------------- */
    piut_disconnect() ;

    /* Bye */
    /* --- */
    exit(0) ;
} 

/*
*******************************************************************************
* Function: gsi_g2_poll
* Purpose:  This function is called by the extension once
*           every clock tick when the Poll External System 
*           for Data attribute is set to YES.  gsi_g2_poll
*           lets the external application return unsolicited
*           values to G2, such as alarms and values out of
*           range. 
*
* Reference: GSI Users Manual, section 4.2.1, page 37
* This function keeps track of the update time and calls the exception 
* reporting routine for each variable.  The variables are established by the
* order in an array that they manage. The array is only MAXEVMPOINTS long. 
* The only way to find the matching event is to traverse the point list and 
* find the matching number. 
*
* Rev  Date      Author     Notes
* 001  13Apr95   P. Hill    Changed the name from gsi_accept_data to 
*                           gsi_g2_poll to conform to GSI3.1        
*******************************************************************************
*/
void gsi_g2_poll() 
{ 
    static int      pollCt[MAXCONTEXTS] ;

    CtxCfg          *pCtxCfg;
    PIAPI_STRUCT    api_err;
    PI_EVENT        snapX ;
    gsi_int         iContext = gsi_current_context();

    char            txtOut[40] ;
    int             nrPiPts, iSrvNr ;
    long            status, ptNr;

    exInfo          *p1stInfo ;


    /* get the system status */
    /* --------------------- */
    pCtxCfg = (CtxCfg *)&CtxCfgs[iContext];

    /* To prevent an excessive number of "gsi_g2_poll" lines in a debug log, */
    /* we only print out and entry message for one in POLL_RPT_FREQ (60)     */
    /* calls to this function unless in at a high debug level.               */
    /* --------------------------------------------------------------------- */
    if (pCtxCfg->log_level < LLEVMOST)
        sprintf(txtOut, "gsi_g2_poll x %ld (ctx %ld)", POLL_RPT_FREQ, iContext) ;
    else
        sprintf(txtOut, "gsi_g2_poll (ctx %ld)", iContext) ;
    if (pollCt[iContext] >= POLL_RPT_FREQ)
        pollCt[iContext] = 0 ;
    if (!pollCt[iContext]++)
        logMsg(LLEVDEBUG, "=> ", TRUE, -1, 0, txtOut, 0) ;
    else
        logMsgld(LLEVMOST,"   ", "gsi_g2_poll (ctx %ld)", iContext);


    /* Find the exception report table for this context */
    /* ------------------------------------------------ */
    if (!pCtxCfg->do_exception)
        return ;


    /* Initialize values needed to retrieve text */
    /* ----------------------------------------- */
    snapX.bsize = STRSZ-1 ;
    snapX.bval = PIText ;


    /* Retrieve the values for any points that are being monitored for */
    /* exception reporting if their values have changed.               */
    /* --------------------------------------------------------------- */
    for (iSrvNr = 0 ; iSrvNr < gNrServers ; iSrvNr++)
    {
        /*      Initialize the number of points to read.     */
        /* This will be changed by the PI exception routine. */
        /* ------------------------------------------------- */
        nrPiPts = pNrPIPts[iSrvNr] ;

        if (nrPiPts > 0)
        {
            if (switchToServer(iSrvNr) == NO_ERR)
            {
                nrPiPts = 1 ;
                pistatus = pisn_evmexceptionsx( &nrPiPts, &ptNr, &snapX, GETFIRST) ;

                while (pistatus != 100)
                {
                    /* Report the call details on an error or high debug level */
                    /* ------------------------------------------------------- */
                    if (pistatus && pollCt[iContext] != 1)
                        LOGMSG(LLEVMOST,"gsi_g2_poll");
                    strcpy( api_err.funct_name, "PISN_EVMEXCEPTIONSX" );
                    api_err.pi_status = pistatus;
                    api_err.pi_point = 0;
                    api_err.object_ind = 0;
                    sprintf (api_err.arguments, "<count = %d>", nrPiPts );
                    piapi_error( &api_err );

                    /* Inform G2 of the error */
                    /* ---------------------- */
                    if (pistatus != 0 )
                    {
                        logMsgsld(LLEVHIGH,"** ", 
                            "Retrieval of value by exception for server %s failed (error code %ld).",
                            gServer[iSrvNr].srvrName, pistatus) ;
                    }
            
                    /* Find the point in pExRptInfo structure */
                    /* -------------------------------------- */
                    else if (GetMatchIndex(iSrvNr, ptNr, &p1stInfo))

                        /* Send the data to G2 */
                        /* ------------------- */
                        status = SendData(&snapX, p1stInfo);
                    else
                        logMsgll(LLEVHIGH, "** ", "Received exception value for unknown variable. Server= %ld.  PI # = %ld", (long)iSrvNr, ptNr) ;

                    /* Try to get information for another point */
                    /* ---------------------------------------- */
                    nrPiPts = 1 ;
                    pistatus = pisn_evmexceptionsx( &nrPiPts, &ptNr, &snapX, GETNEXT) ;
                }
            } 
        }
    }
    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "gsi_g2_poll",0) ;
    return;

} 


 
/*
*******************************************************************************
* Function: gsi_receive_message
* Purpose:  gsi_receive_message is called be the GSI extension whenever
*       it receives a string from G2 as a result of a G2 
*       inform action. 
*
* Reference: GSI Users Manual, section 4.2.3, page 38
* This read text function is used to send messages to log or system output.
* Which one is determined by the initialization string.
*       
*******************************************************************************
*/
void gsi_receive_message(txt_str, str_cnt) 
  gsi_char  *txt_str;
  gsi_int   str_cnt;
{ 

    LOGMSG(LLEVDEBUG, "gsi_receive_message");
    logMsg(0,"", FALSE, -1, 0, txt_str, 0) ;
    return; 

} 



/*  F u n c t i o n s   t h a t   c a n   b e   c a l l e d   f r o m   G 2  */

/* V2 RPCs */
    
/* ========================================================================= */
/*  Tell the bridge the names of the attributes of a variable that will be   */
/*  used for storage of retrieved values.                                    */
/* ========================================================================= */
static void rpc_name_vector(args, count, call_index)
    gsi_item        *args ; 
    gsi_int         count;
    gsi_int         call_index ;
{
    gsi_item        *returnArray = gsi_make_items(RET_ARGS);
    gsi_item        *retrvTypeNameItem = &args[0],
                    *attrNameItem = &args[1] ;
    gsi_attr        *pRetrvAttr ;
    gsi_int         iContext  = gsi_current_context();
    gsi_int         itemType ;
    gsi_char        *retrvTypeName ;
    int             iX ;
    unsigned short  CurRetrvDescSize ;
    short           nrAttrsNeeded ;

    LOGMSG(LLEVDEBUG,"rpc_name_vector");

    /* Make sure there are at least 2 arguments */
    /* ---------------------------------------- */
    if (count >= 2)
    {

        /* Verify that the first argument could be a retrieval class name */
        /* -------------------------------------------------------------- */
        if (((itemType = gsi_type_of(*retrvTypeNameItem)) != GSI_STRING_TAG) &&
            (itemType != GSI_SYMBOL_TAG)) 
        {
            logMsgld(LLEVHIGH,"<* ","First parameter of type %ld cannot be name of vector", itemType) ;
            gsi_set_int(returnArray[CODE_POS], INVALID_VECTORNAME); 
            gsi_set_str(returnArray[MSG_POS], "Invalid vector name - must be type symbol or text"); 
            gsi_rpc_return_values(returnArray, RET_ARGS, call_index, iContext);
            gsi_reclaim_items(returnArray);
            return;
        }

        /*  Find the entry in the master table for this retrieval class   */
        /* -------------------------------------------------------------- */
        retrvTypeName = gsi_str_of(*retrvTypeNameItem) ;
        for (iX = 0 ; iX < NR_RPC_TYPES ; iX++)
        {
            if (strcmp(retrvTypeName, masterRPCtable[iX].typeFld)==0)
                break ;
        }

        /*             Report if this type was not found                  */
        /* -------------------------------------------------------------- */
        if (iX >= NR_RPC_TYPES)
        {
            logMsgs(LLEVHIGH, "<* ", "\"%s\" is not a known vector type.", retrvTypeName) ;
            gsi_set_int(returnArray[CODE_POS], INVALID_VECTORNAME);
            gsi_set_str(returnArray[MSG_POS], "Invalid vector name - vector type not supported"); 
            gsi_rpc_return_values(returnArray, RET_ARGS, call_index, iContext);
            gsi_reclaim_items(returnArray);
            return ;
        }
    }

    /* Make sure that the correct number of arguments were passed to this function */
    /* --------------------------------------------------------------------------- */
    nrAttrsNeeded = masterRPCtable[iX].arraySize ;
    if (count <  2 || count-1 != nrAttrsNeeded)
    {
        logMsgsld(LLEVHIGH, "<* ", "%s vector requires %ld attributes.", 
            retrvTypeName, nrAttrsNeeded ) ;
        gsi_set_int(returnArray[CODE_POS], INVALID_VECTORNAME);
        gsi_set_str(returnArray[MSG_POS], "Invalid vector name - wrong number of attributes"); 
        gsi_rpc_return_values(returnArray, RET_ARGS, call_index, iContext);
        gsi_reclaim_items(returnArray);
        return;
    }

    pRetrvAttr = *(masterRPCtable[iX].vectorArray) ;
    CurRetrvDescSize = masterRPCtable[iX].arraySize ;

    /* Verify that the remaining arguments could contain the names of the attributes */
    /* ----------------------------------------------------------------------------- */
    for (iX = 0 ; iX < CurRetrvDescSize ; iX++)
        if (((itemType = gsi_type_of(attrNameItem[iX])) != GSI_STRING_TAG) &&
            (itemType != GSI_SYMBOL_TAG)) 
        {
            sprintf(str_temp, "Invalid attribute # %d - must be type symbol or text",iX+1);
            LOGMSG(LLEVHIGH, str_temp) ;
            gsi_set_int(returnArray[CODE_POS], INVALID_VECTORNAME);
            gsi_set_str(returnArray[MSG_POS], str_temp);
            gsi_rpc_return_values(returnArray, RET_ARGS, call_index, iContext);
            gsi_reclaim_items(returnArray);
        }

    /* Finally, set the attribute names in the table specific to this retrieval type. */
    /* ------------------------------------------------------------------------------ */
    for (iX = 0 ; iX < CurRetrvDescSize ; iX++)
        gsi_set_attr_name(pRetrvAttr[iX], gsi_str_of(attrNameItem[iX]));
    gsi_set_int(returnArray[CODE_POS], GSI_SUCCESS);
    gsi_set_str(returnArray[MSG_POS],"Success"); 
    gsi_rpc_return_values(returnArray, RET_ARGS, call_index, iContext);
    gsi_reclaim_items(returnArray);
    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "rpc_name_vector", 0) ;
}



/* ========================================================================= */
/*                                                                           */
/*                    Retrieve values from PI archives                       */
/*                                                                           */
/* ========================================================================= */
static void rpc_get_timed_values(args, count, call_index)
     gsi_item *args;
     gsi_int count;
     gsi_int call_index;
{
    int status;

    LOGMSG(LLEVDEBUG,"rpc_get_timed_values");
    status = pi_get_timed_values (args, count, ARCSEQU_MODE, call_index);
    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "rpc_get_timed_values", 0) ;

}


/* ========================================================================= */
/*                                                                           */
/*        Retrieve interpolated values based upon data in PI archives        */
/*                                                                           */
/* ========================================================================= */
static void rpc_get_interp_values(args, count, call_index)
     gsi_item *args;
     gsi_int  count;
     gsi_int  call_index;
{
    int status;

    LOGMSG(LLEVDEBUG,"rpc_get_interp_values");
    status = pi_get_timed_values (args, count, ARCINTERP_MODE, call_index);
    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "rpc_get_timed_values", 0) ;
  
}  

/* ========================================== */
/*                                            */
/* Return the time according to the PI server */
/*                                            */
/* ========================================== */
static void rpc_get_pisys_time(args, count, call_index)
     gsi_item *args;
     gsi_int count;
     gsi_int call_index;
{
    gsi_item    *Ret_array = gsi_make_items(MAXSYSRETARGS);
    long        pitime;
    long        pi_timearray[TIMESIZE];
    char        time_str[STRSZ];

    LOGMSG(LLEVDEBUG,"rpc_get_pisys_time");

  /* zero out the array */
    memset((char *)time_str, '\0', STRSZ);

  /* initialize the return vector */
    gsi_set_int(Ret_array[CODE_POS], GSI_SUCCESS);
    gsi_set_str(Ret_array[MSG_POS], "Success");
    gsi_set_type(Ret_array[TIME_POS], STRING_TAG);
    gsi_set_type(Ret_array[PIYR_POS], INTEGER_TAG);
    gsi_set_type(Ret_array[PIMON_POS], INTEGER_TAG);
    gsi_set_type(Ret_array[PIDY_POS], INTEGER_TAG);
    gsi_set_type(Ret_array[PIHR_POS], INTEGER_TAG);
    gsi_set_type(Ret_array[PIMIN_POS], INTEGER_TAG);
    gsi_set_type(Ret_array[PISEC_POS], INTEGER_TAG);
  
    /* get the actually pi time */
    pitime = pitm_systime();

    /* convert it to individual components */
    pitm_secint(pitime, pi_timearray);

    /* now put it into MMDDYYYYhhmmss format */
    sprintf( time_str, "%02d%02d%4d%02d%02d%02d",
           pi_timearray[PI_MONTH_POS],
           pi_timearray[PI_DAY_POS],
           pi_timearray[PI_YEAR_POS],
           pi_timearray[PI_HOUR_POS],
           pi_timearray[PI_MINUTE_POS],
           pi_timearray[PI_SECOND_POS] );
    gsi_set_str(Ret_array[TIME_POS], time_str);

    gsi_set_int(Ret_array[PIYR_POS],(unsigned short)pi_timearray[PI_YEAR_POS]);
    gsi_set_int(Ret_array[PIMON_POS],(unsigned short)pi_timearray[PI_MONTH_POS]);
    gsi_set_int(Ret_array[PIDY_POS],(unsigned short)pi_timearray[PI_DAY_POS]);
    gsi_set_int(Ret_array[PIHR_POS],(unsigned short)pi_timearray[PI_HOUR_POS]);
    gsi_set_int(Ret_array[PIMIN_POS],(unsigned short)pi_timearray[PI_MINUTE_POS]);
    gsi_set_int(Ret_array[PISEC_POS],(unsigned short)pi_timearray[PI_SECOND_POS]);

    /* return the result */
    gsi_rpc_return_values(Ret_array, MAXSYSRETARGS, call_index, gsi_current_context());
    gsi_reclaim_items(Ret_array);

    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "rpc_get_pisys_time", 0) ;
    return;
}

/* 
*******************************************************************************

    function: rpc_set_debug_mode()
    args: mode

    Since debugging is now part of the logging sequence, and since, with
    rpc_log_level, it is possible to turn logging on and off, there is no
    great need for this function.  We keep it for compatibility purposes,
    only.  Setting debug on will set the log level to LLEVMOST.  Setting it
    to off will set it to LLEVNORM.

*******************************************************************************
*/
static void  rpc_set_debug_mode(args, count, call_index)
     gsi_item *args;
     gsi_int count;
     gsi_int call_index;
{
    gsi_item    *Ret_value= gsi_make_items(MAXDEBUGMODEARGS);
    gsi_int     iMode;
    gsi_int     iContext = gsi_current_context();
    CtxCfg      *systatus;

    LOGMSG(LLEVDEBUG,"rpc_set_debug_mode");
 
    systatus = (CtxCfg *)&CtxCfgs[iContext];

    gsi_set_int(Ret_value[RETCODEPOS], GSI_SUCCESS);
    gsi_set_str(Ret_value[RETMSGPOS], "Success");
  
    switch ( gsi_type_of(args[MODEPOS]) )
    {
        case INTEGER_TAG:   switch ( iMode = gsi_int_of(args[MODEPOS])/*int_of(mode)*/ )
                            {
                                case 0: systatus->log_level = LLEVNORM ;
                                        break;
                                case 1: systatus->log_level = LLEVMOST ;
                                        break;
                                default:sprintf(str_temp, "%d Invalid mode, 0->OFF, 1->ON", iMode/*int_of(mode)*/);
                                        gsi_set_int(Ret_value[RETCODEPOS], GSI_FAILURE);
                                        gsi_set_str(Ret_value[RETMSGPOS], str_temp);
                                        break;
                            }
                            break;

        case SYMBOL_TAG:    if (gleich(gsi_sym_of(args[MODEPOS]), ONSYM))
                            {
                                systatus->log_level = LLEVMOST ;
                                break;
                            }
                            if (gleich(gsi_sym_of(args[MODEPOS]), OFFSYM))
                            {
                                systatus->log_level = LLEVNORM;
                                break;
                            }
                            sprintf(str_temp, "%s is an invalid symbol.  Should be OFF or ON.", 
                                gsi_sym_of(args[MODEPOS]));
                            gsi_set_int(Ret_value[RETCODEPOS], GSI_FAILURE);
                            gsi_set_str(Ret_value[RETMSGPOS], str_temp);
                            break;

        case STRING_TAG:    if (gleich(gsi_str_of(args[MODEPOS]), ONSYM))
                            {
                                systatus->log_level = LLEVMOST ;
                                break;
                            }
                            if (gleich (gsi_str_of(args[MODEPOS]), OFFSYM))
                            {
                                systatus->log_level = LLEVNORM;
                                break;
                            }
                            sprintf(str_temp, "\"%s\" is an invalid string.  Should be \"OFF\" or \"ON\"", 
                                gsi_str_of(args[MODEPOS]));
                            gsi_set_int(Ret_value[RETCODEPOS], GSI_FAILURE);
                            gsi_set_str(Ret_value[RETMSGPOS], str_temp);
                            break;
        default:
                            gsi_set_int(Ret_value[RETCODEPOS], GSI_FAILURE);
                            gsi_set_str(Ret_value[RETMSGPOS], str_temp);
                            break;
    }
  
    gsi_rpc_return_values(Ret_value, MAXDEBUGMODEARGS, call_index, iContext);
    gsi_reclaim_items(Ret_value);
    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "rpc_set_debug_mode", 0);
    return ;

}


/* ====================================================== */
/*                                                        */
/* Retrieve a specific attribute from a specific PI point */
/*                                                        */
/* ====================================================== */
static void rpc_get_property(args, count, call_index)
     gsi_item *args;
     gsi_int count;
     gsi_int call_index;
{
    gsi_registration    reg ;
    gsi_item            *returnArray = gsi_make_items(RET_ARGS);
    gsi_int             handle ;

    GsiPiPointStruct    *pInfo ;

    char                *retMsg ;
    int                 status = NO_ERR ;
    long                attrCode ;
    long                iContext = gsi_current_context() ;



    if (count != 2) { status = 1 ; retMsg = "Incorrect number of parameters"; }

    /* Validate and process first parameter */
    /* ------------------------------------ */
    if (!status)
    {
        if (gsi_type_of(args[0]) != GSI_INTEGER_TAG)
            status = 10 ;
        else
        {
            handle = gsi_int_of(args[0]) ;
            reg = gsi_registration_of(handle, iContext) ;
            if (!reg) 
                status = 11 ;
            else
            {
               pInfo = (GsiPiPointStruct*)gsi_user_data_of(reg) ;
               if (!pInfo)
                   status = 12 ;
            }
        }
        if (status)
            retMsg = "Invalid reference to variable";
    }

    /* Test if 2nd parameter could be an attribute code */
    /* ------------------------------------------------ */
    if (!status)
        if (gsi_type_of(args[1]) != GSI_INTEGER_TAG)
        {
            status = 20 ;
            retMsg = "Invalid attribute code";
        }
        else
            attrCode = gsi_int_of(args[1]) ;

    /* Add statement to log that we have entered rpc_get_property */
    /* ---------------------------------------------------------- */
    if (status)
        LOGMSG(LLEVDEBUG, "rpc_get_property (** Error **)") ;
    else
        logMsgll(LLEVDEBUG, "=> ","rpc_get_property. PI nr %ld, attribute %ld", 
                            pInfo->pt_id, attrCode) ;

    /* Retrieve the PI attribute */
    /* ------------------------- */
    if (!status)
        status = ReadPIAttr(pInfo->pi_srv, pInfo->pt_id, attrCode, returnArray[0], -1) ;

    /* Send the results back to G2 */
    /* --------------------------- */
    if (!status)
    {
        gsi_set_int(returnArray[CODE_POS], GSI_SUCCESS);
        gsi_set_str(returnArray[MSG_POS],"Success"); 
    }
    else
    {
        gsi_set_type(returnArray[0], GSI_NULL_TAG) ;
        gsi_set_int(returnArray[CODE_POS], status);
        gsi_set_str(returnArray[MSG_POS], retMsg); 
    }

    gsi_rpc_return_values(returnArray, RET_ARGS, call_index, iContext);
    gsi_reclaim_items(returnArray);

    logMsg(LLEVMOST, "<= ",FALSE, -1, 0, "rpc_get_property", 0) ;
}


/* ======================================================= */
/*                                                         */
/* Shutdown this bridge once all contexts are disconnected */
/*                                                         */
/* ======================================================= */
static void rpc_shutdown(args, count, call_index)
     gsi_item *args;
     gsi_int count;
     gsi_int call_index;
{
    gsi_item            *returnArray = gsi_make_items(RET_ARGS);
    gsi_item            torf ;
    gsi_int             iContext = gsi_current_context() ;

    char                *retMsg ;
    short               fDown = TRUE ;
    short               status = 0 ;


    /* Make sure that we have a maximum of one parameter */
    /* ------------------------------------------------- */
    if (count > 1)
    {
        status = 1 ;
        retMsg = "shutdown RPC takes 0 or 1 parameters" ;
    }

    /* If a parameter is given, it must be a truth-value */
    /* indicating whether or not we should shut down.    */
    /* ------------------------------------------------- */
    if (count == 1)
    {
        torf = args[0] ;
        if (gsi_type_of(torf) != GSI_LOGICAL_TAG)
        {
            status = 2 ;
            retMsg = "If parameter is given to shutdown, it must be a truth-value" ;
        }
        else
            fDown = (gsi_log_of(torf) == GSI_TRUE) ? TRUE : FALSE ;
    }
    if (!status) 
        LOGMSG(LLEVDEBUG, fDown?"Shutdown requested":"Abort of shutdown requested") ;
    else
    {
        LOGMSG(LLEVDEBUG, "rpc_shutdown") ;
        LOGMSG(LLEVHIGH, retMsg);
    }        

    /* Since this function must be called across a context, we know that  */
    /* at least one context is active.  The actual shutdown will occur in */
    /* gsi_shutdown_context.  Set or clear the flag that tells it that we */
    /* want to stop the bridge.                                           */
    /* ------------------------------------------------------------------ */
    if (!status)
        gShuttingDown = fDown ;

    /* Tell G2 how it went */
    /* ------------------- */
    if (!status)
    {
        gsi_set_int(returnArray[CODE_POS], GSI_SUCCESS);
        gsi_set_str(returnArray[MSG_POS],"Success"); 
    }
    else
    {
        gsi_set_type(returnArray[0], GSI_NULL_TAG) ;
        gsi_set_int(returnArray[CODE_POS], status);
        gsi_set_str(returnArray[MSG_POS], retMsg); 
    }
    if (call_index) gsi_rpc_return_values(returnArray, RET_ARGS, call_index, iContext);

    /* Give back the memory we used */
    /* ---------------------------- */
    gsi_reclaim_items(returnArray);

    logMsg(LLEVMOST, "<= ",FALSE, -1, 0, "rpc_shutdown", 0) ;
}


/* ====================================================================== */
/*                                                                        */
/*   Update a list of variables.  The arguments to this function are the  */
/*   handles of the variables to update.                                  */
/*                                                                        */
/* ====================================================================== */
static void rpc_read(args, count, call_index)
     gsi_item *args;
     gsi_int count;
     gsi_int call_index;
{
    int                 status ;

    gsi_registration    *pReg ;
    gsi_registered_item *pG2Var = gsi_make_registered_items(1) ;
    gsi_int             i, hndl ;
    gsi_int             iContext = gsi_current_context() ;

    CtxCfg              *pCtxState = (CtxCfg *)&CtxCfgs[iContext];
    GsiPiPointStruct    *pInfo;
    PI_EVENT            snX, *pSnap= &snX ;

    LOGMSG(LLEVDEBUG,"rpc_read") ;
    for (i=0 ; i < count ; i++)
    {
        // pi_ptr = gsi_user_data_of(gsi_registration_of(gsi_handle_of(args+i), iContext));

        /* Validate input */
        /* -------------- */
        if (gsi_type_of(args[i]) != GSI_HANDLE_TAG)
        {
            logMsg(LLEVHIGH,"** ",FALSE, -1, 0,"Not a handle.", i) ;
            continue ;
        }
        hndl = gsi_handle_of(args[i]) ;
        pReg = gsi_registration_of(hndl, iContext) ;
        if (!pReg)
        {
            logMsgll(LLEVHIGH,"** ","Variable with handle %ld not found for context %ld.", 
                hndl, iContext) ;
            continue ;
        }
        gsi_set_handle(*pG2Var, hndl) ;

        pInfo = (GsiPiPointStruct *)gsi_user_data_of(pReg);
        if (pInfo == 0)
        {
            logMsgll(LLEVHIGH,"** ", 
                "PI/variable information for handle %ld, context %ld, not found",
                hndl, iContext) ;
            continue ;
        }

        /* Read the current PI value */
        /* ------------------------- */
        pSnap->bval = PIText ;
        pSnap->bsize = STRSZ-1 ;
        status = ReadPIVal(pInfo, pSnap) ;
        pSnap->bval = PIText ;
        if (status == NO_ERR)
        {    
            /* Prepare to send the value to G2 */
            /* ------------------------------- */
            PIValToVar(pInfo, pSnap, pG2Var) ;

            /* Send it to G2 */
            /* ------------- */
            if (pCtxState->do_timestamp)
                gsi_return_timed_attrs(*pG2Var, &gAttr[LRPT_POS], 3, iContext);
            else
                gsi_return_attrs(*pG2Var, &gAttr[LRPT_POS], 3, iContext) ;
        }
    } /* end of the for loop */

    gsi_reclaim_items(pG2Var) ;
    logMsg(LLEVMOST, "<= ",FALSE, -1, 0, "rpc_read", 0) ;

}


struct statlup {    long    code ;
                    char    *desc ; } lup[] = { {      0, "Good" }, 
                                                {      1, "Low Limited" },
                                                {      2, "High Limited" },
                                                {      3, "Constant" },
                                                {     64, "Uncertain, non-specific" },
                                                {     68, "Uncertain, last usuable value" },
                                                {     80, "Uncertain, sensor not accurate" },
                                                {     84, "Uncertain, engineering units exceeded" },
                                                {     88, "Uncertain, sub-normal"},
                                                {    128, "Bad, non-specific" },
                                                {    132, "Bad, configuration error" },
                                                {    136, "Bad, not connected" },
                                                {    140, "Bad, device failure" },
                                                {    144, "Bad, sensor failure" },
                                                {    148, "Bad, last known value" },
                                                {    152, "Bad, comm failure" },
                                                {    156, "Bad, out of service" }, 
                                                {  16389, "General failure" },
                                                { 262147, "Bad value" }, 
                                                { 262148, "Bad type, conversion not supported" },
                                                { 262150, "Not Defined" },
                                                { 262151, "Unknown item ID" },
                                                { 262152, "Invalid item ID" } } ;

#define NR_STATS sizeof(lup)/sizeof(struct statlup)


static void rpc_trans_stat(args, count, call_index)
     gsi_item *args;
     gsi_int count;
     gsi_int call_index ;
{
    char                *msgBack ;
    int                 stat = 0, i ;
    long                vStat ;
    
    gsi_registration    *pReg ;
    gsi_item            *pBack = gsi_make_items(1) ;
    gsi_int             hndl, iContext=gsi_current_context() ;

    GsiPiPointStruct    *pInfo;

    /* Validate input */
    /* -------------- */
    if (count != 1)
    {
        stat = -1 ;
        msgBack = "translate-status requires exactly one parameter" ;
    }
    else if (gsi_type_of(args[0]) != GSI_HANDLE_TAG)
    {
        stat = -2 ;
        msgBack = "the parameter to translate-status must be the handle of a variable";
    }
    else
    {
        hndl = gsi_handle_of(args[0]) ;
        if (!hndl)
        {
            stat = -3 ;
            msgBack = "no such variable" ;
        }
    }
    if (!stat)
    {
        pReg = gsi_registration_of(hndl, iContext) ;
        if (!pReg)
        {
            stat = -4 ;
            msgBack = "Variable not found" ;
        }
    }

    /* Get the pointer to the structure in which we have stored the status */
    /* ------------------------------------------------------------------- */
    if (!stat)
    {
        pInfo = (GsiPiPointStruct *)gsi_user_data_of(pReg);
        if (pInfo == 0)
        {
            stat = -5 ;
            msgBack = "PI/variable information not found";
        }
    }

    /* Get the status and look it up */
    /* ----------------------------- */
    if (!stat)
    {
        vStat = pInfo->status ;
    
        for (i = 0 ; i < NR_STATS ; i++)
            if (lup[i].code == vStat)
                break ;

    /* Prepare to send back the translation */
    /* ------------------------------------ */
        if (i < NR_STATS)
            gsi_set_str(*pBack, lup[i].desc) ;
        else
        {
            sprintf(PIText, "** Unknown status (%ld)", vStat) ;
            logMsg(LLEVHIGH, "", FALSE, -1, 0, PIText, 0) ;
            gsi_set_str(*pBack, PIText) ;
        }
    }
    else
    {
        sprintf(PIText, "** Error in call to translate-status: %s", msgBack) ;
        gsi_set_str(*pBack, PIText) ;
        logMsg(LLEVHIGH, "", FALSE, -1, 0, PIText, stat) ;
    }

    gsi_rpc_return_values(pBack, 1, call_index, iContext);
    gsi_reclaim_items(pBack);

}

/* ######################################################################### */



/* 
*******************************************************************************

   Function: get_time_values()
   args: object, start, finish, delta

   This function is called by the user to get a block of requests from PI.  
   This function returns a series of gsi_return_attrs () or 
   gsi_return_timed_attrs() calls based on the initial setting.

*******************************************************************************
*/
int pi_get_timed_values(args, count, arcmode, call_index)
     gsi_item       *args;
     gsi_int        count;
     unsigned short arcmode;
     gsi_int        call_index;
{
    char                timestring[PITIMELEN+1];
    char                digstate[CHARSPERDIGSTATE+1];
    char                bval[STRSZ] = "" ;
    CtxCfg              *systatus;
    double              drval ;
    float               time_flt;
    gsi_attr            *v_ptr;
    gsi_int             iContext = gsi_current_context();
    gsi_item            object, from, to, number;
    gsi_item            *code, *msg, *ptrRet_vector = gsi_make_items(RET_ARGS);
    gsi_registered_item ret_timearg, *ptrRet_timearg= gsi_make_registered_items(1);
    int                 srvNr ;
    int                 status;
    long                pi_from, pi_to, pi_count, successCt=0 ;
    long                pi_point;
    long                pi_timearray[TIMESIZE];
    long                temp_timearray[TIMESIZE];
    long                historyType ;
    long                ival, bsize, istat, lX ;
    PIAPI_STRUCT        api_err;
    PITIMESTAMP         time0, time1;
    register int        i;
    short               flags ;
    unsigned short      type;
    
    
    /* ------------------------------------------------------ */
    /*                                                        */
    /* VALIDATE THE INPUT AND PREPARE TO RETRIEVE THE HISTORY */
    /*                                                        */
    /* ------------------------------------------------------ */
    ret_timearg = *ptrRet_timearg;
    /* Get The System status structure */
    systatus = (CtxCfg *)&CtxCfgs[iContext];
    
    /* set up the return values */
    /* ------------------------ */
    set_int(ptrRet_vector[CODE_POS], GSI_SUCCESS);
    set_str(ptrRet_vector[MSG_POS], "Success");
    code = &ptrRet_vector[CODE_POS];
    msg = &ptrRet_vector[MSG_POS];
    
    /* get the elements */
    /* ---------------- */
    object = args[OBJECT_POS];
    ival = gsi_type_of(object) ;
    if (ival == GSI_INTEGER_TAG)
        ival = gsi_int_of(object) ;
    status = check_object(&object, &type, &srvNr, &pi_point);
    
    /* Report the problem if the object is invalid */
    /* ------------------------------------------- */
    if (status != GSI_SUCCESS)
    {
        set_int(ptrRet_vector[CODE_POS], INVALID_OBJECT);
        set_str(ptrRet_vector[MSG_POS], "Invalid object index - check type and value"); 
        gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
        gsi_reclaim_registered_items (ptrRet_timearg);
        gsi_reclaim_items(ptrRet_vector);
        return (GSI_SUCCESS); 
    }
    
    /* get the start and end times */
    from = args[FROM_POS];
    to = args[TO_POS];
    
    /* Validate the requested number of values.  Report any problems. */
    /* -------------------------------------------------------------- */
    number =  args[NUMBER_POS];
    if ((type_of(number) != INTEGER_TAG) || (int_of(number) >= MAXARCTIMEVALS))
    {
        set_int(ptrRet_vector[CODE_POS], INVALID_ARGUMENT);
        sprintf(str_temp,"Invalid number of points, must be integer and < %d",MAXARCTIMEVALS); 
        set_str(ptrRet_vector[MSG_POS], str_temp);
        gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
        gsi_reclaim_registered_items (ptrRet_timearg);
        gsi_reclaim_items(ptrRet_vector);
        return (GSI_SUCCESS); 
    }
    
    pi_count = int_of(number);
    
    /* get the vector that will be used to return data */
    v_ptr = piHistoryAttr;
    
    /* initialize the return structure */
    gsi_set_handle(ret_timearg, int_of(object));
    set_status(ret_timearg, NO_ERR);
    
    /* convert the times to a usable format */
    conv_rpc2pi_time(&from,&pi_from);
    if (pi_from == BAD_PI_TIME)
    {
         set_int(ptrRet_vector[CODE_POS], INVALID_TIME);
         sprintf(str_temp, "%s is an invalid time to start from",str_of(from)); 
         gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
         return (GSI_SUCCESS); 
    }
    conv_rpc2pi_time(&to,&pi_to);
    if (pi_to == BAD_PI_TIME)
    {
         set_int(ptrRet_vector[CODE_POS], INVALID_TIME);
         sprintf(str_temp, "%s is an invalid time to finish at",str_of(to)); 
         set_str(ptrRet_vector[MSG_POS], str_temp);
         gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
         return (GSI_SUCCESS); 
    }
    
    pitm_setpitime(&time0, pi_from, 0.0) ;
    pitm_setpitime(&time1, pi_to, 0.0) ;
    
    pistatus =switchToServer(srvNr) ;
    if (pistatus != NO_PI_ERROR)
    {
        set_int(ptrRet_vector[CODE_POS], PIAPI_ERROR);
        sprintf(str_temp,"Unable to switch to server # %d.  Error code: %ld",srvNr, pistatus); 
        set_str(ptrRet_vector[MSG_POS], str_temp);
        gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
        gsi_reclaim_registered_items (ptrRet_timearg);
        gsi_reclaim_items(ptrRet_vector);
        return (GSI_SUCCESS); 
    }
    
    
    /* ----------------------------------------------------------------------- */
    /*                                                                         */
    /*   REQUEST THE HISTORY.  THEN LOOP THROUGH THE RETURNED VALUES, PACK     */
    /*   THEM AND THE CORRESPONDING TIMESTAMPS INTO THE ARRAY OF gsi_attrS     */
    /*   POINTED TO BY piHistoryAttr, AND SEND THEM BACK TO THE SOURCE OBJECT. */
    /*                                                                         */
    /* ----------------------------------------------------------------------- */
    switch (arcmode)
    {
        case ARCINTERP_MODE:    historyType = ARCflag_even ;
                                break;
        case ARCSEQU_MODE:      historyType = ARCflag_comp ;
                                break;
        default:
            set_int(ptrRet_vector[CODE_POS], INVALID_ARGUMENT);
            sprintf(str_temp, "mode not supported( %d )for point %d",arcmode,pi_point); 
            set_str(ptrRet_vector[MSG_POS], str_temp);
            gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
            gsi_reclaim_registered_items (ptrRet_timearg);
            gsi_reclaim_items(ptrRet_vector);
            return (GSI_SUCCESS); 
    }
    
    /* If a debug report was requested, print the heading here */
    /* ------------------------------------------------------- */
    if (systatus->log_level >= 9 ) 
    {
        LOGMSG(LLEVDEBUG,"rpc_get_timed_values\n");
        if ( pi_count > 0 ) 
        {
            printf("\n<< History for point: %d   Num values: %d>>\n", pi_point, pi_count);
            /* convert the PI start time to an array of ints */
            pitm_secint( pi_from, temp_timearray );       
            printf( "<< Start: %02d/%02d/%04d %02d:%02d:%02d  ",
                     temp_timearray[PI_MONTH_POS],
                     temp_timearray[PI_DAY_POS],
                     temp_timearray[PI_YEAR_POS],
                     temp_timearray[PI_HOUR_POS],
                     temp_timearray[PI_MINUTE_POS],
                     temp_timearray[PI_SECOND_POS] );
    
            /* convert the PI end time to an array of ints */
            pitm_secint( pi_to, temp_timearray );
            printf( "End: %02d/%02d/%04d %02d:%02d:%02d >>\n",
                     temp_timearray[PI_MONTH_POS],
                     temp_timearray[PI_DAY_POS],
                     temp_timearray[PI_YEAR_POS],
                     temp_timearray[PI_HOUR_POS],
                     temp_timearray[PI_MINUTE_POS],
                     temp_timearray[PI_SECOND_POS] );
        }
    }


    /* This is where we request the history */
    /* ------------------------------------ */
    bsize = STRSZ-1 ;
    i = 1 ;
    pistatus = piar_getarcvaluesfilterx(pi_point, historyType, &pi_count, &drval, &ival,
                                    bval, &bsize, &istat, &flags, &time0, &time1, NULL, GETFIRST) ;
    while (pistatus != 100)
    {
        if (pistatus == -15010) // truncated
            LOGMSG(LLEVHIGH, "Text of string retrieved from history TRUNCATED") ;
        else if (pistatus < NO_PI_ERROR)
        {
            set_int(ptrRet_vector[CODE_POS], PIAPI_ERROR);
            sprintf(str_temp,"archive value request error %d for point %d",pistatus,pi_point); 
            set_str(ptrRet_vector[MSG_POS], str_temp);
            gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
            gsi_reclaim_registered_items (ptrRet_timearg);
            gsi_reclaim_items(ptrRet_vector);
#ifdef DEBUG
            printf("***** pi_get_timed_values: type = '%c'\n",type);
#endif
            return (GSI_SUCCESS); 
        }

        /* normallize the timestamp */
        /* build_timestamp (time_ptr, time_of(&ret_timearg));*/
        lX = pitm_getpitime(&time1, NULL) ;
        build_timestamp_gsi5 (&lX, ret_timearg, timestring);
        
        /* get the vector that will be used to return data */
        v_ptr = piHistoryAttr;
        
        switch (type)
        {
            case pipFlt:
                        /* Debug report */
                        /* ------------ */
                        sprintf(PIText, " [%4d] %s R: %10.3f  I: %d", i, timeToStr(&time1), drval, istat) ;
                        LOGMSG(LLEVDEBUG, PIText) ;
                        
                        /* check the istat */
                        /* --------------- */
                        if (istat < 0)
                        {
                            set_status(ret_timearg, DIG_STAT_ERROR + abs((int) istat));
                            set_type(ret_timearg, FLOAT64_TAG);
                            gsi_return_values(&ret_timearg, 1, iContext);
                            goto nextVal ;
                        }

                        /* update the structure */
                        /* -------------------- */
                        set_flt(ret_timearg, drval);
                        set_type(ret_timearg, FLOAT64_TAG);
                        set_flt(*v_ptr, drval); 
                        set_type(*v_ptr, FLOAT64_TAG);
                        break;

            case pipInt:
            case pipTim:
                        /* Debug report */
                        /* ------------ */
                        sprintf(PIText, " [%4d] %s V: %10d  istat: %d", i, timeToStr(&time1), ival , istat) ;
                        LOGMSG(LLEVDEBUG, PIText) ;
                        
                        /* check the istat */
                        /* --------------- */
                        if (istat < 0)
                        {
                            set_status(ret_timearg, DIG_STAT_ERROR + abs((int) istat));
                            set_type(ret_timearg, GSI_INTEGER_TAG);
                            gsi_return_values(&ret_timearg, 1, iContext);
                            goto nextVal;
                        }
                        
                        /* update the structure */
                        set_int(ret_timearg, ival);
                        set_int(*v_ptr, ival); 
                        break;

            case pipDig:
                        sprintf(PIText, " [%4d] %s istat: %ld : ", i, timeToStr(&time1), istat) ;

                        /* Translate the code */
                        /* ------------------ */
                        pistatus = pipt_digstate ( istat, digstate, CHARSPERDIGSTATE );

                        /* Report the result, if requested */
                        /* ------------------------------- */
                        if (pistatus == NO_PI_ERROR)
                            strcat(PIText, digstate) ;
                        else
                            strcat(PIText, "?") ;
                        strcat(PIText, "\n") ;
                        LOGMSG(LLEVDEBUG, PIText) ;

                        if (pistatus < 0 )
                        {
                            /* Call the PIAPI error handler */
                            strcpy( api_err.funct_name, "PIPT_DIGSTATE" );
                            api_err.pi_status = pistatus;
                            api_err.pi_point = pi_point;
                            api_err.object_ind = int_of(object);
                            sprintf (api_err.arguments, "<dig code = %ld>", istat );
                            piapi_error( &api_err );
                        }

                        if ( pistatus != NO_PI_ERROR )
                        {
                            logMsg(LLEVHIGH, "** code", FALSE, -1, istat,
                              "Retrieval of digital state string while reading history failed",pistatus) ;
                            goto nextVal;
                        }

                        set_str(ret_timearg, digstate);
                        set_str(*v_ptr, digstate); 
                        break;

            case pipTxt:
                        /* Debug report */
                        /* ------------ */
                        if (pistatus == -15010)
                            bval[STRSZ-1] = '\0';
                        else
                            bval[bsize] = '\0' ;
                        sprintf(PIText, " [%4d] %s istat: %4d  T:\"%s\"", i, timeToStr(&time1), istat, bval) ;
                        LOGMSG(LLEVDEBUG, PIText) ;
                        
                        /* check the istat */
                        /* --------------- */
                        if (istat < 0)
                        {
                            set_status(ret_timearg, DIG_STAT_ERROR + abs((int) istat));
                            set_type(ret_timearg, GSI_INTEGER_TAG);
                            gsi_return_values(&ret_timearg, 1, iContext);
                            goto nextVal ;
                        }

                        /* update the structure */
                        set_str(ret_timearg, bval);
                        set_str(*v_ptr, bval); 
                        break;
                        

            default:    logMsg(LLEVHIGH,"** ",FALSE, srvNr, pi_point, "Invalid PI type", type);
                        goto nextVal ;
        }

        /* the next vector argument is the time also, but it will not be for a list 
           and it will have a timestamp.  We will add the timestamp later when we
           fix the timestamp vector operation in g2. */

        /* send the time as a float */
        v_ptr++;
        time_flt = (float)lX ;
        set_flt(*v_ptr, time_flt); 
        set_type(*v_ptr, FLOAT64_TAG); 

        /* next fill the vector with the time after you */
        /* convert the time to a string */
        v_ptr++;
        set_type(*v_ptr, STRING_TAG);

        /* convert from PI time stamp to an integer array */
        pitm_secint(lX, pi_timearray );

        /* now put it into MMDDYYYYhhmmss format */
        sprintf( timestring,"%02d%02d%4d%02d%02d%02d",
             pi_timearray[PI_MONTH_POS],
             pi_timearray[PI_DAY_POS],
             pi_timearray[PI_YEAR_POS],
             pi_timearray[PI_HOUR_POS],
             pi_timearray[PI_MINUTE_POS],
             pi_timearray[PI_SECOND_POS] );

        set_str(*v_ptr, timestring);
   
        /* return the data as a vector, convert to a tvector later */
        gsi_return_timed_attrs(ret_timearg, piHistoryAttr, TV_SIZE, iContext); 

        successCt++ ;

        /* Read the next point.  A return code of 100 means we are done. */
        /* --------------------------------------------------------------*/
nextVal:
        bsize = STRSZ-1 ;
        i++ ;
        pistatus = piar_getarcvaluesfilterx(pi_point, historyType, &pi_count, &drval, &ival,
                                    bval, &bsize, &istat, &flags, &time0, &time1, NULL, GETNEXT) ;

    }  /* end of while loop */


    /* ----------------------------------------------- */
    /*                                                 */
    /*      REPORT THE SUCCESS OF THIS CALL TO G2      */
    /*                                                 */
    /* ----------------------------------------------- */
    set_int(ptrRet_vector[CODE_POS], GSI_SUCCESS);
    sprintf(str_temp,
                "Block request complete for Pi point %d. %d values retrieved.",
                pi_point,successCt); 
    set_str(ptrRet_vector[MSG_POS], str_temp);
    gsi_rpc_return_values(ptrRet_vector, RET_ARGS, call_index, iContext); 
    gsi_reclaim_registered_items (ptrRet_timearg);
    gsi_reclaim_items(ptrRet_vector);
    return (GSI_SUCCESS); 

}


/* ======================================================================= */
/*                                                                         */
/* We can monitor up to MAXEVMPOINTS points by exception for each context. */
/* However we keep track of how many points are being monitored for each   */
/* PI server being called from a context.  At times we need to know how    */
/* many total points are being monitored for a context.  This function     */
/* calculates the sum.                                                     */
/*                                                                         */
/* setNr is the number of the set of exception report tables being used to */
/* track information for this context. setNr = ContextToERTabNr(iContext). */
/*                                                                         */
/* ======================================================================= */
int exPtCount(long iContext)
{
    int     i ;
    int     total = 0 ;

    for (i=iContext * gNrServers ; i < (iContext + 1) * gNrServers ; i++)
        total += pNrPIPts[i] ;

    return total ;
}

/*
*******************************************************************************
      
    Function: GetMatchIndex()
    args; point, index, obj_index
    
    See if there is an entry for the specified point number in the
    exInfo table.  If so, return a pointer to it.
    
*******************************************************************************
*/
int GetMatchIndex (srvNr, point, ppInfo)
     int     srvNr ;
     long    point;
     exInfo  **ppInfo ;
{
    exInfo          *pInfo=pExRptInfo ;

    while (pInfo != NULL && (pInfo->piSrv < srvNr || (pInfo->piSrv == srvNr &&
            pInfo->piPt < point)))
        pInfo = pInfo->nextPI ;
    if (pInfo == NULL) return FALSE ;
    *ppInfo = pInfo ;
    return (pInfo->piSrv == srvNr && pInfo->piPt == point) ;
}
 

/* ========================================================================= */
/*                                                                           */
/* We are deregistering a variable that was being updated by exception.  As  */
/* a result need to remove its exInfo structure from the structure pointed   */
/* to by pExRptInfo.                                                         */
/*                                                                           */
/* This is moderately complex due to the structure of ExRptInfo.  First we   */
/* need to find the exInfo.  Then we are faced with one of 3 situations:     */
/* 1. The structure is in ExRptInfo and does not have other exInfos linked   */
/*    to it.                                                                 */
/* 2. The structure is in ExRptInfo and does have other exInfos linked to it.*/
/* 3. The structure is in a chain linked to ExRptInfo.                       */
/*                                                                           */
/* ========================================================================= */
void removeExRptInfoFor(pi_ptr)
GsiPiPointStruct    *pi_ptr ;
{
    long    piPtNr = pi_ptr->pt_id ;
    int     piSrvNr = pi_ptr->pi_srv ;
    long    piStat, nr=1 ;
    gsi_int varHandle = pi_ptr->g2_handle ;
    exInfo  *pInfo, **ppWas ;

    pInfo = pExRptInfo ;
    ppWas = &pExRptInfo ;

    while (pInfo != NULL)
        if (pInfo->piPt == piPtNr && pInfo->piSrv == piSrvNr)
            break ;
        else
        {
            ppWas = &(pInfo->nextPI) ;
            pInfo = pInfo->nextPI ;
        }
    if (pInfo == NULL) return ;


    /* We found the point.  Now look for the handle */
    /* -------------------------------------------- */
    if (pInfo->varHandle == varHandle)
    {

        /* Case 1 ? */
        /* -------- */
        if (pInfo->nextVar == NULL)
        {
            /* Yes: disable collection, remove this exInfo from chain,       */
            /* release its memory, decrement # of points and # of variables. */
            /* ------------------------------------------------------------- */
            switchToServer(piSrvNr) ;
            piStat = pisn_evmdisestablish(&nr, &piPtNr) ;
            if (piStat)
                logMsg(LLEVHIGH, "** ", FALSE, piSrvNr, piPtNr, "Disabling exception reporting failed", piStat) ;
            *ppWas = pInfo->nextPI ;
            --pNrPIPts[pInfo->piSrv] ;
        }

        /* Case 2: There are other variables being updated from the same PI  */
        /*         point.  This exInfo's predecessor in the PI chain should  */
        /*         now point to this exInfo's successor in the G2 variable   */
        /*         chain.  Make its PI successor this exInfo's PI successor. */
        /* ----------------------------------------------------------------- */
        else
        {
            *ppWas = pInfo->nextVar ;
            pInfo->nextVar->nextPI = pInfo->nextPI ;
        }

        free(pInfo) ;
        NrG2Vars--; 
    }
                
    /* We found an exInfo for the correct point but not the G2       */
    /* variable.  Search along the 2nd level linked list for the     */
    /* desired exInfo structure.                                     */
    /* ------------------------------------------------------------- */
    else
    {
        ppWas = &(pInfo->nextVar) ;
        pInfo = pInfo->nextVar ;
        while (pInfo != NULL)
        {
            if (varHandle == pInfo->varHandle) 
                break ;
            ppWas = &(pInfo->nextVar) ;
            pInfo = pInfo->nextVar ;
        }

        /* We found it.  This is case 3.  Remove the exInfo pointed  */
        /* to by pTemp from the chain, free its memory, and subtract */
        /* 1 from the number of variables being processed by         */
        /* exception reporting for this context.                     */
        /* --------------------------------------------------------- */
        if (pInfo != NULL)
        {
            *ppWas = pInfo->nextVar ;
            free(pInfo) ;
            NrG2Vars-- ;
        }
    }

}


/* ============================================================================ */
/*                                                                              */
/* Exception reporting has retrieved the values for some PI points and put them */
/* in some arrays.  This function retrieves the values and sends them to G2     */
/*                                                                              */
/*  args: pSnap points to the values that were retrieved from PI                */
/*        index tells us where in ExRptInfo we can find needed info about the   */
/*              point and variable.                                             */
/*                                                                              */
/* ============================================================================ */
int SendData (pSnap, pInfo)
     PI_EVENT   *pSnap ;
     exInfo     *pInfo ;
{
    gsi_int             iContext = gsi_current_context(), 
                        nContext, stat ;
    CtxCfg              *pCtxState = &CtxCfgs[iContext] ;
    gsi_registered_item *pRegItem = gsi_make_registered_items(1), RegItem = *pRegItem ;
    long                istat=0,timedate=0;
    static char         digstate[CHARSPERDIGSTATE+1];
    GsiPiPointStruct    gpsX ;


    /* Display a message if debugging is enabled */
    /* ----------------------------------------- */
    LOGMSG(LLEVDEBUG,"SendData");

    /* Prepare the LAST-RECORDED-PI-TIME attribute */
    /* ------------------------------------------- */
    sprintf(str_temp, "%02d%02d%04d%02d%02d%02d", pSnap->timestamp.month,
        pSnap->timestamp.day, pSnap->timestamp.year, pSnap->timestamp.hour,
        pSnap->timestamp.minute, (long)pSnap->timestamp.second) ;
    gsi_set_str(gAttr[LRPT_POS], str_temp) ;

    /* Send retrieved values to each variable attached to same point */
    /* ------------------------------------------------------------- */
    while (pInfo)
    {

        /* Create a gsi_registered_item that we will use to return */
        /* the values to G2.                                       */
        /* ------------------------------------------------------- */
        gsi_set_handle(RegItem, pInfo->varHandle);
        if (pInfo->varType != GSI_SYMBOL_TAG)
            gsi_set_type(RegItem, pInfo->varType) ;
        set_status(RegItem, NO_ERR);

        /* Copy the values from the PI storage area to the gsi_registered_item, */
        /* performing any needed type conversion.                               */
        /* -------------------------------------------------------------------- */
        gpsX.pt_id     = pInfo->piPt ;
        gpsX.pi_type   = pInfo->piType ;
        gpsX.g2_type   = pInfo->varType ;
        gpsX.g2_handle = pInfo->varHandle ;
        PIValToVar(&gpsX, pSnap, &RegItem) ;


        /* This is where the value is sent to G2. */
        /* -------------------------------------- */
        stat = gsi_status_of(RegItem) ;
        nContext = pInfo->varContext ;
        if (pCtxState->do_timestamp)
            gsi_return_timed_attrs(RegItem, &gAttr[LRPT_POS], 3, nContext);
        else
            gsi_return_attrs(RegItem, &gAttr[LRPT_POS], 3, nContext) ;

        /* Prepare to process next variable */
        /* -------------------------------- */
        pInfo = pInfo->nextVar ;
    }

    LOGMSG(LLEVMOST,"=Leaving SendData");

    /* Avoid a memory leak */
    /* ------------------- */
    gsi_reclaim_registered_items(pRegItem);
    return(GSI_SUCCESS);
}

  
/*
*******************************************************************************

   function: UpdateEventList()
   args: GsiPiPointStruct*  - information about PI point and variable
         int* - flag indicate whether or not we need to tell PI to monitor
                this point (we may have already told it)

  For each variable we register in a context that is using exception reporting,
  we fill in an exInfo structure that contains information we will need when PI 
  sends us a new value for the related point.  However it is possible that more 
  than one G2 variable will get its value from the same PI point.  (This is 
  especially true since this program will, when possible, reformat the value it 
  receives from PI to match the G2 variable type.)
  
  pExRptInfo is pointer to an exinfo for the first variable being monitored by
  exception.  Each exInfo can point to 2 other exInfos: one for a different PI 
  point and one for the same PI point but a different G2 variable.  We get 
  something like this:

     pExRptInfo --> exInfo(PI=2,G2=3) -> exInfo(PI=2,G2=7) -> x
                            V
                    exInfo(PI=5,G2=2) -> exInfo(PI=5,G2=4) -> exInfo(PI=5,G2=1) ->x
                            V
                    exInfo(PI=8,G2=5) ->x
                            V
                            x

*******************************************************************************
*/
int UpdateEventList(GsiPiPointStruct *pi_ptr, int *pTellPI)
{
    exInfo  *pNew, *p1, **pp2 ;
    gsi_int iContext = gsi_current_context();
    int     less ; 
    int     piSrvNr = pi_ptr->pi_srv ;
    long    piPtNr = pi_ptr->pt_id ;
    

    /* Allocate and fill in an exInfo for this G2 variable */
    /* --------------------------------------------------- */
    pNew = (exInfo*)malloc(sizeof(exInfo)) ;
    if (pNew == NULL)
    {
        logMsg(LLEVHIGH, "** ", FALSE, piSrvNr, piPtNr, "Out of memory, cannot update this G2 variable with exception reporting", 0) ;
        return GSI_FAILURE ;
    }
    NrG2Vars++ ;
    pNew->piPt = pi_ptr->pt_id ;
    pNew->piSrv = pi_ptr->pi_srv ;
    pNew->piType = pi_ptr->pi_type ;
    pNew->varContext = iContext ;
    pNew->varHandle = pi_ptr->g2_handle ;
    pNew->varType = pi_ptr->g2_type ;
    pNew->nextPI = NULL ;
    pNew->nextVar = NULL ;


    /* If this is the first exInfo for this context, point to it from */
    /* pExRptInfo, and tell PI to monitor its source point.           */
    /* -------------------------------------------------------------- */
    if (pExRptInfo == NULL)
    {
        pExRptInfo = pNew ;
        pNrPIPts[piSrvNr]++ ;
        *pTellPI = TRUE ;
        return GSI_SUCCESS ;
    }

    /* Look for another exInfo with the same PI point */
    /* ---------------------------------------------- */
    p1  = pExRptInfo ;
    pp2 = &pExRptInfo ;
    while ( (less= (p1->piSrv < piSrvNr || (p1->piSrv==piSrvNr && p1->piPt<piPtNr)))
                 && p1->nextPI != NULL)
    {
        pp2 = &(p1->nextPI) ;
        p1  = p1->nextPI ;
    }

    /* If we found one, add this exInfo to the 2nd level linked list */
    /* ------------------------------------------------------------- */
    if (p1->piSrv==piSrvNr && p1->piPt==piPtNr)
    {
        pNew->nextVar = p1->nextVar ;
        p1->nextVar = pNew ;
        *pTellPI = FALSE ;
        return GSI_SUCCESS ;
    }

    /* This is for a new PI point. */
    /* ----------------------------*/
    pNrPIPts[piSrvNr]++ ;
    *pTellPI = TRUE ;

    /* If less is true, then we came to the end of the list.  Add the */
    /* exInfo at the end of the list                                  */
    /* -------------------------------------------------------------- */
    if (less)
    {
        p1->nextPI = pNew ;
    }

    /* The new exInfo should come before p1.  Insert it. */
    /* ------------------------------------------------- */
    else
    {
        pNew->nextPI = p1 ;
        *pp2 = pNew ;
    }
    return GSI_SUCCESS ;
}

void gsi_error_handler(gsi_int context, gsi_int code, gsi_char *msg)
{
    if (deReging)
        if (code == 85)
            CtxCfgs[context].alive = false ;
        else
            printf("** GSI error %ld context %ld: %s\n", code, context, msg) ;
}
