/* *************************************************************

   File: gsi_utils.c

   This file contains the code for a number of different 
   utility routines. 

   ****************************************************************/

#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#ifdef ON_VMS 
#include <file.h>
#endif

#ifdef WIN32
#include <winsock2.h>
#endif

#include <time.h>
#include "pilogex.h"
#include "gsi_pi_utils.h"
#include "gsi_main.h"
#include "log.h"
#include "osipi.h"
#include "osipi_bridge.h"
#include "piapi.h"
#include "piapix.h"

extern function_handle_type     ErrorHandle[];
extern gsi_attr                 *gAttr ;
extern CtxCfg                   CtxCfgs[] ;

/********************************************************************************

   function: badvalue_handler()
   args: code, index

   This function is called to send and error code back to a variable. The 
   purpose of invoking this function is to let G2 have the ability to keep 
   requesting if necessary and to let the user know what is going on.

*******************************************************************************
*/
void badvalue_handler(code, index)
     long code;
     unsigned short index;
{
	gsi_int	iContext = gsi_current_context() ;

	gsi_registered_item ret_arg;
	gsi_registered_item *pGri = gsi_make_registered_items(1);
	ret_arg = *pGri;
	gsi_set_handle(ret_arg, index);
	set_type(ret_arg, NULL_TAG);
	set_status(ret_arg, code);
	set_int(ret_arg, NO_ERR);

	gsi_return_attrs(ret_arg, &gAttr[AUXCOD_POS], 2, iContext);
	gsi_reclaim_registered_items(pGri);
#ifdef DEBUG
	printf("**** badvalue_handler:: handle= %d\n", index);
#endif
}

/*
*******************************************************************************

   function: build_timestamp()
   args; pitime, date

   This function converts a time in klunks to a g2 compatible time format.

*******************************************************************************
*/
void build_timestamp(pitime, date)
     long *pitime;
     icp_timestamp_type *date;
{
  long PiTimeArray[TIMESIZE];

  pitm_secint( *pitime, PiTimeArray);

  date->year = (unsigned short)PiTimeArray[PI_YEAR_POS];
  date->month = (unsigned short)PiTimeArray[PI_MONTH_POS];
  date->day = (unsigned short)PiTimeArray[PI_DAY_POS];
  date->hour = (unsigned short)PiTimeArray[PI_HOUR_POS];
  date->minute = (unsigned short)PiTimeArray[PI_MINUTE_POS];
  date->second = (unsigned short)PiTimeArray[PI_SECOND_POS];

}


/* New version of build_timestamp() for the gsi50 features */
void build_timestamp_gsi5(pitime, date, sTimetext)
     long *pitime;
     gsi_registered_item  date;
	  char * sTimetext;	/*this is added for convenience;it'd be cumbersome to extract the string from the gsi_registered_item otherwise */
{
  long PiTimeArray[TIMESIZE];

	pitm_secint( *pitime, PiTimeArray);
	gsi_set_timestamp(date, gsi_encode_timestamp( PiTimeArray[PI_YEAR_POS],
								PiTimeArray[PI_MONTH_POS],
								PiTimeArray[PI_DAY_POS],
								PiTimeArray[PI_HOUR_POS],
								PiTimeArray[PI_MINUTE_POS],
								PiTimeArray[PI_SECOND_POS]));
	sprintf(sTimetext, "%02d%02d%4d%02d%02d%02d",
								PiTimeArray[PI_MONTH_POS],
								PiTimeArray[PI_DAY_POS],
								PiTimeArray[PI_YEAR_POS],
								PiTimeArray[PI_HOUR_POS],
								PiTimeArray[PI_MINUTE_POS],
								PiTimeArray[PI_SECOND_POS]);
} 
  


/* 
*******************************************************************************

   Function: check_object ()
   args:

   This function checks to see if the object exists and if so it returns the 
   pi point for that object.  The object contains the object index in TP form.
   The type is taken from the structure at define time. The pi point is the 
   value given from pi that maps to the said object.  

*******************************************************************************
*/
int check_object(object, type, srvNr, pi_point)
     gsi_item       *object;
     unsigned short *type;
     int            *srvNr ;
     long           *pi_point;
{
    gsi_registration    *current_ptr;
    GsiPiPointStruct    *pi_ptr;
    int                 iRet = GSI_SUCCESS;
    gsi_int             iContext = gsi_current_context();
    gsi_int             iX ;

    iX = gsi_int_of(*object) ;
    current_ptr = gsi_registration_of(iX,iContext);
    if (current_ptr == NULL)
    {
        return GSI_FAILURE;
    }
    else
        /* get the element */
        pi_ptr = (GsiPiPointStruct *)gsi_user_data_of(gsi_registration_of(int_of(*object),iContext));

    if (pi_ptr == 0)
    {
        iRet = GSI_FAILURE;
    }
    else
    {
        /* Set the server number, point number, and type */
        /* --------------------------------------------- */
        *pi_point = pi_ptr->pt_id;
        *srvNr = pi_ptr->pi_srv ;
        *type = pi_ptr->pi_type;
    }
#ifdef DEBUG
    printf("\n*****check_object: int_of(*object) = %d, iRet=%d\n\n",int_of(*object), iRet);
#endif
	return (iRet);

}

/* ******************************************************

   function: check_yesno()
   
   This function evaluates the parsed initialization string value
   for a y or a n. And returns a true or a false.

   ***************************************************/
int check_yesno(arg, value)
     char *arg;
     short *value;
{

    switch (*arg)
    {   case 'Y' : 
        case 'y':
                    *value = (short)TRUE;
                    break;
        case 'N': 
        case 'n':
                    *value = (short)FALSE;
                    break;
        default:
                    return(GSI_FAILURE);
                    break;
    }
    return(GSI_SUCCESS);
}


/* 
*******************************************************************************

   Function: conv_rpc2pi_time()
   args: rpc_time, pi time

   This function takes the string format mmddyyyyhhmmss and returns the pi time.  The 
   function must first check to see if the arg is a string.

*******************************************************************************
*/
int conv_rpc2pi_time(rpc_time, pi_time)
     gsi_item *rpc_time;
     long *pi_time;
{
    char temp_string[15];
    long pi_timearray[TIMESIZE];

    /* check to see if the rpc_time is a string */
    if (type_of(*rpc_time) != STRING_TAG)
        return (GSI_FAILURE);

    /* put the timestamp into a char string */
    strcpy( temp_string, str_of(*rpc_time) );

    /* extract the elements into an integer array */
    sscanf( temp_string, "%2d%2d%4d%2d%2d%2d",
	    &pi_timearray[PI_MONTH_POS],
	    &pi_timearray[PI_DAY_POS],
	    &pi_timearray[PI_YEAR_POS],
	    &pi_timearray[PI_HOUR_POS],
	    &pi_timearray[PI_MINUTE_POS],
	    &pi_timearray[PI_SECOND_POS] );

    /* convert the array to PI time */
    pitm_intsec( pi_time, pi_timearray );

    return (GSI_SUCCESS);

}


/* ======================================================================= */
/*                                                                         */
/* Since an encoded password may contain a null character, fgets cannot be */
/* used to read the lines of the server data file.  Instead, we read each  */
/* record character-by-character in this function.                         */
/*                                                                         */
/* ======================================================================= */
int getNextServerRec(char *buffer, long maxChars, FILE *fp)
{
    int     c='\n', ct=0 ;
    char    *p = buffer ;

    if (feof(fp))
        return FALSE ;

    while (ct==0 && c != EOF)
    {
        c = fgetc(fp) ;
        while (c != EOF && c != '\n')
        {
            *p++ = c ;
            if (++ct == maxChars-1)
                break ;
            c = fgetc(fp) ;
        }

        if (c==EOF && ct==0)
            return FALSE ;
    }


    *p = '\0' ;
    return TRUE ;
}

/*
*******************************************************************************

   function get_pi_error_message()
   args: code, index
   
   This function determines the digital state error message for a particular
   variable (identified by its index number) and returns a message to G2.

*******************************************************************************
*/
#define PI_DIGSTATE_OOR   -11
#define CharsPerDigState   12
int get_pi_error_message(code, index)
    long            code;
    unsigned short  index;
{
  
    static char     tag[CharsPerDigState+3];
    char            msg[STRSZ];
    gsi_item        code_param = gsi_make_item();
    register int    i;
    PIAPI_STRUCT    api_err;
    long            pistatus;

  /* clear string and set eol */
  for (i=0; i<CharsPerDigState; i++)
    tag[i]=0L;

  /* get the digital state from pi */
/*if ( code > 0 ) code = code * -1; */
  pistatus = pipt_digstate( abs(code), tag, CharsPerDigState );
 
  switch (pistatus){
  case PI_DIGSTATE_OOR: 
    sprintf (msg,"Digital state %d out of range for object index %d",
	     code, index);
    
    /* Call the PIAPI error handler */
    strcpy( api_err.funct_name, "PIPT_DIGSTATE" );
    api_err.pi_status = pistatus;
    api_err.pi_point = (long) NULL;
    api_err.object_ind = index;
    sprintf (api_err.arguments, "<dig code = %d>", code );
    piapi_error( &api_err );
    
    break;

  case 0: sprintf (msg,"Digital state %d : %s - for object index %d",
		     code, tag, index);
    break;
  default:
        sprintf (msg,"Digital state %d for object index %d, produced unknown error %d",
	     code, index, pistatus);

    /* Call the PIAPI error handler */
    strcpy( api_err.funct_name, "PIPT_DIGSTATE" );
    api_err.pi_status = pistatus;
    api_err.pi_point = (long) NULL;
    api_err.object_ind = index;
    sprintf (api_err.arguments, "<dig code = %d>", tag );
    piapi_error( &api_err );
  }

	/* convert the code into a temp_param for the error handler */
    logMsg(LLEVHIGH, "** handle ", FALSE, -1, index, msg, code) ;
	gsi_reclaim_item(code_param);
	return (GSI_SUCCESS);

}

/* ========================================================================= */
/*                                                                           */
/*                A case-insensitive string comparison.                      */
/*                                                                           */
/*  A return value of TRUE means the strings are the same (with the possible */
/*  exception of case).                                                      */
/*                                                                           */
/* ========================================================================= */
int gleich(char *str1, char *str2)
{
    unsigned int    iLen = strlen(str1) ;
    unsigned int    i ;

    if (iLen != strlen(str2))
        return FALSE ;
    for (i = 0 ; i < iLen ; i++)
        if (toupper(*str1++) != toupper(*str2++))
            return FALSE ;
    return TRUE ;
}

/* ============================================================ */
/*                                                              */
/* Check the time stamp in very rough terms to see if it is     */
/* approximately correct and to make sure it will not overflow  */
/* its buffer when it is stringified.                           */
/*                                                              */
/* ============================================================ */
int NotTooBig(PITIMESTAMP *ts)
{
    if (ts->year < 0 || ts->month < 0 || ts->day < 0)
        return FALSE ;
    if (ts->hour < 0 || ts->minute < 0 || ts->second < 0.0)
        return FALSE ;
    if (ts->year > 9999 || ts->month > 12 || ts->day > 31)
        return FALSE ;
    if (ts->hour > 24 || ts->minute > 59 || ts->second >= 60.0)
        return FALSE ;
    return TRUE ;
}


/* ========================================================================= */
/*                                                                           */
/* Place the value of a PI point that has been stored in a snapshot into a   */
/* gsi_registered_item in preparation for sending it to G2.  Perform any     */
/* type conversions that make sense.  If the user has requested that G2      */
/* variables be timestamped with the last recorded PI time, timestamp the    */
/* gsi_registered_item.                                                      */
/*                                                                           */
/* Store PIB_BAD in the gsi_registered_item when the needed type conversion  */
/* doesn't make sense.                                                       */
/*                                                                           */
/* ========================================================================= */
void PIValToVar(GsiPiPointStruct *pi_ptr, PI_EVENT *pVals, gsi_registered_item *ptr_regit)
{
    char                stateMsg[14] ;
    double              osts ;
    int                 iContext = gsi_current_context() ;
    long                pifStat ;
    long                liX ;

    gsi_item            ret_error = gsi_make_item();
    gsi_int             g2vStat ;

    PIAPI_STRUCT        api_err;
    PITIMESTAMP         ts ;
    CtxCfg*             ptrCtxState = &CtxCfgs[iContext];

    /* Depending upon the type of the PI Point and the G2 variable, do what */
    /* is necessary to store the value in the gsi_registered_item.          */
    /* -------------------------------------------------------------------- */
    g2vStat = NO_ERR ;
	switch (pi_ptr->pi_type)
	{
		case pipFlt:    /* Float -> integer.  OK if it will fit.  Follow ver 4 rules. */
                        /* ---------------------------------------------------------- */
                        if (pi_ptr->g2_type == GSI_INTEGER_TAG)
                        {
                            if (pVals->drval >= MIN_G2_INTEGER && pVals->drval <= MAX_G2_INTEGER)
                            {
                                liX = v4round(pVals->drval) ;
                                gsi_set_int(*ptr_regit, liX);
                            }
                            else
                                g2vStat = PIB_BADTYPE ;
                        }
                        /* Float -> float */
                        /* -------------- */
                        else if (pi_ptr->g2_type == GSI_FLOAT64_TAG)
                        {
                            gsi_set_flt(*ptr_regit, pVals->drval);
                        }
                        /* Float -> string or Float -> symbol     */
                        /* Convert to string before storing value */
                        /* -------------------------------------- */
                        else if (pi_ptr->g2_type == GSI_STRING_TAG || pi_ptr->g2_type == GSI_SYMBOL_TAG)
                        {
                            sprintf(pVals->bval, "%g", pVals->drval) ;
                            if (pi_ptr->g2_type == GSI_STRING_TAG)
                            {
                                gsi_set_str(*ptr_regit, pVals->bval) ;
                            }
                            else
                            {
                                gsi_set_sym(*ptr_regit, pVals->bval) ;
                            }
                        }
                        /* Float -> logical : 0,0 means false, otherwise true */
                        /* -------------------------------------------------- */
                        else if (pi_ptr->g2_type == GSI_LOGICAL_TAG )
                        {
                            gsi_set_log(*ptr_regit, ((pVals->drval != 0.0) ? GSI_TRUE : GSI_FALSE)) ;
                        }
                        /* Float -> anything else is not allowed */
                        /* ------------------------------------- */
                        else
                            g2vStat = PIB_BADTYPE ;
                        break;


                        /* String -> xxx is only allowed if the G2 variable  */
                        /* is a string or a symbol.  Other conversions might */
                        /* make sense depending on the string value but we   */
                        /* follow ver. 4 rules and reject them out of hand.  */
                        /* ------------------------------------------------- */
                        
        case pipTxt:    
                        if (pi_ptr->g2_type == GSI_STRING_TAG)
                        {
                            gsi_set_str(*ptr_regit, pVals->bval) ;
                        }
                        else if (pi_ptr->g2_type == GSI_SYMBOL_TAG)
                        {
                            gsi_set_sym(*ptr_regit, pVals->bval) ;
                        }
                        else
                            g2vStat = PIB_BADTYPE ;
                        break ;

                        
        case pipInt:    /* Integer -> Integer */
                        /* ------------------ */
                        if (pi_ptr->g2_type == GSI_INTEGER_TAG)
                        {
                            gsi_set_int(*ptr_regit, pVals->ival);
                        }
                        /* Integer -> Float */
                        /* ---------------- */
                        else if (pi_ptr->g2_type == GSI_FLOAT64_TAG)
                        {
                            gsi_set_flt(*ptr_regit, (double)pVals->ival);
                        }
                        /* Integer -> String or Symbol.  Display as text. */
                        /* ---------------------------------------------- */
                        else if (pi_ptr->g2_type == GSI_STRING_TAG || pi_ptr->g2_type == GSI_SYMBOL_TAG)
                        {
                            sprintf(pVals->bval, "%ld", pVals->ival) ;
                            if (pi_ptr->g2_type == GSI_STRING_TAG)
                            {
                                gsi_set_str(*ptr_regit, pVals->bval) ;
                            }
                            else
                            {
                                gsi_set_sym(*ptr_regit, pVals->bval) ;
                            }
                        }
                        /* Integer -> Logical.  0 means false, otherwise true. */
                        /* --------------------------------------------------- */
                        else if (pi_ptr->g2_type == GSI_LOGICAL_TAG )
                        {
                            gsi_set_log(*ptr_regit, ((pVals->ival) ? GSI_TRUE : GSI_FALSE)) ;
                        }
                        /* Integer -> anything else (??).  Not allowed. */
                        /* -------------------------------------------- */
                        else
                            g2vStat = PIB_BADTYPE ;                      
                        break;

        case pipDig:    /* We follow ver. 4 rules and only permit the storage   */
                        /* of digital tag values in string or symbol variables. */
                        /* ---------------------------------------------------- */
                        if (pi_ptr->g2_type == GSI_STRING_TAG || pi_ptr->g2_type == GSI_SYMBOL_TAG)
                        {
                            /*if ( istat > 0 ) istat = istat * -1;*/
                            pifStat = pipt_digstate ( abs(pVals->istat), pVals->bval, CHARSPERDIGSTATE );

                            if ( (ptrCtxState->log_level >= 9) || (pifStat < 0) ) 
                            {
                                /* Call the PIAPI error handler */
                                strcpy( api_err.funct_name, "PIPT_DIGSTATE" );
                                api_err.pi_status = pifStat;
                                api_err.pi_point = pi_ptr->pt_id;
                                api_err.object_ind = gsi_handle_of( *ptr_regit );
                                sprintf (api_err.arguments, "<digcode = %d>", pVals->istat );
                                piapi_error( &api_err );
                            }

                            if ( pifStat != NO_PI_ERROR ) 
                            {
                                logMsg(LLEVHIGH,"** ",FALSE, pi_ptr->pi_srv, pi_ptr->pt_id,"Retrieval of digital state string failed"
                                    ,pifStat) ;
                                g2vStat = PIB_BAD ;
                            }
                            if (pi_ptr->g2_type == GSI_STRING_TAG)
                            {
                                gsi_set_str(*ptr_regit, pVals->bval);
                            }
                            else
                            {
                                gsi_set_sym(*ptr_regit, pVals->bval);
                            }
                            
                        }
                        else
                            g2vStat = PIB_BADTYPE ;
                        break;

        case pipTim:    if (pi_ptr->g2_type == GSI_FLOAT64_TAG)
                            gsi_set_flt(*ptr_regit, pVals->drval) ;
                        else if (pi_ptr->g2_type == GSI_STRING_TAG || pi_ptr->g2_type == GSI_SYMBOL_TAG)

                        /* If the variable is a string or a symbol, display    */
                        /* the timestamp as a sequence of digits in US format. */
                        /* --------------------------------------------------- */
                        
                        {
                            pitm_setpitime(&ts, (long)pVals->drval, 0.0) ;
                            if (NotTooBig(&ts))
                                sprintf(pVals->bval, "%02d%02d%04d%02d%02d%02d", ts.month,
                                    ts.day, ts.year, ts.hour, ts.minute, (short)ts.second) ;
                            else
                                strcpy(pVals->bval, "**************") ;
                            if (pi_ptr->g2_type == GSI_STRING_TAG)
                                gsi_set_str(*ptr_regit, pVals->bval) ;
                            else
                                gsi_set_sym(*ptr_regit, pVals->bval) ;
                        }
                        else
                            g2vStat = PIB_BADTYPE ;
                        break ;
 
                        /* We don't know how to deal with this type of PI tag */
                        /* -------------------------------------------------- */
        default:        logMsg(LLEVHIGH,"** ",FALSE, pi_ptr->pi_srv, pi_ptr->pt_id,"PI Ptr type invalid",
                                    pi_ptr->pi_type) ;
                        g2vStat = PIB_BADTYPE ;
    }

    /* Set the variable status to show the success or failure of this operation */
    /* ------------------------------------------------------------------------ */
    gsi_set_status(*ptr_regit, g2vStat);
    pi_ptr->status = g2vStat ;


    /* If the initialization string contains -ty, we should timestamp this */
    /* record with the time returned by PI.                                */
    /* ------------------------------------------------------------------- */
    if (ptrCtxState->do_timestamp)
    {
        osts = gsi_encode_timestamp(pVals->timestamp.year, pVals->timestamp.month, pVals->timestamp.day,
                                    pVals->timestamp.hour, pVals->timestamp.minute, 
                                    (long)pVals->timestamp.second) ;
        gsi_set_timestamp(*ptr_regit, osts) ;
    }

     /* Prepare to the return the auxiliary code and its description */
    /* ------------------------------------------------------------ */
    if (pi_ptr->pi_type == pipFlt || pi_ptr->pi_type == pipInt)
    {
        gsi_set_int(gAttr[AUXCOD_POS], pVals->istat) ;
        if (!pVals->istat)
            strcpy(stateMsg,"") ;
        else if (pipt_digstate(pVals->istat, stateMsg, 13) != NO_ERR)
            sprintf(stateMsg, "???:%ld", pVals->istat) ;
        gsi_set_str(gAttr[AUXMSG_POS], stateMsg);
    }
    else
    {
        gsi_set_int(gAttr[AUXCOD_POS], 0) ;
        gsi_set_str(gAttr[AUXMSG_POS], "") ;
    }

    gsi_reclaim_item(ret_error) ;

}


/* ***************************************************************

   Function: osi_parse_init()
   Args: *init_str, init_args, str_len

   This function breaks the elements of the initialization string
   into individual option commands.  An option command consists of 
   a '-', a single character (the key) and, optionally, a parameter.
   There may be spaces between the key and the parameter, but the
   first character of the parameter may not be '-'.  Information
   about each of the commands is stored in a line of the init_args
   array.
   
   Each option command must be separated from its predecessor by one
   or more spaces.

   *****************************************************************/
int osi_parse_init(init_str, init_args, str_len)
     char *init_str;
     ARG_ELEMENT_STRUCT *init_args;
     unsigned short str_len;
{
#define ERMSGSZ 80

    register int    i = 0, num_args = 0, jArg ;
    char    errorMsg[ERMSGSZ+1] ;

    while (i < str_len)
    {
        /* Find the start of the next key & parameter */
        /* ------------------------------------------ */
        while (i < str_len && init_str[i] == ' ')
            i++ ;
        if ( i >= str_len)
            break ;

        /* Stop scanning if we have already processed  */
        /* the maximum number of arguments allowed.    */
        /* ------------------------------------------- */
        if (num_args >= MAXINITARGS)
        {
            _snprintf(errorMsg,ERMSGSZ,"Number of initialization string arguments exceeds the maximum allowed (%d).", MAXINITARGS) ;
            LOGMSG(LLEVHIGH, errorMsg) ;
            return num_args ;
        }

        /* Legacy code: a single $ means the same as -by, */
        /* send logged messages to message board.         */
        /* ---------------------------------------------- */
        if (init_str[i] == '$')
        {
            i++ ;
            if (i >= str_len || init_str[i] == ' ')
            {
                init_args[num_args].key = 'b';
                init_args[num_args].arg[0] = 'y';
                init_args[num_args].arg[1] = '\0' ;
                num_args++ ;
                continue ;
            }
            else
                init_args[num_args].key = '$' ;
        }

        /* Make sure the command starts with '-' */
        /* ------------------------------------- */
        else if (init_str[i] == '-')
        {
            i++ ;
            if (i >= str_len || init_str[i] == ' ')
            {
               LOGMSG(LLEVHIGH, "Orphaned '-' in the initialization string.");
                continue ;
            }
            init_args[num_args].key = init_str[i++] ;
        }

        /* Bypass this field if the command did not start with '-' */
        /* ------------------------------------------------------- */
        else
        {
            _snprintf(errorMsg, ERMSGSZ, "Command (%c) does not start with '-'.", init_str[i++]) ;
            LOGMSG(LLEVHIGH, errorMsg) ;
            while (i < str_len && init_str[i] != ' ')
                i++ ;
            continue ;
        }

        /* Move to the next character that is not a space where we */
        /* will determine if this command has a parameter or not.  */
        /* ------------------------------------------------------- */
        while (i < str_len && init_str[i] == ' ')
            i++ ;
        
        /* If this option does not have a parameter, count it  */
        /* and go back to look for the next option.            */
        /* --------------------------------------------------- */
        if (i >= str_len || init_str[i] == '-')
        {
            init_args[num_args].arg[0] = '\0' ;
            num_args++ ;
            continue ;
        }

        /* Copy the parameter into its assigned storage area */
        /* ------------------------------------------------- */
        jArg = 0 ;
        while (i < str_len && init_str[i] != ' ' && jArg < ARGLEN)
            init_args[num_args].arg[jArg++] = init_str[i++] ;

        /* Bypass the excess characters if the parameter is too long */
        /* --------------------------------------------------------- */
        if (i < str_len && init_str[i] != ' ')
        {
            _snprintf(errorMsg,ERMSGSZ,"Parameter for %c option truncated.", init_args[num_args].key) ;
            LOGMSG(LLEVHIGH, errorMsg) ;
            do {
                i++ ;
            } while (i < str_len && init_str[i] != ' ') ;
        }

        /* Terminate the parameter, count the option, and try again */
        /* -------------------------------------------------------- */
        init_args[num_args].arg[jArg] = '\0';
        num_args++ ;
    }

    return(num_args);
}

/*
*******************************************************************************
*
* Function: piapi_error
* Purpose: 	Used to print out error information regarding errors
*           that occur in PI API functions.
*		
*******************************************************************************
*/
void piapi_error( PIAPI_STRUCT   *api_err )
{
    char    *msgDet, infoLine[100], scratch[20], scratch2[20] ;
    int     debugLev = (api_err->pi_status) ? LLEVHIGH : LLEVALL ;

    sprintf(infoLine,"%s (%d)  G2# %s  PI# %s",
        api_err->funct_name, api_err->pi_status,
        (api_err->object_ind) ? ltoa(api_err->object_ind,scratch,10) : "N/A" ,
        (api_err->pi_point) ? ltoa(api_err->pi_point, scratch2,10) : "N/A" );
    logMsg(debugLev, api_err->pi_status ? ">  " : "   ", FALSE, -1, 0, infoLine, 0); 

    if ( api_err->arguments )
        logMsgs(debugLev, "   | ", "Args: %s", api_err->arguments) ;

    switch ( api_err->pi_status )
    {
        case ( 0 ):         msgDet = "Success";
                            break;
        case ( -1 ):        msgDet = "Point does not exist" ;
                            break;
        case ( -2 ):        msgDet = "Passed tag is all spaces" ;
                            break;
        case ( -5 ):        msgDet = "Tag not found, or not connected" ;
                            break;
        case ( -11 ):       msgDet = "Digital state code out of range" ;
                            break;
        case ( -13 ):       msgDet = "Digital state string not found within range of tag" ;
                            break;
        case ( -25 ):       msgDet = "Point is not a digital tag" ;
                            break;
        case ( -70 ):       msgDet = "Count is < 0" ;
                            break;
        case ( -71 ):       msgDet = "Point number out of range" ;
                            break;
        case ( -72 ):       msgDet = "No room for more programs requesting exceptions" ;
                            break;
        case ( -73 ):       msgDet = "No room for this many points for this list" ;
                            break;
        case ( -74 ):       msgDet = "No room for more points" ;
                            break;
        case PIB_BADSRV:    msgDet = "Bad server (user/password?)" ;
                            break ;
        case PIB_BADTYPE:   msgDet = "Type conversion error" ;
                            break ;
        case PIB_NOSUCHTAG: 
        case PIB_TOOLONG:   msgDet = "Unknown tag" ;
                            break ;
        default:            msgDet = "Unknown error message" ;
                            break;

    }
    logMsgs(debugLev, "   | ", "Message : %s", msgDet );

} 

/* ============================================================================ */
/*                                                                              */
/*  Return a code for the type of the PI point with the specified point number. */
/*                                                                              */
/* ============================================================================ */
int PIPointTypeOf(int srvNr, long PIPtNr, enum PIPointType *piType)
{
    char                shortType ;
    long                piStat ;
    enum PIPointType    pixType ;

    gsi_item            error_pt = gsi_make_item() ;
    gsi_int             retVal = NO_ERR ;

    // log (ALL, "PIPointTypeOf(%s)", piPointName) ;
    *piType = pipUnknown ;

    /* Determine its type */
    /* ------------------ */
    piStat = pipt_pointtype( PIPtNr, &shortType);
	if (piStat < 0)
	{
        logMsg(LLEVHIGH,"** ",FALSE, srvNr, PIPtNr,
            "Unable to determine point type : pipt_pointtype failed", piStat) ;
		return PIB_BAD ;
	}
    if (shortType == 'R' || shortType == 'r')
        *piType = pipFlt ;
    else if (shortType == 'D' || shortType == 'd')
        *piType = pipDig ;
    else if (shortType == 'I' || shortType == 'i')
    {
        piStat = pipt_pointtypex(PIPtNr, &pixType) ;
	    if (piStat < 0)
	    {
            logMsg(LLEVHIGH,"** ",FALSE, srvNr, PIPtNr,
                "Unable to determine point type : pipt_pointtypex failed", piStat) ;
		    return PIB_BAD ;
	    }
        if (pixType == PI_Type_PIstring)
            *piType = pipTxt ;
        else if (pixType == PI_Type_PItimestamp)
            *piType = pipTim ;
        else
            *piType = pipInt ;
    }
    else
        retVal = PIB_BADTYPE ;

    gsi_reclaim_item(error_pt) ;
    return retVal ;
}

/* Translate the code for the PI point type to a single letter */
/*                                                             */
/*  D=digital  I=integer  R=real  S=string  T=time  U=unknown  */
/* =========================================================== */
char    PITypeToLet(enum PIPointType type)
{
    typedef struct { PIPointType    from ;
                     char           to ; } LUPT ;

 LUPT    lupt[] =  { { pipDig, 'D' }, { pipInt, 'I' }, { pipFlt, 'R' }, 
                     { pipTxt, 'S' }, { pipTim, 'T' }, { pipUnknown, 'U' } } ;

#define NRTYPES sizeof(lupt)/sizeof(LUPT) 

    int     i ;

    for (i = 0 ; i < NRTYPES ; i++)
        if (lupt[i].from == type)
            return lupt[i].to ;
    return 'U' ;
}


/* ======================================================================== */
/*                                                                          */
/*   Retrieve a PI attribute specified by a code for the specified point.   */
/*                                                                          */
/* To avoid making numerous unnecessary calls to PI functions, when more    */
/* than one attribute is returned by a PI function, the values are saved    */
/* in a static buffer. Release the saved values when "firstCall" is set.    */
/*                                                                          */
/* ======================================================================== */
int ReadPIAttr(int srvNr, long piPtNr, gsi_int attrCode, gsi_item ToG2, int firstCall)
{
    static  int     haveCompVals = FALSE ;
    static  long    compdev, compmin, compmax ;

    static  int     haveDates = FALSE ;
    static  long    creaDate, creatorLen, chgDate, changerLen ;
    static  char    creator[STRSZ] ;
    static  char    changer[STRSZ] ;

    static  int     haveExcVals = FALSE ;
    static  float   excdev ;
    static  long    excmin, excmax ;

    static  int     haveState = FALSE ;
    static  long    larchiving, lcompressing, filtercode ;

    static  int     haveLoc = FALSE ;
    static  long    loc[5] ;

    static  int     haveTotalSpecs = FALSE ;
    static  long    totalcode ;
    static  float   convers ;

    char    txtBuffer[STRSZ] ;
    float   fX, fX2 ;
    int     retCode = NO_ERR, i ;
    long    lX ;
    long    piStat ;


    logMsg(LLEVMOST, "   |=> ",FALSE, srvNr, piPtNr, "ReadPIAttr", attrCode) ;
    if (firstCall)
    {
        haveCompVals = FALSE ;
        haveDates = FALSE ;
        haveExcVals = FALSE ;
        haveState = FALSE ;
        haveLoc = FALSE ;
        haveTotalSpecs = FALSE ;
    }
    switch(attrCode)
    {
    case 1:     /* Canonical Data Type */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Canonical Data Type", 0) ;
                /* >>>> check <<<< */
                if ((piStat = pipt_pointtype(piPtNr, txtBuffer)) != 0)
                    return piStat;
                gsi_set_int(ToG2, (long)txtBuffer[0]) ;
                return NO_ERR ;

    case 100:   /* Engineering Units */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Engineering Units", 0) ;
                if ((piStat=pipt_engunitstring(piPtNr, txtBuffer, STRSZ-1)) != 0)
                    return piStat ;
                gsi_set_str(ToG2, txtBuffer) ;
                return NO_ERR ;

    case 101:   /* Description */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Description", 0) ;
                if ((piStat=pipt_descriptor(piPtNr, txtBuffer, 26)) != 0)
                    return piStat ;
                gsi_set_str(ToG2, txtBuffer) ;
                return NO_ERR ;

    case 5004:  /* stepped */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Stepped", 0) ;
                if (pipt_recordtype(piPtNr, &lX) != 0)
                    return GSI_FAILURE ;
                gsi_set_log(ToG2, lX ? GSI_TRUE : GSI_FALSE) ;
                return NO_ERR ;

    case 5005:  /* archiving */
    case 5017:  /* filter time constant */
    case 6005:  /* compressing */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, (attrCode==5005)? "archiving" : 
                    (attrCode==5017) ? "filter time constant": "Compressing", 0) ;
                if (!haveState)
                    if (pipt_inprocbits(piPtNr, &larchiving, &lcompressing, &filtercode) != 0)
                        return GSI_FAILURE ;
                    else
                        haveState = TRUE ;
                if (attrCode == 5005)
                    gsi_set_log(ToG2, larchiving ? GSI_TRUE : GSI_FALSE) ;
                else if (attrCode == 5017)
                    gsi_set_log(ToG2, filtercode) ;
                else
                    gsi_set_int(ToG2, lcompressing ? GSI_TRUE : GSI_FALSE) ;
                return NO_ERR ;

    case 5006:  /* Extended Descriptor */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Extended Descriptor", 0) ;
                if (pipt_exdesc(piPtNr, txtBuffer, STRSZ-1) != 0)
                    return GSI_FAILURE ;
                gsi_set_str(ToG2, txtBuffer) ;
                return NO_ERR ;

    case 5009:  /* Instrument Tag */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Instrument Tag", 0) ;
                if (pipt_instrumenttag(piPtNr, txtBuffer, STRSZ-1) != 0)
                    return GSI_FAILURE ;
                gsi_set_str(ToG2, txtBuffer) ;
                return NO_ERR ;

    case 5010:  /* Point Source */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Point Source", 0) ;
                if (pipt_pointsource(piPtNr, txtBuffer) != 0)
                    return GSI_FAILURE ;
                txtBuffer[1] = '\0';
                gsi_set_str(ToG2, txtBuffer) ;
                return NO_ERR ;

    case 5013:  /* Tag */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Tag", 0) ;
                if (pipt_taglong(piPtNr, txtBuffer, STRSZ-1) != 0)
                    return GSI_FAILURE ;
                gsi_set_str(ToG2, txtBuffer) ;
                return NO_ERR ;

    case 5014:  /* Exception Max Interval */
    case 5015:  /* Exception Min Interval */
    case 5016:  /* Exception Deviation */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, (attrCode==5014)? "Exception Max Interval" : 
                    (attrCode==5015) ? "Exception Min Interval": "Exception Deviation", 0) ;
                if (!haveExcVals)
                    if (pipt_excspecseng(piPtNr, &excdev, &excmin, &excmax) != 0)
                        return GSI_FAILURE ;
                    else
                        haveExcVals = TRUE ;
                if (attrCode == 5014)
                    gsi_set_int(ToG2, excmax) ;
                else if (attrCode == 5015)
                    gsi_set_int(ToG2, excmin) ;
                else
                    gsi_set_flt(ToG2, (double)excdev) ;
                return NO_ERR ;

    case 5018:  /* High Entry Limit */
    case 5019:  /* Low Entry Limit */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, 
                    (attrCode==5018)? "High Entry Limit" : "Low Entry Limit", 0) ;
                if (pipt_scale(piPtNr, &fX, &fX2) != 0)
                    return GSI_FAILURE ;
                if (attrCode == 5018)
                    gsi_set_flt(ToG2, (double)(fX + fX2)) ;
                else
                    gsi_set_flt(ToG2, (double)fX) ;
                return NO_ERR ;


    case 5020:  /* Typical Value */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Typical Value", 0) ;
                if (pipt_typicalvalue(piPtNr, &fX) != 0)
                    return GSI_FAILURE ;
                gsi_set_flt(ToG2, (double)fX) ;
                return NO_ERR ;

    case 5200:  /* Display Digits */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Display Digits", 0) ;
                if (pipt_displaydigits(piPtNr, &lX) != 0)
                    return GSI_FAILURE ;
                gsi_set_int(ToG2, lX) ;
                return NO_ERR ;

    case 6004:  /* Scanning */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Scanning", 0) ;
                if (pipt_scan(piPtNr, &lX) !=0)
                    return GSI_FAILURE ;
                gsi_set_log(ToG2, lX ? GSI_TRUE : GSI_FALSE) ;
                return NO_ERROR ;

    case 6014:  /* Compression Max Interval */
    case 6015:  /* Compression Min Interval */
    case 6016:  /* Compression Deviation */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, (attrCode==6014)? "Compression Max Interval" : 
                    (attrCode==6015) ? "Compression Min Interval": "Compression Deviation", 0) ;
                if (!haveCompVals)
                    if (pipt_compspecs(piPtNr, &compdev, &compmin, &compmax) != 0)
                        return GSI_FAILURE ;
                    else
                        haveCompVals = TRUE ;
                if (attrCode == 6014)
                    gsi_set_int(ToG2, compmax) ;
                else if (attrCode == 6015)
                    gsi_set_int(ToG2, compmin) ;
                else
                    gsi_set_flt(ToG2, (double)compdev) ;
                return NO_ERR ;

    case 7000:  /* Point ID number */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Point ID Number", 0) ;
                if (pipt_pointid(piPtNr, &lX) != 0)
                    return GSI_FAILURE ;
                gsi_set_int(ToG2, lX) ;
                return NO_ERR ;

    case 7001:  /* Creation Date */
    case 7002:  /*    Creator    */
    case 7003:  /*  Change Date  */
    case 7004:  /*    Changer    */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, (attrCode <= 7002) ?
                    (attrCode==7001)?"Creation Date":"Creator" :
                    (attrCode==7003)?"Change Date":"Changer", 0) ;
                if (!haveDates)
                {
                    creatorLen = changerLen = STRSZ-1 ;
                    if (pipt_dates(piPtNr, &creaDate, creator, creatorLen, &chgDate,
                                changer, changerLen) != 0)
                        return GSI_FAILURE ;
                    else
                        haveDates = TRUE ;
                }
                if (attrCode == 7001)
                    gsi_set_flt(ToG2, (double)creaDate) ;
                else if (attrCode == 7002)
                    gsi_set_str(ToG2, creator) ;
                else if (attrCode == 7003)
                    gsi_set_flt(ToG2, (double)chgDate) ;
                else
                    gsi_set_str(ToG2, changer) ;
                return NO_ERR ;

    case 7005:  /* Location 1 */
    case 7006:  /* Location 2 */
    case 7007:  /* Location 3 */
    case 7008:  /* Location 4 */
    case 7009:  /* Location 5 */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Location", attrCode-7004) ;
                if (!haveLoc)
                    if(pipt_location(piPtNr, loc) != 0)
                        return GSI_FAILURE ;
                    else
                        haveLoc = TRUE ;
                i = attrCode - 7005 ;
                gsi_set_int(ToG2, loc[i]) ;
                return NO_ERR ;

    case 8000:  /* Source Tag */
                /* >>>> check <<<< */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Source Tag", 0) ;
                if (pipt_sourcept(piPtNr, &lX) != 0)
                    return GSI_FAILURE ;
                if (pipt_taglong(lX, txtBuffer, STRSZ-1) != 0)
                    return GSI_FAILURE ;
                gsi_set_str(ToG2, txtBuffer) ;
                return NO_ERR ;

    case 8001:  /* Square Root */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Square Root", 0) ;
                if (pipt_squareroot(piPtNr, &lX) != 0)
                    return GSI_FAILURE ;
                gsi_set_int(ToG2, lX) ;
                return NO_ERR ;
            
    case 8002:  /* Totalizer */
    case 8003:  /* Conversion Factor */
                logMsg(LLEVMOST, "   ", FALSE, -1, 0, 
                    (attrCode==8002)? "Totalizer" : "Conversion Factor", 0) ;
                if (!haveTotalSpecs)
                    if (pipt_totalspecs(piPtNr, &totalcode, &convers) != 0)
                        return GSI_FAILURE ;
                    else
                        haveTotalSpecs = TRUE ;
                if (attrCode == 8002)
                    gsi_set_int(ToG2, totalcode) ;
                else
                    gsi_set_flt(ToG2, (double)convers) ;
                return NO_ERR ;

    default:    logMsg(LLEVMOST, "   ", FALSE, -1, 0, "Unknown Code", attrCode) ;
                return GSI_FAILURE ;
    }
    logMsg(LLEVMOST, "  |<== ", FALSE, -1, 0, "ReadPIAttr", 0) ;
    return NO_ERR ;
}

/* =========================================================================== */
/*                                                                             */
/* Read the value of a PI point and store the results in a snapshot structure. */
/*                                                                             */
/*      If successful, prepare the last-recorded-pi-time attribute.            */
/*                                                                             */
/* =========================================================================== */
int ReadPIVal(GsiPiPointStruct *pPInfo, PI_EVENT *pVals)
{
    gsi_int         iContext = gsi_current_context() ;
    CtxCfg*         ptrCtxState = &CtxCfgs[iContext];
    PIAPI_STRUCT    api_err;
    char            datestr[15], dbgBuf[STRSZ] ;
    long            timedate ;
    long            piStat, errCode=0 ;
    PITIMESTAMP     pitsX ;
    size_t          bufLen=STRSZ ;

    /* Read the current value of the PI point */
    /* -------------------------------------- */
    pVals->bsize = STRSZ - 1 ;
    if ((pPInfo->status = switchToServer(pPInfo->pi_srv)) == NO_ERR)
        /* GENSYMCID-1141: value will be truncated if pass a 64 bit float to integer. */
        piStat = pisn_getsnapshotx(pPInfo->pt_id,
                                   (pPInfo->pi_type == pipTxt)? NULL : &pVals->drval,
                                   ((pPInfo->pi_type == pipTxt) || (pPInfo->pi_type == pipFlt)) ? NULL : &pVals->ival,
                                   pVals->bval,
                                   &pVals->bsize,
                                   &pVals->istat,
                                   NULL,
                                   &pVals->timestamp);
    if (pPInfo->status == NO_ERR && !piStat)
    {
        if (pPInfo->pi_type == pipTim)
        {
            pitm_setpitime(&pitsX, pVals->ival, false) ;
            sprintf(dbgBuf, "timestamp: %ld : %02d/%02d/%04d %02d:%02d:%02d", pVals->ival, pitsX.month,
                pitsX.day, pitsX.year, pitsX.hour, pitsX.minute, pitsX.second) ;
            logMsg(LLEVALL, ">  ", FALSE, pPInfo->pi_srv, pPInfo->pt_id, dbgBuf, 0) ;
        }
        else if (pPInfo->pi_type == pipTxt)
        {
            *(((char *)pVals->bval + pVals->bsize)) = '\0' ;
            strcpy(dbgBuf, "Retrieved message: ") ;
            strncat(dbgBuf, pVals->bval, bufLen-1-strlen(dbgBuf)) ;
            dbgBuf[bufLen-1] = '\0' ;
            logMsg(LLEVALL, ">  ", FALSE, pPInfo->pi_srv, pPInfo->pt_id, dbgBuf, 0) ;
        }
    }
    else if (pPInfo->status == NO_ERR)
        pPInfo->status = piStat ;

    /* Prepare a report on what just happened.  The report will only be  */
    /* printed if there was an error or the system is in high debug mode */
    /* ----------------------------------------------------------------- */
    strcpy( api_err.funct_name, "PISN_GETSNAPSHOTX" );
    api_err.pi_status = pPInfo->status ;
    api_err.pi_point = pPInfo->pt_id;
    api_err.object_ind = pPInfo->g2_handle ;

    if (pPInfo->status)
    {
        if (ptrCtxState->log_level > LLEVNORM || 
            !(pPInfo->pi_srv < gNrServers && gServer[pPInfo->pi_srv].errRptd) )
        {
            sprintf(api_err.arguments, "N/A (Snapshot not taken (%ld))", pPInfo->status) ;
            piapi_error( &api_err );
        }
    }
    else
    {
        pitm_intsec(&timedate, (long*)(&pVals->timestamp)) ;
        sprintf (api_err.arguments, "<rval = %g> <istat = %d> <timedate = %d>",
                    pVals->drval, pVals->istat, timedate );
        piapi_error( &api_err );
    }


    /* Report non-zero istat for reals and integers */
    /* -------------------------------------------- */
    if (!pPInfo->status &&  (pPInfo->pi_type == pipFlt || pPInfo->pi_type == pipInt) && pVals->istat)
    {
        logMsg(LLEVHIGH,"** ",FALSE, pPInfo->pi_srv, pPInfo->pt_id, "Non-zero istat.  Possible read failure." , pVals->istat) ;
    }


    /* Prepare the PI-LAST-RECORDED-TIME attribute */
    /* ------------------------------------------- */
    if (pPInfo->status == 0)
    {
        sprintf(datestr, "%02d%02d%04d%02d%02d%02d", pVals->timestamp.month, pVals->timestamp.day, 
            pVals->timestamp.year, pVals->timestamp.hour, pVals->timestamp.minute, (long)pVals->timestamp.second) ;
        gsi_set_str(gAttr[LRPT_POS], datestr);
    }

    /* (AUX-CODE & AUX-MSG will be set in PIValToVar) */

    return pPInfo->status ;
}



void RetrievePIAttrs(gsi_registered_item regItem, gsi_int *pNrAttrsBack, gsi_attr **ppToAttrs)
{
    gsi_registration    reg ;
    gsi_attr            defStruct ;
    gsi_attr            *pFromAttrs, *pFromAttrs0, *pToAttrs, *pNextAttr ;
    gsi_int             regHandle ;
    gsi_int             attrType ;
    gsi_int             nrDefs ;
    gsi_int             iContext = gsi_current_context() ;

    GsiPiPointStruct    *pInfo ;

    char                *pAttrName ;
    int                 i, nrAttrsBack=0 ;

    /* First, find out which identifying attribute tells us which PI */
    /* attributes we want to retrieve.                               */
    /* ------------------------------------------------------------- */
    regHandle = gsi_handle_of(regItem) ;
    reg=gsi_registration_of(regHandle, iContext) ;
    if (reg == NULL) return ;
    pInfo = (GsiPiPointStruct *)gsi_user_data_of(reg) ;
    if (pInfo == NULL) return ;
    if (pInfo->g2_atianr <= 0 || pInfo->g2_atianr > 6 ) return ;
    defStruct = gsi_identifying_attr_of(reg, pInfo->g2_atianr) ;
    attrType = gsi_type_of(defStruct) ;
    if (attrType != GSI_STRUCTURE_TAG) return ;

    /* Determine the maximum number of attributes we will retrieve and */
    /* create an array of gsi_attrs to return them.                    */
    /* --------------------------------------------------------------- */
    nrDefs = gsi_attr_count_of(defStruct) ;
    pFromAttrs0 = gsi_attrs_of(defStruct) ;
    pFromAttrs = pFromAttrs0 ;
    pToAttrs = gsi_make_attrs_with_items(nrDefs) ;
    pNextAttr = pToAttrs ;

    /* Scan the structure to determine which PI attributes we need and in */
    /* which G2 attributes we should store them,  Retrieve the attributes */
    /* from PI and prepare the gsi_attrs to send them to G2.              */
    /* ------------------------------------------------------------------ */                                                         
    for (i = 0 ; i < nrDefs ; i++, pFromAttrs++)
    {
        if (gsi_type_of(*pFromAttrs) != GSI_INTEGER_TAG)
            continue ;
        pAttrName = gsi_attr_name_of(*pFromAttrs) ;
        gsi_set_attr_name(*pNextAttr, gsi_attr_name_of(*pFromAttrs)) ;
        if (ReadPIAttr(pInfo->pi_srv, pInfo->pt_id, gsi_int_of(*pFromAttrs), (gsi_item)(*pNextAttr), i==0) == NO_ERR)
        {
            pNextAttr++ ;
            nrAttrsBack++ ;
        }
    }

    /* The retrieval and preparation process is separated from the actual */
    /* process of sending the data to G2 so that if it becomes necessary  */
    /* in the future to poll the PI attributes, we can do so efficiently  */
    /* in the case of exception reporting.  However since PI attributes   */
    /* should almost never change, it seems reasonable to only retrieve   */
    /* them for a variable when the variable is first registered.         */
    /* ------------------------------------------------------------------ */
    *pNrAttrsBack = nrAttrsBack ;
    *ppToAttrs = pToAttrs ;
}


char    timebuf[MAXNOWLEN+1] ;
char    *tfs = DEF_TFS ;

/*======================================================================
    timestamp
      - format=string containing format specifiers
        listed below; length=length of result buffer
      - returns time in format specified
      - logfile & io = "%d%b%y_%H%M%S" default format
 *======================================================================*/
char *timestamp ( format,result,length )
    char    *format;
    char    *result;
    long     length;
{
  time_t   t;

  /*
  Time-Stamp formats:
  ------------------
    %a  abbr weekday
     A  weekday
     b  abbr month
     B  month
     c  locales date & time representation
     d  day of month (1-31)
     H  hour of day (0-23)
     I  hour of day (1-12)
     j  day of year (1-366)
     m  month of year (1-12)
     M  minute (0-59)
     p  locales version of am or pm
     S  seconds (0-59)
     w  weekday (Sun=0,Sat=6)
     x  locales date rep (mm/dd/yy or dd/mm/yy)
     X  locales time rep
     y  two-digit year (00-99)
     Y  four-digit year
     Z  time zone name
  */

    if (result == NULL || format == NULL)
        return ((char *)NULL);

    time(&t);
    strftime(result,length,format,localtime(&t));  

    return (result);
}


#pragma warning(disable:4244)
/* ================================================================ */
/*      Round to an integer in the style of the version 4 bridge    */
/*                                                                  */
/*        0.5 -> 0   (> 0.5) -> 1    -0.5 -> 0   (< -0.5) -> -1     */
/*                                                                  */
/* ================================================================ */
long    v4round(double dblIn)
{
    int                 negFlag ;
    long                liX ;
    double              dbX ;

    negFlag = (dblIn < 0.0) ? -1 : 1 ;
    if (dblIn < 0.0)  dblIn = -dblIn ;
    if (dblIn <= LONG_MAX)
        liX = (long)dblIn ;
    else
        return 0L ;
    dbX = dblIn - (double)liX ;
    if (dbX > 0.5) liX++ ;
    return (negFlag == 1) ? liX : -liX ;
}
#pragma warning(default:4244)


/* ========================================================================== */    
/*                                                                            */    
/* Upon entry to loadServerInfo(), a single entry has been added to the       */
/* Server Info Table for the default server.  If there is a valid server info */
/* data file, this function will read it, create entries for all additional   */
/* servers, and fill in the (encoded) password and user for the default       */
/* server if provided.  Then, whether a server info file was processed or not,*/
/* memory will be allocated for every known server for tracking the number of */
/* exception points.                                                          */
/*                                                                            */
/* TRUE is returned if the exception point table was allocated, FALSE if not. */
/*                                                                            */    
/* ========================================================================== */    
int loadServerInfo()
{
    char        buffer[99], c , *pFrom, *pPW ;
    char        scratchPad[3][33] ; 
    int         i, j, n, szPW, fOverwrite ;
    int         readFile=TRUE ;
    char        *p, *filNam ;
    struct      stat sts ;
    FILE        *fp ;
    serverInfo  *pSI ;

    filNam=getenv(G2P_ENV_VAR) ;
    if (filNam == NULL || *filNam == '\0')
        filNam = SRV_DAT_FILE ;
    logMsgs(LLEVDEBUG, "  ", "Server info file: \"%s\"", filNam) ;

    if (stat(filNam, &sts))
    {
        logMsgs(LLEVHIGH, "** ", "Unable to read configuration file \"%s\"", filNam) ;
        readFile = FALSE ;
    }
    if (readFile && (sts.st_mode & S_IFREG) != S_IFREG)
    {
        LOGMSG(LLEVNORM, "Not a valid configuration file.") ;
        readFile = FALSE ;
    }
    if (readFile)
    {
        fp = fopen(filNam, "r") ;
        if (fp == NULL)
        {
            LOGMSG(LLEVNORM, "Unable to open configuration file.") ;
            readFile = FALSE ;
        }
    }

    /* Read next line and break it into segments */
    /* ----------------------------------------- */
    if (readFile)
    {
        while (getNextServerRec(buffer, sizeof(buffer)-1, fp))
        {
            i = j = 0 ;
            scratchPad[0][0] = scratchPad[1][0] = scratchPad[2][0] = '\0';
            pFrom = buffer ;
            while (pFrom < buffer + sizeof(buffer) &&  *pFrom != '\n') 

                if ((c = *pFrom++) == ',')
                    if (i < 2)
                    {
                        scratchPad[i][j] = '\0' ;
                        i++ ;
                        j = 0 ;
                    }
                    else
                        break ;
                else if (j < 32) 
                    scratchPad[i][j++] = (i==0) ? toupper(c) : c ;

            scratchPad[i][j] = '\0' ;

            /*     Compare server name with default server name      */
            /* If the same, fill in default's user name and password */
            /* ----------------------------------------------------- */
            if (gleich(scratchPad[0], gServer->srvrName))
            {
                pSI = gServer ;
                fOverwrite = TRUE ;
            }

            /* See if name is already in table */
            /* ------------------------------- */
            else
            {
                for (i = 0 ; i < gNrServers ; i++)
                    if (gleich(gServer[i].srvrName, scratchPad[0]))
                        break ;
                if (i < gNrServers)
                {
                    fOverwrite = TRUE ;
                    pSI = gServer + i ;
                    logMsgs(LLEVHIGH, "** ", 
                        "More than one entry for \"%s\" in PI Server information file.\n   Using last entry", scratchPad[0]) ;
                }
                else

            /* Allocate another serverInfo structure and fill it in */
            /* ---------------------------------------------------- */
                {
                    fOverwrite = FALSE ;
                    i = gNrServers ;
                    gServer = realloc(gServer, ++gNrServers * sizeof(serverInfo)) ;
                    if (gServer == NULL)
                        goto outAmem ;
                    pSI = gServer + i ;
                    p = malloc(strlen(scratchPad[0])+1) ;
                    if (p == NULL)
                        goto outAmem ;
                    strcpy(p, scratchPad[0]) ;
                    pSI->srvrName = (char *)p ;
                    pSI->fLoggedIn = FALSE ;
                }
            }

            /* Fill in the user name */
            /* --------------------- */
            if (fOverwrite && pSI->fUser)
            {
                free(pSI->user) ;
                pSI->user = NULL ;
            }
            if (strcmp(scratchPad[1],"")==0)
                pSI->fUser = FALSE ;
            else
            {
                p = malloc(strlen(scratchPad[1])+1) ;
                if (p == NULL)
                    goto outAmem ;
                else
                {
                    strcpy(p, scratchPad[1]) ;
                    pSI->user = p ;
                    pSI->fUser = TRUE ;
                }
            }

            /* Special handling is required because the encoded password */
            /* may contain null characters.                              */
            /* --------------------------------------------------------- */
            if (fOverwrite && pSI->fPW)
            {
                free(pSI->password) ;
                pSI->password = NULL ;
            }
            if (strcmp(scratchPad[2],"")==0)
                pSI->fPW = FALSE ;
            else
            {
                if ((szPW = (unsigned char)scratchPad[2][2]) <= 112)
                {
                    szPW -= 32 ;
                    p = (char*)malloc(szPW+1) ;
                    if (p == NULL)
                        goto outAmem ;
                    else
                    {
                        pPW = &scratchPad[2][0] ;
                        pSI->password = p ;
                        pSI->fPW = TRUE ;
                        for (n=0 ; n < szPW ; n++)
                            *p++ = *pPW++ ;
                        *p = '\0' ;
                    }
                }
                else
                {
                    printf("** Invalid server password for %s\n", pSI->srvrName);
                    pSI->fPW = FALSE ;
                }
            }
        }

        fclose(fp) ;
    }
    pNrPIPts = calloc(gNrServers, sizeof(int)) ;
    if (pNrPIPts != NULL)
        return TRUE ;
    printf( "ERROR: Unable to allocate memory for exception reporting\n");
    return FALSE;
outAmem:
    printf("ERROR: Memory allocation error.\n") ;
    return FALSE ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Activate the server that is element dsrSrv of the Server Array.  Log into */
/* it, if necessary.  Return a variable status code of NO_ERR or PIB_BADSRV  */
/* to indicate the success or failure of this operation.                     */
/*                                                                           */
/* ------------------------------------------------------------------------- */
long switchToServer(int dsrSrv)
{
    char    *txtpw ;
    int     piStat ;
    long    rights ;

    piStat = piut_setservernode(gServer[dsrSrv].srvrName) ;
    if (piStat)
    {
        logMsgs(gServer[dsrSrv].errRptd?LLEVMORE:LLEVHIGH, "** ","Unable to connect to server \"%s\".", gServer[dsrSrv].srvrName) ;
        gServer[dsrSrv].errRptd = TRUE ;
        return PIB_BADSRV ;
    }


    /* If we are not logged onto desired server, try to do so */
    /* ------------------------------------------------------ */
    if (!gServer[dsrSrv].fLoggedIn)
    {
        if (gServer[dsrSrv].fUser || gServer[dsrSrv].fPW)
        {
            txtpw = gServer[dsrSrv].fPW   ? decodedPW(gServer[dsrSrv].password) : "" ;
            piStat = piut_login(gServer[dsrSrv].fUser ? gServer[dsrSrv].user     : "",
                                txtpw, &rights) ;
            if (txtpw != NULL) memset(txtpw, 0, strlen(txtpw));
        }
        if (!piStat)
        {
            gServer[dsrSrv].fLoggedIn = TRUE ;
            logMsgs(LLEVNORM, "   ", "Connected to PI server \"%s\"", gServer[dsrSrv].srvrName) ;
        }
        else
        {
            gCurSrvr = -1 ;
            logMsgss(gServer[dsrSrv].errRptd?LLEVMORE:LLEVHIGH, "** ","Unable log onto to server %s as %s.", 
                gServer[dsrSrv].srvrName,
                gServer[dsrSrv].fUser? gServer[dsrSrv].user:"default user") ;
            gServer[dsrSrv].errRptd = TRUE ;
        }
    }
    return piStat ? PIB_BADSRV : NO_ERR ;
}


#define PROV_RSA_FULL          1
#define ALG_SID_RC2            2
#define ALG_SID_RC4            1
#define ALG_SID_MD5            3
#define ENCRYPT_ALGORITHM      CALG_RC4
#define ENCRYPT_BLOCK_SIZE     1

short       fDecOK = false ;
char        strDecPW[81] ;
HCRYPTPROV  hCryptProv ;
HCRYPTKEY   hKey ;
HCRYPTHASH  hHash ;

void initDecode()
{
    char    *ppw ;

    if (!CryptAcquireContext(&hCryptProv,NULL,MS_DEF_PROV,PROV_RSA_FULL,0))
        if (!CryptAcquireContext(&hCryptProv,NULL,MS_DEF_PROV,PROV_RSA_FULL,CRYPT_NEWKEYSET))
            return ;
    if (!CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hHash))
        return ;
    ppw = password() ;
    if (!CryptHashData(hHash,password(),18,0)) 
    {
        zap(ppw) ;
        return ;
    }
    zap(ppw) ;
    if (!CryptDeriveKey(hCryptProv,CALG_RC4,hHash,0,&hKey))
        return ;

    fDecOK = true ;
}

// "832769041-viervoor"
char *password()
{
    char    *retptr = malloc(19) ;
    char    *midtxt = "ervo" ;
    int     prime = 9613 ;
    int     pesch = 13 ;

    if (retptr != NULL)
    {
        sprintf(retptr,"%d%d1-vi%s%s",pesch << 6, prime << 3, midtxt , "or") ;
    }
    return retptr ;
}

void zap(char *ppw)
{
    memset(ppw,0,strlen(ppw)) ;
    free(ppw) ;
}


char *decodedPW(char *decMe)
{
    BOOL            fRes ;
    char            decPW[161], *ps, *pd=decPW ;
    int             iLen, oLen, rLen ;
    unsigned int    il0, il1, il2, il3, magic ;

    /* Initialization */
    /* -------------- */
    memset(strDecPW,0,sizeof(strDecPW)) ;
    initDecode() ;

    /* Make sure the encoded password was passed to this function */
    /* and that the initialization was successful.                */
    /* ---------------------------------------------------------- */
    if (decMe == NULL) return strDecPW ;
    if (!*decMe) return strDecPW ;
    iLen = strlen(decMe) ;      ;
    if (iLen < 5) return strDecPW ;
    if (!fDecOK) return strDecPW ;

    /* Extract encoded length values */
    /* ----------------------------- */
    il0 = (unsigned char)decMe[0] ;
    il0 -= (il0 < (int)'A') ? 33 : ((int)'A' - 10) ;
    il2 = (unsigned char)decMe[1] ;
    il2 -= (il2 < (int)'A') ? 33 : ((int)'A' - 10) ;
    il3 = (unsigned char)decMe[2] - 33 ;
    il1 = (unsigned char)decMe[il3] ;
    il1 -= (il1 < (int)'A') ? 33 : ((int)'A' - 10) ;
    magic = 23 * (23 * il2 + il1) + il0 ;
    rLen = magic % 18 ;
    oLen = (magic - rLen) / 18 ;

    /* Copy the true encoded password to decPW */
    /* --------------------------------------- */
    memset(decPW,0,sizeof(decPW)) ;
    ps = decMe+rLen+3 ;
    if (oLen > 80 || (unsigned)(rLen+oLen+3) != il3)
        return strDecPW ;
    while(pd < decPW+oLen) 
        *pd++ = *ps++ ;

    /* Decipher the password */
    /* -------------------- */
    fRes = CryptDecrypt(hKey, 0, 1, 0, decPW, &oLen) ;
    strncpy(strDecPW,decPW,iLen) ;

    /* Destroy the decifer constants */
    /* ----------------------------- */
    if (hKey)       CryptDestroyKey(hKey) ;
    if (hHash)      CryptDestroyHash(hHash) ;
    if (hCryptProv) CryptReleaseContext(hCryptProv, 0) ;
       
    return strDecPW ;

}

/*======================================================================
    upper_case
      - convert string to uppercase
 *======================================================================*/

char *upper_case ( theStr )
    char    *theStr;
{
  register char   *c;

  if (theStr == (char *)NULL)
    return ((char *)NULL);

  c = theStr;
  while (*c != 0) {
    if (*c >= 'a' && *c <= 'z')
      *c -= 32;
    c++;
  }
  return (theStr);
}

char timestr[15] ;

char *timeToStr(PITIMESTAMP *pts)
{
    sprintf(timestr, "%02d%02d%04d%02d%02d%02d",
            pts->month, pts->day, pts->year,
            pts->hour, pts->minute, (int)(pts->second) ) ;
    return timestr ;
}
