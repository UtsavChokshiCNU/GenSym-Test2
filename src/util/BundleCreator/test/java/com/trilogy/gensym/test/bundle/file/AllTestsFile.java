package com.trilogy.gensym.test.bundle.file;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTestsFile {
	
	public static Test suite() {
		TestSuite suite = new TestSuite("com.trilogy.gensym.test.xml.AllTestsFile");
		suite.addTestSuite(FilesWorkerTest.class);
		return suite;
	}
}
