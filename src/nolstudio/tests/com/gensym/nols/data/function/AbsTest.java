package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class AbsTest
{
	private Abs testObj;

	@Before
	public void initObject()
	{
		testObj = new Abs();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Abs", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "B = abs(A).  Returns the absolute value of its argument";
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
		final double minVal = Double.MIN_VALUE * -1;
		final double maxVal = Double.MAX_VALUE * -1;

		final double[] inputVals = {minVal, maxVal, -1100, 900, Double.MIN_VALUE, Double.MAX_VALUE, 0, -0};
		final double[] outputVals = new double[inputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inputVals);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = new long[1];

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(outputVals[0], Double.MIN_VALUE, 0);
		assertEquals(outputVals[1], Double.MAX_VALUE, 0);
		assertEquals(outputVals[2], 1100, 0);
		assertEquals(outputVals[3], 900, 0);
		assertEquals(outputVals[4], Double.MIN_VALUE, 0);
		assertEquals(outputVals[5], Double.MAX_VALUE, 0);
		assertEquals(outputVals[6], 0, 0);
		assertEquals(outputVals[7], 0, 0);
	}
}
