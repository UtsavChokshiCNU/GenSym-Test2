#include "RPCAction.h"
#include "ItemArray.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  RPCAction constructor
	//
 RPCAction::RPCAction(Connection& pConnection,
   char *pName,
   ItemArray* pArgs) :
 ConnectionAction(pConnection),
   mArgs(pArgs),
   mDeleteArgsOnDeletion(false)
 {
   mName = new char [strlen(pName)+1] ;
   strcpy(mName, pName) ;
 }
 
	///////////////////////////////////////////
	//
	//  RPCAction destructor
	//
 RPCAction::~RPCAction() 
 {
   if (mArgs &&
     mDeleteArgsOnDeletion)
     delete mArgs;
   delete [] mName ;
 }
 
 
/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/


	///////////////////////////////////////////
	//
	//  getName
	//
char *RPCAction::getName() 
{
  return mName;
}

	///////////////////////////////////////////
	//
	//  getArgs
	//
ItemArray* RPCAction::getArgs() 
{
  return mArgs;
} 

	///////////////////////////////////////////
	//
	//  getDeleteArgsOnDeletion
	//
bool RPCAction::getDeleteArgsOnDeletion() 
{
  return mDeleteArgsOnDeletion;
} 

	///////////////////////////////////////////
	//
	//  setDeleteArgsOnDeletion
	//
void RPCAction::setDeleteArgsOnDeletion(bool pDeleteArgsOnDeletion) 
{
  mDeleteArgsOnDeletion = pDeleteArgsOnDeletion;
} 
	
}
