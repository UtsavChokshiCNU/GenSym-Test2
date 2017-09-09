/*----------------------------------------------------------------------
CLASS
    ItemArray

KEYWORDS
   Item

AUTHOR
   Allan Scott
   
DESCRIPTION
   An ItemArray wraps an array of Item instances.

   Users construct an ItemArray by passing in the number of Items
   they wish to be in the array:

   ItemArray array = ItemArray(1);

   Note that once an ItemArray is allocated it cannot be increased or
   reduced in size (this is why it is called ItemArray and not ItemVector).

   The ItemArray class supports the array access operator so that
   it is possible to modify individual items in the array easily,
   for example:

   array[0]->setString("Foo");
   
   The size of an ItemArray can be retrieved with the getSize() method.

   When an ItemArray is deleted it will call delete on all the items
   in the array.

   ItemArrays are used widely in CppLink whenever arguments or results
   to remote procedure calls are represented.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ITEM_ARRAY_H
#define _CPP_LINK_ITEM_ARRAY_H

#include "api.h"
#include "Item.h"

namespace CppLink 
{

class API ItemArray
{
 public:
   ItemArray(long pNumItems);
   ~ItemArray();
  
   long getSize();
   Item& item(long pIndex);

   Item& operator[](long pIndex);

 private:
   Item* mItems;
   long mSize;
};

}


#endif // ifndef _CPP_LINK_ITEM_ARRAY_H