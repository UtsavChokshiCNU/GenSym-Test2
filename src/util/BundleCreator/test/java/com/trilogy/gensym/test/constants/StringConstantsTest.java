package com.trilogy.gensym.test.constants;

import com.trilogy.gensym.constants.XMLStringConstants;

import junit.framework.TestCase;

public class StringConstantsTest extends TestCase {
	
	public final void testStringConstantsCreation() throws Exception {
		XMLStringConstants sc = new XMLStringConstants();
		assertNotNull(sc);
	}
}
