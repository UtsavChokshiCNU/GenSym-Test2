package com.trilogy.gensym.test;

import com.trilogy.gensym.test.bundle.AllTestsBundle;
import com.trilogy.gensym.test.bundle.file.AllTestsFile;
import com.trilogy.gensym.test.constants.AllTestsConstants;
import com.trilogy.gensym.test.propertiesloader.AllTestsPropertiesloader;
import com.trilogy.gensym.test.xml.AllTestsXML;
import com.trilogy.gensym.test.xml.exception.AllTestsException;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTests extends TestSuite{
	
	public static Test suite() {
		AllTests allTestSuite = new AllTests();
		allTestSuite.addTest(AllTestsBundle.suite());
		allTestSuite.addTest(AllTestsFile.suite());
		allTestSuite.addTest(AllTestsConstants.suite());
    	allTestSuite.addTest(AllTestsPropertiesloader.suite());
        allTestSuite.addTest(AllTestsXML.suite());
        allTestSuite.addTest(AllTestsException.suite());
        return allTestSuite;
    }
}
