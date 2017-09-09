package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class DivideTest {

	private Divide testObj;

	@Before
	public void initObject()
	{
		testObj = new Divide();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("Divide", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = Divide(A,B).  Returns C = A/B";
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
		final double[] in1 = {2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 0, 100.0};
		final double[] in2 = {200.0, 30.0, 4.0, 500.0, 0, 9000.0, -0};
		final double[] outputVals = new double[in1.length];

		final Vector<double[]> inputVector = new Vector<>();
		inputVector.addElement(in1);
		inputVector.addElement(in2);
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);
		assertEquals(outputVals[0], 10, 0);
		assertEquals(outputVals[1], 100.0, 0);
		assertEquals(outputVals[2], 1000.0, 0);
		assertEquals(outputVals[3], 10.0, 0);
		assertEquals(outputVals[4], Double.POSITIVE_INFINITY, 0);
		assertEquals(outputVals[5], 0.0, 0);
		assertEquals(outputVals[6], Double.POSITIVE_INFINITY, 0);
	}
}
