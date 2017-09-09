package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class RandUniformTest
{
	private RandUniform testObj;

	@Before
	public void initObject()
	{
		testObj = new RandUniform();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("RandUniform", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = RandUniform(A,B).  Returns random numbers uniformly distributed "
				+ "between lower limit A and upper limit B.";
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
		assertEquals(2, testObj.getMaximumInputs());
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
		final double[] lb = {10.0, 0.0, 6.0, 90.0};
		inputVector.addElement(lb);
		final double[] ub = {50.0, 76.0, 19.0, 597.0};
		inputVector.addElement(ub);

		final double[] outputVals = new double[lb.length];
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		Arrays.sort(outputVals);

		final double uniformDiff = 4 * (outputVals[3] - outputVals[0])/4;
		double diff = outputVals[3] - outputVals[2];
		assertTrue(diff<=uniformDiff);

		diff = outputVals[2] - outputVals[1];
		assertTrue(diff<=uniformDiff);

		diff = outputVals[1] - outputVals[0];
		assertTrue(diff<=uniformDiff);
	}
}
