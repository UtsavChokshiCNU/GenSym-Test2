/* Bison grammar file. */

%{

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

%}

/*
Bison declarations
The Bison declarations declare the names of the terminal and nonterminal symbols, and may also 
describe operator precedence and the data types of semantic values of various symbols.
*/
%union 
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
	}

%type	<tok_val>	unary_operator switch_body aux_11 aux_3 aux_4 aux_5 aux_8 aux_9 aux_10

%type	<str_lit>	signed_short_int signed_long_int signed_int unsigned_int unsigned_long_int unsigned_short_int
%type	<str_lit>	integer_type floating_pt_type base_type_spec char_type boolean_type octet_type any_type 
%type	<str_lit>	aux_6 param_attribute enumerator op_attribute object_type

%type	<void_ptr>	param_type_spec attr_dcl export interface_body interface_header interface_dcl forward_dcl
%type	<void_ptr>	interface definition specification op_type_spec param_dcl parameter_dcls enum_type
%type	<void_ptr>	type_dcl constr_type_spec simple_type_spec type_spec op_dcl simple_declarator declarator
%type	<void_ptr>	member member_list declarators aux_2 scoped_name const_type primary_expr literal
%type	<void_ptr>	const_exp or_expr xor_expr and_expr shift_expr add_expr mult_expr unary_expr
%type	<void_ptr>	positive_int_const string_type switch_type_spec union_type boolean_literal const_dcl
%type	<void_ptr>	struct_type element_spec raises_expr except_dcl case case_label sequence_type 
%type	<void_ptr>	fixed_array_size array_declarator complex_declarator template_type_spec 
%type	<void_ptr>	type_declarator module inheritance_spec context_expr aux_1

%token	<str_lit>	xANY xATTRIBUTE xBOOLEAN xCASE xCHAR xCONST xCONTEXT xDEFAULT xDOUBLE xENUM xEXCEPTION 
%token  <str_lit>	xFALSE xFLOAT xIN xINOUT xINTERFACE xLONG xMODULE xOBJECT xOCTET xONEWAY xOUT xRAISES 
%token  <str_lit>	xREADONLY xSEQUENCE xSHORT xSTRING xSTRUCT xSWITCH xTRUE xTYPEDEF xUNSIGNED xUNION xVOID

%token	<tok_val>	OPERATOR PUNCTUATOR LITERAL IDENTIFIER KEYWORD
%token	<tok_val>	LITERAL_DECINT LITERAL_HEXINT LITERAL_OCTINT LITERAL_FP	LITERAL_CHAR LITERAL_CHARHEX 
%token	<tok_val>	LITERAL_CHAROCT LITERAL_STRING
%token	<tok_val>	DOUBLE_COLON DOUBLE_LT DOUBLE_GT
%token	<dbl_val>	FLOATING_PT_LITERAL
%token	<chr_val>	CHARACTER_LITERAL
%token	<str_lit>	STRING_LITERAL
%token	<lng_val>	INTEGER_LITERAL
%token	<str_lit>	xIDENTIFIER



%right	'='
%left	'|'
%left	'^'
%left	'&'										/* Lowest precedence  */
%left	'-' '+'									/*			|		  */
%left	'*' '/' '%'								/*			|		  */
%left	NEG     /* Negation--unary minus */		/*			V		  */
												/* Highest precedence */

%start	specification			/* Explicitly name the start rule */

%%
/*
Grammar rules
The grammar rules define how to construct each nonterminal symbol from its parts. 
*/

specification:			definition					{	if( compiler_debug_state == DEBUG_ON )printf( "specification:case 1\n" );		
														if( compiler_debug_state == DEBUG_ON )printf( "$1= %x\n", $1 );
														/* Create the specification object */
														$$ = buildSpecification();
													  
														/* Load the Builder object with this value for later use */
														loadParseTreeRoot( $$ );

														/* Add the first definition item to the specification */
														addDefinition( $$, $1 );
									   				
													}
					|	specification definition	{	if( compiler_debug_state == DEBUG_ON )printf( "specification:case 2\n" );
														
														/* Add the subsequent definition items to the specification */
														addDefinition( $$, $2 );													
													}
					/*
					|	error						{	yyerrok;  								} 
					*/
;

definition:				type_dcl ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 1\n" ); $$=$1;	}
					|	const_dcl ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 2\n" ); $$=$1;	}
					|	except_dcl ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 3\n" ); $$=$1;	}
					|	interface ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 4\n" ); $$=$1;	}
					|	module ';'					{	if( compiler_debug_state == DEBUG_ON )printf( "definition: case 5\n" ); $$=$1;	}
;


module:					xMODULE xIDENTIFIER '{' aux_11 '}'			
							{
							int i=0;
							
							if( compiler_debug_state == DEBUG_ON )printf( "module: case 1\n" );
							for( i=0 ; i<module_definition_count ; i++ )
								if( compiler_debug_state == DEBUG_ON )printf( "module_definition_array[%d]= %x\n", i, module_definition_array[i] );

							$$ = buildModule( $1, $2, module_definition_array, module_definition_count );
														  
							/* Handle reset details */
							reset_void_array( &module_definition_array, &module_definition_count, &module_definition_array_limit );
							}
;
											    
aux_11:					definition			{	if( compiler_debug_state == DEBUG_ON )printf( "aux_11: case 1\n" ); $$=0; load_module_definition_array($1); }
					|	aux_11 definition	{	if( compiler_debug_state == DEBUG_ON )printf( "aux_11: case 2\n" ); $$=0; load_module_definition_array($2); }
;


interface:				interface_dcl			{	if( compiler_debug_state == DEBUG_ON )printf( "interface: case 1\n" ); $$=$1;	}
					|	forward_dcl				{	if( compiler_debug_state == DEBUG_ON )printf( "interface: case 2\n" ); $$=$1;	}
;

interface_dcl:			interface_header '{' interface_body '}'		
							{
							if( compiler_debug_state == DEBUG_ON )printf( "interface_dcl: case 1\n" ); 
							$$ = buildInterface_Dcl( $1, $3 );
							}
;

forward_dcl:			xINTERFACE xIDENTIFIER						{	if( compiler_debug_state == DEBUG_ON )printf( "forward_dcl: case 1:xIDENTIFIER\n" ); 
																		$$ = buildForward_Dcl( $1, $2 );
																	}
;

interface_header:		xINTERFACE xIDENTIFIER						{	if( compiler_debug_state == DEBUG_ON )printf( "interface_header: case 1:xIDENTIFIER\n" ); 
																		$$ = buildInterface_Header( $1, $2, NULL );
																	}
					|	xINTERFACE xIDENTIFIER inheritance_spec		{	if( compiler_debug_state == DEBUG_ON )printf( "interface_header: case 2:xIDENTIFIER\n" );																		
																		$$ = buildInterface_Header( $1, $2, $3 );
																	}
;

interface_body:			/* Empty */						{	if( compiler_debug_state == DEBUG_ON )printf( "interface_body: case 1\n" ); $$=NULL; /*Flag to show no interface_body has been built*/ }
					|	interface_body export			{	void	*ptr;
															if( compiler_debug_state == DEBUG_ON )printf( "interface_body: case 2\n" ); 
															if( compiler_debug_state == DEBUG_ON )printf( "$1= %x\t $2= %x\n", $1, $2 );
															/* Create an interface_body object if necessary */
															if( $1 == NULL )
																{
																/* We need to create an interface_body object */
																$$ = buildInterface_Body();
																ptr = $$;
																}
															else
																{
																//interface_body object already exists:
																ptr = $1;
																}

															/* Add the export item to the interface_body */
															addExport( ptr, $2 );
									   
														}
;


export:					type_dcl ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 1: type_dcl  \n" );	$$=$1;	}
					|	const_dcl ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 2: const_dcl \n" );	$$=$1;	}
					|	except_dcl ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 3: except_dcl\n" );	$$=$1;	}
					|	attr_dcl ';'				{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 4: attr_dcl  \n" );	$$=$1;	}					 
					|	op_dcl ';'					{	if( compiler_debug_state == DEBUG_ON )printf( "export: case 5: op_dcl    \n" );	$$=$1;	} 
;					 


inheritance_spec:		':' aux_1 						{	
															if( compiler_debug_state == DEBUG_ON )printf( "inheritance_spec: case 1\n" );	/*build obj with scoped_name array */
															$$ = buildInheritance_Spec( scoped_name_array, scoped_name_count );

															/* Handle reset details */
															reset_void_array( &scoped_name_array, &scoped_name_count, &scoped_name_array_limit );
														}
;

aux_1:					scoped_name						{	void *ptr; 
															if( compiler_debug_state == DEBUG_ON )printf( "aux_1: case 1\n" ); 
															ptr = Scoped_Name_buildHandler();

															/* Add this scoped_name object to the scoped_name object array */
															load_scoped_name_array( ptr );	
																																													
															/* return type is not important here */
															$$=NULL;																																							
														}
					|	aux_1 ',' scoped_name			{	void *ptr;
															if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 1\n" ); 
															ptr = Scoped_Name_buildHandler();

															/* Add this scoped_name object to the scoped_name object array */
															load_scoped_name_array( ptr );	
																																													
															/* return type is not important here */
															$$=NULL;	
														}
;

scoped_name:			xIDENTIFIER								{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 1\n" );
																	
																	/* Set the scope type */ 
																	scoped_name_scope_flag = RELATIVE_SCOPE;

																	$$=NULL;							 

																	load_scoped_name_list_array( $1 );	
																}
					|	DOUBLE_COLON xIDENTIFIER				{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 2\n" );

																	/* Set the scope type */ 
																	scoped_name_scope_flag = GLOBAL_SCOPE;

																	$$=NULL; 

																	load_scoped_name_list_array( $2 );	
																}
					|	scoped_name DOUBLE_COLON xIDENTIFIER	{	if( compiler_debug_state == DEBUG_ON )printf( "scoped_name: case 3\n" ); 
																	$$=NULL; 
																	load_scoped_name_list_array( $3 );	
																}
;

const_dcl:				xCONST const_type xIDENTIFIER '=' const_exp	{	if( compiler_debug_state == DEBUG_ON )printf( "const_dcl: case 1\n" ); 
																		$$ = buildConst_Dcl( $1, $2, $3, $5 );																		
																	}

const_type:				integer_type			{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 1\n" ); 
													$$ = buildConst_Type1( $1 );
												}
					|	char_type				{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 2\n" ); 
													$$ = buildConst_Type1( $1 );					
												}
					|	boolean_type			{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 3\n" ); 
													$$ = buildConst_Type1( $1 );																										
												}
					|	floating_pt_type		{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 4\n" ); 
													$$ = buildConst_Type1( $1 );
												}
					|	string_type				{	if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 5\n" );
													$$ = buildConst_Type2( $1 );													
												}
					|	scoped_name				{	void *ptr;
													if( compiler_debug_state == DEBUG_ON )printf( "const_type: case 6\n" ); 	/*scoped_name as a type??? */
													ptr = Scoped_Name_buildHandler();
													$$ = buildConst_Type2( ptr );
												}
;

const_exp:				or_expr								{	if( compiler_debug_state == DEBUG_ON )printf( "const_exp:case 1\n" );	$$=$1;	}		
;

or_expr:				xor_expr							{	if( compiler_debug_state == DEBUG_ON )printf( "or_expr:case 1\n" );	$$=$1;	}		
					|	or_expr '|' xor_expr				{	if( compiler_debug_state == DEBUG_ON )printf( "or_expr:case 2\n" );
																$$ = buildMath_Expression( $1, $3, '|' );																
															}
;

xor_expr:				and_expr							{	if( compiler_debug_state == DEBUG_ON )printf( "xor_expr:case 1\n" );	$$=$1;	}		
					|	xor_expr '^' and_expr				{ 	if( compiler_debug_state == DEBUG_ON )printf( "xor_expr:case 2\n" );
																$$ = buildMath_Expression( $1, $3, '^' );
															}
;

and_expr:				shift_expr							{	if( compiler_debug_state == DEBUG_ON )printf( "and_expr:case 1\n" );	$$=$1;	}		
					|	and_expr '&' shift_expr				{ 	if( compiler_debug_state == DEBUG_ON )printf( "and_expr:case 2\n" );
																$$ = buildMath_Expression( $1, $3, '&' );
															}
;

shift_expr:				add_expr					 		{	if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 1\n" );	$$=$1;	}		
					|	shift_expr DOUBLE_GT add_expr		{	if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 2\n" );
																/* We will pass the single char '>' to signify a '>>' right-shift. */
																/* This will be interpreted by the buildGSIobject() routines     */
																/* as a '>>' */
																$$ = buildMath_Expression( $1, $3, '>' );
															}		
					|	shift_expr DOUBLE_LT add_expr		{   if( compiler_debug_state == DEBUG_ON )printf( "shift_expr:case 3\n" );
																/* We will pass the single char '<' to signify a '<<' left-shift. */
																/* This will be interpreted by the buildGSIobject() routines     */
																/* as a '<<' */
																$$ = buildMath_Expression( $1, $3, '<' );

															}
;															

add_expr:				mult_expr					 		{	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 1\n" );	$$=$1;	}		
					|	add_expr '+' mult_expr				{ 	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 2\n" );
																$$ = buildMath_Expression( $1, $3, '+' );
															}
					|	add_expr '-' mult_expr				{	if( compiler_debug_state == DEBUG_ON )printf( "add_expr:case 3\n" );
																$$ = buildMath_Expression( $1, $3, '-' );
															}
;																
mult_expr:				unary_expr					 		{	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 1\n" );	$$=$1;	}		
					|	mult_expr '*' unary_expr			{	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 2\n" );	
																$$ = buildMath_Expression( $1, $3, '*' );
															}		
					|	mult_expr '/' unary_expr			{ 	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 3\n" );	
																$$ = buildMath_Expression( $1, $3, '/' );
															}		
					|	mult_expr '%' unary_expr			{ 	if( compiler_debug_state == DEBUG_ON )printf( "mult_expr:case 4\n" );	
																$$ = buildMath_Expression( $1, $3, '%' );
															}		
;
																											   
unary_expr:				unary_operator primary_expr			{	if( compiler_debug_state == DEBUG_ON )printf( "unary_expr:case 1\n" );	
																setUnaryOperator( $1, $2 );
																$$=$2;
															}		
					|	primary_expr						{	if( compiler_debug_state == DEBUG_ON )printf( "unary_expr:case 2\n" );	$$=$1;	}
;

unary_operator:			'-'									{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 1\n" );	$$='-';	}		
					|	'+'         						{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 2\n" );	$$='+';	}
					|	'~'         						{	if( compiler_debug_state == DEBUG_ON )printf( "unary_operator:case 3\n" );	$$='~';	}
;

primary_expr:			scoped_name							{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 1\n" );
																$$ = Scoped_Name_buildHandler();								
															}		
					|	literal								{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 2\n" );
																$$ = $1;
															}		
					|	'(' const_exp ')'					{	if( compiler_debug_state == DEBUG_ON )printf( "primary_expr:case 3\n" );
																$$ = $2;
																/* We can disallow a unary operator attached to the (...) 
																   as John H does. */
															}		
;

literal:				INTEGER_LITERAL						{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 1: $1= %d\n", $1  );
																$$ = buildLongIntegerLiteral( $1 );																
															}		 
					|	STRING_LITERAL						{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 2\n" );																
																$$ = buildStringLiteral( $1 ); 
															}
					|	CHARACTER_LITERAL					{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 3: $1= %c\n", $1  );
																$$ = buildCharLiteral( $1 ); 
															}		 
					|	FLOATING_PT_LITERAL					{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 4: $1= %f\n", $1  );
																$$ = buildDoubleLiteral( $1 ); 
															}		 
					|	boolean_literal						{	if( compiler_debug_state == DEBUG_ON )printf( "literal:case 5\n" );
																$$ = buildBooleanLiteral( $1 ); 
															}		 
;

boolean_literal:		xTRUE								{	if( compiler_debug_state == DEBUG_ON )printf( "boolean_literal:case 1\n" );	$$=$1; 	} 		 
					|	xFALSE								{	if( compiler_debug_state == DEBUG_ON )printf( "boolean_literal:case 2\n" );	$$=$1;	}		 	     				
;

positive_int_const:		const_exp							{	if( compiler_debug_state == DEBUG_ON )printf( "positive_int_const:case 1\n" );	$$=$1;	}		
;

type_dcl:				xTYPEDEF type_declarator			{	if( compiler_debug_state == DEBUG_ON )( "type_dcl:case 1\n" );		
																$$ = buildType_Dcl_Case1( $1, $2 );
															}		
					|	struct_type							{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 2\n" );	$$=$1;	}		
					|	union_type							{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 3\n" );	$$=$1;	}		
					|	enum_type							{	if( compiler_debug_state == DEBUG_ON )printf( "type_dcl:case 4\n" );	$$=$1;	}																						 
;		

type_declarator:		type_spec declarators				{	
/* Identical code to 'member' */								if( compiler_debug_state == DEBUG_ON )printf( "type_declarator:case 1\n" ); /*build object with declarators array.*/
																$$ = buildType_Declarator( $1, declarator_array, declarator_count );

																/* Handle reset details */
																reset_void_array( &declarator_array, &declarator_count, &declarator_array_limit );
															}
;

type_spec:				simple_type_spec					{	if( compiler_debug_state == DEBUG_ON )printf( "type_spec:case 1\n" );	$$=$1;	}					
					|	constr_type_spec					{	if( compiler_debug_state == DEBUG_ON )printf( "type_spec:case 2\n" );	$$=$1;	}
;

simple_type_spec:		base_type_spec		{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 1\n" );
												$$ = buildBase_Type_Spec( $1 );
											}
					|	template_type_spec	{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 2\n" );
												$$=$1;
											}
					|	scoped_name			{	if( compiler_debug_state == DEBUG_ON )printf( "simple_type_spec:case 3\n" );	
												$$ = Scoped_Name_buildHandler();
											}
;
																								   
base_type_spec: 		floating_pt_type	{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 1\n");
												$$=$1;
											}
					|	integer_type		{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 2\n" );
												$$=$1;		
											}
					|	char_type			{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 3\n" );
												$$=$1;
											}
					|	boolean_type		{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 4\n" );
												$$=$1;
											}
					|	octet_type			{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 5\n" );
												$$=$1;
											}
					|	any_type			{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 6\n" );
												$$=$1;
											}
											/* The following "Object" case does not actually appear in the	*/
											/* IDL specification, but there doesn't appear to be any other	*/
											/* handler for "Object". It will be handled as a basic type		*/
											/* until a better solution is found.							*/
					|	object_type			{	if( compiler_debug_state == DEBUG_ON )printf( "base_type_spec:case 7\n" );
												$$=$1;
											}
;

template_type_spec:		sequence_type		{	if( compiler_debug_state == DEBUG_ON )printf( "template_type_spec:case 1\n" );	$$=$1;	}
					|	string_type			{	if( compiler_debug_state == DEBUG_ON )printf( "template_type_spec:case 2\n" );	$$=$1;	}		
;

constr_type_spec:		struct_type			{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 1\n" );	$$=$1;	}
					|	union_type			{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 2\n" );	$$=$1;	}
					|	enum_type			{	if( compiler_debug_state == DEBUG_ON )printf( "constr_type_spec:case 3\n" );	$$=$1;	}
;

declarators:			aux_2					{	if( compiler_debug_state == DEBUG_ON )printf( "declarators:case 1\n" );	/*declarator_srray is fully loaded at this point*/ }
;

aux_2:					declarator				{	if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 1\n" );	$$=$1; load_declarator_array( $1 ); }
					|	aux_2 ',' declarator	{	if( compiler_debug_state == DEBUG_ON )printf( "aux_2: case 2\n" );	$$=$1; load_declarator_array( $3 ); }
;

declarator:				simple_declarator		{	if( compiler_debug_state == DEBUG_ON )printf( "declarator:case 1\n" );	$$=$1;	}
					|	complex_declarator		{	if( compiler_debug_state == DEBUG_ON )printf( "declarator:case 2\n" );	$$=$1;	}
;

simple_declarator:		xIDENTIFIER				{	if( compiler_debug_state == DEBUG_ON )printf( "simple_declarator:case 1\n" );
													$$ = buildSimple_Declarator( $1 );
												}
;

complex_declarator:		array_declarator		{	if( compiler_debug_state == DEBUG_ON )printf( "complex_declarator:case 1\n" );	$$=$1;	}
;

floating_pt_type:		xFLOAT				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xFLOAT\n" );	$$=$1;	}
					|	xDOUBLE				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xDOUBLE\n" );	$$=$1;	}
;

integer_type:			signed_int			{	if( compiler_debug_state == DEBUG_ON )printf( "integer_type:signed_int\n" );		$$=$1;	}
					|	unsigned_int		{	if( compiler_debug_state == DEBUG_ON )printf( "integer_type:unsigned_int\n" );	$$=$1;	}
;

signed_int:				signed_long_int		{	if( compiler_debug_state == DEBUG_ON )printf( "signed_int:signed_long_int\n" );	$$=$1;	}
					|	signed_short_int	{	if( compiler_debug_state == DEBUG_ON )printf( "signed_int:signed_short_int\n" );	$$=$1;	}
;													
signed_long_int:		xLONG				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xLONG\n" );		$$=$1;	}
;										

signed_short_int:		xSHORT				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xSHORT\n" );	$$=$1;	}
;

unsigned_int:			unsigned_long_int	{	if( compiler_debug_state == DEBUG_ON )printf( "unsigned_long_int:unsigned_long_int\n" );	$$=$1;	}
					|	unsigned_short_int	{	if( compiler_debug_state == DEBUG_ON )printf( "unsigned_short_int:unsigned_short_int\n" );	$$=$1;	}
;

unsigned_long_int:		xUNSIGNED xLONG		{	char	*u_long;
												u_long = (char *) malloc( 14 );
												strcpy( u_long, $1 );
												strcat( u_long, " " ); 
												strcat( u_long, $2 ); 
												$$ = u_long;
												if( compiler_debug_state == DEBUG_ON )printf( "Got: xUNSIGNED xLONG\n" );
											}
;

unsigned_short_int:		xUNSIGNED xSHORT	{	char	*u_short;
												u_short = (char *) malloc( 15 );
												strcpy( u_short, $1 );   
												strcat( u_short, " " ); 
												strcat( u_short, $2 ); 
												$$ = u_short;
												if( compiler_debug_state == DEBUG_ON )printf( "Got: xUNSIGNED xSHORT\n" );
											} 
;						

char_type:				xCHAR				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xCHAR\n" );	$$=$1;		}
;

boolean_type:			xBOOLEAN			{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xBOOLEAN\n" );$$=$1;	}
;

octet_type:				xOCTET				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xOCTET\n" );	$$=$1;		}
;

any_type:				xANY				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xANY\n" );	$$=$1;		}
;

/* object_type is an addendum to the OMG IDL specification, which apparently doesn't handle the "Object" case */
object_type:			xOBJECT				{	if( compiler_debug_state == DEBUG_ON )printf( "Got: xOBJECT\n" );	$$=$1;		}
;


struct_type:			xSTRUCT xIDENTIFIER '{' member_list '}'		{	
																		if( compiler_debug_state == DEBUG_ON )printf( "struct_type:Got: xSTRUCT: $1= %ld\n", $1 ); 
																		$$ = buildStruct_Type( $1, $2, member_array, member_count );

																		/* Handle reset details */
																		reset_void_array( &member_array, &member_count, &member_array_limit );
																	}
;

member_list:			member					{	if( compiler_debug_state == DEBUG_ON )printf( "member_list:case 1\n" );	$$=$1;	load_member_array( $1 );	}
					|	member_list member		{	if( compiler_debug_state == DEBUG_ON )printf( "member_list:case 2\n" );	$$=$2;	load_member_array( $2 );	}										
;


member:					type_spec declarators ';'		{	int i;
/* Identical code to 'type_declarator' */					if( compiler_debug_state == DEBUG_ON )printf( "member:case 1\n" );	/*build obj with declarators array*/ 
															$$ = buildMember( $1, declarator_array, declarator_count );

															/* Clear declarator_array and then clear declarator_count */
															for( i=0 ; i<attr_dcl_count ; i++ )
																declarator_array[i] = NULL;
																
															declarator_count = 0;
														}
;

union_type:				xUNION xIDENTIFIER xSWITCH '(' switch_type_spec ')' '{' switch_body '}'	
							{ 
							if( compiler_debug_state == DEBUG_ON )printf( "union_type: case 1\n" );
							
							$$ = buildUnion_Type( $1, $2, $3, $5, switch_body_array, switch_body_count );
							
							/* Handle reset details */
							reset_void_array( &switch_body_array, &switch_body_count, &switch_body_array_limit );	
							}
;

switch_type_spec:		integer_type			{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 1\n" ); 
													$$ = buildSwitch_Type_Spec1( $1 );
												}
					|	char_type				{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 2\n" ); 
													$$ = buildSwitch_Type_Spec1( $1 );					
												}	   
					|	boolean_type			{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 3\n" ); 
													$$ = buildSwitch_Type_Spec1( $1 );																	
												}
					|	enum_type				{	if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 5\n" );
													$$ = buildSwitch_Type_Spec2( $1 );													
												}
					|	scoped_name				{	void *ptr;
													if( compiler_debug_state == DEBUG_ON )printf( "switch_type_spec: case 6\n" ); 	/*scoped_name as a type??? */
													ptr = Scoped_Name_buildHandler();
													$$ = buildSwitch_Type_Spec2( ptr );
												}
;

switch_body:			case					{	if( compiler_debug_state == DEBUG_ON )printf( "switch_body: case 1\n" );	$$=0;	load_switch_body_array( $1 );	}
					|	switch_body case		{	if( compiler_debug_state == DEBUG_ON )printf( "switch_body: case 2\n" );	$$=0;	load_switch_body_array( $2 );	}
;

case:					aux_3 element_spec ';'		{	 
														if( compiler_debug_state == DEBUG_ON )printf( "case: case 1\n" ); /*case_label_array is fully loaded at this point*/
														$$ = buildCase( case_label_array, case_label_count, $2 );	
							
														/* Handle reset details */
														reset_void_array( &case_label_array, &case_label_count, &case_label_array_limit );	
													}
;

aux_3:					case_label					{	if( compiler_debug_state == DEBUG_ON )printf( "aux_3: case 1\n" ); $$=0; load_case_label_array( $1 ); }
					|	aux_3 case_label			{	if( compiler_debug_state == DEBUG_ON )printf( "aux_3: case 2\n" ); $$=0; load_case_label_array( $2 ); }
;

case_label:				xCASE const_exp ':'			{	if( compiler_debug_state == DEBUG_ON )printf( "case_label: case 1\n" ); 
														$$ = buildCase_Label( $1, $2 );
													}
					|	xDEFAULT ':'				{	if( compiler_debug_state == DEBUG_ON )printf( "case_label: case 2\n" );
														$$ = buildCase_Label( $1, NULL );
													}
;

element_spec:			type_spec declarator		{	if( compiler_debug_state == DEBUG_ON )printf( "element_spec: case 1\n" );
														$$ = buildElement_Spec( $1, $2 );
													}
;

enum_type:				xENUM xIDENTIFIER '{' aux_4 '}'			
							{
																					 
							if( compiler_debug_state == DEBUG_ON )printf( "enum_type: case 1\n" ); 
							
							$$ = buildEnum_Type( $1, $2, enumerator_array, enumerator_count );
														
							/* Handle reset details */
							reset_char_array( &enumerator_array, &enumerator_count, &enumerator_array_limit );
							}
;
																																			
aux_4:					enumerator					{	if( compiler_debug_state == DEBUG_ON )printf( "aux_4: case 1\n" ); $$=0; load_enumerator_array($1); }														
					|	aux_4 ',' enumerator		{	if( compiler_debug_state == DEBUG_ON )printf( "aux_4: case 2\n" ); $$=0; load_enumerator_array($3); }
;

enumerator:				xIDENTIFIER					{	if( compiler_debug_state == DEBUG_ON )printf( "enumerator: case 1:\n" );	$$=$1;		}
;

sequence_type:			xSEQUENCE '<' simple_type_spec ',' positive_int_const '>'	{	if( compiler_debug_state == DEBUG_ON )printf( "sequence_type: case 1\n" ); 
																						$$ = buildSequence_Type( $1, $3, $5 );
																					}
					|	xSEQUENCE '<' simple_type_spec '>'							{	if( compiler_debug_state == DEBUG_ON )printf( "sequence_type: case 2\n" ); 
																						$$ = buildSequence_Type( $1, $3, NULL );
																					}
;

string_type:			xSTRING '<' positive_int_const '>'	{	if( compiler_debug_state == DEBUG_ON )printf( "string_type:case 1\n" );	
																$$ = buildString_Type( $1, $3 );
															}		
					|	xSTRING								{	if( compiler_debug_state == DEBUG_ON )printf( "string_type:case 2\n" );
																$$ = buildString_Type( $1, NULL );															
															}		
;

array_declarator:		xIDENTIFIER aux_5		 			{	 
																if( compiler_debug_state == DEBUG_ON )printf( "array_declarator: case 1\n" ); 
																
																/*fixed_array_size_array is fully loaded at this point*/				
																$$ = buildArray_Declarator( $1, fixed_array_size_array, fixed_array_size_count );	

																/* Handle reset details */
																reset_void_array( &fixed_array_size_array, &fixed_array_size_count, &fixed_array_size_array_limit );									
															}
;
 
aux_5:					fixed_array_size					{	if( compiler_debug_state == DEBUG_ON )printf( "aux_5: case 1\n" ); $$=0; load_fixed_array_size_array( $1 );	}
					|	aux_5 fixed_array_size				{	if( compiler_debug_state == DEBUG_ON )printf( "aux_5: case 2\n" ); $$=0; load_fixed_array_size_array( $2 );	}
;

fixed_array_size:		'[' positive_int_const ']'			{	if( compiler_debug_state == DEBUG_ON )printf( "fixed_array_size: case 1\n" );	$$=$2; }
;
 

attr_dcl:				xATTRIBUTE param_type_spec aux_6			
							{
							
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl: case 1\n" );
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl_count= %d\n", attr_dcl_count );
							
							$$ = buildAttr_Dcl( NO_READONLY, $1, $2, attr_dcl_array, attr_dcl_count );
							
							/* Handle reset details */
							reset_void_array( &attr_dcl_array, &attr_dcl_count, &attr_dcl_array_limit );
							}					
					|	xREADONLY xATTRIBUTE param_type_spec aux_6	
							{ 
							
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl: case 3\n" );
							if( compiler_debug_state == DEBUG_ON )printf( "attr_dcl_count= %d\n", attr_dcl_count );
							
							$$ = buildAttr_Dcl( YES_READONLY, $2, $3, attr_dcl_array, attr_dcl_count );

							/* Handle reset details */
							reset_void_array( &attr_dcl_array, &attr_dcl_count, &attr_dcl_array_limit );
							}
;
 
aux_6:					simple_declarator				{	if( compiler_debug_state == DEBUG_ON )printf( "aux_6: case 1:\n" ); $$=$1; load_attr_dcl_array($1); }
					|	aux_6 ',' simple_declarator		{	if( compiler_debug_state == DEBUG_ON )printf( "aux_6: case 2:\n" ); $$=$1; load_attr_dcl_array($3); }
;

/**************TRY REPLACING aux_7 WITH member_list SINCE THEY ARE FUNCTIONALLY EQUIVALENT:
except_dcl:				xEXCEPTION xIDENTIFIER '{' '}'		{	if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 1\n" ); }
					|	xEXCEPTION xIDENTIFIER '{' aux_7 '}' {	if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 2\n" ); }
;

aux_7:					member								{	if( compiler_debug_state == DEBUG_ON )printf( "aux_7: case 1\n" ); }
					|	aux_7 member						{	if( compiler_debug_state == DEBUG_ON )printf( "aux_7: case 2\n" ); }
;
***************/
except_dcl:				xEXCEPTION xIDENTIFIER '{' '}'				{	if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 1\n" );
																		/* The member_array will have no members and the count 
																		 * wiil be 0. This will be handled by the constructor */ 
																		$$ = buildExcept_Dcl( $1, $2, member_array, member_count );
																	}
					|	xEXCEPTION xIDENTIFIER '{' member_list '}'	{	
																		if( compiler_debug_state == DEBUG_ON )printf( "except_dcl: case 2\n" );
																		$$ = buildExcept_Dcl( $1, $2, member_array, member_count );

																		/* Handle reset details */
																		reset_void_array( &member_array, &member_count, &member_array_limit );
																	}
;

op_dcl:					op_type_spec xIDENTIFIER parameter_dcls							
							{
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 1\n" );
							$$ = buildOp_Dcl( NO_OPATTRIBUTE, $1, $2, param_dcl_array, param_dcl_count, NULL, NULL );
														
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							}
														
					|	op_type_spec xIDENTIFIER parameter_dcls raises_expr					
							{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 2\n" ); 																		 
							$$ = buildOp_Dcl( NO_OPATTRIBUTE, $1, $2, param_dcl_array, param_dcl_count, $4, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							}
					|	op_type_spec xIDENTIFIER parameter_dcls context_expr				
							{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 3\n" );
							$$ = buildOp_Dcl( NO_OPATTRIBUTE, $1, $2, param_dcl_array, param_dcl_count, NULL, $4 );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							}
					|	op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr
							{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 4\n" ); 
							$$ = buildOp_Dcl( NO_OPATTRIBUTE, $1, $2, param_dcl_array, param_dcl_count, $4, $5 );
														
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit ); 
							}
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls				
							{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 5\n" ); 																		 
							$$ = buildOp_Dcl( YES_OPATTRIBUTE, $2, $3, param_dcl_array, param_dcl_count, NULL, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							}

					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr	
							{
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 5\n" ); 																		 
							$$ = buildOp_Dcl( YES_OPATTRIBUTE, $2, $3, param_dcl_array, param_dcl_count, $5, NULL );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							}							

					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls context_expr
							{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 7\n" ); 
							$$ = buildOp_Dcl( YES_OPATTRIBUTE, $2, $3, param_dcl_array, param_dcl_count, NULL, $5 );
							
							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );							
							}

					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr
							{ 
							if( compiler_debug_state == DEBUG_ON )printf( "op_dcl: case 8\n" ); 
							$$ = buildOp_Dcl( YES_OPATTRIBUTE, $2, $3, param_dcl_array, param_dcl_count, $5, $6 );

							/* Handle reset details */
							reset_void_array( &param_dcl_array, &param_dcl_count, &param_dcl_array_limit );
							}
;

op_attribute:			xONEWAY				{	if( compiler_debug_state == DEBUG_ON )printf( "op_attribute: case 1: Got xONEWAY:$1 = %d\n", $1 );	$$=$1; }
;

op_type_spec:			param_type_spec		{	if( compiler_debug_state == DEBUG_ON )printf( "op_type_spec: case 1:$1= %x\n", $1 );
												$$ = buildOp_Type_Spec1( $1 );
											}
					|	xVOID				{	if( compiler_debug_state == DEBUG_ON )printf( "op_type_spec: case 2\n" );
												$$ = buildOp_Type_Spec2( $1 );					
											}
;

parameter_dcls:			'(' aux_8 ')'					{	if( compiler_debug_state == DEBUG_ON )printf( "parameter_dcls: case 1\n" ); 
															/* For this case, we will let parent rule build an object. */
															$$ = NULL;
														}
					|	'(' ')'							{ 
															if( compiler_debug_state == DEBUG_ON )printf( "parameter_dcls: case 3\n" ); 
															/* Any rule using parameter_dcls will check the param_dcl count. */
															/* If it is 0, this is the case that matched. */
															$$ = NULL;
														}
;

/* SYNTACTIC MATCH ONLY RULE */
aux_8:					param_dcl							{	if( compiler_debug_state == DEBUG_ON )printf( "aux_8: case 1\n" ); $$=0;	}
					|	aux_8 ',' param_dcl					{	if( compiler_debug_state == DEBUG_ON )printf( "aux_8: case 2\n" ); $$=0;	}    
;

param_dcl:				param_attribute param_type_spec simple_declarator	
							{ 
							void	*ptr;
							if( compiler_debug_state == DEBUG_ON )printf( "param_dcl:$2= %x\t $3= %x\n", $2, $3 ); 

							ptr = buildParam_Dcl( $1, $2, $3 );

							/* Add this param_dcl object to the param_dcl object array */
							load_param_dcl_array( ptr );	

							/* The semantic value of each param_dcl is not used individually */
							$$ = NULL;
							}
;
															
param_attribute:		xIN									{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 1\n" );	$$=$1;		}
					|	xOUT								{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 2\n" );	$$=$1;		}
					|	xINOUT								{	if( compiler_debug_state == DEBUG_ON )printf( "param_attribute: case 3\n" );	$$=$1;		}
;

raises_expr:			xRAISES '(' aux_9 ')'				{	if( compiler_debug_state == DEBUG_ON )printf( "raises_expr: case 1\n" ); /*build obj with scoped_name array */
																$$ = buildRaises_Expr( scoped_name_array, scoped_name_count );

																/* Handle reset details */
																reset_void_array( &scoped_name_array, &scoped_name_count, &scoped_name_array_limit );
															}					
;

aux_9:					scoped_name							{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_9: case 1\n" ); 
																ptr = Scoped_Name_buildHandler();

																/* Add this scoped_name object to the scoped_name object array */
																load_scoped_name_array( ptr );	
																																														
																/* return type is not important here */
																$$=0;				
															}
					|	aux_9 ',' scoped_name				{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_9: case 2\n" ); 
																ptr = Scoped_Name_buildHandler();

																/* Add this scoped_name object to the scoped_name object array */
																load_scoped_name_array( ptr );	
																																														
																/* return type is not important here */
																$$=0;				
															}    
;

context_expr:			xCONTEXT '(' aux_10 ')'				{	if( compiler_debug_state == DEBUG_ON )printf( "context_expr: case 1\n" );
																$$ = buildContext_Expr( $1, string_literal_array, string_literal_count );
							
																/* Handle reset details */
																reset_void_array( &string_literal_array, &string_literal_count, &string_literal_array_limit );							
															}
;


aux_10:					STRING_LITERAL						{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_10: case 1\n" ); 
																$$ = 0;	/* value of aux_10 is not used */																
																ptr = buildStringLiteral( $1 );
																load_string_literal_array( ptr );	
															}

					|	aux_10 ',' STRING_LITERAL			{	void *ptr;
																if( compiler_debug_state == DEBUG_ON )printf( "aux_10: case 2\n" );
																$$ = 0;	/* value of aux_10 is not used */																
																ptr = buildStringLiteral( $3 );
																load_string_literal_array( ptr );	
															}
;


param_type_spec:		base_type_spec						{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 1\n" );		
																$$ = buildBase_Type_Spec( $1 );
															}
					|	string_type							{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 2\n" ); 
																$$=$1;
															}
					|	scoped_name							{	if( compiler_debug_state == DEBUG_ON )printf( "param_type_spec: case 3\n" ); 
																$$ = Scoped_Name_buildHandler();
															}
;

/* End of grammar */
%%
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