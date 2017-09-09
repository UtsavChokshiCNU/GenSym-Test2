#include "StringHashtable.h"
#include "Synchronize.h"
#include <stdio.h>

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  StringHashtable constructor
	//


  ///////////////////////////////////////////
	//
	//  StringHashtable destructor
	//
StringHashtable::~StringHashtable()
{
  // FIND ME.  We need to reclaim all the keys in the
  // string hashtable when we are destroying it.  Unfortunately the
  // hashtable we are using does not have an iterator yet
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

void string_do_nothing_free_function(void *elem)
{
}

void string_reclaim_free_function(void *elem)
{
  char *string = (char *)elem;

  if (string)
    delete[] string;
}

size_t string_hash(void *elem)
{
    char *string = (char *)elem;
    int len = strlen(string);
    int hash = 0;

    for (int i=0; i<len; i++) {
      hash <<= 1;

      if (hash < 0) {
        hash |= 1;
      }
      hash ^= string[i];
    }
    return hash;
}

void *string_key_copy(void *elem)
{
    return elem;
}

void *string_value_copy(void *elem)
{
    return elem;
} 

int string_compare(void *elem1, void *elem2)
{
    char *key1 = (char *) elem1;
    char *key2 = (char *) elem2;
    
    return strcmp(key1, key2);
}


	///////////////////////////////////////////
	//
	// initialize   
	//
int StringHashtable::initialize(long pInitialSize)                      
{
  Synchronize sync = Synchronize(mMutex);
  int result = init_hashtable(&mTable, pInitialSize, 
    &string_hash,
    &string_key_copy,
    &string_value_copy,
    &string_compare);    
  set_key_free_function_hashtable(&mTable, &string_reclaim_free_function);
  set_value_free_function_hashtable(&mTable, &string_do_nothing_free_function);
    
  return result;
} 


	///////////////////////////////////////////
	//
	// addKey
	//
int StringHashtable::addKey(char *pKey, void *pValue) 
{
  //Copy keys when adding them to the string hashtable
  char *keyCopy = new char[strlen(pKey) + 1];
  strcpy(keyCopy, pKey);
  
  return this->add((void *)keyCopy, pValue);
}

}