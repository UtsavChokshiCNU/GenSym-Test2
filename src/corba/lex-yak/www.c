
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
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
typedef int yytabelem;
# define YYERRCODE 256

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
}static yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
-1, 80,
	123, 15,
	-2, 14,
	};
# define YYNPROD 180
# define YYLAST 567
static yytabelem yyact[]={

   145,    56,    86,    54,   251,    53,   225,    48,   252,    50,
    19,   229,   144,    49,    47,   204,    54,    64,    53,    57,
    55,   107,    94,    19,    89,    58,    65,    59,    17,    80,
    64,    78,    66,    18,   188,    77,    76,    75,    56,    65,
    54,    74,    53,   284,   272,    66,    50,    19,    48,    88,
    49,   174,   173,    98,    64,    47,    57,    55,   243,   245,
   238,    48,    58,    65,    59,    17,   244,   184,    47,    66,
    18,    56,   238,    54,   241,    53,   240,    83,   251,    50,
   203,   125,   252,    49,   121,    48,   120,    64,   237,    57,
    55,    56,    47,    54,   125,    53,    65,    59,   248,    50,
   134,    12,    66,    49,   157,    19,    13,    64,   262,    57,
    55,    21,   235,    16,   223,    58,    65,    59,    48,   250,
    92,   143,    66,    17,   236,    47,     8,   227,    18,    93,
   114,   116,    56,   152,    54,   136,    53,    12,    48,    84,
    50,    19,    13,   113,    49,    47,   110,   196,    64,   115,
    57,    55,   158,   109,   112,   153,   117,    65,    59,    17,
   137,   154,     8,    66,    18,   157,    56,   122,    54,    29,
    53,   170,   232,    32,    50,    19,    81,   105,    49,    48,
    99,   164,    64,    97,    57,    55,    47,    96,    95,    41,
    58,    65,    59,    17,    79,   171,    40,    66,    18,    56,
   156,    54,    70,    53,   135,   207,   106,    50,    19,    69,
   231,    49,   169,    48,   133,    64,    91,    57,    55,     5,
    47,   167,    90,    58,    65,    59,    17,   276,   195,   220,
    66,    18,    56,   186,    54,   119,    53,   201,   200,   168,
    50,    19,     4,   251,    49,   199,    48,   252,    64,    39,
    57,    55,   198,    47,     3,    46,    58,    65,    59,    17,
   166,   197,    68,    66,    18,    56,    27,    54,    72,    53,
    26,   183,   181,    50,   159,    25,   183,    49,    24,    48,
   182,    64,   165,    57,    55,   123,    47,    54,    30,    53,
    65,    59,    23,    50,    34,   278,    66,    49,    73,   268,
   102,    64,   140,   211,   233,   243,   245,   214,   215,   132,
    65,    59,    48,   244,   185,   210,    66,   205,   222,    47,
   149,   208,   132,   212,   213,   209,   159,   131,     2,   159,
    22,   192,    48,   273,   216,   217,   218,   206,   191,    47,
   131,   234,   224,   148,   277,    48,   263,   103,   129,   128,
   127,   126,    47,   202,   180,   147,   160,   246,    48,   260,
   254,   129,   128,   127,   126,    47,   224,   221,   219,   265,
    12,   261,   256,   253,    19,    13,    34,   159,   255,   108,
    21,    34,    16,    34,   179,   275,   161,   281,   163,   177,
   282,   190,    17,   279,   178,     8,   280,    18,   267,   274,
    37,    11,    11,   228,   226,    35,     9,     9,   160,   141,
   266,   160,    36,    10,    10,   175,   159,   176,   172,   257,
    38,    34,   258,   162,   101,   139,    34,   194,     7,    28,
    33,    85,    87,    71,    45,   264,   130,   189,   161,   111,
   124,   161,    67,   259,    82,   151,    31,     1,     6,    15,
    14,    20,   100,   146,   150,    44,   155,   242,    43,   160,
    42,    63,    62,    52,    51,    60,    61,   187,   271,   269,
   239,   104,   142,   249,   138,   247,   118,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   161,
     0,     0,   230,     0,     0,     0,     0,    11,   160,     0,
     0,    11,     9,     0,     0,     0,     9,     0,     0,    10,
     0,     0,     0,    10,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   161,     0,
     0,     0,     0,     0,     0,    34,     0,     0,     0,    11,
     0,   270,   193,     0,     9,     0,     0,     0,     0,     0,
     0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   283 };
static yytabelem yypact[]={

  -161,  -161, -1000,   233,   219,   216,   211,   207,  -219, -1000,
 -1000, -1000,    28,  -270, -1000, -1000,  -274,  -275,  -276,  -280,
    71,  -282, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  -309,
 -1000, -1000, -1000, -1000,  -255, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  -287, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   162,   156,
 -1000, -1000, -1000, -1000, -1000, -1000,  -153,  -289, -1000, -1000,
 -1000, -1000, -1000,  -255,    65,    64,    60,  -232,    57, -1000,
   242, -1000,   303, -1000, -1000, -1000,   115, -1000,  -290, -1000,
  -166,    41, -1000, -1000,   153,   -25,  -161,  -219,   369,  -299,
  -125, -1000,  -297,  -309,   115, -1000,    41, -1000,   177,   150,
 -1000,    47,   101,   380,  -254,   372,   347, -1000,    54, -1000,
 -1000, -1000, -1000,  -255, -1000,    41, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000,    41, -1000,   -58, -1000,  -309,   108, -1000,
   -91,  -243,   103, -1000, -1000, -1000, -1000,   202,   193,   186,
   179,   178,     8,  -178,  -296,  -186, -1000, -1000, -1000, -1000,
 -1000,  -255,   293,  -255, -1000, -1000,   112,    41, -1000, -1000,
    41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
 -1000,   327, -1000, -1000, -1000,   170, -1000, -1000, -1000,   326,
 -1000, -1000, -1000, -1000,  -255, -1000,  -299, -1000, -1000, -1000,
 -1000, -1000,  -305,     8,   363,  -300,  -297, -1000,   148,   101,
   380,  -254,   372,   372,   347,   347, -1000, -1000, -1000, -1000,
 -1000,    49, -1000,   260, -1000, -1000,  -305,  -191,    35,   363,
  -255, -1000,  -182,  -305,   260,  -203, -1000,   338,   332,   378,
 -1000, -1000,     8, -1000, -1000, -1000,  -191,   -17, -1000,  -256,
 -1000,    41,   241, -1000, -1000,  -297,  -265, -1000,  -212,  -305,
  -203, -1000, -1000, -1000,   168, -1000,  -309,   237, -1000,   352,
  -255,   346, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
  -297, -1000,  -266,  -255, -1000 };
static yytabelem yypgo[]={

     0,   476,   475,   474,   473,   472,   471,   470,   469,   468,
   466,   465,   464,   463,   462,   461,   249,   420,   173,   196,
   189,   460,   458,   114,   457,   121,   456,   455,   200,   454,
   453,   452,   451,   450,   449,   448,   328,   447,   161,    74,
   127,   400,   254,   446,   288,   160,   445,   139,    77,   135,
   204,   176,   444,   285,   442,   235,   440,   146,   439,   154,
   143,   130,   149,   131,   156,   153,   255,   437,   412,   436,
   242,   405,   435,   112,   219,    98,   119,   434,   177,   432,
   431,   430,   429,   428,   424,   124,   423 };
static yytabelem yyr1[]={

     0,    37,    37,    36,    36,    36,    36,    36,    83,     3,
     3,    35,    35,    33,    34,    32,    32,    31,    31,    30,
    30,    30,    30,    30,    84,    86,    86,    53,    53,    53,
    70,    54,    54,    54,    54,    54,    54,    57,    58,    58,
    59,    59,    60,    60,    61,    61,    61,    62,    62,    62,
    63,    63,    63,    63,    64,    64,     1,     1,     1,    55,
    55,    55,    56,    56,    56,    56,    56,    69,    69,    65,
    42,    42,    42,    42,    82,    45,    45,    44,    44,    44,
    18,    18,    18,    18,    18,    18,    18,    81,    81,    43,
    43,    43,    51,    52,    52,    48,    48,    47,    80,    17,
    17,    16,    16,    12,    12,    11,    10,    13,    13,    14,
    15,    19,    20,    21,    22,    27,    71,    50,    50,    49,
    68,    67,    67,    67,    67,    67,     2,     2,    75,     4,
     4,    76,    76,    72,    41,     5,     5,    25,    77,    77,
    66,    66,    79,     6,     6,    78,    29,    29,    23,    23,
    74,    74,    46,    46,    46,    46,    46,    46,    46,    46,
    26,    38,    38,    40,    40,     7,     7,    39,    24,    24,
    24,    73,     8,     8,    85,     9,     9,    28,    28,    28 };
static yytabelem yyr2[]={

     0,     3,     5,     5,     5,     5,     5,     5,    11,     3,
     5,     3,     3,     9,     5,     5,     7,     1,     5,     5,
     5,     5,     5,     5,     5,     3,     7,     3,     5,     7,
    11,     3,     3,     3,     3,     3,     3,     3,     3,     7,
     3,     7,     3,     7,     3,     7,     7,     3,     7,     7,
     3,     7,     7,     7,     5,     3,     3,     3,     3,     3,
     3,     7,     3,     3,     3,     3,     3,     3,     3,     3,
     5,     3,     3,     3,     5,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     7,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
     5,     3,     3,     3,     3,     3,    11,     3,     5,     7,
    19,     3,     3,     3,     3,     3,     3,     5,     7,     3,
     5,     7,     5,     5,    11,     3,     7,     3,    13,     9,
     9,     3,     5,     3,     5,     7,     7,     9,     3,     7,
     9,    11,     7,     9,     9,    11,     9,    11,    11,    13,
     3,     3,     3,     7,     5,     3,     7,     7,     3,     3,
     3,     9,     3,     7,     9,     3,     7,     3,     3,     3 };
static yytabelem yychk[]={

 -1000,   -37,   -36,   -42,   -70,   -74,   -35,   -83,   287,   -71,
   -68,   -41,   262,   267,   -33,   -34,   274,   284,   289,   266,
   -32,   272,   -36,    59,    59,    59,    59,    59,   -82,   -45,
   -44,   -43,   -18,   -81,   -53,   -71,   -68,   -41,   -17,   -16,
   -19,   -20,   -21,   -22,   -27,   -77,   -66,   311,   304,   269,
   265,   -12,   -13,   261,   259,   276,   257,   275,   281,   283,
   -11,   -10,   -14,   -15,   273,   282,   288,   -54,   -16,   -19,
   -20,   -17,   -66,   -53,   311,   311,   311,   311,   311,   123,
   311,   -51,   -52,   -48,   -47,   -80,   311,   -79,   304,   311,
    60,    60,   273,   282,   311,   123,   123,   123,   285,   123,
   -31,   -84,    58,    44,    -6,   -78,    91,   311,   -44,   -65,
   -57,   -58,   -59,   -60,   -61,   -62,   -63,   -64,    -1,   -55,
    45,    43,   126,   -53,   -56,    40,   310,   309,   308,   307,
   -69,   286,   268,    61,   125,   -50,   -49,   -45,    -3,   -36,
   -50,    40,    -5,   -25,   311,   125,   -30,   -42,   -70,   -74,
   -29,   -46,   258,   280,   -38,   -26,   -28,   290,   277,   -18,
   -66,   -53,   -86,   -53,   -48,   -78,   -65,    44,    62,    62,
   124,    94,    38,   306,   305,    43,    45,    42,    47,    37,
   -55,   -57,   -57,   -49,   125,   -51,   125,   -36,   125,   -67,
   -16,   -19,   -20,   -41,   -53,   125,    44,    59,    59,    59,
    59,    59,   -28,   258,   311,   -38,    44,    93,   -65,   -59,
   -60,   -61,   -62,   -62,   -63,   -63,   -64,   -64,   -64,    41,
    59,    41,   -25,   -23,   -47,   311,   -28,   -40,    40,   311,
   -53,    62,   123,    44,   -23,   -73,   -85,   279,   263,    -7,
    41,   -39,   -24,   270,   278,   271,   -40,    -2,   -75,    -4,
   -76,   260,   264,   -47,   -85,    40,    40,    41,    44,   -28,
   -73,   -85,   125,   -75,   -72,   -76,   -45,   -57,    58,    -8,
   -53,    -9,   309,   -39,   -47,   -85,    59,   -48,    58,    41,
    44,    41,    44,   -53,   309 };
static yytabelem yydef[]={

     0,    -2,     1,     0,     0,     0,     0,     0,     0,    71,
    72,    73,     0,     0,    11,    12,     0,     0,     0,     0,
     0,     0,     2,     3,     4,     5,     6,     7,    70,     0,
    75,    76,    77,    78,    79,    89,    90,    91,    80,    81,
    82,    83,    84,    85,    86,    87,    88,    27,     0,    99,
   100,   101,   102,   111,   112,   113,   114,   115,     0,   141,
   103,   104,   107,   108,   105,   106,     0,     0,    31,    32,
    33,    34,    35,    36,     0,     0,     0,     0,     0,    17,
    -2,    74,    92,    93,    95,    96,    97,    98,     0,    28,
     0,     0,   109,   110,     0,     0,     0,     0,     0,     0,
     0,    16,     0,     0,   142,   143,     0,    29,     0,     0,
    69,    37,    38,    40,    42,    44,    47,    50,     0,    55,
    56,    57,    58,    59,    60,     0,    62,    63,    64,    65,
    66,    67,    68,     0,   150,     0,   117,     0,     0,     9,
     0,     0,     0,   135,   137,    13,    18,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   161,   162,   160,   177,
   178,   179,    24,    25,    94,   144,     0,     0,   139,   140,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    54,     0,    30,   118,   151,     0,     8,    10,   116,     0,
   121,   122,   123,   124,   125,   134,     0,    19,    20,    21,
    22,    23,     0,     0,     0,     0,     0,   145,     0,    39,
    41,    43,    45,    46,    48,    49,    51,    52,    53,    61,
   119,     0,   136,   146,   148,    97,     0,   152,     0,     0,
    26,   138,     0,     0,   147,   153,   154,     0,     0,     0,
   164,   165,     0,   168,   169,   170,   156,     0,   126,     0,
   129,     0,     0,   149,   155,     0,     0,   163,     0,     0,
   157,   158,   120,   127,     0,   130,     0,     0,   132,     0,
   172,     0,   175,   166,   167,   159,   128,   133,   131,   171,
     0,   174,     0,   173,   176 };
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"xANY",	257,
	"xATTRIBUTE",	258,
	"xBOOLEAN",	259,
	"xCASE",	260,
	"xCHAR",	261,
	"xCONST",	262,
	"xCONTEXT",	263,
	"xDEFAULT",	264,
	"xDOUBLE",	265,
	"xENUM",	266,
	"xEXCEPTION",	267,
	"xFALSE",	268,
	"xFLOAT",	269,
	"xIN",	270,
	"xINOUT",	271,
	"xINTERFACE",	272,
	"xLONG",	273,
	"xMODULE",	274,
	"xOBJECT",	275,
	"xOCTET",	276,
	"xONEWAY",	277,
	"xOUT",	278,
	"xRAISES",	279,
	"xREADONLY",	280,
	"xSEQUENCE",	281,
	"xSHORT",	282,
	"xSTRING",	283,
	"xSTRUCT",	284,
	"xSWITCH",	285,
	"xTRUE",	286,
	"xTYPEDEF",	287,
	"xUNSIGNED",	288,
	"xUNION",	289,
	"xVOID",	290,
	"OPERATOR",	291,
	"PUNCTUATOR",	292,
	"LITERAL",	293,
	"IDENTIFIER",	294,
	"KEYWORD",	295,
	"LITERAL_DECINT",	296,
	"LITERAL_HEXINT",	297,
	"LITERAL_OCTINT",	298,
	"LITERAL_FP",	299,
	"LITERAL_CHAR",	300,
	"LITERAL_CHARHEX",	301,
	"LITERAL_CHAROCT",	302,
	"LITERAL_STRING",	303,
	"DOUBLE_COLON",	304,
	"DOUBLE_LT",	305,
	"DOUBLE_GT",	306,
	"FLOATING_PT_LITERAL",	307,
	"CHARACTER_LITERAL",	308,
	"STRING_LITERAL",	309,
	"INTEGER_LITERAL",	310,
	"xIDENTIFIER",	311,
	"=",	61,
	"|",	124,
	"^",	94,
	"&",	38,
	"-",	45,
	"+",	43,
	"*",	42,
	"/",	47,
	"%",	37,
	"NEG",	312,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
      "specification : definition",
      "specification : specification definition",
      "definition : type_dcl ';'",
      "definition : const_dcl ';'",
      "definition : except_dcl ';'",
      "definition : interface ';'",
      "definition : module ';'",
      "module : xMODULE xIDENTIFIER '{' aux_11 '}'",
      "aux_11 : definition",
      "aux_11 : aux_11 definition",
      "interface : interface_dcl",
      "interface : forward_dcl",
      "interface_dcl : interface_header '{' interface_body '}'",
      "forward_dcl : xINTERFACE xIDENTIFIER",
      "interface_header : xINTERFACE xIDENTIFIER",
      "interface_header : xINTERFACE xIDENTIFIER inheritance_spec",
      "interface_body : /* empty */",
      "interface_body : interface_body export",
      "export : type_dcl ';'",
      "export : const_dcl ';'",
      "export : except_dcl ';'",
      "export : attr_dcl ';'",
      "export : op_dcl ';'",
      "inheritance_spec : ':' aux_1",
      "aux_1 : scoped_name",
      "aux_1 : aux_1 ',' scoped_name",
      "scoped_name : xIDENTIFIER",
      "scoped_name : DOUBLE_COLON xIDENTIFIER",
      "scoped_name : scoped_name DOUBLE_COLON xIDENTIFIER",
      "const_dcl : xCONST const_type xIDENTIFIER '=' const_exp",
      "const_type : integer_type",
      "const_type : char_type",
      "const_type : boolean_type",
      "const_type : floating_pt_type",
      "const_type : string_type",
      "const_type : scoped_name",
      "const_exp : or_expr",
      "or_expr : xor_expr",
      "or_expr : or_expr '|' xor_expr",
      "xor_expr : and_expr",
      "xor_expr : xor_expr '^' and_expr",
      "and_expr : shift_expr",
      "and_expr : and_expr '&' shift_expr",
      "shift_expr : add_expr",
      "shift_expr : shift_expr DOUBLE_GT add_expr",
      "shift_expr : shift_expr DOUBLE_LT add_expr",
      "add_expr : mult_expr",
      "add_expr : add_expr '+' mult_expr",
      "add_expr : add_expr '-' mult_expr",
      "mult_expr : unary_expr",
      "mult_expr : mult_expr '*' unary_expr",
      "mult_expr : mult_expr '/' unary_expr",
      "mult_expr : mult_expr '%' unary_expr",
      "unary_expr : unary_operator primary_expr",
      "unary_expr : primary_expr",
      "unary_operator : '-'",
      "unary_operator : '+'",
      "unary_operator : '~'",
      "primary_expr : scoped_name",
      "primary_expr : literal",
      "primary_expr : '(' const_exp ')'",
      "literal : INTEGER_LITERAL",
      "literal : STRING_LITERAL",
      "literal : CHARACTER_LITERAL",
      "literal : FLOATING_PT_LITERAL",
      "literal : boolean_literal",
      "boolean_literal : xTRUE",
      "boolean_literal : xFALSE",
      "positive_int_const : const_exp",
      "type_dcl : xTYPEDEF type_declarator",
      "type_dcl : struct_type",
      "type_dcl : union_type",
      "type_dcl : enum_type",
      "type_declarator : type_spec declarators",
      "type_spec : simple_type_spec",
      "type_spec : constr_type_spec",
      "simple_type_spec : base_type_spec",
      "simple_type_spec : template_type_spec",
      "simple_type_spec : scoped_name",
      "base_type_spec : floating_pt_type",
      "base_type_spec : integer_type",
      "base_type_spec : char_type",
      "base_type_spec : boolean_type",
      "base_type_spec : octet_type",
      "base_type_spec : any_type",
      "base_type_spec : object_type",
      "template_type_spec : sequence_type",
      "template_type_spec : string_type",
      "constr_type_spec : struct_type",
      "constr_type_spec : union_type",
      "constr_type_spec : enum_type",
      "declarators : aux_2",
      "aux_2 : declarator",
      "aux_2 : aux_2 ',' declarator",
      "declarator : simple_declarator",
      "declarator : complex_declarator",
      "simple_declarator : xIDENTIFIER",
      "complex_declarator : array_declarator",
      "floating_pt_type : xFLOAT",
      "floating_pt_type : xDOUBLE",
      "integer_type : signed_int",
      "integer_type : unsigned_int",
      "signed_int : signed_long_int",
      "signed_int : signed_short_int",
      "signed_long_int : xLONG",
      "signed_short_int : xSHORT",
      "unsigned_int : unsigned_long_int",
      "unsigned_int : unsigned_short_int",
      "unsigned_long_int : xUNSIGNED xLONG",
      "unsigned_short_int : xUNSIGNED xSHORT",
      "char_type : xCHAR",
      "boolean_type : xBOOLEAN",
      "octet_type : xOCTET",
      "any_type : xANY",
      "object_type : xOBJECT",
      "struct_type : xSTRUCT xIDENTIFIER '{' member_list '}'",
      "member_list : member",
      "member_list : member_list member",
      "member : type_spec declarators ';'",
      "union_type : xUNION xIDENTIFIER xSWITCH '(' switch_type_spec ')' '{' switch_body '}'",
      "switch_type_spec : integer_type",
      "switch_type_spec : char_type",
      "switch_type_spec : boolean_type",
      "switch_type_spec : enum_type",
      "switch_type_spec : scoped_name",
      "switch_body : case",
      "switch_body : switch_body case",
      "case : aux_3 element_spec ';'",
      "aux_3 : case_label",
      "aux_3 : aux_3 case_label",
      "case_label : xCASE const_exp ':'",
      "case_label : xDEFAULT ':'",
      "element_spec : type_spec declarator",
      "enum_type : xENUM xIDENTIFIER '{' aux_4 '}'",
      "aux_4 : enumerator",
      "aux_4 : aux_4 ',' enumerator",
      "enumerator : xIDENTIFIER",
      "sequence_type : xSEQUENCE '<' simple_type_spec ',' positive_int_const '>'",
      "sequence_type : xSEQUENCE '<' simple_type_spec '>'",
      "string_type : xSTRING '<' positive_int_const '>'",
      "string_type : xSTRING",
      "array_declarator : xIDENTIFIER aux_5",
      "aux_5 : fixed_array_size",
      "aux_5 : aux_5 fixed_array_size",
      "fixed_array_size : '[' positive_int_const ']'",
      "attr_dcl : xATTRIBUTE param_type_spec aux_6",
      "attr_dcl : xREADONLY xATTRIBUTE param_type_spec aux_6",
      "aux_6 : simple_declarator",
      "aux_6 : aux_6 ',' simple_declarator",
      "except_dcl : xEXCEPTION xIDENTIFIER '{' '}'",
      "except_dcl : xEXCEPTION xIDENTIFIER '{' member_list '}'",
      "op_dcl : op_type_spec xIDENTIFIER parameter_dcls",
      "op_dcl : op_type_spec xIDENTIFIER parameter_dcls raises_expr",
      "op_dcl : op_type_spec xIDENTIFIER parameter_dcls context_expr",
      "op_dcl : op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr",
      "op_dcl : op_attribute op_type_spec xIDENTIFIER parameter_dcls",
      "op_dcl : op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr",
      "op_dcl : op_attribute op_type_spec xIDENTIFIER parameter_dcls context_expr",
      "op_dcl : op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr",
      "op_attribute : xONEWAY",
      "op_type_spec : param_type_spec",
      "op_type_spec : xVOID",
      "parameter_dcls : '(' aux_8 ')'",
      "parameter_dcls : '(' ')'",
      "aux_8 : param_dcl",
      "aux_8 : aux_8 ',' param_dcl",
      "param_dcl : param_attribute param_type_spec simple_declarator",
      "param_attribute : xIN",
      "param_attribute : xOUT",
      "param_attribute : xINOUT",
      "raises_expr : xRAISES '(' aux_9 ')'",
      "aux_9 : scoped_name",
      "aux_9 : aux_9 ',' scoped_name",
      "context_expr : xCONTEXT '(' aux_10 ')'",
      "aux_10 : STRING_LITERAL",
      "aux_10 : aux_10 ',' STRING_LITERAL",
      "param_type_spec : base_type_spec",
      "param_type_spec : string_type",
      "param_type_spec : scoped_name",
};
#endif /* YYDEBUG */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/* @(#)yaccpar	1.3  com/cmd/lang/yacc,3.1, 9/7/89 18:46:37 */
/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#ifdef YYSPLIT
#   define YYERROR	return(-2)
#else
#   define YYERROR	goto yyerrlab
#endif

#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-1000)

#ifdef YYSPLIT
#   define YYSCODE { \
			extern int (*yyf[])(); \
			register int yyret; \
			if (yyf[yytmp]) \
			    if ((yyret=(*yyf[yytmp])()) == -2) \
				    goto yyerrlab; \
				else if (yyret>=0) return(yyret); \
		   }
#endif

/*
** global variables used by the parser
*/
YYSTYPE yyv[ YYMAXDEPTH ];	/* value stack */
int yys[ YYMAXDEPTH ];		/* state stack */

YYSTYPE *yypv;			/* top of value stack */
YYSTYPE *yypvt;			/* top of value stack for $vars */
int *yyps;			/* top of state stack */

int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ YYMAXDEPTH ] )	/* room on stack? */
		{
			yyerror( "yacc stack overflow" );
			YYABORT;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/

		switch(yytmp){

case 1:{	if( compiler_debug_state == DEBUG_ON )printf( "specification:case 1\n" );		
														if( compiler_debug_state == DEBUG_ON )printf( "$1= %x\n", yypvt[-0].void_ptr );
														/* Create the specification object */
														yyval.void_ptr = buildSpecification();
													  
														/* Load the Builder object with this value for later use */
														loadParseTreeRoot( yyval.void_ptr );

														/* Add the first definition item to the specification */
														addDefinition( yyval.void_ptr, yypvt[-0].void_ptr );
									   				
													} /*NOTREACHED*/ break;
case 2:{	if( compiler_debug_state == DEBUG_ON )printf( "specification:case 2\n" );
														
														/* Add the subsequent definition items to the specification */
														addDefinition( yyval.void_ptr, yypvt[-0].void_ptr );													
													} /*NOTREACHED*/ break;
case 3:{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 1\n" ); yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 4:{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 2\n" ); yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 5:{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 3\n" ); yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 6:{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 4\n" ); yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 7:{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 5\n" ); yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 8:{
							int i=0;
							
							if( compiler_debug_state == DEBUG_ON )printf( "module: case 1\n" );
							for( i=0 ; i<module_definition_count ; i++ )
								if( compiler_debug_state == DEBUG_ON )printf( "module_definition_array[%d]= %x\n", i, module_definition_array[i] );

							yyval.void_ptr = buildModule( yypvt[-4].str_lit, yypvt[-3].str_lit, module_definition_array, module_definition_count );
														  
							/* Handle reset details */
							reset_void_array( &module_definition_array, &module_definition_count, &module_definition_array_limit );
							} /*NOTREACHED*/ break;
case 9:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_11: case 1\n" ); yyval.tok_val=0; load_module_definition_array(yypvt[-0].void_ptr); } /*NOTREACHED*/ break;
case 10:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_11: case 2\n" ); yyval.tok_val=0; load_module_definition_array(yypvt[-0].void_ptr); } /*NOTREACHED*/ break;
case 11:{	if( compiler_debug_state == DEBUG_ON )printf( "interface: case 1\n" ); yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 12:{	if( compiler_debug_state == DEBUG_ON )printf( "interface: case 2\n" ); yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 13:{
							if( compiler_debug_state == DEBUG_ON )printf( "interface_dcl: case 1\n" ); 
							yyval.void_ptr = buildInterface_Dcl( yypvt[-3].void_ptr, yypvt[-1].void_ptr );
							} /*NOTREACHED*/ break;
case 14:{	if( compiler_debug_state == DEBUG_ON )printf( "forward_dcl: case 1:xIDENTIFIER\n" ); 
																		yyval.void_ptr = buildForward_Dcl( yypvt[-1].str_lit, yypvt[-0].str_lit );
																	} /*NOTREACHED*/ break;
case 15:{	if( compiler_debug_state == DEBUG_ON )printf( "interface_header: case 1:xIDENTIFIER\n" ); 
																		yyval.void_ptr = buildInterface_Header( yypvt[-1].str_lit, yypvt[-0].str_lit, NULL );
																	} /*NOTREACHED*/ break;
case 16:{	if( compiler_debug_state == DEBUG_ON )printf( "interface_header: case 2:xIDENTIFIER\n" );																		
																		yyval.void_ptr = buildInterface_Header( yypvt[-2].str_lit, yypvt[-1].str_lit, yypvt[-0].void_ptr );
																	} /*NOTREACHED*/ break;
case 17:{	if( compiler_debug_state == DEBUG_ON )printf( "interface_body: case 1\n" ); yyval.void_ptr=NULL; /*Flag to show no interface_body has been built*/ } /*NOTREACHED*/ break;
case 18:{	void	*ptr;
															if( compiler_debug_state == DEBUG_ON )printf( "interface_body: case 2\n" ); 
															if( compiler_debug_state == DEBUG_ON )printf( "$1= %x\t $2= %x\n", yypvt[-1].void_ptr, yypvt[-0].void_ptr );
															/* Create an interface_body object if necessary */
															if( yypvt[-1].void_ptr == NULL )
																{
																/* We need to create an interface_body object */
																yyval.void_ptr = buildInterface_Body();
																ptr = yyval.void_ptr;
																}
															else
																{
																//interface_body object already exists:
																ptr = yypvt[-1].void_ptr;
																}

															/* Add the export item to the interface_body */
															addExport( ptr, yypvt[-0].void_ptr );
									   
														} /*NOTREACHED*/ break;
case 19:{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 1: type_dcl  \n" );	yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 20:{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 2: const_dcl \n" );	yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 21:{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 3: except_dcl\n" );	yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 22:{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 4: attr_dcl  \n" );	yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 23:{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 5: op_dcl    \n" );	yyval.void_ptr=yypvt[-1].void_ptr;	} /*NOTREACHED*/ break;
case 24:{	
															if( compiler_debug_state == DEBUG_ON )printf( "inheritance_spec: case 1\n" );	/*build obj with scoped_name array */
															yyval.void_ptr = buildInheritance_Spec( scoped_name_array, scoped_name_count );

															/* Handle reset details */
															reset_void_array( &scoped_name_array, &scoped_name_count, &scoped_name_array_limit );
														} /*NOTREACHED*/ break;
case 25:{	void *ptr; 
															if( compiler_debug_state == DEBUG_ON )printf( "aux_1: case 1\n" ); 
															ptr = Scoped_Name_buildHandler();

															/* Add this scoped_name object to the scoped_name object array */
															load_scoped_name_array( ptr );	
																																													
															/* return type is not important here */
															yyval.void_ptr=NULL;																																							
														} /*NOTREACHED*/ break;
case 26:{	void *ptr;
															if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 1\n" ); 
															ptr = Scoped_Name_buildHandler();

															/* Add this scoped_name object to the scoped_name object array */
															load_scoped_name_array( ptr );	
																																													
															/* return type is not important here */
															yyval.void_ptr=NULL;	
														} /*NOTREACHED*/ break;
case 27:{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 1\n" );
																	
																	/* Set the scope type */ 
																	scoped_name_scope_flag = RELATIVE_SCOPE;

																	yyval.void_ptr=NULL;							 

																	load_scoped_name_list_array( yypvt[-0].str_lit );	
																} /*NOTREACHED*/ break;
case 28:{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 2\n" );

																	/* Set the scope type */ 
																	scoped_name_scope_flag = GLOBAL_SCOPE;

																	yyval.void_ptr=NULL; 

																	load_scoped_name_list_array( yypvt[-0].str_lit );	
																} /*NOTREACHED*/ break;
case 29:{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 3\n" ); 
																	yyval.void_ptr=NULL; 
																	load_scoped_name_list_array( yypvt[-0].str_lit );	
																} /*NOTREACHED*/ break;
case 30:{	if( compiler_debug_state == DEBUG_ON )printf( "const_dcl: case 1\n" ); 
																		yyval.void_ptr = buildConst_Dcl( yypvt[-4].str_lit, yypvt[-3].void_ptr, yypvt[-2].str_lit, yypvt[-0].void_ptr );																		
																	} /*NOTREACHED*/ break;
case 31:{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 1\n" ); 
													yyval.void_ptr = buildConst_Type1( yypvt[-0].str_lit );
												} /*NOTREACHED*/ break;
case 32:{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 2\n" ); 
													yyval.void_ptr = buildConst_Type1( yypvt[-0].str_lit );					
												} /*NOTREACHED*/ break;
case 33:{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 3\n" ); 
													yyval.void_ptr = buildConst_Type1( yypvt[-0].str_lit );																										
												} /*NOTREACHED*/ break;
case 34:{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 4\n" ); 
													yyval.void_ptr = buildConst_Type1( yypvt[-0].str_lit );
												} /*NOTREACHED*/ break;
case 35:{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 5\n" );
													yyval.void_ptr = buildConst_Type2( yypvt[-0].void_ptr );													
												} /*NOTREACHED*/ break;
case 36:{	void *ptr;
													if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 6\n" ); 	/*scoped_name as a type??? */
													ptr = Scoped_Name_buildHandler();
													yyval.void_ptr = buildConst_Type2( ptr );
												} /*NOTREACHED*/ break;
case 37:{	if( compiler_debug_state == DEBUG_ON )printf( "const_exp:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 38:{	if( compiler_debug_state == DEBUG_ON )printf( "or_expr:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 39:{	if( compiler_debug_state == DEBUG_ON )printf( "or_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '|' );																
															} /*NOTREACHED*/ break;
case 40:{	if( compiler_debug_state == DEBUG_ON )printf( "xor_expr:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 41:{ 	if( compiler_debug_state == DEBUG_ON )printf( "xor_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '^' );
															} /*NOTREACHED*/ break;
case 42:{	if( compiler_debug_state == DEBUG_ON )printf( "and_expr:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 43:{ 	if( compiler_debug_state == DEBUG_ON )printf( "and_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '&' );
															} /*NOTREACHED*/ break;
case 44:{	if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 45:{	if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 2\n" );
																/* We will pass the single char '>' to signify a '>>' right-shift. */
																/* This will be interpreted by the buildGSIobject() routines     */
																/* as a '>>' */
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '>' );
															} /*NOTREACHED*/ break;
case 46:{   if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 3\n" );
																/* We will pass the single char '<' to signify a '<<' left-shift. */
																/* This will be interpreted by the buildGSIobject() routines     */
																/* as a '<<' */
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '<' );

															} /*NOTREACHED*/ break;
case 47:{	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 48:{ 	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 2\n" );
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '+' );
															} /*NOTREACHED*/ break;
case 49:{	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 3\n" );
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '-' );
															} /*NOTREACHED*/ break;
case 50:{	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 51:{	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 2\n" );	
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '*' );
															} /*NOTREACHED*/ break;
case 52:{ 	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 3\n" );	
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '/' );
															} /*NOTREACHED*/ break;
case 53:{ 	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 4\n" );	
																yyval.void_ptr = buildMath_Expression( yypvt[-2].void_ptr, yypvt[-0].void_ptr, '%' );
															} /*NOTREACHED*/ break;
case 54:{	if( compiler_debug_state == DEBUG_ON )printf( "unary_expr:case 1\n" );	
																setUnaryOperator( yypvt[-1].tok_val, yypvt[-0].void_ptr );
																yyval.void_ptr=yypvt[-0].void_ptr;
															} /*NOTREACHED*/ break;
case 55:{	if( compiler_debug_state == DEBUG_ON )printf( "unary_expr:case 2\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 56:{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 1\n" );	yyval.tok_val='-';	} /*NOTREACHED*/ break;
case 57:{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 2\n" );	yyval.tok_val='+';	} /*NOTREACHED*/ break;
case 58:{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 3\n" );	yyval.tok_val='~';	} /*NOTREACHED*/ break;
case 59:{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 1\n" );
																yyval.void_ptr = Scoped_Name_buildHandler();								
															} /*NOTREACHED*/ break;
case 60:{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 2\n" );
																yyval.void_ptr = yypvt[-0].void_ptr;
															} /*NOTREACHED*/ break;
case 61:{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 3\n" );
																yyval.void_ptr = yypvt[-1].void_ptr;
																/* We can disallow a unary operator attached to the (...) 
																   as John H does. */
															} /*NOTREACHED*/ break;
case 62:{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 1: $1= %d\n", yypvt[-0].lng_val  );
																yyval.void_ptr = buildLongIntegerLiteral( yypvt[-0].lng_val );																
															} /*NOTREACHED*/ break;
case 63:{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 2\n" );																
																yyval.void_ptr = buildStringLiteral( yypvt[-0].str_lit ); 
															} /*NOTREACHED*/ break;
case 64:{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 3: $1= %c\n", yypvt[-0].chr_val  );
																yyval.void_ptr = buildCharLiteral( yypvt[-0].chr_val ); 
															} /*NOTREACHED*/ break;
case 65:{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 4: $1= %f\n", yypvt[-0].dbl_val  );
																yyval.void_ptr = buildDoubleLiteral( yypvt[-0].dbl_val ); 
															} /*NOTREACHED*/ break;
case 66:{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 5\n" );
																yyval.void_ptr = buildBooleanLiteral( yypvt[-0].void_ptr ); 
															} /*NOTREACHED*/ break;
case 67:{	if( compiler_debug_state == DEBUG_ON )printf( "boolean_literal:case 1\n" );	yyval.void_ptr=yypvt[-0].str_lit; 	} /*NOTREACHED*/ break;
case 68:{	if( compiler_debug_state == DEBUG_ON )printf( "boolean_literal:case 2\n" );	yyval.void_ptr=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 69:{	if( compiler_debug_state == DEBUG_ON )printf( "positive_int_const:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 70:{	if( compiler_debug_state == DEBUG_ON )( "type_dcl:case 1\n" );		
																yyval.void_ptr = buildType_Dcl_Case1( yypvt[-1].str_lit, yypvt[-0].void_ptr );
															} /*NOTREACHED*/ break;
case 71:{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 2\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 72:{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 3\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 73:{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 4\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 74:{	
/* Identical code to 'member' */								if( compiler_debug_state == DEBUG_ON )printf( "type_declarator:case 1\n" ); /*build object with declarators array.*/
																yyval.void_ptr = buildType_Declarator( yypvt[-1].void_ptr, declarator_array, declarator_count );

																/* Handle reset details */
																reset_void_array( &declarator_array, &declarator_count, &declarator_array_limit );
															} /*NOTREACHED*/ break;
case 75:{	if( compiler_debug_state == DEBUG_ON )printf( "type_spec:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 76:{	if( compiler_debug_state == DEBUG_ON )printf( "type_spec:case 2\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 77:{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 1\n" );
												yyval.void_ptr = buildBase_Type_Spec( yypvt[-0].str_lit );
											} /*NOTREACHED*/ break;
case 78:{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 2\n" );
												yyval.void_ptr=yypvt[-0].void_ptr;
											} /*NOTREACHED*/ break;
case 79:{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 3\n" );	
												yyval.void_ptr = Scoped_Name_buildHandler();
											} /*NOTREACHED*/ break;
case 80:{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 1\n");
												yyval.str_lit=yypvt[-0].str_lit;
											} /*NOTREACHED*/ break;
case 81:{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 2\n" );
												yyval.str_lit=yypvt[-0].str_lit;		
											} /*NOTREACHED*/ break;
case 82:{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 3\n" );
												yyval.str_lit=yypvt[-0].str_lit;
											} /*NOTREACHED*/ break;
case 83:{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 4\n" );
												yyval.str_lit=yypvt[-0].str_lit;
											} /*NOTREACHED*/ break;
case 84:{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 5\n" );
												yyval.str_lit=yypvt[-0].str_lit;
											} /*NOTREACHED*/ break;
case 85:{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 6\n" );
												yyval.str_lit=yypvt[-0].str_lit;
											} /*NOTREACHED*/ break;
case 86:{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 7\n" );
												yyval.str_lit=yypvt[-0].str_lit;
											} /*NOTREACHED*/ break;
case 87:{	if( compiler_debug_state == DEBUG_ON )printf( "template_type_spec:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 88:{	if( compiler_debug_state == DEBUG_ON )printf( "template_type_spec:case 2\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 89:{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 90:{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 2\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 91:{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 3\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 92:{	if( compiler_debug_state == DEBUG_ON )printf( "declarators:case 1\n" );	/*declarator_srray is fully loaded at this point*/ } /*NOTREACHED*/ break;
case 93:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr; load_declarator_array( yypvt[-0].void_ptr ); } /*NOTREACHED*/ break;
case 94:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 2\n" );	yyval.void_ptr=yypvt[-2].void_ptr; load_declarator_array( yypvt[-0].void_ptr ); } /*NOTREACHED*/ break;
case 95:{	if( compiler_debug_state == DEBUG_ON )printf( "declarator:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 96:{	if( compiler_debug_state == DEBUG_ON )printf( "declarator:case 2\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 97:{	if( compiler_debug_state == DEBUG_ON )printf( "simple_declarator:case 1\n" );
													yyval.void_ptr = buildSimple_Declarator( yypvt[-0].str_lit );
												} /*NOTREACHED*/ break;
case 98:{	if( compiler_debug_state == DEBUG_ON )printf( "complex_declarator:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	} /*NOTREACHED*/ break;
case 99:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xFLOAT\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 100:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xDOUBLE\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 101:{	if( compiler_debug_state == DEBUG_ON )printf( "integer_type:signed_int\n" );		yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 102:{	if( compiler_debug_state == DEBUG_ON )printf( "integer_type:unsigned_int\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 103:{	if( compiler_debug_state == DEBUG_ON )printf( "signed_int:signed_long_int\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 104:{	if( compiler_debug_state == DEBUG_ON )printf( "signed_int:signed_short_int\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 105:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xLONG\n" );		yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 106:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xSHORT\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 107:{	if( compiler_debug_state == DEBUG_ON )printf( "unsigned_long_int:unsigned_long_int\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 108:{	if( compiler_debug_state == DEBUG_ON )printf( "unsigned_short_int:unsigned_short_int\n" );	yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 109:{	char	*u_long;
												u_long = (char *) malloc( 14 );
												strcpy( u_long, yypvt[-1].str_lit );
												strcat( u_long, " " ); 
												strcat( u_long, yypvt[-0].str_lit ); 
												yyval.str_lit = u_long;
												if( compiler_debug_state == DEBUG_ON )printf( "Got: xUNSIGNED xLONG\n" );
											} /*NOTREACHED*/ break;
case 110:{	char	*u_short;
												u_short = (char *) malloc( 15 );
												strcpy( u_short, yypvt[-1].str_lit );   
												strcat( u_short, " " ); 
												strcat( u_short, yypvt[-0].str_lit ); 
												yyval.str_lit = u_short;
												if( compiler_debug_state == DEBUG_ON )printf( "Got: xUNSIGNED xSHORT\n" );
											} /*NOTREACHED*/ break;
case 111:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xCHAR\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 112:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xBOOLEAN\n" );yyval.str_lit=yypvt[-0].str_lit;	} /*NOTREACHED*/ break;
case 113:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xOCTET\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 114:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xANY\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 115:{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xOBJECT\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 116:{	
																		if( compiler_debug_state == DEBUG_ON )printf( "struct_type:Got: xSTRUCT: $1= %ld\n", yypvt[-4].str_lit ); 
																		yyval.void_ptr = buildStruct_Type( yypvt[-4].str_lit, yypvt[-3].str_lit, member_array, member_count );

																		/* Handle reset details */
																		reset_void_array( &member_array, &member_count, &member_array_limit );
																	} /*NOTREACHED*/ break;
case 117:{	if( compiler_debug_state == DEBUG_ON )printf( "member_list:case 1\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	load_member_array( yypvt[-0].void_ptr );	} /*NOTREACHED*/ break;
case 118:{	if( compiler_debug_state == DEBUG_ON )printf( "member_list:case 2\n" );	yyval.void_ptr=yypvt[-0].void_ptr;	load_member_array( yypvt[-0].void_ptr );	} /*NOTREACHED*/ break;
case 119:{	int i;
/* Identical code to 'type_declarator' */					if( compiler_debug_state == DEBUG_ON )printf( "member:case 1\n" );	/*build obj with declarators array*/ 
															yyval.void_ptr = buildMember( yypvt[-2].void_ptr, declarator_array, declarator_count );

															/* Clear declarator_array and then clear declarator_count */
															for( i=0 ; i<attr_dcl_count ; i++ )
																declarator_array[i] = NULL;
																
															declarator_count = 0;
														} /*NOTREACHED*/ break;
case 120:{ 
							if( compiler_debug_state == DEBUG_ON )printf( "union_type: case 1\n" );
							
							yyval.void_ptr = buildUnion_Type( yypvt[-8].str_lit, yypvt[-7].str_lit, yypvt[-6].str_lit, yypvt[-4].void_ptr, switch_body_array, switch_body_count );
							
							/* Handle reset details */
							reset_void_array( &switch_body_array, &switch_body_count, &switch_body_array_limit );	
							} /*NOTREACHED*/ break;
case 121:{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 1\n" ); 
													yyval.void_ptr = buildSwitch_Type_Spec1( yypvt[-0].str_lit );
												} /*NOTREACHED*/ break;
case 122:{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 2\n" ); 
													yyval.void_ptr = buildSwitch_Type_Spec1( yypvt[-0].str_lit );					
												} /*NOTREACHED*/ break;
case 123:{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 3\n" ); 
													yyval.void_ptr = buildSwitch_Type_Spec1( yypvt[-0].str_lit );																	
												} /*NOTREACHED*/ break;
case 124:{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 5\n" );
													yyval.void_ptr = buildSwitch_Type_Spec2( yypvt[-0].void_ptr );													
												} /*NOTREACHED*/ break;
case 125:{	void *ptr;
													if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 6\n" ); 	/*scoped_name as a type??? */
													ptr = Scoped_Name_buildHandler();
													yyval.void_ptr = buildSwitch_Type_Spec2( ptr );
												} /*NOTREACHED*/ break;
case 126:{	if( compiler_debug_state == DEBUG_ON )printf( "switch_body: case 1\n" );	yyval.tok_val=0;	load_switch_body_array( yypvt[-0].void_ptr );	} /*NOTREACHED*/ break;
case 127:{	if( compiler_debug_state == DEBUG_ON )printf( "switch_body: case 2\n" );	yyval.tok_val=0;	load_switch_body_array( yypvt[-0].void_ptr );	} /*NOTREACHED*/ break;
case 128:{	 
														if( compiler_debug_state == DEBUG_ON )printf( "case: case 1\n" ); /*case_label_array is fully loaded at this point*/
														yyval.void_ptr = buildCase( case_label_array, case_label_count, yypvt[-1].void_ptr );	
							
														/* Handle reset details */
														reset_void_array( &case_label_array, &case_label_count, &case_label_array_limit );	
													} /*NOTREACHED*/ break;
case 129:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_3: case 1\n" ); yyval.tok_val=0; load_case_label_array( yypvt[-0].void_ptr ); } /*NOTREACHED*/ break;
case 130:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_3: case 2\n" ); yyval.tok_val=0; load_case_label_array( yypvt[-0].void_ptr ); } /*NOTREACHED*/ break;
case 131:{	if( compiler_debug_state == DEBUG_ON )printf( "case_label: case 1\n" ); 
														yyval.void_ptr = buildCase_Label( yypvt[-2].str_lit, yypvt[-1].void_ptr );
													} /*NOTREACHED*/ break;
case 132:{	if( compiler_debug_state == DEBUG_ON )printf( "case_label: case 2\n" );
														yyval.void_ptr = buildCase_Label( yypvt[-1].str_lit, NULL );
													} /*NOTREACHED*/ break;
case 133:{	if( compiler_debug_state == DEBUG_ON )printf( "element_spec: case 1\n" );
														yyval.void_ptr = buildElement_Spec( yypvt[-1].void_ptr, yypvt[-0].void_ptr );
													} /*NOTREACHED*/ break;
case 134:{
																					 
							if( compiler_debug_state == DEBUG_ON )printf( "enum_type: case 1\n" ); 
							
							yyval.void_ptr = buildEnum_Type( yypvt[-4].str_lit, yypvt[-3].str_lit, enumerator_array, enumerator_count );
														
							/* Handle reset details */
							reset_char_array( &enumerator_array, &enumerator_count, &enumerator_array_limit );
							} /*NOTREACHED*/ break;
case 135:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_4: case 1\n" ); yyval.tok_val=0; load_enumerator_array(yypvt[-0].str_lit); } /*NOTREACHED*/ break;
case 136:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_4: case 2\n" ); yyval.tok_val=0; load_enumerator_array(yypvt[-0].str_lit); } /*NOTREACHED*/ break;
case 137:{	if( compiler_debug_state == DEBUG_ON )printf( "enumerator: case 1:\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 138:{	if( compiler_debug_state == DEBUG_ON )printf( "sequence_type: case 1\n" ); 
																						yyval.void_ptr = buildSequence_Type( yypvt[-5].str_lit, yypvt[-3].void_ptr, yypvt[-1].void_ptr );
																					} /*NOTREACHED*/ break;
case 139:{	if( compiler_debug_state == DEBUG_ON )printf( "sequence_type: case 2\n" ); 
																						yyval.void_ptr = buildSequence_Type( yypvt[-3].str_lit, yypvt[-1].void_ptr, NULL );
																					} /*NOTREACHED*/ break;
case 140:{	if( compiler_debug_state == DEBUG_ON )printf( "string_type:case 1\n" );	
																yyval.void_ptr = buildString_Type( yypvt[-3].str_lit, yypvt[-1].void_ptr );
															} /*NOTREACHED*/ break;
case 141:{	if( compiler_debug_state == DEBUG_ON )printf( "string_type:case 2\n" );
																yyval.void_ptr = buildString_Type( yypvt[-0].str_lit, NULL );															
															} /*NOTREACHED*/ break;
case 142:{	 
																if( compiler_debug_state == DEBUG_ON )printf( "array_declarator: case 1\n" ); 
																
																/*fixed_array_size_array is fully loaded at this point*/				
																yyval.void_ptr = buildArray_Declarator( yypvt[-1].str_lit, fixed_array_size_array, fixed_array_size_count );	

																/* Handle reset details */
																reset_void_array( &fixed_array_size_array, &fixed_array_size_count, &fixed_array_size_array_limit );									
															} /*NOTREACHED*/ break;
case 143:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_5: case 1\n" ); yyval.tok_val=0; load_fixed_array_size_array( yypvt[-0].void_ptr );	} /*NOTREACHED*/ break;
case 144:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_5: case 2\n" ); yyval.tok_val=0; load_fixed_array_size_array( yypvt[-0].void_ptr );	} /*NOTREACHED*/ break;
case 145:{	if( compiler_debug_state == DEBUG_ON )printf( "fixed_array_size: case 1\n" );	yyval.void_ptr=yypvt[-1].void_ptr; } /*NOTREACHED*/ break;
case 146:{
							
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl: case 1\n" );
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl_count= %d\n", attr_dcl_count );
							
							yyval.void_ptr = buildAttr_Dcl( NO_READONLY, yypvt[-2].str_lit, yypvt[-1].void_ptr, attr_dcl_array, attr_dcl_count );
							
							/* Handle reset details */
							reset_void_array( &attr_dcl_array, &attr_dcl_count, &attr_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 147:{ 
							
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl: case 3\n" );
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl_count= %d\n", attr_dcl_count );
							
							yyval.void_ptr = buildAttr_Dcl( YES_READONLY, yypvt[-2].str_lit, yypvt[-1].void_ptr, attr_dcl_array, attr_dcl_count );

							/* Handle reset details */
							reset_void_array( &attr_dcl_array, &attr_dcl_count, &attr_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 148:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_6: case 1:\n" ); yyval.str_lit=yypvt[-0].void_ptr; load_attr_dcl_array(yypvt[-0].void_ptr); } /*NOTREACHED*/ break;
case 149:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_6: case 2:\n" ); yyval.str_lit=yypvt[-2].str_lit; load_attr_dcl_array(yypvt[-0].void_ptr); } /*NOTREACHED*/ break;
case 150:{	if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 1\n" );
																		/* The member_array will have no members and the count 
																		 * wiil be 0. This will be handled by the constructor */ 
																		yyval.void_ptr = buildExcept_Dcl( yypvt[-3].str_lit, yypvt[-2].str_lit, member_array, member_count );
																	} /*NOTREACHED*/ break;
case 151:{	
																		if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 2\n" );
																		yyval.void_ptr = buildExcept_Dcl( yypvt[-4].str_lit, yypvt[-3].str_lit, member_array, member_count );

																		/* Handle reset details */
																		reset_void_array( &member_array, &member_count, &member_array_limit );
																	} /*NOTREACHED*/ break;
case 152:{
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 1\n" );
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yypvt[-2].void_ptr, yypvt[-1].str_lit, param_dcl_array, param_dcl_count, NULL, NULL );
														
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 153:{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 2\n" ); 																		 
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yypvt[-3].void_ptr, yypvt[-2].str_lit, param_dcl_array, param_dcl_count, yypvt[-0].void_ptr, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 154:{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 3\n" );
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yypvt[-3].void_ptr, yypvt[-2].str_lit, param_dcl_array, param_dcl_count, NULL, yypvt[-0].void_ptr );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 155:{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 4\n" ); 
							yyval.void_ptr = buildOp_Dcl( NO_OPATTRIBUTE, yypvt[-4].void_ptr, yypvt[-3].str_lit, param_dcl_array, param_dcl_count, yypvt[-1].void_ptr, yypvt[-0].void_ptr );
														
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit ); 
							} /*NOTREACHED*/ break;
case 156:{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 5\n" ); 																		 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yypvt[-2].void_ptr, yypvt[-1].str_lit, param_dcl_array, param_dcl_count, NULL, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 157:{
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 5\n" ); 																		 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yypvt[-3].void_ptr, yypvt[-2].str_lit, param_dcl_array, param_dcl_count, yypvt[-0].void_ptr, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 158:{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 7\n" ); 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yypvt[-3].void_ptr, yypvt[-2].str_lit, param_dcl_array, param_dcl_count, NULL, yypvt[-0].void_ptr );
							
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );							
							} /*NOTREACHED*/ break;
case 159:{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 8\n" ); 
							yyval.void_ptr = buildOp_Dcl( YES_OPATTRIBUTE, yypvt[-4].void_ptr, yypvt[-3].str_lit, param_dcl_array, param_dcl_count, yypvt[-1].void_ptr, yypvt[-0].void_ptr );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							} /*NOTREACHED*/ break;
case 160:{	if( compiler_debug_state == DEBUG_ON )printf( "op_attribute: case 1: Got xONEWAY:$1 = %d\n", yypvt[-0].str_lit );	yyval.str_lit=yypvt[-0].str_lit; } /*NOTREACHED*/ break;
case 161:{	if( compiler_debug_state == DEBUG_ON )printf( "op_type_spec: case 1:$1= %x\n", yypvt[-0].void_ptr );
												yyval.void_ptr = buildOp_Type_Spec1( yypvt[-0].void_ptr );
											} /*NOTREACHED*/ break;
case 162:{	if( compiler_debug_state == DEBUG_ON )printf( "op_type_spec: case 2\n" );
												yyval.void_ptr = buildOp_Type_Spec2( yypvt[-0].str_lit );					
											} /*NOTREACHED*/ break;
case 163:{	if( compiler_debug_state == DEBUG_ON )printf( "parameter_dcls: case 1\n" ); 
															/* For this case, we will let parent rule build an object. */
															yyval.void_ptr = NULL;
														} /*NOTREACHED*/ break;
case 164:{ 
															if( compiler_debug_state == DEBUG_ON )printf( "parameter_dcls: case 3\n" ); 
															/* Any rule using parameter_dcls will check the param_dcl count. */
															/* If it is 0, this is the case that matched. */
															yyval.void_ptr = NULL;
														} /*NOTREACHED*/ break;
case 165:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_8: case 1\n" ); yyval.tok_val=0;	} /*NOTREACHED*/ break;
case 166:{	if( compiler_debug_state == DEBUG_ON )printf( "aux_8: case 2\n" ); yyval.tok_val=0;	} /*NOTREACHED*/ break;
case 167:{ 
							void	*ptr;
							if( compiler_debug_state == DEBUG_ON )printf( "param_dcl:$2= %x\t $3= %x\n", yypvt[-1].void_ptr, yypvt[-0].void_ptr ); 

							ptr = buildParam_Dcl( yypvt[-2].str_lit, yypvt[-1].void_ptr, yypvt[-0].void_ptr );

							/* Add this param_dcl object to the param_dcl object array */
							load_param_dcl_array( ptr );	

							/* The semantic value of each param_dcl is not used individually */
							yyval.void_ptr = NULL;
							} /*NOTREACHED*/ break;
case 168:{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 1\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 169:{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 2\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 170:{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 3\n" );	yyval.str_lit=yypvt[-0].str_lit;		} /*NOTREACHED*/ break;
case 171:{	if( compiler_debug_state == DEBUG_ON )printf( "raises_expr: case 1\n" ); /*build obj with scoped_name array */
																yyval.void_ptr = buildRaises_Expr( scoped_name_array, scoped_name_count );

																/* Handle reset details */
																reset_void_array( &scoped_name_array, &scoped_name_count, &scoped_name_array_limit );
															} /*NOTREACHED*/ break;
case 172:{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_9: case 1\n" ); 
																ptr = Scoped_Name_buildHandler();

																/* Add this scoped_name object to the scoped_name object array */
																load_scoped_name_array( ptr );	
																																														
																/* return type is not important here */
																yyval.tok_val=0;				
															} /*NOTREACHED*/ break;
case 173:{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_9: case 2\n" ); 
																ptr = Scoped_Name_buildHandler();

																/* Add this scoped_name object to the scoped_name object array */
																load_scoped_name_array( ptr );	
																																														
																/* return type is not important here */
																yyval.tok_val=0;				
															} /*NOTREACHED*/ break;
case 174:{	if( compiler_debug_state == DEBUG_ON )printf( "context_expr: case 1\n" );
																yyval.void_ptr = buildContext_Expr( yypvt[-3].str_lit, string_literal_array, string_literal_count );
							
																/* Handle reset details */
																reset_void_array( &string_literal_array, &string_literal_count, &string_literal_array_limit );							
															} /*NOTREACHED*/ break;
case 175:{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_10: case 1\n" ); 
																yyval.tok_val = 0;	/* value of aux_10 is not used */																
																ptr = buildStringLiteral( yypvt[-0].str_lit );
																load_string_literal_array( ptr );	
															} /*NOTREACHED*/ break;
case 176:{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_10: case 2\n" );
																yyval.tok_val = 0;	/* value of aux_10 is not used */																
																ptr = buildStringLiteral( yypvt[-0].str_lit );
																load_string_literal_array( ptr );	
															} /*NOTREACHED*/ break;
case 177:{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 1\n" );		
																yyval.void_ptr = buildBase_Type_Spec( yypvt[-0].str_lit );
															} /*NOTREACHED*/ break;
case 178:{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 2\n" ); 
																yyval.void_ptr=yypvt[-0].void_ptr;
															} /*NOTREACHED*/ break;
case 179:{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 3\n" ); 
																yyval.void_ptr = Scoped_Name_buildHandler();
															} /*NOTREACHED*/ break;
}


	goto yystack;		/* reset registers in driver code */
}
