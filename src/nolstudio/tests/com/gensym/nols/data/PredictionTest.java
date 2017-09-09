package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import com.gensym.math.matrix.Matrix;

public class PredictionTest
{
	/**
	 * Method to test argument constructor.
	 */
	@Test
	public void testConstructor()
	{
		final long[] timeStamps = new long[2];
		final Matrix Y = new Matrix();
		final Matrix YP = new Matrix();
		final int h = 3;

		final Prediction testObj = new Prediction(timeStamps, Y, YP, h);
		assertEquals(timeStamps, testObj.getTimeStamps());
		assertEquals(Y, testObj.getY());
		assertEquals(YP, testObj.getYP());
		assertEquals(h, testObj.getHorizon());
	}
}
