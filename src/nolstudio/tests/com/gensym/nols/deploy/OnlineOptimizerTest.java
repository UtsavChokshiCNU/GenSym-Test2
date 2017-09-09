package com.gensym.nols.deploy;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.doNothing;
import static org.mockito.Mockito.inOrder;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;
import static org.powermock.api.mockito.PowerMockito.spy;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.OptionalDataException;
import java.io.StreamCorruptedException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Random;
import java.util.Vector;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.mockito.ArgumentCaptor;
import org.mockito.InOrder;
import org.mockito.Matchers;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.reflect.Whitebox;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.EnsembleModelEvent;
import com.gensym.math.datafit.EnsembleModelListener;
import com.gensym.math.datafit.Model;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.NolOptimization;
import com.gensym.nols.data.Variable;
import com.gensym.nols.data.VersionManagerForOnlineOptimizer;

public class OnlineOptimizerTest {
	private final static double DELTA = 0.1;
	private final static int OUTPUT = 0;
	private final static int MANIPULATED = 1;
	private final static int EXOGENOUS = 2;
	private final static int STATE = 3;
	private final static long TIME_IN_MILLI_SECONDS = 100;
	private final static String EXOGENOUS_VARIABLE = "NolOptimizeModelStub Exogenous Variable";
	private final static String MANIPULATED_EXOGENOUS_VARIABLE = "NolOptimizeModelStub Manipulated Exogenous Variable";
	private final static String MANIPULATED_VARIABLE = "NolOptimizeModelStub Manipulated Variable";
	private final static String STATE_VARIABLE = "NolOptimizeModelStub State Variable";

	@Rule
	public TemporaryFolder folder = new TemporaryFolder();

	private boolean autoStop;
	private boolean display;
	private boolean ensembleModelIsTrainedModel;
	private boolean ensembleModelListenerIsPassed;
	private boolean onlineModelListenerIsPassed;
	private boolean newTraining;
	private boolean stateEnsembleModelIsTrainedModel;
	private boolean stateModelExists;
	private boolean variablesAreAboveUpperBound;
	private boolean variablesAresBelowLowerBound;
	private boolean variablesAreWithinBounds;
	private EnsembleModel ensembleModel;
	private EnsembleModel stateEnsembleModel;
	private EnsembleModelEvent ensembleModelEvent;
	private File optimizationsFolder;
	private int ensembleModelEventType;
	private long trainingTime;
	private Matrix expectedModel2TrainInput;
	private Matrix expectedModel2TrainOutput;
	private Matrix expectedModel1TrainInput;
	private Matrix expectedModel1TrainOutput;
	private Model ensembleModelEventModel;
	private NolOnlineConsoleFrame onlineModelListenerOnlineConsole;
	private NolOptimization nolOptimization;
	private NolOptimizeModelStub optimizerModel;
	private OnlineOptimizer optimizer;
	private OnlineOptimizer sut;
	private PreprocessorStub optimizerModelPreprocessor;
	private String optimizationFileNameWithDirectory;
	private String optimizationFileNameWithoutDirectory;
	private String[] dataSeriesFileNames;
	private TrainableModel[] ensembleModels;
	private Vector<EnsembleModelListener> modelListeners;
	private VersionManagerForOnlineOptimizer versionManager;

	@Before
	public void setup() {
		autoStop = false;
		display = false;
		modelListeners = null;
		stateModelExists = true;
		trainingTime = 0;
		variablesAreAboveUpperBound = false;
		variablesAresBelowLowerBound = false;
		variablesAreWithinBounds = false;

		sut = new OnlineOptimizer();
	}

	@Test
	public void test_Name_Always_ValueIsPersisted() {
		// Arrange
		String name = "Optimization Problem Name";

		// Act
		sut.setName(name);

		// Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_Comment_Always_ValueIsPersisted() {
		// Arrange
		String comment = "Optimization Problem Comment";

		// Act
		sut.setComment(comment);

		// Assert
		assertEquals(comment, sut.getComment());
	}

	@Test
	public void test_ItsHashCode_Always_ReturnsHashCode() {
		// Arrange
		// No arrangements

		// Act & Arrange
		assertEquals(sut.hashCode(), sut.getItsHashCode());
	}

	@Test
	public void test_loadOptimizationWithDirectory_Always_CopiesOptimizer() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertEquals(optimizer.getName(), sut.getName());
		assertEquals(optimizer.getComment(), sut.getComment());
		assertEquals(optimizerModel.getName(), sut.getModel().getName());
	}

	@Test
	public void test_loadOptimizationWithoutDirectory_Always_CopiesOptimizer() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();

		// Act
		sut.loadOptimization(optimizationFileNameWithDirectory, null);

		// Assert
		assertEquals(optimizer.getName(), sut.getName());
		assertEquals(optimizer.getComment(), sut.getComment());
		assertEquals(optimizerModel.getName(), sut.getModel().getName());
	}

	@Test
	public void test_loadOptimization_Always_InvokesLoadOptimizationWithoutDirectory() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		OnlineOptimizer sutSpy = spy(sut);
		doNothing().when(sutSpy).loadOptimization(optimizationFileNameWithDirectory, null);

		// Act
		sutSpy.loadOptimization(optimizationFileNameWithDirectory);

		// Assert
		verify(sutSpy, times(1)).loadOptimization(optimizationFileNameWithDirectory, null);
	}

	@Test
	public void test_loadOptimization_Always_LoadsOutputVarNames() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableNames(optimizerModel.getOutputVarNames());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableNames(OUTPUT));
	}

	@Test
	public void test_loadOptimization_Always_LoadsManipulatedNames() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableNames(optimizerModel.getManipulate());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableNames(MANIPULATED));
	}

	@Test
	public void test_loadOptimization_Always_LoadsExogenousNames() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableNames(optimizerModel.getExogenous());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableNames(EXOGENOUS));
	}

	@Test
	public void test_loadOptimization_Always_LoadsStateNames() throws StreamCorruptedException, OptionalDataException,
			FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableNames(optimizerModel.getState());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableNames(STATE));
	}

	@Test
	public void test_loadOptimization_Always_LoadsOutputVarTags() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableTags(optimizerModel.getOutputVarNames());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableTags(OUTPUT));
	}

	@Test
	public void test_loadOptimization_Always_LoadsManipulatedTags() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableTags(optimizerModel.getManipulate());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableTags(MANIPULATED));
	}

	@Test
	public void test_loadOptimization_Always_LoadsExogenousTags() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableTags(optimizerModel.getExogenous());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableTags(EXOGENOUS));
	}

	@Test
	public void test_loadOptimization_Always_LoadsStateTags() throws StreamCorruptedException, OptionalDataException,
			FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableTags(optimizerModel.getState());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableTags(STATE));
	}

	@Test
	public void test_loadOptimization_Always_LoadsOutputVarUnits() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableUnits(optimizerModel.getOutputVarNames());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableUnits(OUTPUT));
	}

	@Test
	public void test_loadOptimization_Always_LoadsManipulatedUnits() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableUnits(optimizerModel.getManipulate());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableUnits(MANIPULATED));
	}

	@Test
	public void test_loadOptimization_Always_LoadsExogenousUnits() throws StreamCorruptedException,
			OptionalDataException, FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableUnits(optimizerModel.getExogenous());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableUnits(EXOGENOUS));
	}

	@Test
	public void test_loadOptimization_Always_LoadsStateUnits() throws StreamCorruptedException, OptionalDataException,
			FileNotFoundException, ClassNotFoundException, IOException, MathException {
		// Arrange
		arrangeForLoadOptimization();
		String[] expected = getVariableUnits(optimizerModel.getState());

		// Act
		sut.loadOptimization(optimizationFileNameWithoutDirectory, optimizationsFolder.getAbsolutePath());

		// Assert
		assertArrayEquals(expected, sut.getVariableUnits(STATE));
	}

	@Test
	public void test_getVariableNames_TypeIsInvalid_ReturnsNull() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		String[] result = sut.getVariableNames(-1);

		// Assert
		assertNull(result);
	}

	@Test
	public void test_getVariableTags_TypeIsInvalid_ReturnsNull() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		String[] result = sut.getVariableTags(-1);

		// Assert
		assertNull(result);
	}

	@Test
	public void test_getVariableUnits_TypeIsInvalid_ReturnsNull() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		String[] result = sut.getVariableUnits(-1);

		// Assert
		assertNull(result);
	}

	@Test
	public void test_getNumberOfVariables_TypeIsOutput_ReturnsOutputVariablesCount() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		int result = sut.getNumberOfVariables(OUTPUT);

		// Assert
		assertEquals(optimizerModel.getOutputVarNames().size(), result);
	}

	@Test
	public void test_getNumberOfVariables_TypeIsManipulated_ReturnsManipulatedCount() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		int result = sut.getNumberOfVariables(MANIPULATED);

		// Assert
		assertEquals(optimizerModel.getManipulate().size(), result);
	}

	@Test
	public void test_getNumberOfVariables_TypeIsExogenous_ReturnsExogenousCount() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		int result = sut.getNumberOfVariables(EXOGENOUS);

		// Assert
		assertEquals(optimizerModel.getExogenous().size(), result);
	}

	@Test
	public void test_getNumberOfVariables_TypeIsState_ReturnsStatesCount() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		int result = sut.getNumberOfVariables(STATE);

		// Assert
		assertEquals(optimizerModel.getState().size(), result);
	}

	@Test
	public void test_getNumberOfVariables_TypeIsInvalid_ReturnsZero() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		int result = sut.getNumberOfVariables(-1);

		// Assert
		assertEquals(0, result);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setValueByName_IsManipulatedExogenousVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByName(MANIPULATED_EXOGENOUS_VARIABLE, 100.0);
	}

	@Test
	public void test_setValueByName_IsManipulatedVariable_SetsValue() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByName(MANIPULATED_VARIABLE, 101.0);

		// Assert
		assertEquals(101.0, sut.getValueByName(MANIPULATED_VARIABLE), DELTA);
	}

	@Test
	public void test_setValueByName_IsExogenousVariable_SetsValue() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByName(EXOGENOUS_VARIABLE, 102.0);

		// Assert
		assertEquals(102.0, sut.getValueByName(EXOGENOUS_VARIABLE), DELTA);
	}

	@Test
	public void test_setValueByName_IsStateVariable_SetsValue() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByName(STATE_VARIABLE, 103.0);

		// Assert
		assertEquals(103.0, sut.getValueByName(STATE_VARIABLE), DELTA);
	}

	@Test
	public void test_getValueByName_IsValidVariable_ReturnsValue() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		Variable variable = optimizerModelPreprocessor.getVariableFromVariableName(optimizerModel.getOutputs().get(0));

		// Act
		sut.getValueByName(variable.getName());

		// Assert
		assertEquals(variable.getSTD(), sut.getValueByName(STATE_VARIABLE), DELTA);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getValueByName_InInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getValueByName("Invalid Variable Name");
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setValueByTag_IsManipulatedExogenousVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByTag(MANIPULATED_EXOGENOUS_VARIABLE + " Variable Tag", 100.0);
	}

	@Test
	public void test_setValueByTag_IsManipulatedVariable_SetsValue() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByTag(MANIPULATED_VARIABLE + " Tag", 101.0);

		// Assert
		assertEquals(101.0, sut.getValueByTag(MANIPULATED_VARIABLE + " Tag"), DELTA);
	}

	@Test
	public void test_setValueByTag_IsExogenousVariable_SetsValue() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByTag(EXOGENOUS_VARIABLE + " Tag", 102.0);

		// Assert
		assertEquals(102.0, sut.getValueByTag(EXOGENOUS_VARIABLE + " Tag"), DELTA);
	}

	@Test
	public void test_setValueByTag_IsStateVariable_SetsValue() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByTag(STATE_VARIABLE + " Tag", 103.0);

		// Assert
		assertEquals(103.0, sut.getValueByTag(STATE_VARIABLE + " Tag"), DELTA);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setValueByTag_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.setValueByTag("Invalid Variable Tag", 100.0);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getValueByTag_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getValues_ValueIsNotSet_ReturnsZeroForOutputVariables() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = new double[optimizerModel.getOutputVarNames().size()];
		for (int idx = 0; idx < expected.length; idx++) {
			expected[idx] = 0.0;
		}

		// Act & Assert
		assertArrayEquals(expected, sut.getValues(OUTPUT), DELTA);
	}

	@Test
	public void test_getValues_ValueIsNotSet_ReturnsMeanValueForManipulatedVariables() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = new double[optimizerModel.getManipulate().size()];
		for (int idx = 0; idx < optimizerModel.getManipulate().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getManipulate().get(idx));
			expected[idx] = variable.getMeanValue();
		}

		// Act & Assert
		assertArrayEquals(expected, sut.getValues(MANIPULATED), DELTA);
	}

	@Test
	public void test_getValues_ValueIsNotSet_ReturnsMeanValueForExogenousVariables() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = new double[optimizerModel.getExogenous().size()];
		for (int idx = 0; idx < optimizerModel.getExogenous().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getExogenous().get(idx));
			expected[idx] = variable.getMeanValue();
		}

		// Act & Assert
		assertArrayEquals(expected, sut.getValues(EXOGENOUS), DELTA);
	}

	@Test
	public void test_getValues_ValueIsNotSet_ReturnsMeanValueForStateVariables() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = new double[optimizerModel.getState().size()];
		for (int idx = 0; idx < optimizerModel.getState().size(); idx++) {
			Variable variable = optimizerModelPreprocessor
					.getVariableFromVariableName(optimizerModel.getState().get(idx));
			expected[idx] = variable.getMeanValue();
		}

		// Act & Assert
		assertArrayEquals(expected, sut.getValues(STATE), DELTA);
	}

	@Test
	public void test_getValues_TypeIsInvalid_ReturnsNull() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertNull(sut.getValues(-1));
	}

	@Test
	public void test_setValues_TypeIsManipulated_UpdatesManipulatedVariableValues() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = getDoubleValuesArray(optimizerModel.getManipulate().size());

		// Act
		sut.setValues(MANIPULATED, expected);

		// Assert
		assertArrayEquals(expected, sut.getValues(MANIPULATED), DELTA);
	}

	@Test
	public void test_setValues_TypeIsExogenous_UpdatesExogenousVariableValues() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = getDoubleValuesArray(optimizerModel.getExogenous().size());

		// Act
		sut.setValues(EXOGENOUS, expected);

		// Assert
		assertArrayEquals(expected, sut.getValues(EXOGENOUS), DELTA);
	}

	@Test
	public void test_setValues_TypeIsState_UpdatesStateVariableValues() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = getDoubleValuesArray(optimizerModel.getState().size());

		// Act
		sut.setValues(STATE, expected);

		// Assert
		assertArrayEquals(expected, sut.getValues(STATE), DELTA);
	}

	@Test
	public void test_setBoundsByName_IsValidVariable_UpdatesVariableBoundsFirstFiveValues() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = sut.getBoundsByName(STATE_VARIABLE);
		System.arraycopy(getDoubleValuesArray(5), 0, expected, 0, 5);

		// Act
		sut.setBoundsByName(STATE_VARIABLE, expected);

		// Assert
		assertArrayEquals(expected, sut.getBoundsByName(STATE_VARIABLE), DELTA);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setBoundsByName_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();

		// Act
		sut.setBoundsByName("Invalid variable name", new double[0]);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getBoundsByName_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();

		// Act
		sut.getBoundsByName("Invalid variable name");
	}

	@Test
	public void test_setBoundsByTag_IsValidVariable_UpdatesVariableBoundsFirstFiveValues() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		String tag = STATE_VARIABLE + " Tag";
		double[] expected = sut.getBoundsByTag(tag);
		System.arraycopy(getDoubleValuesArray(5), 0, expected, 0, 5);

		// Act
		sut.setBoundsByTag(tag, expected);

		// Assert
		assertArrayEquals(expected, sut.getBoundsByTag(tag), DELTA);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setBoundsByTag_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();

		// Act
		sut.setBoundsByTag("Invalid variable tag", new double[0]);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getBoundsByTag_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();

		// Act
		sut.getBoundsByTag("Invalid variable tag");
	}

	@Test
	public void test_setWeightsByName_IsValidVariable_UpdatesVariableWeightsFirstFourValues() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		double[] expected = sut.getWeightsByName(STATE_VARIABLE);
		System.arraycopy(getDoubleValuesArray(4), 0, expected, 0, 4);

		// Act
		sut.setWeightsByName(STATE_VARIABLE, expected);

		// Assert
		assertArrayEquals(expected, sut.getWeightsByName(STATE_VARIABLE), DELTA);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setWeightsByName_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();

		// Act
		sut.setWeightsByName("Invalid variable name", new double[0]);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getWeightsByName_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();

		// Act
		sut.getWeightsByName("Invalid variable name");
	}

	@Test
	public void test_setWeightsByTag_IsValidVariable_UpdatesVariableWeightsFirstFourValues() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		String tag = STATE_VARIABLE + " Tag";
		double[] expected = sut.getWeightsByTag(tag);
		System.arraycopy(getDoubleValuesArray(4), 0, expected, 0, 4);

		// Act
		sut.setWeightsByTag(tag, expected);

		// Assert
		assertArrayEquals(expected, sut.getWeightsByTag(tag), DELTA);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_setWeightsByTag_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		// No arrangements

		// Act
		sut.setWeightsByTag("Invalid variable tag", new double[0]);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getWeightsByTag_IsInvalidVariable_ThrowsMathException() throws MathException {
		// Arrange
		// No arrangements

		// Act
		sut.getWeightsByTag("Invalid variable tag");
	}

	@Test
	public void test_toStringForTest_Always_ReturnsEmptyString() {
		// Arrange
		// No arrangements

		// Act & Assert
		assertEquals("", sut.toStringForTest());
	}

	@Test
	public void test_getMaxValueByName_IsValidVariableName_ReturnsMaxValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMaxValue();

			// Act & Assert
			assertEquals(expected, sut.getMaxValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMaxValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMaxValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getMaxValueByTag_IsValidVariableTag_ReturnsMaxValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMaxValue();

			// Act & Assert
			assertEquals(expected, sut.getMaxValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getMaxValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMaxValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getMinValueByName_IsValidVariableName_ReturnsMinValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMinValue();

			// Act & Assert
			assertEquals(expected, sut.getMinValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMinValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMinValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getMinValueByTag_IsValidVariableTag_ReturnsMinValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMinValue();

			// Act & Assert
			assertEquals(expected, sut.getMinValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getMinValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMinValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getMeanValueByName_IsValidVariableName_ReturnsMeanValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMeanValue();

			// Act & Assert
			assertEquals(expected, sut.getMeanValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMeanValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMeanValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getMeanValueByTag_IsValidVariableTag_ReturnsMeanValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMeanValue();

			// Act & Assert
			assertEquals(expected, sut.getMeanValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getMeanValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException()
			throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMeanValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getMedianValueByName_IsValidVariableName_ReturnsMedianValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMedianValue();

			// Act & Assert
			assertEquals(expected, sut.getMedianValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getMedianValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMedianValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getMedianValueByTag_IsValidVariableTag_ReturnsMedianValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getMedianValue();

			// Act & Assert
			assertEquals(expected, sut.getMedianValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getMedianValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException()
			throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getMedianValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getSumValueByName_IsValidVariableName_ReturnsSumValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getSum();

			// Act & Assert
			assertEquals(expected, sut.getSumValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSumValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getSumValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getSumValueByTag_IsValidVariableTag_ReturnsSumValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getSum();

			// Act & Assert
			assertEquals(expected, sut.getSumValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getSumValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getSumValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getSTDValueByName_IsValidVariableName_ReturnsSTDValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getSTD();

			// Act & Assert
			assertEquals(expected, sut.getSTDValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSTDValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getSTDValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getSTDValueByTag_IsValidVariableTag_ReturnsSTDValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getSTD();

			// Act & Assert
			assertEquals(expected, sut.getSTDValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getSTDValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getSTDValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getVarianceValueByName_IsValidVariableName_ReturnsVarianceValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getVariance();

			// Act & Assert
			assertEquals(expected, sut.getVarianceValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getVarianceValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getVarianceValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getVarianceValueByTag_IsValidVariableTag_ReturnsVarianceValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getVariance();

			// Act & Assert
			assertEquals(expected, sut.getVarianceValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getVarianceValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException()
			throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getVarianceValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getKurtValueByName_IsValidVariableName_ReturnsKurtValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getKurt();

			// Act & Assert
			assertEquals(expected, sut.getKurtValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getKurtValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getKurtValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getKurtValueByTag_IsValidVariableTag_ReturnsKurtValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getKurt();

			// Act & Assert
			assertEquals(expected, sut.getKurtValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getKurtValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException()
			throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getKurtValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getSkewValueByName_IsValidVariableName_ReturnsSkewValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getSkew();

			// Act & Assert
			assertEquals(expected, sut.getSkewValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getSkewValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getSkewValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getSkewValueByTag_IsValidVariableTag_ReturnsSkewValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getSkew();

			// Act & Assert
			assertEquals(expected, sut.getSkewValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getSkewValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException()
			throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getSkewValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getRangeValueByName_IsValidVariableName_ReturnsRangeValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getRange();

			// Act & Assert
			assertEquals(expected, sut.getRangeValueByName(varName), DELTA);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getRangeValueByName_IsInvalidVariableName_ThrowsException() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getRangeValueByName("Invalid Variable Name");
	}

	@Test
	public void test_getRangeValueByTag_IsValidVariableTag_ReturnsRangeValueByVariable() throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		for (String varName : getAllVariableNames()) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getTag();
			double expected = optimizerModel.getPreprocessor().getVariableFromVariableName(varName).getRange();

			// Act & Assert
			assertEquals(expected, sut.getRangeValueByTag(tag), DELTA);
		}
	}

	// Assert
	@Test(expected = ArrayIndexOutOfBoundsException.class)
	public void test_getRangeValueByTag_IsInvalidVariableTag_ThrowsArrayIndexOutOfBoundsException()
			throws MathException {
		// Arrange
		arrangeBaseOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act
		sut.getRangeValueByTag("Invalid Variable Tag");
	}

	@Test
	public void test_getNumberOfOutputModelInputs_Always_ReturnsModelNumberOfInputs() throws MathException {
		// Arrange
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(((EnsembleModel) optimizerModel.getModel()).getNin(), sut.getNumberOfOutputModelInputs());
	}

	@Test
	public void test_getNumberOfOutputModelOutputs_Always_ReturnsModelNumberOfOutputs() throws MathException {
		// Arrange
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(((EnsembleModel) optimizerModel.getModel()).getNout(), sut.getNumberOfOutputModelOutputs());
	}

	@Test
	public void test_getNumberOfStateModelInputs_Always_ReturnsStateModelNumberOfInputs() throws MathException {
		// Arrange
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(((EnsembleModel) optimizerModel.getStateModel()).getNin(), sut.getNumberOfStateModelInputs());
	}

	@Test
	public void test_getNumberOfStateModelInputs_StateModelDoesNotExist_ReturnsZero() throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(0, sut.getNumberOfStateModelInputs());
	}

	@Test
	public void test_getNumberOfStateModelOutputs_Always_ReturnsStateModelNumberOfOutputs() throws MathException {
		// Arrange
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(((EnsembleModel) optimizerModel.getStateModel()).getNout(), sut.getNumberOfStateModelOutputs());
	}

	@Test
	public void test_getNumberOfStateModelOutputs_StateModelDoesNotExist_ReturnsZero() throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(0, sut.getNumberOfStateModelOutputs());
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainOutputModel_InputAndOutputRowsDoesNotMatch_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainOutputModel();
		expectedModel1TrainInput.redimension(expectedModel1TrainOutput.getRows() - 1,
				expectedModel1TrainInput.getCols());

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainOutputModel_InputRowsAreNotEnoughForTraining_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainOutputModel();
		expectedModel1TrainInput.redimension(9, expectedModel1TrainInput.getCols());
		expectedModel1TrainOutput.redimension(9, expectedModel1TrainOutput.getCols());

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainOutputModel_InputMatrixDoesNotMatchModelInput_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainOutputModel();
		when(ensembleModel.getNin()).thenReturn(11);

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainOutputModel_OutputMatrixDoesNotMatchModelOutput_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainOutputModel();
		when(ensembleModel.getNout()).thenReturn(11);

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	@Test
	public void test_trainOutputModel_IsNewTraining_ClearsModels() throws MathException {
		// Arrange
		newTraining = true;
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(ensembleModel, times(1)).clearModels();
	}

	@Test
	public void test_trainOutputModel_Always_SetsTrainingTime() throws MathException {
		// Arrange
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(ensembleModel).setTrainingTime(TIME_IN_MILLI_SECONDS);
	}

	@Test
	public void test_trainOutputModel_AutoStopFlagIsTrue_SetsAutomaticStopping() throws MathException {
		// Arrange
		autoStop = true;
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(ensembleModel).useAutomaticStopping(true);
	}

	@Test
	public void test_trainOutputModel_AutoStopFlagIsFalse_SetsManualStopping() throws MathException {
		// Arrange
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(ensembleModel).useAutomaticStopping(false);
	}

	@Test
	public void test_trainOutputModel_Always_AddsSutAsEnsembleModelListener() throws MathException {
		// Arrange
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		InOrder inOrder = inOrder(ensembleModel);
		inOrder.verify(ensembleModel).removeAllListeners();
		inOrder.verify(ensembleModel).addListener(sut);
	}

	@Test
	public void test_trainOutputModel_ModelListenersAreNotPassed_AddsNewOnlineModelListener() throws MathException {
		// Arrange
		display = true;
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel, times(2)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainOutputModel_ModelListenerIsPassed_SetsConsoleProperties() throws MathException {
		// Arrange
		display = true;
		onlineModelListenerIsPassed = true;
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verifyOutputModelConsoleConfiguration();
	}

	@Test
	public void test_trainOutputModel_ModelListenersDoesNotContainOnlineModelListener_AddsNewOnlineModelListener()
			throws MathException {
		// Arrange
		display = true;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel).addListener(modelListeners.get(0));
		verify(ensembleModel, times(3)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainOutputModel_ConsoleNotToBeDisplayed_AddsAllModelListeners() throws MathException {
		// Arrange
		onlineModelListenerIsPassed = true;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainOutputModel();

		// Act
		sut.trainOutputModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		for (EnsembleModelListener modelListener : modelListeners) {
			verify(ensembleModel, times(1)).addListener(modelListener);
		}
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainStateModel_StateModelDoesNotExist_ThrowsMathException() throws MathException {
		// Arrange
		stateModelExists = false;
		arrangeForTrainStateModel();
		expectedModel1TrainInput.redimension(expectedModel1TrainOutput.getRows() - 1,
				expectedModel1TrainInput.getCols());

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainStateModel_InputAndOutputRowsDoesNotMatch_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainStateModel();
		expectedModel1TrainInput.redimension(expectedModel1TrainOutput.getRows() - 1,
				expectedModel1TrainInput.getCols());

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainStateModel_InputRowsAreNotEnoughForTraining_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainStateModel();
		expectedModel1TrainInput.redimension(9, expectedModel1TrainInput.getCols());
		expectedModel1TrainOutput.redimension(9, expectedModel1TrainOutput.getCols());

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainStateModel_InputMatrixDoesNotMatchModelInput_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainStateModel();
		when(stateEnsembleModel.getNin()).thenReturn(11);

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_trainStateModel_OutputMatrixDoesNotMatchModelOutput_ThrowsMathException() throws MathException {
		// Arrange
		arrangeForTrainStateModel();
		when(stateEnsembleModel.getNout()).thenReturn(11);

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);
	}

	@Test
	public void test_trainStateModel_IsNewTraining_ClearsModels() throws MathException {
		// Arrange
		newTraining = true;
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(stateEnsembleModel, times(1)).clearModels();
	}

	@Test
	public void test_trainStateModel_Always_SetsTrainingTime() throws MathException {
		// Arrange
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(stateEnsembleModel).setTrainingTime(TIME_IN_MILLI_SECONDS);
	}

	@Test
	public void test_trainStateModel_AutoStopFlagIsTrue_SetsAutomaticStopping() throws MathException {
		// Arrange
		autoStop = true;
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(stateEnsembleModel).useAutomaticStopping(true);
	}

	@Test
	public void test_trainStateModel_AutoStopFlagIsFalse_SetsManualStopping() throws MathException {
		// Arrange
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verify(stateEnsembleModel).useAutomaticStopping(false);
	}

	@Test
	public void test_trainStateModel_Always_AddsSutAsEnsembleModelListener() throws MathException {
		// Arrange
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		InOrder inOrder = inOrder(stateEnsembleModel);
		inOrder.verify(stateEnsembleModel).removeAllListeners();
		inOrder.verify(stateEnsembleModel).addListener(sut);
	}

	@Test
	public void test_trainStateModel_ModelListenersAreNotPassed_AddsNewOnlineModelListener() throws MathException {
		// Arrange
		display = true;
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(stateEnsembleModel, times(2)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainStateModel_ModelListenerIsPassed_SetsConsoleProperties() throws MathException {
		// Arrange
		display = true;
		onlineModelListenerIsPassed = true;
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		verifyStateModelConsoleConfiguration();
	}

	@Test
	public void test_trainStateModel_ModelListenersDoesNotContainOnlineModelListener_AddsNewOnlineModelListener()
			throws MathException {
		// Arrange
		display = true;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(stateEnsembleModel).addListener(modelListeners.get(0));
		verify(stateEnsembleModel, times(3)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainStateModel_ConsoleNotToBeDisplayed_AddsAllModelListeners() throws MathException {
		// Arrange
		onlineModelListenerIsPassed = true;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainStateModel();

		// Act
		sut.trainStateModel(modelListeners, expectedModel1TrainInput, expectedModel1TrainOutput, TIME_IN_MILLI_SECONDS,
				autoStop, newTraining, display);

		// Assert
		for (EnsembleModelListener modelListener : modelListeners) {
			verify(stateEnsembleModel, times(1)).addListener(modelListener);
		}
	}

	@Test
	public void test_trainingComplete_EnsembleModelIsTrainedModel_SetsOutputTestRMSE() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].testingResults.rmse.get(0) + ensembleModels[1].testingResults.rmse.get(0)) / 2,
				(ensembleModels[0].testingResults.rmse.get(1) + ensembleModels[1].testingResults.rmse.get(1)) / 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getOutputTestRmse().length; idx++) {
			assertEquals(expected[idx], sut.getOutputTestRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_EnsembleModelIsTrainedModel_SetsOutputTestCORR() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].testingResults.corrcoef.get(0) + ensembleModels[1].testingResults.corrcoef.get(0))
						/ 2,
				(ensembleModels[0].testingResults.corrcoef.get(1) + ensembleModels[1].testingResults.corrcoef.get(1))
						/ 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getOutputTestCorr().length; idx++) {
			assertEquals(expected[idx], sut.getOutputTestCorr()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_EnsembleModelIsTrainedModel_SetsOutputTrainRMSE() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].trainingResults.rmse.get(0) + ensembleModels[1].trainingResults.rmse.get(0)) / 2,
				(ensembleModels[0].trainingResults.rmse.get(1) + ensembleModels[1].trainingResults.rmse.get(1)) / 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getOutputTrainingRmse().length; idx++) {
			assertEquals(expected[idx], sut.getOutputTrainingRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_EnsembleModelIsTrainedModel_SetsOutputTrainCORR() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].trainingResults.corrcoef.get(0) + ensembleModels[1].trainingResults.corrcoef.get(0))
						/ 2,
				(ensembleModels[0].trainingResults.corrcoef.get(1) + ensembleModels[1].trainingResults.corrcoef.get(1))
						/ 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getOutputTrainingCorr().length; idx++) {
			assertEquals(expected[idx], sut.getOutputTrainingCorr()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_EnsembleModelIsTrainedModel_SetsOutputModelRateValue() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].testingResults.corrcoef.get(0) + ensembleModels[1].testingResults.corrcoef.get(0))
						/ 2,
				(ensembleModels[0].testingResults.corrcoef.get(1) + ensembleModels[1].testingResults.corrcoef.get(1))
						/ 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		assertEquals((expected[0] + expected[1]) / 2, sut.getOutputModelRate(), DELTA);
	}

	@Test
	public void test_trainingComplete_StateEnsembleModelIsTrainedModel_SetsStateTestRMSE() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].testingResults.rmse.get(0) + ensembleModels[1].testingResults.rmse.get(0)) / 2,
				(ensembleModels[0].testingResults.rmse.get(1) + ensembleModels[1].testingResults.rmse.get(1)) / 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getStateTestRmse().length; idx++) {
			assertEquals(expected[idx], sut.getStateTestRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_StateEnsembleModelIsTrainedModel_SetsStateTestCORR() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].testingResults.corrcoef.get(0) + ensembleModels[1].testingResults.corrcoef.get(0))
						/ 2,
				(ensembleModels[0].testingResults.corrcoef.get(1) + ensembleModels[1].testingResults.corrcoef.get(1))
						/ 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getStateTestCorr().length; idx++) {
			assertEquals(expected[idx], sut.getStateTestCorr()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_StateEnsembleModelIsTrainedModel_SetsStateTrainRMSE() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].trainingResults.rmse.get(0) + ensembleModels[1].trainingResults.rmse.get(0)) / 2,
				(ensembleModels[0].trainingResults.rmse.get(1) + ensembleModels[1].trainingResults.rmse.get(1)) / 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getStateTrainingRmse().length; idx++) {
			assertEquals(expected[idx], sut.getStateTrainingRmse()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_StateEnsembleModelIsTrainedModel_SetsStateTrainCORR() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].trainingResults.corrcoef.get(0) + ensembleModels[1].trainingResults.corrcoef.get(0))
						/ 2,
				(ensembleModels[0].trainingResults.corrcoef.get(1) + ensembleModels[1].trainingResults.corrcoef.get(1))
						/ 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		for (int idx = 0; idx < sut.getStateTrainingCorr().length; idx++) {
			assertEquals(expected[idx], sut.getStateTrainingCorr()[idx], DELTA);
		}
	}

	@Test
	public void test_trainingComplete_EnsembleModelIsTrainedModel_SetsStateModelRateValue() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		double[] expected = new double[] {
				(ensembleModels[0].testingResults.corrcoef.get(0) + ensembleModels[1].testingResults.corrcoef.get(0))
						/ 2,
				(ensembleModels[0].testingResults.corrcoef.get(1) + ensembleModels[1].testingResults.corrcoef.get(1))
						/ 2 };

		// Act
		sut.trainingComplete(ensembleModelEvent);

		// Assert
		assertEquals((expected[0] + expected[1]) / 2, sut.getStateModelRate(), DELTA);
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTestRmse_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange

		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getOutputTestRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTestCorr_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getOutputTestCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTrainingRmse_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getOutputTrainingRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTrainingCorr_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getOutputTrainingCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputModelRate_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getOutputModelRate();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTestRmse_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		optimizerModel.setStateModel(null);
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getStateTestRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTestCorr_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		optimizerModel.setStateModel(null);
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getStateTestCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTrainingRmse_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		optimizerModel.setStateModel(null);
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getStateTrainingRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTrainingCorr_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		optimizerModel.setStateModel(null);
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getStateTrainingCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateModelRate_TrainingModelIsNotSet_ThrowsMathException() throws MathException {
		// Arrange
		arrangeTrainingComplete();
		optimizerModel.setStateModel(null);
		sut.trainingComplete(ensembleModelEvent);

		// Act
		sut.getStateModelRate();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTestRmse_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getOutputTestRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTestCorr_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getOutputTestCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTrainingRmse_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getOutputTrainingRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputTrainingCorr_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getOutputTrainingCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getOutputModelRate_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		ensembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getOutputModelRate();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTestRmse_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getStateTestRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTestCorr_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getStateTestCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTrainingRmse_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getStateTrainingRmse();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateTrainingCorr_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getStateTrainingCorr();
	}

	// Assert
	@Test(expected = MathException.class)
	public void test_getStateModelRate_TrainingIsUncompleted_ThrowsMathException() throws MathException {
		// Arrange
		stateEnsembleModelIsTrainedModel = true;
		arrangeTrainingComplete();
		sut.trainingComplete(ensembleModelEvent);
		sut.uncompleteTraining();

		// Act
		sut.getStateModelRate();
	}

	@Test
	public void test_trainModelFromFile_Always_PreparesTrainingSetFromDataSeries() throws Exception {
		// Arrange
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyAllDataSeriesAreUsedToPrepareTrainingSet();
	}

	@Test
	public void test_trainModelFromFile_Always_PreparesTrainingSet2FromDataSeries() throws Exception {
		// Arrange
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyAllDataSeriesAreUsedToPrepareTrainingSet2();
	}

	@Test
	public void test_trainModelFromFile_IsNewTraining_ClearsModels() throws Exception {
		// Arrange
		newTraining = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verify(ensembleModel, times(1)).clearModels();
	}

	@Test
	public void test_trainModelFromFile_Always_SetsTrainingTime() throws Exception {
		// Arrange
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verify(ensembleModel, times(1)).setTrainingTime(TIME_IN_MILLI_SECONDS);
	}

	@Test
	public void test_trainModelFromFile_AutoStopFlagIsTrue_SetsAutomaticStopping() throws MathException, IOException {
		// Arrange
		autoStop = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verify(ensembleModel).useAutomaticStopping(true);
	}

	@Test
	public void test_trainModelFromFile_AutoStopFlagIsFalse_SetsManualStopping() throws MathException, IOException {
		// Arrange
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verify(ensembleModel).useAutomaticStopping(false);
	}

	@Test
	public void test_trainModelFromFile_Always_AddsSutAsEnsembleModelListener() throws MathException, IOException {
		// Arrange
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		InOrder inOrder = inOrder(ensembleModel);
		inOrder.verify(ensembleModel).removeAllListeners();
		inOrder.verify(ensembleModel).addListener(sut);
	}

	@Test
	public void test_trainModelFromFile_ModelListenersAreNotPassed_AddsNewOnlineModelListener()
			throws MathException, IOException {
		// Arrange
		display = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel, times(2)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainModelFromFile_ModelListenerIsPassed_SetsConsoleProperties()
			throws MathException, IOException {
		// Arrange
		display = true;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModelConsoleConfigurationWithoutOneModelMode();
	}

	@Test
	public void test_trainModelFromFile_ModelListenerIsPassed_SetsModel1TrainInput() throws MathException, IOException {
		// Arrange
		display = true;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModel1TrainInputIsPassed();
	}

	@Test
	public void test_trainModelFromFile_ModelListenerIsPassed_SetsModel2TrainInput() throws MathException, IOException {
		// Arrange
		display = true;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModel2TrainInputIsPassed();
	}

	@Test
	public void test_trainModelFromFile_ModelListenerIsPassed_SetsModel1TrainOutput()
			throws MathException, IOException {
		// Arrange
		display = true;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModel1TrainOutputIsPassed();
	}

	@Test
	public void test_trainModelFromFile_ModelListenerIsPassed_SetsModel2TrainOutput()
			throws MathException, IOException {
		// Arrange
		display = true;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModel2TrainOutputIsPassed();
	}

	@Test
	public void test_trainModelFromFile_ModelListenersDoesNotContainOnlineModelListener_AddsNewOnlineModelListener()
			throws MathException, IOException {
		// Arrange
		display = true;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel).addListener(modelListeners.get(0));
		verify(ensembleModel, times(3)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainModelFromFile_ConsoleNotToBeDisplayed_AddsAllModelListeners()
			throws MathException, IOException {
		// Arrange
		onlineModelListenerIsPassed = true;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		for (EnsembleModelListener modelListener : modelListeners) {
			verify(ensembleModel, times(1)).addListener(modelListener);
		}
	}

	@Test
	public void test_trainModelFromFile_StateModelDoesNotExistAndModelListenersAreNotPassed_AddsNewOnlineModelListener()
			throws MathException, IOException {
		// Arrange
		display = true;
		stateModelExists = false;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel, times(2)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainOutputModel_StateModelDoesNotExistAndModelListenerIsPassed_SetsModel1TrainInput()
			throws MathException, IOException {
		// Arrange
		display = true;
		stateModelExists = false;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModel1TrainInputIsPassed();
	}

	@Test
	public void test_trainOutputModel_StateModelDoesNotExistAndModelListenerIsPassed_SetsModel1TrainOutput()
			throws MathException, IOException {
		// Arrange
		display = true;
		stateModelExists = false;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModel1TrainOutputIsPassed();
	}

	@Test
	public void test_trainOutputModel_StateModelDoesNotExistAndModelListenerIsPassed_SetsConsoleProperties()
			throws MathException, IOException {
		// Arrange
		display = true;
		stateModelExists = false;
		onlineModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		verifyModelConsoleConfiguration();
	}

	@Test
	public void test_trainOutputModel_StateModelDoesNotExistAndModelListenersDoesNotContainOnlineModelListener_AddsNewOnlineModelListener()
			throws MathException, IOException {
		// Arrange
		display = true;
		stateModelExists = false;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		ArgumentCaptor<OnlineModelListener> argumentCaptor = ArgumentCaptor.forClass(OnlineModelListener.class);
		verify(ensembleModel).addListener(modelListeners.get(0));
		verify(ensembleModel, times(3)).addListener(argumentCaptor.capture());
		verifyConsoleConfiguration(argumentCaptor);
	}

	@Test
	public void test_trainOutputModel_StateModelDoesNotExistAndConsoleNotToBeDisplayed_AddsAllModelListeners()
			throws MathException, IOException {
		// Arrange
		stateModelExists = false;
		onlineModelListenerIsPassed = true;
		ensembleModelListenerIsPassed = true;
		arrangeForTrainModelFromFile();

		// Act
		sut.trainModelFromFile(modelListeners, dataSeriesFileNames, TIME_IN_MILLI_SECONDS, autoStop, newTraining,
				display);

		// Assert
		for (EnsembleModelListener modelListener : modelListeners) {
			verify(ensembleModel, times(1)).addListener(modelListener);
		}
	}

	@Test
	public void test_getObjectiveValue_Always_ReturnsOptimizationObjectiveValue() throws MathException {
		// Arrange
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(nolOptimization.getObjectiveValue(), sut.getObjectiveValue(), DELTA);
	}

	@Test
	public void test_getVariableNameAtHardBound_IsNotCalculated_ReturnsEmptyArray() throws MathException {
		// Arrange
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(0, sut.getVariableNameAtHardBound().length);
	}

	@Test
	public void test_getVariableNameAtHardBound_ValuesAreWithinBounds_ReturnsEmptyArray() throws MathException {
		// Arrange
		variablesAreWithinBounds = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		Whitebox.setInternalState(sut, "isCalculated", true);

		// Act & Assert
		assertEquals(0, sut.getVariableNameAtHardBound().length);
	}

	@Test
	public void test_getVariableNameAtHardBound_ValuesAreBelowLowerBound_ReturnsVariableNames() throws MathException {
		// Arrange
		variablesAresBelowLowerBound = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		Whitebox.setInternalState(sut, "isCalculated", true);

		// Act
		String[] result = sut.getVariableNameAtHardBound();

		// Assert
		Vector<String> allVarNames = new Vector<String>();
		allVarNames.addAll(optimizerModel.getOutputs());
		allVarNames.addAll(optimizerModel.getManipulate());
		allVarNames.addAll(optimizerModel.getExogenous());
		allVarNames.addAll(optimizerModel.getStateInput());
		for (String varName : allVarNames) {
			assertTrue(Arrays.asList(result).contains(varName));
		}
	}

	@Test
	public void test_getVariableNameAtHardBound_VariablesAreAboveUpperBound_ReturnsVariableNames()
			throws MathException {
		// Arrange
		variablesAreAboveUpperBound = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		Whitebox.setInternalState(sut, "isCalculated", true);

		// Act
		String[] result = sut.getVariableNameAtHardBound();

		// Assert
		Vector<String> allVarNames = new Vector<String>();
		allVarNames.addAll(optimizerModel.getOutputs());
		allVarNames.addAll(optimizerModel.getManipulate());
		allVarNames.addAll(optimizerModel.getExogenous());
		allVarNames.addAll(optimizerModel.getStateInput());
		for (String varName : allVarNames) {
			assertTrue(Arrays.asList(result).contains(varName));
		}
	}

	@Test
	public void test_getNumberOfVariableNameAtHardBound_IsNotCalculated_ReturnsZero() throws MathException {
		// Arrange
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		// Act & Assert
		assertEquals(0, sut.getNumberOfVariableNameAtHardBound());
	}

	@Test
	public void test_getNumberOfVariableNameAtHardBound_ValuesAreWithinBounds_ReturnsZero() throws MathException {
		// Arrange
		variablesAreWithinBounds = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		Whitebox.setInternalState(sut, "isCalculated", true);

		// Act & Assert
		assertEquals(0, sut.getNumberOfVariableNameAtHardBound());
	}

	@Test
	public void test_getNumberOfVariableNameAtHardBound_ValuesAreBelowLowerBound_ReturnsCount() throws MathException {
		// Arrange
		variablesAresBelowLowerBound = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		Whitebox.setInternalState(sut, "isCalculated", true);

		// Act & Assert
		assertEquals(8, sut.getNumberOfVariableNameAtHardBound());
	}

	@Test
	public void test_getNumberOfVariableNameAtHardBound_VariablesAreAboveUpperBound_ReturnsCount()
			throws MathException {
		// Arrange
		variablesAreAboveUpperBound = true;
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);
		Whitebox.setInternalState(sut, "isCalculated", true);

		// Act & Assert
		assertEquals(8, sut.getNumberOfVariableNameAtHardBound());
	}

	// -- Helper Methods --

	private void arrangeForLoadOptimization() throws IOException, MathException {
		arrangeOptimizationFolder();
		arrangeBaseOptimizer();

		versionManager = new VersionManagerForOnlineOptimizer();
		versionManager.setOptimizer(optimizer);
		versionManager.saveToFile(optimizationsFolder.getAbsolutePath(), optimizationFileNameWithoutDirectory);
		versionManager.saveToFile(optimizationFileNameWithDirectory);
	}

	private void arrangeForTrainModelFromFile() throws MathException, IOException {
		arrangeForTrainModel();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		File dataSeriesFile = folder.newFile("DataSeries File 1.tmp");
		dataSeriesFileNames = new String[] { dataSeriesFile.getAbsolutePath() };

		Random randomGenerator = new Random();

		expectedModel1TrainInput = new Matrix();
		expectedModel1TrainOutput = new Matrix();
		expectedModel2TrainInput = new Matrix();
		expectedModel2TrainOutput = new Matrix();
		expectedModel1TrainInput.redimension(10, 10);
		expectedModel1TrainOutput.redimension(10, 10);
		expectedModel2TrainInput.redimension(10, 10);
		expectedModel2TrainOutput.redimension(10, 10);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				expectedModel2TrainInput.set(i, j, randomGenerator.nextInt(500));
				expectedModel2TrainOutput.set(i, j, randomGenerator.nextInt(500));
				expectedModel1TrainInput.set(i, j, randomGenerator.nextInt(500));
				expectedModel1TrainOutput.set(i, j, randomGenerator.nextInt(500));
			}
		}

		optimizerModel.setMatrices(expectedModel1TrainInput, expectedModel1TrainOutput, expectedModel2TrainInput,
				expectedModel2TrainOutput);
	}

	private void arrangeForTrainOutputModel() throws MathException {
		arrangeForTrainModel();

		when(ensembleModel.getNin()).thenReturn(10);
		when(ensembleModel.getNout()).thenReturn(10);
		when(ensembleModel.getTrainingTime()).thenReturn(trainingTime);
	}

	private void arrangeForTrainStateModel() throws MathException {
		arrangeForTrainModel();

		if (stateModelExists) {
			when(stateEnsembleModel.getNin()).thenReturn(10);
			when(stateEnsembleModel.getNout()).thenReturn(10);
			when(stateEnsembleModel.getTrainingTime()).thenReturn(trainingTime);
		}
	}

	private void arrangeForTrainModel() throws MathException {
		arrangeOptimizer();
		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		expectedModel1TrainInput = new Matrix();
		expectedModel1TrainInput.redimension(10, 10);
		expectedModel1TrainOutput = new Matrix();
		expectedModel1TrainOutput.redimension(10, 10);

		if (onlineModelListenerIsPassed) {
			modelListeners = new Vector<EnsembleModelListener>();
			OnlineModelListener onlineModelListener = mock(OnlineModelListener.class);
			onlineModelListenerOnlineConsole = mock(NolOnlineConsoleFrame.class);
			when(onlineModelListener.getOnlineConsole()).thenReturn(onlineModelListenerOnlineConsole);
			modelListeners.add(onlineModelListener);
		}

		if (ensembleModelListenerIsPassed) {
			modelListeners = new Vector<EnsembleModelListener>();
			modelListeners.add(mock(EnsembleModelListener.class));
		}
	}

	private void arrangeBaseOptimizer() throws MathException {
		arrangeOptimizerModelProcessor();
		arrangeOptimizerModel();

		nolOptimization = new NolOptimization();
		nolOptimization.setModel(optimizerModel);

		optimizer = new OnlineOptimizer("Optimizer 1 Name", nolOptimization);
		optimizer.setName("Optimizer 1 Name");
		optimizer.setComment("Optimizer 1 Comment");
	}

	private void arrangeEnsembleModel() {
		ensembleModel = PowerMockito.mock(EnsembleModel.class);
		when(ensembleModel.getNin()).thenReturn(105);
		when(ensembleModel.getNout()).thenReturn(205);
	}

	private void arrangeOptimizationFolder() throws IOException {
		optimizationsFolder = folder.newFolder("Optimizations");
		optimizationFileNameWithoutDirectory = "Optimization 1.tmp";
		optimizationFileNameWithDirectory = optimizationsFolder.getAbsolutePath() + "\\Optimization 2.tmp";
	}

	private void arrangeOptimizer() throws MathException {
		arrangeBaseOptimizer();
		arrangeEnsembleModel();
		arrangeStateEnsembleModel();

		optimizerModel.setModel(ensembleModel);
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

		int count = 1;
		for (String name : allNames) {
			Variable variable = new Variable();
			variable.setName(name);
			variable.setTag(name + " Tag");
			variable.setUnit(name + " Unit");
			// There are 10 different statistics used in variable. Hence,
			// creating array of 10 numbers. Multiplying by count to keep
			// statistics in different variables unique which are used
			// for assertions.
			double[] statistics = new double[] { 1 * count, 2 * count, 3 * count, 4 * count, 5 * count, 6 * count,
					7 * count, 8 * count, 9 * count, 10 * count };

			if (outputs.contains(name) == false) {
				// By default, input variables value is Mean value
				if (variablesAreWithinBounds) {
					statistics[0] = 15 * count; // Mean Value
					statistics[7] = 14 * count; // Minimum Value (Lower Bound)
					statistics[8] = 16 * count; // Maximum Value (Upper Bound)
				} else if (variablesAresBelowLowerBound) {
					statistics[0] = 13 * count; // Mean Value
					statistics[7] = 14 * count; // Minimum Value (Lower Bound)
					statistics[8] = 16 * count; // Maximum Value (Upper Bound)
				} else if (variablesAreAboveUpperBound) {
					statistics[0] = 17 * count; // Mean Value
					statistics[7] = 14 * count; // Minimum Value (Lower Bound)
					statistics[8] = 16 * count; // Maximum Value (Upper Bound)
				}
			} else {
				// By default, output variables value is zero
				if (variablesAreWithinBounds) {
					statistics[7] = -1; // Minimum Value (Lower Bound)
					statistics[8] = 1; // Maximum Value (Upper Bound)
				} else if (variablesAresBelowLowerBound) {
					statistics[7] = 1; // Minimum Value (Lower Bound)
					statistics[8] = 2; // Maximum Value (Upper Bound)
				} else if (variablesAreAboveUpperBound) {
					statistics[7] = -2; // Minimum Value (Lower Bound)
					statistics[8] = -1; // Maximum Value (Upper Bound)
				}
			}

			variable.setStatistics(statistics);
			variablesMap.put(name, variable);
			count++;
		}

		optimizerModelPreprocessor.setVariablesFromVariableName(variablesMap);
	}

	private void arrangeTrainingComplete() throws MathException {
		arrangeOptimizer();
		arrangeTrainingModels();

		when(ensembleModel.getNout()).thenReturn(ensembleModels.length);
		when(ensembleModel.size()).thenReturn(ensembleModels.length);
		when(ensembleModel.getModel(Matchers.anyInt())).thenAnswer(new Answer<Object>() {
			@Override
			public Object answer(InvocationOnMock invocation) throws Throwable {
				int idx = (int) invocation.getArguments()[0];
				return ensembleModels[idx];
			}
		});

		if (stateModelExists) {
			when(stateEnsembleModel.getNout()).thenReturn(ensembleModels.length);
			when(stateEnsembleModel.size()).thenReturn(ensembleModels.length);
			when(stateEnsembleModel.getModel(Matchers.anyInt())).thenAnswer(new Answer<Object>() {
				@Override
				public Object answer(InvocationOnMock invocation) throws Throwable {
					int idx = (int) invocation.getArguments()[0];
					return ensembleModels[idx];
				}
			});
		}

		sut = new OnlineOptimizer("Optimization Problem Name", nolOptimization);

		ensembleModelEventModel = mock(Model.class);
		ensembleModelEvent = mock(EnsembleModelEvent.class);

		when(ensembleModelEvent.getModel()).thenReturn(ensembleModelEventModel);
		when(ensembleModelEvent.getType()).thenReturn(ensembleModelEventType);

		if (ensembleModelIsTrainedModel) {
			when(ensembleModelEvent.getEnsembleModel()).thenReturn(ensembleModel);
		} else if (stateEnsembleModelIsTrainedModel) {
			when(ensembleModelEvent.getEnsembleModel()).thenReturn(stateEnsembleModel);
		} else {
			when(ensembleModelEvent.getEnsembleModel()).thenReturn(null);
		}
	}

	private void arrangeTrainingModels() {
		// Adding more than one training models to make assertions
		Random randomGenerator = new Random();

		ensembleModels = new TrainableModel[2];
		for (int modelIdx = 0; modelIdx < ensembleModels.length; modelIdx++) {
			TrainableModel model = mock(TrainableModel.class);

			Matrix trainingRootMeanSquareErrors = new Matrix();
			trainingRootMeanSquareErrors.redimension(1, 2);
			trainingRootMeanSquareErrors.set(0, randomGenerator.nextInt(100));
			trainingRootMeanSquareErrors.set(0, randomGenerator.nextInt(100));

			Matrix trainingCorrelationCoefficients = new Matrix();
			trainingCorrelationCoefficients.redimension(1, 2);
			trainingCorrelationCoefficients.set(0, randomGenerator.nextInt(100));
			trainingCorrelationCoefficients.set(0, randomGenerator.nextInt(100));

			Matrix testingRootMeanSquareErrors = new Matrix();
			testingRootMeanSquareErrors.redimension(1, 2);
			testingRootMeanSquareErrors.set(0, randomGenerator.nextInt(100));
			testingRootMeanSquareErrors.set(0, randomGenerator.nextInt(100));

			Matrix testingCorrelationCoefficients = new Matrix();
			testingCorrelationCoefficients.redimension(1, 2);
			testingCorrelationCoefficients.set(0, randomGenerator.nextInt(100));
			testingCorrelationCoefficients.set(0, randomGenerator.nextInt(100));

			ValidationParameters trainingResults = mock(ValidationParameters.class);
			ValidationParameters testingResults = mock(ValidationParameters.class);

			trainingResults.rmse = trainingRootMeanSquareErrors;
			trainingResults.corrcoef = trainingCorrelationCoefficients;
			model.trainingResults = trainingResults;

			testingResults.rmse = testingRootMeanSquareErrors;
			testingResults.corrcoef = testingCorrelationCoefficients;
			model.testingResults = testingResults;

			ensembleModels[modelIdx] = model;
		}
	}

	private void arrangeStateEnsembleModel() {
		if (stateModelExists) {
			stateEnsembleModel = mock(EnsembleModel.class);
			when(stateEnsembleModel.getNin()).thenReturn(305);
			when(stateEnsembleModel.getNout()).thenReturn(405);
			optimizerModel.setStateModel(stateEnsembleModel);
		}
	}

	private Vector<String> getAllVariableNames() {
		Vector<String> allVariables = new Vector<String>();
		allVariables.addAll(optimizerModel.getExogenous());
		allVariables.addAll(optimizerModel.getManipulate());
		allVariables.addAll(optimizerModel.getOutputVarNames());
		allVariables.addAll(optimizerModel.getState());
		return allVariables;
	}

	private double[] getDoubleValuesArray(int count) {
		Random randomGenerator = new Random();
		double[] doubles = new double[count];
		for (int idx = 0; idx < doubles.length; idx++) {
			doubles[idx] = randomGenerator.nextInt(100);
		}

		return doubles;
	}

	private void arrangeOptimizerModelProcessor() {
		optimizerModelPreprocessor = new PreprocessorStub();
		optimizerModelPreprocessor.setName("PreprocessorStub Name");
	}

	private String[] getVariableTags(Vector<String> variables) {
		String[] tags = new String[variables.size()];
		for (int idx = 0; idx < variables.size(); idx++) {
			String tag = optimizerModel.getPreprocessor().getVariableFromVariableName(variables.get(idx)).getTag();
			tags[idx] = tag;
		}

		return tags;
	}

	private String[] getVariableUnits(Vector<String> variables) {
		String[] units = new String[variables.size()];
		for (int idx = 0; idx < variables.size(); idx++) {
			String unit = optimizerModel.getPreprocessor().getVariableFromVariableName(variables.get(idx)).getUnit();
			units[idx] = unit;
		}

		return units;
	}

	private String[] getVariableNames(Vector<String> variables) {
		String[] units = new String[variables.size()];
		for (int idx = 0; idx < variables.size(); idx++) {
			units[idx] = variables.get(idx);
		}

		return units;
	}

	private void verifyAllDataSeriesAreUsedToPrepareTrainingSet() {
		Vector<String> dataSeriesNames = new Vector<String>();
		for (int idx = 0; idx < optimizerModel.getRetrainDataSeries().size(); idx++) {
			dataSeriesNames.add(optimizerModel.getRetrainDataSeries().get(idx).toString());
		}

		for (String fileAbsolutePath : dataSeriesFileNames) {
			assertTrue(dataSeriesNames.contains(fileAbsolutePath.substring(0, fileAbsolutePath.indexOf("."))));
		}
	}

	private void verifyAllDataSeriesAreUsedToPrepareTrainingSet2() {
		Vector<String> dataSeriesNames = new Vector<String>();
		for (int idx = 0; idx < optimizerModel.getRetrainDataSeries2().size(); idx++) {
			dataSeriesNames.add(optimizerModel.getRetrainDataSeries2().get(idx).toString());
		}

		for (String fileAbsolutePath : dataSeriesFileNames) {
			assertTrue(dataSeriesNames.contains(fileAbsolutePath.substring(0, fileAbsolutePath.indexOf("."))));
		}
	}

	private void verifyConsoleConfiguration(ArgumentCaptor<OnlineModelListener> argumentCaptor) {
		NolOnlineConsoleFrame console = argumentCaptor.getValue().getOnlineConsole();
		assertEquals(100, (int) console.getBounds().getX());
		assertEquals(100, (int) console.getBounds().getY());
		assertEquals(750, (int) console.getBounds().getWidth());
		assertEquals(500, (int) console.getBounds().getHeight());
	}

	private void verifyOutputModelConsoleConfiguration() {
		verify(onlineModelListenerOnlineConsole, times(1)).setModel1TrainInput(expectedModel1TrainInput);
		verify(onlineModelListenerOnlineConsole, times(1)).setModel1TrainOutput(expectedModel1TrainOutput);
		verifyModelConsoleConfiguration();
	}

	private void verifyStateModelConsoleConfiguration() {
		verify(onlineModelListenerOnlineConsole, times(1)).setModel2TrainInput(expectedModel1TrainInput);
		verify(onlineModelListenerOnlineConsole, times(1)).setModel2TrainOutput(expectedModel1TrainOutput);
		verifyModelConsoleConfiguration();
	}

	private void verifyModel1TrainInputIsPassed() {
		ArgumentCaptor<Matrix> model1TrainInputCaptor = ArgumentCaptor.forClass(Matrix.class);
		verify(onlineModelListenerOnlineConsole, times(1)).setModel1TrainInput(model1TrainInputCaptor.capture());
		verifyMatricesAreSame(model1TrainInputCaptor.getValue(), expectedModel1TrainInput);
	}

	private void verifyModel2TrainInputIsPassed() {
		ArgumentCaptor<Matrix> model2TrainInputCaptor = ArgumentCaptor.forClass(Matrix.class);
		verify(onlineModelListenerOnlineConsole, times(1)).setModel2TrainInput(model2TrainInputCaptor.capture());
		verifyMatricesAreSame(model2TrainInputCaptor.getValue(), expectedModel2TrainInput);
	}

	private void verifyModel1TrainOutputIsPassed() {
		ArgumentCaptor<Matrix> model1TrainOutputCaptor = ArgumentCaptor.forClass(Matrix.class);
		verify(onlineModelListenerOnlineConsole, times(1)).setModel1TrainOutput(model1TrainOutputCaptor.capture());
		verifyMatricesAreSame(model1TrainOutputCaptor.getValue(), expectedModel1TrainOutput);
	}

	private void verifyModel2TrainOutputIsPassed() {
		ArgumentCaptor<Matrix> model2TrainOutputCaptor = ArgumentCaptor.forClass(Matrix.class);
		verify(onlineModelListenerOnlineConsole, times(1)).setModel2TrainOutput(model2TrainOutputCaptor.capture());
		verifyMatricesAreSame(model2TrainOutputCaptor.getValue(), expectedModel2TrainOutput);
	}

	private void verifyMatricesAreSame(Matrix actual, Matrix expected) {
		assertEquals(expected.getRows(), actual.getRows());
		assertEquals(expected.getCols(), actual.getCols());
		for (int i = 0; i < expected.getRows(); i++) {
			for (int j = 0; j < expected.getCols(); j++) {
				assertEquals(expected.get(i, j), actual.get(i, j), DELTA);
			}
		}
	}

	private void verifyModelConsoleConfiguration() {
		verify(onlineModelListenerOnlineConsole, times(1)).setOutputModelTrainingThread(Matchers.any(Thread.class));
		verify(onlineModelListenerOnlineConsole, times(1)).setBounds(100, 100, 750, 500);
		verify(onlineModelListenerOnlineConsole, times(1)).setReady(false);
		verify(onlineModelListenerOnlineConsole, times(1)).setOneModelMode(true);
		verify(onlineModelListenerOnlineConsole, times(1)).setVisible(true);
		verify(onlineModelListenerOnlineConsole, times(1)).toFront();
	}

	private void verifyModelConsoleConfigurationWithoutOneModelMode() {
		verify(onlineModelListenerOnlineConsole, times(1)).setOutputModelTrainingThread(Matchers.any(Thread.class));
		verify(onlineModelListenerOnlineConsole, times(1)).setBounds(100, 100, 750, 500);
		verify(onlineModelListenerOnlineConsole, times(1)).setReady(false);
		verify(onlineModelListenerOnlineConsole, times(1)).setOneModelMode(false);
		verify(onlineModelListenerOnlineConsole, times(1)).setVisible(true);
		verify(onlineModelListenerOnlineConsole, times(1)).toFront();
	}
}
