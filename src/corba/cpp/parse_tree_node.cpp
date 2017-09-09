/*
 * ParseTreeNode Class - Holds pointer to an object in the parse tree.
 */
#include <stdio.h>
#include <iostream_ver.h>
//#include <fstream_ver.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
//#include <windows.h>
//#include <windowsx.h>
#include "code_tokens.h"
#include "corba_main.h"
extern "C"
{
#include "yacc_supp.h"
#include "ytab.h"
}

#include "parse_dcl.h"
#include "parse_tree_node_dcl.h"

//**************************Class: ParseTreeNode***************************
/*
 * ParseTreeNode - Constructor     
 */
ParseTreeNode::ParseTreeNode( TopClass *object_ptr_arg )
{    
	//Load the pointer for the object which we will later reference:
	this->parseTreeObject = object_ptr_arg;
	
	//delete this->parseTreeObject;

}


/*
 * ParseTreeNode - Destructor
 */
ParseTreeNode::~ParseTreeNode()	 
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside ParseTreeNode Destructor" << endl;

	//Free the object to which we are holding its pointer:
	delete this->parseTreeObject;
	

	return;
}

/*
 * set_next()
 * 
 * post-conditions: The 'next' pointer of this ParseTreeNode was set.
 */
void ParseTreeNode::set_next( ParseTreeNode *ptr_arg ) 
{

	this->next = ptr_arg;

	return;

}


/*
 * get_next()
 * 
 * post-conditions: A pointer to the 'next' ParseTreeNode was returned.
 */
ParseTreeNode* ParseTreeNode::get_next() 
{

	return( this->next );

}
