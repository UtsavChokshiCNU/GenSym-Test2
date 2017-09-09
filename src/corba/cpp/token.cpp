/*
 * Token Class - Base class for various types of tokens.
 *
 * The declarations for the classes implemented here are in token_dcl.h.
 *
 * This is the Token class. Token represents a single token as determined by the 
 * LexicalAnalyzer. All data fields in Token are loaded via the constructor.
 * The access functions are therefore all of type 'get', except for the 'set next'
 * function.
 */

#include <stdio.h>
#include <iostream_ver.h>
//#include <fstream_ver.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "code_tokens.h"
#include "corba_main.h"

extern "C"
{
#include "yacc_supp.h"
#include "ytab.h"
}

#include "parse_dcl.h"
#include "token_dcl.h"


//**************************Class: Token***************************
/*
 * Token - Constructor     
 */
Token::Token( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, 
			 char *filename)
{    
	//Allocate storage for the token string and load token_string:
	this->token_string = new char[strlen(string_arg)+1]; 
	strcpy( this->token_string, string_arg );

	// And store the file name
	this->filename = new char[strlen(filename)+1];
	strcpy( this->filename, filename);

	this->token_type = type_arg;	
	this->line_num = line_num_arg;
	this->object_index = object_index_arg;
	this->next = 0;	//NULL
	
	//Initialize character buffer, cbuf to all null characters:
	//memset( cbuf, '\0', 63 );

}


/*
 * Token - Destructor
 */
Token::~Token()
{                   
	//cout << "Inside Token Destructor" << endl;

	if( compiler_debug_state == DEBUG_ON )cout << "Deleting Token #" << this->object_index << "..." << endl;

	//Free allocated resources and perform general clean-up:
	delete this->token_string;
	delete this->filename;

	
	return;
}


/*
 * getKeywordType()
 * 
 * For a given keyword passed in, return the appropriate keyword symbol (token type).
 */
int Token::getKeywordType( char *arg ) 
{
	
	//Return appropriate code for the keyword. We know arg is a keyword since it has been 
	//checked previously:
	if( !strcmp( arg, "any" ) )
		return( xANY );
	else if( !strcmp( arg, "attribute" ) )
		return( xATTRIBUTE );
	else if( !strcmp( arg, "boolean" ) )
		return( xBOOLEAN );
   	else if( !strcmp( arg, "case" ) )
		return( xCASE );
	else if( !strcmp( arg, "char" ) )
		return( xCHAR );
	else if( !strcmp( arg, "const" ) )
		return( xCONST );
	else if( !strcmp( arg, "context" ) )
		return( xCONTEXT );
	else if( !strcmp( arg, "default" ) )
		return( xDEFAULT );
	else if( !strcmp( arg, "double" ) )
		return( xDOUBLE );
	else if( !strcmp( arg, "enum" ) )
		return( xENUM );
	else if( !strcmp( arg, "exception" ) )
		return( xEXCEPTION );
	else if( !strcmp( arg, "FALSE" ) )
		return( xFALSE );
	else if( !strcmp( arg, "float" ) )
		return( xFLOAT );
	else if( !strcmp( arg, "in" ) )
		return( xIN );
	else if( !strcmp( arg, "inout" ) )
		return( xINOUT );
	else if( !strcmp( arg, "interface" ) )
		return( xINTERFACE );
	else if( !strcmp( arg, "long" ) )
		return( xLONG );
	else if( !strcmp( arg, "module" ) )
		return( xMODULE );
	else if( !strcmp( arg, "Object" ) )
		return( xOBJECT );
	else if( !strcmp( arg, "octet" ) )
		return( xOCTET );
	else if( !strcmp( arg, "oneway" ) )
		return( xONEWAY );
	else if( !strcmp( arg, "out" ) )
		return( xOUT );
	else if( !strcmp( arg, "raises" ) )
		return( xRAISES );
	else if( !strcmp( arg, "readonly" ) )
		return( xREADONLY );
	else if( !strcmp( arg, "sequence" ) )
		return( xSEQUENCE );
	else if( !strcmp( arg, "short" ) )
		return( xSHORT );
	else if( !strcmp( arg, "string" ) )
		return( xSTRING );
	else if( !strcmp( arg, "struct" ) )
		return( xSTRUCT );
	else if( !strcmp( arg, "switch" ) )
		return( xSWITCH );
	else if( !strcmp( arg, "TRUE" ) )
		return( xTRUE );
	else if( !strcmp( arg, "typedef" ) )
		return( xTYPEDEF );
	else if( !strcmp( arg, "unsigned" ) )
		return( xUNSIGNED );
	else if( !strcmp( arg, "union" ) )
		return( xUNION );
	else if( !strcmp( arg, "void" ) )
		return( xVOID );
	else
		cout << "getKeywordType(): Invalid keyword was passed in here." << endl;


	return( -1 );
}


/*
 * set_next()
 * 
 * post-conditions: The 'next' pointer of this Token was set.
 */
void Token::set_next( Token *ptr_arg ) 
{

	this->next = ptr_arg;

	return;

}


/*
 * get_next()
 * 
 * post-conditions: A pointer to the 'next' Token was returned.
 */
Token* Token::get_next() 
{

	return( this->next );

}


/*
 * get_token_string()
 * 
 * post-conditions: This Token's string representation was returned.
 */
char* Token::get_token_string()
{

	return( this->token_string );

}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int Token::get_token_type()
{

	return( this->token_type );

}

char *Token::get_filename()

{
	return (this->filename);
}


/*
 * get_line_num()
 * 
 * post-conditions: This Token's line number was returned.
 */
int Token::get_line_num()
{

	return( this->line_num );

}


/*
 * get_object_index()
 * 
 * post-conditions: This Token's object index was returned.
 */
int Token::get_object_index()
{

	return( this->object_index );

}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void Token::loadSemanticValueStruct()
{

	//Convert the token string to the appropriate data type and load the yylval union:
	
	//--This method will be overwritten in the various subclasses--

	return;

}


//**************************Class: TokenIdent***************************
/*
 * TokenIdent - Constructor     
 */
TokenIdent::TokenIdent( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}


/*
 * TokenIdent - Destructor
 */
TokenIdent::~TokenIdent()
{                   
	//cout << "Inside TokenIdent Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenIdent::get_token_type()
{

	//return( this->token_type );	//We will always return xIDENTIFIER from here.
	
	return( xIDENTIFIER );		//We will always return xIDENTIFIER from here.

}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenIdent::loadSemanticValueStruct()
{

	//Convert the token string to the appropriate data type and load the yylval union:	
	yylval.str_lit = get_token_string();	//This method is returning a char*

	return;

}


//**************************Class: TokenKeyWrd***************************
/*
 * TokenKeyWrd - Constructor     
 */
TokenKeyWrd::TokenKeyWrd( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}
	   

/*
 * TokenKeyWrd - Destructor
 */
TokenKeyWrd::~TokenKeyWrd()
{                   
	//cout << "Inside TokenKeyWrd Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenKeyWrd::get_token_type()
{

	int		keyword_type;

	//Get the keyword token symbol:
	keyword_type = this->getKeywordType( this->get_token_string() ); 

	return( keyword_type );

}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenKeyWrd::loadSemanticValueStruct()
{

	//Convert the token string to the appropriate data type and load the yylval union:	
	yylval.str_lit = this->get_token_string();	//This method is returning a char*

	return;

}


//**************************Class: TokenOper***************************
/*
 * TokenOper - Constructor     
 */
TokenOper::TokenOper( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}
	   

/*
 * TokenOper - Destructor
 */
TokenOper::~TokenOper()
{                   
	//cout << "Inside TokenOper Destructor" << endl;
	
	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenOper::get_token_type()
{

	int			len;
	char		*chr_array;


	//For OPERATOR tokens, the return type is the ASCII value of the token,
	//Or the defined symbol for '<<' and '>>':

	//For the single-char operators, they will only have a string length of 1.
	//Thus, we can pass back char 0 as the return type. For '<<' and '>>', we can 
	//pass back the appropriate token symbol. For semantic values in yylval union, 
	//load the same character for single-char tokens and both characters for '<<' 
	//or '>>' via the str_lit member:
	chr_array = this->get_token_string();
	
	len = strlen( chr_array );

	if( len == 1 )
		{
		//Pass back ASCII value:
		return( chr_array[0] );
		}
	else if( len == 2 )
		{
		//We have a '<<' or '>>'. Pass back the token symbol:
		if( chr_array[0] == '<' )
			return( DOUBLE_LT );
		else if( chr_array[0] == '>' )
			return( DOUBLE_GT );
		}
	

	return( 601 );


}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenOper::loadSemanticValueStruct()
{
	
	int			len;
	char		*chr_array;
	
	//For OPERATOR tokens, the return type is the ASCII value of the token,
	//Or the defined symbol for '<<' and '>>':

	//For the single-char operators, they will only have a string length of 1.
	//Thus, we can pass back char 0 as the return type. For '<<' and '>>', we can 
	//pass back the appropriate token symbol. For semantic values in yylval union, 
	//load the same character for single-char tokens and both characters for '<<' 
	//or '>>' via the str_lit member:
	chr_array = this->get_token_string();
	
	len = strlen( chr_array );

	if( len == 1 )
		{
		yylval.chr_val = chr_array[0];	//Load the single character as a byte.
		}
	else if( len == 2 )
		{
		//We load yylval the same way for either '<<' or '>>':
		yylval.str_lit = chr_array;
		}

	return;

}


//**************************Class: TokenPunc***************************
/*
 * TokenPunc - Constructor     
 */
TokenPunc::TokenPunc( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}
	   

/*
 * TokenPunc - Destructor
 */
TokenPunc::~TokenPunc()
{                   
	//cout << "Inside TokenPunc Destructor" << endl;
	
	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenPunc::get_token_type()
{

	int			len;
	char		*chr_array;


	//For PUNCTUATOR tokens, the return type is the ASCII value of the token,
	//Or the defined symbol for '::':

	//For the single-char punctuators, they will only have a string length of 1.
	//Thus, we can pass back char 0 as the return type. For '::', we can 
	//pass back the appropriate token symbol. For semantic values in yylval union, 
	//load the same character for single-char tokens and both characters for '::',
	//via the str_lit member:
	chr_array = this->get_token_string();
	
	len = strlen( chr_array );

	if( len == 1 )
		{
		//Pass back ASCII value:
		return( chr_array[0] );
		}
	else if( len == 2 )
		{
		//We have a '::'. Pass back the token symbol:
		if( chr_array[0] == ':' )
			return( DOUBLE_COLON );
		}
	
	return( 601 );


}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenPunc::loadSemanticValueStruct()
{
	
	int			len;
	char		*chr_array;
	
	//For PUNCTUATOR tokens, the return type is the ASCII value of the token,
	//Or the defined symbol for '<<' and '>>':

	//For the single-char punctuators, they will only have a string length of 1.
	//Thus, we can pass back char 0 as the return type. For '::', we can 
	//pass back the appropriate token symbol. For semantic values in yylval union, 
	//load the same character for single-char tokens and both characters for '::', 
	//via the str_lit member:
	chr_array = this->get_token_string();
	
	len = strlen( chr_array );
												  
	if( len == 1 )
		{
		yylval.chr_val = chr_array[0];	//Load the single character as a byte.
		}
	else if( len == 2 )
		{
		//We load yylval the same way for either '::':
		yylval.str_lit = chr_array;
		}

	return;

}



//**************************Class: TokenLiteralInt***************************
/*
 * TokenLiteralInt - Constructor     
 */
TokenLiteralInt::TokenLiteralInt( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}
	   

/*
 * TokenLiteralInt - Destructor
 */
TokenLiteralInt::~TokenLiteralInt()
{                   
	//cout << "Inside TokenLiteralInt Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenLiteralInt::get_token_type()
{

	//For INTEGER_LITERAL tokens of decimal, octal, or hexadecimal type, the return type 
	//is INTEGER_LITERAL.

	//Currently, the strings representing these values are converted to signed long
	//values. We could switch to unsigned long (via strtoul()) which wraps at the 2^31
	//limit. Whereas strtol(), just gives the maximum value with no wrapping around.
	//Strangely, strtoul() doesn't seem to be able to handle positive values of 2^31 -1
	//as unsigned. It wraps around as in a two's-complement format.

	//For semantic values in yylval union, we will load the long value via the lng_val 
	//member.

	return( INTEGER_LITERAL );

}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenLiteralInt::loadSemanticValueStruct()
{
	
	char			*chr_array;
	signed long		ltmp;


	//For INTEGER_LITERAL tokens of decimal, octal, or hexadecimal type, the return type 
	//is INTEGER_LITERAL.

	//Currently, the strings representing these values are converted to signed long
	//values. We could switch to unsigned long (via strtoul()) which wraps at the 2^31
	//limit. Whereas strtol(), just gives the maximum value with no wrapping around.
	//Strangely, strtoul() doesn't seem to be able to handle positive values of 2^31 -1
	//as unsigned. It wraps around as in a two's-complement format.

	//For semantic values in yylval union, we will load the long value via the lng_val 
	//member.

	chr_array = this->get_token_string();

	//Calculate the actual value of the integer literal token:
	//With param #2 (end ptr) set to 0, conversion will terminate on the '\0' character.
	//With param #3 (base) set to 0, leading char will determine base automatically:
	ltmp = strtol( chr_array, 0, 0 );

	//cout << "*****ltmp= " << ltmp << endl;

	//Load the parser's semantic value union:
	yylval.lng_val = ltmp;


	return;
	

}


//**************************Class: TokenLiteralFP***************************
/*
 * TokenLiteralFP - Constructor     
 */
TokenLiteralFP::TokenLiteralFP( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}
	   

/*
 * TokenLiteralFP - Destructor
 */
TokenLiteralFP::~TokenLiteralFP()
{                   
	//cout << "Inside TokenLiteralFP Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenLiteralFP::get_token_type()
{

	//For FLOATING_PT_LITERAL tokens, the return type is FLOATING_PT_LITERAL.

	//The strings representing floating point values are converted to type double.
	//This includes any format of floating point types, including exponential forms.
	
	//For semantic values in yylval union, we will load the double value via the dbl_val 
	//member.

	return( FLOATING_PT_LITERAL );


}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenLiteralFP::loadSemanticValueStruct()
{
	
	char			*chr_array;
	double			dtmp;


	//For FLOATING_PT_LITERAL tokens, the return type is FLOATING_PT_LITERAL.

	//The strings representing floating point values are converted to type double.
	//This includes any format of floating point types, including exponential forms.
	
	//For semantic values in yylval union, we will load the double value via the dbl_val 
	//member.
		
	chr_array = this->get_token_string();

	//Calculate the actual value of the floating point token:
	//With param #2 (end ptr) set to 0, conversion will terminate on the '\0' character.
	dtmp = strtod( chr_array, 0 );
	
	//cout << "*****dtmp= " << dtmp << endl;

	//Load the parser's semantic value union:
	yylval.dbl_val = dtmp;


	return;
	

}


//**************************Class: TokenLiteralString***************************
/*
 * TokenLiteralString - Constructor     
 */
TokenLiteralString::TokenLiteralString( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}


/*
 * TokenLiteralString - Destructor
 */
TokenLiteralString::~TokenLiteralString()
{                   
	//cout << "Inside TokenLiteralString Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenLiteralString::get_token_type()
{

	//For STRING_LITERAL tokens, the return type is STRING_LITERAL.

	//The literal strings are stored with their enclosing double quotes. We will 
	//strip these off and return the raw string as the semantic value, via the 
	//yylval union member str_lit.
	
	return( STRING_LITERAL );


}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenLiteralString::loadSemanticValueStruct()
{

	char			*chr_array;
	int				len;

	//********SEXY NOTE: WE NEED TO HANDLE THE CASE OF CONCATENATED STRINGS!
	//********			 WE WILL NEED TO REMOVE THE TWO ADJACENT 
	//********			 EMBEDDED QUOTES BEFORE RETURNING THE STRING
	//********			 LITERAL VALUE. WE COULD DO THIS BY COPYING THE 
	//********			 CHARS AFTER THE "" INTO THEIR SLOTS, AND WALKING
	//********			 TO THE END OF THE STRING. SO, ' ABC""DEF ' WOULD 
	//********			 LOOK LIKE ' ABCDEF '
	/*	
	//Allocate storage for the token string and load token_string:
	this->token_string = new char( strlen(string_arg) + 1 ); 
	strcpy( this->token_string, string_arg );
	*/
	
	//For STRING_LITERAL tokens, the return type is STRING_LITERAL.

	//The literal strings are stored with their enclosing double quotes. We will 
	//strip these off and return the raw string as the semantic value, via the 
	//yylval union member str_lit:
	chr_array = this->get_token_string();
	
	//Check that first char is indeed a ", and increment chr_array to skip it:
	if( chr_array[0] == '"' )
		chr_array++;		//Now pointing to first character of string.
	else
		{
		cout << "Error occurred: TokenLiteralString::loadSemanticValueStruct()" << endl;
		cout << "				 Expected leading double quote, but none found." << endl;
		}

	//Replace trailing double quote with a '\0', thus isolating the actual string:
	len = strlen( chr_array );		//	ABC" == length of 4
	chr_array[len-1] = '\0';		//	len-1 refers to 4th element, the ". Replace this.
		
	//Load the semantic value with a pointer to the string:
	yylval.str_lit = chr_array;
	
	
	return;

}


//**************************Class: TokenLiteralChar***************************
/*
 * TokenLiteralChar - Constructor     
 */
TokenLiteralChar::TokenLiteralChar( char *string_arg, int type_arg, int line_num_arg, int object_index_arg, char *filename ) :
	Token( string_arg, type_arg, line_num_arg, object_index_arg, filename )
{    

	return;

}


/*
 * TokenLiteralChar - Destructor
 */
TokenLiteralChar::~TokenLiteralChar()
{                   
	//cout << "Inside TokenLiteralChar Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->token_string;

	
	return;
}


/*
 * get_token_type()
 * 
 * post-conditions: This Token's token type was returned.
 */
int TokenLiteralChar::get_token_type()
{

	//For CHARACTER_LITERALS, of single ASCII character, octal escape sequence, or 
	//hexadecimal escape sequence types, the return type is CHARACTER_LITERAL.

	//The literal characters are stored with their enclosing single quotes. Thus for 
	//the semantic value, we will extract the value within these single quotes.
	//The literal characters will be processed according to which of these three types
	//they are. In all three cases, a value equivalent to the ASCII value of the 
	//character will be loaded as the semantic value, via the yylval union member 
	//chr_val.
	
	return( CHARACTER_LITERAL );


}


/* 
 * loadSemanticValueStruct()
 * 
 * post-conditions: This Token's semantic value was loaded into the parser's yylval union.
 */
void TokenLiteralChar::loadSemanticValueStruct()
{

	char			*chr_array;
	int				len;
	int				ltmp;


	//For CHARACTER_LITERALS, of single ASCII character, octal escape sequence, or 
	//hexadecimal escape sequence types, the return type is CHARACTER_LITERAL.

	//The literal characters are stored with their enclosing single quotes. Thus for 
	//the semantic value, we will extract the value within these single quotes.
	//The literal characters will be processed according to which of these three types
	//they are. In all three cases, a value equivalent to the ASCII value of the 
	//character will be loaded as the semantic value, via the yylval union member 
	//chr_val.

	//The character literals are stored with their enclosing single quotes. We will 
	//strip these off and return the raw character ASCII value as the semantic value, 
	//via the yylval union member chr_val:
	chr_array = this->get_token_string();
	
	//Check that first char is indeed a ', and increment chr_array to skip it:
	if( chr_array[0] == '\'' )
		chr_array++;		//Now pointing to first character of string.
	else
		{
		cout << "Error occurred: TokenLiteralChar::loadSemanticValueStruct()" << endl;
		cout << "				 Expected leading double quote, but none found." << endl;
		}

	//Replace trailing single quote with a '\0', thus isolating the actual char literal string:
	len = strlen( chr_array );		//	A' == length of 2
	chr_array[len-1] = '\0';		//	len-1 refers to 2nd element, the '. Replace this.

	
	//Process character literal according to its token type:
	if( chr_array[0] != '\\' )
		{			  
		//This is a standard ASCII character, like 'A':
		//The string should look like: A'\0'
		//We can simply load yylval with the char's ASCII value:
		yylval.chr_val = chr_array[0];
		}
	else if( chr_array[0] == '\\' )
		{
		//We have an octal or hexadecimal escape sequence:
		//The string should look like: \xnn'\0', \Xnn'\0', or \ooo'\0'
		if( (chr_array[1] == 'x') || (chr_array[1] == 'X') )
			{
			//We have a hexadecimal escape sequence.
			//We will replace the leading '\' with a '0' to allow strtol() to convert automatically
			//based on the leading '0x'
			chr_array[0] = '0';
			//Move the chr_array base to be the first character after the 'x':
			//chr_array += 2;	//Skip the '\' and the 'x' (or 'X').
			
			//Perform conversion from string to long integer:
			//With param #3 (base) set to 16, this literal will be treated as a 
			//hexadecimal value:
			//With param #3 (base) set to 0, this literal will be treated as a hexadecimal value automatically:
			ltmp = strtol( chr_array, 0, 0 );
			/*	
			l = strtol( ls, 0, 10 );
			l = strtol( los, 0, 8 );
			l = strtol( los, 0, 10 );				//sexy
			l =		strtol( lhs, 0, 16 );
			l = strtol( lhs, 0, 10 )
			*/
			//Load the yylval union with the character value:
			yylval.chr_val = (char) ltmp;
			}
		else if( isdigit(chr_array[1]) )
			{
			//We have an octal escape sequence.
			//We will replace the leading '\' with a '0' to allow strtol() to convert automatically
			//based on the leading '0':

			//Convert the leading '\' to '0':
			chr_array[0] = '0';

			//With param #3 (base) set to 0, this literal will be treated as an octal value automatically:
			ltmp = strtol( chr_array, 0, 0 );

			//Load the yyval union:	
			yylval.chr_val = (char) ltmp;
			}
			
		}


	return;

}

