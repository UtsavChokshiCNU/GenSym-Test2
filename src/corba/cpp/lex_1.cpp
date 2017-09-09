/*
 * Lexical Analyzer and Control
 *
 * The declarartion for the LexicalAnalyzer class is in lex_1_dcl.h
 *
 * The lexer is built upon a Finite State Machine model for the type of code we 
 * will be tokenizing (IDL files).
 *
 * The Lexical Analyzer class also performs control functions and various other functions.
 *
	An excerpt on tokens:
	A token is the smallest element of a C++ program that is meaningful to the compiler. 
	The C++ parser recognizes these kinds of tokens: identifiers, keywords, literals, 
	operators, punctuators, and other separators. A stream of these tokens makes up a translation unit.
	Tokens are usually separated by white space. White space can be one or more:
	·	Blanks		' ' 
	·	Horizontal or vertical tabs	\t, \v
	·	New lines	\n
	·	Formfeeds	\f
		Carriage Returns	\r
	·	Comments
 *
 */
#include <stdio.h>
#include <iostream_ver.h>
#include <fstream_ver.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "g2string.h"
#include "code_tokens.h"
#include "corba_main.h"

extern "C"
{
#include "yacc_supp.h"
#include "ytab.h"
}

#include "parse_dcl.h"
#include "parse_tree_node_dcl.h"
#include "token_dcl.h"
#include "lex_1_dcl.h"
#include "builder_dcl.h"

#include "gsi_main_cpp.h"
#include "gsi_misc_cpp.h"

#define FAIL				-1
#if !defined( FALSE )
#	define FALSE			0
#endif
#if !defined( TRUE )
#	define TRUE				1 
#endif
#define	END_OF_TOKEN_LIST	0
#define	RECURSION			0
#define	LIST_TRAVERSAL		1


/**** Forward Declarations of Top Level Functions ****/
int lexer_error_handler( char *, int, char * );
void main_control( gsi_item, gsi_item * );
int compiler_cleanup();

//Suppress C++ "name Mangling":
extern "C"
{
extern int yyparse();
extern void parser_initialize();
int yylex();
int parser_error_handler();
int parser_cleanup();

}

//Compiler debug state flag:
int compiler_debug_state = DEBUG_OFF;



//**************************Class: LexicalAnalyzer***************************
//We must initialize static variables at file scope, without 'static' keyword:
const int LexicalAnalyzer::ISALPHA = 0;
const int LexicalAnalyzer::ISDIGIT = 1;
const int LexicalAnalyzer::ISPUNCT = 2;
const int LexicalAnalyzer::ISSPACE = 3;
const int LexicalAnalyzer::ISUNKNOWN = 4;

const int LexicalAnalyzer::OUTALL = 0;
const int LexicalAnalyzer::IDENTIFIER_STATE = 1;
const int LexicalAnalyzer::IN_C_COMMENT = 2;
const int LexicalAnalyzer::PUNCTUATION = 3;
const int LexicalAnalyzer::GENL_NUM_LITERAL = 4;
const int LexicalAnalyzer::HEX_INT_LITERAL_FIRST_PAST_X = 5;
const int LexicalAnalyzer::FP_E_NO_DOT_LITERAL = 6;
const int LexicalAnalyzer::GENL_INT_LITERAL_LEAD_0 = 7;
const int LexicalAnalyzer::OCT_INT_LITERAL = 8;
const int LexicalAnalyzer::FP_DOT_LITERAL = 9;
const int LexicalAnalyzer::FP_E_NO_DOT_SIGNED_LITERAL = 10;
const int LexicalAnalyzer::ADD_DIGIT = 11;
const int LexicalAnalyzer::FP_LEADING_DOT_LITERAL = 12;
const int LexicalAnalyzer::GENL_CHAR_LITERAL = 13;
const int LexicalAnalyzer::TERMINATE_CHAR_LITERAL = 14;
const int LexicalAnalyzer::ESCAPE_CHAR_LITERAL = 15;
const int LexicalAnalyzer::HEX_ESC_1ST_CHAR_LITERAL = 16;
const int LexicalAnalyzer::HEX_ESC_2ND_CHAR_LITERAL = 17;
const int LexicalAnalyzer::OCT_ESC_2ND_CHAR_LITERAL = 18;
const int LexicalAnalyzer::OCT_ESC_LAST_CHAR_LITERAL = 19;
const int LexicalAnalyzer::GENL_STRING_LITERAL = 20;
const int LexicalAnalyzer::STRING_LITERAL_ESC_SEQ = 21;
const int LexicalAnalyzer::STRING_LITERAL_END_CHECK = 22;
const int LexicalAnalyzer::STRING_LITERAL_HEX_ESC_1ST_CHAR = 23;
const int LexicalAnalyzer::STRING_LITERAL_HEX_ESC_2ND_CHAR = 24;
const int LexicalAnalyzer::STRING_LITERAL_OCT_ESC_2ND_CHAR = 25;
const int LexicalAnalyzer::STRING_LITERAL_OCT_ESC_LAST_CHAR = 26;
const int LexicalAnalyzer::CHECK_NO_HEX_CHAR = 27;
const int LexicalAnalyzer::DOUBLE_COLON_CHECK = 28;
const int LexicalAnalyzer::DOUBLE_LT_CHECK = 29;
const int LexicalAnalyzer::DOUBLE_GT_CHECK = 30;
const int LexicalAnalyzer::COMMENT_CHECK = 31;
const int LexicalAnalyzer::IN_CPP_COMMENT = 32;
const int LexicalAnalyzer::C_COMMENT_TERMINATE_CHECK = 33;
const int LexicalAnalyzer::HEX_INT_LITERAL_GENL = 34;

/**************************/
/* LexicalAnalyzer        */
/* Constructor            */
/* Read the file to be tokenized and load it into an array for internal use. */
/**************************/
LexicalAnalyzer::LexicalAnalyzer( void )
{    
	
	
	this->line_num = 1;		//line_num should be 1-based (first line is line 1, not line 0)
	this->token_index = 0;			//For token array.
	this->token_object_index = 0;		//For token list.
	this->cbuf = new char[1024];
	this->filename = NULL;   // null until we get a file 
	this->cbuf_pos = 0;
	this->set_state( OUTALL );

	this->head = 0;
	this->tail = 0;
	this->currentToken = 0;
	this->previousToken = 0;
	this->char_array = NULL; 
	memset(cbuf, 0, 1024);
	this->ptn_head = 0;
}


/*******************/
/* LexicalAnalyzer */
/* Destructor      */
/*******************/
LexicalAnalyzer::~LexicalAnalyzer()
{   

	int			token_removal_method;
	

	if( compiler_debug_state == DEBUG_ON )cout << "Inside LexicalAnalyzer Destructor" << endl;

	//Delete the various memory blocks allocated for this program:
	if (char_array) delete char_array;
	delete [] this->cbuf;		//Temporary character buffer for potential tokens.
	if (filename) delete filename;

	//Free each allocated Token in list:
	//This can be done via the list traversal function deleteTokenList(), which removes 
	//each node it visits, or by deleteToken(), a recursive function which deletes the 
	//list recursively.
	///Set the following to the symbol LIST_TRAVERSAL or RECURSION:
	//token_removal_method = LIST_TRAVERSAL;
	token_removal_method = RECURSION;
	
	if( token_removal_method == LIST_TRAVERSAL )
		{
		this->deleteTokenList();
		}
	else if( token_removal_method == RECURSION )
		{
		//Make sure that list is not empty before proceeding:
		if( this->head == 0 )
			{
			cout << "Token list is empty..." << endl;
			}
		else
			{
			//List has at least one member.
			this->deleteToken( this->head );
			cout << "\nToken list deleted...\n" << endl;
			}
		}

	//Free each allocated ParseTreeNode in list:
	//This is only done via a recursive function:
	//Make sure that list is not empty before proceeding:
	if( this->ptn_head == 0 )
		{
		cout << "ParseTreeNode list is empty..." << endl;
		}
	else
		{
		//List has at least one member.
		this->deleteParseTreeNode( this->ptn_head );
		cout << "ParseTreeNode list deleted...\n" << endl;
		}
	

	return;
}


/*
 * get_ptn_head()
 */
ParseTreeNode *LexicalAnalyzer::get_ptn_head() 
{

	return( this->ptn_head );

}     


//
// read the contents of a file into the input buffer
//

void LexicalAnalyzer::setFile(char *filename)

{
	int		index;
	char		c;
	ifstream	inp_file1 ;
	ifstream        inp_file2 ;

	cout << "Lexing File: " << filename << ":";
	//Open and read the file, counting characters. This will give us a count to use 
	//to size the array that is going to hold the characteres.
	inp_file1.open( filename );
	
	if( inp_file1 == 0 )	lexer_error_handler(filename, 0, "File open error occurred!");
				
	//Read in the characters, count them, and discard them:
	index = 0;
	inp_file1.get( c );
	while( 1 )
		{
		index++;		

		//Get next character:
		inp_file1.get( c );
#if defined(rs6000) || defined(hp9000s700) || defined(hp9000s800) || defined(linux)
		if (inp_file1.eof()) break ;   // end of file
#else
		if (!inp_file1.ipfx(1)) break; // end of file 
#endif
		}

	cout << " " << index << " chars" << endl;  // notify the user
	
	//Clean up:
	inp_file1.close();
	
	//Use the char count information to allocate storage for the character array:
	if (char_array) delete char_array;  // clean up the old one
	this->char_array = new char[index+3];		//Add one for EOF, two extra (not used).
		
	//Prepare to load storage array:
	inp_file2.open( filename );

	if( inp_file2 == 0 ) lexer_error_handler(filename, 0,"File open error occurred!");

	//Load the storage array with the data from the input file:
	index = 0;
	inp_file2.get( c );
	while( 1 )
		{
		//Load the array here:
		char_array[index++] = c;		

		//Get next character:
		inp_file2.get( c );
#if defined(rs6000) || defined(hp9000s700) || defined(hp9000s800) || defined(linux)
		if (inp_file2.eof()) break ;   // end of file
#else
		if (!inp_file2.ipfx(1)) break; // end of file 
#endif
		}


	//Store the EOF character:
	char_array[index++] = EOF;
	char_array[index] = 0;

	this->filename = new char[strlen(filename)+1];
	strcpy(this->filename, filename);

	//Display the EOF character:
	//cout << "c= " << c << " ASCII= " << (int) c << endl;
	//cout << "EOF= " << EOF << endl;

	//Clean up:
	inp_file2.close();
}





//***Declare Global objects. Global needed for interaction with yyparse() C routine:
LexicalAnalyzer		*lex;
Builder				*bobj;        


#ifdef WIN32
#define FILESLASH '\\';
#else
#define FILESLASH '/';
#endif


//
// Fix the '/' file name problem
//
void fix_file_names(char *filename)

{
return;  // this file fix thingy is bogus //// ~~~
	for (char *ptr = filename; *ptr; ptr++) {
		if (*ptr == '~' && ptr[1] == '\\') strcpy(ptr, ptr+1); // skip ~
		if (*ptr == '/' || *ptr == '\\') *ptr = FILESLASH;
	}
}


//
// Incremental routine to parse a file.  This loads the file chars
// into the buffer and calls the lexer to add the tokens to the list
//

void lex_a_file(char *filename)

{
	G2String name = filename;
	fix_file_names((char *) name); // NOT ok to mess with GSI structures
	lex->setFile((char *) name);

	//Tokenize the file:
	lex->token_machine();
}


//
// main_control routine
// This is called by the rpc to parse the files.  This receives a list 
// of file names and is expected to populate GSI return objects to
// be passed back to G2.
//
// A note about error handling:
// If an error occures while parsing the file, it will longjmp to 
// this routine.  A global G2String is used to store the error message.
// 

void main_control( gsi_item file_names, gsi_item *itms )
{

	// First, set the long jump for the error handler
	int ret = setjmp(error_marker);
	if (!ret) { // first time through

		//Display Greeting:
		cout << "\n********Commencing IDL Compilation...\n" << endl;

		//Build a LexicalAnalyzer object:														   
		lex = new LexicalAnalyzer();

		//Build a Builder object:
		bobj = new Builder( lex );
	 
		//Initialize appropriate variables in parser:
		//Ensure that this function is called before any error-generating operations
		//are executed (lexer, parser). This is reqd since error recovery for both the
		//lexer and the parser includes a call to compiler_cleanup(), which runs the 
		//parser_cleanup() routine whether the parser has been run yet (parser error)
		//or not (lexer error). Other wise, freeing of unallocated memory could occur:
		parser_initialize();				
		
		int count = gsi_element_count_of(file_names);
		if (!count) lexer_error_handler("", 0, "No IDL files to compile!");
		char **filenames = gsi_str_list_of(file_names);
    cout << "===> Begin Lexing Operations...\n" << endl;
		for (int i = 0; i < count; i++) // handle each file
			lex_a_file(filenames[i]);		//Lexer error may occur in here, in token_machine().
		cout << "\nLexing Operations Completed.\n" << endl;

		//Build a Builder object:
		//bobj = new Builder( lex ); <===MOVED UP TO ORIGINAL POSITION

		//Tokenize the file:
		//lex->token_machine();		<== Now performed in lex_a_file().
	
		//Now that tokens have been created, point currentToken to the head 
		//of the Token list:
		lex->initCurrentToken();

		//Begin parsing operations:
		//cout << "Begin Parsing Operations...\n" << endl;
		yyparse(); 							//Parser error may occur in here, in yyparse().
		cout << "Parsing Operations Completed.\n" << endl;
		
		//cout << "Begin Output Generation...\n" << endl;
		//Build the GSI data object model from the parse tree model:
		bobj->buildGSIModel();

		//Build the GSI Item for return to G2:
		bobj->buildGSIItem( itms[2] );

		cout << "\nOutput Generation Complete." << endl;

		//Clean up:
		compiler_cleanup();
	
		// If we got this far, then we have the built up array
		gsi_set_sym(itms[0], "SUCCESS");
		gsi_set_str(itms[1], "OK");

		//Display completion message:
		cout << "********IDL Compilation Completed.\n" << endl;

		return;
	}

	// If we get there, then we have a error.  The global string 
	// holds the error message to return to G2

	gsi_set_sym(itms[0], "ERROR");
	gsi_set_str(itms[1], (char *) error_message);
	gsi_item *nitms;
	gsi_item *nvals;
	token_create_array(itms[2], 0, &nitms, &nvals); // build null obj
	return;
}



/*
 * yylex()
 *									
 * This top level function is the interface between the yyparse() function and the 
 * Lex/Token methods that will handle the lexical side of the system.
 */
int yylex()
{

	return( lex->processToken() );	

}


/*
 * compiler_cleanup()
 *									
 * This top level function will remove the LexicalAnalyzer and Builder objects, and also 
 * handle the cleanup of the parser's allocated memory.
 */
int compiler_cleanup()
{
	
	//Terminate the primary compiler objects:
	delete bobj;
	delete lex;

	//Commence parser memory cleanup:
	parser_cleanup();


	return( 0 );

}


/*
 * parser_error_handler()
 *	
 * This function handles errors which occur in the yyparse() function.
 */
int parser_error_handler()
{

	char			*filename;
	int				line_num;
  int       fsize;

	
	//Get error information prior to termination of Compiler objects:
	//Allocate storage for filename, since original will be deallocated:
  fsize = strlen(lex->get_previousToken_filename());
	filename = (char *) malloc( fsize + 1 );
//	strcpy( filename, lex->get_filename() ); ~rjf
  if (fsize <= 1)
    *filename = 0;
  else
	  strcpy( filename, lex->get_previousToken_filename() );

	line_num = lex->get_previousToken_line_num();

	//Commence Compiler shutdown and cleanup:
	compiler_cleanup();
	
	//Pass control to general GSI-related error handler:	
	dispatch_error( filename, line_num, " Syntax Error. ");

	//Free the allocated memory:
	//NOTE: This may never get called because of the annoying long jump in dispatch error:
	free( filename );


	return( 0 );
}


/*
 * lexer_error_handler()
 *
 * This function handles errors which occur in the LexicalAnalyzer::token_machine() method.
 */
int lexer_error_handler( char *filename, int line_num, char *msg )
{
	
	char			*local_filename;


	//Allocate storage for filename, since original will be deallocated:
	local_filename = (char *) malloc( strlen(filename) + 1 );
	strcpy( local_filename, filename );

	//Commence Compiler shutdown and cleanup:
	compiler_cleanup();
	
	//Pass control to general GSI-related error handler:
	dispatch_error( local_filename, line_num, msg );

	//Free the allocated memory:
	//NOTE: This may never get called because of the annoying long jump in dispatch error:
	free( local_filename );


	return( 0 );
}


/*
 * get_previousToken_line_num()
 */
int LexicalAnalyzer::get_previousToken_line_num()
{
	return( this->previousToken->get_line_num() );
}


/*
 * get_previousToken_filename()
 */
char *LexicalAnalyzer::get_previousToken_filename()
{
	return( this->previousToken->get_filename() );
}


/*
 * get_filename()
 */
char *LexicalAnalyzer::get_filename()
{
	return( this->filename );
}


/*
 * token_machine()
 *									
 * This method will tokenize the file data via a Finite State Machine.
 */
void LexicalAnalyzer::token_machine()
{

	char	c;
	int		type;
	int		status;
	int		token_type;
	int     col;


	//Initial state is outside of anything and everything:
	this->set_state( OUTALL );
	//Initialize char_array master index:
	this->char_array_index = 0;
	line_num = 1;  // start at top of file
	col = 0;


	//*******MAIN PROCESSING LOOP:
	c = '\0';
	while( 1 )
		{
		//Get a character:
		c = this->char_array[char_array_index++];
		col++;
		if (c == '\n') col = 0;
		if (c == EOF) break; // done with file...
		//cout << c;
 
		//Determine char type:
		type = char_type( c );

		if( compiler_debug_state == DEBUG_ON )cout << "c= " << c << " type= " << type << endl;


		//Process input according to present state:
		if( this->get_state() == OUTALL )
			{
			switch( type )
				{
				case ISALPHA:
					this->set_state( IDENTIFIER_STATE );
					add_to_cbuf( c );
					break;
				case ISDIGIT:
					if( c == '0' )
						{
						//Not a floating point literal:
						this->set_state( GENL_INT_LITERAL_LEAD_0 );
						add_to_cbuf( c );	
						}
					else	//1-->9
						{
						//May be an int or float:
						this->set_state( GENL_NUM_LITERAL );
						add_to_cbuf( c );
						}
					break;
				case ISPUNCT:
					//If there is a '.' as a leading character, then we have an fp literal.
					//[This is probably the only possibility for a leading '.']
					if( c == '.' )
						{										
						//This is a floating point literal:
						add_to_cbuf( c );
						//Change State:
						this->set_state( FP_LEADING_DOT_LITERAL );
						}
					else if( c == '\'' )	//A single quote.
						{
						//This is probably a character literal.
						add_to_cbuf( c );
						//Change State:
						this->set_state( GENL_CHAR_LITERAL );
						}
					else if( c == '"' )
						{
						//This is probably a string literal.
						add_to_cbuf( c );
						//Change State:
						this->set_state( GENL_STRING_LITERAL );
						}
					else if( c == '\\' )
						{
						//The escape character cannot appear outside of a 
						//char or string literal:
						lexer_error_handler(filename, line_num, "Invalid char");
						}
					else if( c == '/' )
						{
						//this may be a c++ comment, c comment or a divide operator:
						add_to_cbuf( c );
						//Change State:
						this->set_state( COMMENT_CHECK );
						}					
					else if( c == ':' )
						{
						//this may be a ':' or a '::' token:
						add_to_cbuf( c );
						//Change State:
						this->set_state( DOUBLE_COLON_CHECK );
						}     
					else if( c == '<' )
						{
						//this may be a '<' or a '<<' token:
						add_to_cbuf( c );
						//Change State:
						this->set_state( DOUBLE_LT_CHECK );
						}
					else if( c == '>' )
						{
						//this may be a '>' or a '>>' token:
						add_to_cbuf( c );
						//Change State:
						this->set_state( DOUBLE_GT_CHECK );
						}
					//The following punct chars are tokens themselves:
					else if( (c==';') || (c=='{') || (c=='}') || (c=='(') || (c==')') || (c=='~') ||
							 (c==',') || (c=='[') || (c==']') || (c=='=') || (c=='+') || (c=='-') ||
							 (c=='|') || (c=='^') || (c=='&') || (c=='*') || (c=='%') )
						{
						//This is a standalone token. Store it as a token and proceed:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
								
						//Change state (We are now outside of any token):
						this->set_state( OUTALL );
						}
					else if (c == '#' && col == 1) { // start of preprocessor statement
						this->set_state(IN_CPP_COMMENT); // treat like c++ comment
					}
					else
						{
						//Consider any other characters as invalid here also (eg: '!'):	
						lexer_error_handler(filename, line_num, "Invalid char");				    
						}
					break;
				case ISSPACE:
					//Skip over any whitespaces.
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						}
					break;
				case ISUNKNOWN:
					lexer_error_handler(filename, line_num, "Invalid char");
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == IDENTIFIER_STATE )
			{
			switch( type )
				{
				case ISALPHA:
					add_to_cbuf( c );
					break;
				case ISDIGIT:
					add_to_cbuf( c );
  					break;
				case ISPUNCT:
					if( c == '_' )		//Only valid punctuation in an identifier.
						{
						add_to_cbuf( c );
						}
					//The following are the token-terminating chars and are themseleves	tokens. 
 					//Write the current cbuf to the token list, reset cbuf, then
					//add the current char/token to the token list. Then move to the 
					//appropriate state (usually OUTALL: OUTside of ALL tokens).
					else if( (c==';') || (c=='{') || (c=='}') || (c=='(') || (c==')') || (c=='~') ||
							 (c==',') || (c=='[') || (c==']') || (c=='=') || (c=='+') || (c=='-') ||
							 (c=='|') || (c=='^') || (c=='&') || (c=='*') || (c=='%') )
						{
						//Store current identifier token:
						
						//NOTE: WE SHOULD PROBABLY DO THE VALIDITY CHECK BEFORE ADDING THE
						//      TOKEN TO THE LIST.
						//Determine if this token is a plain IDENTIFIER or a KEYWORD:
						status = this->isKeyword(cbuf);
						if( status == TRUE )
							token_type = KEYWORD;
						else if( status == FALSE )
							token_type = IDENTIFIER;
						else
							lexer_error_handler(filename, line_num, "Invalid keyword case" );

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );
												
						//Reset cbuf items:
						this->reset_cbuf();
																			   
						//Load the punct char:
						add_to_cbuf( c );
						//Store it as a token:
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
											
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}
					else if( c == ':' )
						{
						//Store current identifier token:

						//Determine if this token is a plain IDENTIFIER or a KEYWORD:
						status = this->isKeyword(cbuf);
						if( status == TRUE )
							token_type = KEYWORD;
						else if( status == FALSE )
							token_type = IDENTIFIER;	
						else
							{
							if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: IDENTIFIER_STATE: case ISPUNCT" << endl;						    
							lexer_error_handler(filename, line_num, "Invalid keyword case" );						    
							}

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a ':' or a "::' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_COLON_CHECK ); 
						}						
					else if( c == '<' )
						{
						//Store current identifier token:

						//Determine if this token is a plain IDENTIFIER or a KEYWORD:
						status = this->isKeyword(cbuf);
						if( status == TRUE )
							token_type = KEYWORD;
						else if( status == FALSE )
							token_type = IDENTIFIER;							
						else
							lexer_error_handler(filename, line_num, "Invalid keyword case" );
							
						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '<' or a "<<' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_LT_CHECK ); 
						}						
					else if( c == '>' )
						{
						//Determine if this token is a plain IDENTIFIER or a KEYWORD:
						status = this->isKeyword(cbuf);
						if( status == TRUE )
							token_type = KEYWORD;
						else if( status == FALSE )
							token_type = IDENTIFIER;							
						else
							lexer_error_handler(filename, line_num, "Invalid keyword case" );

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '>' or a ">>' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_GT_CHECK ); 
						}
					else if( c == '/' )
						{
						//Store current identifier token:

						//Determine if this token is a plain IDENTIFIER or a KEYWORD:
						status = this->isKeyword(cbuf);
						if( status == TRUE )
							token_type = KEYWORD;
						else if( status == FALSE )
							token_type = IDENTIFIER;							
						else
							lexer_error_handler(filename, line_num, "Invalid keyword case" );
							
						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//this may be a c++ comment, c comment or a divide operator:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( COMMENT_CHECK );
						}						
					else if( (c=='.') || (c=='\'') || (c=='"') || (c=='\\') || (c=='~') )
						{
						//These characters are currently considered invalid.
						lexer_error_handler(filename, line_num, "Invalid char");						    
						}
					break;
				case ISSPACE:
					//Determine if this token is a plain IDENTIFIER or a KEYWORD:
					status = this->isKeyword(cbuf);
					if( status == TRUE )
						token_type = KEYWORD;
					else if( status == FALSE )
						token_type = IDENTIFIER;	
					else
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: IDENTIFIER_STATE: case ISPUNCT" << endl;						    
						lexer_error_handler(filename, line_num, "Invalid keyword case" );
						}						  

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );
										
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						}
					break;   
				case ISUNKNOWN:
					lexer_error_handler(filename, line_num, "Invalid char");
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Invalid char");
				}

			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == GENL_INT_LITERAL_LEAD_0 )  //In here we'll change state based on 2nd character.
			{
			switch( type )
				{
				case ISALPHA:
					//We come in here with first char (0) already in cbuf. Thus the first 
					//char we look at in this state is the 2nd char for cbuf: In fact, the only
					//char we will look at is the second, since we will change state in here:
					if( ((c=='x') || (c=='X')) && (cbuf_pos==1) )  //cbuf_pos check not needed.
						{										
						//This is a hex integer literal:
						add_to_cbuf( c );
						//Change State:
						this->set_state( HEX_INT_LITERAL_FIRST_PAST_X );
						}
					else
						{
						//Since no other alphas are allowed at this point, 
						//A syntax error occurred:
						lexer_error_handler(filename, line_num, "Invalid char");
						}
					break;
				case ISDIGIT:
					//We are in an octal integer:
					add_to_cbuf( c );
					
					//Change State:
					this->set_state( OCT_INT_LITERAL );
  					
					break;
				case ISPUNCT:
					//***********NEED TO ADD '.' SUPPORT FOR LEADING-ZERO FPs AND ALSO SUPPORT
					//***********FOR NUMERICS WITH LEADING 0s
					//TERM&SAVE TOKEN;SAVE CHAR ON: . / < > ; ) , ] = + - | ^ & * %
					//					   INVALID: ' " \ : ~ { } ( [
					//The following are the token-terminating chars and are themseleves	tokens. 
 					//Write the current cbuf to the token list, reset cbuf, then
					//add the current char/token to the token list. Then move to the 
					//appropriate state (usually OUTALL: OUTside of ALL tokens).
					if( (c=='.') || (c=='/') || (c==';') || (c==')') || (c==',') || (c==']') ||
						(c=='=') || (c=='+') || (c=='-') || (c=='|') || (c=='^') || (c=='&') ||
						(c=='*') || (c=='%') )
						{

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
																			   
						//Load the punct char:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
											
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}			
					else if( c == '<' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );
						
						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '<' or a "<<' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_LT_CHECK ); 
						}						
					else if( c == '>' )
						{					

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '>' or a ">>' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_GT_CHECK ); 
						}
					else if( (c=='\'') || (c=='"') || (c=='\\') || (c==':') || (c=='~') ||
							 (c=='{') || (c=='}') || (c=='(') || (c=='[') )
						{
						//These characters are currently considered invalid.

						lexer_error_handler(filename, line_num, "Invalid char");
						}
					else
						{
						//Consider any other characters as invalid here also (eg: '!'):
						lexer_error_handler(filename, line_num, "Invalid char");
						}
					break;
				case ISSPACE:
					//Value was a single int digit 0. we are now moving out of it.
					//Store the token:

					//Create, load, and add-to-list a Token object:
					token_type = INTEGER_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
					
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						}
					break;   
				case ISUNKNOWN:
						lexer_error_handler(filename, line_num, "Invalid char");
					break;
				default:
						lexer_error_handler(filename, line_num, "Invalid char");
				}

			continue;	//Go to next iteration of the while loop

	 		}

																				  
		if( this->get_state() == HEX_INT_LITERAL_FIRST_PAST_X )	//We already have '0x' at this point.
			{
			switch( type )
				{
				case ISALPHA:
					//[a->f],[A->F] are valid hex chars:
					if( (c=='a') || (c=='b') || (c=='c') || (c=='d') || (c=='e') || (c=='f') ||
						(c=='A') || (c=='B') || (c=='C') || (c=='D') || (c=='E') || (c=='F') )
						{
						add_to_cbuf( c );
						//Change State to handle remaining chars:
						this->set_state( HEX_INT_LITERAL_GENL );
						}
					else
						{
						//There should be no other alpha chars now that we are past 2nd slot.
						lexer_error_handler(filename, line_num, "Invalid char in hex constant");
						}
					break;
				case ISDIGIT:
					//Continue adding to hex int literal 
					add_to_cbuf( c );
					
					//Change State to handle remaining chars:
					this->set_state( HEX_INT_LITERAL_GENL );
					break;
				case ISPUNCT:
					// INVALID: [***ALL PUNCT IS INVALID***]
						lexer_error_handler(filename, line_num, "Unexpected char");
					break;
				case ISSPACE:
					//Only a hexadecimal char is valid here:
						lexer_error_handler(filename, line_num, "Invalid char");
					break;
				case ISUNKNOWN:
						lexer_error_handler(filename, line_num, "Invalid char");
					break;
				default:
						lexer_error_handler(filename, line_num, "Invalid char");
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == OCT_INT_LITERAL )	//We already have '0n' at this point.
			{
			switch( type )
				{
				case ISALPHA:
					//There should be no alpha chars in an octal integer:.
						lexer_error_handler(filename, line_num, "Unexpected char");
					break;
				case ISDIGIT:
					//Continue adding to oct int literal, if valid:
					if( (c=='8') || (c=='9') )
						{
						//Since '8' or '9' are not octal digits, 
						//A syntax error occurred.
						lexer_error_handler(filename, line_num, "Invalid char");
						}
					else
						{
						add_to_cbuf( c );
						}
					break;							  
				case ISPUNCT:
					//TERM&SAVE TOKEN;SAVE CHAR ON:  / < > ; ) , ] = + - | ^ & * %
					//					   INVALID: . ' " \ : ~ { } ( [
					//Note: '.' should not be invalid. we need to handle general leading 0 case!!!
					
					//The following are the token-terminating chars and are themseleves	tokens. 
 					//Write the current cbuf to the token list, reset cbuf, then
					//add the current char/token to the token list. Then move to the 
					//appropriate state (usually OUTALL: OUTside of ALL tokens).
					if( (c=='.') || (c=='/') || (c==';') || (c==')') || (c==',') || (c==']') ||
						(c=='=') || (c=='+') || (c=='-') || (c=='|') || (c=='^') || (c=='&') ||
						(c=='*') || (c=='%') )
						{
						//Store current token:

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
																			   
						//Load the punct char:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
											
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}			
					else if( c == '<' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '<' or a "<<' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_LT_CHECK ); 
						}						
					else if( c == '>' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '>' or a ">>' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_GT_CHECK ); 
						}
					else if( (c=='\'') || (c=='"') || (c=='\\') || (c==':') || (c=='~') ||
							 (c=='{') || (c=='}') || (c=='(') || (c=='[') )
						{
						//These characters are currently considered invalid.
						lexer_error_handler(filename, line_num, "Unexpected char");						    
						}
					else
						{
						//Consider any other characters as invalid here also (eg: '!'):
						lexer_error_handler(filename, line_num, "Unexpected char");							    
						}
					break;
				case ISSPACE:
					//We are now moving out of oct int literal:

					//Create, load, and add-to-list a Token object:
					token_type = INTEGER_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
										
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						}

					break;   
				case ISUNKNOWN:
						lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
						lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == HEX_INT_LITERAL_GENL )	//We already have '0xn' at this point.
			{
			switch( type )
				{
				case ISALPHA:
					//[a->f],[A->F] are valid hex chars:
					if( (c=='a') || (c=='b') || (c=='c') || (c=='d') || (c=='e') || (c=='f') ||
						(c=='A') || (c=='B') || (c=='C') || (c=='D') || (c=='E') || (c=='F') )
						{
						add_to_cbuf( c );
						}
					else
						{
						//There should be no other alpha chars now:
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISDIGIT:
					//Continue adding to hex int literal 
					add_to_cbuf( c );
					break;
				case ISPUNCT:
					//TERM&SAVE TOKEN;SAVE CHAR ON:  / < > ; ) , ] = + - | ^ & * %
					//					   INVALID: . ' " \ : ~ { } ( [
					//Note: '.' should not be invalid. we need to handle general leading 0 case!!!
					
					//The following are the token-terminating chars and are themseleves	tokens. 
 					//Write the current cbuf to the token list, reset cbuf, then
					//add the current char/token to the token list. Then move to the 
					//appropriate state (usually OUTALL: OUTside of ALL tokens).
					if( (c=='/') || (c==';') || (c==')') || (c==',') || (c==']') ||
						(c=='=') || (c=='+') || (c=='-') || (c=='|') || (c=='^') ||
						(c=='&') || (c=='*') || (c=='%') )
						{

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
																			   
						//Load the punct char:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
											
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}			
					else if( c == '<' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '<' or a "<<' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_LT_CHECK ); 
						}						
					else if( c == '>' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = INTEGER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '>' or a ">>' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_GT_CHECK ); 
						}
					else if( (c=='.') || (c=='\'') || (c=='"') || (c=='\\') || (c==':') || 
							 (c=='~') || (c=='{') || (c=='}') || (c=='(') || (c=='[') )
						{
						//These characters are currently considered invalid.
						lexer_error_handler(filename, line_num, "Unexpected char");							    
						}
					else
						{
						//Consider any other characters as invalid here also (eg: '!'):
						lexer_error_handler(filename, line_num, "Unexpected char");					    
						}
					break;
			
				case ISSPACE:
					//We are now moving out of hex int literal:

					//Create, load, and add-to-list a Token object:
					token_type = INTEGER_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
					
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						}

					break;   
				case ISUNKNOWN:
						lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
						lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == GENL_NUM_LITERAL )	//We have a 1-->9 character already.
			{
			switch( type )
				{
				case ISALPHA:
					//If there is an 'e' or 'E', then we have an fp literal that can have no dot.
					if( ((c=='e') || (c=='E')) )
						{										
						//This is a floating point literal:
						add_to_cbuf( c );
						//Change State:
						this->set_state( FP_E_NO_DOT_LITERAL );
						}
					else
						{
						//Since no other alphas are allowed at this point, 
						//A syntax error occurred.
						lexer_error_handler(filename, line_num, "Unexpected char in number");	
						}

					break;
				case ISDIGIT:
					//Continue adding to the decimal int or fp literal 
					add_to_cbuf( c );
					break;
				case ISPUNCT:
					//If there is a '.', then we have an fp literal.
					if( c == '.' )
						{										
						//This is a floating point literal:
						add_to_cbuf( c );
						//Change State:
						this->set_state( FP_DOT_LITERAL );
						}
					else
						{
						//TERM&SAVE TOKEN;SAVE CHAR ON: / < > ; ) , ] = + - | ^ & * % :
						//					   INVALID: ' " \ ~ { } ( [
						
						//The following are the token-terminating chars and are themseleves	tokens. 
 						//Write the current cbuf to the token list, reset cbuf, then
						//add the current char/token to the token list. Then move to the 
						//appropriate state (usually OUTALL: OUTside of ALL tokens).
						if( (c=='/') || (c==';') || (c==')') || (c==',') || (c==']') ||
							(c=='=') || (c=='+') || (c=='-') || (c=='|') || (c=='^') || 
							(c=='&') ||	(c=='*') || (c=='%') )
							{

							//Create, load, and add-to-list a Token object:
							token_type = INTEGER_LITERAL;
							this->addTokenToList( this->cbuf, token_type, this->line_num );

							//Reset cbuf items:
							this->reset_cbuf();
																			   
							//Load the punct char:
							add_to_cbuf( c );
							//Check token type:
							if( isOper(cbuf) )
								token_type = OPERATOR;
							else
								token_type = PUNCTUATOR;

							//Create, load, and add-to-list a Token object:
							this->addTokenToList( this->cbuf, token_type, this->line_num );

							//Reset cbuf items:
							this->reset_cbuf();
											
							//Change state (We are now outside of any token):
							this->set_state( OUTALL ); 
							}			
						else if( c == '<' )
							{

							//Create, load, and add-to-list a Token object:
							token_type = INTEGER_LITERAL;
							this->addTokenToList( this->cbuf, token_type, this->line_num );

							//Reset cbuf items:
							this->reset_cbuf();
						
							//This may be a '<' or a "<<' token:
							//Load the punct char:
							add_to_cbuf( c );
												
							//Change state:
							this->set_state( DOUBLE_LT_CHECK ); 
							}						
						else if( c == '>' )
							{

							//Create, load, and add-to-list a Token object:
							token_type = INTEGER_LITERAL;
							this->addTokenToList( this->cbuf, token_type, this->line_num );

							//Reset cbuf items:
							this->reset_cbuf();
						
							//This may be a '>' or a ">>' token:
							//Load the punct char:
							add_to_cbuf( c );
												
							//Change state:
							this->set_state( DOUBLE_GT_CHECK ); 
							}
						else if( c == ':' )
							{
							//This case could be valid if we are in a 'case' statement. For example: case 9:

							//Create, load, and add-to-list a Token object:
							token_type = INTEGER_LITERAL;
							this->addTokenToList( this->cbuf, token_type, this->line_num );

							//Reset cbuf items:
							this->reset_cbuf();
						
							//This may be a ':' or a '::' token:
							//Load the punct char:
							add_to_cbuf( c );
												
							//Change state:
							this->set_state( DOUBLE_COLON_CHECK ); 
							}
						else if( (c=='\'') || (c=='"') || (c=='\\') || (c==':') || (c=='~') ||
							(c=='{') || (c=='}') || (c=='(') || (c=='[') )
							{
							//These characters are currently considered invalid.
						lexer_error_handler(filename, line_num, "Unexpected char");							    
							}
						else
							{
							//Consider any other characters as invalid here also (eg: '!'):
						lexer_error_handler(filename, line_num, "Unexpected char");							    
							}
						}
					break;
				case ISSPACE:
					//We are now moving out of general numeric literal:
					//We most likely have a decimal integer.

					//Create, load, and add-to-list a Token object:
					token_type = INTEGER_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
					
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						}

					break;   
				case ISUNKNOWN:
						lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
						lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == FP_E_NO_DOT_LITERAL ) //We have encountered an 'e' or 'E' in a num literal, 
			{										//which means we have an FP literal with or without
			switch( type )							//a decimal point already encountered.
				{
				case ISALPHA:
					//Since no other alphas are allowed at this point, 
					//A syntax error occurred.
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_E_NO_DOT_LITERAL: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//Continue adding to the fp literal. This is the exponent.
					add_to_cbuf( c );
					break;
				case ISPUNCT:
					//If there is a '+' or '-', then we have a signed fp_e_no_dot_literal:
					if( (c=='+') || (c=='-') )
						{										
						//This is a signed exponentsil floating point literal, with no dot:
						add_to_cbuf( c );
						//Change State:
						this->set_state( FP_E_NO_DOT_SIGNED_LITERAL );
						}
					else								  
						{
						//[***ALL OTHER PUNCT AT THIS POINT IS INVALID***
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_E_NO_DOT_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");
						}
					break;
				case ISSPACE:
					//We are now moving out of fp_e_no_dot literal:

					//Create, load, and add-to-list a Token object:
					token_type = FLOATING_PT_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
					
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						}

					break;   
				case ISUNKNOWN:
						lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
						lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == FP_E_NO_DOT_SIGNED_LITERAL ) //We have nne+ or nne- loaded in an FP literal.
			{
			switch( type )
				{
				case ISALPHA:
					//Since no other alphas are allowed at this point, 
					//A syntax error occurred.
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_E_NO_DOT_SIGNED_LITERAL: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//Continue adding to the fp E signed literal. This is the exponent.
					add_to_cbuf( c );

					//Now that we have placed a char after the exponent sign, 
					//we can go to a state that just looks for digits:
					//Change state:
					this->set_state( ADD_DIGIT );

					break;
				case ISPUNCT:
					//Since we are in the signed fp with E, the character following the
					//sign (+ or -) must not be a punctuation mark, or an error has occurred:
					//A syntax error occurred.
					//*****[NO PUNCT CHARS ALLOWED HERE]*****
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_E_NO_DOT_SIGNED_LITERAL: case ISPUNCT" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISSPACE:
					//Since we are in the signed fp with E, the character following the
					//sign (+ or -) there must not be a space, or an error has occurred:
					//A syntax error occurred.
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_E_NO_DOT_SIGNED_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					
					//If this is a newline, increment line number counter:
/*
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		//For floats only (not integers)
		if( this->get_state() == ADD_DIGIT )	//We want to add only digits to the token.
			{									//We have an nnE+n already
			switch( type )
				{
				case ISALPHA:
					//There should be no alpha chars added..
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ADD_DIGIT: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//Continue adding to the token:
					add_to_cbuf( c );						
					break;
				case ISPUNCT:
					//TERM&SAVE TOKEN;SAVE CHAR ON: / < > ; ) , = + - *
					//					   INVALID: . ' " \ : ~ { } ( [	] | ^ & %
					
					//The following are the token-terminating chars and are themseleves	tokens. 
 					//Write the current cbuf to the token list, reset cbuf, then
					//add the current char/token to the token list. Then move to the 
					//appropriate state (usually OUTALL: OUTside of ALL tokens).
					if( (c=='/') || (c==';') || (c==')') || (c==',') || (c=='=') || (c=='+') || 
						(c=='-') || (c=='*') )
						{

						//Create, load, and add-to-list a Token object:
						token_type = FLOATING_PT_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
																			   
						//Load the punct char:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
											
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}			
					else if( c == '<' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = FLOATING_PT_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '<' or a "<<' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_LT_CHECK ); 
						}						
					else if( c == '>' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = FLOATING_PT_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '>' or a ">>' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_GT_CHECK ); 
						}				  
					else if( (c=='.') || (c=='\'') || (c=='"') || (c=='\\') || (c==':') || (c=='~') ||
						(c=='{') || (c=='}') || (c=='(') || (c=='[') || (c==']') || (c=='|') || 
						(c=='^') || (c=='&') || (c=='%') )
						{
						//These characters are currently considered invalid.
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ADD_DIGIT: case ISPUNCT" << endl;	
						lexer_error_handler(filename, line_num, "Unexpected char");						    
						}
					else
						{
						//Consider any other characters as invalid here also (eg: '!'):
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ADD_DIGIT: case ISPUNCT" << endl;	
						lexer_error_handler(filename, line_num, "Unexpected char");						    
						}
					break;
				case ISSPACE:
					//We are now moving out of the token:

					//Create, load, and add-to-list a Token object:
					token_type = FLOATING_PT_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
					
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;   
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

			}

		
		if( this->get_state() == FP_DOT_LITERAL )	//We have an fp literal with a decimal point.
			{										//We have 65.  for example.
			switch( type )
				{
				case ISALPHA:
					//If there is an 'e' or 'E', then we have an fp literal with dot and exponent.
					//[This is valid: 54.e6]
					if( ((c=='e') || (c=='E')) )
						{										
						//This is a floating point literal:
						add_to_cbuf( c );
						//Change State:
						this->set_state( FP_E_NO_DOT_LITERAL );
						}
					else
						{
						//Since no other alphas are allowed at this point, 
						//A syntax error occurred.
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_DOT_LITERAL: case ISALPHA" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}

					break;
				case ISDIGIT:
					//Continue adding to the decimal int or fp literal 
					add_to_cbuf( c );
					break;							
				case ISPUNCT:
					//TERM&SAVE TOKEN;SAVE CHAR ON: / < > ; ) , = + - *
					//					   INVALID: . ' " \ : ~ { } ( [	] | ^ & %
					
					//The following are the token-terminating chars and are themseleves	tokens. 
 					//Write the current cbuf to the token list, reset cbuf, then
					//add the current char/token to the token list. Then move to the 
					//appropriate state (usually OUTALL: OUTside of ALL tokens).
					if( (c=='/') || (c==';') || (c==')') || (c==',') || (c=='=') || (c=='+') || 
						(c=='-') || (c=='*') )
						{

						//Create, load, and add-to-list a Token object:
						token_type = FLOATING_PT_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
																			   
						//Load the punct char:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
											
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}			
					else if( c == '<' )
						{
						//Create, load, and add-to-list a Token object:
						token_type = FLOATING_PT_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '<' or a "<<' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_LT_CHECK ); 
						}						
					else if( c == '>' )
						{

						//Create, load, and add-to-list a Token object:
						token_type = FLOATING_PT_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
						
						//This may be a '>' or a ">>' token:
						//Load the punct char:
						add_to_cbuf( c );
												
						//Change state:
						this->set_state( DOUBLE_GT_CHECK ); 
						}		
					else if( (c=='.') || (c=='\'') || (c=='"') || (c=='\\') || (c==':') || (c=='~') ||
						(c=='{') || (c=='}') || (c=='(') || (c=='[') || (c==']') || (c=='|') || 
						(c=='^') || (c=='&') || (c=='%') )
						{
						//These characters are currently considered invalid.
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_DOT_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					else
						{
						//Consider any other characters as invalid here also (eg: '!'):
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_DOT_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//We are now moving out of fp_dot_literal:

					//Create, load, and add-to-list a Token object:
					token_type = FLOATING_PT_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
					
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;   
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}
				
		if( this->get_state() == FP_LEADING_DOT_LITERAL ) //We have an FP with just a dot.
			{											  //Next char can only be a digit.
			switch( type )
				{
				case ISALPHA:
					//There should be no alpha chars added..
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_LEADING_DOT_LITERAL: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//Continue adding to the token:
					add_to_cbuf( c );

					//Now that we have received a digit, we will behave like an FP_DOT_LITERAL:
					//Change state:
					this->set_state( FP_DOT_LITERAL );
					
					break;
				case ISPUNCT:
					//********ALL PUNCT IS INVALID HERE********
					
					//There should be no punctuation chars added..
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_LEADING_DOT_LITERAL: case ISPUNCT" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISSPACE:
					//There should be no whitespaces at this point:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: FP_LEADING_DOT_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					//If this is a newline, increment line number counter:

/*					
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

			}

		
		//For char literals, we will only support single characters in the following 
		//forms: 'A', '\n', '\x41', '\101' [character, non-graphic escape, hex escape, octal escape]
		if( this->get_state() == GENL_CHAR_LITERAL )		//We have encountered a single-quote.
			{
			switch( type )
				{
				case ISALPHA:
					//We are in the 'A' character format.
					add_to_cbuf( c );

					//Change state:
					this->set_state( TERMINATE_CHAR_LITERAL );

					break;
				case ISDIGIT:
					//We are in the 'A' character format.
					add_to_cbuf( c );

					//Change state:
					this->set_state( TERMINATE_CHAR_LITERAL );

					break;		
				case ISPUNCT:
					if( c == '\\' )													   
						{														   
						//This is an escape sequence of some type:
						add_to_cbuf( c );

						//Change state:
						this->set_state( ESCAPE_CHAR_LITERAL );
						}
					else if( c == '\'' )
						{
						//INVALID:	' 
						//ALL OTHERS ARE OKAY!
						
						//The single quote here results in an empty constant.
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: GENL_CHAR_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					else
						{
						//We are in the 'A' character format.
						add_to_cbuf( c );

						//Change state:
						this->set_state( TERMINATE_CHAR_LITERAL );
						}
					break;
				case ISSPACE:
					//Of the whitspace chars, we can only have the space character (20 hex) 
					//in a 'A' character format.
					if( c == ' ' )
						{
						add_to_cbuf( c );

						//Change state:
						this->set_state( TERMINATE_CHAR_LITERAL );
						}
					else
						{
						//Non-graphic characters have to be done using escape sequences.
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: GENERAL_CHAR_LITERAL: case ISSPACE" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	

/*
						//If this is a newline, increment line number counter:
						if( c == '\n' )						
							{
							this->line_num++;
							//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
							}
*/

						break;
						}						
					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == TERMINATE_CHAR_LITERAL )	//We are looking for a terminating single quote only.
			{												//The only valid character at this point is a .
			switch( type )									//single quote.
				{
				case ISALPHA:
					//Non-single-quote characters are not allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: TERMINATE_CHAR_LITERAL: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//Non-single-quote characters are not allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: TERMINATE_CHAR_LITERAL: case ISDIGIT" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISPUNCT:
					if( c == '\'' )
						{
						//This is the only valid character at this point.
						add_to_cbuf( c );

						//We are now moving out of terminate_char_literal.

						//Create, load, and add-to-list a Token object:
						token_type = CHARACTER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );
						
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 

						//Reset cbuf items:
						this->reset_cbuf();
						}
					else
						{
						//*****ALL OTHERS ARE INVALID*****
						//Any punctuation other than a closing single quote is not allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: TERMINATE_CHAR_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//Any punctuation other than a closing single quote is not allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: TERMINATE_CHAR_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
/*					
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/
					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == ESCAPE_CHAR_LITERAL )	//We have encountered a '\' 
			{											
			switch( type )								
				{
				case ISALPHA:
					//Handle non-graphic character escape sequence cases:
					if( (c=='n') || (c=='t') || (c=='v') || (c=='b') || (c=='r') || (c=='f') || (c=='a') )
						{
						//Save this character, then the only valid character will be a single quote:
						add_to_cbuf( c );

						//Change state:
						this->set_state( TERMINATE_CHAR_LITERAL );
						}
					else if( c == 'x' )
						{
						//This is a hexadecimal escape sequence.
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( HEX_ESC_1ST_CHAR_LITERAL );
						}
					else
						{
						//No other alpha chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ESCAPE_CHAR_LITERAL: case ISALPHA" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISDIGIT:
					//We may have an octal escape sequence, where '8' and '9' are not valid octal characters
					//and 377 is the highest allowed value (255 dec):
					//For a leading 0-->3, we can have up to three octal digits:
					if( (c=='0') || (c=='1') || (c=='2') || (c=='3') )
						{
						//This is an octal escape sequence.
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( OCT_ESC_2ND_CHAR_LITERAL );						
						}
					//For a leading 4-->7, we can have up to two octal digits:
					else if( (c=='4') || (c=='5') || (c=='6') || (c=='7') )
						{
						//This is an octal escape sequence.
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( OCT_ESC_LAST_CHAR_LITERAL );						
						}

					else
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ESCAPE_CHAR_LITERAL: case ISDIGIT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISPUNCT:
					//[Why are '?' and '"' in this list??]
					if( (c=='\\') || (c=='?') || (c=='\'') || (c=='"') )
						{
						//Save this character, then the only valid character will be a single quote:
						add_to_cbuf( c );

						//Change state:
						this->set_state( TERMINATE_CHAR_LITERAL );
						}
					else
						{
						//*****ALL OTHER PUNCTUATION MARKS ARE INVALID******
						//No other punctuation chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ESCAPE_CHAR_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//No white space is allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ESCAPE_CHAR_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
/*
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == HEX_ESC_1ST_CHAR_LITERAL )	//We have encountered a '\x
			{											
			switch( type )								
				{
				case ISALPHA:
					//Handle hexadecimal alpha characters:
					if( (c=='a') || (c=='A') || (c=='b') || (c=='B') || (c=='c') || (c=='C') || (c=='d') ||
						(c=='D') || (c=='e') || (c=='E') || (c=='f') || (c=='F') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( HEX_ESC_2ND_CHAR_LITERAL );
						}
					else
						{
						//No other alpha chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: HEX_ESC_1ST_CHAR_LITERAL: case ISALPHA" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISDIGIT:
					//Handle hexadecimal digit characters:
					//Save this character:
					add_to_cbuf( c );

					//Change state:
					this->set_state( HEX_ESC_2ND_CHAR_LITERAL );						
					break;
				case ISPUNCT:
					//*******ALL PUNCTUATION IS INVALID HERE********
					//No punctuation chars are allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ESCAPE_CHAR_LITERAL: case ISPUNCT" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISSPACE:
					//No white space is allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: ESCAPE_CHAR_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
/*
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == HEX_ESC_2ND_CHAR_LITERAL )	//We have encountered one hex escape char so far.
			{												// '\x9   for example.									
			switch( type )								
				{
				case ISALPHA:
					//Handle hexadecimal alpha characters:
					if( (c=='a') || (c=='A') || (c=='b') || (c=='B') || (c=='c') || (c=='C') || (c=='d') ||
						(c=='D') || (c=='e') || (c=='E') || (c=='f') || (c=='F') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						//Only a terminating single quote will be allowed now:
						this->set_state( TERMINATE_CHAR_LITERAL );
						}
					else
						{
						//No other alpha chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: HEX_ESC_1ST_CHAR_LITERAL: case ISALPHA" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISDIGIT:
					//Handle hexadecimal digit characters:
					//Save this character:
					add_to_cbuf( c );

					//Change state:
					//Only a terminating single quote will be allowed now:
					this->set_state( TERMINATE_CHAR_LITERAL );
					break;
				case ISPUNCT:
					//Now that we have one hex char, a terminating single quote is the 
					//only punct char allowed here:
					if( c == '\'' )
						{
						//This is the only valid punct character at this point.
						add_to_cbuf( c );

						//We are now moving out of hex_esc_2nd_char_literal.	- HEX

						//Create, load, and add-to-list a Token object:
						token_type = CHARACTER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );
						
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 

						//Reset cbuf items:
						this->reset_cbuf();
						}					
					else
						{
						//********ALL OTHER PUNCT IS INVALID AT THIS POINT*******
						//No other punctuation chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:HEX_ESC_2ND_CHAR_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//No white space is allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: HEX_ESC_2ND_CHAR_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
/*
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == OCT_ESC_2ND_CHAR_LITERAL )	//We have encountered a '\[0-3]
			{												//ie, we have the 1st octal character already,
			switch( type )									//with a potential for a total of three.
				{
				case ISALPHA:
					//No alpha chars are allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:OCT_ESC_2ND_CHAR_LITERAL: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//We have an octal escape sequence, where '8' and '9' are not valid octal characters
					//and 377 is the highest allowed value (255 dec):						
					if( (c!='8') && (c!='9') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( OCT_ESC_LAST_CHAR_LITERAL );						
						}
					else
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:OCT_ESC_2ND_CHAR_LITERAL: case ISDIGIT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISPUNCT:
					//Now that we have one octal char, a terminating single quote is the 
					//only punct char allowed here:
					if( c == '\'' )
						{
						//This is the only valid punct character at this point.
						add_to_cbuf( c );

						//We are now moving out of oct_esc_2nd_char_literal.

						//Create, load, and add-to-list a Token object:
						token_type = CHARACTER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );
						
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 

						//Reset cbuf items:
						this->reset_cbuf();
						}					
					else
						{
						//*******ALL OTHER PUNCT IS INVALID AT THIS POINT*********
						//No other punctuation chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: OCT_ESC_2ND_CHAR_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");		
						}
					break;
				case ISSPACE:
					//No white space is allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: OCT_ESC_2ND_CHAR_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
/*
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == OCT_ESC_LAST_CHAR_LITERAL ) //We have encountered either '\[0-3][0-7]
			{												 //or '\[4-7] previously. This is the last char for
			switch( type )									 //this octal escape sequence.
				{
				case ISALPHA:
					//No alpha chars are allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:OCT_ESC_LAST_CHAR_LITERAL: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//We have an octal escape sequence, where '8' and '9' are not valid octal characters
					//and 377 is the highest allowed value (255 dec):						
					if( (c!='8') && (c!='9') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( TERMINATE_CHAR_LITERAL );						
						}
					else
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:OCT_ESC_LAST_CHAR_LITERAL: case ISDIGIT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISPUNCT:
					//Now that we have at least one octal char, a terminating single quote is the 
					//only punct char allowed here:
					if( c == '\'' )
						{
						//This is the only valid punct character at this point.
						add_to_cbuf( c );

						//We are now moving out of oct_esc_2nd_char_literal. -OCT

						//Create, load, and add-to-list a Token object:
						token_type = CHARACTER_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );
						
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 

						//Reset cbuf items:
						this->reset_cbuf();
						}					
					else
						{
						//********ALL OTHER PUNCTUATION IS INVALID HERE*******
						//No other punctuation chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: OCT_ESC_LAST_CHAR_LITERAL: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");		
						}
					break;
				case ISSPACE:
					//No white space is allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: OCT_ESC_LAST_CHAR_LITERAL: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	

/*
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == GENL_STRING_LITERAL ) //We have encountered a  "
			{												 
			switch( type )									 
				{
				case ISALPHA:
					//All alpha chars are okay:
					add_to_cbuf( c );
					break;
				case ISDIGIT:
					//All digit chars are okay:
					add_to_cbuf( c );
  					break;
				case ISPUNCT:
					//***ALL PUNCT IS HANDLED HERE ALREADY****
					//All punctuation chars are okay, except for special handling of '\', '"':
					if( (c!='\\') && (c!='"') )
						{
						add_to_cbuf( c );
						}
					else
						{
						if( c == '\\' )
							{
							//We have an escape sequence:
							add_to_cbuf( c );

							//Change State:
							this->set_state( STRING_LITERAL_ESC_SEQ );
							}
						else if( c == '"' )
							{
							//This is the end-of-string marker. We will have to look at
							//next character to determine if this is the end of the current
							//token, since we are going to leave adjacent string literals 
							//within one token:
							add_to_cbuf( c );

							//Change State:
							this->set_state( STRING_LITERAL_END_CHECK );
							}
						}
					break;
				case ISSPACE:
					//Of the whitspace chars, we can only have the space character (20 hex) 
					//in a string literal.
					if( c == ' ' )
						{
						add_to_cbuf( c );
						}
					else
						{
						//No non-graphic whitespace chars are allowed in the string literal, except
						//if represented by escape sequences:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:GENL_STRING_LITERAL: case ISSPACE" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
/*
						//If this is a newline, increment line number counter:
						if( c == '\n' )						
							{
							this->line_num++;
							//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
							}
*/

						}		
					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}
				   					  
		if( this->get_state() == STRING_LITERAL_END_CHECK ) //We have encountered a  "  while inside
			{												//of a string literal. This may or may not 
			switch( type )									//be the terminator of the string literal. 
				{
				case ISALPHA:
					//No alpha chars are allowed here:
					if( compiler_debug_state == DEBUG_ON ) cout << "An error occurred in state:STRING_LITERAL_END_CHECK: case ISALPHA" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISDIGIT:
					//No numeric chars are allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:STRING_LITERAL_END_CHECK: case ISDIGIT" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
  					break;
				case ISPUNCT:						
					//TERM&SAVE TOKEN;SAVE CHAR ON: ; ) , 
					//					   INVALID: < > / . ' " \ : ~ { } ( [ ] = + - | ^ & * %
					
					//Handle the case of consecutive '"' characters:
					if( c == '"' )
						{
						//This is a consecutive '"'. Thus we will stay in this token and let the parser
						//do the concatenation.
						add_to_cbuf( c );
																						
						//Change State:
						this->set_state( GENL_STRING_LITERAL );
						}
					//The following are the token-terminating chars and are themseleves	tokens. 
 					//Write the current cbuf to the token list, reset cbuf, then
					//add the current char/token to the token list. Then move to the 
					//appropriate state (usually OUTALL: OUTside of ALL tokens).
					else if( (c==';') || (c==')') || (c==',') )
						{

						//Create, load, and add-to-list a Token object:
						token_type = STRING_LITERAL;
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
																			   
						//Load the punct char:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
											
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}					
					else
						{
						//All other punctiation is considered invalid:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:STRING_LITERAL_END_CHECK: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//Terminate the string literal on any whitespace:
					//We are now moving out of the token:

					//Create, load, and add-to-list a Token object:
					token_type = STRING_LITERAL;
					this->addTokenToList( this->cbuf, token_type, this->line_num );
					
					//Change state:
					this->set_state( OUTALL );

					//Reset cbuf items:
					this->reset_cbuf();

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}

		if( this->get_state() == STRING_LITERAL_ESC_SEQ ) //We have encountered a  \  while inside
			{											  //of a string literal. Handle this escape
			switch( type )								  //sequence as is done for character literals,
				{										  //but without the single quotes.
				case ISALPHA:
					//Handle non-graphic character escape sequence cases:
					if( (c=='n') || (c=='t') || (c=='v') || (c=='b') || (c=='r') || (c=='f') || (c=='a') )
						{
						//Save this character. Then the next character can be any general character:
						add_to_cbuf( c );
						
						//Change state:
						this->set_state( GENL_STRING_LITERAL );
						}
					else if( c == 'x' )
						{
						//This is a hexadecimal escape sequence.
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_HEX_ESC_1ST_CHAR );
						}
					else
						{
						//No other alpha chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_ESC_SEQ: case ISALPHA" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISDIGIT:
					//We may have an octal escape sequence, where '8' and '9' are not valid octal characters
					//and 377 is the highest allowed value (255 dec):
					//For a leading 0-->3, we can have up to three octal digits:
					if( (c=='0') || (c=='1') || (c=='2') || (c=='3') )
						{
						//This is an octal escape sequence.
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_OCT_ESC_2ND_CHAR );						
						}
					//For a leading 4-->7, we can have up to two octal digits:
					else if( (c=='4') || (c=='5') || (c=='6') || (c=='7') )
						{
						//This is an octal escape sequence.
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_OCT_ESC_LAST_CHAR );						
						}

					else
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_ESC_SEQ: case ISDIGIT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISPUNCT:
					if( (c=='\\') || (c=='?') || (c=='\'') || (c=='"') )
						{
						//Save this character, then any general char literal character can follow:
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL );
						}
					else
						{
						//******ALL OTHER PUNCTUATION IS INVALID HERE******
						//No other punctuation chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_ESC_SEQ: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//No white space is allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_ESC_SEQ: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	

/*
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop					

	 		}
		
		//NOTE: THIS STATE IS THE SAME AS THE HEX_ESC_1ST_CHAR_LITERAL STATE!
		if( this->get_state() == STRING_LITERAL_HEX_ESC_1ST_CHAR )	//We have encountered a \x
			{											
			switch( type )								
				{
				case ISALPHA:
					//Handle hexadecimal alpha characters:
					if( (c=='a') || (c=='A') || (c=='b') || (c=='B') || (c=='c') || (c=='C') || (c=='d') ||
						(c=='D') || (c=='e') || (c=='E') || (c=='f') || (c=='F') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_HEX_ESC_2ND_CHAR );
						}
					else
						{
						//No other alpha chars are allowed here:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_HEX_ESC_1ST_CHAR: case ISALPHA" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISDIGIT:
					//Handle hexadecimal digit characters:
					//Save this character:
					add_to_cbuf( c );

					//Change state:
					this->set_state( STRING_LITERAL_HEX_ESC_2ND_CHAR );						
					break;
				case ISPUNCT:
					//******ALL PUNCT IS INVALID HERE******
					//No punctuation chars are allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_HEX_ESC_1ST_CHAR: case ISPUNCT" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISSPACE:
					//No white space is allowed here:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_HEX_ESC_1ST_CHAR: case ISSPACE" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	

/*
					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}
*/

					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == STRING_LITERAL_HEX_ESC_2ND_CHAR )	//We have encountered one hex escape char so far.
			{											
			switch( type )								
				{
				case ISALPHA:
					//Handle hexadecimal alpha characters:
					if( (c=='a') || (c=='A') || (c=='b') || (c=='B') || (c=='c') || (c=='C') || (c=='d') ||
						(c=='D') || (c=='e') || (c=='E') || (c=='f') || (c=='F') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Change state:
						//We need to make sure that there isn't another hex char following this, as
						//it would be ambiguous:
						this->set_state( CHECK_NO_HEX_CHAR );
						}
					else
						{
						//We already have one hex char, so any other alpha terminates the hex escape:
						//Save this character:
						add_to_cbuf( c );

						this->set_state( GENL_STRING_LITERAL );
						
						}
					break;
				case ISDIGIT:
					//Handle hexadecimal digit characters:
					//Save this character:
					add_to_cbuf( c );

					//Change state:
					//We need to make sure that there isn't another hex char following this, as
					//it would be ambiguous:
					this->set_state( CHECK_NO_HEX_CHAR );
					break;
				case ISPUNCT:
					//*******ALL PUNCT CASES HAVE BEEN HANDLED*****
					//Now that we have one hex char, we can accept any punctuation:
					if( c == '\\' )
						{
						//We are immediately starting another escape sequence:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_ESC_SEQ ); 
						}
					else if( c == '"' )
						{
						//This is the end-of-string marker. We will have to look at
						//next character to determine if this is the end of the current
						//token, since we are going to leave adjacent string literals 
						//within one token:
						add_to_cbuf( c );

						//Change State:
						this->set_state( STRING_LITERAL_END_CHECK );
						}
					else
						{
						//Add char to cbuf and continue with string literal processing:
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL ); 						
						}														 
					break;
				case ISSPACE:
					//Only the space(' ') character is allowable:
					if( c == ' ' )
						{
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL );
						}
					else
						{
						//Non-graphic characters have to be done using escape sequences:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: STRING_LITERAL_HEX_ESC_2ND_CHAR: case ISSPACE" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
/*
						//If this is a newline, increment line number counter:
						if( c == '\n' )						
							{
							this->line_num++;
							//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
							}
*/

						break;
						}					
					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}
		
		if( this->get_state() == CHECK_NO_HEX_CHAR )	//Make sure that no hex char is entered here.
			{											
			switch( type )								
				{
				case ISALPHA:
					//Handle hexadecimal alpha characters:
					if( (c=='a') || (c=='A') || (c=='b') || (c=='B') || (c=='c') || (c=='C') || (c=='d') ||
						(c=='D') || (c=='e') || (c=='E') || (c=='f') || (c=='F') )
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: CHECK_NO_HEX_CHAR: case ISALPHA" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					else
						{
						//Character is okay. Save this character:
						add_to_cbuf( c ); 

						//Change state: Continue processing of string literal:
						this->set_state( GENL_STRING_LITERAL );
						}
					break;
				case ISDIGIT:
					//No digits are allowed in this posaition:
					if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: CHECK_NO_HEX_CHAR: case ISDIGIT" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				case ISPUNCT:
					//*******ALL PUNCT CASES HANDLED*******
					//We can accept any punctuation:
					if( c == '\\' )
						{
						//We are immediately starting another escape sequence:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_ESC_SEQ ); 
						}
					else if( c == '"' )
						{
						//This is the end-of-string marker. We will have to look at
						//next character to determine if this is the end of the current
						//token, since we are going to leave adjacent string literals 
						//within one token:
						add_to_cbuf( c );

						//Change State:
						this->set_state( STRING_LITERAL_END_CHECK );
						}
					else
						{
						//Add char to cbuf and continue with string literal processing:
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL ); 						
						}
					break;
				case ISSPACE:
					//Only the space(' ') character is allowable:
					if( c == ' ' )
						{
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL );
						}
					else
						{
						//Non-graphic characters have to be done using escape sequences:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state: CHECK_NO_HEX_CHAR: case ISSPACE" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
/*
						//If this is a newline, increment line number counter:
						if( c == '\n' )						
							{
							this->line_num++;
							//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
							}
*/
						break;
						}					
					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}
		
		//Note: In the HEX escape sequences, if there is a 3rd character that could be interpreted as a
		//hex digit, the C++ compiler gives an error. In the OCT escape sequences, however, after the max 
		//allowed three characters, subsequent characters that could be interpreted as octal are allowed.
		//In this compiler, after the third (or last) octal char is received, we go to general string
		//literal processing, and allow possible octal chars, as the C++ compiler does.
		if( this->get_state() == STRING_LITERAL_OCT_ESC_2ND_CHAR )	//We have encountered a \[0-3]
			{												        //ie, we have the 1st octal character already,
			switch( type )									        //with a potential for a total of three.
				{
				case ISALPHA:
					//We already have one oct char, so any alpha terminates the oct escape:
					//Save this character:
					add_to_cbuf( c );

					//Change State:
					this->set_state( GENL_STRING_LITERAL );
					break;
				case ISDIGIT:
					//We have an octal escape sequence, where '8' and '9' are not valid octal characters
					//and 377 is the highest allowed value (255 dec):						
					if( (c!='8') && (c!='9') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Change State:
						this->set_state( STRING_LITERAL_OCT_ESC_LAST_CHAR );
						}						
					else
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:STRING_LITERAL_OCT_ESC_2ND_CHAR: case ISDIGIT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISPUNCT:
					//*******ALL PUNCT CASES ARE HANDLED HERE******
					//Now that we have one oct char, we can accept any punctuation:
					if( c == '\\' )
						{
						//We are immediately starting another escape sequence:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_ESC_SEQ ); 
						}
					else if( c == '"' )
						{
						//This is the end-of-string marker. We will have to look at
						//next character to determine if this is the end of the current
						//token, since we are going to leave adjacent string literals 
						//within one token:
						add_to_cbuf( c );

						//Change State:
						this->set_state( STRING_LITERAL_END_CHECK );
						}
					else
						{
						//Add char to cbuf and continue with string literal processing:
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL ); 						
						}
				case ISSPACE:
					//Only the space(' ') character is allowable:
					if( c == ' ' )
						{
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL );
						}
					else
						{
						//Non-graphic characters have to be done using escape sequences:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:STRING_LITERAL_OCT_ESC_2ND_CHAR : case ISSPACE" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
/*
						//If this is a newline, increment line number counter:
						if( c == '\n' )						
							{
							this->line_num++;
							//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
							}
*/

						break;
						}					
					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == STRING_LITERAL_OCT_ESC_LAST_CHAR )	//We have encountered a \[0-3][0-3]
			{												        //ie, we have the 1st two octal characters already,
			switch( type )									        //with a potential for a total of three.
				{
				case ISALPHA:
					//We already have two oct char, so any alpha terminates the oct escape:
					//Save this character:
					add_to_cbuf( c );

					//Change State:
					this->set_state( GENL_STRING_LITERAL );
					break;
				case ISDIGIT:
					//We have an octal escape sequence, where '8' and '9' are not valid octal characters
					//and 377 is the highest allowed value (255 dec):						
					if( (c!='8') && (c!='9') )
						{
						//Save this character:
						add_to_cbuf( c );

						//Since this is the last octal char, change state for general processing:
						this->set_state( GENL_STRING_LITERAL );
						}
					else
						{
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:STRING_LITERAL_OCT_ESC_LAST_CHAR: case ISDIGIT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISPUNCT:
					//*********ALL PUNCT CHARS ARE HANDLED HERE********
					//Now that we have one oct char, we can accept any punctuation:
					if( c == '\\' )
						{
						//We are immediately starting another escape sequence:
						add_to_cbuf( c );

						//Change state:
						this->set_state( STRING_LITERAL_ESC_SEQ ); 
						}
					else if( c == '"' )
						{
						//This is the end-of-string marker. We will have to look at
						//next character to determine if this is the end of the current
						//token, since we are going to leave adjacent string literals 
						//within one token:
						add_to_cbuf( c );

						//Change State:
						this->set_state( STRING_LITERAL_END_CHECK );
						}
					else
						{
						//Add char to cbuf and continue with string literal processing:
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL ); 						
						}
				case ISSPACE:
					//Only the space(' ') character is allowable:
					if( c == ' ' )
						{
						add_to_cbuf( c );

						//Change state:
						this->set_state( GENL_STRING_LITERAL );
						}
					else
						{
						//Non-graphic characters have to be done using escape sequences:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:STRING_LITERAL_OCT_ESC_LAST_CHAR : case ISSPACE" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
/*
						//If this is a newline, increment line number counter:
						if( c == '\n' )						
							{
							this->line_num++;
							//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
							}
*/
						break;
						}					
					break;				
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}

			continue;	//Go to next iteration of the while loop

	 		}

		
		if( this->get_state() == DOUBLE_COLON_CHECK ) //We have encountered a  : and want to 
			{										  //determine if it is a token by itself,
			switch( type )							  //or if has a following :, which would make 
				{									  //it a '::' token.
				case ISALPHA:
					//Save the ':' as a token and proceed:
					//':' is a valid token terminator, and is itself a token.					
					//Store the ':' token:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the alpha char:
					add_to_cbuf( c );
									
					//Change state (We are now entering an IDENTIFIER_STATE):
					this->set_state( IDENTIFIER_STATE ); 
					break;
				case ISDIGIT:
					//Save the ':' as a token and proceed:
					//':' is a valid token terminator, and is itself a token.
					//Store the ':' token:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the digit char:					
					//NOTE: A DIGIT FOLLOWING A ':' IS PROBABLY NOT SYNTACTICALLY ALLOWED!!!:
					//Change state according to digit value:
					if( c == '0' )
						{
						//Not a floating point literal:
						this->set_state( GENL_INT_LITERAL_LEAD_0 );
						add_to_cbuf( c );	
						}
					else	//1-->9
						{
						//May be an int or float:
						this->set_state( GENL_NUM_LITERAL );
						add_to_cbuf( c );
						}

  					break;
				case ISPUNCT:
					//Only another ':' is allowed at this point:					
					if( c == ':' )
						{
						//We now have a '::' which is a valid token:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
										
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}
					else
						{
						//*****ALL OTHER PUNCT IS INVALID******
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:DOUBLE_COLON_CHECK: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//A whitespace terminates the token. Thus ':' is the token to be saved:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();
				    
					//Change State: We are now outside of any token:
					this->set_state( OUTALL );

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}

		
		//NOTE: THIS CODE IS IDENTICAL TO DOUBLE_LT_CHECK
		if( this->get_state() == DOUBLE_LT_CHECK ) //We have encountered a  < and want to 
			{										  //determine if it is a token by itself,
			switch( type )							  //or if it has a following <, which would make 
				{									  //it a '<<' token.
				case ISALPHA:
					//Save the '<' as a token and proceed:
					//'<' is a valid token terminator, and is itself a token.				
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the alpha char:
					add_to_cbuf( c );
									
					//Change state (We are now entering an identifier):
					this->set_state( IDENTIFIER_STATE ); 
					break;
				case ISDIGIT:
					//Save the '<' as a token and proceed:
					//'<' is a valid token terminator, and is itself a token.
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the digit char:					
					//Change state according to digit value:
					if( c == '0' )
						{
						//Not a floating point literal:
						this->set_state( GENL_INT_LITERAL_LEAD_0 );
						add_to_cbuf( c );	
						}
					else	//1-->9
						{
						//May be an int or float:
						this->set_state( GENL_NUM_LITERAL );
						add_to_cbuf( c );
						}

  					break;
				case ISPUNCT:
					//Only another '<' is allowed at this point:					
					if( c == '<' )
						{
						//We now have a '<<' which is a valid token:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
										
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}
					else
						{
						//*******ALL OTHER PUNCT CASES ARE INVALID*********
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:DOUBLE_LT_CHECK: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//A whitespace terminates the token. Thus '<' is the token to be saved:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();
				    
					//Change State: We are now outside of any token:
					this->set_state( OUTALL );

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}

	
		//NOTE: THIS CODE IS IDENTICAL TO DOUBLE_LT_CHECK
		if( this->get_state() == DOUBLE_GT_CHECK ) //We have encountered a  > and want to 
			{										  //determine if it is a token by itself,
			switch( type )							  //or if it has a following >, which would make 
				{									  //it a '>>' token.
				case ISALPHA:
					//Save the '>' as a token and proceed:
					//'>' is a valid token terminator, and is itself a token.					
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the alpha char:
					add_to_cbuf( c );
									
					//Change state (We are now entering an identifier):
					this->set_state( IDENTIFIER_STATE ); 
					break;
				case ISDIGIT:
					//Save the '>' as a token and proceed:
					//'>' is a valid token terminator, and is itself a token.
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the digit char:					
					//Change state according to digit value:
					if( c == '0' )
						{
						//Not a floating point literal:
						this->set_state( GENL_INT_LITERAL_LEAD_0 );
						add_to_cbuf( c );	
						}
					else	//1-->9
						{
						//May be an int or float:
						this->set_state( GENL_NUM_LITERAL );
						add_to_cbuf( c );
						}

  					break;
				case ISPUNCT:
					//Only another '>' is allowed at this point:					
					if( c == '>' )
						{
						//We now have a '>>' which is a valid token:
						add_to_cbuf( c );
						//Check token type:
						if( isOper(cbuf) )
							token_type = OPERATOR;
						else
							token_type = PUNCTUATOR;

						//Create, load, and add-to-list a Token object:
						this->addTokenToList( this->cbuf, token_type, this->line_num );

						//Reset cbuf items:
						this->reset_cbuf();
										
						//Change state (We are now outside of any token):
						this->set_state( OUTALL ); 
						}
					else
						{
						//*******ALL OTHER PUNCT IS INVALID***********
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:DOUBLE_GT_CHECK: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//A whitespace terminates the token. Thus '>' is the token to be saved:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();
				    
					//Change State: We are now outside of any token:
					this->set_state( OUTALL );

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}

		
		if( this->get_state() == COMMENT_CHECK ) //We have encountered a  / and want to 
			{								     //determine if it is a divide operator or the 
			switch( type )						 //beginning of a C or C++ comment.
				{
				case ISALPHA:
					//Save the '/' divide operator as a token and proceed:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the current alpha char:
					add_to_cbuf( c );
									
					//Change state (We are now entering an identifier):
					this->set_state( IDENTIFIER_STATE ); 
					break;
				case ISDIGIT:
					//Save the '/' as a token and proceed:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();

					//Start a new token with the digit char:					
					//Change state according to digit value:
					if( c == '0' )
						{
						//Not a floating point literal:
						this->set_state( GENL_INT_LITERAL_LEAD_0 );
						add_to_cbuf( c );	
						}
					else	//1-->9
						{
						//May be an int or float:
						this->set_state( GENL_NUM_LITERAL );
						add_to_cbuf( c );
						}

  					break;
				case ISPUNCT:
					//Only certain punct chars are allowed here:
					if( c == '*' )
						{
						//We are now entering a C-style comment. All characters will be 
						//thrown away until a '*/' is encountered.
						//Since we are in a comment, we want to clear the cbuf of its '/':
						//Reset cbuf items:
						this->reset_cbuf();
										
						//Change state:
						this->set_state( IN_C_COMMENT ); 
						}
					else if( c == '/' )
						{
						//We are now entering a C++-style comment. All characters will be 
						//thrown away until a '\n' is encountered.
						//Since we are in a comment, we want to clear the cbuf of its '/':
						//Reset cbuf items:
						this->reset_cbuf();
										
						//Change state:
						this->set_state( IN_CPP_COMMENT ); 
						}
					else
						{
						//********ALL OTHER PUNCT IS INVALID*********
						//We are not going to support '/=' here, since it is not in the OMG spec.
						//However we could add that support here.
						//All other punct chars are an error:
						if( compiler_debug_state == DEBUG_ON )cout << "An error occurred in state:COMMENT_CHECK: case ISPUNCT" << endl;
						lexer_error_handler(filename, line_num, "Unexpected char");	
						}
					break;
				case ISSPACE:
					//A whitespace terminates the token. Thus '/' is the token to be saved:
					//Check token type:
					if( isOper(cbuf) )
						token_type = OPERATOR;
					else
						token_type = PUNCTUATOR;

					//Create, load, and add-to-list a Token object:
					this->addTokenToList( this->cbuf, token_type, this->line_num );

					//Reset cbuf items:
					this->reset_cbuf();
				    
					//Change State: We are now outside of any token:
					this->set_state( OUTALL );

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}

		
		if( this->get_state() == IN_C_COMMENT ) //We will discard all chars while in the comment.
			{								    //We are only interested in the '*' which can  
			switch( type )						//possibly terminate the comment.
				{
				case ISALPHA:
					//Throw away the alpha character.
					if( compiler_debug_state == DEBUG_ON )cout << "Ignoring alpha char..." << endl;
					break;
				case ISDIGIT:
					//Throw away the numeric character.
					if( compiler_debug_state == DEBUG_ON )cout << "Ignoring digit char..." << endl;
  					break;
				case ISPUNCT:
					//********ALL PUNCT CASES ARE HANDLED HERE********
					//Only the '*' character is of concern here:
					if( c == '*' )
						{
						//This may terminate the C-style comment. We don't need to 
						//save the '*' since it is part of the comment in any case:
						//Change state:
						this->set_state( C_COMMENT_TERMINATE_CHECK ); 
						}
					else
						{
						//Throw away the punct character.
						if( compiler_debug_state == DEBUG_ON )cout << "Ignoring punct char..." << endl;
						}
					break;
				case ISSPACE:
					//Throw away the whitesapce character.

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}


		if( this->get_state() == C_COMMENT_TERMINATE_CHECK ) //Check if the C-style comment is actually
			{												 //terminated. We already have a '*' and 
			switch( type )									 //are now looking for a '/'. Any other char
				{											 //means the '*' was just part of the comment. 
				case ISALPHA:
					//Throw away the alpha character.
					//Comment is not terminated:
					//Change state:
					this->set_state( IN_C_COMMENT ); 
					break;
				case ISDIGIT:
					//Throw away the numeric character.
					//Comment is not terminated:
					//Change state:
					this->set_state( IN_C_COMMENT );
  					break;
				case ISPUNCT:
					//******ALL PUNCT IS HANDLED HERE********
					if( c == '*' )
						{
						//Again, this may terminate the C-style comment. We don't need to 
						//save the '*' since it is part of the comment in any case:
						//Change state (actually, stay in this state):
						this->set_state( C_COMMENT_TERMINATE_CHECK ); 
						}
					else if( c == '/' )
						{
						//This terminates the C-style comment. We are now outside of
						//all tokens.
						//Change state:
						this->set_state( OUTALL ); 
						}
					else
						{
						//Throw away the punct character.
						//Comment is not terminated:
						this->set_state( IN_C_COMMENT );
						}
					break;
				case ISSPACE:
					//Throw away the whitesapce character.
					//Comment is not terminated:
					//Change state:
					this->set_state( IN_C_COMMENT );

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					if( compiler_debug_state == DEBUG_ON )cout << "ISUNKNOWN" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}

		
		if( this->get_state() == IN_CPP_COMMENT ) //We will discard all chars while in the comment.
			{								      //We are only interested in the '\n' which 
			switch( type )						  //terminates the CPP comment.
				{
				case ISALPHA:
					//Throw away the alpha character.
    				if( compiler_debug_state == DEBUG_ON )cout << "Ignoring alpha char..." << endl;
					break;
				case ISDIGIT:
					//Throw away the numeric character.
					if( compiler_debug_state == DEBUG_ON )cout << "Ignoring digit char..." << endl;
  					break;
				case ISPUNCT:
					//*******ALL PUNCT IS HANDLED HERE********
					//Throw away the punct character.
					if( compiler_debug_state == DEBUG_ON )cout << "Ignoring digit char..." << endl;
  					break;
				case ISSPACE:
					//We are concerned only with the newline character:
					if( c == '\n' )
						{
						//This terminates the C++-style comment. We are now outside of
						//all tokens.
						//Change state:
						this->set_state( OUTALL );
						}
					else
						{
						//Throw away the whitesapce character.
						}

					//If this is a newline, increment line number counter:
					if( c == '\n' )						
						{
						this->line_num++;
						//if( compiler_debug_state == DEBUG_ON )cout << "line_num= " << line_num << endl;
						}

					break;
				case ISUNKNOWN:
					//Throw away the unknown characters in comments.
					if( compiler_debug_state == DEBUG_ON )cout << "Ignoring unknown char in comment..." << endl;
					break;
				default:
					if( compiler_debug_state == DEBUG_ON )cout << "default????" << endl;
					lexer_error_handler(filename, line_num, "Unexpected char");	
				}
 
			continue;	//Go to next iteration of the while loop

	 		}


	


		} //end of while-loop

	//DEMO OP: Traverse the Token list, displaying items as we go:
	this->traverseTokenList();

	
	return;

}


/*
 * char_type()
 * 
 * Determine the character's type.
 */
int LexicalAnalyzer::char_type( int ch ) 
{
	/*
	 *  ???? 
	 *  Only call isalpha when ch > 0 because for some
	 *  negative values isalpha will return True.
	 *  The same is true for ispunct
	 *  ????
	 */
	if( (ch > 0) && (isalpha(ch)) )
		return( ISALPHA );
	else if( isdigit(ch) )
		return( ISDIGIT );
	else if( (ch > 0) && (ispunct(ch)) )
		return( ISPUNCT );
	else if( isspace(ch) )
		return( ISSPACE );
	else
		return( ISUNKNOWN );

}


/*
 * reset_cbuf()
 * 
 * Reset the temporary character buffer cbuf:
 */
void LexicalAnalyzer::reset_cbuf() 
{

	//Reset cbuf items:
	this->cbuf_pos = 0;
	memset( this->cbuf, '\0', 63 );
	
	
	return;

}


/*
 * add_to_cbuf()
 * 
 * Add a character to the temporary character buffer cbuf:
 */
void LexicalAnalyzer::add_to_cbuf( char ch ) 
{

	//Add character ch to cbuf and increment position index:
	this->cbuf[cbuf_pos] = ch;
	this->cbuf_pos++;
	
	
	return;

}



/*
 * set_state()
 * 
 * Set the FSM state.
 */
void LexicalAnalyzer::set_state( const int state_arg ) 
{

	//Set the current state of the FSM:
	
	this->state = state_arg;
	
	return;

}


/*
 * get_state()
 * 
 * Return the current FSM state.
 */
const int LexicalAnalyzer::get_state() 
{

	//Return the current state of the FSM:
	return( this->state );
	
}


/*
 * isOper()
 * 
 * If arg is an OPERATOR, return TRUE, if it is a PUNCTUATOR, return FALSE.
 */
int LexicalAnalyzer::isOper( char *arg ) 
{
	if( !(strcmp( arg, ";" )) || !(strcmp( arg, "{" )) || !(strcmp( arg, "}" )) || 
		!(strcmp( arg, ":" )) || !(strcmp( arg, "::" )) || !(strcmp( arg, "'" )) ||
		!(strcmp( arg, "\"" )) || !(strcmp( arg, "\\" )) )
		return( FALSE );
	else
		return( TRUE );
	
}


/*
 * isKeyword()
 * 
 * If arg is a KEYWORD, return TRUE, if it is a plain IDENTIFIER, return FALSE.
 * Unless: If the arg appears to be a keyword but has a case mismatch ('boolean' 
 * vs. 'Boolean', or "TRUE" vs. 'True' eg), then it is not an IDENTIFIER or 
 * a KEYWORD, and this generates a compilation error.
 */
int LexicalAnalyzer::isKeyword( char *arg ) 
{
	char	*temp_arg;
	int		i, length;

	
	//Allocate storage for temp_arg:
	temp_arg = new char[strlen(arg)+1];

	//Make an all upper-case version of arg:
	length = strlen( arg );

	//if( compiler_debug_state == DEBUG_ON )cout << "length= " << length << endl;

	//This loop will also copy the '\0' terminator:
	for( i=0 ; i<length+1 ; i++ )
		{
		*(temp_arg+i) = toupper( *(arg+i) );
		}

	//Check if arg is an outright keyword:
	if( !(strcmp( arg, "any" )) || !(strcmp( arg, "attribute" )) || !(strcmp( arg, "boolean" )) || 
		!(strcmp( arg, "case" )) || !(strcmp( arg, "char" )) || !(strcmp( arg, "const" )) ||
		!(strcmp( arg, "context" )) || !(strcmp( arg, "default" )) || !(strcmp( arg, "double" )) ||
		!(strcmp( arg, "enum" )) || !(strcmp( arg, "exception" )) || !(strcmp( arg, "FALSE" )) ||
		!(strcmp( arg, "float" )) || !(strcmp( arg, "in" )) || !(strcmp( arg, "inout" )) ||
		!(strcmp( arg, "interface" )) || !(strcmp( arg, "long" )) || !(strcmp( arg, "module" )) ||
		!(strcmp( arg, "Object" )) || !(strcmp( arg, "octet" )) || !(strcmp( arg, "oneway" )) ||
		!(strcmp( arg, "out" )) || !(strcmp( arg, "raises" )) || !(strcmp( arg, "readonly" )) ||
		!(strcmp( arg, "sequence" )) || !(strcmp( arg, "short" )) || !(strcmp( arg, "string" )) ||
		!(strcmp( arg, "struct" )) || !(strcmp( arg, "switch" )) || !(strcmp( arg, "TRUE" )) ||	
		!(strcmp( arg, "typedef" )) || !(strcmp( arg, "unsigned" )) || !(strcmp( arg, "union" )) ||
		!(strcmp( arg, "void" )) )
		{
		delete [] temp_arg;
		return( TRUE );
		}
	//Check if arg is keyword in content, but case does not match:
	else if( !(strcmp( temp_arg, "ANY" )) || !(strcmp( temp_arg, "ATTRIBUTE" )) || !(strcmp( temp_arg, "BOOLEAN" )) || 
		!(strcmp( temp_arg, "CASE" )) || !(strcmp( temp_arg, "CHAR" )) || !(strcmp( temp_arg, "CONST" )) ||
		!(strcmp( temp_arg, "CONTEXT" )) || !(strcmp( temp_arg, "DEFAULT" )) || !(strcmp( temp_arg, "DOUBLE" )) ||
		!(strcmp( temp_arg, "ENUM" )) || !(strcmp( temp_arg, "EXCEPTION" )) || !(strcmp( temp_arg, "FALSE" )) ||
		!(strcmp( temp_arg, "FLOAT" )) || !(strcmp( temp_arg, "IN" )) || !(strcmp( temp_arg, "INOUT" )) ||
		!(strcmp( temp_arg, "INTERFACE" )) || !(strcmp( temp_arg, "LONG" )) || !(strcmp( temp_arg, "MODULE" )) ||
		!(strcmp( temp_arg, "OBJECT" )) || !(strcmp( temp_arg, "OCTET" )) || !(strcmp( temp_arg, "ONEWAY" )) ||
		!(strcmp( temp_arg, "OUT" )) || !(strcmp( temp_arg, "RAISES" )) || !(strcmp( temp_arg, "READONLY" )) ||
		!(strcmp( temp_arg, "SEQUENCE" )) || !(strcmp( temp_arg, "SHORT" )) || !(strcmp( temp_arg, "STRING" )) ||
		!(strcmp( temp_arg, "STRUCT" )) || !(strcmp( temp_arg, "SWITCH" )) || !(strcmp( temp_arg, "TRUE" )) ||	
		!(strcmp( temp_arg, "TYPEDEF" )) || !(strcmp( temp_arg, "UNSIGNED" )) || !(strcmp( temp_arg, "UNION" )) ||
		!(strcmp( temp_arg, "VOID" )) )
		{
		cout << "\nAn error occurred in isKeyword(): The token has same spelling as a keyword," << endl;
		cout << "but contains a case mismatch of one or more characters." << endl;
		delete [] temp_arg;
		return( FAIL );			    
		}
	else
		{
		//We have a plain identifier:
		delete [] temp_arg;
		return( FALSE );
		}

}		


/*
 * initCurrentToken()
 * 
 * post-conditions: Initialize the currentToken data member so it may be used in the
 * parsing phase of the program.
 */
void LexicalAnalyzer::initCurrentToken() 
{

	//Currently: Assign 'head' to 'currentToken':
	this->currentToken = this->head;
	
	return;

}


/*
 * addTokenToList 
 *
 * post-condition: A Token node was created and added to the token list.
 */
void LexicalAnalyzer::addTokenToList( char *string_arg, int type_arg, int line_num_arg )
{

	Token			*t;						  
	
	
	//Create a new Token node for the list based on the general type of the token:
	if( type_arg == IDENTIFIER )
		{
		t = new TokenIdent( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		//t = new Token( string_arg, type_arg, line_num_arg, this->token_object_index );   
		}
	else if( type_arg == KEYWORD )
		{
		t = new TokenKeyWrd( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		}
	else if( type_arg == OPERATOR )
		{
		t = new TokenOper( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		}
	else if( type_arg == PUNCTUATOR )
		{
		t = new TokenPunc( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		}
	else if( type_arg == INTEGER_LITERAL )
		{
		t = new TokenLiteralInt( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		}
	else if( type_arg == FLOATING_PT_LITERAL )
		{
		t = new TokenLiteralFP( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		}
	else if( type_arg == STRING_LITERAL )
		{
		t = new TokenLiteralString( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		}
	else if( type_arg == CHARACTER_LITERAL )
		{
		t = new TokenLiteralChar( string_arg, type_arg, line_num_arg, this->token_object_index, filename );
		}

	//Create a Token node for the list:
	//t = new Token( string_arg, type_arg, line_num_arg, this->token_object_index );     

	if( t == 0 )
		{
		cout << "addTokenToList(): 'new' failed. Program Terminating..." << endl;
		//Sleep( 4000 );
		//exit( -1 );
		}

	//Increment token object index counter:
	(this->token_object_index)++;
		
	//Add Token node to list. Note that we are always adding to tail of list 
	//to preserve correct ordering of tokens:
	//Handle first-element-in-list case:
	if( this->head == 0 )
		{
		this->tail = t;
		this->head = t;
		t->set_next( 0 );			//set_next does this: t->next = 0;
		}
	else
		{
		this->tail->set_next( t );	//Note importance of order of
		this->tail = t;				//these two ops
		t->set_next( 0 );			//set_next does this: t->next = 0;
		}

	
	return;

}


/*
 * traverseTokenList()
 *
 * This function will traverse the Token list, head to tail, and perform some operation 
 * at each Token.
 */
int LexicalAnalyzer::traverseTokenList()
{
	
	Token			*t;			//UnsolNodeT	*p;					
	char			*token_string;
	int				token_type;
	int				line_num;
	int				object_index;

	// Find appropriate Token node in list and perform some operation:
	t = this->head;

	while( t != 0 )
		{
		//Demo Op: Display each Token's string, type, and line number:
		token_string = t->get_token_string();
		token_type = t->get_token_type();
		line_num = t->get_line_num();
		object_index = t->get_object_index();

		if( compiler_debug_state == DEBUG_ON )cout << "************" << endl;
		
		if( (compiler_debug_state == DEBUG_ON) && (token_string != 0) )
			cout << "string= " << token_string << " type= " << token_type << " line= " << line_num << endl;
		else if( (compiler_debug_state == DEBUG_ON) && (token_string == 0) )
			cout << "string= (null)" << " type= " << token_type << " line= " << line_num << endl;

		if( compiler_debug_state == DEBUG_ON )cout << "object index= " << object_index << endl;
		//cout << "value= " << (int) int_val << endl;
		//cout << "************" << endl;

		//Pause for 1 second:
		//Sleep( 5 );

		t = t->get_next();
		}


	return( 0 );


}


/*
 * deleteTokenList()
 *
 * This function will traverse the Token list, head to tail, and delete (free) each Token's 
 * allocated memory. This method will be called from the LexicalAnalyzer destructor.
 */
int LexicalAnalyzer::deleteTokenList()
{
	
	Token			*t, *t2;


	//Traverse list, deleting tokens as we go:
	t = this->head;

	if( t == 0 )
		{
		//If there are no Tokens in list, return immediately:
		cout << "Token list is empty..." << endl;
		return( 0 );
		}

	while( t != 0 )
		{
		//Handle case of last node:
		if( t->get_next() == 0 )
			{
			//We are at the last node.
			delete t;
			cout << "Token list deleted...\n" << endl;
			t = 0;		//Or we could do:	break;
			}
		else if( t->get_next() != 0 )
			{
			//Get pointer to next Token:
			t2 = t->get_next();
			
			//Delete current Token:
			delete t;

			//Reassign new 'head' to t:
			t = t2;
			}
		}

	return( 0 );


}


/*
 * deleteToken()
 *
 * This function will traverse the Token list, head to tail, and delete (free) each Token's 
 * allocated memory. This method will be called from the LexicalAnalyzer destructor.
 *
 * pre-condition: The Token list must not be empty. There must be at least one element in
 *				  the list.
 */
void LexicalAnalyzer::deleteToken( Token *t )
{
	
	//Handle case of last node:
	if( t->get_next() == 0 )
		{
		//We are at the last node.
		delete t;
		return;
		}
	else
		{
		this->deleteToken( t->get_next() );
		delete t;
		}

}



/*
 * processToken()
 *
 * pre-conditions:	The currentToken data member must be pointing to the head of 
 *					the Token list the first time this method is called.
 *
 * post-conditions: This function will process the current Token. This method has 
 *					returned the token type code to yyparse() and set the semantic 
 *					value in the yylval union to its proper value. 
 */
int LexicalAnalyzer::processToken()
{
	int				token_type;
	Token			*t;

	//The first time this method is called, the currentToken data member is set to 
	//the head of the Token list. Thus we will set currenToken to point to the 
	//next Token before we leave.

	//Use local variable:
	t = this->currentToken;

	//If we are at the end of the Token list, return a 0 to terminate yyparse()
	//processing:
	if( t == 0 )
		{
		//Do not set any semantic value.
		
		return( END_OF_TOKEN_LIST );		//Defined as 0
		}
	else
		{
		//Set the semantic value:
		//By polymorphism, the correct version of this method will be invoked:
		t->loadSemanticValueStruct();

		//Set the Token type for return:
		token_type = t->get_token_type();

		//Set the previousToken pointer for possible use by the parser:
		this->previousToken = t;

		//Set the current Token:
		this->currentToken = t->get_next();

		//Return the Token type:
		return( token_type );
		}

	
}


/*
 * addParseTreeNodeToList 
 *
 * post-condition: A ParseTreeNode object was created and added to the ParseTreeNode list.
 */
void LexicalAnalyzer::addParseTreeNodeToList( TopClass *object_ptr_arg )
{

	ParseTreeNode			*p;						  
	
	
	//Create a ParseTreeNode node for the list:
	p = new ParseTreeNode( object_ptr_arg );
	
	//Check for failure of ParseTreeNode creation:
	if( p == 0 )
		{
		//*****Simply ignore this for now.
		//cout << "addParseTreeNodeToList(): 'new' failed. Program Terminating..." << endl;
		//Sleep( 4000 );
		//exit( -1 );	
		}

	//Add ParseTreeNode node to list. Note that we are always adding to head of list 
	//since ordering is not important here:
	/*FFF
	if( this->ptn_head == 0 )			//Handle first-element-in-list case:
		{
		this->ptn_head = p;
		p->set_next( 0 );			//set_next does this: t->next = 0;
		}
	else
		{
		p->set_next( this->ptn_head );	//Insert new node at top of list. 'set_next()' does this: p->next = 0;
		this->ptn_head = p;				//New node is pointed to by 'ptn_head' and points to previous 'ptn_head'.
		}
	FFF*/

	if( this->ptn_head == 0 )			//Handle first-element-in-list case:
		p->set_next( 0 );			//set_next does this: p->next = 0;
	else
		p->set_next( this->ptn_head );	//Insert new node at top of list. 'set_next()' does this: p->next = 0;		
	
	//Perform this assignment in any case:
	this->ptn_head = p;					//New node is pointed to by 'ptn_head' and points to previous 'ptn_head'.		

	
	return;

}


/*
 * deleteParseTreeNode()
 *
 * This recursive function will traverse the ParseTreeNode list, head to tail, and delete (free) each 
 * ParseTreeNode object. The destructor of each ParseTreeNode object will delete (free) the object to which it
 * is holding a pointer to. This method will be called from the LexicalAnalyzer destructor or from the 
 * parser_error_handler(), in the event of a syntax error being encountered.
 *
 * pre-condition: The ParseTreeNode list must not be empty. There must be at least one element in
 *				  the list.
 */
void LexicalAnalyzer::deleteParseTreeNode( ParseTreeNode *p )
{
	
	//Handle case of last node:
	if( p->get_next() == 0 )
		{
		//We are at the last node.
		delete p;
		return;
		}
	else
		{
		this->deleteParseTreeNode( p->get_next() );
		delete p;
		return;
		}

}
