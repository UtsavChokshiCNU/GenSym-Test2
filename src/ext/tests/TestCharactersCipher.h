#ifndef _TEST_CHARACTERS_CIPHER_H_
#define _TEST_CHARACTERS_CIPHER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestCharactersCipher : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestCharactersCipher);
		CPPUNIT_TEST(testReferenceValue);
		CPPUNIT_TEST(testCipher);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testReferenceValue();
	void testCipher();
};

#endif // _TEST_CHARACTERS_CIPHER_H_