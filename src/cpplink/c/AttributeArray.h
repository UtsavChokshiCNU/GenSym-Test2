/*----------------------------------------------------------------------
CLASS
    AttributeArray

KEYWORDS
    Attribute Item

AUTHOR
    Allan Scott
  
DESCRIPTION
	 An AttributeArray wraps an array of Item instances.

   Users construct an AttributeArray by passing in the number of Attributes
   they wish to be in the array:

   AttributeArray array = AttributeArray(1);

   Note that once an AttributeArray is allocated it cannot be increased or
   reduced in size (this is why it is called AttributeArray and not 
   AttributeVector).

   The AttributArray class supports the array access operator so that
   it is possible to modify individual items in the array easily,
   for example:

   array[0].setString("Bar");
   array[0].setAttrName("Foo");
   
   The size of an AttributeArray can be retrieved with the getSize() method.

   When an AttributeArray is deleted it will call delete on all the 
   attributes in the array.

   AttributeArrays are used widely in CppLink whenever arguments or results
   to remote procedure calls are represented.

LAST MODIFIED

    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ATTRIBUTE_ARRAY_H
#define _CPP_LINK_ATTRIBUTE_ARRAY_H

#include "api.h"
#include "Attribute.h"

namespace CppLink 
{

class API AttributeArray 
{
 public:
   AttributeArray(long pNumAttributes);
   ~AttributeArray();
      
   long getSize();
   void setSize(long pNewSize);
   
   Attribute& attribute(long pIndex);
  
   Attribute& operator[](long pIndex);

 private:
   Attribute * mAttributes;
   long mSize;
};

}


#endif // ifndef _CPP_LINK_ATTRIBUTE_ARRAY_H