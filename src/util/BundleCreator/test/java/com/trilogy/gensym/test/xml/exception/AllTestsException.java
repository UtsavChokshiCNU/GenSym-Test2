package com.trilogy.gensym.test.xml.exception;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTestsException {

	public static Test suite() {
		TestSuite suite = new TestSuite("com.trilogy.gensym.test.xml.exception.AllTestsException");
		suite.addTestSuite(XMLParserExceptionTest.class);
		suite.addTestSuite(XSDErrorHandlerTest.class);
		return suite;
	}
}
