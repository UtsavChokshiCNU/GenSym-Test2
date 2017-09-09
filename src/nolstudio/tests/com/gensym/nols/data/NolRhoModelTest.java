package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

import java.io.IOException;
import java.util.Vector;

import org.junit.Test;
import org.mockito.Matchers;
import org.mockito.Mockito;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ClassicRbfn;
import com.gensym.math.matrix.Matrix;

public class NolRhoModelTest
{

	@Test
	public void testConstructor() throws MathException
	{
		final NolRhoModel testObj = createTestObject();
		assertNotNull(testObj);
	}

	/**
	 * Method to test train()
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testTrain() throws MathException, IOException
	{
		final Matrix XTrain = new Matrix();
		final Matrix YTrain = new Matrix();

		final NolClassicModelTrainer trainer = mock(NolClassicModelTrainer.class);
		final String[] fileNames = {"File1", "File2"};

		when(trainer.makeRPCfileNames()).thenReturn(fileNames);
		final NolRhoModel testObj = createTestObject();
		testObj.setTrainer(trainer);
		testObj.train(XTrain, YTrain);
		Mockito.verify(trainer).informListeners(Matchers.eq("error"), Matchers.anyString());
		Mockito.verify(trainer).deleteFiles(fileNames);
	}

	@Test
	public void testSetRunningParameter() throws MathException
	{
		final NolRhoModel testObj = createTestObject();
		testObj.setRunningParameter(1);	//  other than zero case
		assertEquals(testObj.getOutputDelays().size(), 2);
		assertEquals(new Long(10000), testObj.getOutputDelays().get(0));
		assertEquals(new Long(10001), testObj.getOutputDelays().get(1));

		testObj.setRunningParameter(0);	// for zero case
		assertEquals(testObj.getOutputDelays().size(), 1);
		final Object element = testObj.getOutputDelays().get(0);
		assertEquals(new Long(10000), element);
	}

	private NolRhoModel createTestObject() throws MathException
	{
		final int[] nodes = {1,2,3};
		final double overlap = 1.0;
		final int unitType = 1;

		final ClassicRbfn net = new ClassicRbfn(nodes, overlap, unitType);
		final String name = "Test Name";
		final Vector outs = new Vector<>();
		outs.addElement(10.0);
		outs.addElement(11.0);
		final Vector ins = new Vector<>();
		final Vector oDelays = new Vector<>();
		oDelays.addElement(10000l);
		oDelays.addElement(10001l);
		final Vector iDelays = new Vector<>();

		final DataSeries ds = new DataSeries();
		final Project p = new Project();
		final Vector<Variable> varObjs = new Vector<>();
		final Variable var = new Variable("Preprocessor1", ds, 1);
		varObjs.addElement(var);
		final ViewFilter filter = new ViewFilter();
		final Preprocessor prep = new Preprocessor("Preprocessor1", p, varObjs, filter);

		final NolRhoModel testObj = new NolRhoModel(net, name, outs, ins, oDelays, iDelays, prep);
		return testObj;
	}

	/**
	 * Method to test readPredictionFromFile()
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testReadPredictionFromFile() throws MathException, IOException
	{
		final String infile = "This test String to test the method ReadPrediction; "
				+ "this input String requires alphabates, numbers";
		final Matrix YPred = new Matrix();
		final NolRhoModel testObj = createTestObject();
		testObj.readPredictionFromFile(infile, YPred);
		assertTrue(testObj.isNormalizeData());
	}
}
