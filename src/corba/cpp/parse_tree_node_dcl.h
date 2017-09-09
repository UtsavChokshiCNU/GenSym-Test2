/*
 * ParseTreeNode Class - Holds pointer to an object in the parse tree.
 *
 * The implementation of this class is in parse_tree_node.cpp.
 */

//**************************Class: ParseTreeNode***************************
class ParseTreeNode
	{
	private:
		TopClass			*parseTreeObject;
		ParseTreeNode		*next;

	protected:
		//-None-
		
	public:
		ParseTreeNode( TopClass * );
		virtual ~ParseTreeNode();
		virtual void set_next( ParseTreeNode * );
		virtual ParseTreeNode* get_next();
	};
