package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class DerivativePolyTest
{
	private DerivativePoly testObj;

	@Before
	public void initObject()
	{
		testObj = new DerivativePoly();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("DerivativePoly", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = DerivativePoly(A). Returns the derivative value of A over time. "
				+ "Must have more than 9 points.";
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
	public void testEvaluateForSevenInputValues() throws MathException
	{
		final double[] fourInputVals = {2000.0, 3000.0, 4000.0, 5000.0};
		final double[] fourOutputVals = new double[fourInputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(fourInputVals);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(fourOutputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};
		testObj.evaluate(t, inputVector, outputVector);// nothing to test here. here it has simply return

		final double[] sevenInputFields = {2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 7000.0, 1000.0};
		final double[] sevenOutputVals = new double[sevenInputFields.length];
		inputVector.remove(0);
		inputVector.addElement(sevenInputFields);
		outputVector.remove(0);
		outputVector.addElement(sevenOutputVals);
		testObj.evaluate(t, inputVector, outputVector);
	}


	/**
	 * Method to test evaluate()
	 * @throws MathException
	 */
	@Test
	public void testEvaluateForSixInputValues() throws MathException
	{
		final double[] inputVals = {2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 7000.0};
		final double[] outputVals = new double[inputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inputVals);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};
		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(Double.NaN, outputVals[4], 0.0);
		assertEquals(Double.NaN, outputVals[5], 0.0);
		assertEquals(0, testObj.getRequiredHistoryLength());
	}

	/**
	 * Method to test evaluate()
	 * @throws MathException
	 */
	@Test
	public void testEvaluateForNineInputValues() throws MathException
	{
		final double[] inputVals = {2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 7000.0, 8000.0, 9000.0, 10000.0};
		final double[] outputVals = new double[inputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inputVals);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};
		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(Double.NaN, outputVals[8], 0.0);
		assertEquals(Double.NaN, outputVals[7], 0.0);
	}

	/**
	 * Method to test evaluate() for five input values.
	 * @throws MathException
	 */
	@Test
	public void testEvaluateForFiveInputValues() throws MathException
	{
		final double[] inputVals = {2000.0, 3000.0, 4000.0, 5000.0, 6000.0};
		final double[] outputVals = new double[inputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inputVals);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};
		// TODO this invocation is throwing ArrayIndexOutOfBooundsException
		testObj.evaluate(t, inputVector, outputVector);
	}

	/**
	 * Method to test evaluate() for five input values.
	 * @throws MathException
	 */
	@Test
	public void testEvaluateForEightInputValues() throws MathException
	{
		final double[] inputVals = {2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 7000.0, 8000.0, 9000.0};
		final double[] outputVals = new double[inputVals.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(inputVals);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};
		// TODO this invocation is throwing ArrayIndexOutOfBooundsException
		testObj.evaluate(t, inputVector, outputVector);
	}
}
