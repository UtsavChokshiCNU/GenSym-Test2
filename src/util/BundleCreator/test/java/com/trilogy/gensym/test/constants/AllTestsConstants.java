package com.trilogy.gensym.test.constants;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTestsConstants {
	
	public static Test suite() {
		TestSuite suite = new TestSuite("com.trilogy.gensym.test.xml.AllTestsConstants");
		suite.addTestSuite(BundleStringConstantsTest.class);
		suite.addTestSuite(FilenamesStringConstantsTest.class);
		suite.addTestSuite(StringConstantsTest.class);
		return suite;
	}
}
