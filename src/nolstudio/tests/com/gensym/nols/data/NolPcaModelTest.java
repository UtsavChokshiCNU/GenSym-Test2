package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.mockito.Mockito.times;
import static org.powermock.api.mockito.PowerMockito.doNothing;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.mockStatic;
import static org.powermock.api.mockito.PowerMockito.verifyStatic;
import static org.powermock.api.mockito.PowerMockito.when;

import java.io.BufferedWriter;
import java.util.Vector;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.core.classloader.annotations.SuppressStaticInitializationFor;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;

@RunWith(PowerMockRunner.class)
@PrepareForTest({Matlib.class, Matrix.class, DataSeries.class, Stats.class})
@SuppressStaticInitializationFor({"com.gensym.math.matrix.Matrix", "com.gensym.math.matrix.Matlib"})
public class NolPcaModelTest
{
	/**
	 * Method to test NolPcaModel() forString& Vector inputs
	 */
	@Test
	public void testNolPcaModel()
	{
		final DataSeries ds = mock(DataSeries.class);
		final Variable var = new Variable("TestVariable", ds, 1);

		final Vector<Variable> varObjs = new Vector<>();
		varObjs.addElement(var);
		final NolPcaModel testObj = new NolPcaModel("TestPCA", varObjs);
		assertNotNull(testObj);
		assertEquals(ds, testObj.getDataSeries());
		assertEquals(1, testObj.getNin());
		assertEquals(0, testObj.getNout());
	}

	/**
	 * Method to test NolPcaModel for Preprocessor input object
	 * @throws MathException
	 */
	@Test
	public void testNolPcaModelForPreprocessor() throws MathException
	{
		final NolPcaModel testObj = createTestObj();
		assertNotNull(testObj);
	}

	/**
	 * Method to test train() for badMatrix block
	 * @throws Exception
	 */
	@Test(expected = MathException.class)
	public void testTrainForMathException() throws Exception
	{
		final NolPcaModel testObj = createTestObj();
		final Matrix m = mock(Matrix.class);
		when(m.getCols()).thenReturn(4);
		when(m.get(0, 0)).thenReturn(3.0);

		mockStatic(Matlib.class);
		when(Matlib.class, "createMatrix").thenReturn(m);
		when(Matlib.createMatrix(Matchers.eq(1), Matchers.anyInt())).thenReturn(m);
		doNothing().when(Matlib.class, "sum", Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		testObj.train();
	}

	@Test
	public void testGetRetainedFactorNumber() throws MathException
	{
		final NolPcaModel testObj = createTestObj();
		assertEquals(5,testObj.getRetainedFactorNumber());
	}

	/**
	 * Method to test fullEvaluate()
	 * @throws MathException
	 */
	@Test
	public void testFullEvaluate() throws MathException
	{
		final NolPcaModel testObj = createTestObj();

		final Matrix X = mock(Matrix.class);
		final Matrix pc = mock(Matrix.class);
		final Matrix Res = mock(Matrix.class);
		mockStatic(Matlib.class);

		final Matrix P = mock(Matrix.class);
		Whitebox.setInternalState(testObj, "P", P);

		testObj.fullEvaluate(X, pc, Res);
		verifyStatic(times(2));
		Matlib.clear(Matchers.any(Matrix.class));
	}

	/**
	 * Method to test evaluate()
	 * @throws MathException
	 */
	@Test
	public void testEvaluate() throws MathException
	{
		final NolPcaModel testObj = createTestObj();

		final Matrix X = mock(Matrix.class);
		final Matrix pc = mock(Matrix.class);
		mockStatic(Matlib.class);

		final Matrix P = mock(Matrix.class);
		Whitebox.setInternalState(testObj, "P", P);

		testObj.evaluate(X, pc);
		verifyStatic(times(2));
		Matlib.clear(Matchers.any(Matrix.class));
	}

	/**
	 *	Method to test setRetainedFactorNumber()
	 * @throws Exception
	 */
	@Test
	public void testSetRetainedFactorNumber() throws Exception
	{
		final NolPcaModel testObj = createTestObj();
		final Matrix Variants = mock(Matrix.class);
		when(Variants.getCols()).thenReturn(9);
		Whitebox.setInternalState(testObj, "Variants", Variants);

		mockStatic(Matlib.class);
		final Matrix m = mock(Matrix.class);
		when(m.getCols()).thenReturn(4);
		when(Matlib.class, "createMatrix").thenReturn(m);
		when(Matlib.createMatrix(Matchers.eq(1), Matchers.anyInt())).thenReturn(m);
		when(m.get(0, 0)).thenReturn(5.0);
		doNothing().when(Matlib.class, "sum", Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		testObj.setRetainedFactorNumber(9);

		assertEquals(Double.NaN, testObj.getQ(), 0);
		assertEquals(Variants, testObj.getVariants());
		assertEquals("", testObj.getDescription());

		//this scenario modifies th1, th2, th3 values
		when(Variants.getCols()).thenReturn(10);
		final Matrix goodRows = mock(Matrix.class);
		when(goodRows.getRows()).thenReturn(2);
		when(goodRows.get(0, 0)).thenReturn(1.0);
		when(goodRows.get(1, 0)).thenReturn(2.0);
		when(Matlib.class, "createMatrix").thenReturn(goodRows);// for good rows object

		final Matrix ssq = mock(Matrix.class);
		when(ssq.get(Matchers.anyInt())).thenReturn(1.0);
		Whitebox.setInternalState(testObj, "ssq", ssq);
		when(Matlib.class, "createMatrix").thenReturn(m);	// for other objects
		testObj.setRetainedFactorNumber(9);
		assertEquals(3.764348422496632, testObj.getQ(), 0);

		testObj.setRetainedFactorNumber(-1);// this throws Exception
		verifyStatic(times(18));
		Matlib.clear(Matchers.any(Matrix.class));

	}

	/**
	 * Helper method to create test object
	 * @return
	 * @throws MathException
	 */
	private NolPcaModel createTestObj() throws MathException
	{
		final DataSeries ds = mock(DataSeries.class);
		when(ds.getColumn()).thenReturn(4);
		final Matrix dataMatrix = mock(Matrix.class);
		when(ds.getDataMatrix()).thenReturn(dataMatrix);

		final Vector<Variable> varObjs = new Vector<>();
		final Variable var = new Variable("Preprocessor1", ds, 1);
		varObjs.addElement(var);
		final Preprocessor processor = mock(Preprocessor.class);
		when(processor.getVariableFromVariableName("Preprocessor1")).thenReturn(var);

		final Vector<String> strVector = new Vector<>();
		strVector.addElement("Preprocessor1");
		strVector.addElement("Preprocessor2");

		final NolPcaModel testObj = new NolPcaModel("TestPCA", strVector, processor);
		return testObj;
	}

	/**
	 * Method to cover getT2Statistics, getQ, getT2Limits methods
	 * @throws MathException
	 */
	@Test
	public void testProperties() throws MathException
	{
		final NolPcaModel testObj =  createTestObj();
		final Matrix T2 = mock(Matrix.class);

		Whitebox.setInternalState(testObj, "T2", T2);
		assertEquals(new Double(0.0), new Double(testObj.getQ()));
		assertEquals(T2, testObj.getT2Statistics());
		assertEquals(new Double(0), new Double(testObj.getT2Limits()));
	}

	/**
	 * Method to test train().
	 * @throws Exception
	 */
	@Test(expected = MathException.class)
	public void testTrain() throws Exception
	{
		final DataSeries ds = mock(DataSeries.class);
		when(ds.getColumn()).thenReturn(4);
		final Matrix dataMatrix = mock(Matrix.class);
		when(ds.getDataMatrix()).thenReturn(dataMatrix);
		when(dataMatrix.getCols()).thenReturn(1);

		final Vector<Variable> varObjs = new Vector<>();
		final Variable var = new Variable("Preprocessor1", ds, 1);
		when(ds.getVarByIndex(Matchers.anyInt())).thenReturn(var);

		varObjs.addElement(var);
		final Preprocessor processor = mock(Preprocessor.class);
		when(processor.getVariableFromVariableName("Preprocessor1")).thenReturn(var);

		final Vector<String> strVector = new Vector<>();
		strVector.addElement("Preprocessor1");
		strVector.addElement("Preprocessor2");

		final NolPcaModel testObj = new NolPcaModel("TestPCA", strVector, processor);

		final Matrix m = mock(Matrix.class);
		when(m.getCols()).thenReturn(4);
		when(m.getRows()).thenReturn(1);
		when(m.get(0, 0)).thenReturn(10.0);

		mockStatic(Matlib.class);
		mockStatic(Stats.class);

		when(Matlib.class, "createMatrix").thenReturn(m);
		when(Matlib.createMatrix(Matchers.eq(1), Matchers.anyInt())).thenReturn(m);
		doNothing().when(Matlib.class, "sum", Matchers.any(Matrix.class), Matchers.any(Matrix.class));

		testObj.train();
		verifyStatic(times(6));
		Matlib.clear(Matchers.any(Matrix.class));
		assertEquals(Double.NaN, testObj.getQ(), 0);

		// Below scenario evaluates th1, th2, th3 variables
		when(Matlib.class, "createMatrix").thenReturn(m, m, m, m, m, m, m);
		final Matrix variant = mock(Matrix.class);
		when(variant.getCols()).thenReturn(3);
		when(variant.get(1)).thenReturn(1.0);
		when(Matlib.class, "createMatrix").thenReturn(variant);

		final Matrix ssq = mock(Matrix.class);
		when(ssq.get(1)).thenReturn(1.0);
		when(ssq.get(3)).thenReturn(1.0);
		when(ssq.getCols()).thenReturn(3);
		when(Matlib.class, "createMatrix").thenReturn(ssq);

		testObj.train();

		verifyStatic(times(12));
		Matlib.clear(Matchers.any(Matrix.class));
		assertEquals(3.764348422496632, testObj.getQ(), 0);

		when(ssq.getCols()).thenReturn(0);// tests the case for retainedFactorNumber for negative integer.
		testObj.train();	// this throws the exception
	}

	/**
	 * Method to test train() for if(badMatrix) block
	 * @throws Exception
	 */
	@Test(expected = MathException.class)
	public void testTrainForBadMatrixBlock() throws Exception
	{
		final DataSeries ds = mock(DataSeries.class);
		when(ds.getColumn()).thenReturn(4);
		final Matrix dataMatrix = mock(Matrix.class);
		when(ds.getDataMatrix()).thenReturn(dataMatrix);
		when(dataMatrix.getCols()).thenReturn(1);

		final Vector<Variable> varObjs = new Vector<>();
		final Variable var = new Variable("Preprocessor1", ds, 1);
		when(ds.getVarByIndex(Matchers.anyInt())).thenReturn(var);

		varObjs.addElement(var);
		final Preprocessor processor = mock(Preprocessor.class);
		when(processor.getVariableFromVariableName("Preprocessor1")).thenReturn(var);

		final Vector<String> strVector = new Vector<>();
		strVector.addElement("Preprocessor1");
		strVector.addElement("Preprocessor2");

		final NolPcaModel testObj = new NolPcaModel("TestPCA", strVector, processor);
		final Matrix m = mock(Matrix.class);
		when(m.getCols()).thenReturn(4);
		when(m.getRows()).thenReturn(1);

		when(m.get(0, 0)).thenReturn(10.0);

		mockStatic(Matlib.class);
		final Matrix badCols = mock(Matrix.class);
		when(badCols.getCols()).thenReturn(1);
		when(badCols.get(0, 0)).thenReturn(1.0);
		when(Matlib.class, "createMatrix", 1, 1).thenReturn(badCols);
		when(Matlib.class, "createMatrix").thenReturn(badCols);
		testObj.train();
	}

	@Test
	public void testSaveScores() throws Exception
	{
		final NolPcaModel testObj =  createTestObj();
		final BufferedWriter Source = mock(BufferedWriter.class);
		mockStatic(Matlib.class);
		mockStatic(Stats.class);

		final Matrix v = mock(Matrix.class);
		when(v.get1(Matchers.anyInt(), Matchers.anyInt())).thenReturn(3.0, 10.0);
		when(v.get1(Matchers.anyInt())).thenReturn(4.0);
		when(Matlib.class, "createMatrix").thenReturn(v);
		when(v.get(Matchers.anyInt(), Matchers.anyInt())).thenReturn(10.0);
		Whitebox.setInternalState(testObj, "score", v);
		when(v.getRows()).thenReturn(1001);
		when(v.get(Matchers.anyInt())).thenReturn(25.0);
		testObj.saveScores(Source);

		Mockito.verify(Source).write("11; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source).write("5; Number of factors");
		Mockito.verify(Source, times(4004)).write("10.0,");
		Mockito.verify(Source, times(1001)).write("25.0;");
		Mockito.verify(Source, times(2005)).newLine();

		verifyStatic(times(3));
		Matlib.clear(Matchers.any(Matrix.class));

		when(v.getRows()).thenReturn(0);
		testObj.saveScores(Source);	// to cover the edge case of row == 0
		Mockito.verify(Source, times(2008)).newLine();
		Mockito.verify(Source, times(2)).write("11; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source, times(2)).write("5; Number of factors");
		Mockito.verify(Source, times(4004)).write("10.0,");
		Mockito.verify(Source, times(1001)).write("25.0;");
		verifyStatic(times(5));
		Matlib.clear(Matchers.any(Matrix.class));


		when(v.getRows()).thenReturn(90);
		testObj.saveScores(Source);	// to cover the edge case of row > 0
		Mockito.verify(Source, times(2191)).newLine();
		Mockito.verify(Source, times(3)).write("11; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source, times(3)).write("5; Number of factors");
		Mockito.verify(Source, times(4364)).write("10.0,");
		Mockito.verify(Source, times(1091)).write("25.0;");
	}

	/**
	 * Method to test saveScores when for various retainedFactorNumber values for 0, 1 values.
	 * >1 scenario will be tested through testSaveScores()
	 * @throws Exception
	 */
	@Test
	public void testSaveScoresForRetainedFactorNumberValues() throws Exception
	{
		final NolPcaModel testObj =  createTestObj();
		final BufferedWriter Source = mock(BufferedWriter.class);
		mockStatic(Matlib.class);
		mockStatic(Stats.class);

		final Matrix v = mock(Matrix.class);
		when(v.get1(Matchers.anyInt(), Matchers.anyInt())).thenReturn(3.0, 10.0);
		when(v.get1(Matchers.anyInt())).thenReturn(4.0);
		when(Matlib.class, "createMatrix").thenReturn(v);
		when(v.get(Matchers.anyInt(), Matchers.anyInt())).thenReturn(10.0);
		Whitebox.setInternalState(testObj, "score", v);
		when(v.getRows()).thenReturn(1001);
		when(v.get(Matchers.anyInt())).thenReturn(25.0);
		when(v.get(Matchers.anyInt(), Matchers.anyInt())).thenReturn(10.0);
		Whitebox.setInternalState(testObj, "retainedFactorNumber", 1);
		testObj.saveScores(Source);

		Mockito.verify(Source).write("11; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source).write("1; Number of factors");
		Mockito.verify(Source).write("1001; Number of samples");
		Mockito.verify(Source, times(1001)).write("10.0;");
		Mockito.verify(Source, times(1001)).write("25.0;");
		Mockito.verify(Source, times(2005)).newLine();
		verifyStatic(times(3));
		Matlib.clear(Matchers.any(Matrix.class));

		Whitebox.setInternalState(testObj, "retainedFactorNumber", 0);	// tests the edge case when retainedFactorNumber = 0
		when(v.getRows()).thenReturn(90);
		testObj.saveScores(Source);
		Mockito.verify(Source, times(2)).write("11; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source, times(1)).write("1; Number of factors");
		Mockito.verify(Source, times(1)).write("90; Number of samples");
		Mockito.verify(Source, times(1091)).write("25.0;");
		Mockito.verify(Source, times(2188)).newLine();
		verifyStatic(times(5));
		Matlib.clear(Matchers.any(Matrix.class));
	}

	/**
	 * Method to test saveParameters
	 * @throws Exception
	 */
	@Test
	public void testSaveParameters() throws Exception
	{
		final NolPcaModel testObj =  createTestObj();
		final BufferedWriter Source = mock(BufferedWriter.class);
		mockStatic(Matlib.class);
		mockStatic(Stats.class);
		final Matrix v = mock(Matrix.class);
		Whitebox.setInternalState(testObj, "P", v);
		when(v.get1(Matchers.anyInt(), Matchers.anyInt())).thenReturn(3.0, 10.0);
		Whitebox.setInternalState(testObj, "Xstd", v);
		when(v.get1(Matchers.anyInt())).thenReturn(4.0);
		Whitebox.setInternalState(testObj, "Pclim", v);
		Whitebox.setInternalState(testObj, "ssq", v);
		when(Matlib.class, "createMatrix").thenReturn(v);
		Whitebox.setInternalState(testObj, "Xmean", v);
		Whitebox.setInternalState(testObj, "Variants", v);

		when(v.getCols()).thenReturn(3);
		when(v.getRows()).thenReturn(1001);
		when(v.get(Matchers.eq(0), Matchers.anyInt())).thenReturn(10.0);
		when(v.get(Matchers.anyInt())).thenReturn(26.0);

		testObj.saveParameters(Source);
		testObj.setParametersVector(new Vector<>());

		Mockito.verify(Source).write("10; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source).write("3; Number of variables");
		Mockito.verify(Source).write("5; Number of factors");
		Mockito.verify(Source, times(10)).write("10.0,");
		Mockito.verify(Source).write("10.0; Means");
		Mockito.verify(Source).write("10.0; Stds");
		Mockito.verify(Source).write("10.0; Explained variants");
		Mockito.verify(Source, times(3)).write("0.0; Weight");
		Mockito.verify(Source, times(4)).write("26.0,");
		Mockito.verify(Source).write("26.0; PC Limits");
		Mockito.verify(Source).write("26.0; EigenValues");
		Mockito.verify(Source).write("0.0; Q value");
		Mockito.verify(Source).write("0.0; tsq value");

		Mockito.verify(Source, times(14)).newLine();
		assertEquals(v, testObj.getScoreLimits());
		assertEquals(v, testObj.getEigenvalues());

		when(v.getCols()).thenReturn(1);	// tests the scenario when Xmean.getCols() = 1;
		testObj.saveParameters(Source);

		Mockito.verify(Source, times(2)).write("10; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source).write("1; Number of variables");
		Mockito.verify(Source, times(2)).write("5; Number of factors");
		Mockito.verify(Source, times(14)).write("10.0,");
		Mockito.verify(Source, times(2)).write("10.0; Means");
		Mockito.verify(Source, times(2)).write("10.0; Stds");
		Mockito.verify(Source, times(2)).write("10.0; Explained variants");
		Mockito.verify(Source, times(4)).write("0.0; Weight");
		Mockito.verify(Source, times(4)).write("26.0,");
		Mockito.verify(Source, times(2)).write("26.0; PC Limits");
		Mockito.verify(Source, times(2)).write("26.0; EigenValues");
		Mockito.verify(Source, times(2)).write("0.0; Q value");
		Mockito.verify(Source, times(2)).write("0.0; tsq value");
		Mockito.verify(Source, times(26)).newLine();

		when(v.getCols()).thenReturn(0);	// tests the scenario when Xmean.getCols() = 1;
		testObj.saveParameters(Source);

		Mockito.verify(Source, times(3)).write("10; Version of this file for PCA save/restore protocol");
		Mockito.verify(Source).write("0; Number of variables");
		Mockito.verify(Source, times(3)).write("5; Number of factors");
		Mockito.verify(Source, times(3)).write("0.0; Q value");
		Mockito.verify(Source, times(3)).write("0.0; tsq value");
		Mockito.verify(Source, times(37)).newLine();
	}

	/**
	 * Method to test getParametersVector()
	 * @return
	 * @throws Exception
	 */
	@Test
	public void testGetParametersVector() throws Exception
	{
		final NolPcaModel testObj =  createTestObj();
		mockStatic(Matlib.class);
		final Matrix v = mock(Matrix.class);
		Whitebox.setInternalState(testObj, "P", v);
		when(v.get(Matchers.anyInt(), Matchers.anyInt())).thenReturn(3.0);
		when(v.getCols()).thenReturn(2);
		Whitebox.setInternalState(testObj, "Xmean", v);

		final double[] pp = {10.0, 11.0, 12.0};
		when(Matlib.class, "create1DArray", Matchers.any(Matrix.class)).thenReturn(pp);
		Vector paramVector = testObj.getParametersVector();
		assertEquals(12, paramVector.size());
		assertEquals(v, testObj.getLoadings());
		assertEquals(10, ((Integer)paramVector.get(0)).intValue());
		assertEquals(2, ((Integer)paramVector.get(1)).intValue());
		assertEquals(5, ((Integer)paramVector.get(2)).intValue());

		//testing double array objects from index 3 to 5
		final double[] expectedVals = {10.0, 11.0, 12.0};
		for(int i = 3; i < 6; i++)
		{
			final double[] returnVal = (double[])paramVector.get(i);
			for(int j = 0; j < returnVal.length; j++)
				assertEquals(expectedVals[j], returnVal[j], 0);
		}

		//testing double array objects from index 6 to 7
		final double[] testedVals = {3.0, 3.0, 3.0, 3.0, 3.0};
		for(int i = 6; i < 8; i++)
		{
			final double[] returnVal = (double[])paramVector.get(6);
			for(int j=0; j < returnVal.length; j++)
				assertEquals(testedVals[j], testedVals[j], 0);
		}

		//testing double array objects from index 8 to 9
		for(int i = 8; i < 10; i++)
		{
			final double[] returnVal = (double[])paramVector.get(i);
			for(int j = 0; j < returnVal.length; j++)
				assertEquals(expectedVals[j], returnVal[j], 0);
		}

		when(v.getCols()).thenReturn(0);
		paramVector = testObj.getParametersVector();// tests when Xmean.getCols() return zero.
		assertEquals(10, paramVector.size());

		for(int i=3; i<8; i++)
		{
			final double[] returnVal = (double[])paramVector.get(i);
			for(int j=0; j<returnVal.length; j++)
				assertEquals(expectedVals[j], returnVal[j], 0);
		}
	}

	/**
	 * Method to test getDataVector()
	 * @throws Exception
	 */
	@Test
	public void testGetDataVector() throws Exception
	{
		final NolPcaModel testObj =  createTestObj();
		mockStatic(Matlib.class);
		mockStatic(Stats.class);
		final Matrix v = mock(Matrix.class);
		when(v.get1(Matchers.anyInt(), Matchers.anyInt())).thenReturn(3.0, 10.0);
		when(v.get1(Matchers.anyInt())).thenReturn(4.0);
		when(Matlib.class, "createMatrix").thenReturn(v);

		Whitebox.setInternalState(testObj, "score", v);
		Whitebox.setInternalState(testObj, "Res", v);
		when(v.getRows()).thenReturn(1001);
		when(v.getCols()).thenReturn(5);

		Vector<Integer> returnVal = testObj.getDataVector();
		assertEquals(v, testObj.getSPEStatistics());
		assertEquals(2005, returnVal.size());
		assertEquals(v, testObj.getScore());

		when(v.getRows()).thenReturn(91);	//Tests when score.getRows()< 1000 scenario
		returnVal = testObj.getDataVector();
		assertEquals(185, returnVal.size());
		assertEquals(new Integer(11), returnVal.get(0));
		assertEquals(new Integer(5), returnVal.get(1));
		assertEquals(new Integer(91), returnVal.get(2));
	}
}