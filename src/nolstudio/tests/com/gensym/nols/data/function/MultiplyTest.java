package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class MultiplyTest
{
	private Multiply testObj;

	@Before
	public void initObject()
	{
		testObj = new Multiply();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Multiply", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = Multiply(A,B,...).  Returns the product of two or more input arguments";
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
		final Vector<double[]> inputVector = new Vector<>();
		final double[] inValues = {10.0, 20.0, 40.0, 90.0, 120.0 };
		final double[] inValues1 = {1.0, 3.0, 5.0, 0.0, -1 };
		inputVector.addElement(inValues);
		inputVector.addElement(inValues1);

		final double[] outputVals = new double[inValues.length];
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(10.0, outputVals[0], 0);
		assertEquals(60.0, outputVals[1], 0);
		assertEquals(200.0, outputVals[2], 0);
		assertEquals(0.0, outputVals[3], 0);
		assertEquals(-120.0, outputVals[4], 0);
	}
}
