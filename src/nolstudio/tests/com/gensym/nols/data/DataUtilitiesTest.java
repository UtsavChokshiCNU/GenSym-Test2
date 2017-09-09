package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class DataUtilitiesTest
{
	/**
	 * Method to test String2Strings method
	 */
	@Test
	public void testString2Strings()
	{
		final String S = "Test String used to test string2Strings	method, "
				+ "This method splits the given string into multiple subStrings";
		final int nSting = 16;
		final String[] subStrings = new String[nSting];
		DataUtilities.string2Strings(S, nSting, subStrings);

		final String[] expSubStrings = {"Test", "String", "used", "to", "test","string2Strings", "method", "This",
				"method", "splits", "the", "given", "string", "into", "multiple", "subStrings"};
		for(int i = 0; i < subStrings.length; i++) {
			assertEquals(expSubStrings[i], subStrings[i]);
		}

		// this scenario tests empty string.
		String[] subStr = new String[1];
		DataUtilities.string2Strings("", 1, subStr);
		for(int i = 0; i < subStr.length; i++) {
			assertEquals("", subStr[i]);
		}

		// this scenario tests string with delimiter with surplus values.
		subStr = new String[10];
		final String[] expStrings = {"This", "used", "to", "test", "\'delimeter\'", "String", "", "", "", ""};
		DataUtilities.string2Strings("\nThis\tused to test \'delimeter\' String\r", 10, subStr);
		for(int i = 0; i < subStr.length; i++) {
			assertEquals(expStrings[i], subStr[i]);
		}

		// this scenario tests delimiter only String.
		subStr = new String[1];
		DataUtilities.string2Strings("\n\t\'\'\"\"\r", 1, subStr);
		assertEquals("''\"\"",subStr[0]);
	}

	/**
	 * Method to test bubbleSort()
	 */
	@Test
	public void testBubbleSort()
	{
		final int[] inputArray = {90, 21, 45, 31, 67, 356, 25};
		DataUtilities.bubbleSort(inputArray);
		final int[] expectedVals = { 21, 25, 31, 45, 67, 90, 356};
		for(int i = 0; i<inputArray.length; i++) {
			assertEquals(expectedVals[i], inputArray[i]);
		}

		// tests empty array
		final int[] emptyArray = {};
		DataUtilities.bubbleSort(emptyArray);
		assertEquals(0, emptyArray.length);	// checking the length of the array.

		// tests one element array
		final int[] oneElementArray = {324};
		DataUtilities.bubbleSort(oneElementArray);
		assertEquals(324, oneElementArray[0]);

		// tests two elements array
		final int[] twoElementArray = {324, 90};
		DataUtilities.bubbleSort(twoElementArray);
		assertEquals(90, twoElementArray[0]);
		assertEquals(324, twoElementArray[1]);
	}

	/**
	 * Method to test median()
	 */
	@Test
	public void testMedian()
	{
		final double[] data = {180.0, 45.6, 67.3, 10.0, 8.7, Double.NaN};
		double returnVal = DataUtilities.median(data);
		assertEquals(45.6, returnVal, 0.0);

		final double[] data1 = {180.0, 45.6, 67.3, 10.0, 8.7, 90.6};	// For other than Double.NaN case.
		returnVal = DataUtilities.median(data1);
		assertEquals(56.45, returnVal, 0.0);

		final double[] data2 = {};	// For empty array
		returnVal = DataUtilities.median(data2);
		assertEquals(Double.NaN, returnVal, 0.0);

		final double[] data3 = {Double.NaN};	// For element array
		returnVal = DataUtilities.median(data3);
		assertEquals(Double.NaN, returnVal, 0.0);

		final double[] data4 = {7, 9, 16, 21, 3, 51, 49, 10};	// For regular Array
		returnVal = DataUtilities.median(data4);
		assertEquals(13.0, returnVal, 0.0);
	}

	/**
	 * Method to test doubleToString()
	 */
	@Test
	public void testDoubleToString()
	{
		final double value = 1796457.783465;
		final int sigDigits = 3;
		String returnVal = DataUtilities.doubleToString(value, sigDigits);
		assertEquals("1.80E6", returnVal);

		returnVal = DataUtilities.doubleToString(-8901.076, sigDigits);
		assertEquals("-8.9e3", returnVal);

		returnVal = DataUtilities.doubleToString(-89.076, sigDigits);
		assertEquals("-89.1", returnVal);

		returnVal = DataUtilities.doubleToString(7, sigDigits);
		assertEquals("7.00", returnVal);

		returnVal = DataUtilities.doubleToString(15, sigDigits);
		assertEquals("15.0", returnVal);

		returnVal = DataUtilities.doubleToString(-150, sigDigits);
		assertEquals("-150.", returnVal);

		returnVal = DataUtilities.doubleToString(0, sigDigits);
		assertEquals("0.0", returnVal);

		returnVal = DataUtilities.doubleToString(-0, sigDigits);
		assertEquals("0.0", returnVal);

		returnVal = DataUtilities.doubleToString(816475, sigDigits);
		assertEquals("8.16E5", returnVal);
	}
}
