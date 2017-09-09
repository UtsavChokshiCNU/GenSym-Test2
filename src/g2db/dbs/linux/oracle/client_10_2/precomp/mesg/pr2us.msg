/ 
/ $Header: pr2us.msg 16-apr-2004.02:21:00 rkoti Exp $
/ 
/ Copyright (c) 1991, 1995, 1996, 1997, 1998, 2000, 2001 by Oracle Corporation 
/   NAME
/     pr2us.msg - General Error Messages.  Command Line Help Messages.
/
/   DESCRIPTION
/     Use pcierr.h when adding new Error Messages to this file.
/
/   RETURNS
/
/   NOTES
/
/   MODIFIED   (MM/DD/YY)
/    rkoti      03/12/04 - [3492512] Add EVENTS = { YES | NO } option.
/    ardesai    08/06/02 - Add help text for native_types command line option.
/    ardesai    09/21/01 - Add Connection Pool Command  Line Options.
/    mkandarp   02/01/01 -  [1607043] Introducing WIN32_THREADS option
/    sylin      08/08/00 -  [UCS2/UTF16] Add utf16_charset help message
/    mchiocca   10/13/98 -  [Optima] Add HEADER option for Precompiled Headers
/    mchiocca   10/06/98 -  [Optima] Implement Stored Persistent Header Files
/    nikeda     05/22/98 -  Add help text for prefetch cmdline option
/    mchiocca   03/10/98 -  [SQL92] Add DYNAMIC and TYPE_CODE Options
/    sylin      12/04/97 -  [556949] Add close_on_commit micro option
/    mchiocca   11/19/97 -  [Optima] Move Command Line Names and Values
/    nikeda     08/05/97 -  Warning when dbms=v6
/    mchiocca   04/15/97 -  [NAV] Add Navigational Command Line Options
/    mchiocca   03/17/97 -  Add some Translation Instructions and Comments
/    erohwedd   11/27/96 -  modify message for UNSAFE_NULL=YES
/    jnewman    11/23/96 -  edit Cause and Action statements
/    jbasu      11/07/96 -  [OBJECTS] Add error for OBJECTS=YES
/    erohwedd   10/28/96 -  [CHAR_MAP] add warning DBMS=V6, CHAR_MAP!=VARCHAR2
/    erohwedd   10/09/96 -  [CHAR_MAP] add objects=yes/no and
/                           char_map=charz/charf/varchar2/string options
/    jbasu      05/25/96 -  [8.0] Add INTYPE and ERRTYPE options
/    mchiocca   03/15/96 -  Eliminate code that handles SQLCHECK=NONE case
/    mchiocca   11/19/95 -  [322693] Allow DBMS=V6_CHAR with UNSAFE_NULL=YES
/    jbasu      11/15/95 -  Codegen NLS - new command-line option COMP_CHARSET
/    jbasu      07/31/95 -  Warning if SQLCHECK=NONE, UNSAFE_NULL cause/action
/    jbasu      06/13/95 -  Rename pccerr.msg to pr2us.msg
/    gdas       04/21/95 -  merge changes from branch 1.20.720.1
/    mchiocca   04/10/95 -  Shorten UNSAFE_NULL messages
/    pthiesen   02/27/95 -  Add UNSAFE_NULL = {YES | NO} option
/    mchiocca   02/09/95 -  Add THREADS = {YES | NO} option
/    gdas       03/03/95 -  Added Cause/Action Text
/    mchiocca   07/26/94 -  NTT MIA - Realphabetize MIA command line options
/    mchiocca   05/23/94 -  merge changes from branch 1.9.710.7
/    mchiocca   05/23/94 -  NTT MIA - Rearrange MIA options
/    mchiocca   04/04/94 -  NTT MIA - nls_char= and nls_local= command-line opt
/    mchiocca   04/02/94 -  NTT MIA - Add host_varchar= option
/    mchiocca   04/02/94 -  NTT MIA - Add def_sqlcode= option
/    mchiocca   03/18/94 -  Message for PERRCPPFULL (parse=full && code=cpp)
/    mchiocca   03/17/94 -  Add cpp_suffix=
/    jweisz     03/16/94 -  Add sys_include=
/    mchiocca   03/14/94 -  Add code=cpp (C++ Code Generation)
/    jweisz     03/08/94 -  add parse= stuff
/    jweisz     02/08/94 -  [196637] err msg for user=
/    jweisz     02/01/94 -  [196099] add asacc
/    mchiocca   01/31/94 -  Align command line descriptions
/    jweisz     12/08/93 -  Add iso, auto_connect
/    jweisz     07/14/93 -  [169815] add v6_char (for dbms=) 
/    jweisz     07/01/93 -  [170401] Delete unnecessary options 
/    mchiocca   04/22/93 -  Syncronize 
/    jweisz     03/25/93 -  Add dbms, pagelen, define 
/    jweisz     02/28/93 -  Adding option TEST
/    jweisz     12/09/92 -  Add list file error
/    jweisz     07/13/92 -  adding options `full`, `limited'  
/    jweisz     06/30/92 -  adding more options 
/    pdufour    05/14/92 -  Creation 
/
/  ==========================================================================
/  TRANSLATION:
/
/      0 -  999: Pro*C/C++ miscellaneous error messages.  These should be
/                translated following standard translation rules and
/                guidelines.
/
/   1100 - 1199: Command Line Option Descriptions.  These are displayed when
/                a user requests to view the command line options.  These may
/                be translated following standard translation guidelines.
/
/  ==========================================================================
/
100,0,	"Unable to initialize PL/SQL"
//    *Cause: The precompiler connected to Oracle but could not invoke the
//            PL/SQL engine. This error can result if an earlier release of
//            Oracle7 is used without the Procedural Option.
//    *Action: To use PL/SQL, upgrade to a more recent release of Oracle7.
101,0,	"Unable to open input file"
//    *Cause: The precompiler could not open the input file. This is the .pc
//            file specified in the INAME=option. This means that the file
//            does not exist, that a directory was incorrectly specified in
//            the pathname, or that the person running the precompiler does
//            not have read permission for the file.
//            This message could also result from operating-system errors.
//            For example, an unmounted file system or disk I/O errors,
//            could trigger this error.
//    *Action: Check that permission to read the file exists and that the full 
//             pathname has been specified correctly. Check for operating-
//             system problems. See also the operating system-specific 
//             Oracle documentation.
102,0,  "Fatal error while doing C preprocessing"
//    *Cause: The precompiler issues this message after a more specific
//            message.
//    *Action: Correct the problem specified in the previous message or 
//             messages.
103,0,	"Password: "
//    *Cause: The username was specified on the command line without a 
//            password. For example,
//                proc sqlcheck=full iname=sample1.pc userid=scott
//    *Action: Re-enter the command line, and include the password or
//             specify the password when prompted.
104,0,	"Unable to connect to Oracle"
//    *Cause: The precompiler could not connect to Oracle with the username,
//            password, and, if applicable, database link that was supplied.
//            Note that this is a precompiler message, not a runtime message.
//            This means that the USERID option value, either on the command
//            line or in a configuration file, was incorrect.
//    *Action: Check that the username and password are current and correct.
//             Run SQL*DBA or SQL*PLUS and verify that connection can be 
//             made using that username and password.
105,0,	"Unable to open list file"
//    *Cause: The precompiler could not open the listing file. This message
//            can result from many causes. For example,
//              o) A pathname for a specified listing file contains a 
//                 non-existent directory.
//              o) An operating-system error occured because the file system
//                 or disk is full.
//              o) Write permission on the specified directory has not been
//                 granted.
//    *Action: Track down the cause of the error, as suggested above, and 
//             correct it.
106,0,	"Userid only used when SQLCHECK = FULL, userid ignored."
//    *Cause: The USERID option was specified on the command line, but SQLCHECK
//            was not equal to FULL or SEMANTICS. The USERID has no effect,
//            unless SQLCHECK=FULL or SQLCHECK=SEMANTICS.
//    *Action: This is a warning message only.
107,0,	"You may not specify PARSE = FULL when CODE = CPP"
//    *Cause: The PARSE=FULL and CODE=CPP options were both specified on the
//            command line. The PARSE=FULL option invokes the C parser which
//            does not understand any C++ constructs generated by the 
//            precompiler with CODE=CPP option.
//    *Action: Set the PARSE option to either NONE or PARTIAL if the
//             CODE=CPP option is specified.
108,0,  "UNSAFE_NULL=YES allowed if MODE=ORACLE and DBMS=V7 or V8"
//    *Cause: UNSAFE_NULL=YES was specified on the command line, but
//            but either the MODE was not ORACLE or the DBMS was not V7 or V8.
//    *Action: Specify MODE=ORACLE and DBMS=V7 or V8 when using
//             UNSAFE_NULL=YES.
109,0,  "SQLCHECK=NONE is no longer supported.. using SYNTAX"
//    *Cause: SQLCHECK=NONE was specified on the command line but is no
//            longer a supported option. SQLCHECK=SYNTAX was used instead.
//    *Action: This is a warning message only.  To avoid this warning, 
//             specify SQLCHECK=SYNTAX or SQLCHECK=SEMANTICS.
110,0,	"DBMS=V6_CHAR is deprecated. Use CHAR_MAP=VARCHAR2, DBMS=V7 instead"
//    *Cause: DBMS=V6_CHAR was specified on the command line but is no longer
//            a supported option. The options CHAR_MAP=VARCHAR2 and
//            DBMS=V7 were used instead.
//    *Action: This is a warning message only.  To avoid this warning, specify
//             CHAR_MAP=VARCHAR2 and, if required, DBMS=V7.
111,0,	"CHAR_MAP option ignored. Only CHAR_MAP=VARCHAR2 allowed for DBMS=V6"
//    *Cause: DBMS=V6 was specified, and CHAR_MAP was specified with a value
//            other than VARCHAR2. The CHAR_MAP value is ignored.
//    *Action: This is a warning message only.  To avoid this warning, specify
//             a DBMS value other than DBMS=V6 or use CHAR_MAP=VARCHAR2.
112,0,  "OBJECTS option ignored. OBJECTS=YES is not allowed for DBMS=V6 or V7."
//    *Cause:  OBJECTS=YES was specified on the Pro*C command line, but the
//             DBMS option value was not valid.
//    *Action: This is a warning message only. To avoid this warning for 
//             OBJECTS=YES, use DBMS=V8 or DBMS=NATIVE with a V8 database.
113,0,  "DBMS=V6 no longer supported; using DBMS=NATIVE, CHAR_MAP=VARCHAR2."
//    *Cause:  DBMS=V6 was specified on the command line, but is no longer a
//             supported option value.  The options DBMS=NATIVE and
//             CHAR_MAP=VARCHAR2 were used instead.
//    *Action: Check your program to verify that you are not depending on
//             any V6 behavior.  Please refer to the Programmer's Guide
//             to the Pro*C/C++ Precompiler for effects of specifying DBMS=V6.
114,0,  "Command line argument MODE=ANSI may not be used with DBMS=V6"
//    *Cause:  The semantics of certain operations (such as character 
//             comparison) in Oracle version ^ are not 100% compliant with 
//             the ANSI/ISO  SQL standards. When V6 semantics are requested, 
//             using the DBMS=V6 or DBMS=V6_CHAR option, precompilation with 
//             MODE=ANSI is not permitted.
//    *Action: Do not use ANSI mode with V6 options.
115,0,  "Unable to open output file for writing"
//    *Cause:  An attempt was made to precompile a header file where the
//             output data file could not be opened (or created) for writing.
//    *Action: Check for appropriate permissions on the directory and possibly
//             file objects (if a data file already exists) to make sure that
//             write permissions have been granted.
116,0,  "You must specify a file extension using the HEADER option"
//    *Cause:  An attempt was made to precompile a header file without
//             specifying the name of the extension to use when creating
//             the generated data file.
//    *Action: Use the HEADER option to specify the name of a file extension
//             to use when creating a data file for a precompiled header.
/
/ Command Line HELP Strings - These may be TRANSLATED.
/
1100,   0,      "Use ASA carriage control formatting"
1101,   0,      "Allow automatic connection to ops$ account"
1102,   0,      "Mapping of character arrays and strings"
1103,   0,      "Close all cursors on COMMIT"
1104,   0,      "CMAX Value for connection pool"
1105,   0,      "CMIN Value for connection pool"
1106,   0,      "CINCR Value for connection pool"
1107,   0,      "CTIMEOUT Value for connection pool"
1108,   0,      "CNOWAIT Value for connection pool"
1109,   0,      "The type of code to be generated"
1110,   0,      "The character set type the C compiler supports"
1111,   0,      "Override system configuration file with another"
1112,   0,      "Support connection pooling"
1113,   0,      "Override the default C++ filename suffix"
1114,   0,      "v6/v7/v8 compatibility mode"
1115,   0,      "Generate '#define SQLCODE sqlca.sqlcode' macro"
1116,   0,      "Define a preprocessor symbol"
1117,   0,      "Set pin duration for objects in the cache"
1118,   0,      "Specify Oracle or ANSI Dynamic SQL Semantics"
1119,   0,      "Whether error messages are sent to the terminal"
1120,   0,      "Name of the list file for intype file errors"
1121,   0,      "Support publish-subscribe event notifications"
1122,   0,      "FIPS flagging of ANSI noncompliant usage"
1123,   0,      "Specify file extension for Precompiled Headers"
1124,   0,      "Control holding of cursors in the cursor cache"
1125,   0,      "The name of the input file"
1126,   0,      "Directory paths for included files"
1127,   0,      "The name of the input file for type information"
1128,   0,      "The record length of the input file"
1129,   0,      "Add #line directives to the generated code"
1130,   0,      "Override default list file name"
1131,   0,      "The record length of the list file"
1132,   0,      "The amount of data generated in the list file"
1133,   0,      "Maximum length of a generated string literal"
1134,   0,      "Maximum number of cached open cursors"
1135,   0,      "Code conformance to Oracle or ANSI rules"
1136,   0,      "Support for native float/double"
1137,   0,      "Specify National Language character variables"
1138,   0,      "Control how NLS character semantics are done"
1139,   0,      "Support object types"
1140,   0,      "The name of the output file"
1141,   0,      "Control the use of the ORACA"
1142,   0,      "The record length of the output file"
1143,   0,      "The page length of the list file"
1144,   0,      "Control which non-SQL code is parsed"
1145,   0,      "Number of rows pre-fetched at cursor OPEN time"
1146,   0,      "Control release of cursors from cursor cache"
1147,   0,      "Control flagging of select errors"
1148,   0,      "Amount of compile-time SQL checking"
1149,   0,      "Directory where system header files are found"
1150,   0,      "Reserved for internal use"
1151,   0,      "Indicates a multi-threaded application"
1152,   0,      "Use Oracle or ANSI type codes for Dynamic SQL"
1153,   0,      "Allow a NULL fetch without indicator variable"
1154,   0,      "A username/password [@dbname] connect string"
1155,   0,      "The character set form used by UTF16 variables"
1156,   0,      "Allow the use of implicit varchar structures"
1157,   0,      "Which version of an object is to be returned"
1158,   0,      "Include a cross-reference in the list file"
1159,   0,      "Support windows default local threading"
1160,   0,      ""
