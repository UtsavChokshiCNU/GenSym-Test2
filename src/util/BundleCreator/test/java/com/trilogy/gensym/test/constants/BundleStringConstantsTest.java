package com.trilogy.gensym.test.constants;

import com.trilogy.gensym.constants.BundleStringConstants;

import junit.framework.TestCase;

public class BundleStringConstantsTest extends TestCase {
	
	public final void testStringConstantsCreation() throws Exception {
		BundleStringConstants sc = new BundleStringConstants();
		assertNotNull(sc);
	}
}