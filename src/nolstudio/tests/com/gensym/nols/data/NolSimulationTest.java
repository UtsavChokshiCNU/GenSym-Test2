package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class NolSimulationTest
{

	/**
	 * Method to test constructor which has arguments.
	 */
	@Test
	public void testArgumentConstructor()
	{
		final Project project = new Project();
		final NolModel2 model = new NolModel2();
		final NolSimulation testObj = new NolSimulation(project, model);
		testObj.initTransient(project);
		testObj.calulationSimulation();
		assertEquals(model, testObj.getModel());
		assertNull(testObj.getOutputData());
	}

	/**
	 * Method to test clone()
	 * @throws CloneNotSupportedException
	 */
	@Test
	public void testClone() throws CloneNotSupportedException
	{
		final NolSimulation testObj = new NolSimulation();
		final NolSimulation returnVal = (NolSimulation) testObj.clone();
		assertEquals(testObj.getModel(), returnVal.getModel());
		assertEquals(testObj.isCalculated(), returnVal.isCalculated());
	}

	/**
	 * Method to test Equals()
	 */
	@Test
	public void testEquals()
	{
		final NolSimulation testObj = new NolSimulation();
		Object inputObj = new Object();
		testObj.setName("NolSimulation");
		assertFalse(testObj.equals(inputObj));
		inputObj = new NolSimulation();
		assertFalse(testObj.equals(inputObj));
		((NolSimulation)inputObj).setName("NolSimulation");
		assertTrue(testObj.equals(inputObj));
	}

	/**
	 * Method to test toString()
	 */
	@Test
	public void testToString()
	{
		final NolSimulation testObj = new NolSimulation();
		testObj.setName("Name");
		assertEquals(testObj.getName(), testObj.toString());
	}


}
