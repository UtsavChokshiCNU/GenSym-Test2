#include "LongHashtable.h"
#include "Synchronize.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  LongHashtable constructor
	//


  ///////////////////////////////////////////
	//
	//  LongHashtable destructor
	//


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/


void long_do_nothing_free_function(void *elem)
{
}

size_t long_hash(void *elem)
{
  long key = (long) elem;
  return key;
}

void *long_key_copy(void *elem)
{
  return elem;
}

void *long_value_copy(void *elem)
{
  return elem;
}

int long_compare(void *elem1, void *elem2)
{
  long key1 = (long) elem1;
  long key2 = (long) elem2;
  
  return (int) (key1 - key2);
}

int LongHashtable::initialize(long pInitialSize)                      
{
  Synchronize sync = Synchronize(mMutex);  
  int result =init_hashtable(&mTable, pInitialSize, 
    &long_hash,
    &long_key_copy,
    &long_value_copy,
    &long_compare);
  set_key_free_function_hashtable(&mTable, &long_do_nothing_free_function);
  set_value_free_function_hashtable(&mTable, &long_do_nothing_free_function);
  return result;
} 

}