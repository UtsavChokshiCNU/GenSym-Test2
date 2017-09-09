package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertThat;
import static org.junit.Assert.assertTrue;
import static org.powermock.api.mockito.PowerMockito.doNothing;
import static org.powermock.api.mockito.PowerMockito.doReturn;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.mockStatic;
import static org.powermock.api.mockito.PowerMockito.verifyStatic;
import static org.powermock.api.mockito.PowerMockito.when;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Vector;

import org.hamcrest.BaseMatcher;
import org.hamcrest.Description;
import org.hamcrest.Matcher;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Matchers;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.matrix.TimeFunctions;

@RunWith(PowerMockRunner.class)
@PrepareForTest({ TimeFunctions.class })
public class NolModel2TestWithMockRunner {
	private EnsembleModel sutModel;
	private long[] createTrainingSetResponse;
	private NolModel2 sut;
	private Preprocessor sutPreprocessor;

	@Before
	public void setup() throws Exception {
		arrangeTimeFunctions();
	}

	@Test
	public void test_prepareTrainingSet_HasTimeStamps_InvokesCreateTrainingSetWithDelays() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class),
				Matchers.anyBoolean());
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSet_HasTimeStamps_InputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(vectorCaptor.capture(), Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.anyBoolean());
		Vector<Variable> inVars = vectorCaptor.getValue();
		assertThat(inVars, containsVariables(sut.getInputVarNames()));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSet_HasTimeStamps_OutputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class), vectorCaptor.capture(),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.anyBoolean());
		Vector<Variable> outVars = vectorCaptor.getValue();
		assertThat(outVars, containsVariables(sut.getOutputVarNames()));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSet_HasTimeStamps_InputDelaysArePassedToCreateTrainingSet() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), vectorCaptor.capture(), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.anyBoolean());
		Vector<long[]> delays = vectorCaptor.getValue();

		for (long[] iDelay : (Vector<long[]>) sut.getInputDelays()) {
			assertThat(delays, containsArray(iDelay));
		}
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSet_HasTimeStamps_OutputDelaysArePassedToCreateTrainingSet() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), vectorCaptor.capture(), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.anyBoolean());
		Vector<long[]> delays = vectorCaptor.getValue();

		for (long[] oDelay : (Vector<long[]>) sut.getOutputDelays()) {
			long[] oDelayWithoutZeroes = removeZeroes(oDelay);
			assertThat(delays, containsArray(oDelayWithoutZeroes));
		}
	}

	@Test
	public void test_prepareTrainingSet_HasTimeStamps_MatricesArePassedToCreateTrainingSet() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Vector.class), matrixXCaptor.capture(), matrixYCaptor.capture(), Matchers.anyBoolean());

		assertEquals(x, matrixXCaptor.getValue());
		assertEquals(y, matrixYCaptor.getValue());
	}

	@Test
	public void test_prepareTrainingSet_HasTimeStamps_ClearBadDataFlagIsTrueToCreateTrainingSet() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Boolean> booleanCaptor = ArgumentCaptor.forClass(Boolean.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class),
				booleanCaptor.capture());

		assertTrue(booleanCaptor.getValue());
	}

	@Test
	public void test_prepareTrainingSet_HasTimeStamps_ReturnsCreatedTrainingSet() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(true);

		// Act & Assert
		assertEquals(createTrainingSetResponse, sut.prepareTrainingSet(x, y));
	}

	@Test
	public void test_prepareTrainingSet_DoesNotHaveTimeStamps_InvokesCreateTrainingSetWithoutDelays()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(false);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class));
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Test
	public void test_prepareTrainingSet_DoesNotHaveTimeStamps_InputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(false);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(vectorCaptor.capture(), Matchers.any(Vector.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));
		Vector<Variable> inVars = vectorCaptor.getValue();
		assertThat(inVars, containsVariables(sut.getInputVarNames()));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSet_DoesNotHaveTimeStamps_OutputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(false);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), vectorCaptor.capture(), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));
		Vector<Variable> outVars = vectorCaptor.getValue();
		assertThat(outVars, containsVariables(sut.getOutputVarNames()));
	}

	@Test
	public void test_prepareTrainingSet_DoesNotHaveTimeStamps_MatricesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(false);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);

		// Act
		sut.prepareTrainingSet(x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class), matrixXCaptor.capture(),
				matrixYCaptor.capture());

		assertEquals(x, matrixXCaptor.getValue());
		assertEquals(y, matrixYCaptor.getValue());
	}

	@Test
	public void test_prepareTrainingSet_DoesNotHaveTimeStamps_ReturnsNull() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(false);

		// Act & Assert
		assertNull(sut.prepareTrainingSet(x, y));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_prepareTrainingSetFromDataSeries_HasTimeStamps_InvokesCreateTrainingSetWithDelays()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(true);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSetFromDataSeries_HasTimeStamps_InputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(vectorCaptor.capture(), Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		Vector<Variable> inVars = vectorCaptor.getValue();
		assertThat(inVars, containsVariables(sut.getInputVarNames()));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSetFromDataSeries_HasTimeStamps_OutputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class), vectorCaptor.capture(),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		Vector<Variable> outVars = vectorCaptor.getValue();
		assertThat(outVars, containsVariables(sut.getOutputVarNames()));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSetFromDataSeries_HasTimeStamps_InputDelaysArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), vectorCaptor.capture(), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		Vector<long[]> delays = vectorCaptor.getValue();

		for (long[] iDelay : (Vector<long[]>) sut.getInputDelays()) {
			assertThat(delays, containsArray(iDelay));
		}
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSetFromDataSeries_HasTimeStamps_OutputDelaysArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), vectorCaptor.capture(), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		Vector<long[]> delays = vectorCaptor.getValue();

		for (long[] oDelay : (Vector<long[]>) sut.getOutputDelays()) {
			long[] oDelayWithoutZeroes = removeZeroes(oDelay);
			assertThat(delays, containsArray(oDelayWithoutZeroes));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_prepareTrainingSetFromDataSeries_HasTimeStamps_MatricesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(true);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Vector.class), matrixXCaptor.capture(), matrixYCaptor.capture());

		assertEquals(x, matrixXCaptor.getValue());
		assertEquals(y, matrixYCaptor.getValue());
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_prepareTrainingSetFromDataSeries_HasTimeStamps_ReturnsCreatedTrainingSet() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(true);

		// Act & Assert
		assertEquals(createTrainingSetResponse, sut.prepareTrainingSetFromDataSeries(processedData, x, y));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_prepareTrainingSetFromDataSeries_DoesNotHaveTimeStamps_InvokesCreateTrainingSetWithoutDelays()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(false);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class));
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Test
	public void test_prepareTrainingSetFromDataSeries_DoesNotHaveTimeStamps_InputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(false);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(vectorCaptor.capture(), Matchers.any(Vector.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));
		Vector<Variable> inVars = vectorCaptor.getValue();
		assertThat(inVars, containsVariables(sut.getInputVarNames()));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Test
	public void test_prepareTrainingSetFromDataSeries_DoesNotHaveTimeStamps_OutputVariablesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(false);
		ArgumentCaptor<Vector> vectorCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), vectorCaptor.capture(), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));
		Vector<Variable> outVars = vectorCaptor.getValue();
		assertThat(outVars, containsVariables(sut.getOutputVarNames()));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_prepareTrainingSetFromDataSeries_DoesNotHaveTimeStamps_MatricesArePassedToCreateTrainingSet()
			throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());
		sut.setHasTimeStamps(false);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);

		// Act
		sut.prepareTrainingSetFromDataSeries(processedData, x, y);

		// Assert
		verifyStatic();
		TimeFunctions.createTrainingSet(Matchers.any(Vector.class), Matchers.any(Vector.class), matrixXCaptor.capture(),
				matrixYCaptor.capture());

		assertEquals(x, matrixXCaptor.getValue());
		assertEquals(y, matrixYCaptor.getValue());
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_prepareTrainingSetFromDataSeries_DoesNotHaveTimeStamps_ReturnsNull() throws MathException {
		// Arrange
		arrangeForPrepareTrainingSet();
		Matrix x = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		sut.setHasTimeStamps(false);
		Vector<DataSeries> processedData = createProcessedData(sut.getInputVarNames(), sut.getOutputVarNames());

		// Act & Assert
		assertNull(sut.prepareTrainingSetFromDataSeries(processedData, x, y));
	}

	// -- Helper Methods --

	private void arrangeForPrepareTrainingSet() {
		Vector<String> ins = createVector(new String[] { "Input 1" });
		Vector<long[]> iDelays = createVector(new long[] { 0, 1, 2 });
		Vector<String> outs = createVector(new String[] { "Output 1" });
		Vector<long[]> oDelays = createVector(new long[] { 0, 3, 4 });
		sut = createSut(ins, outs, iDelays, oDelays);
	}

	private NolModel2 createSut(Vector<String> ins, Vector<String> outs, Vector<long[]> iDelays,
			Vector<long[]> oDelays) {
		sutModel = createSutModel();
		sutPreprocessor = createPreprocessor("Sut Preprocessor Name", ins, outs);
		String name = "NolModel2 Name";

		return new NolModel2(sutModel, name, outs, ins, oDelays, iDelays, sutPreprocessor);
	}

	private Preprocessor createPreprocessor(String name) {
		Preprocessor preprocessor = mock(Preprocessor.class);
		when(preprocessor.getName()).thenReturn(name);
		return preprocessor;
	}

	private Preprocessor createPreprocessor(String name, Vector<String> ins, Vector<String> outs) {
		Preprocessor preprocessor = createPreprocessor(name);

		Vector<String> varNames = new Vector<String>();
		varNames.addAll(ins);
		varNames.addAll(outs);
		HashMap<String, Variable> variables = new HashMap<String, Variable>();
		for (String varName : varNames) {
			Variable variable = new Variable();
			variable.setName(varName);
			variables.put(varName, variable);
		}

		when(preprocessor.getVariableFromVariableName(Matchers.anyString())).thenAnswer(new Answer<Object>() {

			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				String varName = invocation.getArgumentAt(0, String.class);
				return variables.get(varName);
			}
		});

		return preprocessor;
	}

	private Vector<DataSeries> createProcessedData(Vector<String> inVarNames, Vector<String> outVarNames) {
		Vector<DataSeries> processedData = new Vector<DataSeries>();

		Vector<String> varNames = new Vector<String>();
		varNames.addAll(inVarNames);
		varNames.addAll(outVarNames);

		for (String varName : varNames) {
			Variable variable = new Variable();
			variable.setName(varName);

			DataSeries dataSeries = mock(DataSeries.class);
			when(dataSeries.getVarByName(varName)).thenReturn(variable);
			processedData.add(dataSeries);
		}

		return processedData;
	}

	private Vector<String> createVector(String[] elements) {
		Vector<String> vector = new Vector<String>();

		for (String element : elements) {
			vector.add(element);
		}

		return vector;
	}

	private Vector<long[]> createVector(long[] element) {
		Vector<long[]> vector = new Vector<long[]>();
		vector.add(element);
		return vector;
	}

	private EnsembleModel createSutModel() {
		sutModel = mock(EnsembleModel.class);
		when(sutModel.getNin()).thenReturn(10);
		when(sutModel.getNout()).thenReturn(20);

		ArchitectureParameters parameters = new ArchitectureParameters(0, 0, 0, 0);
		when(sutModel.getArchitectureParameters()).thenReturn(parameters);

		return sutModel;
	}

	private long[] removeZeroes(long[] array) {
		int j = 0;
		for (int i = 0; i < array.length; i++) {
			if (array[i] != 0)
				array[j++] = array[i];
		}

		long[] newArray = new long[j];
		System.arraycopy(array, 0, newArray, 0, j);
		return newArray;
	}

	private void arrangeTimeFunctions() throws Exception {
		mockStatic(TimeFunctions.class);

		createTrainingSetResponse = new long[] { 1001, 1002, 1003 };
		doReturn(createTrainingSetResponse).when(TimeFunctions.class, "createTrainingSet", Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Vector.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class), Matchers.anyBoolean());

		doReturn(createTrainingSetResponse).when(TimeFunctions.class, "createTrainingSet", Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Vector.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));

		doNothing().when(TimeFunctions.class, "createTrainingSet", Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class));
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	private static Matcher containsArray(final Object expected) {
		return new BaseMatcher() {
			protected long[] expectedArray = (long[]) expected;

			@Override
			public boolean matches(Object item) {
				Vector<long[]> longArrays = (Vector<long[]>) item;

				boolean containsArray = false;
				for (long[] longArray : longArrays) {
					containsArray = Arrays.equals(expectedArray, longArray);
					if (containsArray) {
						break;
					}
				}

				return containsArray;
			}

			@Override
			public void describeTo(Description description) {
				description.appendText(expectedArray.toString());
			}
		};
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	private static Matcher containsVariables(Object expected) {
		return new BaseMatcher() {
			Vector<String> inputVarNames = (Vector<String>) expected;

			@Override
			public boolean matches(Object item) {
				Vector<Variable> inVars = (Vector<Variable>) item;

				Vector<String> passedVarNames = new Vector<String>();
				for (Variable inVar : inVars) {
					passedVarNames.add(inVar.getName());
				}

				boolean containsAllVariables = true;
				for (String input : inputVarNames) {
					if (passedVarNames.contains(input) == false) {
						containsAllVariables = false;
						break;
					}
				}

				return containsAllVariables;
			}

			@Override
			public void describeTo(Description description) {
				description.appendText(inputVarNames.toString());
			}
		};
	}
}