package com.gensym.nols.deploy;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.doNothing;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.reset;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;
import static org.powermock.api.mockito.PowerMockito.spy;

import java.util.HashMap;
import java.util.Random;
import java.util.Vector;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.InOrder;
import org.mockito.Matchers;
import org.mockito.Mockito;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.EnsembleModelListener;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.NolOptimization;
import com.gensym.nols.data.Variable;

@RunWith(PowerMockRunner.class)
@PrepareForTest({ DataSeries.class, Matlib.class, Matrix.class, NolOptimization.class, OnlineOptimizer.class })
public class OnlineOptimizerTestWithMocks {
	private static final double DELTA = 0.1;
	private static final long TIME_IN_MILLI_SECONDS = 100;
	private static final String EXOGENOUS_VARIABLE = "NolOptimizeModelStub Exogenous Variable";
	private static final String MANIPULATED_EXOGENOUS_VARIABLE = "NolOptimizeModelStub Manipulated Exogenous Variable";
	private static final String MANIPULATED_VARIABLE = "NolOptimizeModelStub Manipulated Variable";
	private static final String STATE_VARIABLE = "NolOptimizeModelStub State Variable";

	private boolean autoStop;
	private boolean display;
	private boolean newTraining;
	private boolean stateModelExists;
	private EnsembleModel ensembleModel;
	private EnsembleModel stateEnsembleModel;
	private int statusFlag;
	private Matrix matrixX;
	private Matrix matrixXResult;
	private Matrix matrixXSetAsInitX;
	private Matrix matrixY;
	private Matrix matrixYResult;
	private NolOptimization nolOptimization;
	private NolOptimizeModelStub optimizerModel;
	private OnlineOptimizer optimizer;
	private OnlineOptimizer sut;
	private PreprocessorStub optimizerModelPreprocessor;
	private String inputFileName;
	private String outputFileName;
	private String statusMessage;
	private Vector<EnsembleModelListener> modelListeners;

	@Before
	public void setup() {
		stateModelExists = false;
		statusFlag = 0;
		statusMessage = "";

		sut = new OnlineOptimizer();
	}

	@Test
	public void test_trainOutputModelFromFile_Always_InvokesTrainOutputModel() throws Exception {
		// Arrange
		arrangeForTrainModelFromFile();
		OnlineOptimizer sutSpy = spy(sut);
		doNothing().when(sutSpy).trainOutputModel(modelListeners, matrixX, matrixY, TIME_IN_MILLI_SECONDS, autoStop,
				newTraining, display);

		// Act
		sutSpy.trainOutputModelFromFile(modelListeners, inputFileName, outputFileName, TIME_IN_MILLI_SECONDS, autoStop,
				newTraining, display);

		// Assert
		verify(sutSpy).trainOutputModel(modelListeners, matrixX, matrixY, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainStateModelFromFile_StateModelDoesNotExist_ThrowsMathException() throws Exception {
		// Arrange
		arrangeForTrainStateModelFromFile();
		OnlineOptimizer sutSpy = spy(sut);
		doNothing().when(sutSpy).trainStateModel(modelListeners, matrixX, matrixY, TIME_IN_MILLI_SECONDS, autoStop,
				newTraining, display);

		// Act
		sutSpy.trainStateModelFromFile(modelListeners, inputFileName, outputFileName, TIME_IN_MILLI_SECONDS, autoStop,
				newTraining, display);
	}

	@Test
	public void test_trainStateModelFromFile_StateModelExists_InvokesTrainStateModel() throws Exception {
		// Arrange
		stateModelExists = true;
		arrangeForTrainStateModelFromFile();
		OnlineOptimizer sutSpy = spy(sut);
		doNothing().when(sutSpy).trainStateModel(modelListeners, matrixX, matrixY, TIME_IN_MILLI_SECONDS, autoStop,
				newTraining, display);

		// Act
		sutSpy.trainStateModelFromFile(modelListeners, inputFileName, outputFileName, TIME_IN_MILLI_SECONDS, autoStop,
				newTraining, display);

		// Assert
		verify(sutSpy).trainStateModel(modelListeners, matrixX, matrixY, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);
	}

	@Test
	public void test_optimize_Always_InvokesCalculator() throws MathException {
		// Arrange
		OnlineOptimizer sutSpy = spy(sut);
		PowerMockito.doNothing().when(sutSpy).calculate();

		// Act
		sutSpy.optimize();

		// Assert
		verify(sutSpy, times(1)).calculate();
	}

	@Test
	public void test_calculate_OutputModelExistsAndStateModelDoesNotExist_InvokesSetInitXWithInitialValues()
			throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		verify(nolOptimization, times(1)).setInitX(Matchers.any(Matrix.class));
		verifyInitialXMatrix();
	}

	@Test
	public void test_calculate_IsNotCalcualtedYet_CalculatesOptimization() throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		InOrder inOrder = Mockito.inOrder(nolOptimization);
		inOrder.verify(nolOptimization, times(1)).setCalculated(false);
		inOrder.verify(nolOptimization, times(1)).calculationOptimization();
	}

	@Test
	public void test_calculate_IfAlreadyCalculated_DoesNotCalculateOptimizationAgain() throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		sut.calculate();
		reset(nolOptimization);

		// Act
		sut.calculate();

		// Assert
		verify(nolOptimization, never()).calculationOptimization();
	}

	@Test
	public void test_calculate_Always_SetsStatusFlag() throws MathException {
		// Arrange
		statusFlag = 2;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		assertEquals(sut.getStatusFlag(), statusFlag);
	}

	@Test
	public void test_calculate_Always_SetsStatusMessage() throws MathException {
		// Arrange
		statusMessage = "Status Message";
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		assertEquals(sut.getStatusMessage(), statusMessage);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_calculate_StatusFlagIsOne_ThrowsMathException() throws MathException {
		// Arrange
		stateModelExists = false;
		statusFlag = 1;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();
	}

	@Test
	public void test_calculate_OutputModelExistsAndStateModelDoesNotExist_SetsInputData() throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		for (int idx = 0; idx < optimizerModel.getInputs().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getInputs().get(idx));
			assertEquals(variable.getResultValue(), sut.getValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_calculate_OutputModelExistsAndStateModelDoesNotExist_SetsOutputData() throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		for (int idx = 0; idx < optimizerModel.getOutputs().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getOutputs().get(idx));
			assertEquals(matrixYResult.get(0, idx), sut.getValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_calculate_StateModelExists_InvokesSetInitXWithInitialValues() throws MathException {
		// Arrange
		stateModelExists = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		verify(nolOptimization, times(1)).setInitX(Matchers.any(Matrix.class));
		verifyInitialXMatrixForStateModel();
	}

	@Test
	public void test_calculate_StatModelExists_SetsInputData() throws MathException {
		// Arrange
		stateModelExists = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		verifyInputDataForStateModel();
	}

	@Test
	public void test_calculate_StatModelExists_SetsOutputData() throws MathException {
		// Arrange
		stateModelExists = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.calculate();

		// Assert
		for (int idx = 0; idx < optimizerModel.getOutputs().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getOutputs().get(idx));
			assertEquals(matrixYResult.get(0, idx + optimizerModel.getState().size()),
					sut.getValueByName(variable.getName()), DELTA);
		}
	}

	// -- Helper Methods --

	private void arrangeForTrainStateModelFromFile() throws Exception {
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		arrangeForTrainModelFromFile();
	}

	private void arrangeForTrainModelFromFile() throws Exception {
		inputFileName = "Input File.tmp";
		outputFileName = "Output File.tmp";
		PowerMockito.mockStatic(Matrix.class);
		matrixX = new Matrix();
		matrixY = new Matrix();
		PowerMockito.doReturn(matrixX).when(Matrix.class, "readFromFile", inputFileName);
		PowerMockito.doReturn(matrixY).when(Matrix.class, "readFromFile", outputFileName);
	}

	private void arrangeBaseOptimizer() throws MathException {
		arrangeOptimizerModelProcessor();
		arrangeOptimizerModel();
		arrangeOptimization();

		optimizer = new OnlineOptimizer("Optimizer 1 Name", nolOptimization);
		optimizer.setName("Optimizer 1 Name");
		optimizer.setComment("Optimizer 1 Comment");
	}

	private void arrangeMatrixXResult() {
		matrixXResult = new Matrix();
		matrixXResult.redimension(1, optimizerModel.getInputs().size());

		for (int idx = 0; idx < optimizerModel.getInputs().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getInputs().get(idx));

			matrixXResult.set(0, idx, variable.getResultValue());
		}
	}

	private void arrangeOptimization() {
		matrixYResult = new Matrix();
		matrixYResult.redimension(1, optimizerModel.getOutputs().size() + optimizerModel.getState().size());

		arrangeMatrixXResult();

		for (int idx = 0; idx < optimizerModel.getState().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getState().get(idx));
			matrixYResult.set(0, idx, variable.getResultValue());
		}

		for (int idx = 0; idx < optimizerModel.getOutputs().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getOutputs().get(idx));
			matrixYResult.set(0, idx + optimizerModel.getState().size(), variable.getResultValue());
		}

		nolOptimization = PowerMockito.mock(NolOptimization.class);
		PowerMockito.when(nolOptimization.getModel()).thenReturn(optimizerModel);
		PowerMockito.when(nolOptimization.getXResult()).thenReturn(matrixXResult);
		PowerMockito.when(nolOptimization.getYResult()).thenReturn(matrixYResult);
		PowerMockito.when(nolOptimization.getStatusFlag()).thenReturn(statusFlag);
		PowerMockito.when(nolOptimization.getStatusMessage()).thenReturn(statusMessage);

		PowerMockito.doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				matrixXSetAsInitX = cloneMatrix((Matrix) invocation.getArguments()[0]);
				return null;
			}
		}).when(nolOptimization).setInitX(Matchers.any(Matrix.class));
	}

	private void arrangeOptimizer() throws MathException {
		arrangeBaseOptimizer();

		ensembleModel = PowerMockito.mock(EnsembleModel.class);
		when(ensembleModel.getNin()).thenReturn(105);
		when(ensembleModel.getNout()).thenReturn(205);

		optimizerModel.setModel(ensembleModel);

		if (stateModelExists) {
			stateEnsembleModel = mock(EnsembleModel.class);
			when(stateEnsembleModel.getNin()).thenReturn(305);
			when(stateEnsembleModel.getNout()).thenReturn(405);
			optimizerModel.setStateModel(stateEnsembleModel);
		}
	}

	private void arrangeOptimizerModel() {
		optimizerModel = new NolOptimizeModelStub(optimizerModelPreprocessor);

		// Setting optimizer model name
		optimizerModel.setName("NolOptimizationModelStub Name");

		// Setting more than one outputs
		Vector<String> outputs = new Vector<String>();
		outputs.addElement("NolOptimizeModelStub Output 1");
		outputs.addElement("NolOptimizeModelStub Output 2");
		optimizerModel.setOutputs(outputs);

		// Setting more than one state names
		Vector<String> stateNames = new Vector<String>();
		stateNames.addElement(STATE_VARIABLE);
		stateNames.addElement("NolOptimizeModelStub State 2");
		optimizerModel.setStateInputs(stateNames);

		// Setting more than one manipulated names
		Vector<String> manipulatedNames = new Vector<String>();
		manipulatedNames.addElement(MANIPULATED_EXOGENOUS_VARIABLE);
		manipulatedNames.addElement(MANIPULATED_VARIABLE);
		optimizerModel.setManipulate(manipulatedNames);

		// Setting more than one exogenous names
		Vector<String> exogNames = new Vector<String>();
		exogNames.addElement(MANIPULATED_EXOGENOUS_VARIABLE);
		exogNames.addElement(EXOGENOUS_VARIABLE);
		optimizerModel.setExogenous(exogNames);

		HashMap<String, Variable> variablesMap = new HashMap<String, Variable>();

		Vector<String> allNames = new Vector<String>();
		allNames.addAll(outputs);
		allNames.addAll(stateNames);
		allNames.addAll(manipulatedNames);
		allNames.addAll(exogNames);

		Random randomGenerator = new Random();

		int count = 1;
		for (String name : allNames) {
			if (variablesMap.containsKey(name)) {
				continue;
			}

			Variable variable = new Variable();
			variable.setName(name);
			variable.setTag(name + " Tag");
			variable.setUnit(name + " Unit");
			variable.setInitialValue(randomGenerator.nextInt(1000));
			variable.setResultValue(randomGenerator.nextInt(1000));
			// There are 10 different statistics used in variable. Hence,
			// creating array of 10 numbers. Multiplying by count to keep
			// statistics in different variables unique which are used
			// for assertions.
			variable.setStatistics(new double[] { 1 * count, 2 * count, 3 * count, 4 * count, 5 * count, 6 * count,
					7 * count, 8 * count, 9 * count, 10 * count });
			variablesMap.put(name, variable);
			count++;
		}

		optimizerModelPreprocessor.setVariablesFromVariableName(variablesMap);
	}

	private void arrangeOptimizerModelProcessor() {
		optimizerModelPreprocessor = new PreprocessorStub();
		optimizerModelPreprocessor.setName("PreprocessorStub Name");
	}

	private Matrix cloneMatrix(Matrix sourceMatrix) {
		Matrix matrix = new Matrix();
		matrix.redimension(sourceMatrix.getRows(), sourceMatrix.getCols());
		for (int i = 0; i < sourceMatrix.getRows(); i++) {
			for (int j = 0; j < sourceMatrix.getCols(); j++) {
				matrix.set(i, j, sourceMatrix.get(i, j));
			}
		}

		return matrix;
	}

	private void verifyInputDataForStateModel() throws MathException {
		for (int idx = 0; idx < optimizerModel.getInputs().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getInputs().get(idx));
			if (idx < optimizerModel.getStateInput().size()) {
				Variable stateVariable = optimizerModelPreprocessor
						.getVariableFromVariableName(optimizerModel.getState().get(idx));
				assertEquals(variable.getResultValue(), sut.getValueByName(stateVariable.getName()), DELTA);
			}
		}
	}

	private void verifyInitialXMatrix() {
		for (int idx = 0; idx < optimizerModel.getInputs().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getInputs().get(idx));
			assertEquals(variable.getMeanValue(), matrixXSetAsInitX.get(0, idx), DELTA);
		}
	}

	private void verifyInitialXMatrixForStateModel() {
		int stateInputsCount = optimizerModel.getStateInput().size();

		for (int idx = 0; idx < stateInputsCount; idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getStateInput().get(idx));
			assertEquals(variable.getMeanValue(), matrixXSetAsInitX.get(0, idx), DELTA);
		}

		for (int idx = 0; idx < optimizerModel.getInputs().size() - stateInputsCount; idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getInputs().get(idx));
			assertEquals(variable.getMeanValue(), matrixXSetAsInitX.get(0, stateInputsCount + idx), DELTA);
		}
	}
}
