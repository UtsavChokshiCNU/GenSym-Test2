/*----------------------------------------------------------------------
CLASS
    Attribute

KEYWORDS
    AttributeArray Item

AUTHOR
    Allan Scott

DESCRIPTION
    Attribute is a subclass of Item that is used to represent
    attributes of sequences of G2 items.

    In addition to all the methods inherited from Item Attribute
    adds setName() and getName() methods that are used to set the
    name of the atribute.

    For example, below would create a string attribute named Foo with
    a value of Bar:

    Attribute attr = Attribute();
    attr.setString("Bar");
    attr.setName("Foo");

    Attributes are usually constructed by the AttributeArray class.
	
LOG
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ATTRIBUTE_H
#define _CPP_LINK_ATTRIBUTE_H

#include "api.h"
#include "gsi_main_cpp.h"
#include "Item.h"

namespace CppLink 
{

class AttributeArray;

class API Attribute : public Item
{
public:
  Attribute();
  virtual ~Attribute();
  
  static int convertToGsiAttr(Attribute& pAttr, gsi_attr pResult);
  static int convertArrayToGsiAttr(AttributeArray& pArray, long pNum,
                                   gsi_attr *pResult);
 
  static  int convertFromGsiAttr(gsi_attr pItem, Attribute& pResult);
  static  int convertArrayFromGsiAttr(gsi_attr *pArray, long pNum,
                                      AttributeArray& pResult);

  void setAttrName(char *pName);
  char *getAttrName();
private:
  char *mName;
};

}


#endif // ifndef _CPP_LINK_ATTRIBUTE_H