#include "delete_symbol_test.h"

#define USE_PROTOTYPES
#define SI_RUNTIME_INTERNAL
#include <windows.h>
#include "config.h"
#include "librtl.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "instance.h"


#define HASH_ALLOC_SMALL  1000
#define HASH_ALLOC_LARGE 40000
#define HASH_ALLOC(pkg) ((SI_Dimension)(HASH_ALLOC_LARGE)


extern "C" Object iintern (char*, Object);
extern "C" Object unintern (Object, Object);
extern "C" Object ifind_symbol (char*, Object);
extern "C" Object ifind_package (char *name);
 

CPPUNIT_TEST_SUITE_REGISTRATION(TestDeleteSymbol);

void TestDeleteSymbol::setUp()
{
}

void TestDeleteSymbol::tearDown()
{
}

bool make_random_string1(char* buffer, int length)
{
	if (IsBadWritePtr(buffer, length+1))
		return false;

	srand(time(0));   

	int i = 0;

	for(i=0; i<length; ++i)
		buffer[i] = rand() % 26 + 65;

	buffer[length] = '\0';

	return true;
}



unsigned hash_string (char* name,Object pkg)
{
	/* compute hash value of a symbol */
	unsigned long hashval = 0;
	char *p = name;
	char current_char;

	while(current_char = *p) {
		hashval = ((hashval << 1) & 0xFFFF) + (hashval >> 15)
			+ (unsigned long)current_char;
		p++;
	}
	hashval &= 0xFFFF;
	return (hashval % HASH_ALLOC_LARGE);
}

void TestDeleteSymbol::Test()
{
	Object package, symbol, next, reclaim_obj;
	Object* mhash_table;
	char* name = "AB";
	char buff[20];
	unsigned int hash_value;
	
	package = ifind_package(name);
	
	mhash_table = PACKAGE_MHASHTAB(package);
	if (mhash_table == NULL)
		return;

	for (int i=0; i<100000; i++)
	{
		make_random_string1(buff, 10);
		symbol = iintern(buff, package);
	}

	for (i=0; i<100000; i++)
	{
		make_random_string1(buff, 10);
		symbol = iintern(buff, package);
		//symbol = ifind_symbol(buff, package);
		next = MSYMBOL_NEXT(symbol);
		
		hash_value = hash_string(buff, package);
		Object parent = mhash_table[hash_value];
		reclaim_obj = unintern(symbol, package);
		
		if (reclaim_obj == NULL)
			continue;

		if (next == package)
			continue;

		CPPUNIT_ASSERT(mhash_table[hash_value] != package);
		CPPUNIT_ASSERT(!TRUEP(ifind_symbol(buff, package)));
		if (mhash_table[hash_value] == package)
			break;
	}

}
