// hla_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int main(int argc, char* argv[])
{
	// Run unit tests
	// --------------
	CPPUNIT_NS::TextUi::TestRunner runner;
	runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	
	bool result = runner.run();

	return result ? 0 : -1;
}

