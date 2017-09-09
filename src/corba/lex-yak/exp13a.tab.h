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


extern YYSTYPE yylval;
