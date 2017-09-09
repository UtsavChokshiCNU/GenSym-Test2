#include <winsock2.h>
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include "CmdLine.h"
#include "gsi_main.h"
#include "log.h"
#include "gsi_pi_utils.h"

int dummy ;

cmdLnCmd    cmds[] = {  {'b', cmdBin,  &defMsgBdLog },
                        {'d', cmdSpec, &defLogLev },
                        {'f', cmdBin,  &fwf },
                        {'g', cmdBin,  &defG2ProcLog },
                        {'h', cmdHelp, NULL },
                        {'l', cmdFN,   &LogFileName },
                        {'m', cmdSpec, &maxLogSize },
                        {'n', cmdYNA,  &ofb }, 
                        {'o', cmdBin,  &defScreenLog }, 
                        {'p', cmdBin,  &defPILog },
                        {'s', cmdBin,  &defScreenLog } } ;

#define NRCMDS sizeof(cmds)/sizeof(cmdLnCmd)
int nrCmds = NRCMDS ;

int         nrArgsForGSI = 1 ;
char        *argsForGSI[MAX_NR_GSI_ARGS] = { "g2pi" } ;

/* ===================================================== */
/*                                                       */
/* Process the command line parameters that are intended */
/* to be processed by this bridge (as opposed to by GSI) */
/*                                                       */
/* ===================================================== */
int procCmdLine(int argc, char **argv, int top)
{
    char        c, *p, *pn, *pln[2] ;
    char        cfgFileBuf[MAX_SZ_CFG_FILE+1] ;
    int         i, retCt = 0, nrChars, lineLen ;
    void        *pX ;

    /* retVal is used for the case where procCmdLine is used to process one   */
    /* command from a file.  Since argc will equal 1 in this case, there is   */
    /* no problem that it is being set in a for loop.  The value will tell    */
    /* the caller whether that single command was processed or not.  In all   */
    /* other cases, the return value is ignored.                              */
    /* ---------------------------------------------------------------------- */
    int     retVal=FALSE ;

    for (i = 1 ; i < argc ; i++)
    {
        /* Could this be for us? */
        /* --------------------- */
        c = argv[i][0] ;
        p = argv[i] + 1 ;
        pn = (i+1 < argc) ? argv[i+1] : NULL ;

        /* Perhaps it is an initialization file specification */
        /* -------------------------------------------------- */
        if (top && (c == '@' || c == '$'))
        {
            if (cfgFileLooksGood(p, cfgFileBuf, &nrChars))
            {
                pln[1] = cfgFileBuf ;
                while (moreGoodCfgLines(&pln[1], &lineLen, cfgFileBuf+nrChars))
                {
                    if (!procCmdLine(2, pln, FALSE))
                    {
                        if (nrArgsForGSI >= MAX_NR_GSI_ARGS)
                        {
                            logMsgs(LLEVHIGH, "** ", "Too many configuration parameters. Ignoring %s.",p);
                        }
                        else
                        {
                            argsForGSI[nrArgsForGSI++] = pX = malloc(lineLen+1) ;
                            if (pX == NULL)
                            {
                                LOGMSG(LLEVNORM, "Memory allocation error: Unable to pass command line parameter to GSI");
                                nrArgsForGSI-- ;
                            }
                            else
                            {
                                strncpy(pX, pln[1],lineLen) ;
                                ((char*)pX)[lineLen] = '\0';
                            }
                        }
                    }
                    pln[1] += (lineLen+1) ;
                }
            }
            else
                saveForGSI(argv[i]) ;
        }

        /* Yes - this could be ours.  Check it out */
        /* --------------------------------------- */
        else if (c == '-')
        {
            c = tolower(*(p++)) ;
            retVal = procInitCmd(c, p, pn) ;
            if (!retVal)
                saveForGSI(argv[i]);
            if (retVal == 2) i++ ;

        }
        else
            saveForGSI(argv[i]) ;
    }

    /* Do we need to open the log file? */
    /* -------------------------------- */
    if (top && defFileLog && pLog==NULL)
    {
        if (ofb == APPEND)
            pLog = fopen(LogFileName,"a+") ;
        else 
        {
            if (ofb == FALSE)
                renameLogFile(LogFileName) ;
            pLog = fopen(LogFileName, "w") ;
        }
        if (pLog == NULL)
        {
            defFileLog = FALSE ;
            LOGMSG(LLEVHIGH, "Unable to open log file") ;
        }
    }
    return retVal ;
}



/* ================================================================================== */
/*                                                                                    */
/* Process one individual command.  Most commands will set or clear a flag and will   */
/* be processed by the generic "cmdBin" processing.  For other commands, (D, L, M)    */
/* procSpecial will be called.                                                        */
/*                                                                                    */
/* We pass in a pointer to the next command line parameter in case the parameter      */
/* setting is separated from the parameter by a space.  In this case, we return 2     */
/* instead of TRUE to tell the caller not to process the next command line argument.  */
/*                                                                                    */
/* ================================================================================== */
int procInitCmd(char let, char *p, char *pn)
{
    char        c ;
    int         i, retVal = TRUE ;
    cmdLnCmd    *pNext ;
#define BYPASS  2


    /* If the parameter setting is separated from the parameter by a space,  */
    /* and we are processing commands from the command line, set p to point  */
    /* to the setting (the next command line argument)               .       */
    /* --------------------------------------------------------------------- */
    c = tolower(*p) ;
    if (c == 0 && pn != NULL && *pn != '-')
    {
        c = tolower(*pn) ;
        p = pn ;
        retVal = BYPASS ;
    }

    /* If p is pointing to a space, then we are processing commands from a   */
    /* configuration file.  Advance p to the first not blank character.      */
    /* --------------------------------------------------------------------  */
    else if (c == ' ')
    {
        while (*++p == ' ')
            ;
        c = tolower(*p) ;
    }


    for (i = 0, pNext = cmds ; i < nrCmds ; i++, pNext++)
    {
        /* Do we know this command? */
        /* ------------------------ */
        if (let == pNext->let)

            /* Yes - does it set a true/false, yes/no, or yes/no/append option? */
            /* ---------------------------------------------------------------- */
            if (pNext->type == cmdBin || pNext->type == cmdYNA)
            {
                /* Yes - process it if we can */
                /* -------------------------- */
                if (c == 'y' || c == 't')
                    *((int*)pNext->gVar) = (int)TRUE ;
                else if (c == 'n' || c == 'f')
                    *((int*)pNext->gVar) = (int)FALSE ;
                else if (pNext->type == cmdYNA && c == 'a')
                    *((int*)pNext->gVar) = (int)APPEND ;
                else
                    return FALSE ;
                return retVal ;
            }

            else if (pNext->type == cmdHelp)
            {
                if (retVal==BYPASS) return FALSE ;
                if (gleich(p-1, "help"))
                {
                    printf("  -b<y/n>\t\tlog to message board\n");
                    printf("  -d<y/n,0-9>\t\tset debug log level\n");
                    printf("  -f<y/n>\t\tforce write on log\n");
                    printf("  -g<y/n>\t\tlog to g2 procedure OSI-ERROR\n");
                    printf("  -help\t\t\tdisplay this text\n");
                    printf("  -l <filename>\t\tset log file name\n");
                    printf("  -m<size>\t\tmaximum log size\n");
                    printf("  -n<y/n/a>\t\tlog overwrite/rename/append\n");
                    printf("  -o<y/n>\t\tlog to screen\n");
                    printf("  -p<y/n>\t\tlog to PI log\n");
                    printf("  -s<y/n>\t\tlog to screen\n");
                    printf("  -tcpipexact\t\tfail if desired port not available\n");
                    printf("  -tcpport <portnum>\tdesired connection port number\n");
                }
                exit(0) ;

            }

            /* No - is it the log file name, memory limitation, or debug level? */
            /* ---------------------------------------------------------------- */
            else
                return !procSpecial(let, p, pNext->gVar) ? FALSE : retVal ;
    }
    return FALSE ;
}

/* ================================================================================== */
/*                                                                                    */
/*   Commands that are not setting a binary or tri-state variable are processed here  */
/*                                                                                    */
/* ================================================================================== */
int procSpecial(char let, char *p, void **ppVar)
{
    char        c, *p2=p, hold[5], *pc_temp ;
    int         multiplier = 1, retVal, i, fOK = TRUE ;
    long        lX ;
    struct stat sts ;
    size_t      cmdLen = strlen(p) ;
    FILE        *pTemp = NULL ;


    /* The L command gets the name of a log file, checks its validity, and sets */
    /* the default log-to-file state to true.                                   */
    /* ------------------------------------------------------------------------ */
    if (let == 'l')
    {
        /* Fail if there is no file name */
        /* ----------------------------- */
        if (!cmdLen) return FALSE ;

        /* Before changing the current log-to-file state, make reasonably sure  */
        /* that we will be able to use the new information.  In particular,     */
        /* see if we will be able to create or use the file and if we can       */
        /* allocate memory for the file name.                                   */
        /* -------------------------------------------------------------------- */
        retVal = stat(p, &sts) ;

        /* If the file doesn't exist, try to create it */
        /* ------------------------------------------- */
        if (retVal)
        {
             pTemp = fopen(p,"w") ;
             if (pTemp == NULL)
             {
                 fOK = FALSE ;
                 fprintf (stderr, "Cannot open \"%s\" as a log file.\n", p) ;
             }
        }

        /* If the file already exists, we check to see if it is a regular file. */
        /* If not, we are not going to be able to use this name.  If so, we     */
        /* won't prepare it for logging yet because we need the state of the    */
        /* overwrite flag before we do so.                                      */
        /* -------------------------------------------------------------------- */
        else if ((sts.st_mode & S_IFREG) != S_IFREG)
         {
             fOK = FALSE ;
             fprintf (stderr, "\"%s\" cannot be used as a log file.\n", p) ;
         }

        if (fOK)
        {
            pc_temp = malloc(strlen(p)+1) ;
            if (pc_temp == NULL)
            {
                fprintf(stderr, "Unable to allocate memory for log file name.\n") ;
                fOK = FALSE ;
            }
            else
            {
                strcpy((char*)(pc_temp), p) ;
             }
        }

        if (!fOK)
        {
            if (pTemp != NULL) fclose(pTemp) ;
            return FALSE ;
        }

        /* This is going to work.  Replace any prior info with the new info */
        /* ---------------------------------------------------------------- */
        if (pLog != NULL) fclose(pLog) ;
        pLog = pTemp ;
        if (fNewLog) free(LogFileName) ;
        LogFileName = pc_temp ;
        fNewLog = TRUE ;
        defFileLog = TRUE ;
        return TRUE ;
    }

    /* The M command declares the maximum size of a log file.  A size of 0 means the */
    /* size of the file is only limited by disk space.                               */
    /* ----------------------------------------------------------------------------- */
    else if (let == 'm')
    {
        if (!cmdLen)
        {
            LOGMSG(LLEVNORM,"command line -M<size>: size required") ;
            return FALSE ;
        }
        c = tolower(p[cmdLen-1]) ;
        if (!isdigit(c))
            if (c == 'k')
                multiplier = 1024 ;
            else if (c = 'm')
                multiplier = 1048576 ;
            else
            {
                LOGMSG(LLEVNORM,"command line -M<size>: invalid size code") ;
                return FALSE ;
            }
        while (p2 < p+cmdLen-1)
            if (!isdigit(*(p2++)))
            {
                LOGMSG(LLEVNORM,"-M<size> command line switch with invalid value") ;
                return FALSE ;
            }
        lX = atol(p) ;
        if (lX >=0 && lX < LONG_MAX / multiplier)
        {
            lX *= multiplier ;
            if (lX == 0 || lX >= 1024)
            {
                maxLogSize = lX * multiplier ;
                return TRUE ;
            }
        }
        LOGMSG(LLEVNORM,"-M<size>: size must be 0 or >= 1K (1024)") ;
        return FALSE ;
    }


    /* The D command sets the default log level.  D meant 'debug' in the ver. */
    /* 2 bridge.  Setting it on sets the debug level to 9, setting it off     */
    /* sets it to 3.  The D can also be followed by a number from 0 to 9 or   */
    /* "all" or "most" which are used for debugging under our direction.      */
    /* ---------------------------------------------------------------------- */
    else if (let == 'd')
    {
        if (cmdLen == 1)
            if (isdigit(*p))
            {
                defLogLev = *p - '0' ;
                return TRUE ;
            }
            else
            {
                c = tolower(*p) ;
                if (c == 'y' || c == 't')
                    defLogLev = LLEVDEBUG ;
                else if (c == 'n' || c == 'f')
                    defLogLev = LLEVNORM ;
                else
                {
                    LOGMSG(LLEVNORM,"command line -D<# | y/n>: invalid value");
                    return FALSE ;
                }
                return TRUE ;
            }
        else if (cmdLen == 3 || cmdLen == 4)
        {
            for (i = 0 ; i < (int)cmdLen ; i++)
                hold[i] = *(p2++) ;
            hold[i] = '\0';
            if (!strcmp(hold, "most"))
            {
                defLogLev = LLEVMOST ;
                return TRUE ;
            }
            else if (!strcmp(hold, "all"))
            {
                defLogLev = LLEVALL ;
                return TRUE ;
            }
        }
        LOGMSG(LLEVNORM, "command line -D: invalid value") ;
        return FALSE ;
    }
    return FALSE ;
}


/* ========================================================================= */
/*                                                                           */
/* If the file with the name pointed to by pfn is less than 4096 characters  */
/* long, read its contents into the cfgFileBuf buffer, return in *nrChars    */
/* the number of characters read, and return TRUE.  If the file does not     */
/* exist, if it is longer than 4K, or if we are unable to read its contents, */
/* report the problem and return FALSE.                                      */
/*                                                                           */
/* ========================================================================= */
int cfgFileLooksGood(char *pfn, char *cfgFileBuf, int *nrChars)
{
    char        *p, *pe ;
    int         fd ;
    long        lX ;
    struct stat sts ;
    

    if (stat(pfn, &sts))
    {
        logMsgs(LLEVHIGH, "** ", "Unable to read configuration file \"%s\"", pfn) ;
        return FALSE ;
    }
    if ((sts.st_mode & S_IFREG) != S_IFREG)
    {
        LOGMSG(LLEVNORM, "Not a valid configuration file.") ;
        return FALSE ;
    }
    if ((sts.st_size > MAX_SZ_CFG_FILE))
    {
        LOGMSG(LLEVNORM, "Not a valid configuration file: too large.") ;
        return FALSE ;
    }
    fd = open(pfn, O_RDONLY | O_TEXT) ;
    if (fd < 0)
    {
        LOGMSG(LLEVNORM, "Unable to open configuration file.") ;
        return FALSE ;
    }
    lX = read(fd, cfgFileBuf, MAX_SZ_CFG_FILE+1) ;
    if (lX > MAX_SZ_CFG_FILE)
    {
        LOGMSG(LLEVNORM, "Not a valid configuration file: too large.") ;
        close(fd) ;
        return FALSE ;
    }
    *nrChars = (int)lX ;
    close(fd) ;

    /* Translate all linefeeds to \0 so we can process the lines as strings */
    /* -------------------------------------------------------------------- */
    for (p = cfgFileBuf, pe = cfgFileBuf + *nrChars ; p < pe ; p++)
        if (*p == '\n')
            *p = '\0' ;

    return TRUE ;
}


/* ========================================================================== */
/*                                                                            */
/* This function scans the line pointed to by *ppLineStart looking for a null */
/* character or the end of the buffer.  If the resulting line is between 1    */
/* and 128 characters long, the length is stored in *pLineLen and the         */
/* function returns TRUE.  If not, an error message is logged, *ppLineStart   */
/* is set to the start of the next line and the  function tries again.        */
/*                                                                            */
/* If no valid line is found before reaching the end of the buffer, the       */
/* function returns FALSE.                                                    */
/*                                                                            */
/* ========================================================================== */
int moreGoodCfgLines(char **ppLineStart, int *pLineLen, char *pBeyondRecord)
{
    char    *pwc =*ppLineStart, *pwch = pwc ;
    int     lineLen ;


    while (pwch < pBeyondRecord)
    {
        lineLen = 0 ;
        while (pwc < pBeyondRecord && *pwc++ != '\0')
            lineLen++ ;
        if (lineLen > 0 && lineLen <= MAX_CMD_LEN)
        {
            *ppLineStart = pwch ;
            *pLineLen = lineLen ;
            return TRUE ;
        }
        if (lineLen > MAX_CMD_LEN)
            LOGMSG(LLEVNORM, "Configuration file appears invalid.  Command line too long.");
        pwch += (lineLen+1) ;
    }
    return FALSE ;
}


/* ========================================================================== */
/*                                                                            */
/* Put the unprocessed command in the list of commands to be processed by GSI */
/*                                                                            */
/* ========================================================================== */
void saveForGSI(char *p)
{
    if (nrArgsForGSI >= MAX_NR_GSI_ARGS)
        logMsgs(LLEVHIGH, "** ", "Too many configuration parameters. Ignoring %s.",p);
    else
        argsForGSI[nrArgsForGSI++] = p ;
}
