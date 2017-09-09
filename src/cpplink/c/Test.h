#include "CppLink.h"
#include <iostream>

using namespace CppLink;
using namespace std;


/*----------------------------------------------------------------------
FORMATTING FUNCTIONS
----------------------------------------------------------------------*/

// The following is here temporarily until I roll it into the main project

#include <iostream>

std::ostream& operator << (std::ostream& pStream, CppLink::Attribute& pItem);
std::ostream& operator << (std::ostream& pStream, CppLink::AttributeArray& pItem);
std::ostream& operator << (std::ostream& pStream, CppLink::Item& pItem);
std::ostream& operator << (std::ostream& pStream, CppLink::ItemArray& pItem);

inline
std::ostream& operator << (std::ostream& pStream, CppLink::Attribute& pItem)
{
  pStream << "Attribute " << &pItem << " {" << std::endl;
  pStream << "Name: " << pItem.getAttrName() << std::endl;
  
  CppLink::GsiType type = pItem.getType();
  switch (type) {

  case CppLink::STRING_TYPE: {
    pStream << "Type: STRING_TYPE" << std::endl;
    pStream << "String: " << pItem.getString() << std::endl;
    break;;
                    }

  case CppLink::SYMBOL_TYPE: {
    pStream << "Type: SYMBOL_TYPE" << std::endl;
    pStream << "Symbol: " << pItem.getString() << std::endl;
    break;;
                    }

  case CppLink::INTEGER_TYPE: {
    pStream << "Type: INTEGER_TYPE" << std::endl;
    pStream << "Integer: " << pItem.getInteger() << std::endl;
    break;;
                     }

  case CppLink::FLOAT_TYPE: {
    pStream << "Type: FLOAT_TYPE" << std::endl;
    pStream << "Float: " << pItem.getFloat() << std::endl;
    break;;
                   }

  case CppLink::LOGICAL_TYPE: {
    pStream << "Type: LOGICAl_TYPE" << std::endl;
    pStream << "Boolean: " << (pItem.getBoolean() ? "true" : "false") << std::endl;
    break;;
                     }

  case CppLink::STRUCTURE_TYPE: {
    pStream << "Type: STRUCTURE" << std::endl;
    pStream << "Structure: {" << std::endl;
    if (pItem.getAttrs()) 
      pStream << *pItem.getAttrs();
    else pStream << "No attrs" << std::endl;
    break;; 
                       } 

  case CppLink::SEQUENCE_TYPE: {
    pStream << "Type: SEQUENCE" << std::endl;
    if (pItem.getElements())
      pStream << *pItem.getElements();
    else pStream << "No elements" << std::endl;
    break;;
                      }

  default: {
    pStream << "Not printed yet" << std::endl;
    break;;
           }
  }
  pStream << "}" << std::endl;
  return pStream;
}

inline
std::ostream& operator << (std::ostream& pStream, CppLink::AttributeArray& pItem)
{
  pStream << "AttributeArray " << &pItem << " {" << std::endl;
  
  for(int i = 0; i < pItem.getSize(); i++) {
    pStream << "[" << i << "]=" << pItem[i];
  }
  pStream << "}" << std::endl;
  return pStream;
}



inline
std::ostream& operator << (std::ostream& pStream, CppLink::Item& pItem)
{
  pStream << "Item " << &pItem <<  " {" << std::endl;
    
  CppLink::GsiType type = pItem.getType();
  switch (type) {

  case CppLink::STRING_TYPE: {
    pStream << "Type: STRING_TYPE" << std::endl;
    pStream << "String: " << pItem.getString() << std::endl;
    break;;
                    }

  case CppLink::SYMBOL_TYPE: {
    pStream << "Type: SYMBOL_TYPE" << std::endl;
    pStream << "Symbol: " << pItem.getString() << std::endl;
    break;;
                    }

  case CppLink::INTEGER_TYPE: {
    pStream << "Type: INTEGER_TYPE" << std::endl;
    pStream << "Integer: " << pItem.getInteger() << std::endl;
    break;;
                     }

  case CppLink::FLOAT_TYPE: {
    pStream << "Type: FLOAT_TYPE" << std::endl;
    pStream << "Float: " << pItem.getFloat() << std::endl;
    break;;
                   }

  case CppLink::LOGICAL_TYPE: {
    pStream << "Type: LOGICAl_TYPE" << std::endl;
    pStream << "Boolean: " << (pItem.getBoolean() ? "true" : "false") << std::endl;
    break;;
                     }

  case CppLink::STRUCTURE_TYPE: {
    pStream << "Type: STRUCTURE" << std::endl;
    pStream << "Structure: {" << std::endl;
    if (pItem.getAttrs()) 
      pStream << *pItem.getAttrs();
    else pStream << "No attrs" << std::endl;
    break;; 
                       } 

  case CppLink::SEQUENCE_TYPE: {
    pStream << "Type: SEQUENCE" << std::endl;
    if (pItem.getElements())
      pStream << *pItem.getElements();
    else pStream << "No elements" << std::endl;
    break;;
                      }

  default: {
    pStream << "Not printed yet" << std::endl;
    break;;
           }
  }
  pStream << "}" << std::endl;
  return pStream;
}

inline
std::ostream& operator << (std::ostream& pStream, CppLink::ItemArray& pItem)
{
  pStream << "ItemArray " << &pItem << " {" << std::endl;
  
  for(int i = 0; i < pItem.getSize(); i++) {
    pStream << "[" << i << "]=" << pItem[i];
  }
  pStream << "}" << std::endl;
  return pStream;
}



