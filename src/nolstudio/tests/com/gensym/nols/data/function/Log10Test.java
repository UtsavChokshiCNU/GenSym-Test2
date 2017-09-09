package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class Log10Test
{
	private Log10 testObj;
	private static double factor = 1.0/Math.log(10.0);

	@Before
	public void initObject()
	{
		testObj = new Log10();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Log10", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = Log10(A).  Returns the base-10 logarithm of A.";
		assertEquals(description, testObj.getDescription());
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
	public void testEvaluate() throws MathException
	{
		final double[] inValues = {1.0, 2.0, 4.0, 9.0, 0.0, Double.MIN_VALUE,Double.MAX_VALUE};
		final double[] outputVals = new double[inValues.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inValues);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(factor * Math.log(1.0), outputVals[0], 0);
		assertEquals(factor * Math.log(2.0), outputVals[1], 0);
		assertEquals(factor * Math.log(4.0), outputVals[2], 0);
		assertEquals(factor * Math.log(9.0), outputVals[3], 0);
		assertEquals(factor * Math.log(0.0), outputVals[4], 0);
		assertEquals(factor * Math.log(Double.MIN_VALUE), outputVals[5], 0);
		assertEquals(factor * Math.log(Double.MAX_VALUE), outputVals[6], 0);
	}
}
