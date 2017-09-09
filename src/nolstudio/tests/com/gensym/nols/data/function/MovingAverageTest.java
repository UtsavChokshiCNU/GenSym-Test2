package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class MovingAverageTest
{
	private MovingAverage testObj;

	@Before
	public void initObject()
	{
		testObj = new MovingAverage();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("MovingAverage", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = MovingAverage(A, B).  Returns the average value "
				+ "of A over the previous B seconds.";
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
		final double[] outputVals = new double[5];
		final Vector<double[]> inputVector = new Vector<>();

		final double[] inValues = {10.0, 20.0, 40.0, 90.0};
		final double[] intervals = {1.0, 2.0, 4.0, 9.0};
		inputVector.addElement(inValues);
		inputVector.addElement(intervals);

		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(10.0, outputVals[0], 0);
		assertEquals(15.0, outputVals[1], 0);
		assertEquals(23.333333333333332, outputVals[2], 0);
		assertEquals(40.0, outputVals[3], 0);
		assertEquals(0.0, outputVals[4], 0);
		assertEquals(9000, testObj.getRequiredHistoryLength());
	}
}
