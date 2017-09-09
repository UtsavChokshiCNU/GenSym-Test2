/*
 * Token Class - Base class for various types of tokens.
 *
 * The implementation of the classes declared here are in token.cpp.
 *
 * This is the Token class. Token represents a single token as determined by the 
 * LexicalAnalyzer. All data fields in Token are loaded via the constructor.
 * The access functions are therefore all of type 'get', except for the 'set next'
 * function.
 */


//**************************Class: Token***************************
class Token
	{
	private:

	protected:
		char				*token_string;
		char				*filename;
		int					token_type;
		int					line_num;
		int					object_index;
		Token				*next;		//For linking token list.
		virtual int getKeywordType( char * ); 

	
		//virtual void set_token_string( char *, int, int ) {}
		//This will be overridden by specific subclasses as needed:
		
		
	public:
		Token( char *, int, int, int, char * );
		virtual ~Token();
		virtual void set_next( Token * );
		virtual Token* get_next();
		virtual char* get_token_string();		
		virtual int get_line_num();
		virtual int get_object_index();

		//These methods will be overriden in each sub-class:
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();
		virtual char *get_filename();
		

	};


//**************************Class: TokenIdent***************************
class TokenIdent : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenIdent( char *, int, int, int, char *);
		virtual ~TokenIdent();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};


//**************************Class: TokenKeyWrd***************************
class TokenKeyWrd : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenKeyWrd( char *, int, int, int, char * );
		virtual ~TokenKeyWrd();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};


//**************************Class: TokenOper***************************
class TokenOper : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenOper( char *, int, int, int, char * );
		virtual ~TokenOper();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};


//**************************Class: TokenPunc***************************
class TokenPunc : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenPunc( char *, int, int, int, char * );
		virtual ~TokenPunc();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};


//**************************Class: TokenLiteralInt***************************
class TokenLiteralInt : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenLiteralInt( char *, int, int, int, char * );
		virtual ~TokenLiteralInt();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};


//**************************Class: TokenLiteralFP***************************
class TokenLiteralFP : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenLiteralFP( char *, int, int, int, char * );
		virtual ~TokenLiteralFP();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};


//**************************Class: TokenLiteralString***************************
class TokenLiteralString : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenLiteralString( char *, int, int, int, char * );
		virtual ~TokenLiteralString();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};
		

//**************************Class: TokenLiteralChar***************************
class TokenLiteralChar : public Token
	{
	private:
		//--Inherited--

	protected:
			
		
	public:
		TokenLiteralChar( char *, int, int, int, char * );
		virtual ~TokenLiteralChar();
		virtual int get_token_type();
		virtual void loadSemanticValueStruct();

	};

