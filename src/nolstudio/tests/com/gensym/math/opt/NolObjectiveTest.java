package com.gensym.math.opt;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.Pls;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.matrix.Matrix;

public class NolObjectiveTest {

	private TrainableModel model;
	private Matrix X;
	private Matrix Y;
	private ArchitectureParameters AP;
	private boolean[] varMask;
	private Matrix xBounds;
	private Matrix xCosts;
	private Matrix yBounds;
	private Matrix yCosts;
	private int nx;
	private int ny;
	private int nindep;
	private NolObjective nolObjective;
	private double delta = 0.2E-10;
	private Matrix P, Q;

	@Before
	public void init() {
		AP = new ArchitectureParameters(2, 2, 1, 2);
		model = new EnsembleModel(AP);
		X = new Matrix();
		X.redimension(3, 3);
		X.set(0, 0, 3.4);
		X.set(0, 1, 0.79);
		X.set(0, 2, 4.1);
		X.set(1, 0, 1.2);
		X.set(1, 1, 5.6);
		X.set(1, 2, 6.5);
		X.set(2, 0, 2.1);
		X.set(2, 1, 1.1);
		X.set(2, 2, 0.0);

		Y = new Matrix();
		Y.redimension(2, 2);
		Y.set(0, 0, 3.4);
		Y.set(0, 1, 0.79);
		Y.set(1, 0, 1.2);
		Y.set(1, 1, 5.6);

		varMask = new boolean[3];
		varMask[0] = false;
		varMask[1] = true;
		varMask[2] = false;

		xBounds = new Matrix();
		xBounds.redimension(5, 5);
		xBounds.set(0, 0, 3.4);
		xBounds.set(0, 1, 0.79);
		xBounds.set(0, 2, 1.2);
		xBounds.set(0, 3, 5.6);
		xBounds.set(0, 4, 0.4);
		xBounds.set(1, 0, 3.4);
		xBounds.set(1, 1, 0.79);
		xBounds.set(1, 2, 1.2);
		xBounds.set(1, 3, 5.6);
		xBounds.set(1, 4, 5.6);
		xBounds.set(2, 0, 3.4);
		xBounds.set(2, 1, 0.79);
		xBounds.set(2, 2, 1.2);
		xBounds.set(2, 3, 5.6);
		xBounds.set(2, 4, 5.6);
		xBounds.set(3, 0, 3.4);
		xBounds.set(3, 1, 0.79);
		xBounds.set(3, 2, 1.2);
		xBounds.set(3, 3, 5.6);
		xBounds.set(3, 4, 5.6);
		xBounds.set(4, 0, 3.4);
		xBounds.set(4, 1, 0.79);
		xBounds.set(4, 2, 1.2);
		xBounds.set(4, 3, 5.6);
		xBounds.set(4, 4, 5.6);

		xCosts = new Matrix();
		xCosts.redimension(4, 4);
		xCosts.set(0, 0, 3.4);
		xCosts.set(0, 1, 0.79);
		xCosts.set(0, 2, 1.2);
		xCosts.set(0, 3, 5.6);
		xCosts.set(1, 0, 3.4);
		xCosts.set(1, 1, 0.79);
		xCosts.set(1, 2, 1.2);
		xCosts.set(1, 3, 5.6);
		xCosts.set(2, 0, 3.4);
		xCosts.set(2, 1, 0.79);
		xCosts.set(2, 2, 1.2);
		xCosts.set(2, 3, 5.6);
		xCosts.set(3, 0, 3.4);
		xCosts.set(3, 1, 0.79);
		xCosts.set(3, 2, 1.2);
		xCosts.set(3, 3, 5.6);

		yBounds = new Matrix();
		yBounds.redimension(5, 5);
		yBounds.set(0, 0, 3.4);
		yBounds.set(0, 1, 0.79);
		yBounds.set(0, 2, 1.2);
		yBounds.set(0, 3, 5.6);
		yBounds.set(1, 0, 3.4);
		yBounds.set(1, 1, 0.79);
		yBounds.set(1, 2, 1.2);
		yBounds.set(1, 3, 5.6);
		yBounds.set(2, 0, 3.4);
		yBounds.set(2, 1, 0.79);
		yBounds.set(2, 2, 1.2);
		yBounds.set(2, 3, 5.6);
		yBounds.set(3, 0, 3.4);
		yBounds.set(3, 1, 0.79);
		yBounds.set(3, 2, 1.2);
		yBounds.set(3, 3, 5.6);

		yCosts = new Matrix();
		yCosts.redimension(5, 5);
		yCosts.set(0, 0, 3.4);
		yCosts.set(0, 1, 0.79);
		yCosts.set(0, 2, 1.2);
		yCosts.set(0, 3, 5.6);
		yCosts.set(1, 0, 3.4);
		yCosts.set(1, 1, 0.79);
		yCosts.set(1, 2, 1.2);
		yCosts.set(1, 3, 5.6);
		yCosts.set(2, 0, 3.4);
		yCosts.set(2, 1, 0.79);
		yCosts.set(2, 2, 1.2);
		yCosts.set(2, 3, 5.6);
		yCosts.set(3, 0, 3.4);
		yCosts.set(3, 1, 0.79);
		yCosts.set(3, 2, 1.2);
		yCosts.set(3, 3, 5.6);

		nx = 1;
		ny = 1;
		nindep = 0;

		P = new Matrix();
		P.redimension(3, 3);
		P.set(0, 0, 3.4);
		P.set(0, 1, 0.79);
		P.set(0, 2, 4.1);
		P.set(1, 0, 1.2);
		P.set(1, 1, 5.6);
		P.set(1, 2, 6.5);
		P.set(2, 0, 2.1);
		P.set(2, 1, 1.1);
		P.set(2, 2, 0.0);

		Q = new Matrix();
		Q.redimension(2, 2);
		Q.set(0, 0, 3.4);
		Q.set(0, 1, 0.79);
		Q.set(1, 0, 1.2);
		Q.set(1, 1, 5.6);
	}

	@Test
	public void testCreateSimplex1() throws MathException {
		nolObjective = new NolObjective(model, varMask, xBounds, xCosts, yBounds, yCosts);
		nolObjective.createSimplex(P, Q);
		assertEquals(1.2, Q.get(0, 0), delta);
		assertEquals(5.6, Q.get(1, 0), delta);
	}

	@Test
	public void testCreateSimplex2() throws MathException {
		xBounds.set(4, 0, 8.1);
		xBounds.set(4, 1, 3.5);
		xBounds.set(4, 2, 5.6);
		xBounds.set(4, 3, 1.1);
		xBounds.set(4, 4, 0.0);
		nolObjective = new NolObjective(model, varMask, xBounds, xCosts, yBounds, yCosts);
		nolObjective.createSimplex(P, Q);
		assertEquals(1.2, Q.get(0, 0), delta);
		assertEquals(1.471, Q.get(1, 0), delta);
	}

	@Test
	public void testCreateSimplex3() throws MathException {
		xBounds.set(4, 0, Double.POSITIVE_INFINITY);
		xBounds.set(4, 1, Double.POSITIVE_INFINITY);
		xBounds.set(4, 2, Double.POSITIVE_INFINITY);
		xBounds.set(4, 3, Double.POSITIVE_INFINITY);
		xBounds.set(4, 4, Double.POSITIVE_INFINITY);
		nolObjective = new NolObjective(model, varMask, xBounds, xCosts, yBounds, yCosts);
		nolObjective.createSimplex(P, Q);
		assertEquals(1.2, Q.get(0, 0), delta);
		assertEquals(1.212, Q.get(1, 0), delta);
	}

	@Test
	public void testCreateSimplex4() throws MathException {
		P.set(0, 0, 0);
		P.set(0, 2, 0);
		xBounds.set(4, 0, Double.POSITIVE_INFINITY);
		xBounds.set(4, 1, Double.POSITIVE_INFINITY);
		xBounds.set(4, 2, Double.POSITIVE_INFINITY);
		xBounds.set(4, 3, Double.POSITIVE_INFINITY);
		xBounds.set(4, 4, Double.POSITIVE_INFINITY);
		nolObjective = new NolObjective(model, varMask, xBounds, xCosts, yBounds, yCosts);
		nolObjective.createSimplex(P, Q);
		assertEquals(1.2, Q.get(0, 0), delta);
		assertEquals(1.212, Q.get(1, 0), delta);
	}

	@Test
	public void testCreateSimplexFailure() throws MathException {
		P.set(0, 0, 0);
		P.set(0, 2, 0);
		xBounds.set(4, 0, 0.0);
		xBounds.set(4, 1, 0.0);
		xBounds.set(4, 2, 0.0);
		xBounds.set(4, 3, 0.0);
		xBounds.set(4, 4, 0.0);
		try {
			nolObjective = new NolObjective(model, varMask, xBounds, xCosts, yBounds, yCosts);
			nolObjective.createSimplex(P, Q);
		} catch (MathException me) {
			assertEquals("Objective Error: LB is greater than UB", me.getMessage());
		}
	}

	@Test
	public void testEvaluate() throws MathException {
		Q.redimension(3, 3);
		Q.set(0, 0, 3.4);
		Q.set(0, 1, 0.79);
		Q.set(0, 2, 1.2);
		Q.set(1, 0, 5.6);
		Q.set(1, 1, 3.4);
		Q.set(1, 2, 0.79);
		Q.set(2, 0, 1.2);
		Q.set(2, 1, 5.6);
		Q.set(2, 2, 5.6);

		Y.redimension(3, 3);
		Y.set(0, 0, 1.2);
		Y.set(0, 1, 7.8);
		Y.set(0, 2, 0.9);
		Y.set(1, 0, 2.3);
		Y.set(1, 1, 5.7);
		Y.set(1, 2, 0.2);
		Y.set(2, 0, 3.1);
		Y.set(2, 1, 6.7);
		Y.set(2, 2, 0.8);

		xBounds.set(4, 0, 8.0);
		xBounds.set(4, 1, 18.0);
		xBounds.set(4, 2, 21.0);
		xBounds.set(4, 3, 60.0);
		xBounds.set(4, 4, 50.0);

		yBounds.set(4, 0, 8.0);
		yBounds.set(4, 1, 18.0);
		yBounds.set(4, 2, 21.0);
		yBounds.set(4, 3, 60.0);
		yBounds.set(4, 4, 50.0);

		AP = new ArchitectureParameters(3, 3, 3, 3);
		model = new Pls(AP);
		Matrix Z = new Matrix();
		Z.redimension(3, 3);
		model.train(X, Z);
		model.learn(X, Z);
		nolObjective = new NolObjective(model, varMask, xBounds, xCosts, yBounds, yCosts);
		nolObjective.evaluate(P, Q);
		assertEquals(Double.NaN, Q.get(0, 0), delta);
		assertEquals(Double.NaN, Q.get(1, 0), delta);
		assertEquals(Double.NaN, Q.get(2, 0), delta);
	}

	@Test
	public void testCleaMatrices() throws MathException {
		nolObjective = new NolObjective(model, varMask, xBounds, xCosts, yBounds, yCosts);
		assertNotNull(nolObjective.getVariableMasks());
		nolObjective.clearMatrices();
		assertNull(nolObjective.getVariableMasks());
	}

}
