/*
 * Builder
 *
 * This file contains the declaration of the Builder class. The implementation of this class is
 * in builder.cpp
 */

/*
 * Builder
 */
class Builder
	{

	private:
	TopClass			*parseTreeRoot;
	g2_file_token		*gsiObjModelroot;
	//void				(*register_object)( TopClass * );	//This will point to LexicalAnalyzer::addParseTreeNodeToList()
	LexicalAnalyzer		*lex_obj;		//Used to access addParseTreeNodeToList().
	
	protected:
	//-None-

	public:
		//Builder( void (*register_object_arg)( TopClass * ) );
		Builder( LexicalAnalyzer * );
		virtual ~Builder();
		virtual void loadParseTreeRoot( void *ptr_arg );
		//virtual void buildInterface( char * [], export_dcl_type_node * [], int );
		virtual void buildGSIItem( gsi_item );
		virtual void buildGSIModel();

	};

