/
/ $Header: pgpus.msg 11-nov-2002.14:50:19 apopat Exp $
/
/ Copyright (c) 1991, 1995, 1996, 1997, 1998, 1999 by Oracle Corporation
/   NAME
/     pgpus.msg - <one-line expansion of the name>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    apopat     11/11/02 -  [2513269] To allow back-slash in ELIF directive
/    mchiocca   04/09/99 -  [346844] Implement EXEC ORACLE BEGIN directive
/    mchiocca   02/18/98 -  [458658] Handle odd ANSI Stringization cases
/    mchiocca   04/25/97 -  Switch Lexers on ENDIF_TOK to allow #endif <eof>
/    mchiocca   04/20/97 -  Allow '#if .. #endif <eof>' without syntax error
/    mchiocca   03/23/97 -  Add recovery strings for PL/SQL tokens
/    apopat     03/05/97 -  [382795] Allow ident and module as a macro name
/    mchiocca   01/20/97 -  [345010] Accept Preprocessor Merging Operator
/    mchiocca   02/26/96 -  [313298] Allow C++ comments with #include directive
/    mchiocca   11/21/95 -  [320153] Change type of RANDOM_TOK, IMMED_TOK
/    mchiocca   10/30/95 -  [317320] Add optional level to #line directive
/    mchiocca   08/07/95 -  [299268] CREATE <PL/SQL> when PARSE != FULL
/    jbasu      06/13/95 -  Rename pgpmsg.msg to pgpus.msg
/    mchiocca   11/10/94 -  [245158] Handle odd include filenames
/    mchiocca   03/16/94 -  code=cpp - C++ Punctuation, Comments and Hints
/    jweisz     04/26/93 -  Bring up to date 
/    jweisz     12/21/92 -  Added many mesg strings
/    jweisz     10/20/92 -  Adding EXEC_ORA_ELSE_TOK etc
/    jweisz     09/24/92 -  Upgrading to new version of SLAX
/    jweisz     07/26/92 -  Lint
/    pdufour    05/14/92 -  Creation
/
/
/
/ Slax Generated Error Message file for pgpgrm Grammar
/
/
/ Terminals
/
1,0,	"end-of-file"
2,0,	"error"
3,0,	";"
4,0,	"{"
5,0,	"}"
6,0,	","
7,0,	"="
8,0,	":"
9,0,	"("
10,0,	")"
11,0,	"["
12,0,	"]"
13,0,	"*"
14,0,	"?"
15,0,	"|"
16,0,	"&"
17,0,	"<"
18,0,	">"
19,0,	"+"
20,0,	"-"
21,0,	"/"
22,0,	"%"
23,0,	"~"
24,0,	"!"
25,0,	"."
26,0,	"#"
27,0,	"@"
28,0,	"^"
29,0,	"*="
30,0,	"/="
31,0,	"%="
32,0,	"+="
33,0,	"-="
34,0,	"<<="
35,0,	">>="
36,0,	"&&="
37,0,	"||="
38,0,	"^="
39,0,	"~="
40,0,	":="
41,0,	"|"
42,0,	"&"
43,0,	"=="
44,0,	"!="
45,0,	"<="
46,0,	">="
47,0,	"<<"
48,0,	">>"
49,0,	"++"
50,0,	"--"
51,0,	"->"
52,0,	"..."
53,0,	".."
54,0,	"<>"
55,0,	"**"
56,0,	"=>"
57,0,	"##"
58,0,	"an identifier,"
59,0,	"a string,"
60,0,	"a numeric constant,"
61,0,	"newline,"
62,0,	"("
63,0,	"a sql string,"
64,0,	"misc. punctuation,"
65,0,	"newline,"
66,0,	"define,"
67,0,	"elif,"
68,0,	"else,"
69,0,	"endif,"
70,0,	"error,"
71,0,	"if,"
72,0,	"ifdef,"
73,0,	"ifndef,"
74,0,	"include,"
75,0,	"line,"
76,0,	"pragma,"
77,0,	"undef,"
78,0,	"exec,"
79,0,	"sql,"
80,0,	"begin,"
81,0,	"end,"
82,0,	"var,"
83,0,	"type,"
84,0,	"oracle,"
85,0,	"an immediate preprocessor command,"
86,0,	"a C token,"
87,0,	"exec sql,"
88,0,	"exec sql include,"
89,0,	"exec sql var,"
90,0,	"exec sql begin,"
91,0,	"exec sql end,"
92,0,	"end-exec,"
93,0,	"exec sql type,"
94,0,	"exec oracle,"
95,0,	"exec oracle else,"
96,0,	"exec oracle endif,"
97,0,	"exec oracle begin,"
98,0,	"a sql hint,"
99,0,	"create,"
100,0,	"function,"
101,0,	"package,"
102,0,	"procedure,"
103,0,	"trigger,"
104,0,	"or,"
105,0,	"replace,"
106,0,	"a C++ token,"
/
/ Nonterminals
/
1000,0,	"accept grammar"
1001,0,	"identifier"
1002,0,	"source"
1003,0,	"control_line"
1004,0,	"rest_define_prod"
1005,0,	"if_line"
1006,0,	"id_with_args"
1007,0,	"concatenation"
1008,0,	"filename"
1009,0,	"token"
1010,0,	"path_filename"
1011,0,	"opt_else_part"
1012,0,	"concat"
1013,0,	"stringize"
1014,0,	"concat_token"
1015,0,	"sql_filename"
1016,0,	"opt_filename"
1017,0,	"overlap_token"
1018,0,	"control_body"
1019,0,	"rest_include_prod"
1020,0,	"token_sequence"
1021,0,	"elif_parts"
1022,0,	"elif_line"
1023,0,	"id_list"
1024,0,	"file_components"
1025,0,	"const_expr"
1026,0,	"opt_token_sequence"
1027,0,	"token_seq"
1028,0,	"opt_id_list"
1029,0,	"file_component"
1030,0,	"opt_const_"
1031,0,	"punctuation"
1032,0,	"$$15"
1033,0,	"$$17"
1034,0,	"$$19"
1035,0,	"$$22"
1036,0,	"id_list_no_comma"
1037,0,	"$$29"
1038,0,	"$$37"
