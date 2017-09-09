/
/ $Header: pcgus.msg 23-feb-00.13:45:43 sylin Exp $
/
/ Copyright (c) 1991, 1996, 1998, 1999, 2000 by Oracle Corporation
/   NAME
/     pcgus.msg - <one-line expansion of the name>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    sylin      02/23/00 -  (598278) rename pci namespace to pcg
/    mchiocca   05/21/99 -  Nav/Col support for DateTime and Interval Types
/    mchiocca   09/30/98 -  [Optima] Implement Stored Persistent Header Files
/    losborne   05/28/98 -  [UCS2] Add UTEXT, UVARCHAR, and LONG_UVARCHAR types
/    mchiocca   03/19/98 -  External Procedures and Threads Context Changes
/    mchiocca   02/17/98 -  Implement Universal Rowid
/    mchiocca   12/04/96 -  [OBJECT] Drop Ociref as an OTS type
/    mchiocca   10/16/96 -  [OBJECT] Implement FILE LOBs
/    mchiocca   10/07/96 -  [OBJECT] Add new OTS type 'orldat'
/    mchiocca   03/30/96 -  [354162] Handle #lint, #machine in a #if directive
/    mchiocca   05/27/96 -  [OBJECT] Support for OTS types and ADT Free
/    jbasu      06/13/95 -  Rename pcimsg.msg to pcius.msg
/    mchiocca   02/09/95 -  Add SQL_CONTEXT Thread context type spec
/    mchiocca   08/10/94 -  [230347] #if directive parse error messages
/    mchiocca   06/14/94 -  Implement Result Sets
/    mchiocca   02/07/94 -  Bring up to date
/    jweisz     09/24/92 -  Upgrading to new version of SLAX
/    pdufour    05/14/92 -  Creation
/
/
/
/ Slax Generated Error Message file for pcgifg Grammar
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
29,0,	"TIMES_EQ_"
30,0,	"DIVIDE_EQ_"
31,0,	"MOD_EQ_"
32,0,	"PLUS_EQ_"
33,0,	"MINUS_EQ_"
34,0,	"SHFL_EQ_"
35,0,	"SHFR_EQ_"
36,0,	"AND_EQ_"
37,0,	"OR_EQ_"
38,0,	"XOR_EQ_"
39,0,	"TILDA_EQ_"
40,0,	"COLON_EQ_"
41,0,	"||"
42,0,	"&&"
43,0,	"=="
44,0,	"!="
45,0,	"<="
46,0,	">="
47,0,	"<<"
48,0,	">>"
49,0,	"INC_"
50,0,	"DEC_"
51,0,	"POINTS_"
52,0,	"ETC_"
53,0,	"DBLDOT_"
54,0,	"ANGLE_BRK_"
55,0,	"DBLSTAR_"
56,0,	"ARROW_"
57,0,	"AUTO_"
58,0,	"BREAK_"
59,0,	"CASE_"
60,0,	"CHAR_"
61,0,	"CONST_"
62,0,	"CONTINUE_"
63,0,	"DEFAULT_"
64,0,	"defined,"
65,0,	"DO_"
66,0,	"DOUBLE_"
67,0,	"ELSE_"
68,0,	"ENUM_"
69,0,	"EXTERN_"
70,0,	"FLOAT_"
71,0,	"FOR_"
72,0,	"GOTO_"
73,0,	"IF_"
74,0,	"INT_"
75,0,	"LONG_"
76,0,	"LONG_UVARCHAR_"
77,0,	"OCIBFILEL_"
78,0,	"OCIBLOBL_"
79,0,	"OCICLOBL_"
80,0,	"OCIDATETIME_"
81,0,	"OCIEXTPROCCONTEXT_"
82,0,	"OCIINTERVAL_"
83,0,	"OCIROWID_"
84,0,	"ORLDAT_"
85,0,	"ORLNUM_"
86,0,	"ORLRAW_"
87,0,	"ORLVSTR_"
88,0,	"REGISTER_"
89,0,	"RETURN_"
90,0,	"SHORT_"
91,0,	"SIGNED_"
92,0,	"SIZEOF_"
93,0,	"SQL_CONTEXT_"
94,0,	"SQL_CURSOR_"
95,0,	"STATIC_"
96,0,	"STRUCT_"
97,0,	"SWITCH_"
98,0,	"TYPEDEF_"
99,0,	"UNION_"
100,0,	"UNSIGNED_"
101,0,	"UTEXT_"
102,0,	"UVARCHAR_"
103,0,	"VARCHAR_"
104,0,	"VOID_"
105,0,	"VOLATILE_"
106,0,	"WHILE_"
107,0,	"an identifier,"
108,0,	"typedef__name"
109,0,	"header__file"
110,0,	"string"
111,0,	"a numeric constant,"
/
/ Nonterminals
/
1000,0,	"accept grammar"
1001,0,	"const__expr"
1002,0,	"logical__OR__expr"
1003,0,	"logical__AND__expr"
1004,0,	"inclusive__OR__expr"
1005,0,	"exclusive__OR__expr"
1006,0,	"AND__expr"
1007,0,	"equality__op"
1008,0,	"equality__expr"
1009,0,	"relational__expr"
1010,0,	"shift__expr"
1011,0,	"additive__expr"
1012,0,	"multiplicative__expr"
1013,0,	"unary__expr"
1014,0,	"defined__kw"
1015,0,	"postfix__expr"
1016,0,	"primary__expr"
1017,0,	"relational__op"
1018,0,	"unary__operator"
1019,0,	"shift__op"
1020,0,	"additive__op"
1021,0,	"multiplicative__op"
1022,0,	"defined__expr"
