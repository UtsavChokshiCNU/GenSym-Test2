package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class ReplaceHighValueTest
{
	private ReplaceHighValue testObj;

	@Before
	public void initObject()
	{
		testObj = new ReplaceHighValue();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("ReplaceHighValue", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "D = ReplaceHighValue(A,B,C). If A > B, then D = C, otherwise D = A.";
		assertEquals(description, testObj.getDescription());
	}

	/**
	 * Method to test getMinimumInputs
	 */
	@Test
	public void testGetMinimumInputs()
	{
		assertEquals(3, testObj.getMinimumInputs());
	}

	/**
	 * Method to test getMaximumInputs
	 */
	@Test
	public void testGetMaximumInputs()
	{
		assertEquals(3, testObj.getMaximumInputs());
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
		final Vector<double[]> inputVector = new Vector<>();
		final double[] inVals = {420.0, 23.0, 9.0, 908.0, 20.0, 5.0, 0, -45.0, Double.MIN_VALUE, Double.MAX_VALUE};
		final double[] threshholds = {20.0, 3.0, 10.0, 8.0, 90.0, 53.0, 5.0, 45.0, 0, Double.MIN_VALUE};
		final double[] replacements = {3218.0, 3986.0, 9106.0, 8731.0, 9860.0, 1513.0, 8975.0, 632.0, Double.MAX_VALUE, 10.0};
		inputVector.addElement(inVals);
		inputVector.addElement(threshholds);
		inputVector.addElement(replacements);

		final double[] outputVals = new double[inVals.length];
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);

		assertEquals(3218.0, outputVals[0], 0);
		assertEquals(3986.0, outputVals[1], 0);
		assertEquals(9.0, outputVals[2], 0);
		assertEquals(8731.0, outputVals[3], 0);
		assertEquals(20.0, outputVals[4], 0);
		assertEquals(5.0, outputVals[5], 0);

		assertEquals(0.0, outputVals[6], 0);
		assertEquals(-45.0, outputVals[7], 0);
		assertEquals(Double.MAX_VALUE, outputVals[8], 0);
		assertEquals(10.0, outputVals[9], 0);
	}
}
