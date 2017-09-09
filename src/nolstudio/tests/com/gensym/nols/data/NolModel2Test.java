package com.gensym.nols.data;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.is;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertThat;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.doAnswer;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

import java.util.HashMap;
import java.util.Random;
import java.util.Vector;

import org.hamcrest.BaseMatcher;
import org.hamcrest.Description;
import org.hamcrest.Matcher;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Matchers;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import com.gensym.DEBUG;
import com.gensym.math.MathException;
import com.gensym.math.Utilities;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;

public class NolModel2Test {
	private static final int DIGITS = 4;
	private static final int NUMBER_OF_STATISTICS = 5;
	private static final int OUTPUTS_BASE_INDEX = 5;
	private static final int TRAINING_RMSE_BASE_INDEX = 6;
	private static final int TESTING_CORRCOEF_BASE_INDEX = 7;
	private static final int TESTING_RMSE_BASE_INDEX = 8;
	private static final int TRAINING_CORRCOEF_BASE_INDEX = 9;
	private static final int NUMBER_OF_OUTPUT_STATISTICS = 5;
	private static final int OUTPUT_TAGS_BASE_INDEX = 2;
	private static final int OUTPUT_UNITS_BASE_INDEX = 3;
	private static final int OUTPUT_STATS_BASE_INDEX = 4;
	private static final int OUTPUT_DELAYS_BASE_INDEX = 5;
	private static final int NUMBER_OF_INPUT_STATISTICS = 5;
	private static final int INPUTS_BASE_INDEX = 2;
	private static final int INPUT_TAGS_BASE_INDEX = 3;
	private static final int INPUT_UNITS_BASE_INDEX = 4;
	private static final int INPUT_STATS_BASE_INDEX = 5;
	private static final int INPUT_DELAYS_BASE_INDEX = 6;

	private static final int HOUR = 1;
	private static final int MINUTE = 2;
	private static final int SECOND = 3;

	private static final int ANY_INTEGER = 0;

	private boolean debugFlag;
	private EnsembleModel sutModel;
	private Matrix matrixXUsedToEvaluate;
	private Matrix evaluatedMatrixY;
	private NolModel2Stub sut;
	private Preprocessor sutPreprocessor;
	private Random randomGenerator;

	@Before
	public void setup() {
		debugFlag = DEBUG.debugFlag;
		DEBUG.debugFlag = true;
		randomGenerator = new Random();
	}

	@After
	public void cleanup() {
		DEBUG.debugFlag = debugFlag;
	}

	@Test
	public void test_getMinimumInputs_Always_ReturnsModelInputsCount() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(sutModel.getNin(), sut.getMinimumInputs());
	}

	@Test
	public void test_getMaximumInputs_Always_ReturnsModelInputsCount() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(sutModel.getNin(), sut.getMaximumInputs());
	}

	@Test
	public void test_getNumberOfOutputs_Always_ReturnsModelOutputsCount() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(sutModel.getNout(), sut.getNumberOfOutputs(ANY_INTEGER));
	}

	@Test
	public void test_isAutoRecursiveModel_InputsAreEmptyAndOutputsAreNotEmpty_ReturnsTrue() throws MathException {
		// Arrange
		Vector<String> outs = createVector(new String[] { "Output 1" });
		sut = createSutWithOutputs(outs, new Vector<long[]>());

		// Act & Assert
		assertTrue(sut.isAutoRecursiveModel());
	}

	@Test
	public void test_isAutoRecursiveModel_InputsAreNotEmpty_ReturnsFalse() throws MathException {
		// Arrange
		Vector<String> ins = createVector(new String[] { "Input 1" });
		Vector<String> outs = createVector(new String[] { "Output 1" });
		sut = createSut(ins, outs, new Vector<long[]>(), new Vector<long[]>());

		// Act & Assert
		assertFalse(sut.isAutoRecursiveModel());
	}

	@Test
	public void test_isAutoRecursiveModel_OutputsAreEmpty_ReturnsFalse() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertFalse(sut.isAutoRecursiveModel());
	}

	@Test
	public void test_isRecursiveModel_OutputDelaysAreZero_ReturnsFalse() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output 1" }), createVector(new long[] { 0 }));

		// Act & Assert
		assertFalse(sut.isRecursiveModel());
	}

	@Test
	public void test_isRecursiveModel_OutputDelaysAreNonZero_ReturnsTrue() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output 1" }), createVector(new long[] { 1 }));

		// Act & Assert
		assertTrue(sut.isRecursiveModel());
	}

	@Test
	public void test_evaluate_always_invokesEnsembleModelEvaluate() throws MathException {
		// Arrange
		sut = createSut();
		Vector<double[]> inputs = createVector(new double[][] { { 0.0, 1.0 }, { 2.0, 3.0 } });
		Vector<double[]> outputs = createVector(new double[][] { { 4.0, 5.0 }, { 6.0, 7.0 } });

		// Act
		sut.evaluate(new long[0], inputs, outputs);

		// Assert
		verify(sutModel).evaluate(Matchers.any(Matrix.class), Matchers.any(Matrix.class));
	}

	@Test
	public void test_evaluate_always_passesCorrectMatrixXToEvaluate() throws MathException {
		// Arrange
		sut = createSut();
		Vector<double[]> inputs = createVector(new double[][] { { 0.0, 1.0 }, { 2.0, 3.0 } });
		Vector<double[]> outputs = createVector(new double[][] { { 4.0, 5.0 }, { 6.0, 7.0 } });

		// Act
		sut.evaluate(new long[0], inputs, outputs);

		// Assert
		for (int r = 0; r < inputs.size(); r++) {
			for (int c = 0; c < inputs.get(0).length; c++) {
				assertThat(matrixXUsedToEvaluate.get(r, c), is(equalTo(inputs.get(c)[r])));
			}
		}
	}

	@Test
	public void test_evaluate_always_setsOutputBasedOnEnsembleModelEvaluation() throws MathException {
		// Arrange
		sut = createSut();
		Vector<double[]> inputs = createVector(new double[][] { { 0.0, 1.0 }, { 2.0, 3.0 } });
		Vector<double[]> outputs = createVector(new double[][] { { 4.0, 5.0 }, { 6.0, 7.0 }, { 8.0, 9.0 } });

		// Act
		sut.evaluate(new long[0], inputs, outputs);

		// Assert
		Matlib.transpose(evaluatedMatrixY, evaluatedMatrixY);
		double[][] outputArray = Matlib.create2DArray(evaluatedMatrixY);
		for (int c = 0; c < evaluatedMatrixY.getCols(); c++) {
			for (int r = 0; r < outputArray.length; r++) {
				assertThat(outputs.get(r)[c], is(equalTo(outputArray[r][c])));
			}
		}
	}

	@Test
	public void test_evaluate_always_setsOutputBasedOnSutModelEvaluation() throws MathException {
		// Arrange
		sut = createSut();
		Vector<double[]> inputs = createVector(new double[][] { { 0.0, 1.0 }, { 2.0, 3.0 } });
		Vector<double[]> outputs = createVector(new double[][] { { 4.0, 5.0 }, { 6.0, 7.0 }, { 8.0, 9.0 } });

		// Act
		sut.evaluate(new long[0], inputs, outputs);

		// Assert
		verify(sutModel).evaluate(Matchers.any(Matrix.class), Matchers.any(Matrix.class));
	}

	@Test
	public void test_getInputVarNames_Always_ReturnsInputs() throws MathException {
		// Arrange
		Vector<String> ins = createVector(new String[] { "Input 1" });
		sut = createSutWithInputs(ins, new Vector<long[]>());

		// Act & Assert
		assertEquals(ins, sut.getInputVarNames());
	}

	@Test
	public void test_getOutputVarNames_Always_ReturnsOutputs() throws MathException {
		// Arrange
		Vector<String> outs = createVector(new String[] { "Output 1" });
		sut = createSutWithOutputs(outs, new Vector<long[]>());

		// Act & Assert
		assertEquals(outs, sut.getOutputVarNames());
	}

	@Test
	public void test_getModel_Always_ReturnsModel() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(sutModel, sut.getModel());
	}

	@Test
	public void test_getComments_Always_ReturnsComments() throws MathException {
		// Arrange
		String comment = "NolModel2 Comment";
		sut = createSut();
		sut.setComment(comment);

		// Act & Assert
		assertEquals(comment, sut.getComment());
	}

	@Test
	public void test_NewInstance_Always_SetsDelayTimeUnitAsMinute() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(MINUTE, sut.getDelayTimeUnit());
	}

	@Test
	public void test_getDelayTimeUnit_WhenChangedToHour_ReturnsHour() throws MathException {
		// Arrange
		sut = createSut();
		sut.setDelayTimeUnit(HOUR);

		// Act & Assert
		assertEquals(HOUR, sut.getDelayTimeUnit());
	}

	@Test
	public void test_getDelayTimeUnit_WhenChangedToSecond_ReturnsSecond() throws MathException {
		// Arrange
		sut = createSut();
		sut.setDelayTimeUnit(SECOND);

		// Act & Assert
		assertEquals(SECOND, sut.getDelayTimeUnit());
	}

	@Test
	public void test_NewInstance_Always_SetsHasTimeStampsAsTrue() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertTrue(sut.getHasTimeStamps());
	}

	@Test
	public void test_getHasTimeStamps_WhenSetToFalse_ReturnsFalse() throws MathException {
		// Arrange
		sut = createSut();
		sut.setHasTimeStamps(false);

		// Act & Assert
		assertFalse(sut.getHasTimeStamps());
	}

	@Test
	public void test_NewInstance_Always_SetsIsTrainedAsFalse() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertFalse(sut.isTrained());
	}

	@Test
	public void test_isTrained_WhenSetToTrue_ReturnsTrue() throws MathException {
		// Arrange
		sut = createSut();
		sut.setIsTrained(true);

		// Act & Assert
		assertTrue(sut.isTrained());
	}

	@Test
	public void test_getInputDelays_Always_ReturnsInputDelays() throws MathException {
		// Arrange
		long[] delays = new long[] { 0, 0, 1 };
		sut = createSutWithInputs(new Vector<String>(), createVector(delays));

		// Act & Assert
		assertTrue(sut.getInputDelays().contains(delays));
	}

	@Test
	public void test_getOutputDelays_Always_ReturnsOutputDelays() throws MathException {
		// Arrange
		long[] delays = new long[] { 0, 0, 1 };
		sut = createSutWithOutputs(new Vector<String>(), createVector(delays));

		// Act & Assert
		assertTrue(sut.getOutputDelays().contains(delays));
	}

	@Test
	public void test_getInputs_Always_ReturnsInputs() throws MathException {
		// Arrange
		Vector<String> ins = createVector(new String[] { "Input 1" });
		sut = createSutWithInputs(ins, new Vector<long[]>());

		// Act & Assert
		assertEquals(ins, sut.getInputs());
	}

	@Test
	public void test_getOutputs_Always_ReturnsOutputs() throws MathException {
		// Arrange
		Vector<String> outs = createVector(new String[] { "Output 1" });
		sut = createSutWithOutputs(outs, new Vector<long[]>());

		// Act & Assert
		assertEquals(outs, sut.getOutputs());
	}

	@Test
	public void test_getPreprocessor_Always_ReturnsPreprocessor() throws MathException {
		// Arrange
		sut = createSut();
		Preprocessor preprocessor = mock(Preprocessor.class);
		sut.getPreprocessor(preprocessor);

		// Act & Assert
		assertEquals(preprocessor, sut.getPreprocessor());
	}

	@Test
	public void test_toString_Always_ReturnsName() throws MathException {
		// Arrange
		String name = "NolModel2 Name";
		sut = createSut();
		sut.setName(name);

		// Act & Assert
		assertEquals(name, sut.toString());
	}

	@Test
	public void test_modelToString_Always_ReturnsFormattedStringOfInputs() throws MathException {
		// Arrange
		Vector<String> ins = createVector(new String[] { "Input 1", "Input 2" });
		sut = createSutWithInputs(ins, new Vector<long[]>());
		String name = "Model Name";
		sut.setName(name);

		// Act & Assert
		assertEquals(name + "(" + ins.get(0) + "," + ins.get(1) + ")", sut.modelToString());
	}

	@Test
	public void test_getNin_Always_ReturnsModelInputsCount() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(sutModel.getNin(), sut.getNin());
	}

	@Test
	public void test_getNout_Always_ReturnsModelOutputsCount() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(sutModel.getNout(), sut.getNout());
	}

	@Test
	public void test_getArchitectureParameters_Always_ReturnsModelArchitectureParameters() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertEquals(sutModel.getArchitectureParameters(), sut.getArchitectureParameters());
	}

	@Test
	public void test_initTransient_PreprocessorHashCodeIsMatched_UpdatesPreprocessor() throws MathException {
		// Arrange
		sut = createSut();

		// Creating project
		Project project = mock(Project.class);
		Preprocessor newPreprocessor = sutPreprocessor;
		Vector<Preprocessor> preprocessors = new Vector<Preprocessor>();
		preprocessors.add(createPreprocessor("Preprocessor 1"));
		preprocessors.add(newPreprocessor);
		when(project.getPreprocessors()).thenReturn(preprocessors);

		// Removing exiting preprocessor
		sut.getPreprocessor(null);

		// Act
		sut.initTransient(project);

		// Assert
		assertEquals(newPreprocessor, sut.getPreprocessor());
	}

	@Test
	public void test_getVariableFromVariableName_ProcessedDataIsEmpty_ReturnsNull() throws MathException {
		// Arrange
		sut = createSut();
		String varName = "Variable Name";
		Vector<DataSeries> processedData = createProcessedData();

		// Act
		assertNull(sut.getVariableFromVariableName(processedData, varName));
	}

	@Test
	public void test_getVariableFromVariableName_ProcessedDataDoesNotContainVariable_ReturnsNull()
			throws MathException {
		// Arrange
		sut = createSut();
		String varName = "Variable 1";
		Vector<DataSeries> processedData = createProcessedData("Variable 2");

		// Act & Assert
		assertNull(sut.getVariableFromVariableName(processedData, varName));
	}

	@Test
	public void test_getVariableFromVariableName_ProcessedDataContainsVariable_ReturnsVariable() throws MathException {
		// Arrange
		sut = createSut();
		String varName = "Variable 1";
		Vector<DataSeries> processedData = createProcessedData(varName);

		// Act
		Variable result = sut.getVariableFromVariableName(processedData, varName);

		// Assert
		assertNotNull(result);
		assertEquals(varName, result.getName());
	}

	@Test
	public void test_getRequiredHistoryLength_DoesNotHaveTimeStamps_ReturnsZero() throws MathException {
		// Arrange
		sut = createSut();
		sut.setHasTimeStamps(false);

		// Act & Assert
		assertEquals(0L, sut.getRequiredHistoryLength());
	}

	@Test
	public void test_getRequiredHistoryLength_HasTimeStamps_ReturnsLongestInputDelay() throws MathException {
		// Arrange
		long maxDelay = 3;
		sut = createSutWithInputs(createVector(new String[] { "Input 1" }),
				createVector(new long[] { 0, 1, maxDelay, 2 }));
		sut.setHasTimeStamps(true);

		// Act & Assert
		assertEquals(maxDelay, sut.getRequiredHistoryLength());
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_startsWithMethodName() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act & Assert
		assertThat(sut.getModelContents(), codeStartsWith("double * " + sut.getName() + "(double x0,double x1){"));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_endsWithMethodClosingBracket() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act
		String result = sut.getModelContents();
		assertThat(result, codeEndsWith("}"));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_declaresVectorsInTheBeginning() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act && Assert
		assertThat(sut.getModelContents(), codeContains(
				"y = vector(m);yp = vector(m);yp1 = vector(m);yp2 = vector(m);yp3 = vector(m);yp4 = vector(m);yp5 = vector(m);yy = matrix(nm,m);"));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_containsCopyVectorSelectionOne() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act & Assert
		assertThat(sut.getModelContents(), codeContains(
				"run_bpn(x,yp1,nlayer1,n11,n12,n13,0,0,tf1,w11,w12,NULL,NULL);if(nm == 1) {copyvector(yp1,y,m);free_vector(yp);free_vector(yp1);free_vector(yp2);free_vector(yp3);free_vector(yp4);free_vector(yp5);return y; }"));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_containsCopyVectorSelectionTwo() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act & Assert
		assertThat(sut.getModelContents(), codeContains(
				"run_bpn(x,yp2,nlayer2,n21,n22,n23,n24,0,tf2,w21,w22,w23,NULL);if(nm == 2) {copymatrix(yy,yp1,yp2,NULL,NULL,NULL,2,m);findmedian(yy,yp,m,2);copyvector(yp,y,m);free_vector(yp);free_vector(yp1);free_vector(yp2);free_vector(yp3);free_vector(yp4);free_vector(yp5);return y; }"));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_containsCopyVectorSelectionThree() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act & Assert
		assertThat(sut.getModelContents(), codeContains(
				"run_bpn(x,yp3,nlayer3,n31,n32,n33,0,0,tf3,w31,w32,NULL,NULL);if(nm == 3) {copymatrix(yy,yp1,yp2,yp3,NULL,NULL,3,m);findmedian(yy,yp,m,3);copyvector(yp,y,m);free_vector(yp);free_vector(yp1);free_vector(yp2);free_vector(yp3);free_vector(yp4);free_vector(yp5);return y; }"));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_containsCopyVectorSelectionFour() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act & Assert
		assertThat(sut.getModelContents(), codeContains(
				"run_bpn(x,yp4,nlayer4,n41,n42,n43,0,0,tf4,w41,w42,NULL,NULL);if(nm == 4){copymatrix(yy,yp1,yp2,yp3,yp4,NULL,4,m);findmedian(yy,yp,m,4);copyvector(yp,y,m);free_vector(yp);free_vector(yp1);free_vector(yp2);free_vector(yp3);free_vector(yp4);free_vector(yp5);return y; }"));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getModelContents_Always_containsCopyVectorSelectionFive() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input 1", "Input 2" }), createVector(new long[0]));

		// Act & Assert
		assertThat(sut.getModelContents(), codeContains(
				"run_bpn(x,yp5,nlayer5,n51,n52,n53,n54,0,tf5,w51,w52,w53,NULL);copymatrix(yy,yp1,yp2,yp3,yp4,yp5,5,m);findmedian(yy,yp,m,5);copyvector(yp,y,m);free_vector(yp);free_vector(yp1);free_vector(yp2);free_vector(yp3);free_vector(yp4);free_vector(yp5);return y;  }"));
	}

	@Test
	public void test_getModelString_always_returnsNameWithInputVarNames() throws MathException {
		// Arrange
		sut = createSutWithInputs(createVector(new String[] { "Input1", "Input2" }), createVector(new long[0]));

		// Act & Assert
		assertThat(sut.getModelString(), is(equalTo(
				sut.getName() + "(" + sut.getInputVarNames().get(0) + "," + sut.getInputVarNames().get(1) + ")")));
	}

	@Test
	public void test_getParametersVector_always_returnsModelParametersVector() throws MathException {
		// Arrange
		sut = createSut();

		// Act & Assert
		assertThat(sut.getParametersVector(), is(equalTo(sutModel.getParametersVector())));
	}

	@Test
	public void test_setParametersVector_always_setsModelParametersVector() throws MathException {
		// Arrange
		sut = createSut();
		Vector<String> parametersVector = new Vector<String>();
		parametersVector.add("newParameter1");

		// Act
		sut.setParametersVector(parametersVector);

		// Assert
		verify(sutModel).setParametersVector(parametersVector);
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsModelName() throws MathException {
		// Arrange
		sut = createSut();

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		assertThat(result.get(0), is(equalTo(sut.getName())));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsModelComment() throws MathException {
		// Arrange
		sut = createSut();
		sut.setComment("Model Comment");

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		assertThat(result.get(1), is(equalTo(sut.getComment())));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_hasTimeStamps_returnsHasTimeStampsAsTrue() throws MathException {
		// Arrange
		sut = createSut();
		sut.setHasTimeStamps(true);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		assertThat(result.get(2), is(equalTo(new Boolean(true))));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_doesNotHaveTimeStamps_returnsHasTimeStampsAsFalse() throws MathException {
		// Arrange
		sut = createSut();
		sut.setHasTimeStamps(false);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		assertThat(result.get(2), is(equalTo(new Boolean(false))));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_isNotTrained_returnsModelRateValueAsZero() throws MathException {
		// Arrange
		sut = createSut();

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		assertThat(result.get(3), is(equalTo(0.0)));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_isTrained_returnsModelRateValueAsCalculatedValue() throws MathException {
		// Arrange
		sut = createSut();
		sut.setIsTrained(true);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		assertThat(result.get(3), is(equalTo(expectedModelRateValue())));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsOutputsSize() throws MathException {
		// Arrange
		sut = createSut();

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		assertThat(result.get(4), is(equalTo(sut.getOutputs().size())));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsOutputs() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String output : (Vector<String>) sut.getOutputs()) {
			assertThat(result.get(OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * idx++)), is(equalTo(output)));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsTrainingRmse() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (double rmse : expectedTrainingRmse()) {
			assertThat(result.get(TRAINING_RMSE_BASE_INDEX + (NUMBER_OF_STATISTICS * idx++)),
					is(equalTo(Utilities.formatDouble(rmse, DIGITS))));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsTestingCorrcoef() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (double corrcoef : expectedTestingCorr()) {
			assertThat(result.get(TESTING_CORRCOEF_BASE_INDEX + (NUMBER_OF_STATISTICS * idx++)),
					is(equalTo(Utilities.formatDouble(corrcoef, DIGITS))));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsTestingRmse() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (double rmse : expectedTestingRmse()) {
			assertThat(result.get(TESTING_RMSE_BASE_INDEX + (NUMBER_OF_STATISTICS * idx++)),
					is(equalTo(Utilities.formatDouble(rmse, DIGITS))));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsTrainingCorrcoef() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (double corrcoef : expectedTrainingCorr()) {
			assertThat(result.get(TRAINING_CORRCOEF_BASE_INDEX + (NUMBER_OF_STATISTICS * idx++)),
					is(equalTo(Utilities.formatDouble(corrcoef, DIGITS))));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsOutputTags() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size()) + OUTPUT_TAGS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String varName : (Vector<String>) sut.getOutputVarNames()) {
			Variable variable = sutPreprocessor.getVariableFromVariableName(varName);
			assertThat(result.get(baseIndex + (NUMBER_OF_OUTPUT_STATISTICS * idx++)), is(equalTo(variable.getTag())));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsOutputUnits() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size()) + OUTPUT_UNITS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String varName : (Vector<String>) sut.getOutputVarNames()) {
			Variable variable = sutPreprocessor.getVariableFromVariableName(varName);
			assertThat(result.get(baseIndex + (NUMBER_OF_OUTPUT_STATISTICS * idx++)), is(equalTo(variable.getUnit())));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsOutputStats() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size()) + OUTPUT_STATS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String varName : (Vector<String>) sut.getOutputVarNames()) {
			Variable variable = sutPreprocessor.getVariableFromVariableName(varName);
			assertThat(result.get(baseIndex + (NUMBER_OF_OUTPUT_STATISTICS * idx++)),
					is(equalTo(variable.getStatistics())));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsOutputDelays() throws MathException {
		// Arrange
		sut = createSutWithOutputs(createVector(new String[] { "Output1", "Output2" }),
				createVector(new long[][] { { 0, 1 }, { 2, 3 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size())
				+ OUTPUT_DELAYS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (long[] delay : (Vector<long[]>) sut.getOutputDelays()) {
			assertThat(result.get(baseIndex + (NUMBER_OF_OUTPUT_STATISTICS * idx)), is(equalTo(delay)));
			idx++;
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsInputs() throws MathException {
		// Arrange
		sut = createSut(createVector(new String[] { "Input1", "Input2" }),
				createVector(new String[] { "Output1", "Output2" }), createVector(new long[][] { { 0, 1 }, { 2, 3 } }),
				createVector(new long[][] { { 4, 5 }, { 6, 7 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size())
				+ (NUMBER_OF_OUTPUT_STATISTICS * sut.getOutputs().size()) + INPUTS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String varName : (Vector<String>) sut.getInputs()) {
			assertThat(result.get(baseIndex + (NUMBER_OF_INPUT_STATISTICS * idx++)), is(equalTo(varName)));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsInputTags() throws MathException {
		// Arrange
		sut = createSut(createVector(new String[] { "Input1", "Input2" }),
				createVector(new String[] { "Output1", "Output2" }), createVector(new long[][] { { 0, 1 }, { 2, 3 } }),
				createVector(new long[][] { { 4, 5 }, { 6, 7 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size())
				+ (NUMBER_OF_OUTPUT_STATISTICS * sut.getOutputs().size()) + INPUT_TAGS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String varName : (Vector<String>) sut.getInputVarNames()) {
			Variable variable = sutPreprocessor.getVariableFromVariableName(varName);
			assertThat(result.get(baseIndex + (NUMBER_OF_INPUT_STATISTICS * idx++)), is(equalTo(variable.getTag())));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsInputUnits() throws MathException {
		// Arrange
		sut = createSut(createVector(new String[] { "Input1", "Input2" }),
				createVector(new String[] { "Output1", "Output2" }), createVector(new long[][] { { 0, 1 }, { 2, 3 } }),
				createVector(new long[][] { { 4, 5 }, { 6, 7 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size())
				+ (NUMBER_OF_OUTPUT_STATISTICS * sut.getOutputs().size()) + INPUT_UNITS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String varName : (Vector<String>) sut.getInputVarNames()) {
			Variable variable = sutPreprocessor.getVariableFromVariableName(varName);
			assertThat(result.get(baseIndex + (NUMBER_OF_INPUT_STATISTICS * idx++)), is(equalTo(variable.getUnit())));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsInputStats() throws MathException {
		// Arrange
		sut = createSut(createVector(new String[] { "Input1", "Input2" }),
				createVector(new String[] { "Output1", "Output2" }), createVector(new long[][] { { 0, 1 }, { 2, 3 } }),
				createVector(new long[][] { { 4, 5 }, { 6, 7 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size())
				+ (NUMBER_OF_OUTPUT_STATISTICS * sut.getOutputs().size()) + INPUT_STATS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String varName : (Vector<String>) sut.getInputVarNames()) {
			Variable variable = sutPreprocessor.getVariableFromVariableName(varName);
			assertThat(result.get(baseIndex + (NUMBER_OF_INPUT_STATISTICS * idx++)),
					is(equalTo(variable.getStatistics())));
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsInputDelays() throws MathException {
		// Arrange
		sut = createSut(createVector(new String[] { "Input1", "Input2" }),
				createVector(new String[] { "Output1", "Output2" }), createVector(new long[][] { { 0, 1 }, { 2, 3 } }),
				createVector(new long[][] { { 4, 5 }, { 6, 7 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size())
				+ (NUMBER_OF_OUTPUT_STATISTICS * sut.getOutputs().size()) + INPUT_DELAYS_BASE_INDEX;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (long[] delay : (Vector<long[]>) sut.getInputDelays()) {
			assertThat(result.get(baseIndex + (NUMBER_OF_INPUT_STATISTICS * idx)), is(equalTo(delay)));
			idx++;
		}
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_getWholeParametersVector_always_returnsModelParameters() throws MathException {
		// Arrange
		sut = createSut(createVector(new String[] { "Input1", "Input2" }),
				createVector(new String[] { "Output1", "Output2" }), createVector(new long[][] { { 0, 1 }, { 2, 3 } }),
				createVector(new long[][] { { 4, 5 }, { 6, 7 } }));
		sut.setIsTrained(true);
		int baseIndex = OUTPUTS_BASE_INDEX + (NUMBER_OF_STATISTICS * sut.getOutputs().size())
				+ (NUMBER_OF_OUTPUT_STATISTICS * sut.getOutputs().size())
				+ (NUMBER_OF_INPUT_STATISTICS * sut.getInputs().size()) + 2;

		// Act
		Vector<Object> result = sut.getWholeParametersVector();

		// Assert
		int idx = 0;
		for (String parameter : (Vector<String>) sutModel.getParametersVector()) {
			assertThat(result.get(baseIndex + (NUMBER_OF_INPUT_STATISTICS * idx)), is(equalTo(parameter)));
			idx++;
		}
	}

	@Test
	public void test_calculateModelStatistics_isNotTrained_doesNotCalculateModelRateValue() throws MathException {
		// Arrange
		sut = createSut();

		// Act
		sut.calculateModelStatistics();

		// Assert
		assertThat(sut.getModelRate(), is(equalTo(0.0)));
	}

	@Test
	public void test_calculateModelStatistics_isTrained_calculatesModelRateValue() throws MathException {
		// Arrange
		sut = createSut();
		sut.setIsTrained(true);

		// Act
		sut.calculateModelStatistics();

		// Assert
		assertThat(sut.getModelRate(), is(equalTo(expectedModelRateValue())));
	}

	@Test
	public void test_calculateModelStatistics_isNotTrained_doesNotCalculateTrainingRmse() throws MathException {
		// Arrange
		sut = createSut();

		// Act
		sut.calculateModelStatistics();

		// Assert
		assertThat(sut.getTrainingRmse().size(), is(equalTo(0)));
	}

	@SuppressWarnings("unchecked")
	@Test
	public void test_calculateModelStatistics_isTrained_calculatesTrainingRmse() throws MathException {
		// Arrange
		sut = createSut();
		sut.setIsTrained(true);

		// Act
		sut.calculateModelStatistics();

		// Assert
		for (double rmse : expectedTrainingRmse()) {
			assertThat(sut.getTrainingRmse(), contains(rmse));
		}
	}

	@Test
	public void test_calculateModelStatistics_isNotTrained_calculatesTestingRmse() throws MathException {
		// Arrange
		sut = createSut();

		// Act
		sut.calculateModelStatistics();

		// Assert
		assertThat(sut.getTestingRmse().size(), is(equalTo(0)));
	}

	// -- Helper Methods --

	private NolModel2Stub createSut() throws MathException {
		Vector<String> ins = new Vector<String>();
		Vector<String> outs = new Vector<String>();
		Vector<long[]> iDelays = new Vector<long[]>();
		Vector<long[]> oDelays = new Vector<long[]>();

		return createSut(ins, outs, iDelays, oDelays);
	}

	private NolModel2Stub createSutWithInputs(Vector<String> ins, Vector<long[]> iDelays) throws MathException {
		Vector<String> outs = new Vector<String>();
		Vector<long[]> oDelays = new Vector<long[]>();

		return createSut(ins, outs, iDelays, oDelays);
	}

	private NolModel2Stub createSutWithOutputs(Vector<String> outs, Vector<long[]> oDelays) throws MathException {
		Vector<String> ins = new Vector<String>();
		Vector<long[]> iDelays = new Vector<long[]>();

		return createSut(ins, outs, iDelays, oDelays);
	}

	private NolModel2Stub createSut(Vector<String> ins, Vector<String> outs, Vector<long[]> iDelays,
			Vector<long[]> oDelays) throws MathException {
		sutModel = createSutModel();
		sutPreprocessor = createPreprocessor("Sut Preprocessor Name", ins, outs);
		String name = "NolModel2Name";

		return new NolModel2Stub(sutModel, name, outs, ins, oDelays, iDelays, sutPreprocessor);
	}

	private Preprocessor createPreprocessor(String name) {
		Preprocessor preprocessor = mock(Preprocessor.class);
		when(preprocessor.getName()).thenReturn(name);
		when(preprocessor.getItsHashCode()).thenReturn(preprocessor.hashCode());
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
			variable.setTag(varName + "Tag");
			variable.setUnit(varName + "Unit");
			variable.setStatistics(new double[] { randomGenerator.nextInt(100), randomGenerator.nextInt(100) });
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

	private Vector<DataSeries> createProcessedData() {
		Vector<DataSeries> processedData = new Vector<DataSeries>();
		return processedData;
	}

	private Vector<DataSeries> createProcessedData(String varName) {
		Vector<DataSeries> processedData = new Vector<DataSeries>();

		Variable variable = new Variable();
		variable.setName(varName);

		DataSeries dataSeries = mock(DataSeries.class);
		when(dataSeries.getVarByName(varName)).thenReturn(variable);
		processedData.add(dataSeries);

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

	private Vector<long[]> createVector(long[][] elements) {
		Vector<long[]> vector = new Vector<long[]>();

		for (long[] element : elements) {
			vector.add(element);
		}

		return vector;
	}

	private Vector<double[]> createVector(double[][] elements) {
		Vector<double[]> vector = new Vector<double[]>();

		for (double[] element : elements) {
			vector.add(element);
		}

		return vector;
	}

	private EnsembleModel createSutModel() throws MathException {
		sutModel = mock(EnsembleModel.class);
		when(sutModel.getNin()).thenReturn(1);
		when(sutModel.getNout()).thenReturn(2);
		when(sutModel.size()).thenReturn(3);
		when(sutModel.getModelCString()).thenReturn("sutModelCString;");
		doAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				Matrix matrixX = invocation.getArgumentAt(0, Matrix.class);
				Matrix matrixY = invocation.getArgumentAt(1, Matrix.class);

				matrixXUsedToEvaluate = clone(matrixX);

				// Randomly setting output values

				for (int r = 0; r < matrixY.getRows(); r++) {
					for (int c = 0; c < matrixY.getRows(); c++) {
						matrixY.set(r, c, randomGenerator.nextInt(100));
					}
				}

				evaluatedMatrixY = clone(matrixY);

				return null;
			}

			private Matrix clone(Matrix matrix) {
				Matrix cloned = Matlib.createMatrix(matrix.getRows(), matrix.getCols());

				for (int r = 0; r < matrix.getRows(); r++) {
					for (int c = 0; c < matrix.getRows(); c++) {
						cloned.set(r, c, matrix.get(r, c));
					}
				}

				return cloned;
			}
		}).when(sutModel).evaluate(Matchers.any(Matrix.class), Matchers.any(Matrix.class));

		Vector<String> parametersVector = new Vector<String>();
		parametersVector.add("param1");
		when(sutModel.getParametersVector()).thenReturn(parametersVector);

		ArchitectureParameters parameters = new ArchitectureParameters(0, 0, 0, 0);
		when(sutModel.getArchitectureParameters()).thenReturn(parameters);

		arrangeSubModels(sutModel);

		return sutModel;
	}

	private void arrangeSubModels(EnsembleModel model) {
		Vector<EnsembleModel> submodels = new Vector<EnsembleModel>();
		for (int i = 0; i < model.size(); i++) {
			EnsembleModel submodel = mock(EnsembleModel.class);

			// Training Results

			ValidationParameters trainingResults = mock(ValidationParameters.class);

			Matrix trainingRmse = Matlib.createMatrix(1, 2);
			trainingRmse.set(0, 0, randomGenerator.nextInt(100));
			trainingRmse.set(0, 1, randomGenerator.nextInt(100));
			trainingResults.rmse = trainingRmse;

			Matrix trainingCorrcoef = Matlib.createMatrix(1, 2);
			trainingCorrcoef.set(0, 0, randomGenerator.nextInt(100));
			trainingCorrcoef.set(0, 1, randomGenerator.nextInt(100));
			trainingResults.corrcoef = trainingCorrcoef;

			submodel.trainingResults = trainingResults;

			// Testing Results

			ValidationParameters testingResults = mock(ValidationParameters.class);

			Matrix testingRmse = Matlib.createMatrix(1, 2);
			testingRmse.set(0, 0, randomGenerator.nextInt(100));
			testingRmse.set(0, 1, randomGenerator.nextInt(100));
			testingResults.rmse = testingRmse;

			Matrix testingCorrcoef = Matlib.createMatrix(1, 2);
			testingCorrcoef.set(0, 0, randomGenerator.nextInt(100));
			testingCorrcoef.set(0, 1, randomGenerator.nextInt(100));
			testingResults.corrcoef = testingCorrcoef;

			submodel.testingResults = testingResults;

			submodels.add(submodel);
		}

		when(model.getModel(Matchers.anyInt())).thenAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				int idx = invocation.getArgumentAt(0, int.class);
				return submodels.get(idx);
			}
		});
	}

	private Double expectedModelRateValue() {
		int ensembleSize = sutModel.size();
		int nout = sutModel.getNout();

		double[] corr = new double[nout];
		double testingRate = 0;
		for (int j = 0; j < nout; j++) {
			corr[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) sutModel.getModel(i);
				ValidationParameters parmas = submodel.testingResults;
				corr[j] += parmas.corrcoef.get(j);
			}

			corr[j] /= ensembleSize;
		}

		for (int i = 0; i < nout; i++) {
			testingRate = testingRate + corr[i];
		}

		testingRate = testingRate / nout;

		corr = new double[nout];
		double trainingRate = 0;
		for (int j = 0; j < nout; j++) {
			corr[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) sutModel.getModel(i);
				corr[j] += submodel.trainingResults.corrcoef.get(j);
			}

			corr[j] /= ensembleSize;
		}

		for (int i = 0; i < nout; i++) {
			trainingRate = trainingRate + corr[i];
		}

		trainingRate = trainingRate / nout;

		return new Double((testingRate + trainingRate) / 2);
	}

	private double[] expectedTrainingRmse() {
		int ensembleSize = sutModel.size();
		int nout = sutModel.getNout();

		double[] rmse = new double[nout];
		for (int j = 0; j < nout; j++) {
			rmse[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) sutModel.getModel(i);
				ValidationParameters parmas = submodel.trainingResults;
				rmse[j] += parmas.rmse.get(j);
			}

			rmse[j] /= ensembleSize;
		}

		return rmse;
	}

	private double[] expectedTestingRmse() {
		int ensembleSize = sutModel.size();
		int nout = sutModel.getNout();

		double[] rmse = new double[nout];
		for (int j = 0; j < nout; j++) {
			rmse[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) sutModel.getModel(i);
				ValidationParameters parmas = submodel.testingResults;
				rmse[j] += parmas.rmse.get(j);
			}

			rmse[j] /= ensembleSize;
		}

		return rmse;
	}

	private double[] expectedTrainingCorr() {
		int ensembleSize = sutModel.size();
		int nout = sutModel.getNout();

		double[] corr = new double[nout];
		for (int j = 0; j < nout; j++) {
			corr[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) sutModel.getModel(i);
				ValidationParameters parmas = submodel.trainingResults;
				corr[j] += parmas.corrcoef.get(j);
			}

			corr[j] /= ensembleSize;
		}

		return corr;
	}

	private double[] expectedTestingCorr() {
		int ensembleSize = sutModel.size();
		int nout = sutModel.getNout();

		double[] corr = new double[nout];
		for (int j = 0; j < nout; j++) {
			corr[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) sutModel.getModel(i);
				ValidationParameters parmas = submodel.testingResults;
				corr[j] += parmas.corrcoef.get(j);
			}

			corr[j] /= ensembleSize;
		}

		return corr;
	}

	// -- Matchers --

	@SuppressWarnings({ "rawtypes" })
	private Matcher codeStartsWith(String expected) {
		return new BaseMatcher() {

			@Override
			public boolean matches(Object string) {
				String actual = (String) string;
				return actual.replace("\n", "").startsWith(expected.replace("\n", ""));
			}

			@Override
			public void describeTo(Description description) {
				description.appendText(expected);
			}
		};
	}

	@SuppressWarnings({ "rawtypes" })
	private Matcher codeContains(String expected) {
		return new BaseMatcher() {

			@Override
			public boolean matches(Object string) {
				String actual = (String) string;
				return actual.replace("\n", "").contains(expected.replace("\n", ""));
			}

			@Override
			public void describeTo(Description description) {
				description.appendText(expected);
			}
		};
	}

	@SuppressWarnings({ "rawtypes" })
	private Matcher codeEndsWith(String expected) {
		return new BaseMatcher() {

			@Override
			public boolean matches(Object string) {
				String actual = (String) string;
				return actual.replaceAll("\\s", "").endsWith(expected.replaceAll("\\s", ""));
			}

			@Override
			public void describeTo(Description description) {
				description.appendText(expected);
			}
		};
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	private Matcher contains(double expected) {
		return new BaseMatcher() {
			@Override
			public boolean matches(Object array) {
				Vector<String> actual = (Vector<String>) array;
				return actual.contains(Utilities.formatDouble(expected, DIGITS));
			}

			@Override
			public void describeTo(Description description) {
				description.appendText(new Double(expected).toString());
			}

		};
	}

	// -- NolModel2Stub --

	private class NolModel2Stub extends NolModel2 {
		private static final long serialVersionUID = 1L;

		public NolModel2Stub(EnsembleModel sutModel, String name, Vector<String> outs, Vector<String> ins,
				Vector<long[]> oDelays, Vector<long[]> iDelays, Preprocessor sutPreprocessor) {
			super(sutModel, name, outs, ins, oDelays, iDelays, sutPreprocessor);
		}

		@SuppressWarnings("rawtypes")
		@Override
		public Variable getVariableFromVariableName(Vector processedData, String varName) {
			return super.getVariableFromVariableName(processedData, varName);
		}
	}
}