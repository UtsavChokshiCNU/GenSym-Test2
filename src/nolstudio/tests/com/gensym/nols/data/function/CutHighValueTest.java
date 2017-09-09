package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class CutHighValueTest
{

	private CutHighValue testObj;

	@Before
	public void initObject()
	{
		testObj = new CutHighValue();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("CutHighValue", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = CutHighValue(A, B).  If A > B, then C = NaN, otherwise C = A.";
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
		final double minVal = Double.MIN_VALUE;
		final double maxVal = Double.MAX_VALUE;

		final double[] inputVals = {minVal, maxVal, -1100, 900};
		final double[] thresholds = {maxVal, minVal, -1900, 1900};
		final double[] outputVals = new double[inputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inputVals);
		inputVector.addElement(thresholds);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = new long[1];

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(outputVals[0], Double.MIN_VALUE, 0);
		assertEquals(outputVals[1], Double.NaN, 0);
		assertEquals(outputVals[2], Double.NaN, 0);
		assertEquals(outputVals[3], 900, 0);
	}
}