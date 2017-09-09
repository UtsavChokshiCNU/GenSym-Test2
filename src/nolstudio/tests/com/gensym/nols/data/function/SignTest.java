package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class SignTest
{
	private Sign testObj;

	@Before
	public void initObject()
	{
		testObj = new Sign();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Sign", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "B = Sign(A).  Returns -1,0, or +1 depending on whether A<0, A=0, "
				+ "or A>0, respectively.";
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
		final double[] inValues = {10.0, 0.0, -40.0, Double.NaN};
		inputVector.addElement(inValues);

		final double[] outputVals = new double[inValues.length];
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(1.0, outputVals[0], 0);
		assertEquals(0.0, outputVals[1], 0);
		assertEquals(-1.0, outputVals[2], 0);
		assertEquals(Double.NaN, outputVals[3], 0);
	}
}
