#include "TestCharactersCipher.h"

#include "cprim.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestCharactersCipher);

extern "C" {
	long g2ext_eval_base_ref_val(long);
	long g2ext_characters_cipher (long, long, long);
}

void TestCharactersCipher::setUp() {}
void TestCharactersCipher::tearDown() {}

void TestCharactersCipher::testReferenceValue()
{
	long result;
	
	result = g2ext_eval_base_ref_val(44L);
	CPPUNIT_ASSERT_EQUAL(2891L, result);

}

void TestCharactersCipher::testCipher() 
{
	long result;

	result = g2ext_characters_cipher(113L, 144L, 1L);
	CPPUNIT_ASSERT_EQUAL(62L, result);
}
