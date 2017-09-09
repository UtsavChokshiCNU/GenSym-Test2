#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <signal.h>



#include "cprim.h"

// Yes, this is _very_ wrong, but, header files are in such a mess
// that it would take way too much time to figure out what to include
// besides `gensym.h` - and including only `gensym.h` doesn't work...
extern "C" {
	long g2ext_g2_gethostname(char* buffer, long length_long);
	long g2ext_get_user_name(char* buffer);
	//long g2ext_get_user_homedir(char* buffer);
	long g2ext_create_argument_list(int argc, char* argv[]);
	long g2ext_return_argc();
	long g2ext_argv_strlen(long argument_number);
	long g2ext_return_argv(char* buffer, long argument_number);
}

bool isLittleEndian() {
	int value = 0x12345678;
	return *reinterpret_cast<char*>(&value) == 0x78;
}

class CPrimTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(CPrimTests);
		CPPUNIT_TEST(test_g2ext_foreign_reconstruct_float);
		CPPUNIT_TEST(test_g2pvt_gprintf1);
		CPPUNIT_TEST(test_g2pvt_gprintf2);
		CPPUNIT_TEST(test_g2ext_g2_gethostname);
		CPPUNIT_TEST(test_g2ext_get_user_name);
		//CPPUNIT_TEST(test_g2ext_get_user_homedir);
		CPPUNIT_TEST(test_g2ext_create_argument_list);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_g2ext_foreign_reconstruct_float() {
		double_float_union testFloat;
		testFloat.float_view = 1.2561;
		double resultValue;

		resultValue = isLittleEndian() ? g2ext_foreign_reconstruct_float(
				testFloat.byte_view.byte4, testFloat.byte_view.byte3,	
				testFloat.byte_view.byte2, testFloat.byte_view.byte1)
			: g2ext_foreign_reconstruct_float(
				testFloat.byte_view.byte1, testFloat.byte_view.byte2,	
				testFloat.byte_view.byte3, testFloat.byte_view.byte4);
		CPPUNIT_ASSERT_EQUAL(testFloat.float_view, resultValue);
	}

	/*****************************************************************************
	* void test_g2pvt_gprintf2 ()
	*
	*   Description:
	*       This unittest should test g2pvt_gprintf2 function with log level lower than
	*		the value set in the class.
	*   Input Arguments:
	*     none
	*   Return value:
	*     none
	*   Notes:
	*   Modifications:
	*****************************************************************************/
	void test_g2pvt_gprintf1() {
		char* buf = (char *)malloc(100);
		char* format = "this is a %s";
		char* expected = "this is a test";

		memset(buf, 0, 100);

		setbuf(stderr, buf);

		g2pvt_gprintf(G2PVT_ERROR, format, "test");

		CPPUNIT_ASSERT_EQUAL(*expected, *buf);

		free(buf);
	}

	/*****************************************************************************
	* void test_g2pvt_gprintf2 ()
	*
	*   Description:
	*       This unittest should test g2pvt_gprintf2 function with log level higher than 
	*		the value set in the class.
	*   Input Arguments:
	*     none
	*   Return value:
	*     none
	*   Notes:
	*   Modifications:
	*****************************************************************************/
	void test_g2pvt_gprintf2() {
		char* buf = (char *)malloc(100);
		char* format = "this is a %s";
		char* expected = "";

		memset(buf, 0, 100);

		setbuf(stderr, buf);

		g2pvt_gprintf(G2PVT_DUMP, format, "test");

		CPPUNIT_ASSERT_EQUAL(*expected, *buf);

		free(buf);
	}

	/*****************************************************************************
	* void test_g2ext_g2_gethostname ()
	*
	*   Description:
	*       This unittest should test g2ext_g2_gethostname.
	*   Input Arguments:
	*     none
	*   Return value:
	*     none
	*   Notes:
	*   Modifications:
	*****************************************************************************/
	void test_g2ext_g2_gethostname() {
		char* buf = (char *)malloc(MAX_PATH);
		long res = g2ext_g2_gethostname(buf, MAX_PATH);

		CPPUNIT_ASSERT(res > 0);
		CPPUNIT_ASSERT(strlen(buf) > 0);

		free(buf);
	}

	/*****************************************************************************
	* void test_g2ext_get_user_name ()
	*
	*   Description:
	*       This unittest should test g2ext_get_user_name.
	*   Input Arguments:
	*     none
	*   Return value:
	*     none
	*   Notes:
	*   Modifications:
	*****************************************************************************/
	void test_g2ext_get_user_name() {
		char *buf = (char *)malloc(300);

		long res = g2ext_get_user_name(buf);

		CPPUNIT_ASSERT_EQUAL(SUCCESS, res);
		CPPUNIT_ASSERT(strlen(buf) > 0);

		free(buf);
	}

	/*****************************************************************************
	* void test_g2ext_get_user_homedir ()
	*
	*   Description:
	*       This unittest should test g2ext_get_user_homedir.
	*   Input Arguments:
	*     none
	*   Return value:
	*     none
	*   Notes:
	*		On Windows OS there is no HOME environment variable by default.
	*   Modifications:
	*****************************************************************************/
	/*void test_g2ext_get_user_homedir() {
		char *buf = (char *)malloc(300);

		long res = g2ext_get_user_homedir(buf);

		CPPUNIT_ASSERT_EQUAL(SUCCESS, res);
		CPPUNIT_ASSERT(strlen(buf) > 0);

		free(buf);
	}*/

	/*****************************************************************************
	* void test_g2ext_get_user_homedir ()
	*
	*   Description:
	*       This unittest should test g2ext_create_argument_list + g2ext_return_argc + 
	*		g2ext_argv_strlen + g2ext_return_argv.
	*   Input Arguments:
	*     none
	*   Return value:
	*     none
	*   Notes:
	*   Modifications:
	*****************************************************************************/
	void test_g2ext_create_argument_list() {
		char *buf = (char *)malloc(10);
		char* listBuf[] = { "val1","val2","val12" };
		
		g2ext_create_argument_list(3, listBuf);


		CPPUNIT_ASSERT_EQUAL(3L, g2ext_return_argc());
		CPPUNIT_ASSERT_EQUAL(5L, g2ext_argv_strlen(2));

		long res = g2ext_return_argv(buf, 1);

		CPPUNIT_ASSERT_EQUAL(SUCCESS, res);
		CPPUNIT_ASSERT_EQUAL(*listBuf[1], *buf);

		free(buf);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CPrimTests);
