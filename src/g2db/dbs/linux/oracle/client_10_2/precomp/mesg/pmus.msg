/ 
/ $Header: pmus.msg 23-dec-99.02:53:10 akatti Exp $ pmerro.msg 
/ 
/ Copyright (c) 1990, 1995, 1996, 1997, 1998, 1999 by the Oracle Corporation
/
/ NAME
/  <name>
/ CONTENTS
/ NOTES
/ MODIFIED
/    akatti     12/23/99 -  [455879]:add new warn message no. 107
/    akatti     07/13/99 -  [934822]:do no translate msgs from 2000 to 2178
/    akatti     04/17/98 -  change case of all error messages
/    mchiocca   11/19/97 -  [Optima] Move Command Line Names and Values
/    gturk      04/01/96 -  Added error for arrays with where current of
/    gturk      03/14/96 -  Added error msg for arrays with diff modes
/    gturk      02/29/96 -  Added array type names
/    gturk      02/20/96 -  Added errors for arrays
/    gturk      02/15/96 -  Added SQL_CONTEXT
/    gdas       09/13/95 -
/    cracicot   02/14/95 -  rename to pmus.msg from pmerro.msg
/    cracicot   08/18/94 -  error message for cursors in early bind
/    cracicot   07/21/94 -  add some fixed strings
/    cracicot   06/23/94 -  fix merge
/    cracicot   06/06/94 -  add a string for SQL_CURSOR
/    cracicot   05/16/94 -  add c++ support
/    jbasu      02/09/94 -  Change logon to connect, add msg #96.
/    jbasu      02/03/94 -  Add message #95 for invalid data type
/    jbasu      02/02/94 -  Remove COMP5 option, add auto_connect
/    jbasu      12/09/93 -  Remove i/l/s/oreclen
/    jbasu      10/18/93 -  Modify msg #79
/    jbasu      10/14/93 -  Modify msg #80, add comp5 cl option
/    jbasu      08/23/93 -  Fix file names 
/    jbasu      08/17/93 -  Add informational msgs #91, #92 for RPC stubs 
/    rvasired   07/29/93 -  add string 
/    jbasu      07/26/93 -  remove mode and cparams command line options 
/    rvasired   07/20/93 -  add varchar2 
/    rvasired   07/06/93 -  change 77 
/    jbasu      06/30/93 -  eNdLesS 
/    jbasu      06/20/93 -  more NLS 
/    mlozoya    06/16/93 -  add new message #88
/    jbasu      06/11/93 -  more NLS 
/    jbasu      05/19/93 -  Add some fixed strings for NLS 
/    jbasu      04/19/93 -  Add new message #79
/    jbasu      04/05/93 -  Include procedure name in message #50 
/    jbasu      03/19/93 -  Make no logon (#49) a fatal error 
/    jbasu      03/18/93 -  Update message #41 to omit PLS error number
/    cracicot   03/13/93 -  new option 
/    jbasu      02/25/93 -  Add message #77 for missing SQLCODE parameter
/    jbasu      02/09/93 -  add new messages #75, #76 for pl/sql errors
/    cracicot   06/17/92 -  remove binding= option 
/    llao       06/11/92 -  add line# for flaggers (#41)
/    cracicot   06/04/92 -  add some error messages 
/    cracicot   05/18/92 -  add rpc_generate option 
/    jmallory   04/16/92 -  More error messages 
/    jmallory   04/02/92 -  More errors 
/    jmallory   03/23/92 -  Add error for oratype.pas missing 
/    jmallory   03/18/92 -  More error messages 
/    jmallory   03/15/92 -  Add some errors 
/    tolkin     03/02/92 -  add new message 
/    jmallory   01/10/92 -  Add some error-messages for pmt 
/	changed severity of PMEPARUN (50) to 7 from 9
/    cracicot   11/25/91 -  shorten the help strings for the options 
/    cracicot   10/02/91 -  undo temp fix.  Real fix now in place. 
/    cracicot   09/30/91 -  modify the connect failure message 
/    cracicot   09/18/91 -  add some options 
/    cracicot   08/29/91 -  change the command line option strings a bit 
/    cracicot   08/16/91 -         fix a couple default values 
/    tolkin     08/15/91 -         shorter product name 
/    tolkin     05/28/91 -         more msgs 
/    tolkin     05/16/91 -         add .pkb and .pks 
/    tolkin     05/15/91 -         more messages 
/    tolkin     05/13/91 -         new strings for command-line 
/  Olkin      10/10/90 - change name of product
/  Olkin      08/28/90 - changes
/
/	MLC Error Messages.
/
/
1,     15,      "unable to open file %s"
2,     13,      "invalid syntax at column %u in line %u of file %s"
3,     10,      "invalid SQL Identifier at column %u in line %u of file %s"
4,     10,      "unsupported datatype in line %u of file %s"
5,     13,      "invalid include file name at column %u in line %u of file %s"
6,     10,      "invalid host variable at column %u in line %u of file %s"
7,     15,      "unable to open a cursor at line %u in file %s"
8,     15,      "unable to open include file \"%s\" at line %u in file %s"
9,     19,      "unable to open input file \"%s\""
10,    15,      "unable to open listing file \"%s\""
11,    15,      "unable to open output file \"%s\""
12,    13,      "unable to parse statement at line %u in file %s"
13,    12,      "expected \"%s\", but found \"%.15s\" at line %u in file %s"
14,    15,      "unable to obtain bind variables at line %u in file %s"
15,    15,      "Oracle Error: %s"
16,    19,      "out of space - unable to allocate %u bytes"
17,    11,      "unable to connect to Oracle with \"%s:%s/%s\".  Oracle error number: %u"
18,    11,      "unable to disconnect from Oracle"
19,    10,      "indicator variable \"%s\" has wrong type or length at line %u in file %s"
20,    10,      "option \"%s\" not legal as EXEC ORACLE OPTION"
21,    10,      "ambiguous option \"%s\""
22,    10,      "invalid operand \"%s\" for option \"%s\""
23,     9,      "invalid option \"%s\""
24,     9,      "missing operand for option \"%s\""
25,    15,      "unable to create access module"
26,    19,      "no host language specified"
27,    19,      "no input file name specified"
28,    10,      "array host variable is illegal in this SQL statement"
29,    10,      "VARCHAR %s at %u is larger than 65533 line %u in file %s"
30,    10,      "both CURSOR and STATEMENT have AT clauses at line %u of file %s."
31,    10,      "error at line %u, column %u. PLS-%u: %s"
32,    13,      "illegal syntax, PL/SQL not allowed! Found statement at line %u of file %s."
33,     8,      "Ireclen exceeded.  Line %u in file %s truncated."
34,    19,      "insufficient authorization to run %s"
35,     3,      "your %s authorization is about to expire"
36,    19,      "internal programming exception"
37,     8,      "end of SQL statement or PL/SQL block not found"
38,    15,      "module name required when output language is Ada"
39,    19,      "unable to open specifications file \"%s\""
40,    19,      "no output language specified; compilation aborted"
41,     7,      "ANSI violation at line %u, column %u: %s"
42,    10,      "cannot declare cursor \"%s\" more than once"
43,    10,      "cannot declare procedure \"%s\" more than once"
44,    10,      "cannot declare parameter \"%s\" in procedure \"%s\" more than once"
45,    14,      "a character string length of %u is illegal"
46,    14,      "cursor \"%s\" has not been declared"
47,    10,      "an open statement already exists for cursor \"%s\""
48,    14,      "cursor \"%s\" was never opened."
49,    19,      "unable to initialize PL/SQL"
50,     7,      "formal parameter \"%s\" is not used in procedure \"%s\""
51,    10,      "invalid reference mode specified for parameter \"%s\""
52,     7,      "STORE_PACKAGE database does not match connection host"
53,     8,      "duplicate macro definition does not match"
54,    14,      "reference \"%s\" is not a valid cursor reference"
55,    12,      "preprocessor directive is not understood"
56,    10,      "array bound must be greater than 0"
57,    12,      "cannot find macro's argument list"
58,    12,      "wrong number of arguments in macro invocation"
59,     7,      "INTO variable \"%s\" is not listed as a formal parameter"
60,    19,      "PL/SQL error in compiling package specification"
61,    19,      "PL/SQL error in compiling package body"
62,    19,      "host variable for indicator is not recognized"
63,    19,      "procedure %s, parameter %s: illegal interface type \"%s\""
64,    19,      "procedure %s: extra parameter \"%s\" in interface"
65,    19,      "interface definition missing for procedure %s"
66,    19,      "unable to load package \"%s\" from database"
67,    19,      "package name is required but not specified"
68,     3,      "could not find or open system configuration file"
69,    19,      "Oracle error %ld while attempting to store package"
70,    19,      "procedure %s interface is missing declaration for %s"
71,    19,      "PNAME option is required but not set"
72,     3,      "PNAME option is specified but not meaningful"
73,     3,      "INAME option is specified but not meaningful"
74,     3,      "ONAME option is specified but not meaningful"
75,    10,      "error at line %u. PLS-%u: %s"
76,     7,      "ANSI violation at line %u. PLS-%u: %s"
77,    14,      "mandatory status parameter, such as SQLCODE or SQLSTATE,is missing"
78,    19,      "must specify a user if generating stubs from stored package"
79,     3,      "SQLCHECK must be SEMANTICS when RPC=yes"
80,     3,      "error extracting stored package source"
81,    19,      "failed assertion\n"
82,     3,      "[compiling package body...]"
83,     3,      "[package body compiled]"
84,     3,      "[compiling package specification...]"
85,     3,      "[package specification compiled]"
86,    19,      "error: could not install username; aborted...\n"
87,     3,      "[storing package in dB]"
88,     5,      "feature not implemented yet"
89,    10,      "in procedure %s: %s"
90,    10,      "in cursor %s : %s"
91,    10,      "[generating RPC calls to stored package...]"
92,    10,      "[RPC calls generated]"
93,     3,      "SNAME option is specified but not meaningful"
94,     3,      "extension in PNAME option is specified but not meaningful"
95,    14,      "datatype \"%s\" is not valid for this host language."
96,     3,      "LNAME option is specified but not meaningful"
97,    19,      "with-interface must be specified for this host language"
98,    19,      "with-interface may only be defaulted when bind=late"
99,    18,      "type %s is invalid when storing a module, store=yes"
100,   10,      "multiple \"%s\" parameters found in procedure \"%s\""
101,    2,      "array \"%s\" mismatched in \"%s\": minimum size (%ld) used"
102,   14,      "array parameter \"%s\" has both IN and OUT modes in \"%s\""
103,   14,      "array size %ld at line %u is beyond bounds of %ld to %ld."
104,   14,      "array parameters are not supported for this host language"
105,   14,      "procedure \"%s\" has both IN and OUT arrays"
106,   14,      "arrays not allowed with WHERE CURRENT of clause"
107,    7,      "\"%s\" unrecognized interface type,no code generated for \"%s\""

/
/ Command Line HELP Strings
1100,   0,      "should application automatically connect to the database?"
1101,   0,      "bind rpcs at compile (early) or runtime (late)?"
1102,   0,      "the type of C code to be generated"
1103,	0,	"override system configuration file with another"
1104,	0,	"should error messages go into the list file?"
1105,	0,	"shall ANSI noncompliance be flagged?"
1106,	0,	"name of the input file"
1107,	0,	"overrides default list file name"
1108,	0,	"how much data to generate in list file?"
1109,   0,      "how shall database object names be mapped?"
1110,	0,	"maximum length of a generated string literal"
1111,	0,	"name of the output (code) file"
1112,	0,	"which output files are to be generated?"
1113,	0,	"name of the PL/SQL package (input or output)"
1114,   0,      "should rpc calling stubs be generated?"
1115,	0,	"should select errors be flagged?"
1116,	0,	"name of the specifications file"
1117,	0,	"which compile-time checking should be done?"
1118,	0,	"should the package be stored in the database?"
1119,   0,      "a username/password [@dbname] connect string"
1120,   0,      ""
/
/ Beginning of Fixed String Table
// NLS_DO_NOT_TRANSLATE [2000,2178]
2000,	0,	""
2001, 	0,	"void"
2002,	0,	"extern void "
2003,	0,	")"
2004,	0,	"("
2005,	0,	"short"
2006,	0,	"long"
2007,	0,	" "
2008,	0,	"char"
2009,	0,	"[]"
2010,	0,	","
2011,	0,	";"
2012,	0,	":"
2013,	0,	"*"
2014,	0,	"/*_ "
2015,	0,	" _*/"
2016,	0,	"float"
2017,	0,	"."
2018,	0,	"\n"
2019,	0,	"77"
2020,	0,	"PICTURE"
2021,	0,	"SV9(%ld)"
2022,	0,	"SUBROUTINE "
2023,	0,	"USAGE BINARY"
2024,	0,	"DISPLAY SIGN LEADING SEPARATE"
2025,	0,	"{"
2026,	0,	"}"
2027, 	0,	"declare"
2028,	0,	"cursor"
2029,	0,	"package "
2030,	0,	"is"
2031,	0,	"body "
2032,	0,	"with "
2033,	0,	"sql_standard"
2034,	0,	"end"
2035,	0,	"#include <sqlli2.h>"
2036,	0,	"h"
2037,	0,	"DEFINE option is of form: (macro1[,macro2[,...]])"
2038,	0,	"%s is not ANSI standard"
2039,	0,	"VARYING"
2040,	0,	"module"
2041,	0,	"Oracle SQL*Module"
2042,	0,	"Enter your password: "
2043,	0,	"<default>"
2044,	0,	"<none>"
2045,	0,	"Comments are not ANSI standard"
2046,	0,	"Multiple SQL statements is not ANSI"
2047,	0,	"in"
2048,	0,	"in out"
2049,	0,	"out"
2050,	0,	"procedure"
2051,	0,	"begin"
2052,	0,	"        "
2053,	0,	"       "
2054,	0,	"IDENTIFICATION DIVISION.\n"
2055,	0,	"PROGRAM-ID. "
2056,	0,	"DATA DIVISION.\n"
2057,	0,	"LINKAGE SECTION.\n\n"
2058,	0,	"PROCEDURE DIVISION USING "
2059,	0,	"BEGIN-"
2060,	0,	"END PROGRAM "
2061,	0,	"      "
2062,	0,	"var"
2063,	0,	"external"
2064,	0,	".specs"
2065,	0,	".spc"
2066,	0,	"DCL"
2067,	0,	"ENTRY"
2068,	0,	"Not a valid ANSI data type in Ada"
2069,	0,	"Not a valid ANSI data type in C"
2070,	0,	"Not a valid ANSI data type in COBOL"
2071,	0,	"Not a valid ANSI data type in FORTRAN"
2072,	0,	"Not a valid ANSI data type in Pascal"
2073,	0, 	"Not a valid ANSI data type in PL/I"
2074,	0,	"SQLCODE is a deprecated feature of ANSI"
2075,	0,	"SQLROWS is not ANSI standard"
2076,	0,	"SQLERRM is not ANSI standard"
2077,	0,	"pks"
2078,	0,	"lis"
2079,	0,	"using"
2080,	0,	"dbname"
2081,	0,	"Arrays is not ANSI standard"
2082,	0,	"pkb"
2083,	0,	"array"
2084,	0,	"of"
2085,	0,	"OCCURS %ld TIMES"
2086,	0,	"[lob_%ld..hib_%ld]"
2087,	0,	"table"
2088,	0,	"sqlgco("
2089,	0,	"sqlgrp("
2090,	0,	"sqlgec("
2091,	0,	"CALL \"SQLGCO\" USING SQLCODE."
2092,	0,	"CALL \"SQLGRP\" USING SQLROWS."
2093,	0,	"CALL \"SQLGEC\" USING SQLERRM."
2094,	0,	"CALL SQLGCO(SQLCODE)"
2095,	0,	"CALL SQLGRP(SQLROWS)"
2096,	0,	"CALL SQLGEC(SQLERRM)"
2097,	0,	"open "
2098,	0,	"close"
2099,	0,	".mpl"
2100,	0,	".pli"
2101,	0,	"mad"
2102,	0,	"ada"
2103,	0,	"ora_dcl"
2104,	0,	"mco"
2105,	0,	"cob"
2106,	0,	"mc"
2107,	0,	"c"
2108,	0,	"mfo"
2109,	0,	"for"
2110,	0,	".mpa"
2111,	0,	".pas"
2112,	0,	"missing a '-' in comment; assumed present"
2113,	0,	"unknown/illegal character found in source"
2114,	0,	"LANGUAGE clause is required"
2115,	0,	"no mode specified"
2116,	0,	"type"
2117,   0,      "exs"
2118,   0,      " FOR UPDATE "
2119,   0,      "number"
2120,   0,      "char(%ld)"
2121,   0,      "integer"
2122,   0,      "real"
2123,   0,      "smallint"
2124,   0,      "double precision"
2125,   0,      "numeric(%ld,%ld)"
2126,   0,      "numeric(%ld)"
2127,   0,      "decimal(%ld,%ld)"
2128,   0,      "float(%ld)"
2129,   0,      "varchar(%ld)"
2130,   0,      "SQLCODE"
2131,   0,      "sqlrows"
2132,   0,      "sqlerrm"
2133,   0,      "sqlstate"
2134,   0,      "unknown"
2135,   0,      "indicator"
2136,   0,      "\""
2137,   0,      "'"
2138,   0,      " with interface procedure "
2139,   0,      " WHERE ROWID = :JIMES"
2140,   0,      "ROLLBACK_NR"
2141,   0,      "COMMIT"
2142,   0,      "double"
2143,   0,      "/"
2144,   0,      "CREATE OR REPLACE "
2145,   0,      "CHARACTER"
2146,   0,      "numeric"
2147,   0,      "DECIMAL"
2148,   0,      "\t"
2149,   0,      "range"
2150,   0,      "="
2151,   0,      "if"
2152,   0,      "WORKING-STORAGE SECTION.\n"
2153,   0, 	"varchar2"
2154,   0,      "varchar2(%ld)"
2155,   0,      "string"
2156,   0,      "string(%ld)"
2157,   0,      "SQL_CURSOR"
2158,   0,      "mod_func_return"
2159,   0,      "binary_integer"
2160,   0,      "raw"
2161,   0,      "long raw"
2162,   0,      "date"
2163,   0,      "rowid"
2164,   0,      "mlslabel"
2165,   0,      "_ind"
2166,   0,      "boolean"
2167,   0,      "semantics"
2168,   0,      "SQL_CONTEXT"
2169,   0,      "SQL_CONTEXT is not ANSI standard"
2170,   0,      "ARRAY OF is not ANSI standard"
2171,   0,      "ANSI standard requires a SQL server name"
2172,   0,      "sql"
2173,   0,      "_"
2174,   0,      "arr"
2175,   0,      "varchar2"
2176,   0,      "int"
2177,   0,      "double_precision"
2178,   0,      "array (positive range <>) of"
/
/
