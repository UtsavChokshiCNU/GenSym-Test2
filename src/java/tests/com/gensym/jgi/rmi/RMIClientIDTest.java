package com.gensym.jgi.rmi;

import org.junit.Test;

import static org.junit.Assert.assertNotNull;


public class RMIClientIDTest {

	@Test
	public final void testRMIClientID(){
		int testNumber = 21;
		RMIClientID rmiClientID = new RMIClientID(testNumber);
		assertNotNull(rmiClientID);
	}
}