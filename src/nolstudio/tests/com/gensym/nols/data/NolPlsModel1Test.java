package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.mockito.Mockito.times;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.mockStatic;
import static org.powermock.api.mockito.PowerMockito.verifyStatic;
import static org.powermock.api.mockito.PowerMockito.when;

import java.util.Vector;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.core.classloader.annotations.SuppressStaticInitializationFor;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.Model;
import com.gensym.math.datafit.Pls;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;

@RunWith(PowerMockRunner.class)
@PrepareForTest({Matlib.class, Matrix.class, DataSeries.class, Stats.class})
@SuppressStaticInitializationFor({"com.gensym.math.matrix.Matrix", "com.gensym.math.matrix.Matlib"})
public class NolPlsModel1Test
{
	@Test
	public void testConstructor()
	{
		final NolPlsModel testObj = createTestObject();
		assertNotNull(testObj);
	}

	/**
	 * Method to test train() method
	 * @throws Exception
	 */
	@Test
	public void testTrain() throws Exception
	{
		final NolPlsModel testObj = createTestObject();
		testObj.setFixedFactor(true);

		final Pls pls = mock(Pls.class);
		final Vector<TrainableModel> models = new Vector<>();
		models.addElement(pls);
		Whitebox.setInternalState(testObj, "models", models);

		final Vector<Double> ratings = new Vector<>();
		ratings.addElement(10.0);
		Whitebox.setInternalState(testObj, "ratings", ratings);

		final Matrix X = mock(Matrix.class);
		final Matrix Y = mock(Matrix.class);
		when(X.getRows()).thenReturn(10);

		final Matrix m = mock(Matrix.class);
		when(m.getCols()).thenReturn(2);
		when(m.get(0, 0)).thenReturn(3.0);

		mockStatic(Matlib.class);
		when(Matlib.class, "createMatrix").thenReturn(m);

		testObj.train(X, Y);
		verifyStatic(times(44));
		Matlib.clear(Matchers.any(Matrix.class));
	}

	/**
	 * Method to test train() method
	 * @throws Exception
	 */
	@Test
	public void testTrainForFixedFactorElse() throws Exception
	{
		final NolPlsModel testObj = createTestObject();
		testObj.setFixedFactor(false);

		final Matrix m = mock(Matrix.class);
		when(m.getCols()).thenReturn(2);
		when(m.get(0, 0)).thenReturn(3.0);

		mockStatic(Matlib.class);
		when(Matlib.class, "createMatrix").thenReturn(m);
		when(Matlib.class, "zeros", Matchers.anyInt(), Matchers.anyInt()).thenReturn(m);

		final int nin = 2;
		final int nout = 2;
		final int nhidden = 2;
		final int nfactors = 2;
		final ArchitectureParameters AP = new ArchitectureParameters(nin, nout, nhidden, nfactors);
		final Pls pls = new Pls(AP);

		final TrainableModel M = mock(TrainableModel.class);
		final Matrix X1 = mock(Matrix.class);
		final Matrix Y2 = mock(Matrix.class);
		final ValidationParameters testingResults = new ValidationParameters(M, X1, Y2);
		testingResults.chisq = 15.0;
		Whitebox.setInternalState(pls, "testingResults", testingResults);

		final ValidationParameters trainingResults = new ValidationParameters(M, X1, Y2);
		trainingResults.chisq = 10.0;
		Whitebox.setInternalState(pls, "trainingResults", trainingResults);

		final Vector<TrainableModel> models = new Vector<>();
		models.addElement(pls);
		Whitebox.setInternalState(testObj, "models", models);

		final Vector<Double> ratings = new Vector<>();
		ratings.addElement(10.0);
		Whitebox.setInternalState(testObj, "ratings", ratings);

		final Matrix X = mock(Matrix.class);
		final Matrix Y = mock(Matrix.class);
		when(X.getRows()).thenReturn(10);

		mockStatic(Matrix.class);
		testObj.train(X, Y);

		assertNotNull(testObj.getModel());
		assertEquals(pls, testObj.getModel());
		assertEquals(10, testObj.size());
		final String description = "Pls with 2 factors";
		assertEquals(description, testObj.getDescription());
	}

	/**
	 * private method to create NolPlsModel object
	 * @return
	 */
	private NolPlsModel createTestObject()
	{
		final int nin = 2;
		final int nout = 2;
		final int nhidden = 2;
		final int nfactors = 0;
		final ArchitectureParameters AP = new ArchitectureParameters(nin, nout, nhidden, nfactors);

		final String name = "TestInput";
		final Vector outs = new Vector<>();
		final Vector ins = new Vector<>();
		final Vector oDelays = new Vector<>();
		final Vector iDelays = new Vector<>();
		final Preprocessor prep = mock(Preprocessor.class);

		final NolPlsModel testObj = new NolPlsModel(AP, name, outs, ins, oDelays, iDelays, prep);
		testObj.VERBOSE = true;
		return testObj;
	}

	/**
	 * Method to test addModel() for (rating > rat) block
	 * @throws MathException
	 */
	@Test
	public void testAddModel() throws MathException
	{
		final Model M = mock(Model.class);
		final double rating = 11.0;
		final NolPlsModel testObj = createTestObject();

		final int nin = 2;
		final int nout = 2;
		final int nhidden = 2;
		final int nfactors = 0;
		final ArchitectureParameters AP = new ArchitectureParameters(nin, nout, nhidden, nfactors);

		when(M.getArchitectureParameters()).thenReturn(AP);
		final Pls pls = mock(Pls.class);
		final Vector<TrainableModel> models = new Vector<>();
		final Vector<Double> ratings = new Vector<>();
		for(int i =0; i<10; i++)
		{
			models.addElement(pls);
			ratings.addElement(10.0);
		}
		Whitebox.setInternalState(testObj, "models", models);
		Whitebox.setInternalState(testObj, "ratings", ratings);

		assertEquals(0, testObj.addModel(M, rating));
	}

	/**
	 * Method to test getParametersVector
	 * @throws MathException
	 */
	@Test
	public void testGetParametersVector() throws MathException
	{
		final NolPlsModel testObj = createTestObject();

		final Vector<TrainableModel> models = new Vector<>();
		final Pls pls = mock(Pls.class);
		models.addElement(pls);
		Whitebox.setInternalState(testObj, "models", models);

		final Vector<Integer> intVect = new Vector<>();
		intVect.addElement(3);
		when(pls.getPlsParametersVector()).thenReturn(intVect);

		testObj.setParametersVector(intVect);
		final Vector<Integer> returnVal = testObj.getParametersVector();
		assertEquals(3, returnVal.size());
		assertEquals(new Integer(1), returnVal.get(0));
		assertEquals(new Integer(1), returnVal.get(1));
		assertEquals(new Integer(3), returnVal.get(2));
	}

	/**
	 * Method to test getParameterMatrix()
	 * @throws MathException
	 */
	@Test
	public void testGetParameterMatrix() throws MathException
	{
		final NolPlsModel testObj = createTestObject();
		final Pls pls = mock(Pls.class);
		final Vector<TrainableModel> models = new Vector<>();
		models.addElement(pls);
		Whitebox.setInternalState(testObj, "models", models);

		final Matrix P = mock(Matrix.class);
		final Matrix r = mock(Matrix.class);
		when(pls.getR()).thenReturn(r);
		when(pls.getB()).thenReturn(r);
		when(pls.getS()).thenReturn(r);

		mockStatic(Matlib.class);
		testObj.getParameterMatrix(P);

		verifyStatic(times(2));
		Matlib.clear(Matchers.any(Matrix.class));
		Matlib.multiplyElements(r, r, P);
		Matlib.multiply(P, r, P);
	}

	/**
	 * Method to test writePLSWeightFile()
	 */
	@Test
	public void testWritePLSWeightFile()
	{
		//String dir = "",String fileName
	}

	@Test
	public void testCalculateModelStatistics() throws MathException
	{
		mockStatic(Matlib.class);
		final Matrix m = mock(Matrix.class);
		when(Matlib.createMatrix()).thenReturn(m);
		when(m.get(Matchers.anyInt())).thenReturn(10.0);

		final int nin = 2;
		final int nout = 2;
		final int nhidden = 2;
		final int nfactors = 2;
		final ArchitectureParameters AP = new ArchitectureParameters(nin, nout, nhidden, nfactors);
		final Pls pls = new Pls(AP);

		final TrainableModel M = mock(TrainableModel.class);
		final Matrix X1 = mock(Matrix.class);
		final Matrix Y2 = mock(Matrix.class);

		final ValidationParameters testingResults = new ValidationParameters(M, X1, Y2);
		testingResults.chisq = 15.0;
		Whitebox.setInternalState(pls, "testingResults", testingResults);

		final ValidationParameters trainingResults = new ValidationParameters(M, X1, Y2);
		trainingResults.chisq = 10.0;
		Whitebox.setInternalState(pls, "trainingResults", trainingResults);

		final NolPlsModel testObj = createTestObject();
		Whitebox.setInternalState(testObj, "model", pls);
		testObj.setIsTrained(true);
		testObj.calculateModelStatistics();
		assertEquals(10.0, testObj.getModelRate(),0);
	}

	@Test
	public void testSetFixedFactorNumber()
	{
		final NolPlsModel testObj = createTestObject();
		testObj.setFixedFactorNumber(10);
		final int fixedFactorNumber = Whitebox.getInternalState(testObj, "fixedFactorNumber");
		assertEquals(10, fixedFactorNumber);
	}
}
