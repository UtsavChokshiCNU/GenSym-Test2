package com.gensym.nols.deploy;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import static org.mockito.Mockito.inOrder;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.doAnswer;
import static org.powermock.api.mockito.PowerMockito.doNothing;
import static org.powermock.api.mockito.PowerMockito.spy;
import static org.powermock.api.mockito.PowerMockito.when;

import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Random;
import java.util.Vector;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.mockito.ArgumentCaptor;
import org.mockito.InOrder;
import org.mockito.Matchers;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.powermock.reflect.Whitebox;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.EnsembleModelEvent;
import com.gensym.math.datafit.EnsembleModelListener;
import com.gensym.math.datafit.Model;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.Formula2;
import com.gensym.nols.data.FormulaException;
import com.gensym.nols.data.NolModel2;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Variable;
import com.gensym.nols.data.VersionManagerForOnlineProcessor;

public class OnlineProcessorTest {
	private static final boolean ANY_BOOLEAN = false;
	private static final double BASE_VALUE = 10;
	private static final double DELTA = 0.01;
	private static final double ANY_DOUBLE = 1;
	private static final int ANY_INTEGER = 1;
	private static final int DS_FORMAT = 0;
	private static final int INITIAL_BUFFER_SIZE = 10;
	private static final int LEAST_INPUT_SAMPLES_FOR_CALCULATION = 1;
	private static final int MAX_INPUT_SAMPLES_FOR_CALCULATION = 100;
	private static final int LEAST_REQUIRED_SAMPLES = 10;
	private static final int MAX_BUFFER_SIZE = 1000;
	private static final int NAME_ROW_INDEX = 1;
	private static final int ONE_SECOND = 1000;
	private static final int TAG_ROW_INDEX = 0;
	private static final int UNIT_ROW_INDEX = 2;
	private static final String ANY_STRING = "ANY STRING";
	private static final String DEFAULT_DATE_FORMAT = "M/d/y H:m:s";
	private static final String DEFAULT_NAME = "OnlineProcessor";
	private static final String NEW_LINE = "\n";
	private static final String ONLINE_PROCESSOR_OUTPUT_DATA_NAME = "OnlinePreprocessorOutputData";
	private static final String TAB_SEPARATOR = "\t";
	private static final String TIME_TAG = "Time";
	private static final String TIME_UNIT = "Millisecond";
	private static final String VARIABLE_NEW_NAME_PREFIX = "varNewName";
	private static final String VARIABLE_NEW_TAG_PREFIX = "varNewTag";
	private static final String VARIABLE_NEW_UNIT_PREFIX = "varNewUnit";

	private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	private OnlineProcessor sut;
	private Random randomGenerator;
	private Vector<String> preprocessorProcessedInputVarNames;
	private Vector<Variable> preprocessorVariables;

	@Rule
	public TemporaryFolder temporaryFolder = new TemporaryFolder();

	@Before
	public void setup() {
		preprocessorProcessedInputVarNames = new Vector<String>();
		preprocessorVariables = new Vector<Variable>();
		randomGenerator = new Random();

		System.setOut(new PrintStream(outContent));
		System.setErr(new PrintStream(errContent));
	}

	@After
	public void cleanup() {
		System.setOut(null);
		System.setErr(null);
	}

	@Test
	public void test_instance_always_setsIncrementedName() throws MathException {
		// Arrange
		int samplesCount = 5;

		for (int idx = 0; idx < samplesCount; idx++) {
			// Act
			createSut();

			// Assert
			assertEquals(DEFAULT_NAME + idx, sut.getName());
		}
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Test
	public void test_instance_always_invokesGetInputNamesDerivedVarsFormulasForModelWithModelInputs()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();

		Vector<String> modelInputs = createNames("inVar");
		NolModel2 model = createModel((Vector<String>) modelInputs.clone(), createNames("outVar"));
		ArgumentCaptor<Vector> modelInputsCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		createSut(prep, model);

		// Assert
		verify(prep).getInputNamesDerivedVarsFormulasForModel(modelInputsCaptor.capture(), Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Vector.class));
		assertEquals(modelInputs.size(), modelInputsCaptor.getValue().size());
		for (int idx = 0; idx < modelInputs.size(); idx++) {
			assertEquals(modelInputs.get(idx), modelInputsCaptor.getValue().get(idx));
		}
	}

	@Test
	public void test_instance_always_setsInputVariablesGotFromPreprocessor() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));

		// Act
		createSut(prep, model);

		// Assert
		for (String varName : preprocessorProcessedInputVarNames) {
			DataSeries ds = sut.getDataSeriesFromVariableName(varName);

			Variable actual = ds.getVarByName(varName);
			Variable expected = prep.getVariableFromVariableName(varName);
			assertThatVariablesAreSame(expected, actual);
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_instance_modelIsRecursive_setsDataAsNaN() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);

		// Act
		createSut(prep, model);

		for (String varName : (Vector<String>) model.getOutputVarNames()) {
			// Assert
			assertEquals(Double.NaN, sut.getCurrentOutputByName(varName), DELTA);
		}
	}

	@Test
	public void test_setName_always_updatesProcessorName() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(), createModel());
		String name = "New Preprocessor Name";

		// Act
		sut.setName(name);

		// Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_setComment_always_updatesProcessorComment() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(), createModel());
		String comment = "New Preprocessor Comment";

		// Act
		sut.setComment(comment);

		// Assert
		assertEquals(comment, sut.getComment());
	}

	@Test
	public void test_getHasTimeStamps_hasTimeStamps_returnsTrue() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act & Assert
		assertTrue(sut.getHasTimeStamps());
	}

	@Test
	public void test_getHasTimeStamps_doesNotHaveTimeStamps_returnsFalse() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act & Assert
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_hasTimeStamps_hasTimeStamps_returnsTrue() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act & Assert
		assertTrue(sut.hasTimeStamps());
	}

	@Test
	public void test_hasTimeStamps_doesNotHaveTimeStamps_returnsFalse() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act & Assert
		assertFalse(sut.hasTimeStamps());
	}

	@Test
	public void test_getItsHashCode_always_returnsHashCode() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(), createModel());

		// Act & Assert
		assertEquals(sut.hashCode(), sut.getItsHashCode());
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getVariableNames_always_containsInputVariableNames() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));

		createSut(prep, model);

		// Act
		Vector<String> result = sut.getVariableNames();

		// Assert
		for (String varName : preprocessorProcessedInputVarNames) {
			assertTrue(result.contains(varName));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getVariableNames_always_containsOutputVariableNames() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		Vector<String> result = sut.getVariableNames();

		// Assert
		for (String varName : (Vector<String>) model.getOutputVarNames()) {
			assertTrue(result.contains(varName));
		}
	}

	@Test
	public void test_getNumberOfVariables_always_returnsInputAndOutputVariablesCount()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		assertEquals(preprocessorProcessedInputVarNames.size() + model.getOutputVarNames().size(),
				sut.getNumberOfVariables());
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getVariableTags_always_containsInputVariableTags() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		Vector<String> result = sut.getVariableTags();

		// Assert
		for (String varName : preprocessorProcessedInputVarNames) {
			Variable variable = prep.getVariableFromVariableName(varName);
			assertTrue(result.contains(variable.getTag()));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getVariableTags_always_containsOutputVariableTags() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		Vector<String> result = sut.getVariableTags();

		// Assert
		for (String varName : (Vector<String>) model.getOutputVarNames()) {
			Variable variable = prep.getVariableFromVariableName(varName);
			assertTrue(result.contains(variable.getTag()));
		}
	}

	@Test
	public void test_getDataSeriesFromVariableName_validInputVarNameIsPassed_returnsDataSeries()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (String varName : preprocessorProcessedInputVarNames) {
			// Act
			DataSeries result = sut.getDataSeriesFromVariableName(varName);

			// Assert
			assertNotNull(result);
			Variable actual = result.getVarByName(varName);
			Variable expected = prep.getVariableFromVariableName(varName);
			assertThatVariablesAreSame(expected, actual);
		}
	}

	@Test
	public void test_getDataSeriesFromVariableName_validInputVarNameIsNotPassed_returnsDataSeries()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act & Assert
		assertNull(sut.getDataSeriesFromVariableName(ANY_STRING));
	}

	@Test
	public void test_loadModel_always_copiesOnlineProcessor()
			throws MathException, IOException, ClassNotFoundException, FormulaException {
		// Arrange
		createSut(createPreprocessor(), createModel());
		VersionManagerForOnlineProcessor versionManager = createVersionManagerForOnlineProcessor();
		File file = createOnlineProcessorObjectFile(versionManager);

		// Act
		sut.loadModel(file.getName(), file.getAbsolutePath().replace(file.getName(), ""));

		// Assert
		assertEquals(versionManager.getProcessor().getName(), sut.getName());
		assertEquals(versionManager.getProcessor().getComment(), sut.getComment());
	}

	@Test
	public void test_loadModelWithoutDirectory_always_copiesOnlineProcessor()
			throws MathException, IOException, ClassNotFoundException, FormulaException {
		// Arrange
		createSut(createPreprocessor(), createModel());
		VersionManagerForOnlineProcessor versionManager = createVersionManagerForOnlineProcessor();
		File file = createOnlineProcessorObjectFile(versionManager, false);

		// Act
		sut.loadModel(file.getAbsolutePath());

		// Assert
		assertEquals(versionManager.getProcessor().getName(), sut.getName());
		assertEquals(versionManager.getProcessor().getComment(), sut.getComment());
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_calculateOutputAtTime_doesNotHaveTimeStamps_throwsMathException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		sut.calculateOutputAtTime(ANY_STRING);
	}

	@Test
	public void test_calculateOutputAtTime_isRecursiveModelAndInvalidTimeStringIsPassed_writesExceptionToOutput()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.calculateOutputAtTime(ANY_STRING);

		// Assert
		assertTrue(outContent.toString().contains("Exception is Unparseable date: \"" + ANY_STRING + "\""));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_calculateOutputAtTime_isRecursiveModel_appliesFormula() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);

		// Act
		sut.calculateOutputAtTime(dateFormat.format(Calendar.getInstance().getTime()));

		// Assert
		for (Formula2 formula : (Vector<Formula2>) prep.getFormulas()) {
			verify(formula).applyFormula(Matchers.any(Vector.class));
		}
	}

	@Test
	public void test_calculateOutputAtTime_isRecursiveModel_setsResultToOutputs()
			throws MathException, FormulaException, ParseException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		Vector<DataSeries> processedData = attachApplyFormula(prep);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		// Act
		sut.calculateOutputAtTime(time);

		// Assert
		DataSeries outputDataSeries = getOutputDataSeries(processedData);
		assertNotNull(outputDataSeries);
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			assertEquals(outputDataSeries.getDataMatrix().get(INITIAL_BUFFER_SIZE - 1, idx),
					sut.getOutputAtTimeByIndex(idx, time), DELTA);
		}
	}

	@Test
	public void test_calculateOutputAtTime_initialBufferSizeIsReached_extendsBuffer()
			throws MathException, FormulaException, ParseException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		attachApplyFormula(prep);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		long baseTime = System.currentTimeMillis();

		for (int idx = 0; idx < INITIAL_BUFFER_SIZE; idx++) {
			sut.calculateOutputAtTime(dateFormat.format(baseTime + ((idx + 1) * ONE_SECOND)));
		}

		// Act
		sut.calculateOutputAtTime(dateFormat.format(baseTime));

		// Assert
		DataSeries outputDataSeries = (DataSeries) Whitebox.getInternalState(sut, "outputData");
		assertNotNull(outputDataSeries);
		assertEquals(INITIAL_BUFFER_SIZE * 2, outputDataSeries.getTimeStamps().length);
	}

	@Test
	public void test_calculateOutputAtTime_maxBufferSizeIsReached_stopsExtendingBufferSize()
			throws MathException, FormulaException, ParseException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		attachApplyFormula(prep);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		long baseTime = System.currentTimeMillis();

		for (int idx = 0; idx < MAX_BUFFER_SIZE; idx++) {
			sut.calculateOutputAtTime(dateFormat.format(baseTime + ((idx + 1) * ONE_SECOND)));
		}

		// Act
		sut.calculateOutputAtTime(dateFormat.format(baseTime));

		// Assert
		DataSeries outputDataSeries = (DataSeries) Whitebox.getInternalState(sut, "outputData");

		assertNotNull(outputDataSeries);
		assertEquals(MAX_BUFFER_SIZE, outputDataSeries.getTimeStamps().length);
	}

	@Test
	public void test_calculateOutputAtTime_isNotRecursiveModelAndInvalidTimeStringIsPassed_writesExceptionToOutput()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), false);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.calculateOutputAtTime(ANY_STRING);

		// Assert
		assertTrue(outContent.toString().contains("Exception is Unparseable date: \"" + ANY_STRING + "\""));
	}

	@Test
	public void test_calculateOutputAtTime_isNotRecursiveModel_setsResultToOutputs()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), false);
		arrangePreprocessorFormulaModel(prep, model);
		Vector<DataSeries> processedData = attachApplyFormula(prep);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		// Act
		sut.calculateOutputAtTime(time);

		// Assert
		DataSeries outputDataSeries = getOutputDataSeries(processedData);
		assertNotNull(outputDataSeries);
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			assertEquals(outputDataSeries.getDataMatrix().get(0, idx), sut.getOutputAtTimeByIndex(idx, time), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_calculateOutputForRow_hasTimeStamps_throwsMatchException() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), false);
		createSut(prep, model);

		// Act
		sut.calculateOutputForRow();
	}

	@Test
	public void test_calculateOutputForRow_doesNotHaveTimeStamps_setsResultToOutputs()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		Vector<DataSeries> processedData = attachApplyFormula(prep);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act
		sut.calculateOutputForRow();

		// Assert
		int baseIndex = model.getInputVarNames().size();
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			assertEquals(processedData.firstElement().getDataMatrix().get(0, baseIndex + idx),
					sut.getCurrentOutputByIndex(idx), DELTA);
		}
	}

	@Test
	public void test_calculateOutputForRow_applyFormulaThrowsException_writesExceptionMessageToOutput()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		Exception exception = new Exception("Failed to apply formula.");
		attachApplyFormula(prep, exception);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act
		sut.calculateOutputForRow();

		// Assert
		assertTrue(outContent.toString().contains("Exception is " + exception.getMessage()));
	}

	@Test
	public void test_getNumberOfInputs_always_returnModelInputsCount() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act & Assert
		assertEquals(model.getInputVarNames().size(), sut.getNumberOfInputs());
	}

	@Test
	public void test_getInputName_always_returnsInputVarName() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			// Act & Assert
			assertEquals(preprocessorProcessedInputVarNames.get(idx), sut.getInputName(idx));
		}
	}

	@Test
	public void test_getInputNames_always_returnsInputVarNames() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act
		String[] result = sut.getInputNames();

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			// Assert
			assertEquals(preprocessorProcessedInputVarNames.get(idx), result[idx]);
		}
	}

	@Test
	public void test_getInputTag_always_returnsInputVarTag() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			// Act & Assert
			assertEquals(variable.getTag(), sut.getInputTag(idx));
		}
	}

	@Test
	public void test_getInputTags_always_returnsInputVarTags() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act
		String[] result = sut.getInputTags();

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			// Assert
			assertEquals(variable.getTag(), result[idx]);
		}
	}

	@Test
	public void test_getNumberOfOutputs_always_returnsNumberOfOutputVars() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act & Assert
		assertEquals(model.getOutputVarNames().size(), sut.getNumberOfOutputs());
	}

	@Test
	public void test_getOutputName_always_returnsOutputVarNameAtCurrentIndex() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			// Act & Assert
			assertEquals(model.getOutputVarNames().get(idx), sut.getOutputName(idx));
		}
	}

	@Test
	public void test_getOutputNames_always_returnsOutputVarNames() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act
		String[] result = sut.getOutputNames();

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			// Assert
			assertEquals(model.getOutputVarNames().get(idx), result[idx]);
		}
	}

	@Test
	public void test_getOutputTag_always_returnsOutputVarTag() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));

			// Act & Assert
			assertEquals(variable.getTag(), sut.getOutputTag(idx));
		}
	}

	@Test
	public void test_getOutputTags_always_returnsOutputVarTags() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);

		// Act
		String[] result = sut.getOutputTags();

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));

			// Assert
			assertEquals(variable.getTag(), result[idx]);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setTimeFormat_doesNotHaveTimeStamps_throwsMathException() throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(), createModel());
		String timeFormat = "M/d/y H:m:s";

		// Act
		sut.setTimeFormat(timeFormat);
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_setTimeFormat_hasTimeStamps_setsDateTime() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		String timeFormat = "dd-MMM-yyyy H:m:s";
		SimpleDateFormat dateFormat = new SimpleDateFormat(timeFormat);

		// Act
		sut.setTimeFormat(timeFormat);

		// Assert
		sut.calculateOutputAtTime(dateFormat.format(Calendar.getInstance().getTime()));
		for (Formula2 formula : (Vector<Formula2>) prep.getFormulas()) {
			verify(formula).applyFormula(Matchers.any(Vector.class));
		}
	}

	@Test
	public void test_setDecimalFormatLocalString_always_setsDecimalFormatLocalString()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(), createModel());
		String form = "EN-US";

		// Act
		sut.setDecimalFormatLocalString(form);

		// Assert
		assertEquals(form, Whitebox.getInternalState(sut, "decFormatLocalString"));
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setInputAtTimeByIndex_doesNotHaveTimeStamps_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(), createModel());

		// Act
		sut.setInputAtTimeByIndex(ANY_INTEGER, ANY_DOUBLE, ANY_STRING);
	}

	@Test
	public void test_setInputAtTimeByIndex_hasTimeStamps_setsInput()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(true), createModel());
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (idx + 1);

			// Act
			sut.setInputAtTimeByIndex(idx, value, time);

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(value, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, 0), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setInputAtTimeByTag_doesNotHaveTimeStamps_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(), createModel());

		// Act
		sut.setInputAtTimeByTag(ANY_STRING, ANY_DOUBLE, ANY_STRING);
	}

	@Test
	public void test_setInputAtTimeByTag_hasTimeStamps_setsInput()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		createSut(prep, createModel());
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			double value = BASE_VALUE * (idx + 1);

			// Act
			sut.setInputAtTimeByTag(variable.getTag(), value, time);

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(value, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, 0), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setInputAtTimeByName_doesNotHaveTimeStamps_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(), createModel());

		// Act
		sut.setInputAtTimeByName(ANY_STRING, ANY_DOUBLE, ANY_STRING);
	}

	@Test
	public void test_setInputAtTimeByName_hasTimeStamps_setsInput()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		createSut(prep, createModel());
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (idx + 1);

			// Act
			sut.setInputAtTimeByName(preprocessorProcessedInputVarNames.get(idx), value, time);

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(value, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, 0), DELTA);
		}
	}

	@Test
	public void test_setInputAtTimeByName_samplesAreAddedOnSameTimeStamp_doesNotExtendsBuffer()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		createSut(prep, createModel());
		long baseTime = System.currentTimeMillis();
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);

		// Adding samples equal to initial buffer size
		addInitialBufferSizeSamples(baseTime, dateFormat);

		// Adding one more sample for each variable, after buffer is full.
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * idx + 1;

			// Act
			sut.setInputAtTimeByName(preprocessorProcessedInputVarNames.get(idx), value, dateFormat.format(baseTime));

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(INITIAL_BUFFER_SIZE, dataSeries.getTimeStamps().length);
		}
	}

	@Test
	public void test_setInputAtTimeByName_initialBufferSizeIsReached_extendsBuffer()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		createSut(prep, createModel());
		long baseTime = System.currentTimeMillis();
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);

		// Adding samples equal to initial buffer size
		addInitialBufferSizeSamples(baseTime, dateFormat);

		// Adding one more sample for each variable, after buffer is full.
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (INITIAL_BUFFER_SIZE + idx + 1);

			// Act
			sut.setInputAtTimeByName(preprocessorProcessedInputVarNames.get(idx), value,
					dateFormat.format(baseTime - ONE_SECOND));

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(INITIAL_BUFFER_SIZE * 2, dataSeries.getTimeStamps().length);
			assertEquals(value, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, 0), DELTA);
		}
	}

	@Test
	public void test_setInputAtTimeByName_maxBufferSizeIsReached_stopsExtendingBufferSize()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		createSut(prep, createModel());
		long baseTime = System.currentTimeMillis();
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);

		addMaxBufferSizeSamples(baseTime, dateFormat);

		// Adding one more sample for each variable, after buffer reaches max
		// buffer size.
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (MAX_BUFFER_SIZE + idx + 1);

			// Act
			sut.setInputAtTimeByName(preprocessorProcessedInputVarNames.get(idx), value,
					dateFormat.format(baseTime - (MAX_BUFFER_SIZE * ONE_SECOND)));

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(MAX_BUFFER_SIZE, dataSeries.getTimeStamps().length);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setInputForRowByIndex_hasTimeStamps_throwsException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.setInputForRowByIndex(ANY_INTEGER, ANY_DOUBLE);
	}

	@Test
	public void test_setInputForRowByIndex_hasTimeStamps_setsInput()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(false), createModel(createNames("inVar"), createNames("outVar")));

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (idx + 1);

			// Act
			sut.setInputForRowByIndex(idx, value);

			// Assert
			DataSeries dataSeries = Whitebox.getInternalState(sut, "rowBasedInputData");
			int varIndex = dataSeries.getVarIndexByName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(value, dataSeries.getValueAt(0, varIndex), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setInputForRowByTag_hasTimeStamps_throwsException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.setInputForRowByTag(ANY_STRING, ANY_DOUBLE);
	}

	@Test
	public void test_setInputForRowByTag_hasTimeStamps_setsInput()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		createSut(prep, createModel(createNames("inVar"), createNames("outVar")));

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (idx + 1);
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			// Act
			sut.setInputForRowByTag(variable.getTag(), value);

			// Assert
			DataSeries dataSeries = Whitebox.getInternalState(sut, "rowBasedInputData");
			int varIndex = dataSeries.getVarIndexByTag(variable.getTag());
			assertEquals(value, dataSeries.getValueAt(0, varIndex), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setInputForRowByName_hasTimeStamps_throwsException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.setInputForRowByName(ANY_STRING, ANY_DOUBLE);
	}

	@Test
	public void test_setInputForRowByName_hasTimeStamps_setsInput()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		createSut(prep, createModel(createNames("inVar"), createNames("outVar")));

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (idx + 1);

			// Act
			sut.setInputForRowByName(preprocessorProcessedInputVarNames.get(idx), value);

			// Assert
			DataSeries dataSeries = Whitebox.getInternalState(sut, "rowBasedInputData");
			int varIndex = dataSeries.getVarIndexByName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(value, dataSeries.getValueAt(0, varIndex), DELTA);
		}
	}

	@Test(expected = MathException.class)
	public void test_setInputForRowByName_wrongVariableNameIsPassed_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(false), createModel(createNames("inVar"), createNames("outVar")));

		// Act
		sut.setInputForRowByName(ANY_STRING, ANY_DOUBLE);
	}

	@Test
	public void test_getCurrentOutputByTag_always_returnsCalculatedOutput() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		Vector<DataSeries> processedData = attachApplyFormula(prep);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		createSut(prep, model);
		sut.calculateOutputForRow();

		// Act & Assert
		int baseIndex = model.getInputVarNames().size();
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			assertEquals(processedData.firstElement().getDataMatrix().get(0, baseIndex + idx),
					sut.getCurrentOutputByIndex(idx), DELTA);
		}
	}

	@Test
	public void test_getOutputAtTimeByName_always_returnsCalculatedOutput()
			throws MathException, FormulaException, ParseException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		Vector<DataSeries> processedData = attachApplyFormula(prep);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());
		sut.calculateOutputAtTime(time);
		DataSeries outputDataSeries = getOutputDataSeries(processedData);

		// Act & Assert
		assertNotNull(outputDataSeries);
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			assertEquals(outputDataSeries.getDataMatrix().get(INITIAL_BUFFER_SIZE - 1, idx),
					sut.getOutputAtTimeByName((String) model.getOutputVarNames().get(idx), time), DELTA);
		}
	}

	@Test
	public void test_getOutputAtTimeByTag_always_returnsCalculatedOutput()
			throws MathException, FormulaException, ParseException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		Vector<DataSeries> processedData = attachApplyFormula(prep);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());
		sut.calculateOutputAtTime(time);
		DataSeries outputDataSeries = getOutputDataSeries(processedData);

		// Act & Assert
		assertNotNull(outputDataSeries);
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(outputDataSeries.getDataMatrix().get(INITIAL_BUFFER_SIZE - 1, idx),
					sut.getOutputAtTimeByTag(variable.getTag(), time), DELTA);
		}
	}

	@Test
	public void test_getMaxValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMaxValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getMinValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMinValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getMeanValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMeanValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getMedianValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMedianValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getSumValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getSumValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getSTDValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getSTDValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getVarianceValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getVarianceValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getKurtValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getKurtValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getSkewValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getSkewValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getRangeValueByName_hasTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getRangeValueByTag_hasTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getMaxValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMaxValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMaxValue(), sut.getMaxValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getMinValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMinValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMinValue(), sut.getMinValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getMeanValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMeanValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMeanValue(), sut.getMeanValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getMedianValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getMedianValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getMedianValue(), sut.getMedianValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getSumValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getSumValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSum(), sut.getSumValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getSTDValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getSTDValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSTD(), sut.getSTDValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getVarianceValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getVarianceValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getVariance(), sut.getVarianceValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getKurtValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getKurtValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getKurt(), sut.getKurtValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getSkewValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getSkewValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getSkew(), sut.getSkewValueByTag(variable.getTag()), DELTA);
		}
	}

	@Test
	public void test_getRangeValueByName_doesNotHaveTimeStampsAndVariableNameExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByName(variable.getName()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByName(variable.getName()), DELTA);
		}
	}

	@Test
	public void test_getRangeValueByTag_doesNotHaveTimeStampsAndVariableTagExists_returnsValue()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(false);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByTag(variable.getTag()), DELTA);
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			assertEquals(variable.getRange(), sut.getRangeValueByTag(variable.getTag()), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMaxValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getMaxValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMinValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getMinValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMeanValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getMeanValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMedianValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getMedianValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSumValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getSumValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSTDValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getSumValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getVarianceValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getVarianceValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getKurtValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getKurtValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSkewValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getSkewValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getRangeValueByName_hasTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(true), createModel());

		// Act
		sut.getRangeValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMaxValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getMaxValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMinValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getMinValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMeanValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getMeanValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMedianValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getMedianValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSumValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getSumValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSTDValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getSumValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getVarianceValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getVarianceValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getKurtValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getKurtValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSkewValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getSkewValueByName(ANY_STRING);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getRangeValueByName_doesNotHaveTimeStampsAndVariableNameDoesNotExist_throwsException()
			throws MathException, FormulaException {
		// Arrange
		createSut(createPreprocessor(false), createModel());

		// Act
		sut.getRangeValueByName(ANY_STRING);
	}

	@Test
	public void test_getInputDelayByName_variableNameIsValid_returnsDelay() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		for (int idx = 0; idx < formulaModel.getInputVarNames().size(); idx++) {
			// Act & Assert
			assertEquals(model.getInputDelays().get(idx),
					sut.getInputDelayByName((String) formulaModel.getInputVarNames().get(idx)));
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getInputDelayByName_variableNameIsNotValid_throwsException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.getInputDelayByName(ANY_STRING);
	}

	@Test
	public void test_getInputDelayByTag_always_returnsDelay() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			// Act & Assert
			assertEquals(model.getInputDelays().get(idx), sut.getInputDelayByTag(variable.getTag()));
		}
	}

	@Test
	public void test_getFormulas_always_returnsFormulasList() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		for (int idx = 0; idx < prep.getFormulas().size(); idx++) {
			// Act & Assert
			assertTrue(sut.getFormulas().contains(prep.getFormulas().get(idx).toString() + "\n"));
		}
	}

	@Test
	public void test_clearDataBuffer_always_setsValuesAsNaN() throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(true), createModel(createNames("inVar"), createNames("outVar")));
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			sut.setInputAtTimeByIndex(idx, BASE_VALUE * (idx + 1), time);
		}

		// Act
		sut.clearDataBuffer();

		// Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(Double.NaN, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, 0), DELTA);
		}
	}

	@Test
	public void test_getNumberOfModelInputs_always_returnsEnsembleModelInputs() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel();
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		assertEquals(((EnsembleModel) formulaModel.getModel()).getNin(), sut.getNumberOfModelInputs());
	}

	@Test
	public void test_getNumberOfModelOutputs_always_returnsEnsembleModelOutputs()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel();
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act & Assert
		assertEquals(((EnsembleModel) formulaModel.getModel()).getNout(), sut.getNumberOfModelOutputs());
	}

	@Test
	public void test_updateMaxAndMinValues_isNewTraining_updatesInputVariablesMinimumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		sut.updateMaxAndMinValues(createMatrix(model.getInputVarNames().size(), ANY_DOUBLE),
				createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), true);

		// Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			assertEquals(ANY_DOUBLE, variable.getMinValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNewTraining_updatesOutputVariablesMinimumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), ANY_DOUBLE),
				createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), true);

		// Assert
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));

			assertEquals(ANY_DOUBLE, variable.getMinValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsGreaterThanExisting_doesNotUpdateInputVariablesMinimumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			double existingMinValue = variable.getMinValue();

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), existingMinValue + 0.1),
					createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), false);

			// Assert
			assertEquals(existingMinValue, variable.getMinValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsLessThanExisting_updatesInputVariablesMinimumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			double minValue = variable.getMinValue() - 0.1;

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), minValue),
					createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), false);

			// Assert
			assertEquals(minValue, variable.getMinValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsGreaterThanExisting_doesNotUpdateOutputVariablesMinimumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			double existingMinValue = variable.getMinValue();

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), ANY_DOUBLE),
					createMatrix(model.getOutputVarNames().size(), existingMinValue + 0.1), false);

			// Assert
			assertEquals(existingMinValue, variable.getMinValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsLessThanExisting_updatesOutputVariablesMinimumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			double minValue = variable.getMinValue() - 0.1;

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), ANY_DOUBLE),
					createMatrix(model.getOutputVarNames().size(), minValue), false);

			// Assert
			assertEquals(minValue, variable.getMinValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNewTraining_updatesInputVariablesMaximumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		sut.updateMaxAndMinValues(createMatrix(model.getInputVarNames().size(), ANY_DOUBLE),
				createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), true);

		// Assert
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			assertEquals(ANY_DOUBLE, variable.getMaxValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNewTraining_updatesOutputVariablesMaximumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), ANY_DOUBLE),
				createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), true);

		// Assert
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));

			assertEquals(ANY_DOUBLE, variable.getMaxValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsLessThanExisting_doesNotUpdateInputVariablesMaximumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			double existingMaxValue = variable.getMaxValue();

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), existingMaxValue - 0.1),
					createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), false);

			// Assert
			assertEquals(existingMaxValue, variable.getMaxValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsGreaterThanExisting_updatesInputVariablesMaximumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			double maxValue = variable.getMaxValue() + 1;

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), maxValue),
					createMatrix(model.getOutputVarNames().size(), ANY_DOUBLE), false);

			// Assert
			assertEquals(maxValue, variable.getMaxValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsGreaterThanExisting_doesNotUpdateOutputVariablesMaximumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			double existingMaxValue = variable.getMaxValue();

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), ANY_DOUBLE),
					createMatrix(model.getOutputVarNames().size(), existingMaxValue - 0.1), false);

			// Assert
			assertEquals(existingMaxValue, variable.getMaxValue(), DELTA);
		}
	}

	@Test
	public void test_updateMaxAndMinValues_isNotNewTrainingAndNewValueIsGreaterThanExisting_updatesOutputVariablesMaximumStatistics()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));
			double maxValue = variable.getMaxValue() + 0.1;

			// Act
			sut.updateMaxAndMinValues(createMatrix(preprocessorProcessedInputVarNames.size(), ANY_DOUBLE),
					createMatrix(model.getOutputVarNames().size(), maxValue), false);

			// Assert
			assertEquals(maxValue, variable.getMaxValue(), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainModel_inputAndOutputDoesNotHaveSameNumberOfSamples_throwsMathException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES + 1, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES + 2, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainModel_dataIsNotEnoughForTraining_throwsMathException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES - 1, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES - 1, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainModel_inputMatrixDoesNotMatchModelInput_throwsMathException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin() + 1),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainModel_outputMatrixDoesNotMatchModelOutput_throwsMathException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout() + 1), trainingTime, useAutoStopping,
				newTraining, display);
	}

	@Test
	public void test_trainModel_isNewTraining_invokesClearModels()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = true, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		verify(ensembleModel).clearModels();
	}

	@Test
	public void test_trainModel_isNotNewTraining_doesNotInvokesClearModels()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = false, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		verify(ensembleModel, times(0)).clearModels();
	}

	@Test
	public void test_trainModel_always_setsTrainingTime() throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		verify(ensembleModel).setTrainingTime((long) trainingTime);
	}

	@Test
	public void test_trainModel_isAutoStop_setsUseAutomcaticStopping()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = true, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		verify(ensembleModel).useAutomaticStopping(true);
	}

	@Test
	public void test_trainModel_isNotAutoStop_resetsUseAutomcaticStopping()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = false, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		verify(ensembleModel).useAutomaticStopping(false);
	}

	@Test
	public void test_trainModel_always_addsSutToEnsembleListeners()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		double trainingTime = System.currentTimeMillis();
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model, (long) trainingTime);
		createSut(prep, model);
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.trainModel(createModelListeners(), createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		InOrder inOrder = inOrder(ensembleModel);
		inOrder.verify(ensembleModel).removeAllListeners();
		inOrder.verify(ensembleModel).addListener(sut);
	}

	@Test
	public void test_trainModel_passedModelListenerIsOnlineModelListener_createsNewOnlineModelListener()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		double trainingTime = System.currentTimeMillis();
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model, (long) trainingTime);
		createSut(prep, model);
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = true;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		Vector<OnlineModelListener> modelListeners = createOnlineModelListeners();
		Matrix matrixX = createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin());
		Matrix matrixY = createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout());

		// Act
		sut.trainModel(modelListeners, matrixX, matrixY, trainingTime, useAutoStopping, newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		verify(ensembleModel).addListener(modelListeners.firstElement());
		verifyConsoleConfiguration(modelListeners.firstElement(), matrixX, matrixY);
	}

	@Test
	public void test_trainModel_passedModelListenerIsNotOnlineModelListener_createsNewOnlineModelListener()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = true;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		Vector<EnsembleModelListener> modelListeners = createModelListeners();
		Matrix matrixX = createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin());
		Matrix matrixY = createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout());
		// 1 SUT, 1 passed EnsembleModelListener and 1 new instance of
		// OnlineModelListener
		int expectedAddedListeners = 3;

		// Act
		sut.trainModel(modelListeners, matrixX, matrixY, trainingTime, useAutoStopping, newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel, times(expectedAddedListeners)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor.getValue());
	}

	@Test
	public void test_trainModel_modelListenerIsNotPassed_createsNewOnlineModelListener()
			throws MathException, FormulaException, InterruptedException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		double trainingTime = System.currentTimeMillis();
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model, (long) trainingTime);
		createSut(prep, model);
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = true;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		// 1 SUT and 1 new instance of OnlineModelListener
		int expectedAddedListeners = 2;

		// Act
		sut.trainModel(null, createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNin()),
				createMatrix(LEAST_REQUIRED_SAMPLES, ensembleModel.getNout()), trainingTime, useAutoStopping,
				newTraining, display);

		// Let the training thread be started
		Thread.sleep(10);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel, times(expectedAddedListeners)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor.getValue());
	}

	@Test
	public void test_trainModelFromFile_always_invokesTrainModel() throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		OnlineProcessor sutSpy = spy(sut);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		Matrix matrixX = createMatrix(LEAST_REQUIRED_SAMPLES + 1, ensembleModel.getNin());
		Matrix matrixY = createMatrix(LEAST_REQUIRED_SAMPLES + 2, ensembleModel.getNout());
		Vector<EnsembleModelListener> modelListeners = createModelListeners();
		doNothing().when(sutSpy).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(),
				Matchers.anyBoolean());

		// Act
		sutSpy.trainModelFromFile(modelListeners, createFile(matrixX), createFile(matrixY), trainingTime,
				useAutoStopping, newTraining, display);

		// Assert
		verifyTrainModelIsInvoked(sutSpy, modelListeners, matrixX, matrixY, trainingTime, useAutoStopping, newTraining,
				display);
	}

	@Test
	public void test_trainModelFromFileWithDataSeriesFileNames_always_invokesTrainModel()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);

		createSut(prep, model);
		OnlineProcessor sutSpy = spy(sut);
		int rows = LEAST_REQUIRED_SAMPLES;
		DataSeries[] dataSeries = new DataSeries[] { new DataSeries(rows, model.getInputs().size()),
				new DataSeries(rows, model.getInputs().size()) };
		String[] dataSeriesFileNames = createDsFiles(dataSeries);
		double trainingTime = System.currentTimeMillis();
		boolean useAutoStopping = ANY_BOOLEAN, newTraining = ANY_BOOLEAN, display = ANY_BOOLEAN;
		Vector<EnsembleModelListener> modelListeners = createModelListeners();
		doNothing().when(sutSpy).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(),
				Matchers.anyBoolean());

		// Act
		sutSpy.trainModelFromFile(modelListeners, dataSeriesFileNames, trainingTime, useAutoStopping, newTraining,
				display);

		// Assert
		verifyTrainModelIsInvoked(sutSpy, modelListeners, Matlib.createMatrix(), Matlib.createMatrix(), trainingTime,
				useAutoStopping, newTraining, display, formulaModel);
	}

	@Test
	public void test_completeTraining_always_calculatesModelRate() throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		createSut(prep, model);

		// Act
		sut.completeTraining();

		// Assert
		assertEquals(calculateModelRate(ensembleModel), sut.getModelRate(), DELTA);
	}

	@Test
	public void test_completeTraining_always_calculatesTestRmse() throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		createSut(prep, model);

		// Act
		sut.completeTraining();

		// Assert
		assertEquals(ensembleModel.getNout(), sut.getTestRmse().length);
		for (int idx = 0; idx < calculateTestRmse(ensembleModel).length; idx++) {
			assertEquals(calculateTestRmse(ensembleModel)[idx], sut.getTestRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_completeTraining_always_calculatesTrainingRmse()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		createSut(prep, model);

		// Act
		sut.completeTraining();

		// Assert
		assertEquals(ensembleModel.getNout(), sut.getTrainingRmse().length);
		for (int idx = 0; idx < calculateTrainingRmse(ensembleModel).length; idx++) {
			assertEquals(calculateTrainingRmse(ensembleModel)[idx], sut.getTrainingRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_completeTraining_always_calculatesTestCorr() throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		createSut(prep, model);

		// Act
		sut.completeTraining();

		// Assert
		assertEquals(ensembleModel.getNout(), sut.getTestCorr().length);
		for (int idx = 0; idx < calculateTestCorr(ensembleModel).length; idx++) {
			assertEquals(calculateTestCorr(ensembleModel)[idx], sut.getTestCorr()[idx], DELTA);
		}
	}

	@Test
	public void test_completeTraining_always_calculatesTrainingCorr()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		createSut(prep, model);

		// Act
		sut.completeTraining();

		// Assert
		assertEquals(ensembleModel.getNout(), sut.getTrainingCorr().length);
		for (int idx = 0; idx < calculateTrainingCorr(ensembleModel).length; idx++) {
			assertEquals(calculateTrainingCorr(ensembleModel)[idx], sut.getTrainingCorr()[idx], DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getModelRate_isNotTrained_throwsMathException()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.getModelRate();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getTestRmse_isNotTrained_throwsMathException()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.getTestRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getTrainingRmse_isNotTrained_throwsMathException()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.getTrainingRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getTestCorr_isNotTrained_throwsMathException()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.getTestCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getTrainingCorr_isNotTrained_throwsMathException()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.getTrainingCorr();
	}

	@Test
	public void test_trainingComplete_always_calculatesModelRate() throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		long trainingTime = System.currentTimeMillis();
		EnsembleModelEvent e = createEnsembleModelEvent(model, trainingTime);
		createSut(prep, model);

		// Act
		sut.trainingComplete(e);

		// Assert
		assertEquals(calculateModelRate(e.getEnsembleModel()), sut.getModelRate(), DELTA);
	}

	@Test
	public void test_trainingComplete_always_calculatesTestRmse() throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		long trainingTime = System.currentTimeMillis();
		EnsembleModelEvent e = createEnsembleModelEvent(model, trainingTime);
		createSut(prep, model);

		// Act
		sut.trainingComplete(e);

		// Assert
		assertEquals(e.getEnsembleModel().getNout(), sut.getTestRmse().length);
		for (int idx = 0; idx < calculateTestRmse(e.getEnsembleModel()).length; idx++) {
			assertEquals(calculateTestRmse(e.getEnsembleModel())[idx], sut.getTestRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_always_calculatesTrainingRmse()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		long trainingTime = System.currentTimeMillis();
		EnsembleModelEvent e = createEnsembleModelEvent(model, trainingTime);
		createSut(prep, model);

		// Act
		sut.trainingComplete(e);

		// Assert
		assertEquals(e.getEnsembleModel().getNout(), sut.getTrainingRmse().length);
		for (int idx = 0; idx < calculateTrainingRmse(e.getEnsembleModel()).length; idx++) {
			assertEquals(calculateTrainingRmse(e.getEnsembleModel())[idx], sut.getTrainingRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_always_calculatesTestCorr() throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		long trainingTime = System.currentTimeMillis();
		EnsembleModelEvent e = createEnsembleModelEvent(model, trainingTime);
		createSut(prep, model);

		// Act
		sut.trainingComplete(e);

		// Assert
		assertEquals(e.getEnsembleModel().getNout(), sut.getTestCorr().length);
		for (int idx = 0; idx < calculateTestCorr(e.getEnsembleModel()).length; idx++) {
			assertEquals(calculateTestCorr(e.getEnsembleModel())[idx], sut.getTestCorr()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_always_calculatesTrainingCorr()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor();
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		long trainingTime = System.currentTimeMillis();
		EnsembleModelEvent e = createEnsembleModelEvent(model, trainingTime);
		createSut(prep, model);

		// Act
		sut.trainingComplete(e);

		// Assert
		assertEquals(e.getEnsembleModel().getNout(), sut.getTrainingCorr().length);
		for (int idx = 0; idx < calculateTrainingCorr(e.getEnsembleModel()).length; idx++) {
			assertEquals(calculateTrainingCorr(e.getEnsembleModel())[idx], sut.getTrainingCorr()[idx], DELTA);
		}
	}

	@Test
	public void test_getInputUnit_variableIsFound_returnsVariableUnit() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			// Act
			sut.getInputUnit(idx);

			// Assert
			assertEquals(variable.getUnit(), sut.getInputUnit(idx));
		}
	}

	@Test
	public void test_getOutputUnit_variableIsFound_returnsVariableUnit() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));

			// Act
			sut.getInputUnit(idx);

			// Assert
			assertEquals(variable.getUnit(), sut.getOutputUnit(idx));
		}
	}

	@Test
	public void test_getInputUnits_always_returnsUnits() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		String[] result = sut.getInputUnits();

		// Assert
		assertEquals(preprocessorProcessedInputVarNames.size(), result.length);
		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			// Assert
			assertEquals(variable.getUnit(), sut.getInputUnits()[idx]);
		}
	}

	@Test
	public void test_getOutputUnits_always_returnsUnits() throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		createSut(prep, model);

		// Act
		String[] result = sut.getInputUnits();

		// Assert
		assertEquals(model.getOutputVarNames().size(), result.length);
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			Variable variable = prep.getVariableFromVariableName((String) model.getOutputVarNames().get(idx));

			// Assert
			assertEquals(variable.getUnit(), sut.getOutputUnits()[idx]);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setVariableValueAtTimeByName_doesNotHaveTimeStamps_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(), createModel());

		// Act
		sut.setVariableValueAtTimeByName(ANY_STRING, ANY_DOUBLE, ANY_STRING);
	}

	@Test
	public void test_setVariableValueAtTimeByName_hasTimeStamps_setsInput()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(true), createModel());
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (idx + 1);

			// Act
			sut.setVariableValueAtTimeByName(preprocessorProcessedInputVarNames.get(idx), value, time);

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(value, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, 0), DELTA);
		}
	}

	@Test(expected = MathException.class)
	public void test_setVariableValueAtTimeByName_isNotInputVariableAndModelIsNotRecursive_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"));
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		// Act
		sut.setVariableValueAtTimeByName(ANY_STRING, ANY_DOUBLE, time);
	}

	@Test(expected = MathException.class)
	public void test_setVariableValueAtTimeByName_isNotOutputVariable_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		// Act
		sut.setVariableValueAtTimeByName(ANY_STRING, ANY_DOUBLE, time);
	}

	@Test
	public void test_setVariableValueAtTimeByName_isOutputVariable_setsOutputVariableData()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		// Act
		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			double value = BASE_VALUE * (idx + 1);

			// Act
			sut.setVariableValueAtTimeByName((String) model.getOutputVarNames().get(idx), value, time);

			// Assert
			DataSeries dataSeries = (DataSeries) Whitebox.getInternalState(sut, "outputData");
			assertEquals(value, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, idx), DELTA);
		}
	}

	@Test
	public void test_setVariableValueAtTimeByName_initialBufferSizeIsReached_extendsBuffer()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		long baseTime = System.currentTimeMillis();

		for (int timeIdx = 0; timeIdx < INITIAL_BUFFER_SIZE; timeIdx++) {
			for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
				double value = BASE_VALUE * (timeIdx + idx + 1);
				sut.setVariableValueAtTimeByName((String) model.getOutputVarNames().get(idx), value,
						dateFormat.format(baseTime + ((timeIdx + 1) * ONE_SECOND)));
			}
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			double value = BASE_VALUE * (INITIAL_BUFFER_SIZE + idx + 1);
			// Act
			sut.setVariableValueAtTimeByName((String) model.getOutputVarNames().get(idx), value,
					dateFormat.format(baseTime + ((INITIAL_BUFFER_SIZE + 1) * ONE_SECOND)));

			// Assert
			DataSeries dataSeries = (DataSeries) Whitebox.getInternalState(sut, "outputData");
			assertNotNull(dataSeries);
			assertEquals(INITIAL_BUFFER_SIZE * 2, dataSeries.getTimeStamps().length);
		}
	}

	@Test
	public void test_setVariableValueAtTimeByName_maxBufferSizeIsReached_doesNotExtendBuffer()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		long baseTime = System.currentTimeMillis();

		for (int timeIdx = 0; timeIdx < MAX_BUFFER_SIZE; timeIdx++) {
			for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
				double value = BASE_VALUE * (timeIdx + idx + 1);
				sut.setVariableValueAtTimeByName((String) model.getOutputVarNames().get(idx), value,
						dateFormat.format(baseTime + ((timeIdx + 1) * ONE_SECOND)));
			}
		}

		for (int idx = 0; idx < model.getOutputVarNames().size(); idx++) {
			double value = BASE_VALUE * (MAX_BUFFER_SIZE + idx + 1);
			// Act
			sut.setVariableValueAtTimeByName((String) model.getOutputVarNames().get(idx), value,
					dateFormat.format(baseTime + ((MAX_BUFFER_SIZE + 1) * ONE_SECOND)));

			// Assert
			DataSeries dataSeries = (DataSeries) Whitebox.getInternalState(sut, "outputData");
			assertNotNull(dataSeries);
			assertEquals(MAX_BUFFER_SIZE, dataSeries.getTimeStamps().length);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setVariableValueAtTimeByTag_doesNotHaveTimeStamps_throwsMathException()
			throws MathException, FormulaException, ParseException {
		// Arrange
		createSut(createPreprocessor(), createModel());

		// Act
		sut.setVariableValueAtTimeByTag(ANY_STRING, ANY_DOUBLE, ANY_STRING);
	}

	@Test
	public void test_setVariableValueAtTimeByTag_hasTimeStamps_invokesSetVariableValueAtTimeByName()
			throws MathException, FormulaException, ParseException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		createSut(prep, createModel());
		SimpleDateFormat dateFormat = new SimpleDateFormat(DEFAULT_DATE_FORMAT);
		String time = dateFormat.format(Calendar.getInstance().getTime());

		for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
			double value = BASE_VALUE * (idx + 1);
			Variable variable = prep.getVariableFromVariableName(preprocessorProcessedInputVarNames.get(idx));

			// Act
			sut.setVariableValueAtTimeByTag(variable.getTag(), value, time);

			// Assert
			DataSeries dataSeries = sut.getDataSeriesFromVariableName(preprocessorProcessedInputVarNames.get(idx));
			assertEquals(value, dataSeries.getValueAt(INITIAL_BUFFER_SIZE - 1, 0), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_calculateSensitivity_dataIsNotEnoughForCalculation_throwsMathException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);

		// Act
		sut.calculateSensitivity(createMatrix(0, ANY_INTEGER), createMatrix(ANY_INTEGER, ANY_INTEGER),
				createMatrix(ANY_INTEGER, ANY_INTEGER));
	}

	@Test(expected = MathException.class)
	public void test_calculateSensitivity_inputMatrixColumnsMismatchModelInput_throwsMathException()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();

		// Act
		sut.calculateSensitivity(createMatrix(LEAST_INPUT_SAMPLES_FOR_CALCULATION, ensembleModel.getNin() + 1),
				createMatrix(), createMatrix());
	}

	@Test
	public void test_calculateSensitivity_inputMatrixIsValid_calculatesSignedSensititvity()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		int samples = 10;
		Matrix input = createMatrixWithUniqueValues(samples, ensembleModel.getNin());
		Matrix signedSensitivity = createMatrix();
		Matrix absSensitivity = createMatrix();

		// Act
		sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

		// Assert
		assertEquals(ensembleModel.getNin(), signedSensitivity.getRows());
		assertEquals(ensembleModel.getNout(), signedSensitivity.getCols());

		Matrix expected = calculateSignedSensitivity(input, prep, formulaModel);
		for (int r = 0; r < expected.getRows(); r++) {
			for (int c = 0; c < expected.getCols(); c++) {
				assertEquals(expected.get(r, c), signedSensitivity.get(r, c), DELTA);
			}
		}
	}

	@Test
	public void test_calculateSensitivity_inputMatrixIsValid_calculatesAbsoluteSensititvity()
			throws MathException, FormulaException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		EnsembleModel ensembleModel = (EnsembleModel) formulaModel.getModel();
		Matrix input = createMatrixWithUniqueValues(MAX_INPUT_SAMPLES_FOR_CALCULATION + 1, ensembleModel.getNin());
		Matrix signedSensitivity = createMatrix();
		Matrix absSensitivity = createMatrix();

		// Act
		sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

		// Assert
		assertEquals(ensembleModel.getNin(), signedSensitivity.getRows());
		assertEquals(ensembleModel.getNout(), signedSensitivity.getCols());

		Matrix expected = calculateAbsoluteSensitivity(input, prep, formulaModel);
		for (int r = 0; r < expected.getRows(); r++) {
			for (int c = 0; c < expected.getCols(); c++) {
				assertEquals(expected.get(r, c), absSensitivity.get(r, c), DELTA);
			}
		}
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Test
	public void test_prepareTrainingDataFile_always_prepareTrainingSetFromDataSeries()
			throws MathException, FormulaException, IOException {
		// Arrange
		Preprocessor prep = createPreprocessor(true);
		NolModel2 model = createModel(createNames("inVar"), createNames("outVar"), true);
		NolModel2 formulaModel = arrangePreprocessorFormulaModel(prep, model);
		createSut(prep, model);
		int rows = 3;
		DataSeries[] dataSeries = new DataSeries[] { new DataSeries(rows, model.getInputs().size()),
				new DataSeries(rows, model.getInputs().size()) };
		String[] dataSeriesFileNames = createDsFiles(dataSeries);
		String inputDataFileName = createEmptyFile();
		String outDataFileName = createEmptyFile();
		ArgumentCaptor<Vector> retraindataSeriesCaptor = ArgumentCaptor.forClass(Vector.class);

		// Act
		sut.prepareTrainingDataFile(dataSeriesFileNames, DS_FORMAT, inputDataFileName, outDataFileName);

		// Assert
		verify(formulaModel).prepareTrainingSetFromDataSeries(retraindataSeriesCaptor.capture(),
				Matchers.any(Matrix.class), Matchers.any(Matrix.class));
		Vector<DataSeries> retraindataSeries = retraindataSeriesCaptor.getValue();
		assertEquals(dataSeries.length, retraindataSeries.size());
		for (int idx = 0; idx < dataSeries.length; idx++) {
			DataSeries actual = retraindataSeries.get(idx);
			DataSeries expected = dataSeries[idx];

			for (int varIdx = 0; varIdx < expected.getVarObjects().size(); varIdx++) {
				assertEquals(expected.getVarByIndex(varIdx).getName(), actual.getVarByIndex(varIdx).getName());
			}
		}
	}

	// -- Helper Methods --

	private void addData(Vector<Vector<String>> fileLines, int rowsCount, int colsCount) {
		for (int idx = 0; idx < rowsCount; idx++) {
			Vector<String> line = new Vector<String>();

			for (int colIdx = 0; colIdx < colsCount; colIdx++) {
				line.add(new Double(randomGenerator.nextDouble()).toString());
			}

			fileLines.add(line);
		}
	}

	private void addInitialBufferSizeSamples(long baseTime, SimpleDateFormat dateFormat)
			throws ParseException, MathException {
		for (int timeIdx = 0; timeIdx < INITIAL_BUFFER_SIZE; timeIdx++) {
			for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
				double value = BASE_VALUE * (timeIdx + idx + 1);

				sut.setInputAtTimeByName(preprocessorProcessedInputVarNames.get(idx), value,
						dateFormat.format(baseTime + (timeIdx * ONE_SECOND)));
			}
		}
	}

	private void addMaxBufferSizeSamples(long baseTime, SimpleDateFormat dateFormat)
			throws ParseException, MathException {
		int addedSamplesCount = 0;

		while (addedSamplesCount < MAX_BUFFER_SIZE) {
			for (int timeIdx = 0; timeIdx < INITIAL_BUFFER_SIZE; timeIdx++) {
				for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
					double value = BASE_VALUE * (timeIdx + idx + 1);

					sut.setInputAtTimeByName(preprocessorProcessedInputVarNames.get(idx), value,
							dateFormat.format(baseTime + ((timeIdx - addedSamplesCount) * ONE_SECOND)));
				}
			}

			addedSamplesCount += INITIAL_BUFFER_SIZE;
		}
	}

	private void addPreprocessorVariables(Vector<String> inputs) {
		for (int idx = 0; idx < inputs.size(); idx++) {
			Variable variable = new Variable();
			variable.setName(inputs.get(idx));
			variable.setTag(inputs.get(idx) + "Tag");
			variable.setUnit(inputs.get(idx) + "Unit");
			variable.setStatistics(createVariableStatistics());
			preprocessorVariables.add(variable);
		}
	}

	private NolModel2 arrangePreprocessorFormulaModel(Preprocessor prep, NolModel2 model) throws MathException {
		return arrangePreprocessorFormulaModel(prep, model, System.currentTimeMillis());
	}

	@SuppressWarnings("unchecked")
	private NolModel2 arrangePreprocessorFormulaModel(Preprocessor prep, NolModel2 model, long trainingTime)
			throws MathException {
		NolModel2 formulaModel = mock(NolModel2.class);

		doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				Matrix matrixX = invocation.getArgumentAt(0, Matrix.class);
				Matrix matrixY = invocation.getArgumentAt(1, Matrix.class);

				int rows = Math.min(matrixX.getRows(), matrixY.getRows());
				int cols = Math.min(matrixX.getCols(), matrixY.getCols());

				for (int r = 0; r < matrixY.getRows(); r++) {
					for (int c = 0; c < matrixY.getCols(); c++) {
						matrixY.set(r, c, 0.0);
					}
				}

				for (int r = 0; r < rows; r++) {
					for (int c = 0; c < cols; c++) {
						matrixY.set(r, c, matrixX.get(r, c) * 2);
					}
				}

				return null;
			}
		}).when(formulaModel).evaluate(Matchers.any(Matrix.class), Matchers.any(Matrix.class));

		when(formulaModel.getInputs()).thenReturn(preprocessorProcessedInputVarNames);
		when(formulaModel.getInputVarNames()).thenReturn(preprocessorProcessedInputVarNames);

		Vector<long[]> inputDelays = model.getInputDelays();
		when(formulaModel.getInputDelays()).thenReturn(inputDelays);

		Vector<String> outputVarNames = model.getOutputVarNames();
		when(formulaModel.getOutputs()).thenReturn(outputVarNames);
		when(formulaModel.getOutputVarNames()).thenReturn(outputVarNames);

		Vector<long[]> outputDelays = model.getOutputDelays();
		when(formulaModel.getOutputDelays()).thenReturn(outputDelays);

		boolean isRecursive = model.isRecursiveModel();
		when(formulaModel.isRecursiveModel()).thenReturn(isRecursive);

		EnsembleModel ensembleModel = createEnsembleModel(formulaModel, trainingTime);
		when(formulaModel.getModel()).thenReturn(ensembleModel);

		when(((Formula2) prep.getFormulas().lastElement()).getFunction()).thenReturn(formulaModel);

		return formulaModel;
	}

	private void assertEqualMatrices(Matrix expected, Matrix actual) {
		assertEquals(expected.getRows(), actual.getRows());
		assertEquals(expected.getCols(), actual.getCols());

		for (int r = 0; r < expected.getRows(); r++) {
			for (int c = 0; c < expected.getCols(); c++) {
				assertEquals(expected.get(r, c), actual.get(r, c), DELTA);
			}
		}
	}

	private void assertThatVariablesAreSame(Variable expected, Variable actual) {
		assertEquals(expected.getName(), actual.getName());
		assertEquals(expected.getTag(), actual.getTag());
		assertEquals(expected.getUnit(), actual.getUnit());

		for (int idx = 0; idx < expected.getStatistics().length; idx++) {
			assertEquals(expected.getStatistics()[idx], actual.getStatistics()[idx], DELTA);
		}
	}

	private Vector<DataSeries> attachApplyFormula(Preprocessor prep) throws MathException, FormulaException {
		return attachApplyFormula(prep, null);
	}

	@SuppressWarnings("unchecked")
	private Vector<DataSeries> attachApplyFormula(Preprocessor prep, Exception exception)
			throws MathException, FormulaException {
		Vector<DataSeries> formulaAppliedData = new Vector<DataSeries>();
		// Adding initial values to this matrix with max possible processed data
		// size.
		int cols = 50;
		for (int idx = 0; idx < 20; idx++) {
			DataSeries dataSeries = new DataSeries(MAX_BUFFER_SIZE, cols);
			for (int r = 0; r < MAX_BUFFER_SIZE; r++) {
				for (int c = 0; c < cols; c++) {
					dataSeries.setValueAt(r, c, randomGenerator.nextDouble());
				}
			}

			formulaAppliedData.add(dataSeries);
		}

		for (Formula2 formula : (Vector<Formula2>) prep.getFormulas()) {
			doAnswer(new Answer<Object>() {
				@Override
				public Object answer(InvocationOnMock invocation) throws Throwable {
					if (exception != null) {
						throw exception;
					}

					Vector<DataSeries> processedData = invocation.getArgumentAt(0, Vector.class);

					for (int idx = 0; idx < processedData.size(); idx++) {
						formulaAppliedData.get(idx).setName(processedData.get(idx).getName());

						for (int r = 0; r < processedData.get(idx).getDataMatrix().getRows(); r++) {
							for (int c = 0; c < processedData.get(idx).getDataMatrix().getCols(); c++) {
								processedData.get(idx).getDataMatrix().set(r, c,
										formulaAppliedData.get(idx).getValueAt(r, c));
							}
						}
					}

					return null;
				}
			}).when(formula).applyFormula(Matchers.any(Vector.class));
		}

		return formulaAppliedData;
	}

	private double calculateModelRate(EnsembleModel ensemble) {
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();

		double[] testRMSE = new double[nout];
		double[] testCORR = new double[nout];
		double[] trainRMSE = new double[nout];
		double[] trainCORR = new double[nout];
		double modelRateValue = 0;

		for (int j = 0; j < nout; j++) {
			testRMSE[j] = 0.0;
			testCORR[j] = 0.0;

			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters parameters = submodel.testingResults;
				testRMSE[j] += parameters.rmse.get(j);
				testCORR[j] += parameters.corrcoef.get(j);
				parameters = submodel.trainingResults;
				trainRMSE[j] += parameters.rmse.get(j);
				trainCORR[j] += parameters.corrcoef.get(j);
			}

			testRMSE[j] /= ensembleSize;
			testCORR[j] /= ensembleSize;
			trainRMSE[j] /= ensembleSize;
			trainCORR[j] /= ensembleSize;
		}

		for (int idx = 0; idx < nout; idx++) {
			modelRateValue = modelRateValue + testCORR[idx];
		}

		modelRateValue = modelRateValue / nout;

		return modelRateValue;
	}

	@SuppressWarnings("unchecked")
	private Matrix calculateSignedSensitivity(Matrix input, Preprocessor prep, NolModel2 model) {
		Vector<String> inputVars = model.getInputs();
		EnsembleModel ensembleModel = (EnsembleModel) model.getModel();
		int ni = ensembleModel.getNin();
		int no = ensembleModel.getNout();
		Matrix signedSensitivity = Matlib.createMatrix(ni, no);

		int row = input.getRows();

		for (int c = 0; c < no; c++) {
			for (int r = 0; r < ni; r++) {
				signedSensitivity.set(r, c, 0.0);
			}
		}

		Matrix pX = Matlib.createMatrix(1, ni);

		Matrix sampledX = Matlib.createMatrix();
		Matrix nX = Matlib.createMatrix(1, ni);
		Matrix pY = Matlib.createMatrix(1, no);
		Matrix nY = Matlib.createMatrix(1, no);
		Matrix singleY = Matlib.createMatrix(1, no);
		int rCount = 100;
		if (row < 100) {
			rCount = row;
		}

		try {
			if (row < 100) {
				Matlib.copy(input, sampledX);
			} else {
				Matrix sampleMatrix = Matlib.createMatrix(input.getRows(), 1);
				Stats.randomSplit(input.getRows(), 100, sampleMatrix);
				Matlib.getRows(input, sampleMatrix, sampledX);
			}
			double[] deltas = new double[ni];
			double[] stds = new double[ni];
			for (int i = 0; i < ni; i++) {
				String varName = inputVars.elementAt(i);
				double[] statistics = prep.getVariableFromVariableName(varName).getStatistics();
				deltas[i] = statistics[6] / 200;
				stds[i] = statistics[2];
			}
			for (int r = 0; r < rCount; r++) {
				for (int i = 0; i < ni; i++) {
					Matlib.getRow(input, r, pX);
					Matlib.getRow(input, r, nX);
					pX.set(0, i, pX.get(0, i) + deltas[i]);
					nX.set(0, i, nX.get(0, i) - deltas[i]);
					model.evaluate(pX, pY);
					model.evaluate(nX, nY);
					Matlib.subtract(pY, nY, singleY);
					Matlib.divide(singleY, deltas[i] * 2, singleY);
					Matlib.multiply(singleY, stds[i], singleY);
					for (int c = 0; c < no; c++) {
						signedSensitivity.set(i, c, signedSensitivity.get(i, c) + singleY.get(0, c));
					}
				}
			}
		} catch (MathException evt) {
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}
		if (rCount > 0) {
			for (int i = 0; i < ni; i++) {
				for (int c = 0; c < no; c++) {
					signedSensitivity.set(i, c, signedSensitivity.get(i, c) / rCount);
				}
			}
		}

		Matlib.clear(pX);
		Matlib.clear(nX);
		Matlib.clear(pY);
		Matlib.clear(nY);
		Matlib.clear(singleY);
		Matlib.clear(sampledX);

		return signedSensitivity;
	}

	@SuppressWarnings("unchecked")
	private Matrix calculateAbsoluteSensitivity(Matrix input, Preprocessor prep, NolModel2 model) {
		Vector<String> inputVars = model.getInputs();
		EnsembleModel ensembleModel = (EnsembleModel) model.getModel();
		int ni = ensembleModel.getNin();
		int no = ensembleModel.getNout();
		Matrix absSensitivity = Matlib.createMatrix(ni, no);

		int row = input.getRows();

		for (int c = 0; c < no; c++) {
			for (int r = 0; r < ni; r++) {
				absSensitivity.set(r, c, 0.0);
			}
		}

		Matrix pX = Matlib.createMatrix(1, ni);

		Matrix sampledX = Matlib.createMatrix();
		Matrix nX = Matlib.createMatrix(1, ni);
		Matrix pY = Matlib.createMatrix(1, no);
		Matrix nY = Matlib.createMatrix(1, no);
		Matrix singleY = Matlib.createMatrix(1, no);
		int rCount = 100;
		if (row < 100) {
			rCount = row;
		}

		try {
			if (row < 100) {
				Matlib.copy(input, sampledX);
			} else {
				Matrix sampleMatrix = Matlib.createMatrix(input.getRows(), 1);
				Stats.randomSplit(input.getRows(), 100, sampleMatrix);
				Matlib.getRows(input, sampleMatrix, sampledX);
			}
			double[] deltas = new double[ni];
			double[] stds = new double[ni];
			for (int i = 0; i < ni; i++) {
				String varName = inputVars.elementAt(i);
				double[] statistics = prep.getVariableFromVariableName(varName).getStatistics();
				deltas[i] = statistics[6] / 200;
				stds[i] = statistics[2];
			}
			for (int r = 0; r < rCount; r++) {
				for (int i = 0; i < ni; i++) {
					Matlib.getRow(input, r, pX);
					Matlib.getRow(input, r, nX);
					pX.set(0, i, pX.get(0, i) + deltas[i]);
					nX.set(0, i, nX.get(0, i) - deltas[i]);
					model.evaluate(pX, pY);
					model.evaluate(nX, nY);
					Matlib.subtract(pY, nY, singleY);
					Matlib.divide(singleY, deltas[i] * 2, singleY);
					Matlib.multiply(singleY, stds[i], singleY);
					for (int c = 0; c < no; c++) {
						absSensitivity.set(i, c, absSensitivity.get(i, c) + Math.abs(singleY.get(0, c)));
					}
				}
			}
		} catch (MathException evt) {
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}
		if (rCount > 0) {
			for (int i = 0; i < ni; i++) {
				for (int c = 0; c < no; c++) {
					absSensitivity.set(i, c, absSensitivity.get(i, c) / rCount);
				}
			}
		}

		Matlib.clear(pX);
		Matlib.clear(nX);
		Matlib.clear(pY);
		Matlib.clear(nY);
		Matlib.clear(singleY);
		Matlib.clear(sampledX);

		return absSensitivity;
	}

	private double[] calculateTestCorr(EnsembleModel ensemble) {
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();

		double[] testCORR = new double[nout];

		for (int j = 0; j < nout; j++) {
			testCORR[j] = 0.0;

			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters parameters = submodel.testingResults;
				testCORR[j] += parameters.corrcoef.get(j);
			}

			testCORR[j] /= ensembleSize;
		}

		return testCORR;
	}

	private double[] calculateTestRmse(EnsembleModel ensemble) {
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();

		double[] testRMSE = new double[nout];

		for (int j = 0; j < nout; j++) {
			testRMSE[j] = 0.0;

			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters parameters = submodel.testingResults;
				testRMSE[j] += parameters.rmse.get(j);
			}

			testRMSE[j] /= ensembleSize;
		}

		return testRMSE;
	}

	private double[] calculateTrainingCorr(EnsembleModel ensemble) {
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();

		double[] trainCORR = new double[nout];

		for (int j = 0; j < nout; j++) {
			trainCORR[j] = 0.0;

			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters parameters = submodel.trainingResults;
				trainCORR[j] += parameters.corrcoef.get(j);
			}

			trainCORR[j] /= ensembleSize;
		}

		return trainCORR;
	}

	private double[] calculateTrainingRmse(EnsembleModel ensemble) {
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();

		double[] trainRMSE = new double[nout];

		for (int j = 0; j < nout; j++) {
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters parameters = submodel.trainingResults;
				trainRMSE[j] += parameters.rmse.get(j);
			}

			trainRMSE[j] /= ensembleSize;
		}

		return trainRMSE;
	}

	private String[] createDsFiles(DataSeries[] dataSerieses) throws IOException {
		String[] filenames = new String[dataSerieses.length];

		for (int idx = 0; idx < dataSerieses.length; idx++) {
			dataSerieses[idx].setName("DataSeries" + (idx + 1) + ".tmp");
			Vector<Vector<String>> fileLines = createVariableSpecsLines(dataSerieses[idx].getDataMatrix().getCols(),
					false);
			addData(fileLines, dataSerieses[idx].getDataMatrix().getRows(),
					dataSerieses[idx].getDataMatrix().getCols());
			filenames[idx] = createDsFile(fileLines, dataSerieses[idx].getName()).getAbsolutePath();
			dataSerieses[idx].Load(filenames[idx], DS_FORMAT);
		}

		return filenames;
	}

	private String createEmptyFile() throws IOException {
		return temporaryFolder.newFile().getAbsolutePath();
	}

	private EnsembleModelEvent createEnsembleModelEvent(NolModel2 model, long trainingTime) {
		EnsembleModelEvent modelEvent = mock(EnsembleModelEvent.class);
		EnsembleModel ensembleModel = createEnsembleModel(model, trainingTime);
		when(modelEvent.getEnsembleModel()).thenReturn(ensembleModel);
		return modelEvent;
	}

	private Vector<long[]> createDelays(NolModel2 model, Vector<String> names) {
		Vector<long[]> delays = new Vector<long[]>();
		long baseDelay = System.currentTimeMillis();

		for (int idx = 0; idx < names.size(); idx++) {
			delays.add(new long[] { baseDelay + 1000 * idx });
		}

		return delays;
	}

	private File createDsFile(Vector<Vector<String>> fileLines, String filename) throws IOException {
		String fileContent = getDsFileContent(fileLines);
		StringBuilder sb = new StringBuilder();

		String[] lines = fileContent.split("\\n");
		for (int idx = 0; idx < lines.length; idx++) {
			String line = lines[idx];
			if (line.startsWith(TAB_SEPARATOR)) {
				line = line.substring(1, line.length());
			}

			if (line.endsWith(TAB_SEPARATOR)) {
				line = line.substring(0, line.length() - 1);
			}

			sb.append(line);
			if (idx < lines.length - 1) {
				sb.append(NEW_LINE);
			}
		}

		return createFile(filename, sb.toString());
	}

	private EnsembleModel createEnsembleModel(NolModel2 formulaModel, long trainingTime) {
		EnsembleModel ensembleModel = mock(EnsembleModel.class);

		int inputs = formulaModel.getInputVarNames().size();
		when(ensembleModel.getNin()).thenReturn(inputs);

		int outputs = formulaModel.getOutputVarNames().size();
		when(ensembleModel.getNout()).thenReturn(outputs);

		when(ensembleModel.getTrainingTime()).thenReturn(trainingTime);

		int models = 4;
		when(ensembleModel.size()).thenReturn(models);
		TrainableModel[] trainingModels = createTrainingModels(models, outputs);
		when(ensembleModel.getModel(Matchers.anyInt())).thenAnswer(new Answer<Model>() {
			@Override
			public Model answer(InvocationOnMock invocation) throws Throwable {
				int index = invocation.getArgumentAt(0, int.class);
				if (index < models) {
					return trainingModels[index];
				}

				return null;
			}
		});

		return ensembleModel;
	}

	private Formula2 createFormula(String stringRepresentation, Vector<String> inputVarNames, long inputBufferLength)
			throws MathException, FormulaException {
		Formula2 formula = mock(Formula2.class);
		when(formula.getInputBufferLength()).thenReturn(inputBufferLength);
		when(formula.hasVariable(Matchers.anyString())).thenAnswer(new Answer<Boolean>() {
			@Override
			public Boolean answer(InvocationOnMock invocation) throws Throwable {
				String varName = invocation.getArgumentAt(0, String.class);
				return inputVarNames.contains(varName);
			}
		});
		when(formula.toString()).thenReturn(stringRepresentation);
		return formula;
	}

	private Matrix createMatrix(int cols, double val) {
		return createMatrix(3, cols, val);
	}

	private String createFile(Matrix matrix) throws IOException {
		File file = temporaryFolder.newFile();

		FileWriter fWriter = null;
		BufferedWriter bWriter = null;
		try {
			fWriter = new FileWriter(file);
			bWriter = new BufferedWriter(fWriter);
			bWriter.write(getContent(matrix));
		} catch (Exception ex) {
			fail("Failed to create DataSeries file.");
		} finally {
			if (bWriter != null) {
				bWriter.close();
			}
		}

		return file.getAbsolutePath();
	}

	private File createFile(String filename, String content) throws IOException {
		File file = temporaryFolder.newFile(filename);
		BufferedWriter writer = null;

		try {
			writer = new BufferedWriter(new FileWriter(file));
			writer.write(content);
		} catch (Exception ex) {
			fail("Failed to create file.");
		} finally {
			if (writer != null) {
				writer.close();
			}
		}

		return file;
	}

	private Vector<Vector<String>> createVariableSpecsLines(int varNumbers, boolean containsTimeStamps) {
		Vector<Vector<String>> fileLines = new Vector<Vector<String>>();

		fileLines.add(new Vector<String>());
		fileLines.add(new Vector<String>());
		fileLines.add(new Vector<String>());

		if (containsTimeStamps) {
			fileLines.get(NAME_ROW_INDEX).add(TIME_TAG);
			fileLines.get(TAG_ROW_INDEX).add(TIME_TAG);
			fileLines.get(UNIT_ROW_INDEX).add(TIME_UNIT);
		}

		for (int idx = 0; idx < varNumbers; idx++) {
			fileLines.get(NAME_ROW_INDEX).add(VARIABLE_NEW_NAME_PREFIX + (idx + 1));
		}

		for (int idx = 0; idx < varNumbers; idx++) {
			fileLines.get(TAG_ROW_INDEX).add(VARIABLE_NEW_TAG_PREFIX + (idx + 1));
		}

		for (int idx = 0; idx < varNumbers; idx++) {
			fileLines.get(UNIT_ROW_INDEX).add(VARIABLE_NEW_UNIT_PREFIX + (idx + 1));
		}

		return fileLines;
	}

	private Matrix createMatrix() {
		return createMatrix(0, 0);
	}

	private Matrix createMatrix(int rows, int cols) {
		return createMatrix(rows, cols, randomGenerator.nextDouble());
	}

	private Matrix createMatrix(int rows, int cols, double val) {
		Matrix matrix = Matlib.createMatrix(rows, cols);

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				matrix.set(r, c, val);
			}
		}

		return matrix;
	}

	private Matrix createMatrixWithUniqueValues(int rows, int cols) {
		Matrix matrix = Matlib.createMatrix(rows, cols);

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				matrix.set(r, c, randomGenerator.nextDouble());
			}
		}

		return matrix;
	}

	private NolModel2 createModel() {
		return createModel(new Vector<String>(), new Vector<String>(), false);
	}

	private NolModel2 createModel(Vector<String> inputNames, Vector<String> outputNames) {
		return createModel(inputNames, outputNames, false);
	}

	private NolModel2 createModel(Vector<String> inputNames, Vector<String> outputNames, boolean isRecursiveModel) {
		NolModel2 model = mock(NolModel2.class);
		when(model.getComment()).thenReturn("Model Comments");
		when(model.getInputVarNames()).thenReturn(inputNames);
		when(model.getInputs()).thenReturn(inputNames);
		when(model.getInputDelays()).thenReturn(createDelays(model, inputNames));
		when(model.getOutputVarNames()).thenReturn(outputNames);
		when(model.getOutputs()).thenReturn(outputNames);
		when(model.getOutputDelays()).thenReturn(createDelays(model, outputNames));
		when(model.isRecursiveModel()).thenReturn(isRecursiveModel);
		return model;
	}

	private EnsembleModelListener createModelListener() {
		EnsembleModelListener modelListener = mock(EnsembleModelListener.class);
		return modelListener;
	}

	private Vector<EnsembleModelListener> createModelListeners() {
		Vector<EnsembleModelListener> modelListeners = new Vector<EnsembleModelListener>();
		modelListeners.add(createModelListener());
		return modelListeners;
	}

	private Vector<String> createNames(String namePrefix) {
		Vector<String> names = new Vector<String>();

		for (int idx = 1; idx <= 3; idx++) {
			names.add(namePrefix + idx);
		}

		addPreprocessorVariables(names);
		return names;
	}

	private OnlineModelListener createOnlineModelListener() {
		OnlineModelListener modelListener = mock(OnlineModelListener.class);
		NolOnlineConsoleFrame console = mock(NolOnlineConsoleFrame.class);
		when(modelListener.getOnlineConsole()).thenReturn(console);
		return modelListener;
	}

	private Vector<OnlineModelListener> createOnlineModelListeners() {
		Vector<OnlineModelListener> modelListeners = new Vector<OnlineModelListener>();
		modelListeners.add(createOnlineModelListener());
		return modelListeners;
	}

	private File createOnlineProcessorObjectFile(VersionManagerForOnlineProcessor versionManager) throws IOException {
		return createOnlineProcessorObjectFile(versionManager, true);
	}

	private File createOnlineProcessorObjectFile(VersionManagerForOnlineProcessor versionManager, boolean withDirectory)
			throws IOException {
		File file = temporaryFolder.newFile();
		if (withDirectory) {
			versionManager.saveToFile(file.getAbsolutePath().replace(file.getName(), ""), file.getName());
		} else {
			versionManager.saveToFile(file.getAbsolutePath());
		}

		return file;
	}

	private Preprocessor createPreprocessor() throws MathException, FormulaException {
		return createPreprocessor(false);
	}

	@SuppressWarnings("unchecked")
	private Preprocessor createPreprocessor(boolean hasTimeStamps) throws MathException, FormulaException {
		Preprocessor preprocessor = mock(Preprocessor.class);
		when(preprocessor.getName()).thenReturn("Preprocessor Name");
		when(preprocessor.getComment()).thenReturn("Preprocessor Comments");
		when(preprocessor.getHasTimeStamps()).thenReturn(hasTimeStamps);

		Vector<Formula2> prepFormulas = createPreprocessorFormulas(preprocessorProcessedInputVarNames);
		when(preprocessor.getFormulas()).thenReturn(prepFormulas);

		when(preprocessor.getVariableFromVariableName(Matchers.anyString())).thenAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				String name = invocation.getArgumentAt(0, String.class);
				for (int idx = 0; idx < preprocessorVariables.size(); idx++) {
					if (preprocessorVariables.get(idx).getName() == name) {
						return preprocessorVariables.get(idx);
					}
				}

				return null;
			}
		});

		preprocessorProcessedInputVarNames = new Vector<String>();
		for (int idx = 1; idx <= 3; idx++) {
			preprocessorProcessedInputVarNames.add("prepVar" + idx);
		}

		addPreprocessorVariables(preprocessorProcessedInputVarNames);

		doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				Vector<String> processedVars = invocation.getArgumentAt(1, Vector.class);
				Vector<Formula2> formulas = invocation.getArgumentAt(3, Vector.class);

				processedVars.removeAllElements();
				for (int idx = 0; idx < preprocessorProcessedInputVarNames.size(); idx++) {
					processedVars.add(preprocessorProcessedInputVarNames.get(idx));
				}

				formulas.removeAllElements();
				formulas.addAll(prepFormulas);
				return null;
			}
		}).when(preprocessor).getInputNamesDerivedVarsFormulasForModel(Matchers.any(Vector.class),
				Matchers.any(Vector.class), Matchers.any(Vector.class), Matchers.any(Vector.class));

		return preprocessor;
	}

	private Vector<Formula2> createPreprocessorFormulas(Vector<String> inputVarNames)
			throws MathException, FormulaException {
		Vector<Formula2> formulas = new Vector<Formula2>();

		formulas.add(createFormula("Formula 1 To String", inputVarNames, 5));
		formulas.add(createFormula("Formula 2 To String", inputVarNames, 3));

		return formulas;
	}

	private void createSut() {
		sut = new OnlineProcessor();
	}

	private void createSut(Preprocessor prep, NolModel2 model) throws MathException {
		sut = new OnlineProcessor(ANY_STRING, prep, model);
	}

	private double[] createVariableStatistics() {
		double[] statistics = new double[10];

		for (int idx = 0; idx < statistics.length; idx++) {
			statistics[idx] = randomGenerator.nextDouble();
		}

		return statistics;
	}

	private VersionManagerForOnlineProcessor createVersionManagerForOnlineProcessor() throws MathException {
		Preprocessor prep = new Preprocessor();

		NolModel2 model = new NolModel2(new EnsembleModel(new ArchitectureParameters(0, 0, 0, 0)), ANY_STRING,
				new Vector<String>(), new Vector<String>(), new Vector<long[]>(), new Vector<long[]>(), prep);

		OnlineProcessor processor = new OnlineProcessor("Online Preprocessor Name in File", prep, model);
		processor.setComment("Online Preprocessor Comment in File");

		VersionManagerForOnlineProcessor versionManager = new VersionManagerForOnlineProcessor();
		versionManager.setProcessor(processor);
		return versionManager;
	}

	private String getContent(Matrix matrixX) {
		StringBuilder sb = new StringBuilder();

		for (int r = 0; r < matrixX.getRows(); r++) {
			for (int c = 0; c < matrixX.getCols(); c++) {
				sb.append(matrixX.get(r, c));

				if (c < matrixX.getCols() - 1) {
					sb.append(",");
				}
			}

			sb.append("\n");
		}

		return sb.toString();
	}

	private DataSeries getOutputDataSeries(Vector<DataSeries> processedData) {
		DataSeries outputDataSeries = null;
		for (DataSeries dataSeries : processedData) {
			if (dataSeries.getName().equals(ONLINE_PROCESSOR_OUTPUT_DATA_NAME)) {
				outputDataSeries = dataSeries;
				break;
			}
		}

		return outputDataSeries;
	}

	private void verifyConsoleConfiguration(OnlineModelListener modelListener) {
		NolOnlineConsoleFrame console = modelListener.getOnlineConsole();
		assertEquals(100, (int) console.getBounds().getX());
		assertEquals(100, (int) console.getBounds().getY());
		assertEquals(750, (int) console.getBounds().getWidth());
		assertEquals(500, (int) console.getBounds().getHeight());
	}

	private void verifyConsoleConfiguration(OnlineModelListener modelListener, Matrix matrixX, Matrix matrixY) {
		NolOnlineConsoleFrame console = modelListener.getOnlineConsole();
		verify(console).setModel1TrainInput(matrixX);
		verify(console).setModel1TrainOutput(matrixY);
		verify(console).setBounds(100, 100, 750, 500);
		verify(console).setReady(false);
		verify(console).setVisible(true);
		verify(console).toFront();
	}

	private String getDsFileContent(Vector<Vector<String>> fileLines) {
		StringBuilder sb = new StringBuilder();

		// Adding header rows
		if (fileLines.size() > 0) {
			for (int lineIdx = 0; lineIdx < 3; lineIdx++) {
				Vector<String> line = fileLines.get(lineIdx);
				for (int valueIdx = 0; valueIdx < line.size(); valueIdx++) {
					sb.append(TAB_SEPARATOR);
					sb.append(line.get(valueIdx));
				}

				sb.append(TAB_SEPARATOR);
				sb.append(NEW_LINE);
			}
		}

		// Adding time stamps rows if any
		if (fileLines.size() > 3) {
			for (int lineIdx = 3; lineIdx < fileLines.size(); lineIdx++) {
				Vector<String> line = fileLines.get(lineIdx);
				for (int valueIdx = 0; valueIdx < line.size(); valueIdx++) {
					sb.append(line.get(valueIdx));

					if (valueIdx < line.size() - 1) {
						sb.append(TAB_SEPARATOR);
					}
				}

				sb.append(NEW_LINE);
			}
		}

		return sb.toString();
	}

	private TrainableModel[] createTrainingModels(int count, int outputs) {
		TrainableModel[] trainingModels = new TrainableModel[count];
		for (int modelIdx = 0; modelIdx < count; modelIdx++) {
			TrainableModel model = mock(TrainableModel.class);

			Matrix trainingRootMeanSquareErrors = new Matrix();
			trainingRootMeanSquareErrors.redimension(1, outputs);
			for (int idx = 0; idx < outputs; idx++) {
				trainingRootMeanSquareErrors.set(idx, randomGenerator.nextInt(100));
			}

			Matrix trainingCorrelationCoefficients = new Matrix();
			trainingCorrelationCoefficients.redimension(1, outputs);
			for (int idx = 0; idx < outputs; idx++) {
				trainingCorrelationCoefficients.set(idx, randomGenerator.nextInt(100));
			}

			Matrix testingRootMeanSquareErrors = new Matrix();
			testingRootMeanSquareErrors.redimension(1, outputs);
			for (int idx = 0; idx < outputs; idx++) {
				testingRootMeanSquareErrors.set(idx, randomGenerator.nextInt(100));
			}

			Matrix testingCorrelationCoefficients = new Matrix();
			testingCorrelationCoefficients.redimension(1, outputs);
			for (int idx = 0; idx < outputs; idx++) {
				testingCorrelationCoefficients.set(idx, randomGenerator.nextInt(100));
			}

			ValidationParameters trainingResults = mock(ValidationParameters.class);
			ValidationParameters testingResults = mock(ValidationParameters.class);

			trainingResults.rmse = trainingRootMeanSquareErrors;
			trainingResults.corrcoef = trainingCorrelationCoefficients;
			model.trainingResults = trainingResults;

			testingResults.rmse = testingRootMeanSquareErrors;
			testingResults.corrcoef = testingCorrelationCoefficients;
			model.testingResults = testingResults;

			trainingModels[modelIdx] = model;
		}

		return trainingModels;
	}

	@SuppressWarnings("unchecked")

	private void verifyTrainModelIsInvoked(OnlineProcessor sutSpy, Vector<EnsembleModelListener> modelListeners,
			Matrix matrixX, Matrix matrixY, double trainingTime, boolean useAutoStopping, boolean newTraining,
			boolean display) throws MathException {
		ArgumentCaptor<Vector> modelListenersCaptor = ArgumentCaptor.forClass(Vector.class);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Double> trainingTimeCaptor = ArgumentCaptor.forClass(Double.class);
		ArgumentCaptor<Boolean> useAutoStoppingCaptor = ArgumentCaptor.forClass(Boolean.class);
		ArgumentCaptor<Boolean> newTrainingCaptor = ArgumentCaptor.forClass(Boolean.class);
		ArgumentCaptor<Boolean> displayCaptor = ArgumentCaptor.forClass(Boolean.class);

		verify(sutSpy).trainModel(modelListenersCaptor.capture(), matrixXCaptor.capture(), matrixYCaptor.capture(),
				trainingTimeCaptor.capture(), useAutoStoppingCaptor.capture(), newTrainingCaptor.capture(),
				displayCaptor.capture());

		assertEquals(modelListeners, modelListenersCaptor.getValue());
		assertEqualMatrices(matrixX, matrixXCaptor.getValue());
		assertEqualMatrices(matrixY, matrixYCaptor.getValue());
		assertEquals(trainingTime, trainingTimeCaptor.getValue(), DELTA);
		assertEquals(useAutoStopping, useAutoStoppingCaptor.getValue());
		assertEquals(newTraining, newTrainingCaptor.getValue());
		assertEquals(display, displayCaptor.getValue());
	}

	@SuppressWarnings("unchecked")
	private void verifyTrainModelIsInvoked(OnlineProcessor sutSpy, Vector<EnsembleModelListener> modelListeners,
			Matrix matrixX, Matrix matrixY, double trainingTime, boolean useAutoStopping, boolean newTraining,
			boolean display, NolModel2 model) throws MathException {
		ArgumentCaptor<Vector> modelListenersCaptor = ArgumentCaptor.forClass(Vector.class);
		ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);
		ArgumentCaptor<Double> trainingTimeCaptor = ArgumentCaptor.forClass(Double.class);
		ArgumentCaptor<Boolean> useAutoStoppingCaptor = ArgumentCaptor.forClass(Boolean.class);
		ArgumentCaptor<Boolean> newTrainingCaptor = ArgumentCaptor.forClass(Boolean.class);
		ArgumentCaptor<Boolean> displayCaptor = ArgumentCaptor.forClass(Boolean.class);

		InOrder inOrder = inOrder(model, sutSpy);
		inOrder.verify(model).prepareTrainingSetFromDataSeries(Matchers.any(Vector.class), Matchers.any(Matrix.class),
				Matchers.any(Matrix.class));
		inOrder.verify(sutSpy).trainModel(modelListenersCaptor.capture(), matrixXCaptor.capture(),
				matrixYCaptor.capture(), trainingTimeCaptor.capture(), useAutoStoppingCaptor.capture(),
				newTrainingCaptor.capture(), displayCaptor.capture());

		assertEquals(modelListeners, modelListenersCaptor.getValue());
		assertEqualMatrices(matrixX, matrixXCaptor.getValue());
		assertEqualMatrices(matrixY, matrixYCaptor.getValue());
		assertEquals(trainingTime, trainingTimeCaptor.getValue(), DELTA);
		assertEquals(useAutoStopping, useAutoStoppingCaptor.getValue());
		assertEquals(newTraining, newTrainingCaptor.getValue());
		assertEquals(display, displayCaptor.getValue());
	}
}
