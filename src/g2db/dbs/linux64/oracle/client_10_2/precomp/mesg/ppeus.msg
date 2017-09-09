/ 
/ $Header: ppeus.msg 24-nov-96.11:14:56 jnewman Exp $
/ 
/ Copyright (c) 1991, 1995, 1996 by Oracle Corporation 
/   NAME
/     ppeus.msg - <one-line expansion of the name>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    jnewman    11/24/96 -  edit Cause and Action statements
/    mchiocca   11/17/95 -  [Optima] Optimize lookup of punctuation symbols
/    jbasu      06/13/95 -  Rename ppcerr.msg to ppeus.msg
/    gdas       02/23/95 - Added Cause/Action Text
/    mchiocca   03/16/94 -  code=cpp - Error message if C++ token seen
/    jweisz     01/25/94 -  [195561] msg for PERRARGMIS
/    jweisz     01/17/94 -  [194595] msgs for PERRNODEFINE, PERRNOINC
/    jweisz     10/05/93 -  [182822] PERR_HOSTDDL (mesg 205)
/    jweisz     04/01/93 -  Add parser error msg 
/    jweisz     03/23/93 -  [156188] PERRNOSQLINC (mesg 204) 
/    jweisz     10/20/92 -  Add strings exec oracle else, endif
/    jweisz     08/10/92 -  Change sql hint close delimiter
/    pdufour    05/14/92 -  Creation 
/
200,0,	"found unrecognized punctuation sequence"
//    *Cause: The error indicates that the precompiler parser encountered a
//            badly-formed identifier or keyword.
//    *Action: Correct the syntax.
201,0,	"Found syntax error"
//    *Cause: This general message precedes one or more specific messages 
//            that detail the nature of the error.
//    *Action: No action required. Correct the errors diagnosed in the 
//             following message(s).
202,0,	"No typedef name was given"
//    *Cause: The precompiler parser encountered a typedef statement that 
//            had no name after the type specification. For example,
//               typedef int;
//    *Action: Correct the syntax
203,0,	"found end of file when not expected"
//    *Cause: The parser can emit this message when a general syntax error 
//            occurs, for example, an unmatched '{' or '('.
//    *Action: Correct the syntax.
204,0,  "EXEC SQL INCLUDE not permitted from within an included file"
//    *Cause: EXEC SQL INCLUDE statements cannot be nested. Also, EXEC SQL
//            INCLUDE statement cannot be put inside a file that is 
//            included using the #include preprocessor command.
//    *Action: Recode the program so that the nested include statement is not
//             required.
205,0,	"Parser error at line %d, column %d, file %s:\n"
//    *Cause: The precompiler parser encountered a syntax error, either in C
//            code or in SQL code. A more specific message should follow.
//    *Action: No action required for this message. Take the appropriate
//             action for any following messages.
206,0,  "Host variables are not permitted within a DDL statement"
//    *Cause: A Data Definition Language statement cannot use host variables.
//            For example, the statement
//                CREATE TABLE :table_name  (c1 char(10));
//            is illegal, because the name of the table in a CREATE TABLE
//            statement cannot be represented using host variable.
//    *Action: Use dynamic SQL to create the names of database objects (tables,
//             views, columns, etc.) at runtime. See the Programmer's Guide 
//             to the Oracle Precompilers, Release2.2 for information about
//             dynamic SQL.
207,0,  "Invalid macro name"
//    *Cause: The precompiler parser encountered a #define directive that
//            had no macro name associated with it. For example,
//                 #define
//    *Action: Correct the syntax.
208,0,  "No filename specified in #include statement"
//    *Cause: The precompiler parser encountered a #include directive that
//            had no filename associated with it. For example,
//               #include
//    *Action: Specify appropriate filename with the #include directive, or
//             correct the syntax.
209,0,  "Macro invocation has incorrect number of arguments"
//    *Cause: A macro invocation in the source does not have the same number
//            of arguments as the macro definition in the #define line.
//    *Action: Correct the macro reference or the macro definition.
210,0,	"C++ punctuation sequences are not permitted"
//    *Cause: C++ punctuation sequences are not supported by the ProC/C++
//            precompiler.
//    *Action: Rewrite your C++ code without using punctuation sequences
//             and precompile it again.
