#include "G2ptrsTest.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(G2ptrsTest);

void G2ptrsTest::setUp()
{
}

void G2ptrsTest::tearDown()
{
}

void G2ptrsTest::test_g2ext_g2pointers_caching_decaching()
{
    srand (time(NULL));

    g2ext_initialize_g2pointers();
    map<G2pointer, Cpointer> pointerMap;

    //cache 5000 g2pointers with random values
    for(int i=1;i<=5000;i++)
    {
	    Cpointer cpointer = (Cpointer) rand() * i; 
	    G2pointer g2pointer = g2ext_cache_cpointer(cpointer);
	    pointerMap[g2pointer] = cpointer;
    }

    //decache 10 random element elements
    for(int i=0;i<10;i++)
    {
	    map<G2pointer, Cpointer>::iterator it = pointerMap.begin();
	    int index = rand()%5000;
	    advance(it, index);
	    g2ext_decache_g2pointer(it->first);
	    it->second = 0;
    }

    //let's compare the 2 maps : g2ptrs map and our map
    for(map<G2pointer, Cpointer>::iterator it = pointerMap.begin(); it != pointerMap.end(); ++it)
    {
	    Cpointer  cpointer = g2ext_map_g2pointer_to_cpointer(it->first);
	    CPPUNIT_ASSERT(cpointer == it->second);
    }
}