#include "ItemArray.h"
#include "Item.h"
#include "Attribute.h"
#include "AttributeArray.h"
#include "ItemArray.h"
#include "Utils.h"
#include "stdio.h"

namespace CppLink
{
/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  Item constructor
	//
Item::Item ():
  mType (NULL_TYPE),
  mFloat(0.0),
  mInteger(0),
  mString(NULL),
  mUsv(NULL),
  mElements(NULL),
  mAttrs(NULL),
  mDeleteSubItems(false)
{
    
}

  ///////////////////////////////////////////
	//
	//  Item destructor
	//
Item::~Item()
{
    if ((mType == SYMBOL_TYPE || mType == STRING_TYPE) && mString)
        delete [] mString ;
    else if (mType == UNSIGNED_SHORT_VECTOR_TYPE && mUsv)
        delete [] mUsv ;

    if (mDeleteSubItems) {
      if (mElements) {
        delete mElements;
      }

      if (mAttrs) {
        delete mAttrs;
      }
    }
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  convertToGsi
	//
int Item::convertToGsi(Item& pItem, gsi_item pGsiItem)
{ 
    // Translate an Item * into a gsi_item
    long itemType = pItem.getType();
    ItemArray* elements;
    int numElements;
    AttributeArray* attrs;
    long numAttrs;
    int result;
    gsi_item *convertedElements;
    gsi_attr *convertedAttrs;
    char *pStr ;
    
    switch(itemType)
    {
    case NULL_TYPE:
        gsi_set_sym(pGsiItem, "NULL");
        break;
    case INTEGER_TYPE:
        gsi_set_int(pGsiItem,pItem.getInteger());
        break;
    case SYMBOL_TYPE: 
        pStr = pItem.getSymbol() ;
        gsi_set_sym(pGsiItem,pStr);
        delete [] pStr ;
        break;
    case STRING_TYPE:
        pStr = pItem.getString() ;
        gsi_set_str(pGsiItem,pStr);
        delete [] pStr ;
        break;
    case LOGICAL_TYPE:
      gsi_set_log(pGsiItem,(pItem.getBoolean() ? GSI_TRUE : GSI_FALSE));
        break;
    case FLOAT_TYPE:
        gsi_set_flt(pGsiItem,pItem.getFloat());
        break;
    case ITEM_TYPE:
        return E_INVALIDARG;
        break;
    case HANDLE_TYPE:
        return E_INVALIDARG;
        break;
    case INTEGER_ARRAY_TYPE:
    case SYMBOL_ARRAY_TYPE:
    case STRING_ARRAY_TYPE:
    case LOGICAL_ARRAY_TYPE:
    case FLOAT_ARRAY_TYPE:
    case ITEM_ARRAY_TYPE:
    case VALUE_ARRAY_TYPE:
    case ITEM_OR_VALUE_ARRAY_TYPE:
    case QUANTITY_ARRAY_TYPE:
        break;
    case INTEGER_LIST_TYPE:
    case SYMBOL_LIST_TYPE:
    case STRING_LIST_TYPE:
    case LOGICAL_LIST_TYPE:
    case FLOAT_LIST_TYPE:
    case ITEM_LIST_TYPE:
    case VALUE_LIST_TYPE:
    case ITEM_OR_VALUE_LIST_TYPE:
    case QUANTITY_LIST_TYPE:
        return E_INVALIDARG;
        break;
    case SEQUENCE_TYPE: {
        elements = pItem.getElements();
        numElements = pItem.getLength();
        
        convertedElements = gsi_make_items(numElements);
        result = Item::convertArrayToGsi(*elements, numElements, convertedElements);
        if (result) {
          //FIND ME.  Need to log an error
          Utils::debugLogException(0, "convertToGsi: convertArrayToGsi failed.\n");
          return result;
        }
        
        gsi_set_elements(pGsiItem, convertedElements, numElements, GSI_SEQUENCE_TAG);

        break;}
    case STRUCTURE_TYPE: {
        attrs = pItem.getAttrs();
        numAttrs = pItem.getNumAttrs();
        
        convertedAttrs = gsi_make_attrs_with_items(numAttrs);
        result = Attribute::convertArrayToGsiAttr(*attrs, numAttrs, convertedAttrs);
        if (result) {
            //FIND ME.  Need to log an error
            Utils::debugLogException(0, "convertToGsi: convertArrayToGsiAttr failed.\n");
            return result;
        }
        gsi_set_attrs(pGsiItem, convertedAttrs, numAttrs);
        gsi_set_type(pGsiItem, GSI_STRUCTURE_TAG);
        break;
                            }
    case VALUE_TYPE:
        // Not valid.  Should never happen per gsi_type_of() spec.
    case QUANTITY_TYPE:
        // Not valid.  Should never happen per gsi_type_of() spec.
    default:
        
        return E_INVALIDARG;
        break;
    }
    return S_OK;
}

  ///////////////////////////////////////////
	//
	//  convertArrayToGsi
	//
int Item::convertArrayToGsi(ItemArray& pItems, long pNum, gsi_item *pResult)
{
    int result;
    for (int i=0; i<pNum; i++) {
        result = Item::convertToGsi(pItems[i],pResult[i]);
        if (result) {
            return result;
        }
    }
    return S_OK;
}

  ///////////////////////////////////////////
	//
	//  convertFromGsi
	//
int Item::convertFromGsi(gsi_item pItem, Item& pResult)
{
    // Translate a gsi_item into an Item *
    long itemType = gsi_type_of(pItem);
    gsi_item *elements;
    int numElements;
    gsi_attr *attrs;
    int numAttrs;
    int result;
    ItemArray* convertedElements;
    AttributeArray* convertedAttrs;
    
    switch(itemType)
    {
    case GSI_NULL_TAG:
        pResult.setNULL();
        break;
    case GSI_INTEGER_TAG:
        pResult.setInteger(gsi_int_of(pItem));
        break;
    case GSI_SYMBOL_TAG: 
        {
          pResult.setSymbol(gsi_sym_of(pItem));
          break;
        }
    case GSI_STRING_TAG:
        pResult.setSymbol(gsi_str_of(pItem));
        break;
    case GSI_LOGICAL_TAG:
        pResult.setBoolean(gsi_log_of(pItem));
        break;
    case GSI_FLOAT64_TAG:
        pResult.setFloat(gsi_flt_of(pItem));
        break;
    case GSI_ITEM_TAG:
        return E_INVALIDARG;
        break;
    case GSI_HANDLE_TAG:
        return E_INVALIDARG;
        break;
    case GSI_INTEGER_ARRAY_TAG:
    case GSI_SYMBOL_ARRAY_TAG:
    case GSI_STRING_ARRAY_TAG:
    case GSI_LOGICAL_ARRAY_TAG:
    case GSI_FLOAT64_ARRAY_TAG:
    case GSI_ITEM_ARRAY_TAG:
    case GSI_VALUE_ARRAY_TAG:
    case GSI_ITEM_OR_VALUE_ARRAY_TAG:
    case GSI_QUANTITY_ARRAY_TAG:
        break;
    case GSI_INTEGER_LIST_TAG:
    case GSI_SYMBOL_LIST_TAG:
    case GSI_STRING_LIST_TAG:
    case GSI_LOGICAL_LIST_TAG:
    case GSI_FLOAT64_LIST_TAG:
    case GSI_ITEM_LIST_TAG:
    case GSI_VALUE_LIST_TAG:
    case GSI_ITEM_OR_VALUE_LIST_TAG:
    case GSI_QUANTITY_LIST_TAG:
        return E_INVALIDARG;
        break;
    case GSI_SEQUENCE_TAG: {
        elements = gsi_elements_of(pItem);
        numElements = gsi_element_count_of(pItem);
        
        convertedElements = new ItemArray(numElements);
        result = Item::convertArrayFromGsi(elements, numElements, *convertedElements);
        
        if (result)  {
            //FIND ME. Need to log an error
            Utils::debugLogException(0, "convertFromGsi: convertArrayFromGsi failed.\n");
            return result;
        }
        
        pResult.setElements(convertedElements, SEQUENCE_TYPE);
        break;}
    case GSI_STRUCTURE_TAG: {
        attrs = gsi_attrs_of(pItem);
        numAttrs = gsi_attr_count_of(pItem);
        
        convertedAttrs = new AttributeArray(numAttrs);
        result = Attribute::convertArrayFromGsiAttr(attrs, numAttrs, *convertedAttrs);
        
        if (result)  {
            //FIND ME. Need to log an error
            Utils::debugLogException(0, "convertFromGsi: convertArrayFromGsiAttr failed.\n");
            return result;
        }
        
        pResult.setAttrs(convertedAttrs);
        pResult.setType(STRUCTURE_TYPE);
        
        break;
                            }
    case GSI_VALUE_TAG:
        // Not valid.  Should never happen per gsi_type_of() spec.
    case GSI_QUANTITY_TAG:
        // Not valid.  Should never happen per gsi_type_of() spec.
    default:
        
        return E_INVALIDARG;
        break;
    }
    return S_OK;
}

  ///////////////////////////////////////////
	//
	//  convertArrayFromGsi
	//
int Item::convertArrayFromGsi(gsi_item *pArray, long pNum, ItemArray& pResult)
{
    int result;
    for (long i=0; i<pNum; i++) {
        result = Item::convertFromGsi(pArray[i], pResult[i]);
        if (result) {
            return result;
        }
    }
    return S_OK;
}


	///////////////////////////////////////////
	//
	//  deepReclaimGsiItems
	//
void Item::deepReclaimGsiItems(gsi_item *args, long count)
{
    for (long i = 0; i < count; i++)
    {
        gsirtl_free_i_or_v_contents(args[i]);
    }

    gsi_reclaim_items(args);
}

/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  getType
  //
	//  Uses GSI type flags 
GsiType Item::getType()
{
  return mType;
}

  ///////////////////////////////////////////
	//
	//  setType
  //
	//  Uses GSI type flags 
void Item::setType(GsiType pType)
{
  mType = pType;
}

  ///////////////////////////////////////////
	//
	//  getLength
  //
  // For multi-valued GSI data types
long Item::getLength()
{
  if (mElements)
     return mElements->getSize();
  else return 0;
}

  ///////////////////////////////////////////
	//
	//  setNULL
  //
  //
void Item::setNULL()
{
  mType = NULL_TYPE;
}


  ///////////////////////////////////////////
	//
	//  setFloat
  //
  //
void Item::setFloat(double pVal)
{
   mFloat = pVal;
   mType = FLOAT_TYPE;
}


  ///////////////////////////////////////////
	//
	//  getFloat
  //
  //
double Item::getFloat()
{
  return mFloat;
}



  ///////////////////////////////////////////
	//
	//  setInteger
  //
  //
void Item::setInteger(int pVal)
{
  mInteger = pVal;
  mType = INTEGER_TYPE;
}

  ///////////////////////////////////////////
	//
	//  getInteger
  //
  //
int Item::getInteger()
{
  return mInteger;
}


  ///////////////////////////////////////////
	//
	//  setSymbol
  //
  //
void Item::setSymbol(char *pString)
{
  setString(pString);
  Utils::toUpper(mString);
  mType = SYMBOL_TYPE;
}


  ///////////////////////////////////////////
	//
	//  getSymbol
  //
  //
char *Item::getSymbol()
{
  char *result = getString();
  return result;
}

  ///////////////////////////////////////////
	//
	//  setString
  //
  // We let the caller own the String and make our own copy 
void Item::setString(char *pString)
{
  mString = new char[strlen(pString)+1];
  strcpy(mString, pString);
  mType = STRING_TYPE;
}

  ///////////////////////////////////////////
  // 
	//  getString
  //
  // We let the caller own the String and make our own copy   
char *Item::getString()
{
  char *result;
  result = new char[strlen(mString)+1];
  strcpy(result, mString);
  return result;
}


  ///////////////////////////////////////////
	//
	//  setUsv
  //
  //
void Item::setUsv(unsigned short* pUsv, int pLength)
{
  mUsv = pUsv;
  mLength = pLength;
}

  ///////////////////////////////////////////
	//
	//  getUsv
  //
  //
unsigned short* Item::getUsv()
{
  return mUsv; 
}

  ///////////////////////////////////////////
	//
	//  setBoolean
  //
  //
void Item::setBoolean(int pBoolean)
{
  mInteger = pBoolean;
  mType = LOGICAL_TYPE;
}

  ///////////////////////////////////////////
	//
	//  getBoolean
  //
  //
int Item::getBoolean()
{
  return mInteger;
}

  ///////////////////////////////////////////
	//
	//  setElements
  //
  //
void Item::setElements(ItemArray* pElements, GsiType pGsiType)
{
  mElements = pElements;
  mType = pGsiType;
}

  ///////////////////////////////////////////
	//
	//  getElements
  //
  //
ItemArray *Item::getElements()
{
  return mElements;
}

  ///////////////////////////////////////////
	//
	//  setAttrs
  //
  //
void Item::setAttrs(AttributeArray* pAttrs)
{
  mAttrs = pAttrs;
}

  ///////////////////////////////////////////
	//
	//  getAttrs
  //
  //
AttributeArray* Item::getAttrs()
{
  return mAttrs;
}

  ///////////////////////////////////////////
	//
	//  getNumAttrs
  //
  //
long Item::getNumAttrs()
{
  if (mAttrs) {
    return mAttrs->getSize();
  }
  else return 0;
}

  ///////////////////////////////////////////
	//
	//  setDeleteSubItems
  //
  //
void Item::setDeleteSubItems(bool pDeleteSubItems)
{
  mDeleteSubItems = pDeleteSubItems;
}

  ///////////////////////////////////////////
  //
  //  getDeleteSubItems
  //
  //
bool Item::getDeleteSubItems()
{
  return mDeleteSubItems;
}

}