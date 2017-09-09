package com.gensym.math;

import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;

public class AlgorithmsTest {

	private double[][] a1;
	private double[][] a2;
	private double[] b;
	private double[] x;
	private int n;
	private double delta = 0.00002;

	@Before
	public void init() {
		a1 = new double[3][3];
		a1[0][0] = 12.0d;
		a1[0][1] = 1.2d;
		a1[0][2] = 3.4d;
		a1[1][0] = 0.7d;
		a1[1][1] = 9.3d;
		a1[1][2] = 2.8d;
		a1[2][0] = 0.8d;
		a1[2][1] = 3.2d;
		a1[2][2] = 16.9d;

		a2 = new double[3][3];
		a2[0][0] = 14.0d;
		a2[0][1] = 0.2d;
		a2[0][2] = 5.4d;
		a2[1][0] = 0.3d;
		a2[1][1] = 19.4d;
		a2[1][2] = 1.8d;
		a2[2][0] = 0.6d;
		a2[2][1] = 5.2d;
		a2[2][2] = 30.9d;

		b = new double[3];
		b[0] = 0.5d;
		b[1] = 6.2d;
		b[2] = 2.3d;

		x = new double[3];

		n = 3;
	}

	@Test
	public void testCholsky() throws MathException {
		Algorithms.cholsky(a1, n, b, x);
		assertEquals(new Double(-0.0338955556981611d), new Double(x[0]));
		assertEquals(new Double(0.6609838356613689d), new Double(x[1]));
		assertEquals(new Double(0.033401783995379575d), new Double(x[2]));
	}

	@Test
	public void testGaussJ() throws MathException {

		Algorithms.gaussj(a1, 2, a2, 1);

		assertEquals(0.08396533044420368, a1[0][0], delta);
		assertEquals(-0.010834236186348862, a1[0][1], delta);
		assertEquals(3.4, a1[0][2], delta);
		assertEquals(-0.0063199711087035025, a1[1][0], delta);
		assertEquals(0.10834236186348863, a1[1][1], delta);
		assertEquals(2.8, a1[1][2], delta);
		assertEquals(0.8, a1[2][0], delta);
		assertEquals(3.2, a1[2][1], delta);
		assertEquals(16.9, a1[2][2], delta);

		assertEquals(1.1722643553629468, a2[0][0], delta);
		assertEquals(0.2, a2[0][1], delta);
		assertEquals(5.4, a2[0][2], delta);
		assertEquals(-0.05597688696280245, a2[1][0], delta);
		assertEquals(19.4, a2[1][1], delta);
		assertEquals(1.8, a2[1][2], delta);
		assertEquals(0.6, a2[2][0], delta);
		assertEquals(5.2, a2[2][1], delta);
		assertEquals(30.9, a2[2][2], delta);
	}

	@Test
	public void testGaussJFaliure1() throws MathException {
		double[][] x = new double[3][3];
		x[0][0] = 0;
		x[0][1] = 0;
		x[0][2] = 0;
		x[1][0] = 0;
		x[1][1] = 0;
		x[1][2] = 0;
		x[2][0] = 0;
		x[2][1] = 0;
		x[2][2] = 0;
		try {
			Algorithms.gaussj(x, 3, a1, 3);
		} catch (MathException me) {
			assertEquals("gaussj: Singular Matrix-2", me.getMessage());
		}
	}

	@Test
	public void testGaussJFaliure2() throws MathException {

		double[][] x = new double[3][3];
		x[0][0] = 0;
		x[0][1] = 2.3;
		x[0][2] = 4.3;
		x[1][0] = 1.8;
		x[1][1] = 0;
		x[1][2] = 4.5;
		x[2][0] = 3.4;
		x[2][1] = 5.6;
		x[2][2] = 0;
		try {
			Algorithms.gaussj(x, 3, a1, 3);
		} catch (MathException me) {
			assertEquals("gaussj: Singular Matrix-2", me.getMessage());
		}
	}

	@Test
	public void testHpSort1() {

		Algorithms.hpsort(b, 3);
		assertEquals(0.5d, b[0], delta);
		assertEquals(2.3d, b[1], delta);
		assertEquals(6.2d, b[2], delta);
	}

	@Test
	public void testHpSort2() {

		Algorithms.hpsort(b, 2);
		assertEquals(0.5d, b[0], delta);
		assertEquals(6.2d, b[1], delta);
		assertEquals(2.3d, b[2], delta);
	}

	@Test
	public void testHpSort3() {

		Algorithms.hpsort(b, 1);
		assertEquals(0.5d, b[0], delta);
		assertEquals(6.2d, b[1], delta);
		assertEquals(2.3d, b[2], delta);
	}

	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void testHpSortFailure1() {
		Algorithms.hpsort(b, 4);
	}

	@Test
	public void testHpSort4() {

		double[] c = new double[4];
		c[0] = 5.7;
		c[1] = 3.8;
		c[2] = 9.0;
		c[3] = 0.7;
		Algorithms.hpsort(b, 3, c);
		assertEquals(0.5d, b[0], delta);
		assertEquals(2.3d, b[1], delta);
		assertEquals(6.2d, b[2], delta);
		assertEquals(5.7d, c[0], delta);
		assertEquals(9.0d, c[1], delta);
		assertEquals(3.8d, c[2], delta);
		assertEquals(0.7d, c[3], delta);
	}

	@Test
	public void testHpSort5() {

		double[][] c = new double[3][3];
		c[0][0] = 6.5;
		c[0][1] = 5.4;
		c[0][2] = 2.6;
		c[1][0] = 2.1;
		c[1][1] = 9.8;
		c[1][2] = 4.0;
		c[2][0] = 0.06;
		c[2][1] = 14.9;
		c[2][2] = 2.7;

		Algorithms.hpsort(b, 3, c);

		assertEquals(6.5d, c[0][0], delta);
		assertEquals(5.4d, c[0][1], delta);
		assertEquals(2.6d, c[0][2], delta);
		assertEquals(0.06d, c[1][0], delta);
		assertEquals(14.9d, c[1][1], delta);
		assertEquals(2.7d, c[1][2], delta);
		assertEquals(2.1d, c[2][0], delta);
		assertEquals(9.8d, c[2][1], delta);
		assertEquals(4.0d, c[2][2], delta);

		assertEquals(0.5, b[0], delta);
		assertEquals(2.3, b[1], delta);
		assertEquals(6.2, b[2], delta);

	}

	@Test
	public void testLubksb() {

		double[][] c = new double[3][3];
		c[0][0] = 6.5;
		c[0][1] = 5.4;
		c[0][2] = 2.6;
		c[1][0] = 2.1;
		c[1][1] = 9.8;
		c[1][2] = 4.0;
		c[2][0] = 0.06;
		c[2][1] = 14.9;
		c[2][2] = 2.7;

		double[][] d = new double[3][3];
		d[0][0] = 4.5;
		d[0][1] = 0.9;
		d[0][2] = 2.0;
		d[1][0] = 3.2;
		d[1][1] = 10.89;
		d[1][2] = 3.78;
		d[2][0] = 8.09;
		d[2][1] = 1.9;
		d[2][2] = 7.4;

		int[] e = new int[3];
		e[0] = 0;
		e[1] = 2;
		e[2] = 1;

		Algorithms.lubksb(c, 3, e, d, 3);

		assertEquals(1.5334426420140703, d[0][0], delta);
		assertEquals(2.87680213965928, d[0][1], delta);
		assertEquals(1.1883630443630437, d[0][2], delta);
		assertEquals(7.780801209372639, d[1][0], delta);
		assertEquals(25.64712773998489, d[1][1], delta);
		assertEquals(8.434391534391533, d[1][2], delta);
		assertEquals(-18.262962962962966, d[2][0], delta);
		assertEquals(-60.112962962962975, d[2][1], delta);
		assertEquals(-19.719259259259257, d[2][2], delta);
	}

	@Test
	public void testLudCmp1() throws MathException {

		int[] e = new int[3];
		e[0] = 0;
		e[1] = 2;
		e[2] = 1;
		Algorithms.ludcmp(a1, 3, e);
		assertEquals(12.0, a1[0][0], delta);
		assertEquals(1.2, a1[0][1], delta);
		assertEquals(3.4, a1[0][2], delta);
		assertEquals(0.05833333333333333, a1[1][0], delta);
		assertEquals(9.23, a1[1][1], delta);
		assertEquals(2.6016666666666666, a1[1][2], delta);
		assertEquals(0.06666666666666667, a1[2][0], delta);
		assertEquals(0.3380281690140845, a1[2][1], delta);
		assertEquals(15.793896713615021, a1[2][2], delta);
	}

	@Test
	public void testLudCmp2() throws MathException {

		double[][] x = new double[3][3];
		x[0][0] = 0;
		x[0][1] = 5.4;
		x[0][2] = 6.5;
		x[1][0] = 2.3;
		x[1][1] = 0;
		x[1][2] = 5.8;
		x[2][0] = 2.9;
		x[2][1] = 4.5;
		x[2][2] = 0;
		int[] e = new int[3];
		e[0] = 0;
		e[1] = 2;
		e[2] = 1;
		Algorithms.ludcmp(x, 3, e);
		assertEquals(2.9, x[0][0], delta);
		assertEquals(4.5, x[0][1], delta);
		assertEquals(0.0, x[0][2], delta);
		assertEquals(0.0, x[1][0], delta);
		assertEquals(5.4, x[1][1], delta);
		assertEquals(6.5, x[1][2], delta);
		assertEquals(0.7931034482758621, x[2][0], delta);
		assertEquals(-0.6609195402298851, x[2][1], delta);
		assertEquals(10.095977011494252, x[2][2], delta);
	}

	@Test
	public void testLudCmpFailure() throws MathException {

		double[][] x = new double[3][3];
		x[0][0] = 0;
		x[0][1] = 0;
		x[0][2] = 0;
		x[1][0] = 0;
		x[1][1] = 0;
		x[1][2] = 0;
		x[2][0] = 0;
		x[2][1] = 0;
		x[2][2] = 0;
		int[] e = new int[3];
		e[0] = 0;
		e[1] = 2;
		e[2] = 1;
		try {
			Algorithms.ludcmp(x, 3, e);
		} catch (MathException me) {
			assertEquals("ludcmp: Singular Matrix", me.getMessage());
		}
	}

	@Test
	public void testPythag1() {
		double result = Algorithms.pythag(3.2, 4.9);
		assertEquals(5.852349955359813, result, delta);
	}

	@Test
	public void testPythag2() {
		double result = Algorithms.pythag(4.9, 3.2);
		assertEquals(5.852349955359813, result, delta);
	}

	@Test
	public void testPythag3() {
		double result = Algorithms.pythag(0.0, 0.0);
		assertEquals(0.0, result, delta);
	}

	@Test
	public void testRemainder1() {
		double result = Algorithms.remainder(9.8, 4.5);
		assertEquals(0.8000000000000007, result, delta);
	}

	@Test
	public void testRemainder2() {
		int result = Algorithms.remainder(348, 127);
		assertEquals(94, result);
	}

	@Test
	public void testSign1() {
		double result = Algorithms.SIGN(3.9, 4.7);
		assertEquals(3.9, result, delta);
	}

	@Test
	public void testSign2() {
		double result = Algorithms.SIGN(3.9, -4.7);
		assertEquals(-3.9, result, delta);
	}

	@Test
	public void testSQR1() {
		double result = Algorithms.SQR(0.0);
		assertEquals(0.0, result, delta);
	}

	@Test
	public void testSQR2() {
		double result = Algorithms.SQR(1.1);
		assertEquals(1.21, result, delta);
	}

	@Test
	public void testSvbksb() {

		double[][] c = new double[3][3];
		c[0][0] = 0;
		c[0][1] = 5.4;
		c[0][2] = 6.5;
		c[1][0] = 2.3;
		c[1][1] = 0;
		c[1][2] = 5.8;
		c[2][0] = 2.9;
		c[2][1] = 4.5;
		c[2][2] = 0;

		double[][] d = new double[3][3];
		d[0][0] = 4.5;
		d[0][1] = 0.9;
		d[0][2] = 2.0;
		d[1][0] = 3.2;
		d[1][1] = 10.89;
		d[1][2] = 3.78;
		d[2][0] = 8.09;
		d[2][1] = 1.9;
		d[2][2] = 7.4;

		int[] e = new int[3];
		e[0] = 0;
		e[1] = 2;
		e[2] = 1;

		Algorithms.svbksb(a1, b, c, 3, 3, d, 3, a2);

		assertEquals(508.1171430575035, a2[0][0], delta);
		assertEquals(280.01165077138853, a2[0][1], delta);
		assertEquals(455.8919691444601, a2[0][2], delta);
		assertEquals(694.4272869565217, a2[1][0], delta);
		assertEquals(257.3202347826087, a2[1][1], delta);
		assertEquals(509.0102086956522, a2[1][2], delta);
		assertEquals(408.0386322580645, a2[2][0], delta);
		assertEquals(194.37367419354842, a2[2][1], delta);
		assertEquals(233.3268322580645, a2[2][2], delta);

	}

	@Test
	public void testSvdcmp1() throws MathException {

		double[][] d = new double[3][3];
		d[0][0] = 4.5;
		d[0][1] = 0.9;
		d[0][2] = 2.0;
		d[1][0] = 3.2;
		d[1][1] = 10.89;
		d[1][2] = 3.78;
		d[2][0] = 8.09;
		d[2][1] = 1.9;
		d[2][2] = 7.4;

		int[] e = new int[3];
		e[0] = 0;
		e[1] = 2;
		e[2] = 1;

		Algorithms.svdcmp(a1, 3, 3, b, d);

		assertEquals(-0.36397360377525356, a1[0][0], delta);
		assertEquals(0.9287159984848558, a1[0][1], delta);
		assertEquals(-0.07078001068897966, a1[0][2], delta);
		assertEquals(-0.30579170280487855, a1[1][0], delta);
		assertEquals(-0.04737081379544614, a1[1][1], delta);
		assertEquals(0.9509192607661544, a1[1][2], delta);
		assertEquals(-0.8797810240341328, a1[2][0], delta);
		assertEquals(-0.3677534502334877, a1[2][1], delta);
		assertEquals(-0.3012353724097122, a1[2][2], delta);
	}

	@Test
	public void testSvdcmp2() throws MathException {

		double[][] c = new double[3][3];
		c[0][0] = 0;
		c[0][1] = 0;
		c[0][2] = 0;
		c[1][0] = 0;
		c[1][1] = 0;
		c[1][2] = 0;
		c[2][0] = 0;
		c[2][1] = 0;
		c[2][2] = 0;

		double[][] d = new double[3][3];
		d[0][0] = 0;
		d[0][1] = 0;
		d[0][2] = 0;
		d[1][0] = 0;
		d[1][1] = 0;
		d[1][2] = 0;
		d[2][0] = 0;
		d[2][1] = 0;
		d[2][2] = 0;

		Algorithms.svdcmp(d, 3, 3, b, c);

		assertEquals(1.0, d[0][0], delta);
		assertEquals(0.0, d[0][1], delta);
		assertEquals(0.0, d[0][2], delta);
		assertEquals(0.0, d[1][0], delta);
		assertEquals(1.0, d[1][1], delta);
		assertEquals(0.0, d[1][2], delta);
		assertEquals(0.0, d[2][0], delta);
		assertEquals(0.0, d[2][1], delta);
		assertEquals(1.0, d[2][2], delta);
	}
}
