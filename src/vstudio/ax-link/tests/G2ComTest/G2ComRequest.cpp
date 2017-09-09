#include "stdafx.h"

#include <comutil.h>
#include "G2ComRequest.h"
#include "G2Gateway.h"
#include "BConReq.h"

CPPUNIT_TEST_SUITE_REGISTRATION(G2ComRequestTestCase);


G2ComRequestTestCase::G2ComRequestTestCase()
{
}
G2ComRequestTestCase::~G2ComRequestTestCase()
{
}

void G2ComRequestTestCase::RequestLenTest()
{
	CG2GatewayObj g2Gateway; 

	g2Gateway.FinalConstruct();

	_bstr_t g2Loc(L"localhost:1111");

	g2Gateway.put_G2Location(g2Loc);

	int count_bef = g2Gateway.getRequestLen(); //Get the length of reguest's gueue, mast be 0.

	g2Gateway.G2ClientConnect(VARIANT_TRUE);

	g2Gateway.G2ClientDisconnect();
	
	Sleep(1000); // wait gsi thread

	int count_after = g2Gateway.getRequestLen(); //Get the length of reguest's gueue, mast be 0 to.

	CPPUNIT_ASSERT(count_bef == count_after);

	g2Gateway.FinalRelease();
}
void G2ComRequestTestCase::setUp()
{
}

void G2ComRequestTestCase::tearDown()
{
}
