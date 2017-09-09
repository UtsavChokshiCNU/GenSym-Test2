package com.gensym.nols.data;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ClassicBpn;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.powermock.api.mockito.PowerMockito;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Random;
import java.util.Vector;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.mockito.Matchers.any;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class NolBpnModelTest {
    private static final String UNSCALED_WEIGHTS_CONTENT = "Unscaled Weights Content";
    private static final String WEIGHTS_CONTENT = "Weights Content";
    private static final String XML_FILE_CONTENT = "XML File Content";
    private static final Random randomGenerator = new Random();
    private static final int writeXmlFileResponse = 10;
    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();
    private ClassicBpn sutClassicBpn;
    private Vector<File> temporaryFiles = new Vector<>();
    private NolBpnModel sut;

    private static String readFileContents(String filepath)
            throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(filepath));
        return new String(encoded);
    }

    @Before
    public void setup() throws IOException, MathException {
        sutClassicBpn = createClassicBpn();
        String name = "NolBpnModel Name";
        Vector<String> outputs = createVariableNames("output");
        Vector<String> inputs = createVariableNames("input");
        Vector<long[]> outputDelays = createDelays(outputs.size());
        Vector<long[]> inputDelays = createDelays(inputs.size());
        Preprocessor preprocessor = createPreprocessor();
        sut = new NolBpnModel(sutClassicBpn, name, outputs, outputDelays, inputs, inputDelays, preprocessor);
    }

    @After
    public void teardown() {
        for (File temporaryFile : temporaryFiles) {
            temporaryFile.delete();
        }

        temporaryFiles.clear();
    }

    @Test
    public void test_setRunningParameter_always_setsRunningParameters() {
        // Arrange
        int iterations = randomGenerator.nextInt();
        int trainingMethod = randomGenerator.nextInt();
        int pcaFlag = randomGenerator.nextInt();

        // Act
        sut.setRunningParameter(iterations, trainingMethod, pcaFlag);

        // Assert
        assertThat(sut.getIterations(), is(equalTo(iterations)));
        assertThat(sut.getTrainingMethod(), is(equalTo(trainingMethod)));
        assertThat(sut.getPcaFlag(), is(equalTo(pcaFlag)));
    }

    @Test
    public void test_prepareDataStat_always_invokesPrepareDataStatMethod() throws MathException {
        // Arrange
        Matrix x = Matlib.createMatrix(anyInt(), anyInt());
        Matrix y = Matlib.createMatrix(anyInt(), anyInt());

        // Act
        sut.prepareDataStat(x, y);

        // Assert
        verify(sutClassicBpn, times(1)).prepareDataStat(x, y);
    }

    @Test
    public void test_writeBpnToFile_always_writesDataToFile() throws IOException, MathException {
        // Arrange
        File file = createFile();
        Matrix x = createMatrix(anyInt(), anyInt());
        Matrix y = createMatrix(anyInt(), anyInt());

        // Act
        sut.writeBpnToFile(file.getAbsolutePath(), x, y);

        // Assert
        verifyThatFileContentIsCorrect(file.getAbsolutePath(), x, y);
    }

    @Test
    public void test_writeBpnToFile_always_writesUnscaledWeights() throws IOException {
        // Arrange
        File file = createFile();

        // Act
        sut.writeBpnToFile(file.getAbsolutePath());

        // Assert
        verifyThatFileContentIsCorrect(file.getAbsolutePath());
    }

    @Test
    public void test_readBpnFromFile_always_readsWeights() throws IOException {
        // Arrange
        File file = createFile();

        // Act
        sut.readBpnFromFile(file.getAbsolutePath());

        // Assert
        verify(sutClassicBpn).readWeights(any(BufferedReader.class));
    }

    @Test
    public void test_getRMSE_always_returnsValueFromModelRmse() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(sut.getRMSE(), is(equalTo(sutClassicBpn.getRMSE())));
    }

    @Test
    public void test_train_always_preparesDataStat() throws IOException, MathException {
        // Arrange
        String[] rpcFileNames = new String[]{"RPC FileName 1", "RPC FileName 2", "RPC FileName 3"};
        // jbpnTrainer = 1 means errors is not returned
        int jbpnTrainer = 1;
        String errorMessage = "Error Message";
        NolClassicModelTrainer trainer = createClassicModelTrainer(rpcFileNames, jbpnTrainer, errorMessage);
        sut.setTrainer(trainer);
        Matrix x = createMatrix(anyInt(), anyInt());
        Matrix y = createMatrix(anyInt(), anyInt());

        // Act
        sut.train(x, y);

        // Assert
        verify(sutClassicBpn).prepareDataStat(x, y);
    }

    @Test
    public void test_train_errorsAreNotReturned_invokesReadWeight() throws IOException, MathException {
        // Arrange
        // Multiplying with 100 as train is done for iterations divide by 100.
        int iterations = anyInt() * 100;
        sut.setRunningParameter(iterations, randomGenerator.nextInt(), randomGenerator.nextInt());
        String[] rpcFileNames = new String[]{createFile().getAbsolutePath(), createFile().getAbsolutePath(), createFile().getAbsolutePath()};
        // jbpnTrainer = 1 means errors is not returned
        int jbpnTrainer = 1;
        String errorMessage = "Error Message";
        NolClassicModelTrainer trainer = createClassicModelTrainer(rpcFileNames, jbpnTrainer, errorMessage);
        sut.setTrainer(trainer);
        Matrix x = createMatrix(anyInt(), anyInt());
        Matrix y = createMatrix(anyInt(), anyInt());

        // Act
        sut.train(x, y);

        // Assert
        verify(sutClassicBpn, times(iterations / 100)).readWeights(any(BufferedReader.class));
    }

    @Test
    public void test_train_errorsAreNotReturned_invokesInformListenersForUpdate() throws IOException, MathException {
        // Arrange
        // Multiplying with 100 as train is done for iterations divide by 100.
        int iterations = anyInt() * 100;
        sut.setRunningParameter(iterations, randomGenerator.nextInt(), randomGenerator.nextInt());
        String[] rpcFileNames = new String[]{createFile().getAbsolutePath(), createFile().getAbsolutePath(), createFile().getAbsolutePath()};
        // jbpnTrainer = 1 means errors is not returned
        int jbpnTrainer = 1;
        String errorMessage = "Error Message";
        NolClassicModelTrainer trainer = createClassicModelTrainer(rpcFileNames, jbpnTrainer, errorMessage);
        sut.setTrainer(trainer);
        Matrix x = createMatrix(anyInt(), anyInt());
        Matrix y = createMatrix(anyInt(), anyInt());

        // Act
        sut.train(x, y);

        // Assert
        verify(trainer, times(iterations / 100)).informListeners("update", "");
    }

    @Test
    public void test_train_errorsAreNotReturned_invokesDeleteFiles() throws IOException, MathException {
        // Arrange
        // Multiplying with 100 as train is done for iterations divide by 100.
        int iterations = anyInt() * 100;
        sut.setRunningParameter(iterations, randomGenerator.nextInt(), randomGenerator.nextInt());
        String[] rpcFileNames = new String[]{createFile().getAbsolutePath(), createFile().getAbsolutePath(), createFile().getAbsolutePath()};
        // jbpnTrainer = 1 means errors is not returned
        int jbpnTrainer = 1;
        String errorMessage = "Error Message";
        NolClassicModelTrainer trainer = createClassicModelTrainer(rpcFileNames, jbpnTrainer, errorMessage);
        sut.setTrainer(trainer);
        Matrix x = createMatrix(anyInt(), anyInt());
        Matrix y = createMatrix(anyInt(), anyInt());

        // Act
        sut.train(x, y);

        // Assert
        verify(trainer, times(iterations / 100)).deleteFiles(rpcFileNames);
    }

    @Test
    public void test_train_errorsAreReturned_invokesInformListenersForError() throws IOException, MathException {
        // Arrange
        // Multiplying with 100 as train is done for iterations divide by 100.
        int iterations = anyInt() * 100;
        sut.setRunningParameter(iterations, randomGenerator.nextInt(), randomGenerator.nextInt());
        String[] rpcFileNames = new String[]{createFile().getAbsolutePath(), createFile().getAbsolutePath(), createFile().getAbsolutePath()};
        String errorMessage = "readErrorFromFile Message";
        Matrix x = createMatrix(anyInt(), anyInt());
        Matrix y = createMatrix(anyInt(), anyInt());

        // jbpnTrainer > 1 means errors is returned
        int jbpnTrainer = 2;
        NolClassicModelTrainer trainer = createClassicModelTrainer(rpcFileNames, jbpnTrainer, errorMessage);
        sut.setTrainer(trainer);

        // Act
        sut.train(x, y);

        // Assert
        verify(trainer).readErrorFromFile(rpcFileNames[1]);
        verify(trainer).informListeners("error", errorMessage);
    }

    @Test
    public void test_train_errorsAreNotReturned_invokesInformListenersForCompletion() throws IOException, MathException {
        // Arrange
        // Multiplying with 100 as train is done for iterations divide by 100.
        int iterations = anyInt() * 100;
        sut.setRunningParameter(iterations, randomGenerator.nextInt(), randomGenerator.nextInt());
        String[] rpcFileNames = new String[]{createFile().getAbsolutePath(), createFile().getAbsolutePath(), createFile().getAbsolutePath()};
        // jbpnTrainer = 1 means errors is not returned
        int jbpnTrainer = 1;
        String errorMessage = "Error Message";
        NolClassicModelTrainer trainer = createClassicModelTrainer(rpcFileNames, jbpnTrainer, errorMessage);
        sut.setTrainer(trainer);
        Matrix x = createMatrix(anyInt(), anyInt());
        Matrix y = createMatrix(anyInt(), anyInt());

        // Act
        sut.train(x, y);

        // Assert
        verify(trainer).informListeners("complete", "");
    }

    @Test
    public void test_getDescription_always_returnsModelDescription() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(sut.getDescription(), is(equalTo(sutClassicBpn.getDescription())));
    }

    @Test
    public void test_getParametersVector_always_returnsModelParametersVector() throws MathException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(sut.getParametersVector(), is(equalTo(sutClassicBpn.getParametersVector())));
    }

    @Test
    public void test_setParametersVector_always_invokesClassicBpnSetParametersVector() throws MathException {
        // Arrange
        Vector<String> parameters = new Vector<>();
        parameters.add("New Parameter 1");
        parameters.add("New Parameter 2");
        parameters.add("New Parameter 3");

        // Act
        sut.setParametersVector(parameters);

        // Assert
        verify(sutClassicBpn).setParametersVector(parameters);
    }

    @Test
    public void test_writeXMLFile_always_invokesClassicBpnWriteXMLFile() throws MathException, IOException {
        // Arrange
        int indentNumber = 3;
        File file = createFile();
        FileWriter fileWriter = null;
        BufferedWriter bufferedWriter = null;
        int retIndentNumber;

        try {
            fileWriter = new FileWriter(file.getAbsoluteFile());
            bufferedWriter = new BufferedWriter(fileWriter);

            // Act
            retIndentNumber = sut.writeXMLFile(bufferedWriter, indentNumber);
        } finally {
            if (bufferedWriter != null) {
                bufferedWriter.close();
            } else if (fileWriter != null) {
                fileWriter.close();
            }
        }

        // Assert
        String content = readFileContents(file.getAbsolutePath());
        assertThat(content, is(equalTo(indentNumber + XML_FILE_CONTENT)));
        assertThat(retIndentNumber, is(equalTo(writeXmlFileResponse)));
    }

    // -- Helper Methods --

    private int anyInt() {
        // Adding 2 to always return an integer between 2 and 11
        return randomGenerator.nextInt(10) + 2;
    }

    private ClassicBpn createClassicBpn() throws IOException, MathException {
        ClassicBpn classicBpn = mock(ClassicBpn.class);

        PowerMockito.when(classicBpn.getDescription()).thenReturn("ClassicBpn Description");

        Vector<String> parameters = new Vector<>();
        parameters.add("Parameter 1");
        parameters.add("Parameter 2");
        parameters.add("Parameter 3");
        PowerMockito.when(classicBpn.getParametersVector()).thenReturn(parameters);

        PowerMockito.doAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            Matrix x = invocation.getArgumentAt(1, Matrix.class);
            Matrix y = invocation.getArgumentAt(2, Matrix.class);

            String content = getMatrixContentString(x, y);
            target.write(content, 0, content.length());
            return null;
        }).when(classicBpn).writeData(any(BufferedWriter.class), any(Matrix.class), any(Matrix.class));

        PowerMockito.doAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            target.write(UNSCALED_WEIGHTS_CONTENT);
            return null;
        }).when(classicBpn).writeUnscaledWeights(any(BufferedWriter.class));

        PowerMockito.doAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            target.write(WEIGHTS_CONTENT);
            return null;
        }).when(classicBpn).writeWeights(any(BufferedWriter.class));

        PowerMockito.when(classicBpn.writeXMLFile(any(BufferedWriter.class), any(int.class))).then(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            int indentNumber = invocation.getArgumentAt(1, int.class);

            if (target != null) {
                target.write(indentNumber + XML_FILE_CONTENT);
            }

            return writeXmlFileResponse;
        });

        when(classicBpn.getRMSE()).thenReturn(randomGenerator.nextDouble());

        return classicBpn;
    }

    private Vector<long[]> createDelays(int variablesCount) {
        Vector<long[]> delays = new Vector<>();
        for (int i = 0; i < variablesCount; i++) {
            int variableDelaysCount = 3;
            long[] delay = new long[variableDelaysCount];
            for (int j = 0; j < delay.length; j++) {
                delay[j] = randomGenerator.nextLong();
            }

            delays.add(delay);
        }

        return delays;
    }

    private File createFile() throws IOException {
        temporaryFiles.addElement(temporaryFolder.newFile());
        return temporaryFiles.lastElement();
    }

    private Matrix createMatrix(int rows, int cols) {
        Matrix matrix = Matlib.createMatrix(rows, cols);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                matrix.set(r, c, randomGenerator.nextInt());
            }
        }

        return matrix;
    }

    private Preprocessor createPreprocessor() {
        return mock(Preprocessor.class);
    }

    private NolClassicModelTrainer createClassicModelTrainer(String[] rpcFileNames, int jbpnTrainer, String errorMessage) throws IOException {
        NolClassicModelTrainer trainer = mock(NolClassicModelTrainer.class);

        when(trainer.makeRPCfileNames()).thenReturn(rpcFileNames);
        when(trainer.jbpn_trainer(any(String.class), any(String.class))).thenReturn(jbpnTrainer);
        when(trainer.readErrorFromFile(any(String.class))).thenReturn(errorMessage);

        return trainer;
    }

    private Vector<String> createVariableNames(String prefix) {
        int variableSamplesCount = 3;
        Vector<String> variableNames = new Vector<>();
        for (int i = 1; i <= variableSamplesCount; i++) {
            variableNames.add(prefix + i);
        }

        return variableNames;
    }

    private String getMatrixContentString(Matrix x, Matrix y) {
        String content = "Matrix X:";
        for (int r = 0; r < x.getRows(); r++) {
            for (int c = 0; c < x.getCols(); c++) {
                content += r + "," + c + "=" + x.get(r, c);
            }
        }

        content += "Matrix Y:";
        for (int r = 0; r < y.getRows(); r++) {
            for (int c = 0; c < y.getCols(); c++) {
                content += r + "," + c + "=" + y.get(r, c);
            }
        }
        return content;
    }

    private void verifyThatFileContentIsCorrect(String filePath) throws IOException {
        String fileContent = readFileContents(filePath);
        assertThat(fileContent, is(equalTo(UNSCALED_WEIGHTS_CONTENT)));
    }

    private void verifyThatFileContentIsCorrect(String filePath, Matrix x, Matrix y) throws IOException {
        double pcaFactor = 0;
        if (sut.getPcaFlag() > 0) pcaFactor = 0.02;

        String expected = getMatrixContentString(x, y);
        expected += "100, 0.0, " + sut.getTrainingMethod() + ", " + pcaFactor + " ; Control vector for training";
        expected += "\r\n";
        expected += WEIGHTS_CONTENT;

        String fileContent = readFileContents(filePath);
        assertThat(fileContent, is(equalTo(expected)));
    }
}
