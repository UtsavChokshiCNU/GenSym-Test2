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

extern int yylex();


%}

/*
Bison declarations
The Bison declarations declare the names of the terminal and nonterminal symbols, and may also 
describe operator precedence and the data types of semantic values of various symbols.
*/
%union 
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
	}

%type	<tok_val>	floating_pt_type integer_type signed_int signed_long_int signed_short_int
%type	<tok_val>	unsigned_int unsigned_long_int unsigned_short_int base_type_spec simple_type_spec
%type	<tok_val>	template_type_spec sequence_type string_type positive_int_const const_exp or_expr
%type	<tok_val>	xor_expr and_expr shift_expr add_expr mult_expr unary_expr unary_operator 
%type	<tok_val>	primary_expr scoped_name literal boolean_literal definition type_dcl const_dcl
%type	<tok_val>	except_dcl interface module interface_dcl forward_dcl interface_header inheritance_spec
%type	<tok_val>	interface_body export attr_dcl op_dcl aux_1 
%type	<tok_val>	type_declarator struct_type union_type enum_type type_spec declarators constr_type_spec
%type	<tok_val>	declarator aux_2 simple_declarator complex_declarator array_declarator member_list
%type	<tok_val>	member switch_type_spec switch_body case case_label element_spec aux_3 aux_4 enumerator
%type	<tok_val>	fixed_array_size aux_5 aux_6 aux_7 op_attribute	op_type_spec parameter_dcls raises_expr
%type	<tok_val>	context_expr param_type_spec param_dcl aux_8 param_attribute aux_9 aux_10


 
%token	<tok_val>	xANY xATTRIBUTE xBOOLEAN xCASE xCHAR xCONST xCONTEXT xDEFAULT xDOUBLE xENUM xEXCEPTION 
%token  <tok_val>	xFALSE xFLOAT xIN xINOUT xINTERFACE xLONG xMODULE xOBJECT xOCTET xONEWAY xOUT xRAISES 
%token  <tok_val>	xREADONLY xSEQUENCE xSHORT xSTRING xSTRUCT xSWITCH xTRUE xTYPEDEF xUNSIGNED xUNION xVOID
%token	<tok_val>	OPERATOR PUNCTUATOR LITERAL IDENTIFIER KEYWORD
%token	<tok_val>	LITERAL_DECINT LITERAL_HEXINT LITERAL_OCTINT LITERAL_FP	LITERAL_CHAR LITERAL_CHARHEX 
%token	<tok_val>	LITERAL_CHAROCT LITERAL_STRING
%token	<tok_val>	DOUBLE_COLON DOUBLE_LT DOUBLE_GT
%token	<dbl_val>	FLOATING_PT_LITERAL
%token	<chr_val>	CHARACTER_LITERAL
%token	<str_lit>	STRING_LITERAL
%token	<lng_val>	INTEGER_LITERAL
%token	<str_lit>	xIDENTIFIER



%token	<str_lit>	VAR
%token	<dbl_val>	NUM

%right	'='
%left	'|'
%left	'^'
%left	'&'										/* Lowest precedence  */
%left	'-' '+'									/*			|		  */
%left	'*' '/' '%'									/*			|		  */
%left	NEG     /* Negation--unary minus */		/*			V		  */
												/* Highest precedence */

%start	specification			/* Explicitly name the start rule */

%%
/*
Grammar rules
The grammar rules define how to construct each nonterminal symbol from its parts. 
*/

/*
specification:			Empty						{ printf( "specification: Empty...\n" );	}
					|	definition					{ printf( "specification:case 1\n" );		}			
					|	specification definition	{ printf( "specification:case 2\n" );		}
					|	error						{ yyerrok;  								} 
;
*/

specification:			/* empty */					{ printf( "specification: Empty...\n" );	}
					|	specification definition	{ printf( "specification:case 1\n" );		}
					/*
					|	error						{ yyerrok;  								} 
					*/
;

definition:				type_dcl ';'				{ printf( "definition: case 1\n" ); }
					|	const_dcl ';'				{ printf( "definition: case 2\n" ); }
					|	except_dcl ';'				{ printf( "definition: case 3\n" ); }
					|	interface ';'				{ printf( "definition: case 4\n" ); }
					|	module ';'					{ printf( "definition: case 5\n" ); }
;

module:					xMODULE xIDENTIFIER '{' definition '}'	{ printf( "module: case 1\n" ); }
;

interface:				interface_dcl			{ printf( "interface: case 1\n" ); }
					|	forward_dcl				{ printf( "interface: case 2\n" ); }
;

interface_dcl:			interface_header '{' interface_body '}'		{ printf( "interface_dcl: case 1\n" ); }
;

forward_dcl:			xINTERFACE xIDENTIFIER						{ printf( "interface: case 1:xIDENTIFIER= %s\n", $2 ); }
;

interface_header:		xINTERFACE xIDENTIFIER						{ printf( "interface_header: case 1:xIDENTIFIER= %s\n", $2 ); }
					|	xINTERFACE xIDENTIFIER inheritance_spec		{ printf( "interface_header: case 2:xIDENTIFIER= %s\n", $2 ); }
;

interface_body:			/* Empty */						{ printf( "interface_body: case 1\n" ); }
					|	interface_body export			{ printf( "interface_body: case 2\n" ); }
;

export:					type_dcl ';'				{ printf( "export: case 1\n" ); }
					|	const_dcl ';'				{ printf( "export: case 2\n" ); }
					|	except_dcl ';'				{ printf( "export: case 3\n" ); }
					|	attr_dcl ';'				{ printf( "export: case 4\n" ); }
					|	op_dcl ';'					{ printf( "export: case 5\n" ); }
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
					|	enum_type							{ printf( "type_dcl:case 4\n" );	}
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

base_type_spec: 		floating_pt_type	{ printf( "base_type_spec:case 1\n" );	}
					|	integer_type		{ printf( "base_type_spec:case 2\n" );	}
					|	char_type			{ printf( "base_type_spec:case 3\n" );	}
					|	boolean_type		{ printf( "base_type_spec:case 4\n" );	}			   
					|	octet_type			{ printf( "base_type_spec:case 5\n" );	}
					|	any_type			{ printf( "base_type_spec:case 6\n" );	}
;

template_type_spec:		sequence_type		{ printf( "template_type_spec:case 1\n" );	}
					|	string_type			{ printf( "template_type_spec:case 2\n" );		}
;

constr_type_spec:		struct_type			{ printf( "constr_type_spec:case 1\n" );	}
					|	union_type			{ printf( "constr_type_spec:case 2\n" );	}
					|	enum_type			{ printf( "constr_type_spec:case 3\n" );	}
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

simple_declarator:		xIDENTIFIER				{ printf( "simple_declarator:case 1\n" );	}
;

complex_declarator:		array_declarator		{ printf( "complex_declarator:case 1\n" );	}
;

floating_pt_type:		xFLOAT				{ printf( "Got: xFLOAT: $1= %d\n", $1 );			}
					|	xDOUBLE				{ printf( "Got: xDOUBLE: $1= %d\n", $1 );			}
;

integer_type:			signed_int			{ printf( "integer_type:signed_int\n" );			}
					|	unsigned_int		{ printf( "integer_type:unsigned_int\n" );			}
;

signed_int:				signed_long_int		{ printf( "signed_int:signed_long_int\n" );			}
					|	signed_short_int	{ printf( "signed_int:signed_short_int\n" );		}
;

signed_long_int:		xLONG				{ printf( "Got: xLONG: $1= %ld\n", $1 );				}
;										

signed_short_int:		xSHORT				{ printf( "Got: xSHORT: $1= %ld\n", $1 );			}
;

unsigned_int:			unsigned_long_int	{ printf( "unsigned_long_int:unsigned_long_int\n" );	}
					|	unsigned_short_int	{ printf( "unsigned_short_int:unsigned_short_int\n" );	}
;

unsigned_long_int:		xUNSIGNED xLONG		{ printf( "Got: xUNSIGNED xLONG: $1= %ld\n", $1 );	}
;

unsigned_short_int:		xUNSIGNED xSHORT		{ printf( "Got: xUNSIGNED xSHORT: $1= %ld\n", $1 );	}
;

char_type:				xCHAR				{ printf( "Got: xCHAR: $1= %ld\n", $1 );	}
;

boolean_type:			xBOOLEAN				{ printf( "Got: xBOOLEAN: $1= %ld\n", $1 );	}
;

octet_type:				xOCTET				{ printf( "Got: xOCTET: $1= %ld\n", $1 );	}
;

any_type:				xANY					{ printf( "Got: xANY: $1= %ld\n", $1 );	}
;

struct_type:			xSTRUCT xIDENTIFIER '{' member_list '}'		{ printf( "struct_type:Got: xSTRUCT: $1= %ld\n", $1 );	}
;

member_list:			member					{ printf( "member_list:case 1\n" );	}										
					|	member_list member		{ printf( "member_list:case 2\n" );	}										
;

member:					type_spec declarators ';'		{ printf( "member:case 1\n" );	}
;

union_type:				xUNION xIDENTIFIER xSWITCH '(' switch_type_spec ')' '{' switch_body '}'
;

switch_type_spec:		integer_type			{ printf( "switch_type_spec: case 1\n" ); }
					|	char_type				{ printf( "switch_type_spec: case 2\n" ); }
					|	boolean_type			{ printf( "switch_type_spec: case 3\n" ); }
					|	enum_type				{ printf( "switch_type_spec: case 4\n" ); }
					|	scoped_name				{ printf( "switch_type_spec: case 5\n" ); }
;

switch_body:			case					{ printf( "switch_body: case 1\n" ); }
					|	switch_body case		{ printf( "switch_body: case 2\n" ); }
;

/*
case:					case_label element_spec ';'	{ printf( "case: case 1\n" ); }
					|	aux_3 element_spec ';'		{ printf( "case: case 2\n" ); }
;

aux_3:					case_label					{ printf( "aux_3: case 1\n" ); }
					|	aux_3 case_label			{ printf( "aux_3: case 2\n" ); }
;
*/
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

enum_type:				xENUM xIDENTIFIER '{' enumerator '}'			{ printf( "enum_type: case 1\n" ); }
					|	xENUM xIDENTIFIER '{' enumerator aux_4 '}'	{ printf( "enum_type: case 2\n" ); }
;

aux_4:					',' enumerator				{ printf( "aux_4: case 1\n" ); }
					|	aux_4 ',' enumerator		{ printf( "aux_4: case 2\n" ); }
;

enumerator:			xIDENTIFIER						{ printf( "enumerator: case 1\n" ); }
;

sequence_type:			xSEQUENCE '<' simple_type_spec ',' positive_int_const '>'	{ printf( "sequence_type: case 1\n" ); }
					|	xSEQUENCE '<' simple_type_spec '>'							{ printf( "sequence_type: case 2\n" ); }
;

string_type:			xSTRING '<' positive_int_const '>'	{ printf( "string_type:case 1\n" );	}		
					|	xSTRING								{ printf( "string_type:case 2\n" );	}		
;

/*
array_declarator:		xIDENTIFIER fixed_array_size			{ printf( "array_declarator: case 1\n" ); }
					|	xIDENTIFIER aux_5					{ printf( "array_declarator: case 2\n" ); }
;

aux_5:					fixed_array_size					{ printf( "aux_5: case 1\n" ); }
					|	aux_5 fixed_array_size				{ printf( "aux_5: case 2\n" ); }
*/

array_declarator:		xIDENTIFIER aux_5		 			{ printf( "array_declarator: case 1\n" ); }
;

aux_5:					fixed_array_size					{ printf( "aux_5: case 1\n" ); }
					|	aux_5 fixed_array_size				{ printf( "aux_5: case 2\n" ); }
;

fixed_array_size:		'[' positive_int_const ']'			{ printf( "fixed_array_size: case 1\n" ); }
;

attr_dcl:				xATTRIBUTE param_type_spec simple_declarator					{ printf( "attr_dcl: case 1\n" ); }
					|	xATTRIBUTE param_type_spec simple_declarator aux_6				{ printf( "attr_dcl: case 2\n" ); }
					|	xREADONLY xATTRIBUTE param_type_spec simple_declarator			{ printf( "attr_dcl: case 3\n" ); }
					|	xREADONLY xATTRIBUTE param_type_spec simple_declarator aux_6	{ printf( "attr_dcl: case 4\n" ); }
;

aux_6:					',' simple_declarator				{ printf( "aux_6: case 1\n" ); }
					|	aux_6 ',' simple_declarator			{ printf( "aux_6: case 2\n" ); }
;

except_dcl:				xEXCEPTION xIDENTIFIER '{' '}'		{ printf( "except_dcl: case 1\n" ); }
					|	xEXCEPTION xIDENTIFIER '{' aux_7 '}' { printf( "except_dcl: case 2\n" ); }
;

aux_7:					member								{ printf( "aux_7: case 1\n" ); }
					|	aux_7 member						{ printf( "aux_7: case 2\n" ); }
;

op_dcl:					op_type_spec xIDENTIFIER parameter_dcls							{ printf( "op_dcl: case 1\n" ); }
					|	op_type_spec xIDENTIFIER parameter_dcls raises_expr				{ printf( "op_dcl: case 2\n" ); }
					|	op_type_spec xIDENTIFIER parameter_dcls context_expr				{ printf( "op_dcl: case 3\n" ); }
					|	op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr	{ printf( "op_dcl: case 4\n" ); }
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls				{ printf( "op_dcl: case 5\n" ); }
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr	{ printf( "op_dcl: case 6\n" ); }
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls context_expr	{ printf( "op_dcl: case 7\n" ); }
					|	op_attribute op_type_spec xIDENTIFIER parameter_dcls raises_expr context_expr { printf( "op_dcl: case 8\n" ); }
;

op_attribute:			xONEWAY				{ printf( "op_attribute: case 1: Got xONEWAY:$1 = %d\n", $1 ); }
;

op_type_spec:			param_type_spec		{ printf( "op_type_spec: case 1\n" ); }
					|	xVOID				{ printf( "op_type_spec: case 2: Got xVOID:$1= %d\n", $1 ); }
;

parameter_dcls:			'(' param_dcl ')'					{ printf( "parameter_dcls: case 1\n" ); }
					|	'(' param_dcl aux_8')'				{ printf( "parameter_dcls: case 2\n" ); }
					|	'(' ')'								{ printf( "parameter_dcls: case 3\n" ); }
;

aux_8:					',' param_dcl						{ printf( "aux_8: case 1\n" ); }
					|	aux_8 ',' param_dcl					{ printf( "aux_8: case 2\n" ); }    
;

param_dcl:				param_attribute param_type_spec simple_declarator	{ printf( "param_dcl: case 1\n" ); }
;
															
param_attribute:		xIN									{ printf( "param_attribute: case 1: Got xIN:$1 = %ld\n", $1 ); }			
					|	xOUT								{ printf( "param_attribute: case 2: Got xOUT:$1 = %d\n", $1 ); }			
					|	xINOUT								{ printf( "param_attribute: case 3: Got xINOUT:$1 = %d\n", $1 ); }			 
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

param_type_spec:		base_type_spec						{ printf( "param_type_spec: case 1\n" ); }
					|	string_type							{ printf( "param_type_spec: case 2\n" ); }
					|	scoped_name							{ printf( "param_type_spec: case 3\n" ); }
;

/* End of grammar */
%%
/*
Additional C code
The additional C code can contain any C code you want to use. Often the definition of the lexical analyzer yylex goes here, plus
subroutines called by the actions in the grammar rules. In a simple program, all the rest of the program can go here. 
*/

/* Lexical analyzer returns a double floating point 
   number on the stack and the token NUM, or the ASCII
   character read if not a number.  Skips all blanks
   and tabs, returns 0 for EOF. */

/*
#include <stdio.h>
#include <ctype.h>
*/

yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("yerror(): %s\n", s);
}