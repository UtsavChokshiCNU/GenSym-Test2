package com.trilogy.gensym.test.propertiesloader;

import junit.framework.Test;
import junit.framework.TestSuite;


public class AllTestsPropertiesloader {
		
    public static Test suite() {
        TestSuite suite = new TestSuite("com.trilogy.gensym.test.propertiesloader.AllTestsPropertiesloader");
        suite.addTestSuite(PropertiesLoaderTest.class);
        return suite;
    }
}
