#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <signal.h>

#include "g2signal.h"

class G2SignalTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(G2SignalTests);
		CPPUNIT_TEST(test_g2ext_unestablish_signal_handler_unregister_not_supported);
		CPPUNIT_TEST(testIsSignalSupportedByWindows);
		CPPUNIT_TEST(testWindowsSupportedSignalsCount);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_g2ext_unestablish_signal_handler_unregister_not_supported() {
		 g2ext_unestablish_signal_handler(5);
	}

	void testIsSignalSupportedByWindows() {
#ifdef _WIN32
		CPPUNIT_ASSERT(isSignalSupportedByWindows(SIGINT));
		CPPUNIT_ASSERT(!isSignalSupportedByWindows(5));
		CPPUNIT_ASSERT(isSignalSupportedByWindows(SIGILL));
		CPPUNIT_ASSERT(isSignalSupportedByWindows(SIGFPE));
		CPPUNIT_ASSERT(isSignalSupportedByWindows(SIGSEGV));
		CPPUNIT_ASSERT(isSignalSupportedByWindows(SIGTERM));
		CPPUNIT_ASSERT(isSignalSupportedByWindows(SIGBREAK));
		CPPUNIT_ASSERT(isSignalSupportedByWindows(SIGABRT));
#endif
	}

	void testWindowsSupportedSignalsCount() {
		CPPUNIT_ASSERT_EQUAL((size_t) 7, sizeof(windowsSupportedSignals)
			/ sizeof(windowsSupportedSignals[0]));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(G2SignalTests);
