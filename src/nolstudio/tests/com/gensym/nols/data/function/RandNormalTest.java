package com.gensym.nols.data.function;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class RandNormalTest
{
	private RandNormal testObj;

	@Before
	public void initObject()
	{
		testObj = new RandNormal();
	}
	/**
	 * Method to test getName()
	 */
	@Test
	public void testGetName()
	{
		assertEquals("RandNormal", testObj.getName());
	}

	/**
	 * Method to test getDescription()
	 */
	@Test
	public void testGetDescription()
	{
		final String description = "C = RandNormal(A,B). Returns normally-distributed random numbers, "
				+ "with mean A and standard deviation B.";
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
	 * Method to test evaluate().
	 * @throws MathException
	 */
	@Test
	public void testEvaluate() throws MathException
	{
		final Vector<double[]> inputVector = new Vector<>();
		// The "class under test" calls this "mean", while
		// it's actually more of (changing) bias or offset.
		// While it's strange to have a changing bias, we can
		// "test around" that. Keep in mind that the more
		// numbers you put into input, the "better" results
		// you get - that is, the mean and std dev of the
		// result(s) should be closer to expected
		final double[] means = {2.1, 2.9, 0.2, -2.0, 8.2, 5.5, 0, -22, 3.92, -0.41 };
		inputVector.addElement(means);
		// The "class under test" calls this "standard
		// deviation", while it's more of a (changing)
		// amplitude for the random signal (which has a mean
		// of 0 and std dev of 1). We can't think of a way to
		// test a random signal with a changing amplitude, so
		// we use the same amplitude for all inputs.
		final double amp = 3.141592;
		final double[] stdDev = { amp, amp, amp, amp, amp, amp, amp, amp, amp, amp };
		inputVector.addElement(stdDev);

		final double[] outputVals = new double[means.length];
		final Vector<double[]> outputVector = new Vector<>();
		outputVector.addElement(outputVals);
		final long[] t = {5000l, 6000l, 7000l, 8000l};

		testObj.evaluate(t, inputVector, outputVector);

		final double inputValsMean = calculateMean(means);
		final double outValsMean = calculateMean(outputVals);
		// This is a very "forgiving" test, but, since the
		// "signal" is random, even this is not 100% safe
		assertEquals(inputValsMean, outValsMean, amp);

		final double outValsSD = calculateStandardDeviation(outputVals);
		// We haven't "done the math" to try to figure out
		// what is really the expected "deviation from
		// deviation", even for the same A ("mean", "bias"),
		// let alone for the changing one. But, this seems to
		// be good/safe and has proved such in our tests.
		assertEquals(amp, outValsSD, amp*amp);
	}

	/**
	 * Helper method to calculate mean
	 * @param inputVals
	 * @return
	 */
	private double calculateMean(double[] inputVals)
	{
		double sum = 0;
		for(final double d:inputVals)
		{
			sum += d;
		}
		return (sum/inputVals.length);
	}

	/**
	 * Helper method to calculate Standard Deviation
	 * @param inputVals
	 * @return
	 */
	private double calculateStandardDeviation(double[] inputVals)
	{
		final double average = calculateMean(inputVals);

		double finalsumX=0;
		for (int i = 0; i<inputVals.length; i++){
			finalsumX += (Math.pow((inputVals[i] - average), 2));
		}
		return Math.sqrt(finalsumX/(inputVals.length));
	}
}
