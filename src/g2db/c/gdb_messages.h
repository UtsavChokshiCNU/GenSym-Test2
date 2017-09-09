/*================================================================
 *  GDB_MESSAGES.H                                        [header]
 *================================================================
 *   This module contains GDB message information.
 *================================================================*/

#ifndef GDB_MESSAGES_H
#define GDB_MESSAGES_H

/*-----------------------
    macros
  -----------------------*/

#define IN_RANGE(val,low,hi) ((val >= low && val <= hi) ? 1 : 0) 

/*-----------------------
    defines
  -----------------------*/

#define  MAX_CONTEXT_NAME_LEN     15L
#define  GDB_MSG_BASE           9000L  /* Added to every msg number (+/-) */
#define  MAX_MSGS                100L
#define  MAX_SUBS                 10L  /* max # of substitutions into msg string */
#define  MAX_SUB_LEN              20L  /* max length of substitution string */
#define  MAX_STATUS_LEN           12L  /* max length of the status symbol */
#define  MSG_DELIM                '%'
#define  STATUS_MSG_LEN          512L  /* at least PREFIX_SZ + MSG_SZ */
#define  MSG_SZ                  256L  /* must NOT exceed STATUS_MSG_LEN - was 128 */  
#define  PREFIX_SZ               DB_TYPE_LEN+MAX_CONTEXT_NAME_LEN+STAT_SYM_LEN+4  /* approx 42 */

#define  SUCCESS_CD                0L
#define  ERROR_CD                 -1L
#define  FATAL_CD                 -2L
#define  WARN_CD                   1L
#define  INFO_CD                   2L
#define  EOCURSOR_CD          999999L
#define  NOCONNECT_CD        -888888L


#define  SUCC_SYM           _T("SUCCESS")
#define  WARN_SYM           _T("WARNING")
#define  ERROR_SYM          _T("ERROR")
#define  INFO_SYM           _T("INFO")
#define  FATAL_SYM          _T("FATAL")
#define  INV_SYM            _T("INVALID")
#define  EOCURSOR_SYM       _T("EOCURSOR")
#define  NOCONNECT_SYM      _T("DISCONNECTED")
#define  GDB_UNKNOWN        _T("UNKNOWN")

#define  STAT_SYM_LEN             12L

/*==========================================================
                      INFORMATIONAL
 ==========================================================*/

/*----------------------------
    informational      ( 0-99)
 -----------------------------*/
#define NULL_MSG           0L
#define IEOFETC            1L
#define IDBCONA            2L
#define IDBCONE            3L
#define IDBDISC            4L
#define IBRTERM            5L
#define ILOGOPN            6L
#define ILOGCLO            7L
#define ILOGROP            8L
#define ILOGCLP            9L
#define ILOGOPR           10L
#define IADBREC           11L
#define ISHUTCX           12L
#define ICALLMD           13L
#define IDSNADD           14L
#define IDSNMOD           15L
#define IDSNDEL           16L

#define MIN_MSG_INFO       0L
#define MAX_MSG_INFO      16L
#define NUM_MSG_INFO      MAX_MSG_INFO - MIN_MSG_INFO + 1

static GDB_CHAR MSG_INFO[NUM_MSG_INFO][MSG_SZ] =
  {
   /* 0*/ _T("\0"),
   /* 1*/ _T("END_OF_CURSOR: Last record has been reached.\0"),
   /* 2*/ _T("Database connection ALREADY established.\0"),
   /* 3*/ _T("Database connection established.\0"),
   /* 4*/ _T("Database connection terminated for context (%) %.\0"),
   /* 5*/ _T("Bridge shutdown by user\0"),
   /* 6*/ _T("Logfile '%' has been OPENED.\0"),
   /* 7*/ _T("Logfile '%' has been CLOSED.\0"),
   /* 8*/ _T("Logfile '%' has been RE-OPENED.\0"),
   /* 9*/ _T("Logfile '%' has been closed via 'PAUSE'.\0"),
   /*10*/ _T("Logfile '%' has been opened via 'RESUME'.\0"),
   /*11*/ _T("Attempting to re-connect to database.\0"),
   /*12*/ _T("Shutting down % (%).\0"),
   /*13*/ _T("Callback '%' has been redefined to '%'.\0"),
   /*14*/ _T("Created % DSN \"%\".\0"),
   /*15*/ _T("Modified % DSN \"%\".\0"),
   /*16*/ _T("Deleted % DSN \"%\".\0")
  };


/*==========================================================
                          WARNING
 ==========================================================*/

/*----------------------------
    warnings          (100-299)
 -----------------------------*/
#define WTYPCHG          100L
#define WILLSET          101L
#define WWRNCAT          102L
#define WDBRECN          103L
#define WTYPCDF          104L
#define WCTRUNC          105L
#define WALCONF          106L
#define WNOTEOC          107L


#define MIN_MSG_WARN     100L
#define MAX_MSG_WARN     107L
#define NUM_MSG_WARN     MAX_MSG_WARN - MIN_MSG_WARN + 1

static GDB_CHAR MSG_WARN[NUM_MSG_WARN][MSG_SZ] =
  {
   /*100*/_T("Datatype of % has been changed from % to %.\0"),
   /*101*/_T("Illegal SET operation performed on a query object.\0"),
   /*102*/_T("Could not concat warning message to status message.\0"),
   /*103*/_T("Database connection was broken and has been re-established.\0"),
   /*104*/_T("Datatype of return value has changed, see logfile for details.\0"),
   /*105*/_T("Supplied context name is too long and has been truncated.\0"),
   /*106*/_T("Context has already been configured.\0"),
   /*107*/_T("END_OF_CURSOR has NOT been reached.\0")
  };
                          
/*==========================================================
                          ERROR
 ==========================================================*/

/*----------------------------
    errors             (1-199)
 -----------------------------*/
#define EINVSQL            1L
#define EINVFCT            2L
#define ENOGENP            3L
#define EBADIND            4L
#define ENOHNDL            5L
#define EFETDAT            6L
#define EINVQUR            7L
#define ECURSEX            8L
#define ENCOLEX            9L
#define EINITFL           10L
#define ENODBCT           11L
#define EINSMEM           12L
#define EARGNUM           13L
#define EINVDTY           14L
#define EINVARG           15L
#define EBADSEQ           16L
#define ESQLPRO           17L
#define ENONSEL           18L
#define ENOCONS           19L
#define EINMEMR           20L
#define EINVSEL           21L
#define EINVHDL           22L
#define ENOUSER           23L
#define ENOPASS           24L
#define EINVCST           25L
#define EBADCON           26L
#define EINMEMM           27L
#define EININST           28L
#define ENOMCTX           29L
#define ELOGOPN           30L
#define ELOGCLO           31L
#define ENOERMG           32L
#define ENOSTRA           33L
#define ENOLOGN           34L
#define ELOGWRI           35L
#define ENOSERV           36L
#define EALDESC           37L
#define EDBRECN           38L
#define ECONUNA           39L
#define ENOSUPS           40L
#define EOPNSUP           41L
#define EINITFA           42L
#define EALCONF           43L
#define ECONACT           44L
#define EINCHAR           45L
#define EBADTLN           46L
#define EESTCON           47L
#define ENOINPT           48L
#define ENUMVAL           49L
#define ENOTINI           50L
#define EWRNGKB           51L
#define EEXREGI           52L
#define ESQLBDP           53L
#define EUNEXDA           54L
#define EINMAXL           55L
#define EMAXCTX           56L
#define EINVITM           57L
#define EBNDLEN           58L
#define ENOATTR           59L
#define ENOBIND           60L
#define EBADOBJ           61L
#define EBADDTP           62L
#define EINCDTP           63L
#define EBADCNM           64L
#define EBINDEX           65L
#define ERESUSE           66L
#define EREFCUR           67L
#define EBVEXLN           68L
#define EINVCBS           69L
#define EUNSPDT           70L
#define EDTBVWF           71L
#define EMBVEXD           72L
#define ESNUSDS           73L
#define EDSNOPT           74L
#define EDSNDRV           75L
#define EDSNKVS           76L
#define ENODSNS           77L
#define EDSNTYP           78L
#define EDSNEST           79L
#define EDSNMUL           80L
#define ESLEXRQ           81L
#define EINTOVF           82L
#define EBADATY           83L
#define ERATYEF           84L
#define EINCRAT           85L
#define ENOCOLS           86L
#define EQINCOL           87L
#define ESCONAT           88L

#define MIN_MSG_ERROR      0L
#define MAX_MSG_ERROR     88L
#define NUM_MSG_ERROR     MAX_MSG_ERROR - MIN_MSG_ERROR + 1


static GDB_CHAR MSG_ERROR[NUM_MSG_ERROR][MSG_SZ] =
  {
   /* 0*/_T("\0"),
   /* 1*/_T("Invalid or NULL query statement.\0"),
   /* 2*/_T("Invalid function call or query statement.\0"),
   /* 3*/_T("Object has not been properly initialized.\0"),
   /* 4*/_T("Invalid object handle.\0"),
   /* 5*/_T("No statement handles available. MAX_CURSORS exceeded.\0"),
   /* 6*/_T("Problems fetching or processing data.\0"),
   /* 7*/_T("Could not process query statement.\0"),
   /* 8*/_T("Maximum cursors exceeded.\0"),
   /* 9*/_T("Number of query columns % exceeds -MAXCOLS %.\0"),
   /*10*/_T("Parameter initialization failed.\0"),
   /*11*/_T("Database connection broken or not established.\0"),
   /*12*/_T("Insufficient memory available for allocation.\0"),
   /*13*/_T("Invalid or wrong number of arguments supplied to remote procedure.\0"),
   /*14*/_T("Unsupported datatype encountered: DB=% Col=%.\0"),
   /*15*/_T("Invalid or wrong number of arguments supplied to internal function.\0"),
   /*16*/_T("Programmatic flow is out-of-sequence.\0"),
   /*17*/_T("SQL statement has not been processed.\0"),
   /*18*/_T("Non-select is unsupported for this operation.\0"),
   /*19*/_T("No database connect string specified.\0"),
   /*20*/_T("Insufficient memory available for reallocation.\0"),
   /*21*/_T("Non-queries may not contain *select*.\0"),
   /*22*/_T("Invalid statement handle specified.\0"),
   /*23*/_T("Database username not specified.\0"),
   /*24*/_T("Database password not specified.\0"),
   /*25*/_T("Invalid database connect string specified.\0"),
   /*26*/_T("Could not connect to database.\0"),
   /*27*/_T("Insufficient memory available for messages.\0"),
   /*28*/_T("Invalid or NULL initialization string.\0"),
   /*29*/_T("Multiple bridge connections are not supported.\0"),
   /*30*/_T("Logfile '%' could not be opened.\0"),
   /*31*/_T("Logfile '%' could not be closed.\0"),
   /*32*/_T("Unable to generate error message.\0"),
   /*33*/_T("A data structure has not been allocated.\0"),
   /*34*/_T("No filename specified for logfile.\0"),
   /*35*/_T("Error writing to logfile.\0"),
   /*36*/_T("Database server not specified.\0"),
   /*37*/_T("Could not allocate descriptor.\0"),
   /*38*/_T("Database connection has broken and can not be re-established.\0"),
   /*39*/_T("Context is currently not available for transactions.\0"),
   /*40*/_T("This operation is not supported from within a SELECT statement.\0"),
   /*41*/_T("This operation is currently not supported.\0"),
   /*42*/_T("Context initialization has failed.\0"),
   /*43*/_T("Context has already been configured.\0"),
   /*44*/_T("Context is no longer active.\0"),
   /*45*/_T("Invalid character set specified: %.\0"),
   /*46*/_T("Unable to perform character set translation.\0"),
   /*47*/_T("Unable to connect to database, please restart bridge process.\0"),
   /*48*/_T("Dynamic SQL 'bind' variable values/names are invalid or have not been specified.\0"),
   /*49*/_T("Number of bind values supplied % not equal to the number expected %.\0"),
   /*50*/_T("Dynamic query statement has not been initialized.\0"),
   /*51*/_T("This bridge is incompatible with KB version %. KB version % is required.\0"),
   /*52*/_T("Number of registered items exceeds limit of %.\0"),
   /*53*/_T("SQL statement or bind variables have not been processed.\0"),
   /*54*/_T("Unexpected datatype % for RPC argument % encountered.\0"),
   /*55*/_T("Supplied bind variable exceeds maximum length of % characters.\0"),
   /*56*/_T("Maximum number of contexts % has been exceeded. Context initialization rejected.\0"),
   /*57*/_T("Invalid or NULL % specified.\0"),
   /*58*/_T("Dynamic SQL object bind arrays/lists are not of the same length.\0"),
   /*59*/_T("Attribute '%' does not exist or contains no data elements for object '%'.\0"),
   /*60*/_T("Bind variables have not been processed.\0"),
   /*61*/_T("Invalid object received. Object must be a %.\0"),
   /*62*/_T("Invalid datatype % encountered for attribute %. Attributes must be 'simple' datatypes.\0"),
   /*63*/_T("Incompatible datatypes between bind variable % and database column.\0"),
   /*64*/_T("Unrecognized column name encountered: %\0"),
   /*65*/_T("Number of bind values supplied exceeds number expected %.\0"),
   /*66*/_T("RESERVED\0"),
   /*67*/_T("Unable to refresh cursor, cursor has not been defined.\0"),
   /*68*/_T("Length of bind value '%' is % which exceeds database limit of % characters.\0"),
   /*69*/_T("Invalid callback specified '%'.\0"),
   /*70*/_T("Unsupported datatype % encountered for attribute %.\0"),
   /*71*/_T("DATE bind variables must be in the following format: 'DD-MMM-YYYY hh:mm:ss.cc'.\0"),
   /*72*/_T("Number of bind variables % exceeds maximum %.\0"),
   /*73*/_T("Set null string option disabled.  Set null string not specified.\0"),
   /*74*/_T("Invalid DSN configuration option.\0"),
   /*75*/_T("Invalid DSN driver name.\0"),
   /*76*/_T("Missing DSN key/value structure.\0"),
   /*77*/_T("Configuration of DSNs not supported by the % bridge.\0"),
   /*78*/_T("DSN configuration parameter of invalid type.\0"),
   /*79*/_T("DSN key/value structure is empty.\0"),
   /*80*/_T("DSN name defined more than once.\0"),
   /*81*/_T("SELECT or EXEC is required.\0"),
   /*82*/_T("Integer overflow.\0"),
   /*83*/_T("Attribute type incompatible with value of %.\0"),
   /*84*/_T("Record attributes type evaluation failed.\0"),
   /*85*/_T("Cannot translate % to % data type.\0"),
   /*86*/_T("Query does not return any columns.\0"),
   /*87*/_T("No array or list in query item for %.\0"),
   /*88*/_T("Can't set connection's attribute.\0")
  };

#endif
