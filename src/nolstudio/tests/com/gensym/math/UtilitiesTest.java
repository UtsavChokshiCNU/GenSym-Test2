package com.gensym.math;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.matrix.Matrix;

public class UtilitiesTest {

	private double[] arr;
	private Matrix X, Y;
	private double delta = 0.00002;
	private double[][] arr2d;

	@Before
	public void init() {
		arr2d = new double[2][2];
		arr = new double[6];
		arr[0] = 3.4;
		arr[1] = 2.3;
		arr[2] = 7.8;
		arr[3] = 6.5;
		arr[4] = 16.90;
		arr[5] = 12.8;
		X = new Matrix();
		X.redimension(2, 3);
		Y = new Matrix();
		Y.redimension(2, 3);
	}

	@Test
	public void testDisp1() {
		Utilities.disp(arr, 3);
		assertEquals(3.4, arr[0], delta);
		assertEquals(2.3, arr[1], delta);
		assertEquals(7.8, arr[2], delta);
	}

	@Test
	public void testDisp2() {
		Utilities.disp(arr);
		assertEquals(3.4, arr[0], delta);
		assertEquals(2.3, arr[1], delta);
		assertEquals(7.8, arr[2], delta);
	}

	@Test
	public void testFormatDouble1() {
		String result = Utilities.formatDouble(34.867854678006543, 3);
		assertEquals(String.valueOf(34.9), result);
	}

	@Test
	public void testFormatDouble2() {
		String result = Utilities.formatDouble(-14.867854678006543, 3);
		assertEquals(String.valueOf(-14.9), result);
	}

	@Test
	public void testFormatDouble3() {
		String result = Utilities.formatDouble(0.0, 3);
		assertEquals(String.valueOf(0.0), result);
	}

	@Test
	public void testFormatDouble4() {
		String result = Utilities.formatDouble(Double.NaN, 3);
		assertEquals("NaN", result);
	}

	@Test
	public void testFormatDouble5() {
		String result = Utilities.formatDouble(19.68795d, 1);
		assertEquals("2.e1", result);
	}

	@Test
	public void testFormatDouble6() {
		String result = Utilities.formatDouble(109.68795d, 0);
		assertEquals(".e3", result);
	}

	@Test
	public void testFormatDouble7() {
		String result = Utilities.formatDouble(0.8E-67, 0);
		assertEquals(".e-67", result);
	}

	@Test
	public void testString2Data1() {
		String str = "23 14 56 89 07";
		double[] arrLocal = new double[5];
		Utilities.string2Data(str, 4, arrLocal);
		assertEquals(23.0, arrLocal[0], delta);
		assertEquals(14.0, arrLocal[1], delta);
		assertEquals(56.0, arrLocal[2], delta);
		assertEquals(89.0, arrLocal[3], delta);
		assertEquals(0.0, arrLocal[4], delta);
	}

	@Test
	public void testString2Data2() {
		String str = "23	14	56	89	07";
		double[] arrLocal = new double[5];
		Utilities.string2Data(str, 4, arrLocal);
		assertEquals(23.0, arrLocal[0], delta);
		assertEquals(14.0, arrLocal[1], delta);
		assertEquals(56.0, arrLocal[2], delta);
		assertEquals(89.0, arrLocal[3], delta);
		assertEquals(0.0, arrLocal[4], delta);
	}

	@Test
	public void testString2Data3() {
		String str = "23,14,56,89,07";
		double[] arrLocal = new double[5];
		Utilities.string2Data(str, 4, arrLocal);
		assertEquals(23.0, arrLocal[0], delta);
		assertEquals(14.0, arrLocal[1], delta);
		assertEquals(56.0, arrLocal[2], delta);
		assertEquals(89.0, arrLocal[3], delta);
		assertEquals(0.0, arrLocal[4], delta);
	}

	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void testString2DataFailure1() {
		String str = "23 14 56 89 07";
		double[] arrLocal = new double[5];
		Utilities.string2Data(str, 8, arrLocal);
	}

	@Test(expected = NumberFormatException.class)
	public void testString2DataFailure2() {
		String str = " ";
		double[] arrLocal = new double[5];
		Utilities.string2Data(str, 3, arrLocal);
	}

	@Test
	public void testGetNumberCount1() {
		String str = "23 14 56 89 07";
		int results = Utilities.getNumberCount(str);
		assertEquals(5, results);
	}

	@Test
	public void testGetNumberCount2() {
		String str = "23	14	56	89	07";
		int results = Utilities.getNumberCount(str);
		assertEquals(5, results);
	}

	@Test
	public void testGetNumberCount3() {
		String str = "23,14,56,89,07";
		int results = Utilities.getNumberCount(str);
		assertEquals(5, results);
	}

	@Test
	public void testGammaln1() {
		double fig = 0.567d;
		double result = Utilities.gammln(fig);
		assertEquals(0.45111632954855985, result, delta);
	}

	@Test
	public void testGammp2() throws MathException {
		double a = 0.567d;
		double fig = 23.67d;
		double result = Utilities.gammp(a, fig);
		assertEquals(0.9999999999916491, result, delta);
	}

	@Test
	public void testGammp1() throws MathException {
		double fig = 0.567d;
		double a = 23.67d;
		double result = Utilities.gammp(a, fig);
		assertEquals(3.94379570200231E-30, result, 2E-30);
	}

	@Test
	public void testGammpFailure() throws MathException {
		double fig = 0.567d;
		double a = -23.67d;
		try {
			Utilities.gammp(a, fig);
		} catch (MathException me) {
			assertEquals("Invalid arguments in routine gammp", me.getMessage());
		}
	}

	@Test
	public void testErfcc1() {
		double fig = 0.567d;
		double res = Utilities.erfcc(fig);
		assertEquals(0.6809145314584678, res, 0.00000002);
	}

	@Test
	public void testErfcc2() {
		double fig = -0.567d;
		double res = Utilities.erfcc(fig);
		assertEquals(1.319085468541532, res, 0.00000002);
	}

	@Test
	public void testErfcc3() {
		double fig = 0.0;
		double res = Utilities.erfcc(fig);
		assertEquals(1.0000000300000005, res, 0.00000002);
	}

	@Test
	public void testErff1() throws MathException {
		double fig = 0.567d;
		double result = Utilities.erff(fig);
		assertEquals(0.5773655264790452, result, delta);
	}

	@Test
	public void testErff2() throws MathException {
		double fig = -0.567d;
		double result = Utilities.erff(fig);
		assertEquals(-0.5773655264790452, result, delta);
	}

	@Test
	public void testErff3() throws MathException {
		double fig = 0.0d;
		double result = Utilities.erff(fig);
		assertEquals(0.0, result, delta);
	}

	@Test
	public void testGcf() throws MathException {
		Utilities.gcf(X, 3.4d, 1.2d, Y);
		assertEquals(1.092328059698489, Y.get(0, 0), 0.00003);
		assertEquals(0.9256112715101487, X.get(0, 0), 0.00003);
	}

	@Test
	public void testGcfFailure() throws MathException {

		try {
			Utilities.gcf(X, 8E8, 8E8, Y);
		} catch (MathException me) {
			assertEquals("a too large, ITMAX too small in gcf", me.getMessage());
		}
	}

	@Test
	public void testGser1() throws MathException {

		Utilities.gser(X, 3.4d, 1.2d, Y);
		assertEquals(0.07438890910276583, X.get(0, 0), delta);
		assertEquals(1.092328059698489, Y.get(0, 0), delta);
	}

	@Test
	public void testGser2() throws MathException {

		Utilities.gser(X, 3.4d, 0.0d, Y);
		assertEquals(0.0, X.get(0, 0), delta);
		assertEquals(1.092328059698489, Y.get(0, 0), delta);
	}

	@Test
	public void testGserFailure1() {

		try {
			Utilities.gser(X, 8E8, 8E8, Y);
		} catch (MathException me) {
			assertEquals("a too large, ITMAX too small in routine gser", me.getMessage());
		}
	}

	@Test
	public void testGserFailure2() {

		try {
			Utilities.gser(X, 3.4d, -1.2d, Y);
		} catch (MathException me) {
			assertEquals("x less than 0 in routine gser", me.getMessage());
		}
	}

	@Test
	public void testBetaCf() throws MathException {
		double result = Utilities.betacf(3.6, 5.8, 45.7);
		assertEquals(-0.009450425588898354, result, delta);
	}

	@Test
	public void testBetaincomplete1() throws MathException {
		double result = Utilities.betaincomplete(5.8, 23.7, 0.58);
		assertEquals(0.9999920029779009, result, delta);
	}

	@Test
	public void testBetaincomplete2() throws MathException {
		double result = Utilities.betaincomplete(5.8, 23.7, 0.0);
		assertEquals(0.0, result, delta);
		result = Utilities.betaincomplete(5.8, 23.7, 1.0);
		assertEquals(1.0, result, delta);
	}

	@Test
	public void testBetaincomplete3() throws MathException {
		double result = Utilities.betaincomplete(150.8, 3.7, 0.00058);
		assertEquals(0.0, result, delta);
	}

	@Test
	public void testBetaincompleteFailure() throws MathException {
		try {
			Utilities.betaincomplete(5.8, 23.7, 2.58);
		} catch (MathException me) {
			assertEquals("Bad x in routine betai", me.getMessage());
		}
	}

	@Test
	public void testIndent() {
		String result = Utilities.indent(4);
		assertEquals("\t\t\t\t", result);
	}

	@Test
	public void testDisp3() {
		Utilities.disp(arr2d);
		assertEquals(0.0, arr2d[0][0], delta);
		assertEquals(0.0, arr2d[0][1], delta);
		assertEquals(0.0, arr2d[1][0], delta);
		assertEquals(0.0, arr2d[1][1], delta);
	}

	@Test
	public void testDisp4() {
		Utilities.disp(arr2d, 2);
		assertEquals(0.0, arr2d[0][0], delta);
		assertEquals(0.0, arr2d[0][1], delta);
		assertEquals(0.0, arr2d[1][0], delta);
		assertEquals(0.0, arr2d[1][1], delta);
	}

	@Test
	public void testClone() throws CloneNotSupportedException {
		Utilities ut = new Utilities();
		Utilities utClone = (Utilities) ut.clone();
		assertNotEquals(ut, utClone);
	}
}
