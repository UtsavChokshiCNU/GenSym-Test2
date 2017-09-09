package com.gensym.nols.data;

import com.gensym.DEBUG;
import com.gensym.math.MathException;
import com.gensym.math.datafit.Model;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Matchers;
import org.mockito.Mockito;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.Random;
import java.util.Vector;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.empty;
import static org.hamcrest.Matchers.greaterThanOrEqualTo;
import static org.hamcrest.Matchers.not;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;
import static org.powermock.api.mockito.PowerMockito.*;

public class ResponseSurfaceSimulationTest {
    private static final String INPUT_DATA_NAME = "Input";
    private static final String OUTPUT_DATA_NAME = "Output";
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();

    private boolean debugFlag;
    private boolean isEvaluatedThroughSubModel;
    private boolean isEvaluatedThroughStateModel;
    private boolean optimizeModelHasStateModel;
    private Matrix matrixXUsedToEvaluateModel;
    private Random randomGenerator;
    private Vector<String> preprocessorProcessedInputVarNames;
    private Vector<Variable> preprocessorVariables;

    @Before
    public void setup() {
        debugFlag = DEBUG.debugFlag;
        DEBUG.debugFlag = true;

        isEvaluatedThroughSubModel = false;
        isEvaluatedThroughStateModel = false;
        matrixXUsedToEvaluateModel = null;
        optimizeModelHasStateModel = false;
        preprocessorProcessedInputVarNames = new Vector<>();
        preprocessorVariables = new Vector<>();
        randomGenerator = new Random();

        setupStreams();
    }

    @After
    public void teardown() {
        DEBUG.debugFlag = debugFlag;
        cleanUpStreams();
    }

    @Test
    public void test_getMinMax_always_returnsVariableMinMax() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();
        String varName = "Variable 1";
        double min = 1;
        double max = 2;

        sut.setMinMax(varName, min, max);

        // Act
        double[] result = sut.getMinMax(varName);

        // Assert
        assertThat(result[0], is(equalTo(min)));
        assertThat(result[1], is(equalTo(max)));
    }

    @Test
    public void test_setMinMax_always_setsVariableMinMax() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();
        String varName = "Variable 1";
        sut.setMinMax(varName, 1, 2);
        double min = 3;
        double max = 4;

        // Act
        sut.setMinMax(varName, min, max);

        // Assert
        double[] result = sut.getMinMax(varName);
        assertThat(result[0], is(equalTo(min)));
        assertThat(result[1], is(equalTo(max)));
    }

    @Test
    public void test_getNumberOfPoints_always_returnsNumberOfPoints() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();
        int[] numberOfPointsList = new int[] { 10, 50, 100 };

        for (int numberOfPoints : numberOfPointsList)
        {
            sut.setNumberOfPoints(numberOfPoints);

            // Act & Assert
            assertThat(sut.getNumberOfPoints(), is(equalTo(numberOfPoints)));
        }
    }

    @Test
    public void test_getOutputData_dataSeriesIsEmpty_returnsNull() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();

        // Act & Assert
        assertNull(sut.getOutputData());
    }

    @Test
    public void test_getOutputData_dataSeriesContainsOutputData_returnsOutputData() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();
        Vector<DataSeries> inputOutputDataSeries = new Vector<>();
        inputOutputDataSeries.add(createDataSeries());
        sut.setDataSeries(inputOutputDataSeries);

        // Act & Assert
        assertThat(sut.getOutputData(), is(equalTo(inputOutputDataSeries.elementAt(0))));
    }

    @Test
    public void test_getInputData_dataSeriesIsEmpty_returnsNull() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();

        // Act & Assert
        assertNull(sut.getInputData());
    }

    @Test
    public void test_getInputData_dataSeriesIsDoesNotContainInputData_returnsNull() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();
        Vector<DataSeries> inputOutputDataSeries = createInputOutputDataSeries();
        inputOutputDataSeries.remove(1);
        sut.setDataSeries(inputOutputDataSeries);

        // Act & Assert
        assertNull(sut.getInputData());
    }

    @Test
    public void test_getInputData_dataSeriesContainsInputData_returnsInputData() {
        // Arrange
        ResponseSurfaceSimulation sut = createSut();
        Vector<DataSeries> inputOutputDataSeries = createInputOutputDataSeries();
        sut.setDataSeries(inputOutputDataSeries);

        // Act & Assert
        assertThat(sut.getInputData(), is(equalTo(inputOutputDataSeries.elementAt(1))));
    }

    @Test
    public void test_instance_createdWithNolOptimizeModel_setsMinMaxOfInputVariables() throws MathException, FormulaException {
        // Arrange
        NolOptimizeModel model = createNolOptimizeModel();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        assertThat(Arrays.asList(model.getInputs()), is(not(empty())));
        for (String varName : (Vector<String>) model.getInputs()) {
            Variable variable = model.getPreprocessor().getVariableFromVariableName(varName);
            double[] minMax = sut.getMinMax(varName);
            // In SUT, both first and second number is set as first statistics as follows.
            // minMax[0] = statistic[0];
            // minMax[1] = statistic[0];
            assertThat(minMax[0], is(equalTo(variable.getStatistics()[0])));
            assertThat(minMax[1], is(equalTo(variable.getStatistics()[0])));
        }
    }

    @Test
    public void test_instance_createdWithNolOptimizeModel_setsMinMaxOfOutputVariablesWhenDelayIsNonZero() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        assertThat(Arrays.asList(model.getOutputs()), is(not(empty())));
        for (int idx = 0; idx < model.getOutputs().size(); idx++) {
            String varName = ((Vector<String>) model.getOutputs()).get(idx);
            long[] delays = (long[]) model.getOutputDelays().elementAt(idx);

            assertThat(Arrays.asList(delays), is(not(empty())));
            for (long delay : delays) {
                if (delay > 0) {
                    Variable variable = model.getPreprocessor().getVariableFromVariableName(varName);
                    double[] minMax = sut.getMinMax(varName);
                    // In SUT, both first and second number is set as first statistics as follows.
                    // minMax[0] = statistic[0];
                    // minMax[1] = statistic[0];
                    assertThat(minMax[0], is(equalTo(variable.getStatistics()[0])));
                    assertThat(minMax[1], is(equalTo(variable.getStatistics()[0])));
                }
            }
        }
    }

    @Test
    public void test_instance_createdWithNolOptimizeModel_setsMinMaxOfInputStateVariables() throws MathException, FormulaException {
        // Arrange
        NolOptimizeModel model = createNolOptimizeModel();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        assertThat(Arrays.asList(model.getStateInput()), is(not(empty())));
        for (String varName : (Vector<String>) model.getStateInput()) {
            Variable variable = model.getPreprocessor().getVariableFromVariableName(varName);
            double[] minMax = sut.getMinMax(varName);
            // In SUT, both first and second number is set as first statistics as follows.
            // minMax[0] = statistic[0];
            // minMax[1] = statistic[0];
            assertThat(minMax[0], is(equalTo(variable.getStatistics()[0])));
            assertThat(minMax[1], is(equalTo(variable.getStatistics()[0])));
        }
    }

    @Test
    public void test_instance_createdWithNolOptimizeModel_setsInputData() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        DataSeries inputData = sut.getInputData();
        assertThat(inputData.getName(), is(equalTo(INPUT_DATA_NAME)));
        assertThat(Arrays.asList(model.getInputs()), is(not(empty())));
        for (String varName : (Vector<String>) model.getInputs()) {
            Variable expectedVariable = model.getPreprocessor().getVariableFromVariableName(varName);
            Variable actualVariable = inputData.getVarByName(varName);
            assertThat(actualVariable.getTag(), is(equalTo(expectedVariable.getTag())));
            assertThat(actualVariable.getUnit(), is(equalTo(expectedVariable.getUnit())));
        }
    }

    @Test
    public void test_instance_createdWithNolOptimizeModel_setsOutputData() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        DataSeries outputData = sut.getOutputData();
        assertThat(outputData.getName(), is(equalTo(OUTPUT_DATA_NAME)));
        assertThat(Arrays.asList(model.getOutputs()), is(not(empty())));
        for (String varName : (Vector<String>) model.getOutputs()) {
            Variable expectedVariable = model.getPreprocessor().getVariableFromVariableName(varName);
            Variable actualVariable = outputData.getVarByName(varName);
            assertThat(actualVariable.getTag(), is(equalTo(expectedVariable.getTag())));
            assertThat(actualVariable.getUnit(), is(equalTo(expectedVariable.getUnit())));
        }
    }

    @Test
    public void test_instance_createdWithNolModel2_setsMinMaxOfInputVariables() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        assertThat(Arrays.asList(model.getInputs()), is(not(empty())));
        for (String varName : (Vector<String>) model.getInputs()) {
            Variable variable = model.getPreprocessor().getVariableFromVariableName(varName);
            double[] minMax = sut.getMinMax(varName);
            // In SUT, both first and second number is set as first statistics as follows.
            // minMax[0] = statistic[0];
            // minMax[1] = statistic[0];
            assertThat(minMax[0], is(equalTo(variable.getStatistics()[0])));
            assertThat(minMax[1], is(equalTo(variable.getStatistics()[0])));
        }
    }

    @Test
    public void test_instance_createdWithNolModel2_setsMinMaxOfOutputVariables() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        assertThat(Arrays.asList(model.getOutputs()), is(not(empty())));
        for (int idx = 0; idx < model.getOutputs().size(); idx++) {
            String varName = ((Vector<String>) model.getOutputs()).get(idx);
            long[] delays = (long[]) model.getOutputDelays().elementAt(idx);

            assertThat(Arrays.asList(delays), is(not(empty())));
            for (long delay : delays) {
                if (delay > 0) {
                    Variable variable = model.getPreprocessor().getVariableFromVariableName(varName);
                    double[] minMax = sut.getMinMax(varName);
                    // In SUT, both first and second number is set as first statistics as follows.
                    // minMax[0] = statistic[0];
                    // minMax[1] = statistic[0];
                    assertThat(minMax[0], is(equalTo(variable.getStatistics()[0])));
                    assertThat(minMax[1], is(equalTo(variable.getStatistics()[0])));
                }
            }
        }
    }

    @Test
    public void test_instance_createdWithNolModel2_setsInputData() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        DataSeries inputData = sut.getInputData();
        assertThat(inputData.getName(), is(equalTo(INPUT_DATA_NAME)));
        assertThat(Arrays.asList(model.getInputs()), is(not(empty())));
        for (String varName : (Vector<String>) model.getInputs()) {
            Variable expectedVariable = model.getPreprocessor().getVariableFromVariableName(varName);
            Variable actualVariable = inputData.getVarByName(varName);
            assertThat(actualVariable.getTag(), is(equalTo(expectedVariable.getTag())));
            assertThat(actualVariable.getUnit(), is(equalTo(expectedVariable.getUnit())));
        }
    }

    @Test
    public void test_instance_createdWithNolModel2_setsOutputData() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();

        // Act
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Assert
        DataSeries outputData = sut.getOutputData();
        assertThat(outputData.getName(), is(equalTo(OUTPUT_DATA_NAME)));
        assertThat(Arrays.asList(model.getOutputs()), is(not(empty())));
        for (String varName : (Vector<String>) model.getOutputs()) {
            Variable expectedVariable = model.getPreprocessor().getVariableFromVariableName(varName);
            Variable actualVariable = outputData.getVarByName(varName);
            assertThat(actualVariable.getTag(), is(equalTo(expectedVariable.getTag())));
            assertThat(actualVariable.getUnit(), is(equalTo(expectedVariable.getUnit())));
        }
    }

    @Test
    public void test_calculateSimulation_modelIsNolModel2AndNumberOfPointsIsOne_updatesInputDataMatrix() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);
        Matrix expectedMatrix = expectedInputMatrixData(model, sut);

        // Act
        sut.calulationSimulation();

        // Assert
        DataSeries inputData = sut.getInputData();
        Matrix inputDataMatrix = inputData.getDataMatrix();
        assertAreEquals(expectedMatrix, inputDataMatrix);
    }

    @Test
    public void test_calculateSimulation_modelIsNolModel2AndThereAreMoreThanOnePoints_updatesInputDataMatrix() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);
        sut.setNumberOfPoints(3);
        Matrix expectedMatrix = expectedInputMatrixData(model, sut);

        // Act
        sut.calulationSimulation();

        // Assert
        DataSeries inputData = sut.getInputData();
        Matrix inputDataMatrix = inputData.getDataMatrix();
        assertAreEquals(expectedMatrix, inputDataMatrix);
    }

    @Test
    public void test_calculateSimulation_modelIsNolModel2_calculatesPredictiveModel() throws MathException, FormulaException {
        // Arrange
        NolModel2 model = createNolModel2();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);
        Matrix expectedMatrix = expectedMatrixUsedToCalculatePredictiveModel(model, sut);

        // Act
        sut.calulationSimulation();

        // Assert
        assertAreEquals(expectedMatrix, matrixXUsedToEvaluateModel);
    }

    @Test
    public void test_calculateSimulation_optmizeModelDoesNotHaveStateModelAndThereIsOnePoint_calculatesPredictiveModel() throws MathException, FormulaException {
        // Arrange
        NolOptimizeModel model = createNolOptimizeModel();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);
        Matrix expectedMatrix = expectedMatrixUsedToCalculateSubModel(model, sut);

        // Act
        sut.calulationSimulation();

        // Assert
        assertTrue(isEvaluatedThroughSubModel);
        assertAreEquals(expectedMatrix, matrixXUsedToEvaluateModel);
    }

    @Test
    public void test_calculateSimulation_optmizeModelDoesNotHaveStateModelAndThereAreMoreThanOnePoints_calculatesPredictiveModel() throws MathException, FormulaException {
        // Arrange
        NolOptimizeModel model = createNolOptimizeModel();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);
        sut.setNumberOfPoints(3);
        Matrix expectedMatrix = expectedMatrixUsedToCalculateSubModel(model, sut);

        // Act
        sut.calulationSimulation();

        // Assert
        assertTrue(isEvaluatedThroughSubModel);
        assertAreEquals(expectedMatrix, matrixXUsedToEvaluateModel);
    }

    @Test
    public void test_calculateSimulation_optmizeModelHasStateModelAndThereIsNoPoint_calculatesPredictiveModel() throws MathException, FormulaException {
        // Arrange
        optimizeModelHasStateModel = true;
        NolOptimizeModel model = createNolOptimizeModel();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);
        sut.setNumberOfPoints(0);

        // Act
        sut.calulationSimulation();

        // Assert
        assertTrue(isEvaluatedThroughStateModel);
        assertTrue(isEvaluatedThroughSubModel);
    }

    @Test
    public void test_calculateSimulation_optmizeModelHasStateModelAndThereIsOnePoint_calculatesPredictiveModel() throws MathException, FormulaException {
        // Arrange
        optimizeModelHasStateModel = true;
        NolOptimizeModel model = createNolOptimizeModel();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);

        // Act
        sut.calulationSimulation();

        // Assert
        assertTrue(isEvaluatedThroughStateModel);
        assertTrue(isEvaluatedThroughSubModel);
    }

    @Test
    public void test_calculateSimulation_optmizeModelHasStateModelAndThereAreMoreThanOnePoints_calculatesPredictiveModel() throws MathException, FormulaException {
        // Arrange
        optimizeModelHasStateModel = true;
        NolOptimizeModel model = createNolOptimizeModel();
        ResponseSurfaceSimulation sut = createSut(createProject(), model);
        sut.setNumberOfPoints(2);

        // Act
        sut.calulationSimulation();

        // Assert
        assertTrue(isEvaluatedThroughStateModel);
        assertTrue(isEvaluatedThroughSubModel);
    }

    private Matrix expectedMatrixUsedToCalculateSubModel(NolOptimizeModel model, ResponseSurfaceSimulation sut) {
        Vector inputs = model.getInputs();

        int ic = inputs.size();
        int numberOfPoints = sut.getNumberOfPoints();
        Matrix matrixX = Matlib.createMatrix(numberOfPoints, ic);
        for (int c = 0; c < ic; c++) {
            String varName = (String) inputs.elementAt(c);
            double[] minMax = sut.getMinMax(varName);
            if (numberOfPoints <= 1) {
                matrixX.set(0, c, minMax[0]);
            } else {
                for (int r = 0; r < numberOfPoints; r++) {
                    double value = minMax[0] + r * (minMax[1] - minMax[0]) / (numberOfPoints - 1);
                    matrixX.set(r, c, value);
                }
            }
        }

        return matrixX;
    }

    private Matrix expectedMatrixUsedToCalculatePredictiveModel(NolModel2 model, ResponseSurfaceSimulation sut) {
        Vector minMaxBuffer = new Vector();

        int inputCols = 0;
        for (int i = 0; i < model.getOutputDelays().size(); i++) {
            long[] dls = (long[]) model.getOutputDelays().elementAt(i);
            for (long dl : dls) {
                if (dl > 0) {
                    inputCols++;
                    String varName = (String) model.getOutputs().elementAt(i);
                    double[] minMax = sut.getMinMax(varName);
                    minMaxBuffer.addElement(minMax);
                }
            }
        }

        for (int i = 0; i < model.getInputDelays().size(); i++) {
            long[] dls = (long[]) model.getInputDelays().elementAt(i);
            for (long ignored : dls) {
                inputCols++;
                String varName = (String) model.getInputs().elementAt(i);
                double[] minMax = sut.getMinMax(varName);
                minMaxBuffer.addElement(minMax);
            }
        }

        Matrix matrixX = Matlib.createMatrix(sut.getNumberOfPoints(), inputCols);

        for (int c = 0; c < inputCols; c++) {
            double[] minMax = (double[]) minMaxBuffer.elementAt(c);
            if (sut.getNumberOfPoints() <= 1) {
                matrixX.set(0, c, minMax[0]);
            } else {
                for (int r = 0; r < sut.getNumberOfPoints(); r++) {
                    double value = minMax[0] + r * (minMax[1] - minMax[0]) / (sut.getNumberOfPoints() - 1);
                    matrixX.set(r, c, value);
                }
            }
        }

        return matrixX;
    }

    private void addPreprocessorVariables(Vector<String> inputs) {
        for (String input : inputs) {
            Variable variable = new Variable();
            variable.setName(input);
            variable.setTag(input + "Tag");
            variable.setUnit(input + "Unit");
            variable.setStatistics(createVariableStatistics());
            preprocessorVariables.add(variable);
        }
    }

    private void assertAreEquals(Matrix expected, Matrix actual) {
        assertNotNull(actual);
        assertThat(actual.getRows(), is(greaterThanOrEqualTo(expected.getRows())));
        assertThat(actual.getCols(), is(greaterThanOrEqualTo(expected.getCols())));
        for (int r = 0; r < expected.getRows(); r++) {
            for (int c = 0; c < expected.getCols(); c++) {
                assertThat(actual.get(r, c), is(equalTo(expected.get(r, c))));
            }
        }
    }

    private void cleanUpStreams() {
        System.setOut(null);
    }

    private DataSeries createDataSeries() {
        return mock(DataSeries.class);
    }

    private Vector<long[]> createDelays(Vector<String> names) {
        Vector<long[]> delaysList = new Vector<>();
        long baseDelay = System.currentTimeMillis();

        for (int idx = 0; idx < names.size(); idx++) {
            long[] delays = new long[idx];

            for (int dIdx = 0; dIdx < idx; dIdx++) {
                delays[dIdx] = baseDelay + 1000 * dIdx;
            }

            delaysList.add(delays);
        }

        return delaysList;
    }

    private Formula2 createFormula(String stringRepresentation, Vector<String> inputVarNames, long inputBufferLength)
            throws MathException, FormulaException {
        Formula2 formula = mock(Formula2.class);
        when(formula.getInputBufferLength()).thenReturn(inputBufferLength);
        when(formula.hasVariable(Matchers.anyString())).thenAnswer(invocation -> {
            String varName = invocation.getArgumentAt(0, String.class);
            return inputVarNames.contains(varName);
        });
        when(formula.toString()).thenReturn(stringRepresentation);
        return formula;
    }

    private Vector<DataSeries> createInputOutputDataSeries() {
        Vector<DataSeries> inputOutputDataSeries = new Vector<>();
        inputOutputDataSeries.add(createDataSeries());
        inputOutputDataSeries.add(createDataSeries());
        return inputOutputDataSeries;
    }

    private Vector<String> createNames(String namePrefix) {
        Vector<String> names = new Vector<>();

        for (int idx = 1; idx <= 3; idx++) {
            names.add(namePrefix + idx);
        }

        addPreprocessorVariables(names);
        return names;
    }

    private NolModel2 createNolModel2() throws MathException, FormulaException {
        NolModel2 model = mock(NolModel2.class);

        Preprocessor preprocessor = createPreprocessor();
        when(model.getPreprocessor()).thenReturn(preprocessor);

        Vector<String> modelInputs = createNames("inVar");

        when(model.getInputVarNames()).thenReturn(modelInputs);
        when(model.getInputs()).thenReturn(modelInputs);
        when(model.getInputDelays()).thenReturn(createDelays(modelInputs));

        Vector<String> modelOutputs = createNames("outVar");

        when(model.getOutputVarNames()).thenReturn(modelOutputs);
        when(model.getOutputs()).thenReturn(modelOutputs);
        when(model.getOutputDelays()).thenReturn(createDelays(modelOutputs));

        doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Matrix matrixX = invocation.getArgumentAt(0, Matrix.class);
                Matrix matrixY = invocation.getArgumentAt(1, Matrix.class);

                matrixXUsedToEvaluateModel = clone(matrixX);

                matrixY.redimension(matrixX.getRows(), matrixX.getCols());
                for (int r = 0; r < matrixX.getRows(); r++) {
                    for (int c = 0; c < matrixX.getCols(); c++) {
                        matrixY.set(r, c, randomGenerator.nextDouble());
                    }
                }

                return null;
            }

            private Matrix clone(Matrix matrix) {
                Matrix cloned = Matlib.createMatrix(matrix.getRows(), matrix.getCols());

                for (int r = 0; r < matrix.getRows(); r++) {
                    for (int c = 0; c < matrix.getCols(); c++) {
                        cloned.set(r, c, matrix.get(r, c));
                    }
                }

                return cloned;
            }
        }).when(model).evaluate(Matchers.any(Matrix.class), Matchers.any(Matrix.class));

        return model;
    }

    private NolOptimizeModel createNolOptimizeModel() throws MathException, FormulaException {
        NolOptimizeModel model = mock(NolOptimizeModel.class);

        Preprocessor preprocessor = createPreprocessor();
        when(model.getPreprocessor()).thenReturn(preprocessor);

        Vector<String> modelInputs = createNames("inVar");

        when(model.getInputVarNames()).thenReturn(modelInputs);
        when(model.getInputs()).thenReturn(modelInputs);
        when(model.getInputDelays()).thenReturn(createDelays(modelInputs));

        Vector<String> modelOutputs = createNames("outVar");

        when(model.getOutputVarNames()).thenReturn(modelOutputs);
        when(model.getOutputs()).thenReturn(modelOutputs);
        when(model.getOutputDelays()).thenReturn(createDelays(modelOutputs));

        Vector<String> modelStates = createNames("stateVar");

        when(model.getState()).thenReturn(modelStates);
        when(model.getStateDelays()).thenReturn(createDelays(modelStates));

        Vector<String> modelInputStates = createNames("inStateVar");

        when(model.getStateInput()).thenReturn(modelInputStates);
        when(model.getStateInputDelays()).thenReturn(createDelays(modelInputStates));

        model.model = mock(Model.class);
        when(model.getModel()).thenReturn(model.model);

        doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Matrix matrixX = invocation.getArgumentAt(0, Matrix.class);
                Matrix matrixY = invocation.getArgumentAt(1, Matrix.class);

                matrixXUsedToEvaluateModel = clone(matrixX);
                isEvaluatedThroughSubModel = true;

                matrixY.redimension(matrixX.getRows(), matrixX.getCols());
                for (int r = 0; r < matrixX.getRows(); r++) {
                    for (int c = 0; c < matrixX.getCols(); c++) {
                        matrixY.set(r, c, randomGenerator.nextDouble());
                    }
                }

                return null;
            }

            private Matrix clone(Matrix matrix) {
                Matrix cloned = Matlib.createMatrix(matrix.getRows(), matrix.getCols());

                for (int r = 0; r < matrix.getRows(); r++) {
                    for (int c = 0; c < matrix.getCols(); c++) {
                        cloned.set(r, c, matrix.get(r, c));
                    }
                }

                return cloned;
            }
        }).when(model.model).evaluate(Matchers.any(Matrix.class), Matchers.any(Matrix.class));

        if (optimizeModelHasStateModel) {
            Model stateModel = mock(Model.class);
            when(model.getStateModel()).thenReturn(stateModel);

            doAnswer(new Answer<Object>() {
                @Override
                public Object answer(InvocationOnMock invocation) throws Throwable {
                    Matrix matrixX = invocation.getArgumentAt(0, Matrix.class);
                    Matrix matrixY = invocation.getArgumentAt(1, Matrix.class);

                    matrixXUsedToEvaluateModel = clone(matrixX);
                    isEvaluatedThroughStateModel = true;

                    matrixY.redimension(matrixX.getRows(), matrixX.getCols());
                    for (int r = 0; r < matrixX.getRows(); r++) {
                        for (int c = 0; c < matrixX.getCols(); c++) {
                            matrixY.set(r, c, randomGenerator.nextDouble());
                        }
                    }

                    return null;
                }

                private Matrix clone(Matrix matrix) {
                    Matrix cloned = Matlib.createMatrix(matrix.getRows(), matrix.getCols());

                    for (int r = 0; r < matrix.getRows(); r++) {
                        for (int c = 0; c < matrix.getCols(); c++) {
                            cloned.set(r, c, matrix.get(r, c));
                        }
                    }

                    return cloned;
                }
            }).when(stateModel).evaluate(Matchers.any(Matrix.class), Matchers.any(Matrix.class));
        }

        return model;
    }

    private Preprocessor createPreprocessor() throws MathException, FormulaException {
        Preprocessor preprocessor = Mockito.mock(Preprocessor.class);
        when(preprocessor.getName()).thenReturn("Preprocessor Name");
        when(preprocessor.getComment()).thenReturn("Preprocessor Comments");

        Vector<Formula2> prepFormulas = createPreprocessorFormulas(preprocessorProcessedInputVarNames);
        when(preprocessor.getFormulas()).thenReturn(prepFormulas);

        when(preprocessor.getVariableFromVariableName(Matchers.anyString())).thenAnswer(invocation -> {
            String name = invocation.getArgumentAt(0, String.class);
            for (Variable preprocessorVariable : preprocessorVariables) {
                if (preprocessorVariable.getName().equals(name)) {
                    return preprocessorVariable;
                }
            }

            return null;
        });

        preprocessorProcessedInputVarNames = new Vector<>();
        for (int idx = 1; idx <= 3; idx++) {
            preprocessorProcessedInputVarNames.add("prepVar" + idx);
        }

        addPreprocessorVariables(preprocessorProcessedInputVarNames);

        doAnswer(invocation -> {
            Vector<String> processedVars = invocation.getArgumentAt(1, Vector.class);
            Vector<Formula2> formulas = invocation.getArgumentAt(3, Vector.class);

            processedVars.removeAllElements();
            for (String preprocessorProcessedInputVarName : preprocessorProcessedInputVarNames) {
                processedVars.add(preprocessorProcessedInputVarName);
            }

            formulas.removeAllElements();
            formulas.addAll(prepFormulas);
            return null;
        }).when(preprocessor).getInputNamesDerivedVarsFormulasForModel(Matchers.any(Vector.class),
                Matchers.any(Vector.class), Matchers.any(Vector.class), Matchers.any(Vector.class));

        return preprocessor;
    }

    private Vector<Formula2> createPreprocessorFormulas(Vector<String> inputVarNames)
            throws MathException, FormulaException {
        Vector<Formula2> formulas = new Vector<>();

        formulas.add(createFormula("Formula 1 To String", inputVarNames, 5));
        formulas.add(createFormula("Formula 2 To String", inputVarNames, 3));

        return formulas;
    }

    private Project createProject() {
        return mock(Project.class);
    }

    private double[] createVariableStatistics() {
        double[] statistics = new double[11];

        for (int idx = 0; idx < statistics.length; idx++) {
            statistics[idx] = randomGenerator.nextDouble();
        }

        return statistics;
    }

    private ResponseSurfaceSimulation createSut() {
        return new ResponseSurfaceSimulation();
    }

    private ResponseSurfaceSimulation createSut(Project project, NolModel2 model) throws MathException {
        return new ResponseSurfaceSimulation(project, model);
    }

    private Matrix expectedInputMatrixData(NolModel2 model, ResponseSurfaceSimulation simulation) {
        Vector outputs = model.getOutputs();
        Vector inputs = model.getInputs();
        Vector outputDelays = model.getOutputDelays();
        int numberOfPoints = simulation.getNumberOfPoints();

        int inputVarCount = 0;
        for (int i = 0; i < outputDelays.size(); i++) {
            long[] dls = (long[]) outputDelays.elementAt(i);
            for (long dl : dls) {
                if (dl > 0) {
                    inputVarCount++;
                    break;
                }
            }
        }

        inputVarCount = inputVarCount + inputs.size();

        Matrix inputM = Matlib.createMatrix(numberOfPoints, inputVarCount);

        int ccc = 0;
        for (int i = 0; i < outputDelays.size(); i++) {
            long[] dls = (long[]) outputDelays.elementAt(i);
            for (long dl : dls) {
                if (dl > 0) {
                    String varName = outputs.elementAt(i).toString();
                    double[] minMax = simulation.getMinMax(varName);
                    if (numberOfPoints <= 1) {
                        inputM.set(0, ccc, minMax[0]);
                    } else {
                        for (int r = 0; r < numberOfPoints; r++) {
                            double value = minMax[0] + r * (minMax[1] - minMax[0]) / (numberOfPoints - 1);
                            inputM.set(r, ccc, value);
                        }
                    }
                    ccc++;
                    break;
                }
            }
        }

        for (int c = 0; c < inputs.size(); c++) {
            String varName = inputs.elementAt(c).toString();
            double[] minMax = simulation.getMinMax(varName);
            if (numberOfPoints <= 1) {
                inputM.set(0, c + ccc, minMax[0]);
            } else {
                for (int r = 0; r < numberOfPoints; r++) {
                    double value = minMax[0] + r * (minMax[1] - minMax[0]) / (numberOfPoints - 1);
                    inputM.set(r, c + ccc, value);
                }
            }
        }

        return inputM;
    }

    private void setupStreams() {
        System.setOut(new PrintStream(outContent));
    }
}