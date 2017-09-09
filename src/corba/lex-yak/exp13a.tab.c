
/*  A Bison parser, made from exp13a.y  */

#define	xANY	258
#define	xATTRIBUTE	259
#define	xBOOLEAN	260
#define	xCASE	261
#define	xCHAR	262
#define	xCONST	263
#define	xCONTEXT	264
#define	xDEFAULT	265
#define	xDOUBLE	266
#define	xENUM	267
#define	xEXCEPTION	268
#define	xFALSE	269
#define	xFLOAT	270
#define	xIN	271
#define	xINOUT	272
#define	xINTERFACE	273
#define	xLONG	274
#define	xMODULE	275
#define	xOBJECT	276
#define	xOCTET	277
#define	xONEWAY	278
#define	xOUT	279
#define	xRAISES	280
#define	xREADONLY	281
#define	xSEQUENCE	282
#define	xSHORT	283
#define	xSTRING	284
#define	xSTRUCT	285
#define	xSWITCH	286
#define	xTRUE	287
#define	xTYPEDEF	288
#define	xUNSIGNED	289
#define	xUNION	290
#define	xVOID	291
#define	OPERATOR	292
#define	PUNCTUATOR	293
#define	LITERAL	294
#define	IDENTIFIER	295
#define	KEYWORD	296
#define	LITERAL_DECINT	297
#define	LITERAL_HEXINT	298
#define	LITERAL_OCTINT	299
#define	LITERAL_FP	300
#define	LITERAL_CHAR	301
#define	LITERAL_CHARHEX	302
#define	LITERAL_CHAROCT	303
#define	LITERAL_STRING	304
#define	DOUBLE_COLON	305
#define	DOUBLE_LT	306
#define	DOUBLE_GT	307
#define	FLOATING_PT_LITERAL	308
#define	CHARACTER_LITERAL	309
#define	STRING_LITERAL	310
#define	INTEGER_LITERAL	311
#define	xIDENTIFIER	312
#define	NEG	313



/*
C declarations
The C declarations may define types and variables used in the actions. You can also use 
preprocessor commands to define macros used there, and use #include to include header files 
that do any of these things.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "yacc_supp.h"

extern int yylex();
extern int parser_error_handler();
extern void *buildAttr_Dcl();
extern void *buildInterface_Body();
extern void addExport();
extern void *buildInterface_Header();
extern void *buildInterface_Dcl();
extern void *buildSpecification();
extern void addDefinition();
extern int  applyUnaryOperator();
extern void setUnaryOperator(); 
extern void loadParseTreeRoot();
extern void *buildOp_Type_Spec1();
extern void *buildOp_Type_Spec2();
extern void *buildParam_Dcl();
extern void *buildOp_Dcl();
extern void *buildBase_Type_Spec();
extern void *buildSimple_Declarator();
extern void *buildMember();
extern void *buildStruct_Type();
extern void *buildScoped_Name();
extern void *buildEnum_Type();
extern void *buildContext_Expr();
extern void *buildInheritance_Spec();
extern void *buildLongIntegerLiteral();
extern void *buildStringLiteral();
extern void *buildCharLiteral();
extern void *buildDoubleLiteral();
extern void *buildBooleanLiteral();
extern void *buildRaises_Expr();
extern void *buildExcept_Dcl();
extern void *buildConst_Type1();
extern void *buildConst_Type2();
extern void *buildConst_Dcl();
extern void *buildString_Type();
extern void *buildSwitch_Type_Spec1();
extern void *buildSwitch_Type_Spec2();
extern void *buildElement_Spec();
extern void *buildCase_Label();
extern void *buildCase();
extern void *buildArray_Declarator();
extern void *buildUnion_Type();
extern void *buildSequence_Type();
extern void *buildType_Declarator();
extern void *buildType_Dcl_Case1();
extern void *buildForward_Dcl();
extern void *buildModule();
extern void *buildMath_Expression();


/*****Global Data for use by the Production Rules*****/
/* These values are all declared 'static' to set internal linkage, thus preventing their access from 
 * outside of this file. */
/* For: attr_dcl */
static	void	**attr_dcl_array;
static	int		attr_dcl_count;
static	int		attr_dcl_array_limit;

/* For: declarators */
static	void	**declarator_array;
static	int		declarator_count;
static	int		declarator_array_limit;

/* For: fixed_array_size */
static	void	**fixed_array_size_array;
static	int		fixed_array_size_count;
static	int		fixed_array_size_array_limit;

/* For: case_label */
static	void	**case_label_array;
static	int		case_label_count;
static	int		case_label_array_limit;

/* For: switch_body */
static	void	**switch_body_array;
static	int		switch_body_count;
static	int		switch_body_array_limit;

/* For: member */
static	void	**member_array;
static	int		member_count;
static	int		member_array_limit;

/* For: enumerator */
static	char	**enumerator_array;
static	int		enumerator_count;
static	int		enumerator_array_limit;

/* For: module - definition */
static	void	**module_definition_array;
static	int		module_definition_count;
static	int		module_definition_array_limit;

/* For: scoped_name_list (internal, per scoped_name object) */
static	char	**scoped_name_list_array;
static	int		scoped_name_list_count;
static	int		scoped_name_list_array_limit;

/* For: scoped_name (external, an array of scoped_name objects) */
static	void	**scoped_name_array;
static	int		scoped_name_count;
static	int		scoped_name_array_limit;

/* For: op_dcl */
static	void	**param_dcl_array;
static	int		param_dcl_count;
static	int		param_dcl_array_limit;

/* For: context_expr */
static	void	**string_literal_array;
static	int		string_literal_count;
static	int		string_literal_array_limit;

/*****End: Global Data for use by the Production Rules*****/


/*****Miscellaneous Global Data******/
int		scoped_name_scope_flag;


/*****Forward Declarations*****/
int reset_char_array();
int reset_void_array();


typedef union 
	{
	void			*void_ptr;
	char			*str_lit;		
	int				int_val;		
	int				tok_val;
	float			flt_val;
	double			dbl_val;
	char			chr_val;
	unsigned long	ulng_val;
	long			lng_val;
	short			shrt_val;
	double			val;
	} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __STDC__
#define const
#endif



#define	YYFINAL		286
#define	YYFLAG		-32768
#define	YYNTBASE	80

#define YYTRANSLATE(x) ((unsigned)(x) <= 313 ? yytranslate[x] : 166)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    66,    61,     2,    74,
    75,    64,    63,    72,    62,     2,    65,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    71,    68,    76,
    58,    77,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    78,     2,    79,    60,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    69,    59,    70,    73,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    67
};

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   218,   230,   240,   241,   242,   243,   244,   248,   263,   264,
   268,   269,   272,   279,   284,   287,   292,   293,   316,   317,
   318,   319,   320,   324,   333,   343,   355,   364,   373,   379,
   383,   386,   389,   392,   395,   398,   405,   408,   409,   414,
   415,   420,   421,   426,   427,   433,   442,   443,   446,   450,
   451,   454,   457,   462,   466,   469,   470,   471,   474,   477,
   480,   487,   490,   493,   496,   499,   504,   505,   508,   511,
   514,   515,   516,   519,   528,   529,   532,   535,   538,   543,
   546,   549,   552,   555,   558,   565,   570,   571,   574,   575,
   576,   579,   582,   583,   586,   587,   590,   595,   598,   599,
   602,   603,   606,   607,   609,   612,   615,   616,   619,   629,
   639,   642,   645,   648,   652,   656,   665,   666,   670,   682,
   693,   696,   699,   702,   705,   712,   713,   716,   725,   726,
   729,   732,   737,   742,   754,   755,   758,   761,   764,   769,
   772,   777,   788,   789,   792,   796,   807,   820,   821,   833,
   838,   847,   856,   864,   872,   880,   889,   898,   907,   917,
   920,   923,   928,   932,   941,   942,   945,   960,   961,   962,
   965,   973,   983,   995,  1004,  1011,  1020,  1023,  1026
};

static const char * const yytname[] = {     0,
"error","$illegal.","xANY","xATTRIBUTE","xBOOLEAN","xCASE","xCHAR","xCONST","xCONTEXT","xDEFAULT",
"xDOUBLE","xENUM","xEXCEPTION","xFALSE","xFLOAT","xIN","xINOUT","xINTERFACE","xLONG","xMODULE",
"xOBJECT","xOCTET","xONEWAY","xOUT","xRAISES","xREADONLY","xSEQUENCE","xSHORT","xSTRING","xSTRUCT",
"xSWITCH","xTRUE","xTYPEDEF","xUNSIGNED","xUNION","xVOID","OPERATOR","PUNCTUATOR","LITERAL","IDENTIFIER",
"KEYWORD","LITERAL_DECINT","LITERAL_HEXINT","LITERAL_OCTINT","LITERAL_FP","LITERAL_CHAR","LITERAL_CHARHEX","LITERAL_CHAROCT","LITERAL_STRING","DOUBLE_COLON",
"DOUBLE_LT","DOUBLE_GT","FLOATING_PT_LITERAL","CHARACTER_LITERAL","STRING_LITERAL","INTEGER_LITERAL","xIDENTIFIER","'='","'|'","'^'",
"'&'","'-'","'+'","'*'","'/'","'%'","NEG","';'","'{'","'}'",
"':'","','","'~'","'('","')'","'<'","'>'","'['","']'","specification"
};
#endif

static const short yyr1[] = {     0,
    80,    80,    81,    81,    81,    81,    81,    82,    83,    83,
    84,    84,    85,    86,    87,    87,    88,    88,    89,    89,
    89,    89,    89,    90,    91,    91,    92,    92,    92,    93,
    94,    94,    94,    94,    94,    94,    95,    96,    96,    97,
    97,    98,    98,    99,    99,    99,   100,   100,   100,   101,
   101,   101,   101,   102,   102,   103,   103,   103,   104,   104,
   104,   105,   105,   105,   105,   105,   106,   106,   107,   108,
   108,   108,   108,   109,   110,   110,   111,   111,   111,   112,
   112,   112,   112,   112,   112,   112,   113,   113,   114,   114,
   114,   115,   116,   116,   117,   117,   118,   119,   120,   120,
   121,   121,   122,   122,   123,   124,   125,   125,   126,   127,
   128,   129,   130,   131,   132,   133,   134,   134,   135,   136,
   137,   137,   137,   137,   137,   138,   138,   139,   140,   140,
   141,   141,   142,   143,   144,   144,   145,   146,   146,   147,
   147,   148,   149,   149,   150,   151,   151,   152,   152,   153,
   153,   154,   154,   154,   154,   154,   154,   154,   154,   155,
   156,   156,   157,   157,   158,   158,   159,   160,   160,   160,
   161,   162,   162,   163,   164,   164,   165,   165,   165
};

static const short yyr2[] = {     0,
     1,     2,     2,     2,     2,     2,     2,     5,     1,     2,
     1,     1,     4,     2,     2,     3,     0,     2,     2,     2,
     2,     2,     2,     2,     1,     3,     1,     2,     3,     5,
     1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
     3,     1,     3,     1,     3,     3,     1,     3,     3,     1,
     3,     3,     3,     2,     1,     1,     1,     1,     1,     1,
     3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
     1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
     1,     1,     1,     1,     1,     5,     1,     2,     3,     9,
     1,     1,     1,     1,     1,     1,     2,     3,     1,     2,
     3,     2,     2,     5,     1,     3,     1,     6,     4,     4,
     1,     2,     1,     2,     3,     3,     4,     1,     3,     4,
     5,     3,     4,     4,     5,     4,     5,     5,     6,     1,
     1,     1,     3,     2,     1,     3,     3,     1,     1,     1,
     4,     1,     3,     4,     1,     3,     1,     1,     1
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
     0,     0,    11,    12,     0,     0,     0,    71,    72,    73,
     0,   112,   111,   100,    99,   105,   106,   141,     0,     0,
    27,    36,     0,    34,    31,   101,   103,   104,   102,   107,
   108,    32,    33,    35,     0,     0,    14,     0,     0,   114,
   115,   113,     0,    79,    70,     0,    75,    77,    78,    76,
    80,    81,    82,    83,    84,    85,    86,    89,    90,    91,
    87,    88,     0,     2,     7,     6,    17,     4,     3,     5,
     0,   109,   110,    28,     0,     0,     0,     0,     0,    16,
     0,     0,     0,    97,    74,    92,    93,    95,    96,    98,
     0,     0,    68,    67,    65,    64,    63,    62,    56,    57,
    58,     0,    59,    69,    37,    38,    40,    42,    44,    47,
    50,     0,    55,    60,    66,     0,    29,     0,   137,     0,
   135,   150,     0,     0,   117,    24,    25,     9,     0,     0,
     0,     0,   142,   143,     0,     0,     0,   160,     0,   162,
    13,    18,   179,     0,     0,   177,   178,     0,     0,     0,
     0,     0,   161,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    54,   140,    30,   134,     0,     0,
   151,   118,     0,     8,    10,   116,     0,   139,     0,   144,
    94,   125,   121,   122,   123,     0,   124,     0,     0,    20,
    19,    22,    21,    23,     0,     0,    61,    39,    41,    43,
    46,    45,    49,    48,    51,    52,    53,   136,   119,    26,
     0,   145,     0,    97,   148,   146,     0,     0,     0,   152,
   138,     0,     0,   147,   156,   168,   170,   169,   164,     0,
   165,     0,     0,     0,   153,   154,     0,     0,     0,   126,
     0,   129,   149,   157,   158,     0,   163,     0,     0,     0,
   155,     0,   132,   120,   127,     0,   130,     0,   159,   166,
   167,   175,     0,   172,     0,   131,   133,   128,     0,   174,
     0,   171,   176,   173,     0,     0
};

static const short yydefgoto[] = {     9,
    10,    11,   139,    12,    13,    14,    15,   102,   152,    90,
   136,   113,    16,    33,   114,   115,   116,   117,   118,   119,
   120,   121,   122,   123,   124,   125,   126,    17,    55,   133,
    57,    58,    59,    60,    95,    96,    97,    98,    99,    61,
    62,    36,    37,    38,    39,    40,    41,    63,    64,    65,
    66,    67,    68,   134,   135,    69,   196,   249,   250,   251,
   252,   268,    70,   130,   131,    71,    72,   100,   143,   144,
   158,   226,    21,   160,   161,   162,   230,   240,   241,   242,
   245,   275,   246,   273,   163
};

static const short yypact[] = {   524,
   495,   -47,   -24,     0,    17,    19,   377,    32,   513,-32768,
   -17,    -4,-32768,-32768,    33,    29,    36,-32768,-32768,-32768,
    48,-32768,-32768,-32768,-32768,-32768,-32768,    43,    30,    64,
-32768,    78,    72,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    62,    67,   -26,    69,    74,-32768,
-32768,-32768,    68,    78,-32768,    90,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    41,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   174,-32768,-32768,-32768,    99,   100,   104,    25,   -23,-32768,
   524,   377,   410,    81,-32768,    91,-32768,-32768,-32768,-32768,
    92,   182,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   174,    78,-32768,   105,   107,   108,    27,    22,    47,
-32768,   274,-32768,-32768,-32768,    88,-32768,   174,-32768,    28,
-32768,-32768,    90,   255,-32768,    96,    78,-32768,   102,   288,
    -9,   174,    81,-32768,    90,   237,   470,-32768,   166,-32768,
-32768,-32768,    78,   103,   106,-32768,-32768,   109,   110,   111,
   440,   116,-32768,   101,   174,   174,   174,   174,   174,   174,
   174,   174,   174,   174,-32768,-32768,-32768,-32768,   104,   112,
-32768,-32768,   -23,-32768,-32768,-32768,   174,-32768,   113,-32768,
-32768,    78,-32768,-32768,-32768,   121,-32768,   118,   470,-32768,
-32768,-32768,-32768,-32768,   124,   117,-32768,   107,   108,    27,
    22,    22,    47,    47,-32768,-32768,-32768,-32768,-32768,    78,
   122,-32768,   114,-32768,-32768,   130,   118,   117,     2,    14,
-32768,    61,   118,   130,    14,-32768,-32768,-32768,-32768,     8,
-32768,   470,   133,   135,   175,-32768,   174,   142,    11,-32768,
   344,-32768,-32768,   175,-32768,    45,-32768,   118,   159,   -23,
-32768,   148,-32768,-32768,-32768,    90,-32768,   152,-32768,-32768,
-32768,-32768,    18,    78,    24,-32768,-32768,-32768,   167,-32768,
   -23,-32768,-32768,    78,   221,-32768
};

static const short yypgoto[] = {-32768,
    -5,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    -1,   123,-32768,   -90,-32768,    58,    60,    66,   -42,
   -30,   -49,-32768,   129,-32768,-32768,  -122,   132,-32768,    -6,
   145,   -91,-32768,-32768,   120,-32768,  -136,  -185,-32768,   234,
     4,-32768,-32768,-32768,-32768,-32768,-32768,     6,     7,-32768,
-32768,-32768,    15,   154,  -105,    16,-32768,-32768,     5,-32768,
   -11,-32768,     3,-32768,    76,-32768,     1,-32768,-32768,   125,
-32768,    34,   155,-32768,-32768,   131,    35,-32768,    13,-32768,
    37,-32768,  -204,-32768,  -133
};


#define	YYLAST		559


static const short yytable[] = {    32,
    56,    44,    20,    74,    35,    54,    42,    43,   191,    45,
   156,    20,   225,   198,    18,    19,   247,   236,   237,   189,
   248,   164,   243,    18,    19,   238,    30,    50,   182,    22,
   255,    23,    46,    31,   182,    24,     2,   177,   244,    25,
   261,   225,   -15,    26,    89,    51,    52,   253,    82,   269,
    75,    53,    27,    28,     6,   156,    47,    83,    29,     8,
   236,   237,   187,    76,   221,   227,   247,   188,   238,   156,
   248,   101,   271,    48,    30,    49,   239,   168,   169,   256,
   264,    31,   257,   170,   171,   138,    54,   137,    73,   279,
    54,    54,   280,    20,   132,   281,    78,   178,   282,   179,
   153,    77,   157,    79,    20,    18,    19,   156,   258,     1,
   172,   173,   174,     2,     3,    80,    18,    19,    81,     4,
    84,     5,   215,   216,   217,   211,   212,    85,    86,   277,
    87,     6,    54,   185,     7,    88,     8,    91,    54,   213,
   214,    20,    92,    93,   192,   153,    94,   157,   197,   193,
   156,   194,   195,    18,    19,   127,   262,   128,   142,   153,
   129,   157,   145,   165,   176,   146,   166,   183,   167,   199,
   200,   184,   206,   201,   224,   207,   202,   203,   204,   219,
   228,   220,   232,   243,    50,   147,    22,   103,    23,     1,
   229,   222,    24,     2,     3,   223,    25,   153,   231,   157,
    26,   233,    51,    52,   148,   104,   259,   149,   260,    27,
    28,     6,   263,   272,     7,    29,     8,   150,   276,   278,
   286,   283,   208,    30,   154,   209,   105,   106,   107,   108,
    31,    30,   210,   155,    34,   109,   110,   141,    31,   267,
   153,    22,   157,    23,   266,   140,   111,   112,     2,    54,
   175,   151,   180,   265,   218,    26,   159,    50,   274,    22,
   234,    23,   235,     0,    27,    24,     2,   190,   270,    25,
    29,   254,     0,    26,     0,    51,    52,     0,     0,   284,
     0,    53,    27,    28,     6,     0,    30,   103,    29,     8,
    50,   205,    22,    31,    23,     0,     0,     0,    24,     2,
     0,     0,    25,     0,    30,   104,    26,     0,    51,    52,
     0,    31,     0,     0,    53,    27,    28,     6,     0,     0,
     0,    29,     8,    30,   181,     0,   105,   106,   107,   108,
    31,     0,     0,     0,     0,     0,     0,    30,     0,     0,
     0,     0,     0,     0,    31,     0,    50,   112,    22,   247,
    23,     0,     0,   248,    24,     2,     0,   186,    25,     0,
     0,     0,    26,     0,    51,    52,     0,     0,     0,     0,
    53,    27,    28,     6,     0,     0,     0,    29,     8,    50,
     0,    22,     0,    23,     0,     0,     0,    24,     2,     0,
     0,    25,     0,    30,     0,    26,     0,    51,    52,     0,
    31,     0,     0,    53,    27,    28,     6,     0,     0,     0,
    29,     8,    50,     0,    22,     0,    23,     0,     0,     0,
    24,     0,     0,     0,    25,     0,    30,     0,    26,     0,
    51,    52,     0,    31,     0,     0,    53,    27,    28,     0,
     0,     0,    50,    29,    22,     0,    23,     0,     0,     0,
    24,     0,     0,     0,    25,     0,     0,     0,    26,    30,
    51,    52,     0,     0,     0,     0,    31,    27,    28,     0,
     0,     0,    50,    29,    22,   150,    23,     0,     0,     0,
    24,     0,     0,     0,    25,     0,     0,     0,    26,    30,
    51,    52,     0,     0,     0,     0,    31,    27,    28,    22,
     0,    23,     0,    29,     0,    24,     0,     0,     0,    25,
     0,     0,   285,    26,     0,     0,     0,     0,     0,    30,
     1,     0,    27,    28,     2,     3,    31,     0,    29,     0,
     4,     1,     5,     0,     0,     2,     3,     0,     0,     0,
     0,     4,     6,     5,    30,     7,     0,     8,     0,     0,
     0,    31,     0,     6,     0,     0,     7,     0,     8
};

static const short yycheck[] = {     1,
     7,     1,     0,     9,     1,     7,     1,     1,   145,    57,
   102,     9,   198,   147,     0,     0,     6,    16,    17,   142,
    10,   112,     9,     9,     9,    24,    50,     3,   134,     5,
   235,     7,    57,    57,   140,    11,    12,   128,    25,    15,
   245,   227,    69,    19,    71,    21,    22,   233,    19,   254,
    68,    27,    28,    29,    30,   147,    57,    28,    34,    35,
    16,    17,    72,    68,   187,   199,     6,    77,    24,   161,
    10,    31,   258,    57,    50,    57,    75,    51,    52,    72,
    70,    57,    75,    62,    63,    91,    88,    89,    57,    72,
    92,    93,    75,    91,    70,    72,    68,    70,    75,    72,
   102,    69,   102,    68,   102,    91,    91,   199,   242,     8,
    64,    65,    66,    12,    13,    68,   102,   102,    76,    18,
    57,    20,   172,   173,   174,   168,   169,    50,    57,   266,
    69,    30,   134,   139,    33,    69,    35,    69,   140,   170,
   171,   139,    69,    76,   146,   147,    57,   147,   146,   146,
   242,   146,   146,   139,   139,    57,   247,    58,    78,   161,
    57,   161,    72,    59,    77,    74,    60,    72,    61,     4,
    68,    70,    57,    68,    57,    75,    68,    68,    68,    68,
    57,   183,    69,     9,     3,     4,     5,    14,     7,     8,
    74,    79,    11,    12,    13,    75,    15,   199,    77,   199,
    19,    72,    21,    22,    23,    32,    74,    26,    74,    28,
    29,    30,    71,    55,    33,    34,    35,    36,    71,    68,
     0,    55,   165,    50,   102,   166,    53,    54,    55,    56,
    57,    50,   167,   102,     1,    62,    63,    93,    57,   251,
   242,     5,   242,     7,   251,    92,    73,    74,    12,   251,
   122,    70,   133,   249,   179,    19,   102,     3,   260,     5,
   227,     7,   228,    -1,    28,    11,    12,   143,   256,    15,
    34,   235,    -1,    19,    -1,    21,    22,    -1,    -1,   281,
    -1,    27,    28,    29,    30,    -1,    50,    14,    34,    35,
     3,   161,     5,    57,     7,    -1,    -1,    -1,    11,    12,
    -1,    -1,    15,    -1,    50,    32,    19,    -1,    21,    22,
    -1,    57,    -1,    -1,    27,    28,    29,    30,    -1,    -1,
    -1,    34,    35,    50,    70,    -1,    53,    54,    55,    56,
    57,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
    -1,    -1,    -1,    -1,    57,    -1,     3,    74,     5,     6,
     7,    -1,    -1,    10,    11,    12,    -1,    70,    15,    -1,
    -1,    -1,    19,    -1,    21,    22,    -1,    -1,    -1,    -1,
    27,    28,    29,    30,    -1,    -1,    -1,    34,    35,     3,
    -1,     5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,
    -1,    15,    -1,    50,    -1,    19,    -1,    21,    22,    -1,
    57,    -1,    -1,    27,    28,    29,    30,    -1,    -1,    -1,
    34,    35,     3,    -1,     5,    -1,     7,    -1,    -1,    -1,
    11,    -1,    -1,    -1,    15,    -1,    50,    -1,    19,    -1,
    21,    22,    -1,    57,    -1,    -1,    27,    28,    29,    -1,
    -1,    -1,     3,    34,     5,    -1,     7,    -1,    -1,    -1,
    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    50,
    21,    22,    -1,    -1,    -1,    -1,    57,    28,    29,    -1,
    -1,    -1,     3,    34,     5,    36,     7,    -1,    -1,    -1,
    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    50,
    21,    22,    -1,    -1,    -1,    -1,    57,    28,    29,     5,
    -1,     7,    -1,    34,    -1,    11,    -1,    -1,    -1,    15,
    -1,    -1,     0,    19,    -1,    -1,    -1,    -1,    -1,    50,
     8,    -1,    28,    29,    12,    13,    57,    -1,    34,    -1,
    18,     8,    20,    -1,    -1,    12,    13,    -1,    -1,    -1,
    -1,    18,    30,    20,    50,    33,    -1,    35,    -1,    -1,
    -1,    57,    -1,    30,    -1,    -1,    33,    -1,    35
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */


/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* Not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__)
#include <alloca.h>
#endif /* Sparc.  */
#endif /* Not GNU C.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYIMPURE
#define YYLEX		yylex()
#endif

#ifndef YYPURE
#define YYLEX		yylex(&yylval, &yylloc)
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYIMPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* YYIMPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}


int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/

#define YYPOPSTACK   (yyvsp--, yysp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yysp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifndef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
#ifdef YYLSP_NEEDED
		 &yyls1, size * sizeof (*yylsp),
#endif
		 &yystacksize);

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Next token is %d (%s)\n", yychar, yytname[yychar1]);
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      if (yylen == 1)
	fprintf (stderr, "Reducing 1 value via rule %d (line %d), ",
		 yyn, yyrline[yyn]);
      else
	fprintf (stderr, "Reducing %d values via rule %d (line %d), ",
		 yylen, yyn, yyrline[yyn]);
    }
#endif


  switch (yyn) {

case 1:
{	if( compiler_debug_state == DEBUG_ON )printf( "specification:case 1\n" );		
														if( compiler_debug_state == DEBUG_ON )printf( "$1= %x\n", yyvsp[0].void_ptr );
														/* Create the specification object */
														yyval.void_ptr = buildSpecification();
													  
														/* Load the Builder object with this value for later use */
														loadParseTreeRoot( yyval.void_ptr );

														/* Add the first definition item to the specification */
														addDefinition( yyval.void_ptr, yyvsp[0].void_ptr );
									   				
													;
    break;}
case 2:
{	if( compiler_debug_state == DEBUG_ON )printf( "specification:case 2\n" );
														
														/* Add the subsequent definition items to the specification */
														addDefinition( yyval.void_ptr, yyvsp[0].void_ptr );													
													;
    break;}
case 3:
{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 1\n" ); yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 4:
{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 2\n" ); yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 5:
{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 3\n" ); yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 6:
{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 4\n" ); yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 7:
{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 5\n" ); yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 8:
{
							int i=0;
							
							if( compiler_debug_state == DEBUG_ON )printf( "module: case 1\n" );
							for( i=0 ; i<module_definition_count ; i++ )
								if( compiler_debug_state == DEBUG_ON )printf( "module_definition_array[%d]= %x\n", i, module_definition_array[i] );

							yyval.void_ptr = buildModule( yyvsp[-4].str_lit, yyvsp[-3].str_lit, module_definition_array, module_definition_count );
														  
							/* Handle reset details */
							reset_void_array( &module_definition_array, &module_definition_count, &module_definition_array_limit );
							;
    break;}
case 9:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_11: case 1\n" ); yyval.tok_val=0; load_module_definition_array(yyvsp[0].void_ptr); ;
    break;}
case 10:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_11: case 2\n" ); yyval.tok_val=0; load_module_definition_array(yyvsp[0].void_ptr); ;
    break;}
case 11:
{	if( compiler_debug_state == DEBUG_ON )printf( "interface: case 1\n" ); yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 12:
{	if( compiler_debug_state == DEBUG_ON )printf( "interface: case 2\n" ); yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 13:
{
							if( compiler_debug_state == DEBUG_ON )printf( "interface_dcl: case 1\n" ); 
							yyval.void_ptr = buildInterface_Dcl( yyvsp[-3].void_ptr, yyvsp[-1].void_ptr );
							;
    break;}
case 14:
{	if( compiler_debug_state == DEBUG_ON )printf( "forward_dcl: case 1:xIDENTIFIER\n" ); 
																		yyval.void_ptr = buildForward_Dcl( yyvsp[-1].str_lit, yyvsp[0].str_lit );
																	;
    break;}
case 15:
{	if( compiler_debug_state == DEBUG_ON )printf( "interface_header: case 1:xIDENTIFIER\n" ); 
																		yyval.void_ptr = buildInterface_Header( yyvsp[-1].str_lit, yyvsp[0].str_lit, NULL );
																	;
    break;}
case 16:
{	if( compiler_debug_state == DEBUG_ON )printf( "interface_header: case 2:xIDENTIFIER\n" );																		
																		yyval.void_ptr = buildInterface_Header( yyvsp[-2].str_lit, yyvsp[-1].str_lit, yyvsp[0].void_ptr );
																	;
    break;}
case 17:
{	if( compiler_debug_state == DEBUG_ON )printf( "interface_body: case 1\n" ); yyval.void_ptr=NULL; /*Flag to show no interface_body has been built*/ ;
    break;}
case 18:
{	void	*ptr;
															if( compiler_debug_state == DEBUG_ON )printf( "interface_body: case 2\n" ); 
															if( compiler_debug_state == DEBUG_ON )printf( "$1= %x\t $2= %x\n", yyvsp[-1].void_ptr, yyvsp[0].void_ptr );
															/* Create an interface_body object if necessary */
															if( yyvsp[-1].void_ptr == NULL )
																{
																/* We need to create an interface_body object */
																yyval.void_ptr = buildInterface_Body();
																ptr = yyval.void_ptr;
																}
															else
																{
																//interface_body object already exists:
																ptr = yyvsp[-1].void_ptr;
																}

															/* Add the export item to the interface_body */
															addExport( ptr, yyvsp[0].void_ptr );
									   
														;
    break;}
case 19:
{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 1: type_dcl  \n" );	yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 20:
{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 2: const_dcl \n" );	yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 21:
{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 3: except_dcl\n" );	yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 22:
{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 4: attr_dcl  \n" );	yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 23:
{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 5: op_dcl    \n" );	yyval.void_ptr=yyvsp[-1].void_ptr;	;
    break;}
case 24:
{	
															if( compiler_debug_state == DEBUG_ON )printf( "inheritance_spec: case 1\n" );	/*build obj with scoped_name array */
															yyval.void_ptr = buildInheritance_Spec( scoped_name_array, scoped_name_count );

															/* Handle reset details */
															reset_void_array( &scoped_name_array, &scoped_name_count, &scoped_name_array_limit );
														;
    break;}
case 25:
{	void *ptr; 
															if( compiler_debug_state == DEBUG_ON )printf( "aux_1: case 1\n" ); 
															ptr = Scoped_Name_buildHandler();

															/* Add this scoped_name object to the scoped_name object array */
															load_scoped_name_array( ptr );	
																																													
															/* return type is not important here */
															yyval.void_ptr=NULL;																																							
														;
    break;}
case 26:
{	void *ptr;
															if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 1\n" ); 
															ptr = Scoped_Name_buildHandler();

															/* Add this scoped_name object to the scoped_name object array */
															load_scoped_name_array( ptr );	
																																													
															/* return type is not important here */
															yyval.void_ptr=NULL;	
														;
    break;}
case 27:
{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 1\n" );
																	
																	/* Set the scope type */ 
																	scoped_name_scope_flag = RELATIVE_SCOPE;

																	yyval.void_ptr=NULL;							 

																	load_scoped_name_list_array( yyvsp[0].str_lit );	
																;
    break;}
case 28:
{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 2\n" );

																	/* Set the scope type */ 
																	scoped_name_scope_flag = GLOBAL_SCOPE;

																	yyval.void_ptr=NULL; 

																	load_scoped_name_list_array( yyvsp[0].str_lit );	
																;
    break;}
case 29:
{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 3\n" ); 
																	yyval.void_ptr=NULL; 
																	load_scoped_name_list_array( yyvsp[0].str_lit );	
																;
    break;}
case 30:
{	if( compiler_debug_state == DEBUG_ON )printf( "const_dcl: case 1\n" ); 
																		yyval.void_ptr = buildConst_Dcl( yyvsp[-4].str_lit, yyvsp[-3].void_ptr, yyvsp[-2].str_lit, yyvsp[0].void_ptr );																		
																	;
    break;}
case 31:
{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 1\n" ); 
													yyval.void_ptr = buildConst_Type1( yyvsp[0].str_lit );
												;
    break;}
case 32:
{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 2\n" ); 
													yyval.void_ptr = buildConst_Type1( yyvsp[0].str_lit );					
												;
    break;}
case 33:
{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 3\n" ); 
													yyval.void_ptr = buildConst_Type1( yyvsp[0].str_lit );																										
												;
    break;}
case 34:
{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 4\n" ); 
													yyval.void_ptr = buildConst_Type1( yyvsp[0].str_lit );
												;
    break;}
case 35:
{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 5\n" );
													yyval.void_ptr = buildConst_Type2( yyvsp[0].void_ptr );													
												;
    break;}
case 36:
{	void *ptr;
													if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 6\n" ); 	/*scoped_name as a type??? */
													ptr = Scoped_Name_buildHandler();
													yyval.void_ptr = buildConst_Type2( ptr );
												;
    break;}
case 37:
{	if( compiler_debug_state == DEBUG_ON )printf( "const_exp:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 38:
{	if( compiler_debug_state == DEBUG_ON )printf( "or_expr:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 39:
{	if( compiler_debug_state == DEBUG_ON )printf( "or_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '|' );																
															;
    break;}
case 40:
{	if( compiler_debug_state == DEBUG_ON )printf( "xor_expr:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 41:
{ 	if( compiler_debug_state == DEBUG_ON )printf( "xor_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '^' );
															;
    break;}
case 42:
{	if( compiler_debug_state == DEBUG_ON )printf( "and_expr:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 43:
{ 	if( compiler_debug_state == DEBUG_ON )printf( "and_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '&' );
															;
    break;}
case 44:
{	if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 45:
{	if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 2\n" );
																/* We will pass the single char '>' to signify a '>>' right-shift. */
																/* This will be interpreted by the buildGSIobject() routines     */
																/* as a '>>' */
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '>' );
															;
    break;}
case 46:
{   if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 3\n" );
																/* We will pass the single char '<' to signify a '<<' left-shift. */
																/* This will be interpreted by the buildGSIobject() routines     */
																/* as a '<<' */
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '<' );

															;
    break;}
case 47:
{	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 48:
{ 	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '+' );
															;
    break;}
case 49:
{	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 3\n" );
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '-' );
															;
    break;}
case 50:
{	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 51:
{	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 2\n" );	
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '*' );
															;
    break;}
case 52:
{ 	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 3\n" );	
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '/' );
															;
    break;}
case 53:
{ 	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 4\n" );	
																yyval.void_ptr = buildMath_Expression( yyvsp[-2].void_ptr, yyvsp[0].void_ptr, '%' );
															;
    break;}
case 54:
{	if( compiler_debug_state == DEBUG_ON )printf( "unary_expr:case 1\n" );	
																setUnaryOperator( yyvsp[-1].tok_val, yyvsp[0].void_ptr );
																yyval.void_ptr=yyvsp[0].void_ptr;
															;
    break;}
case 55:
{	if( compiler_debug_state == DEBUG_ON )printf( "unary_expr:case 2\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 56:
{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 1\n" );	yyval.tok_val='-';	;
    break;}
case 57:
{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 2\n" );	yyval.tok_val='+';	;
    break;}
case 58:
{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 3\n" );	yyval.tok_val='~';	;
    break;}
case 59:
{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 1\n" );
																yyval.void_ptr = Scoped_Name_buildHandler();								
															;
    break;}
case 60:
{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 2\n" );
																yyval.void_ptr = yyvsp[0].void_ptr;
															;
    break;}
case 61:
{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 3\n" );
																yyval.void_ptr = yyvsp[-1].void_ptr;
																/* We can disallow a unary operator attached to the (...) 
																   as John H does. */
															;
    break;}
case 62:
{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 1: $1= %d\n", yyvsp[0].lng_val  );
																yyval.void_ptr = buildLongIntegerLiteral( yyvsp[0].lng_val );																
															;
    break;}
case 63:
{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 2\n" );																
																yyval.void_ptr = buildStringLiteral( yyvsp[0].str_lit ); 
															;
    break;}
case 64:
{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 3: $1= %c\n", yyvsp[0].chr_val  );
																yyval.void_ptr = buildCharLiteral( yyvsp[0].chr_val ); 
															;
    break;}
case 65:
{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 4: $1= %f\n", yyvsp[0].dbl_val  );
																yyval.void_ptr = buildDoubleLiteral( yyvsp[0].dbl_val ); 
															;
    break;}
case 66:
{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 5\n" );
																yyval.void_ptr = buildBooleanLiteral( yyvsp[0].void_ptr ); 
															;
    break;}
case 67:
{	if( compiler_debug_state == DEBUG_ON )printf( "boolean_literal:case 1\n" );	yyval.void_ptr=yyvsp[0].str_lit; 	;
    break;}
case 68:
{	if( compiler_debug_state == DEBUG_ON )printf( "boolean_literal:case 2\n" );	yyval.void_ptr=yyvsp[0].str_lit;	;
    break;}
case 69:
{	if( compiler_debug_state == DEBUG_ON )printf( "positive_int_const:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 70:
{	if( compiler_debug_state == DEBUG_ON )( "type_dcl:case 1\n" );		
																yyval.void_ptr = buildType_Dcl_Case1( yyvsp[-1].str_lit, yyvsp[0].void_ptr );
															;
    break;}
case 71:
{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 2\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 72:
{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 3\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 73:
{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 4\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 74:
{	
/* Identical code to 'member' */								if( compiler_debug_state == DEBUG_ON )printf( "type_declarator:case 1\n" ); /*build object with declarators array.*/
																yyval.void_ptr = buildType_Declarator( yyvsp[-1].void_ptr, declarator_array, declarator_count );

																/* Handle reset details */
																reset_void_array( &declarator_array, &declarator_count, &declarator_array_limit );
															;
    break;}
case 75:
{	if( compiler_debug_state == DEBUG_ON )printf( "type_spec:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 76:
{	if( compiler_debug_state == DEBUG_ON )printf( "type_spec:case 2\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 77:
{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 1\n" );
												yyval.void_ptr = buildBase_Type_Spec( yyvsp[0].str_lit );
											;
    break;}
case 78:
{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 2\n" );
												yyval.void_ptr=yyvsp[0].void_ptr;
											;
    break;}
case 79:
{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 3\n" );	
												yyval.void_ptr = Scoped_Name_buildHandler();
											;
    break;}
case 80:
{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 1\n");
												yyval.str_lit=yyvsp[0].str_lit;
											;
    break;}
case 81:
{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 2\n" );
												yyval.str_lit=yyvsp[0].str_lit;		
											;
    break;}
case 82:
{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 3\n" );
												yyval.str_lit=yyvsp[0].str_lit;
											;
    break;}
case 83:
{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 4\n" );
												yyval.str_lit=yyvsp[0].str_lit;
											;
    break;}
case 84:
{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 5\n" );
												yyval.str_lit=yyvsp[0].str_lit;
											;
    break;}
case 85:
{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 6\n" );
												yyval.str_lit=yyvsp[0].str_lit;
											;
    break;}
case 86:
{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 7\n" );
												yyval.str_lit=yyvsp[0].str_lit;
											;
    break;}
case 87:
{	if( compiler_debug_state == DEBUG_ON )printf( "template_type_spec:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 88:
{	if( compiler_debug_state == DEBUG_ON )printf( "template_type_spec:case 2\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 89:
{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 90:
{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 2\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 91:
{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 3\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 92:
{	if( compiler_debug_state == DEBUG_ON )printf( "declarators:case 1\n" );	/*declarator_srray is fully loaded at this point*/ ;
    break;}
case 93:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr; load_declarator_array( yyvsp[0].void_ptr ); ;
    break;}
case 94:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 2\n" );	yyval.void_ptr=yyvsp[-2].void_ptr; load_declarator_array( yyvsp[0].void_ptr ); ;
    break;}
case 95:
{	if( compiler_debug_state == DEBUG_ON )printf( "declarator:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 96:
{	if( compiler_debug_state == DEBUG_ON )printf( "declarator:case 2\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 97:
{	if( compiler_debug_state == DEBUG_ON )printf( "simple_declarator:case 1\n" );
													yyval.void_ptr = buildSimple_Declarator( yyvsp[0].str_lit );
												;
    break;}
case 98:
{	if( compiler_debug_state == DEBUG_ON )printf( "complex_declarator:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	;
    break;}
case 99:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xFLOAT\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 100:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xDOUBLE\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 101:
{	if( compiler_debug_state == DEBUG_ON )printf( "integer_type:signed_int\n" );		yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 102:
{	if( compiler_debug_state == DEBUG_ON )printf( "integer_type:unsigned_int\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 103:
{	if( compiler_debug_state == DEBUG_ON )printf( "signed_int:signed_long_int\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 104:
{	if( compiler_debug_state == DEBUG_ON )printf( "signed_int:signed_short_int\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 105:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xLONG\n" );		yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 106:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xSHORT\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 107:
{	if( compiler_debug_state == DEBUG_ON )printf( "unsigned_long_int:unsigned_long_int\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 108:
{	if( compiler_debug_state == DEBUG_ON )printf( "unsigned_short_int:unsigned_short_int\n" );	yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 109:
{	char	*u_long;
												u_long = (char *) malloc( 14 );
												strcpy( u_long, yyvsp[-1].str_lit );
												strcat( u_long, " " ); 
												strcat( u_long, yyvsp[0].str_lit ); 
												yyval.str_lit = u_long;
												if( compiler_debug_state == DEBUG_ON )printf( "Got: xUNSIGNED xLONG\n" );
											;
    break;}
case 110:
{	char	*u_short;
												u_short = (char *) malloc( 15 );
												strcpy( u_short, yyvsp[-1].str_lit );   
												strcat( u_short, " " ); 
												strcat( u_short, yyvsp[0].str_lit ); 
												yyval.str_lit = u_short;
												if( compiler_debug_state == DEBUG_ON )printf( "Got: xUNSIGNED xSHORT\n" );
											;
    break;}
case 111:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xCHAR\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 112:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xBOOLEAN\n" );yyval.str_lit=yyvsp[0].str_lit;	;
    break;}
case 113:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xOCTET\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 114:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xANY\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 115:
{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xOBJECT\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 116:
{	
																		if( compiler_debug_state == DEBUG_ON )printf( "struct_type:Got: xSTRUCT: $1= %ld\n", yyvsp[-4].str_lit ); 
																		yyval.void_ptr = buildStruct_Type( yyvsp[-4].str_lit, yyvsp[-3].str_lit, member_array, member_count );

																		/* Handle reset details */
																		reset_void_array( &member_array, &member_count, &member_array_limit );
																	;
    break;}
case 117:
{	if( compiler_debug_state == DEBUG_ON )printf( "member_list:case 1\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	load_member_array( yyvsp[0].void_ptr );	;
    break;}
case 118:
{	if( compiler_debug_state == DEBUG_ON )printf( "member_list:case 2\n" );	yyval.void_ptr=yyvsp[0].void_ptr;	load_member_array( yyvsp[0].void_ptr );	;
    break;}
case 119:
{	int i;
/* Identical code to 'type_declarator' */					if( compiler_debug_state == DEBUG_ON )printf( "member:case 1\n" );	/*build obj with declarators array*/ 
															yyval.void_ptr = buildMember( yyvsp[-2].void_ptr, declarator_array, declarator_count );

															/* Clear declarator_array and then clear declarator_count */
															for( i=0 ; i<attr_dcl_count ; i++ )
																declarator_array[i] = NULL;
																
															declarator_count = 0;
														;
    break;}
case 120:
{ 
							if( compiler_debug_state == DEBUG_ON )printf( "union_type: case 1\n" );
							
							yyval.void_ptr = buildUnion_Type( yyvsp[-8].str_lit, yyvsp[-7].str_lit, yyvsp[-6].str_lit, yyvsp[-4].void_ptr, switch_body_array, switch_body_count );
							
							/* Handle reset details */
							reset_void_array( &switch_body_array, &switch_body_count, &switch_body_array_limit );	
							;
    break;}
case 121:
{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 1\n" ); 
													yyval.void_ptr = buildSwitch_Type_Spec1( yyvsp[0].str_lit );
												;
    break;}
case 122:
{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 2\n" ); 
													yyval.void_ptr = buildSwitch_Type_Spec1( yyvsp[0].str_lit );					
												;
    break;}
case 123:
{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 3\n" ); 
													yyval.void_ptr = buildSwitch_Type_Spec1( yyvsp[0].str_lit );																	
												;
    break;}
case 124:
{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 5\n" );
													yyval.void_ptr = buildSwitch_Type_Spec2( yyvsp[0].void_ptr );													
												;
    break;}
case 125:
{	void *ptr;
													if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 6\n" ); 	/*scoped_name as a type??? */
													ptr = Scoped_Name_buildHandler();
													yyval.void_ptr = buildSwitch_Type_Spec2( ptr );
												;
    break;}
case 126:
{	if( compiler_debug_state == DEBUG_ON )printf( "switch_body: case 1\n" );	yyval.tok_val=0;	load_switch_body_array( yyvsp[0].void_ptr );	;
    break;}
case 127:
{	if( compiler_debug_state == DEBUG_ON )printf( "switch_body: case 2\n" );	yyval.tok_val=0;	load_switch_body_array( yyvsp[0].void_ptr );	;
    break;}
case 128:
{	 
														if( compiler_debug_state == DEBUG_ON )printf( "case: case 1\n" ); /*case_label_array is fully loaded at this point*/
														yyval.void_ptr = buildCase( case_label_array, case_label_count, yyvsp[-1].void_ptr );	
							
														/* Handle reset details */
														reset_void_array( &case_label_array, &case_label_count, &case_label_array_limit );	
													;
    break;}
case 129:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_3: case 1\n" ); yyval.tok_val=0; load_case_label_array( yyvsp[0].void_ptr ); ;
    break;}
case 130:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_3: case 2\n" ); yyval.tok_val=0; load_case_label_array( yyvsp[0].void_ptr ); ;
    break;}
case 131:
{	if( compiler_debug_state == DEBUG_ON )printf( "case_label: case 1\n" ); 
														yyval.void_ptr = buildCase_Label( yyvsp[-2].str_lit, yyvsp[-1].void_ptr );
													;
    break;}
case 132:
{	if( compiler_debug_state == DEBUG_ON )printf( "case_label: case 2\n" );
														yyval.void_ptr = buildCase_Label( yyvsp[-1].str_lit, NULL );
													;
    break;}
case 133:
{	if( compiler_debug_state == DEBUG_ON )printf( "element_spec: case 1\n" );
														yyval.void_ptr = buildElement_Spec( yyvsp[-1].void_ptr, yyvsp[0].void_ptr );
													;
    break;}
case 134:
{
																					 
							if( compiler_debug_state == DEBUG_ON )printf( "enum_type: case 1\n" ); 
							
							yyval.void_ptr = buildEnum_Type( yyvsp[-4].str_lit, yyvsp[-3].str_lit, enumerator_array, enumerator_count );
														
							/* Handle reset details */
							reset_char_array( &enumerator_array, &enumerator_count, &enumerator_array_limit );
							;
    break;}
case 135:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_4: case 1\n" ); yyval.tok_val=0; load_enumerator_array(yyvsp[0].str_lit); ;
    break;}
case 136:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_4: case 2\n" ); yyval.tok_val=0; load_enumerator_array(yyvsp[0].str_lit); ;
    break;}
case 137:
{	if( compiler_debug_state == DEBUG_ON )printf( "enumerator: case 1:\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 138:
{	if( compiler_debug_state == DEBUG_ON )printf( "sequence_type: case 1\n" ); 
																						yyval.void_ptr = buildSequence_Type( yyvsp[-5].str_lit, yyvsp[-3].void_ptr, yyvsp[-1].void_ptr );
																					;
    break;}
case 139:
{	if( compiler_debug_state == DEBUG_ON )printf( "sequence_type: case 2\n" ); 
																						yyval.void_ptr = buildSequence_Type( yyvsp[-3].str_lit, yyvsp[-1].void_ptr, NULL );
																					;
    break;}
case 140:
{	if( compiler_debug_state == DEBUG_ON )printf( "string_type:case 1\n" );	
																yyval.void_ptr = buildString_Type( yyvsp[-3].str_lit, yyvsp[-1].void_ptr );
															;
    break;}
case 141:
{	if( compiler_debug_state == DEBUG_ON )printf( "string_type:case 2\n" );
																yyval.void_ptr = buildString_Type( yyvsp[0].str_lit, NULL );															
															;
    break;}
case 142:
{	 
																if( compiler_debug_state == DEBUG_ON )printf( "array_declarator: case 1\n" ); 
																
																/*fixed_array_size_array is fully loaded at this point*/				
																yyval.void_ptr = buildArray_Declarator( yyvsp[-1].str_lit, fixed_array_size_array, fixed_array_size_count );	

																/* Handle reset details */
																reset_void_array( &fixed_array_size_array, &fixed_array_size_count, &fixed_array_size_array_limit );									
															;
    break;}
case 143:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_5: case 1\n" ); yyval.tok_val=0; load_fixed_array_size_array( yyvsp[0].void_ptr );	;
    break;}
case 144:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_5: case 2\n" ); yyval.tok_val=0; load_fixed_array_size_array( yyvsp[0].void_ptr );	;
    break;}
case 145:
{	if( compiler_debug_state == DEBUG_ON )printf( "fixed_array_size: case 1\n" );	yyval.void_ptr=yyvsp[-1].void_ptr; ;
    break;}
case 146:
{
							
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl: case 1\n" );
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl_count= %d\n", attr_dcl_count );
							
							yyval.void_ptr = buildAttr_Dcl( NO_READONLY, yyvsp[-2].str_lit, yyvsp[-1].void_ptr, attr_dcl_array, attr_dcl_count );
							
							/* Handle reset details */
							reset_void_array( &attr_dcl_array, &attr_dcl_count, &attr_dcl_array_limit );
							;
    break;}
case 147:
{ 
							
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl: case 3\n" );
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl_count= %d\n", attr_dcl_count );
							
							yyval.void_ptr = buildAttr_Dcl( YES_READONLY, yyvsp[-2].str_lit, yyvsp[-1].void_ptr, attr_dcl_array, attr_dcl_count );

							/* Handle reset details */
							reset_void_array( &attr_dcl_array, &attr_dcl_count, &attr_dcl_array_limit );
							;
    break;}
case 148:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_6: case 1:\n" ); yyval.str_lit=yyvsp[0].void_ptr; load_attr_dcl_array(yyvsp[0].void_ptr); ;
    break;}
case 149:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_6: case 2:\n" ); yyval.str_lit=yyvsp[-2].str_lit; load_attr_dcl_array(yyvsp[0].void_ptr); ;
    break;}
case 150:
{	if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 1\n" );
																		/* The member_array will have no members and the count 
																		 * wiil be 0. This will be handled by the constructor */ 
																		yyval.void_ptr = buildExcept_Dcl( yyvsp[-3].str_lit, yyvsp[-2].str_lit, member_array, member_count );
																	;
    break;}
case 151:
{	
																		if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 2\n" );
																		yyval.void_ptr = buildExcept_Dcl( yyvsp[-4].str_lit, yyvsp[-3].str_lit, member_array, member_count );

																		/* Handle reset details */
																		reset_void_array( &member_array, &member_count, &member_array_limit );
																	;
    break;}
case 152:
{
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 1\n" );
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yyvsp[-2].void_ptr, yyvsp[-1].str_lit, param_dcl_array, param_dcl_count, NULL, NULL );
														
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							;
    break;}
case 153:
{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 2\n" ); 																		 
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yyvsp[-3].void_ptr, yyvsp[-2].str_lit, param_dcl_array, param_dcl_count, yyvsp[0].void_ptr, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							;
    break;}
case 154:
{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 3\n" );
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yyvsp[-3].void_ptr, yyvsp[-2].str_lit, param_dcl_array, param_dcl_count, NULL, yyvsp[0].void_ptr );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							;
    break;}
case 155:
{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 4\n" ); 
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yyvsp[-4].void_ptr, yyvsp[-3].str_lit, param_dcl_array, param_dcl_count, yyvsp[-1].void_ptr, yyvsp[0].void_ptr );
														
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit ); 
							;
    break;}
case 156:
{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 5\n" ); 																		 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yyvsp[-2].void_ptr, yyvsp[-1].str_lit, param_dcl_array, param_dcl_count, NULL, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							;
    break;}
case 157:
{
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 5\n" ); 																		 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yyvsp[-3].void_ptr, yyvsp[-2].str_lit, param_dcl_array, param_dcl_count, yyvsp[0].void_ptr, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							;
    break;}
case 158:
{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 7\n" ); 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yyvsp[-3].void_ptr, yyvsp[-2].str_lit, param_dcl_array, param_dcl_count, NULL, yyvsp[0].void_ptr );
							
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );							
							;
    break;}
case 159:
{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 8\n" ); 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yyvsp[-4].void_ptr, yyvsp[-3].str_lit, param_dcl_array, param_dcl_count, yyvsp[-1].void_ptr, yyvsp[0].void_ptr );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							;
    break;}
case 160:
{	if( compiler_debug_state == DEBUG_ON )printf( "op_attribute: case 1: Got xONEWAY:$1 = %d\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit; ;
    break;}
case 161:
{	if( compiler_debug_state == DEBUG_ON )printf( "op_type_spec: case 1:$1= %x\n", yyvsp[0].void_ptr );
												yyval.void_ptr = buildOp_Type_Spec1( yyvsp[0].void_ptr );
											;
    break;}
case 162:
{	if( compiler_debug_state == DEBUG_ON )printf( "op_type_spec: case 2\n" );
												yyval.void_ptr = buildOp_Type_Spec2( yyvsp[0].str_lit );					
											;
    break;}
case 163:
{	if( compiler_debug_state == DEBUG_ON )printf( "parameter_dcls: case 1\n" ); 
															/* For this case, we will let parent rule build an object. */
															yyval.void_ptr = NULL;
														;
    break;}
case 164:
{ 
															if( compiler_debug_state == DEBUG_ON )printf( "parameter_dcls: case 3\n" ); 
															/* Any rule using parameter_dcls will check the param_dcl count. */
															/* If it is 0, this is the case that matched. */
															yyval.void_ptr = NULL;
														;
    break;}
case 165:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_8: case 1\n" ); yyval.tok_val=0;	;
    break;}
case 166:
{	if( compiler_debug_state == DEBUG_ON )printf( "aux_8: case 2\n" ); yyval.tok_val=0;	;
    break;}
case 167:
{ 
							void	*ptr;
							if( compiler_debug_state == DEBUG_ON )printf( "param_dcl:$2= %x\t $3= %x\n", yyvsp[-1].void_ptr, yyvsp[0].void_ptr ); 

							ptr = buildParam_Dcl( yyvsp[-2].str_lit, yyvsp[-1].void_ptr, yyvsp[0].void_ptr );

							/* Add this param_dcl object to the param_dcl object array */
							load_param_dcl_array( ptr );	

							/* The semantic value of each param_dcl is not used individually */
							yyval.void_ptr = NULL;
							;
    break;}
case 168:
{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 1\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 169:
{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 2\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 170:
{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 3\n" );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 171:
{	if( compiler_debug_state == DEBUG_ON )printf( "raises_expr: case 1\n" ); /*build obj with scoped_name array */
																yyval.void_ptr = buildRaises_Expr( scoped_name_array, scoped_name_count );

																/* Handle reset details */
																reset_void_array( &scoped_name_array, &scoped_name_count, &scoped_name_array_limit );
															;
    break;}
case 172:
{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_9: case 1\n" ); 
																ptr = Scoped_Name_buildHandler();

																/* Add this scoped_name object to the scoped_name object array */
																load_scoped_name_array( ptr );	
																																														
																/* return type is not important here */
																yyval.tok_val=0;				
															;
    break;}
case 173:
{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_9: case 2\n" ); 
																ptr = Scoped_Name_buildHandler();

																/* Add this scoped_name object to the scoped_name object array */
																load_scoped_name_array( ptr );	
																																														
																/* return type is not important here */
																yyval.tok_val=0;				
															;
    break;}
case 174:
{	if( compiler_debug_state == DEBUG_ON )printf( "context_expr: case 1\n" );
																yyval.void_ptr = buildContext_Expr( yyvsp[-3].str_lit, string_literal_array, string_literal_count );
							
																/* Handle reset details */
																reset_void_array( &string_literal_array, &string_literal_count, &string_literal_array_limit );							
															;
    break;}
case 175:
{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_10: case 1\n" ); 
																yyval.tok_val = 0;	/* value of aux_10 is not used */																
																ptr = buildStringLiteral( yyvsp[0].str_lit );
																load_string_literal_array( ptr );	
															;
    break;}
case 176:
{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_10: case 2\n" );
																yyval.tok_val = 0;	/* value of aux_10 is not used */																
																ptr = buildStringLiteral( yyvsp[0].str_lit );
																load_string_literal_array( ptr );	
															;
    break;}
case 177:
{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 1\n" );		
																yyval.void_ptr = buildBase_Type_Spec( yyvsp[0].str_lit );
															;
    break;}
case 178:
{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 2\n" ); 
																yyval.void_ptr=yyvsp[0].void_ptr;
															;
    break;}
case 179:
{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 3\n" ); 
																yyval.void_ptr = Scoped_Name_buildHandler();
															;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */


  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) xmalloc(size + 15);
	  strcpy(msg, "parse error");

	  if (count < 5)
	    {
	      count = 0;
	      for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
		if (yycheck[x + yyn] == x)
		  {
		    strcat(msg, count == 0 ? ", expecting `" : " or `");
		    strcat(msg, yytname[x]);
		    strcat(msg, "'");
		    count++;
		  }
	    }
	  yyerror(msg);
	  free(msg);
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}

/*
Additional C code
The additional C code can contain any C code you want to use. Often the definition of the lexical analyzer yylex goes here, plus
subroutines called by the actions in the grammar rules. In a simple program, all the rest of the program can go here. 
*/

/*
yyerror( "Error in application of infix operator: '*'\n" );
YYERROR;
*/

int load_attr_dcl_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( attr_dcl_count == 0 )
		{
		/* Perform initial allocation of storage */
		attr_dcl_array = (void **) malloc( attr_dcl_array_limit * sizeof(void *) );
		}
	else if( attr_dcl_count == attr_dcl_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( attr_dcl_array_limit * sizeof(void *) );

		for( i=0 ; i<attr_dcl_count ; i++ )
			{
			temp_array[i] = attr_dcl_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( attr_dcl_array );
		attr_dcl_array = (void **) malloc( (attr_dcl_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<attr_dcl_count ; i++ )
			{
			attr_dcl_array[i] = temp_array[i];
			}

		/* Change attr_dcl_array_limit to reflect new array size */
		attr_dcl_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", attr_dcl_count, arg );

	attr_dcl_array[attr_dcl_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl_array[%d]= %x\n", attr_dcl_count, arg );

	attr_dcl_count++;

	return( 0 );


}


int load_param_dcl_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( param_dcl_count == 0 )
		{
		/* Perform initial allocation of storage */
		param_dcl_array = (void **) malloc( param_dcl_array_limit * sizeof(void *) );
		}
	else if( param_dcl_count == param_dcl_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( param_dcl_array_limit * sizeof(void *) );

		for( i=0 ; i<param_dcl_count ; i++ )
			{
			temp_array[i] = param_dcl_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( param_dcl_array );
		param_dcl_array = (void **) malloc( (param_dcl_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<param_dcl_count ; i++ )
			{
			param_dcl_array[i] = temp_array[i];
			}

		/* Change param_dcl_array_limit to reflect new array size */
		param_dcl_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", param_dcl_count, arg );

	param_dcl_array[param_dcl_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "param_dcl_array[%d]= %x\n", param_dcl_count, arg );

	param_dcl_count++;

	return( 0 );


}


int load_declarator_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( declarator_count == 0 )
		{
		/* Perform initial allocation of storage */
		declarator_array = (void **) malloc( declarator_array_limit * sizeof(void *) );
		}
	else if( declarator_count == declarator_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( declarator_array_limit * sizeof(void *) );

		for( i=0 ; i<declarator_count ; i++ )
			{
			temp_array[i] = declarator_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( declarator_array );
		declarator_array = (void **) malloc( (declarator_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<declarator_count ; i++ )
			{
			declarator_array[i] = temp_array[i];
			}

		/* Change declarator_array_limit to reflect new array size */
		declarator_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", declarator_count, arg );

	declarator_array[declarator_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "declarator_array[%d]= %x\n", declarator_count, arg );

	declarator_count++;

	return( 0 );

}


int load_fixed_array_size_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( fixed_array_size_count == 0 )
		{
		/* Perform initial allocation of storage */
		fixed_array_size_array = (void **) malloc( fixed_array_size_array_limit * sizeof(void *) );
		}
	else if( fixed_array_size_count == fixed_array_size_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( fixed_array_size_array_limit * sizeof(void *) );

		for( i=0 ; i<fixed_array_size_count ; i++ )
			{
			temp_array[i] = fixed_array_size_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( fixed_array_size_array );
		fixed_array_size_array = (void **) malloc( (fixed_array_size_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<fixed_array_size_count ; i++ )
			{
			fixed_array_size_array[i] = temp_array[i];
			}

		/* Change fixed_array_size_array_limit to reflect new array size */
		fixed_array_size_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", fixed_array_size_count, arg );

	fixed_array_size_array[fixed_array_size_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "fixed_array_size_array[%d]= %x\n", fixed_array_size_count, arg );

	fixed_array_size_count++;

	return( 0 );

}


int load_module_definition_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( module_definition_count == 0 )
		{
		/* Perform initial allocation of storage */
		module_definition_array = (void **) malloc( module_definition_array_limit * sizeof(void *) );
		}
	else if( module_definition_count == module_definition_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( module_definition_array_limit * sizeof(void *) );

		for( i=0 ; i<module_definition_count ; i++ )
			{
			temp_array[i] = module_definition_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( module_definition_array );
		module_definition_array = (void **) malloc( (module_definition_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<module_definition_count ; i++ )
			{
			module_definition_array[i] = temp_array[i];
			}

		/* Change module_definition_array_limit to reflect new array size */
		module_definition_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", module_definition_count, arg );

	module_definition_array[module_definition_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "module_definition_array[%d]= %x\n", module_definition_count, arg );

	module_definition_count++;

	return( 0 );

}

int load_case_label_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( case_label_count == 0 )
		{
		/* Perform initial allocation of storage */
		case_label_array = (void **) malloc( case_label_array_limit * sizeof(void *) );
		}
	else if( case_label_count == case_label_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( case_label_array_limit * sizeof(void *) );

		for( i=0 ; i<case_label_count ; i++ )
			{
			temp_array[i] = case_label_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( case_label_array );
		case_label_array = (void **) malloc( (case_label_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<case_label_count ; i++ )
			{
			case_label_array[i] = temp_array[i];
			}

		/* Change case_label_array_limit to reflect new array size */
		case_label_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", case_label_count, arg );

	case_label_array[case_label_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "case_label_array[%d]= %x\n", case_label_count, arg );

	case_label_count++;

	return( 0 );

}


int load_switch_body_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( switch_body_count == 0 )
		{
		/* Perform initial allocation of storage */
		switch_body_array = (void **) malloc( switch_body_array_limit * sizeof(void *) );
		}
	else if( switch_body_count == switch_body_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( switch_body_array_limit * sizeof(void *) );

		for( i=0 ; i<switch_body_count ; i++ )
			{
			temp_array[i] = switch_body_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( switch_body_array );
		switch_body_array = (void **) malloc( (switch_body_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<switch_body_count ; i++ )
			{
			switch_body_array[i] = temp_array[i];
			}

		/* Change switch_body_array_limit to reflect new array size */
		switch_body_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", switch_body_count, arg );

	switch_body_array[switch_body_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "switch_body_array[%d]= %x\n", switch_body_count, arg );

	switch_body_count++;

	return( 0 );

}


int load_member_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( member_count == 0 )
		{
		/* Perform initial allocation of storage */
		member_array = (void **) malloc( member_array_limit * sizeof(void *) );
		}
	else if( member_count == member_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( member_array_limit * sizeof(void *) );

		for( i=0 ; i<member_count ; i++ )
			{
			temp_array[i] = member_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( member_array );
		member_array = (void **) malloc( (member_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<member_count ; i++ )
			{
			member_array[i] = temp_array[i];
			}

		/* Change member_array_limit to reflect new array size */
		member_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", member_count, arg );

	member_array[member_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "memberr_array[%d]= %x\n", member_count, arg );

	member_count++;

	return( 0 );

}

int load_enumerator_array( char *arg )
{
	char		**temp_enumerator_array;
	int			i;

	/* Handle special values of count */
	if( enumerator_count == 0 )
		{
		/* Perform initial allocation of storage. We don't need to allocate storage 
		 * for the char* strings, since that storage already exists and we just 
		 * need to hold a pointer to it. 
		 */
		 enumerator_array = (char **) malloc( enumerator_array_limit * sizeof(char *) );
		/* We should now have an array of 64 char* pointers */
		}
	else if( enumerator_count == enumerator_array_limit )
		{
		/* We need to increase the size of the array */
		/* Create temporary storage and recreate the array */
		temp_enumerator_array = (char **) malloc( enumerator_array_limit * sizeof(char *) );

		for( i=0 ; i<enumerator_count ; i++ )
			{
			temp_enumerator_array[i] = enumerator_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( enumerator_array );
		enumerator_array = (char **) malloc( (enumerator_array_limit + 64) * sizeof(char *) );
		
		/* Now reload: */ 
		for( i=0 ; i<enumerator_count ; i++ )
			{
			enumerator_array[i] = temp_enumerator_array[i];
			}

		/* Change enumerator_array_limit to reflect new array size */
		enumerator_array_limit += 64;

		/* free the temp storage */
		free( temp_enumerator_array );
		}

	/* Proceed as usual */
	
	if( (compiler_debug_state == DEBUG_ON) && (arg != NULL) )
		printf( "arg #%d= %s\n", enumerator_count, arg );
	else if( (compiler_debug_state == DEBUG_ON) && (arg == NULL) )
		printf( "arg #%d= (null)\n", enumerator_count );

	enumerator_array[enumerator_count] = arg;

	if( (compiler_debug_state == DEBUG_ON) && (arg != NULL) )
		printf( "enumerator_array[%d]= %s\n", enumerator_count, arg );
	else if( (compiler_debug_state == DEBUG_ON) && (arg == NULL) )
		printf( "enumerator_array[%d]= (null)\n", enumerator_count );

	enumerator_count++;

	return( 0 );

}


int load_string_literal_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( string_literal_count == 0 )
		{
		/* Perform initial allocation of storage */
		string_literal_array = (void **) malloc( string_literal_array_limit * sizeof(void *) );
		}
	else if( string_literal_count == string_literal_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( string_literal_array_limit * sizeof(void *) );

		for( i=0 ; i<string_literal_count ; i++ )
			{
			temp_array[i] = string_literal_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( string_literal_array );
		string_literal_array = (void **) malloc( (string_literal_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<string_literal_count ; i++ )
			{
			string_literal_array[i] = temp_array[i];
			}

		/* Change string_literal_array_limit to reflect new array size */
		string_literal_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", string_literal_count, arg );

	string_literal_array[string_literal_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "string_literal_array[%d]= %x\n", string_literal_count, arg );

	string_literal_count++;

	return( 0 );

}
	   

int load_scoped_name_list_array( char *arg )
{
	char		**temp_array;
	int			i;

	/* Handle special values of count */
	if( scoped_name_list_count == 0 )
		{
		/* Perform initial allocation of storage. */
		scoped_name_list_array = (char **) malloc( scoped_name_list_array_limit * sizeof(char *) );
		}
	else if( scoped_name_list_count == scoped_name_list_array_limit )
		{
		/* We need to increase the size of the array */
		/* Create temporary storage and recreate the array */
		temp_array = (char **) malloc( scoped_name_list_array_limit * sizeof(char *) );

		for( i=0 ; i<scoped_name_list_count ; i++ )
			{
			temp_array[i] = scoped_name_list_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( scoped_name_list_array );
		scoped_name_list_array = (char **) malloc( (scoped_name_list_array_limit + 64) * sizeof(char *) );
		
		/* Now reload: */ 
		for( i=0 ; i<scoped_name_list_count ; i++ )
			{
			scoped_name_list_array[i] = temp_array[i];
			}

		/* Change scoped_name_list_array_limit to reflect new array size */
		scoped_name_list_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( (compiler_debug_state == DEBUG_ON) && (arg != NULL) )
		printf( "arg #%d= %s\n", scoped_name_list_count, arg );
	else if( (compiler_debug_state == DEBUG_ON) && (arg == NULL) )
		printf( "arg #%d= (null)\n", scoped_name_list_count );

	scoped_name_list_array[scoped_name_list_count] = arg;

	if( (compiler_debug_state == DEBUG_ON) && (arg != NULL) )
		printf( "scoped_name_list_array[%d]= %s\n", scoped_name_list_count, arg );
	else if( (compiler_debug_state == DEBUG_ON) && (arg == NULL) )
		printf( "scoped_name_list_array[%d]= (null)\n", scoped_name_list_count );

	scoped_name_list_count++;

	return( 0 );

}


int load_scoped_name_array( void *arg )
{
	void		**temp_array;
	int			i;

	/* Handle special values of count */
	if( scoped_name_count == 0 )
		{
		/* Perform initial allocation of storage */
		scoped_name_array = (void **) malloc( scoped_name_array_limit * sizeof(void *) );
		}
	else if( scoped_name_count == scoped_name_array_limit )
		{
		/* We need to increase the size of the array. Create temp storage and recreate the array */
		temp_array = (void **) malloc( scoped_name_array_limit * sizeof(void *) );

		for( i=0 ; i<scoped_name_count ; i++ )
			{
			temp_array[i] = scoped_name_array[i];
			}

		/* free the original array and recreate it with the new size */
		free( scoped_name_array );
		scoped_name_array = (void **) malloc( (scoped_name_array_limit + 64) * sizeof(void *) );
		
		/* Now reload: */ 
		for( i=0 ; i<scoped_name_count ; i++ )
			{
			scoped_name_array[i] = temp_array[i];
			}

		/* Change scoped_name_array_limit to reflect new array size */
		scoped_name_array_limit += 64;

		/* free the temp storage */
		free( temp_array );
		}

	/* Proceed as usual */

	if( compiler_debug_state == DEBUG_ON )printf( "arg #%d= %x\n", scoped_name_count, arg );

	scoped_name_array[scoped_name_count] = arg;

	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name_array[%d]= %x\n", scoped_name_count, arg );

	scoped_name_count++;

	return( 0 );

}


void *Scoped_Name_buildHandler()
{	
	/* 
	 * Since a scoped_name object is built when a rule match is found, and these objects
	 * are built the same way each time, and since there are several places where 
	 * these objects are built, the common code for this process has been 
	 * offloaded to this function.
	 */
	
	void		*ptr;

	/* Since the scoped_name arrays are global, we can access them directly: */
	/* We must also include the state of the scoped_name_scope_flag as an argument, as this */
	/* will affect the type of object which is built for the GSI object model */
	ptr = buildScoped_Name( scoped_name_list_array, scoped_name_list_count, scoped_name_scope_flag );

	/* Handle reset details */
	reset_char_array( &scoped_name_list_array, &scoped_name_list_count, &scoped_name_list_array_limit );

	/* Set this flag back to initial value */
	scoped_name_scope_flag = RELATIVE_SCOPE;
										
   	return( ptr );

}


int reset_char_array( char ***char_array, int *array_count, int *array_limit )
{
	/* We are passing in arguments for global variables */
	
	/*Free the memory */
	free( *char_array );

	/*Set pointer to NULL to indicate that it has been freed */
	*char_array = NULL;
	
	/*Reset the count*/																			  
	*array_count = 0;

	/*Reset the array limit*/
    *array_limit = 64;

	return( 0 );
}


int reset_void_array( void ***void_array, int *array_count, int *array_limit )
{
	/* We are passing in arguments for global variables */
	
	/*Free the memory */
	free( *void_array );

	/*Set pointer to NULL to indicate that it has been freed */
	*void_array = NULL;
	
	/*Reset the count*/																			  
	*array_count = 0;

	/*Reset the array limit*/
    *array_limit = 64;

	return( 0 );																	 
}


void parser_initialize()
{
	/* 
	 * This function will initialize all of the global arrays, counters, 
	 * and variables used in building the parse tree. It should be called 
	 * before each invocation of the yyparse() function.  
	 */

	/* Setting the pointers to NULL indicates they have yet to have any 
	   storage allocated for them */

	/* We assume here that all previously allocated memory has been freed */

	/* For: attr_dcl */
	attr_dcl_array = NULL;
	attr_dcl_count = 0;
	attr_dcl_array_limit = 64;

	/* For: declarators */
	declarator_array = NULL;
	declarator_count = 0;
	declarator_array_limit = 64;

	/* For: fixed_array_size */
	fixed_array_size_array = NULL;
	fixed_array_size_count = 0;
	fixed_array_size_array_limit = 64;

	/* For: case_label */
	case_label_array = NULL;
	case_label_count = 0;
	case_label_array_limit = 64;

	/* For: switch_body */
	switch_body_array = NULL;
	switch_body_count = 0;
	switch_body_array_limit = 64;

	/* For: member */
	member_array = NULL;		
	member_count = 0;
	member_array_limit = 64;

	/* For: enumerator */
	enumerator_array = NULL;
	enumerator_count = 0;
	enumerator_array_limit = 64;

	/* For: module - definition */
	module_definition_array = NULL;
	module_definition_count = 0;
	module_definition_array_limit = 64;

	/* For: scoped_name_list (internal, per scoped_name object) */
	scoped_name_list_array = NULL;
	scoped_name_list_count = 0;
	scoped_name_list_array_limit = 64;

	/* For: scoped_name (external, an array of scoped_name objects) */
	scoped_name_array = NULL;
	scoped_name_count = 0;
	scoped_name_array_limit = 64;

	/* For: op_dcl */
	param_dcl_array = NULL;
	param_dcl_count = 0;
	param_dcl_array_limit = 64;

	/* For: context_expr */
	string_literal_array = NULL;
	string_literal_count = 0;
	string_literal_array_limit = 64;

	/*****End: Global Data for use by the Production Rules*****/

	/*****Miscalleaneous Global Data*****/
	scoped_name_scope_flag = RELATIVE_SCOPE;

	printf( "Parser Initialization Completed.\n\n" );

	return;

}


void parser_cleanup()
{
	/* 
	 * This function will deallocate all of the global array memory which 
	 * has been allocated. This function should be called after yyparse()
	 * completes successfully or if a parse error occurs.
	 */
	
	/* 
	 * When any memory is freed, its pointer should be set to NULL, so we 
	 * can check if the memory needs to be freed by whether it is non-NULL 
	 * or not.
	 */
	
	/* For: attr_dcl */
	if( attr_dcl_array != NULL )
		free( attr_dcl_array );
	

	/* For: declarators */
	if( declarator_array != NULL )
		free( declarator_array );
	

	/* For: fixed_array_size */
	if( fixed_array_size_array != NULL )
		free( fixed_array_size_array );
	

	/* For: case_label */
	if( case_label_array != NULL )
		free( case_label_array );
	

	/* For: switch_body */
	if( switch_body_array != NULL )
		free( switch_body_array );
	

	/* For: member */
	if( member_array != NULL )
		free( member_array );		

	
	/* For: enumerator */
	if( enumerator_array != NULL )
		free( enumerator_array ); 
	

	/* For: module - definition */
	if( module_definition_array != NULL )
		free( module_definition_array );


	/* For: scoped_name_list (internal, per scoped_name object) */
	if( scoped_name_list_array != NULL )
		free( scoped_name_list_array );


	/* For: scoped_name (external, an array of scoped_name objects) */
	if( scoped_name_array != NULL )
		free( scoped_name_array );

	/* For: op_dcl */
	if( param_dcl_array != NULL )
		free( param_dcl_array );

	/* For: context_expr */
	if( string_literal_array != NULL )
		free( string_literal_array );

	printf( "Parser Cleanup completed...\n\n" );


	/*****End: Global Data for use by the Production Rules*****/

	return;

}


int yyerror (s)  /* Called by yyparse on error */
     char *s;
{
	/* if( (compiler_debug_state == DEBUG_ON) && (s != NULL) )printf ("yerror(): You fucked up! \n%s\n", s); */
 
	/* Present relevant information regarding the syntax error and perform memory clean-up */
	parser_error_handler();

	return( 0 );
}