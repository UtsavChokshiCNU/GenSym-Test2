
typedef union  
	{
	void			*void_ptr;
	char			*str_lit;		
	int			int_val;		
	int			tok_val;
	float			flt_val;
	double			dbl_val;
	char			chr_val;
	unsigned long	ulng_val;
	long			lng_val;
	short			shrt_val;
	double			val;
	} YYSTYPE;
extern YYSTYPE yylval;
# define xANY 257
# define xATTRIBUTE 258
# define xBOOLEAN 259
# define xCASE 260
# define xCHAR 261
# define xCONST 262
# define xCONTEXT 263
# define xDEFAULT 264
# define xDOUBLE 265
# define xENUM 266
# define xEXCEPTION 267
# define xFALSE 268
# define xFLOAT 269
# define xIN 270
# define xINOUT 271
# define xINTERFACE 272
# define xLONG 273
# define xMODULE 274
# define xOBJECT 275
# define xOCTET 276
# define xONEWAY 277
# define xOUT 278
# define xRAISES 279
# define xREADONLY 280
# define xSEQUENCE 281
# define xSHORT 282
# define xSTRING 283
# define xSTRUCT 284
# define xSWITCH 285
# define xTRUE 286
# define xTYPEDEF 287
# define xUNSIGNED 288
# define xUNION 289
# define xVOID 290
# define OPERATOR 291
# define PUNCTUATOR 292
# define LITERAL 293
# define IDENTIFIER 294
# define KEYWORD 295
# define LITERAL_DECINT 296
# define LITERAL_HEXINT 297
# define LITERAL_OCTINT 298
# define LITERAL_FP 299
# define LITERAL_CHAR 300
# define LITERAL_CHARHEX 301
# define LITERAL_CHAROCT 302
# define LITERAL_STRING 303
# define DOUBLE_COLON 304
# define DOUBLE_LT 305
# define DOUBLE_GT 306
# define FLOATING_PT_LITERAL 307
# define CHARACTER_LITERAL 308
# define STRING_LITERAL 309
# define INTEGER_LITERAL 310
# define xIDENTIFIER 311
# define NEG 312
