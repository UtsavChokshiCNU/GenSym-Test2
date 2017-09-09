/*
 * LexicalAnalyzer
 *
 * This file contains the class declaration for the LexicalAnalyzer class. The implementation
 * of this class is in lex_1.cpp.
 *
 */
//***
//** Class - LexicalAnalyzer
//***
class LexicalAnalyzer
	{

	private:
		ifstream		inp_file;
		char			*filename;
		char			*cbuf;
		int				cbuf_pos;
		char			*char_array;
		int				char_array_index;
		int				state;
		int				token_index;
		int				token_object_index;
		int				line_num;

		Token			*head;			//Beginning of Token object linked-list.
		Token			*tail;			//End of Token object linked-list.
		Token			*currentToken;	//The current Token to be processed;
		Token			*previousToken;	//The just-processed token. Can be accessed if 
										//a parser error occurs and line number/filename 
										//information is needed.
		ParseTreeNode	*ptn_head;		//Beginning of ParseTreeNode object linked-list.



	protected:
		virtual int char_type( int );
		virtual void reset_cbuf();
		virtual void add_to_cbuf( char );
		virtual const int get_state();
		virtual void set_state( const int );
		static int isOper( char * );
		static int isKeyword( char * );
		static void setIdentifierType( int );		//IDENTIFIER or KEYWORD

		//virtual void addTokenToList( char*, int, int );
		virtual int traverseTokenList();
		virtual int deleteTokenList();		        
		virtual void deleteToken( Token * );		        

	public:
		LexicalAnalyzer();
		virtual ~LexicalAnalyzer();
		virtual void addParseTreeNodeToList( TopClass * );
		virtual void token_machine();
		virtual void addTokenToList( char*, int, int );
		virtual int processToken();
		virtual void initCurrentToken();
		virtual int get_previousToken_line_num();
		virtual char *get_previousToken_filename();
		virtual ParseTreeNode* get_ptn_head();
		virtual void deleteParseTreeNode( ParseTreeNode * );		        
		
		virtual char *get_filename();
		virtual void setFile(char *filename);
		

		//Character type constants:
		const static int ISALPHA;
		const static int ISDIGIT;
		const static int ISPUNCT;
		const static int ISSPACE;
		const static int ISUNKNOWN;


		const static int OUTALL;
		const static int IDENTIFIER_STATE;
		const static int PUNCTUATION;
		const static int GENL_NUM_LITERAL;
		const static int GENL_INT_LITERAL_LEAD_0;
		const static int HEX_INT_LITERAL_FIRST_PAST_X;
		const static int HEX_INT_LITERAL_GENL;
		const static int OCT_INT_LITERAL;
		const static int FP_E_NO_DOT_LITERAL;
		const static int FP_E_NO_DOT_SIGNED_LITERAL;
		const static int FP_DOT_LITERAL;
		const static int FP_LEADING_DOT_LITERAL;
		const static int ADD_DIGIT;
		const static int GENL_CHAR_LITERAL;
		const static int TERMINATE_CHAR_LITERAL;
		const static int ESCAPE_CHAR_LITERAL;
		const static int HEX_ESC_1ST_CHAR_LITERAL;
		const static int HEX_ESC_2ND_CHAR_LITERAL;
		const static int OCT_ESC_2ND_CHAR_LITERAL;
		const static int OCT_ESC_LAST_CHAR_LITERAL;
		const static int GENL_STRING_LITERAL;
		const static int STRING_LITERAL_ESC_SEQ;
		const static int STRING_LITERAL_END_CHECK;
		const static int STRING_LITERAL_HEX_ESC_1ST_CHAR;
		const static int STRING_LITERAL_HEX_ESC_2ND_CHAR;
		const static int STRING_LITERAL_OCT_ESC_2ND_CHAR;
		const static int STRING_LITERAL_OCT_ESC_LAST_CHAR;
		const static int DOUBLE_COLON_CHECK;
		const static int DOUBLE_LT_CHECK;
		const static int DOUBLE_GT_CHECK;
		const static int CHECK_NO_HEX_CHAR;
		const static int COMMENT_CHECK;
		const static int IN_C_COMMENT;
		const static int IN_CPP_COMMENT;
		const static int C_COMMENT_TERMINATE_CHECK;
  
	};

