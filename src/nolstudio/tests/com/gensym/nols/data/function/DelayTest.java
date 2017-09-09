package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class DelayTest
{
	private Delay testObj;

	@Before
	public void initObject()
	{
		testObj = new Delay();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Delay", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = Delay(A, B).  Returns the value of variable A, "
				+ "B seconds before the current time.";
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
		final double[] inputVals = {2000.0, 3000.0, 4000.0, 5000.0};
		final double[] delays = {100.0, 200.0, 300.0, 400.0};
		final double[] outputVals = new double[inputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inputVals);
		inputVector.addElement(delays);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(outputVals[0], 2000.0, 0);
		assertEquals(outputVals[1], 2000.0, 0);
		assertEquals(outputVals[2], 2000.0, 0);
		assertEquals(outputVals[3], 2000.0, 0);
		assertEquals(400000, testObj.getRequiredHistoryLength());
	}
}
