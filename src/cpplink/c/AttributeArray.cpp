#include "AttributeArray.h"

namespace CppLink
{
/*-----------------------y-----------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  AttributeArray constructor.  
	//  Makes an array of specified number of
  //  items
 AttributeArray::AttributeArray(long pNumAttributes)
 {
   if (pNumAttributes == 0) {
     mSize = 0;
     mAttributes = NULL;
   }
   else {
     mSize = pNumAttributes;
     mAttributes = new Attribute[pNumAttributes];
   }
 }
  
  ///////////////////////////////////////////
	//
	//  AttributeArray destructor
	//
AttributeArray::~AttributeArray()
{   
  if (mAttributes)
    delete[] mAttributes;
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
long AttributeArray::getSize()
{
  return mSize;
}

  ///////////////////////////////////////////
	//
	//  item
	//    
Attribute& AttributeArray::attribute(long pIndex)
{
  // FIND ME.  Handle out of bounds reference here
  return mAttributes[pIndex];
}

  ///////////////////////////////////////////
	//
	//  operator []
	//    
Attribute& AttributeArray::operator[](long pIndex)
{
  // FIND ME.  Handle out of bounds reference here
  return mAttributes[pIndex];
}

}