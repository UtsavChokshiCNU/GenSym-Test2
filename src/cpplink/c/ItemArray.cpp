#include "ItemArray.h"
#include "Item.h"

namespace CppLink
{
/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  ItemArray constructor.  
	//  Makes an array of specified number of
  //  items
 ItemArray::ItemArray(long pNumItems)
 {
   if (pNumItems == 0) {
     mSize = 0;
     mItems = NULL;
   }
   else {
     mSize = pNumItems;
     mItems = new Item[pNumItems];
   }
 }
  
  ///////////////////////////////////////////
	//
	//  ItemArray destructor
	//
ItemArray::~ItemArray()
{
  if (mItems)
    delete[] mItems;
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
long ItemArray::getSize()
{
  return mSize;
}

  ///////////////////////////////////////////
	//
	//  item
	//    
Item& ItemArray::item(long pIndex)
{
  // FIND ME.  Handle out of bounds reference here
  return mItems[pIndex];
}

  ///////////////////////////////////////////
	//
	//  operator []
	//    
Item& ItemArray::operator[](long pIndex)
{
  // FIND ME.  Handle out of bounds reference here
  return mItems[pIndex];
}

}