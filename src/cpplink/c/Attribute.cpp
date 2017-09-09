#include "Attribute.h"
#include "AttributeArray.h"
#include "Utils.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  Attribute constructor
	//
Attribute::Attribute():
mName(NULL)
{
}

  ///////////////////////////////////////////
	//
	//  Attribute destructor
	//
Attribute::~Attribute()
{
  if (mName)
    delete []mName;
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  convertToGsiAttr
	//
int Attribute::convertToGsiAttr(Attribute& pAttr, gsi_attr pResult)
{
    // First convert it as if it is regular item
    int result = Item::convertToGsi(pAttr, pResult);
    
    if (result) {
        return result;
    }
    
    // Second change the attr name of the attribute
    gsi_set_attr_name(pResult, pAttr.getAttrName());
    return S_OK;
}

  ///////////////////////////////////////////
	//
	//  convertArrayToGsiAttr
	//
int Attribute::convertArrayToGsiAttr(AttributeArray &pArray, long pNum, gsi_attr *pResult)
{
    int result;
    for (int i=0; i< pNum; i++) {
        result = Attribute::convertToGsiAttr(pArray[i], pResult[i]);
        if (result) {
            return result;
        }
    }
    return S_OK;
}

  ///////////////////////////////////////////
	//
	//  convertFromGsiAttr
	//
int Attribute::convertFromGsiAttr(gsi_attr pAttr, Attribute& pResult)
{
    // First convert it as if it is regular item
    int result = Item::convertFromGsi(pAttr, pResult);
    
    if (result) {
        return result;
    }
    
    // Second change the attr name of the attribute
    pResult.setAttrName(gsi_attr_name_of(pAttr));
    
    return S_OK;
}

  ///////////////////////////////////////////
	//
	//  convertArrayFromGsiAttr
	//
int Attribute::convertArrayFromGsiAttr(gsi_attr *pArray, long pNum, AttributeArray& pResult)
{
    int result;
    for (int i=0; i< pNum; i++) {
        result = Attribute::convertFromGsiAttr(pArray[i], pResult[i]);
        if (result) {
            return result;
        }
    }
    
    return S_OK;
}


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  setAttrName
	//
void Attribute::setAttrName(char *pName)
{
  mName = new char[strlen(pName)+1];
  strcpy(mName, pName);
  Utils::toUpper(mName);
}

  ///////////////////////////////////////////
	//
	//  getAttrName
	//
char *Attribute::getAttrName()
{
   char *result = new char[strlen(mName)+1];
   strcpy(result, mName);
   return result;
}

}