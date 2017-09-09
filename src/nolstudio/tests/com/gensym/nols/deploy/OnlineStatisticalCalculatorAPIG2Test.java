package com.gensym.nols.deploy;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.powermock.api.mockito.PowerMockito.doNothing;

import org.junit.Before;
import org.junit.Test;
import org.powermock.api.mockito.PowerMockito;

import com.gensym.classes.FloatArray;
import com.gensym.classes.FloatArrayImpl;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 * Unit test for the class
 * com.gensym.nols.deploy.OnlineStatisticalCalculatorAPIG2
 *
 * @author Ambarish
 *
 */
public class OnlineStatisticalCalculatorAPIG2Test
{

	private OnlineStatisticalCalculatorAPIG2 testObj;

	private Sequence sequence;
	private int arrayLength;

	/**
	 * Initialize test variables
	 *
	 * @throws G2AccessException
	 */
	@Before
	public void initApi() throws G2AccessException
	{
		testObj = new OnlineStatisticalCalculatorAPIG2();

		final FloatArray rows = new FloatArrayImpl();
		final FloatArray rowsTwo = new FloatArrayImpl();

		rows.setG2ArrayContents(new double[] { 1.4, 2.6, 3.8, 5.0, 7.5 });
		rowsTwo.setG2ArrayContents(new double[] { 11.4, 12.6, 31.8, 22.3 });
		arrayLength=rows.getArrayLength();

		sequence = new Sequence();
		sequence.add(rows);
		sequence.add(rowsTwo);
	}

	/**
	 * Test for debug processor
	 */
	@Test
	public void testDebugProcessor()
	{
		testObj.setDebugProcessor(true);
		assertTrue(testObj.getDebugProcessor());
	}

	/**
	 * Test method for pca full
	 *
	 * @throws NoSuchAttributeException
	 */
	@Test
	public void testPcaFull() throws NoSuchAttributeException
	{
		final Structure structure = testObj.pcaFull(sequence);
		final Symbol symbol = Symbol.intern("RETVAL");
		final Sequence resultSequence = (Sequence)structure.getAttributeValue(symbol);
		final Sequence tempSequence = (Sequence)resultSequence.get(0);
		final Sequence varTempSequence = (Sequence)resultSequence.get(1);
		final Sequence meanSequence = (Sequence)resultSequence.get(2);
		final Sequence stdSequence = (Sequence)resultSequence.get(3);
		assertEquals(4, resultSequence.size());

		assertEquals(arrayLength, tempSequence.size());
		assertEquals(tempSequence.get(0).toString(), "[0.5, -0.4472135954999579]");
		assertEquals(tempSequence.get(1).toString(), "[0.5, -0.4472135954999579]");
		assertEquals(tempSequence.get(2).toString(), "[0.0, -0.44721359549995804]");
		assertEquals(tempSequence.get(3).toString(), "[0.5, -0.4472135954999579]");

		assertEquals(2, varTempSequence.size());
		assertEquals(varTempSequence.get(0).toString(), "1.0");
		assertEquals(varTempSequence.get(1).toString(), "1.0");

		assertEquals(arrayLength, meanSequence.size());
		assertEquals(meanSequence.get(0).toString(), "6.4");
		assertEquals(meanSequence.get(1).toString(), "7.6");
		assertEquals(meanSequence.get(2).toString(), "17.8");
		assertEquals(meanSequence.get(3).toString(), "13.65");

		assertEquals(arrayLength, stdSequence.size());
		assertEquals(stdSequence.get(0).toString(), "7.0710678118654755");
		assertEquals(stdSequence.get(1).toString(), "7.0710678118654755");
		assertEquals(stdSequence.get(2).toString(), "19.79898987322333");
		assertEquals(stdSequence.get(3).toString(), "12.232947314527273");
	}

	/**
	 * Test method for pca weights
	 *
	 * @throws NoSuchAttributeException
	 */
	@Test
	public void testPcaWeights() throws NoSuchAttributeException
	{
		final Structure structure = testObj.pcaWeights(sequence);
		final Symbol symbol = Symbol.intern("RETVAL");
		final Sequence resultSequence =(Sequence)structure.getAttributeValue(symbol);

		assertEquals(arrayLength, resultSequence.size());
		double[] returnVals =  (double[])resultSequence.get(0);
		assertEquals(2, returnVals.length);
		assertEquals(returnVals[0], -0.2702787436542171, 0.0);
		assertEquals(returnVals[1], -0.20836156779400566, 0.0);

		returnVals =  (double[])resultSequence.get(1);
		assertEquals(returnVals[0], -0.29461222145029126, 0.0);
		assertEquals(returnVals[1], -0.2979204439594656, 0.0);

		returnVals =  (double[])resultSequence.get(2);
		assertEquals(returnVals[0], -0.7543471344522006, 0.0);
		assertEquals(returnVals[1], -0.5744565022066699, 0.0);

		returnVals =  (double[])resultSequence.get(1);
		assertEquals(returnVals[0], -0.29461222145029126, 0.0);
		assertEquals(returnVals[1], -0.2979204439594656, 0.0);
	}

	/**
	 * Test method for pca components
	 *
	 * @throws NoSuchAttributeException
	 */
	@Test
	public void testPcaComponents() throws NoSuchAttributeException {
		final Structure structure = testObj.pcaComponents(sequence, 1);
		final Symbol symbol = Symbol.intern("RETVAL");
		final Sequence resultSequence =(Sequence)structure.getAttributeValue(symbol);
		assertEquals(arrayLength, resultSequence.size());

		double[] returnVal = (double[])resultSequence.get(0);
		assertEquals(-0.2702787436542171, returnVal[0], 0.0);

		returnVal = (double[])resultSequence.get(1);
		assertEquals(-0.29461222145029126, returnVal[0], 0.0);

		returnVal = (double[])resultSequence.get(2);
		assertEquals(-0.7543471344522006, returnVal[0], 0.0);

		returnVal = (double[])resultSequence.get(3);
		assertEquals(-0.5198586479870283, returnVal[0], 0.0);
	}

	/**
	 * Test method for pca variance
	 *
	 * @throws NoSuchAttributeException
	 */
	@Test
	public void testPcaVariance() throws NoSuchAttributeException {
		final Structure structure = testObj.pcaVariance(sequence, 1.0);
		final Symbol symbol = Symbol.intern("RETVAL");
		final Sequence resultSequence = (Sequence)structure.getAttributeValue(symbol);
		assertEquals(arrayLength, resultSequence.size());

		double[] returnVal = (double[])resultSequence.get(0);
		assertEquals(-0.2702787436542171, returnVal[0], 0.0);
		assertEquals(-0.20836156779400566, returnVal[1], 0.0);

		returnVal = (double[])resultSequence.get(1);
		assertEquals(-0.29461222145029126, returnVal[0], 0.0);
		assertEquals(-0.2979204439594656, returnVal[1], 0.0);

		returnVal = (double[])resultSequence.get(2);
		assertEquals(-0.7543471344522006, returnVal[0], 0.0);
		assertEquals(-0.5744565022066699, returnVal[1], 0.0);

		returnVal = (double[])resultSequence.get(3);
		assertEquals(-0.5198586479870283, returnVal[0], 0.0);
		assertEquals(-0.5528678312457594, returnVal[1], 0.0);
	}

	/**
	 * Test method for pls
	 *
	 * @throws NoSuchAttributeException
	 */
	@Test
	public void testPls() throws NoSuchAttributeException {
		final Structure structure = testObj.pls(sequence, sequence, 1);
		final Symbol symbol = Symbol.intern("RETVAL");
		final Sequence resultSequence =(Sequence)structure.getAttributeValue(symbol);
		final Sequence xmeanSequence = (Sequence)resultSequence.get(0);
		final Sequence ymeanSequence = (Sequence)resultSequence.get(1);
		final Sequence rSequence = (Sequence)resultSequence.get(2);
		final Sequence bSequence = (Sequence)resultSequence.get(3);
		final Sequence sSequence = (Sequence)resultSequence.get(4);
		assertEquals(5, resultSequence.size());
		assertEquals(arrayLength, xmeanSequence.size());

		Object[] returnVals = xmeanSequence.getContents();
		assertEquals(6.4, returnVals[0]);
		assertEquals(7.6, returnVals[1]);
		assertEquals(17.8, returnVals[2]);
		assertEquals(13.65, returnVals[3]);
		assertEquals(3.75, returnVals[4]);

		assertEquals(arrayLength, ymeanSequence.size());
		returnVals = ymeanSequence.getContents();
		assertEquals(6.4, returnVals[0]);
		assertEquals(7.6, returnVals[1]);
		assertEquals(17.8, returnVals[2]);
		assertEquals(13.65, returnVals[3]);
		assertEquals(3.75, returnVals[4]);

		assertEquals(arrayLength, rSequence.size());
		returnVals = rSequence.getContents();
		Object[] sequenceVals = ((Sequence)returnVals[0]).getContents();
		assertEquals("0.0632455532033676", sequenceVals[0].toString());

		assertEquals(1, bSequence.size());
		returnVals = bSequence.getContents();
		sequenceVals = ((Sequence)returnVals[0]).getContents();
		assertEquals("1.0000000000000004", sequenceVals[0].toString());

		assertEquals(1, sSequence.size());
		returnVals = sSequence.getContents();
		sequenceVals = ((Sequence)returnVals[0]).getContents();
		assertEquals("3.16227766016838", sequenceVals[0].toString());
	}
}
