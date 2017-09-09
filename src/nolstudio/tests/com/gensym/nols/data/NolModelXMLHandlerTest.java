package com.gensym.nols.data;

import com.gensym.math.MathException;
import com.gensym.math.Utilities;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.mockito.Matchers;

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Objects;
import java.util.Random;
import java.util.Vector;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.greaterThan;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class NolModelXMLHandlerTest {
    private static final int ROUND_OFF_DIGITS = 4;
    private static final String NOL_BPN_MODEL_CONTENT = "NolBpnModel writeXMLFile is invoked.\n";
    private static final String ENSEMBLE_MODEL_CONTENT = "EnsembleModel writeXMLFile is invoked.\n";
    private static final String NOL_PLS_MODEL_CONTENT = "NolPlsModel writeXMLFile is invoked.\n";
    private static final String NOL_RBFN_MODEL_CONTENT = "NolRbfnModel writeXMLFile is invoked.\n";

    private final static Random randomGenerator = new Random();
    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();
    private NolModelXMLHandler sut;

    private static String readFileContents(File file)
            throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(file.getAbsolutePath()));
        return new String(encoded);
    }

    @Before
    public void setup() {
        sut = new NolModelXMLHandler();
    }

    @Test
    public void test_clone_always_clonesHandler() throws MathException, CloneNotSupportedException {
        // Arrange
        NolModelXMLHandler handler;
        NolModel2 model = createNolModel2();
        sut.setModel(model);

        // Act
        handler = (NolModelXMLHandler) sut.clone();

        // Assert
        assertThat(handler.getModelRate(), is(equalTo(sut.getModelRate())));
    }

    @Test
    public void test_setModel_modelIsNotTrained_resetsAllModelStats() throws MathException {
        // Assert
        NolModel2 model = createNolModel2();

        // Act
        sut.setModel(model);

        // Assert
        assertThat(sut.getModelRate(), is(equalTo(0.0)));
        assertThat(sut.getTestingCorref().size(), is(equalTo(0)));
        assertThat(sut.getTestingRmse().size(), is(equalTo(0)));
        assertThat(sut.getTrainingCorroef().size(), is(equalTo(0)));
        assertThat(sut.getTrainingRmse().size(), is(equalTo(0)));
    }

    @Test
    public void test_setModel_modelIsTrained_setsModelRateValue() throws MathException {
        // Assert
        NolModel2 model = createNolModel2();
        model.setIsTrained(true);

        // Act
        sut.setModel(model);

        // Assert
        assertThat(sut.getModelRate(), is(equalTo(expectedModelRateValue((EnsembleModel) model.getModel()))));
        verifyTestingCorrefIsMatching(model);
        verifyTestingRmseIsMatching(model);
        verifyTrainingCorrefIsMatching(model);
        verifyTrainingRmseIsMatching(model);
    }

    @Test
    public void test_setModel_modelIsTrained_setsTestingCorref() throws MathException {
        // Assert
        NolModel2 model = createNolModel2();
        model.setIsTrained(true);

        // Act
        sut.setModel(model);

        // Assert
        verifyTestingCorrefIsMatching(model);
    }

    @Test
    public void test_setModel_modelIsTrained_setsTestingRmse() throws MathException {
        // Assert
        NolModel2 model = createNolModel2();
        model.setIsTrained(true);

        // Act
        sut.setModel(model);

        // Assert
        verifyTestingRmseIsMatching(model);
    }

    @Test
    public void test_setModel_modelIsTrained_setsTrainingCorref() throws MathException {
        // Assert
        NolModel2 model = createNolModel2();
        model.setIsTrained(true);

        // Act
        sut.setModel(model);

        // Assert
        verifyTrainingCorrefIsMatching(model);
    }

    @Test
    public void test_setModel_modelIsTrained_setsTrainingRmse() throws MathException {
        // Assert
        NolModel2 model = createNolModel2();
        model.setIsTrained(true);

        // Act
        sut.setModel(model);

        // Assert
        verifyTrainingRmseIsMatching(model);
    }

    @Test
    public void test_setModelRate_always_setsModelRateValue() {
        // Arrange
        double modelRateValue = randomGenerator.nextDouble();

        // Act
        sut.setModelRate(modelRateValue);

        // Assert
        assertThat(sut.getModelRate(), is(equalTo(modelRateValue)));
    }

    @Test
    public void test_saveToFile_modelIsNolAnnModelInstance_savesAnnModelToFile() throws IOException, MathException {
        // Arrange
        NolAnnModel model = createNolAnnModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForAnnModel(model))));
    }

    @Test
    public void test_saveToFileWithoutDirectory_modelIsNolAnnModelInstance_savesAnnModelToFile() throws IOException, MathException {
        // Arrange
        NolAnnModel model = createNolAnnModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath(), null);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForAnnModel(model))));
    }

    @Test
    public void test_saveToFileWithDirectory_modelIsNolAnnModelInstance_savesAnnModelToFile() throws IOException, MathException {
        // Arrange
        NolAnnModel model = createNolAnnModel();
        sut.setModel(model);
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        sut.saveToFile(filename, directory);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForAnnModel(model))));
    }

    @Test
    public void test_saveToFile_modelIsNolBpnModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolBpnModel model = createNolBpnModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForBpnModel(model))));
    }

    @Test
    public void test_saveToFileWithoutDirectory_modelIsNolBpnModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolBpnModel model = createNolBpnModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath(), null);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForBpnModel(model))));
    }

    @Test
    public void test_saveToFileWithDirectory_modelIsNolBpnModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolBpnModel model = createNolBpnModel();
        sut.setModel(model);
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        sut.saveToFile(filename, directory);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForBpnModel(model))));
    }

    @Test
    public void test_saveToFile_modelIsNolRhoModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolRhoModel model = createNolRhoModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForRhoModel(model))));
    }

    @Test
    public void test_saveToFileWithoutDirectory_modelIsNolRhoModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolRhoModel model = createNolRhoModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath(), null);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForRhoModel(model))));
    }

    @Test
    public void test_saveToFileWithDirectory_modelIsNolRhoModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolRhoModel model = createNolRhoModel();
        sut.setModel(model);
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        sut.saveToFile(filename, directory);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForRhoModel(model))));
    }

    @Test
    public void test_saveToFile_modelIsNolRbfnModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolRbfnModel model = createNolRbfnModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForRbfnModel(model))));
    }

    @Test
    public void test_saveToFileWithoutDirectory_modelIsNolRbfnModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolRbfnModel model = createNolRbfnModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath(), null);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForRbfnModel(model))));
    }

    @Test
    public void test_saveToFileWithDirectory_modelIsNolRbfnModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolRbfnModel model = createNolRbfnModel();
        sut.setModel(model);
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        sut.saveToFile(filename, directory);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForRbfnModel(model))));
    }

    @Test
    public void test_saveToFile_modelIsNolPlsModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolPlsModel model = createNolPlsModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForPlsModel(model))));
    }

    @Test
    public void test_saveToFileWithoutDirectory_modelIsNolPlsModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolPlsModel model = createNolPlsModel();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath(), null);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForPlsModel(model))));
    }

    @Test
    public void test_saveToFileWithDirectory_modelIsNolPlsModelInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolPlsModel model = createNolPlsModel();
        sut.setModel(model);
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        sut.saveToFile(filename, directory);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForPlsModel(model))));
    }

    @Test
    public void test_saveToFile_modelIsNolModel2StubInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolModel2Stub model = createNolModel2Stub();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForNolModel2Stub(model))));
    }

    @Test
    public void test_saveToFileWithoutDirectory_modelIsNolModel2StubInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolModel2Stub model = createNolModel2Stub();
        sut.setModel(model);
        File file = createFile();

        // Act
        sut.saveToFile(file.getAbsolutePath(), null);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForNolModel2Stub(model))));
    }

    @Test
    public void test_saveToFileWithDirectory_modelIsNolModel2StubInstance_savesBpnModelToFile() throws IOException, MathException {
        // Arrange
        NolModel2Stub model = createNolModel2Stub();
        sut.setModel(model);
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        sut.saveToFile(filename, directory);

        // Assert
        String content = readFileContents(file);
        assertThat(content, is(equalTo(expectedXmlForNolModel2Stub(model))));
    }

    // -- Helper Methods --

    private void arrangeBpnModelWriteXmlFile(NolBpnModel model) throws IOException, MathException {
        when(model.writeXMLFile(Matchers.any(BufferedWriter.class), Matchers.anyInt())).thenAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            int indentation = invocation.getArgumentAt(1, int.class);
            String stringBuilder = indent(indentation) + NOL_BPN_MODEL_CONTENT;
            target.write(stringBuilder, 0, stringBuilder.length());

            return null;
        });
    }

    private void arrangePlsModelWriteXmlFile(NolPlsModel model) throws IOException, MathException {
        when(model.writeXMLFile(Matchers.any(BufferedWriter.class), Matchers.anyInt())).thenAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            int indentation = invocation.getArgumentAt(1, int.class);
            String stringBuilder = indent(indentation) + NOL_PLS_MODEL_CONTENT;
            target.write(stringBuilder, 0, stringBuilder.length());

            return null;
        });
    }

    private void arrangeRbfnModelWriteXmlFile(NolRbfnModel model) throws IOException, MathException {
        when(model.writeXMLFile(Matchers.any(BufferedWriter.class), Matchers.anyInt())).thenAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            int indentation = invocation.getArgumentAt(1, int.class);
            String stringBuilder = indent(indentation) + NOL_RBFN_MODEL_CONTENT;
            target.write(stringBuilder, 0, stringBuilder.length());

            return null;
        });
    }

    private void arrangeTrainableModels(EnsembleModel model) throws MathException {
        int trainableModelSamplesCount = 3;

        for (int i = 0; i < trainableModelSamplesCount; i++) {
            int architectureParametersSampleNumberOfInputs = 1;
            int architectureParametersSampleNumberOfOutputs = 2;
            int architectureParametersSampleNumberOfHidden = 3;
            int architectureParametersSampleNumberOfFactors = 4;
            ArchitectureParameters params = new ArchitectureParameters(
                    architectureParametersSampleNumberOfInputs,
                    architectureParametersSampleNumberOfOutputs,
                    architectureParametersSampleNumberOfHidden,
                    architectureParametersSampleNumberOfFactors);
            TrainableModel subModel = new TrainableModel(params);
            ValidationParameters trainingResults = mock(ValidationParameters.class);

            Matrix trainingRmse = Matlib.createMatrix(1, 2);
            trainingRmse.set(0, 0, randomGenerator.nextInt(100));
            trainingRmse.set(0, 1, randomGenerator.nextInt(100));
            trainingResults.rmse = trainingRmse;

            Matrix trainingCorref = Matlib.createMatrix(1, 2);
            trainingCorref.set(0, 0, randomGenerator.nextInt(100));
            trainingCorref.set(0, 1, randomGenerator.nextInt(100));
            trainingResults.corrcoef = trainingCorref;

            subModel.trainingResults = trainingResults;

            // Testing Results

            ValidationParameters testingResults = mock(ValidationParameters.class);

            Matrix testingRmse = Matlib.createMatrix(1, 2);
            testingRmse.set(0, 0, randomGenerator.nextInt(100));
            testingRmse.set(0, 1, randomGenerator.nextInt(100));
            testingResults.rmse = testingRmse;

            Matrix testingCorref = Matlib.createMatrix(1, 2);
            testingCorref.set(0, 0, randomGenerator.nextInt(100));
            testingCorref.set(0, 1, randomGenerator.nextInt(100));
            testingResults.corrcoef = testingCorref;

            subModel.testingResults = testingResults;

            model.addModel(subModel);
        }
    }

    private Vector<long[]> createDelays(int numberOfVariables) {
        Vector<long[]> delays = new Vector<>();

        for (int i = 0; i < numberOfVariables; i++) {
            int variableDelaySamplesCount = 3;
            long[] delay = new long[variableDelaySamplesCount];
            for (int j = 0; j < delay.length; j++) {
                delay[j] = randomGenerator.nextLong();
            }

            delays.addElement(delay);
        }

        return delays;
    }

    private Vector createDoublesVector() {
        int doubleSamplesCount = 3;
        Vector<String> doubles = new Vector<>();
        for (int i = 0; i < doubleSamplesCount; i++) {
            doubles.add(Utilities.formatDouble(randomGenerator.nextDouble(), ROUND_OFF_DIGITS));
        }

        return doubles;
    }

    private EnsembleModel createEnsembleModel() throws MathException {
        int architectureParametersSampleNumberOfInputs = 1;
        int architectureParametersSampleNumberOfOutputs = 2;
        int architectureParametersSampleNumberOfHidden = 3;
        int architectureParametersSampleNumberOfFactors = 4;
        ArchitectureParameters params = new ArchitectureParameters(
                architectureParametersSampleNumberOfInputs,
                architectureParametersSampleNumberOfOutputs,
                architectureParametersSampleNumberOfHidden,
                architectureParametersSampleNumberOfFactors);
        EnsembleModel model = new EnsembleModel(params);
        arrangeTrainableModels(model);
        return model;
    }

    private File createFile() throws IOException {
        return temporaryFolder.newFile();
    }

    private NolAnnModel createNolAnnModel() throws IOException, MathException {
        NolAnnModel model = mock(NolAnnModel.class);
        setModelProperties(model, "NolAnnModel");

        when(model.getHasTimeStamps()).thenReturn(true);
        Vector<long[]> inputDelays = createDelays(model.getInputs().size());
        inputDelays.set(0, new long[0]);
        inputDelays.set(1, new long[] { 0 });
        when(model.getInputDelays()).thenReturn(inputDelays);

        arrangeBpnModelWriteXmlFile(model);
        return model;
    }

    private NolBpnModel createNolBpnModel() throws IOException, MathException {
        NolBpnModel model = mock(NolBpnModel.class);
        setModelProperties(model, "NolBpnModel");
        when(model.getHasTimeStamps()).thenReturn(false);
        arrangeBpnModelWriteXmlFile(model);
        return model;
    }

    private NolModel2 createNolModel2() throws MathException {
        NolModel2 model = new NolModel2();

        // Initializing Architecture Parameters object with random numbers.
        model.setModel(createEnsembleModel());

        return model;
    }

    private NolModel2Stub createNolModel2Stub() throws IOException, MathException {
        NolModel2Stub model = mock(NolModel2Stub.class);

        setModelProperties(model, "NolModel2Stub");
        EnsembleModel ensembleModel = mock(EnsembleModel.class);
        when(ensembleModel.writeXMLFile(Matchers.any(BufferedWriter.class), Matchers.anyInt())).thenAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            int indentation = invocation.getArgumentAt(1, int.class);
            String stringBuilder = indent(indentation) + ENSEMBLE_MODEL_CONTENT;
            target.write(stringBuilder, 0, stringBuilder.length());

            return null;
        });

        when(model.getModel()).thenReturn(ensembleModel);

        return model;
    }

    private NolPlsModel createNolPlsModel() throws IOException, MathException {
        NolPlsModel model = mock(NolPlsModel.class);
        when(model.getHasTimeStamps()).thenReturn(true);
        setModelProperties(model, "NolPlsModel");
        arrangePlsModelWriteXmlFile(model);
        return model;
    }

    private NolRbfnModel createNolRbfnModel() throws IOException, MathException {
        NolRbfnModel model = mock(NolRbfnModel.class);
        setModelProperties(model, "NolRbfnModel");
        arrangeRbfnModelWriteXmlFile(model);
        return model;
    }

    private NolRhoModel createNolRhoModel() throws IOException, MathException {
        NolRhoModel model = mock(NolRhoModel.class);
        setModelProperties(model, "NolRhoModel");
        arrangeRbfnModelWriteXmlFile(model);
        return model;
    }

    private Preprocessor createPreprocessor(Vector<String> variableNames) {
        Preprocessor preprocessor = mock(Preprocessor.class);

        Vector<Variable> variables = new Vector<>();
        for (String variableName : variableNames) {
            Variable variable = new Variable();
            variable.setName(variableName);
            variable.setTag(variableName + "Tag");
            variable.setUnit(variableName + "Unit");

            double[] statistics = new double[11];
            for (int i = 0; i < statistics.length; i++) {
                statistics[i] = randomGenerator.nextDouble();
            }

            variable.setStatistics(statistics);
            variables.addElement(variable);
        }

        when(preprocessor.getVariableFromVariableName(Matchers.anyString())).thenAnswer(invocation -> {
            String variableName = invocation.getArgumentAt(0, String.class);

            for (Variable variable : variables) {
                if (Objects.equals(variable.getName(), variableName)) {
                    return variable;
                }
            }

            return null;
        });

        return preprocessor;
    }

    private Vector<String> createVariableNames(String prefix) {
        int variableSamplesCount = 3;
        Vector<String> variableNames = new Vector<>();
        for (int i = 0; i < variableSamplesCount; i++) {
            variableNames.add(prefix + i);
        }

        return variableNames;
    }

    private Double expectedModelRateValue(EnsembleModel model) {
        int ensembleSize = model.size();
        int outputs = model.getNout();

        double[] corr = new double[outputs];
        double testingRate = 0;
        for (int j = 0; j < outputs; j++) {
            corr[j] = 0.0;
            for (int i = 0; i < ensembleSize; i++) {
                TrainableModel subModel = (TrainableModel) model.getModel(i);
                ValidationParameters params = subModel.testingResults;
                corr[j] += params.corrcoef.get(j);
            }

            corr[j] /= ensembleSize;
        }

        for (int i = 0; i < outputs; i++) {
            testingRate = testingRate + corr[i];
        }

        testingRate = testingRate / outputs;

        corr = new double[outputs];
        double trainingRate = 0;
        for (int j = 0; j < outputs; j++) {
            corr[j] = 0.0;
            for (int i = 0; i < ensembleSize; i++) {
                TrainableModel subModel = (TrainableModel) model.getModel(i);
                corr[j] += subModel.trainingResults.corrcoef.get(j);
            }

            corr[j] /= ensembleSize;
        }

        for (int i = 0; i < outputs; i++) {
            trainingRate = trainingRate + corr[i];
        }

        trainingRate = trainingRate / outputs;

        return (testingRate + trainingRate) / 2;
    }

    private double[] expectedTrainingCorr(EnsembleModel model) {
        int ensembleSize = model.size();
        int outputs = model.getNout();

        double[] corr = new double[outputs];
        for (int j = 0; j < outputs; j++) {
            corr[j] = 0.0;
            for (int i = 0; i < ensembleSize; i++) {
                TrainableModel subModel = (TrainableModel) model.getModel(i);
                ValidationParameters params = subModel.trainingResults;
                corr[j] += params.corrcoef.get(j);
            }

            corr[j] /= ensembleSize;
        }

        return corr;
    }

    private double[] expectedTrainingRmse(EnsembleModel model) {
        int ensembleSize = model.size();
        int outputs = model.getNout();

        double[] rmse = new double[outputs];
        for (int j = 0; j < outputs; j++) {
            rmse[j] = 0.0;
            for (int i = 0; i < ensembleSize; i++) {
                TrainableModel trainingModel = (TrainableModel) model.getModel(i);
                ValidationParameters params = trainingModel.trainingResults;
                rmse[j] += params.rmse.get(j);
            }

            rmse[j] /= ensembleSize;
        }

        return rmse;
    }

    private double[] expectedTestingCorr(EnsembleModel model) {
        int ensembleSize = model.size();
        int outputs = model.getNout();

        double[] corr = new double[outputs];
        for (int j = 0; j < outputs; j++) {
            corr[j] = 0.0;
            for (int i = 0; i < ensembleSize; i++) {
                TrainableModel subModels = (TrainableModel) model.getModel(i);
                ValidationParameters params = subModels.testingResults;
                corr[j] += params.corrcoef.get(j);
            }

            corr[j] /= ensembleSize;
        }

        return corr;
    }

    private double[] expectedTestingRmse(EnsembleModel model) {
        int ensembleSize = model.size();
        int outputs = model.getNout();

        double[] rmse = new double[outputs];
        for (int j = 0; j < outputs; j++) {
            rmse[j] = 0.0;
            for (int i = 0; i < ensembleSize; i++) {
                TrainableModel subModel = (TrainableModel) model.getModel(i);
                ValidationParameters params = subModel.testingResults;
                rmse[j] += params.rmse.get(j);
            }

            rmse[j] /= ensembleSize;
        }

        return rmse;
    }

    private String expectedXmlForAnnModel(NolAnnModel model) {
        StringBuilder stringBuilder = new StringBuilder("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        stringBuilder.append("<GNNEAANModel>\n");

        int indentTabs = expectedXmlForModel(stringBuilder, model);

        stringBuilder.append(indent(indentTabs)).append(NOL_BPN_MODEL_CONTENT);
        stringBuilder.append("</GNNEAANModel>");
        return stringBuilder.toString();
    }

    private String expectedXmlForBpnModel(NolBpnModel model) {
        StringBuilder stringBuilder = new StringBuilder("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        stringBuilder.append("<GNNEBPNModel>\n");

        int indentTabs = expectedXmlForModel(stringBuilder, model);

        stringBuilder.append(indent(indentTabs)).append(NOL_BPN_MODEL_CONTENT);
        stringBuilder.append("</GNNEBPNModel>");
        return stringBuilder.toString();
    }

    private String expectedXmlForNolModel2Stub(NolModel2 model) {
        StringBuilder stringBuilder = new StringBuilder("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        stringBuilder.append("<PredictiveModel>\n");

        int indentTabs = expectedXmlForModel(stringBuilder, model);

        stringBuilder.append(indent(indentTabs)).append(ENSEMBLE_MODEL_CONTENT);
        stringBuilder.append("</PredictiveModel>");
        return stringBuilder.toString();
    }

    private String expectedXmlForPlsModel(NolPlsModel model) {
        StringBuilder stringBuilder = new StringBuilder("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        stringBuilder.append("<GNNEPLSModel>\n");

        int indentTabs = expectedXmlForModel(stringBuilder, model);

        stringBuilder.append(indent(indentTabs)).append(NOL_PLS_MODEL_CONTENT);
        stringBuilder.append("</GNNEPLSModel>");
        return stringBuilder.toString();
    }

    private String expectedXmlForRbfnModel(NolRbfnModel model) {
        StringBuilder stringBuilder = new StringBuilder("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        stringBuilder.append("<GNNERBFNModel>\n");

        int indentTabs = expectedXmlForModel(stringBuilder, model);

        stringBuilder.append(indent(indentTabs)).append(NOL_RBFN_MODEL_CONTENT);
        stringBuilder.append("</GNNERBFNModel>");
        return stringBuilder.toString();
    }

    private String expectedXmlForRhoModel(NolRhoModel model) {
        StringBuilder stringBuilder = new StringBuilder("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        stringBuilder.append("<GNNERHOModel>\n");

        int indentTabs = expectedXmlForModel(stringBuilder, model);

        stringBuilder.append(indent(indentTabs)).append(NOL_RBFN_MODEL_CONTENT);
        stringBuilder.append("</GNNERHOModel>");
        return stringBuilder.toString();
    }

    private int expectedXmlForModel(StringBuilder stringBuilder, NolModel2 model) {
        int indentTabs = 1;
        indentTabs = expectedXmlForModelProperties(stringBuilder, model, indentTabs);
        indentTabs = expectedXmlForOutputVariableRmseAndCorref(stringBuilder, model, indentTabs);
        indentTabs = expectedXmlForVariableStatistics(stringBuilder, model, indentTabs);

        indentTabs--;
        stringBuilder.append(indent(indentTabs)).append("</variables>\n");

        return indentTabs;
    }

    private int expectedXmlForModelProperties(StringBuilder stringBuilder, NolModel2 model, int indentTabs) {
        stringBuilder.append(indent(indentTabs)).append("<name>").append(model.getName()).append("</name>\n");
        stringBuilder.append(indent(indentTabs)).append("<comment>").append(model.getComment()).append("</comment>\n");
        stringBuilder.append(indent(indentTabs)).append("<isTimeBased>").append(model.getHasTimeStamps()).append("</isTimeBased>\n");
        stringBuilder.append(indent(indentTabs)).append("<modelStatistics>\n");
        indentTabs++;
        stringBuilder.append(indent(indentTabs)).append("<modelRate>").append(model.getModelRate()).append("</modelRate>\n");
        stringBuilder.append(indent(indentTabs)).append("<outputStatistics>\n");
        indentTabs++;
        return indentTabs;
    }

    private int expectedXmlForOutputVariableRmseAndCorref(StringBuilder stringBuilder, NolModel2 model, int indentTabs) {
        Vector outputVarNames = model.getOutputVarNames();
        Vector trainingRmse = model.getTrainingRmse();
        Vector trainingCorref = model.getTrainingCorrcoef();
        Vector testingRmse = model.getTestingRmse();
        Vector testingCorref = model.getTestingCorrcoef();

        int outputsCount = model.getOutputVarNames().size();
        for (int i = 0; i < outputsCount; i++) {
            stringBuilder.append(indent(indentTabs)).append("<variableStatistics>\n");
            indentTabs++;
            stringBuilder.append(indent(indentTabs)).append("<name>").append(outputVarNames.elementAt(i)).append("</name>\n");
            stringBuilder.append(indent(indentTabs)).append("<training>\n");
            indentTabs++;
            stringBuilder.append(indent(indentTabs)).append("<rmse>").append(trainingRmse.elementAt(i)).append("</rmse>\n");
            stringBuilder.append(indent(indentTabs)).append("<corrcoef>").append(trainingCorref.elementAt(i)).append("</corrcoef>\n");
            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</training>\n");

            stringBuilder.append(indent(indentTabs)).append("<testing>\n");
            indentTabs++;
            stringBuilder.append(indent(indentTabs)).append("<rmse>").append(testingRmse.elementAt(i)).append("</rmse>\n");
            stringBuilder.append(indent(indentTabs)).append("<corrcoef>").append(testingCorref.elementAt(i)).append("</corrcoef>\n");
            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</testing>\n");
            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</variableStatistics>\n");
        }

        indentTabs--;
        stringBuilder.append(indent(indentTabs)).append("</outputStatistics>\n");
        indentTabs--;
        stringBuilder.append(indent(indentTabs)).append("</modelStatistics>\n");
        return indentTabs;
    }

    private int expectedXmlForVariableStatistics(StringBuilder stringBuilder, NolModel2 model, int indentTabs) {
        Vector modelOutputs = model.getOutputs();
        int outputsCount = modelOutputs.size();
        Preprocessor preprocessor = model.getPreprocessor();

        int inputIndex = 0;
        Vector outDelays = model.getOutputDelays();
        stringBuilder.append(indent(indentTabs)).append("<variables>\n");
        indentTabs++;

        for (int i = 0; i < outputsCount; i++) {
            stringBuilder.append(indent(indentTabs)).append("<variable>\n");
            indentTabs++;

            String varName = (String) modelOutputs.elementAt(i);
            Variable varObj = preprocessor.getVariableFromVariableName(varName);

            stringBuilder.append(indent(indentTabs)).append("<name>").append(varObj.getName()).append("</name>\n");
            if (!varObj.getTag().equals("")) {
                stringBuilder.append(indent(indentTabs)).append("<tag>").append(varObj.getTag()).append("</tag>\n");
            }

            if (!(varObj.getUnit().equals("")) && !(varObj.getUnit().equals("None"))) {
                stringBuilder.append(indent(indentTabs)).append("<unit>").append(varObj.getUnit()).append("</unit>\n");
            }

            stringBuilder.append(indent(indentTabs)).append("<statistics>\n");
            indentTabs++;
            stringBuilder.append(indent(indentTabs)).append("<min>").append(varObj.getMinValue()).append("</min>\n");
            stringBuilder.append(indent(indentTabs)).append("<max>").append(varObj.getMaxValue()).append("</max>\n");
            stringBuilder.append(indent(indentTabs)).append("<mean>").append(varObj.getMeanValue()).append("</mean>\n");
            stringBuilder.append(indent(indentTabs)).append("<median>").append(varObj.getMedianValue()).append("</median>\n");
            stringBuilder.append(indent(indentTabs)).append("<std>").append(varObj.getSTD()).append("</std>\n");
            stringBuilder.append(indent(indentTabs)).append("<variance>").append(varObj.getVariance()).append("</variance>\n");
            stringBuilder.append(indent(indentTabs)).append("<kurt>").append(varObj.getKurt()).append("</kurt>\n");
            stringBuilder.append(indent(indentTabs)).append("<skew>").append(varObj.getSkew()).append("</skew>\n");
            stringBuilder.append(indent(indentTabs)).append("<range>").append(varObj.getRange()).append("</range>\n");
            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</statistics>\n");

            stringBuilder.append(indent(indentTabs)).append("<node>\n");
            indentTabs++;
            stringBuilder.append(indent(indentTabs)).append("<index>").append(i).append("</index>\n");
            stringBuilder.append(indent(indentTabs)).append("<classification>output</classification>\n");
            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</node>\n");

            if (model.getHasTimeStamps()) {
                long[] delays = (long[]) outDelays.elementAt(i);
                if (delays.length > 0) {
                    if (delays.length != 1 || delays[0] != 0) {
                        for (long delay : delays) {
                            stringBuilder.append(indent(indentTabs)).append("<node>\n");
                            indentTabs++;
                            stringBuilder.append(indent(indentTabs)).append("<index>").append(inputIndex).append("</index>\n");
                            inputIndex = inputIndex + 1;
                            stringBuilder.append(indent(indentTabs)).append("<classification>input</classification>\n");
                            stringBuilder.append(indent(indentTabs)).append("<delay>").append(delay).append("</delay>\n");
                            indentTabs--;
                            stringBuilder.append(indent(indentTabs)).append("</node>\n");
                        }
                    }
                }
            }

            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</variable>\n");
        }

        Vector ins = model.getInputs();
        Vector inDelays = model.getInputDelays();
        for (int i = 0; i < ins.size(); i++) {
            stringBuilder.append(indent(indentTabs)).append("<variable>\n");
            indentTabs++;
            String varName = (String) ins.elementAt(i);
            Variable varObj = preprocessor.getVariableFromVariableName(varName);
            stringBuilder.append(indent(indentTabs)).append("<name>").append(varObj.getName()).append("</name>\n");
            if (!varObj.getTag().equals("")) {
                stringBuilder.append(indent(indentTabs)).append("<tag>").append(varObj.getTag()).append("</tag>\n");
            }

            if (!(varObj.getUnit().equals("")) && !(varObj.getUnit().equals("None"))) {
                stringBuilder.append(indent(indentTabs)).append("<unit>").append(varObj.getUnit()).append("</unit>\n");
            }

            stringBuilder.append(indent(indentTabs)).append("<statistics>\n");
            indentTabs++;
            stringBuilder.append(indent(indentTabs)).append("<min>").append(varObj.getMinValue()).append("</min>\n");
            stringBuilder.append(indent(indentTabs)).append("<max>").append(varObj.getMaxValue()).append("</max>\n");
            stringBuilder.append(indent(indentTabs)).append("<mean>").append(varObj.getMeanValue()).append("</mean>\n");
            stringBuilder.append(indent(indentTabs)).append("<median>").append(varObj.getMedianValue()).append("</median>\n");
            stringBuilder.append(indent(indentTabs)).append("<std>").append(varObj.getSTD()).append("</std>\n");
            stringBuilder.append(indent(indentTabs)).append("<variance>").append(varObj.getVariance()).append("</variance>\n");
            stringBuilder.append(indent(indentTabs)).append("<kurt>").append(varObj.getKurt()).append("</kurt>\n");
            stringBuilder.append(indent(indentTabs)).append("<skew>").append(varObj.getSkew()).append("</skew>\n");
            stringBuilder.append(indent(indentTabs)).append("<range>").append(varObj.getRange()).append("</range>\n");
            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</statistics>\n");

            if (model.getHasTimeStamps()) {
                long[] delays = (long[]) inDelays.elementAt(i);
                if ((delays.length == 1 && delays[0] == 0) || delays.length == 0) {
                    stringBuilder.append(indent(indentTabs)).append("<node>\n");
                    indentTabs++;
                    stringBuilder.append(indent(indentTabs)).append("<index>").append(inputIndex).append("</index>\n");
                    inputIndex = inputIndex + 1;
                    stringBuilder.append(indent(indentTabs)).append("<classification>input</classification>\n");
                    stringBuilder.append(indent(indentTabs)).append("<delay>").append(0.0).append("</delay>\n");
                    indentTabs--;
                    stringBuilder.append(indent(indentTabs)).append("</node>\n");
                } else {
                    for (long delay : delays) {
                        if (delay > 0) {
                            stringBuilder.append(indent(indentTabs)).append("<node>\n");
                            indentTabs++;
                            stringBuilder.append(indent(indentTabs)).append("<index>").append(inputIndex).append("</index>\n");
                            inputIndex = inputIndex + 1;
                            stringBuilder.append(indent(indentTabs)).append("<classification>input</classification>\n");
                            stringBuilder.append(indent(indentTabs)).append("<delay>").append(delay).append("</delay>\n");
                            indentTabs--;
                            stringBuilder.append(indent(indentTabs)).append("</node>\n");
                        }
                    }
                }
            } else {
                stringBuilder.append(indent(indentTabs)).append("<node>\n");
                indentTabs++;
                stringBuilder.append(indent(indentTabs)).append("<index>").append(inputIndex).append("</index>\n");
                inputIndex = inputIndex + 1;
                stringBuilder.append(indent(indentTabs)).append("<classification>input</classification>\n");
                indentTabs--;
                stringBuilder.append(indent(indentTabs)).append("</node>\n");
            }

            indentTabs--;
            stringBuilder.append(indent(indentTabs)).append("</variable>\n");
        }

        return indentTabs;
    }

    private String indent(int indentNumber) {
        String str = "";
        for (int i = 0; i < indentNumber; i++) {
            str = str + "\t";
        }
        return str;
    }

    private void setModelProperties(NolModel2 model, String prefix) {
        when(model.getName()).thenReturn(prefix + "Name");
        when(model.getComment()).thenReturn(prefix + "Comment");
        when(model.getHasTimeStamps()).thenReturn(true);

        Vector<String> inputs = createVariableNames("input");
        when(model.getInputVarNames()).thenReturn(inputs);
        when(model.getInputs()).thenReturn(inputs);
        Vector<long[]> inputDelays = createDelays(inputs.size());
        when(model.getInputDelays()).thenReturn(inputDelays);
        Vector<String> outputs = createVariableNames("output");
        when(model.getOutputVarNames()).thenReturn(outputs);
        when(model.getOutputs()).thenReturn(outputs);
        Vector<long[]> outputDelays = createDelays(outputs.size());
        when(model.getOutputDelays()).thenReturn(outputDelays);
        when(model.getTestingCorrcoef()).thenReturn(createDoublesVector());
        when(model.getTestingRmse()).thenReturn(createDoublesVector());
        when(model.getTrainingCorrcoef()).thenReturn(createDoublesVector());
        when(model.getTrainingRmse()).thenReturn(createDoublesVector());

        Vector<String> variableNames = new Vector<>();
        variableNames.addAll(inputs);
        variableNames.addAll(outputs);

        Preprocessor preprocessor = createPreprocessor(variableNames);
        when(model.getPreprocessor()).thenReturn(preprocessor);
    }

    private void verifyTestingCorrefIsMatching(NolModel2 model) {
        double[] expected = expectedTestingCorr((EnsembleModel) model.getModel());
        assertThat(expected.length, is(greaterThan(0)));
        for (int i = 0; i < expected.length; i++) {
            assertThat(sut.getTestingCorref().get(i), is(equalTo(Utilities.formatDouble(expected[i], ROUND_OFF_DIGITS))));
        }
    }

    private void verifyTestingRmseIsMatching(NolModel2 model) {
        double[] expected = expectedTestingRmse((EnsembleModel) model.getModel());
        assertThat(expected.length, is(greaterThan(0)));
        for (int i = 0; i < expected.length; i++) {
            assertThat(sut.getTestingRmse().get(i), is(equalTo(Utilities.formatDouble(expected[i], ROUND_OFF_DIGITS))));
        }
    }

    private void verifyTrainingCorrefIsMatching(NolModel2 model) {
        double[] expected = expectedTrainingCorr((EnsembleModel) model.getModel());
        assertThat(expected.length, is(greaterThan(0)));
        for (int i = 0; i < expected.length; i++) {
            assertThat(sut.getTrainingCorroef().get(i), is(equalTo(Utilities.formatDouble(expected[i], ROUND_OFF_DIGITS))));
        }
    }

    private void verifyTrainingRmseIsMatching(NolModel2 model) {
        double[] expected = expectedTrainingRmse((EnsembleModel) model.getModel());
        assertThat(expected.length, is(greaterThan(0)));
        for (int i = 0; i < expected.length; i++) {
            assertThat(sut.getTrainingRmse().get(i), is(equalTo(Utilities.formatDouble(expected[i], ROUND_OFF_DIGITS))));
        }
    }

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
