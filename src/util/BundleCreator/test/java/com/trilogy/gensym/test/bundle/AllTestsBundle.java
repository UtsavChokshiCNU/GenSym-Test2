package com.trilogy.gensym.test.bundle;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTestsBundle {
	
	public static Test suite() {
		TestSuite suite = new TestSuite("com.trilogy.gensym.test.xml.AllTestsBundle");
		suite.addTestSuite(BundleCrearotTest.class);
		suite.addTestSuite(OSStorageTest.class);
		suite.addTestSuite(ZipArchiverTest.class);
		return suite;
	}
}
