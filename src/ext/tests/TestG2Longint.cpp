#include "TestG2Longint.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestG2Longint);


void TestG2Longint::testAllocation() {
	g2longint* value = g2ext_alloc_g2longint(10L);
	CPPUNIT_ASSERT(value != NULL);
	CPPUNIT_ASSERT(value->value == 10);
	g2ext_free_g2longint(value);
}

void TestG2Longint::testCopy() {
	g2longint* value = g2ext_alloc_g2longint(8474L);
	CPPUNIT_ASSERT(value != NULL);
	CPPUNIT_ASSERT(value->value == 8474);
	g2longint* new_value = g2ext_copy_g2longint(value);
	CPPUNIT_ASSERT(new_value != NULL);
	CPPUNIT_ASSERT(new_value != value);
	CPPUNIT_ASSERT(new_value->value == 8474);	
}

void TestG2Longint::testSummation() {
	g2longint* v1 = g2ext_alloc_g2longint(6499999);
	g2longint* v2 = g2ext_alloc_g2longint(789488);
	v1 = g2ext_sum_g2longints(v1,v2);
	CPPUNIT_ASSERT(v1->value == 7289487);
	v1 = g2ext_alloc_g2longint(9223372036854775807);
	v2 = g2ext_alloc_g2longint(1);
	v1 = g2ext_sum_g2longints(v1,v2);
	CPPUNIT_ASSERT(v1->value == 0L);
}

void TestG2Longint::testSubtraction() {
	g2longint v1,v2;
	v1.value = 67126154;
	v2.value = 37147234743;
	g2ext_sub_g2longints(&v2,&v1);
	CPPUNIT_ASSERT(v2.value == 37080108589);
	v1.value = -9223372036854775808;
	v2.value = 1;
	g2ext_sub_g2longints(&v1,&v2);
	CPPUNIT_ASSERT(v1.value == 9223372036854775807L);
}

void TestG2Longint::testMultiplication() {
	g2longint* v1 = g2ext_alloc_g2longint(4652365L);
	g2longint* v2 = g2ext_alloc_g2longint(77865L);
	v1 = g2ext_mul_g2longints(v1,v2);
	CPPUNIT_ASSERT(v1->value == 362256400725);
}

void TestG2Longint::testString2G2Longint() {
	g2longint* v = g2ext_convert_string_to_g2longint("477386793763L",0,11);
	CPPUNIT_ASSERT(v->value == 477386793763);
	v = g2ext_convert_string_to_g2longint("-2L",0,1);
	CPPUNIT_ASSERT(v->value == -2);
	v = g2ext_convert_string_to_g2longint("9223372036854775807L",0,19);
	CPPUNIT_ASSERT(v->value == 9223372036854775807L);
	v = g2ext_convert_string_to_g2longint("-9223372036854775808L",0,19);
	CPPUNIT_ASSERT(v->value == -9223372036854775808L);
}

void TestG2Longint::testDivision() {
	g2longint a,b,c;
	a.value = 800;
	b.value = 25;
	g2ext_div_g2longints(&a, &b);
	CPPUNIT_ASSERT(a.value == 32);
	a.value = 123456789;
	b.value = 783;
	g2ext_div_g2longints(&a, &b);
	CPPUNIT_ASSERT(a.value == 157671);

}

void TestG2Longint::testGSIComposer() {
	g2longint* r = g2ext_compose_g2longint_for_gsi(65535, 65535, 65535, 65535, 0);
//	CPPUNIT_ASSERT(r->lp == 0xFFFFFFFFFFFFFFFF);
//	CPPUNIT_ASSERT(r->hp == 0);
}

void TestG2Longint::testG2Longint2Double() {
	g2longint x;
	double r;

	x.value = 8237469999999;

	r = g2ext_convert_g2longint_to_double(&x);

	CPPUNIT_ASSERT(r == 8237469999999.0);
}

void TestG2Longint::testG2Longint2String() {
	char buff[50];
	g2longint n;
	n.value = 7123469907;
	g2ext_convert_g2longint_to_string(&n, buff, 50);
	CPPUNIT_ASSERT(strcmp(buff, "7123469907L") == 0);
}

void TestG2Longint::testPredicates() {
	g2longint v1,v2;
	v1.value = 81234;
	v2.value = 156234;
	CPPUNIT_ASSERT(g2ext_g2longint_eq(&v1, &v2) == 0);
	CPPUNIT_ASSERT(g2ext_g2longint_gt(&v1, &v2) == 0);
}

void TestG2Longint::testICPComposition() {
/*	g2longint v;
	v.lp = 0x0;
	v.hp = 0x0;
	unsigned short word;
	int i;

	for (i = 0; i < 7; i++) {
		word = g2ext_get_g2longint_word_at(&v, i);
		CPPUNIT_ASSERT(word == 0);
	}

	for (i = 0; i < 7; i++) {
		g2ext_set_g2longint_word_at(&v, i, 65535);
	}

	for (i = 0; i < 7; i++) {
		word = g2ext_get_g2longint_word_at(&v, i);
		CPPUNIT_ASSERT(word == 65535);
	}*/
	}

void TestG2Longint::testOverflow() {
	g2longint g2lmax;
	g2longint g2lmin;
	g2longint g2lzero;
	g2longint* v;

	g2lmin.value = -9223372036854775808L;
	g2lmax.value = 9223372036854775807L;
	g2lzero.value = 0L;
	
	v = g2ext_convert_string_to_g2longint("2922337203685477580755L",0,19);
	CPPUNIT_ASSERT(1 == g2ext_g2longint_eq(v, &g2lmax));
	CPPUNIT_ASSERT(0 == g2ext_g2longint_eq(v, &g2lmin));

	v = g2ext_convert_string_to_g2longint("-544922337203685477580755L",0,19);
	CPPUNIT_ASSERT(0 == g2ext_g2longint_eq(v, &g2lmax));
	CPPUNIT_ASSERT(1 == g2ext_g2longint_eq(v, &g2lmin));

	v->value = 7347L;
	v = g2ext_div_g2longints(v, &g2lzero);
	CPPUNIT_ASSERT(1 == g2ext_g2longint_eq(v, &g2lmax));

	v->value = -7347L;
	v = g2ext_div_g2longints(v, &g2lzero);
	CPPUNIT_ASSERT(1 == g2ext_g2longint_eq(v, &g2lmin));

}

void TestG2Longint::setUp()
{
}

void TestG2Longint::tearDown()
{
}