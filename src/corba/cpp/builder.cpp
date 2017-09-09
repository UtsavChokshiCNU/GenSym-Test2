/*
 * Builder
 *
 * This file contains the routines which will build the data structures for use by G2.
 * The methods in here are the link between the parser's K+R C output and the G2/GSI C++
 * data structures.
 *
 * CPP and C Dependencies
 *  lex_1.cpp
 *  gsi_compile.cpp
 *  ytab.c
 *  parse.cpp
 */
#include <stdio.h>
#include <iostream_ver.h>
#include <fstream_ver.h>
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
#include "parse_tree_node_dcl.h"
#include "token_dcl.h"
#include "lex_1_dcl.h"
#include "builder_dcl.h"

#include "gsi_main_cpp.h"
#include "gsi_misc_cpp.h"


#define FAIL				-1
#define	END_OF_TOKEN_LIST	0
#define	RECURSION			0
#define	LIST_TRAVERSAL		1


//Suppress C++ name mangling of C function names:
extern "C"
{
void *buildBase_Type_Spec( char * );
void *buildAttr_Dcl( int, char *, void *, void * [], int );
void *buildUnion_Type( char *, char *, char *, void *, void * [], int );
void *buildInterface_Body();
void addExport( void *, void * );
void *buildInterface_Header( char *, char *, void * );
void *buildForward_Dcl( char *, char * );
void *buildInterface_Dcl( void *, void * );
void *buildSpecification();
void addDefinition( void *, void * );
void loadParseTreeRoot( void * );
void *buildParam_Dcl( char *, void *, void * );
void *buildOp_Type_Spec1( void * );
void *buildOp_Type_Spec2( char * );
void *buildOp_Dcl( int, void*, char *, void * [], int, void *, void * );
void *buildEnum_Type( char *, char *, char * [], int );
void *buildContext_Expr( char *, void * [], int );
void *buildSimple_Declarator( char * );
void *buildMember( void *, void * [], int );
void *buildType_Declarator( void *, void * [], int );
void *buildStruct_Type( char *, char *, void * [], int );
void *buildModule( char *, char *, void * [], int );
void *buildExcept_Dcl( char *, char *, void * [], int );
void *buildScoped_Name( char * [], int, int );
void *buildInheritance_Spec( void * [], int );
void *buildRaises_Expr( void * [], int );
void *buildLongIntegerLiteral( long );
void *buildStringLiteral( char * );
void *buildCharLiteral( char );
void *buildDoubleLiteral( double );
void *buildBooleanLiteral( char * );
//int applyUnaryOperator( int, void * );
void setUnaryOperator( int, void * );
void *buildConst_Type1( char * );
void *buildConst_Type2( void * ); 
void *buildConst_Dcl( char *, void *, char *, void * );
void *buildSequence_Type( char *, void *, void * );
void *buildString_Type( char *, void * ); 
void *buildSwitch_Type_Spec1( char * );
void *buildSwitch_Type_Spec2( void * );
void *buildElement_Spec( void *, void * );
void *buildMath_Expression( void *, void *, int );
void *buildCase_Label( char *, void * );
void *buildType_Dcl_Case1( char *, void * );
void *buildCase( void * [], int, void * );
void *buildArray_Declarator( char *, void * [], int );

}


//Object 'lex' will be used to add objects to the parse tree node list:
extern class LexicalAnalyzer	*lex;


//**************************Class: Builder***************************
/***************/
/* Builder     */
/* Constructor */
/***************/
Builder::Builder( LexicalAnalyzer *lex_obj_arg )
{
	//We are receiving a pointer to the LexicalAnalyzer object. We will 
	//use this to access the addParseTreeNodeToList() function.
	this->lex_obj = lex_obj_arg;
	
	return;
}


/***************/
/* Builder     */
/* Destructor  */
/***************/
Builder::~Builder()
{   

	return;

}


/********Top Level Interface Functions For Translating calls from ytab.c ********/
/*
 * buildBase_Type_Spec()
 */
void *buildBase_Type_Spec( char *arg )
{
	TopClass		*ptr;

	
	ptr = new Base_Type_Spec( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );


}


/*
 * buildSimple_Declarator()
 */
void *buildSimple_Declarator( char *arg )
{
	TopClass		*ptr;

	
	ptr = new Simple_Declarator( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );


}


/*
 * buildLongIntegerLiteral()
 */
void *buildLongIntegerLiteral( long arg )
{
	TopClass		*ptr;

	ptr = new LongIntegerLiteral( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr ); 
}

/*
 * buildStringLiteral()
 */
void *buildStringLiteral( char *arg )
{
	TopClass		*ptr;

	ptr = new StringLiteral( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr ); 
}


/*
 * buildCharLiteral()
 */
void *buildCharLiteral( char arg )
{
	TopClass		*ptr;

	ptr = new CharLiteral( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr ); 
}

/*
 * buildDoubleLiteral()
 */
void *buildDoubleLiteral( double arg )
{
	TopClass		*ptr;

	ptr = new DoubleLiteral( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr ); 
}

/*
 * buildBooleanLiteral() - boolean (TRUE, FALSE) - currently a string, but may change.
 */
void *buildBooleanLiteral( char *arg )
{
	TopClass		*ptr;

	ptr = new BooleanLiteral( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr ); 
}


/*
 * buildOp_Type_Spec1()
 */
void *buildOp_Type_Spec1( void *ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new Op_Type_Spec( ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildOp_Type_Spec2()
 */
void *buildOp_Type_Spec2( char *arg )
{
	TopClass		*ptr;

	
	ptr = new Op_Type_Spec( arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildConst_Type1()
 */
void *buildConst_Type1( char *string_arg )
{
	TopClass		*ptr;

	
	ptr = new Const_Type( string_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}

/*
 * buildConst_Type2()
 */
void *buildConst_Type2( void *ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new Const_Type( ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildSwitch_Type_Spec1()
 */
void *buildSwitch_Type_Spec1( char *string_arg )
{
	TopClass		*ptr;

	
	ptr = new Switch_Type_Spec( string_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildSwitch_Type_Spec2()
 */
void *buildSwitch_Type_Spec2( void *ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new Switch_Type_Spec( ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildConst_Dcl()
 */
void *buildConst_Dcl( char *keyword_arg, void *const_type_ptr_arg, char *name_arg, void *const_exp_ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new Const_Dcl( keyword_arg, const_type_ptr_arg, name_arg, const_exp_ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildSequence_Type()
 */
void *buildSequence_Type( char *keyword_arg, void *simple_type_spec_ptr_arg, void *positive_int_const_ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new Sequence_Type( keyword_arg, simple_type_spec_ptr_arg, positive_int_const_ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}  


/*
 * buildString_Type()
 */
void *buildString_Type( char *keyword_arg, void *positive_int_const_ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new String_Type( keyword_arg, positive_int_const_ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildCase_Label()
 */
void *buildCase_Label( char *string_arg, void *const_exp_ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new Case_Label( string_arg, const_exp_ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildType_Dcl_Case1()
 */
void *buildType_Dcl_Case1( char *keyword_arg, void *type_declarator_ptr_arg )
{
	TopClass		*ptr;

	
	ptr = new Type_Dcl_Case1( keyword_arg, type_declarator_ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildAttr_Dcl()
 */
void *buildAttr_Dcl( int readonly_flag_arg, char *keyword_arg, void *param_type_spec_ptr_arg, void *attr_dcl_array_arg[], int attr_dcl_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Attr_Dcl( readonly_flag_arg, keyword_arg, param_type_spec_ptr_arg, attr_dcl_array_arg, attr_dcl_array_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );	
	

	return( (void *) ptr );

}


/*
 * buildUnion_Type()
 */
void *buildUnion_Type( char *keyword_arg, char *union_name_arg, char *string_arg, void *switch_type_spec_ptr_arg, void *switch_body_array_arg[], int switch_body_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Union_Type( keyword_arg, union_name_arg, string_arg, switch_type_spec_ptr_arg, switch_body_array_arg, switch_body_array_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildCase()
 */			   
void *buildCase( void *case_label_array_arg[], int case_label_array_count_arg, void *element_spec_ptr_arg )
{
	TopClass		*ptr;


	ptr = new Case( case_label_array_arg, case_label_array_count_arg, element_spec_ptr_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildArray_Declarator()
 */			   
void *buildArray_Declarator( char *array_name_arg, void *fixed_array_size_array_arg[], int fixed_array_size_count_arg )
{
	TopClass		*ptr;


	ptr = new Array_Declarator( array_name_arg, fixed_array_size_array_arg, fixed_array_size_count_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildScoped_Name()
 */
void *buildScoped_Name( char *scoped_name_list_array_arg[], int scoped_name_list_array_count_arg, int scoped_name_scope_flag_arg )
{
	TopClass		*ptr;


	ptr = new Scoped_Name( scoped_name_list_array_arg,  scoped_name_list_array_count_arg, scoped_name_scope_flag_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildStruct_Type()
 */
void *buildStruct_Type( char *keyword_arg, char *struct_name_arg, void *member_array_arg[], int member_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Struct_Type( keyword_arg, struct_name_arg, member_array_arg, member_array_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildModule()
 */
void *buildModule( char *keyword_arg, char *module_name_arg, void *module_definition_array_arg[], int module_definition_count_arg )
{
	TopClass		*ptr;


	ptr = new Module( keyword_arg, module_name_arg, module_definition_array_arg, module_definition_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildExcept_Dcl()
 */
void *buildExcept_Dcl( char *keyword_arg, char *except_name_arg, void *member_array_arg[], int member_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Except_Dcl( keyword_arg, except_name_arg, member_array_arg, member_array_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildMember()
 */
void *buildMember( void *type_spec_ptr_arg, void *declarator_array_arg[], int declarator_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Member( type_spec_ptr_arg, declarator_array_arg, declarator_array_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildType_Declarator()
 */
void *buildType_Declarator( void *type_spec_ptr_arg, void *declarator_array_arg[], int declarator_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Type_Declarator( type_spec_ptr_arg, declarator_array_arg, declarator_array_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildInheritance_Spec()
 */
void *buildInheritance_Spec( void *scoped_name_array_arg[], int scoped_name_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Inheritance_Spec( scoped_name_array_arg, scoped_name_array_count_arg );
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildRaises_Expr()
 */
void *buildRaises_Expr( void *scoped_name_array_arg[], int scoped_name_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Raises_Expr( scoped_name_array_arg, scoped_name_array_count_arg );
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildOp_Dcl()
 */
void *buildOp_Dcl( int opattribute_flag_arg, void* op_type_spec_ptr_arg, char *operation_name_arg, void *param_dcl_array_arg[], int param_dcl_array_count_arg, void *raises_expr_ptr_arg, void *context_expr_ptr_arg )
{
	TopClass		*ptr;


	ptr = new Op_Dcl( opattribute_flag_arg, op_type_spec_ptr_arg, operation_name_arg, param_dcl_array_arg, param_dcl_array_count_arg, raises_expr_ptr_arg, context_expr_ptr_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );


}


/*
 * buildEnum_Type()
 */
void *buildEnum_Type( char *keyword_arg, char *enum_name_arg, char *enumerator_array_arg[], int enumerator_array_count_arg )
{
	TopClass		*ptr;


	ptr = new Enum_Type( keyword_arg, enum_name_arg, enumerator_array_arg, enumerator_array_count_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildContext_Expr()
 */
void *buildContext_Expr( char *keyword_arg, void *string_literal_array_arg[], int string_literal_count_arg )
{
	TopClass		*ptr;


	ptr = new Context_Expr( keyword_arg, string_literal_array_arg, string_literal_count_arg );
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}



/*
 * buildInterface_Body()
 */
void *buildInterface_Body()
{
	TopClass		*ptr;


	ptr = new Interface_Body();
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );


}


/*
 * buildParam_Dcl()
 */
void *buildParam_Dcl( char *param_attribute_arg, void *param_type_spec_ptr_arg, void *simple_declarator_arg )
{
	TopClass		*ptr;


	ptr = new Param_Dcl( param_attribute_arg, param_type_spec_ptr_arg, simple_declarator_arg );
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );
}


/*
 * buildElement_Spec()
 */
void *buildElement_Spec( void *type_spec_ptr_arg, void *declarator_ptr_arg )
{
	TopClass		*ptr;


	ptr = new Element_Spec( type_spec_ptr_arg, declarator_ptr_arg );
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );
}


/*
 * buildMath_Expression()
 */
void *buildMath_Expression( void *left_operand_ptr_arg, void *right_operand_ptr_arg, int operator_code_arg )
{
	TopClass		*ptr;


	ptr = new Math_Expression( left_operand_ptr_arg, right_operand_ptr_arg, operator_code_arg );

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );
}


/*
 * buildInterface_Header()
 */
void *buildInterface_Header( char *keyword_arg, char *identifier_name_arg, void *inheritance_spec_arg )
{
	TopClass		*ptr;

	if( inheritance_spec_arg == NULL )
		ptr = new Interface_Header( keyword_arg, identifier_name_arg );	
	else
		ptr = new Interface_Header( keyword_arg, identifier_name_arg, inheritance_spec_arg );
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );


}


/*
 * buildForward_Dcl()
 */
void *buildForward_Dcl( char *keyword_arg, char *identifier_name_arg )
{
	TopClass		*ptr;

	ptr = new Forward_Dcl( keyword_arg, identifier_name_arg );
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );
	

	return( (void *) ptr );
}


/*
 * buildInterface_Dcl()
 */
void *buildInterface_Dcl( void *interface_header_arg, void *interface_body_arg )
{
	TopClass		*ptr;

	ptr = new Interface_Dcl( interface_header_arg, interface_body_arg );	

	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );

}


/*
 * buildSpecification()
 */
void *buildSpecification()
{
	TopClass		*ptr;


	ptr = new Specification();
	
	//Add this object to the parse tree list:
	lex->addParseTreeNodeToList( ptr );

	
	return( (void *) ptr );


}


/*
 * addDefinition()
 */
void addDefinition( void *Specification_arg, void *ptr_arg )
{
	Specification	*ptr1;


	ptr1 = (Specification *) Specification_arg;

	ptr1->addDefinition( ptr_arg );

		
	return;

}


/*
 * addExport()
 */
void addExport( void *Interface_Body_arg, void *ptr_arg )
{
	Interface_Body	*ptr1;


	ptr1 = (Interface_Body *) Interface_Body_arg;

	ptr1->addExport( ptr_arg );

		
	return;


}


/*
 * loadParseTreeRoot()
 *
 * This top-level function loads the root address of the parse tree generated
 * by yyparse().
 */
void loadParseTreeRoot( void *ptr_arg )
{

	extern class Builder		*bobj;        
	
	bobj->loadParseTreeRoot( ptr_arg );
	
	return;


}


/*
 * applyUnaryOperator()
 */
/*****
int applyUnaryOperator( int arg, void *ptr_arg )
{								    
	Literal			*ptr1;
	int				ret_val;

	ptr1 = (Literal *) ptr_arg;

	ret_val = ptr1->applyUnaryOperator( arg );

		
	return( ret_val );


}
*******/


/*
 * setUnaryOperator()
 */
void setUnaryOperator( int arg, void *ptr_arg )
{								    
	TopClass		*ptr1;


	ptr1 = (TopClass *) ptr_arg;

	ptr1->setUnaryOperator( arg );

		
	return;

}




/********************************************************************************/


/*
 * loadParseTreeRoot()
 *
 * This method loads the root address of the parse tree generated by yyparse().
 */
void Builder::loadParseTreeRoot( void *ptr_arg )
{

	this->parseTreeRoot = (TopClass *) ptr_arg;	

	
	return;

}


/*
 * buildGSIItem()
 * 
 * Build a GSI data structure inside of a gsi_item. Then return it to the calling function.
 */
void Builder::buildGSIItem( gsi_item itm )
{

	//Build the data structure to be passed back up to G2:
	this->gsiObjModelroot->build_gsi_object( itm, NULL );			//root->build_gsi_object(rets[0]);

	//Output the pseudo-tree of the generated GSI object model:
	if( compiler_debug_state == DEBUG_ON )
		{
		gsirtl_display_item_or_value( itm, 0, 1 );
		}

	return;

}


/*
 * buildGSIModel()
 * 
 * Build the GSI object model from the parse tree object model. This method
 * will begin a cascade of processing through the entire parse tree.
 */
void Builder::buildGSIModel()
{

	//Build the GSI object model from the parse tree object model:
	//this->parseTreeRoot->buildGSIobject( (g2_token_object *) &(this->gsiObjModelroot) );			
	this->parseTreeRoot->buildGSIobject( (SuperClass *) &(this->gsiObjModelroot) );			
	//The preceeding way-hack arg cast gets around type constraint of buildGSIobject.
	//It is "un-cast" in called function.
	//By passing the address of the this->gsiObjModelroot, we can allow changes which 
	//occur in the called function to be "felt" here.

	return;

}
