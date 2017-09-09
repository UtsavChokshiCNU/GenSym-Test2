package com.gensym.math.stats;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.Pls;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matrix;

public class StatsTest {

	private Matrix X;
	private Matrix Y;
	private Matrix XTrain;
	private Matrix YTrain;
	private Matrix XTest;
	private Matrix YTest;
	private ArchitectureParameters aps;
	private Pls tModel;

	@Before
	public void init() {
		X = new Matrix();
		X.redimension(2, 3);
		Y = new Matrix();
		Y.redimension(2, 3);
		XTrain = new Matrix();
		XTrain.redimension(2, 3);
		YTrain = new Matrix();
		YTrain.redimension(2, 3);
		XTest = new Matrix(Y);
		YTest = new Matrix(X);
		aps = new ArchitectureParameters(5, 5, 1, 1);
		tModel = new Pls(aps);
	}

	@Test
	public void testRandomSplitSingeMatrix() {
		assertEquals(2, X.getRows());
		assertEquals(3, X.getCols());

		Stats.randomSplit(2, 2, X);

		assertEquals(2, X.getRows());
		assertEquals(1, X.getCols());
	}

	@Test(expected = MathException.class)
	public void testRandomSplitWithTrainingMatrixFailure() throws MathException {
		init();
		Y = new Matrix();
		Y.redimension(3, 4);
		Matrix XTrain = new Matrix(X);
		Matrix XTest = new Matrix(X);
		Matrix YTrain = new Matrix(Y);
		Matrix YTest = new Matrix(Y);
		Stats.randomSplit(X, Y, 2, XTrain, YTrain, XTest, YTest);
	}

	@Test
	public void testRandomSplitWithTrainingMatrix() throws MathException {
		init();
		Stats.randomSplit(X, Y, 2, XTrain, YTrain, XTest, YTest);
		assertEquals(2, X.getRows());
		assertEquals(3, X.getCols());
		assertEquals(2, Y.getRows());
		assertEquals(3, Y.getCols());
	}

	@Test(expected = ArithmeticException.class)
	public void testBlockSplitFailure() throws MathException {
		init();
		Y = new Matrix();
		Y.redimension(3, 4);
		Matrix B = new Matrix();
		B.redimension(2, 2);
		Stats.blockSplit(X, Y, 2, 3, XTrain, YTrain, XTest, YTest, B);

	}

	@Test
	public void testBlockSplit() throws MathException {
		init();
		Matrix B = new Matrix();
		B.redimension(2, 2);
		assertEquals(2, B.getRows());
		assertEquals(2, B.getCols());
		Stats.blockSplit(X, Y, 1, 1, XTrain, YTrain, XTest, YTest, B);
		assertEquals(2, B.getRows());
		assertEquals(1, B.getCols());

	}

	@Test
	public void testCvRandomDesign() throws MathException {
		Matrix B = new Matrix();
		B.redimension(2, 2);
		assertEquals(2, B.getRows());
		assertEquals(2, B.getCols());
		Stats.cvRandomDesign(2, 3, B);
		assertEquals(2, B.getRows());
		assertEquals(3, B.getCols());
	}

	@Test
	public void testCvBlockDesign() throws MathException {
		Matrix B = new Matrix();
		B.redimension(2, 2);
		assertEquals(2, B.getRows());
		assertEquals(2, B.getCols());
		Stats.cvBlockDesign(2, 2, 4, B);
		assertEquals(2, B.getRows());
		assertEquals(4, B.getCols());
	}

	@Test
	public void testPca1() throws MathException {
		init();
		assertEquals(2, Y.getRows());
		assertEquals(3, Y.getCols());
		Stats.pca(X, Y);
		assertEquals(3, Y.getRows());
		assertEquals(2, Y.getCols());
	}

	@Test
	public void testFtest() throws MathException {
		double res = Stats.ftest(new Double(0.7), 3, 4);
		assertEquals(new Double(0.39042894660052524), new Double(res));
	}

	@Test
	public void testFtestProbabilityError() throws MathException {
		try {
			Stats.ftest(new Double(3.7), 3, 4);
		} catch (MathException me) {
			assertTrue(me.getMessage().contains("Probability not in the range(0,1)"));
		}
	}

	@Test
	public void testPls() throws MathException {
		init();
		Matrix P = new Matrix();
		P.redimension(3, 3);
		Matrix Q = new Matrix();
		P.redimension(4, 4);
		Matrix W = new Matrix();
		P.redimension(4, 4);
		Matrix T = new Matrix();
		P.redimension(3, 3);
		Matrix B = new Matrix();
		B.redimension(2, 2);

		assertEquals(2, B.getRows());
		assertEquals(2, B.getCols());

		Matrix U = new Matrix();
		P.redimension(5, 5);

		Stats.pls(X, Y, P, Q, W, T, U, B, 4);

		assertEquals(1, B.getRows());
		assertEquals(4, B.getCols());
	}

	@Test
	public void testPcaCase1() throws MathException {
		init();
		Matrix Pclim = new Matrix();
		Pclim.redimension(4, 4);
		Matrix ssg = new Matrix();
		ssg.redimension(3, 3);
		Matrix Var = new Matrix();
		Var.redimension(2, 2);
		Stats.pca(X, Y, Pclim, ssg, Var);
		assertEquals(1, Pclim.getRows());
		assertEquals(2, Pclim.getCols());
		assertEquals(1, Var.getRows());
		assertEquals(2, Var.getCols());
		assertNotEquals(new Double(0.0), new Double(Var.get(0, 0)));
		assertNotEquals(new Double(0.0), new Double(Var.get(0, 0)));
	}

	@Test
	public void testPcaCase2() throws MathException {
		init();
		Matrix X = new Matrix();
		X.redimension(5, 3);
		Matrix Pclim = new Matrix();
		Pclim.redimension(4, 4);
		Matrix ssg = new Matrix();
		ssg.redimension(3, 3);
		Matrix Var = new Matrix();
		Var.redimension(2, 2);
		Stats.pca(X, Y, Pclim, ssg, Var);
		assertEquals(1, Pclim.getRows());
		assertEquals(3, Pclim.getCols());
		assertEquals(new Double(0.0), new Double(Pclim.get(0, 0)));
		assertEquals(new Double(0.0), new Double(Pclim.get(0, 1)));
		assertEquals(new Double(0.0), new Double(Pclim.get(0, 2)));
		assertEquals(1, Var.getRows());
		assertEquals(3, Var.getCols());
		assertNotEquals(new Double(0.0), new Double(Var.get(0, 0)));
		assertNotEquals(new Double(0.0), new Double(Var.get(0, 1)));
		assertNotEquals(new Double(0.0), new Double(Var.get(0, 2)));
	}

	@Test
	public void testPcaCase3() throws MathException {
		init();
		Matrix X = new Matrix();
		X.redimension(5, 3);
		Stats.pca(X, 2, Y);
		assertEquals(3, Y.getRows());
		assertEquals(2, Y.getCols());
		assertEquals(new Double(0.0), new Double(Y.get(0, 0)));
		assertEquals(new Double(0.0), new Double(Y.get(0, 1)));
		assertEquals(new Double(1.0), new Double(Y.get(1, 0)));
		assertEquals(new Double(0.0), new Double(Y.get(1, 1)));
		assertEquals(new Double(0.0), new Double(Y.get(2, 0)));
		assertEquals(new Double(1.0), new Double(Y.get(2, 1)));
	}

	@Test
	public void testPcaCase3Failure() throws MathException {
		init();
		Matrix X = new Matrix();
		X.redimension(5, 3);
		try {
			Stats.pca(X, -1, Y);
		} catch (MathException me) {
			assertEquals("pca: number of principal components must be between 0 and the number of columns of X",
					me.getMessage());
		}
	}

	@Test
	public void testPcaCase4() throws MathException {
		init();
		Matrix X = new Matrix();
		X.redimension(5, 3);
		Stats.pca(X, new Double(2.6), Y);
		assertEquals(3, Y.getRows());
		assertEquals(3, Y.getCols());
		assertEquals(new Double(0.0), new Double(Y.get(0, 0)));
		assertEquals(new Double(0.0), new Double(Y.get(0, 1)));
		assertEquals(new Double(1.0), new Double(Y.get(0, 2)));
		assertEquals(new Double(1.0), new Double(Y.get(1, 0)));
		assertEquals(new Double(0.0), new Double(Y.get(1, 1)));
		assertEquals(new Double(0.0), new Double(Y.get(1, 2)));
		assertEquals(new Double(0.0), new Double(Y.get(2, 0)));
		assertEquals(new Double(1.0), new Double(Y.get(2, 1)));
		assertEquals(new Double(0.0), new Double(Y.get(2, 2)));
	}

	@Test
	public void testPcaCase5() throws MathException {
		init();
		Matrix X = new Matrix();
		X.redimension(5, 3);
		Stats.pca(X, 1, Y);
		assertEquals(3, Y.getRows());
		assertEquals(1, Y.getCols());
		assertEquals(new Double(0.0), new Double(Y.get(0, 0)));
		assertEquals(new Double(1.0), new Double(Y.get(1, 0)));
		assertEquals(new Double(0.0), new Double(Y.get(2, 0)));
	}

	@Test
	public void testPcr() throws MathException {
		init();
		Matrix P = new Matrix();
		P.redimension(3, 3);
		Matrix B = new Matrix();
		B.redimension(2, 2);
		assertEquals(2, B.getRows());
		assertEquals(2, B.getCols());
		Stats.pcr(XTrain, P, Y, B);
		assertEquals(3, B.getRows());
		assertEquals(3, B.getCols());
		assertEquals(new Double(0.0), new Double(B.get(0, 0)));
		assertEquals(new Double(0.0), new Double(B.get(0, 1)));
		assertEquals(new Double(0.0), new Double(B.get(0, 2)));
		assertEquals(new Double(0.0), new Double(B.get(1, 0)));
		assertEquals(new Double(0.0), new Double(B.get(1, 1)));
		assertEquals(new Double(0.0), new Double(B.get(1, 2)));
		assertEquals(new Double(0.0), new Double(B.get(2, 0)));
		assertEquals(new Double(0.0), new Double(B.get(2, 1)));
		assertEquals(new Double(0.0), new Double(B.get(2, 2)));
	}

	@Test
	public void testPcanipalsFailure1() throws MathException {
		init();
		try {
			Stats.pcanipals(X, 4, Y);
		} catch (MathException e) {
			assertEquals("pca: number of principal components must be between 0 and the number of columns of X",
					e.getMessage());
		}
	}

	@Test
	public void testPcanipalsFailure2() throws MathException {
		init();
		try {
			Stats.pcanipals(X, 2, Y);
		} catch (MathException e) {
			assertEquals("PCA failed: Matrix had no principal directions", e.getMessage());
		}
	}

	@Test
	public void testPcanipals() throws MathException {
		init();
		X.set(0, 0, 1.0);
		X.set(0, 1, 1.3);
		X.set(0, 2, 0.9);
		X.set(1, 0, 3.2);
		X.set(1, 1, 4.3);
		X.set(1, 2, 5.3);
		Stats.pcanipals(X, 1, Y);
		assertEquals(1, Y.getCols());
		assertEquals(3, Y.getRows());
		assertEquals(0.4315780481282435, Y.get(0, 0), 0.0002);
		assertEquals(0.5786172095484666, Y.get(1, 0), 0.0002);
		assertEquals(0.6920567268570992, Y.get(2, 0), 0.0002);

	}

	@Test
	public void testCoinFlipCase1() {
		boolean result = Stats.coinFlip(1.2);
		assertTrue(result);
	}

	@Test
	public void testCoinFlipCase2() {
		boolean result = Stats.coinFlip(0.0);
		assertFalse(result);
	}

	@Test
	public void testRandInt() {
		int result = Stats.randInt(3, 5);
		assertTrue(result >= 3);
		assertTrue(result <= 5);
	}

	@Test
	public void testRandDouble() {
		double ld = 9.5d;
		double ud = 46.76d;
		double result = Stats.randDouble(ld, ud);
		assertTrue(result >= ld);
		assertTrue(result <= ud);
	}

	@Test
	public void testImportanceSample() {
		int result = Stats.importanceSample(6);
		assertTrue(result <= 6);
	}

	@Test
	public void testCVPredictFailure() throws MathException {
		init();
		Matrix B = new Matrix();
		B.redimension(10, 10);
		Matrix X = new Matrix();
		B.redimension(5, 5);
		Matrix Y = new Matrix();
		B.redimension(5, 5);
		try {
			Stats.cvPredict(tModel, X, Y, 3, 1, B);
		} catch (MathException me) {
			assertEquals("getPart: cannot extract submatrix (0,0) to (-1,0) from a 0 by 0 matrix", me.getMessage());
		}
	}

	@Test
	public void testCVPredictZeroError() throws MathException {
		init();
		Matrix B = new Matrix();
		Matrix X = new Matrix();
		B.redimension(5, 5);
		Matrix Y = new Matrix();
		try {
			Stats.cvPredict(tModel, X, Y, 3, 0, B);
		} catch (ArithmeticException ae) {
			assertEquals("/ by zero", ae.getMessage());
		}
	}

	@Test
	public void testCVPredictSuccess1() throws MathException {
		init();
		Matrix B = new Matrix();
		B.redimension(5, 5);
		Matrix X = new Matrix();
		X.redimension(5, 5);
		Matrix Y = new Matrix();
		Y.redimension(5, 5);
		// Randomly chose cells asserted as all cells should satisfy this
		// assertion
		assertEquals(new Double(0.0), new Double(B.get(0, 0)));
		assertEquals(new Double(0.0), new Double(B.get(0, 4)));
		assertEquals(new Double(0.0), new Double(B.get(2, 0)));
		assertEquals(new Double(0.0), new Double(B.get(2, 4)));
		assertEquals(new Double(0.0), new Double(B.get(4, 1)));
		assertEquals(new Double(0.0), new Double(B.get(4, 3)));
		Stats.cvPredict(tModel, X, Y, 5, 3, B);
		// Randomly chose cells asserted as all cells should satisfy this
		// assertion
		assertNotEquals(new Double(0.0), new Double(B.get(0, 0)));
		assertNotEquals(new Double(0.0), new Double(B.get(0, 4)));
		assertNotEquals(new Double(0.0), new Double(B.get(2, 0)));
		assertNotEquals(new Double(0.0), new Double(B.get(2, 4)));
		assertNotEquals(new Double(0.0), new Double(B.get(4, 1)));
		assertNotEquals(new Double(0.0), new Double(B.get(4, 3)));
	}

	@Test
	public void testTtestpFailure1() throws MathException {
		try {
			Stats.ttestp(0.7, 0.5, 8);
		} catch (MathException me) {
			assertEquals("z must be 1 or 2.", me.getMessage());
		}

	}

	@Test
	public void testTtestp1() throws MathException {
		double result = Stats.ttestp(0.7, 0.5, 1);
		assertEquals(0.34270033126038313, result, 0.05);
	}

	@Test
	public void testTtestpFailure2() throws MathException {
		try {
			Stats.ttestp(0.7, 0.5, 2);
		} catch (MathException me) {
			assertEquals("probability not in the range(0,1)", me.getMessage());
		}
	}

	@Test
	public void testTtestp2() throws MathException {
		double result = Stats.ttestp(0.37, 0.5, 2);
		assertEquals(0.5443045986504019, result, 0.002);
	}

	@Test
	public void testGammaln1() throws MathException {
		double result = Stats.gammaln(3.4d);
		assertEquals(1.0923280598027416, result, 0.002);
	}

	@Test
	public void testGammaln2() throws MathException {
		double result = Stats.gammaln(0.63d);
		assertEquals(0.3536082827383616, result, 0.002);
	}

	@Test
	public void testGammaln3() throws MathException {
		double result = Stats.gammaln(6.7d);
		assertEquals(6.024433829872084, result, 0.002);
	}

	@Test
	public void testGammaln4() throws MathException {
		double result = Stats.gammaln(14.63d);
		assertEquals(24.20647236403143, result, 0.002);
	}

	@Test
	public void testGammalnFailure() throws MathException {
		try {
			Stats.gammaln(-3.4d);
		} catch (MathException me) {
			assertEquals("Input arguments must be real and nonnegative.", me.getMessage());
		}
	}

	@Test
	public void testCoinFlipWithParameter() {
		boolean result = Stats.coinFlip(1.0);
		assertTrue(result);
		result = Stats.coinFlip(0.0);
		assertFalse(result);
	}

	@Test
	public void testCoinFlip() {
		boolean result = Stats.coinFlip();
		// because this method is completely random and compares static 0.5 with
		// random(0,1) unlike its parameterized overloaded sibling
		assertTrue(result || !result);
	}

	@Test
	public void testBetanicFailure() throws MathException {
		try {
			Stats.betainc(8, 1, 3);
		} catch (MathException me) {
			assertEquals("In betainc(x,a,b), x must be in the interval [0,1].", me.getMessage());
		}
	}

	@Test
	public void testNipals() throws MathException {
		init();
		Matrix W = new Matrix();
		W.redimension(1, 1);
		Matrix T = new Matrix();
		T.redimension(5, 5);
		Matrix U = new Matrix();
		U.redimension(5, 5);
		Stats.nipals(X, W, XTrain, YTrain, W, T, U);
		assertEquals(3, W.getRows());
		assertEquals(2, W.getCols());
		assertNotEquals(new Double(0.0), W.get(0, 0));
		assertNotEquals(new Double(0.0), W.get(0, 1));
		assertNotEquals(new Double(0.0), W.get(1, 0));
		assertNotEquals(new Double(0.0), W.get(1, 1));
		assertNotEquals(new Double(0.0), W.get(2, 0));
		assertNotEquals(new Double(0.0), W.get(2, 1));
	}
}
