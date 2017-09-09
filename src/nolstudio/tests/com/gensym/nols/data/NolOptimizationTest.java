package com.gensym.nols.data;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Vector;

import org.easymock.Capture;
import org.easymock.EasyMock;
import org.easymock.IArgumentMatcher;
import org.easymock.IMocksControl;
import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.opt.INolObjective;
import com.gensym.math.opt.IObjectiveFactory;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import static org.easymock.EasyMock.capture;
import static org.easymock.EasyMock.expect;
import static org.easymock.EasyMock.expectLastCall;
import static org.easymock.EasyMock.isA;
import static org.easymock.EasyMock.reportMatcher;

public class NolOptimizationTest {

	private static final String INPUT_VARIABLE = "DeC2FeedFlow.m";
	private static final String OUTPUT_VARIABLE = "% C3 IN C2 COMP";
	private Vector<String> outs;
	private Vector<String> ins;
	private Vector<String> exogs;
	private Vector<String> manis;
	private Vector<String> state;
	private Vector<long[]> outDelays;
	private Vector<long[]> inputDelays;
	private DataSeries ds;
	private Vector<DataSeries> series;
	private Preprocessor prep;
	private IMocksControl ctrl;
	private INolModel2 inputModel;
	private INolOptimizeModel model;
	private NolOptimization optimization;
	
	private static final class EvaluateMatcher implements IArgumentMatcher {

		private static final EvaluateMatcher MATCHER = new EvaluateMatcher();
		
		private boolean isFirst = true;
		private int numberOfRows = 0;
		
		public void appendTo(StringBuffer buffer) {
		}

		public boolean matches(Object argument) {
			Matrix matrix = (Matrix) argument;
			if (isFirst) {
				numberOfRows = matrix.getRows();
			} else {
				matrix.redimension(numberOfRows, 1);
			}
			isFirst = ! isFirst;
			return true;
		}
		
		public static final Matrix evaluateMatcher() {
			reportMatcher(MATCHER);
			return null;
		}
		
	}
	
	private static final class ResultMatrixMatcher implements IArgumentMatcher {

		private int rows;
		private int cols;

		public ResultMatrixMatcher(int rows, int cols) {
			this.rows = rows;
			this.cols = cols;
		}
		
		public void appendTo(StringBuffer buffer) {
		}

		public boolean matches(Object argument) {
			Matrix matrix = (Matrix) argument;
			matrix.redimension(rows, cols);
			return true;
		}
		
		public static final Matrix resultMatrixMatcher(int rows, int cols) {
			reportMatcher(new ResultMatrixMatcher(rows, cols));
			return null;
		}
		
		
	}

	@Before
	public void setup() throws MathException {
		outs = new Vector<String>();
		outs.add(OUTPUT_VARIABLE);
		
		ins = new Vector<String>();
		ins.add(INPUT_VARIABLE);
		
		manis = (Vector<String>) ins.clone();
		exogs = new Vector<String>();
		state = new Vector<String>();
		
		outDelays = new Vector<long[]>();
		outDelays.add(new long[] {0});
		
		inputDelays = new Vector<long[]>();
		inputDelays.add(new long[] {0, 60000});
		
		ds = new DataSeries(0, 2);
		ds.setVariableParameters(0, null, OUTPUT_VARIABLE, null);
		ds.setVariableParameters(1, null, INPUT_VARIABLE, null);
		
		series = new Vector<DataSeries>();
		series.add(ds);
		
		prep = new Preprocessor();
		prep.setDataSeries(series);
		
		ctrl = EasyMock.createControl();
		inputModel = ctrl.createMock(INolModel2.class);
		model = ctrl.createMock(INolOptimizeModel.class);

		optimization = new NolOptimization();

		expect(model.getInputs()).andStubReturn(ins);
		expect(model.getInputDelays()).andStubReturn(inputDelays);
		expect(model.getState()).andStubReturn(state);
		expect(model.getOutputs()).andStubReturn(outs);
		expect(model.getOutputDelays()).andStubReturn(outDelays);
		expect(model.getManipulate()).andStubReturn(manis);
		expect(model.getExogenous()).andStubReturn(exogs);
		expect(model.getPreprocessor()).andStubReturn(prep);
		expect(model.getNin()).andStubReturn(2);
		expect(model.getNout()).andStubReturn(1);
		expect(model.getModel()).andStubReturn(inputModel);
		expect(model.getStateModel()).andStubReturn(null);
		model.evaluate(EvaluateMatcher.evaluateMatcher(),
				EvaluateMatcher.evaluateMatcher());
		expectLastCall().asStub();
		
	}
	
	private void runCalculateOptimization() throws MathException {
		ctrl.replay();
		optimization.setModel(model);
		optimization.calculationOptimization();
	}
	
	@Test
	public void testInitCostsAndBoundsForVarsWithMultipleDelays()
			throws MathException {
		runCalculateOptimization();
		assertTrue(optimization.isCalculated());
	}
	
	@Test
	public void testVariableMasks() throws MathException {
		INolObjective objective = ctrl.createMock(INolObjective.class);
		IObjectiveFactory factory = ctrl.createMock(IObjectiveFactory.class);
		
		optimization.setObjectiveFactory(factory);

		Capture<boolean[]> varMaskCapture = new Capture<boolean[]>();
		expect(factory.createObjective(isA(INolOptimizeModel.class), 
				capture(varMaskCapture), isA(Matrix.class), isA(Matrix.class),
				isA(Matrix.class), isA(Matrix.class))).andStubReturn(
						objective);
		
		objective.createSimplex(isA(Matrix.class), isA(Matrix.class));
		objective.evaluateModel(isA(Matrix.class),
				ResultMatrixMatcher.resultMatrixMatcher(1, 1),
				ResultMatrixMatcher.resultMatrixMatcher(1, 1));
		objective.evaluate(EvaluateMatcher.evaluateMatcher(),
				EvaluateMatcher.evaluateMatcher());
		objective.clearMatrices();
		
		runCalculateOptimization();
		assertTrue(varMaskCapture.getValue()[0]);
		assertTrue(varMaskCapture.getValue()[1]);
	}

	/*
	 * After loading from project for the old projects objectiveFactory
	 * can be null as it appeared after the project had been saved.
	 */
	@Test
	public void testNullObjectiveFactory() throws MathException {
		optimization.setObjectiveFactory(null);
		runCalculateOptimization();
		assertTrue(optimization.isCalculated());
	}

	@Test
	public void testInitXMatrixNumberOfColumns() throws MathException {
		ctrl.replay();
		optimization.setModel(model);
		Matrix x = optimization.getInitX();
		assertEquals(2, x.getCols());
	}

	/*
	 * After loading from project for the old projects initX
	 * can be of the incorrect dimension (not accounting multiple delays).
	 */
	@Test
	public void testIncorrectInitXMatrix() throws MathException {
		ctrl.replay();
		optimization.setModel(model);
		optimization.setInitXDirectly(Matlib.createMatrix(1, 1));
		Matrix x = optimization.getInitX();
		assertEquals(2, x.getCols());
	}

	@Test
	public void testInitXMatrixElements() throws MathException {
		IPreprocessor prepMock = ctrl.createMock(IPreprocessor.class);
		expect(model.getPreprocessor()).andStubReturn(prepMock);
		ctrl.replay();
		optimization.setModel(model);
		Matrix x = optimization.getInitX();
		assertTrue(x.get(0, 0) == x.get(0, 1));
	}

	@Test
	public void testSerialization() throws Exception {
		ObjectOutputStream out;
		ObjectInputStream in;
		String serFilename = "ser.out";

		out = new ObjectOutputStream(new FileOutputStream(serFilename));
		out.writeObject(optimization);
		out.close();
		in = new ObjectInputStream(new FileInputStream(serFilename));
		assertEquals(optimization, (NolOptimization) in.readObject());
	}

	@Test
	public void testPutGetBoundsWithDelay() {
		int ARRAY_SIZE = 7;
		double[] bb = new double[ARRAY_SIZE];
		for (int i=0; i<bb.length; i++) {
			bb[i] = Math.random();
		}
		long delay = Math.round((Math.random()*1000));
		optimization.putBounds(INPUT_VARIABLE, bb.clone(), delay);
		
		for (int i=0; i<bb.length; i++) {
			bb[i] = Math.random();
		}
		delay = Math.round((Math.random()*1000));
		optimization.putBounds(OUTPUT_VARIABLE, bb.clone(), delay);
		
		double[] bb1;
		bb1 = optimization.getBounds(OUTPUT_VARIABLE, delay);
		assertArrayEquals(bb, bb1, 1e-6);
		bb1 = optimization.getBounds(INPUT_VARIABLE, delay);
		assertNull(bb1);
	}

	private void assertArrayEquals(double[] bb, double[] bb1, double e) {
		assertEquals(bb.length, bb1.length);
		for(int i=0; i<bb.length;i++) {
			assertEquals(Math.round(bb[i]/e),Math.round(bb[i]/e));
		}
	}
}
