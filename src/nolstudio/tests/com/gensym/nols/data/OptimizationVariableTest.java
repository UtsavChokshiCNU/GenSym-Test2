package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class OptimizationVariableTest
{
	/**
	 * Method to test constructor with name argument.
	 */
	@Test
	public void testConstructor()
	{
		final String name = "OptimizationConstructor";
		final OptimizationVariable testObj = new OptimizationVariable(name);
		assertEquals(name, testObj.toString());
	}
}
