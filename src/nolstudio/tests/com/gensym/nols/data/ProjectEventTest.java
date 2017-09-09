package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class ProjectEventTest
{
	/**
	 * Method to test getProject & getIdentifier methods
	 */
	@Test
	public void testGetters()
	{
		final Object project = new Object();
		final String id = "TestId";
		final ProjectEvent testObj = new ProjectEvent(project, id);
		assertEquals(project, testObj.getProject());
		assertEquals(id, testObj.getIdentifier());
	}
}
