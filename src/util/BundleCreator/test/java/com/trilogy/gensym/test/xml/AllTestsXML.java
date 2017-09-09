package com.trilogy.gensym.test.xml;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTestsXML {
	
	public static Test suite() {
		TestSuite suite = new TestSuite("com.trilogy.gensym.test.xml.AllTestsXML");
		suite.addTestSuite(XMLParserTest.class);
		return suite;
	}
}
