
/* Bison grammar file. */

%{

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
extern void *buildParam_Type_Spec();
extern void *buildAttr_Dcl();
extern void *buildInterface_Body();
extern void addExport();
extern void *buildInterface_Header();
extern void *buildInterface_Dcl();
extern void *buildSpecification();
extern void addDefinition();
extern void loadParseTreeRoot();


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

/*****End: Global Data for use by the Production Rules*****/



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
	char			*interface_header[2];	/* Holds: xINTERFACE xIDENTIFIER */
	sAttributeNode	*sAttributeNode_ptr;
	sOperationNode	*sOperationNode_ptr;
	sEnumeratorNode	*sEnumeratorNode_ptr;
	nodeType2		*nodeType2_ptr;
	}

%type	<tok_val>	simple_type_spec
%type	<tok_val>	template_type_spec sequence_type string_type positive_int_const const_exp or_expr
%type	<tok_val>	xor_expr and_expr shift_expr add_expr mult_expr unary_expr unary_operator 
%type	<tok_val>	primary_expr scoped_name literal boolean_literal const_dcl
%type	<tok_val>	except_dcl module inheritance_spec
%type	<tok_val>	aux_1 
%type	<tok_val>	type_declarator struct_type union_type type_spec declarators constr_type_spec
%type	<tok_val>	declarator aux_2 complex_declarator array_declarator member_list
%type	<tok_val>	member switch_body case case_label element_spec aux_3 aux_4
%type	<tok_val>	fixed_array_size aux_5 aux_7 op_attribute parameter_dcls raises_expr
%type	<tok_val>	context_expr param_dcl aux_8 aux_9 aux_10

%type	<str_lit>	signed_short_int signed_long_int signed_int unsigned_int unsigned_long_int unsigned_short_int
%type	<str_lit>	integer_type floating_pt_type base_type_spec char_type boolean_type octet_type any_type 
%type	<str_lit>	switch_type_spec simple_declarator aux_6 op_type_spec param_attribute enumerator


%type	<void_ptr>	param_type_spec attr_dcl export interface_body interface_header interface_dcl forward_dcl
%type	<void_ptr>	interface definition specification


%type	<sOperationNode_ptr>	op_dcl
%type	<sEnumeratorNode_ptr>	enum_type
%type	<nodeType2_ptr>			type_dcl
 
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


/*
%token	<str_lit>	VAR
%token	<dbl_val>	NUM
&/

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

specification:			definition					{ printf( "specification:case 1\n" );		
													  printf( "$1= %x\n", $1 );
													  /* Create the specification object */
													  $$ = buildSpecification();
													  
													  /* Load the Builder object with this value for later use */
													  loadParseTreeRoot( $$ );

													  /* Add the first definition item to the specification */
													  addDefinition( $$, $1 );
									   				
													}
					|	specification definition	{ printf( "specification:case 2\n" );		}
					/*
					|	error						{ yyerrok;  								} 
					*/
;

definition:				type_dcl ';'				{ printf( "definition: case 1\n" ); }
					|	const_dcl ';'				{ printf( "definition: case 2\n" ); }
					|	except_dcl ';'				{ printf( "definition: case 3\n" ); }
					|	interface ';'				{ printf( "definition: case 4\n" ); $$=$1;	}
					|	module ';'					{ printf( "definition: case 5\n" ); }
;

module:					xMODULE xIDENTIFIER '{' definition '}'	{ printf( "module: case 1\n" ); }
;

interface:				interface_dcl			{ printf( "interface: case 1\n" ); $$=$1;	}
					|	forward_dcl				{ printf( "interface: case 2\n" ); $$=$1;	}
;

interface_dcl:			interface_header '{' interface_body '}'		
							{ 	
							int i;
							printf( "interface_dcl: case 1\n" ); 
							$$ = buildInterface_Dcl( $1, $3 );
							}
;

forward_dcl:			xINTERFACE xIDENTIFIER						{ printf( "interface: case 1:xIDENTIFIER= %s\n", $2 ); }
;

interface_header:		xINTERFACE xIDENTIFIER						{ printf( "interface_header: case 1:xIDENTIFIER= %s\n", $2 ); 
																	  $$ = buildInterface_Header( $1, $2, NULL );
																	}
					|	xINTERFACE xIDENTIFIER inheritance_spec		{ printf( "interface_header: case 2:xIDENTIFIER= %s\n", $2 ); 
																	  $$ = buildInterface_Header( $1, $2, $3 );
																	}
;

interface_body:			 /* Empty */					{ printf( "interface_body: case 1\n" ); $$=NULL; /*Flag to show no interface_body has been built*/ }
					|	interface_body export			{ void	*ptr;
														  printf( "interface_body: case 2\n" ); 
														  printf( "$1= %x\t $2= %x\n", $1, $2 );
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


export:					type_dcl ';'				{	export_dcl_type_node	*ptr;
														printf( "export: case 1\n" );
														ptr = (export_dcl_type_node *) malloc( sizeof(export_dcl_type_node) );
														ptr->dcl_type = TYPE_DCL;
														ptr->nodePtr.nodeType2_ptr = $1;
													   	export_array[export_count] = ptr;
														export_count++;
													}
					|	const_dcl ';'				{ printf( "export: case 2\n" ); }
					|	except_dcl ';'				{ printf( "export: case 3\n" ); }
					|	attr_dcl ';'				{	
														printf( "export: sexy case 4\n" );
														$$ = $1;	
													}							 
					|	op_dcl ';'					{	export_dcl_type_node	*ptr;
														printf( "export: case 5: op_dcl:\n" ); 
														ptr = (export_dcl_type_node *) malloc( sizeof(export_dcl_type_node) );
														ptr->dcl_type = OP_DCL;
														ptr->nodePtr.sOperationNode_ptr = $1;
													   	export_array[export_count] = ptr;
														export_count++;		
													}
;					 

inheritance_spec:		':' scoped_name 				{ printf( "inheritance_spec: case 1\n" ); }
					|	':' scoped_name aux_1 			{ printf( "inheritance_spec: case 2\n" ); }
;

aux_1:					',' scoped_name					{ printf( "aux_1: case 1\n" ); }
					|	aux_1 ',' scoped_name			{ printf( "aux_1: case 2\n" ); }
;

scoped_name:			xIDENTIFIER								{ printf( "scoped_name: case 1\n" ); }
					|	DOUBLE_COLON xIDENTIFIER				{ printf( "scoped_name: case 2\n" ); }
					|	scoped_name DOUBLE_COLON xIDENTIFIER	{ printf( "scoped_name: case 3\n" ); }
;

const_dcl:				xCONST const_type xIDENTIFIER '=' const_exp	{ printf( "const_dcl: case 1\n" ); }
;

const_type:				integer_type			{ printf( "const_type: case 1\n" ); }
					|	char_type				{ printf( "const_type: case 2\n" ); }
					|	boolean_type			{ printf( "const_type: case 3\n" ); }
					|	floating_pt_type		{ printf( "const_type: case 4\n" ); }
					|	string_type				{ printf( "const_type: case 5\n" ); }
					|	scoped_name				{ printf( "const_type: case 6\n" ); }
;

const_exp:				or_expr								{ printf( "const_exp:case 1\n" );	}		
;

or_expr:				xor_expr							{ printf( "or_expr:case 1\n" );	}		
					|	or_expr '|' xor_expr				{ printf( "or_expr:case 2\n" );	}		
;

xor_expr:				and_expr							{ printf( "xor_expr:case 1\n" );	}		
					|	xor_expr '^' and_expr				{ printf( "xor_expr:case 2\n" );	}		
;

and_expr:				shift_expr							{ printf( "and_expr:case 1\n" );	}		
					|	and_expr '&' shift_expr				{ printf( "and_expr:case 2\n" );	}		
;

shift_expr:				add_expr					 		{ printf( "shift_expr:case 1\n" );	}		
					|	shift_expr DOUBLE_GT add_expr		{ printf( "shift_expr:case 2\n" );	}		
					|	shift_expr DOUBLE_LT add_expr		{ printf( "shift_expr:case 3\n" );	}		
;

add_expr:				mult_expr					 		{ printf( "add_expr:case 1\n" );	}		
					|	add_expr '+' mult_expr				{ printf( "add_expr:case 2\n" );	}		
					|	add_expr '-' mult_expr				{ printf( "add_expr:case 3\n" );	}		
;

mult_expr:				unary_expr					 		{ printf( "mult_expr:case 1\n" );	}		
					|	mult_expr '*' unary_expr			{ printf( "mult_expr:case 2\n" );	}		
					|	mult_expr '/' unary_expr			{ printf( "mult_expr:case 3\n" );	}		
					|	mult_expr '%' unary_expr			{ printf( "mult_expr:case 4\n" );	}		
;

unary_expr:				unary_operator primary_expr			{ printf( "unary_expr:case 1\n" );	}		
					|	primary_expr						{ printf( "unary_expr:case 2\n" );	}
;

unary_operator:			'-'									{ printf( "unary_operator:case 1\n" );	}		
					|	'+'         						{ printf( "unary_operator:case 2\n" );	}
					|	'~'         						{ printf( "unary_operator:case 3\n" );	}
;

primary_expr:			scoped_name							{ printf( "primary_expr:case 1\n" );	}		
					|	literal								{ printf( "primary_expr:case 2\n" );	}		
					|	'(' const_exp ')'					{ printf( "primary_expr:case 3\n" );	}		
;

literal:				INTEGER_LITERAL						{ printf( "literal:case 1\n" );			}		 
					|	STRING_LITERAL						{ printf( "literal:case 2\n" );			}		 
					|	CHARACTER_LITERAL					{ printf( "literal:case 3\n" );			}		 
					|	FLOATING_PT_LITERAL					{ printf( "literal:case 4\n" );			}		 
					|	boolean_literal						{ printf( "literal:case 5\n" );			}		 
;

boolean_literal:		xTRUE								{ printf( "boolean_literal:case 1\n" );	}		 
					|	xFALSE								{ printf( "boolean_literal:case 2\n" );	}		 					
;

positive_int_const:		const_exp							{ printf( "positive_int_const:case 1\n" );	}		
;

type_dcl:				xTYPEDEF type_declarator			{ printf( "type_dcl:case 1\n" );	}		
					|	struct_type							{ printf( "type_dcl:case 2\n" );	}		
					|	union_type							{ printf( "type_dcl:case 3\n" );	}		
					|	enum_type							{	nodeType2	*ptr;
																printf( "type_dcl:case 4:ptr= %x\n", $1 );			
																ptr = (nodeType2 *) malloc( sizeof(nodeType2) );
																ptr->data_type = ENUM_TYPE;
																ptr->u2Ptr.sEnumeratorNode_ptr = $1;
													   			type_dcl_array[type_dcl_count] = ptr;
																type_dcl_count++;
																$$ = ptr;		
															}							 
;		

type_declarator:		type_spec declarators				{ printf( "type_declarator:case 1\n" );	}					
;

type_spec:				simple_type_spec					{ printf( "type_spec:case 1\n" );	}					
					|	constr_type_spec					{ printf( "type_spec:case 2\n" );	}					
;

simple_type_spec:		base_type_spec		{ printf( "simple_type_spec:case 1\n" );	}
					|	template_type_spec	{ printf( "simple_type_spec:case 2\n" );	}
					|	scoped_name			{ printf( "simple_type_spec:case 3\n" );	}
;

base_type_spec: 		floating_pt_type	{ printf( "base_type_spec:case 1:$1= %s\n", $1 );		$$=$1;		}
					|	integer_type		{ printf( "base_type_spec:case 2:$1= %s\n", $1 );		$$=$1;		}
					|	char_type			{ printf( "base_type_spec:case 3:$1= %s\n", $1 );		$$=$1;		}
					|	boolean_type		{ printf( "base_type_spec:case 4:$1= %s\n", $1 );		$$=$1;		}
					|	octet_type			{ printf( "base_type_spec:case 5:$1= %s\n", $1 );		$$=$1;		}
					|	any_type			{ printf( "base_type_spec:case 6:$1= %s\n", $1 );		$$=$1;		}
;

template_type_spec:		sequence_type		{ printf( "template_type_spec:case 1\n" );	}
					|	string_type			{ printf( "template_type_spec:case 2\n" );		}
;

constr_type_spec:		struct_type			{ printf( "constr_type_spec:case 1\n" );	}
					|	union_type			{ printf( "constr_type_spec:case 2\n" );	}
					|	enum_type			{ printf( "constr_type_spec:case 3:$1= %x\n", $1 );	$$=$1;		}
;

declarators:			declarator			{ printf( "declarators:case 1\n" );	}
					|	declarator aux_2	{ printf( "declarators:case 2\n" );	}
;


aux_2:					',' declarator			{ printf( "aux_2: case 1\n" ); }
					|	aux_2 ',' declarator	{ printf( "aux_2: case 2\n" ); }
;

declarator:				simple_declarator		{ printf( "declarator:case 1\n" );	}
					|	complex_declarator		{ printf( "declarator:case 2\n" );	}
;

simple_declarator:		xIDENTIFIER				{ printf( "simple_declarator:case 1:$1= %s\n", $1 );		$$=$1;		}
;

complex_declarator:		array_declarator		{ printf( "complex_declarator:case 1\n" );	}
;

floating_pt_type:		xFLOAT				{ printf( "Got: xFLOAT:$1= %s\n", $1 );		$$=$1;		}
					|	xDOUBLE				{ printf( "Got: xDOUBLE:$1= %s\n", $1 );	$$=$1;		}
;

integer_type:			signed_int			{ printf( "integer_type:signed_int:$1= %s\n", $1 );		$$=$1;		}
					|	unsigned_int		{ printf( "integer_type:unsigned_int:$1= %s\n", $1 );		$$=$1;		}
;

signed_int:			signed_long_int		{ printf( "signed_int:signed_long_int:$1= %s\n", $1 );	$$=$1;		}
					|	signed_short_int	{ printf( "signed_int:signed_short_int:$1= %s\n", $1 );	$$=$1;		}
;

signed_long_int:		xLONG				{ printf( "Got: xLONG: $1= %s\n", $1 );		$$=$1;		}
;										

signed_short_int:		xSHORT				{ printf( "Got: xSHORT: $1= %s\n", $1 );	$$=$1;		}
;

unsigned_int:			unsigned_long_int	{ printf( "unsigned_long_int:unsigned_long_int:$1= %s\n", $1 );	$$=$1;		}
					|	unsigned_short_int	{ printf( "unsigned_short_int:unsigned_short_int:$1= %s\n", $1 );	$$=$1;		}
;

unsigned_long_int:		xUNSIGNED xLONG		{ strcat( $1, " " ); strcat( $1, $2 ); $$=$1; printf( "Got: xUNSIGNED xLONG:$1= %s, $2= %s, $$= %>>s<<\n", $1, $2, $$ ); }
;

unsigned_short_int:	xUNSIGNED xSHORT	{ strcat( $1, " " ); strcat( $1, $2 ); $$=$1; printf( "Got: xUNSIGNED xSHORT:$1= %s, $2= %s, $$= %>>s<<\n", $1, $2, $$ ); }
;						

char_type:				xCHAR				{ printf( "Got: xCHAR: $1= %s\n", $1 );	$$=$1;		}
;

boolean_type:			xBOOLEAN				{ printf( "Got: xBOOLEAN: $1= %s\n", $1 );	$$=$1;		}
;

octet_type:				xOCTET				{ printf( "Got: xOCTET: $1= %s\n", $1 );	$$=$1;		}
;

any_type:				xANY					{ printf( "Got: xANY: $1= %s\n", $1 );	$$=$1;		}
;

struct_type:			xSTRUCT xIDENTIFIER '{' member_list '}'		{ printf( "struct_type:Got: xSTRUCT: $1= %ld\n", $1 );	}
;

member_list:			member					{ printf( "member_list:case 1\n" );	}										
					|	member_list member		{ printf( "member_list:case 2\n" );	}										
;

member:					type_spec declarators ';'		{ printf( "member:case 1\n" );	}
;

union_type:				xUNION xIDENTIFIER xSWITCH '(' switch_type_spec ')' '{' switch_body '}'	{ printf( "%s\n", "fucking union_type!" ); }
;

switch_type_spec:		integer_type			{ printf( "switch_type_spec: case 1:$1= %s\n", $1 );		$$=$1;		}
					|	char_type				{ printf( "switch_type_spec: case 2:$1= %s\n", $1 );		$$=$1;		}
					|	boolean_type			{ printf( "switch_type_spec: case 3:$1= %s\n", $1 );		$$=$1;		}
					|	enum_type				{ printf( "switch_type_spec: case 4:$1= %x\n", $1 );	$$=$1;		}
					|	scoped_name				{ printf( "switch_type_spec: case 5\n" ); }
;

switch_body:			case					{ printf( "switch_body: case 1\n" ); }
					|	switch_body case		{ printf( "switch_body: case 2\n" ); }
;

case:					aux_3 element_spec ';'		{ printf( "case: case 1\n" ); }
;

aux_3:					case_label					{ printf( "aux_3: case 1\n" ); }
					|	aux_3 case_label			{ printf( "aux_3: case 2\n" ); }
;

case_label:				xCASE const_exp ':'			{ printf( "case_label: case 1\n" ); }
					|	xDEFAULT ':'				{ printf( "case_label: case 2\n" ); }
;

element_spec:			type_spec declarator		{ printf( "element_spec: case 1\n" ); }
;

enum_type:				xENUM xIDENTIFIER '{' aux_4 '}'			
							{
							int i=0;
														 
							printf( "enum_type: case 1\n" ); 
							for( i=0 ; i<enumerator_count ; i++ )
								printf( "enumerator_array[%d]= %s\n", i, enumerator_array[i] );
							$$ = buildEnumerator( $1, $2, enumerator_array, enumerator_count );
							/* Clear enumerator_array and then clear enumerator_count */
							for( i=0 ; i<enumerator_count ; i++ )
								enumerator_array[i] = NULL;
														  
							enumerator_count = 0;
							}
;

aux_4:					enumerator					{ printf( "aux_4: case 1:$1 %s\n", $1 ); $$=$1; loadenumerator_array($1); }
					|	aux_4 ',' enumerator		{ printf( "aux_4: case 2:$1= %s, $3= %s\n", $1, $3); $$=$1; loadenumerator_array($3); }
;

enumerator:				xIDENTIFIER					{ printf( "enumerator: case 1:$1= %s\n", $1 );	$$=$1;		}
;

sequence_type:			xSEQUENCE '<' simple_type_spec ',' positive_int_const '>'	{ printf( "sequence_type: case 1\n" ); }
					|	xSEQUENCE '<' simple_type_spec '>'							{ printf( "sequence_type: case 2\n" ); }
;

string_type:			xSTRING '<' positive_int_const '>'	{ printf( "string_type:case 1\n" );	}		
					|	xSTRING								{ printf( "string_type:case 2\n" );	}		
;

array_declarator:		xIDENTIFIER aux_5		 			{ printf( "array_declarator: case 1\n" ); }
;

aux_5:					fixed_array_size					{ printf( "aux_5: case 1\n" ); }
					|	aux_5 fixed_array_size				{ printf( "aux_5: case 2\n" ); }
;

fixed_array_size:		'[' positive_int_const ']'			{ printf( "fixed_array_size: case 1\n" ); }
;
 
/****SINCE FOLLOWING TWO CASES ARE SO SIMILAR, MAYBE MOVE FUNCTIONALITY TO A SEPARATE FUNCTION****/
attr_dcl:				xATTRIBUTE param_type_spec aux_6			
							{
							int i=0; 
							printf( "attr_dcl: case 1:$1= %s, $2= %x, $3= %s\n", $1, $2, $3 );
							printf( "attr_dcl_count= %d\n", attr_dcl_count );
							for( i=0 ; i<attr_dcl_count ; i++ )
								printf( "attr_dcl_array[%d]= %s\n", i, attr_dcl_array[i] );
							$$ = buildAttr_Dcl( NO_READONLY, $1, $2, attr_dcl_array, attr_dcl_count );
							/* Clear attr_dcl_array and then clear attr_dcl_count */
							for( i=0 ; i<attr_dcl_count ; i++ )
								attr_dcl_array[i] = NULL;
														  
							attr_dcl_count = 0;
							}					
					|	xREADONLY xATTRIBUTE param_type_spec aux_6	
							{ 
							int i=0;
							printf( "attr_dcl: case 3\n" );
							printf( "attr_dcl_count= %d\n", attr_dcl_count );
							for( i=0 ; i<attr_dcl_count ; i++ )
								printf( "attr_dcl_array[%d]= %s\n", i, attr_dcl_array[i] );
							$$ = buildAttribute( YES_READONLY, $2, $3, attr_dcl_array, attr_dcl_count );
							/* Clear attr_dcl_array and then clear attr_dcl_count */
							for( i=0 ; i<attr_dcl_count ; i++ )
								attr_dcl_array[i] = NULL;
														  
							attr_dcl_count = 0;
							}
;
 
aux_6:					simple_declarator				{ printf( "aux_6: case 1:$1 %s\n", $1 ); $$=$1; loadattr_dcl_array($1); }
					|	aux_6 ',' simple_declarator		{ printf( "aux_6: case 2:$1= %s, $3= %s\n", $1, $3); $$=$1; loadattr_dcl_array($3); }
;

except_dcl:				xEXCEPTION xIDENTIFIER '{' '}'		{ printf( "except_dcl: case 1\n" ); }
					|	xEXCEPTION xIDENTIFIER '{' aux_7 '}' { printf( "except_dcl: case 2\n" ); }
;

aux_7:					member								{ printf( "aux_7: case 1\n" ); }
					|	aux_7 member						{ printf( "aux_7: case 2\n" ); }
;

op_dcl:					op_type_spec xIDENTIFIER parameter_dcls							
							{
							int i=0;
							printf( "op_dcl: case 1:$1= %s\t $2= %s\t %3= %x\n", $1, $2, $3 ); 																		 
							$$ = buildOperation( NO_OPATTRIBUTE, $1, $2, param_dcl_array, param_dcl_count );
							
							/* Clear param_dcl_array and then clear param_dcl_count */
							for( i=0 ; i<param_dcl_count ; i++ )
								{
								free( param_dcl_array[i] );		/* free() what was allocated in param_dcl */
								param_dcl_array[i] = NULL;
								}
														  
							param_dcl_count = 0;
							}
							
					
					/* HANDLE THE FOLLOWING CASES WITH SEPARATE BUILD FUNCTIONS?? */		
					|	op_type_spec xIDENTIFIER parameter_dcls raises_expr				{ printf( "op_dcl: case 2\n" ); }
					|	op_type_spec xIDENTIFIER parameter_dcls context_expr				{ printf( "op_dcl: case 3\n" ); }
					|	op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr	{ printf( "op_dcl: case 4\n" ); }
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls				
							{ 
							int i=0;
							printf( "op_dcl: case 5:$1= %s\t $2= %s\t %3= %x\n", $1, $2, $3 ); 																		 
							$$ = buildOperation( YES_OPATTRIBUTE, $2, $3, param_dcl_array, param_dcl_count );
							
							/* Clear param_dcl_array and then clear param_dcl_count */
							for( i=0 ; i<param_dcl_count ; i++ )
								{
								free( param_dcl_array[i] );		/* free() what was allocated in param_dcl */
								param_dcl_array[i] = NULL;
								}
														  
							param_dcl_count = 0;							
							}

					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr	{ printf( "op_dcl: case 6\n" ); }
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls context_expr	{ printf( "op_dcl: case 7\n" ); }
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr { printf( "op_dcl: case 8\n" ); }
;

op_attribute:			xONEWAY				{ printf( "op_attribute: case 1: Got xONEWAY:$1 = %d\n", $1 ); }
;

op_type_spec:			param_type_spec		{ printf( "op_type_spec: case 1:$1= %s\n", $1 );	$$=$1;		}
					|	xVOID				{ printf( "op_type_spec: case 2:$1= %s\n", $1 );	$$=$1;		}
;

/******
parameter_dcls:			'(' param_dcl ')'					{ printf( "parameter_dcls: case 1\n" ); }
					|	'(' param_dcl aux_8')'				{ printf( "parameter_dcls: case 2\n" ); }
					|	'(' ')'								{ printf( "parameter_dcls: case 3\n" ); }
;

aux_8:					',' param_dcl						{ printf( "aux_8: case 1\n" ); }
					|	aux_8 ',' param_dcl					{ printf( "aux_8: case 2\n" ); }    
;
*******/
parameter_dcls:			'(' aux_8 ')'					{ printf( "parameter_dcls: case 1\n" ); }
					|	'(' ')'							{ printf( "parameter_dcls: case 3\n" ); }
;

aux_8:					param_dcl							{ printf( "aux_8: case 1\n" ); }
					|	aux_8 ',' param_dcl					{ printf( "aux_8: case 2\n" ); }    
;

param_dcl:				param_attribute param_type_spec simple_declarator	
							{ 
							param_dcl_struct	*ptr;
							ptr = (param_dcl_struct *) malloc( sizeof(param_dcl_struct) );
							printf( "param_dcl: $1= %s\t $2= %s\t $3= %s\n", $1, $2, $3 ); 

							/* Load the struct */
							strcpy( ptr->p1, $1 );
							strcpy( ptr->p2, $2 );
							strcpy( ptr->p3, $3 );

							/* Place the struct in the param_dcl array */
							param_dcl_array[param_dcl_count] = ptr;

							/* Increment the param_dcl_array counter */
							param_dcl_count++;
							}
;
															
param_attribute:		xIN									{ printf( "param_attribute: case 1:$1= %s\n", $1 );	$$=$1;		}
					|	xOUT								{ printf( "param_attribute: case 2:$1= %s\n", $1 );	$$=$1;		}			
					|	xINOUT								{ printf( "param_attribute: case 3:$1= %s\n", $1 );	$$=$1;		}
;

raises_expr:			xRAISES '(' scoped_name ')'			{ printf( "raises_expr: case 1\n" ); }
					|	xRAISES '(' scoped_name aux_9 ')'	{ printf( "raises_expr: case 2\n" ); }
;

aux_9:					',' scoped_name						{ printf( "aux_9: case 1\n" ); }
					|	aux_9 ',' scoped_name				{ printf( "aux_9: case 2\n" ); }    
;

context_expr:			xCONTEXT '(' STRING_LITERAL ')'			{ printf( "context_expr: case 1\n" ); }
					|	xCONTEXT '(' STRING_LITERAL aux_10 ')'	{ printf( "context_expr: case 2\n" ); }
;

aux_10:					',' STRING_LITERAL					{ printf( "aux_10: case 1\n" ); }
					|	aux_10 ',' STRING_LITERAL			{ printf( "aux_10: case 2\n" ); }    
;

param_type_spec:		base_type_spec						{	printf( "param_type_spec: case 1:$1= %s\n", $1 );		
																$$ = buildParam_Type_Spec( (void *) $1, 1000 );
															}
					|	string_type							{ printf( "param_type_spec: case 2\n" ); }
					|	scoped_name							{ printf( "param_type_spec: case 3\n" ); }
;

/* End of grammar */
%%
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