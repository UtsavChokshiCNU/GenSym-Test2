#include "Hashtable.h"
#include "Synchronize.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Hashtable constructor
	//
 Hashtable::Hashtable() 
 {
   mMutex = new Mutex();
 }

	///////////////////////////////////////////
	//
	//  Hashtable destructor
	//
Hashtable::~Hashtable()
{

}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	// add  
	//
int Hashtable::add(void *pKey, void *pValue)
{
  Synchronize sync = Synchronize(mMutex);  
  return insert_hashtable(&mTable, pKey, pValue);
}

	///////////////////////////////////////////
	//
	// get
	//
void *Hashtable::get(void *pKey)
{
  Synchronize sync = Synchronize(mMutex);  
  return get_hashtable(&mTable, pKey);
}

	///////////////////////////////////////////
	//
	// remove
	//
void Hashtable::remove(void *pKey)
{
  Synchronize sync = Synchronize(mMutex);  
  remove_hashtable(&mTable, pKey);
}

	///////////////////////////////////////////
	//
	// clear
	//
void Hashtable::clear()
{
  // No-Op for now!
}

}