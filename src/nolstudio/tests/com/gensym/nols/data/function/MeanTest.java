package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class MeanTest
{
	private Mean testObj;

	@Before
	public void initObject()
	{
		testObj = new Mean();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Mean", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = Mean(A,B,...).  Returns the mean of two or more input arguments";
		assertEquals(description, testObj.getDescription());
	}

	/**
	 * Method to test getMinimumInputs
	 */
	@Test
	public void testGetMinimumInputs()
	{
		assertEquals(2, testObj.getMinimumInputs());
	}

	/**
	 * Method to test getMaximumInputs
	 */
	@Test
	public void testGetMaximumInputs()
	{
		assertEquals(99999, testObj.getMaximumInputs());
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
		final double[] outputVals = new double[4];
		final Vector<double[]> inputVector = new Vector<>();

		final double[] inValues1 = {10.0, Double.MIN_VALUE, -908, -90};
		final double[] inValues2 = {Double.MIN_VALUE, 90, 0, Double.MIN_VALUE};
		final double[] inValues3 = {253.0, Double.MAX_VALUE, -800, Double.MIN_VALUE};
		final double[] inValues4 = {-100.0, Double.MAX_VALUE, 200, -500};
		final double[] inValues5 = {0.0, Double.MIN_VALUE, 0, Double.MIN_VALUE};

		inputVector.addElement(inValues1);
		inputVector.addElement(inValues2);
		inputVector.addElement(inValues3);
		inputVector.addElement(inValues4);
		inputVector.addElement(inValues5);

		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(32.6, outputVals[0], 0);
		assertEquals(Double.POSITIVE_INFINITY , outputVals[1], 0);
		assertEquals(-301.6, outputVals[2], 0);
		assertEquals(-118.0, outputVals[3], 0);
	}
}
