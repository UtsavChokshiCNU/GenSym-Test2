package com.trilogy.gensym.test.constants;

import com.trilogy.gensym.constants.FilenamesStringConstants;

import junit.framework.TestCase;

public class FilenamesStringConstantsTest extends TestCase {
	
	public final void testStringConstantsCreation() throws Exception {
		FilenamesStringConstants sc = new FilenamesStringConstants();
		assertNotNull(sc);
	}
}