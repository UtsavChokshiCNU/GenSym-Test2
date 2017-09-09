/*----------------------------------------------------------------------
CLASS
    Item

KEYWORDS
    ItemArray Attribute AttributeArray
    
AUTHOR
    Allan Scott
    
DESCRIPTION
    Item and it's subclass Attribute is used to represent all 
    Gsi data in CppLink.

    The Item class bears some resemblence to the gsi_item structure
    in GSI (although it is not binary compatable).
    
    To make an Item be a string item users will call the setString()
    method.

    To make an Item into a symbol item users will call the setSymbol()
    method.

    To make an Item into a logical item users will call the setBoolean()
    method.

    To make an Item into a NULL item users will call the setNull()
    method.

    To make an Item into structure then users will call the 
    setType() method with STRUCTURE_TYPE as an argument.

    To add attributes to a structure item users will create an
    AttributeArray and set it on the Item using the setAttrs() method.

    To make an Item into a sequence then users will call the setElements()
    method passing in an ItemArray for the Items in the sequence and
    the SEQUENCE_TYPE flag to indicate that the Item should be a sequence.
 
      
CURRENTLY SUPPORTED TYPES
    The enumeration GsiType represents all the different types of data
    that are supported by Gsi.
     
    Currently the following subset of these tyes are supported by
    CppLink:

    NULL_TYPE
    FLOAT_TYPE
    INTEGER_TYPE
    LOGICAL_TYPE
    SYMBOL_TYPE
    STRUCTURE_TYPE
    SEQUENCE_TYPE

    Support for G2 items and arrays are expected for a future 
    version of CppLink.

  
RECLAIMING ITEMS
    By default if the destructor of an Item is called it will not
    delete any child items (attributes or elements).

    Users may call the setDeleteSubItems() method to change this
    behavior and to cause child items to be deleted when an Item is
    deleted.


LAST MODIFIED
	
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ITEM_H
#define _CPP_LINK_ITEM_H

#include "api.h"
#include "gsi_main_cpp.h"


namespace CppLink
{

  enum API GsiType {
    NULL_TYPE = GSI_NULL_TAG,
    VALUE_TYPE = GSI_VALUE_TAG,
    QUANTITY_TYPE = GSI_QUANTITY_TAG,
    ITEM_TYPE = GSI_ITEM_TAG,
    HANDLE_TYPE = GSI_HANDLE_TAG,
    FLOAT_TYPE = GSI_FLOAT64_TAG,
    INTEGER_TYPE = GSI_INTEGER_TAG,
    LOGICAL_TYPE = GSI_LOGICAL_TAG,
    SYMBOL_TYPE = GSI_SYMBOL_TAG,
    STRING_TYPE = GSI_STRING_TAG,
    STRUCTURE_TYPE = GSI_STRUCTURE_TAG,
    SEQUENCE_TYPE = GSI_SEQUENCE_TAG,
    UNSIGNED_SHORT_VECTOR_TYPE = GSI_UNSIGNED_SHORT_VECTOR_TAG,

    INTEGER_ARRAY_TYPE = INTEGER_ARRAY_TAG,
    SYMBOL_ARRAY_TYPE = SYMBOL_ARRAY_TAG,
    STRING_ARRAY_TYPE = GSI_STRING_ARRAY_TAG,
    LOGICAL_ARRAY_TYPE = GSI_LOGICAL_ARRAY_TAG,
    FLOAT_ARRAY_TYPE = GSI_FLOAT64_ARRAY_TAG,
    ITEM_ARRAY_TYPE = GSI_ITEM_ARRAY_TAG,
    VALUE_ARRAY_TYPE = GSI_VALUE_ARRAY_TAG,
    ITEM_OR_VALUE_ARRAY_TYPE = GSI_ITEM_OR_VALUE_ARRAY_TAG,
    QUANTITY_ARRAY_TYPE = GSI_QUANTITY_ARRAY_TAG,
    INTEGER_LIST_TYPE = GSI_INTEGER_LIST_TAG,
    SYMBOL_LIST_TYPE = GSI_SYMBOL_LIST_TAG,
    STRING_LIST_TYPE = GSI_STRING_LIST_TAG,
    LOGICAL_LIST_TYPE = GSI_LOGICAL_LIST_TAG,
    FLOAT_LIST_TYPE = GSI_FLOAT64_LIST_TAG,
    ITEM_LIST_TYPE = GSI_ITEM_LIST_TAG,
    VALUE_LIST_TYPE = GSI_VALUE_LIST_TAG,
    ITEM_OR_VALUE_LIST_TYPE = GSI_ITEM_OR_VALUE_LIST_TAG,
    QUANTITY_LIST_TYPE = GSI_QUANTITY_LIST_TAG
  };
class AttributeArray;
class ItemArray;
class API Item 
{
public:
  Item();
  ~Item();
  
  static int convertToGsi(Item& pItem, gsi_item pResult);
  static int convertArrayToGsi(ItemArray& pArray, long pNum,
                               gsi_item *pResult);
  
  static int convertFromGsi(gsi_item pItem, Item& pResult);
  static int convertArrayFromGsi(gsi_item *pArray, long pNum,
                                 ItemArray& pResult);

  // Uses GSI type flags 
  GsiType getType();


  // As currently written, the mutator methods assume a 
  // Item is never reused.
  // ---------------------------------------------------
  void setType(GsiType pType);

  // For multi-valued GSI data types
  long getLength();

  void setNULL();
  
  void setFloat(double pVal);
  double getFloat();

  void setInteger(int pVal);
  int getInteger();

  void setSymbol(char *pString);
  char *getSymbol();

  // We let the caller own the String and make our own copy 
  void setString(char *pString);
  char *getString();
 
  void setUsv(unsigned short* pUsv, int pLength);
  unsigned short* getUsv();
  void setBoolean(int pBoolean);
  int getBoolean();
  void setElements(ItemArray* pElements, GsiType pGsiType);
 
  ItemArray* getElements();

  void setAttrs(AttributeArray* pAttrs);
  AttributeArray* getAttrs();
 
  long getNumAttrs();

  static void deepReclaimGsiItems(gsi_item *pItems, long pCount);

  void setDeleteSubItems(bool pDeleteSubItems);
  bool getDeleteSubItems();

private:
  GsiType mType;
  double mFloat;
  int mInteger;
  char *mString;
  long mLength;
  unsigned short *mUsv;
  ItemArray* mElements;
  AttributeArray* mAttrs;
  bool mDeleteSubItems;
};

#ifndef S_OK
#define S_OK 0
#endif

}

#endif // ifndef _CPP_LINK_ITEM_H