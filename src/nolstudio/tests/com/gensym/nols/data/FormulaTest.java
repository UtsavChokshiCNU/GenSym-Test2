package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import java.io.IOException;
import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;
import com.gensym.nols.data.function.FunctionInterface;

/**
 * Unit test class to test various formula evaluations for the given set of input values
 */
public class FormulaTest {

	private Formula formula;
	private Vector<Object> inputVarNames,inputValues,resultValues;
	private InnerFormula innerFormula;
	private final long[] longArray = {1000L, 2000L, 3000L, 4000L};
	private Vector<String[]> properties;
	private static final String[] PROP_ARRAY = {"Test","1.0"};

	/**
	 * Initialize test variables
	 */
	@Before
	public void initFormula(){
		formula=new Formula();
		innerFormula = new InnerFormula();
		inputVarNames = new Vector<Object>();
		inputValues = new Vector<Object>();
		resultValues = new Vector<Object>();
		properties = new Vector<String[]>();
		innerFormula.inputs = inputValues;
		innerFormula.inputs = inputValues;
		innerFormula.name = "abs";

		inputVarNames.add("test");
		inputVarNames.add(innerFormula);
		resultValues.add(new double[5]);
		properties.add(PROP_ARRAY);

		formula.inputs = inputVarNames;
	}

	/**
	 * Test method to test evaluation of abs operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertAbs() throws MathException,IOException
	{
		final double minVal = Double.MIN_VALUE * -1;
		final double maxVal = Double.MAX_VALUE * -1;

		final double[] inputArray = {minVal, maxVal, -1100, 900, Double.MIN_VALUE, Double.MAX_VALUE, 0, -0};
		final double[] outputArray = new double[inputArray.length];

		inputValues.clear();
		inputValues.add(inputArray);
		resultValues.clear();
		resultValues.add(outputArray);

		formula.name = "abs";
		final FunctionInterface result=formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "Abs");

		assertEquals(outputArray[0], Double.MIN_VALUE, 0);
		assertEquals(outputArray[1], Double.MAX_VALUE, 0);
		assertEquals(outputArray[2], 1100, 0);
		assertEquals(outputArray[3], 900, 0);
		assertEquals(outputArray[4], Double.MIN_VALUE, 0);
		assertEquals(outputArray[5], Double.MAX_VALUE, 0);
		assertEquals(outputArray[6], 0, 0);
		assertEquals(outputArray[7], 0, 0);
	}

	/**
	 * Test method to test evaluation of divide operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertDivide() throws MathException,IOException{
		formula.name = "divide";

		final double[] in1 = {2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 0, 100.0};
		final double[] in2 = {200.0, 30.0, 4.0, 500.0, 0, 9000.0, -0};
		final double[] outputVals = new double[in1.length];

		inputValues.clear();
		inputValues.add(in1);
		inputValues.add(in2);

		resultValues.clear();
		resultValues.add(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(outputVals[0], 10, 0);
		assertEquals(outputVals[1], 100.0, 0);
		assertEquals(outputVals[2], 1000.0, 0);
		assertEquals(outputVals[3], 10.0, 0);
		assertEquals(outputVals[4], Double.POSITIVE_INFINITY, 0);
		assertEquals(outputVals[5], 0.0, 0);
		assertEquals(outputVals[6], Double.POSITIVE_INFINITY, 0);
	}

	/**
	 * Test method to test evaluation of exponent operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertExp() throws MathException,IOException{
		formula.name = "exp";

		final double[] inValues = {1.0, 2.0, 4.0, 9.0, 0.5, 0, -1};
		final double[] outputVals = new double[inValues.length];
		inputValues.clear();
		inputValues.add(inValues);

		resultValues.clear();
		resultValues.add(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(Math.exp(1.0), outputVals[0], 0);
		assertEquals(Math.exp(2.0), outputVals[1], 0);
		assertEquals(Math.exp(4.0), outputVals[2], 0);
		assertEquals(Math.exp(9.0), outputVals[3], 0);

		assertEquals(Math.exp(0.5), outputVals[4], 0);
		assertEquals(Math.exp(0), outputVals[5], 0);
		assertEquals(Math.exp(-1), outputVals[6], 0);
	}

	/**
	 * Test method to test evaluation of log operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertLog() throws MathException,IOException{
		formula.name = "log";
		final double[] inValues = {1.0, 2.0, 4.0, 9.0, 0.0, Double.MIN_VALUE, Double.MAX_VALUE};
		final double[] outputVals = new double[inValues.length];

		inputValues.clear();
		inputValues.addElement(inValues);
		resultValues.clear();
		resultValues.addElement(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(),"Log");
		assertEquals(Math.log(1.0), outputVals[0], 0);
		assertEquals(Math.log(2.0), outputVals[1], 0);
		assertEquals(Math.log(4.0), outputVals[2], 0);
		assertEquals(Math.log(9.0), outputVals[3], 0);
		assertEquals(Math.log(0.0), outputVals[4], 0);
		assertEquals(Math.log(Double.MIN_VALUE), outputVals[5], 0);
		assertEquals(Math.log(Double.MAX_VALUE), outputVals[6], 0);
	}

	/**
	 * Test method to test evaluation of log base 10 operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertLog10() throws MathException,IOException{

		final double factor = 1.0/Math.log(10.0);
		final double[] inValues = {1.0, 2.0, 4.0, 9.0, 0.0, Double.MIN_VALUE,Double.MAX_VALUE};
		final double[] outputVals = new double[inValues.length];
		formula.name = "log10";

		inputValues.clear();
		inputValues.add(inValues);
		resultValues.clear();
		resultValues.add(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);

		assertEquals(result.getName(),"Log10");
		assertEquals(factor * Math.log(1.0), outputVals[0], 0);
		assertEquals(factor * Math.log(2.0), outputVals[1], 0);
		assertEquals(factor * Math.log(4.0), outputVals[2], 0);
		assertEquals(factor * Math.log(9.0), outputVals[3], 0);
		assertEquals(factor * Math.log(0.0), outputVals[4], 0);
		assertEquals(factor * Math.log(Double.MIN_VALUE), outputVals[5], 0);
		assertEquals(factor * Math.log(Double.MAX_VALUE), outputVals[6], 0);
	}

	/**
	 * Test method to test evaluation of multiply operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertMultiply() throws MathException,IOException{
		formula.name = "multiply";
		final FunctionInterface result = formula.convert_1_2().function;
		final double[] inValues = {10.0, 20.0, 40.0, 90.0, 120.0 };
		final double[] inValues1 = {1.0, 3.0, 5.0, 0.0, -1 };
		inputValues.clear();
		inputValues.addElement(inValues);
		inputValues.addElement(inValues1);

		resultValues.clear();
		final double[] outputVals = new double[inValues.length];
		resultValues.addElement(outputVals);

		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "Multiply");
		assertEquals(10.0, outputVals[0], 0);
		assertEquals(60.0, outputVals[1], 0);
		assertEquals(200.0, outputVals[2], 0);
		assertEquals(0.0, outputVals[3], 0);
		assertEquals(-120.0, outputVals[4], 0);
	}

	/**
	 * Method to test evaluation of random operation for the given formula name.
	 * The functionality is tested in RandNormalTest.java
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertRandom() throws MathException,IOException{
		formula.name = "random";
		final FunctionInterface result = formula.convert_1_2().function;
		assertEquals(result.getName(), "RandNormal");
	}

	/**
	 * Test method to test evaluation of signs (positive/negative
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertSign() throws MathException,IOException{
		formula.name = "sign";
		final double[] inValues = {10.0, 0.0, -40.0, Double.NaN};
		inputValues.clear();
		inputValues.add(inValues);

		final double[] outputVals = new double[inValues.length];
		resultValues.clear();
		resultValues.addElement(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "Sign");
		assertEquals(1.0, outputVals[0], 0);
		assertEquals(0.0, outputVals[1], 0);
		assertEquals(-1.0, outputVals[2], 0);
		assertEquals(Double.NaN, outputVals[3], 0);
	}

	/**
	 * Test method to test evaluation of square root operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test(expected = MathException.class)
	public void testConvertSqrt() throws MathException,IOException{

		formula.name = "sqrt";
		final FunctionInterface result = formula.convert_1_2().function;
		final double[] inValues = {9.0, 0.0, 16.0, 26.0, 0.0, -25.0};
		inputValues.clear();
		inputValues.add(inValues);

		final double[] outputVals = new double[inValues.length];
		resultValues.clear();
		resultValues.add(outputVals);

		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "Sqrt");
		assertEquals(Math.sqrt(9.0), outputVals[0], 0);
		assertEquals(Math.sqrt(0.0), outputVals[1], 0);
		assertEquals(Math.sqrt(16.0), outputVals[2], 0);
		assertEquals(Math.sqrt(26.0), outputVals[3], 0);
		assertEquals(Math.sqrt(0.0), outputVals[4], 0);
	}

	/**
	 * Test method to test evaluation of addition operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertSum() throws MathException,IOException{
		formula.name = "sum";
		final FunctionInterface result = formula.convert_1_2().function;

		final double[] inputs = {10.0, 20.0, 40.0, 90.0, -100.0, Double.MAX_VALUE, -200};
		final double[] in2 = {0.0, 120.0, 20.0, -90.0, -100.0, 10000.0, Double.MIN_VALUE};
		inputValues.clear();
		inputValues.addElement(inputs);
		inputValues.addElement(in2);

		resultValues.clear();
		final double[] outputVals = new double[inputs.length];
		resultValues.add(outputVals);

		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "Sum");
		assertEquals(10.0, outputVals[0], 0);
		assertEquals(140.0, outputVals[1], 0);
		assertEquals(60.0, outputVals[2], 0);
		assertEquals(0.0, outputVals[3], 0);
		assertEquals(-200.0, outputVals[4], 0);
		assertEquals(Double.MAX_VALUE, outputVals[5], 0);
		assertEquals(Double.MIN_VALUE-200, outputVals[6], 0);
	}

	/**
	 * Test method to test evaluation of subtraction operation
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertSubtract() throws MathException,IOException{
		formula.name = "subtract";
		final FunctionInterface result = formula.convert_1_2().function;

		final double[] in1 = {10.0, 20.0, 40.0, 90.0, Double.NaN, 67};
		final double[] in2 = {6.0, 120.0, 20.0, -90.0, 45, Double.NaN};
		inputValues.clear();
		inputValues.addElement(in1);
		inputValues.addElement(in2);

		resultValues.clear();
		final double[] outputVals = new double[in1.length];
		resultValues.add(outputVals);
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "Subtract");
		assertEquals(4.0, outputVals[0], 0);
		assertEquals(-100.0, outputVals[1], 0);
		assertEquals(20.0, outputVals[2], 0);
		assertEquals(180.0, outputVals[3], 0);
		assertEquals(Double.NaN, outputVals[4], 0);
		assertEquals(Double.NaN, outputVals[5], 0);
	}

	/**
	 * Test method to test evaluation of removal of high values from the input
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertCutHighValue() throws MathException,IOException{
		formula.name = "CUT_HIGH_VALUE";
		formula.properties = properties;

		final double minVal = Double.MIN_VALUE;
		final double maxVal = Double.MAX_VALUE;
		final double[] inputVals = {minVal, maxVal, -1100, 900};
		final double[] thresholds = {maxVal, minVal, -1900, 1900};
		final double[] outputVals = new double[inputVals.length];

		inputValues.clear();
		inputValues.add(inputVals);
		inputValues.add(thresholds);

		resultValues.clear();
		resultValues.add(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "CutHighValue");
		assertEquals(outputVals[0], Double.MIN_VALUE, 0);
		assertEquals(outputVals[1], Double.NaN, 0);
		assertEquals(outputVals[2], Double.NaN, 0);
		assertEquals(outputVals[3], 900, 0);
	}

	/**
	 * Test method to test evaluation of removal of low values from the input
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertCutLowValue() throws MathException,IOException{
		formula.name="CUT_LOW_VALUE";
		formula.properties=properties;

		final double minVal = Double.MIN_VALUE;
		final double maxVal = Double.MAX_VALUE;

		final double[] inputArray = {minVal, maxVal, -1100, 900};
		final double[] thresholds = {maxVal, minVal, -1900, 1900};
		final double[] outputArray = new double[inputArray.length];

		inputValues.clear();
		inputValues.add(inputArray);
		inputValues.add(thresholds);

		resultValues.clear();
		resultValues.add(outputArray);
		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(outputArray[0], Double.NaN, 0);
		assertEquals(outputArray[1], Double.MAX_VALUE, 0);
		assertEquals(outputArray[2], -1100, 0);
		assertEquals(outputArray[3], Double.NaN, 0);
	}

	/**
	 * Test method to test evaluation of moving average hours
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testMovingAveHours() throws MathException,IOException{
		properties.clear();
		final String[] propertiesArray = {"", "H"};
		final String[] propertiesValueArray = {"", "5"};
		properties.add(propertiesArray);
		properties.add(propertiesValueArray);
		formula.name = "MOVING_AVE";
		formula.properties = properties;

		final double[] inValues = {10.0, 20.0, 40.0, 90.0};
		final double[] intervals = {1.0, 2.0, 4.0, 9.0};
		inputValues.clear();
		inputValues.add(inValues);
		inputValues.add(intervals);

		resultValues.clear();
		final double[] outputVals = new double[5];
		resultValues.add(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "MovingAverage");
		assertEquals(10.0, outputVals[0], 0);
		assertEquals(15.0, outputVals[1], 0);
		assertEquals(23.333333333333332, outputVals[2], 0);
		assertEquals(40.0, outputVals[3], 0);
		assertEquals(0.0, outputVals[4], 0);
	}

	/**
	 * Test method to test evaluation of moving average minutes
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testMovingAveMinutes() throws MathException,IOException{
		properties.clear();
		final String[] propertiesArray = {"", "M"};
		final String[] propertiesValueArray = {"", "30"};
		properties.add(propertiesArray);
		properties.add(propertiesValueArray);
		formula.name = "MOVING_AVE";
		formula.properties = properties;

		final double[] inValues = {10.0, 20.0, 40.0, 90.0};
		final double[] intervals = {1.0, 2.0, 4.0, 9.0};
		inputValues.clear();
		inputValues.add(inValues);
		inputValues.add(intervals);

		final double[] outputVals = new double[intervals.length];
		resultValues.clear();
		resultValues.add(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "MovingAverage");
		assertEquals(10.0, outputVals[0], 0);
		assertEquals(15.0, outputVals[1], 0);
		assertEquals(23.333333333333332, outputVals[2], 0);
		assertEquals(40.0, outputVals[3], 0);
	}

	/**
	 * Test method to test evaluation of moving average seconds
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testMovingAveSeconds() throws MathException,IOException{
		properties.clear();
		final String[] propertiesArray = {"", "S"};
		final String[] propertiesValueArray = {"", "600"};
		properties.add(propertiesArray);
		properties.add(propertiesValueArray);
		formula.name = "MOVING_AVE";
		formula.properties = properties;

		final double[] inValues = {10.0, 20.0, 40.0, 90.0};
		final double[] intervals = {1.0, 2.0, 4.0, 9.0};
		inputValues.clear();
		inputValues.add(inValues);
		inputValues.add(intervals);

		final double[] outputArray = new double[inValues.length];
		resultValues.clear();
		resultValues.add(outputArray);
		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "MovingAverage");
		assertEquals(10.0, outputArray[0], 0);
		assertEquals(15.0, outputArray[1], 0);
		assertEquals(23.333333333333332, outputArray[2], 0);
		assertEquals(40.0, outputArray[3], 0);
	}

	/**
	 * Test method to test evaluation of replacing high values from the given input paramters
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertReplaceHighValue() throws MathException,IOException
	{
		properties.add(PROP_ARRAY);
		formula.name = "REPLACE_HIGH_VALUE";
		formula.properties = properties;

		final double[] inVals = {420.0, 23.0, 9.0, 908.0, 20.0, 5.0, 0, -45.0, Double.MIN_VALUE, Double.MAX_VALUE};
		final double[] threshholds = {20.0, 3.0, 10.0, 8.0, 90.0, 53.0, 5.0, 45.0, 0, Double.MIN_VALUE};
		final double[] replacements = {3218.0, 3986.0, 9106.0, 8731.0, 9860.0, 1513.0, 8975.0, 632.0, Double.MAX_VALUE, 10.0};

		inputValues.clear();
		inputValues.addElement(inVals);
		inputValues.addElement(threshholds);
		inputValues.addElement(replacements);

		final double[] outputVals = new double[inVals.length];
		resultValues.clear();
		resultValues.addElement(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "ReplaceHighValue");
		assertEquals(3218.0, outputVals[0], 0);
		assertEquals(3986.0, outputVals[1], 0);
		assertEquals(9.0, outputVals[2], 0);
		assertEquals(8731.0, outputVals[3], 0);
		assertEquals(20.0, outputVals[4], 0);
		assertEquals(5.0, outputVals[5], 0);

		assertEquals(0.0, outputVals[6], 0);
		assertEquals(-45.0, outputVals[7], 0);
		assertEquals(Double.MAX_VALUE, outputVals[8], 0);
		assertEquals(10.0, outputVals[9], 0);
	}

	/**
	 * Test method to test evaluation of replacing low values from the given input paramters
	 * @throws MathException
	 * @throws IOException
	 */
	@Test
	public void testConvertReplaceLowValue() throws MathException,IOException{
		properties.add(PROP_ARRAY);
		formula.name = "REPLACE_LOW_VALUE";
		formula.properties = properties;

		final double[] inVals = {420.0, 23.0, 9.0, 908.0, 20.0, 5.0, 0, -45.0, Double.MIN_VALUE, Double.MAX_VALUE};
		final double[] threshholds = {20.0, 3.0, 10.0, 8.0, 90.0, 53.0, 5.0, 45.0, 0, Double.MIN_VALUE};
		final double[] replacements = {3218.0, 3986.0, 9106.0, 8731.0, 9860.0, 1513.0, 8975.0, 632.0, Double.MAX_VALUE, 10.0};
		inputValues.clear();
		inputValues.addElement(inVals);
		inputValues.addElement(threshholds);
		inputValues.addElement(replacements);

		resultValues.clear();
		final double[] outputVals = new double[inVals.length];
		resultValues.add(outputVals);

		final FunctionInterface result = formula.convert_1_2().function;
		result.evaluate(longArray, inputValues, resultValues);
		assertEquals(result.getName(), "ReplaceLowValue");
		assertEquals(420.0, outputVals[0], 0);
		assertEquals(23.0, outputVals[1], 0);
		assertEquals(9106.0, outputVals[2], 0);
		assertEquals(908.0, outputVals[3], 0);
		assertEquals(9860.0, outputVals[4], 0);
		assertEquals(1513.0, outputVals[5], 0);

		assertEquals(8975.0, outputVals[6], 0);
		assertEquals(632.0, outputVals[7], 0);
		assertEquals(Double.MIN_VALUE, outputVals[8], 0);
		assertEquals(Double.MAX_VALUE, outputVals[9], 0);
	}
}
