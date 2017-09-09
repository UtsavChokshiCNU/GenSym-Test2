#include "OptionsArray.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  OptionsArray constructor
	//
 OptionsArray::OptionsArray
   (Option *pOptions,
   long pNumOptions):
 mOptions(pOptions),
 mSize(pNumOptions)
 {
 }
 
  ///////////////////////////////////////////
	//
	//  OptionsArray destructor
	//
               
OptionsArray::~OptionsArray()
{
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

long OptionsArray::getSize()
{
  return mSize;
}
Option OptionsArray::option(long pIndex)
{
  // FIND ME.  Check for incorrect index.
  return mOptions[pIndex];
}

Option OptionsArray::operator[](long pIndex)
{
  // FIND ME.  Check for incorrect index.
  return mOptions[pIndex];
}

}