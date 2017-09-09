/*							  
 * This file contains the classes for use in building a parse tree before creation of
 * G2 data objects. The class declarations are in the parse_dcl.h file.
 *
 * A note about memory clean-up: Each destructor should 'delete' any storage that was allocated 
 * dynamically by the object in the constructor or in any method that does not delete its own
 * storage. Since there is a global parse tree object list which contains pointers to all of the
 * allocated parse tree objects, we SHOULD NOT delete any objects that may be pointed to by an 
 * object's pointer data members. These objects will be deleted globally instead. For example, 
 * if there is an array of TopClass* pointers to various objects, we can delete the array (which
 * we allocated in the constructor) and not worry about the elements in the array being lost, as
 * pointers to them are held in the parse tree node list. In summary, in the destructors for the
 * parse tree classes, delete all storage allocated within the class, and do not free any pointed-to
 * objects. They will be handled separately.
 * 
 */

#include <stdio.h>
#include <iostream_ver.h>
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


//**************************Class: TopClass***************************
/*
 * TopClass - Constructor
 * 
 */
TopClass::TopClass()
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside TopClass Constructor" << endl;
	
	return;
}


/*
 * TopClass - Destructor
 */
TopClass::~TopClass()
{                   
	//if( compiler_debug_state == DEBUG_ON )cout << "Inside TopClass Destructor" << endl;

	return;
}


//*****Methods to be overridden in various subclasses:
/*
 * setUnaryOperator():
 * 
 * post-conditions: The unary operator's ASCII value was loaded.
 *
 */
void TopClass::setUnaryOperator( int op_code )
{
	return;
}
//*****End: Methods to be overridden in various subclasses.


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *TopClass::buildGSIobject( SuperClass *faux_arg )
{
	
	return( 0 );

}


/*
 * toUpperPlus():
 * 
 * post-conditions: Input arg was converted to upper case chars and any spaces
 *					as in "unsigned long" or "unsigned short" are converted to 
 *					hyphen characters. This is necessary since G2 is confused 
 *					by space characters in a string, and hyphens are the 
 *					chosen substitute here.
 *
 * NOTE: This function will permanently convert original string!
 *
 */
char *TopClass::toUpperPlus( char *arg )
{
	int			k, len;
	
	len = strlen( arg );

	for( k=0 ; k<len ; k++ )
		{
		if( arg[k] == ' ' )
			arg[k] = '-';
		else
			arg[k] = toupper( arg[k] );
		}

		
	return( arg );

}


//**************************Class: Inheritance_Spec***************************
/*
 * Inheritance_Spec - Constructor     
 */
Inheritance_Spec::Inheritance_Spec( void *scoped_name_array_arg[], int scoped_name_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Inheritance_Spec Constructor" << endl;

	this->scoped_name_array = new TopClass*[scoped_name_array_count_arg];
	this->scoped_name_array_count = scoped_name_array_count_arg;

	for( i=0 ; i<scoped_name_array_count_arg ; i++ )
		{
		//Each array element contains a pointer to a Scoped_Name object:
		this->scoped_name_array[i] = (TopClass *) scoped_name_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Inheritance_Spec - Destructor
 */																							  
Inheritance_Spec::~Inheritance_Spec()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Inheritance_Spec Destructor" << endl;

	//Delete the declarator array:
	delete [] this->scoped_name_array;
 
	
	return;
}


/*
 * run_scoped_name_array_i_buildGSIobject(): 
 */
SuperClass *Inheritance_Spec::run_scoped_name_array_i_buildGSIobject( int i )	//Provide access to private members.
{

	return( this->scoped_name_array[i]->buildGSIobject( 0 ) );

}


/*
 * get_scoped_name_array_count():
 *
 */
int Inheritance_Spec::get_scoped_name_array_count()	//Provide access to private members.
{

	return( this->scoped_name_array_count );

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Inheritance_Spec::buildGSIobject( SuperClass *faux_arg )
{
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Inheritance_Spec::buildGSIobject()" << endl;

	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the 
	//Interface_Header constructs from this object's data will be performed in 
	//the calling object's buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Raises_Expr***************************
/*
 * Raises_Expr - Constructor     
 */
Raises_Expr::Raises_Expr( void *scoped_name_array_arg[], int scoped_name_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Raises_Expr Constructor" << endl;

	this->scoped_name_array = new TopClass*[scoped_name_array_count_arg];
	this->scoped_name_array_count = scoped_name_array_count_arg;

	for( i=0 ; i<scoped_name_array_count_arg ; i++ )
		{
		//Each array element contains a pointer to a Scoped_Name object:
		this->scoped_name_array[i] = (TopClass *) scoped_name_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Raises_Expr - Destructor
 */																							  
Raises_Expr::~Raises_Expr()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Raises_Expr Destructor" << endl;

	//Delete the declarator array:
	delete [] this->scoped_name_array;
 
	
	return;
}


/*
 * run_scoped_name_array_i_buildGSIobject(): 
 */
SuperClass *Raises_Expr::run_scoped_name_array_i_buildGSIobject( int i )	//Provide access to private members.
{

	return( this->scoped_name_array[i]->buildGSIobject( 0 ) );

}


/*
 * get_scoped_name_array_count():
 *
 */
int Raises_Expr::get_scoped_name_array_count()	//Provide access to private members.
{

	return( this->scoped_name_array_count );

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Raises_Expr::buildGSIobject( SuperClass *faux_arg )
{

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Raises_Expr::buildGSIobject()" << endl;
	
	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the Raises_Expr
	//constructs from this object's data will be performed in the calling object's 		  
	//buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Context_Expr***************************
/*
 * Context_Expr - Constructor
 */
Context_Expr::Context_Expr( char *keyword_arg, void *string_literal_array_arg[], int string_literal_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Context_Expr Constructor" << endl;

	//Allocate storage for the char * parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->string_literal_array = new TopClass*[string_literal_count_arg];
	this->string_literal_count = string_literal_count_arg;

	for( i=0 ; i<string_literal_count_arg ; i++ )
		{
		this->string_literal_array[i] = (TopClass *) string_literal_array_arg[i];	//No storage needed. Pointers only.
		}
	
	return;

}

	
/*
 * Context_Expr - Destructor
 */
Context_Expr::~Context_Expr()
{                   
	int		i;

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Context_Expr Destructor" << endl;
		
	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
										      
	//Delete all of the array elements:
	for( i=0 ; i<this->string_literal_count ; i++ )
		{
		//delete [] this->string_literal_array[i];
		}

	//Delete the array itself:
	delete [] this->string_literal_array;
 
	
	return;
	
}


/*
 * run_string_literal_array_i_buildGSIobject(): 
 */
SuperClass *Context_Expr::run_string_literal_array_i_buildGSIobject( int i )	//Provide access to private members.
{

	return( this->string_literal_array[i]->buildGSIobject( 0 ) );

}


/*
 * get_string_literal_count():
 */
int Context_Expr::get_string_literal_count()	//Provide access to private members.
{

	return( this->string_literal_count );

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Context_Expr::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Context_Expr::buildGSIobject()" << endl;
	
	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the Context_Expr
	//constructs from this object's data will be performed in the calling object's 		  
	//buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Base_Type_Spec***************************
/*
 * Base_Type_Spec - Constructor     
 */
Base_Type_Spec::Base_Type_Spec( char *string_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Base_Type_Spec Constructor" << endl;

	//Allocate storage for the string parameter: 
	this->string = new char[strlen(string_arg)+1];
	strcpy( this->string, string_arg );

	return;

}


/*
 * Base_Type_Spec - Destructor
 */
Base_Type_Spec::~Base_Type_Spec()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Base_Type_Spec Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->string;

	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Base_Type_Spec::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Base_Type_Spec::buildGSIobject()" << endl;	

	g2_prim_type_token		*typetoken;	
	
	typetoken = new g2_prim_type_token(); 
				
	typetoken->m_name = toUpperPlus( this->string );

	return( typetoken );

}


//**************************Class: Attr_Dcl***************************
/*
 * Attr_Dcl - Constructor     
 */
Attr_Dcl::Attr_Dcl( int readonly_flag_arg, char *keyword_arg, void *param_type_spec_ptr_arg, void *attr_dcl_array_arg[], int attr_dcl_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Attr_Dcl Constructor" << endl;

	this->readonly_flag = readonly_flag_arg;

	//Allocate storage for the keyword parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->param_type_spec_ptr = (TopClass *) param_type_spec_ptr_arg;

	this->attr_dcl_array = new TopClass*[attr_dcl_array_count_arg];
	this->attr_dcl_array_count = attr_dcl_array_count_arg;

	for( i=0 ; i<attr_dcl_array_count_arg ; i++ )
		{
		//this->attr_dcl_array[i] = new char[strlen(attr_dcl_array_arg[i])+1];
		//strcpy( this->attr_dcl_array[i], attr_dcl_array_arg[i] );
		this->attr_dcl_array[i] = (TopClass *) attr_dcl_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Attr_Dcl - Destructor
 */
Attr_Dcl::~Attr_Dcl()
{                   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Attr_Dcl Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;

	//Delete all of the array elements:
	for( i=0 ; i<this->attr_dcl_array_count ; i++ )
		{
		//Comment out the following for now since we are going to delete all objects globally:
		//delete [] this->attr_dcl_array[i];
		}

	//Delete the array itself:
	delete [] this->attr_dcl_array;
 
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Attr_Dcl::buildGSIobject( SuperClass *faux_arg )
{

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Attr_Dcl::buildGSIobject()" << endl;


	g2_attribute_token		*attrToken;
	int						i;


	//Create an ATTRIBUTE object:
	attrToken = new g2_attribute_token();

	//Build the referenced param_type_spec and add it to the attribute token:
	//The g2_token_object* cast should be okay:
	attrToken->m_type.m_type = (g2_token_object *) this->param_type_spec_ptr->buildGSIobject( 0 );

	//Load the declarators:
	for( i=0 ; i<this->attr_dcl_array_count ; i++ )
		{
		//All the 'Add' functions are G2OrbContained subclass ops, so this is a safe cast:
		attrToken->m_names.Add( (g2_token_object *) this->attr_dcl_array[i]->buildGSIobject( 0 ) );
		}
				
	//Handle readonly flag:
	attrToken->m_readonly = this->readonly_flag;
				
	//Return attribute token to be added to appropriate container:
	return( attrToken );

}


//**************************Class: Interface_Body***************************
/*
 * Interface_Body - Constructor     
 */
Interface_Body::Interface_Body() : TopClass()
{   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Body Constructor" << endl;

	//Initialize these:
	export_array_count = 0;
	export_array_size_limit = 64;

	//Create the export_array: 64 TopClass objects:
	//This will be resized if necessary in the addExport method:
	export_array = new TopClass*[export_array_size_limit];
	
	
	return;

}

	
/*
 * Interface_Body - Destructor
 */
Interface_Body::~Interface_Body()
{                   
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Body Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->export_array;

	return;
}


/*
 * addExport()
 * 
 * post-conditions: A pointer to an export item was added to the export_array.
 */
void Interface_Body::addExport( void *ptr_arg )
{
	TopClass	**temp_export_array;
	int			i;
	
	//Check if array resizing is necessary due to full array:
	if( this->export_array_count == this->export_array_size_limit )
		{
		//Build and load a temporary storage array:
		temp_export_array = new TopClass*[this->export_array_size_limit];

		for( i=0 ; i<this->export_array_size_limit ; i++ )
			{
			temp_export_array[i] = this->export_array[i];
			}

		//delete and remake permanent storage export_array:
		delete [] this->export_array;

		this->export_array = new TopClass*[export_array_size_limit + 64];    

		//Load the new export_array:
		for( i=0 ; i<this->export_array_size_limit ; i++ )
			{
			this->export_array[i] = temp_export_array[i];
			}
		
		//Set new export_array_size_limit:
		this->export_array_size_limit += 64;

		//free the temporary storage array:
		delete [] temp_export_array;
		}

	//Add the ptr_arg to the array:
	this->export_array[this->export_array_count++] = (TopClass *) ptr_arg;
	
	return;

}


/*
 * get_export_array_count():
 */
int Interface_Body::get_export_array_count()	//Provide access to private members.
{

	return( this->export_array_count );

}


/*
 * run_scoped_name_array_i_buildGSIobject(): 
 */
SuperClass *Interface_Body::run_export_array_i_buildGSIobject( int i )	//Provide access to private members.
{

	return( this->export_array[i]->buildGSIobject( 0 ) );

}


/*
 * delete_export_array_element(): 
 */
void Interface_Body::delete_export_array_element( int i )	//Provide access to private members.
{

	//Free the object whose pointer is held at athe ith location:
	
	//Comment out the following for now since we are going to delete all objects globally:
	//delete this->export_array[i];
	
	return;

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Interface_Body::buildGSIobject( SuperClass *faux_arg )
{

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Body::buildGSIobject()" << endl;

	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the 
	//Interface_Header constructs from this object's data will be performed in 
	//the calling object's buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Interface_Header***************************
/*
 * Interface_Header - Constructor #1     
 */
Interface_Header::Interface_Header( char *keyword_arg, char *identifier_name_arg ) : TopClass()
{   										        
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Header Constructor #1" << endl;

	//Allocate storage for the keyword parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	//Allocate storage for the keyword parameter: 
	this->identifier_name = new char[strlen(identifier_name_arg)+1];
	strcpy( this->identifier_name, identifier_name_arg );

	//Set inheritance_spec to null, since it is not used here:
	this->inheritance_spec = 0;
	

	return;

}


/*
 * Interface_Header - Constructor #2     
 */
Interface_Header::Interface_Header( char *keyword_arg, char *identifier_name_arg, void *inheritance_spec_arg ) : TopClass()
{   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Header Constructor #1" << endl;

	//Allocate storage for the keyword parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	//Allocate storage for the keyword parameter: 
	this->identifier_name = new char[strlen(identifier_name_arg)+1];
	strcpy( this->identifier_name, identifier_name_arg );

	//Handle inheritance_spec:
	this->inheritance_spec = (TopClass *) inheritance_spec_arg;
	

	return;

}

	
/*
 * Interface_Header - Destructor
 */
Interface_Header::~Interface_Header()
{                   
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Header Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->identifier_name;


	return;
}


/*
 * get_identifier_name():
 *
 * post-conditions: The interface_header name was returned.
 */
char *Interface_Header::get_identifier_name()	//Provide access to private members.
{

	return( this->identifier_name );

}


/*
 * get_inheritance_spec_ptr():
 */
TopClass *Interface_Header::get_inheritance_spec_ptr()	//Provide access to private members.
{

	return( this->inheritance_spec );

}


/*
 * run_inheritance_spec_ptr_buildGSIobject(): 
 */
SuperClass *Interface_Header::run_inheritance_spec_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->inheritance_spec->buildGSIobject( 0 ) );

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 */
SuperClass *Interface_Header::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Header::buildGSIobject()" << endl;

	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the 
	//Interface_Header constructs from this object's data will be performed in 
	//the calling object's buildGSIobject() method:
	return( (SuperClass *) this );
	
}


//**************************Class: Interface_Dcl***************************
/*
 * Interface_Dcl - Constructor
 */
Interface_Dcl::Interface_Dcl( void *interface_header_arg, void *interface_body_arg ) : TopClass()
{   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Dcl Constructor" << endl;

	//Load the pointer variables:
	this->interface_header = (TopClass *) interface_header_arg;
	this->interface_body = (TopClass *) interface_body_arg;
	

	return;

}

	
/*
 * Interface_Dcl - Destructor
 */
Interface_Dcl::~Interface_Dcl()
{                   
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Dcl Destructor" << endl;

	return;

}

/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Interface_Dcl::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Interface_Dcl::buildGSIobject()" << endl;

	int						i;
	int						local_scoped_name_array_count;
	int						local_export_array_count;
	g2_interface_token		*ifaceDcl;
	g2_inheritance_token	*inheritanceToken;
	Interface_Header		*ifaceHeader;
	Interface_Body			*ifaceBody;
	Inheritance_Spec		*inheritanceSpec;


	//Build an interface object:
	ifaceDcl = new g2_interface_token();

	//*******Begin Interface_Header handling:
	//Retrieve a pointer to the Interface_Header object:
	//Cast to the specific type, since there will only be one possible type:
	ifaceHeader = (Interface_Header *) this->interface_header->buildGSIobject( 0 );

	//Add the name of the interface:
	ifaceDcl->m_name = ifaceHeader->get_identifier_name();

	//Build inheritance token:
	//NOT USED:inheritanceToken = new g2_inheritance_token();

	//Add inheritance_spec parameters if they are applicable:
	//(NULL indicates no inheritance_spec present).
	if( ifaceHeader->get_inheritance_spec_ptr() != 0 )	
		{
		//Build inheritance token:
		inheritanceToken = new g2_inheritance_token();

		//Retrieve a pointer to the Inheritance_Spec object:
		//Cast to the specific type, since there will only be one possible type:
		inheritanceSpec = (Inheritance_Spec *) ifaceHeader->run_inheritance_spec_ptr_buildGSIobject();

		//Load the scoped_name members:
		local_scoped_name_array_count = inheritanceSpec->get_scoped_name_array_count();
		for( i=0 ; i<local_scoped_name_array_count ; i++ )
			{										 
			//Build an individual scoped name list, which is returned as a Scoped_Name object,
			//and add it to the inheritance_spec object:
			inheritanceToken->m_contents.Add( (g2_token_object *) inheritanceSpec->run_scoped_name_array_i_buildGSIobject( i ) );
			}

		//Add the inheritance token to the interface token object:
		ifaceDcl->m_contents.Add( inheritanceToken );
		}
	else
		{
		//Do nothing for now.
		}
	//*******End Interface_Header handling:

	//*******Begin Interface_Body handling:
	//It is possible that the interface body is empty in which case a NULL is loaded 
	//into the Interface_Body pointer. Handle this case also:
	//Retrieve a pointer to the Interface_Body object if the body exists:
	if( this->interface_body != 0 )
		{
		//Cast to the specific type, since there will only be one possible type:
		ifaceBody = (Interface_Body *) this->interface_body->buildGSIobject( 0 );

		//Add the items that are in the export_array to the interface token:
		local_export_array_count = ifaceBody->get_export_array_count();
		for( i=0 ; i<local_export_array_count ; i++ )
			{
			//This cast may work, or it may need to be modified, or another method of 
			//determinig the type of the returned ptr will have to be found:
			ifaceDcl->m_contents.Add( (g2_token_object *) ifaceBody->run_export_array_i_buildGSIobject( i ) );

			//Free the parse tree object just accessed:

			//Comment out the following for now since we are going to delete all objects globally:
			//ifaceBody->delete_export_array_element( i );
			}
		}

	//*******End Interface_Body handling:

	//Return the interface token for attachment to the top-level object:
	return( ifaceDcl );

}


//**************************Class: Specification***************************
/*
 * Specification - Constructor     
 */
Specification::Specification() : TopClass()
{   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Specification Constructor" << endl;

	//Initialize these:
	definition_array_count = 0;
	definition_array_size_limit = 64;

	//Create the export_array: 64 TopClass objects:
	//This will be resized if necessary in the addDefinition method:
	this->definition_array = new TopClass*[definition_array_size_limit];


	return;

}

	
/*
 * Specification - Destructor
 */
Specification::~Specification()
{                   
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Specification Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->definition_array;

	return;
}


/*
 * addDefinition()
 * 
 * post-conditions: A pointer to a definition item was added to the definition_array.
 */
void Specification::addDefinition( void *ptr_arg )
{

	TopClass		**temp_definition_array;
	int				i;
	
	//Check if array resizing is necessary due to full array:
	if( this->definition_array_count == this->definition_array_size_limit )
		{
		//Build and load a temporary storage array:
		temp_definition_array = new TopClass*[this->definition_array_size_limit];

		for( i=0 ; i<this->definition_array_size_limit ; i++ )
			{
			temp_definition_array[i] = this->definition_array[i];
			}

		//delete and remake permanent storage definition_array:
		delete [] this->definition_array;

		this->definition_array = new TopClass*[definition_array_size_limit + 64];    

		//Load the new definition_array:
		for( i=0 ; i<this->definition_array_size_limit ; i++ )
			{
			this->definition_array[i] = temp_definition_array[i];
			}
		
		//Set new definition_array_size_limit:
		this->definition_array_size_limit += 64;

		//free the temporary storage array:
		delete [] temp_definition_array;
		}

	//Add the ptr_arg to the array:
	this->definition_array[this->definition_array_count++] = (TopClass *) ptr_arg;
	
	return;

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.											
 */
SuperClass *Specification::buildGSIobject( SuperClass *ptr_arg )
{	
	int				i;
	g2_file_token	**gsiObjModelroot;	
	
	//Recast pointer passed in here as its true type. It is passed in here 
	//as a SuperClass ptr for hacker convenience purposes.
	
	//Create the GSI object model's top-level 'FILE' object:
	gsiObjModelroot = (g2_file_token **) ptr_arg;		//Hack action!
	*gsiObjModelroot = new g2_file_token();

	//Add the filename: [Make more general later]
	(*gsiObjModelroot)->m_name = "GRIDXXX.IDL";
	
	//Traverse the definition array, building and adding as we go:
	for( i=0 ; i<this->definition_array_count ; i++ )
		{
		if( compiler_debug_state == DEBUG_ON )cout << "*****Processing definition_array[" << i << "]*************" << endl;
		(*gsiObjModelroot)->m_contents.Add( (g2_token_object *) this->definition_array[i]->buildGSIobject( 0 ) );
		}

	cout << "Definition Array Processing Completed. " << this->definition_array_count << " Arrays Processed...\n" << endl;
	
	if( compiler_debug_state == DEBUG_ON )cout << "*****************END OF Specification***********************" << endl;
 
	
	return( 0 );

}


//**************************Class: Op_Type_Spec***************************
/*
 * Op_Type_Spec - Constructor #1
 */
Op_Type_Spec::Op_Type_Spec( char *string_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Op_Type_Spec Constructor #1" << endl;

	//Allocate storage for the string parameter: 
	this->string = new char[strlen(string_arg)+1];
	strcpy( this->string, string_arg );

	//Handle other parameter initialization:
	this->param_type_spec_ptr = 0;


	return;

}


/*
 * Op_Type_Spec - Constructor #2
 */
Op_Type_Spec::Op_Type_Spec( void *ptr_arg ) : TopClass()
{   
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Op_Type_Spec Constructor #2" << endl;

	//Load pointer to the param_type_spec:
	this->param_type_spec_ptr = (TopClass *) ptr_arg;


	//Handle other parameter initialization:
	this->string = 0;


	return;

}


/*
 * Op_Type_Spec - Destructor
 */
Op_Type_Spec::~Op_Type_Spec()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Op_Type_Spec Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	if( this->string != 0 )
		delete [] this->string;

	
	return;
}


/*
 * run_param_type_spec_ptr_buildGSIobject():
 */
SuperClass *Op_Type_Spec::run_param_type_spec_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->param_type_spec_ptr->buildGSIobject( 0 ) );

}


/*
 * get_string():
 */
char *Op_Type_Spec::get_string()	//Provide access to private members.
{

	return( this->string );

}


/*
 * get_param_type_spec_ptr():
 */
TopClass *Op_Type_Spec::get_param_type_spec_ptr()	//Provide access to private members.
{

	return( this->param_type_spec_ptr );

} 


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Op_Type_Spec::buildGSIobject( SuperClass *faux_arg )
{

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Op_Type_Spec::buildGSIobject()" << endl;

	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the 
	//Op_Type_Spec constructs from this object's data will be performed in 
	//the calling object's buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Param_Dcl***************************
/*
 * Param_Dcl - Constructor     
 */
Param_Dcl::Param_Dcl( char *param_attribute_arg, void *param_type_spec_ptr_arg, void *simple_declarator_arg ) : TopClass()
{   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Param_Dcl Constructor" << endl;

	//Allocate storage for char * parameters: 
	this->param_attribute = new char[strlen(param_attribute_arg)+1];
	strcpy( this->param_attribute, param_attribute_arg );
	
	//this->simple_declarator = new char[strlen(simple_declarator_arg)+1];
	//strcpy( this->simple_declarator, simple_declarator_arg );
											 
	this->simple_declarator = (TopClass *) simple_declarator_arg;

	this->param_type_spec_ptr = (TopClass *) param_type_spec_ptr_arg;

		
	return;

}

	
/*
 * Param_Dcl - Destructor
 */
Param_Dcl::~Param_Dcl()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Param_Dcl Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->param_attribute;
	//delete [] this->simple_declarator;
	 
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Param_Dcl::buildGSIobject( SuperClass *faux_arg )
{

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Param_Dcl::buildGSIobject()" << endl;

	g2_parm_token		*paramDcl;
	g2_string_token		*strToken;
	

	//Create a param token:
	paramDcl = new g2_parm_token();

	//Load the param_attribute state:
	if( !strcmp( this->param_attribute, "in" ) )
		paramDcl->m_direction = 1;
	else if( !strcmp( this->param_attribute, "out" ) )
		paramDcl->m_direction = 2;
	else if( !strcmp( this->param_attribute, "inout" ) )
		paramDcl->m_direction = 3;

	//Load the param_type:
	paramDcl->m_type.m_type = (g2_token_object *) this->param_type_spec_ptr->buildGSIobject( 0 );

	//Load the declarator:
	strToken = (g2_string_token *) this->simple_declarator->buildGSIobject( 0 );
	paramDcl->m_name = strToken->m_name;	//Usually we assign a char* to an m_name, 
											//but hopefully this assignment also works.

	//Return this object back to the calling method:
	return( paramDcl );

}



//**************************Class: Op_Dcl***************************
/*
 * Op_Dcl - Constructor
 */
Op_Dcl::Op_Dcl( int opattribute_flag_arg, void *op_type_spec_ptr_arg, char *operation_name_arg, void *param_dcl_array_arg[], int param_dcl_array_count_arg, void *raises_expr_ptr_arg, void *context_expr_ptr_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Op_Dcl Constructor" << endl;

	this->opattribute_flag = opattribute_flag_arg;

	//Allocate storage for the char * parameters: 
	this->operation_name = new char[strlen(operation_name_arg)+1];
	strcpy( this->operation_name, operation_name_arg );

	this->op_type_spec_ptr = (TopClass *) op_type_spec_ptr_arg;

	this->param_dcl_array = new TopClass*[param_dcl_array_count_arg];
	this->param_dcl_array_count = param_dcl_array_count_arg;

	for( i=0 ; i<param_dcl_array_count_arg ; i++ )
		{
		//No storage is allocated here since param_dcl_array only holds void *'s:
		this->param_dcl_array[i] = (TopClass *) param_dcl_array_arg[i];
		}

	this->raises_expr_ptr = (TopClass *) raises_expr_ptr_arg;
	this->context_expr_ptr = (TopClass *) context_expr_ptr_arg;


	return;

}

	
/*
 * Op_Dcl - Destructor
 */
Op_Dcl::~Op_Dcl()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Op_Dcl Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->operation_name;

	//Delete the param_dcl_array:
	delete [] this->param_dcl_array;

	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Op_Dcl::buildGSIobject( SuperClass *faux_arg )
{

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Op_Dcl::buildGSIobject()" << endl;

	g2_operation_token		*operDcl;
	g2_prim_type_token		*typetoken;
	Op_Type_Spec			*opTypeSpec_ptr;
	Raises_Expr				*raisesExpr;
	Context_Expr			*contextExpr;
	int						local_scoped_name_array_count;
	int						local_string_literal_count;
	int						i;	


	//Build an operation token object:
	operDcl = new g2_operation_token();

	//Add the operation name:
	operDcl->m_name = this->operation_name;

	//Handle op_attribute flag:
	if( this->opattribute_flag == NO_OPATTRIBUTE )
		operDcl->m_oneway = 0;
	else if( this->opattribute_flag == YES_OPATTRIBUTE )
		operDcl->m_oneway = 1;

	//*******Begin Op_Type_Spec handling:
	//Retrieve a pointer to the Op_Type_Spec object:
	//Cast to the specific type, since there will only be one possible type:
	opTypeSpec_ptr = (Op_Type_Spec *) this->op_type_spec_ptr->buildGSIobject( 0 );

	if( (opTypeSpec_ptr->get_string() == 0) && (opTypeSpec_ptr->get_param_type_spec_ptr() != 0) )
		{
		//We have a pointer to a param_type_spec:
		operDcl->m_type.m_type = (g2_token_object *) opTypeSpec_ptr->run_param_type_spec_ptr_buildGSIobject();
		}
	else if( (opTypeSpec_ptr->get_string() != 0) && (opTypeSpec_ptr->get_param_type_spec_ptr() == 0) )
		{
		//We have a string: "void"
		//Create a symbol token and load it:
		typetoken = new g2_prim_type_token();
		typetoken->m_name = toUpperPlus( opTypeSpec_ptr->get_string() );		//Storage is allocated by overloaded '=' operator.

		operDcl->m_type.m_type = typetoken;
		}
	//*******End Op_Type_Spec handling.

	//*******Begin Param_Dcl array handling:
	//Load the param dcls:
	for( i=0 ; i<this->param_dcl_array_count ; i++ )
		{
		//All the 'Add' functions are G2OrbContained subclass ops, so this is a safe cast:
		operDcl->m_parms.Add( (g2_token_object *) this->param_dcl_array[i]->buildGSIobject( 0 ) );
		}
	//*******End Param_Dcl array handling:

	//*******Begin Raises_Expr handling:
	if( this->raises_expr_ptr != 0 )
		{
		//We have a Raises_Expr object to process:
		//Retrieve a pointer to the Raises_Expr object:
		//Cast to the specific type, since there will only be one possible type:
		raisesExpr = (Raises_Expr *) this->raises_expr_ptr->buildGSIobject( 0 );
		
		//Load the scoped_name members contained in the Raises_Expr object:
		local_scoped_name_array_count = raisesExpr->get_scoped_name_array_count();
		for( i=0 ; i<local_scoped_name_array_count ; i++ )
			{										 
			//Build an individual scoped name list, which is returned as a Scoped_Name object,
			//and add it to the operation token object:
			operDcl->m_exceptions.Add( (g2_token_object *) raisesExpr->run_scoped_name_array_i_buildGSIobject( i ) );
			}
		}
	else
		{
		//Do nothing for now.
		}
	//*******End Raises_Expr handling:

	//*******Begin Context_Expr handling:
	if( this->context_expr_ptr != 0 )
		{
		//We have a Context_Expr object to process:
		//Retrieve a pointer to the Context_Expr object:
		//Cast to the specific type, since there will only be one possible type:
		contextExpr = (Context_Expr *) this->context_expr_ptr->buildGSIobject( 0 );
		
		//Load the strings contained in the string_literal members which are contained in the 
		//Context_Expr object:
		local_string_literal_count = contextExpr->get_string_literal_count();
		for( i=0 ; i<local_string_literal_count ; i++ )
			{
			operDcl->m_contexts.Add( (g2_string_token *) contextExpr->run_string_literal_array_i_buildGSIobject( i ) );
			}
		}
	else
		{
		//Do nothing for now.
		}
	//*******End Context_Expr handling:
	
	//Return the operation token for further processing:
	return( operDcl );

}


//**************************Class: Enum_Type***************************
/*
 * Enum_Type - Constructor
 */
Enum_Type::Enum_Type( char *keyword_arg, char *enum_name_arg, char *enumerator_array_arg[], int enumerator_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Enum_Type Constructor" << endl;

	//Allocate storage for the char * parameters: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->enum_name = new char[strlen(enum_name_arg)+1];
	strcpy( this->enum_name, enum_name_arg );
	
	this->enumerator_array = new char*[enumerator_array_count_arg];
	this->enumerator_array_count = enumerator_array_count_arg;

	for( i=0 ; i<enumerator_array_count_arg ; i++ )
		{
		this->enumerator_array[i] = new char[strlen(enumerator_array_arg[i])+1];
		strcpy( this->enumerator_array[i], enumerator_array_arg[i] );
		}

	
	return;

}

	
/*
 * Enum_Type - Destructor
 */
Enum_Type::~Enum_Type()
{                   
	int		i;

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Enum_Type Destructor" << endl;
		
	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->enum_name;

	//Delete all of the array elements:
	for( i=0 ; i<this->enumerator_array_count ; i++ )
		{
		//The elements in the array are char*:
		delete [] this->enumerator_array[i];	
		}

	//Delete the array itself:
	delete [] this->enumerator_array;
 
	
	return;
	
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Enum_Type::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Enum_Type::buildGSIobject()" << endl;

	g2_enum_token			*enumType;
	g2_string_token			*str;
	int						i;


	//Build the enum_type object:
	enumType = new g2_enum_token();

	//Add the enum's name:
	enumType->m_name = this->enum_name;

	//Load the enumerator values:
	for( i=0 ; i<this->enumerator_array_count ; i++ )
		{
		//Each enum member can be a simple string:
		str = new g2_string_token();

		//Overloaded '=' operator allocates storage:
		str->m_name = enumerator_array[i];

		//Add to enum_type object:
		enumType->m_values.Add( str );
		}

	//Pass back enum_type object for insertion into container object:
	return( enumType );

}


//**************************Class: Simple_Declarator***************************
/*
 * Simple_Declarator - Constructor     
 */
Simple_Declarator::Simple_Declarator( char *string_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Simple_Declarator Constructor" << endl;

	//Allocate storage for the string parameter: 
	this->string = new char[strlen(string_arg)+1];
	strcpy( this->string, string_arg );

	return;

}


/*
 * Simple_Declarator - Destructor
 */
Simple_Declarator::~Simple_Declarator()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Simple_Declarator Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->string;

	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Simple_Declarator::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Simple_Declarator::buildGSIobject()" << endl;

	g2_string_token			*str;
	
	//Create a g2_string_token to hold the declarator string:
	str = new g2_string_token();

	str->m_name = this->string;

	return( str );

}


//**************************Class: Member***************************
//***NOTE: Virtually identical to Type_Declarator class***
/*
 * Member - Constructor     
 */
Member::Member( void *type_spec_ptr_arg, void *declarator_array_arg[], int declarator_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Member Constructor" << endl;

	this->type_spec_ptr = (TopClass *) type_spec_ptr_arg;

	this->declarator_array = new TopClass*[declarator_array_count_arg];
	this->declarator_array_count = declarator_array_count_arg;

	for( i=0 ; i<declarator_array_count_arg ; i++ )
		{
		this->declarator_array[i] = (TopClass *) declarator_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Member - Destructor
 */																							  
Member::~Member()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Member Destructor" << endl;

	//Delete the declarator array:
	delete [] this->declarator_array;
 
	
	return;
}


/*
 * run_type_spec_ptr_buildGSIobject():
 */
SuperClass *Member::run_type_spec_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->type_spec_ptr->buildGSIobject( 0 ) );

}


/*
 * run_declarator_array_buildGSIobject():
 */
SuperClass *Member::run_declarator_array_buildGSIobject( int i )	//Provide access to private members.
{

	return( this->declarator_array[i]->buildGSIobject( 0 ) );

}


/*
 * get_declarator_array_count():
 */
int Member::get_declarator_array_count()	//Provide access to private members.
{

	return( this->declarator_array_count );

} 


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Member::buildGSIobject( SuperClass *faux_arg )
{
	
	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the Member
	//constructs from this object's data will be performed in the calling object's 
	//buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Struct_Type***************************
/*
 * Struct_Type - Constructor     
 */
Struct_Type::Struct_Type( char *keyword_arg, char *struct_name_arg, void *member_array_arg[], int member_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Struct_Type Constructor" << endl;

	//Allocate storage for the char* parameters: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->struct_name = new char[strlen(struct_name_arg)+1];
	strcpy( this->struct_name, struct_name_arg );

	this->member_array = new TopClass*[member_array_count_arg];
	this->member_array_count = member_array_count_arg;

	for( i=0 ; i<member_array_count_arg ; i++ )
		{
		//this->attr_dcl_array[i] = new char[strlen(attr_dcl_array_arg[i])+1];
		//strcpy( this->attr_dcl_array[i], attr_dcl_array_arg[i] );
		this->member_array[i] = (TopClass *) member_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Struct_Type - Destructor
 */
Struct_Type::~Struct_Type()
{                   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Struct_Type Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->struct_name;

	//Delete all of the array elements:
	for( i=0 ; i<this->member_array_count ; i++ )
		{
		//delete [] this->attr_dcl_array[i];
		}

	//Delete the array itself:
	delete [] this->member_array;
 
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Struct_Type::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Struct_Type::buildGSIobject()" << endl;

	g2_struct_token			*structType;
	g2_struct_mem_token		*struct_member;
	Member					*p1;
	int						i, j;
	int						local_declarator_array_count;

	//Build struct object:
	structType = new g2_struct_token();

	//Load name:
	structType->m_name = this->struct_name;
																
	//Load the struct members:
	for( i=0 ; i<this->member_array_count ; i++ )
		{
		//Build a struct member and load its type and identifier:
		struct_member = new g2_struct_mem_token();

		//Retrieve a pointer to the Member object:
		//p1 = (TopClass *) this->member_array[i]->buildGSIobject( 0 );
		//Cast to the specific type, since there will only be one possible type:
		p1 = (Member *) this->member_array[i]->buildGSIobject( 0 );
		
		//Build the Member's type spec and attach it to struct_mem_token:
		//struct_member->m_type = p1->type_spec_ptr->buildGSIobject( 0 );
		struct_member->m_type.m_type = (g2_token_object *) p1->run_type_spec_ptr_buildGSIobject();

		//Build and attach the various declarators to the struct_mem token:
		local_declarator_array_count = p1->get_declarator_array_count();
		for( j=0 ; j<local_declarator_array_count ; j++ )
			{
			//struct_member->m_name.Add( p1->declarator_array[i]->buildGSIobject( 0 ) );
			struct_member->m_name.Add( (g2_token_object *) p1->run_declarator_array_buildGSIobject( j ) );
			}
		
		//Add this member to the struct token:
		structType->m_members.Add( struct_member );

		}

	//return the struct object to the caller of this method for further processing:
	return( structType );

}


//**************************Class: Scoped_Name***************************
/*
 * Scoped_Name - Constructor     
 */
Scoped_Name::Scoped_Name( char *scoped_name_list_array_arg[], int scoped_name_list_array_count_arg, int scoped_name_scope_flag_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Scoped_Name Constructor" << endl;

	this->scoped_name_list_array = new char*[scoped_name_list_array_count_arg];
	this->scoped_name_list_array_count = scoped_name_list_array_count_arg;

	//The scoped_name_scope_flag is used to determine if a g2_scoped_name or 
	//g2_global_scoped_name token is to be built in the buildGSIobject method:
	this->scoped_name_scope_flag = scoped_name_scope_flag_arg;

	//This will be set by access functions if a unary_operator needs to be applied. If this value 
	//remains 0, no unary operator is applied, otherwise, the value of this variable is the ASCII
	//code of the unary_operator:
	this->unary_operator = 0;	
	
	for( i=0 ; i<scoped_name_list_array_count_arg ; i++ )
		{
		//Allocate storage for and load scoped_name_list_array:
		this->scoped_name_list_array[i] = new char[strlen(scoped_name_list_array_arg[i])+1];
		strcpy( this->scoped_name_list_array[i], scoped_name_list_array_arg[i] );
		}

	
	return;

}

	
/*
 * Scoped_Name - Destructor
 */
Scoped_Name::~Scoped_Name()
{                   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Scoped_Name Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	
	//Delete all of the array elements:
	for( i=0 ; i<this->scoped_name_list_array_count ; i++ )
		{
		//The elements in the array are char*:
		delete [] this->scoped_name_list_array[i];
		}

	//Delete the array itself:
	delete [] this->scoped_name_list_array;
 
	
	return;
}


/*
 * setUnaryOperator():
 * 
 * post-conditions: The unary operator's ASCII value was loaded.
 *
 */
void Scoped_Name::setUnaryOperator( int op_code )
{
	
	this->unary_operator = op_code;


	return;

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Scoped_Name::buildGSIobject( SuperClass *faux_arg )
{
		
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Scoped_Name::buildGSIobject()" << endl;

	g2_scoped_name_token		*scopedName;
	g2_global_scoped_name_token	*globalScopedName;
	g2_string_token				*str;
	int							i;


	//Construct the appropriate GSI object model token based on the 
	//value of the scoped_name_scope_flag data member:
	if( this->scoped_name_scope_flag == RELATIVE_SCOPE )
		{
		//Build the scoped_name object:
		scopedName = new g2_scoped_name_token();

		for( i=0 ; i<this->scoped_name_list_array_count ; i++ )
			{
			//Each scoped name can use a g2_string_token:
			str = new g2_string_token();

			//Overloaded '=' operator allocates storage:
			str->m_name = scoped_name_list_array[i];

			//Add to scoped_name object:
			scopedName->m_contents.Add( str );
			}
		
		//Pass back scoped_name object for insertion into container object:
		return( scopedName );
		}
	//else if( this->scoped_name_scope_flag == GLOBAL_SCOPE )
	else		//We have a GLOBAL_SCOPE scoped_name.
		{
		//Build the global_scoped_name object:
		globalScopedName = new g2_global_scoped_name_token();

		for( i=0 ; i<this->scoped_name_list_array_count ; i++ )
			{
			//Each global scoped name can use a g2_string_token:
			str = new g2_string_token();

			//Overloaded '=' operator allocates storage:
			str->m_name = scoped_name_list_array[i];

			//Add to global scoped_name object:
			globalScopedName->m_contents.Add( str );
			}
		
		//Pass back global_scoped_name object for insertion into container object:
		return( globalScopedName );
		}	

}

		 
//**************************Class: Literal*************************** Each specific literal type has its own subclass.
/*
 * Literal - Constructor     
 */
Literal::Literal() : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Literal Constructor" << endl;

	return;

}


/*
 * Literal - Destructor
 */
Literal::~Literal()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Literal Destructor" << endl;
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Literal::buildGSIobject( SuperClass *faux_arg )
{
	
	return( 0 );

}



//**************************Class: LongIntegerLiteral***************************
/*
 * LongIntegerLiteral - Constructor
 */		   
LongIntegerLiteral::LongIntegerLiteral( long longInt_arg ) : Literal()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside IntegerLiteral Constructor" << endl;
				    
	this->value_member = (long) longInt_arg;
	this->unary_operator = 0;

	return;

}


/*
 * LongIntegerLiteral - getValue()
 */		   
long LongIntegerLiteral::getValue()
{   
				    
	return( this->value_member );

}


/*
 * LongIntegerLiteral - setValue()
 */		   
void LongIntegerLiteral::setValue( long longInt_arg )
{   
				    
	this->value_member = longInt_arg;

}


/*
 * LongIntegerLiteral - applyUnaryOperator()
 */		   
int LongIntegerLiteral::applyUnaryOperator()
{   
	switch( this->unary_operator )
		{
		case '+':
			this->value_member = this->value_member;
			break;
		case '-':
			this->value_member = this->value_member * -1;
			break;
		case '~':
			this->value_member = (this->value_member + 1) * -1; //Ref: OMG spec, pg 3-19.
			break;
		default:
			break;
		}

	return( 0 );	//0 = SUCCESS


}


/*
 * setUnaryOperator():
 * 
 * post-conditions: The unary operator's ASCII value was loaded.
 *
 */
void LongIntegerLiteral::setUnaryOperator( int op_code )
{
	
	this->unary_operator = op_code;


	return;

}


/*
 * LongIntegerLiteral - Destructor
 */
LongIntegerLiteral::~LongIntegerLiteral()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside LongIntegerLiteral Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->string;

	//Only free if we have a char * allocated. How to tell this is the case ?

	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *LongIntegerLiteral::buildGSIobject( SuperClass *faux_arg )
{
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside LongIntegerLiteral::buildGSIobject()" << endl;

	//long		value_member;
	//int		unary_operator;

	g2_gsi_integer_constant_token	*longLiteral;
	
	//Build the g2_gsi_integer_constant_token:
	longLiteral = new g2_gsi_integer_constant_token();

	//Apply the unary operator to the value data member, if applicable:
	this->applyUnaryOperator();

	//Load GSI-side value:
	longLiteral->m_name = (gsi_int) this->value_member;

	//Return it:
	return( longLiteral );

}


//**************************Class: StringLiteral***************************
/*
 * StringLiteral - Constructor
 */		   
StringLiteral::StringLiteral( char *string_arg ) : Literal()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside String Constructor" << endl;
	
	this->value_member = new char[strlen(string_arg)+1];
	strcpy( this->value_member, string_arg );

		

	return;

}


/*
 * StringLiteral - applyUnaryOperator()
 */		   
int StringLiteral::applyUnaryOperator()
{   
	//Not a valid operation for strings:
	return( 1 );	//1 = FAILURE

}


/*
 * setUnaryOperator():
 * 
 * post-conditions: The unary operator's ASCII value was loaded.
 *
 */
void StringLiteral::setUnaryOperator( int op_code )
{
	
	if( compiler_debug_state == DEBUG_ON )cout << "Error in StringLiteral::setUnaryOperator(): This method should never be called" << endl;
	
	return;

}

  
/*
 * StringLiteral - Destructor
 */
StringLiteral::~StringLiteral()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside StringLiteral Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->value_member;

	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *StringLiteral::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside StringLiteral::buildGSIobject()" << endl;

	g2_string_token		*stringLiteral;
	
	//Build the gsi-bound token:
	stringLiteral = new g2_string_token();

	//Load GSI-side value:
	stringLiteral->m_name = this->value_member;

	//Return it:
	return( stringLiteral );

}


//**************************Class: CharLiteral***************************
/*
 * CharLiteral - Constructor
 */		   
CharLiteral::CharLiteral( char chr_arg ) : Literal()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside CharLiteral Constructor" << endl;
				    
	this->value_member = (char) chr_arg;

	return;

}


/*
 * CharLiteral - applyUnaryOperator()
 */		   
int CharLiteral::applyUnaryOperator()
{   
	//Not a valid operation for strings:
	return( 1 );	//1 = FAILURE

}


/*
 * setUnaryOperator():
 * 
 * post-conditions: The unary operator's ASCII value was loaded.
 *
 */
void CharLiteral::setUnaryOperator( int op_code )
{
	
	cout << "Error in CharLiteral::setUnaryOperator(): This method should never be called" << endl;

	return;

}


/*
 * CharLiteral - Destructor
 */
CharLiteral::~CharLiteral()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside CharLiteral Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	//delete [] this->string;

	//Only free if we have a char * allocated. How to tell this is the case ?

	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *CharLiteral::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside CharLiteral::buildGSIobject()" << endl;

	//Provide this typedef until an actual char token class exits:
////////	typedef g2_gsi_integer_constant_token g2_gsi_char_constant_token;

	g2_gsi_char_constant_token	*charLiteral;
	
	//Build the gsi-bound token:
	charLiteral = new g2_gsi_char_constant_token();

	//Load GSI-side value:
	charLiteral->m_namex = this->value_member;

	//Return it:
	return( charLiteral );


}


//**************************Class: DoubleLiteral***************************
/*
 * DoubleLiteral - Constructor
 */		   
DoubleLiteral::DoubleLiteral( double arg ) : Literal()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside IntegerLiteral Constructor" << endl;
				    
	this->value_member = (double) arg;
	this->unary_operator = 0;

	return;

}


/*
 * DoubleLiteral - applyUnaryOperator()
 */		   
int DoubleLiteral::applyUnaryOperator()
{   
	switch( this->unary_operator )
		{
		case '+':
			this->value_member = this->value_member;
			break;
		case '-':
			this->value_member = this->value_member * -1.0;
			break;
		case '~':
			//bitwise complement is not applicable to floating point numbers:
			return( 1 );	//1 = FAILURE
		default:
			break;
		}

	return( 0 );	//0 = SUCCESS

}


/*
 * setUnaryOperator():
 * 
 * post-conditions: The unary operator's ASCII value was loaded.
 *
 */
void DoubleLiteral::setUnaryOperator( int op_code )
{
	
	if( op_code != '~' )
		this->unary_operator = op_code;
	else
		cout << "Error in DoubleLiteral::setUnaryOperator(): '~' is not valid for floating point numbers." << endl;


	return;

}


/*
 * DoubleLiteral - getValue()
 */		   
double DoubleLiteral::getValue()
{   
				    
	return( this->value_member );

}


/*
 * DoubleLiteral - setValue()
 */		   
void DoubleLiteral::setValue( double arg )
{   
				    
	this->value_member = arg;

}



/*
 * DoubleLiteral - Destructor
 */
DoubleLiteral::~DoubleLiteral()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside DoubleLiteral Destructor" << endl;


	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *DoubleLiteral::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside DoubleLiteral::buildGSIobject()" << endl;

	g2_gsi_float_constant_token		*doubleLiteral;
	
	//Build the gsi-bound token:
	doubleLiteral = new g2_gsi_float_constant_token();

	//Apply the unary operator to the value data member, if applicable:
	this->applyUnaryOperator();

	//Load GSI-side value:
	doubleLiteral->m_name = this->value_member;

	//Return it:
	return( doubleLiteral );


}


//**************************Class: BooleanLiteral***************************
/*
 * BooleanLiteral - Constructor
 */		   
BooleanLiteral::BooleanLiteral( char *boolean_arg ) : Literal()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Boolean Constructor" << endl;
	
	this->value_member = new char[strlen(boolean_arg)+1];
	strcpy( this->value_member, boolean_arg );

		

	return;

}


/*
 * BooleanLiteral - applyUnaryOperator()
 */		   
int BooleanLiteral::applyUnaryOperator()
{   
	//Not a valid operation for strings:
	return( 1 );	//1 = FAILURE

}


/*
 * setUnaryOperator():
 * 
 * post-conditions: The unary operator's ASCII value was loaded.
 *
 */
void BooleanLiteral::setUnaryOperator( int op_code )
{
	
	cout << "Error in BooleanLiteral::setUnaryOperator(): This method should never be called." << endl;

	return;

}

  
/*
 * BooleanLiteral - Destructor
 */
BooleanLiteral::~BooleanLiteral()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside BooleanLiteral Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->value_member;

	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *BooleanLiteral::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside BooleanLiteral::buildGSIobject()" << endl;

	g2_gsi_symbol_constant_token	*booleanLiteral;
	
	//Build the gsi-bound token:
	booleanLiteral = new g2_gsi_symbol_constant_token();

	//Load GSI-side value:
	booleanLiteral->m_name = this->value_member;

	//Return it:
	return( booleanLiteral );

}

//**************************Class: Except_Dcl***************************
/*
 * Except_Dcl - Constructor     
 */
Except_Dcl::Except_Dcl( char *keyword_arg, char *except_name_arg, void *member_array_arg[], int member_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Except_Dcl Constructor" << endl;

	//Allocate storage for the char* parameters: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->except_name = new char[strlen(except_name_arg)+1];
	strcpy( this->except_name, except_name_arg );

	this->member_array = new TopClass*[member_array_count_arg];
	this->member_array_count = member_array_count_arg;

	for( i=0 ; i<member_array_count_arg ; i++ )
		{
		this->member_array[i] = (TopClass *) member_array_arg[i];		//No storage needed. Pointers only.
		}

	//If member_array_count is 0 (except_dcl:case 1), then set the member_array to NULL:
	if( member_array_count_arg == 0 )
		this->member_array = 0;

	
	return;

}

	
/*
 * Except_Dcl - Destructor
 */
Except_Dcl::~Except_Dcl()
{                   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Except_Dcl Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->except_name;

	//Delete all of the array elements:
	for( i=0 ; i<this->member_array_count ; i++ )
		{
		//delete [] this->attr_dcl_array[i];
		}

	//Delete the array itself:
	delete [] this->member_array;
 
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Except_Dcl::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Except_Dcl::buildGSIobject()" << endl;

	g2_except_token			*exceptDcl;
	g2_struct_mem_token		*except_member;		//These are used here in lieu of g2_except_mem_token, which does not exist.
	Member					*p1;
	int						i, j;
	int						local_declarator_array_count;

	//Build exception dcl object:
	exceptDcl = new g2_except_token();

	//Load name:
	exceptDcl->m_name = this->except_name;

	//Load the exception members:
	for( i=0 ; i<this->member_array_count ; i++ )
		{
		//Build an exception member and load its type and identifier:
		except_member = new g2_struct_mem_token();

		//Retrieve a pointer to the Member object:
		//p1 = (TopClass *) this->member_array[i]->buildGSIobject( 0 );
		//Cast to the specific type, since there will only be one possible type:
		p1 = (Member *) this->member_array[i]->buildGSIobject( 0 );
		
		//Build the Member's type spec and attach it to the mem_token object:
		//except_member->m_type = p1->type_spec_ptr->buildGSIobject( 0 );
		except_member->m_type.m_type = (g2_token_object *) p1->run_type_spec_ptr_buildGSIobject();

		//Build and attach the various declarators to the mem_token object:
		local_declarator_array_count = p1->get_declarator_array_count();
		for( j=0 ; j<local_declarator_array_count ; j++ )
			{
			//except_member->m_name.Add( (g2_token_object *) p1->declarator_array[i]->buildGSIobject( 0 ) );
			except_member->m_name.Add( (g2_token_object *) p1->run_declarator_array_buildGSIobject( j ) );
			}
		
		//Add this member to the except token:
		exceptDcl->m_members.Add( except_member );

		}

	//return the except object to the caller of this method for further processing:
	return( exceptDcl );
	
}


//**************************Class: Const_Type***************************
/*
 * Const_Type - Constructor #1
 */
Const_Type::Const_Type( char *string_arg ) : TopClass()									          
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Const_Type Constructor #1" << endl;

	//Allocate storage for the string parameter: 
	this->string = new char[strlen(string_arg)+1];
	strcpy( this->string, string_arg );

	//Set ptr to NULL to indicate not in use:
	this->ptr = 0;

	return;

}


/*
 * Const_Type - Constructor #2
 */
Const_Type::Const_Type( void *ptr_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Const_Type Constructor #2" << endl;

	//Set the string parameter to NULL to indicate not in use:
	this->string = 0;
	
	//Set ptr to ptr_arg:
	this->ptr = (TopClass *) ptr_arg;

	return;

}


/*
 * Const_Type - Destructor
 */
Const_Type::~Const_Type()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Const_Type Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	if( this->string != 0 )
		delete [] this->string;
	
	return;
}

/*
 * run_ptr_buildGSIobject():
 */
SuperClass *Const_Type::run_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->ptr->buildGSIobject( 0 ) );

}


/*
 * get_string():
 */
char *Const_Type::get_string()	//Provide access to private members.
{

	return( this->string );

}


/*
 * get_ptr():
 */
TopClass *Const_Type::get_ptr()	//Provide access to private members.
{

	return( this->ptr );

} 


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Const_Type::buildGSIobject( SuperClass *faux_arg )
{
	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the constructs 
	//from this object's data will be performed in the calling object's buildGSIobject()
	//method:
	return( (SuperClass *) this );

}


//**************************Class: Const_Dcl*******************
/*
 * Const_Dcl - Constructor     
 */
Const_Dcl::Const_Dcl( char *keyword_arg, void *const_type_ptr_arg, char *name_arg, void *const_exp_ptr_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Const_Dcl Constructor" << endl;

	//Allocate storage for the keyword and name parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->name = new char[strlen(name_arg)+1];
	strcpy( this->name, name_arg );

	this->const_type_ptr = (TopClass *) const_type_ptr_arg;
	this->const_exp_ptr = (TopClass *) const_exp_ptr_arg;

		
	return;

}

	
/*
 * Const_Dcl - Destructor
 */
Const_Dcl::~Const_Dcl()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Const_Dcl Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->name;

		
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Const_Dcl::buildGSIobject( SuperClass *faux_arg )
{
	
	g2_const_token			*constDcl;
	Const_Type				*p1;
	g2_prim_type_token		*typetoken;

	//Build a const token:
	constDcl = new g2_const_token();

	//Load the name:
	constDcl->m_name = this->name;

	//Retrieve the const_type object:		    
	p1 = (Const_Type *) this->const_type_ptr->buildGSIobject( 0 );

	//Handle the type loading:
	if( p1->get_string() == 0 )
		{
		//Then we have a pointer to the type, rather than a simple char* string:
		//constDcl->m_type.m_type = p1->ptr->buildGSIobject( 0 );
		constDcl->m_type.m_type = (g2_token_object *) p1->run_ptr_buildGSIobject();
		}
	else if( p1->get_ptr() == 0 )
		{
		//Then we have a simple char* string, rather than a pointer to another type:
		//Load this as a symbol for GSI:
		//str = new g2_string_token();
		typetoken = new g2_prim_type_token();

		//str->m_name = p1->get_string();		//g2_string_token class will allocate storage.
		typetoken->m_name = TopClass::toUpperPlus( p1->get_string() );	//g2_prim_type_token class will allocate storage.

		constDcl->m_type.m_type = typetoken;
		}

	//Handle the const expression loading:
	constDcl->m_value.m_type = (g2_token_object *) this->const_exp_ptr->buildGSIobject( 0 );

	//Return the constDcl object for attachment to the calling object:
	return( constDcl );

}


//**************************Class: String_Type***************************
/*
 * String_Type - Constructor
 */
String_Type::String_Type( char *keyword_arg, void *positive_int_const_ptr_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside String_Type Constructor" << endl;

	//Allocate storage for the string parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	//This will be null if string had no dimension (string_type:case 2):
	this->positive_int_const_ptr = (TopClass *) positive_int_const_ptr_arg;

	return;

}


/*
 * String_Type - Destructor
 */
String_Type::~String_Type()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside String_Type Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *String_Type::buildGSIobject( SuperClass *faux_arg )
{
	g2_string_type_token	*str_type;
	SuperClass				*p1;

	str_type = new g2_string_type_token();

	//Get a built positive_int_const, if necessary:
	if( positive_int_const_ptr != 0 )
		p1 = positive_int_const_ptr->buildGSIobject( 0 );
	else
		p1 = 0;		//Signifies that there is no bounding parameter.

	//This cast may be safe. All of the type parameters should be subclasses of
	//g2_token_object:
	str_type->m_bound.m_type = (g2_token_object *) p1;
	

	return( str_type );

}


//**************************Class: Switch_Type_Spec***************************
/*
 * Switch_Type_Spec - Constructor #1
 */
Switch_Type_Spec::Switch_Type_Spec( char *string_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Switch_Type_Spec Constructor #1" << endl;

	//Allocate storage for the string parameter: 
	this->string = new char[strlen(string_arg)+1];
	strcpy( this->string, string_arg );

	//Set ptr to NULL to indicate not in use:
	this->ptr = 0;

	return;

}


/*
 * Switch_Type_Spec - Constructor #2
 */
Switch_Type_Spec::Switch_Type_Spec( void *ptr_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Switch_Type_Spec Constructor #2" << endl;

	//Set the string parameter to NULL to indicate not in use:
	this->string = 0;
	
	//Set ptr to ptr_arg:
	this->ptr = (TopClass *) ptr_arg;

	return;

}


/*
 * Switch_Type_Spec - Destructor
 */
Switch_Type_Spec::~Switch_Type_Spec()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Switch_Type_Spec Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	if( this->string != 0 )
		delete [] this->string;
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Switch_Type_Spec::buildGSIobject( SuperClass *faux_arg )
{						  

/*%%%%%%%%%%%%%%%%
	g2_prim_type_token		*typetoken;	
	
	typetoken = new g2_prim_type_token(); 
				
	typetoken->m_name = toUpperPlus( this->string );

%%%%%%%%%%%%%%%%*/
	
	g2_union_switch_token	*switchType;
	//YYYg2_string_token			*str;
	//g2_gsi_symbol_constant_token	*sym;
	g2_prim_type_token		*typetoken;	
	

	//Build a switch_type token:
	switchType = new g2_union_switch_token;

	//Handle the type loading:
	if( this->string == 0 )
		{											   
		//Then we have a pointer to the type, rather than a simple char* string:
		switchType->m_type.m_type = (g2_token_object *) this->ptr->buildGSIobject( 0 );
		}
	else if( this->ptr == 0 )
		{
		//Then we have a simple char* string, rather than a pointer to another type:
		//Load this as a symbol:
		//YYYstr = new g2_string_token();
		//sym = new g2_gsi_symbol_constant_token();
		typetoken = new g2_prim_type_token();

		//YYYstr->m_name = this->string;		//g2_string_token class will allocate storage.
		//sym->m_name = this->string;				//g2_gsi_symbol_constant_token class will allocate storage.
		typetoken->m_name = toUpperPlus( this->string );


		//YYYswitchType->m_type.m_type = str;
		//switchType->m_type.m_type = sym;
		switchType->m_type.m_type = typetoken;
		}

	//Return the switchType object for attachment to the calling object:
	return( switchType );

}


//**************************Class: Element_Spec***************************
/*
 * Element_Spec - Constructor     
 */
Element_Spec::Element_Spec( void *type_spec_ptr_arg, void *declarator_ptr_arg ) : TopClass()
{   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Element_Spec Constructor" << endl;

	this->type_spec_ptr = (TopClass *) type_spec_ptr_arg;
	this->declarator_ptr = (TopClass *) declarator_ptr_arg;

		
	return;
}

	
/*
 * Element_Spec - Destructor
 */
Element_Spec::~Element_Spec()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Element_Spec Destructor" << endl;

	return;
}


/*
 * run_declarator_ptr_buildGSIobject():
 */
SuperClass *Element_Spec::run_declarator_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->declarator_ptr->buildGSIobject( 0 ) );

}


/*
 * run_type_spec_ptr_buildGSIobject(): 
 */
SuperClass *Element_Spec::run_type_spec_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->type_spec_ptr->buildGSIobject( 0 ) );

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Element_Spec::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Element_Spec::buildGSIobject()" << endl;

	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the Element_Spec
	//constructs from this object's data will be performed in the calling object's 
	//buildGSIobject() method:
	return( (SuperClass *) this );
}


//**************************Class: Case_Label***************************
/*
 * Case_Label - Constructor
 */
Case_Label::Case_Label( char *string_arg, void *const_exp_ptr_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Case_Label Constructor" << endl;

	//Allocate storage for the string parameter: 
	this->string = new char[strlen(string_arg)+1];
	strcpy( this->string, string_arg );

	//This will be null if string had no dimension (case_label:case 2):
	this->const_exp_ptr = (TopClass *) const_exp_ptr_arg;

	return;

}


/*
 * Case_Label - Destructor
 */
Case_Label::~Case_Label()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Case_Label Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->string;
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Case_Label::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Case_Label::buildGSIobject()" << endl;

	g2_prim_type_token			*typetoken;

	//If const_exp_ptr is NULL, then we have encountered a 'default' keyword in the 
	//case specification. In this situation, assign 'default' to a g2_prim_type_token 
	//(g2 symbol type), set all characters to upper case, and return it. Otherwise, 
	//call the buildGSIobject() method for whatever the const_exp_ptr is pointing to, 
	//and return the appropriate pointer:

	if( this->const_exp_ptr == 0 )
		{
		typetoken = new g2_prim_type_token();

		typetoken->m_name = TopClass::toUpperPlus( this->string );		//Storage is allocated by the overloaded '=' operator.

		return( typetoken );
		}
	else
		{
		//Build the object which is being pointed to:
		return( this->const_exp_ptr->buildGSIobject( 0 ) );
		}

}


//**************************Class: Case***************************
/*
 * Case - Constructor     
 */
Case::Case( void *case_label_array_arg[], int case_label_array_count_arg, void *element_spec_ptr_arg ) : TopClass()
{   
	int		i;

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Case Constructor" << endl;

	this->case_label_array = new TopClass*[case_label_array_count_arg];
	this->case_label_array_count = case_label_array_count_arg;

	for( i=0 ; i<case_label_array_count_arg ; i++ )
		{
		this->case_label_array[i] = (TopClass *) case_label_array_arg[i];		//No storage needed. Pointers only.
		}

	this->element_spec_ptr = (TopClass *) element_spec_ptr_arg;

	
	return;

}

	
/*
 * Case - Destructor
 */
Case::~Case()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Case Destructor" << endl;

	//Delete the array itself:
	delete [] this->case_label_array;
 
	
	return;
}


/*
 * run_element_spec_ptr_buildGSIobject(): 
 */
SuperClass *Case::run_element_spec_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->element_spec_ptr->buildGSIobject( 0 ) );

}


/*
 * get_case_label_array_count(): 
 */
int Case::get_case_label_array_count()	//Provide access to private members.
{

	return( this->case_label_array_count );

}


/*
 * run_case_label_array_buildGSIobject():
 */
SuperClass *Case::run_case_label_array_buildGSIobject( int i )	//Provide access to private members.
{

	return( this->case_label_array[i]->buildGSIobject( 0 ) );

}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Case::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Case::buildGSIobject()" << endl;

	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the Case
	//constructs from this object's data will be performed in the calling object's 
	//buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Union_Type***************************
/*
 * Union_Type - Constructor     
 */
Union_Type::Union_Type( char *keyword_arg, char *union_name_arg, char *string_arg, void *switch_type_spec_ptr_arg, void *switch_body_array_arg[], int switch_body_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Union_Type Constructor" << endl;

	//Allocate storage for the char * parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );
	this->union_name = new char[strlen(union_name_arg)+1];
	strcpy( this->union_name, union_name_arg );
	this->string = new char[strlen(string_arg)+1];
	strcpy( this->string, string_arg );

	this->switch_type_spec_ptr = (TopClass *) switch_type_spec_ptr_arg;

	this->switch_body_array = new TopClass*[switch_body_array_count_arg];
	this->switch_body_array_count = switch_body_array_count_arg;

	for( i=0 ; i<switch_body_array_count_arg ; i++ )
		{
		this->switch_body_array[i] = (TopClass *) switch_body_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Union_Type - Destructor
 */
Union_Type::~Union_Type()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Union_Type Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->union_name;
	delete [] this->string;

	//Delete the array itself:
	delete [] this->switch_body_array;
 
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Union_Type::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Union_Type::buildGSIobject()" << endl;

	g2_union_token			*unionType;
	//XXXg2_union_switch_token	*switchType;
	g2_union_case_token		*caseType;
	Case					*p1;
	Element_Spec			*p2;
	int						i, j;
	int						local_case_label_array_count;

	//Build union object:
	unionType = new g2_union_token();

	//Load name:
	unionType->m_name = this->union_name;

	//Build switch type object:
	//XXXswitchType = new g2_union_switch_token();

	//Add the switch_type_spec object to the switch token object:
	//XXXswitchType->m_type.m_type = (g2_token_object *) switch_type_spec_ptr->buildGSIobject( 0 );

	//Add the switch token to the union:
	//XXXunionType->m_contents.Add( switchType );
	unionType->m_contents.Add( (g2_token_object *) switch_type_spec_ptr->buildGSIobject( 0 ) );

	//Load the union token with case tokens:
	for( i=0 ; i<this->switch_body_array_count ; i++ )
		{
		//Build and load a union case token:
		caseType = new g2_union_case_token();

		//Retrieve a pointer to the ith Case object:
		p1 = (Case *) this->switch_body_array[i]->buildGSIobject( 0 );

		//Retrieve a pointer to the ith Case object's Element_Spec object:
		//p2 = (Element_Spec *) p1->element_spec_ptr->buildGSIobject( 0 );
		p2 = (Element_Spec *) p1->run_element_spec_ptr_buildGSIobject();

		//Build the Case's element spec components and attach them to the union case token:
		//caseType->m_type.m_type = p2->type_spec_ptr->buildGSIobject( 0 );
		//caseType->m_name.m_type = p2->declarator_ptr->buildGSIobject( 0 );
		caseType->m_type.m_type = (g2_token_object *) p2->run_type_spec_ptr_buildGSIobject();
		caseType->m_name.m_type = (g2_token_object *) p2->run_declarator_ptr_buildGSIobject();
		

		//Access the Case's case_label array and add each label to this union case token:
		local_case_label_array_count = p1->get_case_label_array_count();
		for( j=0 ; j<local_case_label_array_count ; j++ )
			{
			//May be able to cast this to an OrbContained or token object:
			//caseType->m_val.Add( p1->case_label_array[i]->buildGSIobject( 0 ) );
			caseType->m_val.Add( (g2_token_object *) p1->run_case_label_array_buildGSIobject( j ) );
			}
		
		//Add this union case token to the union token:
		unionType->m_contents.Add( caseType );

		}

	//return the struct object to the caller of this method for further processing:
	return( unionType );

}


//**************************Class: Sequence_Type*******************
/*
 * Sequence_Type - Constructor     
 */
Sequence_Type::Sequence_Type( char *keyword_arg, void *simple_type_spec_ptr_arg, void *positive_int_const_ptr_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Sequence_Type Constructor" << endl;

	//Allocate storage for the char * parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->simple_type_spec_ptr = (TopClass *) simple_type_spec_ptr_arg;

	//The following pointer may be set to NULL by build function (sequence_type:case 2):
	this->positive_int_const_ptr = (TopClass *) positive_int_const_ptr_arg;

		
	return;

}

	
/*
 * Sequence_Type - Destructor
 */
Sequence_Type::~Sequence_Type()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Sequence_Type Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
			
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Sequence_Type::buildGSIobject( SuperClass *faux_arg )
{
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Sequence_Type::buildGSIobject()" << endl;

	g2_seq_type_token	*seq_type;
	SuperClass			*p1, *p2;


	seq_type = new g2_seq_type_token();

	//Get a built simple_type_spec:
	p1 = simple_type_spec_ptr->buildGSIobject( 0 );

	//This cast may be safe. All of the type parameters should be subclasses of
	//g2_token_object:
	seq_type->m_type.m_type = (g2_token_object *) p1;

	//Get a built positive_int_const, if necessary:
	if( positive_int_const_ptr != 0 )
		p2 = positive_int_const_ptr->buildGSIobject( 0 );
	else
		p2 = 0;		//Signifies that there is no bounding parameter.

	//Casting to g2_token object* should be okay:
	seq_type->m_bound.m_type = (g2_token_object *) p2;


	return( seq_type );

}


//**************************Class: Array_Declarator***************************
/*
 * Array_Declarator - Constructor     
 */
Array_Declarator::Array_Declarator( char *array_name_arg, void *fixed_array_size_array_arg[], int fixed_array_size_count_arg ) : TopClass()
{   
	int		i;

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Array_Declarator Constructor" << endl;

	//Allocate storage for the char * arg:
	this->array_name = new char[strlen(array_name_arg)+1];
	strcpy( this->array_name, array_name_arg );

	this->fixed_array_size_array = new TopClass*[fixed_array_size_count_arg];
	this->fixed_array_size_count = fixed_array_size_count_arg;

	for( i=0 ; i<fixed_array_size_count_arg ; i++ )
		{
		this->fixed_array_size_array[i] = (TopClass *) fixed_array_size_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;
}

	
/*
 * Array_Declarator - Destructor
 */
Array_Declarator::~Array_Declarator()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Array_Declarator Destructor" << endl;

	//Delete any allocated storage:
	delete [] this->array_name;
	delete [] this->fixed_array_size_array;
 
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Array_Declarator::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Array_Declarator::buildGSIobject()" << endl;

	g2_array_token		*arrayDcl;
	int					i;

	//Build the array_declarator:
	arrayDcl = new g2_array_token();
	//Load name:
	arrayDcl->m_name = this->array_name;

	for( i=0 ; i<this->fixed_array_size_count ; i++ )
		{
		//Add the dimension declarators to the array object:
		arrayDcl->m_contents.Add( (g2_token_object *) fixed_array_size_array[i]->buildGSIobject( 0 ) );
		}


	return( arrayDcl );

}


//**************************Class: Type_Declarator***************************
//***NOTE: Virtually identical to Member class***
/*
 * Type_Declarator - Constructor     
 */
Type_Declarator::Type_Declarator( void *type_spec_ptr_arg, void *declarator_array_arg[], int declarator_array_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Type_Declarator Constructor" << endl;

	this->type_spec_ptr = (TopClass *) type_spec_ptr_arg;

	this->declarator_array = new TopClass*[declarator_array_count_arg];
	this->declarator_array_count = declarator_array_count_arg;

	for( i=0 ; i<declarator_array_count_arg ; i++ )
		{
		this->declarator_array[i] = (TopClass *) declarator_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Type_Declarator - Destructor
 */																							  
Type_Declarator::~Type_Declarator()
{                   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Type_Declarator Destructor" << endl;

	//Delete the declarator array:
	delete [] this->declarator_array;
 
	
	return;
}


/*
 * run_type_spec_ptr_buildGSIobject():
 */
SuperClass *Type_Declarator::run_type_spec_ptr_buildGSIobject()	//Provide access to private members.
{

	return( this->type_spec_ptr->buildGSIobject( 0 ) );

}


/*
 * run_declarator_array_buildGSIobject():
 */
SuperClass *Type_Declarator::run_declarator_array_buildGSIobject( int i )	//Provide access to private members.
{

	return( this->declarator_array[i]->buildGSIobject( 0 ) );

}


/*
 * get_declarator_array_count():
 */
int Type_Declarator::get_declarator_array_count()	//Provide access to private members.
{

	return( this->declarator_array_count );

} 


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Type_Declarator::buildGSIobject( SuperClass *faux_arg )
{

	//Since this class does not have a counterpart in the GSI object model, the 
	//return object will be a pointer to this object. The building of the Type_Declarator
	//constructs from this object's data will be performed in the calling object's 		  
	//buildGSIobject() method:
	return( (SuperClass *) this );

}


//**************************Class: Type_Dcl_Case1***************************
/*
 * Type_Dcl_Case1 - Constructor
 */
Type_Dcl_Case1::Type_Dcl_Case1( char *keyword_arg, void *type_declarator_ptr_arg ) : TopClass()
{   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Type_Dcl_Case1 Constructor" << endl;

	//Allocate storage for the string parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	//This will be null if string had no dimension (case_label:case 2):
	this->type_declarator_ptr = (TopClass *) type_declarator_ptr_arg;

	return;

}


/*
 * Type_Dcl_Case1 - Destructor
 */
Type_Dcl_Case1::~Type_Dcl_Case1()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Type_Dcl_Case1 Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Type_Dcl_Case1::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Type_Dcl_Case1::buildGSIobject()" << endl;

	g2_typedef_token		*typeDclCase1;
	Type_Declarator			*p1;
	int						i;
	int						local_declarator_array_count;
																						 

	//Build type dcl case 1 object:
	typeDclCase1 = new g2_typedef_token();

	//Retrieve a pointer to the Type_Declarator object:
	p1 = (Type_Declarator *) this->type_declarator_ptr->buildGSIobject( 0 );
		
	//Build the Type_Declarator's type spec and attach it to the typeDclCase1 object:
	//typeDclCase1->m_type = p1->type_spec_ptr->buildGSIobject( 0 );
	typeDclCase1->m_type.m_type = (g2_token_object *) p1->run_type_spec_ptr_buildGSIobject();
	
	//Build and attach the various declarators to the type spec token:
	local_declarator_array_count = p1->get_declarator_array_count();
	for( i=0 ; i<local_declarator_array_count ; i++ )
		{
		//typeDclCase1->m_names.Add( p1->declarator_array[i]->buildGSIobject( 0 ) );
		typeDclCase1->m_names.Add( (g2_token_object *) p1->run_declarator_array_buildGSIobject( i ) );
		}
		
	//return the type spec for typdef to the caller of this method for further processing:
	return( typeDclCase1 );


}


//**************************Class: Forward_Dcl***************************
/*
 * Forward_Dcl - Constructor
 */
Forward_Dcl::Forward_Dcl( char *keyword_arg, char *identifier_name_arg ) : TopClass()
{   										        
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Forward_Dcl Constructor #1" << endl;

	//Allocate storage for the keyword parameter: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	//Allocate storage for the keyword parameter: 
	this->identifier_name = new char[strlen(identifier_name_arg)+1];
	strcpy( this->identifier_name, identifier_name_arg );

	
	return;

}


/*
 * Forward_Dcl - Destructor
 */
Forward_Dcl::~Forward_Dcl()
{                   
	
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Forward_Dcl Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->identifier_name;


	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Forward_Dcl::buildGSIobject( SuperClass *faux_arg )
{
	//NOTE: This code should generate output similar to John H's
	
	//Build an interface object:
	g2_interface_token *forwardDcl = new g2_interface_token();

	//Add the interface name:
	//HOPEFULLY OBSOLETE:forwardDcl->load_m_name( this->identifier_name );
	forwardDcl->m_name = this->identifier_name;

	//Return pointer to this forward declaration:
	return( forwardDcl );

}


//**************************Class: Module***************************
/*
 * Module - Constructor     
 */
Module::Module( char *keyword_arg, char *module_name_arg, void *module_definition_array_arg[], int module_definition_count_arg ) : TopClass()
{   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Module Constructor" << endl;

	//Allocate storage for the char* parameters: 
	this->keyword = new char[strlen(keyword_arg)+1];
	strcpy( this->keyword, keyword_arg );

	this->module_name = new char[strlen(module_name_arg)+1];
	strcpy( this->module_name, module_name_arg );

	this->module_definition_array = new TopClass*[128];
	this->module_definition_count = module_definition_count_arg;

	for( i=0 ; i<module_definition_count_arg ; i++ )
		{
		this->module_definition_array[i] = (TopClass *) module_definition_array_arg[i];		//No storage needed. Pointers only.
		}

	
	return;

}

	
/*
 * Module - Destructor
 */
Module::~Module()
{                   
	int		i;


	if( compiler_debug_state == DEBUG_ON )cout << "Inside Module Destructor" << endl;

	//Free allocated resources and perform general clean-up:
	delete [] this->keyword;
	delete [] this->module_name;

	//Delete all of the array elements:
	for( i=0 ; i<this->module_definition_count ; i++ )
		{
		//delete [] this->attr_dcl_array[i];
		}

	//Delete the array itself:
	delete [] this->module_definition_array;
 	   
	
	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 */
SuperClass *Module::buildGSIobject( SuperClass *faux_arg )
{

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Module::buildGSIobject()" << endl;

	g2_module_token			*moduleType;
	int						i;
	

	//Build module token:
	moduleType = new g2_module_token();

	//Load name:
	moduleType->m_name = this->module_name;

	//Load the definitions:
	for( i=0 ; i<this->module_definition_count ; i++ )
		{
		//All the 'Add' functions are G2OrbContained subclass ops, so this is a safe cast:
		moduleType->m_contents.Add( (g2_token_object *) this->module_definition_array[i]->buildGSIobject( 0 ) );

		//Free the parse tree object just accessed:

		//Comment out the following for now since we are going to delete all objects globally:
		//delete module_definition_array[i];

		}
				
	//Return module token to be added to appropriate container:
	return( moduleType );

}


//**************************Class: Math_Expression***************************
//This class will handle the mult_expr, add_expr, shift_expr, and_expr, xor_expr, 
//and or_expr cases in the parser file. Each object will have a math op passed in 
//when it is constructed.
/*
 * Math_Expression - Constructor     
 */
Math_Expression::Math_Expression( void *left_operand_ptr_arg, void *right_operand_ptr_arg, int operator_code_arg ) : TopClass()
{   

	if( compiler_debug_state == DEBUG_ON )cout << "Inside Math_Expression Constructor" << endl;

	this->left_operand_ptr = (TopClass *) left_operand_ptr_arg;
	this->right_operand_ptr = (TopClass *) right_operand_ptr_arg;
	this->operator_code = operator_code_arg;

		
	return;
}

	
/*
 * Math_Expression - Destructor
 */
Math_Expression::~Math_Expression()
{                   
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Math_Expression Destructor" << endl;

	return;
}


/*
 * buildGSIobject():
 * 
 * post-conditions: A GSI object was built.
 *
 * Since this function is virtual, it will be overloaded in all of the subclasses to
 * handle the particular requirements of building each type of object.
 */
SuperClass *Math_Expression::buildGSIobject( SuperClass *faux_arg )
{
	if( compiler_debug_state == DEBUG_ON )cout << "Inside Math_Expression::buildGSIobject()" << endl;

	g2_math_op_token	*mathExpr;
	char				*temp_str;

	mathExpr = new g2_math_op_token();
	temp_str = new char[8];

	//***Load mathExpr:
	//convert operator_code to a string for the GSI object model:
	if( this->operator_code == '<' )		//'<' is surrogate for '<<'
		strcpy( temp_str, "<<" );
	else if( this->operator_code == '>' )	//'>' is surrogate for '>>'
		strcpy( temp_str, ">>" );
	else
		{
		//Convert ASCII code for the operator to a string:
		sprintf( temp_str, "%c", this->operator_code );
		if( (compiler_debug_state == DEBUG_ON) && (temp_str != 0) )
			cout << "Math_Expression::buildGSIobject():temp_str= " << temp_str << endl;
		else if( (compiler_debug_state == DEBUG_ON) && (temp_str == 0) )
			cout << "Math_Expression::buildGSIobject():temp_str= (null)" << endl;

		}						       

	//Load the operator: 
	mathExpr->m_name = temp_str;
	
	//Since overloaded '=' operator in g2_math_op_token allocates its own storage, 
	//we can safely delete the temp_str:
	delete [] temp_str;

	//Load the operands:
	//These calls will work there way down through the buildGSIobjects() of other 
	//Math_expression objects until one is encountered which has only true operands, 
	//Then we will walk back up the tree.
	//This cast compiles, but may need to be revised later:
	mathExpr->val1.m_type = (g2_token_object *) this->left_operand_ptr->buildGSIobject( 0 );
	mathExpr->val2.m_type = (g2_token_object *) this->right_operand_ptr->buildGSIobject( 0 );
	
	
	return( mathExpr );

}



