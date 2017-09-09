#include "StartArgsArray.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/
	///////////////////////////////////////////
	//
	//  StartArgsArray constructor
	//
StartArgsArray::StartArgsArray(char *pStartArgs[],
   long pSize) :
mArgs(pStartArgs),
mSize(pSize)
 {  
 }
                
  ///////////////////////////////////////////
	//
	//  StartArgsArray destructor
	//
StartArgsArray::~StartArgsArray()
 {
 }


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  getSize
	//
long StartArgsArray::getSize()
{
  return mSize;
}

	///////////////////////////////////////////
	//
	//  getArgs
	//
char **StartArgsArray::getArgs()
{
  return mArgs;
}

	///////////////////////////////////////////
	//
	//  startArg
	//
char *StartArgsArray::startArg(long pIndex)
{
  // FIND ME.  Check for incorrect index.
  return mArgs[pIndex];
}

	///////////////////////////////////////////
	//
	//  operator []
	//
char *StartArgsArray::operator[](long pIndex)
{
  // FIND ME.  Check for incorrect index.
  return mArgs[pIndex];
}

}