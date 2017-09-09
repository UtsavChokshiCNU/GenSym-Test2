#ifndef _TEST_TCP_H_
#define _TEST_TCP_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class ServerThread;

// Class that tests changed functionality in tcp.c file

class TestTCP : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestTCP);
		CPPUNIT_TEST(testSend);
		CPPUNIT_TEST(testConnect);
		CPPUNIT_TEST(testAcceptBuffers);
		CPPUNIT_TEST(testAcceptHandle);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testSend();
	void testConnect();
	void testAcceptBuffers();
	void testAcceptHandle();

private:
	static const int port;

	void StartServer(ServerThread* pServer);
	void WaitServer();
	SOCKET Connect();

	ServerThread* my_server;
};

#endif
