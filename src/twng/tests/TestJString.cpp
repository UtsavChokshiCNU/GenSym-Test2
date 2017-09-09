#include "stdafx.h"
#include "TestJString.h"
#include "JString.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestJString);


void TestJString::Test()
{
	JString str1 = "mwef[m[23-3j-23ej2mfmoewmo fnofnopinfo-n-0320-j23rnf2nfqwdqwmlqw";
	JString str2 = str1;
	CPPUNIT_ASSERT(Equal(str1, str2));

	CString strX = _T("mwef[m[23-3j-23ej2mfmoewmo fnofnopinfo-n-0320-j23rnf2nfqwdqwmlqw");
	JString str3(strX);
	CPPUNIT_ASSERT(Equal(str1, str3));

	JString str4  = str2;
	CPPUNIT_ASSERT(Equal(str4, str1));

	LPWSTR strY = _T("sad,pfpks  sdomvdmopvsdmmk23333333333  l2 l ll l2 l l l l l l2,f]pwe]f]w]fpw=223=krfmrbvnm");
	JString str5(strY);
	JString str6 = str5;
	CPPUNIT_ASSERT(Equal(str5, str6));

	JString str7((long)123456), str8("123456");
	CPPUNIT_ASSERT(Equal(str7, str8));

	double d = 1.234567;
	JString str9(d);
	CPPUNIT_ASSERT(d == atof(str9));

}

bool TestJString::Equal(const JString& j1, const JString& j2) const
{
	return 0 == strcmp(j1, j2);
}