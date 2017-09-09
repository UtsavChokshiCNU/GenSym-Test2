package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class SqrtTest
{
	private Sqrt testObj;

	@Before
	public void initObject()
	{
		testObj = new Sqrt();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Sqrt", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "B = Sqrt(A).  Returns the square root of its argument";
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
		final Vector<double[]> inputVector = new Vector<>();
		final double[] inValues = {9.0, 0.0, 16.0, 26.0, -0.0};
		inputVector.addElement(inValues);

		final double[] outputVals = new double[inValues.length];
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(Math.sqrt(9.0), outputVals[0], 0);
		assertEquals(Math.sqrt(0.0), outputVals[1], 0);
		assertEquals(Math.sqrt(16.0), outputVals[2], 0);
		assertEquals(Math.sqrt(26.0), outputVals[3], 0);
		assertEquals(Math.sqrt(-0.0), outputVals[4], 0);
	}

	/**
	 * This method to test sqrt value for negative value.
	 * @throws MathException
	 */
	@Test(expected = MathException.class)
	public void testEvaluateForNegativeVal() throws MathException
	{
		final Vector<double[]> inputVector = new Vector<>();
		final double[] inValues = {-25.0};
		inputVector.addElement(inValues);

		final double[] outputVals = new double[inValues.length];
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
	}
}
