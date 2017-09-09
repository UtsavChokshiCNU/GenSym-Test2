#include "PoolsTest.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(PoolsTest);

void PoolsTest::setUp()
{
}

void PoolsTest::tearDown()
{
}

void PoolsTest::test_allocate_use()
{
    char *ptrBlb1 = NULL;
    char *ptrBlb2 = NULL;

    //allocate 1st blob
    icp_int result = allocate_blob(icp_int(256), &ptrBlb1);
    CPPUNIT_ASSERT(result == ICP_SUCCESS);

    //allocate 2nd blob with similar size
    result = allocate_blob(icp_int(256), &ptrBlb2);
    CPPUNIT_ASSERT(result == ICP_SUCCESS);

    // the 2 blob ptr have to be different
    CPPUNIT_ASSERT(ptrBlb1 != ptrBlb2);

    //using blobs
    CPPUNIT_ASSERT_NO_THROW( memset(ptrBlb1, 0, 256) );
    CPPUNIT_ASSERT_NO_THROW( memset(ptrBlb2, 0, 256) );

}


void PoolsTest::test_reclaim_use()
{
    char *ptrBlb1 = NULL;
    char *ptrBlb2 = NULL;

    //allocate 1st blob
    icp_int result = allocate_blob(icp_int(512), &ptrBlb1);
    CPPUNIT_ASSERT(result == ICP_SUCCESS);

    //using blob
    CPPUNIT_ASSERT_NO_THROW( memset(ptrBlb1, 'X', 512) );

    //reclaim used blobs
    result = reclaim_used_blobs();
    CPPUNIT_ASSERT(result == ICP_SUCCESS);

    //allocate 2nd blob with same size
    result = allocate_blob(icp_int(512), &ptrBlb2);
    CPPUNIT_ASSERT(result == ICP_SUCCESS);

    // check we are using the recycled blob
    CPPUNIT_ASSERT(ptrBlb1 == ptrBlb2);

    //using blob
    CPPUNIT_ASSERT_NO_THROW( memset(ptrBlb1, 'Y', 512) );
}


void PoolsTest::test_allocate_load()
{
    srand (time(NULL));
    char *tabPtrBlb1[10];
    char *tabPtrBlb2[10];
    icp_int tabBlbSize[10];
    memset(tabPtrBlb1, 0x0, 10);
    memset(tabPtrBlb2, 0x0, 10);

    //allocate and use 10 blobs: empty pool
    for(int i=0;i<10;i++)
    {	
	//random size (without exceeding max supported size)
	icp_int size = (icp_int)(  (rand() * i)%60000 + 2048);
	tabBlbSize[i] = size;

	icp_int result = allocate_blob(size, &tabPtrBlb1[i]);

	//check for successfull allocation
	CPPUNIT_ASSERT(result == ICP_SUCCESS);

	//using the blob
	CPPUNIT_ASSERT_NO_THROW( memset(tabPtrBlb1[i], 'A', size) );
    }

    //reclaim used blobs ==> now the pool will contain 1000 free blob
    icp_int result = reclaim_used_blobs();
    CPPUNIT_ASSERT(result == ICP_SUCCESS);

    //allocate and use 10 blobs: check we are using the Pool
    //keep track of all blb in the pool using a set
    set<char*> setPtrBlb(tabPtrBlb1, tabPtrBlb1+10);

    for(int i=0;i<10;i++)
    {	
	icp_int result = allocate_blob(tabBlbSize[i], &tabPtrBlb2[i]);

	//check for successfull allocation
	CPPUNIT_ASSERT(result == ICP_SUCCESS);

	//using the blob
	CPPUNIT_ASSERT_NO_THROW( memset(tabPtrBlb2[i], 'B', tabBlbSize[i]) );

	//check the blb is in the pool and not new allocated one
	CPPUNIT_ASSERT( setPtrBlb.find(tabPtrBlb2[i]) != setPtrBlb.end() );
    }   
}

void PoolsTest::test_allocate_limit()
{
    char *ptrBlb1 = NULL;
    char *ptrBlb2 = NULL;
    int maxSize = 65536;

    //allocate blob with max size
    icp_int result = allocate_blob(icp_int(maxSize), &ptrBlb1);
    CPPUNIT_ASSERT(result == ICP_SUCCESS);
    CPPUNIT_ASSERT_NO_THROW( memset(ptrBlb1, 'Z', maxSize) );

    //exceeding max size
    result = allocate_blob(icp_int(maxSize+1), &ptrBlb2);
    CPPUNIT_ASSERT(result == ICP_FAILURE);
    CPPUNIT_ASSERT(ptrBlb2 == NULL);
}