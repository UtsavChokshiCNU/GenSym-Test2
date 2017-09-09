package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class FunctionTest
{
	private Function testObj;

	@Before
	public void initObject()
	{
		testObj = new Function();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		assertEquals("No information on ", testObj.getDescription());
	}

	/**
	 * Method to test getMinimumInputs
	 */
	@Test
	public void testGetMinimumInputs()
	{
		assertEquals(1, testObj.getMinimumInputs());
	}

	/**
	 * Method to test getMaximumInputs
	 */
	@Test
	public void testGetMaximumInputs()
	{
		assertEquals(1, testObj.getMaximumInputs());
	}

	/**
	 * Method to test getNumberOfOutputs
	 */
	@Test
	public void testGetNumberOfOutputs()
	{
		assertEquals(1, testObj.getNumberOfOutputs(12));
	}

	/**
	 * Method to test evaluate()
	 * @throws MathException
	 */
	@Test
	public void testOtherMethods() throws MathException
	{
		final Vector<double[]> inputs = new Vector<>();
		final Vector<double[]> outputs = new Vector<>();
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputs, outputs);
		assertNull(testObj.getInputVarNames());
		assertNull(testObj.getOutputVarNames());
		assertEquals(0L, testObj.getRequiredHistoryLength());
	}
}
