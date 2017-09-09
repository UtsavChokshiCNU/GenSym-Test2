
/*  A Bison parser, made from exp11a.y  */

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

#line 4 "exp11a.y"


/*
C declarations
The C declarations may define types and variables used in the actions. You can also use 
preprocessor commands to define macros used there, and use #include to include header files 
that do any of these things.
*/
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <windowsx.h>
#include "yacc_supp.h"

extern int yylex();
extern void buildInterface();


/*****Global Data for use by the Production Rules*****/
/*@@@@@@@@ MAKE THESE ARRAYS ALL 'static" TO LIMIT VISIBILITY TO THIS FILE!!! @@@@@@@@@*/
/* For: attr_dcl */
char	*attr_dcl_array[64];
int		attr_dcl_count = 0;

/* For: enumerator */
char	*enumerator_array[64];
int		enumerator_count = 0;

/* For: op_dcl */
param_dcl_struct	*param_dcl_array[64];
int		param_dcl_count = 0;

/* For: export */
export_dcl_type_node	*export_array[64];
int		export_count = 0;

/* For: type_dcl */
nodeType2	*type_dcl_array[64];
int		type_dcl_count = 0;

/* For: interface */

/*****End: Global Data for use by the Production Rules*****/




#line 61 "exp11a.y"
typedef union 
	{
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
	char			*interface_header[2];	/* Holds: xINTERFACE xIDENTIFIER */
	sAttributeNode	*sAttributeNode_ptr;
	sOperationNode	*sOperationNode_ptr;
	sEnumeratorNode	*sEnumeratorNode_ptr;
	nodeType2		*nodeType2_ptr;
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



#define	YYFINAL		294
#define	YYFLAG		-32768
#define	YYNTBASE	80

#define YYTRANSLATE(x) ((unsigned)(x) <= 313 ? yytranslate[x] : 165)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    62,    72,     2,    74,
    75,    60,    59,    68,    58,     2,    61,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    67,    64,    76,
    69,    77,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    78,     2,    79,    71,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    65,    70,    66,    73,     2,     2,     2,     2,
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
    56,    57,    63
};

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   143,   144,   150,   151,   152,   153,   154,   157,   160,   161,
   164,   190,   193,   194,   197,   198,   201,   209,   210,   211,
   219,   229,   230,   233,   234,   237,   238,   239,   242,   245,
   246,   247,   248,   249,   250,   253,   256,   257,   260,   261,
   264,   265,   268,   269,   270,   273,   274,   275,   278,   279,
   280,   281,   284,   285,   288,   289,   290,   293,   294,   295,
   298,   299,   300,   301,   302,   305,   306,   309,   312,   313,
   314,   315,   326,   329,   330,   333,   334,   335,   339,   340,
   341,   342,   343,   344,   347,   348,   351,   352,   353,   356,
   357,   361,   362,   365,   366,   369,   372,   376,   377,   381,
   382,   386,   387,   391,   395,   399,   400,   404,   408,   412,
   416,   420,   424,   427,   430,   431,   434,   437,   441,   442,
   443,   444,   445,   448,   449,   452,   455,   456,   459,   460,
   463,   466,   482,   483,   486,   489,   490,   493,   494,   497,
   500,   501,   504,   518,   532,   548,   549,   552,   553,   556,
   557,   560,   578,   579,   580,   581,   597,   598,   599,   602,
   605,   606,   619,   620,   623,   624,   627,   646,   647,   648,
   651,   652,   655,   656,   659,   660,   663,   664,   668,   669,
   670
};

static const char * const yytname[] = {     0,
"error","$illegal.","xANY","xATTRIBUTE","xBOOLEAN","xCASE","xCHAR","xCONST","xCONTEXT","xDEFAULT",
"xDOUBLE","xENUM","xEXCEPTION","xFALSE","xFLOAT","xIN","xINOUT","xINTERFACE","xLONG","xMODULE",
"xOBJECT","xOCTET","xONEWAY","xOUT","xRAISES","xREADONLY","xSEQUENCE","xSHORT","xSTRING","xSTRUCT",
"xSWITCH","xTRUE","xTYPEDEF","xUNSIGNED","xUNION","xVOID","OPERATOR","PUNCTUATOR","LITERAL","IDENTIFIER",
"KEYWORD","LITERAL_DECINT","LITERAL_HEXINT","LITERAL_OCTINT","LITERAL_FP","LITERAL_CHAR","LITERAL_CHARHEX","LITERAL_CHAROCT","LITERAL_STRING","DOUBLE_COLON",
"DOUBLE_LT","DOUBLE_GT","FLOATING_PT_LITERAL","CHARACTER_LITERAL","STRING_LITERAL","INTEGER_LITERAL","xIDENTIFIER","'-'","'+'","'*'",
"'/'","'%'","NEG","';'","'{'","'}'","':'","','","'='","'|'",
"'^'","'&'","'~'","'('","')'","'<'","'>'","'['","']'","specification"
};
#endif

static const short yyr1[] = {     0,
    80,    80,    81,    81,    81,    81,    81,    82,    83,    83,
    84,    85,    86,    86,    87,    87,    88,    88,    88,    88,
    88,    89,    89,    90,    90,    91,    91,    91,    92,    93,
    93,    93,    93,    93,    93,    94,    95,    95,    96,    96,
    97,    97,    98,    98,    98,    99,    99,    99,   100,   100,
   100,   100,   101,   101,   102,   102,   102,   103,   103,   103,
   104,   104,   104,   104,   104,   105,   105,   106,   107,   107,
   107,   107,   108,   109,   109,   110,   110,   110,   111,   111,
   111,   111,   111,   111,   112,   112,   113,   113,   113,   114,
   114,   115,   115,   116,   116,   117,   118,   119,   119,   120,
   120,   121,   121,   122,   123,   124,   124,   125,   126,   127,
   128,   129,   130,   131,   132,   132,   133,   134,   135,   135,
   135,   135,   135,   136,   136,   137,   138,   138,   139,   139,
   140,   141,   142,   142,   143,   144,   144,   145,   145,   146,
   147,   147,   148,   149,   149,   150,   150,   151,   151,   152,
   152,   153,   153,   153,   153,   153,   153,   153,   153,   154,
   155,   155,   156,   156,   157,   157,   158,   159,   159,   159,
   160,   160,   161,   161,   162,   162,   163,   163,   164,   164,
   164
};

static const short yyr2[] = {     0,
     1,     2,     2,     2,     2,     2,     2,     5,     1,     1,
     4,     2,     2,     3,     0,     2,     2,     2,     2,     2,
     2,     2,     3,     2,     3,     1,     2,     3,     5,     1,
     1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
     1,     3,     1,     3,     3,     1,     3,     3,     1,     3,
     3,     3,     2,     1,     1,     1,     1,     1,     1,     3,
     1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
     1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     2,     2,     3,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
     1,     1,     1,     5,     1,     2,     3,     9,     1,     1,
     1,     1,     1,     1,     2,     3,     1,     2,     3,     2,
     2,     5,     1,     3,     1,     6,     4,     4,     1,     2,
     1,     2,     3,     3,     4,     1,     3,     4,     5,     1,
     2,     3,     4,     4,     5,     4,     5,     5,     6,     1,
     1,     1,     3,     2,     1,     3,     3,     1,     1,     1,
     4,     5,     2,     3,     4,     5,     2,     3,     1,     1,
     1
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
     0,     0,     9,    10,     0,     0,     0,    70,    71,    72,
     0,   111,   110,    99,    98,   104,   105,   139,     0,     0,
    26,    35,     0,    33,    30,   100,   102,   103,   101,   106,
   107,    31,    32,    34,     0,     0,    12,     0,     0,   113,
   112,     0,    78,    69,     0,    74,    76,    77,    75,    79,
    80,    81,    82,    83,    84,    87,    88,    89,    85,    86,
     0,     2,     7,     6,    15,     4,     3,     5,     0,   108,
   109,    27,     0,     0,     0,     0,     0,    14,     0,     0,
     0,    96,    73,    90,    94,    95,    97,     0,     0,    67,
    66,    64,    63,    62,    61,    55,    56,    57,     0,    58,
    68,    36,    37,    39,    41,    43,    46,    49,     0,    54,
    59,    65,     0,    28,     0,   135,     0,   133,   148,     0,
   150,     0,    22,     0,     0,   115,     0,     0,   140,   141,
     0,    91,     0,     0,   160,     0,   162,    11,    16,   181,
     0,     0,   179,   180,     0,     0,     0,     0,     0,   161,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    53,   138,    29,   132,     0,     0,   149,   151,     0,
    23,     8,   114,   116,     0,   137,     0,   142,    92,     0,
   123,   119,   120,   121,     0,   122,     0,     0,    18,    17,
    20,    19,    21,     0,     0,    60,    38,    40,    42,    45,
    44,    48,    47,    50,    51,    52,   134,   117,    24,     0,
     0,   143,    93,     0,    96,   146,   144,     0,     0,     0,
   152,    25,   136,     0,     0,   145,   156,   168,   170,   169,
   164,     0,   165,     0,     0,     0,   153,   154,     0,     0,
     0,   124,     0,   127,   147,   157,   158,     0,   163,     0,
     0,     0,   155,     0,   130,   118,   125,     0,   128,     0,
   159,   166,   167,     0,     0,   129,   131,   126,     0,   175,
     0,     0,   171,     0,   177,     0,   176,   173,     0,   172,
   178,   174,     0,     0
};

static const short yydefgoto[] = {     9,
    10,    11,    12,    13,    14,    15,    99,   149,    88,   181,
   110,    16,    33,   111,   112,   113,   114,   115,   116,   117,
   118,   119,   120,   121,   122,   123,    17,    54,   130,    56,
    57,    58,    59,    93,   142,    94,    95,    96,    60,    61,
    36,    37,    38,    39,    40,    41,    62,    63,    64,    65,
    66,   135,   131,    67,   195,   251,   252,   253,   254,   270,
    68,   127,   128,    69,    70,    97,   139,   140,   155,   227,
    21,   132,   157,   158,   159,   231,   242,   243,   244,   247,
   284,   248,   281,   160
};

static const short yypact[] = {   450,
   308,   -36,     0,    14,    25,    27,   352,    30,   403,-32768,
   -35,   -13,-32768,-32768,    42,    57,    61,-32768,-32768,-32768,
    66,-32768,-32768,-32768,-32768,-32768,-32768,    19,    13,    76,
-32768,    94,    96,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    90,    91,     9,    93,    95,-32768,
-32768,    78,    94,-32768,   107,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   136,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   243,-32768,
-32768,-32768,   111,   103,   117,    31,   -24,-32768,   450,   352,
   385,    97,-32768,   108,-32768,-32768,-32768,   104,   158,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   243,    94,
-32768,   112,   114,   118,    60,    77,    58,-32768,   254,-32768,
-32768,-32768,   106,-32768,   243,-32768,    56,-32768,-32768,   107,
-32768,   198,   -33,   123,   255,-32768,   -28,   243,    97,-32768,
   107,   127,    89,   445,-32768,   192,-32768,-32768,-32768,    94,
   134,   138,-32768,-32768,   140,   142,   143,   415,   154,-32768,
   125,   243,   243,   243,   243,   243,   243,   243,   243,   243,
   243,-32768,-32768,-32768,-32768,   117,   148,-32768,-32768,   -24,
   146,-32768,-32768,-32768,   243,-32768,   137,-32768,-32768,   107,
    94,-32768,-32768,-32768,   147,-32768,   161,   445,-32768,-32768,
-32768,-32768,-32768,   164,   149,-32768,   114,   118,    60,    77,
    77,    58,    58,-32768,-32768,-32768,-32768,-32768,    94,   -24,
   152,-32768,-32768,   165,-32768,-32768,   163,   161,   149,    51,
    22,    94,-32768,    73,   161,   163,    22,-32768,-32768,-32768,
-32768,     5,-32768,   445,   160,   162,   226,-32768,   243,   170,
    12,-32768,   319,-32768,-32768,   226,-32768,    39,-32768,   161,
   183,   -24,-32768,   172,-32768,-32768,-32768,   107,-32768,   176,
-32768,-32768,-32768,    24,   -31,-32768,-32768,-32768,   186,-32768,
    38,   -24,-32768,    41,-32768,   187,-32768,    94,   -24,-32768,
-32768,    94,   244,-32768
};

static const short yypgoto[] = {-32768,
     2,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    -1,   150,-32768,   -97,-32768,    84,    87,    92,   -25,   -30,
   -42,-32768,   132,-32768,-32768,  -115,   155,-32768,    -6,   168,
   -96,-32768,-32768,   133,-32768,  -136,  -183,-32768,   252,     6,
-32768,-32768,-32768,-32768,-32768,-32768,     7,     8,-32768,-32768,
    15,-32768,   -63,    16,-32768,-32768,    18,-32768,    20,-32768,
     4,-32768,   100,-32768,     1,-32768,-32768,   126,-32768,    43,
   173,-32768,-32768,-32768,   120,    50,-32768,    29,-32768,    54,
-32768,  -217,-32768,  -134
};


#define	YYLAST		502


static const short yytable[] = {    32,
    55,    44,   153,    20,   189,    53,    35,    42,    43,   197,
    72,   161,    20,   226,    18,    19,    83,   249,    83,   257,
    45,   250,   187,    18,    19,    30,   136,   174,    73,   263,
   245,    80,    31,    50,   180,    22,   282,    23,   271,   185,
    81,    24,     2,   283,   226,    25,   246,   153,   186,    26,
    74,   255,    51,   223,   238,   239,    46,    52,    27,    28,
     6,   153,   240,   228,    29,     8,   238,   239,   179,   221,
    47,   184,   258,   -13,   240,    87,   273,   266,   249,   259,
    30,    48,   250,    49,    53,   133,    71,    31,    53,    53,
   134,   279,    20,    22,    79,    23,   129,   150,   280,   154,
     2,   153,    20,    18,    19,   286,    75,    26,   289,   260,
   165,   166,   287,    18,    19,   290,    27,   169,   170,   171,
    76,   175,    29,   176,    77,   241,   214,   215,   216,    78,
    53,   277,    82,    53,   167,   168,   212,   213,    30,   210,
   211,   191,   150,    83,   154,    31,   196,   153,   192,   193,
   194,   264,    84,    91,    85,    86,   150,    89,   154,    90,
    50,   144,    22,    92,    23,     1,    98,   124,    24,     2,
     3,   125,    25,   126,   138,   141,    26,   143,   219,    51,
   145,   162,   173,   146,   163,    27,    28,     6,   182,   164,
     7,    29,     8,   147,   190,   198,   150,   199,   154,   206,
    50,   200,    22,   201,    23,   202,   203,    30,    24,     2,
   205,   218,    25,   220,    31,   222,    26,   225,   232,    51,
   229,   224,   230,   148,    52,    27,    28,     6,   233,   234,
   235,    29,     8,   261,   245,   262,   265,   274,   276,   278,
   285,   291,   150,   294,   154,   207,   268,    30,   151,   208,
   172,    53,    34,   152,    31,   209,   100,    50,   137,    22,
   275,    23,   177,   178,   188,    24,     2,   100,   267,    25,
   236,   156,   269,    26,   101,   217,    51,   204,   237,     0,
   288,    52,    27,    28,     6,   101,   272,   292,    29,     8,
   256,     0,    30,     0,     0,   102,   103,   104,   105,    31,
   106,   107,     0,    30,    30,     0,   102,   103,   104,   105,
    31,    31,    22,     0,    23,   108,   109,     0,    24,     0,
   183,    50,    25,    22,   249,    23,    26,   109,   250,    24,
     2,     0,     0,    25,     0,    27,    28,    26,     0,     0,
    51,    29,     0,     0,     0,    52,    27,    28,     6,     0,
     0,     0,    29,     8,    50,     0,    22,    30,    23,     0,
     0,     0,    24,     2,    31,     0,    25,     0,    30,     0,
    26,     0,     0,    51,     0,    31,     0,     0,    52,    27,
    28,     6,     0,     0,     0,    29,     8,    50,     0,    22,
     0,    23,     0,     0,     0,    24,     0,     0,     0,    25,
     0,    30,   293,    26,     0,     0,    51,     0,    31,     0,
     1,    52,    27,    28,     2,     3,     0,    50,    29,    22,
     4,    23,     5,     0,     0,    24,     0,     0,     0,    25,
     0,     0,     6,    26,    30,     7,    51,     8,     0,     0,
     0,    31,    27,    28,     0,     0,     0,    50,    29,    22,
   147,    23,     0,     0,     0,    24,     0,     1,     0,    25,
     0,     2,     3,    26,    30,     0,    51,     4,     0,     5,
     0,    31,    27,    28,     0,     0,     0,     0,    29,     6,
     0,     0,     7,     0,     8,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
     0,    31
};

static const short yycheck[] = {     1,
     7,     1,    99,     0,   141,     7,     1,     1,     1,   144,
     9,   109,     9,   197,     0,     0,    50,     6,    50,   237,
    57,    10,   138,     9,     9,    50,    90,   125,    64,   247,
     9,    19,    57,     3,    68,     5,    68,     7,   256,    68,
    28,    11,    12,    75,   228,    15,    25,   144,    77,    19,
    64,   235,    22,   190,    16,    17,    57,    27,    28,    29,
    30,   158,    24,   198,    34,    35,    16,    17,   132,   185,
    57,   135,    68,    65,    24,    67,   260,    66,     6,    75,
    50,    57,    10,    57,    86,    87,    57,    57,    90,    91,
    89,    68,    89,     5,    76,     7,    66,    99,    75,    99,
    12,   198,    99,    89,    89,    68,    65,    19,    68,   244,
    51,    52,    75,    99,    99,    75,    28,    60,    61,    62,
    64,    66,    34,    68,    64,    75,   169,   170,   171,    64,
   132,   268,    57,   135,    58,    59,   167,   168,    50,   165,
   166,   143,   144,    50,   144,    57,   143,   244,   143,   143,
   143,   249,    57,    76,    65,    65,   158,    65,   158,    65,
     3,     4,     5,    57,     7,     8,    31,    57,    11,    12,
    13,    69,    15,    57,    78,    68,    19,    74,   180,    22,
    23,    70,    77,    26,    71,    28,    29,    30,    66,    72,
    33,    34,    35,    36,    68,     4,   198,    64,   198,    75,
     3,    64,     5,    64,     7,    64,    64,    50,    11,    12,
    57,    64,    15,    68,    57,    79,    19,    57,   220,    22,
    57,    75,    74,    66,    27,    28,    29,    30,    77,    65,
    68,    34,    35,    74,     9,    74,    67,    55,    67,    64,
    55,    55,   244,     0,   244,   162,   253,    50,    99,   163,
   119,   253,     1,    99,    57,   164,    14,     3,    91,     5,
   262,     7,   130,    66,   139,    11,    12,    14,   251,    15,
   228,    99,   253,    19,    32,   176,    22,   158,   229,    -1,
   282,    27,    28,    29,    30,    32,   258,   289,    34,    35,
   237,    -1,    50,    -1,    -1,    53,    54,    55,    56,    57,
    58,    59,    -1,    50,    50,    -1,    53,    54,    55,    56,
    57,    57,     5,    -1,     7,    73,    74,    -1,    11,    -1,
    66,     3,    15,     5,     6,     7,    19,    74,    10,    11,
    12,    -1,    -1,    15,    -1,    28,    29,    19,    -1,    -1,
    22,    34,    -1,    -1,    -1,    27,    28,    29,    30,    -1,
    -1,    -1,    34,    35,     3,    -1,     5,    50,     7,    -1,
    -1,    -1,    11,    12,    57,    -1,    15,    -1,    50,    -1,
    19,    -1,    -1,    22,    -1,    57,    -1,    -1,    27,    28,
    29,    30,    -1,    -1,    -1,    34,    35,     3,    -1,     5,
    -1,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,
    -1,    50,     0,    19,    -1,    -1,    22,    -1,    57,    -1,
     8,    27,    28,    29,    12,    13,    -1,     3,    34,     5,
    18,     7,    20,    -1,    -1,    11,    -1,    -1,    -1,    15,
    -1,    -1,    30,    19,    50,    33,    22,    35,    -1,    -1,
    -1,    57,    28,    29,    -1,    -1,    -1,     3,    34,     5,
    36,     7,    -1,    -1,    -1,    11,    -1,     8,    -1,    15,
    -1,    12,    13,    19,    50,    -1,    22,    18,    -1,    20,
    -1,    57,    28,    29,    -1,    -1,    -1,    -1,    34,    30,
    -1,    -1,    33,    -1,    35,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
    -1,    57
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/lib/bison.simple"

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

#line 131 "/usr/local/lib/bison.simple"
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
#line 143 "exp11a.y"
{ printf( "specification:case 1\n" );		;
    break;}
case 2:
#line 144 "exp11a.y"
{ printf( "specification:case 2\n" );		;
    break;}
case 3:
#line 150 "exp11a.y"
{ printf( "definition: case 1\n" ); ;
    break;}
case 4:
#line 151 "exp11a.y"
{ printf( "definition: case 2\n" ); ;
    break;}
case 5:
#line 152 "exp11a.y"
{ printf( "definition: case 3\n" ); ;
    break;}
case 6:
#line 153 "exp11a.y"
{ printf( "definition: case 4\n" ); ;
    break;}
case 7:
#line 154 "exp11a.y"
{ printf( "definition: case 5\n" ); ;
    break;}
case 8:
#line 157 "exp11a.y"
{ printf( "module: case 1\n" ); ;
    break;}
case 9:
#line 160 "exp11a.y"
{ printf( "interface: case 1\n" ); ;
    break;}
case 10:
#line 161 "exp11a.y"
{ printf( "interface: case 2\n" ); ;
    break;}
case 11:
#line 165 "exp11a.y"
{ 	
							/* Finally! Build the interface here!! */
							int i;
							printf( "interface_dcl: case 1\n" ); /* RESET export_array AND export_count HERE!! */ 
							printf( "interface_header[0]= %s \t interface_header[1]= %s\n", yyvsp[-3].interface_header[0], yyvsp[-3].interface_header[1] );
							printf( "export_count= %d\n", export_count );
							
							/* Build the interface data model and attach it to the top-level object */
							buildInterface( yyvsp[-3].interface_header, export_array, export_count );

							for( i=0 ; i<export_count ; i++ )
								{
								printf( "export_array[i]= %x\n", export_array[i] );
								/* free() any allocated memory */
								free( export_array[i] );	/* This is the "ptr" variable that is malloced in 'export' */

								/* Reset export_array */
								export_array[i] = NULL;
								}
								
							/* Reset export_count */
							export_count = 0;
							;
    break;}
case 12:
#line 190 "exp11a.y"
{ printf( "interface: case 1:xIDENTIFIER= %s\n", yyvsp[0].str_lit ); ;
    break;}
case 13:
#line 193 "exp11a.y"
{ printf( "interface_header: case 1:xIDENTIFIER= %s\n", yyvsp[0].str_lit ); yyval.interface_header[0] = yyvsp[-1].str_lit; yyval.interface_header[1] = yyvsp[0].str_lit; ;
    break;}
case 14:
#line 194 "exp11a.y"
{ printf( "interface_header: case 2:xIDENTIFIER= %s\n", yyvsp[-1].str_lit ); 
; /* WE WILL NEED A MODEL SIMILAR TO THAT USED FOR THE MULTI DECLARATORS IN attr_dcl */ ;
    break;}
case 15:
#line 197 "exp11a.y"
{ printf( "interface_body: case 1\n" ); ;
    break;}
case 16:
#line 198 "exp11a.y"
{ printf( "interface_body: case 2\n" ); ;
    break;}
case 17:
#line 201 "exp11a.y"
{	export_dcl_type_node	*ptr;
														printf( "export: case 1\n" );
														ptr = (export_dcl_type_node *) malloc( sizeof(export_dcl_type_node) );
														ptr->dcl_type = TYPE_DCL;
														ptr->nodePtr.nodeType2_ptr = yyvsp[-1].nodeType2_ptr;
													   	export_array[export_count] = ptr;
														export_count++;
													;
    break;}
case 18:
#line 209 "exp11a.y"
{ printf( "export: case 2\n" ); ;
    break;}
case 19:
#line 210 "exp11a.y"
{ printf( "export: case 3\n" ); ;
    break;}
case 20:
#line 211 "exp11a.y"
{	export_dcl_type_node	*ptr;
														printf( "export: case 4: attr_dcl:\n" ); 
														ptr = (export_dcl_type_node *) malloc( sizeof(export_dcl_type_node) );
														ptr->dcl_type = ATTR_DCL;
														ptr->nodePtr.sAttributeNode_ptr = yyvsp[-1].sAttributeNode_ptr;
													   	export_array[export_count] = ptr;
														export_count++;		
													;
    break;}
case 21:
#line 219 "exp11a.y"
{	export_dcl_type_node	*ptr;
														printf( "export: case 5: op_dcl:\n" ); 
														ptr = (export_dcl_type_node *) malloc( sizeof(export_dcl_type_node) );
														ptr->dcl_type = OP_DCL;
														ptr->nodePtr.sOperationNode_ptr = yyvsp[-1].sOperationNode_ptr;
													   	export_array[export_count] = ptr;
														export_count++;		
													;
    break;}
case 22:
#line 229 "exp11a.y"
{ printf( "inheritance_spec: case 1\n" ); ;
    break;}
case 23:
#line 230 "exp11a.y"
{ printf( "inheritance_spec: case 2\n" ); ;
    break;}
case 24:
#line 233 "exp11a.y"
{ printf( "aux_1: case 1\n" ); ;
    break;}
case 25:
#line 234 "exp11a.y"
{ printf( "aux_1: case 2\n" ); ;
    break;}
case 26:
#line 237 "exp11a.y"
{ printf( "scoped_name: case 1\n" ); ;
    break;}
case 27:
#line 238 "exp11a.y"
{ printf( "scoped_name: case 2\n" ); ;
    break;}
case 28:
#line 239 "exp11a.y"
{ printf( "scoped_name: case 3\n" ); ;
    break;}
case 29:
#line 242 "exp11a.y"
{ printf( "const_dcl: case 1\n" ); ;
    break;}
case 30:
#line 245 "exp11a.y"
{ printf( "const_type: case 1\n" ); ;
    break;}
case 31:
#line 246 "exp11a.y"
{ printf( "const_type: case 2\n" ); ;
    break;}
case 32:
#line 247 "exp11a.y"
{ printf( "const_type: case 3\n" ); ;
    break;}
case 33:
#line 248 "exp11a.y"
{ printf( "const_type: case 4\n" ); ;
    break;}
case 34:
#line 249 "exp11a.y"
{ printf( "const_type: case 5\n" ); ;
    break;}
case 35:
#line 250 "exp11a.y"
{ printf( "const_type: case 6\n" ); ;
    break;}
case 36:
#line 253 "exp11a.y"
{ printf( "const_exp:case 1\n" );	;
    break;}
case 37:
#line 256 "exp11a.y"
{ printf( "or_expr:case 1\n" );	;
    break;}
case 38:
#line 257 "exp11a.y"
{ printf( "or_expr:case 2\n" );	;
    break;}
case 39:
#line 260 "exp11a.y"
{ printf( "xor_expr:case 1\n" );	;
    break;}
case 40:
#line 261 "exp11a.y"
{ printf( "xor_expr:case 2\n" );	;
    break;}
case 41:
#line 264 "exp11a.y"
{ printf( "and_expr:case 1\n" );	;
    break;}
case 42:
#line 265 "exp11a.y"
{ printf( "and_expr:case 2\n" );	;
    break;}
case 43:
#line 268 "exp11a.y"
{ printf( "shift_expr:case 1\n" );	;
    break;}
case 44:
#line 269 "exp11a.y"
{ printf( "shift_expr:case 2\n" );	;
    break;}
case 45:
#line 270 "exp11a.y"
{ printf( "shift_expr:case 3\n" );	;
    break;}
case 46:
#line 273 "exp11a.y"
{ printf( "add_expr:case 1\n" );	;
    break;}
case 47:
#line 274 "exp11a.y"
{ printf( "add_expr:case 2\n" );	;
    break;}
case 48:
#line 275 "exp11a.y"
{ printf( "add_expr:case 3\n" );	;
    break;}
case 49:
#line 278 "exp11a.y"
{ printf( "mult_expr:case 1\n" );	;
    break;}
case 50:
#line 279 "exp11a.y"
{ printf( "mult_expr:case 2\n" );	;
    break;}
case 51:
#line 280 "exp11a.y"
{ printf( "mult_expr:case 3\n" );	;
    break;}
case 52:
#line 281 "exp11a.y"
{ printf( "mult_expr:case 4\n" );	;
    break;}
case 53:
#line 284 "exp11a.y"
{ printf( "unary_expr:case 1\n" );	;
    break;}
case 54:
#line 285 "exp11a.y"
{ printf( "unary_expr:case 2\n" );	;
    break;}
case 55:
#line 288 "exp11a.y"
{ printf( "unary_operator:case 1\n" );	;
    break;}
case 56:
#line 289 "exp11a.y"
{ printf( "unary_operator:case 2\n" );	;
    break;}
case 57:
#line 290 "exp11a.y"
{ printf( "unary_operator:case 3\n" );	;
    break;}
case 58:
#line 293 "exp11a.y"
{ printf( "primary_expr:case 1\n" );	;
    break;}
case 59:
#line 294 "exp11a.y"
{ printf( "primary_expr:case 2\n" );	;
    break;}
case 60:
#line 295 "exp11a.y"
{ printf( "primary_expr:case 3\n" );	;
    break;}
case 61:
#line 298 "exp11a.y"
{ printf( "literal:case 1\n" );			;
    break;}
case 62:
#line 299 "exp11a.y"
{ printf( "literal:case 2\n" );			;
    break;}
case 63:
#line 300 "exp11a.y"
{ printf( "literal:case 3\n" );			;
    break;}
case 64:
#line 301 "exp11a.y"
{ printf( "literal:case 4\n" );			;
    break;}
case 65:
#line 302 "exp11a.y"
{ printf( "literal:case 5\n" );			;
    break;}
case 66:
#line 305 "exp11a.y"
{ printf( "boolean_literal:case 1\n" );	;
    break;}
case 67:
#line 306 "exp11a.y"
{ printf( "boolean_literal:case 2\n" );	;
    break;}
case 68:
#line 309 "exp11a.y"
{ printf( "positive_int_const:case 1\n" );	;
    break;}
case 69:
#line 312 "exp11a.y"
{ printf( "type_dcl:case 1\n" );	;
    break;}
case 70:
#line 313 "exp11a.y"
{ printf( "type_dcl:case 2\n" );	;
    break;}
case 71:
#line 314 "exp11a.y"
{ printf( "type_dcl:case 3\n" );	;
    break;}
case 72:
#line 315 "exp11a.y"
{	nodeType2	*ptr;
																printf( "type_dcl:case 4:ptr= %x\n", yyvsp[0].sEnumeratorNode_ptr );			
																ptr = (nodeType2 *) malloc( sizeof(nodeType2) );
																ptr->data_type = ENUM_TYPE;
																ptr->u2Ptr.sEnumeratorNode_ptr = yyvsp[0].sEnumeratorNode_ptr;
													   			type_dcl_array[type_dcl_count] = ptr;
																type_dcl_count++;
																yyval.nodeType2_ptr = ptr;		
															;
    break;}
case 73:
#line 326 "exp11a.y"
{ printf( "type_declarator:case 1\n" );	;
    break;}
case 74:
#line 329 "exp11a.y"
{ printf( "type_spec:case 1\n" );	;
    break;}
case 75:
#line 330 "exp11a.y"
{ printf( "type_spec:case 2\n" );	;
    break;}
case 76:
#line 333 "exp11a.y"
{ printf( "simple_type_spec:case 1\n" );	;
    break;}
case 77:
#line 334 "exp11a.y"
{ printf( "simple_type_spec:case 2\n" );	;
    break;}
case 78:
#line 335 "exp11a.y"
{ printf( "simple_type_spec:case 3\n" );	;
    break;}
case 79:
#line 339 "exp11a.y"
{ printf( "base_type_spec:case 1:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 80:
#line 340 "exp11a.y"
{ printf( "base_type_spec:case 2:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 81:
#line 341 "exp11a.y"
{ printf( "base_type_spec:case 3:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 82:
#line 342 "exp11a.y"
{ printf( "base_type_spec:case 4:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 83:
#line 343 "exp11a.y"
{ printf( "base_type_spec:case 5:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 84:
#line 344 "exp11a.y"
{ printf( "base_type_spec:case 6:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 85:
#line 347 "exp11a.y"
{ printf( "template_type_spec:case 1\n" );	;
    break;}
case 86:
#line 348 "exp11a.y"
{ printf( "template_type_spec:case 2\n" );		;
    break;}
case 87:
#line 351 "exp11a.y"
{ printf( "constr_type_spec:case 1\n" );	;
    break;}
case 88:
#line 352 "exp11a.y"
{ printf( "constr_type_spec:case 2\n" );	;
    break;}
case 89:
#line 353 "exp11a.y"
{ printf( "constr_type_spec:case 3:$1= %x\n", yyvsp[0].sEnumeratorNode_ptr );	yyval.tok_val=yyvsp[0].sEnumeratorNode_ptr;		;
    break;}
case 90:
#line 356 "exp11a.y"
{ printf( "declarators:case 1\n" );	;
    break;}
case 91:
#line 357 "exp11a.y"
{ printf( "declarators:case 2\n" );	;
    break;}
case 92:
#line 361 "exp11a.y"
{ printf( "aux_2: case 1\n" ); ;
    break;}
case 93:
#line 362 "exp11a.y"
{ printf( "aux_2: case 2\n" ); ;
    break;}
case 94:
#line 365 "exp11a.y"
{ printf( "declarator:case 1\n" );	;
    break;}
case 95:
#line 366 "exp11a.y"
{ printf( "declarator:case 2\n" );	;
    break;}
case 96:
#line 369 "exp11a.y"
{ printf( "simple_declarator:case 1:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 97:
#line 372 "exp11a.y"
{ printf( "complex_declarator:case 1\n" );	;
    break;}
case 98:
#line 376 "exp11a.y"
{ printf( "Got: xFLOAT:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 99:
#line 377 "exp11a.y"
{ printf( "Got: xDOUBLE:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 100:
#line 381 "exp11a.y"
{ printf( "integer_type:signed_int:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 101:
#line 382 "exp11a.y"
{ printf( "integer_type:unsigned_int:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 102:
#line 386 "exp11a.y"
{ printf( "signed_int:signed_long_int:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 103:
#line 387 "exp11a.y"
{ printf( "signed_int:signed_short_int:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 104:
#line 391 "exp11a.y"
{ printf( "Got: xLONG: $1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 105:
#line 395 "exp11a.y"
{ printf( "Got: xSHORT: $1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 106:
#line 399 "exp11a.y"
{ printf( "unsigned_long_int:unsigned_long_int:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 107:
#line 400 "exp11a.y"
{ printf( "unsigned_short_int:unsigned_short_int:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 108:
#line 404 "exp11a.y"
{ strcat( yyvsp[-1].str_lit, " " ); strcat( yyvsp[-1].str_lit, yyvsp[0].str_lit ); yyval.str_lit=yyvsp[-1].str_lit; printf( "Got: xUNSIGNED xLONG:$1= %s, $2= %s, $$= %>>s<<\n", yyvsp[-1].str_lit, yyvsp[0].str_lit, yyval.str_lit ); ;
    break;}
case 109:
#line 408 "exp11a.y"
{ strcat( yyvsp[-1].str_lit, " " ); strcat( yyvsp[-1].str_lit, yyvsp[0].str_lit ); yyval.str_lit=yyvsp[-1].str_lit; printf( "Got: xUNSIGNED xSHORT:$1= %s, $2= %s, $$= %>>s<<\n", yyvsp[-1].str_lit, yyvsp[0].str_lit, yyval.str_lit ); ;
    break;}
case 110:
#line 412 "exp11a.y"
{ printf( "Got: xCHAR: $1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 111:
#line 416 "exp11a.y"
{ printf( "Got: xBOOLEAN: $1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 112:
#line 420 "exp11a.y"
{ printf( "Got: xOCTET: $1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 113:
#line 424 "exp11a.y"
{ printf( "Got: xANY: $1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 114:
#line 427 "exp11a.y"
{ printf( "struct_type:Got: xSTRUCT: $1= %ld\n", yyvsp[-4].str_lit );	;
    break;}
case 115:
#line 430 "exp11a.y"
{ printf( "member_list:case 1\n" );	;
    break;}
case 116:
#line 431 "exp11a.y"
{ printf( "member_list:case 2\n" );	;
    break;}
case 117:
#line 434 "exp11a.y"
{ printf( "member:case 1\n" );	;
    break;}
case 118:
#line 437 "exp11a.y"
{ printf( "%s\n", "fucking union_type!" ); ;
    break;}
case 119:
#line 441 "exp11a.y"
{ printf( "switch_type_spec: case 1:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 120:
#line 442 "exp11a.y"
{ printf( "switch_type_spec: case 2:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 121:
#line 443 "exp11a.y"
{ printf( "switch_type_spec: case 3:$1= %s\n", yyvsp[0].str_lit );		yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 122:
#line 444 "exp11a.y"
{ printf( "switch_type_spec: case 4:$1= %x\n", yyvsp[0].sEnumeratorNode_ptr );	yyval.str_lit=yyvsp[0].sEnumeratorNode_ptr;		;
    break;}
case 123:
#line 445 "exp11a.y"
{ printf( "switch_type_spec: case 5\n" ); ;
    break;}
case 124:
#line 448 "exp11a.y"
{ printf( "switch_body: case 1\n" ); ;
    break;}
case 125:
#line 449 "exp11a.y"
{ printf( "switch_body: case 2\n" ); ;
    break;}
case 126:
#line 452 "exp11a.y"
{ printf( "case: case 1\n" ); ;
    break;}
case 127:
#line 455 "exp11a.y"
{ printf( "aux_3: case 1\n" ); ;
    break;}
case 128:
#line 456 "exp11a.y"
{ printf( "aux_3: case 2\n" ); ;
    break;}
case 129:
#line 459 "exp11a.y"
{ printf( "case_label: case 1\n" ); ;
    break;}
case 130:
#line 460 "exp11a.y"
{ printf( "case_label: case 2\n" ); ;
    break;}
case 131:
#line 463 "exp11a.y"
{ printf( "element_spec: case 1\n" ); ;
    break;}
case 132:
#line 467 "exp11a.y"
{
							int i=0;
														 
							printf( "enum_type: case 1\n" ); 
							for( i=0 ; i<enumerator_count ; i++ )
								printf( "enumerator_array[%d]= %s\n", i, enumerator_array[i] );
							yyval.sEnumeratorNode_ptr = buildEnumerator( yyvsp[-4].str_lit, yyvsp[-3].str_lit, enumerator_array, enumerator_count );
							/* Clear enumerator_array and then clear enumerator_count */
							for( i=0 ; i<enumerator_count ; i++ )
								enumerator_array[i] = NULL;
														  
							enumerator_count = 0;
							;
    break;}
case 133:
#line 482 "exp11a.y"
{ printf( "aux_4: case 1:$1 %s\n", yyvsp[0].str_lit ); yyval.tok_val=yyvsp[0].str_lit; loadenumerator_array(yyvsp[0].str_lit); ;
    break;}
case 134:
#line 483 "exp11a.y"
{ printf( "aux_4: case 2:$1= %s, $3= %s\n", yyvsp[-2].tok_val, yyvsp[0].str_lit); yyval.tok_val=yyvsp[-2].tok_val; loadenumerator_array(yyvsp[0].str_lit); ;
    break;}
case 135:
#line 486 "exp11a.y"
{ printf( "enumerator: case 1:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 136:
#line 489 "exp11a.y"
{ printf( "sequence_type: case 1\n" ); ;
    break;}
case 137:
#line 490 "exp11a.y"
{ printf( "sequence_type: case 2\n" ); ;
    break;}
case 138:
#line 493 "exp11a.y"
{ printf( "string_type:case 1\n" );	;
    break;}
case 139:
#line 494 "exp11a.y"
{ printf( "string_type:case 2\n" );	;
    break;}
case 140:
#line 497 "exp11a.y"
{ printf( "array_declarator: case 1\n" ); ;
    break;}
case 141:
#line 500 "exp11a.y"
{ printf( "aux_5: case 1\n" ); ;
    break;}
case 142:
#line 501 "exp11a.y"
{ printf( "aux_5: case 2\n" ); ;
    break;}
case 143:
#line 504 "exp11a.y"
{ printf( "fixed_array_size: case 1\n" ); ;
    break;}
case 144:
#line 519 "exp11a.y"
{
							int i=0; 
							printf( "attr_dcl: case 1:$1= %s, $2= %s, $3= %s\n", yyvsp[-2].str_lit, yyvsp[-1].str_lit, yyvsp[0].str_lit );
							printf( "attr_dcl_count= %d\n", attr_dcl_count );
							for( i=0 ; i<attr_dcl_count ; i++ )
								printf( "attr_dcl_array[%d]= %s\n", i, attr_dcl_array[i] );
							yyval.sAttributeNode_ptr = buildAttribute( NO_READONLY, yyvsp[-2].str_lit, yyvsp[-1].str_lit, attr_dcl_array, attr_dcl_count );
							/* Clear attr_dcl_array and then clear attr_dcl_count */
							for( i=0 ; i<attr_dcl_count ; i++ )
								attr_dcl_array[i] = NULL;
														  
							attr_dcl_count = 0;
							;
    break;}
case 145:
#line 533 "exp11a.y"
{ 
							int i=0;
							printf( "attr_dcl: case 3\n" );
							printf( "attr_dcl_count= %d\n", attr_dcl_count );
							for( i=0 ; i<attr_dcl_count ; i++ )
								printf( "attr_dcl_array[%d]= %s\n", i, attr_dcl_array[i] );
							yyval.sAttributeNode_ptr = buildAttribute( YES_READONLY, yyvsp[-2].str_lit, yyvsp[-1].str_lit, attr_dcl_array, attr_dcl_count );
							/* Clear attr_dcl_array and then clear attr_dcl_count */
							for( i=0 ; i<attr_dcl_count ; i++ )
								attr_dcl_array[i] = NULL;
														  
							attr_dcl_count = 0;
							;
    break;}
case 146:
#line 548 "exp11a.y"
{ printf( "aux_6: case 1:$1 %s\n", yyvsp[0].str_lit ); yyval.str_lit=yyvsp[0].str_lit; loadattr_dcl_array(yyvsp[0].str_lit); ;
    break;}
case 147:
#line 549 "exp11a.y"
{ printf( "aux_6: case 2:$1= %s, $3= %s\n", yyvsp[-2].str_lit, yyvsp[0].str_lit); yyval.str_lit=yyvsp[-2].str_lit; loadattr_dcl_array(yyvsp[0].str_lit); ;
    break;}
case 148:
#line 552 "exp11a.y"
{ printf( "except_dcl: case 1\n" ); ;
    break;}
case 149:
#line 553 "exp11a.y"
{ printf( "except_dcl: case 2\n" ); ;
    break;}
case 150:
#line 556 "exp11a.y"
{ printf( "aux_7: case 1\n" ); ;
    break;}
case 151:
#line 557 "exp11a.y"
{ printf( "aux_7: case 2\n" ); ;
    break;}
case 152:
#line 561 "exp11a.y"
{
							int i=0;
							printf( "op_dcl: case 1:$1= %s\t $2= %s\t %3= %x\n", yyvsp[-2].str_lit, yyvsp[-1].str_lit, yyvsp[0].tok_val ); 																		 
							yyval.sOperationNode_ptr = buildOperation( NO_OPATTRIBUTE, yyvsp[-2].str_lit, yyvsp[-1].str_lit, param_dcl_array, param_dcl_count );
							
							/* Clear param_dcl_array and then clear param_dcl_count */
							for( i=0 ; i<param_dcl_count ; i++ )
								{
								free( param_dcl_array[i] );		/* free() what was allocated in param_dcl */
								param_dcl_array[i] = NULL;
								}
														  
							param_dcl_count = 0;
							;
    break;}
case 153:
#line 578 "exp11a.y"
{ printf( "op_dcl: case 2\n" ); ;
    break;}
case 154:
#line 579 "exp11a.y"
{ printf( "op_dcl: case 3\n" ); ;
    break;}
case 155:
#line 580 "exp11a.y"
{ printf( "op_dcl: case 4\n" ); ;
    break;}
case 156:
#line 582 "exp11a.y"
{ 
							int i=0;
							printf( "op_dcl: case 5:$1= %s\t $2= %s\t %3= %x\n", yyvsp[-3].tok_val, yyvsp[-2].str_lit, yyvsp[-1].str_lit ); 																		 
							yyval.sOperationNode_ptr = buildOperation( YES_OPATTRIBUTE, yyvsp[-2].str_lit, yyvsp[-1].str_lit, param_dcl_array, param_dcl_count );
							
							/* Clear param_dcl_array and then clear param_dcl_count */
							for( i=0 ; i<param_dcl_count ; i++ )
								{
								free( param_dcl_array[i] );		/* free() what was allocated in param_dcl */
								param_dcl_array[i] = NULL;
								}
														  
							param_dcl_count = 0;							
							;
    break;}
case 157:
#line 597 "exp11a.y"
{ printf( "op_dcl: case 6\n" ); ;
    break;}
case 158:
#line 598 "exp11a.y"
{ printf( "op_dcl: case 7\n" ); ;
    break;}
case 159:
#line 599 "exp11a.y"
{ printf( "op_dcl: case 8\n" ); ;
    break;}
case 160:
#line 602 "exp11a.y"
{ printf( "op_attribute: case 1: Got xONEWAY:$1 = %d\n", yyvsp[0].str_lit ); ;
    break;}
case 161:
#line 605 "exp11a.y"
{ printf( "op_type_spec: case 1:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 162:
#line 606 "exp11a.y"
{ printf( "op_type_spec: case 2:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 163:
#line 619 "exp11a.y"
{ printf( "parameter_dcls: case 1\n" ); ;
    break;}
case 164:
#line 620 "exp11a.y"
{ printf( "parameter_dcls: case 3\n" ); ;
    break;}
case 165:
#line 623 "exp11a.y"
{ printf( "aux_8: case 1\n" ); ;
    break;}
case 166:
#line 624 "exp11a.y"
{ printf( "aux_8: case 2\n" ); ;
    break;}
case 167:
#line 628 "exp11a.y"
{ 
							param_dcl_struct	*ptr;
							ptr = (param_dcl_struct *) malloc( sizeof(param_dcl_struct) );
							printf( "param_dcl: $1= %s\t $2= %s\t $3= %s\n", yyvsp[-2].str_lit, yyvsp[-1].str_lit, yyvsp[0].str_lit ); 

							/* Load the struct */
							strcpy( ptr->p1, yyvsp[-2].str_lit );
							strcpy( ptr->p2, yyvsp[-1].str_lit );
							strcpy( ptr->p3, yyvsp[0].str_lit );

							/* Place the struct in the param_dcl array */
							param_dcl_array[param_dcl_count] = ptr;

							/* Increment the param_dcl_array counter */
							param_dcl_count++;
							;
    break;}
case 168:
#line 646 "exp11a.y"
{ printf( "param_attribute: case 1:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 169:
#line 647 "exp11a.y"
{ printf( "param_attribute: case 2:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 170:
#line 648 "exp11a.y"
{ printf( "param_attribute: case 3:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 171:
#line 651 "exp11a.y"
{ printf( "raises_expr: case 1\n" ); ;
    break;}
case 172:
#line 652 "exp11a.y"
{ printf( "raises_expr: case 2\n" ); ;
    break;}
case 173:
#line 655 "exp11a.y"
{ printf( "aux_9: case 1\n" ); ;
    break;}
case 174:
#line 656 "exp11a.y"
{ printf( "aux_9: case 2\n" ); ;
    break;}
case 175:
#line 659 "exp11a.y"
{ printf( "context_expr: case 1\n" ); ;
    break;}
case 176:
#line 660 "exp11a.y"
{ printf( "context_expr: case 2\n" ); ;
    break;}
case 177:
#line 663 "exp11a.y"
{ printf( "aux_10: case 1\n" ); ;
    break;}
case 178:
#line 664 "exp11a.y"
{ printf( "aux_10: case 2\n" ); ;
    break;}
case 179:
#line 668 "exp11a.y"
{ printf( "param_type_spec: case 1:$1= %s\n", yyvsp[0].str_lit );	yyval.str_lit=yyvsp[0].str_lit;		;
    break;}
case 180:
#line 669 "exp11a.y"
{ printf( "param_type_spec: case 2\n" ); ;
    break;}
case 181:
#line 670 "exp11a.y"
{ printf( "param_type_spec: case 3\n" ); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 362 "/usr/local/lib/bison.simple"

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
#line 674 "exp11a.y"

/*
Additional C code
The additional C code can contain any C code you want to use. Often the definition of the lexical analyzer yylex goes here, plus
subroutines called by the actions in the grammar rules. In a simple program, all the rest of the program can go here. 

$1= %s\n", $1 );	$$=$1;		}
*/

/* Lexical analyzer returns a double floating point 
   number on the stack and the token NUM, or the ASCII
   character read if not a number.  Skips all blanks
   and tabs, returns 0 for EOF. */

loadattr_dcl_array( char *arg )
{

	printf( "arg #%d= %s\n", attr_dcl_count, arg );

	attr_dcl_array[attr_dcl_count] = arg;

	printf( "attr_dcl_array[%d]= %s\n", attr_dcl_count, arg );

	attr_dcl_count++;

}

loadenumerator_array( char *arg )
{

	printf( "arg #%d= %s\n", enumerator_count, arg );

	enumerator_array[enumerator_count] = arg;

	printf( "enumerator_array[%d]= %s\n", enumerator_count, arg );

	enumerator_count++;

}

sAttributeNode *buildAttribute( int readonly_arg, char *type_arg, char *param_type_arg, char *attr_dcl_array_arg[], int attr_dcl_count_arg )
{
	sAttributeNode	*ptr;
	int				i;

	ptr = (sAttributeNode *) malloc( sizeof(sAttributeNode) );

	/* Create storage for each pointer in the structure */
	ptr->readonly_flag = readonly_arg;
	ptr->count_member = attr_dcl_count_arg;
	
	ptr->type = (char *) malloc( strlen(type_arg) + 1 );
	strcpy( ptr->type, type_arg );
	
	ptr->param_type = (char *) malloc( strlen(param_type_arg) + 1 );
	strcpy( ptr->param_type, param_type_arg );

	/* Allocate storage for each array entry, then load that entry */
	ptr->attr_dcl_array_member = (char **) malloc( sizeof( char *) );
	for( i=0 ; i<attr_dcl_count_arg ; i++ )
		{
		ptr->attr_dcl_array_member[i] = (char *) malloc( strlen(attr_dcl_array_arg[i])+1 );
		strcpy( ptr->attr_dcl_array_member[i], attr_dcl_array_arg[i] );
		}
	
	return( ptr );

}


sOperationNode *buildOperation( int opattribute_arg, char *return_type_arg, char *operation_name_arg, param_dcl_struct *param_dcl_array_arg[], int param_dcl_count_arg )
{
	sOperationNode	*ptr;
	int				i;

	ptr = (sOperationNode *) malloc( sizeof(sOperationNode) );

	/* Create storage for each pointer in the structure */
	ptr->opattribute_flag = opattribute_arg;
	ptr->count_member = param_dcl_count_arg;
	
	ptr->return_type = (char *) malloc( strlen(return_type_arg) + 1 );
	strcpy( ptr->return_type, return_type_arg );
	
	ptr->operation_name = (char *) malloc( strlen(operation_name_arg) + 1 );
	strcpy( ptr->operation_name, operation_name_arg );

	/* Allocate storage for each array entry, then load that entry */
	ptr->param_dcl_array_member = (param_dcl_struct **) malloc( sizeof(param_dcl_struct *) );
	for( i=0 ; i<param_dcl_count_arg ; i++ )
		{
		ptr->param_dcl_array_member[i] = (param_dcl_struct *) malloc( sizeof(param_dcl_struct) );
		strcpy( ptr->param_dcl_array_member[i]->p1, param_dcl_array_arg[i]->p1 );
		strcpy( ptr->param_dcl_array_member[i]->p2, param_dcl_array_arg[i]->p2 );
		strcpy( ptr->param_dcl_array_member[i]->p3, param_dcl_array_arg[i]->p3 );
		}
	
	return( ptr );

}


sEnumeratorNode *buildEnumerator( char *keyword_arg, char *enum_name_arg, char *enumerator_array_arg[], int enumerator_count_arg )
{
	sEnumeratorNode	*ptr;
	int				i;

	ptr = (sEnumeratorNode *) malloc( sizeof(sEnumeratorNode) );

	/* Create storage for each pointer in the structure */
	//ptr->readonly_flag = readonly_arg;
	ptr->count_member = enumerator_count_arg;
	
	ptr->keyword = (char *) malloc( strlen(keyword_arg) + 1 );
	strcpy( ptr->keyword, keyword_arg );
	
	ptr->enum_name = (char *) malloc( strlen(enum_name_arg) + 1 );
	strcpy( ptr->enum_name, enum_name_arg );

	/* Allocate storage for each array entry, then load that entry */
	ptr->enumerator_array_member = (char **) malloc( sizeof( char *) );
	for( i=0 ; i<enumerator_count_arg ; i++ )
		{
		ptr->enumerator_array_member[i] = (char *) malloc( strlen(enumerator_array_arg[i])+1 );
		strcpy( ptr->enumerator_array_member[i], enumerator_array_arg[i] );
		}
	
	return( ptr );

}


yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("yerror(): %s\n", s);
}