package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.times;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.mockStatic;
import static org.powermock.api.mockito.PowerMockito.verifyStatic;
import static org.powermock.api.mockito.PowerMockito.when;

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
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.matrix.TimeFunctions;
import com.gensym.nols.data.function.FunctionInterface;
import com.gensym.nols.data.function.Subtract;
import com.gensym.nols.data.function.Sum;

@RunWith(PowerMockRunner.class)
@PrepareForTest({Matlib.class, Matrix.class, DataSeries.class, TimeFunctions.class})
@SuppressStaticInitializationFor({"com.gensym.math.matrix.Matrix", "com.gensym.math.matrix.Matlib"})
public class Formula2Test
{

	/**
	 * Method to test empty parameter constructor.
	 */
	@Test
	public void testEmptyParamConstructor()
	{
		final Formula2 testObj = new Formula2();
		assertEquals(0, testObj.getInputs().size());
		assertEquals(0, testObj.getOutputs().size());
		assertNull(testObj.getFunction());
	}

	/**
	 * Method to test empty parameter constructor.
	 */
	@Test
	public void testFormulaParamConstructor()
	{
		final Formula2 formula = new Formula2();
		final Vector inputs = new Vector<>();
		final InnerFormula2 innerFormula2 = new InnerFormula2();
		inputs.addElement(innerFormula2);
		inputs.addElement(new Integer(-100));
		inputs.addElement(new Integer(500));

		final Vector outputs = new Vector<>();
		outputs.addElement(new Integer(200));
		formula.setFunction(new Sum());

		formula.setInputs(inputs);
		formula.setOutputs(outputs);
		final Formula2 testObj = new Formula2(formula);
		assertEquals(3, testObj.getInputs().size());
		assertEquals(-100, testObj.getInputs().get(1));
		assertEquals(500, testObj.getInputs().get(2));
		assertEquals("()", testObj.getInputs().get(0).toString());
	}

	/**
	 * Method to test constructor for input & FunctionInterface parameter values
	 */
	@Test
	public void testConstructorForInputParam()
	{
		final FunctionInterface func = new Sum();
		final Vector ins = new Vector<>();
		final Formula2 testObj = new Formula2(func, ins);
		assertEquals(ins, testObj.getInputs());
		assertEquals(func, testObj.getFunction());
	}

	/**
	 * Method to test constructor for FunctionInterface parameter value
	 */
	@Test
	public void testConstructorForFIParam()
	{
		final FunctionInterface func = new Sum();
		final Formula2 testObj = new Formula2(func);
		assertEquals(func, testObj.getFunction());
	}

	/**
	 * Method to test setFunction()
	 */
	@Test
	public void testSetFunction()
	{
		final Formula2 testObj = new Formula2();
		final Vector inputs = new Vector<>();
		inputs.addElement(new Integer(-100));
		inputs.addElement(new Integer(500));

		final Vector outputs = new Vector<>();
		outputs.addElement(new Integer(200));
		final FunctionInterface sumObj = new Sum();

		final EnsembleModel net = mock(EnsembleModel.class);
		final String name = "NolModel2";

		final Vector outs = new Vector<>();
		outs.addElement(10.0);
		outs.addElement(20.0);

		final Vector ins = new Vector<>();
		ins.addElement(10.0);
		ins.addElement(20.0);

		final Vector oDelays = new Vector<>();
		final Vector iDelays = new Vector<>();
		final Preprocessor prep = mock(Preprocessor.class);
		final NolModel2 nolModel = new NolModel2(net, name, outs, ins, oDelays, iDelays, prep);

		testObj.setFunction(nolModel);
		assertEquals(2, testObj.getInputs().size());
		assertEquals(2, testObj.getOutputs().size());
		assertEquals(10.0, testObj.getInput(0));
		assertEquals(20.0, testObj.getInput(1));
		assertEquals(10.0, testObj.getOutputs().get(0));
		assertEquals(20.0, testObj.getOutputs().get(1));
	}

	/**
	 * Method to test setFunction()
	 * @throws InstantiationException
	 * @throws IllegalAccessException
	 * @throws ClassNotFoundException
	 */
	@Test
	public void testSetFunctionForStringInput() throws ClassNotFoundException, IllegalAccessException, InstantiationException
	{
		final Formula2 testObj = new Formula2();
		testObj.setFunction("Sum");
		assertTrue(testObj.getFunction() instanceof Sum);
		assertEquals("Sum", testObj.getName());

		testObj.clearFunction();
		assertNull(testObj.getFunction());
		assertEquals("", testObj.getName());
	}

	/**
	 * Method to test hasInput()
	 */
	@Test
	public void testHasInput()
	{
		final String sumInput = "SumInput";
		final Formula2 formula = new Formula2();
		final Vector inputs = new Vector<>();

		inputs.addElement(new Integer(-100));
		inputs.addElement(new Integer(500));
		inputs.addElement(new Formula2());

		final Vector outputs = new Vector<>();
		outputs.addElement(new Integer(200));
		formula.setFunction(new Sum());
		formula.setInputs(inputs);
		formula.setOutputs(outputs);

		final Formula2 testObj = new Formula2(formula);
		assertFalse(testObj.hasInput("SumInput"));

		testObj.removeInput();
		testObj.addInput(sumInput);
		testObj.addInput(new Integer(-100));
		testObj.addInput(new Integer(500));

		assertTrue(testObj.hasInput(sumInput));
		assertFalse(testObj.hasInput("Sum"));
	}

	/**
	 * Method to test hasInput()
	 */
	@Test
	public void testHasOutput()
	{
		final String sumOutput = "SumOutput";
		final Vector inputs = new Vector<>();
		inputs.addElement(new Integer(-100));
		inputs.addElement(new Integer(500));

		final Vector outputs = new Vector<>();
		outputs.addElement(new Integer(200));

		final Formula2 testObj = new Formula2(new Sum(), inputs, outputs);
		assertFalse(testObj.hasOutput("TestOutput"));

		testObj.removeOutput();
		testObj.addOutput(sumOutput);
		assertTrue(testObj.hasOutput(sumOutput));
		assertEquals(1, testObj.getNumberOfOutputs());
		assertEquals(2, testObj.getNumberOfInputs());
	}

	/**
	 * Method to test getInputVars
	 */
	@Test
	public void testGetInputVars()
	{
		final Vector vars = new Vector<>();
		final Vector inputs = new Vector<>();
		inputs.addElement("Input1");
		inputs.addElement("Input2");
		inputs.addElement(new Formula2());

		final Formula2 testObj = new Formula2(new Sum(), inputs);
		testObj.getInputVars(vars);
		assertEquals(2, vars.size());
		assertTrue(testObj.hasVariable("Input2"));
		assertFalse(testObj.hasVariable("Input3"));
	}

	/**
	 * Method to test getInput
	 */
	@Test
	public void testGetInput()
	{
		final Vector indices = new Vector();
		indices.add(0);

		final Vector inputs = new Vector<>();
		final Formula2 inputTestObj = new Formula2();
		inputs.addElement(inputTestObj);

		final Formula2 testObj = new Formula2(new Sum(), inputs);
		assertEquals(inputTestObj, testObj.getInput(indices));
		assertEquals(testObj, testObj.getInput(indices, -2));
	}

	/**
	 * Method to test toString()
	 */
	@Test
	public void testToString()
	{
		final Vector inputs = new Vector();
		inputs.addElement("Input1");
		inputs.addElement("Input2");

		final Vector outputs = new Vector();
		outputs.addElement("Input1 Input2");

		final Formula2 testObj = new Formula2(new Sum(), inputs, outputs);
		assertEquals("{Input1 Input2}=Sum(Input1, Input2)", testObj.toString());
	}

	/**
	 * Method to test applyFormula
	 * @throws FormulaException
	 * @throws MathException
	 */
	@Test
	public void testApplyFormula() throws MathException, FormulaException
	{
		mockStatic(Matlib.class);
		final DataSeries ds1 = mock(DataSeries.class);
		when(ds1.getVarIndexByName(Matchers.anyString())).thenReturn(0);
		final double[] thisInput= {10.0, 11.0, 12.0};
		when(ds1.getVarArrayByName(Matchers.anyString())).thenReturn(thisInput);

		final DataSeries[] allData = {ds1, mock(DataSeries.class)};
		final Vector inputs = new Vector<>();
		inputs.addElement("InputText");
		inputs.addElement("InputText2");

		final Vector outputs = new Vector<>();
		outputs.addElement("OutputText");

		final Formula2 testObj = new Formula2(new Sum(), inputs, outputs);
		testObj.applyFormula(allData);
	}

	/**
	 * Method to test applyFormula()
	 * @throws FormulaException
	 * @throws MathException
	 */
	@Test
	public void testApplyFormulaForVectorInput() throws MathException, FormulaException
	{
		final Vector dataSeriesVector = new Vector();
		final DataSeries ds1 = mock(DataSeries.class);
		when(ds1.getVarIndexByName(Matchers.anyString())).thenReturn(0);
		final double[] thisInput= {10.0, 11.0, 12.0};
		when(ds1.getVarArrayByName(Matchers.anyString())).thenReturn(thisInput);

		final DataSeries ds2 = mock(DataSeries.class);
		dataSeriesVector.addElement(ds1);
		dataSeriesVector.addElement(ds2);

		final Vector inputs = new Vector<>();
		inputs.addElement("InputText");
		inputs.addElement("InputText2");

		final Vector outputs = new Vector<>();
		outputs.addElement("OutputText");

		final Formula2 testObj = new Formula2(new Sum(), inputs, outputs);
		testObj.applyFormula(dataSeriesVector);
		Mockito.verify(ds1).setColumnValues(Matchers.anyInt(), Matchers.any(double[].class));
	}

	/**
	 * Method to test getInputBufferLength()
	 */
	@Test
	public void testGetInputBufferLength()
	{
		final Vector inputs = new Vector<>();
		inputs.addElement("InputText");
		inputs.addElement("InputText2");

		final Vector outputs = new Vector<>();
		outputs.addElement("OutputText");

		final EnsembleModel net = mock(EnsembleModel.class);
		final String name = "NolModel2";

		final Vector outs = new Vector<>();
		outs.addElement(10.0);
		outs.addElement(20.0);

		final Vector ins = new Vector<>();
		ins.addElement(10.0);
		ins.addElement(20.0);

		final Vector oDelays = new Vector<>();
		final Vector iDelays = new Vector<>();
		iDelays.addElement(new long[]{10l,20l, 30l});
		final Preprocessor prep = mock(Preprocessor.class);
		final NolModel2 nolModel = new NolModel2(net, name, outs, ins, oDelays, iDelays, prep);

		Formula2 testObj = new Formula2(nolModel, inputs, outputs);
		assertEquals(30, testObj.getInputBufferLength());
		testObj = new Formula2(null, inputs, outputs);
		assertEquals(0L, testObj.getInputBufferLength());
	}

	/**
	 * Method to test applyFormula
	 * @throws Exception
	 */
	@Test(expected = FormulaException.class)
	public void testApplyFormulaForNolModel2Objects() throws Exception
	{
		final Vector inputs = new Vector<>();
		inputs.addElement("InputText");
		inputs.addElement("InputText2");

		final Vector outputs = new Vector<>();
		outputs.addElement("OutputText");

		final EnsembleModel net = mock(EnsembleModel.class);
		when(net.getNout()).thenReturn(3);
		final String name = "NolModel2";

		final Vector outs = new Vector<>();
		outs.addElement("Test1");

		final Vector ins = new Vector<>();
		ins.addElement("Input1");

		final Vector oDelays = new Vector<>();
		oDelays.addElement(new long[]{10l,20l, 30l});
		final Vector iDelays = new Vector<>();
		iDelays.addElement(new long[]{10l,20l, 30l});

		final Preprocessor prep = mock(Preprocessor.class);
		final NolModel2 nolModel = new NolModel2(net, name, outs, ins, oDelays, iDelays, prep);

		mockStatic(Matlib.class);
		final Matrix x = mock(Matrix.class);
		when(x.getRows()).thenReturn(2);
		when(Matlib.class, "createMatrix").thenReturn(x);
		when(Matlib.class, "createMatrix", Matchers.anyInt(), Matchers.anyInt()).thenReturn(x);
		when(Matlib.create2DArray(Matchers.any(Matrix.class))).thenReturn(new double[][]{{10.0, 11.0}, {12.0, 20.0}, {21.0, 22.0}});

		final DataSeries ds1 = mock(DataSeries.class);
		when(ds1.getRow()).thenReturn(3);
		when(ds1.getVarIndexByName(Matchers.anyString())).thenReturn(0);
		final double[] thisInput= {10.0, 11.0, 12.0};
		when(ds1.getVarArrayByName(Matchers.anyString())).thenReturn(thisInput);
		when(ds1.getHasTimeStamps()).thenReturn(true);
		when(ds1.getTimeStamps()).thenReturn(new long[]{20l,21l,22l});
		final DataSeries[] allData = {ds1, mock(DataSeries.class)};

		mockStatic(TimeFunctions.class);
		when(TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class))).thenReturn(new long[]{10l,11l,12l});

		final Formula2 testObj = new Formula2(nolModel, inputs, outputs);
		testObj.applyFormula(allData);
	}

	/**
	 * Method to test prepareInputs()
	 * @throws Exception
	 */
	@Test
	public void testPrepareInputs() throws Exception
	{
		mockStatic(Matlib.class);
		final Matrix x = mock(Matrix.class);
		when(x.getRows()).thenReturn(2);
		when(x.getCols()).thenReturn(2);
		when(x.get(Matchers.anyInt(), Matchers.anyInt())).thenReturn(21.0);

		when(Matlib.class, "createMatrix").thenReturn(x);
		when(Matlib.class, "createMatrix", Matchers.anyInt(), Matchers.anyInt()).thenReturn(x);

		final DataSeries timeSource = mock(DataSeries.class);
		when(timeSource.getHasTimeStamps()).thenReturn(true);
		when(timeSource.getTimeStamps()).thenReturn(new long[]{21l, 22l, 20l});
		final DataSeries[] allData = {timeSource, new DataSeries()};

		final EnsembleModel net = mock(EnsembleModel.class);
		when(net.getNout()).thenReturn(3);
		final String name = "NolModel2";

		final Vector outs = new Vector<>();
		outs.addElement("Test1");

		final Vector ins = new Vector<>();
		ins.addElement("Input1");

		final Vector oDelays = new Vector<>();
		oDelays.addElement(new long[]{10l,20l, 30l});
		final Vector iDelays = new Vector<>();
		iDelays.addElement(new long[]{10l,20l, 30l});

		final Preprocessor prep = mock(Preprocessor.class);
		final NolModel2 nolModel = new NolModel2(net, name, outs, ins, oDelays, iDelays, prep);

		final Vector inputs = new Vector<>();
		inputs.addElement("InputText");
		inputs.addElement("InputText2");

		final Vector outputs = new Vector<>();
		outputs.addElement("OutputText");

		mockStatic(TimeFunctions.class);
		when(TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class))).thenReturn(new long[]{10l,21l,12l});

		final Formula2 testObj = new Formula2(nolModel, inputs, outputs);
		Whitebox.invokeMethod(testObj, "prepareInputs", timeSource, allData);

		verifyStatic(times(2));
		Matlib.clear(Matchers.any(Matrix.class));
	}

	/**
	 * Method to test prepareInputs for double block
	 * @throws Exception
	 */
	@Test
	public void testprepareInputsForDoubleBlock() throws Exception
	{
		mockStatic(Matlib.class);
		final Matrix x = mock(Matrix.class);
		when(x.getRows()).thenReturn(2);
		when(x.getCols()).thenReturn(2);
		//when(x.get(Matchers.anyInt(), Matchers.anyInt())).thenReturn(21.0);

		when(Matlib.class, "createMatrix").thenReturn(x);
		when(Matlib.class, "createMatrix", Matchers.anyInt(), Matchers.anyInt()).thenReturn(x);

		final DataSeries timeSource = mock(DataSeries.class);
		final DataSeries[] allData = {timeSource, new DataSeries()};

		final Vector innerInputs = new Vector();
		innerInputs.addElement(10.0);
		innerInputs.addElement(11.0);

		final Vector innerOutputs = new Vector();
		innerOutputs.addElement(10.0);
		innerOutputs.addElement(11.0);

		final Vector inputs = new Vector<>();
		inputs.addElement(new Formula2(new Sum(), innerInputs, innerOutputs));

		final Vector outputs = new Vector<>();
		final Formula2 testObj = new Formula2(new Subtract(), inputs, outputs);

		final Vector ins = Whitebox.invokeMethod(testObj, "prepareInputs", timeSource, allData);
		assertEquals(1, ins.size());
	}

	/**
	 * Method to test findTimeSource()
	 * @throws Exception
	 */
	@Test(expected = FormulaException.class)
	public void testFindTimeSource() throws Exception
	{
		mockStatic(Matlib.class);
		final Matrix x = mock(Matrix.class);
		when(x.getRows()).thenReturn(2);
		when(x.getCols()).thenReturn(2);
		//when(x.get(Matchers.anyInt(), Matchers.anyInt())).thenReturn(21.0);

		when(Matlib.class, "createMatrix").thenReturn(x);
		when(Matlib.class, "createMatrix", Matchers.anyInt(), Matchers.anyInt()).thenReturn(x);

		final DataSeries timeSource = mock(DataSeries.class);
		when(timeSource.getHasTimeStamps()).thenReturn(true);
		when(timeSource.getVarIndexByName(Matchers.anyString())).thenReturn(-1);

		final DataSeries[] allData = new DataSeries[1];
		allData[0] = timeSource;

		final Vector innerInputs = new Vector();
		innerInputs.addElement("Input1");
		innerInputs.addElement("Input2");

		final Vector innerOutputs = new Vector();
		final Vector inputs = new Vector<>();
		inputs.addElement(new Formula2(new Sum(), innerInputs, innerOutputs));

		final Vector outputs = new Vector<>();
		final Formula2 testObj = new Formula2(new Subtract(), inputs, outputs);
		testObj.applyFormula(allData);
	}

	/**
	 * Method to test copyResultsToDataSeries()
	 * @throws Exception
	 */
	@Test(expected = FormulaException.class)
	public void testCopyResultsToDataSeries() throws Exception
	{
		mockStatic(Matlib.class);
		final Matrix x = mock(Matrix.class);
		when(x.getRows()).thenReturn(2);
		when(x.getCols()).thenReturn(2);

		when(Matlib.class, "createMatrix").thenReturn(x);
		when(Matlib.class, "createMatrix", Matchers.anyInt(), Matchers.anyInt()).thenReturn(x);

		final DataSeries timeSource = mock(DataSeries.class);
		when(timeSource.getVarIndexByName(Matchers.anyString())).thenReturn(-1);
		final DataSeries[] allData = {new DataSeries(), timeSource};

		final Vector inputs = new Vector<>();
		inputs.addElement("InputString1");

		final Vector outputs = new Vector<>();
		outputs.addElement("OutputString1");
		outputs.addElement("OutputString2");

		final Vector results = new Vector<>();
		results.addElement("Input1");
		results.addElement("Input2");
		results.addElement("Input3");

		final Formula2 testObj = new Formula2(new Sum(), inputs, outputs);
		Whitebox.invokeMethod(testObj, "copyResultsToDataSeries", timeSource, allData, results);
	}

	/**
	 * Method to test copyResultsToDataSeries()
	 * @throws Exception
	 */
	@Test(expected = FormulaException.class)
	public void testCopyResultsToDataSeriesForFormulaException() throws Exception
	{
		mockStatic(Matlib.class);
		final Matrix x = mock(Matrix.class);
		when(x.getRows()).thenReturn(2);
		when(x.getCols()).thenReturn(2);

		when(Matlib.class, "createMatrix").thenReturn(x);
		when(Matlib.class, "createMatrix", Matchers.anyInt(), Matchers.anyInt()).thenReturn(x);

		final DataSeries timeSource = mock(DataSeries.class);
		when(timeSource.getVarIndexByName(Matchers.anyString())).thenReturn(-1);
		final DataSeries[] allData = {new DataSeries(), timeSource};

		final Vector inputs = new Vector<>();
		inputs.addElement("InputString1");

		final Vector outputs = new Vector<>();
		outputs.addElement("OutputString1");
		outputs.addElement("OutputString2");

		final Vector results = new Vector<>();
		results.addElement("Input1");

		final Formula2 testObj = new Formula2(new Sum(), inputs, outputs);
		Whitebox.invokeMethod(testObj, "copyResultsToDataSeries", timeSource, allData, results);
	}
}